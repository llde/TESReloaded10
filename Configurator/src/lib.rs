#![feature(vec_into_raw_parts,const_trait_impl)]

extern crate  memchr;
extern crate alloc;
extern crate winapi;

pub mod sys_string;
pub mod main_config;
pub mod effect_config;
pub mod shader_config;
pub mod cfile;
pub mod menu;

use std::ffi::{CString, CStr};
use std::ffi::c_char;
use std::path::{Path};
use std::ffi::OsString;
use std::fs::File;
use std::io;

use std::{fs, ptr};
use std::io::{Read, Write};
use cfile::CFile;
use menu::CreateFontRender;
use sys_string::SysString;
use std::os::windows::ffi::OsStringExt;
use std::slice::from_raw_parts;
use serde::{Serialize,Deserialize};
use toml::de::Deserializer;
use toml::Table;

use serde_deserialize_over::DeserializeOver;

use winapi::shared::d3d9::LPDIRECT3DDEVICE9;

use crate::ConfigurationError::{Deserialization, FileError};
use crate::main_config::Config;
use crate::effect_config::Effects;
use crate::shader_config::Shaders;
use crate::menu::MENU_STATE;
use crate::menu::MenuMove;

#[derive(Debug)]
pub enum ConfigurationError{
	Deserialization,
	FileError(io::Error)
}
//TODO separation between games

pub static mut CONFIG : Option<Config> = None;
pub static mut EFFECTS : Option<Effects> = None;
pub static mut SHADERS : Option<Shaders> = None;

pub static mut CONFIG_TABLE : Option<Table> = None;
pub static mut SHADERS_TABLE : Option<Table> = None;
pub static mut EFFECTS_TABLE : Option<Table> = None;


pub static mut LOGGER : Option<CFile> = None;

pub fn log<S: AsRef<str>>(message : S) -> () {
	let log = unsafe{
		LOGGER.as_mut().unwrap()
	};
	log.write(message.as_ref().as_bytes());
}

pub fn read_config_from_file<'a, T : AsRef<Path>, C >(file : T) -> Result<(C, bool) ,ConfigurationError> where C : Deserialize<'a> + DeserializeOver<'a> + Default{
	let file_res  = File::open(&file);
	let mut cont = String::new();
	match file_res {
		Err(err) => {
			log(format!("Cannot open Configuration file {:#?}  {}",file.as_ref(),err));
			Err(FileError(err))
		},
		Ok(mut file) =>{
			match file.read_to_string(&mut cont){
				Ok(_) => {
					match C::deserialize(Deserializer::new(&cont)){
				        Ok(config) => Ok((config, true)),
				        Err(_) => {
							let mut config = C::default();
							match config.deserialize_over(Deserializer::new(&cont)){
								Err(err) =>{
									log(format!("Cannot Parse Configuration {}",err));
									Err(Deserialization)
								},
								Ok(()) => Ok((config, false))
							}
						},
				    }
				},
				Err(err) => {
					log(format!("Cannot Read Configuration content {}",err));
					Err(FileError(err))
				}
			}
		}
	}
}

pub fn  write_config_to_file<T : AsRef<Path>, C>(file : T, config : C) where C : Serialize{
    let file = File::create(file);
	match file {
		Ok(mut file) => {
			let toml = toml::to_string(&config).unwrap();
		    match file.write_all(toml.as_ref()){
				Ok(_) => {},
				Err(err) => {
					log(format!("Cannot Save Configuration {}",err));
				}
			}

		},
		Err(err) => {
			log(format!("Cannot Create Configuration file {}", err));
		}
	}
}

#[no_mangle]
pub extern "C" fn getConfiguration() -> *mut Config {
	unsafe{
		match CONFIG.as_mut() {
			None => ptr::null_mut(),
			Some(mutref) => {
				mutref as *mut Config
			}
		}
	}
}

#[no_mangle]
pub extern "C" fn getEffectsConfiguration() -> *mut Effects {
	unsafe{
		match EFFECTS.as_mut() {
			None => ptr::null_mut(),
			Some(mutref) => mutref as *mut Effects
		}
	}
}

#[no_mangle]
pub extern "C" fn getShadersConfiguration() -> *mut Shaders {
	unsafe{
		match SHADERS.as_mut() {
			None => ptr::null_mut(),
			Some(mutref) => 
				mutref as *mut Shaders
				
		}
	}
}

pub fn load_config<'a, P : AsRef<Path>, C> (path : P) -> C where C : Deserialize<'a> + DeserializeOver<'a> + Default + Serialize{
	let config_res = read_config_from_file(&path);
	let mut backup_file = false;
	let config = match config_res{
	    Ok(conf) => {
			if conf.1 == false{
				log("Partial or partially invalid configuration found. Maybe older version?");
				backup_file = true;
			} 
			conf
		},
	    Err(err) => match err{
	        Deserialization => {
				backup_file = true;
				(C::default(),false)
			},
	        FileError(err) => { 
				match err.kind() {
					io::ErrorKind::NotFound => {
						backup_file = false;
						(C::default(),false)
					}
				    _ => {
						backup_file = true;
						(C::default(),false)
					}
				}
			}
	    }
	};
	if config.1 == false {
		if backup_file {
			let path_back = path.as_ref().with_extension("ini.bak");
			log(format!("Backup Configuration file to {:?}", path_back));
			let res = std::fs::rename(&path, path_back);
			if res.is_err() {
				log("Failed to move file")
			}
		}
		write_config_to_file(path, &config.0);
	}
	config.0
}


#[no_mangle]
pub extern "C" fn LoadConfiguration() -> (){
	let path_main = "./Data/OBSE/Plugins/OblivionReloaded.ini";
	let path_effect = "./Data/Shaders/OblivionReloaded/Effects/Effects.ini";
	let path_shader = "./Data/Shaders/OblivionReloaded/Shaders/Shaders.ini";	
	let config : Config = load_config(path_main);
	let effects : Effects = load_config(path_effect);
	let shaders : Shaders = load_config(path_shader);
	let config_table = Table::try_from(&config).unwrap();
	let shader_table = Table::try_from(&shaders).unwrap();
	let effect_table = Table::try_from(&effects).unwrap();

	unsafe{
		CONFIG.replace(config);
		EFFECTS.replace(effects);
		SHADERS.replace(shaders);
		CONFIG_TABLE.replace(config_table);
		SHADERS_TABLE.replace(shader_table);
		EFFECTS_TABLE.replace(effect_table);
	}

	log("Configuration File Loaded");
}


#[no_mangle]
pub extern "C" fn CreateFontRenderer(device: LPDIRECT3DDEVICE9){
	CreateFontRender(device);
}

#[no_mangle]
pub extern "C" fn WriteVersionString(width: i32, height : i32, string : *const i8){
	menu::WriteVersionString(width, height, string);
}

#[no_mangle]
pub extern "C" fn RenderConfigurationMenu(width: i32, height : i32){ menu::RenderMenu(width, height );}

#[no_mangle]
pub extern "C" fn MoveActiveNode(mov : MoveCursor){
	let moveconv = match mov {
		MoveCursor::Up => MenuMove::Up,
		MoveCursor::Down => MenuMove::Down,
		MoveCursor::Left => MenuMove::Left,
		MoveCursor::Right => MenuMove::Right
	};
	unsafe {
		MENU_STATE.move_menu_active_field(moveconv);
	}
}

#[no_mangle]
pub extern "C" fn EditActiveSetting(mov : menu::OperationSetting, callback: unsafe extern "C" fn(*const libc::c_char)){
	match menu::ChangeCurrentSetting(mov){
		Some(ref field_modified) => {
			let switch = CString::new(field_modified.to_owned()).unwrap();
			unsafe {
				callback(switch.as_ptr());
			}
		},
		None => {}
	}
}

#[no_mangle]
pub extern "C" fn SaveConfigurations(){
	let path_main = "./Data/OBSE/Plugins/OblivionReloaded.ini";
	let path_effect = "./Data/Shaders/OblivionReloaded/Effects/Effects.ini";
	let path_shader = "./Data/Shaders/OblivionReloaded/Shaders/Shaders.ini";	
	unsafe{
		write_config_to_file(CONFIG, path_main);
		write_config_to_file(SHADERS, path_shader);
		write_config_to_file(EFFECTS, path_effect);
	}
}

#[no_mangle]
pub extern  "C" fn EnterEditorMode(){
	
}

#[no_mangle]
pub extern "C" fn IsEditorMode() {
	
}

#[repr(C)]
#[derive(Debug)]
pub enum Errors {
	None,
	InvalidLog
}

#[repr(C)]
#[derive(Debug)]
pub enum MoveCursor{
	Up,Down,Left,Right
}

#[no_mangle]
pub extern "C" fn SetLogFile(file: *mut libc::FILE) -> Errors {
	match CFile::wrap(file){
		Err(err) => Errors::InvalidLog,
		Ok(file) => {
			unsafe {
				LOGGER.replace(file);
				Errors::None
			}
		}
	}
}

#[cfg(test)]
mod tests {
    use super::*;

	#[test]
	fn it_reads() {
		let p = CString::new("./test.log").expect("Ok");
		let m = CString::new("w").expect("Ok");
		
		let f = unsafe { libc::fopen(p.as_ptr(), m.as_ptr()) }; 
		let a = SetLogFile(f);

		let conf : Config = load_config("./test.ini");
		println!("{:?}", conf);
		let effconf : Effects = load_config("./effect.ini");
		let shaderconf : Shaders = load_config("./shader.ini");

	}
}
