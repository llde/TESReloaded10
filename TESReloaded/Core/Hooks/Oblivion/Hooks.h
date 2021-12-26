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
	DetourAttach(&(PVOID&)SetShaderPackage,			&SetShaderPackageHook);
	DetourAttach(&(PVOID&)Render,					&RenderHook);
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders, &ProcessImageSpaceShadersHook);
	DetourAttach(&(PVOID&)ShowDetectorWindow,		&ShowDetectorWindowHook);
	DetourAttach(&(PVOID&)SetupShaderPrograms,		&SetupShaderProgramsHook);
	DetourAttach(&(PVOID&)EndTargetGroup,			&EndTargetGroupHook);
	DetourAttach(&(PVOID&)HDRRender,				&HDRRenderHook);
	DetourAttach(&(PVOID&)WaterHeightMapRender,		&WaterHeightMapRenderHook);
	DetourAttach(&(PVOID&)FarPlane,					&FarPlaneHook);
	DetourAttach(&(PVOID&)SetSamplerState,			&SetSamplerStateHook);
	DetourAttach(&(PVOID&)RenderReflections,		&RenderReflectionsHook);
	DetourAttach(&(PVOID&)WaterCullingProcess,		&WaterCullingProcessHook);
	DetourAttach(&(PVOID&)SaveGameScreenshot,		&SaveGameScreenshotHook);
	DetourAttach(&(PVOID&)LoadForm,					&LoadFormHook);
	DetourAttach(&(PVOID&)RunScript,				&RunScriptHook);
	DetourTransactionCommit();
	
	SafeWrite8(0x00801BCB,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x008023A1,	sizeof(NiD3DPixelShaderEx));
	SafeWrite8(0x00448843,	sizeof(TESRegionEx));
	SafeWrite8(0x004A2EFF,	sizeof(TESRegionEx));
	SafeWrite32(0x0076BD75, sizeof(RenderManager));
	SafeWrite32(0x004486ED, sizeof(TESWeatherEx));
	SafeWrite32(0x0044CBE3, sizeof(TESWeatherEx));

	SafeWrite8(0x00A38280, 0x5A); // Fixes the "purple water bug"
	SafeWrite32(0x0049BFAF, WaterReflectionMapSize); // Constructor
	SafeWrite32(0x007C1045, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C104F, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C10F9, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C1103, WaterReflectionMapSize); // RenderedSurface

	SafeWriteJump(kDetectorWindowCreateTreeView,	(UInt32)DetectorWindowCreateTreeViewHook);
	SafeWriteJump(kDetectorWindowDumpAttributes,	(UInt32)DetectorWindowDumpAttributesHook);
	SafeWriteJump(kDetectorWindowConsoleCommand,	(UInt32)DetectorWindowConsoleCommandHook);
	SafeWriteJump(kRenderInterface,					(UInt32)RenderInterfaceHook);
	SafeWriteJump(kSkipFogPass,						(UInt32)SkipFogPassHook);
	SafeWriteJump(kSetRegionEditorName,				(UInt32)SetRegionEditorNameHook);
	SafeWriteJump(kSetWeatherEditorName,			(UInt32)SetWeatherEditorNameHook);
	SafeWriteJump(kHitEventHook,					(UInt32)HitEventHook);
	SafeWriteJump(kDetectorWindowScale,				kDetectorWindowScaleReturn); // Avoids to add the scale to the node description in the detector window
	SafeWriteJump(0x00553EAC,						0x00553EB2); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x007D1BC4,						0x007D1BFD); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x007D1BCD,						0x007D1BFD); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x0049C3A2,						0x0049C41D); // Avoids to manage the cells culling for reflections
	SafeWriteJump(0x0049C8CB,						0x0049C931); // Avoids to manage the cells culling for reflections

	SafeWriteCall(kDetectorWindowSetNodeName, (UInt32)DetectorWindowSetNodeName);
	
	if (TheSettingManager->SettingsMain.Shaders.Water) {
		*LocalWaterHiRes = 1;
		SafeWriteJump(0x0053B16F, 0x0053B20C); // Avoids to change atmosphere colors when underwater
		SafeWriteJump(0x00542F63, 0x00542FC1); // Avoids to remove the sun over the scene when underwater
		SafeWrite8(0x0049EBAC, 0); // Avoids to change the shader for the skydome when underwater
	}
	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) {
		SafeWrite8(0x007BE1D3, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
		SafeWrite8(0x007BE32B, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
	}
	if (TheSettingManager->SettingsMain.Main.RemovePrecipitations) SafeWriteJump(0x00543167, 0x00543176);

}

//#include <fstream>
//LPD3DXBUFFER Disasm;
//char FileNameS[MAX_PATH];
//void* ShaderPackage = *(void**)0x00B430B8;
//
//char* ShaderFunction = (char*)ThisCall(0x007DAC70, ShaderPackage, ShaderName);
//ShaderFunction = ShaderFunction + 0x104;
//D3DXDisassembleShader((const DWORD*)ShaderFunction, FALSE, NULL, &Disasm);
//strcpy(FileNameS, "C:\\Archivio\\TES\\Shaders\\OblivionShadersNew\\");
//strcat(FileNameS, ShaderName);
//strcat(FileNameS, ".dis");
//std::ofstream FileBinary(FileNameS, std::ios::out | std::ios::binary);
//FileBinary.write((char*)Disasm->GetBufferPointer(), Disasm->GetBufferSize());
//FileBinary.flush();
//FileBinary.close();