#pragma once

Main* (__thiscall* NewMain)(HWND, HINSTANCE) = (Main* (__thiscall*)(HWND, HINSTANCE))Hooks::NewMain;
Main* __fastcall NewMainHook(HWND Window, HINSTANCE Instance) { SetMenuManager; Global = (Main*)(this->*NewMain)(Window, Instance); return Global; }

NiDX9Renderer* (__thiscall GameInitialization::* InitializeRenderer)();
NiDX9Renderer* (__thiscall GameInitialization::* TrackInitializeRenderer)();
NiDX9Renderer* GameInitialization::TrackInitializeRenderer() { TheRenderManager = (RenderManager*)(this->*InitializeRenderer)(); TheRenderManager->Initialize(); InitializeManagers(); TheShaderManager->CreateEffects(); return TheRenderManager; }

PlayerCharacter* (__thiscall GameInitialization::* NewPlayerCharacter)();
PlayerCharacter* (__thiscall GameInitialization::* TrackNewPlayerCharacter)();
PlayerCharacter* GameInitialization::TrackNewPlayerCharacter() { Player = (PlayerCharacter*)(this->*NewPlayerCharacter)(); return Player; }

SceneGraph* (__thiscall GameInitialization::* NewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* (__thiscall GameInitialization::* TrackNewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* GameInitialization::TrackNewSceneGraph(char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) { SceneGraph* SG = (SceneGraph*)(this->*NewSceneGraph)(Name, IsMinFarPlaneDistance, Camera); if (!strcmp(Name, "World")) WorldSceneGraph = SG; return SG; }

MasterDataHandler* (__thiscall GameInitialization::* NewMasterDataHandler)();
MasterDataHandler* (__thiscall GameInitialization::* TrackNewMasterDataHandler)();
MasterDataHandler* GameInitialization::TrackNewMasterDataHandler() { DataHandler = (MasterDataHandler*)(this->*NewMasterDataHandler)(); TheScriptManager->LoadForms(); TheEquipmentManager->LoadForms(); return DataHandler; }

MenuInterfaceManager* (__thiscall GameInitialization::* NewMenuInterfaceManager)();
MenuInterfaceManager* (__thiscall GameInitialization::* TrackNewMenuInterfaceManager)();
MenuInterfaceManager* GameInitialization::TrackNewMenuInterfaceManager() { MenuManager = (MenuInterfaceManager*)(this->*NewMenuInterfaceManager)(); return MenuManager; }

QueuedModelLoader* (__thiscall GameInitialization::* NewQueuedModelLoader)();
QueuedModelLoader* (__thiscall GameInitialization::* TrackNewQueuedModelLoader)();
QueuedModelLoader* GameInitialization::TrackNewQueuedModelLoader() { ModelLoader = (QueuedModelLoader*)(this->*NewQueuedModelLoader)(); return ModelLoader; }