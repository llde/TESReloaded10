#pragma once
#define ForearmTwistNodeName "Bip01 L ForearmTwist"
#define QuiverNodeName "Quiver"
#define TorchNodeName "Torch"
#define BeltNodeName "Bip01 Pelvis"
#define ScabbardNodeName "Scb"

static void AttachShieldToQuiver(Character* Act, HighProcessEx* Process, NiNode* ForearmTwistNode, NiNode* QuiverNode) {

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

static void AttachShieldToForearmTwist(Character* Act, HighProcessEx* Process, NiNode* ForearmTwistNode, NiNode* QuiverNode) {

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

static void AttachWeaponToQuiver(Character* Act, HighProcessEx* Process, NiNode* TorchNode, NiNode* QuiverNode) {

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

static void AttachWeaponToTorch(Character* Act, HighProcessEx* Process, NiNode* TorchNode, NiNode* QuiverNode) {

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

static HighProcess* (__thiscall* NewHighProcess)(HighProcess*) = (HighProcess* (__thiscall*)(HighProcess*))Hooks::NewHighProcess;
static HighProcess* __fastcall NewHighProcessHook(HighProcess* This, UInt32 edx) {

	HighProcessEx* Process = (HighProcessEx*)(*NewHighProcess)(This);

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

static void (__thiscall* ManageItem)(InventoryMenu*, int, TileRect*) = (void (__thiscall*)(InventoryMenu*, int, TileRect*))Hooks::ManageItem;
static void __fastcall ManageItemHook(InventoryMenu* This, UInt32 edx, int SelectedID, TileRect* SelectedRect) {
	
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
	(*ManageItem)(This, SelectedID, SelectedRect);
	Process->LeftEquippingState = HighProcessEx::State::StateNone;
	
}

static int (__thiscall* ProcessAction)(Character*, float, float) = (int (__thiscall*)(Character*, float, float))Hooks::ProcessAction;
static int __fastcall ProcessActionHook(Character* This, UInt32 edx, float Arg1, float Arg2) {

	HighProcessEx* Process = (HighProcessEx*)This->process;

	if (Process && Process->GetProcessLevel() == 0 && This->formType == TESForm::FormType::kFormType_ACHR) {
		InventoryChanges::EntryData* WeaponData = Process->equippedWeaponData;
		InventoryChanges::EntryData* ShieldData = Process->equippedShieldData;
		InventoryChanges::EntryData* LightData = Process->equippedLightData;
		InventoryChanges::EntryData* LeftWeaponData = Process->EquippedLeftWeaponData;
		if (Process->OnProcessNew == HighProcessEx::State::StateNone) { // The HighProcess could arrive from a MiddleHighProcess so equipment is already on
			if (WeaponData && ShieldData && !Process->WeaponState) {
				NiNode* ForearmTwistNode = This->ActorSkinInfo->LForearmTwistNode;
				NiNode* QuiverNode = This->ActorSkinInfo->QuiverNode;
				AttachShieldToQuiver(This, Process, ForearmTwistNode, QuiverNode);
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
						if (Process->OnBackActionState == HighProcessEx::State::In || Process->OnBackActionState == HighProcessEx::State::Out) Process->animData->QueueIdle(TheEquipmentManager->OnBackAnim, This, TheEquipmentManager->OnBackAnim->animFlags);
						break;
					case HighProcess::kAnimAction_SpecialIdle:
						if (Process->OnBackActionState == HighProcessEx::State::In || Process->OnBackActionState == HighProcessEx::State::Out) {
							BSAnimGroupSequence* AnimSequence = Process->animData->animSequences[4];
							if (AnimSequence && !memcmp(AnimSequence->filePath, "Meshes\\Characters\\_Male\\IdleAnims\\oronbackanim.kf", 49) && AnimSequence->last >= 0.4) {
								NiNode* ForearmTwistNode = This->ActorSkinInfo->LForearmTwistNode;
								NiNode* QuiverNode = This->ActorSkinInfo->QuiverNode;
								NiNode* TorchNode = This->ActorSkinInfo->TorchNode;
								NiAVObject* Object = NULL;
								if (Process->OnBackActionState == HighProcessEx::State::In) {
									if (LeftWeaponData)
										AttachWeaponToQuiver(This, Process, TorchNode, QuiverNode);
									else
										AttachShieldToQuiver(This, Process, ForearmTwistNode, QuiverNode);
									Process->OnBackState = HighProcessEx::State::In;
								}
								else {
									if (LeftWeaponData)
										AttachWeaponToTorch(This, Process, TorchNode, QuiverNode);
									else
										AttachShieldToForearmTwist(This, Process, ForearmTwistNode, QuiverNode);
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
		if (This == Player && LightData && Process->OnBackState == HighProcessEx::State::In && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.EquipmentMode.TorchKey)) {
			NiNode* BeltNode = (NiNode*)This->niNode->GetObjectByName(BeltNodeName);
			NiNode* TorchNode = This->ActorSkinInfo->TorchNode;
			NiAVObject* Object = NULL;
			if (Process->OnBeltState == HighProcessEx::State::In) {
				Object = This->ActorSkinInfo->LightObject;
				BeltNode->RemoveObject(&Object, Object);
				if (Object) {
					TheEquipmentManager->SetTorchLight(This, Object, 1);
					TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
					TorchNode->AddObject(Object, 1);
					if (This == Player) {
						Object = Player->firstPersonSkinInfo->LightObject;
						BeltNode = (NiNode*)Player->firstPersonNiNode->GetObjectByName(BeltNodeName);
						TorchNode = Player->firstPersonSkinInfo->TorchNode;
						BeltNode->RemoveObject(&Object, Object);
						TheEquipmentManager->SetTorchLight(This, Object, 1);
						TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::None, 0);
						TorchNode->AddObject(Object, 1);
					}
				}
				Process->OnBeltState = HighProcessEx::State::Out;
			}
			else {
				Object = This->ActorSkinInfo->LightObject;
				TorchNode->RemoveObject(&Object, Object);
				if (Object) {
					TheEquipmentManager->SetTorchLight(This, Object, 0);
					TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Light, Process->SitSleepState);
					BeltNode->AddObject(Object, 1);
					if (This == Player) {
						Object = Player->firstPersonSkinInfo->LightObject;
						BeltNode = (NiNode*)Player->firstPersonNiNode->GetObjectByName(BeltNodeName);
						TorchNode = Player->firstPersonSkinInfo->TorchNode;
						TorchNode->RemoveObject(&Object, Object);
						TheEquipmentManager->SetTorchLight(This, Object, 0);
						TheEquipmentManager->SetRotationPosition(Object, EquipmentManager::PositionRotationType::Light, Process->SitSleepState);
						BeltNode->AddObject(Object, 1);
					}
				}
				Process->OnBeltState = HighProcessEx::State::In;
			}
		}
	}
	return (*ProcessAction)(This, Arg1, Arg2);

}

static UInt8 (__thiscall* ProcessControlAttack)(PlayerCharacter*) = (UInt8 (__thiscall*)(PlayerCharacter*))Hooks::ProcessControlAttack;
static UInt8 __fastcall ProcessControlAttackHook(PlayerCharacter* This, UInt32 edx) {
	
	HighProcessEx* Process = (HighProcessEx*)This->process;
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
	return (*ProcessControlAttack)(This);

}

static void (__thiscall* AttackHandling)(Actor*, UInt8, TESObjectREFR*, TESObjectREFR*) = (void (__thiscall*)(Actor*, UInt8, TESObjectREFR*, TESObjectREFR*))Hooks::AttackHandling;
static void __fastcall AttackHandlingHook(Actor* This, UInt32 edx, UInt8 Arg1, TESObjectREFR* Arrow, TESObjectREFR* Target) {
	
	HighProcessEx* Process = (HighProcessEx*)This->process;
	InventoryChanges::EntryData* LeftWeaponData = Process->EquippedLeftWeaponData;

	(*AttackHandling)(This, Arg1, Arrow, Target);
	if (This == Player && Process->LeftAnimState == HighProcessEx::State::In) {
		TheEquipmentManager->SetAnimGroup(Process, 20, 2, "Characters\\_Male\\OnehandAttackLeft_OR_dual.kf");
		if (Process->SitSleepState < 3 || Process->SitSleepState > 5)
			TheEquipmentManager->SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_dual.kf");
		else
			TheEquipmentManager->SetAnimGroup(Process, 21, 2, "Characters\\_Male\\OnehandAttackRight_OR_mounted.kf");
		Process->LeftAnimState = HighProcessEx::State::StateNone;
	}

}

static InventoryChanges::EntryData* (__thiscall* GetEquippedWeaponData)(HighProcess*, UInt8) = (InventoryChanges::EntryData* (__thiscall*)(HighProcess*, UInt8))Hooks::GetEquippedWeaponData;
static InventoryChanges::EntryData* __fastcall GetEquippedWeaponDataHook(HighProcess* This, UInt32 edx, UInt8 Arg1) {
	
	HighProcessEx* Process = (HighProcessEx*)This;

	if (Process->GetProcessLevel() == 0 && (Process->LeftEquippingState || Process->LeftAnimState)) return Process->EquippedLeftWeaponData;
	return (*GetEquippedWeaponData)(This, Arg1);

}

static bool (__thiscall* SetEquippedWeaponData)(HighProcess*, InventoryChanges::EntryData*, NiNode*) = (bool (__thiscall*)(HighProcess*, InventoryChanges::EntryData*, NiNode*))Hooks::SetEquippedWeaponData;
static bool __fastcall SetEquippedWeaponDataHook(HighProcess* This, UInt32 edx, InventoryChanges::EntryData* InventoryData, NiNode* ActorNode) {
	
	HighProcessEx* Process = (HighProcessEx*)This;
	
	if (Process->GetProcessLevel() == 0 && Process->LeftEquippingState) {
		Process->EquippedLeftWeaponData = InventoryData;
		return 1;
	}
	return (*SetEquippedWeaponData)(This, InventoryData, ActorNode);

}

static void (__thiscall* EquipItem)(InventoryChanges::Data*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8) = (void (__thiscall*)(InventoryChanges::Data*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8))Hooks::EquipItem;
static void __fastcall EquipItemHook(InventoryChanges::Data* This, UInt32 edx, TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock) {
	
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0 && Process->LeftEquippingState) Left = 1;
	(*EquipItem)(This, Form, Quantity, Act, DataList, Left, Lock);

}

static void (__thiscall* UnequipItem)(InventoryChanges::Data*, UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8) = (void (__thiscall*)(InventoryChanges::Data*, UInt8*, TESForm*, int, Actor*, ExtraDataList*, UInt8, UInt8))Hooks::UnequipItem;
static void __fastcall UnequipItemHook(InventoryChanges::Data* This, UInt32 edx, UInt8* Arg1, TESForm* Form, int Quantity, Actor* Act, ExtraDataList* DataList, UInt8 Left, UInt8 Lock) {
	
	HighProcessEx* Process = (HighProcessEx*)Act->process;

	if (Process && Process->GetProcessLevel() == 0 && Form->formType == TESForm::FormType::kFormType_Weapon && Left) Process->LeftEquippingState = HighProcessEx::State::Out;
	(*UnequipItem)(This, Arg1, Form, Quantity, Act, DataList, Left, Lock);
	if (Process && Process->GetProcessLevel() == 0 && Form->formType == TESForm::FormType::kFormType_Weapon && Left) Process->LeftEquippingState = HighProcessEx::State::StateNone;

}

static void (__thiscall* EquipWeapon)(Actor*, TESObjectWEAP*) = (void (__thiscall*)(Actor*, TESObjectWEAP*))Hooks::EquipWeapon;
static void __fastcall EquipWeaponHook(Actor* This, UInt32 edx, TESObjectWEAP* Weapon) {

	HighProcessEx* Process = (HighProcessEx*)This->process;
	
	if (Process && Process->GetProcessLevel() == 0) {
		if (Process->LeftEquippingState) {
			NiNode* (__cdecl * LoadNiFile)(const char*, UInt32, Actor*, NiNode*) = (NiNode*(__cdecl *)(const char*, UInt32, Actor*, NiNode*))0x00479450;
			Process->EquippingType = HighProcessEx::ObjectType::Weapon;
			if (Process->WeaponState)
				Process->OnBackState = HighProcessEx::State::Out;
			else
				Process->OnBackState = HighProcessEx::State::In;
			NiNode* ObjectNode = LoadNiFile(Weapon->model.nifPath.m_data, 9, This, This->niNode);
			ObjectNode->SetName("LeftWeapon");
			Process->LeftWeaponObject = ObjectNode;
			if (This == Player) {
				ObjectNode = LoadNiFile(Weapon->model.nifPath.m_data, 9, Player, Player->firstPersonNiNode);
				ObjectNode->SetName("LeftWeapon");
				Process->LeftWeaponObjectFirst = ObjectNode;
			}
			Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
			TheEquipmentManager->SetAnimations(Process, 1);
		}
		else {
			Process->EquippingType = HighProcessEx::ObjectType::Weapon;
			(*EquipWeapon)(This, Weapon);
			Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;
		}
	}
	else 
		(*EquipWeapon)(This, Weapon);

}

static void (__thiscall* UnequipWeapon)(Actor*) = (void (__thiscall*)(Actor*))Hooks::UnequipWeapon;
static void __fastcall UnequipWeaponHook(Actor* This, UInt32 edx) {

	HighProcessEx* Process = (HighProcessEx*)This->process;
	
	if (Process && Process->GetProcessLevel() == 0 && Process->LeftEquippingState) {
		const char* WeaponModelPath = ((TESObjectWEAP*)Process->EquippedLeftWeaponData->type)->model.nifPath.m_data;
		NiAVObject* Object = Process->LeftWeaponObject;
		NiNode* ParentNode = (NiNode*)Object->m_parent;
		ParentNode->RemoveObject(&Object, Object);
		Object->Destructor(1);
		ModelLoader->RemoveModel(WeaponModelPath);
		Process->LeftWeaponObject = NULL;
		if (This == Player) {
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
	else (*UnequipWeapon)(This);

}

static void (__thiscall* EquipShield)(Actor*, TESObjectARMO*) = (void (__thiscall*)(Actor*, TESObjectARMO*))Hooks::EquipShield;
static void __fastcall EquipShieldHook(Actor* This, UInt32 edx, TESObjectARMO* Shield) {

	HighProcessEx* Process = (HighProcessEx*)This->process;

	if (Process && Process->GetProcessLevel() == 0) {
		Process->EquippingType = HighProcessEx::ObjectType::Shield;
		if (Process->WeaponState)
			Process->OnBackState = HighProcessEx::State::Out;
		else
			Process->OnBackState = HighProcessEx::State::In;
	}
	(*EquipShield)(This, Shield);
	if (Process && Process->GetProcessLevel() == 0) Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;

}

static void (__thiscall* EquipLight)(Actor*, TESObjectLIGH*) = (void (__thiscall*)(Actor*, TESObjectLIGH*))Hooks::EquipLight;
static void __fastcall EquipLightHook(Actor* This, UInt32 edx, TESObjectLIGH* Light) {

	HighProcessEx* Process = (HighProcessEx*)This->process;

	if (This == Player && Process) {
		Process->EquippingType = HighProcessEx::ObjectType::Light;
		Process->OnBeltState = HighProcessEx::State::In;
	}
	(*EquipLight)(This, Light);
	if (This == Player && Process) Process->EquippingType = HighProcessEx::ObjectType::ObjectTypeNone;

}

static void (__thiscall* UnequipLight)(Character*) = (void (__thiscall*)(Character*))Hooks::UnequipLight;
static void __fastcall UnequipLightHook(Character* This, UInt32 edx) {

	PlayerCharacter* Act = (PlayerCharacter*)This;
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
	(*UnequipLight)(This);

}

static void (__thiscall* HideEquipment)(Actor*, TESForm*, UInt8) = (void (__thiscall*)(Actor*, TESForm*, UInt8))Hooks::HideEquipment;
static void __fastcall HideEquipmentHook(Actor* This, UInt32 edx, TESForm* Form, UInt8 Arg2) {

	if (This == Player) return;
	(*HideEquipment)(This, Form, Arg2);

}

static InventoryChanges::EntryData* (__thiscall* GetEquippedLightData)(HighProcess*, UInt8) = (InventoryChanges::EntryData* (__thiscall*)(HighProcess*, UInt8))Hooks::GetEquippedLightData;
static InventoryChanges::EntryData* __fastcall GetEquippedLightDataHook(HighProcess* This, UInt32 edx, UInt8 Arg1) {

	HighProcessEx* Process = (HighProcessEx*)This;
	
	if (Process == Player->process && Process->OnBeltState == HighProcessEx::State::In) return NULL;
	return (*GetEquippedLightData)(This, Arg1);

}

static void (__thiscall* SaveGame)(InventoryChanges::EntryData*) = (void (__thiscall*)(InventoryChanges::EntryData*))Hooks::SaveGame;
static void __fastcall SaveGameHook(InventoryChanges::EntryData* This, UInt32 edx) {

	ExtraDataList* DataList = NULL;

	if (This->type->formType == TESForm::FormType::kFormType_Weapon && This->extendData) {
		for (TList<ExtraDataList>::Iterator Itr = This->extendData->Begin(); !Itr.End(); ++Itr) {
			DataList = Itr.Get();
			if (DataList && DataList->IsWorn(1)) {
				DataList->SetWorn(0, 1);
				break;
			}
			DataList = NULL;
		}
	}
	(*SaveGame)(This);
	if (DataList) DataList->SetWorn(1, 1);

}

static void UnequipTorch(Actor* Act) {

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
		jmp		Jumpers::Equipment::UnequipTorchReturn
	}

}

static bool IsWorn = 0;
static void EquipItemWorn(InventoryChanges::EntryData* EntryData, Actor* Act) {

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
		jmp		Jumpers::Equipment::EquipItemWornReturn
	}

}

static void Prn(NiNode* ActorNode, NiNode* AttachToNode, NiNode* ObjectNode, SkinInfo* Info, int SkinInfoSlot) {

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
		jmp		Jumpers::Equipment::PrnReturn
	}

}

static void SetWeaponRotationPosition(HighProcess* Process, NiNode* ObjectNode) {
	
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
		jmp		Jumpers::Equipment::SetWeaponRotationPositionReturn
	}

}

static int MouseMenuButton(MenuInterfaceManager* Im, UInt8 Button1State) {
	
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
		jmp		Jumpers::Equipment::MenuMouseButtonReturn1

	loc_notpressed:
		popad
		jmp		Jumpers::Equipment::MenuMouseButtonReturn2
	}

}