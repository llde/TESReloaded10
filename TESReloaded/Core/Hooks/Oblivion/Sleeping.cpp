#include "Sleeping.h"

int (__thiscall* ServeSentence)(PlayerCharacter*) = (int (__thiscall*)(PlayerCharacter*))Hooks::ServeSentence;
int __fastcall ServeSentenceHook(PlayerCharacter* This, UInt32 edx) {

	TheCameraManager->ResetCamera();
	Player->unk61C = 0.0f;
	Player->Resurrect(0, 0, 0);
	return (*ServeSentence)(This);

}

bool (__thiscall* RemoveWornItems)(PlayerCharacter*, Actor*, UInt8, int) = (bool (__thiscall*)(PlayerCharacter*, Actor*, UInt8, int))Hooks::RemoveWornItems;
bool __fastcall RemoveWornItemsHook(PlayerCharacter* This, UInt32 edx, Actor* Act, UInt8 Arg2, int Arg3) {
	
	if (Act == Player) return 1;
	return (*RemoveWornItems)(This, Act, Arg2, Arg3);

}

bool (__cdecl* ProcessSleepWaitMenu)() = (bool (__cdecl*)())Hooks::ProcessSleepWaitMenu;
bool __cdecl ProcessSleepWaitMenuHook() {

	if (Player->JailedState && Player->isSleeping) Served = true;
	return ProcessSleepWaitMenu();
}

void (__cdecl* CloseSleepWaitMenu)() = (void (__cdecl*)())Hooks::CloseSleepWaitMenu;
void __cdecl CloseSleepWaitMenuHook() {

	CloseSleepWaitMenu();
	if (Served) {
		Served = false;
		InterfaceManager->ShowMessageBox(*(const char**)0x00B38B30, (void*)0x00671600, *(const char**)0x00B38CF8, *(const char**)0x00B38D00);
	}

}