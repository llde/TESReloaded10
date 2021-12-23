CommandManager*		TheCommandManager = NULL;
TextureManager*		TheTextureManager = NULL;
ShaderManager*		TheShaderManager = NULL;
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