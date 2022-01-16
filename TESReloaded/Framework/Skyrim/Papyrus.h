#pragma once

static bool SetExtraEffectEnabled(BSFixedString Name, bool Value) {

	double result;

	TheCommandManager->Commands.SetExtraEffectEnabled(&result, Name.m_data, Value);
	return result;

}

static bool SetCustomConstant(BSFixedString Name, float Value1, float Value2, float Value3, float Value4) {

	double result;
	D3DXVECTOR4 Value = { Value1, Value2, Value3, Value4 };

	TheCommandManager->Commands.SetCustomConstant(&result, Name.m_data, &Value);
	return result;

}

static bool RegisterPapyrusCommands(VMClassRegistry* registry) {

	registry->RegisterFunction(new PapyrusFunction2<BSFixedString, bool>("SetExtraEffectEnabled", "SRCommands", SetExtraEffectEnabled, registry));
	registry->RegisterFunction(new PapyrusFunction5<BSFixedString, float, float, float, float>("SetCustomConstant", "SRCommands", SetCustomConstant, registry));
	return true;

}