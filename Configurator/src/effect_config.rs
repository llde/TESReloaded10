#[allow(non_snake_case)]

use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;

type UInt16 = u16;
type UInt32 = u32;
type UInt8 = u8;
//TODO SPlit config into multiple files
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct BloodLens{
    Chance : u32
}

impl Default for BloodLens{
	fn default() ->Self{
		Self { Chance: 20 }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Effects{
	#[deserialize_over]
    BloodLens :  BloodLens
}

impl Default for Effects{
	fn default() -> Self {
    		Self { BloodLens: BloodLens::default() }
	}
}