#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>
#include "SettingsStructureCommon.h"

namespace ffi {

enum class Errors {
  None,
  InvalidLog,
};

enum class Game {
  Oblivion,
  NewVegas,
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

struct MainStruct {
  bool RemoveUnderwater;
  bool RemovePrecipitations;
  bool RemoveFogPass;
  bool MemoryTextureManagement;
  bool GrassMode;
  bool ReplaceIntro;
  uint8_t AnisotropicFilter;
  uint32_t ScreenshotKey;
  float FarPlaneDistance;
  bool TestDirectionLight;
};

struct WaterEngine {
  uint16_t ReflectionMapSize;
  bool SetAtmoshpere;
};

struct DevelopStruct {
  uint8_t CompileShaders;
  uint8_t CompileEffects;
  bool DebugMode;
  uint8_t TraceShaders;
};

struct CullingEngine {
  bool EnableMainCulling;
  bool EnableRelfectionCulling;
  float CullMinSize;
  float CullReflectionMinSize;
};

struct FlyCamStruct {
  bool Enabled;
  float ScrollMultiplier;
  uint16_t KeyAdd;
  uint16_t KeySubtract;
  float StepValue;
};

struct SleepingModeStruct {
  bool Enabled;
  uint8_t Mode;
};

struct LowHFSoundStruct {
  bool HealthEnabled;
  bool FatigueEnabled;
  float HealthCoeff;
  float FatigueCoeff;
};

struct ShadersStruct {
  bool Blood;
  bool Grass;
  bool HDR;
  bool NightEye;
  bool POM;
  bool Skin;
  bool Terrain;
  bool Water;
  bool Extra;
};

struct EffectsStruct {
  bool AmbientOcclusion;
  bool BloodLens;
  bool Bloom;
  bool Cinema;
  bool Coloring;
  bool DepthOfField;
  bool GodRays;
  bool LowHF;
  bool MotionBlur;
  bool Rain;
  bool Snow;
  bool Sharpening;
  bool SnowAccumulation;
  bool Underwater;
  bool WaterLens;
  bool WetWorld;
  bool VolumetricFog;
  bool ShadowsExteriors;
  bool ShadowsInteriors;
  bool Specular;
  bool Extra;
};

///   * Represent a null terminated string, passable to FFI. Use C structure alignment rules   * Allocated from the LIBC allocator, modifiable from FFI.   * SAFETY:   * Modifying the struct from C++ require care: changing the string require carefully setting   * length and capacity, as well keeping the null terminator and avoid null bytes inside the string,   * and keep character representable as UTF8   * The Rust side should instead take care of avoiding NULL bytes in the middle of the string, as   * c strings use only one NULL byte as string terminator TODO create a FFI API for SysString manipulations
struct SysString {
  char *data;
  uintptr_t length;
  uintptr_t capacity;
};

struct MenuStruct {
  SysString TextFont;
  SysString TextFontStatus;
  uint8_t TextSize;
  uint8_t TextSizeStatus;
  uint8_t TextColorNormal[3];
  uint8_t TextShadowColorNormal[3];
  uint8_t TextColorSelected[3];
  uint8_t TextShadowColorSelected[3];
  uint8_t KeyEnable;
  uint8_t KeyUp;
  uint8_t KeyDown;
  uint8_t KeyLeft;
  uint8_t KeyRight;
  uint8_t KeyPageUp;
  uint8_t KeyPageDown;
  uint8_t KeyAdd;
  uint8_t KeySubtract;
  uint8_t KeySave;
  uint8_t KeyEditing;
};

struct ShadowFormsStruct {
  bool Activators;
  bool Actors;
  bool Apparatus;
  bool Books;
  bool Containers;
  bool Doors;
  bool Furniture;
  bool Misc;
  bool Statics;
  bool Terrain;
  bool Trees;
  bool Lod;
  float MinRadius;
  bool Alpha;
};

struct ShadowsExteriorStruct {
  bool Enabled;
  uint8_t ShadowMode;
  uint32_t ShadowMapResolution;
  float ShadowMapRadius;
  float ShadowMapFarPlane;
  bool BlurShadowMaps;
};

struct ShadowsInteriorStruct {
  bool Enabled;
  uint8_t ShadowMode;
  uint32_t ShadowCubeMapResolution;
  uint8_t LightPoints;
  bool TorchesCastShadows;
  float LightRadiusMult;
};

struct Config {
  MainStruct Main;
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
  AmbientOcclusionInner Exterior;
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
  ShadowsExteriorShaderStruct ShadowsExterior;
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

void IsEditorMode();

Errors SetLogFile(FILE *file);

} // extern "C"

} // namespace ffi
