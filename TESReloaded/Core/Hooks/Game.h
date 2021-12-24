#pragma once

static NiDX9Renderer* (__thiscall* InitializeRenderer)(NiDX9Renderer*) = (NiDX9Renderer* (__thiscall*)(NiDX9Renderer*))Hooks::InitializeRenderer;
static NiDX9Renderer* __fastcall InitializeRendererHook(NiDX9Renderer* This, UInt32 edx) {

	TheRenderManager = (RenderManager*)(*InitializeRenderer)(This);
	TheRenderManager->Initialize();
	InitializeManagers();
	TheShaderManager->CreateEffects();
	return TheRenderManager;

}

static PlayerCharacter* (__thiscall* NewPlayerCharacter)(PlayerCharacter*) = (PlayerCharacter* (__thiscall*)(PlayerCharacter*))Hooks::NewPlayerCharacter;
static PlayerCharacter* __fastcall NewPlayerCharacterHook(PlayerCharacter* This, UInt32 edx) {

	Player = (*NewPlayerCharacter)(This);
	return Player;

}

static SceneGraph* (__thiscall* NewSceneGraph)(SceneGraph*, char*, UInt8, NiCamera*) = (SceneGraph* (__thiscall*)(SceneGraph*, char*, UInt8, NiCamera*))Hooks::NewSceneGraph;
static SceneGraph* __fastcall NewSceneGraphHook(SceneGraph* This, UInt32 edx, char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) {
	
	SceneGraph* SG = (*NewSceneGraph)(This, Name, IsMinFarPlaneDistance, Camera);
	
	if (!strcmp(Name, "World")) WorldSceneGraph = SG;
	return SG;

}

static MainDataHandler* (__thiscall* NewMainDataHandler)(MainDataHandler*) = (MainDataHandler* (__thiscall*)(MainDataHandler*))Hooks::NewMainDataHandler;
static MainDataHandler* __fastcall NewMainDataHandlerHook(MainDataHandler* This, UInt32 edx) {
	
	DataHandler = (*NewMainDataHandler)(This);
	TheScriptManager->LoadForms();
	TheEquipmentManager->LoadForms();
	return DataHandler;

}

static MenuInterfaceManager* (__thiscall* NewMenuInterfaceManager)(MenuInterfaceManager*) = (MenuInterfaceManager* (__thiscall*)(MenuInterfaceManager*))Hooks::NewMenuInterfaceManager;
static MenuInterfaceManager* __fastcall NewMenuInterfaceManagerHook(MenuInterfaceManager* This, UInt32 edx) {

	InterfaceManager = (*NewMenuInterfaceManager)(This);
	return InterfaceManager;

}

static QueuedModelLoader* (__thiscall* NewQueuedModelLoader)(QueuedModelLoader*) = (QueuedModelLoader* (__thiscall*)(QueuedModelLoader*))Hooks::NewQueuedModelLoader;
static QueuedModelLoader* __fastcall NewQueuedModelLoaderHook(QueuedModelLoader* This, UInt32 edx) {

	ModelLoader = (*NewQueuedModelLoader)(This);
	return ModelLoader;

}