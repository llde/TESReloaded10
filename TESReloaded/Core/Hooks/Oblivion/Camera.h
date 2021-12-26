#pragma once

static void (__thiscall* ToggleCamera)(PlayerCharacter*, UInt8) = (void (__thiscall*)(PlayerCharacter*, UInt8))Hooks::ToggleCamera;
static void __fastcall ToggleCameraHook(PlayerCharacter* This, UInt32 edx, UInt8 FirstPersonView) {
	
	TheCameraManager->FirstPersonView = FirstPersonView;
	if (Player->IsAiming()) { (*ToggleCamera)(This, 1); return; }
	(*ToggleCamera)(This, 0);

}

static void (__thiscall* ToggleBody)(PlayerCharacter*, UInt8) = (void (__thiscall*)(PlayerCharacter*, UInt8))Hooks::ToggleBody;
static void __fastcall ToggleBodyHook(PlayerCharacter* This, UInt32 edx, UInt8 FirstPersonView) {
	
	if (Player->IsAiming()) { (*ToggleBody)(This, 1); return; }
	(*ToggleBody)(This, 0);

}

static void (__thiscall* SetDialogCamera)(PlayerCharacter*, Actor*, float, UInt8) = (void (__thiscall*)(PlayerCharacter*, Actor*, float, UInt8))Hooks::SetDialogCamera;
static void __fastcall SetDialogCameraHook(PlayerCharacter* This, UInt32 edx, Actor* Act, float Arg2, UInt8 Arg3) {

	TheCameraManager->DialogTarget = Act;

}

static void (__thiscall* UpdateCameraCollisions)(PlayerCharacter*, NiPoint3*, NiPoint3*, UInt8) = (void (__thiscall*)(PlayerCharacter*, NiPoint3*, NiPoint3*, UInt8))Hooks::UpdateCameraCollisions;
static void __fastcall UpdateCameraCollisionsHook(PlayerCharacter* This, UInt32 edx, NiPoint3* CameraPosition, NiPoint3* PlayerPosition, UInt8 CameraChasing) {
	
	SettingsMainStruct::CameraModeStruct* CameraMode = &TheSettingManager->SettingsMain.CameraMode;
	UInt8 Crosshair = TheSettingManager->SettingsMain.CameraMode.Crosshair;
	UInt8 DisableFading = Player->DisableFading;
	UInt8 SitSleepState = Player->GetSitSleepState();

	if (SitSleepState >= HighProcess::kSitSleep_SleepingIn && SitSleepState <= HighProcess::kSitSleep_SleepingOut) Player->DisableFading = 1;
	if (!TheCameraManager->FirstPersonView) {
		CameraChasing = !CameraMode->ChasingThird;
	}
	else {
		Player->DisableFading = 1;
		CameraChasing = !CameraMode->ChasingFirst;
	}
	(*UpdateCameraCollisions)(This, CameraPosition, PlayerPosition, CameraChasing);
	Player->DisableFading = DisableFading;
	if (Crosshair == 0) {
		if (!TheCameraManager->FirstPersonView) InterfaceManager->SetCrosshair(0); else InterfaceManager->SetCrosshair(1);
	}
	else {
		if (Crosshair == 1) {
			InterfaceManager->SetCrosshair(0);
		}
		else {
			if (Player->IsAiming())
				InterfaceManager->SetCrosshair(1);
			else
				InterfaceManager->SetCrosshair(0);
		}
	}

}

static void (__thiscall* SetAimingZoom)(PlayerCharacter*, float) = (void (__thiscall*)(PlayerCharacter*, float))Hooks::SetAimingZoom;
static void __fastcall SetAimingZoomHook(PlayerCharacter* This, UInt32 edx, float Arg1) {
	
	if (TheCameraManager->FirstPersonView) {
		if (Player->IsAiming()) ThisCall(kToggleCamera, Player, 1);
		(*SetAimingZoom)(This, Arg1);
	}

}

static void UpdateCamera(NiAVObject* CameraNode, NiPoint3* LocalPosition) {
	
	PlayerCharacterEx* PlayerEx = (PlayerCharacterEx*)Player;
	SettingsMainStruct::CameraModeStruct* CameraMode = &TheSettingManager->SettingsMain.CameraMode;
	NiMatrix33* CameraRotation = &CameraNode->m_localTransform.rot;
	NiPoint3* CameraPosition = &CameraNode->m_localTransform.pos;
	UInt8 SitSleepState = Player->GetSitSleepState();
	HighProcess* Process = (HighProcess*)Player->process;
	NiPoint3* HeadPosition = &Process->animData->nHead->m_worldTransform.pos;
	NiPoint3* From = &TheCameraManager->From;
	NiPoint3* FromOffset = &TheCameraManager->FromOffset;
	NiPoint3 Rot = { 0.0f, 0.0f, 0.0f };
	NiMatrix33 mw, ml;
	NiPoint3 Offset;
	
	if (SitSleepState < HighProcess::kSitSleep_SleepingIn || SitSleepState > HighProcess::kSitSleep_SleepingOut) From->x = 0.0f;
	if (!TheCameraManager->FirstPersonView && SitSleepState >= HighProcess::kSitSleep_SleepingIn && SitSleepState <= HighProcess::kSitSleep_SleepingOut) {
		if (From->x == 0.0f) {
			From->x = CameraPosition->x;
			From->y = CameraPosition->y;
			From->z = CameraPosition->z - 20.0f;
		}
		else {
			TheCameraManager->FromOffset = { 0.0f, 0.0f, 0.0f };
			if (TheKeyboardManager->OnControlPressed(2))
				FromOffset->x -= 5.0f;
			else if (TheKeyboardManager->OnControlPressed(3))
				FromOffset->x += 5.0f;
			if (TheKeyboardManager->OnControlPressed(0))
				FromOffset->y += 5.0f;
			else if (TheKeyboardManager->OnControlPressed(1))
				FromOffset->y -= 5.0f;
			if (TheKeyboardManager->OnControlPressed(4))
				FromOffset->z += 5.0f;
			else if (TheKeyboardManager->OnControlPressed(6))
				FromOffset->z -= 5.0f;
			if (FromOffset->x != 0.0f || FromOffset->y != 0.0f || FromOffset->z != 0.0f) {
				Offset = CameraNode->m_worldTransform.rot * TheCameraManager->FromOffset;
				From->x += Offset.x;
				From->y += Offset.y;
				From->z += Offset.z;
			}
		}
		CameraPosition->x = From->x;
		CameraPosition->y = From->y;
		CameraPosition->z = From->z;
		mw.GenerateRotationMatrixZXY(&Rot, 1);
		CameraPosition->GetLookAt(HeadPosition, &Rot);
		ml.GenerateRotationMatrixZXY(&Rot, 1);
		CameraNode->m_worldTransform.rot = mw;
		CameraNode->m_localTransform.rot = ml;
	}
	else if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog) || InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) {
		HighProcess* DialogTargetProcess = (HighProcess*)TheCameraManager->DialogTarget->process;
		Offset = { CameraMode->DialogOffset.z * Player->scale, CameraMode->DialogOffset.y * Player->scale, CameraMode->DialogOffset.x * Player->scale };
		Offset = Process->animData->nHead->m_worldTransform.rot * Offset;
		CameraPosition->x = HeadPosition->x + Offset.x;
		CameraPosition->y = HeadPosition->y + Offset.y;
		CameraPosition->z = HeadPosition->z + Offset.z;
		HeadPosition = &DialogTargetProcess->animData->nHead->m_worldTransform.pos;
		mw.GenerateRotationMatrixZXY(&Rot, 1);
		CameraPosition->GetLookAt(HeadPosition, &Rot);
		ml.GenerateRotationMatrixZXY(&Rot, 1);
		CameraNode->m_worldTransform.rot = mw;
		CameraNode->m_localTransform.rot = ml;
	}
	else if (TheCameraManager->FirstPersonView && !TheCameraManager->IsVanityView()) {
		if (SitSleepState != HighProcess::kSitSleep_SittingIn && SitSleepState != HighProcess::kSitSleep_SittingOut) {
			Offset = { CameraMode->Offset.z * Player->scale, CameraMode->Offset.y * Player->scale, CameraMode->Offset.x * Player->scale };
			if (Player->IsAiming() && Player->ActorSkinInfo->WeaponForm->weaponType == TESObjectWEAP::WeaponType::kWeapType_Bow) {
				Offset.x = CameraMode->AimingOffset.z * Player->scale;
				Offset.y = CameraMode->AimingOffset.y * Player->scale;
				Offset.z = CameraMode->AimingOffset.x * Player->scale;
			}
			Offset = Process->animData->nHead->m_worldTransform.rot * Offset;
			CameraPosition->x = HeadPosition->x + Offset.x;
			CameraPosition->y = HeadPosition->y + Offset.y;
			CameraPosition->z = HeadPosition->z + Offset.z;
			PlayerEx->ReticleOffset.x = Offset.x;
			PlayerEx->ReticleOffset.y = Offset.y;
			PlayerEx->ReticleOffset.z = Offset.z;
		}
		BSAnimGroupSequence* AnimSequence = Process->animData->animSequences[0];
		TESAnimGroup* AnimGroup = (AnimSequence ? AnimSequence->animGroup : NULL);
		if ((AnimGroup && AnimGroup->animGroup >= TESAnimGroup::kAnimGroup_DodgeForward && AnimGroup->animGroup <= TESAnimGroup::kAnimGroup_DodgeRight && AnimGroup->animType == 0) || (SitSleepState >= HighProcess::kSitSleep_SleepingIn && SitSleepState <= HighProcess::kSitSleep_SleepingOut) || !Player->IsAlive() || Process->KnockedState) {
			Rot.z = 90.0f;
			ml.GenerateRotationMatrixZXY(&Rot, 1);
			ml = Process->animData->nHead->m_worldTransform.rot * ml;
			memcpy(CameraRotation, &ml, sizeof(NiMatrix33));
		}
	}
	
	TheCameraManager->ExecuteCommands(CameraNode);
	
	LocalPosition->x = CameraPosition->x;
	LocalPosition->y = CameraPosition->y;
	LocalPosition->z = CameraPosition->z;

}

static __declspec(naked) void UpdateCameraHook() {

	__asm {
		pushad
		lea		ecx, [esp + 0x58]
		push	ecx
		push	eax
		call	UpdateCamera
		pop		eax
		pop		ecx
		popad
		jmp		kUpdateCameraReturn
	}

}

static __declspec(naked) void SwitchCameraHook() {

	__asm {
		mov		eax, TheCameraManager
		movzx	edx, byte ptr[eax + CameraManager::FirstPersonView]
		cmp		edx, 1
		jmp		kSwitchCameraReturn
	}

}

static __declspec(naked) void SwitchCameraPOVHook() {

	__asm {
		mov		eax, TheCameraManager
		movzx	ecx, byte ptr [eax + CameraManager::FirstPersonView]
		xor		ecx, 1
		push	ecx
		mov		ecx, ebx
		call	GameToggleCamera
		jmp		kSwitchCameraPOVReturn
	}

}

static __declspec(naked) void HeadTrackingHook() {

	__asm {
		mov     eax, [ebp + 0x114]
		cmp		eax, Player
		jz		short loc_SkipTracking
		jmp		kHeadTrackingReturn

	loc_SkipTracking:
		jmp		kHeadTrackingReturn1
	}

}

static __declspec(naked) void SpineTrackingHook() {

	__asm {
		cmp		esi, Player
		jz		short loc_SkipTracking
		jmp		kSpineTrackingReturn

	loc_SkipTracking:
		jmp		kSpineTrackingReturn1
	}

}

static void SetReticleOffset(NiPoint3* CameraPos) {
	
	PlayerCharacterEx* PlayerEx = (PlayerCharacterEx*)Player;

	CameraPos->x += PlayerEx->ReticleOffset.x;
	CameraPos->y += PlayerEx->ReticleOffset.y;
	CameraPos->z += PlayerEx->ReticleOffset.z;

}

static __declspec(naked) void SetReticleOffsetHook() {

	__asm {
		lea		eax, [esp + 0x20]
		push	eax
		call	SetReticleOffset
		pop		eax
		mov     ecx, Player
		jmp		kSetReticleOffsetReturn
	}

}