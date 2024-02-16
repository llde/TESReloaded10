static CommandParam SetCustomConstantParams[5] = {

	{ "string",	CommandParam::ParamType::kParamType_String, 0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },

};

static CommandParam SetExtraEffectEnabledParams[2] = {

	{ "string",	CommandParam::ParamType::kParamType_String,  0 },
	{ "int",	CommandParam::ParamType::kParamType_Integer, 0 },

};

static CommandParam GetSettingParams[2] = {

	{ "string",	CommandParam::ParamType::kParamType_String, 0 },
	{ "string",	CommandParam::ParamType::kParamType_String, 0 },

};

static CommandParam SetSettingParams[3] = {

	{ "string",	CommandParam::ParamType::kParamType_String, 0 },
	{ "string",	CommandParam::ParamType::kParamType_String, 0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },

};

static CommandParam CameraTranslateParams[4] = {
	
	{ "objectRef",	CommandParam::ParamType::kParamType_ObjectRef, 0 },
	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },
	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },
	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },
	
};

static CommandParam CameraTranslateToPositionParams[3] = {

	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },
	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },
	{ "float",		CommandParam::ParamType::kParamType_Float, 0 },

};

static bool CommandExecuter_IsThirdPerson(CommandArgs Args) {

	TheCommandManager->Commands.IsThirdPerson(Args.result);
	return true;

}

static bool CommandExecuter_GetVersion(CommandArgs Args) {

	TheCommandManager->Commands.GetVersion(Args.result);
	return true;

}

static bool CommandExecuter_GetLocationName(CommandArgs Args) {

	TheCommandManager->Commands.GetLocationName(Args.result);
	return true;

}

static bool CommandExecuter_SetExtraEffectEnabled(CommandArgs Args) {

	char Name[80];
	int Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value)) TheCommandManager->Commands.SetExtraEffectEnabled(Args.result, Name, Value);
	return true;

}

static bool CommandExecuter_SetCustomConstant(CommandArgs Args) {

	char Name[80];
	D3DXVECTOR4 Value;
	
	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value.x, &Value.y, &Value.z, &Value.w)) TheCommandManager->Commands.SetCustomConstant(Args.result, Name, &Value);
	return true;

}

static bool CommandExecuter_GetWeatherName(CommandArgs Args) {

	TheCommandManager->Commands.GetWeatherName(Args.result);
	return true;

}

static bool CommandExecuter_GetSetting(CommandArgs Args) {

	char Section[40];
	char Key[40];

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Section, &Key)) TheCommandManager->Commands.GetSetting(Args.result, Section, Key);
	return true;

}

static bool CommandExecuter_SetSetting(CommandArgs Args) {

	char Section[40];
	char Key[40];
	float Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Section, &Key, &Value)) TheCommandManager->Commands.SetSetting(Args.result, Section, Key, Value);
	return true;

}

static bool CommandExecuter_CameraTranslate(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraTranslate(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraRotate(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.z, &Value.x, &Value.y)) TheCommandManager->Commands.CameraRotate(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraTranslateToPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraTranslateToPosition(Args.result, &Value);
	return true;

}

static bool CommandExecuter_CameraRotateToPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.z, &Value.x, &Value.y)) TheCommandManager->Commands.CameraRotateToPosition(Args.result, &Value);
	return true;

}

static bool CommandExecuter_CameraLookAt(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraLookAt(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraLookAtPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (Pointers::Functions::ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraLookAtPosition(Args.result, &Value);
	return true;

}

static bool CommandExecuter_CameraReset(CommandArgs Args) {

	TheCommandManager->Commands.CameraReset(Args.result);
	return true;

}

static CommandInfo CommandInfo_GetVersion					= { CommandPrefix"GetVersion", "", 0, "Returns the plugin version (console command only)", 0, 0, NULL, CommandExecuter_GetVersion, NULL, NULL, 0 };
static CommandInfo CommandInfo_GetLocationName				= { CommandPrefix"GetLocationName", "", 0, "Gets the name of the current worldspace and current cell(console command only)", 0, 0, NULL, CommandExecuter_GetLocationName, NULL, NULL, 0 };
static CommandInfo CommandInfo_SetExtraEffectEnabled		= { CommandPrefix"SetExtraEffectEnabled", "", 0, "Enables or disables a custom effect", 0, 2, SetExtraEffectEnabledParams, CommandExecuter_SetExtraEffectEnabled, NULL, NULL, 0 };
static CommandInfo CommandInfo_SetCustomConstant			= { CommandPrefix"SetCustomConstant", "", 0, "Sets the value of a custom shader constant", 0, 5, SetCustomConstantParams, CommandExecuter_SetCustomConstant, NULL, NULL, 0 };
static CommandInfo CommandInfo_GetWeatherName				= { CommandPrefix"GetWeatherName", "", 0, "Returns the plugin version (console command only)", 0, 0, NULL, CommandExecuter_GetWeatherName, NULL, NULL, 0 };
static CommandInfo CommandInfo_GetSetting					= { CommandPrefix"GetSetting", "", 0, "Gets a configuration setting", 0, 2, GetSettingParams, CommandExecuter_GetSetting, NULL, NULL, 0 };
static CommandInfo CommandInfo_SetSetting					= { CommandPrefix"SetSetting", "", 0, "Sets a configuration setting", 0, 3, SetSettingParams, CommandExecuter_SetSetting, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraTranslate				= { CommandPrefix"CameraTranslate", "", 0, "Translates the camera position in relation of the ref", 0, 4, CameraTranslateParams, CommandExecuter_CameraTranslate, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraRotate					= { CommandPrefix"CameraRotate", "", 0, "Rotates the camera in relation of the ref (yaw, pitch, roll)", 0, 4, CameraTranslateParams, CommandExecuter_CameraRotate, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraTranslateToPosition	= { CommandPrefix"CameraTranslateToPosition", "", 0, "Translates the camera position in the world", 0, 3, CameraTranslateToPositionParams, CommandExecuter_CameraTranslateToPosition, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraRotateToPosition		= { CommandPrefix"CameraRotateToPosition", "", 0, "Rotates the camera in the world (yaw, pitch, roll)", 0, 3, CameraTranslateToPositionParams, CommandExecuter_CameraRotateToPosition, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraLookAt					= { CommandPrefix"CameraLookAt", "", 0, "Looks at the ref with an offset", 0, 4, CameraTranslateParams, CommandExecuter_CameraLookAt, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraLookAtPosition			= { CommandPrefix"CameraLookAtPosition", "", 0, "Looks at the position in the world", 0, 3, CameraTranslateToPositionParams, CommandExecuter_CameraLookAtPosition, NULL, NULL, 0 };
static CommandInfo CommandInfo_CameraReset					= { CommandPrefix"CameraReset", "", 0, "Resets the camera to the normal state", 0, 0, NULL, CommandExecuter_CameraReset, NULL, NULL, 0 };

static bool Papyrus_SetExtraEffectEnabled(BSFixedString Name, bool Value) {

	double result;

	TheCommandManager->Commands.SetExtraEffectEnabled(&result, Name.m_data, Value);
	return result;

}

static bool Papyrus_SetCustomConstant(BSFixedString Name, float Value1, float Value2, float Value3, float Value4) {

	double result;
	D3DXVECTOR4 Value = { Value1, Value2, Value3, Value4 };

	TheCommandManager->Commands.SetCustomConstant(&result, Name.m_data, &Value);
	return result;

}

void CommandManager::Initialize(const PluginInterface* Interface) {

	Logger::Log("Initializing the command manager...");
	TheCommandManager = new CommandManager();

	void* CommandExecuters[] = { CommandExecuter_IsThirdPerson };
	CommandInfo* CommandInfos[] = { &CommandInfo_GetVersion, &CommandInfo_GetLocationName, &CommandInfo_SetExtraEffectEnabled, &CommandInfo_SetCustomConstant, &CommandInfo_GetWeatherName, &CommandInfo_GetSetting, &CommandInfo_SetSetting, &CommandInfo_CameraTranslate, &CommandInfo_CameraRotate, &CommandInfo_CameraTranslateToPosition, &CommandInfo_CameraRotateToPosition, &CommandInfo_CameraLookAt, &CommandInfo_CameraLookAtPosition, &CommandInfo_CameraReset };
	void* PapyrusCommands[] = { Papyrus_SetExtraEffectEnabled, Papyrus_SetCustomConstant };
	TheCommandManager->RegisterCommands(Interface, CommandExecuters, CommandInfos, 14, PapyrusCommands);

}

void CommandManager::PluginCommands::IsThirdPerson(double* result) {

	*result = !TheCameraManager->IsFirstPerson();

}

void CommandManager::PluginCommands::GetVersion(double* result) {

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Console)) Pointers::Functions::PrintToConsole(PluginVersion::VersionString);
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
		Pointers::Functions::PrintToConsole(s.c_str());
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
		Pointers::Functions::PrintToConsole(s.c_str());
	}
	*result = 1;

}

void CommandManager::PluginCommands::GetSetting(double* result, const char* Section, const char* Key) {
#ifdef EXPERIMENTAL_FEATURE
	*result = TheSettingManager->GetSettingF(Section, Key);
#endif
}

void CommandManager::PluginCommands::SetSetting(double* result, const char* Section, const char* Key, float Value) {
#ifdef EXPERIMENTAL_FEATURE

	TheSettingManager->SetSetting(Section, Key, Value);
	*result = 1; 
#endif
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