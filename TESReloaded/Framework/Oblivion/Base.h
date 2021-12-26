#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting					= 0x004A8800;
	static const UInt32 WriteSetting				= 0x004A85F0;
	static const UInt32 LoadGame					= 0x00465860;
	static const UInt32 NewMain						= 0x00404A00;
	static const UInt32 InitializeRenderer			= 0x004052F0;
	static const UInt32 NewTES						= 0x00441970;
	static const UInt32 NewPlayerCharacter			= 0x0066A740;
	static const UInt32 NewSceneGraph				= 0x004114E0;
	static const UInt32 NewMainDataHandler			= 0x00446D80;
	static const UInt32 NewMenuInterfaceManager		= 0x005802B0;
	static const UInt32 NewQueuedModelLoader		= 0x0043E950;
	static const UInt32 CreateVertexShader			= 0x008014E0;
	static const UInt32 CreatePixelShader			= 0x00801C90;
	static const UInt32 SetShaderPackage			= 0x007B45F0;
	static const UInt32 Render						= 0x0040C830;
	static const UInt32 ProcessImageSpaceShaders	= 0x007B48E0;
	static const UInt32 ShowDetectorWindow			= 0x00496CB0;
	static const UInt32 SetupShaderPrograms			= 0x0077A1F0;
	static const UInt32 EndTargetGroup				= 0x007AAA30;
	static const UInt32 HDRRender					= 0x007BDFC0;
	static const UInt32 WaterHeightMapRender		= 0x007E17D0;
	static const UInt32 FarPlane					= 0x00410EE0;
	static const UInt32 SetSamplerState				= 0x0077B610;
	static const UInt32 RenderReflections			= 0x0049BEF0;
	static const UInt32 WaterCullingProcess			= 0x0049CBF0;
	static const UInt32 SaveGameScreenshot			= 0x00411B70;
	static const UInt32 LoadForm					= 0x00447050;
	static const UInt32 RunScript					= 0x004402F0;
};

class CommandManagerBase {
public:
	
	void RegisterCommands(const PluginInterface* Interface, void* CommandExecuters[], CommandInfo* CommandInfos[], int CommandInfoSize) {

		CommandTableInterface* CommandsInterface = (CommandTableInterface*)Interface->QueryInterface(PluginInterface::kInterface_CommandTable);

		CommandsInterface->GetByName("IsThirdPerson")->execute = CommandExecuters[0];
		Interface->SetOpcodeBase(0x3000);
		for (int i = 0; i < CommandInfoSize; i++) {
			Interface->RegisterCommand(CommandInfos[i]);
		}

	}

};

class SettingManagerBase {
public:

	bool IsMatching(char* Versioning) {

		return Versioning[0] == '1';

	}
	
	void SetTextureAndHDR(TESWeatherEx* WeatherEx, char* UpperLayer, char* LowerLayer, float* HDR) {
		
		WeatherEx->textureLayers[0].ddsPath.Set(UpperLayer);
		WeatherEx->textureLayers[1].ddsPath.Set(LowerLayer);
		memcpy(WeatherEx->hdrInfo, HDR, 0x38);

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