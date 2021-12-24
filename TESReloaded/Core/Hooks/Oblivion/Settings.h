#pragma once

static bool (__thiscall* LoadGame)(TESSaveLoadGame*, BSFile*, char*, UInt8) = (bool (__thiscall*)(TESSaveLoadGame*, BSFile*, char*, UInt8))Hooks::LoadGame;
static bool __fastcall LoadGameHook(TESSaveLoadGame* This, UInt32 edx, BSFile* GameFile, char* FileName, UInt8 Arg3) {

	bool r;
	
	TheSettingManager->GameLoading = true;
	r = (*LoadGame)(This, GameFile, FileName, Arg3);
	TheSettingManager->GameLoading = false;
	if (r) TheShaderManager->InitializeConstants();
	return r;

}