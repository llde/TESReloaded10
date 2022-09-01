#pragma once
extern void(__thiscall* ToggleCamera)(PlayerCharacter*, UInt8);
void __fastcall ToggleCameraHook(PlayerCharacter* This, UInt32 edx, UInt8 FirstPersonView);

extern void(__thiscall* ToggleBody)(PlayerCharacter*, UInt8);
void __fastcall ToggleBodyHook(PlayerCharacter* This, UInt32 edx, UInt8 FirstPersonView);

extern void(__thiscall* SetDialogCamera)(PlayerCharacter*, Actor*, float, UInt8);
void __fastcall SetDialogCameraHook(PlayerCharacter* This, UInt32 edx, Actor* Act, float Arg2, UInt8 Arg3);

extern void(__thiscall* UpdateCameraCollisions)(PlayerCharacter*, NiPoint3*, NiPoint3*, UInt8);
void __fastcall UpdateCameraCollisionsHook(PlayerCharacter* This, UInt32 edx, NiPoint3* CameraPosition, NiPoint3* PlayerPosition, UInt8 CameraChasing);

extern void(__thiscall* SetAimingZoom)(PlayerCharacter*, float);
void __fastcall SetAimingZoomHook(PlayerCharacter* This, UInt32 edx, float Arg1);

void UpdateCameraHook();
void SwitchCameraHook();
void SwitchCameraPOVHook();
void HeadTrackingHook();
void SpineTrackingHook();
void SetReticleOffsetHook();