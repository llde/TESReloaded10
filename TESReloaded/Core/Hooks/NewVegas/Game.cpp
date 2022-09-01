#pragma once

Main* (__thiscall* NewMain)(Main*, HWND, HINSTANCE) = (Main* (__thiscall*)(Main*, HWND, HINSTANCE))Hooks::NewMain;
Main* __fastcall NewMainHook(Main* This, UInt32 edx, HWND Window, HINSTANCE Instance) {

	Global = (*NewMain)(This, Window, Instance);
	return Global;

}

TES* (__thiscall* NewTES)(TES*, char*, NiNode*, NiNode*, Sky*, NiNode*) = (TES* (__thiscall*)(TES*, char*, NiNode*, NiNode*, Sky*, NiNode*))Hooks::NewTES;
TES* __fastcall NewTESHook(TES* This, UInt32 edx, char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky, NiNode* WaterLOD) {
	
	Tes = (*NewTES)(This, RootData, ObjectLODRoot, LandLOD, Sky, WaterLOD);
	SceneNode = *(ShadowSceneNode**)0x011F91C8;
	return Tes;

}

MainDataHandler* (__thiscall* NewMainDataHandler)(MainDataHandler*) = (MainDataHandler* (__thiscall*)(MainDataHandler*))Hooks::NewMainDataHandler;
MainDataHandler* __fastcall NewMainDataHandlerHook(MainDataHandler* This, UInt32 edx) {

	DataHandler = (*NewMainDataHandler)(This);
	return DataHandler;

}