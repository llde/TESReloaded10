#pragma once

CommandTable	commandTable;

namespace SRPapyrus {

	const char* SRClass = "SRCommands";

	bool SetExtraEffectEnabled(BSFixedString Name, bool Value) {

		double result;

		TheCommandManager->Commands.SetExtraEffectEnabled(&result, Name.m_data, Value);
		return result;

	}

	bool SetCustomConstant(BSFixedString Name, float Value1, float Value2, float Value3, float Value4) {

		double result;
		float Value[4] = { Value1, Value2, Value3, Value4 };

		TheCommandManager->Commands.SetCustomConstant(&result, Name.m_data, Value);
		return result;

	}

	bool RegisterCommands(VMClassRegistry* registry) {

		registry->RegisterFunction(new PapyrusFunction2<BSFixedString, bool>("SetExtraEffectEnabled", SRClass, SetExtraEffectEnabled, registry));
		registry->RegisterFunction(new PapyrusFunction5<BSFixedString, float, float, float, float>("SetCustomConstant", SRClass, SetCustomConstant, registry));
		return true;

	}

}

void (__cdecl* ToggleConsole)() = (void (__cdecl*)())0x00847210;
void __cdecl TrackToggleConsole() {

	if (!commandTable.Patched) {
		commandTable.Initialize();
		commandTable.Add(&CommandInfo_GetVersion);
		commandTable.Add(&CommandInfo_GetLocationName);
		commandTable.Add(&CommandInfo_SetExtraEffectEnabled);
		commandTable.Add(&CommandInfo_SetCustomConstant);
		commandTable.Add(&CommandInfo_GetWeatherName);
		commandTable.Set();
		commandTable.Patched = true;
	}
	ToggleConsole();

}

class CommandManagerBase {
public:

	void RegisterCommands(const PluginInterface* Interface, void* CommandExecuters[], CommandInfo* CommandInfos[], int CommandInfoSize) {

		PapyrusInterface* PInterface = (PapyrusInterface*)Interface->QueryInterface(PluginInterface::InterfaceType::kInterface_Papyrus);
		PInterface->Register(SRPapyrus::RegisterCommands);
		
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)ToggleConsole, &TrackToggleConsole);
		DetourTransactionCommit();

	}

};

class SettingManagerBase {
public:

	bool IsMatching(char* Versioning) {

		return Versioning[1] == '1';

	}

};