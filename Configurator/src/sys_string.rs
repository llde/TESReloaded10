use fmt::Formatter;
use serde::ser::SerializeSeq;
use std::ffi::{c_void, CStr, CString};
use std::ops::Deref;
use std::{fmt, ptr};
use serde::de::{Deserializer, Error, Unexpected, Visitor};
use serde::de::Deserialize;
use serde::{Serialize, Serializer};
use hex_serde_util::{HexU32PrefixUpper};
#[repr(C)]
#[derive(Debug)]
pub struct SysVec{
	cont : *const u32,
	len : usize,
	vec : Vec<u32>
}

impl SysVec{
	pub fn new() -> SysVec {
		SysVec {cont : ptr::null(), len : 0, vec : Vec::new() }
	}
	pub fn new_from(cont : Vec<u32> ) -> SysVec {
		SysVec {cont : cont.as_ptr(), len : cont.len(), vec : cont }
	}

}


impl <'de> Deserialize<'de> for SysVec {
    fn deserialize<D>(deserializer: D) -> Result<SysVec, D::Error>
        where D: Deserializer<'de>
    {
		return deserializer.deserialize_seq(SeqVisitor);
		
    }
}
impl Serialize for SysVec {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
        where S: Serializer
    {
		
		let mut seq = serializer.serialize_seq(Some(self.len))?;
		for el in &self.vec{
			let pref : HexU32PrefixUpper = (*el).into();
			seq.serialize_element(&pref)?;
		}
		seq.end()
    }
}

struct SeqVisitor;
impl <'de> Visitor<'de> for SeqVisitor {
    type Value = SysVec;

    fn expecting(&self, formatter: &mut Formatter) -> fmt::Result {
        formatter.write_str("a sequence")
    }

    fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
    where
        A: serde::de::SeqAccess<'de>,
    {
		let mut vec : Vec<u32> = Vec::new();
		loop{
			let next = seq.next_element::<HexU32PrefixUpper>();
			
			match next {
			    Ok(inner) => {
					match inner {
						Some(inn) => {
							let value = *inn; 
							vec.push(value);
						}
						None => {
							break;
						}
					}
				}
			    Err(_) =>{
					println!("NOOPE! {:?}", next);
					continue;
				},
			}
			
		}
		if vec.len() == 0 {
			Ok(SysVec::new())
		}
		else{ 
			Ok(SysVec::new_from(vec))	
	    }    
	}
}

#[derive(Debug)]
pub struct NulError(pub usize, pub Vec<u8>);

/**
  * Represent a null terminated string, passable to FFI. Use C structure alignment rules
  * Allocated from the LIBC allocator, modifiable from FFI.
  * SAFETY:
  * Modifying the struct from C++ require care: changing the string require carefully setting
  * length and capacity, as well keeping the null terminator and avoid null bytes inside the string,
  * and keep character representable as UTF8
  * The Rust side should instead take care of avoiding NULL bytes in the middle of the string, as
  * c strings use only one NULL byte as string terminator
TODO create a FFI API for SysString manipulations
  */
#[repr(C)]
#[derive(Debug)]
pub struct SysString{
     data : *mut libc::c_char,
     length: usize,
     capacity : usize,
}

 impl SysString{
     pub fn new_emtpy() ->SysString{
         SysString{
             data : ptr::null_mut(),
             length: 0,
             capacity: 0,
         }
     }

     pub fn new<T : Into<Vec<u8>>>(t : T) -> Result<SysString, NulError> {
         let buf = t.into();
         let len = buf.len();
         match memchr::memchr(0, &buf) {
             Some(i) => return Err(NulError(i, buf)),
             None => {}
         }

         let buffer = unsafe { libc::malloc(len + 1) } as *mut i8;
         let str = if buffer == ptr::null_mut() {
             SysString {
                 data: ptr::null_mut(),
                 length: 0,
                 capacity: 0,
             }
         } else {
             unsafe {
                 libc::memcpy(buffer as *mut c_void, buf.as_ptr() as *const c_void, len);
                 *buffer.offset((len + 1) as isize) = 0;
             }
             SysString {
                 data: buffer,
                 length: len,
                 capacity: len,
             }
         };
         Ok(str)
     }
     //TODO use Into trait
     pub fn box_to_vector(&self) -> Vec<u8>{
         let mut vec = Vec::new();
         vec.resize(self.length, 0);
         for i in 0..self.length{
             unsafe { vec[i] = *(self.data.offset(i as isize)) as u8; }
         }
         vec
     }
 }

impl <T> From<T> for SysString where T : AsRef<CStr>{
    fn from(v : T) -> Self {
        let value = v.as_ref();
        let len = unsafe { libc::strlen(value.as_ptr()) };
        let buffer = unsafe { libc::malloc(len + 1) } as *mut i8;
        unsafe {
            libc::strcpy(buffer, value.as_ptr());
            *buffer.offset((len + 1) as isize) = 0;
        }
        SysString{
            data : buffer,
            length: len,
            capacity: len,
        }
    }
}

impl Drop for SysString{
    fn drop(&mut self) {
        unsafe {
            libc::free(self.data  as *mut c_void);
        }
        self.data = ptr::null_mut();
        self.capacity = 0;
        self.length = 0;
    }
}

impl <'de> Deserialize<'de> for SysString {
    fn deserialize<D>(deserializer: D) -> Result<SysString, D::Error>
        where D: Deserializer<'de>
    {
        deserializer.deserialize_str(SysStringVisitor)
    }
}
impl Serialize for SysString {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
        where S: Serializer
    {
        let s = String::from_utf8(self.box_to_vector()).expect("Invalid UTF8");
        serializer.serialize_str(&s)
    }
}

unsafe impl Sync for SysString{}

struct SysStringVisitor;
impl <'de> Visitor<'de> for SysStringVisitor {
    type Value = SysString;

    fn expecting(&self, formatter: &mut Formatter) -> fmt::Result {
        formatter.write_str("a string")
    }

    fn visit_str<E>(self, v: &str) -> Result<Self::Value, E>
        where E: Error
    {
        let c = SysString::new(v.as_bytes());
        Ok(c.expect("Null bytes in the vector"))
    }

    fn visit_string<E>(self, v: String) -> Result<Self::Value, E>
        where E: Error
    {
        let c = SysString::new(v.as_bytes());
        Ok(c.expect("Null bytes in the vector"))
    }

    fn visit_bytes<E>(self, v: &[u8]) -> Result<Self::Value, E>
        where E: Error
    {
        Ok(SysString::new(v).expect("Null bytes in the vector"))
    }

    fn visit_byte_buf<E>(self, v: Vec<u8>) -> Result<Self::Value, E>
        where E: Error
    {
        Ok(SysString::new(v).expect("Null bytes in the vector"))
    }

    fn visit_unit<E>(self) -> Result<Self::Value, E>
        where E: Error
    {
        Ok(SysString::new_emtpy())
    }
}