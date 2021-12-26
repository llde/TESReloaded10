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
	DetourAttach(&(PVOID&)LoadForm,					&LoadFormHook);
	DetourAttach(&(PVOID&)SetCameraState,			&SetCameraStateHook);
	DetourAttach(&(PVOID&)ManageButtonEvent,		&ManageButtonEventHook);
	DetourAttach(&(PVOID&)SetCameraPosition,		&SetCameraPositionHook);
	DetourTransactionCommit();

	SafeWrite8(0x00CCBD66,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x00CCC676,	sizeof(NiD3DPixelShaderEx));
	SafeWrite8(0x0048BC15,	sizeof(TESRegionEx));
	SafeWrite32(0x00CDB659, sizeof(RenderManager));
	SafeWrite32(0x00442B22, sizeof(TESWeatherEx));
	SafeWrite32(0x004EF7F5, sizeof(TESWeatherEx));

	SafeWrite8(0x00698BBB, 0); // Stops to clear the depth buffer when rendering the 1st person node
	SafeWrite8(0x0083F69B, 0); // Stops PlayerCharacter fading

	SafeWriteJump(kRenderInterface,				(UInt32)RenderInterfaceHook);
	SafeWriteJump(kRenderingGeometry,			(UInt32)RenderingGeometryHook);
	SafeWriteJump(kSetRegionEditorName,			(UInt32)SetRegionEditorNameHook);
	SafeWriteJump(kSetWeatherEditorName,		(UInt32)SetWeatherEditorNameHook);
	SafeWriteJump(kHitEventHook,				(UInt32)HitEventHook);

	if (TheSettingManager->SettingsMain.ShadowMode.NearQuality) {
		SafeWriteJump(kSetShadowDistance,		(UInt32)SetShadowDistanceHook);
		SafeWriteJump(kSetShadowDistanceShader, (UInt32)SetShadowDistanceShaderHook);
	}
	

}