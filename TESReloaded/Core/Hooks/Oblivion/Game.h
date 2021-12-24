#pragma once

static Main* (__thiscall* NewMain)(Main*, HWND, HINSTANCE) = (Main* (__thiscall*)(Main*, HWND, HINSTANCE))Hooks::NewMain;
static Main* __fastcall NewMainHook(Main* This, UInt32 edx, HWND Window, HINSTANCE Instance) {

	Global = (*NewMain)(This, Window, Instance);
	return Global;

}

static TES* (__thiscall* NewTES)(TES*, char*, NiNode*, NiNode*, Sky*) = (TES* (__thiscall*)(TES*, char*, NiNode*, NiNode*, Sky*))Hooks::NewTES;
static TES* __fastcall NewTESHook(TES* This, UInt32 edx, char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky) {
	
	Tes = (*NewTES)(This, RootData, ObjectLODRoot, LandLOD, Sky);
	SceneNode = *(ShadowSceneNode**)0x00B42F54;
	return Tes;

}