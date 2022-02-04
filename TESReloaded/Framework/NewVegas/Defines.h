#pragma once

#define CommandPrefix "NVR"
#define SettingsFile "\\Data\\NVSE\\Plugins\\NewVegasReloaded.dll.config"
#define ShadersPath "Data\\Shaders\\NewVegasReloaded\\Shaders\\"
#define EffectsPath "Data\\Shaders\\NewVegasReloaded\\Effects\\"
#define RenderStateArgs 0, 0
#define TerrainShaders ""
#define BloodShaders ""
static const char* IntroMovie = "NVRGameStudios.bik";
static const char* MainMenuMovie = "\\Data\\Video\\NVRMainMenu.bik";
static const char* MainMenuMusic = "NVRMainMenu";
static char* TitleMenu = "New Vegas Reloaded - Settings";

// to review
static const char* WeatherColorTypes[TESWeather::kNumColorTypes] = { "SkyUpper", "Fog", "CloudsLower", "Ambient", "Sunlight", "Sun", "Stars", "SkyLower", "Horizon", "CloudsUpper" };
static const char* WeatherTimesOfDay[TESWeather::kNumTimeOfDay] = { "Sunrise", "Day", "Sunset", "Night" };
static const char* WeatherHDRTypes[14] = { "EyeAdaptation", "BlurRadius", "BlurPasses", "EmissiveMult", "TargetLUM", "UpperLUMClamp", "BrightScale", "BrightClamp", "LUMRampNoTex", "LUMRampMin", "LUMRampMax", "SunlightDimmer", "GrassDimmer", "TreeDimmer" };