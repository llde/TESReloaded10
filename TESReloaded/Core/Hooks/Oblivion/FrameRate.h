#pragma once
static const UInt32 ASMTimeInfoUpdate = 0x0047D170;

static __declspec(naked) void UpdateTimeInfoHook() {

	__asm {
		pushad
		mov		ecx, TheFrameRateManager
		call	FrameRateManager::PerformSync
		popad
		call	ASMTimeInfoUpdate
		jmp		Jumpers::UpdateTimeInfo::Return
	}

}

static void EndProcessHook() {
	
	void* SettingCollection = (void*)0x00B07BF0;
	char* SettingName = (char*)0x00B07BF4;

	ThisCall(0x0040C180, SettingCollection, SettingName);
	TerminateProcess(GetCurrentProcess(), 0);

}