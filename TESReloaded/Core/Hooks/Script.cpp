#pragma once

void (__thiscall* RunScript)(TES*) = (void (__thiscall*)(TES*))Hooks::RunScript;
void __fastcall RunScriptHook(TES* This, UInt32 edx) {

	(*RunScript)(This);
	TheScriptManager->Run();

}