#pragma once

bool (__thiscall* ReadSetting)(INISettingCollection*, GameSetting*) = (bool (__thiscall*)(INISettingCollection*, GameSetting*))Hooks::ReadSetting;
bool __fastcall ReadSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting) {
	
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
	else if (!strcmp(Setting->Name, "iMultiSample:Display") && Setting->iValue < 2 && TheSettingManager->SettingsMain.Main.ForceMSAA)
		Setting->iValue = 2;
	else if (!strcmp(Setting->Name, "bDoHighDynamicRange:BlurShaderHDR"))
		Setting->iValue = 1;
	else if (!strcmp(Setting->Name, "bUseBlurShader:BlurShader"))
		Setting->iValue = 0;
	else if (!strcmp(Setting->Name, "bUseWaterHiRes:Water"))
		Setting->iValue = 1;
	return r;

}

bool (__thiscall* WriteSetting)(INISettingCollection*, GameSetting*) = (bool (__thiscall*)(INISettingCollection*, GameSetting*))Hooks::WriteSetting;
bool __fastcall WriteSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting) {

	if (!strcmp(Setting->Name, "fNearDistance:Display") || !strcmp(Setting->Name, "fNear1stPersonDistance:Display"))
		return true;
	else if (!strcmp(Setting->Name, "fDefaultFOV:Display") || !strcmp(Setting->Name, "fDefaultWorldFOV:Display") || !strcmp(Setting->Name, "fDefault1stPersonFOV:Display") || !strcmp(Setting->Name, "fPipboy1stPersonFOV:Display"))
		return true;
	else if (!strcmp(Setting->Name, "fLODFadeOutMultActors:LOD") || !strcmp(Setting->Name, "fLODFadeOutMultItems:LOD") || !strcmp(Setting->Name, "fLODFadeOutMultObjects:LOD"))
		return true;
	else if (!strcmp(Setting->Name, "SIntroSequence:General") || !strcmp(Setting->Name, "SMainMenuMovie:General") || !strcmp(Setting->Name, "SMainMenuMusic:General") || !strcmp(Setting->Name, "STitleMusic:Loading"))
		return true;
	return (*WriteSetting)(This, Setting);
	
}

bool (__thiscall* LoadGame)(TESSaveLoadGame*, char*, UInt8) = (bool (__thiscall*)(TESSaveLoadGame*, char*, UInt8))Hooks::LoadGame;
bool __fastcall LoadGameHook(TESSaveLoadGame* This, UInt32 edx, char* FileName, UInt8 Arg2) {

	bool r;
	
	TheSettingManager->GameLoading = true;
	r = (*LoadGame)(This, FileName, Arg2);
	TheSettingManager->GameLoading = false;
	if (r) TheShaderManager->InitializeConstants();
	return r;

}

void MainMenuMusicFix(char* DestinationBuffer, size_t Size, char* SourceBuffer) {

	char Buffer[64] = { NULL };

	strcpy(Buffer, "Data\\Music\\Special\\");
	strcat(Buffer, MainMenuMusic);
	strcat(Buffer, ".mp3");
	strcpy(DestinationBuffer, Buffer);

}