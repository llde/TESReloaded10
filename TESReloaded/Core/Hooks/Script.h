#pragma once

extern void(__thiscall* RunScript)(TES*);
void __fastcall RunScriptHook(TES* This, UInt32 edx);