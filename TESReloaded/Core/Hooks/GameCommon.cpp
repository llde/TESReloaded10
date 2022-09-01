#pragma once

NiDX9Renderer* (__thiscall* InitializeRenderer)(NiDX9Renderer*) = (NiDX9Renderer* (__thiscall*)(NiDX9Renderer*))Hooks::InitializeRenderer;
NiDX9Renderer* __fastcall InitializeRendererHook(NiDX9Renderer* This, UInt32 edx) {

	TheRenderManager = (RenderManager*)(*InitializeRenderer)(This);
	TheRenderManager->Initialize();
	InitializeManagers();
	TheShaderManager->CreateEffects();
	return TheRenderManager;

}

PlayerCharacter* (__thiscall* NewPlayerCharacter)(PlayerCharacter*) = (PlayerCharacter* (__thiscall*)(PlayerCharacter*))Hooks::NewPlayerCharacter;
PlayerCharacter* __fastcall NewPlayerCharacterHook(PlayerCharacter* This, UInt32 edx) {

	Player = (*NewPlayerCharacter)(This);
	return Player;

}

SceneGraph* (__thiscall* NewSceneGraph)(SceneGraph*, char*, UInt8, NiCamera*) = (SceneGraph* (__thiscall*)(SceneGraph*, char*, UInt8, NiCamera*))Hooks::NewSceneGraph;
SceneGraph* __fastcall NewSceneGraphHook(SceneGraph* This, UInt32 edx, char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) {
	
	SceneGraph* SG = (*NewSceneGraph)(This, Name, IsMinFarPlaneDistance, Camera);
	
	if (!strcmp(Name, "World")) WorldSceneGraph = SG;
	return SG;

}

MenuInterfaceManager* (__thiscall* NewMenuInterfaceManager)(MenuInterfaceManager*) = (MenuInterfaceManager* (__thiscall*)(MenuInterfaceManager*))Hooks::NewMenuInterfaceManager;
MenuInterfaceManager* __fastcall NewMenuInterfaceManagerHook(MenuInterfaceManager* This, UInt32 edx) {

	InterfaceManager = (*NewMenuInterfaceManager)(This);
	return InterfaceManager;

}

QueuedModelLoader* (__thiscall* NewQueuedModelLoader)(QueuedModelLoader*) = (QueuedModelLoader* (__thiscall*)(QueuedModelLoader*))Hooks::NewQueuedModelLoader;
QueuedModelLoader* __fastcall NewQueuedModelLoaderHook(QueuedModelLoader* This, UInt32 edx) {

	ModelLoader = (*NewQueuedModelLoader)(This);
	return ModelLoader;

}