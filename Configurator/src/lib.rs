use serde::{Serialize, Deserialize};
use std::path::{Path};
use std::fs::File;
use std::fs;
use std::io::Write;

type UInt16 = u16; 
type UInt32 = u32; 
type UInt8 = u8; 
//TODO sepration between games

#[derive(Serialize, Deserialize, Debug)]
#[repr(C)]
pub struct Config{
	Main : MainStruct,
	Develop : DevelopStruct,
	FlyCam : FlyCamStruct
}

impl Config{
	pub fn new() -> Config{
		Config{
			Main : MainStruct::new(),
			Develop : DevelopStruct::new(),
			FlyCam : FlyCamStruct::new()
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

pub fn read_file(left: usize, right: usize) -> usize {
    0
}

pub fn  write_file<T : AsRef<Path> >(file : T){
	let main = Config::new();
    let mut file = File::create(file);
	match file {
		Ok(mut file) => {
			let toml = toml::to_string(&main).unwrap();
		    match file.write_all(toml.as_ref()){
				Ok(_) => {},
				Err(err) => {
					println!("{}", err);
				}
			}

		},
		Err(err) => {
			println!("{}", err);
		}
	}
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        write_file("./test.ini");
    }
}
