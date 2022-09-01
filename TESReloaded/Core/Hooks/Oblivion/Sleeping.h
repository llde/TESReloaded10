#pragma once
extern int(__thiscall* ServeSentence)(PlayerCharacter*);
int __fastcall ServeSentenceHook(PlayerCharacter* This, UInt32 edx);

extern bool(__thiscall* RemoveWornItems)(PlayerCharacter*, Actor*, UInt8, int);
bool __fastcall RemoveWornItemsHook(PlayerCharacter* This, UInt32 edx, Actor* Act, UInt8 Arg2, int Arg3);

extern bool(__cdecl* ProcessSleepWaitMenu)();
bool __cdecl ProcessSleepWaitMenuHook();

extern void(__cdecl* CloseSleepWaitMenu)();
void __cdecl CloseSleepWaitMenuHook();
