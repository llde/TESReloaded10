#pragma once
#define FlyCamFBValue [ebp - 0x80]
#define FlyCamRLValue [ebp - 0x84]

static float Scroll = 0.0f;

void (__thiscall* UpdateFlyCam)(PlayerCharacter*) = (void (__thiscall*)(PlayerCharacter*))Hooks::UpdateFlyCam;
void __fastcall UpdateFlyCamHook(PlayerCharacter* This, UInt32 edx) {
	
	ffi::FlyCamStruct* FlyCam = &TheSettingManager->Config->FlyCam;
	float ScrollMultiplier = FlyCam->ScrollMultiplier;

	if (Global->OnKeyDown(FlyCam->KeyAdd)) FlyCam->ScrollMultiplier += FlyCam->StepValue;
	if (Global->OnKeyDown(FlyCam->KeySubtract)) FlyCam->ScrollMultiplier -= FlyCam->StepValue;
	if (FlyCam->ScrollMultiplier <= 0.0f) FlyCam->ScrollMultiplier = 1.0f;
	Scroll = FlyCam->ScrollMultiplier * 10.0f;
	if (ScrollMultiplier != FlyCam->ScrollMultiplier) {
		char Message[64];
		sprintf(Message, "Fly cam scroll multiplier: %.1f", FlyCam->ScrollMultiplier);
		InterfaceManager->ShowMessage(Message);
	}
	(*UpdateFlyCam)(This);

}

 __declspec(naked) void UpdateForwardFlyCamHook() {

	__asm {
		fld		FlyCamFBValue
		fadd	Scroll
		fstp	FlyCamFBValue
		jmp		Jumpers::FlyCam::UpdateForwardFlyCamReturn
	}

}

__declspec(naked) void UpdateBackwardFlyCamHook() {

	__asm {
		fld		FlyCamFBValue
		fsub	Scroll
		fstp	FlyCamFBValue
		jmp		Jumpers::FlyCam::UpdateBackwardFlyCamReturn
	}

}

__declspec(naked) void UpdateRightFlyCamHook() {

	__asm {
		fld		FlyCamRLValue
		fadd	Scroll
		fstp	FlyCamRLValue
		jmp		Jumpers::FlyCam::UpdateRightFlyCamReturn
	}

}

__declspec(naked) void UpdateLeftFlyCamHook() {

	__asm {
		fld		FlyCamRLValue
		fsub	Scroll
		fstp	FlyCamRLValue
		jmp		Jumpers::FlyCam::UpdateLeftFlyCamReturn
	}

}