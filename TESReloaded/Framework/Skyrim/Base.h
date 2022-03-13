#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting					= 0x00AFED60;
	static const UInt32 WriteSetting				= 0x00AFEB50;
	static const UInt32 LoadGame					= 0x0067B720;
	static const UInt32 NewMain						= 0x0069BFE0;
	static const UInt32 InitializeRenderer			= 0x00691030;
	static const UInt32 NewTES						= 0x00435C10;
	static const UInt32 NewPlayerCharacter			= 0x0074DB40;
	static const UInt32 NewSceneGraph				= 0x0069F1F0;
	static const UInt32 NewMainDataHandler			= 0x0043DE50;
	static const UInt32 NewMenuInterfaceManager		= 0x00000000;
	static const UInt32 NewQueuedModelLoader		= 0x00430470;
	static const UInt32 CreateVertexShader			= 0x00CCBB00;
	static const UInt32 CreatePixelShader			= 0x00CCC420;
	static const UInt32 LoadBloodSplatterShader		= 0x00C9D0D0;
	static const UInt32 LoadDistantTreeShader		= 0x00CAE6C0;
	static const UInt32 LoadGrassShader				= 0x00C95FC0;
	static const UInt32 LoadParticleShader			= 0x00CC20C0;
	static const UInt32 LoadSkyShader				= 0x00CA9AE0;
	static const UInt32 LoadEffectShader			= 0x00CAD980;
	static const UInt32 LoadLightingShader			= 0x00CA2090;
	static const UInt32 LoadUtilityShader			= 0x00CB7E60;
	static const UInt32 LoadWaterShader				= 0x00CB38D0;
	static const UInt32 LoadImageSpaceShaders		= 0x00C7CC10;
	static const UInt32 LoadLightingShaderExtra		= 0x00CA38D0;
	static const UInt32 Render						= 0x0069BDF0;
	static const UInt32 SetupRenderingPass			= 0x00CAF9C0;
	static const UInt32 ProcessImageSpaceShaders	= 0x00C70DA0;
	static const UInt32 RenderWorldSceneGraph		= 0x00692290;
	static const UInt32 RenderFirstPerson			= 0x00698B30;
	static const UInt32 LoadForm					= 0x0043B4A0;
	static const UInt32 SetCameraState				= 0x006533D0;
	static const UInt32 ManageButtonEvent			= 0x00840BE0;
	static const UInt32 SetCameraPosition			= 0x0083F690;
	static const UInt32 SetFurnitureCameraState		= 0x0083D6E0;
	static const UInt32 ProcessSleepWaitMenu		= 0x00887F90;
	static const UInt32 ShowSleepWaitMenu			= 0x00887B20;
	static const UInt32 ServeSentence				= 0x0074B7E0;
};

class Jumpers {
public:
	struct CreateDevice {
		static const UInt32 Hook	= 0x00CD8B6F;
		static const UInt32 Return	= 0x00CD8B74;
	};
	struct SetRegionEditorName {
		static const UInt32 Hook	= 0x0048BEE4;
		static const UInt32 Return	= 0x0048BEEA;
	};
	struct SetWeatherEditorName {
		static const UInt32 Hook	= 0x004EF358;
		static const UInt32 Return	= 0x004EF35E;
	};
	struct RenderInterface {
		static const UInt32 Hook	= 0x00A5CB57;
		static const UInt32 Return	= 0x00A5CB5C;
		static const UInt32 Method	= 0x00A623F0;
	};
	struct RenderingGeometry {
		static const UInt32 Hook	= 0x00CAFFC0;
		static const UInt32 Return	= 0x00CAFFC5;
	};
	struct Shadows {
		static const UInt32 SetShadowDistanceHook			= 0x00CBB140;
		static const UInt32 SetShadowDistanceReturn			= 0x00CBB146;
		static const UInt32 SetShadowDistanceShaderHook		= 0x00CB7365;
		static const UInt32 SetShadowDistanceShaderReturn	= 0x00CB736D;
	};
	struct HitEvent {
		static const UInt32 Hook	= 0x006E4837;
		static const UInt32 Return	= 0x006E483E;
	};
};
static CommandTable	commandTable;
static void* PapyrusFunctions[2];

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

static bool RegisterPapyrusCommands(VMClassRegistry* registry) {

	registry->RegisterFunction(new PapyrusFunction2<BSFixedString, bool>(CommandPrefix"SetExtraEffectEnabled", CommandPrefix"Commands", PapyrusFunctions[0], registry));
	registry->RegisterFunction(new PapyrusFunction5<BSFixedString, float, float, float, float>(CommandPrefix"SetCustomConstant", CommandPrefix"Commands", PapyrusFunctions[1], registry));
	return true;

}

class CommandManagerBase {
public:

	void RegisterCommands(const PluginInterface* Interface, void** CommandExecuters, CommandInfo** CommandInfos, int CommandInfoSize, void** PapyrusCommands) {

		PapyrusInterface* PInterface = (PapyrusInterface*)Interface->QueryInterface(PluginInterface::InterfaceType::kInterface_Papyrus);

		PapyrusFunctions[0] = PapyrusCommands[0];
		PapyrusFunctions[1] = PapyrusCommands[1];
		PInterface->Register(RegisterPapyrusCommands);
		
		//DetourTransactionBegin();
		//DetourUpdateThread(GetCurrentThread());
		//DetourAttach(&(PVOID&)ToggleConsole, &TrackToggleConsole);
		//DetourTransactionCommit();

	}

};

class SettingManagerBase {
public:
	
	void SetTextureAndHDR(TESWeatherEx* WeatherEx, char* UpperLayer, char* LowerLayer, float* HDR) {}

	void SetWindowedMode(UInt8 Fullscreen) {

		if (!Fullscreen) {
			SafeWrite32(0x012CF5F8, 0);
			SafeWrite32(0x012CF604, 0);
			SafeWrite32(0x0069D832, WS_POPUP);
			SafeWrite32(0x0069D877, WS_POPUP | WS_VISIBLE);
		}

	}

};

class RenderManagerBase : public NiDX9Renderer {
public:
	
	IDirect3DSurface9* CreateHDRRenderTarget() {
		
		return NULL;

	}

};

class ShaderManagerBase {
public:

	static int GetShader(const char* Name, NiD3DVertexShader*** Shader, NiD3DVertexShader** AdditionalShader, int AdditionalShaderSize) {

		int Size = 0;

		if (!strcmp(Name, "Water")) {
			*Shader = AdditionalShader;
			Size = AdditionalShaderSize;
		}
		return Size;

	}

	static int GetShader(const char* Name, NiD3DPixelShader*** Shader, NiD3DPixelShader** AdditionalShader, int AdditionalShaderSize) {

		int Size = 0;

		if (!strcmp(Name, "Water")) {
			*Shader = AdditionalShader;
			Size = AdditionalShaderSize;
		}
		return Size;

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