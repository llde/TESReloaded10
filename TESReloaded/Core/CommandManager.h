#pragma once

class CommandManager: public CommandManagerBase { // Never disposed
public:
	class PluginCommands {
	public:
		void IsThirdPerson(double* result);
		void GetVersion(double* result);
		void GetLocationName(double* result);
		void SetExtraEffectEnabled(double* result, const char* Name, bool Value);
		void SetCustomConstant(double* result, const char* Name, D3DXVECTOR4* Value);
		void GetWeatherName(double* result);
		void GetSetting(double* result, const char* Section, const char* Key);
		void SetSetting(double* result, const char* Section, const char* Key, float Value);
		void CameraTranslate(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraRotate(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraTranslateToPosition(double* result, NiPoint3* Value);
		void CameraRotateToPosition(double* result, NiPoint3* Value);
		void CameraLookAt(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraLookAtPosition(double* result, NiPoint3* Value);
		void CameraReset(double* result);
	};

	static void			Initialize(const PluginInterface* Interface);

	PluginCommands		Commands;
};

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

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value)) TheCommandManager->Commands.SetExtraEffectEnabled(Args.result, Name, Value);
	return true;

}

static bool CommandExecuter_SetCustomConstant(CommandArgs Args) {

	char Name[80];
	D3DXVECTOR4 Value;
	
	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value.x, &Value.y, &Value.z, &Value.w)) TheCommandManager->Commands.SetCustomConstant(Args.result, Name, &Value);
	return true;

}

static bool CommandExecuter_GetWeatherName(CommandArgs Args) {

	TheCommandManager->Commands.GetWeatherName(Args.result);
	return true;

}

static bool CommandExecuter_GetSetting(CommandArgs Args) {

	char Section[40];
	char Key[40];

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Section, &Key)) TheCommandManager->Commands.GetSetting(Args.result, Section, Key);
	return true;

}

static bool CommandExecuter_SetSetting(CommandArgs Args) {

	char Section[40];
	char Key[40];
	float Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Section, &Key, &Value)) TheCommandManager->Commands.SetSetting(Args.result, Section, Key, Value);
	return true;

}

static bool CommandExecuter_CameraTranslate(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraTranslate(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraRotate(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.z, &Value.x, &Value.y)) TheCommandManager->Commands.CameraRotate(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraTranslateToPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraTranslateToPosition(Args.result, &Value);
	return true;

}

static bool CommandExecuter_CameraRotateToPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.z, &Value.x, &Value.y)) TheCommandManager->Commands.CameraRotateToPosition(Args.result, &Value);
	return true;

}

static bool CommandExecuter_CameraLookAt(CommandArgs Args) {

	TESObjectREFR* Ref;
	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Ref, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraLookAt(Args.result, Ref, &Value);
	return true;

}

static bool CommandExecuter_CameraLookAtPosition(CommandArgs Args) {

	NiPoint3 Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Value.x, &Value.y, &Value.z)) TheCommandManager->Commands.CameraLookAtPosition(Args.result, &Value);
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