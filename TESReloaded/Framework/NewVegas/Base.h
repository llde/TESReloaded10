#pragma once

class Hooks {
public:

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
			WaterShaderHeightMap* S = (WaterShaderHeightMap*)Shaders[19]->Shader;
			*Shader = &S->Vertex;
			Size = sizeof(S->Vertex) / 4;
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
			WaterShaderHeightMap* S = (WaterShaderHeightMap*)Shaders[19]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
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