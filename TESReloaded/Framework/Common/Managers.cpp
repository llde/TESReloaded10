CommandManager*		TheCommandManager = NULL;
SettingManager*		TheSettingManager = NULL;
ShaderManager*		TheShaderManager = NULL;
TextureManager*		TheTextureManager = NULL;
RenderManager*		TheRenderManager = NULL;
FrameRateManager*	TheFrameRateManager = NULL;
GameEventManager*	TheGameEventManager = NULL;
GameMenuManager*	TheGameMenuManager = NULL;
KeyboardManager*	TheKeyboardManager = NULL;
ShadowManager*		TheShadowManager = NULL;
OcclusionManager*	TheOcclusionManager = NULL;
EquipmentManager*	TheEquipmentManager = NULL;
ScriptManager*		TheScriptManager = NULL;
CameraManager*		TheCameraManager = NULL;

Main*					Global			= NULL;
TES*					Tes				= NULL;
PlayerCharacter*		Player			= NULL;
SceneGraph*				WorldSceneGraph = NULL;
MasterDataHandler*		DataHandler		= NULL;
MenuInterfaceManager*	MenuManager		= NULL;
QueuedModelLoader*		ModelLoader		= NULL;
ShadowSceneNode*		SceneNode		= NULL;

void InitializeManagers() {

	new TextureManager();
	new ShaderManager();
	new FrameRateManager();
	new GameMenuManager();
	new KeyboardManager();
	new GameEventManager();
	new ShadowManager();
	new OcclusionManager();
	new EquipmentManager();
	new ScriptManager();
	new CameraManager();

}