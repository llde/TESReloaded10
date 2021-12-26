#pragma once

static __declspec(naked) void UpdateTimeInfoHook() {

	__asm {
		pushad
		mov		ecx, TheFrameRateManager
		call	FrameRateManager::PerformSync
		popad
		call	TimeInfoUpdate
		jmp		kUpdateTimeInfoReturn
	}

}

static void EndProcessHook() {
	
	void* SettingCollection = (void*)0x00B07BF0;
	char* SettingName = (char*)0x00B07BF4;

	ThisCall(0x0040C180, SettingCollection, SettingName);
	TerminateProcess(GetCurrentProcess(), 0);

}