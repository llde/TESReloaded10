#![feature(vec_into_raw_parts)]

extern crate  memchr;
extern crate alloc;

pub mod sys_string;
pub mod main_config;
pub mod effect_config;
pub mod shader_config;
pub mod cfile;

use std::ffi::{CString, CStr};
#[allow(non_snake_case)]
use std::ffi::c_char;
use std::path::{Path};
use std::ffi::OsString;
use std::fs::File;

use std::{fs, ptr};
use std::io::{Read, Write};
use cfile::CFile;
use sys_string::SysString;
use std::os::windows::ffi::OsStringExt;
use std::slice::from_raw_parts;
use crate::ConfigurationError::{Deserialization, FileError};
use crate::main_config::Config;
use serde::Deserialize;
use toml::de::Deserializer;
use serde_deserialize_over::DeserializeOver;
#[derive(Debug)]
pub enum ConfigurationError{
	Deserialization,
	FileError
}
//TODO separation between games

pub static mut CONFIG : Option<Config> = None;
pub static mut LOGGER : Option<CFile> = None;

pub fn log<S: AsRef<str>>(message : S) -> () {
	let log = unsafe{
		LOGGER.as_mut().unwrap()
	};
	log.write(message.as_ref().as_bytes());
}

pub fn read_file<T : AsRef<Path> >(file : T) -> Result<(Config, bool) ,ConfigurationError> {
	let file_res  = File::open(&file);
	let mut cont = String::new();
	match file_res {
		Err(err) => {
			log(format!("Cannot open Configuration file {:#?}  {}",file.as_ref(),err));
			Err(FileError)
		},
		Ok(mut file) =>{
			match file.read_to_string(&mut cont){
				Ok(_) => {
					match Config::deserialize(Deserializer::new(&cont)){
				        Ok(config) => Ok((config, true)),
				        Err(_) => {
							let mut config = Config::new();
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
					Err(FileError)
				}
			}
		}
	}
}

pub fn  write_file<T : AsRef<Path> >(file : T){
	let main = Config::new();
    let file = File::create(file);
	match file {
		Ok(mut file) => {
			let toml = toml::to_string(&main).unwrap();
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
			Some(mutref) => mutref as *mut Config
		}
	}
}


#[no_mangle]
pub extern "C" fn LoadConfiguration(path : *const libc::wchar_t) -> (){
	let len = unsafe{libc::wcslen(path)};
	let slice = unsafe{from_raw_parts(path, len) };
	let widePath =  OsString::from_wide(slice);
	
	let config = read_file(widePath).unwrap();
	if config.1 == false {
		log("Not full validated configuration. Different version found")
	}
	unsafe{
		CONFIG.replace(config.0);
	}
	log("Configuration File Loaded");
}

#[repr(C)]
#[derive(Debug)]
pub enum Errors {
	None,
	InvalidLog
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
    fn it_writes() {
//        write_file("./test.ini");
	}
	#[test]
	fn it_reads() {
		let p = CString::new("./test.log").expect("Ok");
		let m = CString::new("w").expect("Ok");
		
		let f = unsafe { libc::fopen(p.as_ptr(), m.as_ptr()) }; 
		let a = SetLogFile(f);

		let conf = read_file("./test.ini").expect("Error with deserialization");
		println!("{:?}", conf);
	}
}
