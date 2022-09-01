#pragma once
extern NiDX9Renderer* (__thiscall* InitializeRenderer)(NiDX9Renderer*);
NiDX9Renderer* __fastcall InitializeRendererHook(NiDX9Renderer* This, UInt32 edx);

extern PlayerCharacter* (__thiscall* NewPlayerCharacter)(PlayerCharacter*);
PlayerCharacter* __fastcall NewPlayerCharacterHook(PlayerCharacter* This, UInt32 edx);

extern SceneGraph* (__thiscall* NewSceneGraph)(SceneGraph*, char*, UInt8, NiCamera*);
SceneGraph* __fastcall NewSceneGraphHook(SceneGraph* This, UInt32 edx, char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera);

extern MenuInterfaceManager* (__thiscall* NewMenuInterfaceManager)(MenuInterfaceManager*);
MenuInterfaceManager* __fastcall NewMenuInterfaceManagerHook(MenuInterfaceManager* This, UInt32 edx);

extern QueuedModelLoader* (__thiscall* NewQueuedModelLoader)(QueuedModelLoader*);
QueuedModelLoader* __fastcall NewQueuedModelLoaderHook(QueuedModelLoader* This, UInt32 edx);