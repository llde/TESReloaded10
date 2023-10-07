use std::ffi::CString;
use crate::sys_string::SysString;
use serde::{Serialize, Deserialize};

type UInt16 = u16;
type UInt32 = u32;
type UInt8 = u8;
#[allow(non_snake_case)]

#[repr(C)]
#[derive(Debug,Serialize,Deserialize)]
pub struct ShaderStruct{
    ShadowsExterior : ShadowsExteriorStruct
}
/*
While current NV shadows are post processing, it started as a forward render modification, that is still present in Oblivion
Keep the Shadows info here
*/
#[repr(C)]
#[derive(Debug,Serialize,Deserialize)]
pub struct ShadowsExteriorStruct{

}