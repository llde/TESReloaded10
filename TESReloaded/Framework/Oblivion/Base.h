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
	static const UInt32 NewActorAnimData			= 0x00473EB0;
	static const UInt32 DisposeActorAnimData		= 0x00475B60;
	static const UInt32 AddAnimation				= 0x00474070;
	static const UInt32 AddSingle					= 0x00470BA0;
	static const UInt32 AddMultiple					= 0x00471930;
	static const UInt32 GetAnimGroupSequenceSingle	= 0x00471710;
	static const UInt32 GetAnimGroupSequenceMultiple= 0x00470BF0;
	static const UInt32 NewAnimSequenceMultiple		= 0x00473D90;
	static const UInt32 ApplyActorAnimData			= 0x00471F20;
	static const UInt32 LoadAnimGroup				= 0x0051B490;
	static const UInt32 ToggleCamera				= 0x0066C580;
	static const UInt32 ToggleBody					= 0x00664F70;
	static const UInt32 SetDialogCamera				= 0x0066C6F0;
	static const UInt32 SetAimingZoom				= 0x00666670;
	static const UInt32 UpdateCameraCollisions		= 0x0065F080;
	static const UInt32 NewHighProcess				= 0x00628EE0;
	static const UInt32 ManageItem					= 0x005ABBC0;
	static const UInt32 ProcessAction				= 0x005FCAB0;
	static const UInt32 ProcessControlAttack		= 0x0065E960;
	static const UInt32 AttackHandling				= 0x005FEBF0;
	static const UInt32 GetEquippedWeaponData		= 0x0064B240;
	static const UInt32 SetEquippedWeaponData		= 0x00658550;
	static const UInt32 EquipItem					= 0x00489C30;
	static const UInt32 UnequipItem					= 0x0048A540;
	static const UInt32 EquipWeapon					= 0x004E1900;
	static const UInt32 UnequipWeapon				= 0x004DC5B0;
	static const UInt32 EquipShield					= 0x004E1B40;
	static const UInt32 EquipLight					= 0x004E1C70;
	static const UInt32 UnequipLight				= 0x004DCAB0;
	static const UInt32 GetEquippedLightData		= 0x0064B270;
	static const UInt32 HideEquipment				= 0x005E7230;
	static const UInt32 SaveGame					= 0x00485730;
	static const UInt32 ServeSentence				= 0x00670700;
	static const UInt32 RemoveWornItems				= 0x0064BAC0;
	static const UInt32 ProcessSleepWaitMenu		= 0x005D7090;
	static const UInt32 CloseSleepWaitMenu			= 0x005D6A10;
	static const UInt32 ShowSleepWaitMenu			= 0x0057B420;
	static const UInt32 UpdateFlyCam				= 0x006643A0;
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

	void SetWindowedMode(UInt8 Fullscreen) {

		if (!Fullscreen) {
			SafeWrite32(kRectStyle, WS_POPUP);
			SafeWrite32(kWindowStyle, WS_POPUP | WS_VISIBLE);
		}

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