void CommandManager::Initialize(const PluginInterface* Interface) {

	Logger::Log("Initializing the command manager...");
	TheCommandManager = new CommandManager();

	void* CommandExecuters[] = { CommandExecuter_IsThirdPerson };
	CommandInfo* CommandInfos[] = { &CommandInfo_GetVersion, &CommandInfo_GetLocationName, &CommandInfo_SetExtraEffectEnabled, &CommandInfo_SetCustomConstant, &CommandInfo_GetWeatherName, &CommandInfo_GetSetting, &CommandInfo_SetSetting, &CommandInfo_CameraTranslate, &CommandInfo_CameraRotate, &CommandInfo_CameraTranslateToPosition, &CommandInfo_CameraRotateToPosition, &CommandInfo_CameraLookAt, &CommandInfo_CameraLookAtPosition, &CommandInfo_CameraReset };
	TheCommandManager->RegisterCommands(Interface, CommandExecuters, CommandInfos, 14);

}

void CommandManager::PluginCommands::IsThirdPerson(double* result) {

	*result = !TheCameraManager->FirstPersonView;

}

void CommandManager::PluginCommands::GetVersion(double* result) {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Console)) PrintToConsole(PluginVersion::VersionString);
	*result = 1;

}

void CommandManager::PluginCommands::GetLocationName(double* result) {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Console)) {
		const char* worldName = NULL;
		const char* regionName = NULL;
		const char* cellName = Player->parentCell->GetEditorName();

		std::string s = "Worldspace: ";
		if (TESWorldSpace* currentWS = Player->GetWorldSpace()) worldName = currentWS->GetEditorName();
		if (worldName != NULL)
			s += worldName;
		else
			s += "(no worldspace)";
		s += ", Region: ";
		if (TESRegionEx* currentRE = (TESRegionEx*)Player->GetRegion()) regionName = currentRE->EditorName;
		if (regionName != NULL)
			s += regionName;
		else
			s += "(no region)";
		s += ", Cell: ";
		s += cellName;
		PrintToConsole(s.c_str());
	}
	*result = 1;

}

void CommandManager::PluginCommands::SetExtraEffectEnabled(double* result, const char* Name, bool Value) {

	TheShaderManager->SetExtraEffectEnabled(Name, Value);
	*result = 1;

}

void CommandManager::PluginCommands::SetCustomConstant(double* result, const char* Name, D3DXVECTOR4* Value) {

	TheShaderManager->SetCustomConstant(Name, *Value);
	*result = 1;

}

void CommandManager::PluginCommands::GetWeatherName(double* result) {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Console)) {
		const char* weatherName = NULL;

		if (TESWeatherEx* currentWE = (TESWeatherEx*)TheShaderManager->ShaderConst.pWeather) weatherName = currentWE->EditorName;
		std::string s = "Weather: ";
		if (weatherName != NULL)
			s += weatherName;
		else
			s += "(no weather)";
		PrintToConsole(s.c_str());
	}
	*result = 1;

}

void CommandManager::PluginCommands::GetSetting(double* result, const char* Section, const char* Key) {

	*result = TheSettingManager->GetSettingF(Section, Key);

}

void CommandManager::PluginCommands::SetSetting(double* result, const char* Section, const char* Key, float Value) {
	
	TheSettingManager->SetSetting(Section, Key, Value);
	*result = 1; 

}

void CommandManager::PluginCommands::CameraTranslate(double* result, TESObjectREFR* Ref, NiPoint3* Value) {
	
	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsTranslating = true;
	CameraCommands->Ref = Ref;
	CameraCommands->Position.x = Value->z;
	CameraCommands->Position.y = Value->y;
	CameraCommands->Position.z = Value->x;
	*result = 1;

}

void CommandManager::PluginCommands::CameraRotate(double* result, TESObjectREFR* Ref, NiPoint3* Value) {

	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsRotating = true;
	CameraCommands->Ref = Ref;
	CameraCommands->Rotation.x = Value->z;
	CameraCommands->Rotation.y = Value->x;
	CameraCommands->Rotation.z = Value->y;
	*result = 1;

}

void CommandManager::PluginCommands::CameraTranslateToPosition(double* result, NiPoint3* Value) {
	
	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsTranslatingToPosition = true;
	CameraCommands->Position.x = Value->x;
	CameraCommands->Position.y = Value->y;
	CameraCommands->Position.z = Value->z;
	*result = 1;

}

void CommandManager::PluginCommands::CameraRotateToPosition(double* result, NiPoint3* Value) {
	
	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsRotatingToPosition = true;
	CameraCommands->Rotation.x = Value->z;
	CameraCommands->Rotation.y = Value->x;
	CameraCommands->Rotation.z = Value->y;
	*result = 1;

}

void CommandManager::PluginCommands::CameraLookAt(double* result, TESObjectREFR* Ref, NiPoint3* Value) {

	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsLookingAt = true;
	CameraCommands->Ref = Ref;
	CameraCommands->LookingAtOffset.x = Value->z;
	CameraCommands->LookingAtOffset.y = Value->y;
	CameraCommands->LookingAtOffset.z = Value->x;
	*result = 1;

}

void CommandManager::PluginCommands::CameraLookAtPosition(double* result, NiPoint3* Value) {
	
	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsLookingAtPosition = true;
	CameraCommands->LookingAtPosition.x = Value->x;
	CameraCommands->LookingAtPosition.y = Value->y;
	CameraCommands->LookingAtPosition.z = Value->z;
	*result = 1;

}

void CommandManager::PluginCommands::CameraReset(double* result) {
	
	CameraManager::CameraManagerCommands* CameraCommands = TheCameraManager->CameraCommands;

	CameraCommands->IsTranslating = false;
	CameraCommands->IsRotating = false;
	CameraCommands->IsTranslatingToPosition = false;
	CameraCommands->IsRotatingToPosition = false;
	CameraCommands->IsLookingAt = false;
	CameraCommands->IsLookingAtPosition = false;
	*result = 1;

}