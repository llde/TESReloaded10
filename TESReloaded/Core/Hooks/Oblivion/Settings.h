#pragma once

static bool (__thiscall* ReadSetting)(INISettingCollection*, GameSetting*) = (bool (__thiscall*)(INISettingCollection*, GameSetting*))Hooks::ReadSetting;
static bool __fastcall ReadSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting) {
	
	bool r = (*ReadSetting)(This, Setting);

	if (!strcmp(Setting->Name, "iLocation X:Display") || !strcmp(Setting->Name, "iLocation Y:Display"))
		Setting->iValue = 0;
	else if (!strcmp(Setting->Name, "bFull Screen:Display"))
		TheSettingManager->SetWindowedMode(Setting->iValue);
	else if (!strcmp(Setting->Name, "SIntroSequence:General") && TheSettingManager->SettingsMain.Main.ReplaceIntro)
		Setting->pValue = (char*)IntroMovie;
	else if (!strcmp(Setting->Name, "SMainMenuMovie:General") && TheSettingManager->SettingsMain.Main.ReplaceIntro)
		Setting->pValue = (char*)MainMenuMovie;
	else if ((!strcmp(Setting->Name, "SMainMenuMusic:General") || !strcmp(Setting->Name, "STitleMusic:Loading")) && TheSettingManager->SettingsMain.Main.ReplaceIntro)
		Setting->pValue = (char*)MainMenuMusic;
	else if (!strcmp(Setting->Name, "bDoCanopyShadowPass:Display") || !strcmp(Setting->Name, "bDoActorShadows:Display") || !strcmp(Setting->Name, "iActorShadowCountExt:Display") || !strcmp(Setting->Name, "iActorShadowCountInt:Display"))
		Setting->iValue = 0;
	else if (!strcmp(Setting->Name, "iMultiSample:Display") && Setting->iValue < 2)
		Setting->iValue = 2;
	else if (!strcmp(Setting->Name, "bDoHighDynamicRange:BlurShaderHDR"))
		Setting->iValue = 1;
	else if (!strcmp(Setting->Name, "bUseBlurShader:BlurShader"))
		Setting->iValue = 0;
	else if (!strcmp(Setting->Name, "bUseWaterDepth:Water") && TheSettingManager->SettingsMain.Shaders.Water)
		Setting->iValue = 0;
	else if (!strcmp(Setting->Name, "iPostProcessMilliseconds:BackgroundLoad") && TheSettingManager->SettingsMain.FrameRate.SmartBackgroundProcess)
		Setting->iValue = TheSettingManager->SettingsMain.FrameRate.BackgroundThreadPriority;
	else if (!strcmp(Setting->Name, "iPostProcessMillisecondsLoadingQueuedPriority:BackgroundLoad") && TheSettingManager->SettingsMain.FrameRate.SmartBackgroundProcess)
		Setting->iValue = TheSettingManager->SettingsMain.FrameRate.BackgroundThreadPriority;
	return r;

}

static bool (__thiscall* WriteSetting)(INISettingCollection*, GameSetting*) = (bool (__thiscall*)(INISettingCollection*, GameSetting*))Hooks::WriteSetting;
static bool __fastcall WriteSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting) {

	if (!strcmp(Setting->Name, "fNearDistance:Display") || !strcmp(Setting->Name, "fNear1stPersonDistance:Display"))
		return true;
	else if (!strcmp(Setting->Name, "fDefaultFOV:Display") || !strcmp(Setting->Name, "fDefaultWorldFOV:Display") || !strcmp(Setting->Name, "fDefault1stPersonFOV:Display"))
		return true;
	else if (!strcmp(Setting->Name, "fLODFadeOutMultActors:LOD") || !strcmp(Setting->Name, "fLODFadeOutMultItems:LOD") || !strcmp(Setting->Name, "fLODFadeOutMultObjects:LOD"))
		return true;
	else if (!strcmp(Setting->Name, "iMinGrassSize:Grass") || !strcmp(Setting->Name, "fGrassEndDistance:Grass") || !strcmp(Setting->Name, "fGrassStartFadeDistance:Grass") || !strcmp(Setting->Name, "fGrassWindMagnitudeMax:Grass") || !strcmp(Setting->Name, "fGrassWindMagnitudeMin:Grass") || !strcmp(Setting->Name, "fTexturePctThreshold:Grass"))
		return true;
	else if (!strcmp(Setting->Name, "SIntroSequence:General") || !strcmp(Setting->Name, "SMainMenuMovie:General") || !strcmp(Setting->Name, "SMainMenuMusic:General") || !strcmp(Setting->Name, "STitleMusic:Loading"))
		return true;
	return (*WriteSetting)(This, Setting);
	
}

static bool (__thiscall* LoadGame)(TESSaveLoadGame*, BSFile*, char*, UInt8) = (bool (__thiscall*)(TESSaveLoadGame*, BSFile*, char*, UInt8))Hooks::LoadGame;
static bool __fastcall LoadGameHook(TESSaveLoadGame* This, UInt32 edx, BSFile* GameFile, char* FileName, UInt8 Arg3) {

	bool r;
	
	TheSettingManager->GameLoading = true;
	r = (*LoadGame)(This, GameFile, FileName, Arg3);
	TheSettingManager->GameLoading = false;
	if (r) TheShaderManager->InitializeConstants();
	return r;

}