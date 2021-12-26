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



#define ORAnimString "_OR_"

static const UInt32 kNewAnimSequenceSingleHook = 0x0047414D;
static const UInt32 kNewAnimSequenceSingleReturn = 0x00474157;
static const UInt32 kRemoveSequenceHook = 0x004742B7;
static const UInt32 kRemoveSequenceReturn1 = 0x004742BF;
static const UInt32 kRemoveSequenceReturn2 = 0x004742CD;

static ActorAnimDataEx* AnimDataAnimation = NULL;



#define RenderStateArgs 0
#define kRockParams 0x00B46778
#define kRustleParams 0x00B46788
#define kWindMatrixes 0x00B467B8
static const UInt32 kRenderShadowMapHook = 0x0040C919;
static const UInt32 kRenderShadowMapReturn = 0x0040C920;
static const UInt32 kAddCastShadowFlagHook = 0x004B1A25;
static const UInt32 kAddCastShadowFlagReturn = 0x004B1A2A;
static const UInt32 kEditorCastShadowFlagHook = 0x005498DD;
static const UInt32 kEditorCastShadowFlagReturn = 0x005498E3;


static const UInt32 TimeInfoUpdate = 0x0047D170;
static const UInt32 kUpdateTimeInfoHook = 0x0040D8AB;
static const UInt32 kUpdateTimeInfoReturn = 0x0040D8B0;
static float* MPF = (float*)0x00B33E94;


static const UInt32 kWaterHeightMapHook = 0x0049D9FF;
static const UInt32 kWaterHeightMapReturn = 0x0049DA08;


#define WordSampler2D "sampler2D"
#define WordSampler3D "sampler3D"
#define WordSamplerCUBE "samplerCU"
#define WordSamplerDelimeter "};"
#define WordSamplerStateDelimeter ";"
#define WordRegister "register(s"
#define WordRegisterDelimeter ")"
#define WordTextureName "string ResourceName = \x22"
#define WordTextureNameDelimeter "\x22;"


#define RenderStateArgs 0
#define kFormType_MoveableStatic kFormType_Stat
static const UInt32 kNew1CollisionObjectHook = 0x00564529;
static const UInt32 kNew1CollisionObjectReturn = 0x0056452E;
static const UInt32 kNew2CollisionObjectHook = 0x0089E989;
static const UInt32 kNew2CollisionObjectReturn = 0x0089E98E;
static const UInt32 kNew3CollisionObjectHook = 0x0089EA1C;
static const UInt32 kNew3CollisionObjectReturn = 0x0089EA21;
static const UInt32 kDisposeCollisionObjectHook = 0x00532DD1;
static const UInt32 kDisposeCollisionObjectReturn = 0x00532DD8;
static const UInt32 kMaterialPropertyHook = 0x0089F7C6;
static const UInt32 kMaterialPropertyReturn1 = 0x0089F7CE;
static const UInt32 kMaterialPropertyReturn2 = 0x0089F8A0;
static const UInt32 kCoordinateJackHook = 0x008A3101;
static const UInt32 kCoordinateJackReturn1 = 0x008A3107;
static const UInt32 kCoordinateJackReturn2 = 0x008A3165;
static const UInt32 kObjectCullHook = 0x007073D6;
static const UInt32 kObjectCullReturn1 = 0x007073DC;
static const UInt32 kObjectCullReturn2 = 0x007073E7;

static const UInt32 kMemReallocHook = 0x00401E66;
static const UInt32 kMemReallocReturn = 0x00401EC7;
static const UInt32 kCreateTextureFromFileInMemory = 0x007610D3;


static const UInt32 kGrassHook = 0x004EBF87;
static const UInt32 kGrassReturn = 0x004EC4E8;