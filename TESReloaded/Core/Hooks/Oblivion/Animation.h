#pragma once

extern ActorAnimData* (__thiscall* NewActorAnimData)(ActorAnimData*);
ActorAnimData* __fastcall NewActorAnimDataHook(ActorAnimData* This, UInt32 edx);

extern ActorAnimData* (__thiscall* DisposeActorAnimData)(ActorAnimData*);
ActorAnimData* __fastcall DisposeActorAnimDataHook(ActorAnimData* This, UInt32 edx);

extern bool(__thiscall* AddAnimation)(ActorAnimData*, ModelKF*, UInt8);
bool __fastcall AddAnimationHook(ActorAnimData* This, UInt32 edx, ModelKF* Model, UInt8 Arg);

void AddORAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence);

extern void(__thiscall* AddSingle)(AnimSequenceSingle*, BSAnimGroupSequence*);
void __fastcall AddSingleHook(AnimSequenceSingle* This, UInt32 edx, BSAnimGroupSequence* AnimGroupSequence);

extern void(__thiscall* AddMultiple)(AnimSequenceMultiple*, BSAnimGroupSequence*);
void __fastcall AddMultipleHook(AnimSequenceMultiple* This, UInt32 edx, BSAnimGroupSequence* AnimGroupSequence);

extern BSAnimGroupSequence* (__thiscall* GetAnimGroupSequenceSingle)(AnimSequenceSingle*, int);
BSAnimGroupSequence* __fastcall GetAnimGroupSequenceSingleHook(AnimSequenceSingle* This, UInt32 edx, int Index);

extern BSAnimGroupSequence* (__thiscall* GetAnimGroupSequenceMultiple)(AnimSequenceMultiple*, int);
BSAnimGroupSequence* __fastcall GetAnimGroupSequenceMultipleHook(AnimSequenceMultiple* This, UInt32 edx, int Index);

extern AnimSequenceMultiple* (__thiscall* NewAnimSequenceMultiple)(AnimSequenceMultiple*, AnimSequenceSingle*);
AnimSequenceMultiple* __fastcall NewAnimSequenceMultipleHook(AnimSequenceMultiple* This, UInt32 edx, AnimSequenceSingle* SourceAnimSequence);

extern void(__thiscall* ApplyActorAnimData)(ActorAnimData*);
void __fastcall ApplyActorAnimDataHook(ActorAnimData* This, UInt32 edx);

extern TESAnimGroup* (__cdecl* LoadAnimGroup)(NiControllerSequence*, char*);
TESAnimGroup* __cdecl LoadAnimGroupHook(NiControllerSequence* ControllerSequence, char* FilePath);

 void NewAnimSequenceSingleHook();
 void RemoveSequenceHook();