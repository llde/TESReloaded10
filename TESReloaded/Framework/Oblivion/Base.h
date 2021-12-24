#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting				= 0x004A8800;
	static const UInt32 WriteSetting			= 0x004A85F0;
	static const UInt32 LoadGame				= 0x00465860;
	static const UInt32 NewMain					= 0x00404A00;
	static const UInt32 InitializeRenderer		= 0x004052F0;
	static const UInt32 NewTES					= 0x00441970;
	static const UInt32 NewPlayerCharacter		= 0x0066A740;
	static const UInt32 NewSceneGraph			= 0x004114E0;
	static const UInt32 NewMainDataHandler		= 0x00446D80;
	static const UInt32 NewMenuInterfaceManager = 0x005802B0;
	static const UInt32 NewQueuedModelLoader	= 0x0043E950;
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