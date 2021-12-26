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
	DetourAttach(&(PVOID&)SetShaderPackage,				&SetShaderPackageHook);
	DetourAttach(&(PVOID&)Render,						&RenderHook);
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders,		&ProcessImageSpaceShadersHook);
	DetourAttach(&(PVOID&)ShowDetectorWindow,			&ShowDetectorWindowHook);
	DetourAttach(&(PVOID&)SetupShaderPrograms,			&SetupShaderProgramsHook);
	DetourAttach(&(PVOID&)EndTargetGroup,				&EndTargetGroupHook);
	DetourAttach(&(PVOID&)HDRRender,					&HDRRenderHook);
	DetourAttach(&(PVOID&)WaterHeightMapRender,			&WaterHeightMapRenderHook);
	DetourAttach(&(PVOID&)FarPlane,						&FarPlaneHook);
	DetourAttach(&(PVOID&)SetSamplerState,				&SetSamplerStateHook);
	DetourAttach(&(PVOID&)RenderReflections,			&RenderReflectionsHook);
	DetourAttach(&(PVOID&)WaterCullingProcess,			&WaterCullingProcessHook);
	DetourAttach(&(PVOID&)SaveGameScreenshot,			&SaveGameScreenshotHook);
	DetourAttach(&(PVOID&)LoadForm,						&LoadFormHook);
	DetourAttach(&(PVOID&)RunScript,					&RunScriptHook);
	DetourAttach(&(PVOID&)NewActorAnimData,				&NewActorAnimDataHook);
	DetourAttach(&(PVOID&)DisposeActorAnimData,			&DisposeActorAnimDataHook);
	DetourAttach(&(PVOID&)AddAnimation,					&AddAnimationHook);
	DetourAttach(&(PVOID&)AddSingle,					&AddSingleHook);
	DetourAttach(&(PVOID&)AddMultiple,					&AddMultipleHook);
	DetourAttach(&(PVOID&)GetAnimGroupSequenceSingle,	&GetAnimGroupSequenceSingleHook);
	DetourAttach(&(PVOID&)GetAnimGroupSequenceMultiple,	&GetAnimGroupSequenceMultipleHook);
	DetourAttach(&(PVOID&)NewAnimSequenceMultiple,		&NewAnimSequenceMultipleHook);
	if (TheSettingManager->SettingsMain.IKFoot.Enabled) DetourAttach(&(PVOID&)ApplyActorAnimData, &ApplyActorAnimDataHook);
	DetourAttach(&(PVOID&)LoadAnimGroup,				&LoadAnimGroupHook);
	DetourTransactionCommit();
	
	SafeWrite8(0x00801BCB,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x008023A1,	sizeof(NiD3DPixelShaderEx));
	SafeWrite8(0x00448843,	sizeof(TESRegionEx));
	SafeWrite8(0x004A2EFF,	sizeof(TESRegionEx));
	SafeWrite8(0x00474140,	sizeof(AnimSequenceSingleEx));
	SafeWrite8(0x004741C0,	sizeof(AnimSequenceMultipleEx));
	SafeWrite32(0x0076BD75, sizeof(RenderManager));
	SafeWrite32(0x004486ED, sizeof(TESWeatherEx));
	SafeWrite32(0x0044CBE3, sizeof(TESWeatherEx));
	SafeWrite32(0x004E3814, sizeof(ActorAnimDataEx));
	SafeWrite32(0x004E3ADD, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00667E23, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00669258, sizeof(ActorAnimDataEx));

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
	SafeWriteJump(kNewAnimSequenceSingleHook,		(UInt32)NewAnimSequenceSingleHook);
	SafeWriteJump(kRemoveSequenceHook,				(UInt32)RemoveSequenceHook);
	SafeWriteJump(kRenderShadowMapHook,				(UInt32)RenderShadowMapHook);
	SafeWriteJump(kAddCastShadowFlagHook,			(UInt32)AddCastShadowFlagHook);
	SafeWriteJump(kWaterHeightMapHook,				(UInt32)WaterHeightMapHook);
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

	SettingsMainStruct::FrameRateStruct* FrameRate = &TheSettingManager->SettingsMain.FrameRate;

	if (FrameRate->SmartControl) SafeWriteJump(kUpdateTimeInfoHook, (UInt32)UpdateTimeInfoHook);
	if (FrameRate->SmartBackgroundProcess) {
		SafeWriteJump(0x00701739, 0x00701748); // Skips init	 SourceDataCriticalSection (NiRenderer::New)
		SafeWriteJump(0x00763565, 0x0076357F); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x00763596, 0x007635AA); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x007635C4, 0x007635DE); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWriteJump(0x007635FB, 0x0076360F); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWrite8(0x007635F9, 0x8B); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWrite8(0x007635FA, 0xF8); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWriteJump(0x0077ACBF, 0x0077ACD9); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD08, 0x0077AD1C); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD52, 0x0077AD66); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AE2A, 0x0077AE44); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AE6C, 0x0077AE80); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AEAF, 0x0077AEC3); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
	}

	SafeWriteJump(0x0040F488, (UInt32)EndProcessHook);

	if (TheSettingManager->SettingsMain.OcclusionCulling.Enabled) {
		SafeWrite8(0x00564523, sizeof(bhkCollisionObjectEx));
		SafeWrite8(0x0089E983, sizeof(bhkCollisionObjectEx));
		SafeWrite8(0x0089EA16, sizeof(bhkCollisionObjectEx));

		SafeWriteJump(kNew1CollisionObjectHook,		(UInt32)New1CollisionObjectHook);
		SafeWriteJump(kNew2CollisionObjectHook,		(UInt32)New2CollisionObjectHook);
		SafeWriteJump(kNew3CollisionObjectHook,		(UInt32)New3CollisionObjectHook);
		SafeWriteJump(kDisposeCollisionObjectHook,	(UInt32)DisposeCollisionObjectHook);
		SafeWriteJump(kMaterialPropertyHook,		(UInt32)MaterialPropertyHook);
		SafeWriteJump(kCoordinateJackHook,			(UInt32)CoordinateJackHook);
		SafeWriteJump(kObjectCullHook,				(UInt32)ObjectCullHook);
	}


	HMODULE Module = NULL;
	char Filename[MAX_PATH];

	if (TheSettingManager->SettingsMain.Main.MemoryHeapManagement) {
		GetCurrentDirectoryA(MAX_PATH, Filename);
		strcat(Filename, FastMMFile);
		Module = LoadLibraryA(Filename);
		if (Module) {
			Mem.Malloc = (void* (*)(size_t))GetProcAddress(Module, "GetMemory");
			Mem.Free = (void (*)(void*))GetProcAddress(Module, "FreeMemory");
			Mem.Realloc = (void* (*)(void*, size_t))GetProcAddress(Module, "ReallocMemory");
			Logger::Log("Fast memory manager loaded correctly.");
		}
		else {
			char Error[160];
			sprintf(Error, "CRITICAL ERROR: Cannot load the memory manager, please reinstall the package.");
			Logger::Log(Error);
			MessageBoxA(NULL, Error, PluginVersion::VersionString, MB_ICONERROR | MB_OK);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		SafeWriteJump(0x009D7E40, 0x009D7E60); //Skips MemoryHeap initialization
		SafeWriteJump(0x0040E3BF, 0x0040E62A); //Skips MemoryHeap pools creation and cleanup assignment
		SafeWriteJump(0x0040B3A0, 0x0040C008); //Skips MemoryHeap stats
		SafeWriteCall(0x00401AAE, (UInt32)Mem.Malloc);
		SafeWriteCall(0x00401495, (UInt32)Mem.Free);
		SafeWriteJump(kMemReallocHook, (UInt32)MemReallocHook);
	}
	if (TheSettingManager->SettingsMain.Main.MemoryTextureManagement) SafeWriteCall(kCreateTextureFromFileInMemory, (UInt32)CreateTextureFromFileInMemory);

	if (TheSettingManager->SettingsMain.GrassMode.Enabled) SafeWriteJump(kGrassHook, (UInt32)GrassHook);

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