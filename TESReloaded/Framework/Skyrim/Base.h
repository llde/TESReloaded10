#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting				= 0x00AFED60;
	static const UInt32 WriteSetting			= 0x00AFEB50;
	static const UInt32 LoadGame				= 0x0067B720;
	static const UInt32 NewMain					= 0x0069BFE0;
	static const UInt32 InitializeRenderer		= 0x00691030;
	static const UInt32 NewTES					= 0x00435C10;
	static const UInt32 NewPlayerCharacter		= 0x0074DB40;
	static const UInt32 NewSceneGraph			= 0x0069F1F0;
	static const UInt32 NewMainDataHandler		= 0x0043DE50;
	static const UInt32 NewMenuInterfaceManager = 0x00000000;
	static const UInt32 NewQueuedModelLoader	= 0x00430470;
};

static CommandTable	commandTable;

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
		PInterface->Register(RegisterPapyrusCommands);
		
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

class ShadowManagerBase {
public:

	enum ShadowMapTypeEnum {
		MapNear = 0,
		MapFar = 1,
		MapOrtho = 2,
	};

};