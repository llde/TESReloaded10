Memory Mem;

CommandManager*		TheCommandManager = NULL;
SettingManager*		TheSettingManager = NULL;
ShaderManager*		TheShaderManager = NULL;
TextureManager*		TheTextureManager = NULL;
RenderManager*		TheRenderManager = NULL;
FrameRateManager*	TheFrameRateManager = NULL;
GameEventManager*	TheGameEventManager = NULL;
GameMenuManager*	TheGameMenuManager = NULL;
ShadowManager*		TheShadowManager = NULL;
OcclusionManager*	TheOcclusionManager = NULL;
EquipmentManager*	TheEquipmentManager = NULL;
ScriptManager*		TheScriptManager = NULL;
CameraManager*		TheCameraManager = NULL;
DebugManager*		TheDebugManager = nullptr;

Main*					Global			 = NULL;
TES*					Tes				 = NULL;
PlayerCharacter*		Player			 = NULL;
SceneGraph*				WorldSceneGraph  = NULL;
MainDataHandler*		DataHandler		 = NULL;
MenuInterfaceManager*	InterfaceManager = NULL;
QueuedModelLoader*		ModelLoader		 = NULL;
ShadowSceneNode*		SceneNode		 = NULL;

void InitializeManagers() {

	TextureManager::Initialize();
	ShaderManager::Initialize();
	FrameRateManager::Initialize();
	GameMenuManager::Initialize();
	GameEventManager::Initialize();
	ShadowManager::Initialize();
	OcclusionManager::Initialize();
	EquipmentManager::Initialize();
	ScriptManager::Initialize();
	CameraManager::Initialize();
}