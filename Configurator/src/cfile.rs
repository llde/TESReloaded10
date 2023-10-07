use fmt::Formatter;
use std::ffi::{c_void, CStr, CString};
use std::ops::Deref;
use std::{fmt, ptr};
use std::io::{Read, Write};
use std::io::{Error, ErrorKind};
pub struct CFile {
	file : *mut libc::FILE
}

#[derive(Debug)]
pub enum ErrorCFile {
	InvalidStream
}

impl CFile {
	
	pub fn wrap(file : *mut libc::FILE) -> Result<CFile, ErrorCFile>{
		if file == std::ptr::null_mut() { Err(ErrorCFile::InvalidStream) }
		else { Ok(CFile {file }) }
	}
}

impl From<*mut libc::FILE>  for CFile {
	fn from(file : *mut libc::FILE) -> CFile{
		CFile::wrap(file).unwrap()
	}
}

impl Write for CFile {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
		let bytes =  unsafe{
			libc::fprintf(self.file, buf.as_ptr() as *const i8)
		};
		unsafe {
			libc::fputc(b'\n'.into(), self.file);
		}
		if bytes <= 0 {
			Err(Error::last_os_error())
    
		}
		else{
			Ok(bytes as usize)
		}
	}

    fn flush(&mut self) -> std::io::Result<()> {
        unsafe{ libc::fflush(self.file); }
		Ok(())
    }
}