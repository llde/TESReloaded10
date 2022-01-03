#pragma once

#define CommandPrefix "SR"

#define SettingsFile "\\Data\\SKSE\\Plugins\\SkyrimReloaded.dll.config"
#define ShadersPath "Data\\Shadersfx\\SkyrimReloaded\\Shaders\\"
#define EffectsPath "Data\\Shadersfx\\SkyrimReloaded\\Effects\\"
static const char* IntroMovie = "";
static const char* MainMenuMovie = "";
static const char* MainMenuMusic = "";

#define kMenuRenderedTexture 0x01B2E8D8

#define cloudSpeedLower general.cloudSpeedLower
#define cloudSpeedUpper general.cloudSpeedUpper
#define sunDamage general.sunDamage
#define sunGlare general.sunGlare
#define transDelta general.transDelta
#define windSpeed general.windSpeed


static const UInt32 kRenderInterface = 0x00A5CB57;
static const UInt32 kRenderInterfaceReturn = 0x00A5CB5C;
static const UInt32 kRenderInterfaceMethod = 0x00A623F0;
static const UInt32 kRenderingGeometry = 0x00CAFFC0;
static const UInt32 kRenderingGeometryReturn = 0x00CAFFC5;
static const UInt32 kSetShadowDistance = 0x00CBB140;
static const UInt32 kSetShadowDistanceReturn = 0x00CBB146;
static const UInt32 kSetShadowDistanceShader = 0x00CB7365;
static const UInt32 kSetShadowDistanceShaderReturn = 0x00CB736D;
static NiGeometry* Geometry = NULL;



static const UInt32 kSetRegionEditorName = 0x0048BEE4;
static const UInt32 kSetRegionEditorNameReturn = 0x0048BEEA;
static const UInt32 kSetWeatherEditorName = 0x004EF358;
static const UInt32 kSetWeatherEditorNameReturn = 0x004EF35E;


#define wtype gameData.type
static const UInt32 kHitEventHook = 0x006E4837;
static const UInt32 kHitEventReturn = 0x006E483E;

#define process processManager->process


#define kMessageBoxServeSentenceText 0x01B19068
#define kMessageBoxButtonYes 0x01B17FA0
#define kMessageBoxButtonNo 0x01B17FAC
#define SleepingState 7


static const UInt32 kCreateDeviceHook = 0x00CD8B6F;
static const UInt32 kCreateDeviceReturn = 0x00CD8B74;


static char* TitleMenu = "Skyrim Reloaded - Settings";

#define kRectStyle 0x0069D832
#define kWindowStyle 0x0069D877


#define kCameraWorldTranslate 0x01B913FC

#define sunGlare general.sunGlare
#define windSpeed general.windSpeed
#define weatherType general.weatherType
#define TerrainShaders ""
#define BloodShaders ""