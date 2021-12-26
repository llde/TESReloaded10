#pragma once

#define CommandPrefix "OR"

#define SettingsFile "\\Data\\OBSE\\Plugins\\OblivionReloaded.dll.config"
#define FastMMFile "\\Data\\OBSE\\Plugins\\OblivionReloadedFastMM.dll"
#define ShadersPath "Data\\Shaders\\OblivionReloaded\\Shaders\\"
#define EffectsPath "Data\\Shaders\\OblivionReloaded\\Effects\\"
#define WaterReflectionMapSize 512
#define kSettingGridsToLoad 0x00B06A2C
#define kSettingMinGrassSize 0x00B09B20
#define kSettingGrassStartFadeDistance 0x00B09B10
#define kSettingGrassEndDistance 0x00B09B18
#define kSettingGrassWindMagnitudeMin 0x00B09B28
#define kSettingGrassWindMagnitudeMax 0x00B09B30
#define kSettingTexturePctThreshold 0x00B08B6C
#define kSettingMultiSample 0x00B06D0C
#define kSettingHDR 0x00B06DE4
static const char* IntroMovie = "ORGameStudios.bik";
static const char* MainMenuMovie = "ORMainMenu.bik";
static const char* MainMenuMusic = "Special\\ORMainMenu.mp3";
#define kMenuRenderedTexture 0x00B333E8


#define WeatherColorsSize TESWeather::kNumColorTypes * TESWeather::kNumTimeOfDay * 4

static const char* WeatherColorTypes[TESWeather::kNumColorTypes] = { "SkyUpper", "Fog", "CloudsLower", "Ambient", "Sunlight", "Sun", "Stars", "SkyLower", "Horizon", "CloudsUpper" };
static const char* WeatherTimesOfDay[TESWeather::kNumTimeOfDay] = { "Sunrise", "Day", "Sunset", "Night" };
static const char* WeatherHDRTypes[14] = { "EyeAdaptation", "BlurRadius", "BlurPasses", "EmissiveMult", "TargetLUM", "UpperLUMClamp", "BrightScale", "BrightClamp", "LUMRampNoTex", "LUMRampMin", "LUMRampMax", "SunlightDimmer", "GrassDimmer", "TreeDimmer" };

static const UInt32* SettingGridsToLoad = (UInt32*)kSettingGridsToLoad;
static UInt32* SettingMinGrassSize = (UInt32*)kSettingMinGrassSize;
static float* SettingGrassStartFadeDistance = (float*)kSettingGrassStartFadeDistance;
static float* SettingGrassEndDistance = (float*)kSettingGrassEndDistance;
static float* SettingGrassWindMagnitudeMin = (float*)kSettingGrassWindMagnitudeMin;
static float* SettingGrassWindMagnitudeMax = (float*)kSettingGrassWindMagnitudeMax;
static float* SettingTexturePctThreshold = (float*)kSettingTexturePctThreshold;
static const UInt32* SettingMultiSample = (UInt32*)kSettingMultiSample;
static const UInt8* SettingHDR = (UInt8*)kSettingHDR;


#define kDetectorWindowScale 0x004965A8
#define kDetectorWindowScaleReturn 0x0049660F
static const UInt32 kRenderInterface = 0x0057F3F3;
static const UInt32 kRenderInterfaceReturn = 0x0057F3F8;
static const UInt32 kRenderInterfaceMethod = 0x0070E0A0;
static const UInt32 kSkipFogPass = 0x007AE6F5;
static const UInt32 kSkipFogPassReturn = 0x007AE6FB;
static const UInt32 kDetectorWindowSetNodeName = 0x0049658E;
static const UInt32 kDetectorWindowCreateTreeView = 0x00495E1F;
static const UInt32 kDetectorWindowCreateTreeViewReturn = 0x00495E27;
static const UInt32 kDetectorWindowDumpAttributes = 0x004967C7;
static const UInt32 kDetectorWindowDumpAttributesReturn = 0x004967CD;
static const UInt32 kDetectorWindowConsoleCommand = 0x0040CC6C;
static const UInt32 kDetectorWindowConsoleCommandReturn = 0x0040CC73;



static const UInt32 kSetRegionEditorName = 0x004A32A6;
static const UInt32 kSetRegionEditorNameReturn = 0x004A33A6;
static const UInt32 kSetWeatherEditorName = 0x004EE04E;
static const UInt32 kSetWeatherEditorNameReturn = 0x004EE0EA;


#define wtype weaponType
static const UInt32 kHitEventHook = 0x005FF613;
static const UInt32 kHitEventReturn = 0x005FF618;