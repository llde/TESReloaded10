#pragma once

static __declspec(naked) void JumpPressedHook() {

	__asm {
		push    1
		push	13
		mov		ecx, edi
		call	kGetControlState
		test	eax, eax
		jz		short loc_notpressed
		mov		ecx, ebx
		call	kGetCharacterController
		jmp		kJumpPressedReturn1

	loc_notpressed:
		jmp		kJumpPressedReturn2
	}

}

static void DoubleTap(UInt16 PressedDirection) {
	
	IsDoubleTapped = 0;
	if (PressedDirection & 0xF) {
		if (PressedDirection & 0x1)
			Direction[DoubleTapStep] = PressedDirection & 0x1;
		else if (PressedDirection & 0x2)
			Direction[DoubleTapStep] = PressedDirection & 0x2;
		else if (PressedDirection & 0x4)
			Direction[DoubleTapStep] = PressedDirection & 0x4;
		else if (PressedDirection & 0x8)
			Direction[DoubleTapStep] = PressedDirection & 0x8;
		if (DoubleTapTime == -1.0f)
			DoubleTapTime = 0.0f;
		else {
			DoubleTapTime += TheFrameRateManager->ElapsedTime;
			if (DoubleTapStep == 1 && Direction[0] == Direction[1]) {
				IsDoubleTapped = 1;
				DoubleTapStep = 0;
				DoubleTapTime = -1.0f;
			}
		}
		if (DoubleTapTime > TheSettingManager->SettingsMain.Dodge.DoubleTapTime) {
			DoubleTapStep = 0;
			DoubleTapTime = -1.0f;
		}
	}
	else if (DoubleTapTime >= 0.0f) {
		if (DoubleTapTime < TheSettingManager->SettingsMain.Dodge.DoubleTapTime) {
			DoubleTapTime += TheFrameRateManager->ElapsedTime;
			if (DoubleTapStep == 0) DoubleTapStep = 1;
		}
		else {
			DoubleTapTime = -1.0f;
			DoubleTapStep = 0;
		}
	}

}

static __declspec(naked) void DoubleTapHook() {

	__asm {
		mov		byte ptr [esp + 0x13], 0
		pushad
		mov		eax, [esp + 0x34]
		push	eax
		call	DoubleTap
		add		esp, 4
		popad
		mov		eax, IsDoubleTapped
		jmp		kDoubleTapReturn
	}

}