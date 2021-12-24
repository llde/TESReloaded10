#include "CameraManager.h"

#if defined(OBLIVION)
#define kToggleCamera 0x0066C580
static const UInt32 kUpdateCameraHook = 0x0066BE6E;
static const UInt32 kUpdateCameraReturn = 0x0066BE7C;
static const UInt32 kSwitchCameraHook = 0x00671AC9;
static const UInt32 kSwitchCameraReturn = 0x00671AD0;
static const UInt32 kSwitchCameraPOVHook = 0x00672FDA;
static const UInt32 kSwitchCameraPOVReturn = 0x00672FE2;
static const UInt32 kHeadTrackingHook = 0x0055D6A8;
static const UInt32 kHeadTrackingReturn = 0x0055D6B5;
static const UInt32 kHeadTrackingReturn1 = 0x0055D7E6;
static const UInt32 kSpineTrackingHook = 0x00603C55;
static const UInt32 kSpineTrackingReturn = 0x00603C5E;
static const UInt32 kSpineTrackingReturn1 = 0x00603C95;

CameraManager::CameraManager() {

	Logger::Log("Starting the camera manager...");
	TheCameraManager = this;

	DialogTarget = NULL;
	From = { 0.0f, 0.0f, 0.0f };
	FromOffset = { 0.0f, 0.0f, 0.0f };
	CameraCommands = new CameraManagerCommands();
	FirstPersonView = false;

}

void CameraManager::ResetCamera() {
	
	ThisCall(0x0066C600, this);

}

void CameraManager::SetSceneGraph() {
	
	float* SettingWorldFoV = (float*)0x00B0313C;
	float* Setting1stPersonFoV = (float*)0x00B0313C;
	float* SettingNearDistance = (float*)0x00B03134;
	float FoV = TheSettingManager->SettingsMain.CameraMode.FoV;
	
	*SettingNearDistance = 2.5f;
	if (FoV != WorldSceneGraph->cameraFOV && !Player->IsAiming() && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		WorldSceneGraph->UpdateParticleShaderFoVData(FoV);
		Player->worldFoV = *SettingWorldFoV = *Setting1stPersonFoV = FoV;
	}
	TheShaderManager->ShaderConst.ReciprocalResolution.w = Player->worldFoV;
}

bool CameraManager::IsVanityView() {
	
	return *(bool*)0x00B3BB04;

}

void CameraManager::ExecuteCommands(NiAVObject* CameraNode) {

	CameraCommands->Execute(CameraNode);

}

CameraManager::CameraManagerCommands::CameraManagerCommands() {

	memset(this, NULL, sizeof(CameraManagerCommands));

}

void CameraManager::CameraManagerCommands::Execute(NiAVObject* CameraNode) {

	if (!IsTranslating && !IsRotating && !IsLookingAt && !IsTranslatingToPosition && !IsRotatingToPosition && !IsLookingAtPosition) return;

	NiMatrix33* CameraRotationW = &CameraNode->m_worldTransform.rot;
	NiPoint3* CameraPositionW = &CameraNode->m_worldTransform.pos;
	NiMatrix33* CameraRotationL = &CameraNode->m_localTransform.rot;
	NiPoint3* CameraPositionL = &CameraNode->m_localTransform.pos;
	NiMatrix33* NodeRotationW = NULL;
	NiPoint3* NodePositionW = NULL;
	NiMatrix33 m;
	NiPoint3 v;

	if (Ref) {
		NiNode* RootNode = Ref->GetNiNode();
		if (Ref->IsActor() && (IsTranslating || IsLookingAt)) {
			NiAVObject* Head = RootNode->GetObjectByName("Bip01 Head");
			NodeRotationW = &Head->m_worldTransform.rot;
			NodePositionW = &Head->m_worldTransform.pos;
		}
		else {
			NodeRotationW = &RootNode->m_worldTransform.rot;
			NodePositionW = &RootNode->m_worldTransform.pos;
		}
	}

	if (IsTranslating) {
		v = *NodeRotationW * Position;
		v.x += NodePositionW->x;
		v.y += NodePositionW->y;
		v.z += NodePositionW->z;
		memcpy(CameraPositionW, &v, sizeof(NiPoint3));
		memcpy(CameraPositionL, &v, sizeof(NiPoint3));
	}

	if (IsRotating) {
		m.GenerateRotationMatrixZXY(&Rotation, 1);
		m = *NodeRotationW * m;
		memcpy(CameraRotationW, &m, sizeof(NiMatrix33));
		memcpy(CameraRotationL, &m, sizeof(NiMatrix33));
	}

	if (IsTranslatingToPosition) {
		memcpy(CameraPositionW, &Position, sizeof(NiPoint3));
		memcpy(CameraPositionL, &Position, sizeof(NiPoint3));
	}

	if (IsRotatingToPosition) {
		m.GenerateRotationMatrixZXY(&Rotation, 1);
		memcpy(CameraRotationW, &m, sizeof(NiMatrix33));
		memcpy(CameraRotationL, &m, sizeof(NiMatrix33));
	}

	if (IsLookingAt || IsLookingAtPosition) {
		if (!IsTranslating && !IsTranslatingToPosition) {
			Position.x = CameraPositionW->x;
			Position.y = CameraPositionW->y;
			Position.z = CameraPositionW->z;
		}
		if (IsLookingAt) {
			LookingAtPosition = *NodeRotationW * LookingAtOffset;
			LookingAtPosition.x += NodePositionW->x;
			LookingAtPosition.y += NodePositionW->y;
			LookingAtPosition.z += NodePositionW->z;
		}
		Position.GetLookAt(&LookingAtPosition, &v);
		m.GenerateRotationMatrixZXY(&v, 1);
		memcpy(CameraRotationW, &m, sizeof(NiMatrix33));
		memcpy(CameraRotationL, &m, sizeof(NiMatrix33));
	}

}

class CameraMode {
public:
	void TrackToggleCamera(UInt8);
	void TrackToggleBody(UInt8);
	void TrackSetDialogCamera(Actor*, float, UInt8);
	void TrackUpdateCameraCollisions(NiPoint3*, NiPoint3*, UInt8);
	void TrackSetAimingZoom(float);
};

void (__thiscall CameraMode::* ToggleCamera)(UInt8);
void (__thiscall CameraMode::* TrackToggleCamera)(UInt8);
void CameraMode::TrackToggleCamera(UInt8 FirstPersonView) {
	
	TheCameraManager->FirstPersonView = FirstPersonView;
	if (Player->IsAiming()) { (this->*ToggleCamera)(1); return; }
	(this->*ToggleCamera)(0);

}

void (__thiscall CameraMode::* ToggleBody)(UInt8);
void (__thiscall CameraMode::* TrackToggleBody)(UInt8);
void CameraMode::TrackToggleBody(UInt8 FirstPersonView) {
	
	if (Player->IsAiming()) { (this->*ToggleBody)(1); return; }
	(this->*ToggleBody)(0);

}

void (__thiscall CameraMode::* SetDialogCamera)(Actor*, float, UInt8);
void (__thiscall CameraMode::* TrackSetDialogCamera)(Actor*, float, UInt8);
void CameraMode::TrackSetDialogCamera(Actor* Act, float Arg2, UInt8 Arg3) {

	TheCameraManager->DialogTarget = Act;

}

void (__thiscall CameraMode::* UpdateCameraCollisions)(NiPoint3*, NiPoint3*, UInt8);
void (__thiscall CameraMode::* TrackUpdateCameraCollisions)(NiPoint3*, NiPoint3*, UInt8);
void CameraMode::TrackUpdateCameraCollisions(NiPoint3* CameraPosition, NiPoint3* PlayerPosition, UInt8 CameraChasing) {
	
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
	(this->*UpdateCameraCollisions)(CameraPosition, PlayerPosition, CameraChasing);
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

void (__thiscall CameraMode::* SetAimingZoom)(float);
void (__thiscall CameraMode::* TrackSetAimingZoom)(float);
void CameraMode::TrackSetAimingZoom(float Arg1) {
	
	if (TheCameraManager->FirstPersonView) {
		if (Player->IsAiming()) ThisCall(kToggleCamera, Player, 1);
		(this->*SetAimingZoom)(Arg1);
	}

}

void UpdateCamera(NiAVObject* CameraNode, NiPoint3* LocalPosition) {
	
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

static const UInt32 GameToggleCamera = kToggleCamera;
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

void SetReticleOffset(NiPoint3* CameraPos) {
	
	PlayerCharacterEx* PlayerEx = (PlayerCharacterEx*)Player;

	CameraPos->x += PlayerEx->ReticleOffset.x;
	CameraPos->y += PlayerEx->ReticleOffset.y;
	CameraPos->z += PlayerEx->ReticleOffset.z;

}

static const UInt32 kSetReticleOffsetHook = 0x00580796;
static const UInt32 kSetReticleOffsetReturn = 0x0058079C;
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

void CreateCameraModeHook() {

	*((int*)&ToggleCamera)					= kToggleCamera;
	TrackToggleCamera						= &CameraMode::TrackToggleCamera;
	*((int*)&ToggleBody)					= 0x00664F70;
	TrackToggleBody							= &CameraMode::TrackToggleBody;
	*((int *)&SetDialogCamera)				= 0x0066C6F0;
	TrackSetDialogCamera					= &CameraMode::TrackSetDialogCamera;
	*((int *)&SetAimingZoom)				= 0x00666670;
	TrackSetAimingZoom						= &CameraMode::TrackSetAimingZoom;
	*((int *)&UpdateCameraCollisions)		= 0x0065F080;
	TrackUpdateCameraCollisions				= &CameraMode::TrackUpdateCameraCollisions;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ToggleCamera,				*((PVOID*)&TrackToggleCamera));
	DetourAttach(&(PVOID&)ToggleBody,				*((PVOID*)&TrackToggleBody));
	DetourAttach(&(PVOID&)SetDialogCamera,			*((PVOID*)&TrackSetDialogCamera));
	DetourAttach(&(PVOID&)SetAimingZoom,			*((PVOID*)&TrackSetAimingZoom));
	DetourAttach(&(PVOID&)UpdateCameraCollisions,	*((PVOID*)&TrackUpdateCameraCollisions));
	DetourTransactionCommit();

	SafeWriteJump(kUpdateCameraHook,	 (UInt32)UpdateCameraHook);
	SafeWriteJump(kSwitchCameraHook,	 (UInt32)SwitchCameraHook);
	SafeWriteJump(kSwitchCameraPOVHook,  (UInt32)SwitchCameraPOVHook);
	SafeWriteJump(kHeadTrackingHook,	 (UInt32)HeadTrackingHook);
	SafeWriteJump(kSpineTrackingHook,	 (UInt32)SpineTrackingHook);
	SafeWriteJump(kSetReticleOffsetHook, (UInt32)SetReticleOffsetHook);
	SafeWriteJump(0x0066B769, 0x0066B795); // Does not lower the player Z axis value (fixes the bug of the camera on feet after resurrection)
	SafeWriteJump(0x00666704, 0x0066672D); // Enables the zoom with the bow

	SafeWrite32(0x00406775, sizeof(PlayerCharacterEx));
	SafeWrite32(0x0046451E, sizeof(PlayerCharacterEx));

}
#elif defined (SKYRIM)
static bool TogglePOV = false;

class CameraMode {
public:
	int TrackSetCameraState(TESCameraState*);
	void TrackManageButtonEvent(ButtonEvent*, int);
	void TrackSetCameraPosition();
};

int (__thiscall CameraMode::* SetCameraState)(TESCameraState*);
int (__thiscall CameraMode::* TrackSetCameraState)(TESCameraState*);
int CameraMode::TrackSetCameraState(TESCameraState* CameraState) {
	
	PlayerCamera* Camera = (PlayerCamera*)this;
	bool IsWeaponOut = false;

	if (Camera->cameraNode->m_pcName && CameraState->camera->thirdPersonState2 != NULL) {
		if (CameraState->stateId == TESCameraState::CameraState::kCameraState_FirstPerson) {
			if (TheRenderManager->FirstPersonView && TogglePOV) {
				CameraState = Camera->thirdPersonState2;
				TheRenderManager->FirstPersonView = false;
			}
			else {
				CameraState = Camera->thirdPersonState2;
				TheRenderManager->FirstPersonView = true;
			}
		}
		else if (CameraState->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) TheRenderManager->FirstPersonView = false;
		if (TheRenderManager->FirstPersonView && CameraState->stateId != TESCameraState::CameraState::kCameraState_ThirdPerson2) TheRenderManager->FirstPersonView = false;
		if (!TheRenderManager->FirstPersonView && CameraState->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) {
			IsWeaponOut = Player->actorState.IsWeaponOut();
			Camera->AllowVanityMode = !IsWeaponOut;
			Camera->UpdateOverShoulder(IsWeaponOut);
		}
		TogglePOV = false;
	}
	return (this->*SetCameraState)(CameraState);

}

void (__thiscall CameraMode::* ManageButtonEvent)(ButtonEvent*, int);
void (__thiscall CameraMode::* TrackManageButtonEvent)(ButtonEvent*, int);
void CameraMode::TrackManageButtonEvent(ButtonEvent* Event, int Arg2) {
	
	ThirdPersonState* State = (ThirdPersonState*)(this - 0x10); //ecx is ThirdPersonState for PlayerInputHandler (class is "shifted" due to the multi inheritance)
	
	(this->*ManageButtonEvent)(Event, Arg2);
	if (State->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2) {
		if (PlayerControls::Get()->IsCamSwitchControlEnabled()) {
			if (State->TogglePOV) TogglePOV = true;
			if (TheRenderManager->FirstPersonView && *Event->GetControlID() == InputStringHolder::Get()->zoomOut) State->camera->SetCameraState(State->camera->thirdPersonState2);
		}
	}

}

void (__thiscall CameraMode::* SetCameraPosition)();
void (__thiscall CameraMode::* TrackSetCameraPosition)();
void CameraMode::TrackSetCameraPosition() {

	ThirdPersonState* State = (ThirdPersonState*)this;
	BSFixedString Head;

	if (TheRenderManager->FirstPersonView) {
		Head.Create("NPC Head [Head]");
		NiNode* ActorNode = Player->GetNiRootNode(0);
		NiPoint3* HeadPosition = &ActorNode->GetObjectByName(&Head)->m_worldTransform.pos;
		NiPoint3 v = ActorNode->m_worldTransform.rot * TheSettingManager->SettingsMain.CameraMode.Offset;
		State->CameraPosition.x = HeadPosition->x + v.x;
		State->CameraPosition.y = HeadPosition->y + v.y;
		State->CameraPosition.z = HeadPosition->z + v.z;
		State->OverShoulderPosX = State->OverShoulderPosY = State->OverShoulderPosZ = 0.0f;
		State->camera->AllowVanityMode = 0;
		Head.Dispose();
	}
	(this->*SetCameraPosition)();
	
}

void CreateCameraModeHook() {

	*((int *)&SetCameraState)			= 0x006533D0;
	TrackSetCameraState					= &CameraMode::TrackSetCameraState;
	*((int *)&ManageButtonEvent)		= 0x00840BE0;
	TrackManageButtonEvent				= &CameraMode::TrackManageButtonEvent;
	*((int *)&SetCameraPosition)		= 0x0083F690;
	TrackSetCameraPosition				= &CameraMode::TrackSetCameraPosition;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)SetCameraState,		*((PVOID*)&TrackSetCameraState));
	DetourAttach(&(PVOID&)ManageButtonEvent,	*((PVOID*)&TrackManageButtonEvent));
	DetourAttach(&(PVOID&)SetCameraPosition,	*((PVOID*)&TrackSetCameraPosition));
	DetourTransactionCommit();
	
	SafeWrite8(0x0083F69B, 0); // Stops PlayerCharacter fading

}
#endif