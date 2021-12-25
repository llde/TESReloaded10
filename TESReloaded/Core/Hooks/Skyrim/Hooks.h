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
	DetourAttach(&(PVOID&)CreateVertexShader,		&CreateVertexShaderHook);
	DetourAttach(&(PVOID&)CreatePixelShader,		&CreatePixelShaderHook);
	DetourAttach(&(PVOID&)LoadBloodSplatterShader,	&LoadBloodSplatterShaderHook);
	DetourAttach(&(PVOID&)LoadDistantTreeShader,	&LoadDistantTreeShaderHook);
	DetourAttach(&(PVOID&)LoadGrassShader,			&LoadGrassShaderHook);
	DetourAttach(&(PVOID&)LoadParticleShader,		&LoadParticleShaderHook);
	DetourAttach(&(PVOID&)LoadSkyShader,			&LoadSkyShaderHook);
	DetourAttach(&(PVOID&)LoadEffectShader,			&LoadEffectShaderHook);
	DetourAttach(&(PVOID&)LoadLightingShader,		&LoadLightingShaderHook);
	DetourAttach(&(PVOID&)LoadUtilityShader,		&LoadUtilityShaderHook);
	DetourAttach(&(PVOID&)LoadWaterShader,			&LoadWaterShaderHook);
	DetourAttach(&(PVOID&)LoadImageSpaceShaders,	&LoadImageSpaceShadersHook);
	DetourAttach(&(PVOID&)LoadLightingShaderExtra,	&LoadLightingShaderExtraHook);
	DetourTransactionCommit();

	SafeWrite32(0x00CDB659, sizeof(RenderManager));
	SafeWrite8(0x00CCBD66,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x00CCC676,	sizeof(NiD3DPixelShaderEx));

}