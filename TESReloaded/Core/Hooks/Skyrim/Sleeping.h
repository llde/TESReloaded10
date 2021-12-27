#pragma once

int (__thiscall SleepingMode::* ServeSentence)();
int (__thiscall SleepingMode::* TrackServeSentence)();
int SleepingMode::TrackServeSentence() {

	Player->RestoreCamera();
	return (this->*ServeSentence)();

}

void (__thiscall SleepingMode::* SetFurnitureCameraState)(TESFurniture*);
void (__thiscall SleepingMode::* TrackSetFurnitureCameraState)(TESFurniture*);
void SleepingMode::TrackSetFurnitureCameraState(TESFurniture* Furniture) {

	PlayerCamera* Camera = (PlayerCamera*)this;
	UInt8 SitSleepState = Player->GetSitSleepState();

	if (SitSleepState == 7 && Camera->cameraState->stateId == TESCameraState::CameraState::kCameraState_Furniture) Player->QueueNiNodeUpdate();
	(this->*SetFurnitureCameraState)(Furniture);

}

int (__thiscall SleepingMode::* ProcessSleepWaitMenu)(UInt32);
int (__thiscall SleepingMode::* TrackProcessSleepWaitMenu)(UInt32);
int SleepingMode::TrackProcessSleepWaitMenu(UInt32 Arg1) {
	
	bool IsPlayerSleeping = Player->flags725 & 4;

	if (Player->JailedState && IsPlayerSleeping) Served = true;
	bool r = (this->*ProcessSleepWaitMenu)(Arg1);
	if (Served && !IsPlayerSleeping) {
		Served = false;
		MenuManager->ShowMessageBox(*MessageBoxServeSentenceText, (void*)0x00499D70, *MessageBoxButtonYes, *MessageBoxButtonNo);
	}
	return r;

}