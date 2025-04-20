
use std::ffi::CString;
use crate::sys_string::{SysString};
use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;

/*Configuration for the Main Configuration file*/
#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct Config{
	#[deserialize_over]
    Main : MainStruct,
    #[deserialize_over]
    WaterEngine: WaterEngine,
	#[deserialize_over]
    Develop : DevelopStruct,
    #[deserialize_over]
    Culling : CullingEngine,
	#[deserialize_over]
    FlyCam : FlyCamStruct,
	#[deserialize_over]
    SleepingMode : SleepingModeStruct,
	#[deserialize_over]
    LowHFSound : LowHFSoundStruct,
	#[deserialize_over]
    Shaders : ShadersStruct,
	#[deserialize_over]
    Effects : EffectsStruct,
	#[deserialize_over]
    Menu : MenuStruct,
	#[deserialize_over]
	ShadowsForm : ShadowFormsStruct,
	#[deserialize_over]
    ShadowsExterior : ShadowsExteriorStruct,
	#[deserialize_over]
    ShadowsInterior : ShadowsInteriorStruct,
}

impl Default for Config{
    fn default() -> Config{
        Config{
            Main : MainStruct::default(),
            WaterEngine : WaterEngine::default(),
            Develop : DevelopStruct::default(),
            Culling : CullingEngine::default(),
            FlyCam : FlyCamStruct::default(),
            SleepingMode : SleepingModeStruct::default(),
            LowHFSound : LowHFSoundStruct::default(),
            Shaders : ShadersStruct::default(),
            Effects : EffectsStruct::default(),
            Menu : MenuStruct::default(),
            ShadowsForm : ShadowFormsStruct::default(),
            ShadowsExterior: ShadowsExteriorStruct::default(),
            ShadowsInterior: ShadowsInteriorStruct::default(),
        }
    }
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MainStruct {
    RemoveUnderwater : bool,
    RemovePrecipitations : bool,
	RemoveFogPass : bool,
    MemoryTextureManagement : bool,
	GrassMode : bool,
    ReplaceIntro : bool,
    AnisotropicFilter : u8,
    ScreenshotKey : u32,
    FarPlaneDistance : f32,
	TestDirectionLight : bool,
}

impl Default for MainStruct{
    fn default() -> Self{
        MainStruct{
            RemoveUnderwater : true,
            RemovePrecipitations : true,
            MemoryTextureManagement : true,
			RemoveFogPass : false,
			GrassMode : true,
            ReplaceIntro : false,
            AnisotropicFilter : 4,
            ScreenshotKey : 87,
            FarPlaneDistance : 283840.0,
			TestDirectionLight : false,
        }
    }
}
/*Some settings are related to OR only, while CameraMode will be removed from NVR*/
#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub	struct DevelopStruct {
    CompileShaders : u8,  // 1 Compile All, 2 Compile modified or missing only, 3 Compile only in menu
    CompileEffects : u8,
    DebugMode : bool,       // enables hotkeys to print textures
    TraceShaders : u8,
}

impl Default for DevelopStruct{
    fn default() -> Self{
        DevelopStruct{
            CompileShaders : 2,
            CompileEffects : 2,
            DebugMode : false,
            TraceShaders : 25
        }
    }

}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub	struct LowHFSoundStruct {
    HealthEnabled : bool,  // 1 Compile All, 2 Compile modified or missing only, 3 Compile only in menu
    FatigueEnabled : bool,
    HealthCoeff : f32,       // enables hotkeys to print textures
    FatigueCoeff : f32,
}

impl Default for LowHFSoundStruct{
    fn default() -> Self{
        LowHFSoundStruct{
            HealthEnabled : true,
            FatigueEnabled : true,
            HealthCoeff : 0.5,
            FatigueCoeff : 0.5,
        }
    }
}
#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub	struct FlyCamStruct {
    Enabled : bool,
    ScrollMultiplier : f32,
    KeyAdd : u16,
    KeySubtract : u16,
    StepValue : f32
}

impl Default for FlyCamStruct{
    fn default() -> Self{
        FlyCamStruct{
            Enabled : true,
            ScrollMultiplier : 2.0,
            KeyAdd : 78,
            KeySubtract : 74,
            StepValue : 1.0,
        }
    }
}
#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct ShadersStruct {
    Blood : bool,
    Grass : bool,
    HDR : bool,
    NightEye : bool,
    POM : bool,
    Skin : bool,
    Terrain : bool,
    Water : bool,
    Extra : bool,
}

impl Default for ShadersStruct{
    fn default() -> Self{
        ShadersStruct{
            Blood : true,
            Grass : false,
            HDR : true,
            NightEye : true,
            POM : true,
            Skin : true,
            Terrain : true,
            Water : true,
            Extra : true,
        }
    }
}
#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
struct EffectsStruct {
    AmbientOcclusion : bool,
    BloodLens : bool,
    Bloom : bool,
    Cinema : bool,
    Coloring : bool,
    DepthOfField : bool,
    GodRays : bool,
    LowHF : bool,
    MotionBlur : bool,
    Rain : bool,
    Snow : bool,
    Sharpening : bool,
    SnowAccumulation : bool,
    Underwater : bool,
    WaterLens : bool,
    WetWorld : bool,
    VolumetricFog : bool,
    ShadowsExteriors : bool,
    ShadowsInteriors : bool,
    Specular : bool,
    Extra : bool,
}

impl Default for EffectsStruct{
    fn default() -> Self{
        EffectsStruct{
            AmbientOcclusion : false,
            BloodLens : true,
            Bloom : true,
            Cinema : true,
            Coloring : true,
            DepthOfField : false,
            GodRays : true,
            LowHF : true,
            MotionBlur : false,
            Rain : true,
            Snow : true,
            Sharpening : true,
            SnowAccumulation : true,
            Underwater : true,
            WaterLens : true,
            WetWorld : true,
            VolumetricFog : false,
            ShadowsExteriors : true,
            ShadowsInteriors : false,
            Specular : true,
            Extra : true,
        }
    }
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MenuStruct {
    TextFont : SysString,
    TextFontStatus : SysString,
    TextSize : u8,
    TextSizeStatus : u8,
	TextColorNormal : [u8; 3],
	TextShadowColorNormal : [u8;3],
	TextColorSelected : [u8; 3],
	TextShadowColorSelected : [u8 ; 3],
    KeyEnable : u8,
    KeyUp : u8,
    KeyDown : u8,
    KeyLeft : u8,
    KeyRight : u8,
    KeyPageUp : u8,
    KeyPageDown : u8,
    KeyAdd : u8,
    KeySubtract : u8,
    KeySave : u8,
    KeyEditing : u8
}

impl Default for MenuStruct{
    fn default() -> Self{
        MenuStruct {
            TextFont : CString::new("Calibri").unwrap().into(),
            TextFontStatus : CString::new("Consolas").unwrap().into(),
            TextSize : 22,
            TextSizeStatus : 12,
			TextColorNormal : [240,200,80],
			TextShadowColorNormal : [50,50,50],
			TextColorSelected : [255,255,255],
			TextShadowColorSelected : [50,50,50],
            KeyEnable : 24,
            KeyUp : 200,
            KeyDown : 208,
            KeyLeft : 203,
            KeyRight : 205,
            KeyPageUp : 201,
            KeyPageDown : 209,
            KeyAdd : 78,
            KeySubtract : 74,
            KeySave : 28,
            KeyEditing : 156
        }
    }
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct SleepingModeStruct{
    Enabled : bool,
    Mode : u8
}

impl Default for SleepingModeStruct{
    fn default() -> Self{
        SleepingModeStruct{
            Enabled: false,
            Mode: 0,
        }
    }
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowFormsStruct {
	Activators : bool,
	Actors : bool,
	Apparatus: bool,
	Books : bool,
	Containers : bool,
	Doors : bool,
	Furniture : bool,
	Misc : bool,
	Statics : bool,
	Terrain : bool,
	Trees : bool,
	Lod : bool, 
	MinRadius : f32,
	Alpha : bool,
}

impl Default for ShadowFormsStruct{
    fn default() -> Self{
		ShadowFormsStruct {
			Activators: true, Actors: true , Apparatus: true, Books: true, Containers: true, Doors: true, Furniture: true, Misc: true, Statics: true, Terrain: true, Trees: true, Lod: false, MinRadius: 10.0, Alpha : true
			
		}
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowsExteriorStruct{
	Enabled : bool,
	ShadowMode : u8,
    ShadowMapResolution : u32,
    ShadowMapRadius : f32,
    ShadowMapFarPlane : f32,
    BlurShadowMaps : bool,
}
/*Other Shadows Related settings will be in the Shader configuration
TODO what about cascade specific settings??
 */

impl Default for ShadowsExteriorStruct{
    fn default() -> Self{
        ShadowsExteriorStruct{
			Enabled : true,
			ShadowMode : 1,
            ShadowMapResolution: 2048,
            ShadowMapRadius: 8000.0,
            ShadowMapFarPlane: 32768.0,
            BlurShadowMaps: true,
        }
    }
}


#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowsInteriorStruct{
	Enabled : bool,
	ShadowMode : u8,
    ShadowCubeMapResolution : u32,
    LightPoints : u8,
    TorchesCastShadows : bool,
	LightRadiusMult : f32
}

impl Default for ShadowsInteriorStruct{
    fn default() -> Self{
        ShadowsInteriorStruct {
			Enabled : false,
			ShadowMode : 1,
            ShadowCubeMapResolution: 2048,
            LightPoints: 4,
            TorchesCastShadows: true,
			LightRadiusMult : 1.0
        }
    }
}

#[derive(Serialize, Deserialize,DeserializeOver, Debug)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct CullingEngine{
    EnableMainCulling: bool,
    EnableRelfectionCulling : bool,
    CullMinSize : f32,
    CullReflectionMinSize : f32
}

impl Default for CullingEngine{
    fn default() -> Self {
        CullingEngine {
            EnableMainCulling : true,
            EnableRelfectionCulling : true,
            CullMinSize : 10.0,
            CullReflectionMinSize : 100.0
        }
    }

}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct WaterEngine{
    ReflectionMapSize : u16,
    SetAtmoshpere : bool,
}

impl Default for WaterEngine{
    fn default() -> Self{
        WaterEngine{
            ReflectionMapSize : 512,
            SetAtmoshpere : false,
        }
    }
}
