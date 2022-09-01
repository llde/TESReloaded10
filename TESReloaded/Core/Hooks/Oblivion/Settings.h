#pragma once
extern bool(__thiscall* ReadSetting)(INISettingCollection*, GameSetting*);
bool __fastcall ReadSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting);

extern bool(__thiscall* WriteSetting)(INISettingCollection*, GameSetting*);
bool __fastcall WriteSettingHook(INISettingCollection* This, UInt32 edx, GameSetting* Setting);

extern bool(__thiscall* LoadGame)(TESSaveLoadGame*, BSFile*, char*, UInt8);
bool __fastcall LoadGameHook(TESSaveLoadGame* This, UInt32 edx, BSFile* GameFile, char* FileName, UInt8 Arg3);