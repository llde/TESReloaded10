#pragma once

static bool (__thiscall* LoadGame)(TESSaveLoadGame*, char*, UInt8) = (bool (__thiscall*)(TESSaveLoadGame*, char*, UInt8))Hooks::LoadGame;
static bool __fastcall LoadGameHook(TESSaveLoadGame* This, UInt32 edx, char* FileName, UInt8 Arg2) {

	bool r;
	
	TheSettingManager->GameLoading = true;
	r = (*LoadGame)(This, FileName, Arg2);
	TheSettingManager->GameLoading = false;
	if (r) TheShaderManager->InitializeConstants();
	return r;

}