#pragma once

#define CommandPrefix "OR"
#define SettingsFile "\\Data\\OBSE\\Plugins\\OblivionReloaded.dll.config"
#define FastMMFile "\\Data\\OBSE\\Plugins\\OblivionReloadedFastMM.dll"
#define ShadersPath "Data\\Shaders\\OblivionReloaded\\Shaders\\"
#define EffectsPath "Data\\Shaders\\OblivionReloaded\\Effects\\"
#define AnimString "_OR_"
#define RenderStateArgs 0
#define kFormType_MoveableStatic kFormType_Stat
#define TerrainShaders "SLS2001.vso SLS2001.pso SLS2062.vso SLS2066.pso SLS2063.vso SLS2067.pso SLS2064.vso SLS2068.pso"
#define BloodShaders "GDECALS.vso GDECAL.pso SLS2040.vso SLS2046.pso"
static const char* IntroMovie = "ORGameStudios.bik";
static const char* MainMenuMovie = "ORMainMenu.bik";
static const char* MainMenuMusic = "Special\\ORMainMenu.mp3";
static const char* TitleMenu = "Oblivion Reloaded - Settings";
static const char* WeatherColorTypes[TESWeather::kNumColorTypes] = { "SkyUpper", "Fog", "CloudsLower", "Ambient", "Sunlight", "Sun", "Stars", "SkyLower", "Horizon", "CloudsUpper" };
static const char* WeatherTimesOfDay[TESWeather::kNumTimeOfDay] = { "Sunrise", "Day", "Sunset", "Night" };
static const char* WeatherHDRTypes[14] = { "EyeAdaptation", "BlurRadius", "BlurPasses", "EmissiveMult", "TargetLUM", "UpperLUMClamp", "BrightScale", "BrightClamp", "LUMRampNoTex", "LUMRampMin", "LUMRampMax", "SunlightDimmer", "GrassDimmer", "TreeDimmer" };
