#pragma once

static ActorAnimData* (__thiscall* NewActorAnimData)(ActorAnimData*) = (ActorAnimData* (__thiscall*)(ActorAnimData*))Hooks::NewActorAnimData;
static ActorAnimData* __fastcall NewActorAnimDataHook(ActorAnimData* This, UInt32 edx) {

	ActorAnimDataEx* AnimData = (ActorAnimDataEx*)(*NewActorAnimData)(This);
	
	NiTList<BSAnimGroupSequence>* ORAnims = (NiTList<BSAnimGroupSequence>*)MemoryAlloc(0x10);
	*(void**)ORAnims = (void*)0x00A3C748;
	ORAnims->start = NULL;
	ORAnims->end = NULL;
	ORAnims->numItems = NULL;
	AnimData->ORAnims = ORAnims;
	return (ActorAnimData*)AnimData;

}

static ActorAnimData* (__thiscall* DisposeActorAnimData)(ActorAnimData*) = (ActorAnimData* (__thiscall*)(ActorAnimData*))Hooks::DisposeActorAnimData;
static ActorAnimData* __fastcall DisposeActorAnimDataHook(ActorAnimData* This, UInt32 edx) {
	
	ActorAnimDataEx* AnimData = (ActorAnimDataEx*)This;
	BSAnimGroupSequence* AnimGroupSequence = NULL;
	NiTList<BSAnimGroupSequence>* ORAnims = AnimData->ORAnims;
	NiTList<BSAnimGroupSequence>::Entry* Iter = ORAnims->start;

	while (Iter) {
		AnimGroupSequence = Iter->data;
		if (AnimGroupSequence && !InterlockedDecrement(&AnimGroupSequence->m_uiRefCount)) AnimGroupSequence->Destructor(true);
		Iter = Iter->next;
	}
	ORAnims->Destructor(true);
	return (*DisposeActorAnimData)(This);

}

static bool (__thiscall* AddAnimation)(ActorAnimData*, ModelKF*, UInt8) = (bool (__thiscall*)(ActorAnimData*, ModelKF*, UInt8))Hooks::AddAnimation;
static bool __fastcall AddAnimationHook(ActorAnimData* This, UInt32 edx, ModelKF* Model, UInt8 Arg) {

	AnimDataAnimation = (ActorAnimDataEx*)This;

	return (*AddAnimation)(This, Model, Arg);

}

static void AddORAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence) {
	
	BSAnimGroupSequence* ExistedAnimGroupSequence = NULL;
	NiTList<BSAnimGroupSequence>::Entry* Iter = AnimDataAnimation->ORAnims->start;

	while (Iter) {
		ExistedAnimGroupSequence = Iter->data;
		if (ExistedAnimGroupSequence == AnimGroupSequence) break;
		Iter = Iter->next;
		ExistedAnimGroupSequence = NULL;
	}
	if (!ExistedAnimGroupSequence) {
		InterlockedIncrement(&AnimGroupSequence->m_uiRefCount);
		NiTList<BSAnimGroupSequence>* ORAnims = AnimDataAnimation->ORAnims;
		NiTList<BSAnimGroupSequence>::Entry* AnimNode = ORAnims->AllocateEntry();
		AnimNode->next = NULL;
		AnimNode->prev = ORAnims->end;
		AnimNode->data = AnimGroupSequence;
		if (ORAnims->end) {
			ORAnims->end->next = AnimNode;
			ORAnims->end = AnimNode;
		}
		else {
			ORAnims->start = AnimNode;
			ORAnims->end = AnimNode;
		}
		++ORAnims->numItems;
	}

}

static void (__thiscall* AddSingle)(AnimSequenceSingle*, BSAnimGroupSequence*) = (void (__thiscall*)(AnimSequenceSingle*, BSAnimGroupSequence*))Hooks::AddSingle;
static void __fastcall AddSingleHook(AnimSequenceSingle* This, UInt32 edx, BSAnimGroupSequence* AnimGroupSequence) {

	if (AnimGroupSequence && AnimGroupSequence->animGroup->animOR) AddORAnimGroupSequence(AnimGroupSequence);
	(*AddSingle)(This, AnimGroupSequence);

}

static void(__thiscall* AddMultiple)(AnimSequenceMultiple*, BSAnimGroupSequence*) = (void(__thiscall*)(AnimSequenceMultiple*, BSAnimGroupSequence*))Hooks::AddMultiple;
static void __fastcall AddMultipleHook(AnimSequenceMultiple* This, UInt32 edx, BSAnimGroupSequence* AnimGroupSequence) {

	if (AnimGroupSequence->animGroup->animOR)
		AddORAnimGroupSequence(AnimGroupSequence);
	else
		(*AddMultiple)(This, AnimGroupSequence);

}

static BSAnimGroupSequence* (__thiscall* GetAnimGroupSequenceSingle)(AnimSequenceSingle*, int) = (BSAnimGroupSequence* (__thiscall*)(AnimSequenceSingle*, int))Hooks::GetAnimGroupSequenceSingle;
static BSAnimGroupSequence* __fastcall GetAnimGroupSequenceSingleHook(AnimSequenceSingle* This, UInt32 edx, int Index) {

	AnimSequenceSingleEx* AnimSequence = (AnimSequenceSingleEx*)This;

	if (AnimSequence->ORAnim) return AnimSequence->ORAnim;
	return (*GetAnimGroupSequenceSingle)(This, Index);

}

static BSAnimGroupSequence* (__thiscall* GetAnimGroupSequenceMultiple)(AnimSequenceMultiple*, int) = (BSAnimGroupSequence* (__thiscall*)(AnimSequenceMultiple*, int))Hooks::GetAnimGroupSequenceMultiple;
static BSAnimGroupSequence* __fastcall GetAnimGroupSequenceMultipleHook(AnimSequenceMultiple* This, UInt32 edx, int Index) {

	AnimSequenceMultipleEx* AnimSequence = (AnimSequenceMultipleEx*)This;
	
	if (AnimSequence->Anims->numItems == 0) return NULL; // Fixes an Oblivion bug; Oblivion does a division by numItems before checking it.
	if (Index == -1 && AnimSequence->ORAnim) return AnimSequence->ORAnim;
	return (*GetAnimGroupSequenceMultiple)(This, Index);

}

static AnimSequenceMultiple* (__thiscall* NewAnimSequenceMultiple)(AnimSequenceMultiple*, AnimSequenceSingle*) = (AnimSequenceMultiple* (__thiscall*)(AnimSequenceMultiple*, AnimSequenceSingle*))Hooks::NewAnimSequenceMultiple;
static AnimSequenceMultiple* __fastcall NewAnimSequenceMultipleHook(AnimSequenceMultiple* This, UInt32 edx, AnimSequenceSingle* SourceAnimSequence) {

	AnimSequenceMultipleEx* AnimSequence = (AnimSequenceMultipleEx*)(*NewAnimSequenceMultiple)(This, SourceAnimSequence);

	AnimSequence->ORAnim = NULL;
	return (AnimSequenceMultiple*)AnimSequence;

}

static void (__thiscall* ApplyActorAnimData)(ActorAnimData*) = (void (__thiscall*)(ActorAnimData*))Hooks::ApplyActorAnimData;
static void __fastcall ApplyActorAnimDataHook(ActorAnimData* This, UInt32 edx) {
	
	const float RayDistance = 50.0f;
	const float Thigh = 50.0f;

	hkWorld* HavokWorld = NULL;
	NiMatrix33* ThighM = NULL;
	NiMatrix33* CalfM = NULL;
	NiMatrix33* FootM = NULL;
	NiMatrix33* ToeM = NULL;
	NiMatrix33 ThighMA;
	NiMatrix33 CalfMA;
	NiMatrix33 FootMA;
	NiMatrix33 ToeMA;
	NiPoint3 P;
	bhkWorldRayCastData WorldRayCastData;
	float RDistance = 0.0f;
	float LDistance = 0.0f;
	float Height = 0.0f;
	float Angle = 0.0f;
	HighProcess* Process = (HighProcess*)Player->process;
	SettingsMainStruct::IKFootStruct* IKFoot = &TheSettingManager->SettingsMain.IKFoot;
	UInt8 AnimGroup = TESAnimGroup::AnimGroup::kAnimGroup_Idle;

	(*ApplyActorAnimData)(This);
	if (This == Process->animData && This->animSequences[0]) {
		AnimGroup = This->animSequences[0]->animGroup->animGroup;
		if (AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_Idle || AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_TurnLeft || AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_TurnRight) {
			NiNode* RFoot = (NiNode*)This->nBip01->GetObjectByName("Bip01 R Foot");
			NiNode* LFoot = (NiNode*)This->nBip01->GetObjectByName("Bip01 L Foot");
			HavokWorld = Player->parentCell->GetHavokWorld();
			WorldRayCastData.Init();
			P = RFoot->m_worldTransform.pos;
			WorldRayCastData.SetFrom(&P);
			P.z -= RayDistance;
			WorldRayCastData.SetTo(&P);
			if (HavokWorld->CastRay(&WorldRayCastData)) RDistance = WorldRayCastData.WorldRayCastOutput.HitFraction * RayDistance;
			#if _DEBUG
			NiNode* RNode = Tes->CastRay(&WorldRayCastData);
			#endif		
			WorldRayCastData.Init();
			P = LFoot->m_worldTransform.pos;
			WorldRayCastData.SetFrom(&P);
			P.z -= RayDistance;
			WorldRayCastData.SetTo(&P);
			HavokWorld->CastRay(&WorldRayCastData);
			if (HavokWorld->CastRay(&WorldRayCastData)) LDistance = WorldRayCastData.WorldRayCastOutput.HitFraction * RayDistance;
			#if _DEBUG
			NiNode* LNode = Tes->CastRay(&WorldRayCastData);
			#endif		
			Height = abs(RDistance - LDistance) / Player->niNode->m_worldTransform.scale;
			if (RDistance > LDistance) {
				ThighM = &This->nBip01->GetObjectByName("Bip01 L Thigh")->m_localTransform.rot;
				CalfM = &This->nBip01->GetObjectByName("Bip01 L Calf")->m_localTransform.rot;
				FootM = &LFoot->m_localTransform.rot;
				ToeM = &This->nBip01->GetObjectByName("Bip01 L Toe0")->m_localTransform.rot;
			}
			else if (RDistance < LDistance) {
				ThighM = &This->nBip01->GetObjectByName("Bip01 R Thigh")->m_localTransform.rot;
				CalfM = &This->nBip01->GetObjectByName("Bip01 R Calf")->m_localTransform.rot;
				FootM = &RFoot->m_localTransform.rot;
				ToeM = &This->nBip01->GetObjectByName("Bip01 R Toe0")->m_localTransform.rot;
			}
			if (Height > 1.0f) {
				Angle = acos((Thigh - Height) / Thigh) * IKFoot->Coeff;
				P = { Angle * IKFoot->CoeffThigh, 0.0f, 0.0f };
				ThighMA.GenerateRotationMatrixZXY(&P, false);
				P.x = Angle * IKFoot->CoeffCalf;
				CalfMA.GenerateRotationMatrixZXY(&P, false);
				P.x = Angle * IKFoot->CoeffFoot;
				FootMA.GenerateRotationMatrixZXY(&P, false);
				P.x = Angle * IKFoot->CoeffToe;
				ToeMA.GenerateRotationMatrixZXY(&P, false);
				*ThighM = *ThighM * ThighMA;
				*CalfM = *CalfM * CalfMA;
				*FootM = *FootM * FootMA;
				*ToeM = *ToeM * ToeMA;
				Player->niNode->m_localTransform.pos.z -= Height;
				(*ApplyActorAnimData)(This);
			}
		}
	}

}

static TESAnimGroup* (__cdecl* LoadAnimGroup)(NiControllerSequence*, char*) = (TESAnimGroup* (__cdecl*)(NiControllerSequence*, char*))Hooks::LoadAnimGroup;
static TESAnimGroup* __cdecl LoadAnimGroupHook(NiControllerSequence* ControllerSequence, char* FilePath) {

	TESAnimGroup* AnimGroup = LoadAnimGroup(ControllerSequence, FilePath);

	AnimGroup->animOR = (bool)strstr(FilePath, ORAnimString);
	return AnimGroup;

}

static __declspec(naked) void NewAnimSequenceSingleHook() {

	__asm {
		mov		[eax+0x8], esi
		mov		[eax+0x4], esi
		push	eax
		mov     dword ptr [eax], 0x00A3C72C
		jmp		kNewAnimSequenceSingleReturn
	}

}

static __declspec(naked) void RemoveSequenceHook() {

	__asm {
		mov		ecx, [eax+0x68]
		mov		edx, [ecx+0x0A]
		test	dl, dl
		jnz		short skip_removal
		push	eax
		lea		ecx, [esp+0x1C]
		push	ecx
		mov		ecx, edi
		jmp		kRemoveSequenceReturn1

	skip_removal:
		jmp		kRemoveSequenceReturn2
	}

}