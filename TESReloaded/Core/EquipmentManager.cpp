#define FlameCapName "FlameCap"
#define FlameNode0Name "FlameNode0"
#define FlameNode1Name "FlameNode1"
#define FlameNode2Name "FlameNode2"
#define LightNodeName "AttachLight"

void EquipmentManager::Initialize() {

	Logger::Log("Starting the equipment manager...");
	TheEquipmentManager = new EquipmentManager();

	TheEquipmentManager->OnBackAnim = NULL;
	TheEquipmentManager->LeftTime = -1.0f;

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

void EquipmentManager::SetRotationPosition(NiAVObject* Object, PositionRotationType Type, UInt8 SitSleepState) {

	NiPoint3 RotationZero = { 0.0f, 0.0f, 0.0f };
	NiPoint3 PositionZero = { 0.0f, 0.0f, 0.0f };
    if(Object == nullptr) return;

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
    if(Torch == nullptr) return;
    /*The functions check for null Torch, but in certain conditions nullptr is passed, WHY? Maybe one of the functions between this and the if assign the pointer value?*/
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