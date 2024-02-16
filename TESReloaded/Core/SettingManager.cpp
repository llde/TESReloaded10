#include "SettingManager.h"

void SettingManager::LoadSettings() {
	ffi::LoadConfiguration();
	this->Config = ffi::getConfiguration();
	this->Effects = ffi::getEffectsConfiguration();
	this->Shaders = ffi::getShadersConfiguration();
}

bool SettingManager::GetMenuShaderEnabled(const char* Name) {

	bool Value = false;

	if (!strcmp(Name, "AmbientOcclusion"))
		Value = Config->Effects.AmbientOcclusion;
	else if (!strcmp(Name, "Blood"))
		Value = Config->Shaders.Blood;
	else if (!strcmp(Name, "BloodLens"))
		Value = Config->Effects.BloodLens;
	else if (!strcmp(Name, "Bloom"))
		Value = Config->Effects.Bloom;
	else if (!strcmp(Name, "Cinema"))
		Value = Config->Effects.Cinema;
	else if (!strcmp(Name, "Coloring"))
		Value = Config->Effects.Coloring;
	else if (!strcmp(Name, "DepthOfField"))
		Value = Config->Effects.DepthOfField;
	else if (!strcmp(Name, "ExtraEffects"))
		Value = Config->Effects.Extra;
	else if (!strcmp(Name, "ExtraShaders"))
		Value = Config->Shaders.Extra;
	else if (!strcmp(Name, "GodRays"))
		Value = Config->Effects.GodRays;
	else if (!strcmp(Name, "Grass"))
		Value = Config->Shaders.Grass;
	else if (!strcmp(Name, "HDR"))
		Value = Config->Shaders.HDR;
	else if (!strcmp(Name, "LowHF"))
		Value = Config->Effects.LowHF;
	else if (!strcmp(Name, "MotionBlur"))
		Value = Config->Effects.MotionBlur;
	else if (!strcmp(Name, "NightEye"))
		Value = Config->Shaders.NightEye;
	else if (!strcmp(Name, "POM"))
		Value = Config->Shaders.POM;
	else if (!strcmp(Name, "Rain"))
		Value = Config->Effects.Rain;
	else if (!strcmp(Name, "Snow"))
		Value = Config->Effects.Snow;
	else if (!strcmp(Name, "ShadowsExteriors"))
		Value = Config->Effects.ShadowsExteriors;
	else if (!strcmp(Name, "ShadowsInteriors"))
		Value = Config->Effects.ShadowsInteriors;
	else if (!strcmp(Name, "Sharpening"))
		Value = Config->Effects.Sharpening;
	else if (!strcmp(Name, "Specular"))
		Value = Config->Effects.Specular;
	else if (!strcmp(Name, "Skin"))
		Value = Config->Shaders.Skin;
	else if (!strcmp(Name, "SnowAccumulation"))
		Value = Config->Effects.SnowAccumulation;
	else if (!strcmp(Name, "Terrain"))
		Value = Config->Shaders.Terrain;
	else if (!strcmp(Name, "Underwater"))
		Value = Config->Effects.Underwater;
	else if (!strcmp(Name, "VolumetricFog"))
		Value = Config->Effects.VolumetricFog;
	else if (!strcmp(Name, "Water"))
		Value = Config->Shaders.Water;
	else if (!strcmp(Name, "WaterLens"))
		Value = Config->Effects.WaterLens;
	else if (!strcmp(Name, "WetWorld"))
		Value = Config->Effects.WetWorld;
	return Value;
}

void SettingManager::Initialize()
{
	TheSettingManager = new SettingManager();
	ffi::SetLogFile(Logger::LogFile);
}
