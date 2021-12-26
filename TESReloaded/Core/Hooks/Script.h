#pragma once

static void (__thiscall* RunScript)(TES*) = (void (__thiscall*)(TES*))Hooks::RunScript;
static void __fastcall RunScriptHook(TES* This, UInt32 edx) {

	(*RunScript)(This);
	TheScriptManager->Run();

}