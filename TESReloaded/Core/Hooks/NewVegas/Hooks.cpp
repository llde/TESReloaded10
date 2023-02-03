#include "Hooks.h"

void AttachHooks() {
	
	SettingsMainStruct* SettingsMain = &TheSettingManager->SettingsMain;

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
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,		&RenderWorldSceneGraphHook);
	DetourAttach(&(PVOID&)RenderFirstPerson,			&RenderFirstPersonHook);
	DetourAttach(&(PVOID&)SetShaders,					&SetShadersHook);
	DetourAttach(&(PVOID&)SetSamplerState,				&SetSamplerStateHook);
	
	if (SettingsMain->Main.ForceReflections) {
		DetourAttach(&(PVOID&)RenderReflections, &RenderReflectionsHook);
		DetourAttach(&(PVOID&)GetWaterHeightLOD, &GetWaterHeightLODHook);
	}

	DetourAttach(&(PVOID&)RenderPipboy,					&RenderPipboyHook);
	DetourAttach(&(PVOID&)ShowDetectorWindow,			&ShowDetectorWindowHook);
	DetourAttach(&(PVOID&)LoadForm,						&LoadFormHook);
	if (SettingsMain->FlyCam.Enabled) DetourAttach(&(PVOID&)UpdateFlyCam, &UpdateFlyCamHook);
	DetourTransactionCommit();
	
	
	SafeWrite8(0x00BE1690,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x00BE1DFB,	sizeof(NiD3DPixelShaderEx));
	SafeWrite8(0x00466877,	sizeof(TESRegionEx));
	SafeWrite8(0x004F1107,	sizeof(TESRegionEx));
	SafeWrite32(0x00E7624D, sizeof(RenderManager));
	SafeWrite32(0x00466606, sizeof(TESWeatherEx));
	SafeWrite32(0x0046CF9B, sizeof(TESWeatherEx));

	SafeWrite8(0x008751C0, 0);				// Stops to clear the depth buffer when rendering the 1st person node
	SafeWrite16(0x0086A170, 0x9090);		// Avoids to pause the game when ALT-TAB

	SafeWriteJump(Jumpers::DetectorWindow::CreateTreeViewHook,	(UInt32)DetectorWindowCreateTreeViewHook);
	SafeWriteJump(Jumpers::DetectorWindow::DumpAttributesHook,	(UInt32)DetectorWindowDumpAttributesHook);
	SafeWriteJump(Jumpers::DetectorWindow::ConsoleCommandHook,	(UInt32)DetectorWindowConsoleCommandHook);
	SafeWriteCall(Jumpers::DetectorWindow::SetNodeName,			(UInt32)DetectorWindowSetNodeName);
	SafeWriteJump(Jumpers::RenderInterface::Hook,				(UInt32)RenderInterfaceHook);
	SafeWriteJump(Jumpers::SetRegionEditorName::Hook,			(UInt32)SetRegionEditorNameHook);
	SafeWriteJump(Jumpers::SetWeatherEditorName::Hook,			(UInt32)SetWeatherEditorNameHook);
	SafeWriteJump(Jumpers::Shadows::RenderShadowMapHook,		(UInt32)RenderShadowMapHook);
//	SafeWriteJump(Jumpers::Shadows::RenderShadowMap1Hook,		(UInt32)RenderShadowMap1Hook);
	SafeWriteJump(Jumpers::Shadows::AddCastShadowFlagHook,		(UInt32)AddCastShadowFlagHook);
	SafeWriteJump(Jumpers::Shadows::LeavesNodeNameHook,			(UInt32)LeavesNodeNameHook);
	SafeWriteCall(Jumpers::MainMenuMusic::Fix1,					(UInt32)MainMenuMusicFix);
	SafeWriteCall(Jumpers::MainMenuMusic::Fix2,					(UInt32)MainMenuMusicFix);

	SafeWriteJump(0x004E4C3B, 0x004E4C42); // Fixes reflections when cell water height is not like worldspace water height
	SafeWriteJump(0x004E4DA4, 0x004E4DAC); // Fixes reflections on the distant water
	SafeWriteCall(0x00875B86, 0x00710AB0); // Sets the world fov at the end of 1st person rendering
	SafeWriteCall(0x00875B9D, 0x00710AB0); // Sets the world fov at the end of 1st person rendering
	SafeWriteJump(0x00C03F49, 0x00C03F5A); // Fixes wrong rendering for image space effects
	
	if (SettingsMain->Main.ForceReflections) {
		//*Pointers::ShaderParams::WaterHighResolution = 1;
		SafeWriteCall(Jumpers::MultiBoundWaterHeight::Fix1, (UInt32)MultiBoundWaterHeightFix);
		SafeWriteCall(Jumpers::MultiBoundWaterHeight::Fix2, (UInt32)MultiBoundWaterHeightFix);
	}

	if (TheSettingManager->SettingsMain.Main.ReplaceIntro) SafeWriteJump(Jumpers::SetTileShaderConstants::Hook, (UInt32)SetTileShaderConstantsHook);
	
	if (TheSettingManager->SettingsMain.Main.RemovePrecipitations) {
		SafeWriteJump(0x0063AFC4, 0x0063AFD8);
		SafeWriteJump(0x0063A5CB, 0x0063A5DE);
	}
	
	if (SettingsMain->FlyCam.Enabled) {
		SafeWriteJump(Jumpers::FlyCam::UpdateForwardFlyCamHook, (UInt32)UpdateForwardFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateBackwardFlyCamHook, (UInt32)UpdateBackwardFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateRightFlyCamHook, (UInt32)UpdateRightFlyCamHook);
		SafeWriteJump(Jumpers::FlyCam::UpdateLeftFlyCamHook, (UInt32)UpdateLeftFlyCamHook);
	}

}
