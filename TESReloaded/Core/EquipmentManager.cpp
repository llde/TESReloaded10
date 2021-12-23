#if defined(OBLIVION)
#include "Animation.h"

#define ForearmTwistNodeName "Bip01 L ForearmTwist"
#define QuiverNodeName "Quiver"
#define TorchNodeName "Torch"
#define BeltNodeName "Bip01 Pelvis"
#define ScabbardNodeName "Scb"
#define FlameCapName "FlameCap"
#define FlameNode0Name "FlameNode0"
#define FlameNode1Name "FlameNode1"
#define FlameNode2Name "FlameNode2"
#define LightNodeName "AttachLight"

static const UInt32 kPrnHook = 0x0047927B;
static const UInt32 kPrnReturn = 0x0047928A;
static const UInt32 kMenuMouseButtonHook = 0x0058251B;
static const UInt32 kMenuMouseButtonReturn1 = 0x00582525;
static const UInt32 kMenuMouseButtonReturn2 = 0x0058264F;
static const UInt32 kUnequipTorchHook = 0x0048A7AD;
static const UInt32 kUnequipTorchReturn = 0x0048A7B5;
static const UInt32 kEquipItemWornHook = 0x00489E0A;
static const UInt32 kEquipItemWornReturn = 0x00489E13;
static const UInt32 kSetWeaponRotationPositionHook = 0x006563F3;
static const UInt32 kSetWeaponRotationPositionReturn = 0x006563FC;
#endif

EquipmentManager::EquipmentManager() {

	Logger::Log("Starting the equipment manager...");
	TheEquipmentManager = this;

	OnBackAnim = NULL;
	LeftTime = -1.0f;

}

void EquipmentManager::LoadForms() {

	if (TheSettingManager->SettingsMain.EquipmentMode.Enabled) {
		OnBackAnim = (TESIdleForm*)DataHandler->CreateForm(TESForm::FormType::kFormType_Idle);
		OnBackAnim->GenerateID(0x22F);
		OnBackAnim->flags = 0;
		OnBackAnim->SetFile("Characters\\_Male\\IdleAnims\\oronbackanim.kf");
		OnBackAnim->animFlags = TESIdleForm::AnimFlag::kAnimFlag_SpecialIdle;
		DataHandler->AddData(OnBackAnim);
	}

}

#if defined(OBLIVION)
void EquipmentManager::SetRotationPosition(NiAVObject* Object, PositionRotationType Type, UInt8 SitSleepState) {

	NiPoint3 RotationZero = { 0.0f, 0.0f, 0.0f };
	NiPoint3 PositionZero = { 0.0f, 0.0f, 0.0f };

	NiMatrix33* m = &Object->m_localTransform.rot;
	NiPoint3* v = &Object->m_localTransform.pos;
	NiPoint3* Rotation = NULL;
	NiPoint3* Position = NULL;

	switch (Type) {
		case EquipmentManager::None:
			Rotation = &RotationZero;
			Position = &PositionZero;
			break;
		case EquipmentManager::Shield:
			Rotation = &TheSettingManager->SettingsMain.EquipmentMode.ShieldOnBackRot;
			Position = &TheSettingManager->SettingsMain.EquipmentMode.ShieldOnBackPos;
			break;
		case EquipmentManager::Weapon:
			if (SitSleepState < 3 || SitSleepState > 5) {
				Rotation = &TheSettingManager->SettingsMain.EquipmentMode.WeaponOnBackRot;
				Position = &TheSettingManager->SettingsMain.EquipmentMode.WeaponOnBackPos;
			}
			else {
				Rotation = &TheSettingManager->SettingsMain.MountedCombat.WeaponOnBackRot;
				Position = &TheSettingManager->SettingsMain.MountedCombat.WeaponOnBackPos;
			}
			break;
		case EquipmentManager::TwoHandWeapon:
			if (SitSleepState < 3 || SitSleepState > 5) {
				Rotation = &TheSettingManager->SettingsMain.EquipmentMode.TwoHandWeaponOnBackRot;
				Position = &TheSettingManager->SettingsMain.EquipmentMode.TwoHandWeaponOnBackPos;
			}
			else {
				Rotation = &TheSettingManager->SettingsMain.MountedCombat.TwoHandWeaponOnBackRot;
				Position = &TheSettingManager->SettingsMain.MountedCombat.TwoHandWeaponOnBackPos;
			}
			break;
		case EquipmentManager::Staff:
			if (SitSleepState < 3 || SitSleepState > 5) {
				Rotation = &TheSettingManager->SettingsMain.EquipmentMode.StaffOnBackRot;
				Position = &TheSettingManager->SettingsMain.EquipmentMode.StaffOnBackPos;
			}
			else {
				Rotation = &TheSettingManager->SettingsMain.MountedCombat.StaffOnBackRot;
				Position = &TheSettingManager->SettingsMain.MountedCombat.StaffOnBackPos;
			}
			break;
		case EquipmentManager::Bow:
			if (SitSleepState < 3 || SitSleepState > 5) {
				Rotation = &TheSettingManager->SettingsMain.EquipmentMode.BowOnBackRot;
				Position = &TheSettingManager->SettingsMain.EquipmentMode.BowOnBackPos;
			}
			else {
				Rotation = &TheSettingManager->SettingsMain.MountedCombat.BowOnBackRot;
				Position = &TheSettingManager->SettingsMain.MountedCombat.BowOnBackPos;
			}
			break;
		case EquipmentManager::Light:
			Rotation = &TheSettingManager->SettingsMain.EquipmentMode.TorchOnBeltRot;
			Position = &TheSettingManager->SettingsMain.EquipmentMode.TorchOnBeltPos;
			break;
	}
	m->GenerateRotationMatrixZXY(Rotation, 1);
	v->x = Position->x;
	v->y = Position->y;
	v->z = Position->z;

}

void EquipmentManager::SetTorchLight(Actor* Act, NiAVObject* Torch, UInt8 Enable) {

	NiAVObject* FlameCap = Torch->GetObjectByName(FlameCapName);
	NiAVObject* FlameNode0 = Torch->GetObjectByName(FlameNode0Name);
	NiAVObject* FlameNode1 = Torch->GetObjectByName(FlameNode1Name);
	NiAVObject* FlameNode2 = Torch->GetObjectByName(FlameNode2Name);
	NiNode* AttachLight = (NiNode*)Torch->GetObjectByName(LightNodeName);
	
	if (Enable) {
		if (FlameCap) FlameCap->m_flags &= ~NiAVObject::kFlag_AppCulled;
		if (FlameNode0) FlameNode0->m_flags &= ~NiAVObject::kFlag_AppCulled;
		if (FlameNode1) FlameNode1->m_flags &= ~NiAVObject::kFlag_AppCulled;
		if (FlameNode2) FlameNode2->m_flags &= ~NiAVObject::kFlag_AppCulled;
		if (AttachLight) {
			NiPointLight* Light = (NiPointLight*)AttachLight->m_children.data[0];
			Light->m_flags &= ~NiAVObject::kFlag_AppCulled;
		}
		((HighProcess*)Act->process)->PlaySoundITMTorchHeldLP(Act);
	}
	else {
		if (FlameCap) FlameCap->m_flags |= NiAVObject::kFlag_AppCulled;
		if (FlameNode0) FlameNode0->m_flags |= NiAVObject::kFlag_AppCulled;
		if (FlameNode1) FlameNode1->m_flags |= NiAVObject::kFlag_AppCulled;
		if (FlameNode2) FlameNode2->m_flags |= NiAVObject::kFlag_AppCulled;
		if (AttachLight) {
			NiPointLight* Light = (NiPointLight*)AttachLight->m_children.data[0];
			Light->m_flags |= NiAVObject::kFlag_AppCulled;
		}
		((HighProcess*)Act->process)->StopSoundITMTorchHeldLP();
	}
}

void EquipmentManager::SetAnimations(HighProcess* Process, UInt8 LeftWeapon) {

	if (LeftWeapon) {
		SetAnimGroup(Process, 0, 2, "Characters\\_Male\\OnehandIdle_OR_dual.kf");
		SetAnimGroup(Process, 3, 2, "Characters\\_Male\\OnehandForward_OR_dual.kf");
		SetAnimGroup(Process, 4, 2, "Characters\\_Male\\OnehandBackward_OR_dual.kf");
		SetAnimGroup(Process, 5, 2, "Characters\\_Male\\OnehandLeft_OR_dual.kf");
		SetAnimGroup(Process, 6, 2, "Characters\\_Male\\OnehandRight_OR_dual.kf");
		SetAnimGroup(Process, 7, 2, "Characters\\_Male\\OnehandFastForward_OR_dual.kf");
		SetAnimGroup(Process, 8, 2, "Characters\\_Male\\OnehandFastBackward_OR_dual.kf");
		SetAnimGroup(Process, 9, 2, "Characters\\_Male\\OnehandFastLeft_OR_dual.kf");
		SetAnimGroup(Process, 10, 2, "Characters\\_Male\\OnehandFastRight_OR_dual.kf");
		SetAnimGroup(Process, 15, 2, "Characters\\_Male\\OnehandTurnLeft_OR_dual.kf");
		SetAnimGroup(Process, 16, 2, "Characters\\_Male\\OnehandTurnRight_OR_dual.kf");
		SetAnimGroup(Process, 20, 2, "Characters\\_Male\\OnehandAttackLeft_OR_dual.kf");
		if (Process->SitSleepState < 3 || Process->SitSleepState > 5)
			SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_dual.kf");
		else
			SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_mounted.kf");
		SetAnimGroup(Process, 27, 2, "Characters\\_Male\\OnehandBlockIdle_OR_dual.kf");
		SetAnimGroup(Process, 28, 2, "Characters\\_Male\\OnehandBlockHit_OR_dual.kf");
	}
	else {
		ResetAnimGroup(Process, 0, 2);
		ResetAnimGroup(Process, 3, 2);
		ResetAnimGroup(Process, 4, 2);
		ResetAnimGroup(Process, 5, 2);
		ResetAnimGroup(Process, 6, 2);
		ResetAnimGroup(Process, 7, 2);
		ResetAnimGroup(Process, 8, 2);
		ResetAnimGroup(Process, 9, 2);
		ResetAnimGroup(Process, 10, 2);
		ResetAnimGroup(Process, 15, 2);
		ResetAnimGroup(Process, 16, 2);
		ResetAnimGroup(Process, 20, 2);
		ResetAnimGroup(Process, 21, 2);
		ResetAnimGroup(Process, 27, 2);
		ResetAnimGroup(Process, 28, 2);
	}
}

void EquipmentManager::SetAnimGroup(HighProcess* Process, UInt8 AnimGroup, UInt8 AnimType, const char* Filename) {

	BSAnimGroupSequence* AnimGroupSequence = NULL;
	ActorAnimDataEx* AnimData = (ActorAnimDataEx*)Process->animData;
	AnimSequenceBase* AnimSequence = NULL;
	UInt16 AnimGroupKey = (AnimType << 8) | AnimGroup;

	if (AnimData->animsMap->GetAnimSequence(AnimGroupKey, &AnimSequence)) {
		NiTList<BSAnimGroupSequence>::Entry* Iter = AnimData->ORAnims->start;
		while (Iter) {
			AnimGroupSequence = Iter->data;
			if (!_stricmp(AnimGroupSequence->filePath, Filename)) break;
			Iter = Iter->next;
			AnimGroupSequence = NULL;
		}
		if (AnimSequence->IsSingle()) {
			AnimSequenceSingleEx* AnimSequenceS = (AnimSequenceSingleEx*)AnimSequence;
			AnimSequenceS->ORAnim = AnimGroupSequence;
		}
		else {
			AnimSequenceMultipleEx* AnimSequenceM = (AnimSequenceMultipleEx*)AnimSequence;
			AnimSequenceM->ORAnim = AnimGroupSequence;
		}
	}
}

void EquipmentManager::ResetAnimGroup(HighProcess* Process, UInt8 AnimGroup, UInt8 AnimType) {

	ActorAnimData* AnimData = Process->animData;
	AnimSequenceBase* AnimSequence = NULL;
	UInt16 AnimGroupKey = (AnimType << 8) | AnimGroup;

	if (AnimData->animsMap->GetAnimSequence(AnimGroupKey, &AnimSequence)) {
		if (AnimSequence->IsSingle()) {
			AnimSequenceSingleEx* AnimSequenceS = (AnimSequenceSingleEx*)AnimSequence;
			AnimSequenceS->ORAnim = NULL;
		}
		else {
			AnimSequenceMultipleEx* AnimSequenceM = (AnimSequenceMultipleEx*)AnimSequence;
			AnimSequenceM->ORAnim = NULL;
		}
	}
}

void AttachShieldToQuiver(Character* Act, HighProcessEx* Process, NiNode* ForearmTwistNode, NiNode* QuiverNode) {

	NiAVObject* Object = Act->ActorSkinInfo->ShieldObject;
	ForearmTwistNode->RemoveObject(&Object, Object);
	if (Object) {
		TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Shield, Process->SitSleepState);
		QuiverNode->AddObject(Object, 1);
		if (Act == Player) {
			Object = Player->firstPersonSkinInfo->ShieldObject;
			ForearmTwistNode = Player->firstPersonSkinInfo->LForearmTwistNode;
			QuiverNode = Player->firstPersonSkinInfo->QuiverNode;
			ForearmTwistNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Shield, Process->SitSleepState);
			QuiverNode->AddObject(Object, 1);
		}
	}

}

void AttachShieldToForearmTwist(Character* Act, HighProcessEx* Process, NiNode* ForearmTwistNode, NiNode* QuiverNode) {

	NiAVObject* Object = Act->ActorSkinInfo->ShieldObject;
	QuiverNode->RemoveObject(&Object, Object);
	if (Object) {
		TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
		ForearmTwistNode->AddObject(Object, 1);
		if (Act == Player) {
			Object = Player->firstPersonSkinInfo->ShieldObject;
			QuiverNode = Player->firstPersonSkinInfo->QuiverNode;
			ForearmTwistNode = Player->firstPersonSkinInfo->LForearmTwistNode;
			QuiverNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
			ForearmTwistNode->AddObject(Object, 1);
		}
	}

}

void AttachWeaponToQuiver(Character* Act, HighProcessEx* Process, NiNode* TorchNode, NiNode* QuiverNode) {

	NiAVObject* Object = Process->LeftWeaponObject;
	TorchNode->RemoveObject(&Object, Object);
	if (Object) {
		TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Weapon, Process->SitSleepState);
		QuiverNode->AddObject(Object, 1);
		if (Act == Player) {
			Object = Process->LeftWeaponObjectFirst;
			QuiverNode = Player->firstPersonSkinInfo->QuiverNode;
			TorchNode = Player->firstPersonSkinInfo->TorchNode;
			TorchNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Weapon, Process->SitSleepState);
			QuiverNode->AddObject(Object, 1);
		}
	}

}

void AttachWeaponToTorch(Character* Act, HighProcessEx* Process, NiNode* TorchNode, NiNode* QuiverNode) {

	NiAVObject* Object = Process->LeftWeaponObject;
	QuiverNode->RemoveObject(&Object, Object);
	if (Object) {
		TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
		TorchNode->AddObject(Object, 1);
		if (Act == Player) {
			Object = Process->LeftWeaponObjectFirst;
			QuiverNode = Player->firstPersonSkinInfo->QuiverNode;
			TorchNode = Player->firstPersonSkinInfo->TorchNode;
			QuiverNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
			TorchNode->AddObject(Object, 1);
		}
	}

}

class Equipment {
public:
	HighProcess*	TrackNewHighProcess();
	void			TrackManageItem(int, TileRect*);
	int				TrackProcessAction(float, float);
	void			TrackAttackHandling(UInt8, TESObjectREFR*, TESObjectREFR*);
	UInt8			TrackProcessControlAttack();
	InventoryChanges::EntryData* TrackGetEquippedWeaponData(UInt8);
	bool			TrackSetEquippedWeaponData(InventoryChanges::EntryData*, NiNode*);
	void			TrackEquipItem(TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
	void			TrackUnequipItem(UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
	void			TrackEquipWeapon(TESObjectWEAP*);
	void			TrackUnequipWeapon();
	void			TrackEquipShield(TESObjectARMO*);
	void			TrackEquipLight(TESObjectLIGH*);
	void			TrackUnequipLight();
	void			TrackHideEquipment(TESForm*, UInt8);
	InventoryChanges::EntryData* TrackGetEquippedLightData(UInt8);
	void			TrackSaveGame();
};

HighProcess* (__thiscall Equipment::* NewHighProcess)();
HighProcess* (__thiscall Equipment::* TrackNewHighProcess)();
HighProcess* Equipment::TrackNewHighProcess() {

	HighProcessEx* Process = (HighProcessEx*)(this->*NewHighProcess)();

	Process->EquippedLeftWeaponData = NULL;
	Process->LeftWeaponObject = NULL;
	Process->LeftWeaponObjectFirst = NULL;
	Process->OnProcessNew = HighProcessEx::State::StateNone;
	Process->OnBackActionState = HighProcessEx::State::StateNone;
	Process->OnBackState = HighProcessEx::State::In;
	Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
	Process->LeftEquippingState = HighProcessEx::State::StateNone;
	Process->LeftAnimState = HighProcessEx::State::StateNone;
	Process->OnBeltActionState = HighProcessEx::State::StateNone;
	Process->OnBeltState = HighProcessEx::State::StateNone;
	return Process;
	
}

void (__thiscall Equipment::* ManageItem)(int, TileRect*);
void (__thiscall Equipment::* TrackManageItem)(int, TileRect*);
void Equipment::TrackManageItem(int SelectedID, TileRect* SelectedRect) {
	
	HighProcessEx* Process = (HighProcessEx*)Player->process;

	if (SelectedRect) {
		if (!memcmp(SelectedRect->name.m_data, "inv_OREquipment_button", 22) && TheScriptManager->EquipmentSetup->ConfigStep == EquipmentSetupScript::StepType::None) TheScriptManager->EquipmentSetup->ConfigStep = EquipmentSetupScript::StepType::Request;
		if (TheKeyboardManager->OnMouseUp(1)) {
			float fIndex = 0.0f;
			if (SelectedRect->GetFloatValue(Tile::TileValue::kTileValue_user11, &fIndex)) {
				InventoryChanges::EntryData* InventoryData = Player->GetInventoryItem(fIndex);
				if (InventoryData->type->formType == TESForm::FormType::kFormType_Weapon) {
					TESObjectWEAP* Weapon = (TESObjectWEAP*)InventoryData->type;
					if ((Weapon->weaponType == TESObjectWEAP::kWeapType_BladeOneHand || Weapon->weaponType == TESObjectWEAP::kWeapType_BluntOneHand) && !(Weapon->flags & 0x400) && !Weapon->scriptable.script) Process->LeftEquippingState = HighProcessEx::State::In;
				}
			}
		}
	}
	(this->*ManageItem)(SelectedID, SelectedRect);
	Process->LeftEquippingState = HighProcessEx::State::StateNone;
	
}

int (__thiscall Equipment::* ProcessAction)(float, float);
int (__thiscall Equipment::* TrackProcessAction)(float, float);
int Equipment::TrackProcessAction(float Arg1, float Arg2) {

	Character* Act = (Character*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0 && Act->formType == TESForm::FormType::kFormType_ACHR) {
		InventoryChanges::EntryData* WeaponData = Process->equippedWeaponData;
		InventoryChanges::EntryData* ShieldData = Process->equippedShieldData;
		InventoryChanges::EntryData* LightData = Process->equippedLightData;
		InventoryChanges::EntryData* LeftWeaponData = Process->EquippedLeftWeaponData;
		if (Process->OnProcessNew == HighProcessEx::State::StateNone) { // The HighProcess could arrive from a MiddleHighProcess so equipment is already on
			if (WeaponData && ShieldData && !Process->WeaponState) {
				NiNode* ForearmTwistNode = Act->ActorSkinInfo->LForearmTwistNode;
				NiNode* QuiverNode = Act->ActorSkinInfo->QuiverNode;
				AttachShieldToQuiver(Act, Process, ForearmTwistNode, QuiverNode);
			}
			Process->OnProcessNew = HighProcessEx::State::In;
		}
		if (WeaponData && (ShieldData || LeftWeaponData) && (!LightData || (LightData && Process->OnBeltState == HighProcessEx::State::In))) {
			TESObjectWEAP* Weapon = (TESObjectWEAP*)WeaponData->type;
			if (Weapon->weaponType == TESObjectWEAP::kWeapType_BladeOneHand || Weapon->weaponType == TESObjectWEAP::kWeapType_BluntOneHand) {
				switch (Process->currentAction) {
					case HighProcess::kAnimAction_None:
						if (Process->OnBackActionState == HighProcessEx::State::StateNone) {
							if (Process->WeaponState && Process->OnBackState == HighProcessEx::State::In)
								Process->OnBackActionState = HighProcessEx::State::Out;
							else if (!Process->WeaponState && Process->OnBackState == HighProcessEx::State::Out)
								Process->OnBackActionState = HighProcessEx::State::In;
						}
						if (Process->OnBackActionState == HighProcessEx::State::In || Process->OnBackActionState == HighProcessEx::State::Out) Process->animData->QueueIdle(TheEquipmentManager->OnBackAnim, Act, TheEquipmentManager->OnBackAnim->animFlags);
						break;
					case HighProcess::kAnimAction_SpecialIdle:
						if (Process->OnBackActionState == HighProcessEx::State::In || Process->OnBackActionState == HighProcessEx::State::Out) {
							BSAnimGroupSequence* AnimSequence = Process->animData->animSequences[4];
							if (AnimSequence && !memcmp(AnimSequence->filePath, "Meshes\\Characters\\_Male\\IdleAnims\\oronbackanim.kf", 49) && AnimSequence->last >= 0.4) {
								NiNode* ForearmTwistNode = Act->ActorSkinInfo->LForearmTwistNode;
								NiNode* QuiverNode = Act->ActorSkinInfo->QuiverNode;
								NiNode* TorchNode = Act->ActorSkinInfo->TorchNode;
								NiAVObject* Object = NULL;
								if (Process->OnBackActionState == HighProcessEx::State::In) {
									if (LeftWeaponData)
										AttachWeaponToQuiver(Act, Process, TorchNode, QuiverNode);
									else
										AttachShieldToQuiver(Act, Process, ForearmTwistNode, QuiverNode);
									Process->OnBackState = HighProcessEx::State::In;
								}
								else {
									if (LeftWeaponData)
										AttachWeaponToTorch(Act, Process, TorchNode, QuiverNode);
									else
										AttachShieldToForearmTwist(Act, Process, ForearmTwistNode, QuiverNode);
									Process->OnBackState = HighProcessEx::State::Out;
								}
								Process->OnBackActionState = HighProcessEx::State::StateNone;
							}
						}
						break;
					default:
						break;
				}
			}
		}
		if (Act == Player && LightData && Process->OnBackState == HighProcessEx::State::In && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.EquipmentMode.TorchKey)) {
			NiNode* BeltNode = (NiNode*)Act->niNode->GetObjectByName(BeltNodeName);
			NiNode* TorchNode = Act->ActorSkinInfo->TorchNode;
			NiAVObject* Object = NULL;
			if (Process->OnBeltState == HighProcessEx::State::In) {
				Object = Act->ActorSkinInfo->LightObject;
				BeltNode->RemoveObject(&Object, Object);
				if (Object) {
					TheEquipmentManager->SetTorchLight(Act, Object, 1);
					TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
					TorchNode->AddObject(Object, 1);
					if (Act == Player) {
						Object = Player->firstPersonSkinInfo->LightObject;
						BeltNode = (NiNode*)Player->firstPersonNiNode->GetObjectByName(BeltNodeName);
						TorchNode = Player->firstPersonSkinInfo->TorchNode;
						BeltNode->RemoveObject(&Object, Object);
						TheEquipmentManager->SetTorchLight(Act, Object, 1);
						TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
						TorchNode->AddObject(Object, 1);
					}
				}
				Process->OnBeltState = HighProcessEx::State::Out;
			}
			else {
				Object = Act->ActorSkinInfo->LightObject;
				TorchNode->RemoveObject(&Object, Object);
				if (Object) {
					TheEquipmentManager->SetTorchLight(Act, Object, 0);
					TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Light, Process->SitSleepState);
					BeltNode->AddObject(Object, 1);
					if (Act == Player) {
						Object = Player->firstPersonSkinInfo->LightObject;
						BeltNode = (NiNode*)Player->firstPersonNiNode->GetObjectByName(BeltNodeName);
						TorchNode = Player->firstPersonSkinInfo->TorchNode;
						TorchNode->RemoveObject(&Object, Object);
						TheEquipmentManager->SetTorchLight(Act, Object, 0);
						TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Light, Process->SitSleepState);
						BeltNode->AddObject(Object, 1);
					}
				}
				Process->OnBeltState = HighProcessEx::State::In;
			}
		}
	}
	return (this->*ProcessAction)(Arg1, Arg2);

}

UInt8 (__thiscall Equipment::* ProcessControlAttack)();
UInt8 (__thiscall Equipment::* TrackProcessControlAttack)();
UInt8 Equipment::TrackProcessControlAttack() {
	
	HighProcessEx* Process = (HighProcessEx*)Player->process;
	InventoryChanges::EntryData* LeftWeaponData = Process->EquippedLeftWeaponData;
	
	if (LeftWeaponData) {
		if (TheKeyboardManager->OnControlDown(6)) {
			if (TheEquipmentManager->LeftTime == -1.0f)
				TheEquipmentManager->LeftTime = 0.0f;
			else
				TheEquipmentManager->LeftTime += TheFrameRateManager->ElapsedTime;
			if (TheEquipmentManager->LeftTime < TheSettingManager->SettingsMain.EquipmentMode.DualBlockDelay) TheKeyboardManager->SetControlState(6, 0, 0);
		}
		else if (TheEquipmentManager->LeftTime >= 0.0f) {
			if (TheEquipmentManager->LeftTime < TheSettingManager->SettingsMain.EquipmentMode.DualBlockDelay) {
				TheEquipmentManager->SetAnimGroup(Process, 20, 2, "Characters\\_Male\\OnehandAttackLeft_OR_dual_left.kf");
				TheEquipmentManager->SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_dual_left.kf");
				Process->LeftAnimState = HighProcessEx::State::In;
				TheKeyboardManager->SetControlState(4, 0x80, 0);
			}
			TheEquipmentManager->LeftTime = -1.0f;
		}
	}
	return (this->*ProcessControlAttack)();

}

void (__thiscall Equipment::* AttackHandling)(UInt8, TESObjectREFR*, TESObjectREFR*);
void (__thiscall Equipment::* TrackAttackHandling)(UInt8, TESObjectREFR*, TESObjectREFR*);
void Equipment::TrackAttackHandling(UInt8 Arg1, TESObjectREFR* Arrow, TESObjectREFR* Target) {
	
	Actor* Act = (Actor*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;
	InventoryChanges::EntryData* LeftWeaponData = Process->EquippedLeftWeaponData;

	(this->*AttackHandling)(Arg1, Arrow, Target);
	if (Act == Player && Process->LeftAnimState == HighProcessEx::State::In) {
		TheEquipmentManager->SetAnimGroup(Process, 20, 2, "Characters\\_Male\\OnehandAttackLeft_OR_dual.kf");
		if (Process->SitSleepState < 3 || Process->SitSleepState > 5)
			TheEquipmentManager->SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_dual.kf");
		else
			TheEquipmentManager->SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_mounted.kf");
		Process->LeftAnimState = HighProcessEx::State::StateNone;
	}

}

InventoryChanges::EntryData* (__thiscall Equipment::* GetEquippedWeaponData)(UInt8);
InventoryChanges::EntryData* (__thiscall Equipment::* TrackGetEquippedWeaponData)(UInt8);
InventoryChanges::EntryData* Equipment::TrackGetEquippedWeaponData(UInt8 Arg1) {
	
	HighProcessEx* Process = (HighProcessEx*)this;

	if (Process->GetProcessLevel() == 0 && (Process->LeftEquippingState || Process->LeftAnimState)) return Process->EquippedLeftWeaponData;
	return (this->*GetEquippedWeaponData)(Arg1);

}

bool (__thiscall Equipment::* SetEquippedWeaponData)(InventoryChanges::EntryData*, NiNode*);
bool (__thiscall Equipment::* TrackSetEquippedWeaponData)(InventoryChanges::EntryData*, NiNode*);
bool Equipment::TrackSetEquippedWeaponData(InventoryChanges::EntryData* InventoryData, NiNode* ActorNode) {
	
	HighProcessEx* Process = (HighProcessEx*)this;
	
	if (Process->GetProcessLevel() == 0 && Process->LeftEquippingState) {
		Process->EquippedLeftWeaponData = InventoryData;
		return 1;
	}
	return (this->*SetEquippedWeaponData)(InventoryData, ActorNode);

}

void (__thiscall Equipment::* EquipItem)(TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void (__thiscall Equipment::* TrackEquipItem)(TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void Equipment::TrackEquipItem(TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock) {
	
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0 && Process->LeftEquippingState) Left = 1;
	(this->*EquipItem)(Form, Quantity, Act, DataList, Left, Lock);

}

void (__thiscall Equipment::* UnequipItem)(UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void (__thiscall Equipment::* TrackUnequipItem)(UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8);
void Equipment::TrackUnequipItem(UInt8* Arg1, TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock) {
	
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0 && Form->formType == TESForm::FormType::kFormType_Weapon && Left) Process->LeftEquippingState = HighProcessEx::State::Out;
	(this->*UnequipItem)(Arg1, Form, Quantity, Act, DataList, Left, Lock);
	if (Process && Process->GetProcessLevel() == 0 && Form->formType == TESForm::FormType::kFormType_Weapon && Left) Process->LeftEquippingState = HighProcessEx::State::StateNone;

}

void (__thiscall Equipment::* EquipWeapon)(TESObjectWEAP*);
void (__thiscall Equipment::* TrackEquipWeapon)(TESObjectWEAP*);
void Equipment::TrackEquipWeapon(TESObjectWEAP* Weapon) {

	Actor* Act = (Actor*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;
	
	if (Process && Process->GetProcessLevel() == 0) {
		if (Process->LeftEquippingState) {
			NiNode* (__cdecl * LoadNiFile)(const char*, UInt32, Actor*, NiNode*) = (NiNode*(__cdecl *)(const char*, UInt32, Actor*, NiNode*))0x00479450;
			Process->EquippingType = HighProcessEx::ObjectType::Weapon;
			if (Process->WeaponState)
				Process->OnBackState = HighProcessEx::State::Out;
			else
				Process->OnBackState = HighProcessEx::State::In;
			NiNode* ObjectNode = LoadNiFile(Weapon->model.nifPath.m_data, 9, Act, Act->niNode);
			ObjectNode->SetName("LeftWeapon");
			Process->LeftWeaponObject = ObjectNode;
			if (Act == Player) {
				ObjectNode = LoadNiFile(Weapon->model.nifPath.m_data, 9, Player, Player->firstPersonNiNode);
				ObjectNode->SetName("LeftWeapon");
				Process->LeftWeaponObjectFirst = ObjectNode;
			}
			Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
			TheEquipmentManager->SetAnimations(Process, 1);
		}
		else {
			Process->EquippingType = HighProcessEx::ObjectType::Weapon;
			(this->*EquipWeapon)(Weapon);
			Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
		}
	}
	else 
		(this->*EquipWeapon)(Weapon);

}

void (__thiscall Equipment::* UnequipWeapon)();
void (__thiscall Equipment::* TrackUnequipWeapon)();
void Equipment::TrackUnequipWeapon() {

	Actor* Act = (Actor*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;
	
	if (Process && Process->GetProcessLevel() == 0 && Process->LeftEquippingState) {
		const char* WeaponModelPath = ((TESObjectWEAP*)Process->EquippedLeftWeaponData->type)->model.nifPath.m_data;
		NiAVObject* Object = Process->LeftWeaponObject;
		NiNode* ParentNode = (NiNode*)Object->m_parent;
		ParentNode->RemoveObject(&Object, Object);
		Object->Destructor(1);
		ModelLoader->RemoveModel(WeaponModelPath);
		Process->LeftWeaponObject = NULL;
		if (Act == Player) {
			Object = Process->LeftWeaponObjectFirst;
			ParentNode = (NiNode*)Object->m_parent;
			ParentNode->RemoveObject(&Object, Object);
			Object->Destructor(1);
			ModelLoader->RemoveModel(WeaponModelPath);
			Process->LeftWeaponObjectFirst = NULL;
		}
		TheEquipmentManager->SetAnimations(Process, 0);
		if (Process->equippedShieldData && Process->WeaponState) Process->OnBackActionState = HighProcessEx::State::Out;
	}
	else (this->*UnequipWeapon)();

}

void (__thiscall Equipment::* EquipShield)(TESObjectARMO*);
void (__thiscall Equipment::* TrackEquipShield)(TESObjectARMO*);
void Equipment::TrackEquipShield(TESObjectARMO* Shield) {

	Actor* Act = (Actor*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0) {
		Process->EquippingType = HighProcessEx::ObjectType::Shield;
		if (Process->WeaponState)
			Process->OnBackState = HighProcessEx::State::Out;
		else
			Process->OnBackState = HighProcessEx::State::In;
	}
	(this->*EquipShield)(Shield);
	if (Process && Process->GetProcessLevel() == 0) Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;

}

void (__thiscall Equipment::* EquipLight)(TESObjectLIGH*);
void (__thiscall Equipment::* TrackEquipLight)(TESObjectLIGH*);
void Equipment::TrackEquipLight(TESObjectLIGH* Light) {

	Actor* Act = (Actor*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Act == Player && Process) {
		Process->EquippingType = HighProcessEx::ObjectType::Light;
		Process->OnBeltState = HighProcessEx::State::In;
	}
	(this->*EquipLight)(Light);
	if (Act == Player && Process) Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;

}

void (__thiscall Equipment::* UnequipLight)();
void (__thiscall Equipment::* TrackUnequipLight)();
void Equipment::TrackUnequipLight() {

	PlayerCharacter* Act = (PlayerCharacter*)this;
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Act == Player && Process && Process->OnBeltState == HighProcessEx::State::In && Act->niNode) {
		NiNode* BeltNode = (NiNode*)Act->niNode->GetObjectByName(BeltNodeName);
		NiNode* TorchNode = Act->ActorSkinInfo->TorchNode;
		NiAVObject* Object = Act->ActorSkinInfo->LightObject;
		if (Object) {
			BeltNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetTorchLight(Act, Object, 1);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
			TorchNode->AddObject(Object, 1);
			Object = Act->firstPersonSkinInfo->LightObject;
			BeltNode = (NiNode*)Act->firstPersonNiNode->GetObjectByName(BeltNodeName);
			TorchNode = Act->firstPersonSkinInfo->TorchNode;
			BeltNode->RemoveObject(&Object, Object);
			TheEquipmentManager->SetTorchLight(Act, Object, 1);
			TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
			TorchNode->AddObject(Object, 1);
		}
	}
	(this->*UnequipLight)();

}

void (__thiscall Equipment::* HideEquipment)(TESForm*, UInt8);
void (__thiscall Equipment::* TrackHideEquipment)(TESForm*, UInt8);
void Equipment::TrackHideEquipment(TESForm* Form, UInt8 Arg2) {

	Actor* Act = (Actor*)this;

	if (Act == Player) return;
	(this->*HideEquipment)(Form, Arg2);

}

InventoryChanges::EntryData* (__thiscall Equipment::* GetEquippedLightData)(UInt8);
InventoryChanges::EntryData* (__thiscall Equipment::* TrackGetEquippedLightData)(UInt8);
InventoryChanges::EntryData* Equipment::TrackGetEquippedLightData(UInt8 Arg1) {

	HighProcessEx* Process = (HighProcessEx*)this;
	
	if (Process == Player->process && Process->OnBeltState == HighProcessEx::State::In) return NULL;
	return (this->*GetEquippedLightData)(Arg1);

}

void (__thiscall Equipment::* SaveGame)();
void (__thiscall Equipment::* TrackSaveGame)();
void Equipment::TrackSaveGame() {

	InventoryChanges::EntryData* EntryData = (InventoryChanges::EntryData*)this;
	ExtraDataList* DataList = NULL;

	if (EntryData->type->formType == TESForm::FormType::kFormType_Weapon && EntryData->extendData) {
		for (TList<ExtraDataList>::Iterator Itr = EntryData->extendData->Begin(); !Itr.End(); ++Itr) {
			DataList = Itr.Get();
			if (DataList && DataList->IsWorn(1)) {
				DataList->SetWorn(0, 1);
				break;
			}
			DataList = NULL;
		}
	}
	(this->*SaveGame)();
	if (DataList) DataList->SetWorn(1, 1);

}

void UnequipTorch(Actor* Act) {

	HighProcessEx* Process = (HighProcessEx*)Act->process;
	
	if (Act == Player) Process->OnBeltState = HighProcessEx::State::Out;

}

static __declspec(naked) void UnequipTorchHook() {

	__asm {
		pushad
		push	ebp
		call	UnequipTorch
		add		esp, 4
		popad
		mov     edx, [ecx]
		mov     eax, [edx + 0xF0]
		jmp		kUnequipTorchReturn
	}

}

static bool IsWorn = 0;
void EquipItemWorn(InventoryChanges::EntryData* EntryData, Actor* Act) {

	HighProcessEx* Process = (HighProcessEx*)Act->process;
	bool Left = 0;

	if (Process && Process->GetProcessLevel() == 0 && EntryData->type->formType == TESForm::FormType::kFormType_Weapon && Process->LeftEquippingState) Left = 1;		
	IsWorn = EntryData->IsWorn(Left);

}

static __declspec(naked) void EquipItemWornHook() {

	__asm {
		pushad
		mov		ecx, dword ptr[esp + 0x58]
		push	ecx
		mov		ecx, edi
		push	ecx
		call	EquipItemWorn
		add		esp, 8
		popad
		mov		al, IsWorn
		jmp		kEquipItemWornReturn
	}

}

void Prn(NiNode* ActorNode, NiNode* AttachToNode, NiNode* ObjectNode, SkinInfo* Info, int SkinInfoSlot) {

	Character* Act = NULL;
	HighProcessEx* Process = NULL;

	if (SkinInfoSlot == 13) {
		Act = (Character*)Info->Actor150;
		if (Act->formType == TESForm::FormType::kFormType_ACHR && Act->process->GetProcessLevel() == 0) {
			Process = (HighProcessEx*)Act->process;
			Process->EquippingType = HighProcessEx::ObjectType::Shield;
		}
	}
	else if (!Info) {
		if (!memcmp(ActorNode->m_pcName, "Player1stPerson", 15)) {
			Act = Player;
			Info = Player->firstPersonSkinInfo;
			Process = (HighProcessEx*)Act->process;
		}
		else {
			Act = (Character*)ActorNode->GetRef();
			if (Act->formType == TESForm::FormType::kFormType_ACHR && Act->process->GetProcessLevel() == 0) {
				Info = Act->ActorSkinInfo;
				Process = (HighProcessEx*)Act->process;
			}
		}
	}
	if (Process && Process->EquippingType) {
		NiNode* ForearmTwistNode = (NiNode*)ActorNode->GetObjectByName(ForearmTwistNodeName);
		NiNode* TorchNode = (NiNode*)ActorNode->GetObjectByName(TorchNodeName);
		NiNode* QuiverNode = (NiNode*)ActorNode->GetObjectByName(QuiverNodeName);
		NiNode* BeltNode = (NiNode*)ActorNode->GetObjectByName(BeltNodeName);
		NiAVObject* Scabbard = ObjectNode->GetObjectByName(ScabbardNodeName);
		NiAVObject* Object = NULL;
		if (Process->EquippingType == HighProcessEx::ObjectType::Weapon) {
			if (Process->LeftEquippingState) {
				if (Scabbard) {
					ObjectNode->RemoveObject(&Scabbard, Scabbard);
					Scabbard->Destructor(1);
				}
				if (!Process->WeaponState) {
					TheEquipmentManager->SetRotationPosition(ObjectNode, EquipmentManager::PositionRotationType::Weapon, Process->SitSleepState);
					QuiverNode->AddObject(ObjectNode, 1);
				}
				else {
					if (Process->equippedShieldData) {
						Object = Info->ShieldObject;
						ForearmTwistNode->RemoveObject(&Object, Object);
						TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Shield, Process->SitSleepState);
						QuiverNode->AddObject(Object, 1);
					}
					TorchNode->AddObject(ObjectNode, 1);
				}
			}
			else
				AttachToNode->AddObject(ObjectNode, 1);
		}
		else if (Process->EquippingType == HighProcessEx::ObjectType::Shield) {
			if (!Process->WeaponState || Process->EquippedLeftWeaponData) {
				TheEquipmentManager->SetRotationPosition(ObjectNode, EquipmentManager::PositionRotationType::Shield, Process->SitSleepState);
				QuiverNode->AddObject(ObjectNode, 1);
			}
			else 
				AttachToNode->AddObject(ObjectNode, 1);
			if (SkinInfoSlot == 13) Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
		}
		else if (Process->EquippingType == HighProcessEx::ObjectType::Light) {
			TheEquipmentManager->SetTorchLight(Act, ObjectNode, 0);
			TheEquipmentManager->SetRotationPosition(ObjectNode, EquipmentManager::PositionRotationType::Light, Process->SitSleepState);
			BeltNode->AddObject(ObjectNode, 1);
		}
	}
	else
		AttachToNode->AddObject(ObjectNode, 1);

}

static __declspec(naked) void PrnHook() {

	__asm {
		pushad
		mov		ecx, dword ptr[esp + 0x34]
		mov		eax, dword ptr[esp + 0x40]
		mov		ebx, dword ptr[esp + 0x44]
		push	ebx
		push	eax
		push	ebp
		push	esi
		push	ecx
		call	Prn
		add		esp, 0x14
		popad
		jmp		kPrnReturn
	}

}

void SetWeaponRotationPosition(HighProcess* Process, NiNode* ObjectNode) {
	
	if (Process->GetProcessLevel() == 0 && !Process->WeaponState) {
		TESObjectWEAP* Weapon = (TESObjectWEAP*)Process->equippedWeaponData->type;
		EquipmentManager::PositionRotationType Type = EquipmentManager::PositionRotationType::None;
		if (Weapon->weaponType == TESObjectWEAP::kWeapType_BladeTwoHand || Weapon->weaponType == TESObjectWEAP::kWeapType_BluntTwoHand)
			Type = EquipmentManager::PositionRotationType::TwoHandWeapon;
		else if (Weapon->weaponType == TESObjectWEAP::kWeapType_Staff)
			Type = EquipmentManager::PositionRotationType::Staff;
		else if (Weapon->weaponType == TESObjectWEAP::kWeapType_Bow)
			Type = EquipmentManager::PositionRotationType::Bow;
		TheEquipmentManager->SetRotationPosition(ObjectNode, Type, Process->SitSleepState);
	}

}

static __declspec(naked) void SetWeaponRotationPositionHook() {

	__asm {
		mov		[ebx + 0x54], edx
		mov		[ebx + 0x58], eax
		mov		[ebx + 0x5C], ecx
		pushad
		push	ebx
		push	ebp
		call	SetWeaponRotationPosition
		add		esp, 8
		popad
		jmp		kSetWeaponRotationPositionReturn
	}

}

int MouseMenuButton(MenuInterfaceManager* Im, UInt8 Button1State) {
	
	if (Button1State || (Im->activeMenu && Im->activeMenu->id == Menu::MenuType::kMenuType_Inventory && TheKeyboardManager->OnMouseUp(1))) return 1;
	return 0;

}

static __declspec(naked) void MenuMouseButtonHook() {

	__asm {
		pushad
		mov		eax, [esp + 0x68]
		push	eax
		push	esi
		call	MouseMenuButton
		add		esp, 8
		cmp		eax, 0
		jz		short loc_notpressed
		popad
		jmp		kMenuMouseButtonReturn1

	loc_notpressed:
		popad
		jmp		kMenuMouseButtonReturn2
	}

}

void CreateEquipmentHook() {

	*((int *)&NewHighProcess)			= 0x00628EE0;
	TrackNewHighProcess					= &Equipment::TrackNewHighProcess;
	*((int *)&ManageItem)				= 0x005ABBC0;
	TrackManageItem						= &Equipment::TrackManageItem;
	*((int *)&ProcessAction)			= 0x005FCAB0;
	TrackProcessAction					= &Equipment::TrackProcessAction;
	*((int *)&ProcessControlAttack)		= 0x0065E960;
	TrackProcessControlAttack			= &Equipment::TrackProcessControlAttack;
	*((int *)&AttackHandling)			= 0x005FEBF0;
	TrackAttackHandling					= &Equipment::TrackAttackHandling;
	*((int *)&GetEquippedWeaponData)	= 0x0064B240;
	TrackGetEquippedWeaponData			= &Equipment::TrackGetEquippedWeaponData;
	*((int *)&SetEquippedWeaponData)	= 0x00658550;
	TrackSetEquippedWeaponData			= &Equipment::TrackSetEquippedWeaponData;
	*((int *)&EquipItem)				= 0x00489C30;
	TrackEquipItem						= &Equipment::TrackEquipItem;
	*((int *)&UnequipItem)				= 0x0048A540;
	TrackUnequipItem					= &Equipment::TrackUnequipItem;
	*((int *)&EquipWeapon)				= 0x004E1900;
	TrackEquipWeapon					= &Equipment::TrackEquipWeapon;
	*((int *)&UnequipWeapon)			= 0x004DC5B0;
	TrackUnequipWeapon					= &Equipment::TrackUnequipWeapon;
	*((int *)&EquipShield)				= 0x004E1B40;
	TrackEquipShield					= &Equipment::TrackEquipShield;
	*((int *)&EquipLight)				= 0x004E1C70;
	TrackEquipLight						= &Equipment::TrackEquipLight;
	*((int *)&UnequipLight)				= 0x004DCAB0;
	TrackUnequipLight					= &Equipment::TrackUnequipLight;
	*((int *)&GetEquippedLightData)		= 0x0064B270;
	TrackGetEquippedLightData			= &Equipment::TrackGetEquippedLightData;
	*((int *)&HideEquipment)			= 0x005E7230;
	TrackHideEquipment					= &Equipment::TrackHideEquipment;
	*((int *)&SaveGame)					= 0x00485730;
	TrackSaveGame						= &Equipment::TrackSaveGame;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)NewHighProcess,			*((PVOID*)&TrackNewHighProcess));
	DetourAttach(&(PVOID&)ManageItem,				*((PVOID*)&TrackManageItem));
	DetourAttach(&(PVOID&)ProcessAction,			*((PVOID*)&TrackProcessAction));
	DetourAttach(&(PVOID&)ProcessControlAttack,		*((PVOID*)&TrackProcessControlAttack));
	DetourAttach(&(PVOID&)AttackHandling,			*((PVOID*)&TrackAttackHandling));
	DetourAttach(&(PVOID&)GetEquippedWeaponData,	*((PVOID*)&TrackGetEquippedWeaponData));
	DetourAttach(&(PVOID&)SetEquippedWeaponData,	*((PVOID*)&TrackSetEquippedWeaponData));
	DetourAttach(&(PVOID&)EquipItem,				*((PVOID*)&TrackEquipItem));
	DetourAttach(&(PVOID&)UnequipItem,				*((PVOID*)&TrackUnequipItem));
	DetourAttach(&(PVOID&)EquipWeapon,				*((PVOID*)&TrackEquipWeapon));
	DetourAttach(&(PVOID&)UnequipWeapon,			*((PVOID*)&TrackUnequipWeapon));
	DetourAttach(&(PVOID&)EquipShield,				*((PVOID*)&TrackEquipShield));
	if (TheSettingManager->SettingsMain.EquipmentMode.TorchKey != 255) {
		DetourAttach(&(PVOID&)EquipLight,			*((PVOID*)&TrackEquipLight));
		DetourAttach(&(PVOID&)UnequipLight,			*((PVOID*)&TrackUnequipLight));
		DetourAttach(&(PVOID&)GetEquippedLightData, *((PVOID*)&TrackGetEquippedLightData));
	}
	DetourAttach(&(PVOID&)HideEquipment,			*((PVOID*)&TrackHideEquipment));
	DetourAttach(&(PVOID&)SaveGame,					*((PVOID*)&TrackSaveGame));
	DetourTransactionCommit();

	UInt32 HighProcessExSize = sizeof(HighProcessEx);
	SafeWrite32(0x005FA47C, HighProcessExSize);
	SafeWrite32(0x00607582, HighProcessExSize);
	SafeWrite32(0x0060791A, HighProcessExSize);
	SafeWrite32(0x0060CC36, HighProcessExSize);
	SafeWrite32(0x00659A9C, HighProcessExSize);
	SafeWrite32(0x00659D3D, HighProcessExSize);
	SafeWrite32(0x00664B09, HighProcessExSize);
	SafeWrite32(0x0066A9AA, HighProcessExSize);
	SafeWrite32(0x0068336E, HighProcessExSize);
	SafeWrite32(0x0069F2F2, HighProcessExSize);
	SafeWrite32(0x0069F3D4, HighProcessExSize);

	SafeWriteJump(kPrnHook,							(UInt32)PrnHook);
	SafeWriteJump(kSetWeaponRotationPositionHook,	(UInt32)SetWeaponRotationPositionHook);
	SafeWriteJump(kMenuMouseButtonHook,				(UInt32)MenuMouseButtonHook);
	SafeWriteJump(kEquipItemWornHook,				(UInt32)EquipItemWornHook);
	if (TheSettingManager->SettingsMain.EquipmentMode.TorchKey != 255) {
		SafeWriteJump(0x004E1DA1, 0x004E1DAF); // Do not play the torch held LP sound on equipping light
		SafeWriteJump(kUnequipTorchHook, (UInt32)UnequipTorchHook);
	}

}
#endif