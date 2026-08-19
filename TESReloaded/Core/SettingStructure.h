#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>
#include "SettingsStructureCommon.h"

namespace ffi {

enum class Game {
  Oblivion,
  NewVegas,
};

enum class ShadowType : uint8_t {
  DISABLED,
  VSM,
  ESM,
  ESSM,
};

enum class MoveCursor {
  Up,
  Down,
  Left,
  Right,
};

enum class OperationSetting {
  Add,
  Sub,
};

enum class Errors {
  None,
  InvalidLog,
};

struct MainStruct {
  /// Remove vanilla underwater pass effect 
  bool RemoveUnderwater;
  /// Remove vanilla precipitation pass effect (rain, snow)
  bool RemovePrecipitations;
  /// Remove vanilla fog pass effect (UNSTABLE)
  bool RemoveFogPass;
  /// Enable memory texture management (May cause Alt+Tab crash or hangs with full screen mode)
  bool MemoryTextureManagement;
  /// Enable grass mode. This is separated from the Grass shader
  bool GrassMode;
  /// Replace the intro video and the main menu background video with a custom one
  bool ReplaceIntroAndMainMenuBackgroundVideos;
  /// Override the default anisotropic filter value (0-16)
  uint8_t AnisotropicFilter;
  /// Key (in dx scancodes) to take a screenshot
  uint32_t ScreenshotKey;
  /// Override the default far plane distance (in game units)
  float FarPlaneDistance;
  /// Enable directional light  as sun source instead of the normal sun position (for testing purposes only)
  bool TestDirectionLight;
};

struct WaterEngine {
  /// Water reflection map size (prefers power of 2 sizes)
  uint16_t ReflectionMapSize;
  /// Enable or disable atmosphere  changes when underwater (UNSTABLE).
  bool SetAtmoshpere;
};

struct DevelopStruct {
  /// 0 disable effects compilation, 1 Compile All effects when enabled, 2 Compile modified or missing only, 3 Compile only in menu
  uint8_t CompileEffects;
  /// 0 disable shaders compilation, 1 Compile All shaders when enabled, 2 Compile modified or missing only, 3 Compile only in menu
  uint8_t CompileShaders;
  /// enables hotkeys to print reneder data (may change between versions)
  bool DebugMode;
  /// Key (in dx scancodes) to toggle debug log for the frame and the render window
  uint8_t TraceShaders;
};

struct CullingEngine {
  /// Enable or disable the main culling engine. This will cull objects based on their size and distance from the camera.
  bool EnableMainCulling;
  /// Enable or disable the reflection culling engine. This will cull objects based on their size and distance from the camera when rendering reflections.
  bool EnableRelfectionCulling;
  /// Minimum size (in game units) for an object to be rendered. Objects smaller than this size will be culled.
  float CullMinSize;
  /// Minimum size (in game units) for an object to be rendered in reflections. Objects smaller than this size will be culled.
  float CullReflectionMinSize;
};

struct FlyCamStruct {
  /// Enable fly camera mode (true or false)
  bool Enabled;
  /// Multiplier for the scroll wheel to change the fly camera speed
  float ScrollMultiplier;
  /// Key (in dx scancodes) to increase the fly camera speed
  uint16_t KeyAdd;
  /// Key (in dx scancodes) to decrease the fly camera speed
  uint16_t KeySubtract;
  /// Step value for the fly camera speed change
  float StepValue;
};

struct SleepingModeStruct {
  /// Enable sleeping mode (true or false)
  bool Enabled;
  /// Sleeping mode type (0 = Disabled, 1 = Sleep, 2 = Wait)
  uint8_t Mode;
};

struct LowHFSoundStruct {
  /// Enable LowHF effect for health
  bool HealthEnabled;
  /// Enable LowHF effect for fatigue
  bool FatigueEnabled;
  /// Coefficient for LowHF effect for health (0.0 - 1.0)
  float HealthCoeff;
  /// Coefficient for LowHF effect for fatigue (0.0 - 1.0)
  float FatigueCoeff;
};

struct ShadersStruct {
  /// Eanble OR Blood shader
  bool Blood;
  /// Enable OR Grass shader
  bool Grass;
  /// Enable OR HDR shader
  bool HDR;
  /// Enable OR NightEye shader
  bool NightEye;
  /// Enable OR POM shader
  bool POM;
  /// Enable OR Skin shader
  bool Skin;
  /// Enable OR Terrain shader
  bool Terrain;
  /// Enable OR Water shader
  bool Water;
  /// Enable custom extra shaders, if provided in the shaders folder, for shaders not included in the other shaders sets. 
  bool Extra;
};

struct EffectsStruct {
  /// Enable OR Ambient Occlusion effect
  bool AmbientOcclusion;
  /// Enable OR Blood Lens effect
  bool BloodLens;
  /// Enable OR Bloom effect
  bool Bloom;
  /// Enable OR Cinema effect
  bool Cinema;
  /// Enable OR Coloring effect
  bool Coloring;
  /// Enable OR Depth of Field effect
  bool DepthOfField;
  /// Enable OR God Rays effect
  bool GodRays;
  /// Enable OR LowHF effect
  bool LowHF;
  /// Enable OR Motion Blur effect
  bool MotionBlur;
  /// Enable OR Rain effect 
  bool Rain;
  /// Enable OR Snow effect
  bool Snow;
  /// Enable OR Sharpening effect
  bool Sharpening;
  /// Enable OR Snow Accumulation effect
  bool SnowAccumulation;
  /// Enable OR Underwater effect
  bool Underwater;
  /// Enable OR Water Lens effect
  bool WaterLens;
  /// Enable OR Wet World effect
  bool WetWorld;
  /// Enable OR Volumetric Fog effect
  bool VolumetricFog;
  /// Enable OR Shadows Exteriors effect.  This doesn't disable the underlying system.
  bool ShadowsExteriors;
  /// Enable OR Shadows Interiors effect. This doesn't disable the underlying system.
  bool ShadowsInteriors;
  /// Enable OR Specular effect
  bool Specular;
  /// Enable OR Extra effect. These effects aren't triggered automatically by the engine, but can be triggered by scripts or, in future, by obse plugins.
  bool Extra;
};

///   * Represent a null terminated string, passable to FFI. Use C structure alignment rules
///   * Allocated from the LIBC allocator, modifiable from FFI.
///   * SAFETY:
///   * Modifying the struct from C++ require care: changing the string require carefully setting
///   * length and capacity, as well keeping the null terminator and avoid null bytes inside the string,
///   * and keep character representable as UTF8
///   * The Rust side should instead take care of avoiding NULL bytes in the middle of the string, as
///   * c strings use only one NULL byte as string terminator
/// TODO create a FFI API for SysString manipulations
struct SysString {
  char *data;
  uintptr_t length;
  uintptr_t capacity;
};

struct MenuStruct {
  /// Font used for the menu text
  SysString TextFont;
  /// Font used for the menu status text
  SysString TextFontStatus;
  /// Size of the menu text
  uint8_t TextSize;
  /// Size of the menu status text
  uint8_t TextSizeStatus;
  /// Color of the menu text in normal state (RGB)
  uint8_t TextColorNormal[3];
  /// Color of the menu text shadow in normal state (RGB)
  uint8_t TextShadowColorNormal[3];
  /// Color of the menu text in selected state (RGB)
  uint8_t TextColorSelected[3];
  /// Color of the menu text shadow in selected state (RGB)
  uint8_t TextShadowColorSelected[3];
  /// Key (in dx scancodes) to enable the menu
  uint8_t KeyEnable;
  /// Key (in dx scancodes) to navigate up in the menu
  uint8_t KeyUp;
  /// Key (in dx scancodes) to navigate down in the menu
  uint8_t KeyDown;
  /// Key (in dx scancodes) to navigate left in the menu
  uint8_t KeyLeft;
  /// Key (in dx scancodes) to navigate right in the menu
  uint8_t KeyRight;
  /// Key (in dx scancodes) to navigate page up in the menu
  uint8_t KeyPageUp;
  /// Key (in dx scancodes) to navigate page down in the menu
  uint8_t KeyPageDown;
  /// Key (in dx scancodes) to increase a value in the menu
  uint8_t KeyAdd;
  /// Key (in dx scancodes) to decrease a value in the menu
  uint8_t KeySubtract;
  /// Key (in dx scancodes) to save the configuration in the menu or exiting editing mode saving the new value
  uint8_t KeySave;
  /// Key (in dx scancodes) to enter editing mode in the menu
  uint8_t KeyEditing;
};

struct ShadowFormsStruct {
  /// Enable shadow rendering for activators
  bool Activators;
  /// Enable shadow rendering for actors
  bool Actors;
  /// Enable shadow rendering for apparatus objects
  bool Apparatus;
  /// Enable shadow rendering for books
  bool Books;
  /// Enable shadow rendering for containers
  bool Containers;
  /// Enable shadow rendering for doors
  bool Doors;
  /// Enable shadow rendering for furniture objects
  bool Furniture;
  /// Enable shadow rendering for miscellaneous objects
  bool Misc;
  /// Enable shadow rendering for static objects
  bool Statics;
  /// Enable shadow rendering for terrain
  bool Terrain;
  /// Enable shadow rendering for trees
  bool Trees;
  /// Enable shadow rendering for LOD objects
  bool Lod;
  /// Minimum radius for shadow rendering (in game units)
  float MinRadius;
  /// Enable alpha when rendering shadows 
  bool Alpha;
};

struct ShadowsExteriorStruct {
  /// Shadows engine enabled (true or false). This disable both the shadowmaps and the orthomap
  bool Enabled;
  /// Shadow engine type (DISABLED, VSM, ESM, ESSM)
  ShadowType ShadowMode;
  /// Shadow map resolution (prefers power of 2 sizes)
  uint32_t ShadowMapResolution;
  /// Shadow map radius (in game units) for cascade generation
  float ShadowMapRadius;
  /// Shadow map far plane (in game units) for cascade generation
  float ShadowMapFarPlane;
  /// Blur shadow maps
  bool BlurShadowMaps;
};

struct ShadowsInteriorStruct {
  /// Enable interior shadows. This disable the underlying system. 
  bool Enabled;
  /// Shadow engine type. 
  uint8_t ShadowMode;
  /// Shadow cube map resolution (prefers power of 2 sizes)
  uint32_t ShadowCubeMapResolution;
  /// Number of light points to use for interior shadows (1-8)
  uint8_t LightPoints;
  /// Enable or disable torches casting shadows in interiors
  bool TorchesCastShadows;
  /// Multiplier for the light radius used for interior shadows //TODO!!: check
  float LightRadiusMult;
};

struct Config {
  /// Main configuration settings
  MainStruct Main;
  /// Water (non shader related) settings
  WaterEngine WaterEngine;
  DevelopStruct Develop;
  CullingEngine Culling;
  FlyCamStruct FlyCam;
  SleepingModeStruct SleepingMode;
  LowHFSoundStruct LowHFSound;
  ShadersStruct Shaders;
  EffectsStruct Effects;
  MenuStruct Menu;
  ShadowFormsStruct ShadowsForm;
  ShadowsExteriorStruct ShadowsExterior;
  ShadowsInteriorStruct ShadowsInterior;
};

struct BloodLens {
  uint32_t Chance;
  double ColorR;
  double ColorG;
  double ColorB;
  double Intensity;
  double Time;
};

struct AmbientOcclusionInner {
  bool Enabled;
  uint32_t Samples;
  double StrengthMultiplier;
  double ClampStrength;
  double AngleBias;
  double Range;
  double LumThreshold;
  double BlurDropThreshold;
  double BlurRadiusMultiplier;
};

struct AmbientOcclusion {
  /// Ambient Occlusion is a post processing effect that darkens corners and crevices, simulating the way light behaves in real life. It can add depth and realism to the scene, but it can also be performance intensive. For exterior ambients
  AmbientOcclusionInner Exterior;
  /// Ambient Occlusion is a post processing effect that darkens corners and crevices, simulating the way light behaves in real life. It can add depth and realism to the scene, but it can also be performance intensive. For Interiors ambient  
  AmbientOcclusionInner Interior;
};

struct Bloom {
  double BloomIntensity;
  double OriginalIntensity;
  double BloomSaturation;
  double OriginalSaturation;
  double Luminance;
  double MiddleGray;
  double WhiteCutOff;
};

struct GodRays {
  bool TimeEnabled;
  bool SunGlareEnabled;
  uint32_t LightShaftPasses;
  double RayIntensity;
  double RayLength;
  double RayDensity;
  double RayVisibility;
  double Luminance;
  double GlobalMultiplier;
  double RayR;
  double RayG;
  double RayB;
  double Saturate;
};

struct WaterLens {
  double TimeMultA;
  double TimeMultB;
  double Time;
  double Amount;
  double Viscosity;
};

struct SnowAccumulation {
  double Amount;
  double Increase;
  double Decrease;
  double SunPower;
  double BlurNormDropThreshhold;
  double BlurRadiusMultiplier;
};

struct WetWorld {
  double Amount;
  double Increase;
  double Decrease;
  double PuddleCoeff_R;
  double PuddleCoeff_G;
  double PuddleCoeff_B;
  double PuddleSpecularMultiplier;
};

struct LowHF {
  double HealthLimit;
  double FatigueLimit;
  double LumaMultiplier;
  double BlurMultiplier;
  double VignetteMultiplier;
  double DarknessMultiplier;
};

struct DepthOfFieldInner {
  bool Enabled;
  uint8_t Mode;
  bool DistantBlur;
  double DistantBlurStartRange;
  double DistantBlurEndRange;
  double BaseBlurRadius;
  double BlurFallOff;
  double Radius;
  double DiameterRange;
  double NearBlurCutOff;
};

struct DepthOfField {
  DepthOfFieldInner FirstPerson;
  DepthOfFieldInner ThirdPerson;
  DepthOfFieldInner VanityView;
};

struct Cinema {
  uint8_t Mode;
  double AspectRatio;
  double VignetteDarkness;
  double VignetteRadius;
};

struct MotionBlurInner {
  bool Enabled;
  double GaussianWeight;
  double BlurScale;
  double BlurOffsetMax;
  double BlurCutOff;
};

struct MotionBlur {
  MotionBlurInner FirstPerson;
  MotionBlurInner ThirdPerson;
};

struct Sharpening {
  double Strength;
  double Clamp;
  double Offset;
};

struct SpecularInner {
  double Strength;
  double BlurMultiplier;
  double Glossiness;
  uint32_t DistanceFade;
};

struct Specular {
  SpecularInner Exterior;
  SpecularInner Rain;
};

struct VolumetricFog {
  double Exponent;
  double ColorCoeff;
  double Amount;
  uint32_t MaxDistance;
};

struct Coloring {
  double Strength;
  double BaseGamma;
  double Fade;
  double Contrast;
  double Saturation;
  double Bleach;
  double BleachLuma;
  double ColorCurve;
  double ColorCurveR;
  double ColorCurveG;
  double ColorCurveB;
  double EffectGamma;
  double EffectGammaR;
  double EffectGammaG;
  double EffectGammaB;
  double Linearization;
};

struct Effects {
  BloodLens BloodLens;
  AmbientOcclusion AmbientOcclusion;
  Bloom Bloom;
  GodRays GodRays;
  WaterLens WaterLens;
  SnowAccumulation SnowAccumulation;
  WetWorld WetWorld;
  LowHF LowHF;
  DepthOfField DepthOfField;
  Cinema Cinema;
  MotionBlur MotionBlur;
  Sharpening Sharpening;
  Specular Specular;
  VolumetricFog VolumetricFog;
  Coloring Coloring;
};

struct ShadowsExteriorShaderStruct {
  uint32_t Quality;
  double Darkness;
  double NightMinDarkness;
};

struct ShadowsInteriorShaderStruct {
  uint32_t Quality;
  double Darkness;
};

struct ShadowStruct {
  /// Parameters for exterior shadows
  ShadowsExteriorShaderStruct ShadowsExterior;
  /// Parameters for interior shadows
  ShadowsInteriorShaderStruct ShadowsInterior;
};

struct Rain {
  double DepthStep;
  double Speed;
};

struct Snow {
  double DepthStep;
  double Speed;
  double Flakes;
};

struct Water {
  double choppiness;
  double waveWidth;
  double waveSpeed;
  double reflectivity;
  double causticsStrength;
  double causticsStrengthS;
  double shoreFactor;
  double shoreMovement;
  double turbidity;
  double inScattCoeff;
  double inExtCoeff_R;
  double inExtCoeff_G;
  double inExtCoeff_B;
  double depthDarkness;
};

struct HDR {
  double ToneMapping;
  double ToneMappingBlur;
  double ToneMappingColor;
  double Linearization;
};

struct POM {
  double HeightMapScale;
  uint32_t MinSamples;
  uint32_t MaxSamples;
};

struct Skin {
  double Attenuation;
  double SpecularPower;
  double MaterialThickness;
  double RimScalar;
  double CoeffRed;
  double CoeffGreen;
  double CoeffBlue;
};

struct Terrain {
  double DistantNoise;
  double DistantSpecular;
  double NearSpecular;
  double MiddleSpecular;
};

struct Grass {
  bool WindEnabled;
  double WindCoefficient;
  uint32_t GrassDensity;
  double ScaleX;
  double ScaleY;
  double ScaleZ;
  double MinDistance;
  double MaxDistance;
};

struct Shaders {
  ShadowStruct Shadows;
  Rain Rain;
  Snow Snow;
  Water Water;
  HDR HDR;
  POM POM;
  Skin Skin;
  Terrain Terrain;
  Grass Grass;
};

extern "C" {

void SetGame(Game game);

Config *getConfiguration();

Effects *getEffectsConfiguration();

Shaders *getShadersConfiguration();

void LoadConfiguration();

void CreateFontRenderer(LPDIRECT3DDEVICE9 device);

void WriteVersionString(int32_t width, int32_t height, const int8_t *string);

void RenderConfigurationMenu(int32_t width, int32_t height);

void MoveActiveNode(MoveCursor mov);

void EditActiveSetting(OperationSetting mov, void (*callback)(const char*));

void SaveConfigurations();

void EnterEditorMode();

bool IsEditorMode();

void CloseEditorMode();

void AddCharToEditor(char ch);

Errors SetLogFile(FILE *file);

}  // extern "C"

}  // namespace ffi
