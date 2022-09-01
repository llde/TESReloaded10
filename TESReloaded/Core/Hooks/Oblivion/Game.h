#pragma once
extern Main* (__thiscall* NewMain)(Main*, HWND, HINSTANCE);
Main* __fastcall NewMainHook(Main* This, UInt32 edx, HWND Window, HINSTANCE Instance);

extern TES* (__thiscall* NewTES)(TES*, char*, NiNode*, NiNode*, Sky*);
TES* __fastcall NewTESHook(TES* This, UInt32 edx, char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky);

extern MainDataHandler* (__thiscall* NewMainDataHandler)(MainDataHandler*);
MainDataHandler* __fastcall NewMainDataHandlerHook(MainDataHandler* This, UInt32 edx);