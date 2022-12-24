use std::ffi::CString;
use crate::sys_string::SysString;
use serde::{Serialize, Deserialize};
type UInt16 = u16;
type UInt32 = u32;
type UInt8 = u8;
#[allow(non_snake_case)]

/*Configuration for the Main Configuration file*/
#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub struct Config{
    Main : MainStruct,
    Develop : DevelopStruct,
    FlyCam : FlyCamStruct,
    LowHFSound : LowHFSoundStruct,
    Shaders : ShadersStruct,
    Effects : EffectsStruct,
    Menu : MenuStruct
}

impl Config{
    pub fn new() -> Config{
        Config{
            Main : MainStruct::new(),
            Develop : DevelopStruct::new(),
            FlyCam : FlyCamStruct::new(),
            LowHFSound : LowHFSoundStruct::new(),
            Shaders : ShadersStruct::new(),
            Effects : EffectsStruct::new(),
            Menu : MenuStruct::new()
        }
    }
}

#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub struct MainStruct {
    RemoveUnderwater : bool,
    RemovePrecipitations : bool,
    MemoryTextureManagement : bool,
    ReplaceIntro : bool,
    AnisotropicFilter : UInt8,
    ScreenshotKey : UInt16,
    FarPlaneDistance : f32,
}

impl MainStruct{
    pub fn new() -> MainStruct{
        MainStruct{
            RemoveUnderwater : true,
            RemovePrecipitations : true,
            MemoryTextureManagement : true,
            ReplaceIntro : true,
            AnisotropicFilter : 4,
            ScreenshotKey : 87,
            FarPlaneDistance : 283840.0
        }
    }
}
/*Some settings are related to OR only, while CameraMode will be removed from NVR*/
#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub	struct DevelopStruct {
    CompileShaders : UInt8,  // 1 Compile All, 2 Compile modified or missing only, 3 Compile only in menu
    CompileEffects : UInt8,
    DebugMode : bool,       // enables hotkeys to print textures
    TraceShaders : UInt8,
}

impl DevelopStruct{
    pub fn new() -> DevelopStruct{
        DevelopStruct{
            CompileShaders : 2,
            CompileEffects : 2,
            DebugMode : true,
            TraceShaders : 25
        }
    }

}

#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub	struct LowHFSoundStruct {
    HealthEnabled : bool,  // 1 Compile All, 2 Compile modified or missing only, 3 Compile only in menu
    FatigueEnabled : bool,
    HealthCoeff : f32,       // enables hotkeys to print textures
    FatigueCoeff : f32,
}
impl LowHFSoundStruct{
    pub fn new() -> LowHFSoundStruct{
        LowHFSoundStruct{
            HealthEnabled : true,
            FatigueEnabled : true,
            HealthCoeff : 0.5,
            FatigueCoeff : 0.5
        }
    }
}
#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub	struct FlyCamStruct {
    Enabled : bool,
    ScrollMultiplier : f32,
    KeyAdd : UInt16,
    KeySubtract : UInt16,
    StepValue : f32
}

impl FlyCamStruct{
    pub fn new() -> FlyCamStruct{
        FlyCamStruct{
            Enabled : true,
            ScrollMultiplier : 2.0,
            KeyAdd : 78,
            KeySubtract : 74,
            StepValue : 1.0,
        }
    }
}
#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
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

impl ShadersStruct{
    pub fn new() -> ShadersStruct{
        ShadersStruct{
            Blood : false,
            Grass : false,
            HDR : false,
            NightEye : false,
            POM : false,
            Skin : false,
            Terrain : false,
            Water : true,
            Extra : true,
        }
    }
}
#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
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

impl EffectsStruct{
    pub fn new() -> EffectsStruct{
        EffectsStruct{
            AmbientOcclusion : true,
            BloodLens : true,
            Bloom : true,
            Cinema : true,
            Coloring : true,
            DepthOfField : true,
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
            ShadowsInteriors : true,
            Specular : true,
            Extra : true,
        }
    }
}

#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub struct MenuStruct {
    TextFont : SysString,
    TextFontStatus : SysString,
    TextSize : UInt8,
    TextSizeStatus : UInt8,
    KeyEnable : UInt8,
    KeyUp : UInt8,
    KeyDown : UInt8,
    KeyLeft : UInt8,
    KeyRight : UInt8,
    KeyPageUp : UInt8,
    KeyPageDown : UInt8,
    KeyAdd : UInt8,
    KeySubtract : UInt8,
    KeySave : UInt8,
    KeyEditing : UInt8
}
impl MenuStruct{
    pub fn new() -> MenuStruct{
        MenuStruct {
            TextFont : CString::new("Calibri").unwrap().into(),
            TextFontStatus : CString::new("Consolas").unwrap().into(),
            TextSize : 22,
            TextSizeStatus : 12,
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
