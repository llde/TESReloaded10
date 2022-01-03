#pragma once

static int (__thiscall* SetCameraState)(PlayerCamera*, TESCameraState*) = (int (__thiscall*)(PlayerCamera*, TESCameraState*))Hooks::SetCameraState;
static int __fastcall SetCameraStateHook(PlayerCamera* This, UInt32 edx, TESCameraState* CameraState) {
	
	bool IsWeaponOut = false;

	if (This->cameraNode->m_pcName && CameraState->camera->thirdPersonState2 != NULL) {
		if (CameraState->stateId == TESCameraState::CameraState::kCameraState_FirstPerson) {
			if (TheCameraManager->IsFirstPerson() && TheCameraManager->TogglePOV) {
				CameraState = This->thirdPersonState2;
				TheCameraManager->SetFirstPerson(false);
			}
			else {
				CameraState = This->thirdPersonState2;
				TheCameraManager->SetFirstPerson(true);
			}
		}
		else if (CameraState->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) TheCameraManager->SetFirstPerson(false);
		if (TheCameraManager->IsFirstPerson() && CameraState->stateId != TESCameraState::CameraState::kCameraState_ThirdPerson2) TheCameraManager->SetFirstPerson(false);
		if (!TheCameraManager->IsFirstPerson() && CameraState->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) {
			IsWeaponOut = Player->actorState.IsWeaponOut();
			This->AllowVanityMode = !IsWeaponOut;
			This->UpdateOverShoulder(IsWeaponOut);
		}
		TheCameraManager->TogglePOV = false;
	}
	return (*SetCameraState)(This, CameraState);

}

static void (__thiscall* ManageButtonEvent)(PlayerInputHandler*, ButtonEvent*, int) = (void (__thiscall*)(PlayerInputHandler*, ButtonEvent*, int))Hooks::ManageButtonEvent;
static void __fastcall ManageButtonEventHook(PlayerInputHandler* This, UInt32 edx, ButtonEvent* Event, int Arg2) {
	
	ThirdPersonState* State = (ThirdPersonState*)(This - 0x10); //ecx is ThirdPersonState for PlayerInputHandler (class is "shifted" due to the multi inheritance)
	
	(*ManageButtonEvent)(This, Event, Arg2);
	if (State->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) {
		if (PlayerControls::Get()->IsCamSwitchControlEnabled()) {
			if (State->TogglePOV) TheCameraManager->TogglePOV = true;
			if (TheCameraManager->IsFirstPerson() && *Event->GetControlID() == InputStringHolder::Get()->zoomOut) State->camera->SetCameraState(State->camera->thirdPersonState2);
		}
	}

}

static void (__thiscall* SetCameraPosition)(ThirdPersonState*) = (void (__thiscall*)(ThirdPersonState*))Hooks::SetCameraPosition;
static void __fastcall SetCameraPositionHook(ThirdPersonState* This, UInt32 edx) {

	BSFixedString Head;

	if (TheCameraManager->IsFirstPerson()) {
		Head.Create("NPC Head [Head]");
		NiNode* ActorNode = Player->GetNiRootNode(0);
		NiPoint3* HeadPosition = &ActorNode->GetObjectByName(&Head)->m_worldTransform.pos;
		NiPoint3 v = ActorNode->m_worldTransform.rot * TheSettingManager->SettingsMain.CameraMode.Offset;
		This->CameraPosition.x = HeadPosition->x + v.x;
		This->CameraPosition.y = HeadPosition->y + v.y;
		This->CameraPosition.z = HeadPosition->z + v.z;
		This->OverShoulderPosX = This->OverShoulderPosY = This->OverShoulderPosZ = 0.0f;
		This->camera->AllowVanityMode = 0;
		Head.Dispose();
	}
	(*SetCameraPosition)(This);
	
}