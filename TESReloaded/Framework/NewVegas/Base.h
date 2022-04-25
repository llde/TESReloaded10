#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting					= 0x00C44280;
	static const UInt32 WriteSetting				= 0x00C43E90;
	static const UInt32 LoadGame					= 0x00847DF0;
	static const UInt32 NewMain						= 0x0086C160;
	static const UInt32 InitializeRenderer			= 0x0086D500;
	static const UInt32 NewTES						= 0x0044FB20;
	static const UInt32 NewPlayerCharacter			= 0x00938180;
	static const UInt32 NewSceneGraph				= 0x00878610;
	static const UInt32 NewMainDataHandler			= 0x0045D270;
	static const UInt32 NewMenuInterfaceManager		= 0x0070A130;
	static const UInt32 NewQueuedModelLoader		= 0x00442650;
	static const UInt32 CreateVertexShader			= 0x00BE0FE0;
	static const UInt32 CreatePixelShader			= 0x00BE1750;
	static const UInt32 SetShaderPackage			= 0x00B4F710;
	static const UInt32 Render						= 0x008706B0;
	static const UInt32 SetShaders					= 0x00BE1F90;
	static const UInt32 SetSamplerState				= 0x00E910A0;
	static const UInt32 ProcessImageSpaceShaders	= 0x00B55AC0;
	static const UInt32 RenderWorldSceneGraph		= 0x00873200;
	static const UInt32 RenderFirstPerson			= 0x00875110;
	static const UInt32 RenderReflections			= 0x004E1BC0;
	static const UInt32 RenderPipboy				= 0x008761E0;
	static const UInt32 GetWaterHeightLOD			= 0x0045CD80;
	static const UInt32 ShowDetectorWindow			= 0x004D61B0;
	static const UInt32 LoadForm					= 0x004601D0;
	static const UInt32 UpdateFlyCam				= 0x0094A8C0;
};

class Jumpers {
public:
	struct CreateDevice {
		static const UInt32 Hook	= 0x00E731FF;
		static const UInt32 Return	= 0x00E73204;
	};
	struct SetRegionEditorName {
		static const UInt32 Hook	= 0x004F0D29;
		static const UInt32 Return	= 0x004F0E1B;
	};
	struct SetWeatherEditorName {
		static const UInt32 Hook	= 0x00580B54;
		static const UInt32 Return	= 0x0058130E;
	};
	struct DetectorWindow {
		static const UInt32 CreateTreeViewHook		= 0x004D6476;
		static const UInt32 CreateTreeViewReturn	= 0x004D647F;
		static const UInt32 DumpAttributesHook		= 0x004D6A2E;
		static const UInt32 DumpAttributesReturn	= 0x004D69C5;
		static const UInt32 ConsoleCommandHook		= 0x00872D09;
		static const UInt32 ConsoleCommandReturn	= 0x00872D10;
		static const UInt32 SetNodeName				= 0x004D678A;
	};
	struct RenderInterface {
		static const UInt32 Hook	= 0x007144D3;
		static const UInt32 Return	= 0x007144D8;
		static const UInt32 Method	= 0x007134D0;
	};
	struct Shadows {
		static const UInt32 RenderShadowMapHook			= 0x00870C39;
		static const UInt32 RenderShadowMapReturn		= 0x00870C41;
		static const UInt32 AddCastShadowFlagHook		= 0x0050DD06;
		static const UInt32 AddCastShadowFlagReturn		= 0x0050DD0B;
		static const UInt32 LeavesNodeNameHook			= 0x0066A115;
		static const UInt32 LeavesNodeNameReturn		= 0x0066A11E;
	};
	struct SetTileShaderConstants {
		static const UInt32 Hook	= 0x00BCAAD7;
		static const UInt32 Return	= 0x00BCAADE;
	};
	struct MainMenuMusic {
		static const UInt32 Fix1	= 0x007D0B48;
		static const UInt32 Fix2	= 0x007D6CE7;
	};
	struct MultiBoundWaterHeight {
		static const UInt32 Fix1	= 0x006FAE04;
		static const UInt32 Fix2	= 0x006FAF50;
	};
	struct FlyCam {
		static const UInt32 UpdateForwardFlyCamHook		= 0x0094ABDF;
		static const UInt32 UpdateForwardFlyCamReturn	= 0x0094ABEB;
		static const UInt32 UpdateBackwardFlyCamHook	= 0x0094ABFB;
		static const UInt32 UpdateBackwardFlyCamReturn	= 0x0094AC07;
		static const UInt32 UpdateRightFlyCamHook		= 0x0094AC17;
		static const UInt32 UpdateRightFlyCamReturn		= 0x0094AC29;
		static const UInt32 UpdateLeftFlyCamHook		= 0x0094AC39;
		static const UInt32 UpdateLeftFlyCamReturn		= 0x0094AC4B;
	};
};

class CommandManagerBase {
public:
	
	void RegisterCommands(const PluginInterface* Interface, void** CommandExecuters, CommandInfo** CommandInfos, int CommandInfoSize, void** PapyrusCommands) {

		Interface->SetOpcodeBase(0x3000);
		for (int i = 0; i < CommandInfoSize; i++) {
			Interface->RegisterCommand(CommandInfos[i]);
		}

	}

};

class SettingManagerBase {
public:
	
	void SetTextureAndHDR(TESWeatherEx* WeatherEx, char* UpperLayer, char* LowerLayer, float* HDR) {

		WeatherEx->textureLayers[0].ddsPath.Set(UpperLayer);
		WeatherEx->textureLayers[1].ddsPath.Set(LowerLayer);

	}
	
	void SetWindowedMode(UInt8 Fullscreen) {

		if (!Fullscreen) {
			SafeWrite32(0x0086AF04, WS_POPUP);
			SafeWrite32(0x0086AF2F, WS_POPUP | WS_VISIBLE);
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

		BSShader** Shaders = (BSShader**)0x011F9548;
		NiD3DVertexShader** ShadowLightVertexShaders = (NiD3DVertexShader**)0x011FDE5C;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17];
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			*Shader = AdditionalShader;
			Size = AdditionalShaderSize;
		}
		else if (!strcmp(Name, "Terrain") || !strcmp(Name, "ExtraShaders")) {
			*Shader = ShadowLightVertexShaders;
			Size = 103;
		}
		return Size;

	}

	static int GetShader(const char* Name, NiD3DPixelShader*** Shader, NiD3DPixelShader** AdditionalShader, int AdditionalShaderSize) {

		BSShader** Shaders = (BSShader**)0x011F9548;
		NiD3DPixelShader** ShadowLightPixelShaders = (NiD3DPixelShader**)0x011FDB08;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17];
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			*Shader = AdditionalShader;
			Size = AdditionalShaderSize;
		}
		else if (!strcmp(Name, "Terrain") || !strcmp(Name, "ExtraShaders")) {
			*Shader = ShadowLightPixelShaders;
			Size = 160;
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
