BaseScript::BaseScript() {

	ElapsedTime = 0.0f;

}

LowHSoundScript::LowHSoundScript() {
	
	HeartSlow = NULL;
	ElapsedTime = -1.0f;

}

void LowHSoundScript::Run() {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		if (TheShaderManager->ShaderConst.LowHF.Data.x || ElapsedTime != -1.0f) {
			float HealthCoeff = TheShaderManager->ShaderConst.LowHF.HealthCoeff;

			if (Player->IsAlive()) {
				if (HealthCoeff) {
					if (ElapsedTime == -1.0f && HealthCoeff >= TheSettingManager->SettingsMain.LowHFSound.HealthCoeff) {
						Global->GetSound()->Play(HeartSlow);
						ElapsedTime = 0.0f;
					}
					else if (ElapsedTime >= 0.0f) {
						ElapsedTime += TheFrameRateManager->ElapsedTime;
						if (ElapsedTime >= 1.5f) ElapsedTime = -1.0f;
					}
				}
			}
		}
	}

}

LowFSoundScript::LowFSoundScript() {

	BreathingF = NULL;
	BreathingM = NULL;
	ElapsedTime = -1.0f;

}

void LowFSoundScript::Run() {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		if (TheShaderManager->ShaderConst.LowHF.Data.x || ElapsedTime != -1.0f) {
			float FatigueCoeff = TheShaderManager->ShaderConst.LowHF.FatigueCoeff;

			if (Player->IsAlive()) {
				if (FatigueCoeff) {
					if (ElapsedTime == -1.0f && FatigueCoeff >= TheSettingManager->SettingsMain.LowHFSound.FatigueCoeff) {
						if (Player->IsFemale()) {
							Global->GetSound()->Play(BreathingF);
							BreathingTime = 8.0f;
						}
						else {
							Global->GetSound()->Play(BreathingM);
							BreathingTime = 1.0f;
						}
						ElapsedTime = 0.0f;
					}
					else if (ElapsedTime >= 0.0f) {
						ElapsedTime += TheFrameRateManager->ElapsedTime;
						if (ElapsedTime >= BreathingTime) ElapsedTime = -1.0f;
					}
				}
			}
		}
	}

}

PurgerScript::PurgerScript() { }

void PurgerScript::Run() {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		int PurgerTime = TheSettingManager->SettingsMain.Purger.Time;
		bool PurgerKeyPressed = Global->OnKeyDown(TheSettingManager->SettingsMain.Purger.Key);

		if (PurgerTime || PurgerKeyPressed) {
			ElapsedTime += TheFrameRateManager->ElapsedTime;
			if (ElapsedTime >= PurgerTime || PurgerKeyPressed) {
				if (TheSettingManager->SettingsMain.Purger.PurgeCells) { Tes->PurgeCells(); Global->PurgeModels(); }
				if (TheSettingManager->SettingsMain.Purger.PurgeTextures) { TheRenderManager->device->EvictManagedResources(); }
				ElapsedTime = 0.0f;
			}
		}
	}

}

GravityScript::GravityScript() { }

void GravityScript::Run() {

	TESObjectCELL* CurrentCell = Player->parentCell;

	if (CurrentCell) CurrentCell->GetHavokWorld()->gravity.z = -17.0f * TheSettingManager->SettingsMain.Gravity.Value;

}

void EquipmentSetupChoice() {

	TheScriptManager->EquipmentSetup->ConfigStep = (EquipmentSetupScript::StepType)(InterfaceManager->GetMessageBoxButton() + EquipmentSetupScript::StepType::Normal);
	if (TheScriptManager->EquipmentSetup->ConfigStep <= EquipmentSetupScript::StepType::Swimming)
		TheScriptManager->EquipmentSetup->EquipItems(EquipmentSetupScript::StepType::Normal, TheScriptManager->EquipmentSetup->ConfigStep);
	else
		TheScriptManager->EquipmentSetup->ConfigStep = EquipmentSetupScript::StepType::None;

}

EquipmentSetupScript::EquipmentSetupScript() {
	
	memset(LeftWeapon, NULL, 16);
	ConfigStep = None;
	GameStep = Normal;
	CombatState = 0;

}

void EquipmentSetupScript::Run() {

	if (ConfigStep == None && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		StepType CurrentStep = GetCurrentEquipmentType();
		if (CurrentStep != GameStep) {
			if (CurrentStep == Normal || CurrentStep == Combat || (TheSettingManager->SettingsMain.EquipmentMode.SleepingEquipment && CurrentStep == Sleeping) || (TheSettingManager->SettingsMain.EquipmentMode.SwimmingEquipment && CurrentStep == Swimming)) {
				EquipItems(GameStep, CurrentStep);
				GameStep = CurrentStep;
			}
		}
	}
	else if (ConfigStep == Request) {
		if (GameStep == EquipmentSetupScript::StepType::Normal && !CombatState) {
			ConfigStep = Choice;
			InterfaceManager->ShowMessageBox("Equipment setup", EquipmentSetupChoice, "Combat", "Sleeping", "Swimming", "Cancel");
		}
		else {
			ConfigStep = EquipmentSetupScript::StepType::None;
			InterfaceManager->ShowMessage("You cannot use the equipment menu now.");
		}
	}
	else if (ConfigStep >= Combat && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None)) {
		EquipItems(ConfigStep, Normal);
		ConfigStep = None;
	}

}

void EquipmentSetupScript::EquipItems(StepType From, StepType To) {

	HighProcessEx* Process = (HighProcessEx*)Player->process;
	InventoryChanges::Data* InventoryChangesData = Player->extraDataList.GetInventoryChangesData();
	TList<InventoryChanges::EntryData>* EntryDataList = NULL;
	InventoryChanges::EntryData* Data = NULL;
	ExtraDataList* DataList = NULL;
	TList<ExtraDataList>* ExtendData = NULL;
	bool Loop = true;
	
	Items[From - Normal].clear();
	while (Loop) {
		Loop = false;
		if (InventoryChangesData) {
			if (EntryDataList = InventoryChangesData->data) {
				for (TList<InventoryChanges::EntryData>::Iterator ItrE = EntryDataList->Begin(); !ItrE.End(); ++ItrE) {
					Data = ItrE.Get();
					if (Data && (ExtendData = Data->extendData)) {
						for (TList<ExtraDataList>::Iterator Itr = ExtendData->Begin(); !Itr.End(); ++Itr) {
							DataList = Itr.Get();
							if (DataList && DataList->IsWorn()) {
								TESForm* Form = Data->type;
								Items[From - Normal].push_back(Form);
								if (Form->formType == TESForm::FormType::kFormType_Weapon && DataList->IsWorn(1)) LeftWeapon[From - Normal] = (TESObjectWEAP*)Form;
								Player->UnequipItem(Form, 1, DataList);
								Loop = true;
								break;
							}
						}
					}
					if (Loop) break;
				}
			}
		}
	}
	for each (TESForm* Form in Items[To - Normal]) {
		if (LeftWeapon[To - Normal] && Form == LeftWeapon[To - Normal]) {
			LeftWeapon[To - Normal] = NULL;
			Process->LeftEquippingState = HighProcessEx::State::In;
		}
		Player->EquipItem(Form, 1, NULL);
		Process->LeftEquippingState = HighProcessEx::State::StateNone;
	}
	Player->UpdateInventory();

}

EquipmentSetupScript::StepType EquipmentSetupScript::GetCurrentEquipmentType() {

	UInt8 SitSleepState = Player->GetSitSleepState();
	StepType CurrentStep = Normal;
	
	if (CombatState) CurrentStep = Combat;
	if (Global->OnKeyDown(TheSettingManager->SettingsMain.EquipmentMode.CombatEquipmentKey)) {
		if (CombatState) CurrentStep = Normal; else CurrentStep = Combat;
		CombatState = !CombatState;
	}
	else if (SitSleepState >= 8 && SitSleepState <= 10) {
		if (!CombatState) CurrentStep = Sleeping;
	}
	else if (Player->IsMoving()) {
		if (!CombatState) {
			ElapsedTime = 0.0f;
			CurrentStep = Swimming;
		}
	}
	if (CurrentStep == Normal && GameStep == Swimming && ElapsedTime < 2.0f) {
		ElapsedTime += TheFrameRateManager->ElapsedTime;
		CurrentStep = Swimming;
	}
	return CurrentStep;

}

void ScriptManager::Initialize() {

	Logger::Log("Starting the script manager...");
	TheScriptManager = new ScriptManager();
	
	SettingsMainStruct* MainStruct = &TheSettingManager->SettingsMain;

	if (MainStruct->Effects.LowHF) {
		if (MainStruct->LowHFSound.HealthEnabled) TheScriptManager->LowHSound = new LowHSoundScript();
		if (MainStruct->LowHFSound.FatigueEnabled) TheScriptManager->LowFSound = new LowFSoundScript();
	}
	if (MainStruct->Purger.Enabled) TheScriptManager->Purger = new PurgerScript();
	if (MainStruct->Gravity.Enabled) TheScriptManager->Gravity = new GravityScript();
	if (MainStruct->EquipmentMode.Enabled) TheScriptManager->EquipmentSetup = new EquipmentSetupScript();

}

void ScriptManager::LoadForms() {
	
	if (LowHSound) {
		LowHSound->HeartSlow = (TESSound*)DataHandler->CreateForm(TESForm::FormType::kFormType_Sound);
		LowHSound->HeartSlow->GenerateID(0x22C);
		LowHSound->HeartSlow->flags = 0;
		LowHSound->HeartSlow->SetFile("fx\\tesr\\heartslow.wav");
		DataHandler->AddData(LowHSound->HeartSlow);
	}
	if (LowFSound) {
		LowFSound->BreathingF = (TESSound*)DataHandler->CreateForm(TESForm::FormType::kFormType_Sound);
		LowFSound->BreathingF->GenerateID(0x22D);
		LowFSound->BreathingF->flags = 0;
		LowFSound->BreathingF->SetFile("fx\\tesr\\breathingf.wav");
		DataHandler->AddData(LowFSound->BreathingF);
		LowFSound->BreathingM = (TESSound*)DataHandler->CreateForm(TESForm::FormType::kFormType_Sound);
		LowFSound->BreathingM->GenerateID(0x22E);
		LowFSound->BreathingM->flags = 0;
		LowFSound->BreathingM->SetFile("fx\\tesr\\breathingm.wav");
		DataHandler->AddData(LowFSound->BreathingM);
	}

}

void ScriptManager::Run() {

	if (Purger) Purger->Run();
	if (Gravity) Gravity->Run();
	if (LowHSound) LowHSound->Run();
	if (LowFSound) LowFSound->Run();
	if (EquipmentSetup) EquipmentSetup->Run();

}