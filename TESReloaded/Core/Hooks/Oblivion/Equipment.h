#pragma once
extern HighProcess* (__thiscall* NewHighProcess)(HighProcess*);
HighProcess* __fastcall NewHighProcessHook(HighProcess* This, UInt32 edx);

extern void(__thiscall* ManageItem)(InventoryMenu*, int, TileRect*);
void __fastcall ManageItemHook(InventoryMenu* This, UInt32 edx, int SelectedID, TileRect* SelectedRect);

extern int(__thiscall* ProcessAction)(Character*, float, float);
int __fastcall ProcessActionHook(Character* This, UInt32 edx, float Arg1, float Arg2);

extern UInt8(__thiscall* ProcessControlAttack)(PlayerCharacter*);
UInt8 __fastcall ProcessControlAttackHook(PlayerCharacter* This, UInt32 edx);

extern void(__thiscall* AttackHandling)(Actor*, UInt8, TESObjectREFR*, TESObjectREFR*);
void __fastcall AttackHandlingHook(Actor* This, UInt32 edx, UInt8 Arg1, TESObjectREFR* Arrow, TESObjectREFR* Target);

extern InventoryChanges::EntryData* (__thiscall* GetEquippedWeaponData)(HighProcess*, UInt8);
InventoryChanges::EntryData* __fastcall GetEquippedWeaponDataHook(HighProcess* This, UInt32 edx, UInt8 Arg1);

extern bool(__thiscall* SetEquippedWeaponData)(HighProcess*, InventoryChanges::EntryData*, NiNode*);
bool __fastcall SetEquippedWeaponDataHook(HighProcess* This, UInt32 edx, InventoryChanges::EntryData* InventoryData, NiNode* ActorNode);

extern void(__thiscall* EquipItem)(InventoryChanges::Data*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void __fastcall EquipItemHook(InventoryChanges::Data* This, UInt32 edx, TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock);

extern void(__thiscall* UnequipItem)(InventoryChanges::Data*, UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void __fastcall UnequipItemHook(InventoryChanges::Data* This, UInt32 edx, UInt8* Arg1, TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock);

extern void(__thiscall* EquipWeapon)(Actor*, TESObjectWEAP*);
void __fastcall EquipWeaponHook(Actor* This, UInt32 edx, TESObjectWEAP* Weapon);

extern void(__thiscall* UnequipWeapon)(Actor*);
void __fastcall UnequipWeaponHook(Actor* This, UInt32 edx);

extern void(__thiscall* EquipShield)(Actor*, TESObjectARMO*);
void __fastcall EquipShieldHook(Actor* This, UInt32 edx, TESObjectARMO* Shield);

extern void(__thiscall* EquipLight)(Actor*, TESObjectLIGH*);
void __fastcall EquipLightHook(Actor* This, UInt32 edx, TESObjectLIGH* Light);

extern void(__thiscall* UnequipLight)(Character*);
void __fastcall UnequipLightHook(Character* This, UInt32 edx);

extern void(__thiscall* HideEquipment)(Actor*, TESForm*, UInt8);
void __fastcall HideEquipmentHook(Actor* This, UInt32 edx, TESForm* Form, UInt8 Arg2);

extern InventoryChanges::EntryData* (__thiscall* GetEquippedLightData)(HighProcess*, UInt8);
InventoryChanges::EntryData* __fastcall GetEquippedLightDataHook(HighProcess* This, UInt32 edx, UInt8 Arg1);

extern void(__thiscall* SaveGame)(InventoryChanges::EntryData*);
void __fastcall SaveGameHook(InventoryChanges::EntryData* This, UInt32 edx);

void UnequipTorchHook();
void EquipItemWornHook();
void PrnHook();
void SetWeaponRotationPositionHook();
void MenuMouseButtonHook();
