#pragma once

extern int (__thiscall* ServeSentence)(PlayerCharacter*);
int __fastcall ServeSentenceHook(PlayerCharacter* This, UInt32 edx);

extern void (__thiscall* SetFurnitureCameraState)(PlayerCamera*, TESFurniture*);
void __fastcall SetFurnitureCameraStateHook(PlayerCamera* This, UInt32 edx, TESFurniture* Furniture);

extern int (__thiscall* ProcessSleepWaitMenu)(SleepWaitMenu*, UInt32);
int __fastcall ProcessSleepWaitMenuHook(SleepWaitMenu* This, UInt32 edx, UInt32 Arg1);