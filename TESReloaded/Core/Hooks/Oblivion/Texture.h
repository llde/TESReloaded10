#pragma once
extern void(__thiscall* WaterSurfacePass)(WaterManager*, NiCamera*);
void __fastcall WaterSurfacePassHook(WaterManager* This, UInt32 edx, NiCamera* Camera);

