#[allow(non_snake_case)]

use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;

//TODO SPlit config into multiple files
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct BloodLens{
    Chance : u32,
	ColorR : f64,
	ColorG : f64,
	ColorB : f64,
	Intensity : f64,
	Time : f64
}

impl Default for BloodLens{
	fn default() ->Self{
		Self { Chance: 20, ColorR: 0.92 , ColorG: 0.16, ColorB: 0.16, Intensity: 0.8, Time: 900.0 }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct AmbientOcclusionInner{
	Enabled : bool,
	Samples : u32,
	StrengthMultiplier : f64,
	ClampStrength : f64,
	AngleBias : f64,
	Range : f64,
	LumThreshold : f64,
	BlurDropThreshold : f64,
	BlurRadiusMultiplier : f64
}


#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct AmbientOcclusion{
	#[deserialize_over]
	Exterior : AmbientOcclusionInner,
	#[deserialize_over]
	Interior : AmbientOcclusionInner
}

impl Default for AmbientOcclusion{
	fn default() -> Self {
		let exterior = 	AmbientOcclusionInner{Enabled : true, Samples : 20, StrengthMultiplier : 1.0, ClampStrength : -0.5, AngleBias : 0.1, Range : 150.0, LumThreshold : 0.2, BlurDropThreshold : 3.0, BlurRadiusMultiplier : 1.0};
		let interior = AmbientOcclusionInner{Enabled : true, Samples : 20, StrengthMultiplier : 1.0, ClampStrength : -0.5, AngleBias : 0.1, Range : 1000.0, LumThreshold : 0.2, BlurDropThreshold : 3.0, BlurRadiusMultiplier : 1.0};
	    Self { Exterior: exterior, Interior:  interior }
	}
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct Bloom{
	BloomIntensity : f64,
	OriginalIntensity : f64,
	BloomSaturation : f64,
	OriginalSaturation : f64,
	Luminance : f64,
	MiddleGray : f64,
	WhiteCutOff : f64
}

impl  Default for Bloom {
    fn default() -> Self {
	    Self { BloomIntensity : 1.4, OriginalIntensity : 1.0, BloomSaturation : 1.2, OriginalSaturation : 1.0, Luminance : 0.06, MiddleGray : 0.18, WhiteCutOff : 0.8 }
	}
} 

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct GodRays{
	TimeEnabled : bool,
	SunGlareEnabled : bool,
	LightShaftPasses : u32,
	RayIntensity : f64,
	RayLength : f64,
	RayDensity : f64,
	RayVisibility : f64,
	Luminance : f64,
	GlobalMultiplier : f64,
	RayR : f64,
	RayG : f64,
	RayB : f64,
	Saturate : f64
}

impl  Default for GodRays {
    fn default() -> Self {
	    Self { TimeEnabled: false, SunGlareEnabled: true, LightShaftPasses: 45, RayIntensity: 3.2 ,RayLength : 0.98, RayDensity: 0.6, RayVisibility: 0.3, Luminance: 1.2, GlobalMultiplier: 3.0, RayR: 0.38, RayG: 0.54, RayB: 0.44, Saturate: 0.4}
	}
} 

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct WaterLens {
	TimeMultA : f64,
	TimeMultB : f64,
	Time : f64,
	Amount : f64,
	Viscosity : f64
}

impl Default for WaterLens{
	fn default() -> Self {
	    Self { TimeMultA: 0.1, TimeMultB: 0.2, Time : 180.0, Amount: 0.1, Viscosity: 0.05 }
	}
}



#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct SnowAccumulation {
	Amount : f64,
	Increase : f64,
	Decrease : f64,
	SunPower : f64,
	BlurNormDropThreshhold : f64,
	BlurRadiusMultiplier : f64
}

impl Default for SnowAccumulation {
	fn default() -> Self {
	    Self { Amount:1.6 , Increase:0.0005 , Decrease: 0.0001 , SunPower: 0.3, BlurNormDropThreshhold: 0.82, BlurRadiusMultiplier:  0.6}
	}
}


#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct WetWorld {
	Amount : f64,
	Increase : f64,
	Decrease : f64,
	PuddleCoeff_R : f64,
	PuddleCoeff_G : f64,
	PuddleCoeff_B : f64,
	PuddleSpecularMultiplier : f64
}

impl Default for  WetWorld {
	fn default() -> Self {
	    Self { Amount: 0.85, Increase: 0.001, Decrease: 0.0001, PuddleCoeff_R: 0.72, PuddleCoeff_G: 0.62, PuddleCoeff_B: 0.48, PuddleSpecularMultiplier: 0.2 }
	}
}			

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct LowHF{
	HealthLimit : f64,
	FatigueLimit : f64,
	LumaMultiplier : f64,
	BlurMultiplier : f64,
	VignetteMultiplier : f64,
	DarknessMultiplier : f64
}

impl Default for  LowHF {
	fn default() -> Self {
		Self { HealthLimit: 0.5, FatigueLimit: 0.25, LumaMultiplier: 1.0, BlurMultiplier: 0.2, VignetteMultiplier: 1.0, DarknessMultiplier: 1.0 }
	}
}


#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct DepthOfFieldInner{
	Enabled : bool,
	Mode : u8,
	DistantBlur : bool,
	DistantBlurStartRange : f64,
	DistantBlurEndRange : f64,
	BaseBlurRadius : f64,
	BlurFallOff : f64,
	Radius : f64,
	DiameterRange : f64,
	NearBlurCutOff : f64
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct DepthOfField{
	#[deserialize_over]
	FirstPerson : DepthOfFieldInner,
	#[deserialize_over]
	ThirdPerson : DepthOfFieldInner,
	#[deserialize_over]	
	VanityView : DepthOfFieldInner
}


impl Default for DepthOfField {
    fn default() -> Self {
	    let first = DepthOfFieldInner { Enabled: true, Mode: 0, DistantBlur: false, DistantBlurStartRange: 900.0, DistantBlurEndRange: 1000.0, BaseBlurRadius: 1.0, BlurFallOff: 2.0, Radius: 8.0, DiameterRange: 0.009, NearBlurCutOff: 0.8 };
	    let third = DepthOfFieldInner { Enabled: true, Mode: 0, DistantBlur: true, DistantBlurStartRange: 900.0, DistantBlurEndRange: 1000.0, BaseBlurRadius: 0.25, BlurFallOff: 2.5, Radius: 3.0, DiameterRange: 0.009, NearBlurCutOff: 0.8 };
	    let vanity = DepthOfFieldInner { Enabled: true, Mode: 0, DistantBlur: false, DistantBlurStartRange: 900.0, DistantBlurEndRange: 1000.0, BaseBlurRadius: 1.0, BlurFallOff: 2.0, Radius: 8.0, DiameterRange: 0.009, NearBlurCutOff: 0.8 };
		Self { FirstPerson: first, ThirdPerson: third , VanityView: vanity }
	}
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct Cinema {
	Mode : u8,
	AspectRatio : f64,
	VignetteDarkness : f64,
	VignetteRadius : f64
}
impl Default for Cinema {
    fn default() -> Self {
	    Self { Mode: 0, AspectRatio: 1.20 , VignetteDarkness:3.0 , VignetteRadius: 0.55 }
	}
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MotionBlurInner{
	Enabled : bool,
	GaussianWeight : f64,
	BlurScale : f64,
	BlurOffsetMax : f64,
	BlurCutOff : f64
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MotionBlur {
	#[deserialize_over]
	FirstPerson : MotionBlurInner,
	#[deserialize_over]
	ThirdPerson : MotionBlurInner
}

impl Default for MotionBlur {
	fn default() ->Self {
		MotionBlur {
			FirstPerson: MotionBlurInner { Enabled: true , GaussianWeight: 6.0 , BlurScale: 4.0, BlurOffsetMax: 24.0, BlurCutOff: 15.0 },
			ThirdPerson: MotionBlurInner { Enabled: false, GaussianWeight: 6.0, BlurScale: 4.0, BlurOffsetMax: 24.0, BlurCutOff: 15.0 } }
	}
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct Sharpening {
	Strength :f64,
	Clamp : f64,
	Offset : f64
	
} 

impl Default for Sharpening {
	fn default() -> Self {
	    Self { Strength: 0.75, Clamp: 0.1, Offset: 2.0 }
	}
}
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct SpecularInner{
	Strength : f64,
	BlurMultiplier : f64,
	Glossiness : f64,
	DistanceFade : u32
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Specular {
	#[deserialize_over]
	Exterior : SpecularInner,
	#[deserialize_over]
	Rain : SpecularInner
}

impl Default for Specular{
	fn default() -> Self {
	    Self { 
			Exterior: SpecularInner { Strength: 0.6, BlurMultiplier:1.0 , Glossiness: 15.9, DistanceFade: 5000 },
			Rain: SpecularInner { Strength: 2.5, BlurMultiplier:1.0 , Glossiness: 8.0, DistanceFade: 2000 }  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct VolumetricFog{
	Exponent : f64,
	ColorCoeff : f64,
	Amount : f64,
	MaxDistance : u32
}

impl Default for VolumetricFog  {
    fn default() -> Self {
	    Self { Exponent: 2.0, ColorCoeff: 1.8, Amount: 0.9, MaxDistance: 100000  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Coloring{
	Strength : f64,
	BaseGamma : f64,
	Fade : f64,
	Contrast : f64,
	Saturation : f64,
	Bleach : f64,
	BleachLuma : f64,
	ColorCurve : f64,
	ColorCurveR : f64,
	ColorCurveG : f64,
	ColorCurveB : f64,
	EffectGamma : f64,
	EffectGammaR : f64,
	EffectGammaG : f64,
	EffectGammaB : f64,
	Linearization : f64
}

impl Default for Coloring  {
    fn default() -> Self {
		Self { Strength: 0.5, BaseGamma: 1.6, Fade: 0.0, Contrast: 0.8, Saturation: -0.1, Bleach: 0.1, BleachLuma: 0.2, ColorCurve: 1.2, ColorCurveR: 0.9, ColorCurveG: 1.0, ColorCurveB: 1.0, EffectGamma: 0.9, EffectGammaR: 1.0, EffectGammaG: 1.0 , EffectGammaB: 1.0 , Linearization: 1.1 }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Effects{
	#[deserialize_over]
    BloodLens :  BloodLens,
    #[deserialize_over]
	AmbientOcclusion : AmbientOcclusion,
    #[deserialize_over]
	Bloom : Bloom,
	#[deserialize_over]
	GodRays : GodRays,
	#[deserialize_over]
	WaterLens : WaterLens,
	#[deserialize_over]
	SnowAccumulation : SnowAccumulation,
	#[deserialize_over]
	WetWorld : WetWorld,
	#[deserialize_over]
	LowHF : LowHF,
	#[deserialize_over]
	DepthOfField : DepthOfField,
	#[deserialize_over]
	Cinema : Cinema,
	#[deserialize_over]
	MotionBlur : MotionBlur,
	#[deserialize_over]
	Sharpening : Sharpening,
	#[deserialize_over]
	Specular : Specular,
	#[deserialize_over]
	VolumetricFog : VolumetricFog,
	#[deserialize_over]
	Coloring : Coloring
}

impl Default for Effects{
	fn default() -> Self {
    		Self { BloodLens: BloodLens::default(), AmbientOcclusion : AmbientOcclusion::default(), Bloom : Bloom::default(), GodRays : GodRays::default(), WaterLens : WaterLens::default(), SnowAccumulation : SnowAccumulation::default(), WetWorld : WetWorld::default(), LowHF : LowHF::default(), DepthOfField :DepthOfField::default(), Cinema : Cinema::default(), MotionBlur : MotionBlur::default(), Sharpening : Sharpening::default(), Specular : Specular::default(), VolumetricFog : VolumetricFog::default(), Coloring : Coloring::default() }
	}
}