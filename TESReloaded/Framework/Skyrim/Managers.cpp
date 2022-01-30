CommandManager*		TheCommandManager = NULL;
SettingManager*		TheSettingManager = NULL;
ShaderManager*		TheShaderManager = NULL;
TextureManager*		TheTextureManager = NULL;
RenderManager*		TheRenderManager = NULL;
FrameRateManager*	TheFrameRateManager = NULL;
GameEventManager*	TheGameEventManager = NULL;
GameMenuManager*	TheGameMenuManager = NULL;
CameraManager*		TheCameraManager = NULL;

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
	CameraManager::Initialize();

}