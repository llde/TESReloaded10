#pragma once
extern void(__thiscall* UpdateFlyCam)(PlayerCharacter*);
void __fastcall UpdateFlyCamHook(PlayerCharacter* This, UInt32 edx);

void UpdateForwardFlyCamHook();
void UpdateBackwardFlyCamHook();
void UpdateRightFlyCamHook();
void UpdateLeftFlyCamHook();