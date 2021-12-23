#include "Dodge.h"

static const UInt32 kJumpPressedHook = 0x00672A79;
static const UInt32 kJumpPressedReturn1 = 0x00672A80;
static const UInt32 kJumpPressedReturn2 = 0x00672B94;
static const UInt32 kDoubleTapHook = 0x006729DA;
static const UInt32 kDoubleTapReturn = 0x006729EA;

static UInt8 DoubleTapStep = 0;
static UInt8 Direction[2] = { 0, 0 };
static UInt32 IsDoubleTapped = 0;
static float DoubleTapTime = -1.0f;

static const UInt32 kGetControlState = 0x00403520;
static const UInt32 kGetCharacterController = 0x0065A2C0;
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

void DoubleTap(UInt16 PressedDirection) {
	
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

void CreateDodgeHook() {

	if (TheSettingManager->SettingsMain.Dodge.Enabled) {
		SafeWrite8(0x00672A17, TheSettingManager->SettingsMain.Dodge.AcrobaticsLevel);

		if (TheSettingManager->SettingsMain.Dodge.DoubleTap) {
			SafeWriteJump(0x00672941, 0x00672954);
			SafeWriteJump(kJumpPressedHook,	(UInt32)JumpPressedHook);
			SafeWriteJump(kDoubleTapHook,	(UInt32)DoubleTapHook);
		}
	}

}