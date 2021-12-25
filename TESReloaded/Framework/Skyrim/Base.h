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
	static const UInt32 CreateVertexShader		= 0x00CCBB00;
	static const UInt32 CreatePixelShader		= 0x00CCC420;
	static const UInt32 LoadBloodSplatterShader = 0x00C9D0D0;
	static const UInt32 LoadDistantTreeShader	= 0x00CAE6C0;
	static const UInt32 LoadGrassShader			= 0x00C95FC0;
	static const UInt32 LoadParticleShader		= 0x00CC20C0;
	static const UInt32 LoadSkyShader			= 0x00CA9AE0;
	static const UInt32 LoadEffectShader		= 0x00CAD980;
	static const UInt32 LoadLightingShader		= 0x00CA2090;
	static const UInt32 LoadUtilityShader		= 0x00CB7E60;
	static const UInt32 LoadWaterShader			= 0x00CB38D0;
	static const UInt32 LoadImageSpaceShaders	= 0x00C7CC10;
	static const UInt32 LoadLightingShaderExtra = 0x00CA38D0;
};

static CommandTable	commandTable;

//void (__cdecl* ToggleConsole)() = (void (__cdecl*)())0x00847210;
//void __cdecl TrackToggleConsole() {
//
//	if (!commandTable.Patched) {
//		commandTable.Initialize();
//		commandTable.Add(&CommandInfo_GetVersion);
//		commandTable.Add(&CommandInfo_GetLocationName);
//		commandTable.Add(&CommandInfo_SetExtraEffectEnabled);
//		commandTable.Add(&CommandInfo_SetCustomConstant);
//		commandTable.Add(&CommandInfo_GetWeatherName);
//		commandTable.Set();
//		commandTable.Patched = true;
//	}
//	ToggleConsole();
//
//}

class CommandManagerBase {
public:

	void RegisterCommands(const PluginInterface* Interface, void* CommandExecuters[], CommandInfo* CommandInfos[], int CommandInfoSize) {

		PapyrusInterface* PInterface = (PapyrusInterface*)Interface->QueryInterface(PluginInterface::InterfaceType::kInterface_Papyrus);
		PInterface->Register(RegisterPapyrusCommands);
		
		//DetourTransactionBegin();
		//DetourUpdateThread(GetCurrentThread());
		//DetourAttach(&(PVOID&)ToggleConsole, &TrackToggleConsole);
		//DetourTransactionCommit();

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