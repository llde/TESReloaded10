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
	DetourAttach(&(PVOID&)Render,					&RenderHook);
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders, &ProcessImageSpaceShadersHook);
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,	&RenderWorldSceneGraphHook);
	DetourAttach(&(PVOID&)RenderFirstPerson,		&RenderFirstPersonHook);
	DetourAttach(&(PVOID&)SetupRenderingPass,		&SetupRenderingPassHook);
	DetourTransactionCommit();

	SafeWrite8(0x00CCBD66,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x00CCC676,	sizeof(NiD3DPixelShaderEx));
	SafeWrite32(0x00CDB659, sizeof(RenderManager));

	SafeWrite8(0x00698BBB, 0); // Stops to clear the depth buffer when rendering the 1st person node

	SafeWriteJump(kRenderInterface,				(UInt32)RenderInterfaceHook);
	SafeWriteJump(kRenderingGeometry,			(UInt32)RenderingGeometryHook);

	if (TheSettingManager->SettingsMain.ShadowMode.NearQuality) {
		SafeWriteJump(kSetShadowDistance,		(UInt32)SetShadowDistance);
		SafeWriteJump(kSetShadowDistanceShader, (UInt32)SetShadowDistanceShader);
	}
	

}