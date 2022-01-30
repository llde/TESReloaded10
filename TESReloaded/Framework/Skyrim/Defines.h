#pragma once

#define CommandPrefix "SR"
#define SettingsFile "\\Data\\SKSE\\Plugins\\SkyrimReloaded.dll.config"
#define ShadersPath "Data\\Shadersfx\\SkyrimReloaded\\Shaders\\"
#define EffectsPath "Data\\Shadersfx\\SkyrimReloaded\\Effects\\"
#define TerrainShaders ""
#define BloodShaders ""
static const char* IntroMovie = "";
static const char* MainMenuMovie = "";
static const char* MainMenuMusic = "";
static char* TitleMenu = "Skyrim Reloaded - Settings";

// to review
static const char* WeatherColorTypes[TESWeather::kNumColorTypes] = { "SkyUpper", "Fog", "CloudsLower", "Ambient", "Sunlight", "Sun", "Stars", "SkyLower", "Horizon", "CloudsUpper" };
static const char* WeatherTimesOfDay[TESWeather::kNumTimeOfDay] = { "Sunrise", "Day", "Sunset", "Night" };
static const char* WeatherHDRTypes[14] = { "EyeAdaptation", "BlurRadius", "BlurPasses", "EmissiveMult", "TargetLUM", "UpperLUMClamp", "BrightScale", "BrightClamp", "LUMRampNoTex", "LUMRampMin", "LUMRampMax", "SunlightDimmer", "GrassDimmer", "TreeDimmer" };