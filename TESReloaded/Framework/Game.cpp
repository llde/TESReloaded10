#if defined(OBLIVION)
#define kNewMain				 0x00404A00
#define kInitializeRenderer		 0x004052F0
#define kNewTES					 0x00441970
#define kNewPlayerCharacter		 0x0066A740
#define kNewSceneGraph			 0x004114E0
#define kNewMasterDataHandler	 0x00446D80
#define kNewMenuInterfaceManager 0x005802B0
#define kNewQueuedModelLoader	 0x0043E950
#define kShadowSceneNode		 0x00B42F54
#define SetMenuManager           MenuManager = NULL
#elif defined(SKYRIM)
#define kNewMain				 0x0069BFE0
#define kInitializeRenderer		 0x00691030
#define kNewTES					 0x00435C10
#define kNewPlayerCharacter		 0x0074DB40
#define kNewSceneGraph			 0x0069F1F0
#define kNewMasterDataHandler	 0x0043DE50
#define kNewMenuInterfaceManager 0x00A5DE30 // Special case: this cannot be detoured because it is called in preinit and the plugin is not attached yet
#define kNewQueuedModelLoader	 0x00430470
#define kShadowSceneNode		 0x00000000
#define SetMenuManager			 MenuManager = *(MenuInterfaceManager**)0x012E3548
#endif

Main*					Global			= NULL;
TES*					Tes				= NULL;
PlayerCharacter*		Player			= NULL;
SceneGraph*				WorldSceneGraph = NULL;
MasterDataHandler*		DataHandler		= NULL;
MenuInterfaceManager*	MenuManager		= NULL;
QueuedModelLoader*		ModelLoader		= NULL;
ShadowSceneNode*		SceneNode		= NULL;

class GameInitialization {
public:
	Main*					TrackNewMain(HWND, HINSTANCE);
	NiDX9Renderer*			TrackInitializeRenderer();
#if defined(OBLIVION)
	TES*					TrackNewTES(char*, NiNode*, NiNode*, Sky*);
#elif defined(SKYRIM)
	TES*					TrackNewTES(char*, NiNode*, NiNode*, Sky*, NiNode*);
#endif
	PlayerCharacter*		TrackNewPlayerCharacter();
	SceneGraph*				TrackNewSceneGraph(char*, UInt8, NiCamera*);
	MasterDataHandler*		TrackNewMasterDataHandler();
	MenuInterfaceManager*	TrackNewMenuInterfaceManager();
	QueuedModelLoader*		TrackNewQueuedModelLoader();
};

Main* (__thiscall GameInitialization::* NewMain)(HWND, HINSTANCE);
Main* (__thiscall GameInitialization::* TrackNewMain)(HWND, HINSTANCE);
Main* GameInitialization::TrackNewMain(HWND Window, HINSTANCE Instance) { SetMenuManager; Global = (Main*)(this->*NewMain)(Window, Instance); return Global; }

NiDX9Renderer* (__thiscall GameInitialization::* InitializeRenderer)();
NiDX9Renderer* (__thiscall GameInitialization::* TrackInitializeRenderer)();
NiDX9Renderer* GameInitialization::TrackInitializeRenderer() { TheRenderManager = (RenderManager*)(this->*InitializeRenderer)(); TheRenderManager->Initialize(); InitializeManagers(); TheShaderManager->CreateEffects(); return TheRenderManager; }

#if defined(OBLIVION)
TES* (__thiscall GameInitialization::* NewTES)(char*, NiNode*, NiNode*, Sky*);
TES* (__thiscall GameInitialization::* TrackNewTES)(char*, NiNode*, NiNode*, Sky*);
TES* GameInitialization::TrackNewTES(char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky) { Tes = (TES*)(this->*NewTES)(RootData, ObjectLODRoot, LandLOD, Sky); SceneNode = *(ShadowSceneNode**)kShadowSceneNode; return Tes; }
#elif defined(SKYRIM)
TES* (__thiscall GameInitialization::* NewTES)(char*, NiNode*, NiNode*, Sky*, NiNode*);
TES* (__thiscall GameInitialization::* TrackNewTES)(char*, NiNode*, NiNode*, Sky*, NiNode*);
TES* GameInitialization::TrackNewTES(char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky, NiNode* WaterLOD) { Tes = (TES*)(this->*NewTES)(RootData, ObjectLODRoot, LandLOD, Sky, WaterLOD); SceneNode = *(ShadowSceneNode**)kShadowSceneNode; return Tes; }
#endif

PlayerCharacter* (__thiscall GameInitialization::* NewPlayerCharacter)();
PlayerCharacter* (__thiscall GameInitialization::* TrackNewPlayerCharacter)();
PlayerCharacter* GameInitialization::TrackNewPlayerCharacter() { Player = (PlayerCharacter*)(this->*NewPlayerCharacter)(); return Player; }

SceneGraph* (__thiscall GameInitialization::* NewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* (__thiscall GameInitialization::* TrackNewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* GameInitialization::TrackNewSceneGraph(char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) { SceneGraph* SG = (SceneGraph*)(this->*NewSceneGraph)(Name, IsMinFarPlaneDistance, Camera); if (!strcmp(Name, "World")) WorldSceneGraph = SG; return SG; }

MasterDataHandler* (__thiscall GameInitialization::* NewMasterDataHandler)();
MasterDataHandler* (__thiscall GameInitialization::* TrackNewMasterDataHandler)();
MasterDataHandler* GameInitialization::TrackNewMasterDataHandler() { DataHandler = (MasterDataHandler*)(this->*NewMasterDataHandler)(); TheScriptManager->LoadForms(); TheEquipmentManager->LoadForms(); return DataHandler; }

MenuInterfaceManager* (__thiscall GameInitialization::* NewMenuInterfaceManager)();
MenuInterfaceManager* (__thiscall GameInitialization::* TrackNewMenuInterfaceManager)();
MenuInterfaceManager* GameInitialization::TrackNewMenuInterfaceManager() { MenuManager = (MenuInterfaceManager*)(this->*NewMenuInterfaceManager)(); return MenuManager; }

QueuedModelLoader* (__thiscall GameInitialization::* NewQueuedModelLoader)();
QueuedModelLoader* (__thiscall GameInitialization::* TrackNewQueuedModelLoader)();
QueuedModelLoader* GameInitialization::TrackNewQueuedModelLoader() { ModelLoader = (QueuedModelLoader*)(this->*NewQueuedModelLoader)(); return ModelLoader; }

void CreateGameInitializationHook() {

	*((int*)&NewMain)					= kNewMain;
	TrackNewMain						= &GameInitialization::TrackNewMain;
	*((int*)&InitializeRenderer)		= kInitializeRenderer;
	TrackInitializeRenderer				= &GameInitialization::TrackInitializeRenderer;
	*((int*)&NewTES)					= kNewTES;
	TrackNewTES							= &GameInitialization::TrackNewTES;
	*((int*)&NewPlayerCharacter)		= kNewPlayerCharacter;
	TrackNewPlayerCharacter				= &GameInitialization::TrackNewPlayerCharacter;
	*((int*)&NewSceneGraph)				= kNewSceneGraph;
	TrackNewSceneGraph					= &GameInitialization::TrackNewSceneGraph;
	*((int*)&NewMasterDataHandler)		= kNewMasterDataHandler;
	TrackNewMasterDataHandler			= &GameInitialization::TrackNewMasterDataHandler;
	*((int*)&NewMenuInterfaceManager)	= kNewMenuInterfaceManager;
	TrackNewMenuInterfaceManager		= &GameInitialization::TrackNewMenuInterfaceManager;
	*((int*)&NewQueuedModelLoader)		= kNewQueuedModelLoader;
	TrackNewQueuedModelLoader			= &GameInitialization::TrackNewQueuedModelLoader;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)NewMain,					*((PVOID*)&TrackNewMain));
	DetourAttach(&(PVOID&)InitializeRenderer,		*((PVOID*)&TrackInitializeRenderer));
	DetourAttach(&(PVOID&)NewTES,					*((PVOID*)&TrackNewTES));
	DetourAttach(&(PVOID&)NewPlayerCharacter,		*((PVOID*)&TrackNewPlayerCharacter));
	DetourAttach(&(PVOID&)NewSceneGraph,			*((PVOID*)&TrackNewSceneGraph));
	DetourAttach(&(PVOID&)NewMasterDataHandler,		*((PVOID*)&TrackNewMasterDataHandler));
	DetourAttach(&(PVOID&)NewMenuInterfaceManager,	*((PVOID*)&TrackNewMenuInterfaceManager));
	DetourAttach(&(PVOID&)NewQueuedModelLoader,		*((PVOID*)&TrackNewQueuedModelLoader));
	DetourTransactionCommit();

#if defined(OBLIVION)
	SafeWrite32(0x0076BD75, sizeof(RenderManager));
#elif defined(SKYRIM)
	SafeWrite32(0x00CDB659, sizeof(RenderManager));
#endif

}
