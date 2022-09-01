#pragma once
extern bool(__cdecl* LoadForm)(TESForm*, UInt32);
bool __cdecl LoadFormHook(TESForm* Form, UInt32 ModEntry);

void SetWeatherEditorName(TESWeatherEx* Weather, const char* Name);
void SetRegionEditorName(TESRegionEx* Region, const char* Name);