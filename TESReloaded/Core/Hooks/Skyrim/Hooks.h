#pragma once

void AttachHooks() {

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ReadSetting,				&ReadSettingHook);
	DetourAttach(&(PVOID&)WriteSetting,				&WriteSettingHook);
	DetourAttach(&(PVOID&)LoadGame,					&LoadGameHook);
	DetourAttach(&(PVOID&)NewMain,					&NewMainHook);
	DetourAttach(&(PVOID&)InitializeRenderer,		&InitializeRendererHook);
	DetourAttach(&(PVOID&)NewTES,					&NewTESHook);
	DetourAttach(&(PVOID&)NewPlayerCharacter,		&NewPlayerCharacterHook);
	DetourAttach(&(PVOID&)NewSceneGraph,			&NewSceneGraphHook);
	DetourAttach(&(PVOID&)NewMainDataHandler,		&NewMainDataHandlerHook);
	DetourAttach(&(PVOID&)NewMenuInterfaceManager,	&NewMenuInterfaceManagerHook);
	DetourAttach(&(PVOID&)NewQueuedModelLoader,		&NewQueuedModelLoaderHook);
	DetourTransactionCommit();

	SafeWrite32(0x00CDB659, sizeof(RenderManager));

}