use std::ffi::CString;
use crate::sys_string::SysString;
use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;

type UInt16 = u16;
type UInt32 = u32;
type UInt8 = u8;

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowStruct{
	#[deserialize_over]
    ShadowsExterior : ShadowsExteriorShaderStruct,
	#[deserialize_over]
    ShadowsInterior : ShadowsInteriorShaderStruct
}



impl Default for ShadowStruct{
    fn default() -> Self {
        Self{ShadowsExterior : ShadowsExteriorShaderStruct::default(), ShadowsInterior : ShadowsInteriorShaderStruct::default()}
    }
}

/*
While current NV shadows are post processing, it started as a forward render modification, that is still present in Oblivion
Keep the Shadows info here
*/
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowsExteriorShaderStruct{
	Quality : u32,
	Darkness : f64,
	NightMinDarkness : f64
}

impl Default for ShadowsExteriorShaderStruct{
    fn default() -> Self {
        Self{Quality : 2, Darkness : 0.1, NightMinDarkness : 0.8}
    }
}
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct ShadowsInteriorShaderStruct{
	Quality : u32,
	Darkness : f64
}

impl Default for ShadowsInteriorShaderStruct{
    fn default() -> Self {
        Self{Quality : 1, Darkness : 0.1}
    }
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Shaders{
	#[deserialize_over]
	Shadows :  ShadowStruct
}

impl Default for Shaders  {
       fn default() -> Self {
        Self{Shadows : ShadowStruct::default()}
    }
 
}