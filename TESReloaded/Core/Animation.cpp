#include "Animation.h"

#define ORAnimString "_OR_"

static const UInt32 kNewAnimSequenceSingleHook = 0x0047414D;
static const UInt32 kNewAnimSequenceSingleReturn = 0x00474157;
static const UInt32 kRemoveSequenceHook = 0x004742B7;
static const UInt32 kRemoveSequenceReturn1 = 0x004742BF;
static const UInt32 kRemoveSequenceReturn2 = 0x004742CD;

static ActorAnimDataEx* AnimDataAnimation = NULL;

class Animation {
public:
	ActorAnimData*			TrackNewActorAnimData();
	ActorAnimData*			TrackDisposeActorAnimData();
	bool					TrackAddAnimation(ModelKF* Model, UInt8 Arg);
	void					TrackAddSingle(BSAnimGroupSequence* AnimGroupSequence);
	void					TrackAddMultiple(BSAnimGroupSequence* AnimGroupSequence);
	BSAnimGroupSequence*	TrackGetBSAnimGroupSequenceS(int Index);
	BSAnimGroupSequence*	TrackGetBSAnimGroupSequenceM(int Index);
	AnimSequenceMultiple*	TrackNewAnimSequenceMultiple(AnimSequenceSingle* SourceAnimSequence);
	void					TrackApplyActorAnimData();
};

ActorAnimData* (__thiscall Animation::* NewActorAnimData)();
ActorAnimData* (__thiscall Animation::* TrackNewActorAnimData)();
ActorAnimData* Animation::TrackNewActorAnimData() {	

	ActorAnimDataEx* AnimData = (ActorAnimDataEx*)(this->*NewActorAnimData)();
	
	NiTList<BSAnimGroupSequence>* ORAnims = (NiTList<BSAnimGroupSequence>*)MemoryAlloc(0x10);
	*(void**)ORAnims = (void*)0x00A3C748;
	ORAnims->start = NULL;
	ORAnims->end = NULL;
	ORAnims->numItems = NULL;
	AnimData->ORAnims = ORAnims;
	return (ActorAnimData*)AnimData;

}

ActorAnimData* (__thiscall Animation::* DisposeActorAnimData)();
ActorAnimData* (__thiscall Animation::* TrackDisposeActorAnimData)();
ActorAnimData* Animation::TrackDisposeActorAnimData() {
	
	ActorAnimDataEx* AnimData = (ActorAnimDataEx*)this;
	BSAnimGroupSequence* AnimGroupSequence = NULL;
	NiTList<BSAnimGroupSequence>* ORAnims = AnimData->ORAnims;
	NiTList<BSAnimGroupSequence>::Entry* Iter = ORAnims->start;

	while (Iter) {
		AnimGroupSequence = Iter->data;
		if (AnimGroupSequence && !InterlockedDecrement(&AnimGroupSequence->m_uiRefCount)) AnimGroupSequence->Destructor(true);
		Iter = Iter->next;
	}
	ORAnims->Destructor(true);
	return (this->*DisposeActorAnimData)();

}

bool (__thiscall Animation::* AddAnimation)(ModelKF*, UInt8);
bool (__thiscall Animation::* TrackAddAnimation)(ModelKF*, UInt8);
bool Animation::TrackAddAnimation(ModelKF* Model, UInt8 Arg) {

	AnimDataAnimation = (ActorAnimDataEx*)this;

	return (this->*AddAnimation)(Model, Arg);

}

void AddORAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence) {
	
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

void (__thiscall Animation::* AddSingle)(BSAnimGroupSequence*);
void (__thiscall Animation::* TrackAddSingle)(BSAnimGroupSequence*);
void Animation::TrackAddSingle(BSAnimGroupSequence* AnimGroupSequence) {

	if (AnimGroupSequence && AnimGroupSequence->animGroup->animOR) AddORAnimGroupSequence(AnimGroupSequence);
	(this->*AddSingle)(AnimGroupSequence);

}

void(__thiscall Animation::* AddMultiple)(BSAnimGroupSequence*);
void(__thiscall Animation::* TrackAddMultiple)(BSAnimGroupSequence*);
void Animation::TrackAddMultiple(BSAnimGroupSequence* AnimGroupSequence) {

	if (AnimGroupSequence->animGroup->animOR)
		AddORAnimGroupSequence(AnimGroupSequence);
	else
		(this->*AddMultiple)(AnimGroupSequence);

}

BSAnimGroupSequence* (__thiscall Animation::* GetBSAnimGroupSequenceS)(int);
BSAnimGroupSequence* (__thiscall Animation::* TrackGetBSAnimGroupSequenceS)(int);
BSAnimGroupSequence* Animation::TrackGetBSAnimGroupSequenceS(int Index) {

	AnimSequenceSingleEx* AnimSequence = (AnimSequenceSingleEx*)this;

	if (AnimSequence->ORAnim) return AnimSequence->ORAnim;
	return (this->*GetBSAnimGroupSequenceS)(Index);

}

BSAnimGroupSequence* (__thiscall Animation::* GetBSAnimGroupSequenceM)(int);
BSAnimGroupSequence* (__thiscall Animation::* TrackGetBSAnimGroupSequenceM)(int);
BSAnimGroupSequence* Animation::TrackGetBSAnimGroupSequenceM(int Index) {

	AnimSequenceMultipleEx* AnimSequence = (AnimSequenceMultipleEx*)this;
	
	if (AnimSequence->Anims->numItems == 0) return NULL; // Fixes an Oblivion bug; Oblivion does a division by numItems before checking it.
	if (Index == -1 && AnimSequence->ORAnim) return AnimSequence->ORAnim;
	return (this->*GetBSAnimGroupSequenceM)(Index);

}

AnimSequenceMultiple* (__thiscall Animation::* NewAnimSequenceMultiple)(AnimSequenceSingle*);
AnimSequenceMultiple* (__thiscall Animation::* TrackNewAnimSequenceMultiple)(AnimSequenceSingle*);
AnimSequenceMultiple* Animation::TrackNewAnimSequenceMultiple(AnimSequenceSingle* SourceAnimSequence) {

	AnimSequenceMultipleEx* AnimSequence = (AnimSequenceMultipleEx*)(this->*NewAnimSequenceMultiple)(SourceAnimSequence);

	AnimSequence->ORAnim = NULL;
	return (AnimSequenceMultiple*)AnimSequence;

}

void (__thiscall Animation::* ApplyActorAnimData)();
void (__thiscall Animation::* TrackApplyActorAnimData)();
void Animation::TrackApplyActorAnimData() {
	
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
	ActorAnimData* AnimData = (ActorAnimData*)this;
	HighProcess* Process = (HighProcess*)Player->process;
	SettingsMainStruct::IKFootStruct* IKFoot = &TheSettingManager->SettingsMain.IKFoot;
	UInt8 AnimGroup = TESAnimGroup::AnimGroup::kAnimGroup_Idle;

	(this->*ApplyActorAnimData)();
	if (AnimData == Process->animData && AnimData->animSequences[0]) {
		AnimGroup = AnimData->animSequences[0]->animGroup->animGroup;
		if (AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_Idle || AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_TurnLeft || AnimGroup == TESAnimGroup::AnimGroup::kAnimGroup_TurnRight) {
			NiNode* RFoot = (NiNode*)AnimData->nBip01->GetObjectByName("Bip01 R Foot");
			NiNode* LFoot = (NiNode*)AnimData->nBip01->GetObjectByName("Bip01 L Foot");
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
				ThighM = &AnimData->nBip01->GetObjectByName("Bip01 L Thigh")->m_localTransform.rot;
				CalfM = &AnimData->nBip01->GetObjectByName("Bip01 L Calf")->m_localTransform.rot;
				FootM = &LFoot->m_localTransform.rot;
				ToeM = &AnimData->nBip01->GetObjectByName("Bip01 L Toe0")->m_localTransform.rot;
			}
			else if (RDistance < LDistance) {
				ThighM = &AnimData->nBip01->GetObjectByName("Bip01 R Thigh")->m_localTransform.rot;
				CalfM = &AnimData->nBip01->GetObjectByName("Bip01 R Calf")->m_localTransform.rot;
				FootM = &RFoot->m_localTransform.rot;
				ToeM = &AnimData->nBip01->GetObjectByName("Bip01 R Toe0")->m_localTransform.rot;
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
				(this->*ApplyActorAnimData)();
			}
		}
	}

}

TESAnimGroup* (__cdecl* LoadTESAnimGroup)(NiControllerSequence*, char*) = (TESAnimGroup* (__cdecl*)(NiControllerSequence*, char*))0x0051B490;
TESAnimGroup* __cdecl TrackLoadTESAnimGroup(NiControllerSequence* ControllerSequence, char* FilePath) {

	TESAnimGroup* AnimGroup = LoadTESAnimGroup(ControllerSequence, FilePath);

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

void CreateAnimationHook() {

	*((int *)&NewActorAnimData)			= 0x00473EB0;
	TrackNewActorAnimData				= &Animation::TrackNewActorAnimData;
	*((int *)&DisposeActorAnimData)		= 0x00475B60;
	TrackDisposeActorAnimData			= &Animation::TrackDisposeActorAnimData;
	*((int *)&AddAnimation)				= 0x00474070;
	TrackAddAnimation					= &Animation::TrackAddAnimation;
	*((int *)&AddSingle)				= 0x00470BA0;
	TrackAddSingle						= &Animation::TrackAddSingle;
	*((int *)&AddMultiple)				= 0x00471930;
	TrackAddMultiple					= &Animation::TrackAddMultiple;
	*((int *)&GetBSAnimGroupSequenceS)	= 0x00471710;
	TrackGetBSAnimGroupSequenceS		= &Animation::TrackGetBSAnimGroupSequenceS;
	*((int *)&GetBSAnimGroupSequenceM)	= 0x00470BF0;
	TrackGetBSAnimGroupSequenceM		= &Animation::TrackGetBSAnimGroupSequenceM;
	*((int *)&NewAnimSequenceMultiple)	= 0x00473D90;
	TrackNewAnimSequenceMultiple		= &Animation::TrackNewAnimSequenceMultiple;
	*((int*)&ApplyActorAnimData)		= 0x00471F20;
	TrackApplyActorAnimData				= &Animation::TrackApplyActorAnimData;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)NewActorAnimData,			*((PVOID*)&TrackNewActorAnimData));
	DetourAttach(&(PVOID&)DisposeActorAnimData,		*((PVOID*)&TrackDisposeActorAnimData));
	DetourAttach(&(PVOID&)AddAnimation,				*((PVOID*)&TrackAddAnimation));
	DetourAttach(&(PVOID&)AddSingle,				*((PVOID*)&TrackAddSingle));
	DetourAttach(&(PVOID&)AddMultiple,				*((PVOID*)&TrackAddMultiple));
	DetourAttach(&(PVOID&)GetBSAnimGroupSequenceS,	*((PVOID*)&TrackGetBSAnimGroupSequenceS));
	DetourAttach(&(PVOID&)GetBSAnimGroupSequenceM,	*((PVOID*)&TrackGetBSAnimGroupSequenceM));
	DetourAttach(&(PVOID&)NewAnimSequenceMultiple,	*((PVOID*)&TrackNewAnimSequenceMultiple));
	if (TheSettingManager->SettingsMain.IKFoot.Enabled) DetourAttach(&(PVOID&)ApplyActorAnimData,		*((PVOID*)&TrackApplyActorAnimData));
	DetourAttach(&(PVOID&)LoadTESAnimGroup,					  &TrackLoadTESAnimGroup);
	DetourTransactionCommit();

	SafeWriteJump(kNewAnimSequenceSingleHook, (UInt32)NewAnimSequenceSingleHook);
	SafeWriteJump(kRemoveSequenceHook,		  (UInt32)RemoveSequenceHook);

	SafeWrite32(0x004E3814, sizeof(ActorAnimDataEx));
	SafeWrite32(0x004E3ADD, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00667E23, sizeof(ActorAnimDataEx));
	SafeWrite32(0x00669258, sizeof(ActorAnimDataEx));

	SafeWrite8(0x00474140, sizeof(AnimSequenceSingleEx));
	SafeWrite8(0x004741C0, sizeof(AnimSequenceMultipleEx));

}