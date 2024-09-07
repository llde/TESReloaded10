#include "Hooks.h"
#include "Shadows.h"
HRESULT(__thiscall* RemoveTexture)(NiDX9RenderState*, UInt32 ) = (HRESULT(__thiscall*)(NiDX9RenderState*, UInt32))0x0077B2C0;
HRESULT _fastcall RemoveTextureH(NiDX9RenderState* state, UInt32 edx, UInt32 sampler) {

	return D3D_OK;
}

HRESULT(__thiscall* SetTexture)(NiDX9RenderState*, UInt32, IDirect3DBaseTexture9*) = (HRESULT(__thiscall*)(NiDX9RenderState*, UInt32, IDirect3DBaseTexture9*))0x0077B280;
HRESULT _fastcall SetTextureH(NiDX9RenderState* state, UInt32 edx, UInt32 sampler, IDirect3DBaseTexture9* tex) {
	if (tex == nullptr) return  D3D_OK;
	return (*SetTexture)(state, sampler, tex);
}

void(__cdecl* SetNameThread)(int, const char*) = (void(__cdecl*)(int, const char*)) 0x00747830;
void __cdecl NameThread(int threadID, const char* name) {

}

int(__thiscall* RemoveTextureList)(NiDX9RenderState*) = (int(__thiscall*)(NiDX9RenderState*)) 0x0077B210;
int __fastcall RemoveTextureListH(NiDX9RenderState* This) {
	return 0;
}

static const UInt32 kRetU = 0x0053B175;
static const UInt32 kRet = 0x0053B20C;
void __declspec(naked) SetAtmosphereUnderwater() {
	__asm {
		pushad
	}
//	Logger::Log("%u", Tes->sky->unk0DC);
//	Tes->sky->unk0DC = 0;
	if (TheSettingManager->Config->WaterEngine.SetAtmoshpere) {
		__asm {
			popad 
			jmp [kRetU]
		}
	}
	else {
		__asm {
			popad
			jmp[kRet]
		}
	}
}

void AttachHooks() {

	HMODULE Module = NULL;
	char Filename[MAX_PATH];
	ffi::Config* SettingsMain = TheSettingManager->Config;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
//	DetourAttach(&(PVOID&)RemoveTexture, &RemoveTextureH);
//	DetourAttach(&(PVOID&)SetTexture, &SetTextureH);
//	DetourAttach(&(PVOID&)RemoveTextureList, &RemoveTextureListH);

	DetourAttach(&(PVOID&)SetNameThread, &NameThread);

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
	DetourAttach(&(PVOID&)RenderObject,					&RenderObjectHook);
	DetourAttach(&(PVOID&)LoadForm,						&LoadFormHook);
	DetourAttach(&(PVOID&)RunScript,					&RunScriptHook);
#ifdef EXPERIMENTAL_FEATURE
	DetourAttach(&(PVOID&)NewActorAnimData, &NewActorAnimDataHook);
	DetourAttach(&(PVOID&)DisposeActorAnimData, &DisposeActorAnimDataHook);
	DetourAttach(&(PVOID&)AddAnimation, &AddAnimationHook);
	DetourAttach(&(PVOID&)AddSingle, &AddSingleHook);
	DetourAttach(&(PVOID&)AddMultiple, &AddMultipleHook);
	DetourAttach(&(PVOID&)GetAnimGroupSequenceSingle, &GetAnimGroupSequenceSingleHook);
	DetourAttach(&(PVOID&)GetAnimGroupSequenceMultiple, &GetAnimGroupSequenceMultipleHook);
	DetourAttach(&(PVOID&)NewAnimSequenceMultiple, &NewAnimSequenceMultipleHook);
	DetourAttach(&(PVOID&)LoadAnimGroup, &LoadAnimGroupHook);
	if (SettingsMain->IKFoot.Enabled) DetourAttach(&(PVOID&)ApplyActorAnimData, &ApplyActorAnimDataHook);
#endif
#ifdef EXPERIMENTAL_FEATURE

 	if(SettingsMain->CameraMode.Enabled){
		DetourAttach(&(PVOID&)ToggleCamera,					&ToggleCameraHook);
		DetourAttach(&(PVOID&)ToggleBody,					&ToggleBodyHook);
		DetourAttach(&(PVOID&)SetDialogCamera,				&SetDialogCameraHook);
		DetourAttach(&(PVOID&)SetAimingZoom,				&SetAimingZoomHook);
		DetourAttach(&(PVOID&)UpdateCameraCollisions,		&UpdateCameraCollisionsHook);
	}
	if (SettingsMain->EquipmentMode.Enabled) {
		DetourAttach(&(PVOID&)NewHighProcess,				&NewHighProcessHook);
		DetourAttach(&(PVOID&)ManageItem,					&ManageItemHook);
		DetourAttach(&(PVOID&)ProcessAction,				&ProcessActionHook);
		DetourAttach(&(PVOID&)ProcessControlAttack,			&ProcessControlAttackHook);
		DetourAttach(&(PVOID&)AttackHandling,				&AttackHandlingHook);
		DetourAttach(&(PVOID&)GetEquippedWeaponData,		&GetEquippedWeaponDataHook);
		DetourAttach(&(PVOID&)SetEquippedWeaponData,		&SetEquippedWeaponDataHook);
		DetourAttach(&(PVOID&)EquipItem,					&EquipItemHook);
		DetourAttach(&(PVOID&)UnequipItem,					&UnequipItemHook);
		DetourAttach(&(PVOID&)EquipWeapon,					&EquipWeaponHook);
		DetourAttach(&(PVOID&)UnequipWeapon,				&UnequipWeaponHook);
		DetourAttach(&(PVOID&)EquipShield,					&EquipShieldHook);
		if (SettingsMain->EquipmentMode.TorchKey != 255) {
			DetourAttach(&(PVOID&)EquipLight,				&EquipLightHook);
			DetourAttach(&(PVOID&)UnequipLight,				&UnequipLightHook);
			DetourAttach(&(PVOID&)GetEquippedLightData,		&GetEquippedLightDataHook);
		}
		DetourAttach(&(PVOID&)HideEquipment,				&HideEquipmentHook);
		DetourAttach(&(PVOID&)SaveGame,						&SaveGameHook);
	}
#endif
	if (SettingsMain->SleepingMode.Enabled) {
		DetourAttach(&(PVOID&)RemoveWornItems,				&RemoveWornItemsHook);
		DetourAttach(&(PVOID&)ServeSentence,				&ServeSentenceHook);
		DetourAttach(&(PVOID&)ProcessSleepWaitMenu,			&ProcessSleepWaitMenuHook);
		DetourAttach(&(PVOID&)CloseSleepWaitMenu,			&CloseSleepWaitMenuHook);
		DetourAttach(&(PVOID&)ShowSleepWaitMenu,			&ShowSleepWaitMenuHook);
	}
	if (SettingsMain->FlyCam.Enabled) DetourAttach(&(PVOID&)UpdateFlyCam, &UpdateFlyCamHook);
  //  DetourAttach(&(PVOID&)LoadTextureFile,				&LoadTextureFileHook);
    DetourAttach(&(PVOID&)WaterSurfacePass,				&WaterSurfacePassHook);
//	DetourAttach(&(PVOID&)RenderCanopyMap, &RenderCanopyMapHook);

	DetourTransactionCommit();
	
	SafeWrite8(0x00801BCB,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x008023A1,	sizeof(NiD3DPixelShaderEx));
	SafeWrite8(0x00448843,	sizeof(TESRegionEx));
	SafeWrite8(0x004A2EFF,	sizeof(TESRegionEx));
	SafeWrite32(0x0076BD75, sizeof(RenderManager));
	SafeWrite32(0x00406775, sizeof(PlayerCharacterEx));
	SafeWrite32(0x0046451E, sizeof(PlayerCharacterEx));
	SafeWrite32(0x004486ED, sizeof(TESWeatherEx));
	SafeWrite32(0x0044CBE3, sizeof(TESWeatherEx));

#ifdef EXPERIMENTAL_FEATURES

	SafeWrite8(0x00564523, sizeof(bhkCollisionObjectEx));
	SafeWrite8(0x0089E983, sizeof(bhkCollisionObjectEx));
	SafeWrite8(0x0089EA16, sizeof(bhkCollisionObjectEx));

	SafeWrite8(0x00474140, sizeof(AnimSequenceSingleEx));
	SafeWrite8(0x004741C0, sizeof(AnimSequenceMultipleEx));
	SafeWrite32(0x004E3814, sizeof(ActorAnimDataEx));
	SafeWrite32(0x004E3ADD, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00667E23, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00669258, sizeof(ActorAnimDataEx));
	SafeWrite32(0x005FA47C, sizeof(HighProcessEx));
	SafeWrite32(0x00607582, sizeof(HighProcessEx));
	SafeWrite32(0x0060791A, sizeof(HighProcessEx));
	SafeWrite32(0x0060CC36, sizeof(HighProcessEx));
	SafeWrite32(0x00659A9C, sizeof(HighProcessEx));
	SafeWrite32(0x00659D3D, sizeof(HighProcessEx));
	SafeWrite32(0x00664B09, sizeof(HighProcessEx));
	SafeWrite32(0x0066A9AA, sizeof(HighProcessEx));
	SafeWrite32(0x0068336E, sizeof(HighProcessEx));
	SafeWrite32(0x0069F2F2, sizeof(HighProcessEx));
	SafeWrite32(0x0069F3D4, sizeof(HighProcessEx));

	SafeWriteJump(Jumpers::NewAnimSequenceSingle::Hook, (UInt32)NewAnimSequenceSingleHook);
	SafeWriteJump(Jumpers::RemoveSequence::Hook, (UInt32)RemoveSequenceHook);

#endif // EXPERIMENTAL_FEATURES

	SafeWrite8(0x00A38280, 0x5A); // Fixes the "purple water bug"
	SafeWrite32(0x0049BFAF, SettingsMain->WaterEngine.ReflectionMapSize); // Constructor
	SafeWrite32(0x007C1045, SettingsMain->WaterEngine.ReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C104F, SettingsMain->WaterEngine.ReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C10F9, SettingsMain->WaterEngine.ReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C1103, SettingsMain->WaterEngine.ReflectionMapSize); // RenderedSurface

	SafeWrite8(0x0049EBAC, 0); // Avoids to change the shader for the skydome when underwaterb (avoid using Fade shaders)
	SafeWriteJump(0x0053B11F, (UInt32)SetAtmosphereUnderwater); // Avoids to change atmosphere colors when underwater. 
	if(SettingsMain->Main.RemoveUnderwater) SafeWriteJump(0x00542F63, 0x00542FC1); // Avoids to remove the sun over the scene when underwater. Prevent rendering the vanilla underwater fog. Actually turn the Sky green
	if (!SettingsMain->Main.RemoveUnderwater) 
		Logger::Log("[WARNING] RemoveUnderwater=false is incompatible with showing the Sun when underwater. Vanilla Sun behaviour restored. ");
	if (!SettingsMain->Main.RemoveUnderwater && SettingsMain->Main.RemoveFogPass)
		Logger::Log("[WARNING] RemoveUnderwater=false and RemoveFogPass=true are incompatible. Disabling RemoveFogPass. Could experience visual problems");


	SafeWriteJump(Jumpers::DetectorWindow::CreateTreeViewHook,	(UInt32)DetectorWindowCreateTreeViewHook);
	SafeWriteJump(Jumpers::DetectorWindow::DumpAttributesHook,	(UInt32)DetectorWindowDumpAttributesHook);
	SafeWriteJump(Jumpers::DetectorWindow::ConsoleCommandHook,	(UInt32)DetectorWindowConsoleCommandHook);
	SafeWriteCall(Jumpers::DetectorWindow::SetNodeName,			(UInt32)DetectorWindowSetNodeName);
	SafeWriteJump(Jumpers::RenderInterface::Hook,				(UInt32)RenderInterfaceHook);
	SafeWriteJump(Jumpers::SetRegionEditorName::Hook,			(UInt32)SetRegionEditorNameHook);
	SafeWriteJump(Jumpers::SetWeatherEditorName::Hook,			(UInt32)SetWeatherEditorNameHook);
	SafeWriteJump(Jumpers::HitEvent::Hook,						(UInt32)HitEventHook);
	SafeWriteJump(Jumpers::Shadows::RenderShadowMapHook,		(UInt32)RenderShadowMapHook);


	SafeWriteCall(0x0040D650, (UInt32)RenderCanopyMapHook); //Avoid tree canopy shadows rendering. This actually only seems to disable initialization, but not prevent the actual shadowmap to be disabled
	SafeWriteJump(0x004425F7, 0x00442621); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	SafeWriteJump(0x004446FB, 0x00444723); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	SafeWriteJump(0x00444CCF, 0x00444CF9); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	SafeWriteJump(0x0055F5C9, 0x0055F5ED); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)

	SafeWriteJump(Jumpers::Shadows::AddCastShadowFlagHook,		(UInt32)AddCastShadowFlagHook);
//	SafeWriteJump(Jumpers::WaterHeightMap::Hook,				(UInt32)WaterHeightMapHook);
	SafeWriteJump(Jumpers::EndProcess::Hook,					(UInt32)EndProcessHook);
    /*RemoveUnderwater must be true for this hook to not cause glitches*/
    if(SettingsMain->Main.RemoveFogPass && SettingsMain->Main.RemoveUnderwater) 	SafeWriteJump(Jumpers::SkipFogPass::Hook, (UInt32)SkipFogPassHook);

//	SafeWriteJump(0x00553EAC, 0x00553EB2); // Patches the use of Lighting30Shader only for the hair
//	SafeWriteJump(0x007D1BC4, 0x007D1BFD); // Patches the use of Lighting30Shader only for the hair //TODO this cause issue with some objects, seems it0s used by different objects
//	SafeWriteJump(0x007D1BCD, 0x007D1BFD); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x0049C3A2, 0x0049C41D); // Avoids to manage the cells culling for reflections
	SafeWriteJump(0x0049C8CB, 0x0049C931); // Avoids to manage the cells culling for reflections
	SafeWriteJump(0x004965A8, 0x0049660F); // Skip the scale in the detector window
	SafeWriteJump(0x0049849A, 0x004984A0); // Skips antialiasing deactivation if HDR is enabled on the D3DDevice
	SafeWriteJump(0x005DEE60, 0x005DEE68); // Skips antialiasing deactivation if HDR is enabled on loading the video menu
	SafeWriteJump(0x005DF69E, 0x005DF755); // Skips HDR deactivation changing antialising (video menu)
	SafeWriteJump(0x00497D5A, 0x00497D63); // Unlocks antialising bar if HDR is enabled (video menu)
	SafeWriteJump(0x005DF8E9, 0x005DF983); // Skips antialising deactivation changing HDR (video menu)
	SafeWriteJump(0x006738B1, 0x00673935); // Cancels the fPlayerDeathReloadTime
	SafeWrite8(0x0040CE11, 0); // Stops to clear the depth buffer when rendering the 1st person node

	*Pointers::ShaderParams::WaterHighResolution = 1;

	if (SettingsMain->Main.AnisotropicFilter >= 2) {
		SafeWrite8(0x007BE1D3, SettingsMain->Main.AnisotropicFilter);
		SafeWrite8(0x007BE32B, SettingsMain->Main.AnisotropicFilter);
	}

	if (SettingsMain->Main.RemovePrecipitations) SafeWriteJump(0x00543167, 0x00543176);
#ifdef EXPERIMENTAL_FEATURE
	if (SettingsMain->FrameRate.SmartControl) SafeWriteJump(Jumpers::UpdateTimeInfo::Hook, (UInt32)UpdateTimeInfoHook);

	if (SettingsMain->FrameRate.SmartBackgroundProcess) {
		SafeWrite8(0x007635F9, 0x8B); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWrite8(0x007635FA, 0xF8); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWriteJump(0x00701739, 0x00701748); // Skips init	 SourceDataCriticalSection (NiRenderer::New)
		SafeWriteJump(0x00763565, 0x0076357F); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x00763596, 0x007635AA); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x007635C4, 0x007635DE); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWriteJump(0x007635FB, 0x0076360F); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWriteJump(0x0077ACBF, 0x0077ACD9); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD08, 0x0077AD1C); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD52, 0x0077AD66); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AE2A, 0x0077AE44); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AE6C, 0x0077AE80); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AEAF, 0x0077AEC3); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
	}

	if (SettingsMain->OcclusionCulling.Enabled) {
		SafeWriteJump(Jumpers::Occlusion::New1CollisionObjectHook,		(UInt32)New1CollisionObjectHook);
		SafeWriteJump(Jumpers::Occlusion::New2CollisionObjectHook,		(UInt32)New2CollisionObjectHook);
		SafeWriteJump(Jumpers::Occlusion::New3CollisionObjectHook,		(UInt32)New3CollisionObjectHook);
		SafeWriteJump(Jumpers::Occlusion::DisposeCollisionObjectHook,	(UInt32)DisposeCollisionObjectHook);
		SafeWriteJump(Jumpers::Occlusion::MaterialPropertyHook, (UInt32)MaterialPropertyHook);
		SafeWriteJump(Jumpers::Occlusion::CoordinateJackHook, (UInt32)CoordinateJackHook);
	}
#endif
	SafeWriteJump(Jumpers::Occlusion::ObjectCullHook, (UInt32)ObjectCullHook);
#ifdef EXPERIMENTAL_FEATURE	
	if (SettingsMain->Main.MemoryHeapManagement) {
		GetCurrentDirectoryA(MAX_PATH, Filename);
		strcat(Filename, FastMMFile);
		Module = LoadLibraryA(Filename);
		Mem.Malloc = (void* (*)(size_t))GetProcAddress(Module, "GetMemory");
		Mem.Free = (void (*)(void*))GetProcAddress(Module, "FreeMemory");
		Mem.Realloc = (void* (*)(void*, size_t))GetProcAddress(Module, "ReallocMemory");
		SafeWriteJump(0x009D7E40, 0x009D7E60); //Skips MemoryHeap initialization
		SafeWriteJump(0x0040E3BF, 0x0040E62A); //Skips MemoryHeap pools creation and cleanup assignment
		SafeWriteJump(0x0040B3A0, 0x0040C008); //Skips MemoryHeap stats
		SafeWriteCall(0x00401AAE, (UInt32)Mem.Malloc);
		SafeWriteCall(0x00401495, (UInt32)Mem.Free);
		SafeWriteJump(Jumpers::Memory::MemReallocHook, (UInt32)MemReallocHook);
	}
#endif
	if (SettingsMain->Main.MemoryTextureManagement){
        SafeWriteCall(Jumpers::Memory::CreateTextureFromFileInMemory, (UInt32)CreateTextureFromFileInMemory);
    }
	if (SettingsMain->Main.GrassMode) SafeWriteJump(Jumpers::UpdateGrass::Hook, (UInt32)UpdateGrassHook);
#ifdef EXPERIMENTAL_FEATURE	
	if (SettingsMain->CameraMode.Enabled) {
		SafeWriteJump(Jumpers::Camera::UpdateCameraHook,		(UInt32)UpdateCameraHook);
		SafeWriteJump(Jumpers::Camera::SwitchCameraHook,		(UInt32)SwitchCameraHook);
		SafeWriteJump(Jumpers::Camera::SwitchCameraPOVHook,		(UInt32)SwitchCameraPOVHook);
		SafeWriteJump(Jumpers::Camera::HeadTrackingHook,		(UInt32)HeadTrackingHook);
		SafeWriteJump(Jumpers::Camera::SpineTrackingHook,		(UInt32)SpineTrackingHook);
		SafeWriteJump(Jumpers::Camera::SetReticleOffsetHook,	(UInt32)SetReticleOffsetHook);
		SafeWriteJump(0x00666704, 0x0066672D); // Enables the zoom with the bow
	}

	if (SettingsMain->EquipmentMode.Enabled) {
		SafeWriteJump(Jumpers::Equipment::PrnHook,							(UInt32)PrnHook);
		SafeWriteJump(Jumpers::Equipment::SetWeaponRotationPositionHook,	(UInt32)SetWeaponRotationPositionHook);
		SafeWriteJump(Jumpers::Equipment::MenuMouseButtonHook,				(UInt32)MenuMouseButtonHook);
		SafeWriteJump(Jumpers::Equipment::EquipItemWornHook,				(UInt32)EquipItemWornHook);
		if (SettingsMain->EquipmentMode.TorchKey != 255) {
			SafeWriteJump(0x004E1DA1, 0x004E1DAF); // Do not play the torch held LP sound on equipping light
			SafeWriteJump(Jumpers::Equipment::UnequipTorchHook,				(UInt32)UnequipTorchHook);
		}
		if (SettingsMain->MountedCombat.Enabled) {
			SafeWriteCall(Jumpers::Mounted::PlayerReadyWeaponHook,			(UInt32)ReadyWeaponHook);
			SafeWriteCall(Jumpers::Mounted::ActorReadyWeaponHook,			(UInt32)ReadyWeaponHook);
			SafeWriteJump(Jumpers::Mounted::ActorReadyWeaponSittingHook,	(UInt32)ActorReadyWeaponSittingHook);
			SafeWriteJump(Jumpers::Mounted::PlayerAttackHook,				(UInt32)PlayerAttackHook);
			SafeWriteJump(Jumpers::Mounted::HittingMountedCreatureHook,		(UInt32)HittingMountedCreatureHook);
			SafeWriteJump(Jumpers::Mounted::HideWeaponHook,					(UInt32)HideWeaponHook);
			SafeWriteJump(Jumpers::Mounted::BowEquipHook,					(UInt32)BowEquipHook);
			SafeWriteJump(Jumpers::Mounted::BowUnequipHook,					(UInt32)BowUnequipHook);
			SafeWriteJump(Jumpers::Mounted::AnimControllerHook,				(UInt32)AnimControllerHook);
			SafeWriteJump(Jumpers::Mounted::HorsePaletteHook,				(UInt32)HorsePaletteHook);
			SafeWriteJump(0x005FB089, 0x005FB0AD); // Enables the possibility to equip the weapon when sitting/mounting
			SafeWriteJump(0x005F2F97, 0x005F2FE8); // Enables the possibility to unequip the weapon when sitting/mounting

			SafeWrite16(0x005F4E55, 0xC031); // Enables blockhit animation when mounting
			SafeWrite16(0x005F4F45, 0xC031); // Enables recoil animation when mounting
			SafeWrite16(0x005F4FEF, 0xC031); // Enables stagger animation when mounting
		}
	}
#endif
	if (SettingsMain->SleepingMode.Enabled) {
		SafeWriteJump(0x004AEA1C, 0x004AEAEE); // Enables the Player to get into the bed
		SafeWriteJump(0x004AE961, 0x004AEAEE); // Enables the Player to get into the bed when in prison
		SafeWriteJump(0x00672BFF, 0x00672C18); // Enables the rest key when in prison
	}
#ifdef EXPERIMENTAL_FEATURE
	if (SettingsMain->Dodge.Enabled) {
		SafeWrite8(0x00672A17, SettingsMain->Dodge.AcrobaticsLevel);
		if (SettingsMain->Dodge.DoubleTap) {
			SafeWriteJump(0x00672941, 0x00672954);
			SafeWriteJump(Jumpers::Dodge::JumpPressedHook,	(UInt32)JumpPressedHook);
			SafeWriteJump(Jumpers::Dodge::DoubleTapHook,	(UInt32)DoubleTapHook);
		}
	}
#endif
	if (SettingsMain->FlyCam.Enabled) {
		SafeWriteJump(Jumpers::FlyCam::UpdateForwardFlyCamHook,		(UInt32)UpdateForwardFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateBackwardFlyCamHook,	(UInt32)UpdateBackwardFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateRightFlyCamHook,		(UInt32)UpdateRightFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateLeftFlyCamHook,		(UInt32)UpdateLeftFlyCamHook);
	}

}

void AttachEditorHooks() {
	
	SafeWriteJump(Jumpers::Shadows::EditorCastShadowFlagHook, (UInt32)EditorCastShadowFlagHook);

}
//#include <fstream>
//LPD3DXBUFFER Disasm;
//char FileNameS[MAX_PATH];
//void* ShaderPackage = *(void**)0x00B430B8;
//
//char* ShaderFunction = (char*)ThisCall(0x007DAC70, ShaderPackage, ShaderName);
//ShaderFunction = ShaderFunction + 0x104;
//D3DXDisassembleShader((const DWORD*)ShaderFunction, FALSE, NULL, &Disasm);
//strcpy(FileNameS, "C:\\Archive\\TES\\Shaders\\OblivionShadersNew\\");
//strcat(FileNameS, ShaderName);
//strcat(FileNameS, ".dis");
//std::ofstream FileBinary(FileNameS, std::ios::out | std::ios::binary);
//FileBinary.write((char*)Disasm->GetBufferPointer(), Disasm->GetBufferSize());
//FileBinary.flush();
//FileBinary.close();
