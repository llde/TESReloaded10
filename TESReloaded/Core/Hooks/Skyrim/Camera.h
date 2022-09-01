#pragma once

extern int (__thiscall* SetCameraState)(PlayerCamera*, TESCameraState*);
int __fastcall SetCameraStateHook(PlayerCamera* This, UInt32 edx, TESCameraState* CameraState);

extern void (__thiscall* ManageButtonEvent)(PlayerInputHandler*, ButtonEvent*, int);
void __fastcall ManageButtonEventHook(PlayerInputHandler* This, UInt32 edx, ButtonEvent* Event, int Arg2);

extern void (__thiscall* SetCameraPosition)(ThirdPersonState*);
void __fastcall SetCameraPositionHook(ThirdPersonState* This, UInt32 edx);