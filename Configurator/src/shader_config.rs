use std::ffi::CString;
use crate::sys_string::SysString;
use serde::{Serialize, Deserialize};
use serde_deserialize_over::DeserializeOver;


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
        Self{Quality : 2, Darkness : 0.4}
    }
}
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Rain{
	DepthStep : f64,
	Speed : f64
}

impl Default for Rain{
	fn default() -> Self {
	    Self { DepthStep: 8.0 , Speed: 3.0  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Snow{
	DepthStep : f64,
	Speed : f64,
	Flakes : f64
}

impl Default for Snow{
	fn default() -> Self {
	    Self { DepthStep: 2.5 , Speed: 1.4, Flakes : 0.5  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Water{
	choppiness : f64,
	waveWidth : f64,
	waveSpeed : f64,
	reflectivity : f64,
	causticsStrength : f64,
	causticsStrengthS : f64,
	shoreFactor : f64,
	shoreMovement : f64,
	turbidity : f64,
	inScattCoeff : f64,
	inExtCoeff_R : f64,
	inExtCoeff_G : f64,
	inExtCoeff_B : f64,
	depthDarkness : f64
}

impl Default for Water {
	fn default() -> Self {
	    Self { choppiness: 0.8, waveWidth: 0.7, waveSpeed: 0.3, reflectivity: 2.0 , causticsStrength: 0.6, causticsStrengthS: 0.4, shoreFactor:1.2 , shoreMovement: 20.0, turbidity: 2.0, inScattCoeff: 0.12, inExtCoeff_R: 0.40, inExtCoeff_G: 0.26, inExtCoeff_B: 0.30, depthDarkness: 1.0 }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct HDR {
	ToneMapping : f64,
	ToneMappingBlur : f64,
	ToneMappingColor : f64,
	Linearization : f64
}

impl Default for HDR {
	fn default() -> Self {
	    Self { ToneMapping: 1.0, ToneMappingBlur: 0.0, ToneMappingColor: 1.2 , Linearization: 2.2 }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct POM{
	HeightMapScale : f64,
	MinSamples : u32,
	MaxSamples : u32
} 

impl Default for POM{
	fn default() -> Self {
	    Self { HeightMapScale: 0.55, MinSamples: 8, MaxSamples: 32 }
	} 
}
			
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Skin{
	Attenuation : f64,
	SpecularPower : f64,
	MaterialThickness : f64,
	RimScalar : f64,
	CoeffRed : f64,
	CoeffGreen : f64,
	CoeffBlue : f64,
}

impl Default for Skin{
	fn default() -> Self {
	    Self { Attenuation: 0.84, SpecularPower: 0.78, MaterialThickness: 0.12, RimScalar: 0.5, CoeffRed: 0.36 , CoeffGreen: 0.22 , CoeffBlue:0.12  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Terrain{
	DistantNoise : f64,
	DistantSpecular : f64,
	NearSpecular : f64,
	MiddleSpecular : f64
}

impl Default for Terrain {
	fn default() -> Self {
	    Self { DistantNoise: 0.6, DistantSpecular: 0.2, NearSpecular: 0.0, MiddleSpecular: 0.0  }
	}
}
			
#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Grass {
	WindEnabled : bool,
	WindCoefficient : f64,
	GrassDensity : u32,
	ScaleX : f64,
	ScaleY : f64,
	ScaleZ : f64,
	MinDistance : f64,
	MaxDistance : f64
	
}

impl Default for Grass {
	fn default() -> Self {
	    Self { WindEnabled: true, WindCoefficient: 100.0, GrassDensity: 3, ScaleX: 2.0, ScaleY: 2.0 , ScaleZ:2.0 , MinDistance: 9000.0, MaxDistance:11000.0  }
	}
}

#[repr(C)]
#[derive(Debug,Serialize,Deserialize,DeserializeOver)]
#[allow(non_snake_case)]
pub struct Shaders{
	#[deserialize_over]
	Shadows :  ShadowStruct,
	#[deserialize_over]
	Rain : Rain,
	#[deserialize_over]
	Snow : Snow,
	#[deserialize_over]
	Water : Water,
	#[deserialize_over]
	HDR : HDR,
	#[deserialize_over]
	POM : POM,
	#[deserialize_over]
	Skin : Skin,
	#[deserialize_over]
	Terrain : Terrain,
	#[deserialize_over]
	Grass : Grass	
}

impl Default for Shaders  {
       fn default() -> Self {
        Self{Shadows : ShadowStruct::default() , Rain : Rain::default(), Snow : Snow::default(), Water : Water::default(), HDR : HDR::default(), POM : POM::default(), Skin : Skin::default(), Terrain : Terrain::default(), Grass : Grass::default()}
    }
 
}