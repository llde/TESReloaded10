#pragma once

void AttachHooks() {

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ReadSetting,					&ReadSettingHook);
	DetourAttach(&(PVOID&)WriteSetting,					&WriteSettingHook);
	DetourAttach(&(PVOID&)LoadGame,						&LoadGameHook);
	DetourAttach(&(PVOID&)NewMain,						&NewMainHook);
	DetourAttach(&(PVOID&)InitializeRenderer,			&InitializeRendererHook);
	DetourAttach(&(PVOID&)NewTES,						&NewTESHook);
	DetourAttach(&(PVOID&)NewPlayerCharacter,			&NewPlayerCharacterHook);
	DetourAttach(&(PVOID&)NewSceneGraph,				&NewSceneGraphHook);
	DetourAttach(&(PVOID&)NewMainDataHandler,			&NewMainDataHandlerHook);
	DetourAttach(&(PVOID&)NewMenuInterfaceManager,		&NewMenuInterfaceManagerHook);
	DetourAttach(&(PVOID&)NewQueuedModelLoader,			&NewQueuedModelLoaderHook);
	DetourAttach(&(PVOID&)CreateVertexShader,			&CreateVertexShaderHook);
	DetourAttach(&(PVOID&)CreatePixelShader,			&CreatePixelShaderHook);
	DetourAttach(&(PVOID&)Render,						&RenderHook);
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders,		&ProcessImageSpaceShadersHook);
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,		&RenderWorldSceneGraphHook);
	DetourAttach(&(PVOID&)RenderFirstPerson,			&RenderFirstPersonHook);
	DetourAttach(&(PVOID&)SetupRenderingPass,			&SetupRenderingPassHook);
	DetourAttach(&(PVOID&)RenderReflections,			&RenderReflectionsHook);
	DetourAttach(&(PVOID&)ShowDetectorWindow,			&ShowDetectorWindowHook);
	DetourAttach(&(PVOID&)LoadForm,						&LoadFormHook);
	DetourTransactionCommit();
	
	
	SafeWrite8(0x00BE1690,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x00BE1DFB,	sizeof(NiD3DPixelShaderEx));
	SafeWrite32(0x00E7624D, sizeof(RenderManager));

	SafeWrite16(0x0086A170, 0x9090);		// Avoids to pause the game when ALT-TAB

	SafeWriteCall(0x007D0B48, (UInt32)MainMenuMusicFix);
	SafeWriteCall(0x007D6CE7, (UInt32)MainMenuMusicFix);

}