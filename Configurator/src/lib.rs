#![feature(ascii_char)]
#![allow(non_snake_case)]
extern crate  memchr;
extern crate alloc;
extern crate winapi;

pub mod sys_string;
pub mod main_config;
pub mod effect_config;
pub mod shader_config;
pub mod cfile;
pub mod menu;

use std::ffi::CString;
use std::path::Path;
use std::fs::File;
use std::{io, panic};
use std::panic::catch_unwind;
use std::ptr;
use std::io::{Read, Write};
use cfile::CFile;
use menu::CreateFontRender;
use serde::de::DeserializeOwned;
use serde::{Serialize,Deserialize};
use toml::de::Deserializer;
use toml::Table;
use toml_comment::TomlComment;

use serde_deserialize_over::DeserializeOver;

use winapi::shared::d3d9::LPDIRECT3DDEVICE9;

use crate::ConfigurationError::{Deserialization};
use crate::main_config::Config;
use crate::effect_config::Effects;
use crate::shader_config::Shaders;
use crate::menu::MENU_STATE;
use crate::menu::MenuMove;

#[derive(Debug)]
pub enum ConfigurationError{
	Deserialization,
}
//TODO separation between games

pub static mut CONFIG : Option<Config> = None;
pub static mut EFFECTS : Option<Effects> = None;
pub static mut SHADERS : Option<Shaders> = None;

pub static mut CONFIG_TABLE : Option<Table> = None;
pub static mut SHADERS_TABLE : Option<Table> = None;
pub static mut EFFECTS_TABLE : Option<Table> = None;

#[repr(C)]
#[derive(Debug)]
pub enum Game{
	Oblivion,NewVegas
}

pub fn static_mut_insert<T>(stat :*mut Option<T> , val : T ) {
	unsafe{
		(&mut *stat).replace(val);
	}
}

pub fn get_static_ref<T>(stat : *mut Option<T>) -> &'static mut T{
	unsafe {
		return (&mut *stat).as_mut().unwrap();
	}
}

pub fn get_static_ref_const<T>(stat : *const Option<T>) -> &'static  T{
	unsafe {
		return (& *stat).as_ref().unwrap();
	}
}
pub static mut GAME : Option<Game> = None;

pub static mut LOGGER : Option<CFile> = None;

pub fn log<S: AsRef<str>>(message : S) -> () {
	let log = get_static_ref(&raw mut LOGGER);
	let _ = log.write(message.as_ref().as_bytes());
}


pub fn read_config_from_file<T:AsRef<Path>>(file : T) -> Result<String,io::Error> {
	let file_res  = File::open(&file);
	let mut cont = String::new();
	match file_res {
		Err(err) => {
			log(format!("Cannot open Configuration file {:#?}  {}",file.as_ref(),err));
			Err(err)
		},
		Ok(mut file) =>{
			match file.read_to_string(&mut cont){
				Ok(_) => Ok(cont),
				Err(err) => {
					log(format!("Cannot Read Configuration content {}",err));
					Err(err)
				}
			}
		}
	}
}

pub fn deserialize_config_from_string<'de, C>(file_buf : &'de str) -> Result<(C, bool) ,ConfigurationError>
where
    C: Deserialize<'de> + DeserializeOver<'de> + Default,
{
	match Deserializer::parse(file_buf){
		Ok(parsed) => {
			match C::deserialize(parsed){
				Ok(config) => Ok((config, true)),
				Err(_) => {
					/*the file isn't fully mappable to the struct. Can mean some values are missing some are different types, etc. Configuration may be from a different version*/
					let mut config = C::default();
					let parser  = Deserializer::parse(file_buf).unwrap(); /*should be safe here the file_buf is the same */
					match config.deserialize_over(parser){
						Err(err) =>{
							log(format!("Cannot Parse Configuration {}",err));
							Err(Deserialization)
						},
						Ok(()) => Ok((config, false))
					}
				}
			}
		},
		Err(err) =>{
			log(format!("Cannot Parse Configuration {}",err));
			Err(Deserialization)
		},
	}
}

pub fn  write_config_to_file<T : AsRef<Path>, C>(file : T, config : C) where C : Serialize + TomlComment{
    let file = File::create(file);
	match file {
		Ok(mut file) => {
			let toml = config.to_commented_toml();
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

#[unsafe(no_mangle)]
pub extern "C" fn SetGame(game : Game){
	static_mut_insert(&raw mut  GAME , game);
}

#[unsafe(no_mangle)]
pub extern "C" fn getConfiguration() -> *mut Config {
	unsafe{
		match  &mut *(&raw mut CONFIG) {
			None => ptr::null_mut(),
			Some(mutref) =>  	mutref
		}
	}
}

#[unsafe(no_mangle)]
pub extern "C" fn getEffectsConfiguration() -> *mut Effects {
	unsafe{
		match &mut *(&raw mut EFFECTS){
			None => ptr::null_mut(),
			Some(mutref) => mutref
		}
	}
}

#[unsafe(no_mangle)]
pub extern "C" fn getShadersConfiguration() -> *mut Shaders {
	unsafe{
		match &mut *(&raw mut SHADERS){
			None => ptr::null_mut(),
			Some(mutref) => mutref
		}
	}
}

pub fn load_config<P : AsRef<Path>, C>(path : P) -> C
where
    C: DeserializeOwned + Default + Serialize + TomlComment,
    for<'de> C: DeserializeOver<'de>,
{
	let file_result = read_config_from_file(&path);
	let mut backup_file = false;

	let config = match file_result{
		Ok(buf) => {
			let config_res = deserialize_config_from_string(&buf);
			match  config_res {
				Ok(conf) => {
					if conf.1 == false{
						log(format!("Partial or partially invalid configuration for {} found. Maybe older version? Regenerating configuration file keeping valid options", path.as_ref().display()));
						backup_file = true;
					}
					else {
						log(format!("Configuration file loaded for {}", path.as_ref().display()));
					}
					conf
				},
				Err(_) => {
					backup_file = true;
					(C::default(),false)
				},
			}
		},
		Err(err) => {
			match err.kind() {
				io::ErrorKind::NotFound => {
					log(format!("Configuration file {} not found. Creating default configuration", path.as_ref().display()));
					backup_file = false;
					(C::default(),false)
				},
				_ => {
					log(format!("Configuration file {} cannot be read. Creating default configuration", path.as_ref().display()));
					backup_file = true;
					(C::default(),false)
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
				log(format!("Failed to move configuration file {}", path.as_ref().display()));
			}
		}
		write_config_to_file(path, &config.0);
	}
	config.0
}


#[unsafe(no_mangle)]
pub extern "C" fn LoadConfiguration() -> (){
	let game = unsafe { (& *(&raw const GAME)).as_ref().unwrap() };
	let path_main = match game {
	    Game::Oblivion => "./Data/OBSE/Plugins/OblivionReloaded.ini",
	    Game::NewVegas => "./Data/NVSE/Plugins/NewVegasReloaded.ini",
	};

	let base_shader = match game {
	    Game::Oblivion => "./Data/Shaders/OblivionReloaded",
	    Game::NewVegas => "./Data/Shaders/NewVegasReloaded",
	}.to_owned();

	let path_effect = base_shader.clone() + "/Effects/Effects.ini";
	let path_shader = base_shader + "/Shaders/Shaders.ini";
	let config : Config = load_config(path_main);
	let effects : Effects = load_config(path_effect);
	let shaders : Shaders = load_config(path_shader);
	let config_table = Table::try_from(&config).unwrap();
	let shader_table = Table::try_from(&shaders).unwrap();
	let effect_table = Table::try_from(&effects).unwrap();
	static_mut_insert(&raw mut CONFIG, config);
	static_mut_insert(&raw mut EFFECTS, effects);
	static_mut_insert(&raw mut SHADERS, shaders);
	static_mut_insert(&raw mut CONFIG_TABLE, config_table);
	static_mut_insert(&raw mut SHADERS_TABLE, shader_table);
	static_mut_insert(&raw mut EFFECTS_TABLE, effect_table);

	log("All configuration loaded");
}


#[unsafe(no_mangle)]
pub extern "C" fn CreateFontRenderer(device: LPDIRECT3DDEVICE9){
	CreateFontRender(device);
}

#[unsafe(no_mangle)]
pub extern "C" fn WriteVersionString(width: i32, height : i32, string : *const i8){
	menu::WriteVersionString(width, height, string);
}

#[unsafe(no_mangle)]
pub extern "C" fn RenderConfigurationMenu(width: i32, height : i32){
	panic::set_hook(Box::new(|pi| {
		log(pi.to_string());
	} ));
	let _ = catch_unwind( ||  {
		menu::RenderMenu(width, height );
	} );
}

#[unsafe(no_mangle)]
pub extern "C" fn MoveActiveNode(mov : MoveCursor){
	let moveconv = match mov {
		MoveCursor::Up => MenuMove::Up,
		MoveCursor::Down => MenuMove::Down,
		MoveCursor::Left => MenuMove::Left,
		MoveCursor::Right => MenuMove::Right
	};
	unsafe {
		(&mut *(&raw mut MENU_STATE)).move_menu_active_field(moveconv);
	}
}

#[unsafe(no_mangle)]
pub extern "C" fn EditActiveSetting(mov : menu::OperationSetting, callback: unsafe extern "C" fn(*const libc::c_char)){
	match menu::ChangeCurrentSetting(mov){
		Some(field_modified) => {
			let switch = CString::new(field_modified.to_owned()).unwrap();
			unsafe {
				callback(switch.as_ptr());
			}
		},
		None => {}
	}
}

#[unsafe(no_mangle)]
pub extern "C" fn SaveConfigurations(){
	let game = unsafe { (& *(&raw const GAME)).as_ref().unwrap() };
	let path_main = match game {
	    Game::Oblivion => "./Data/OBSE/Plugins/OblivionReloaded.ini",
	    Game::NewVegas => "./Data/NVSE/Plugins/NewVegasReloaded.ini",
	};

	let base_shader = match game {
	    Game::Oblivion => "./Data/Shaders/OblivionReloaded",
	    Game::NewVegas => "./Data/Shaders/NewVegasReloaded",
	}.to_owned();

	let path_effect = base_shader.clone() + "/Effects/Effects.ini";
	let path_shader = base_shader + "/Shaders/Shaders.ini";
	write_config_to_file(path_main, get_static_ref_const(&raw const CONFIG));
	write_config_to_file(path_shader, get_static_ref_const(&raw const SHADERS));
	write_config_to_file(path_effect, get_static_ref_const(&raw const EFFECTS));

}

#[unsafe(no_mangle)]
pub extern  "C" fn EnterEditorMode(){
	menu::EnterEditorMode();
}

#[unsafe(no_mangle)]
pub extern "C" fn IsEditorMode() -> bool {
	menu::IsEditorMode()
}

#[unsafe(no_mangle)]
pub extern "C" fn CloseEditorMode() {
	menu::CloseEditorMode()
}

#[unsafe(no_mangle)]
pub extern "C" fn AddCharToEditor(ch : libc::c_char) {
	let cha = std::ascii::Char::from_u8(ch.try_into().unwrap());
//	log(format!("{:?} {:?}", cha,ch));
	if let Some(ascii_chara) = cha {
		menu::AddCharacterToEditorMode(ascii_chara);
	}
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

#[repr(C)]
#[derive(Debug)]
pub enum MessageType{
	Message,Messagebox
}

#[unsafe(no_mangle)]
pub extern "C" fn SetLogFile(file: *mut libc::FILE) -> Errors {
	match CFile::wrap(file){
		Err(_err) => Errors::InvalidLog,
		Ok(file) => {
			static_mut_insert(&raw mut LOGGER, file );
			Errors::None
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
