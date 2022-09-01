#pragma once

int (__thiscall* ServeSentence)(PlayerCharacter*) = (int (__thiscall*)(PlayerCharacter*))Hooks::ServeSentence;
int __fastcall ServeSentenceHook(PlayerCharacter* This, UInt32 edx) {

	This->ResetCamera();
	return (*ServeSentence)(This);

}

void (__thiscall* SetFurnitureCameraState)(PlayerCamera*, TESFurniture*) = (void (__thiscall*)(PlayerCamera*, TESFurniture*))Hooks::SetFurnitureCameraState;
void __fastcall SetFurnitureCameraStateHook(PlayerCamera* This, UInt32 edx, TESFurniture* Furniture) {

	PlayerCamera* Camera = (PlayerCamera*)This;
	UInt8 SitSleepState = Player->GetSitSleepState();

	if (SitSleepState == 7 && Camera->cameraState->stateId == TESCameraState::CameraState::kCameraState_Furniture) Player->QueueNiNodeUpdate();
	(*SetFurnitureCameraState)(This, Furniture);

}

int (__thiscall* ProcessSleepWaitMenu)(SleepWaitMenu*, UInt32) = (int (__thiscall*)(SleepWaitMenu*, UInt32))Hooks::ProcessSleepWaitMenu;
int __fastcall ProcessSleepWaitMenuHook(SleepWaitMenu* This, UInt32 edx, UInt32 Arg1) {
	
	bool IsPlayerSleeping = Player->flags725 & 4;

	if (Player->JailedState && IsPlayerSleeping) Served = true;
	bool r = (*ProcessSleepWaitMenu)(This, Arg1);
	if (Served && !IsPlayerSleeping) {
		Served = false;
		InterfaceManager->ShowMessageBox(*(const char**)0x01B19068, (void*)0x00499D70, *(const char**)0x01B17FA0, *(const char**)0x01B17FAC);
	}
	return r;

}