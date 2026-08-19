#![allow(non_snake_case)]
use std::ffi::CString;
use crate::sys_string::{SysString};
use bevy_reflect::Reflect;
use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;
use toml_comment::TomlComment;

/*Configuration for the Main Configuration file*/
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct Config{
    /// Main configuration settings
	#[deserialize_over]
    Main : MainStruct,
    /// Water (non shader related) settings
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

#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MainStruct {
    /// Remove vanilla underwater pass effect 
    RemoveUnderwater : bool,
    /// Remove vanilla precipitation pass effect (rain, snow)
    RemovePrecipitations : bool,
    /// Remove vanilla fog pass effect (UNSTABLE)
	RemoveFogPass : bool,
    /// Enable memory texture management (May cause Alt+Tab crash or hangs with full screen mode)
    MemoryTextureManagement : bool,
    /// Enable grass mode. This is separated from the Grass shader
	GrassMode : bool,
    /// Replace the intro video and the main menu background video with a custom one
    ReplaceIntroAndMainMenuBackgroundVideos : bool,
    /// Override the default anisotropic filter value (0-16)
    AnisotropicFilter : u8,
    /// Key (in dx scancodes) to take a screenshot
    ScreenshotKey : u32,
    /// Override the default far plane distance (in game units)
    FarPlaneDistance : f32,
    /// Enable directional light  as sun source instead of the normal sun position (for testing purposes only)
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
            ReplaceIntroAndMainMenuBackgroundVideos : false,
            AnisotropicFilter : 4,
            ScreenshotKey : 87,
            FarPlaneDistance : 283840.0,
			TestDirectionLight : false,
        }
    }
}
/*Some settings are related to OR only, while CameraMode will be removed from NVR*/
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct DevelopStruct {
    /// 0 disable effects compilation, 1 Compile All effects when enabled, 2 Compile modified or missing only, 3 Compile only in menu
    CompileEffects : u8,
    /// 0 disable shaders compilation, 1 Compile All shaders when enabled, 2 Compile modified or missing only, 3 Compile only in menu
    CompileShaders : u8,
    /// enables hotkeys to print reneder data (may change between versions)
    DebugMode : bool,
    /// Key (in dx scancodes) to toggle debug log for the frame and the render window
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

#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub	struct LowHFSoundStruct {
    /// Enable LowHF effect for health
    HealthEnabled : bool,
    /// Enable LowHF effect for fatigue
    FatigueEnabled : bool,
    /// Coefficient for LowHF effect for health (0.0 - 1.0)
    HealthCoeff : f32,
    /// Coefficient for LowHF effect for fatigue (0.0 - 1.0)
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub	struct FlyCamStruct {
    /// Enable fly camera mode (true or false)
    Enabled : bool,
    /// Multiplier for the scroll wheel to change the fly camera speed
    ScrollMultiplier : f32,
    /// Key (in dx scancodes) to increase the fly camera speed
    KeyAdd : u16,
    /// Key (in dx scancodes) to decrease the fly camera speed
    KeySubtract : u16,
    /// Step value for the fly camera speed change
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct ShadersStruct {
    /// Eanble OR Blood shader
    Blood : bool,
    /// Enable OR Grass shader
    Grass : bool,
    /// Enable OR HDR shader
    HDR : bool,
    /// Enable OR NightEye shader
    NightEye : bool,
    /// Enable OR POM shader
    POM : bool,
    /// Enable OR Skin shader
    Skin : bool,
    /// Enable OR Terrain shader
    Terrain : bool,
    /// Enable OR Water shader
    Water : bool,
    /// Enable custom extra shaders, if provided in the shaders folder, for shaders not included in the other shaders sets. 
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
struct EffectsStruct {
    /// Enable OR Ambient Occlusion effect
    AmbientOcclusion : bool,
    /// Enable OR Blood Lens effect
    BloodLens : bool,
    /// Enable OR Bloom effect
    Bloom : bool,
    /// Enable OR Cinema effect
    Cinema : bool,
    /// Enable OR Coloring effect
    Coloring : bool,
    /// Enable OR Depth of Field effect
    DepthOfField : bool,
    /// Enable OR God Rays effect
    GodRays : bool,
    /// Enable OR LowHF effect
    LowHF : bool,
    /// Enable OR Motion Blur effect
    MotionBlur : bool,
    /// Enable OR Rain effect 
    Rain : bool,
    /// Enable OR Snow effect
    Snow : bool,
    /// Enable OR Sharpening effect
    Sharpening : bool,
    /// Enable OR Snow Accumulation effect
    SnowAccumulation : bool,
    /// Enable OR Underwater effect
    Underwater : bool,
    /// Enable OR Water Lens effect
    WaterLens : bool,
    /// Enable OR Wet World effect
    WetWorld : bool,
    /// Enable OR Volumetric Fog effect
    VolumetricFog : bool,
    /// Enable OR Shadows Exteriors effect.  This doesn't disable the underlying system.
    ShadowsExteriors : bool,
    /// Enable OR Shadows Interiors effect. This doesn't disable the underlying system.
    ShadowsInteriors : bool,
    /// Enable OR Specular effect
    Specular : bool,
    /// Enable OR Extra effect. These effects aren't triggered automatically by the engine, but can be triggered by scripts or, in future, by obse plugins.
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

#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct MenuStruct {
    #[toml_comment(inline)]
    /// Font used for the menu text
    TextFont : SysString,
    #[toml_comment(inline)]
    /// Font used for the menu status text
    TextFontStatus : SysString,
    /// Size of the menu text
    TextSize : u8,
    /// Size of the menu status text
    TextSizeStatus : u8,
    /// Color of the menu text in normal state (RGB)
	TextColorNormal : [u8; 3],
    /// Color of the menu text shadow in normal state (RGB)
	TextShadowColorNormal : [u8;3],
    /// Color of the menu text in selected state (RGB)
	TextColorSelected : [u8; 3],
    /// Color of the menu text shadow in selected state (RGB)
	TextShadowColorSelected : [u8 ; 3],
    /// Key (in dx scancodes) to enable the menu
    KeyEnable : u8,
    /// Key (in dx scancodes) to navigate up in the menu
    KeyUp : u8,
    /// Key (in dx scancodes) to navigate down in the menu
    KeyDown : u8,
    /// Key (in dx scancodes) to navigate left in the menu
    KeyLeft : u8,
    /// Key (in dx scancodes) to navigate right in the menu
    KeyRight : u8,
    /// Key (in dx scancodes) to navigate page up in the menu
    KeyPageUp : u8,
    /// Key (in dx scancodes) to navigate page down in the menu
    KeyPageDown : u8,
    /// Key (in dx scancodes) to increase a value in the menu
    KeyAdd : u8,
    /// Key (in dx scancodes) to decrease a value in the menu
    KeySubtract : u8,
    /// Key (in dx scancodes) to save the configuration in the menu or exiting editing mode saving the new value
    KeySave : u8,
    /// Key (in dx scancodes) to enter editing mode in the menu
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[allow(non_snake_case)]
pub struct SleepingModeStruct{
    /// Enable sleeping mode (true or false)
    Enabled : bool,
    /// Sleeping mode type (0 = Disabled, 1 = Sleep, 2 = Wait)
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[allow(non_snake_case)]
pub struct ShadowFormsStruct {
    /// Enable shadow rendering for activators
	Activators : bool,
    /// Enable shadow rendering for actors
	Actors : bool,
    /// Enable shadow rendering for apparatus objects
	Apparatus: bool,
    /// Enable shadow rendering for books
	Books : bool,
    /// Enable shadow rendering for containers
	Containers : bool,
    /// Enable shadow rendering for doors
	Doors : bool,
    /// Enable shadow rendering for furniture objects
	Furniture : bool,
    /// Enable shadow rendering for miscellaneous objects
	Misc : bool,
    /// Enable shadow rendering for static objects
	Statics : bool,
    /// Enable shadow rendering for terrain
	Terrain : bool,
    /// Enable shadow rendering for trees
	Trees : bool,
    /// Enable shadow rendering for LOD objects
	Lod : bool, 
    /// Minimum radius for shadow rendering (in game units)
	MinRadius : f32,
    /// Enable alpha when rendering shadows 
	Alpha : bool,
}

impl Default for ShadowFormsStruct{
    fn default() -> Self{
		ShadowFormsStruct {
			Activators: true, Actors: true , Apparatus: true, Books: true, Containers: true, Doors: true, Furniture: true, Misc: true, Statics: true, Terrain: true, Trees: true, Lod: false, MinRadius: 10.0, Alpha : true
			
		}
	}
}

#[repr(u8)]
#[derive(Debug,Serialize,Deserialize, Reflect)]
#[allow(non_snake_case)]
enum ShadowType {
    DISABLED,
    VSM,
    ESM,
    ESSM
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[allow(non_snake_case)]
pub struct ShadowsExteriorStruct{
    /// Shadows engine enabled (true or false). This disable both the shadowmaps and the orthomap
	Enabled : bool,
    /// Shadow engine type (DISABLED, VSM, ESM, ESSM)
    #[toml_comment(inline)]
	ShadowMode : ShadowType,
    /// Shadow map resolution (prefers power of 2 sizes)
    ShadowMapResolution : u32,
    /// Shadow map radius (in game units) for cascade generation
    ShadowMapRadius : f32,
    /// Shadow map far plane (in game units) for cascade generation
    ShadowMapFarPlane : f32,
    /// Blur shadow maps
    BlurShadowMaps : bool,
}
/*Other Shadows Related settings will be in the Shader configuration
TODO what about cascade specific settings??
 */

impl Default for ShadowsExteriorStruct{
    fn default() -> Self{
        ShadowsExteriorStruct{
			Enabled : true,
			ShadowMode : ShadowType::VSM,
            ShadowMapResolution: 2048,
            ShadowMapRadius: 8000.0,
            ShadowMapFarPlane: 32768.0,
            BlurShadowMaps: true,
        }
    }
}


#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[allow(non_snake_case)]
pub struct ShadowsInteriorStruct{
    /// Enable interior shadows. This disable the underlying system. 
	Enabled : bool,
    /// Shadow engine type. 
	ShadowMode : u8,
    /// Shadow cube map resolution (prefers power of 2 sizes)
    ShadowCubeMapResolution : u32,
    /// Number of light points to use for interior shadows (1-8)
    LightPoints : u8,
    /// Enable or disable torches casting shadows in interiors
    TorchesCastShadows : bool,
    /// Multiplier for the light radius used for interior shadows //TODO!!: check
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

#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[repr(C)]
#[allow(non_snake_case)]
pub struct CullingEngine{
    /// Enable or disable the main culling engine. This will cull objects based on their size and distance from the camera.
    EnableMainCulling: bool,
    /// Enable or disable the reflection culling engine. This will cull objects based on their size and distance from the camera when rendering reflections.
    EnableRelfectionCulling : bool,
    /// Minimum size (in game units) for an object to be rendered. Objects smaller than this size will be culled.
    CullMinSize : f32,
    /// Minimum size (in game units) for an object to be rendered in reflections. Objects smaller than this size will be culled.
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
#[derive(Debug,Serialize,Deserialize,DeserializeOver, Reflect,TomlComment)]
#[allow(non_snake_case)]
pub struct WaterEngine{
    /// Water reflection map size (prefers power of 2 sizes)
    ReflectionMapSize : u16,
    /// Enable or disable atmosphere  changes when underwater (UNSTABLE).
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
