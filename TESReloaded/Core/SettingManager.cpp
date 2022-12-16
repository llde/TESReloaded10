void SettingManager::Configuration::Init() {

	char Filename[MAX_PATH];

	Config = NULL;
	ConfigB = NULL;
	FileSize = 0;
	GetCurrentDirectoryA(MAX_PATH, Filename);
	strcat(Filename, SettingsFile);
	std::ifstream ConfigurationFile(Filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (ConfigurationFile.is_open()) {
		std::streamoff Size = ConfigurationFile.tellg();
		FileSize = Size + (Size / 3);
		Config = new char[FileSize]; memset(Config, NULL, FileSize);
		ConfigB = new char[FileSize]; memset(ConfigB, NULL, FileSize);
		ConfigurationFile.seekg(0, std::ios::beg);
		ConfigurationFile.read(Config, Size);
		ConfigurationFile.close();
	}

}

SettingManager::Configuration::SectionPosition SettingManager::Configuration::GoToSection(const char* Section, const char* FromPosition) {

	SectionPosition SectionPosition = { NULL, NULL, true };
	char* Finder = NULL;
	char* KeyPositionR = NULL;
	char SectionB[80];
	char ToFind[80];
	bool RootSection = (FromPosition ? false : true);

	SectionPosition.Start = (char*)(FromPosition ? FromPosition : Config);
	SectionPosition.End = SectionPosition.Start + strlen(Config);
	if (Section) {
		strcpy(SectionB, Section);
		Finder = strtok(SectionB, ".");
		while (Finder != NULL) {
			strcpy(ToFind, "<");
			if (RootSection) strcat(ToFind, "_");
			strcat(ToFind, Finder);
			strcat(ToFind, ">");
			KeyPositionR = strstr(SectionPosition.Start, ToFind);
			if (!KeyPositionR) {
				SectionPosition.Found = false;
				break;
			}
			KeyPositionR++;
			SectionPosition.Start = KeyPositionR;
			KeyPositionR = NULL;
			strcpy(ToFind, "</");
			if (RootSection) { strcat(ToFind, "_"); RootSection = false; }
			strcat(ToFind, Finder);
			strcat(ToFind, ">");
			Finder = strtok(NULL, ".");
		}
		SectionPosition.End = strstr(SectionPosition.Start, ToFind);
	}
	return SectionPosition;

}

bool SettingManager::Configuration::FillNode(ConfigNode* Node, const char* Section, const char* Key) {

	char ToFind[80];
	char AttributeValue[80];
	char* KeyPosition = NULL;
	SectionPosition SectionPosition = GoToSection(Section);
	bool Result = false;
	
	if (SectionPosition.Found) {
		strcpy(ToFind, "<");
		strcat(ToFind, Key);
		strcat(ToFind, " ");
		KeyPosition = strstr(SectionPosition.Start, ToFind);
		if (KeyPosition && KeyPosition < SectionPosition.End) {
			strcpy(Node->Section, Section);
			strcpy(Node->Key, Key);
			strcpy(Node->Value, GetAttribute(KeyPosition, "Value", AttributeValue));
			Node->Type = atoi(GetAttribute(KeyPosition, "Type", AttributeValue));
			Node->Reboot = atoi(GetAttribute(KeyPosition, "Reboot", AttributeValue));
			Result = true;
		}
	}
	return Result;

}

char* SettingManager::Configuration::GetAttribute(char* KeyPosition, const char* Attribute, char* AttributeValue) {

	char* AttributePositionStart = NULL;
	char* AttributePositionEnd = NULL;
	char ToFind[80];
	size_t Size = 0;

	strcpy(ToFind, Attribute);
	strcat(ToFind, "=");
	AttributePositionStart = strstr(KeyPosition, ToFind);
	strcpy(ToFind, "\"");
	AttributePositionStart = strstr(AttributePositionStart, ToFind);
	AttributePositionStart++;
	AttributePositionEnd = strstr(AttributePositionStart, ToFind);
	Size = AttributePositionEnd - AttributePositionStart;
	strncpy(AttributeValue, AttributePositionStart, Size);
	AttributeValue[Size] = NULL;
	return AttributeValue;

}

void SettingManager::Configuration::FillSections(StringList* Sections, const char* ParentSection) {

	SettingManager::Configuration::SectionPosition SectionPosition = GoToSection(ParentSection);
	SettingManager::Configuration::SectionPosition InnerSectionPosition = SectionPosition;
	char* SectionPositionStart = SectionPosition.Start;
	char* SectionPositionEnd = NULL;
	char ToFind[80];
	char SectionName[80];
	size_t Size = 0;

	Sections->clear();
	if (SectionPosition.Found) {
		while (true) {
			strcpy(ToFind, "<");
			SectionPositionStart = strstr(SectionPositionStart, ToFind);
			if (SectionPositionStart == NULL || SectionPositionStart == SectionPosition.End) break;
			SectionPositionStart++;
			strcpy(ToFind, ">");
			SectionPositionEnd = strstr(SectionPositionStart, ToFind);
			Size = SectionPositionEnd - SectionPositionStart;
			strncpy(SectionName, SectionPositionStart, Size);
			SectionName[Size] = NULL;
			if (!memcmp(SectionPositionStart, "_", 1))
				Sections->push_back(SectionName + 1);
			else
				Sections->push_back(SectionName);
			InnerSectionPosition = GoToSection(SectionName, InnerSectionPosition.Start);
			SectionPositionStart = InnerSectionPosition.End + 1;
		}			


		std::sort(Sections->begin(), Sections->end());
	}

}

void SettingManager::Configuration::FillSettings(SettingList* Nodes, const char* Section) {

	Configuration::ConfigNode Node;
	SettingManager::Configuration::SectionPosition SectionPosition = GoToSection(Section);
	char* KeyPositionStart = SectionPosition.Start;
	char* KeyPositionEnd = NULL;
	char ToFind[80];
	char KeyName[80];
	size_t Size = 0;

	Nodes->clear();
	if (SectionPosition.Found) {
		while (true) {
			strcpy(ToFind, "<");
			KeyPositionStart = strstr(KeyPositionStart, ToFind);
			if (KeyPositionStart == NULL || KeyPositionStart == SectionPosition.End) break;
			KeyPositionStart++;
			strcpy(ToFind, " ");
			KeyPositionEnd = strstr(KeyPositionStart, ToFind);
			Size = KeyPositionEnd - KeyPositionStart;
			strncpy(KeyName, KeyPositionStart, Size);
			KeyName[Size] = NULL;
			FillNode(&Node, Section, KeyName);
			Nodes->push_back(Node);
			strcpy(ToFind, "/>");
			KeyPositionStart = strstr(KeyPositionStart, ToFind);
		}
		std::sort(Nodes->begin(), Nodes->end());
	}

}

void SettingManager::Configuration::SetValue(ConfigNode* Node) {

	char ToFind[80];
	char* KeyPosition = NULL;
	SettingManager::Configuration::SectionPosition SectionPosition = GoToSection(Node->Section);
	
	if (SectionPosition.Found) {
		strcpy(ToFind, "<");
		strcat(ToFind, Node->Key);
		KeyPosition = strstr(SectionPosition.Start, ToFind);
		SetAttribute(KeyPosition, "Value", Node->Value);
	}

}

void SettingManager::Configuration::SetAttribute(char* KeyPosition, const char* Attribute, const char* Value) {

	char* AttributePositionStart = NULL;
	char* AttributePositionEnd = NULL;
	char ToFind[80];

	strcpy(ToFind, Attribute);
	strcat(ToFind, "=");
	AttributePositionStart = strstr(KeyPosition, ToFind);
	strcpy(ToFind, "\"");
	AttributePositionStart = strstr(AttributePositionStart, ToFind);
	AttributePositionStart++;
	AttributePositionEnd = strstr(AttributePositionStart, ToFind);
	strncpy(ConfigB, Config, AttributePositionStart - Config);
	strcat(ConfigB, Value);
	strncat(ConfigB, AttributePositionEnd, Config + strlen(Config) - AttributePositionEnd);
	strcpy(Config, ConfigB);
	memset(ConfigB, NULL, FileSize);

}

void SettingManager::Configuration::CreateWeatherSection(const char* WeatherName, TESWeather* Weather) {

	char Section[4096];
	char SectionNode[256];
	char Value[80] = { NULL };
	SettingManager::Configuration::SectionPosition SectionPosition = GoToSection("Weathers");

	if (SectionPosition.Found) {
		strcpy(Section, "<");
		strcat(Section, WeatherName);
		strcat(Section, ">");
		strcat(Section, "<Colors>");
		for (UInt32 x = 0; x < TESWeather::kNumColorTypes; x++) {
			Value[0] = NULL;
			for (UInt32 y = 0; y < TESWeather::kNumTimeOfDay; y++) {
				strcat(Value, ToString(Weather->colors[x].colors[y].r).c_str());
				strcat(Value, ",");
				strcat(Value, ToString(Weather->colors[x].colors[y].g).c_str());
				strcat(Value, ",");
				strcat(Value, ToString(Weather->colors[x].colors[y].b).c_str());
				if (y < TESWeather::kNumTimeOfDay - 1) strcat(Value, " ");
			}
			sprintf(SectionNode, "<Color%i Value=\"%s\" Type=\"3\" Reboot=\"0\" Info=\"\" />", x, Value); strcat(Section, SectionNode);
		}
		strcat(Section, "</Colors>");
		strcat(Section, "<HDR>");
		Value[0] = NULL;
		for (UInt32 i = 0; i < 14; i++) {
			strcat(Value, ToString(Weather->GetHDR(i)).c_str());
			if (i < 13) strcat(Value, " ");
		}
		sprintf(SectionNode, "<HDR Value=\"%s\" Type=\"3\" Reboot=\"0\" Info=\"\" />", Value); strcat(Section, SectionNode);
		strcat(Section, "</HDR>");
		strcat(Section, "<Main>");
		sprintf(SectionNode, "<CloudSpeedLower Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetCloudSpeedLower()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<CloudSpeedUpper Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetCloudSpeedUpper()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<FogFarDay Value=\"%.1f\" Type=\"2\" Reboot=\"0\" Info=\"\" />", Weather->GetFogDayFar()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<FogFarNight Value=\"%.1f\" Type=\"2\" Reboot=\"0\" Info=\"\" />", Weather->GetFogNightFar()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<FogNearDay Value=\"%.1f\" Type=\"2\" Reboot=\"0\" Info=\"\" />", Weather->GetFogDayNear()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<FogNearNight Value=\"%.1f\" Type=\"2\" Reboot=\"0\" Info=\"\" />", Weather->GetFogNightNear()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<SunDamage Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetSunDamage()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<SunGlare Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetSunGlare()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<TransDelta Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetTransDelta()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<WindSpeed Value=\"%i\" Type=\"1\" Reboot=\"0\" Info=\"\" />", Weather->GetWindSpeed()); strcat(Section, SectionNode);
		sprintf(SectionNode, "<UpperLayer Value=\"%s\" Type=\"3\" Reboot=\"0\" Info=\"\" />", Weather->textureLayers[0].ddsPath.m_data); strcat(Section, SectionNode);
		sprintf(SectionNode, "<LowerLayer Value=\"%s\" Type=\"3\" Reboot=\"0\" Info=\"\" />", Weather->textureLayers[1].ddsPath.m_data); strcat(Section, SectionNode);
		strcat(Section, "</Main>");
		strcat(Section, "</");
		strcat(Section, WeatherName);
		strcat(Section, ">");
		strncpy(ConfigB, Config, SectionPosition.End - Config);
		strcat(ConfigB, Section);
		strncat(ConfigB, SectionPosition.End, Config + strlen(Config) - SectionPosition.End);
		strcpy(Config, ConfigB);
		memset(ConfigB, NULL, FileSize);
	}

}

void SettingManager::Initialize() {

	Logger::Log("Starting the settings manager...");
	TheSettingManager = new SettingManager();

	TheSettingManager->GameLoading = false;

}

void SettingManager::LoadSettings() {

	StringList List;
	StringList InnerList;
	SettingsWaterStruct SW{};
	SettingsColoringStruct SC{};
	SettingsWeatherStruct SE{};
	char Value[80];

	if (!Config.Config) Config.Init();
	SettingsMain.Main.RemoveUnderwater = GetSettingI("Main.Main.Water", "RemoveUnderwater");
	SettingsMain.Main.RemovePrecipitations = GetSettingI("Main.Main.Precipitations", "RemovePrecipitations");
	SettingsMain.Main.MemoryHeapManagement = GetSettingI("Main.Main.Memory", "HeapManagement");
	SettingsMain.Main.MemoryTextureManagement = GetSettingI("Main.Main.Memory", "TextureManagement");
	SettingsMain.Main.AnisotropicFilter = GetSettingI("Main.Main.Misc", "AnisotropicFilter");
	SettingsMain.Main.FarPlaneDistance = GetSettingF("Main.Main.Misc", "FarPlaneDistance");
	SettingsMain.Main.ScreenshotKey = GetSettingI("Main.Main.Misc", "ScreenshotKey");
	SettingsMain.Main.ReplaceIntro = GetSettingI("Main.Main.Misc", "ReplaceIntro");
	SettingsMain.Main.SkipFog = GetSettingI("Main.Main.Misc", "SkipFog");

	SettingsMain.FrameRate.SmartControl = GetSettingI("Main.FrameRate.SmartControl", "SmartControl");
	SettingsMain.FrameRate.SmartControlFPS = GetSettingI("Main.FrameRate.SmartControl", "SmartControlFPS");
	SettingsMain.FrameRate.FlowControl = GetSettingF("Main.FrameRate.SmartControl", "FlowControl");
	SettingsMain.FrameRate.SmartBackgroundProcess = GetSettingI("Main.FrameRate.Stuttering", "SmartBackgroundProcess");
	SettingsMain.FrameRate.BackgroundThreadPriority = GetSettingI("Main.FrameRate.Stuttering", "BackgroundThreadPriority");

	SettingsMain.CullingProcess.EnableCulling = GetSettingI("Main.CullingProcess.Main", "EnableCulling");
	SettingsMain.CullingProcess.EnableReflectionCulling = GetSettingI("Main.CullingProcess.Main", "EnableReflectionCulling");
	SettingsMain.CullingProcess.CullMinSize = GetSettingF("Main.CullingProcess.Main", "CullMinSize");
	SettingsMain.CullingProcess.CullMinSizeReflection = GetSettingF("Main.CullingProcess.Main", "CullMinSizeReflection");

	SettingsMain.OcclusionCulling.Enabled = GetSettingI("Main.OcclusionCulling.Main", "Enabled");
	SettingsMain.OcclusionCulling.OcclusionMapRatio = GetSettingI("Main.OcclusionCulling.Main", "OcclusionMapRatio");
	SettingsMain.OcclusionCulling.OccludingStatic = GetSettingI("Main.OcclusionCulling.Main", "OccludingStatic");
	SettingsMain.OcclusionCulling.OccludedStatic = GetSettingI("Main.OcclusionCulling.Main", "OccludedStatic");
	SettingsMain.OcclusionCulling.OccludedDistantStatic = GetSettingI("Main.OcclusionCulling.Main", "OccludedDistantStatic");
	SettingsMain.OcclusionCulling.OccludedDistantStaticIC = GetSettingI("Main.OcclusionCulling.Main", "OccludedDistantStaticIC");
	SettingsMain.OcclusionCulling.OccludingStaticMin = GetSettingF("Main.OcclusionCulling.Main", "OccludingStaticMin");
	SettingsMain.OcclusionCulling.OccludedStaticMin = GetSettingF("Main.OcclusionCulling.Main", "OccludedStaticMin");
	SettingsMain.OcclusionCulling.OccludedStaticMax = GetSettingF("Main.OcclusionCulling.Main", "OccludedStaticMax");
	SettingsMain.OcclusionCulling.OccludedDistantStaticMax = GetSettingF("Main.OcclusionCulling.Main", "OccludedDistantStaticMax");

	SettingsMain.CameraMode.Enabled = GetSettingI("Main.CameraMode.Main", "Enabled");
	SettingsMain.CameraMode.Crosshair = GetSettingI("Main.CameraMode.Main", "Crosshair");
	SettingsMain.CameraMode.ChasingFirst = GetSettingI("Main.CameraMode.Main", "ChasingFirst");
	SettingsMain.CameraMode.ChasingThird = GetSettingI("Main.CameraMode.Main", "ChasingThird");
	SettingsMain.CameraMode.FoV = GetSettingF("Main.CameraMode.Main", "FoV");
	SettingsMain.CameraMode.Offset.x = GetSettingF("Main.CameraMode.Positioning", "OffsetX");
	SettingsMain.CameraMode.Offset.y = GetSettingF("Main.CameraMode.Positioning", "OffsetY");
	SettingsMain.CameraMode.Offset.z = GetSettingF("Main.CameraMode.Positioning", "OffsetZ");
	SettingsMain.CameraMode.DialogOffset.x = GetSettingF("Main.CameraMode.Positioning", "DialogOffsetX");
	SettingsMain.CameraMode.DialogOffset.y = GetSettingF("Main.CameraMode.Positioning", "DialogOffsetY");
	SettingsMain.CameraMode.DialogOffset.z = GetSettingF("Main.CameraMode.Positioning", "DialogOffsetZ");
	SettingsMain.CameraMode.AimingOffset.x = GetSettingF("Main.CameraMode.Positioning", "AimingOffsetX");
	SettingsMain.CameraMode.AimingOffset.y = GetSettingF("Main.CameraMode.Positioning", "AimingOffsetY");
	SettingsMain.CameraMode.AimingOffset.z = GetSettingF("Main.CameraMode.Positioning", "AimingOffsetZ");

	SettingsMain.IKFoot.Enabled = GetSettingI("Main.IKFoot.Main", "Enabled");
	SettingsMain.IKFoot.Coeff = GetSettingF("Main.IKFoot.Main", "Coeff");
	SettingsMain.IKFoot.CoeffThigh = GetSettingF("Main.IKFoot.Main", "CoeffThigh");
	SettingsMain.IKFoot.CoeffCalf = GetSettingF("Main.IKFoot.Main", "CoeffCalf");
	SettingsMain.IKFoot.CoeffFoot = GetSettingF("Main.IKFoot.Main", "CoeffFoot");
	SettingsMain.IKFoot.CoeffToe = GetSettingF("Main.IKFoot.Main", "CoeffToe");

	SettingsMain.EquipmentMode.Enabled = GetSettingI("Main.EquipmentMode.Main", "Enabled");
	SettingsMain.EquipmentMode.TorchKey = GetSettingI("Main.EquipmentMode.Main", "TorchKey");
	SettingsMain.EquipmentMode.SleepingEquipment = GetSettingI("Main.EquipmentMode.Main", "SleepingEquipment");
	SettingsMain.EquipmentMode.SwimmingEquipment = GetSettingI("Main.EquipmentMode.Main", "SwimmingEquipment");
	SettingsMain.EquipmentMode.CombatEquipmentKey = GetSettingI("Main.EquipmentMode.Main", "CombatEquipmentKey");
	SettingsMain.EquipmentMode.DualBlockDelay = GetSettingF("Main.EquipmentMode.Main", "DualBlockDelay");
	SettingsMain.EquipmentMode.ShieldOnBackPos.x = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackPosX");
	SettingsMain.EquipmentMode.ShieldOnBackPos.y = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackPosY");
	SettingsMain.EquipmentMode.ShieldOnBackPos.z = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackPosZ");
	SettingsMain.EquipmentMode.ShieldOnBackRot.x = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackRotX");
	SettingsMain.EquipmentMode.ShieldOnBackRot.y = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackRotY");
	SettingsMain.EquipmentMode.ShieldOnBackRot.z = GetSettingF("Main.EquipmentMode.Positioning", "ShieldOnBackRotZ");
	SettingsMain.EquipmentMode.WeaponOnBackPos.x = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackPosX");
	SettingsMain.EquipmentMode.WeaponOnBackPos.y = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackPosY");
	SettingsMain.EquipmentMode.WeaponOnBackPos.z = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackPosZ");
	SettingsMain.EquipmentMode.WeaponOnBackRot.x = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackRotX");
	SettingsMain.EquipmentMode.WeaponOnBackRot.y = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackRotY");
	SettingsMain.EquipmentMode.WeaponOnBackRot.z = GetSettingF("Main.EquipmentMode.Positioning", "WeaponOnBackRotZ");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackPos.x = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackPosX");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackPos.y = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackPosY");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackPos.z = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackPosZ");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackRot.x = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackRotX");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackRot.y = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackRotY");
	SettingsMain.EquipmentMode.TwoHandWeaponOnBackRot.z = GetSettingF("Main.EquipmentMode.Positioning", "TwoHandWeaponOnBackRotZ");
	SettingsMain.EquipmentMode.BowOnBackPos.x = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackPosX");
	SettingsMain.EquipmentMode.BowOnBackPos.y = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackPosY");
	SettingsMain.EquipmentMode.BowOnBackPos.z = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackPosZ");
	SettingsMain.EquipmentMode.BowOnBackRot.x = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackRotX");
	SettingsMain.EquipmentMode.BowOnBackRot.y = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackRotY");
	SettingsMain.EquipmentMode.BowOnBackRot.z = GetSettingF("Main.EquipmentMode.Positioning", "BowOnBackRotZ");
	SettingsMain.EquipmentMode.StaffOnBackPos.x = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackPosX");
	SettingsMain.EquipmentMode.StaffOnBackPos.y = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackPosY");
	SettingsMain.EquipmentMode.StaffOnBackPos.z = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackPosZ");
	SettingsMain.EquipmentMode.StaffOnBackRot.x = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackRotX");
	SettingsMain.EquipmentMode.StaffOnBackRot.y = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackRotY");
	SettingsMain.EquipmentMode.StaffOnBackRot.z = GetSettingF("Main.EquipmentMode.Positioning", "StaffOnBackRotZ");
	SettingsMain.EquipmentMode.TorchOnBeltPos.x = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltPosX");
	SettingsMain.EquipmentMode.TorchOnBeltPos.y = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltPosY");
	SettingsMain.EquipmentMode.TorchOnBeltPos.z = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltPosZ");
	SettingsMain.EquipmentMode.TorchOnBeltRot.x = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltRotX");
	SettingsMain.EquipmentMode.TorchOnBeltRot.y = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltRotY");
	SettingsMain.EquipmentMode.TorchOnBeltRot.z = GetSettingF("Main.EquipmentMode.Positioning", "TorchOnBeltRotZ");


	SettingsMain.MountedCombat.Enabled = GetSettingI("Main.MountedCombat.Main", "Enabled");
	SettingsMain.MountedCombat.WeaponOnBackPos.x = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackPosX");
	SettingsMain.MountedCombat.WeaponOnBackPos.y = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackPosY");
	SettingsMain.MountedCombat.WeaponOnBackPos.z = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackPosZ");
	SettingsMain.MountedCombat.WeaponOnBackRot.x = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackRotX");
	SettingsMain.MountedCombat.WeaponOnBackRot.y = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackRotY");
	SettingsMain.MountedCombat.WeaponOnBackRot.z = GetSettingF("Main.MountedCombat.Positioning", "WeaponOnBackRotZ");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackPos.x = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackPosX");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackPos.y = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackPosY");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackPos.z = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackPosZ");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackRot.x = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackRotX");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackRot.y = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackRotY");
	SettingsMain.MountedCombat.TwoHandWeaponOnBackRot.z = GetSettingF("Main.MountedCombat.Positioning", "TwoHandWeaponOnBackRotZ");
	SettingsMain.MountedCombat.BowOnBackPos.x = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackPosX");
	SettingsMain.MountedCombat.BowOnBackPos.y = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackPosY");
	SettingsMain.MountedCombat.BowOnBackPos.z = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackPosZ");
	SettingsMain.MountedCombat.BowOnBackRot.x = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackRotX");
	SettingsMain.MountedCombat.BowOnBackRot.y = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackRotY");
	SettingsMain.MountedCombat.BowOnBackRot.z = GetSettingF("Main.MountedCombat.Positioning", "BowOnBackRotZ");
	SettingsMain.MountedCombat.StaffOnBackPos.x = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackPosX");
	SettingsMain.MountedCombat.StaffOnBackPos.y = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackPosY");
	SettingsMain.MountedCombat.StaffOnBackPos.z = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackPosZ");
	SettingsMain.MountedCombat.StaffOnBackRot.x = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackRotX");
	SettingsMain.MountedCombat.StaffOnBackRot.y = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackRotY");
	SettingsMain.MountedCombat.StaffOnBackRot.z = GetSettingF("Main.MountedCombat.Positioning", "StaffOnBackRotZ");

	SettingsMain.GrassMode.Enabled = GetSettingI("Main.GrassMode.Main", "Enabled");

	SettingsMain.SleepingMode.Enabled = GetSettingI("Main.SleepingMode.Main", "Enabled");
	SettingsMain.SleepingMode.Mode = GetSettingI("Main.SleepingMode.Main", "Mode");

	SettingsMain.WeatherMode.Enabled = GetSettingI("Main.WeatherMode.Main", "Enabled");
	SettingsMain.WeatherMode.CoeffNight.x = GetSettingF("Main.WeatherMode.General", "CoeffNightR");
	SettingsMain.WeatherMode.CoeffNight.y = GetSettingF("Main.WeatherMode.General", "CoeffNightG");
	SettingsMain.WeatherMode.CoeffNight.z = GetSettingF("Main.WeatherMode.General", "CoeffNightB");
	SettingsMain.WeatherMode.CoeffFog.x = GetSettingF("Main.WeatherMode.General", "CoeffFogR");
	SettingsMain.WeatherMode.CoeffFog.y = GetSettingF("Main.WeatherMode.General", "CoeffFogG");
	SettingsMain.WeatherMode.CoeffFog.z = GetSettingF("Main.WeatherMode.General", "CoeffFogB");
	SettingsMain.WeatherMode.CoeffSun.x = GetSettingF("Main.WeatherMode.General", "CoeffSunR");
	SettingsMain.WeatherMode.CoeffSun.y = GetSettingF("Main.WeatherMode.General", "CoeffSunG");
	SettingsMain.WeatherMode.CoeffSun.z = GetSettingF("Main.WeatherMode.General", "CoeffSunB");

	SettingsMain.ShadowMode.NearQuality = GetSettingF("Main.ShadowMode.Main", "NearQuality");

	SettingsMain.Shaders.Water = GetSettingI("Shaders.Water.Status", "Enabled");
	SettingsMain.Shaders.Grass = GetSettingI("Shaders.Grass.Status", "Enabled");
	SettingsMain.Shaders.HDR = GetSettingI("Shaders.HDR.Status", "Enabled");
	SettingsMain.Shaders.POM = GetSettingI("Shaders.POM.Status", "Enabled");
	SettingsMain.Shaders.Skin = GetSettingI("Shaders.Skin.Status", "Enabled");
	SettingsMain.Shaders.Terrain = GetSettingI("Shaders.Terrain.Status", "Enabled");
	SettingsMain.Shaders.Blood = GetSettingI("Shaders.Blood.Status", "Enabled");
	SettingsMain.Shaders.NightEye = GetSettingI("Shaders.NightEye.Status", "Enabled");
	SettingsMain.Shaders.Extra = GetSettingI("Shaders.ExtraShaders.Status", "Enabled");

	SettingsMain.Effects.AmbientOcclusion = GetSettingI("Shaders.AmbientOcclusion.Status", "Enabled");
	SettingsMain.Effects.Underwater = GetSettingI("Shaders.Underwater.Status", "Enabled");
	SettingsMain.Effects.WaterLens = GetSettingI("Shaders.WaterLens.Status", "Enabled");
	SettingsMain.Effects.GodRays = GetSettingI("Shaders.GodRays.Status", "Enabled");
	SettingsMain.Effects.DepthOfField = GetSettingI("Shaders.DepthOfField.Status", "Enabled");
	SettingsMain.Effects.Coloring = GetSettingI("Shaders.Coloring.Status", "Enabled");
	SettingsMain.Effects.Cinema = GetSettingI("Shaders.Cinema.Status", "Enabled");
	SettingsMain.Effects.Bloom = GetSettingI("Shaders.Bloom.Status", "Enabled");
	SettingsMain.Effects.SnowAccumulation = GetSettingI("Shaders.SnowAccumulation.Status", "Enabled");
	SettingsMain.Effects.BloodLens = GetSettingI("Shaders.BloodLens.Status", "Enabled");
	SettingsMain.Effects.MotionBlur = GetSettingI("Shaders.MotionBlur.Status", "Enabled");
	SettingsMain.Effects.LowHF = GetSettingI("Shaders.LowHF.Status", "Enabled");
	SettingsMain.Effects.WetWorld = GetSettingI("Shaders.WetWorld.Status", "Enabled");
	SettingsMain.Effects.Sharpening = GetSettingI("Shaders.Sharpening.Status", "Enabled");
	SettingsMain.Effects.VolumetricFog = GetSettingI("Shaders.VolumetricFog.Status", "Enabled");
	SettingsMain.Effects.Rain = GetSettingI("Shaders.Precipitations.Status", "Enabled");
	SettingsMain.Effects.Snow = GetSettingI("Shaders.Precipitations.Status", "Enabled"); //TODO change in the INI
	SettingsMain.Effects.ShadowsExteriors = GetSettingI("Shaders.ShadowsExteriors.Status", "PostProcess");
	SettingsMain.Effects.ShadowsInteriors = GetSettingI("Shaders.ShadowsInteriors.Status", "PostProcess");
	SettingsMain.Effects.Specular = GetSettingI("Shaders.Specular.Status", "Enabled");
	SettingsMain.Effects.Extra = GetSettingI("Shaders.ExtraEffects.Status", "Enabled");

	strcpy(SettingsMain.Menu.TextFont, GetSettingS("Main.Menu.Style", "TextFont", Value));
	SettingsMain.Menu.TextSize = GetSettingI("Main.Menu.Style", "TextSize");
	strcpy(SettingsMain.Menu.TextFontStatus, GetSettingS("Main.Menu.Style", "TextFontStatus", Value));
	SettingsMain.Menu.TextSizeStatus = GetSettingI("Main.Menu.Style", "TextSizeStatus");
	FillFromString(GetSettingS("Main.Menu.Style", "TextColorNormal", Value), ",", SettingsMain.Menu.TextColorNormal);
	FillFromString(GetSettingS("Main.Menu.Style", "TextShadowColorNormal", Value), ",", SettingsMain.Menu.TextShadowColorNormal);
	FillFromString(GetSettingS("Main.Menu.Style", "TextColorSelected", Value), ",", SettingsMain.Menu.TextColorSelected);
	FillFromString(GetSettingS("Main.Menu.Style", "TextShadowColorSelected", Value), ",", SettingsMain.Menu.TextShadowColorSelected);
	FillFromString(GetSettingS("Main.Menu.Style", "TextColorEditing", Value), ",", SettingsMain.Menu.TextColorEditing);
	FillFromString(GetSettingS("Main.Menu.Style", "TextShadowColorEditing", Value), ",", SettingsMain.Menu.TextShadowColorEditing);
	FillFromString(GetSettingS("Main.Menu.Style", "TextColorEnabled", Value), ",", SettingsMain.Menu.TextColorEnabled);
	FillFromString(GetSettingS("Main.Menu.Style", "TextShadowColorEnabled", Value), ",", SettingsMain.Menu.TextShadowColorEnabled);
	SettingsMain.Menu.PositionX = GetSettingI("Main.Menu.Style", "PositionX");
	SettingsMain.Menu.PositionY = GetSettingI("Main.Menu.Style", "PositionY");
	SettingsMain.Menu.TitleColumnSize = GetSettingI("Main.Menu.Style", "TitleColumnSize");
	SettingsMain.Menu.MainItemColumnSize = GetSettingI("Main.Menu.Style", "MainItemColumnSize");
	SettingsMain.Menu.ItemColumnSize = GetSettingI("Main.Menu.Style", "ItemColumnSize");
	SettingsMain.Menu.RowSpace = GetSettingI("Main.Menu.Style", "RowSpace");
	SettingsMain.Menu.RowsPerPage = GetSettingI("Main.Menu.Style", "RowsPerPage");
	SettingsMain.Menu.KeyEnable = GetSettingI("Main.Menu.Keys", "KeyEnable");
	SettingsMain.Menu.KeyUp = GetSettingI("Main.Menu.Keys", "KeyUp");
	SettingsMain.Menu.KeyDown = GetSettingI("Main.Menu.Keys", "KeyDown");
	SettingsMain.Menu.KeyLeft = GetSettingI("Main.Menu.Keys", "KeyLeft");
	SettingsMain.Menu.KeyRight = GetSettingI("Main.Menu.Keys", "KeyRight");
	SettingsMain.Menu.KeyPageUp = GetSettingI("Main.Menu.Keys", "KeyPageUp");
	SettingsMain.Menu.KeyPageDown = GetSettingI("Main.Menu.Keys", "KeyPageDown");
	SettingsMain.Menu.KeyAdd = GetSettingI("Main.Menu.Keys", "KeyAdd");
	SettingsMain.Menu.KeySubtract = GetSettingI("Main.Menu.Keys", "KeySubtract");
	SettingsMain.Menu.KeySave = GetSettingI("Main.Menu.Keys", "KeySave");
	SettingsMain.Menu.KeyEditing = GetSettingI("Main.Menu.Keys", "KeyEditing");

	SettingsMain.LowHFSound.HealthEnabled = GetSettingI("Main.LowHFSound.Main", "HealthEnabled");
	SettingsMain.LowHFSound.FatigueEnabled = GetSettingI("Main.LowHFSound.Main", "FatigueEnabled");
	SettingsMain.LowHFSound.HealthCoeff = GetSettingF("Main.LowHFSound.Main", "HealthCoeff");
	SettingsMain.LowHFSound.FatigueCoeff = GetSettingF("Main.LowHFSound.Main", "FatigueCoeff");

	SettingsMain.Purger.Enabled = GetSettingI("Main.Purger.Main", "Enabled");
	SettingsMain.Purger.Time = GetSettingI("Main.Purger.Main", "Time");
	SettingsMain.Purger.PurgeTextures = GetSettingI("Main.Purger.Main", "PurgeTextures");
	SettingsMain.Purger.PurgeCells = GetSettingI("Main.Purger.Main", "PurgeCells");
	SettingsMain.Purger.Key = GetSettingI("Main.Purger.Main", "Key");

	SettingsMain.Gravity.Enabled = GetSettingI("Main.Gravity.Main", "Enabled");
	SettingsMain.Gravity.Value = GetSettingF("Main.Gravity.Main", "Value");

	SettingsMain.Dodge.Enabled = GetSettingI("Main.Dodge.Main", "Enabled");
	SettingsMain.Dodge.AcrobaticsLevel = GetSettingI("Main.Dodge.Main", "AcrobaticsLevel");
	SettingsMain.Dodge.DoubleTap = GetSettingI("Main.Dodge.Main", "DoubleTap");
	SettingsMain.Dodge.DoubleTapTime = GetSettingF("Main.Dodge.Main", "DoubleTapTime");

	SettingsMain.FlyCam.Enabled = GetSettingI("Main.FlyCam.Main", "Enabled");
	SettingsMain.FlyCam.ScrollMultiplier = GetSettingF("Main.FlyCam.Main", "ScrollMultiplier");
	SettingsMain.FlyCam.KeyAdd = GetSettingI("Main.FlyCam.Main", "KeyAdd");
	SettingsMain.FlyCam.KeySubtract = GetSettingI("Main.FlyCam.Main", "KeySubtract");
	SettingsMain.FlyCam.StepValue = GetSettingF("Main.FlyCam.Main", "StepValue");

	SettingsMain.Develop.CompileShaders = GetSettingI("Main.Develop.Main", "CompileShaders");
	SettingsMain.Develop.CompileEffects = GetSettingI("Main.Develop.Main", "CompileEffects");
	SettingsMain.Develop.DebugMode = GetSettingI("Main.Develop.Main", "DebugMode");
	SettingsMain.Develop.TraceShaders = GetSettingI("Main.Develop.Main", "TraceShaders");


	Config.FillSections(&List, "Weathers");
	for (StringList::iterator Iter = List.begin(); Iter != List.end(); ++Iter) {
		const char* WeatherSection = Iter->c_str();
		char SectionName[80];
		char Key[12];
		UInt8 Color[3];
		strcpy(SectionName, "Weathers.");
		strcat(SectionName, WeatherSection);
		strcat(SectionName, ".Colors");
		for (int x = 0; x < TESWeather::kNumColorTypes; x++) {
			sprintf(Key, "Color%i", x);
			SplitString(GetSettingS(SectionName, Key, Value), " ", &InnerList);
			for (int y = 0; y < TESWeather::kNumTimeOfDay; y++) {
				FillFromString(InnerList[y].c_str(), ",", Color);
				SE.Colors[x].colors[y].r = Color[0];
				SE.Colors[x].colors[y].g = Color[1];
				SE.Colors[x].colors[y].b = Color[2];
			}
		}
		strcpy(SectionName, "Weathers.");
		strcat(SectionName, WeatherSection);
		strcat(SectionName, ".HDR");
		FillFromString(GetSettingS(SectionName, "HDR", Value), " ", SE.HDR);
		strcpy(SectionName, "Weathers.");
		strcat(SectionName, WeatherSection);
		strcat(SectionName, ".Main");
		SE.FogNearDay = GetSettingF(SectionName, "FogNearDay");
		SE.FogNearNight = GetSettingF(SectionName, "FogNearNight");
		SE.FogFarDay = GetSettingF(SectionName, "FogFarDay");
		SE.FogFarNight = GetSettingF(SectionName, "FogFarNight");
		SE.WindSpeed = GetSettingI(SectionName, "WindSpeed");
		SE.CloudSpeedLower = GetSettingI(SectionName, "CloudSpeedLower");
		SE.CloudSpeedUpper = GetSettingI(SectionName, "CloudSpeedUpper");
		SE.TransDelta = GetSettingI(SectionName, "TransDelta");
		SE.SunGlare = GetSettingI(SectionName, "SunGlare");
		SE.SunDamage = GetSettingI(SectionName, "SunDamage");
		strcpy(SE.LowerLayer, GetSettingS(SectionName, "LowerLayer", Value));
		strcpy(SE.UpperLayer, GetSettingS(SectionName, "UpperLayer", Value));
		SettingsWeather[WeatherSection] = SE;
	}


	SettingsAmbientOcclusionExteriors.Enabled = GetSettingI("Shaders.AmbientOcclusion.Exteriors", "Enabled");
	SettingsAmbientOcclusionExteriors.Samples = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "Samples");
	SettingsAmbientOcclusionExteriors.StrengthMultiplier = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "StrengthMultiplier");
	SettingsAmbientOcclusionExteriors.ClampStrength = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "ClampStrength");
	SettingsAmbientOcclusionExteriors.AngleBias = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "AngleBias");
	SettingsAmbientOcclusionExteriors.Range = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "Range");
	SettingsAmbientOcclusionExteriors.LumThreshold = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "LumThreshold");
	SettingsAmbientOcclusionExteriors.BlurDropThreshold = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "BlurDropThreshold");
	SettingsAmbientOcclusionExteriors.BlurRadiusMultiplier = GetSettingF("Shaders.AmbientOcclusion.Exteriors", "BlurRadiusMultiplier");

	SettingsAmbientOcclusionInteriors.Enabled = GetSettingI("Shaders.AmbientOcclusion.Interiors", "Enabled");
	SettingsAmbientOcclusionInteriors.Samples = GetSettingF("Shaders.AmbientOcclusion.Interiors", "Samples");
	SettingsAmbientOcclusionInteriors.StrengthMultiplier = GetSettingF("Shaders.AmbientOcclusion.Interiors", "StrengthMultiplier");
	SettingsAmbientOcclusionInteriors.ClampStrength = GetSettingF("Shaders.AmbientOcclusion.Interiors", "ClampStrength");
	SettingsAmbientOcclusionInteriors.AngleBias = GetSettingF("Shaders.AmbientOcclusion.Interiors", "AngleBias");
	SettingsAmbientOcclusionInteriors.Range = GetSettingF("Shaders.AmbientOcclusion.Interiors", "Range");
	SettingsAmbientOcclusionInteriors.LumThreshold = GetSettingF("Shaders.AmbientOcclusion.Interiors", "LumThreshold");
	SettingsAmbientOcclusionInteriors.BlurDropThreshold = GetSettingF("Shaders.AmbientOcclusion.Interiors", "BlurDropThreshold");
	SettingsAmbientOcclusionInteriors.BlurRadiusMultiplier = GetSettingF("Shaders.AmbientOcclusion.Interiors", "BlurRadiusMultiplier");


	SettingsBloodLens.Chance = GetSettingF("Shaders.BloodLens.Main", "Chance");
	SettingsBloodLens.ColorR = GetSettingF("Shaders.BloodLens.Main", "ColorR");
	SettingsBloodLens.ColorG = GetSettingF("Shaders.BloodLens.Main", "ColorG");
	SettingsBloodLens.ColorB = GetSettingF("Shaders.BloodLens.Main", "ColorB");
	SettingsBloodLens.Intensity = GetSettingF("Shaders.BloodLens.Main", "Intensity");
	SettingsBloodLens.Time = GetSettingF("Shaders.BloodLens.Main", "Time");


	SettingsBloomExteriors.BloomIntensity = GetSettingF("Shaders.Bloom.Exteriors", "BloomIntensity");
	SettingsBloomExteriors.OriginalIntensity = GetSettingF("Shaders.Bloom.Exteriors", "OriginalIntensity");
	SettingsBloomExteriors.BloomSaturation = GetSettingF("Shaders.Bloom.Exteriors", "BloomSaturation");
	SettingsBloomExteriors.OriginalSaturation = GetSettingF("Shaders.Bloom.Exteriors", "OriginalSaturation");
	SettingsBloomExteriors.Luminance = GetSettingF("Shaders.Bloom.Exteriors", "Luminance");
	SettingsBloomExteriors.MiddleGray = GetSettingF("Shaders.Bloom.Exteriors", "MiddleGray");
	SettingsBloomExteriors.WhiteCutOff = GetSettingF("Shaders.Bloom.Exteriors", "WhiteCutOff");

	SettingsBloomInteriors.BloomIntensity = GetSettingF("Shaders.Bloom.Interiors", "BloomIntensity");
	SettingsBloomInteriors.OriginalIntensity = GetSettingF("Shaders.Bloom.Interiors", "OriginalIntensity");
	SettingsBloomInteriors.BloomSaturation = GetSettingF("Shaders.Bloom.Interiors", "BloomSaturation");
	SettingsBloomInteriors.OriginalSaturation = GetSettingF("Shaders.Bloom.Interiors", "OriginalSaturation");
	SettingsBloomInteriors.Luminance = GetSettingF("Shaders.Bloom.Interiors", "Luminance");
	SettingsBloomInteriors.MiddleGray = GetSettingF("Shaders.Bloom.Interiors", "MiddleGray");
	SettingsBloomInteriors.WhiteCutOff = GetSettingF("Shaders.Bloom.Interiors", "WhiteCutOff");


	SettingsCinema.Mode = GetSettingI("Shaders.Cinema.Main", "Mode");
	SettingsCinema.AspectRatio = GetSettingF("Shaders.Cinema.Main", "AspectRatio");
	SettingsCinema.VignetteRadius = GetSettingF("Shaders.Cinema.Main", "VignetteRadius");
	SettingsCinema.VignetteDarkness = GetSettingF("Shaders.Cinema.Main", "VignetteDarkness");


	Config.FillSections(&List, "Shaders.Coloring");
	for (StringList::iterator Iter = List.begin(); Iter != List.end(); ++Iter) {
		const char* ColoringSection = Iter->c_str();
		if (strcmp(ColoringSection, "Status")) {
			char SectionName[80];
			strcpy(SectionName, "Shaders.Coloring.");
			strcat(SectionName, ColoringSection);
			SC.Strength = GetSettingF(SectionName, "Strength");
			SC.BaseGamma = GetSettingF(SectionName, "BaseGamma");
			SC.Fade = GetSettingF(SectionName, "Fade");
			SC.Contrast = GetSettingF(SectionName, "Contrast");
			SC.Saturation = GetSettingF(SectionName, "Saturation");
			SC.Bleach = GetSettingF(SectionName, "Bleach");
			SC.BleachLuma = GetSettingF(SectionName, "BleachLuma");
			SC.ColorCurve = GetSettingF(SectionName, "ColorCurve");
			SC.ColorCurveR = GetSettingF(SectionName, "ColorCurveR");
			SC.ColorCurveG = GetSettingF(SectionName, "ColorCurveG");
			SC.ColorCurveB = GetSettingF(SectionName, "ColorCurveB");
			SC.EffectGamma = GetSettingF(SectionName, "EffectGamma");
			SC.EffectGammaR = GetSettingF(SectionName, "EffectGammaR");
			SC.EffectGammaG = GetSettingF(SectionName, "EffectGammaG");
			SC.EffectGammaB = GetSettingF(SectionName, "EffectGammaB");
			SC.Linearization = GetSettingF(SectionName, "Linearization");
			SettingsColoring[ColoringSection] = SC;
		}
	}


	SettingsDepthOfFieldFirstPersonView.Enabled = GetSettingI("Shaders.DepthOfField.FirstPersonView", "Enabled");
	SettingsDepthOfFieldFirstPersonView.Mode = GetSettingI("Shaders.DepthOfField.FirstPersonView", "Mode");
	SettingsDepthOfFieldFirstPersonView.DistantBlur = GetSettingI("Shaders.DepthOfField.FirstPersonView", "DistantBlur");
	SettingsDepthOfFieldFirstPersonView.DistantBlurStartRange = GetSettingF("Shaders.DepthOfField.FirstPersonView", "DistantBlurStartRange");
	SettingsDepthOfFieldFirstPersonView.DistantBlurEndRange = GetSettingF("Shaders.DepthOfField.FirstPersonView", "DistantBlurEndRange");
	SettingsDepthOfFieldFirstPersonView.BaseBlurRadius = GetSettingF("Shaders.DepthOfField.FirstPersonView", "BaseBlurRadius");
	SettingsDepthOfFieldFirstPersonView.BlurFallOff = GetSettingF("Shaders.DepthOfField.FirstPersonView", "BlurFallOff");
	SettingsDepthOfFieldFirstPersonView.Radius = GetSettingF("Shaders.DepthOfField.FirstPersonView", "Radius");
	SettingsDepthOfFieldFirstPersonView.DiameterRange = GetSettingF("Shaders.DepthOfField.FirstPersonView", "DiameterRange");
	SettingsDepthOfFieldFirstPersonView.NearBlurCutOff = GetSettingF("Shaders.DepthOfField.FirstPersonView", "NearBlurCutOff");

	SettingsDepthOfFieldThirdPersonView.Enabled = GetSettingI("Shaders.DepthOfField.ThirdPersonView", "Enabled");
	SettingsDepthOfFieldThirdPersonView.Mode = GetSettingI("Shaders.DepthOfField.ThirdPersonView", "Mode");
	SettingsDepthOfFieldThirdPersonView.DistantBlur = GetSettingI("Shaders.DepthOfField.ThirdPersonView", "DistantBlur");
	SettingsDepthOfFieldThirdPersonView.DistantBlurStartRange = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "DistantBlurStartRange");
	SettingsDepthOfFieldThirdPersonView.DistantBlurEndRange = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "DistantBlurEndRange");
	SettingsDepthOfFieldThirdPersonView.BaseBlurRadius = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "BaseBlurRadius");
	SettingsDepthOfFieldThirdPersonView.BlurFallOff = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "BlurFallOff");
	SettingsDepthOfFieldThirdPersonView.Radius = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "Radius");
	SettingsDepthOfFieldThirdPersonView.DiameterRange = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "DiameterRange");
	SettingsDepthOfFieldThirdPersonView.NearBlurCutOff = GetSettingF("Shaders.DepthOfField.ThirdPersonView", "NearBlurCutOff");

	SettingsDepthOfFieldVanityView.Enabled = GetSettingI("Shaders.DepthOfField.VanityView", "Enabled");
	SettingsDepthOfFieldVanityView.Mode = GetSettingI("Shaders.DepthOfField.VanityView", "Mode");
	SettingsDepthOfFieldVanityView.DistantBlur = GetSettingI("Shaders.DepthOfField.VanityView", "DistantBlur");
	SettingsDepthOfFieldVanityView.DistantBlurStartRange = GetSettingF("Shaders.DepthOfField.VanityView", "DistantBlurStartRange");
	SettingsDepthOfFieldVanityView.DistantBlurEndRange = GetSettingF("Shaders.DepthOfField.VanityView", "DistantBlurEndRange");
	SettingsDepthOfFieldVanityView.BaseBlurRadius = GetSettingF("Shaders.DepthOfField.VanityView", "BaseBlurRadius");
	SettingsDepthOfFieldVanityView.BlurFallOff = GetSettingF("Shaders.DepthOfField.VanityView", "BlurFallOff");
	SettingsDepthOfFieldVanityView.Radius = GetSettingF("Shaders.DepthOfField.VanityView", "Radius");
	SettingsDepthOfFieldVanityView.DiameterRange = GetSettingF("Shaders.DepthOfField.VanityView", "DiameterRange");
	SettingsDepthOfFieldVanityView.NearBlurCutOff = GetSettingF("Shaders.DepthOfField.VanityView", "NearBlurCutOff");


	SettingsGodRays.TimeEnabled = GetSettingI("Shaders.GodRays.Main", "TimeEnabled");
	SettingsGodRays.SunGlareEnabled = GetSettingI("Shaders.GodRays.Main", "SunGlareEnabled");
	SettingsGodRays.LightShaftPasses = GetSettingI("Shaders.GodRays.Main", "LightShaftPasses");
	SettingsGodRays.RayIntensity = GetSettingF("Shaders.GodRays.Main", "RayIntensity");
	SettingsGodRays.RayLength = GetSettingF("Shaders.GodRays.Main", "RayLength");
	SettingsGodRays.RayDensity = GetSettingF("Shaders.GodRays.Main", "RayDensity");
	SettingsGodRays.RayVisibility = GetSettingF("Shaders.GodRays.Main", "RayVisibility");
	SettingsGodRays.Luminance = GetSettingF("Shaders.GodRays.Main", "Luminance");
	SettingsGodRays.GlobalMultiplier = GetSettingF("Shaders.GodRays.Main", "GlobalMultiplier");
	SettingsGodRays.RayR = GetSettingF("Shaders.GodRays.Main", "RayR");
	SettingsGodRays.RayG = GetSettingF("Shaders.GodRays.Main", "RayG");
	SettingsGodRays.RayB = GetSettingF("Shaders.GodRays.Main", "RayB");
	SettingsGodRays.Saturate = GetSettingF("Shaders.GodRays.Main", "Saturate");


	SettingsGrass.WindEnabled = GetSettingI("Shaders.Grass.Main", "WindEnabled");
	SettingsGrass.GrassDensity = GetSettingI("Shaders.Grass.Main", "GrassDensity");
	SettingsGrass.WindCoefficient = GetSettingF("Shaders.Grass.Main", "WindCoefficient");
	SettingsGrass.ScaleX = GetSettingF("Shaders.Grass.Main", "ScaleX");
	SettingsGrass.ScaleY = GetSettingF("Shaders.Grass.Main", "ScaleY");
	SettingsGrass.ScaleZ = GetSettingF("Shaders.Grass.Main", "ScaleZ");
	SettingsGrass.MinDistance = GetSettingF("Shaders.Grass.Main", "MinDistance");
	SettingsGrass.MaxDistance = GetSettingF("Shaders.Grass.Main", "MaxDistance");


	SettingsHDR.ToneMapping = GetSettingF("Shaders.HDR.Main", "ToneMapping");
	SettingsHDR.ToneMappingBlur = GetSettingF("Shaders.HDR.Main", "ToneMappingBlur");
	SettingsHDR.ToneMappingColor = GetSettingF("Shaders.HDR.Main", "ToneMappingColor");
	SettingsHDR.Linearization = GetSettingF("Shaders.HDR.Main", "Linearization");


	SettingsLowHF.HealthLimit = GetSettingF("Shaders.LowHF.Main", "HealthLimit");
	SettingsLowHF.FatigueLimit = GetSettingF("Shaders.LowHF.Main", "FatigueLimit");
	SettingsLowHF.LumaMultiplier = GetSettingF("Shaders.LowHF.Main", "LumaMultiplier");
	SettingsLowHF.BlurMultiplier = GetSettingF("Shaders.LowHF.Main", "BlurMultiplier");
	SettingsLowHF.VignetteMultiplier = GetSettingF("Shaders.LowHF.Main", "VignetteMultiplier");
	SettingsLowHF.DarknessMultiplier = GetSettingF("Shaders.LowHF.Main", "DarknessMultiplier");


	SettingsMotionBlurFirstPersonView.Enabled = GetSettingI("Shaders.MotionBlur.FirstPersonView", "Enabled");
	SettingsMotionBlurFirstPersonView.GaussianWeight = GetSettingF("Shaders.MotionBlur.FirstPersonView", "GaussianWeight");
	SettingsMotionBlurFirstPersonView.BlurScale = GetSettingF("Shaders.MotionBlur.FirstPersonView", "BlurScale");
	SettingsMotionBlurFirstPersonView.BlurOffsetMax = GetSettingF("Shaders.MotionBlur.FirstPersonView", "BlurOffsetMax");
	SettingsMotionBlurFirstPersonView.BlurCutOff = GetSettingF("Shaders.MotionBlur.FirstPersonView", "BlurCutOff");

	SettingsMotionBlurThirdPersonView.Enabled = GetSettingI("Shaders.MotionBlur.ThirdPersonView", "Enabled");
	SettingsMotionBlurThirdPersonView.GaussianWeight = GetSettingF("Shaders.MotionBlur.ThirdPersonView", "GaussianWeight");
	SettingsMotionBlurThirdPersonView.BlurScale = GetSettingF("Shaders.MotionBlur.ThirdPersonView", "BlurScale");
	SettingsMotionBlurThirdPersonView.BlurOffsetMax = GetSettingF("Shaders.MotionBlur.ThirdPersonView", "BlurOffsetMax");
	SettingsMotionBlurThirdPersonView.BlurCutOff = GetSettingF("Shaders.MotionBlur.ThirdPersonView", "BlurCutOff");


	SettingsPOM.HeightMapScale = GetSettingF("Shaders.POM.Main", "HeightMapScale");
	SettingsPOM.MinSamples = GetSettingF("Shaders.POM.Main", "MinSamples");
	SettingsPOM.MaxSamples = GetSettingF("Shaders.POM.Main", "MaxSamples");


	SettingsPrecipitations.Rain.DepthStep = GetSettingF("Shaders.Rain.Main", "DepthStep");
	SettingsPrecipitations.Rain.Speed = GetSettingF("Shaders.Rain.Main", "Speed");
	SettingsPrecipitations.Snow.DepthStep = GetSettingF("Shaders.Snow.Main", "DepthStep");
	SettingsPrecipitations.Snow.Flakes = GetSettingF("Shaders.Snow.Main", "Flakes");
	SettingsPrecipitations.Snow.Speed = GetSettingF("Shaders.Snow.Main", "Speed");
	SettingsPrecipitations.WetWorld.Amount = GetSettingF("Shaders.Precipitations.WetWorld", "Amount");
	SettingsPrecipitations.WetWorld.Increase = GetSettingF("Shaders.Precipitations.WetWorld", "Increase");
	SettingsPrecipitations.WetWorld.Decrease = GetSettingF("Shaders.Precipitations.WetWorld", "Decrease");
	SettingsPrecipitations.WetWorld.PuddleCoeff_R = GetSettingF("Shaders.Precipitations.WetWorld", "PuddleCoeff_R");
	SettingsPrecipitations.WetWorld.PuddleCoeff_G = GetSettingF("Shaders.Precipitations.WetWorld", "PuddleCoeff_G");
	SettingsPrecipitations.WetWorld.PuddleCoeff_B = GetSettingF("Shaders.Precipitations.WetWorld", "PuddleCoeff_B");
	SettingsPrecipitations.WetWorld.PuddleSpecularMultiplier = GetSettingF("Shaders.Precipitations.WetWorld", "PuddleSpecularMultiplier");
	SettingsPrecipitations.SnowAccumulation.Amount = GetSettingF("Shaders.Precipitations.SnowAccumulation", "Amount");
	SettingsPrecipitations.SnowAccumulation.Increase = GetSettingF("Shaders.Precipitations.SnowAccumulation", "Increase");
	SettingsPrecipitations.SnowAccumulation.Decrease = GetSettingF("Shaders.Precipitations.SnowAccumulation", "Decrease");
	SettingsPrecipitations.SnowAccumulation.SunPower = GetSettingF("Shaders.Precipitations.SnowAccumulation", "SunPower");
	SettingsPrecipitations.SnowAccumulation.BlurNormDropThreshhold = GetSettingF("Shaders.Precipitations.SnowAccumulation", "BlurNormDropThreshhold");
	SettingsPrecipitations.SnowAccumulation.BlurRadiusMultiplier = GetSettingF("Shaders.Precipitations.SnowAccumulation", "BlurRadiusMultiplier");

	// Specular effect settings
	SettingsSpecular.Exterior.Strength = GetSettingF("Shaders.Specular.Exterior", "Strength");
	SettingsSpecular.Exterior.BlurMultiplier = GetSettingF("Shaders.Specular.Exterior", "BlurMultiplier");
	SettingsSpecular.Exterior.Glossiness = GetSettingF("Shaders.Specular.Exterior", "Glossiness");
	SettingsSpecular.Exterior.DistanceFade = GetSettingF("Shaders.Specular.Exterior", "DistanceFade");

	SettingsSpecular.Rain.Strength = GetSettingF("Shaders.Specular.Rain", "Strength");
	SettingsSpecular.Rain.BlurMultiplier = GetSettingF("Shaders.Specular.Rain", "BlurMultiplier");
	SettingsSpecular.Rain.Glossiness = GetSettingF("Shaders.Specular.Rain", "Glossiness");
	SettingsSpecular.Rain.DistanceFade = GetSettingF("Shaders.Specular.Rain", "DistanceFade");

	// Generic exterior shadows settings
	SettingsShadows.Exteriors.Enabled = GetSettingI("Shaders.ShadowsExteriors.Main", "Enabled");
	SettingsShadows.Exteriors.Quality = GetSettingI("Shaders.ShadowsExteriors.Main", "Quality");
	SettingsShadows.Exteriors.Darkness = GetSettingF("Shaders.ShadowsExteriors.Main", "Darkness");
	SettingsShadows.Exteriors.NightMinDarkness = GetSettingF("Shaders.ShadowsExteriors.Main", "NightMinDarkness");
	SettingsShadows.Exteriors.ShadowRadius = GetSettingF("Shaders.ShadowsExteriors.Main", "ShadowsRadius");
	SettingsShadows.Exteriors.ShadowMapResolution = GetSettingI("Shaders.ShadowsExteriors.Main", "ShadowMapResolution");
	SettingsShadows.Exteriors.ShadowMapFarPlane = GetSettingF("Shaders.ShadowsExteriors.Main", "ShadowMapFarPlane");
	SettingsShadows.Exteriors.ShadowMode = GetSettingI("Shaders.ShadowsExteriors.Main", "ShadowMode");
	SettingsShadows.Exteriors.BlurShadowMaps = GetSettingI("Shaders.ShadowsExteriors.Main", "BlurShadowMaps");

	SettingsShadows.ScreenSpace.Enabled = GetSettingI("Shaders.ShadowsExteriors.ScreenSpace", "Enabled");
	SettingsShadows.ScreenSpace.BlurRadius = GetSettingI("Shaders.ShadowsExteriors.ScreenSpace", "BlurRadius");
	SettingsShadows.ScreenSpace.RenderDistance = GetSettingI("Shaders.ShadowsExteriors.ScreenSpace", "RenderDistance");

	SettingsShadows.Exteriors.AlphaEnabled[ShadowManager::ShadowMapTypeEnum::MapNear] = GetSettingI("Shaders.ShadowsExteriors.Near", "AlphaEnabled");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Activators = GetSettingI("Shaders.ShadowsExteriors.Near", "Activators");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Actors = GetSettingI("Shaders.ShadowsExteriors.Near", "Actors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Apparatus = GetSettingI("Shaders.ShadowsExteriors.Near", "Apparatus");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Books = GetSettingI("Shaders.ShadowsExteriors.Near", "Books");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Containers = GetSettingI("Shaders.ShadowsExteriors.Near", "Containers");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Doors = GetSettingI("Shaders.ShadowsExteriors.Near", "Doors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Furniture = GetSettingI("Shaders.ShadowsExteriors.Near", "Furniture");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Misc = GetSettingI("Shaders.ShadowsExteriors.Near", "Misc");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Statics = GetSettingI("Shaders.ShadowsExteriors.Near", "Statics");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Terrain = GetSettingI("Shaders.ShadowsExteriors.Near", "Terrain");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Trees = GetSettingI("Shaders.ShadowsExteriors.Near", "Trees");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapNear].Lod = GetSettingI("Shaders.ShadowsExteriors.Near", "Lod");

	SettingsShadows.Exteriors.AlphaEnabled[ShadowManager::ShadowMapTypeEnum::MapMiddle] = GetSettingI("Shaders.ShadowsExteriors.Middle", "AlphaEnabled");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Activators = GetSettingI("Shaders.ShadowsExteriors.Middle", "Activators");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Actors = GetSettingI("Shaders.ShadowsExteriors.Middle", "Actors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Apparatus = GetSettingI("Shaders.ShadowsExteriors.Middle", "Apparatus");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Books = GetSettingI("Shaders.ShadowsExteriors.Middle", "Books");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Containers = GetSettingI("Shaders.ShadowsExteriors.Middle", "Containers");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Doors = GetSettingI("Shaders.ShadowsExteriors.Middle", "Doors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Furniture = GetSettingI("Shaders.ShadowsExteriors.Middle", "Furniture");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Misc = GetSettingI("Shaders.ShadowsExteriors.Middle", "Misc");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Statics = GetSettingI("Shaders.ShadowsExteriors.Middle", "Statics");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Terrain = GetSettingI("Shaders.ShadowsExteriors.Middle", "Terrain");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Trees = GetSettingI("Shaders.ShadowsExteriors.Middle", "Trees");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapMiddle].Lod = GetSettingI("Shaders.ShadowsExteriors.Middle", "Lod");

	SettingsShadows.Exteriors.AlphaEnabled[ShadowManager::ShadowMapTypeEnum::MapFar] = GetSettingI("Shaders.ShadowsExteriors.Far", "AlphaEnabled");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Activators = GetSettingI("Shaders.ShadowsExteriors.Far", "Activators");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Actors = GetSettingI("Shaders.ShadowsExteriors.Far", "Actors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Apparatus = GetSettingI("Shaders.ShadowsExteriors.Far", "Apparatus");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Books = GetSettingI("Shaders.ShadowsExteriors.Far", "Books");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Containers = GetSettingI("Shaders.ShadowsExteriors.Far", "Containers");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Doors = GetSettingI("Shaders.ShadowsExteriors.Far", "Doors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Furniture = GetSettingI("Shaders.ShadowsExteriors.Far", "Furniture");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Misc = GetSettingI("Shaders.ShadowsExteriors.Far", "Misc");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Statics = GetSettingI("Shaders.ShadowsExteriors.Far", "Statics");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Terrain = GetSettingI("Shaders.ShadowsExteriors.Far", "Terrain");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Trees = GetSettingI("Shaders.ShadowsExteriors.Far", "Trees");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapFar].Lod = GetSettingI("Shaders.ShadowsExteriors.Far", "Lod");

	SettingsShadows.Exteriors.AlphaEnabled[ShadowManager::ShadowMapTypeEnum::MapLod] = GetSettingI("Shaders.ShadowsExteriors.Lod", "AlphaEnabled");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Activators = GetSettingI("Shaders.ShadowsExteriors.Lod", "Activators");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Actors = GetSettingI("Shaders.ShadowsExteriors.Lod", "Actors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Apparatus = GetSettingI("Shaders.ShadowsExteriors.Lod", "Apparatus");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Books = GetSettingI("Shaders.ShadowsExteriors.Lod", "Books");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Containers = GetSettingI("Shaders.ShadowsExteriors.Lod", "Containers");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Doors = GetSettingI("Shaders.ShadowsExteriors.Lod", "Doors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Furniture = GetSettingI("Shaders.ShadowsExteriors.Lod", "Furniture");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Misc = GetSettingI("Shaders.ShadowsExteriors.Lod", "Misc");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Statics = GetSettingI("Shaders.ShadowsExteriors.Lod", "Statics");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Terrain = GetSettingI("Shaders.ShadowsExteriors.Lod", "Terrain");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Trees = GetSettingI("Shaders.ShadowsExteriors.Lod", "Trees");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapLod].Lod = GetSettingI("Shaders.ShadowsExteriors.Lod", "Lod");

	SettingsShadows.Exteriors.AlphaEnabled[ShadowManager::ShadowMapTypeEnum::MapOrtho] = GetSettingI("Shaders.ShadowsExteriors.Ortho", "AlphaEnabled");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Activators = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Activators");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Actors = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Actors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Apparatus = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Apparatus");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Books = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Books");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Containers = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Containers");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Doors = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Doors");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Furniture = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Furniture");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Misc = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Misc");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Statics = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Statics");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Terrain = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Terrain");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Trees = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Trees");
	SettingsShadows.Exteriors.Forms[ShadowManager::ShadowMapTypeEnum::MapOrtho].Lod = GetSettingI("Shaders.ShadowsExteriors.Ortho", "Lod");

	Config.FillSections(&List, "Shaders.ShadowsExteriors.ExcludedFormID");
	if (List.size()) SettingsShadows.Exteriors.ExcludedForms.reserve(List.size());
	for (StringList::iterator Iter = List.begin(); Iter != List.end(); ++Iter) {
		SettingsShadows.Exteriors.ExcludedForms.push_back(strtol(Iter->c_str(), NULL, 16));
	}
	if (List.size()) std::sort(SettingsShadows.Exteriors.ExcludedForms.begin(), SettingsShadows.Exteriors.ExcludedForms.end());

	SettingsShadows.Interiors.Enabled = GetSettingI("Shaders.ShadowsInteriors.Main", "Enabled");
	SettingsShadows.Interiors.AlphaEnabled = GetSettingI("Shaders.ShadowsInteriors.Main", "AlphaEnabled");
	SettingsShadows.Interiors.Forms.Activators = GetSettingI("Shaders.ShadowsInteriors.Main", "Activators");
	SettingsShadows.Interiors.Forms.Actors = GetSettingI("Shaders.ShadowsInteriors.Main", "Actors");
	SettingsShadows.Interiors.Forms.Apparatus = GetSettingI("Shaders.ShadowsInteriors.Main", "Apparatus");
	SettingsShadows.Interiors.Forms.Books = GetSettingI("Shaders.ShadowsInteriors.Main", "Books");
	SettingsShadows.Interiors.Forms.Containers = GetSettingI("Shaders.ShadowsInteriors.Main", "Containers");
	SettingsShadows.Interiors.Forms.Doors = GetSettingI("Shaders.ShadowsInteriors.Main", "Doors");
	SettingsShadows.Interiors.Forms.Furniture = GetSettingI("Shaders.ShadowsInteriors.Main", "Furniture");
	SettingsShadows.Interiors.Forms.Misc = GetSettingI("Shaders.ShadowsInteriors.Main", "Misc");
	SettingsShadows.Interiors.Forms.Statics = GetSettingI("Shaders.ShadowsInteriors.Main", "Statics");
	SettingsShadows.Interiors.Forms.MinRadius = GetSettingF("Shaders.ShadowsInteriors.Main", "MinRadius");
	SettingsShadows.Interiors.Quality = GetSettingI("Shaders.ShadowsInteriors.Main", "Quality");
	SettingsShadows.Interiors.LightPoints = GetSettingI("Shaders.ShadowsInteriors.Main", "LightPoints");
	SettingsShadows.Interiors.TorchesCastShadows = GetSettingI("Shaders.ShadowsInteriors.Main", "TorchesCastShadows");
	SettingsShadows.Interiors.ShadowCubeMapSize = GetSettingI("Shaders.ShadowsInteriors.Main", "ShadowCubeMapSize");
	SettingsShadows.Interiors.Darkness = GetSettingF("Shaders.ShadowsInteriors.Main", "Darkness");
	SettingsShadows.Interiors.LightRadiusMult = GetSettingF("Shaders.ShadowsInteriors.Main", "LightRadiusMult");

	Config.FillSections(&List, "Shaders.ShadowsInteriors.ExcludedFormID");
	SettingsShadows.Interiors.ExcludedForms.reserve(List.size());
	for (StringList::iterator Iter = List.begin(); Iter != List.end(); ++Iter) {
		SettingsShadows.Interiors.ExcludedForms.push_back(strtol(Iter->c_str(), NULL, 16));
	}
	if (List.size()) std::sort(SettingsShadows.Interiors.ExcludedForms.begin(), SettingsShadows.Interiors.ExcludedForms.end());


	SettingsSharpening.Strength = GetSettingF("Shaders.Sharpening.Main", "Strength");
	SettingsSharpening.Clamp = GetSettingF("Shaders.Sharpening.Main", "Clamp");
	SettingsSharpening.Offset = GetSettingF("Shaders.Sharpening.Main", "Offset");


	SettingsSkin.Attenuation = GetSettingF("Shaders.Skin.Main", "Attenuation");
	SettingsSkin.SpecularPower = GetSettingF("Shaders.Skin.Main", "SpecularPower");
	SettingsSkin.MaterialThickness = GetSettingF("Shaders.Skin.Main", "MaterialThickness");
	SettingsSkin.RimScalar = GetSettingF("Shaders.Skin.Main", "RimScalar");
	SettingsSkin.CoeffRed = GetSettingF("Shaders.Skin.Main", "CoeffRed");
	SettingsSkin.CoeffGreen = GetSettingF("Shaders.Skin.Main", "CoeffGreen");
	SettingsSkin.CoeffBlue = GetSettingF("Shaders.Skin.Main", "CoeffBlue");


	SettingsTerrain.DistantSpecular = GetSettingF("Shaders.Terrain.Main", "DistantSpecular");
	SettingsTerrain.DistantNoise = GetSettingF("Shaders.Terrain.Main", "DistantNoise");
	SettingsTerrain.NearSpecular = GetSettingF("Shaders.Terrain.Main", "NearSpecular");
	SettingsTerrain.MiddleSpecular = GetSettingF("Shaders.Terrain.Main", "MiddleSpecular");


	SettingsVolumetricFog.Exponent = GetSettingF("Shaders.VolumetricFog.Main", "Exponent");
	SettingsVolumetricFog.ColorCoeff = GetSettingF("Shaders.VolumetricFog.Main", "ColorCoeff");
	SettingsVolumetricFog.Amount = GetSettingF("Shaders.VolumetricFog.Main", "Amount");
	SettingsVolumetricFog.MaxDistance = GetSettingF("Shaders.VolumetricFog.Main", "MaxDistance");


	Config.FillSections(&List, "Shaders.Water");
	for (StringList::iterator Iter = List.begin(); Iter != List.end(); ++Iter) {
		const char* WaterSection = Iter->c_str();
		if (strcmp(WaterSection, "Status")) {
			char SectionName[80];
			strcpy(SectionName, "Shaders.Water.");
			strcat(SectionName, WaterSection);
			SW.choppiness = GetSettingF(SectionName, "choppiness");
			SW.waveWidth = GetSettingF(SectionName, "waveWidth");
			SW.waveSpeed = GetSettingF(SectionName, "waveSpeed");
			SW.reflectivity = GetSettingF(SectionName, "reflectivity");
			SW.causticsStrength = GetSettingF(SectionName, "causticsStrength");
			SW.causticsStrengthS = GetSettingF(SectionName, "causticsStrengthS");
			SW.shoreFactor = GetSettingF(SectionName, "shoreFactor");
			SW.shoreMovement = GetSettingF(SectionName, "shoreMovement");
			SW.turbidity = GetSettingF(SectionName, "turbidity");
			SW.inScattCoeff = GetSettingF(SectionName, "inScattCoeff");
			SW.inExtCoeff_R = GetSettingF(SectionName, "inExtCoeff_R");
			SW.inExtCoeff_G = GetSettingF(SectionName, "inExtCoeff_G");
			SW.inExtCoeff_B = GetSettingF(SectionName, "inExtCoeff_B");
			SW.depthDarkness = GetSettingF(SectionName, "depthDarkness");
			SettingsWater[WaterSection] = SW;
		}
	}

	SettingsWaterLens.TimeMultA = GetSettingF("Shaders.WaterLens.Main", "TimeMultA");
	SettingsWaterLens.TimeMultB = GetSettingF("Shaders.WaterLens.Main", "TimeMultB");
	SettingsWaterLens.Time = GetSettingF("Shaders.WaterLens.Main", "Time");
	SettingsWaterLens.Amount = GetSettingF("Shaders.WaterLens.Main", "Amount");
	SettingsWaterLens.Viscosity = GetSettingF("Shaders.WaterLens.Main", "Viscosity");

}

void SettingManager::SaveSettings() {

	char Filename[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, Filename);
	strcat(Filename, SettingsFile);
	std::ofstream ConfigurationFile(Filename, std::ios::trunc | std::ios::binary);
	ConfigurationFile << Config.Config;
	ConfigurationFile.close();

}

int SettingManager::GetSettingI(const char* Section, const char* Key) {

	Configuration::ConfigNode Node;
	int Value = 0;

	if (Config.FillNode(&Node, Section, Key)) Value = atoi(Node.Value);
	return Value;

}

float SettingManager::GetSettingF(const char* Section, const char* Key) {

	Configuration::ConfigNode Node;
	float Value = 0.0f;

	if (Config.FillNode(&Node, Section, Key)) Value = atof(Node.Value);
	return Value;

}

char* SettingManager::GetSettingS(const char* Section, const char* Key, char* Value) {

	Configuration::ConfigNode Node;
	
	strcpy(Value, "\"");
	if (Config.FillNode(&Node, Section, Key)) strcpy(Value, Node.Value);
	return Value;

}

void SettingManager::SetSetting(const char* Section, const char* Key, float Value) {

	Configuration::ConfigNode Node;

	if (memcmp(Section, "Weathers", 8)) {
		Config.FillNode(&Node, Section, Key);
		switch (Node.Type) {
		case Configuration::NodeType::Boolean:
			strcpy(Node.Value, ToString<bool>(Value).c_str());
			break;
		case Configuration::NodeType::Integer:
			strcpy(Node.Value, ToString<int>(Value).c_str());
			break;
		case Configuration::NodeType::Float:
			strcpy(Node.Value, ToString<float>(Value).c_str());
			break;
		}
		SetSetting(&Node);
	}
	else {
		SetSettingWeather(Section, Key, Value);
	}

}

void SettingManager::SetSettingS(const char* Section, const char* Key, char* Value) {

	Configuration::ConfigNode Node;

	Config.FillNode(&Node, Section, Key);
	strcpy(Node.Value, Value);
	SetSetting(&Node);

}

void SettingManager::SetSetting(Configuration::ConfigNode* Node) {

	Config.SetValue(Node);
	LoadSettings();

}

void SettingManager::SetSettingWeather(const char* Section, const char* Key, float Value) {

	Configuration::ConfigNode Node;
	SettingsWeatherStruct* SettingsWeather = NULL;
	const char* WeatherName = NULL;
	TESWeather* Weather = NULL;
	StringList Values;
	char AttributeValue[80] = { NULL };
	char ColorSection[40];
	char ColorNode[8];

	SplitString(Section, ".", &Values);
	WeatherName = Values[1].c_str();
	Weather = (TESWeather*)DataHandler->GetFormByName(WeatherName, TESForm::FormType::kFormType_Weather);
	SettingsWeather = GetSettingsWeather(WeatherName);
	if (!SettingsWeather) {
		Config.CreateWeatherSection(WeatherName, Weather);
		LoadSettings();
		SettingsWeather = GetSettingsWeather(WeatherName);
	}
	if (Values[2] == "Main") {
		Config.FillNode(&Node, Section, Key);
		switch (Node.Type) {
		case Configuration::NodeType::Boolean:
			strcpy(Node.Value, ToString<bool>(Value).c_str());
			break;
		case Configuration::NodeType::Integer:
			strcpy(Node.Value, ToString<int>(Value).c_str());
			break;
		case Configuration::NodeType::Float:
			strcpy(Node.Value, ToString<float>(Value).c_str());
			break;
		}
	}
	else if (Values[2] == "HDR") {
		AttributeValue[0] = NULL;
		for (UInt32 i = 0; i < 14; i++) {
			if (!strcmp(WeatherHDRTypes[i], Key))
				strcat(AttributeValue, ToString(Value).c_str());
			else
				strcat(AttributeValue, ToString(SettingsWeather->HDR[i]).c_str());
			if (i < 13) strcat(AttributeValue, " ");
		}
		CreateNodeS(&Node, Section, "HDR", AttributeValue, 0);
	}
	else {
		AttributeValue[0] = NULL;
		for (UInt32 x = 0; x < TESWeather::kNumColorTypes; x++) {
			if (Values[2] == WeatherColorTypes[x]) {
				for (UInt32 y = 0; y < TESWeather::kNumTimeOfDay; y++) {
					if (strstr(Key, WeatherTimesOfDay[y])) {
						if (!memcmp(Key + strlen(Key) - 1, "R", 1)) {
							strcat(AttributeValue, ToString(Value).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].g).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].b).c_str());
						}
						else if (!memcmp(Key + strlen(Key) - 1, "G", 1)) {
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].r).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(Value).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].b).c_str());
						}
						else if (!memcmp(Key + strlen(Key) - 1, "B", 1)) {
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].r).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].g).c_str());
							strcat(AttributeValue, ",");
							strcat(AttributeValue, ToString(Value).c_str());
						}
					}
					else {
						strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].r).c_str());
						strcat(AttributeValue, ",");
						strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].g).c_str());
						strcat(AttributeValue, ",");
						strcat(AttributeValue, ToString(SettingsWeather->Colors[x].colors[y].b).c_str());
					}
					if (y < TESWeather::kNumTimeOfDay - 1) strcat(AttributeValue, " ");
				}
				strcpy(ColorSection, Values[0].c_str());
				strcat(ColorSection, ".");
				strcat(ColorSection, Values[1].c_str());
				strcat(ColorSection, ".");
				strcat(ColorSection, "Colors");
				sprintf(ColorNode, "Color%i", x);
				CreateNodeS(&Node, ColorSection, ColorNode, AttributeValue, 0);
				break;
			}
		}
	}
	SetSetting(&Node);
	SetSettingsWeather(Weather);

}

void SettingManager::FillMenuSections(StringList* Sections, const char* ParentSection) {

	if (ParentSection == NULL || memcmp(ParentSection, "Weathers", 8)) {
		Config.FillSections(Sections, ParentSection);
	}
	else {
		if (strlen(ParentSection) == 8) {
			DataHandler->FillNames(Sections, TESForm::FormType::kFormType_Weather);
			std::sort(Sections->begin(), Sections->end());
		}
		else {
			Sections->clear();
			Sections->push_back("Main");
			for (UInt32 i = 0; i < TESWeather::kNumColorTypes; i++) {
				Sections->push_back(WeatherColorTypes[i]);
			}
			Sections->push_back("HDR");
		}
	}

}

void SettingManager::FillMenuSettings(Configuration::SettingList* Settings, const char* Section) {

	SettingsWeatherStruct* SettingsWeather = NULL;
	Configuration::ConfigNode Node;
	StringList Values;

	if (memcmp(Section, "Weathers", 8)) {
		Config.FillSettings(Settings, Section);
	}
	else {
		Settings->clear();
		SplitString(Section, ".", &Values);
		SettingsWeather = GetSettingsWeather(Values[1].c_str());
		if (SettingsWeather) {
			if (Values[2] == "Main") {
				Config.FillSettings(Settings, Section);
			}
			else if (Values[2] == "HDR") {
				for (UInt32 i = 0; i < 14; i++) {
					CreateNodeF(&Node, Section, WeatherHDRTypes[i], SettingsWeather->HDR[i], 0, Configuration::NodeType::Float);
					Settings->push_back(Node);
				}
			}
			else {
				for (UInt32 i = 0; i < TESWeather::kNumColorTypes; i++) {
					if (Values[2] == WeatherColorTypes[i]) {
						CreateNodeF(&Node, Section, "DayR", SettingsWeather->Colors[i].colors[TESWeather::eTime_Day].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "DayG", SettingsWeather->Colors[i].colors[TESWeather::eTime_Day].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "DayB", SettingsWeather->Colors[i].colors[TESWeather::eTime_Day].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightR", SettingsWeather->Colors[i].colors[TESWeather::eTime_Night].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightG", SettingsWeather->Colors[i].colors[TESWeather::eTime_Night].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightB", SettingsWeather->Colors[i].colors[TESWeather::eTime_Night].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseR", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunrise].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseG", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunrise].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseB", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunrise].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetR", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunset].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetG", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunset].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetB", SettingsWeather->Colors[i].colors[TESWeather::eTime_Sunset].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
					}
				}
			}
		}
		else {
			TESWeather* Weather = (TESWeather*)DataHandler->GetFormByName(Values[1].c_str(), TESForm::FormType::kFormType_Weather);
			if (Values[2] == "Main") {
				CreateNodeF(&Node, Section, "CloudSpeedLower", Weather->GetCloudSpeedLower(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "CloudSpeedUpper", Weather->GetCloudSpeedUpper(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "FogFarDay", Weather->GetFogDayFar(), 0, Configuration::NodeType::Float);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "FogFarNight", Weather->GetFogNightFar(), 0, Configuration::NodeType::Float);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "FogNearDay", Weather->GetFogDayNear(), 0, Configuration::NodeType::Float);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "FogNearNight", Weather->GetFogNightNear(), 0, Configuration::NodeType::Float);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "SunDamage", Weather->GetSunDamage(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "SunGlare", Weather->GetSunGlare(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "TransDelta", Weather->GetTransDelta(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
				CreateNodeF(&Node, Section, "WindSpeed", Weather->GetWindSpeed(), 0, Configuration::NodeType::Integer);
				Settings->push_back(Node);
			}
			else if (Values[2] == "HDR") {
				for (UInt32 i = 0; i < 14; i++) {
					CreateNodeF(&Node, Section, WeatherHDRTypes[i], Weather->GetHDR(i), 0, Configuration::NodeType::Float);
					Settings->push_back(Node);
				}
			}
			else {
				for (UInt32 i = 0; i < TESWeather::kNumColorTypes; i++) {
					if (Values[2] == WeatherColorTypes[i]) {
						CreateNodeF(&Node, Section, "DayR", Weather->colors[i].colors[TESWeather::eTime_Day].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "DayG", Weather->colors[i].colors[TESWeather::eTime_Day].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "DayB", Weather->colors[i].colors[TESWeather::eTime_Day].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightR", Weather->colors[i].colors[TESWeather::eTime_Night].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightG", Weather->colors[i].colors[TESWeather::eTime_Night].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "NightB", Weather->colors[i].colors[TESWeather::eTime_Night].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseR", Weather->colors[i].colors[TESWeather::eTime_Sunrise].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseG", Weather->colors[i].colors[TESWeather::eTime_Sunrise].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunriseB", Weather->colors[i].colors[TESWeather::eTime_Sunrise].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetR", Weather->colors[i].colors[TESWeather::eTime_Sunset].r, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetG", Weather->colors[i].colors[TESWeather::eTime_Sunset].g, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
						CreateNodeF(&Node, Section, "SunsetB", Weather->colors[i].colors[TESWeather::eTime_Sunset].b, 0, Configuration::NodeType::Integer);
						Settings->push_back(Node);
					}
				}
			}
		}
	}

}

void SettingManager::CreateNodeF(Configuration::ConfigNode* Node, const char* Section, const char* Key, float Value, bool Reboot, UInt32 Type) {

	strcpy(Node->Section, Section);
	strcpy(Node->Key, Key);
	switch (Type) {
	case Configuration::NodeType::Boolean:
		strcpy(Node->Value, ToString<bool>(Value).c_str());
		break;
	case Configuration::NodeType::Integer:
		strcpy(Node->Value, ToString<int>(Value).c_str());
		break;
	case Configuration::NodeType::Float:
		strcpy(Node->Value, ToString<float>(Value).c_str());
		break;
	}
	Node->Reboot = Reboot;
	Node->Type = Type;

}

void SettingManager::CreateNodeS(Configuration::ConfigNode* Node, const char* Section, const char* Key, const char* Value, bool Reboot) {

	strcpy(Node->Section, Section);
	strcpy(Node->Key, Key);
	strcpy(Node->Value, Value);
	Node->Reboot = Reboot;
	Node->Type = Configuration::NodeType::String;

}

bool SettingManager::GetMenuShaderEnabled(const char* Name) {

	bool Value = false;

	if (!strcmp(Name, "AmbientOcclusion"))
		Value = SettingsMain.Effects.AmbientOcclusion;
	else if (!strcmp(Name, "Blood"))
		Value = SettingsMain.Shaders.Blood;
	else if (!strcmp(Name, "BloodLens"))
		Value = SettingsMain.Effects.BloodLens;
	else if (!strcmp(Name, "Bloom"))
		Value = SettingsMain.Effects.Bloom;
	else if (!strcmp(Name, "Cinema"))
		Value = SettingsMain.Effects.Cinema;
	else if (!strcmp(Name, "Coloring"))
		Value = SettingsMain.Effects.Coloring;
	else if (!strcmp(Name, "DepthOfField"))
		Value = SettingsMain.Effects.DepthOfField;
	else if (!strcmp(Name, "ExtraEffects"))
		Value = SettingsMain.Effects.Extra;
	else if (!strcmp(Name, "ExtraShaders"))
		Value = SettingsMain.Shaders.Extra;
	else if (!strcmp(Name, "GodRays"))
		Value = SettingsMain.Effects.GodRays;
	else if (!strcmp(Name, "Grass"))
		Value = SettingsMain.Shaders.Grass;
	else if (!strcmp(Name, "HDR"))
		Value = SettingsMain.Shaders.HDR;
	else if (!strcmp(Name, "LowHF"))
		Value = SettingsMain.Effects.LowHF;
	else if (!strcmp(Name, "MotionBlur"))
		Value = SettingsMain.Effects.MotionBlur;
	else if (!strcmp(Name, "NightEye"))
		Value = SettingsMain.Shaders.NightEye;
	else if (!strcmp(Name, "POM"))
		Value = SettingsMain.Shaders.POM;
	else if (!strcmp(Name, "Rain"))
		Value = SettingsMain.Effects.Rain;
	else if (!strcmp(Name, "Snow"))
		Value = SettingsMain.Effects.Snow;
	else if (!strcmp(Name, "ShadowsExteriors"))
		Value = SettingsMain.Effects.ShadowsExteriors;
	else if (!strcmp(Name, "ShadowsInteriors"))
		Value = SettingsMain.Effects.ShadowsInteriors;
	else if (!strcmp(Name, "Sharpening"))
		Value = SettingsMain.Effects.Sharpening;
	else if (!strcmp(Name, "Specular"))
		Value = SettingsMain.Effects.Specular;
	else if (!strcmp(Name, "Skin"))
		Value = SettingsMain.Shaders.Skin;
	else if (!strcmp(Name, "SnowAccumulation"))
		Value = SettingsMain.Effects.SnowAccumulation;
	else if (!strcmp(Name, "Terrain"))
		Value = SettingsMain.Shaders.Terrain;
	else if (!strcmp(Name, "Underwater"))
		Value = SettingsMain.Effects.Underwater;
	else if (!strcmp(Name, "VolumetricFog"))
		Value = SettingsMain.Effects.VolumetricFog;
	else if (!strcmp(Name, "Water"))
		Value = SettingsMain.Shaders.Water;
	else if (!strcmp(Name, "WaterLens"))
		Value = SettingsMain.Effects.WaterLens;
	else if (!strcmp(Name, "WetWorld"))
		Value = SettingsMain.Effects.WetWorld;
	return Value;

}

SettingsWaterStruct* SettingManager::GetSettingsWater(const char* PlayerLocation) {

	SettingsWaterMap::iterator v = SettingsWater.find(std::string(PlayerLocation));
	if (v == SettingsWater.end())
		return NULL;
	else
		return &v->second;

}

SettingsColoringStruct* SettingManager::GetSettingsColoring(const char* PlayerLocation) {

	SettingsColoringMap::iterator v = SettingsColoring.find(std::string(PlayerLocation));
	if (v == SettingsColoring.end())
		return NULL;
	else
		return &v->second;

}

SettingsWeatherStruct* SettingManager::GetSettingsWeather(const char* WeatherName) {

	SettingsWeatherMap::iterator v = SettingsWeather.find(std::string(WeatherName));
	if (v == SettingsWeather.end())
		return NULL;
	else
		return &v->second;

}

void SettingManager::SetSettingsWeather(TESWeather* Weather) {

	TESWeatherEx* WeatherEx = (TESWeatherEx*)Weather;
	SettingsWeatherStruct* SettingsWeather = GetSettingsWeather(WeatherEx->EditorName);

	if (SettingsWeather) {
		SetTextureAndHDR(WeatherEx, SettingsWeather->UpperLayer, SettingsWeather->LowerLayer, SettingsWeather->HDR);
		WeatherEx->SetWindSpeed(SettingsWeather->WindSpeed);
		WeatherEx->SetCloudSpeedLower(SettingsWeather->CloudSpeedLower);
		WeatherEx->SetCloudSpeedUpper(SettingsWeather->CloudSpeedUpper);
		WeatherEx->SetTransDelta(SettingsWeather->TransDelta);
		WeatherEx->SetSunGlare(SettingsWeather->SunGlare);
		WeatherEx->SetSunDamage(SettingsWeather->SunDamage);
		WeatherEx->SetFogDayNear(SettingsWeather->FogNearDay);
		WeatherEx->SetFogDayFar(SettingsWeather->FogFarDay);
		WeatherEx->SetFogNightNear(SettingsWeather->FogNearNight);
		WeatherEx->SetFogNightFar(SettingsWeather->FogFarNight);
		memcpy(WeatherEx->colors, SettingsWeather->Colors, TESWeather::kNumColorTypes * TESWeather::kNumTimeOfDay * 4);
		memcpy(WeatherEx->colorsb, SettingsWeather->Colors, TESWeather::kNumColorTypes * TESWeather::kNumTimeOfDay * 4);
	}
	for (int c = 0; c < TESWeatherEx::eColor_Lighting; c++) {
		WeatherEx->colors[c].colors[TESWeatherEx::eTime_Night].r = WeatherEx->colorsb[c].colors[TESWeatherEx::eTime_Night].r * SettingsMain.WeatherMode.CoeffNight.x;
		WeatherEx->colors[c].colors[TESWeatherEx::eTime_Night].g = WeatherEx->colorsb[c].colors[TESWeatherEx::eTime_Night].g * SettingsMain.WeatherMode.CoeffNight.y;
		WeatherEx->colors[c].colors[TESWeatherEx::eTime_Night].b = WeatherEx->colorsb[c].colors[TESWeatherEx::eTime_Night].b * SettingsMain.WeatherMode.CoeffNight.z;
	}
	for (int t = 0; t < TESWeatherEx::eTime_Night; t++) {
		WeatherEx->colors[TESWeatherEx::eColor_Fog].colors[t].r = WeatherEx->colorsb[TESWeatherEx::eColor_Fog].colors[t].r * SettingsMain.WeatherMode.CoeffFog.x;
		WeatherEx->colors[TESWeatherEx::eColor_Fog].colors[t].g = WeatherEx->colorsb[TESWeatherEx::eColor_Fog].colors[t].g * SettingsMain.WeatherMode.CoeffFog.y;
		WeatherEx->colors[TESWeatherEx::eColor_Fog].colors[t].b = WeatherEx->colorsb[TESWeatherEx::eColor_Fog].colors[t].b * SettingsMain.WeatherMode.CoeffFog.z;
		WeatherEx->colors[TESWeatherEx::eColor_Sunlight].colors[t].r = WeatherEx->colorsb[TESWeatherEx::eColor_Sunlight].colors[t].r * SettingsMain.WeatherMode.CoeffSun.x;
		WeatherEx->colors[TESWeatherEx::eColor_Sunlight].colors[t].g = WeatherEx->colorsb[TESWeatherEx::eColor_Sunlight].colors[t].g * SettingsMain.WeatherMode.CoeffSun.y;
		WeatherEx->colors[TESWeatherEx::eColor_Sunlight].colors[t].b = WeatherEx->colorsb[TESWeatherEx::eColor_Sunlight].colors[t].b * SettingsMain.WeatherMode.CoeffSun.z;
		WeatherEx->colors[TESWeatherEx::eColor_Sun].colors[t].r = WeatherEx->colorsb[TESWeatherEx::eColor_Sun].colors[t].r * SettingsMain.WeatherMode.CoeffSun.x;
		WeatherEx->colors[TESWeatherEx::eColor_Sun].colors[t].g = WeatherEx->colorsb[TESWeatherEx::eColor_Sun].colors[t].g * SettingsMain.WeatherMode.CoeffSun.y;
		WeatherEx->colors[TESWeatherEx::eColor_Sun].colors[t].b = WeatherEx->colorsb[TESWeatherEx::eColor_Sun].colors[t].b * SettingsMain.WeatherMode.CoeffSun.z;
	}

}

template<typename T>
std::string SettingManager::ToString(const T Value) {

	std::ostringstream os;

	os << (float)Value;
	return os.str();

}

template<typename T>
T SettingManager::FromString(const char* Value) {

	float Result = 0.0f;
	std::istringstream is(Value);

	is >> Result;
	return Result;

}

void SettingManager::SplitString(const char* String, const char* Delimiter, StringList* Values) {

	char StringB[256];
	char* Finder = NULL;

	strcpy(StringB, String);
	Finder = strtok(StringB, Delimiter);
	Values->clear();
	while (Finder != NULL) {
		Values->push_back(Finder);
		Finder = strtok(NULL, Delimiter);
	}

}

template<typename T>
void SettingManager::FillFromString(const char* String, const char* Delimiter, T* Values) {

	char StringB[256];
	char* Finder = NULL;
	UInt32 c = 0;

	strcpy(StringB, String);
	Finder = strtok(StringB, Delimiter);
	while (Finder != NULL) {
		Values[c] = FromString<T>(Finder);
		Finder = strtok(NULL, Delimiter);
		c++;
	}

}
