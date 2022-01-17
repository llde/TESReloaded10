#pragma once

static int (__thiscall* ServeSentence)(PlayerCharacter*) = (int (__thiscall*)(PlayerCharacter*))Hooks::ServeSentence;
static int __fastcall ServeSentenceHook(PlayerCharacter* This, UInt32 edx) {

	TheCameraManager->ResetCamera();
	Player->unk61C = 0.0f;
	Player->Resurrect(0, 0, 0);
	return (*ServeSentence)(This);

}

static bool (__thiscall* RemoveWornItems)(PlayerCharacter*, Actor*, UInt8, int) = (bool (__thiscall*)(PlayerCharacter*, Actor*, UInt8, int))Hooks::RemoveWornItems;
static bool __fastcall RemoveWornItemsHook(PlayerCharacter* This, UInt32 edx, Actor* Act, UInt8 Arg2, int Arg3) {
	
	if (Act == Player) return 1;
	return (*RemoveWornItems)(This, Act, Arg2, Arg3);

}

static bool (__cdecl* ProcessSleepWaitMenu)() = (bool (__cdecl*)())Hooks::ProcessSleepWaitMenu;
static bool __cdecl ProcessSleepWaitMenuHook() {

	if (Player->JailedState && Player->isSleeping) Served = true;
	return ProcessSleepWaitMenu();

}

static void (__cdecl* CloseSleepWaitMenu)() = (void (__cdecl*)())Hooks::CloseSleepWaitMenu;
static void __cdecl CloseSleepWaitMenuHook() {

	CloseSleepWaitMenu();
	if (Served) {
		Served = false;
		InterfaceManager->ShowMessageBox(Pointers::Generic::MessageBoxServeSentenceText, Pointers::Generic::ServeSentenceCallback, Pointers::Generic::MessageBoxButtonYes, Pointers::Generic::MessageBoxButtonNo);
	}

}