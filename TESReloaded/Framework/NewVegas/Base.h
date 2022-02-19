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
};

class Jumpers {
public:
	struct CreateDevice {
		static const UInt32 Hook	= 0x00E731FF;
		static const UInt32 Return	= 0x00E73204;
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

	bool IsMatching(char* Versioning) {

		return Versioning[2] == '1';

	}
	
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

	static int GetShader(const char* Name, NiD3DVertexShader*** Shader, NiD3DVertexShader** AdditionalShader) {

		BSShader** Shaders = (BSShader**)0x011F9548;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17];
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			*Shader = AdditionalShader;
			Size = sizeof(AdditionalShader) / 4;
		}
		return Size;

	}

	static int GetShader(const char* Name, NiD3DPixelShader*** Shader, NiD3DPixelShader** AdditionalShader) {

		BSShader** Shaders = (BSShader**)0x011F9548;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17];
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			*Shader = AdditionalShader;
			Size = sizeof(AdditionalShader) / 4;
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