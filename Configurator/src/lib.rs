extern crate  memchr;
pub mod sys_string;
pub mod main_config;
#[allow(non_snake_case)]

use std::path::{Path};
use std::fs::File;
use std::fs;
use std::io::{Read, Write};
use crate::ConfigurationError::{Deserialization, FileError};
use crate::main_config::Config;

#[derive(Debug)]
pub enum ConfigurationError{
	Deserialization,
	FileError
}
//TODO separation between games

pub fn read_file<T : AsRef<Path> >(file : T) -> Result<Config,ConfigurationError> {
	let file_res  = File::open(file);
	let mut cont = String::new();
	match file_res {
		Err(err) => {
			println!("{}",err);
			Err(FileError)
		},
		Ok(mut file) =>{
			match file.read_to_string(&mut cont){
				Ok(_) => {
					match toml::from_str(&cont) {
						Err(err) =>{
							println!("{}", err);
							Err(Deserialization)
						},
						Ok(o) => Ok(o)
					}
				},
				Err(err) => {
					println!("{}",err);
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
    fn it_writes() {
        write_file("./test.ini");
    }
	#[test]
	fn it_reads() {
		let conf = read_file("./test.ini").expect("Error with deserialization");
		println!("{:?}", conf);
	}
}
