extern crate cbindgen;

use std::env;
use std::path::PathBuf;


fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    let package_name = env::var("CARGO_PKG_NAME").unwrap();
	let path_file = target_dir().parent().unwrap().join("../TESReloaded/Core/SettingStructure.h");
    let output_file = path_file
        .display()
        .to_string();

    cbindgen::Builder::new()
      .with_crate(crate_dir).with_namespace("ffi").with_cpp_compat(true).with_include("SettingsStructureCommon.h")
      .generate()
      .expect("Unable to generate bindings")
      .write_to_file(output_file);
}
 
fn target_dir() -> PathBuf {
    if let Ok(target) = env::var("CARGO_TARGET_DIR") {
        PathBuf::from(target)
    } else {
        PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("target")
    }
}