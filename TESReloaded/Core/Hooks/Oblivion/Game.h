#pragma once

TES* (__thiscall GameInitialization::* NewTES)(char*, NiNode*, NiNode*, Sky*);
TES* (__thiscall GameInitialization::* TrackNewTES)(char*, NiNode*, NiNode*, Sky*);
TES* GameInitialization::TrackNewTES(char* RootData, NiNode* ObjectLODRoot, NiNode* LandLOD, Sky* Sky) { Tes = (TES*)(this->*NewTES)(RootData, ObjectLODRoot, LandLOD, Sky); SceneNode = *(ShadowSceneNode**)kShadowSceneNode; return Tes; }