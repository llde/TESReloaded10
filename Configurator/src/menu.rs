use serde::Deserialize;
use winapi::shared::guiddef::{GUID, IID};
use winapi::shared::minwindef::{BOOL, BYTE, DWORD, FLOAT, INT, UINT};
use winapi::um::unknwnbase::{IUnknown, IUnknownVtbl};
use winapi::shared::ntdef::{LPCWSTR,LPCSTR, HRESULT};
use winapi::shared::d3d9::LPDIRECT3DDEVICE9;
use winapi::shared::d3d9types::{D3DCOLOR, D3DCOLOR_XRGB};
use winapi::um::wingdi::{FW_NORMAL,DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,FF_DONTCARE};
use winapi::shared::windef::{HDC,LPRECT,RECT};
use winapi::um::winuser::{SetRect,DT_CENTER, DT_LEFT,DT_RIGHT};

use std::marker::PhantomData;
use std::ptr;
use std::ffi::CString;
use winapi::RIDL;
use winapi::DEFINE_GUID;

use once_cell::sync::Lazy;
use toml::{Table, Value};
use crate::{log, CONFIG_TABLE, SHADERS_TABLE, EFFECTS_TABLE, CONFIG, SHADERS, EFFECTS};

#[link(name = "d3dx9")]
extern "system" {
	pub fn  D3DXCreateFontA(device: LPDIRECT3DDEVICE9, Height : i32, Width : i32, Weight: i32, MipLevels: UINT, Italic: bool, CharSet: DWORD ,OutputPrecision: DWORD, Quality: DWORD, PitchAndFamily: DWORD,pFacename : *const i8, ppfont : *mut *mut  ID3DXFont) -> HRESULT;
}


DEFINE_GUID!(IID_ID3DXFont, 
0xd79dbb70, 0x5f21, 0x4d36, 0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc);

RIDL!{#[uuid(0xd79dbb70, 0x5f21, 0x4d36, 0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc)]
interface ID3DXFont(ID3DXFontVtbl): IUnknown(IUnknownVtbl) {
	fn GetDevice(ppDevice : *mut LPDIRECT3DDEVICE9,) -> HRESULT,
    fn GetDescA(pDesc : *mut *mut libc::c_void,) -> HRESULT,
    fn GetDescW(pDesc : *mut *mut libc::c_void,) -> HRESULT,
    fn GetTextMetricsA(pTextMetrics : *mut *mut libc::c_void,) -> BOOL,
    fn GetTextMetricsW(pTextMetrics : *mut *mut libc::c_void,) -> BOOL,
	fn GetDC() -> HDC,
	fn GetGlyphData(/*STUB*/) -> HRESULT, // UINT Glyph, LPDIRECT3DTEXTURE9 *ppTexture, RECT *pBlackBox, POINT *pCellInc
	fn PreloadCharacters(First : UINT, Last : UINT,) -> HRESULT,
	fn PreloadGlyphs(First : UINT, Last : UINT,) -> HRESULT,
	fn PreloadTextA(pString : LPCSTR, Count :INT,) -> HRESULT,
	fn PreloadTextW(pString : LPCWSTR , Count :INT,) -> HRESULT,
	fn DrawTextA(pSprite : *const IUnknown,pString: LPCSTR, Count : INT, pRect : LPRECT, Format : DWORD, Color : D3DCOLOR,) -> HRESULT,
	fn DrawTextW(pSprite :  *const IUnknown,pString: LPCWSTR, Count : INT, pRect : LPRECT, Format : DWORD, Color : D3DCOLOR,) -> HRESULT, //TODO LPD3DXSPRITE
	fn OnLostDevice() -> HRESULT,
	fn OnResetDevice() -> HRESULT,
}}

pub static mut FontRenderer : Option<*mut ID3DXFont> = None;


pub fn CreateFontRender(device: LPDIRECT3DDEVICE9) {
	let mut font : *mut ID3DXFont = ptr::null_mut();
	let font_src = CString::new("Calibri").unwrap();
	let res = unsafe{
		D3DXCreateFontA(device, 22 , 0 , FW_NORMAL , 1 , false , DEFAULT_CHARSET , OUT_DEFAULT_PRECIS , ANTIALIASED_QUALITY , FF_DONTCARE , font_src.as_ptr() , &mut font as *mut *mut ID3DXFont)
	};
	
	log(format!("Create font renderer {}  {:?}", res, font));
	unsafe {
		FontRenderer.replace(font);
	}	
} 

enum Align{
	Left,Center,Right
}

fn DrawText(renderer : *mut ID3DXFont, rect: &mut RECT, text : *const i8, color : (u32,u32,u32), align : Align){
	let xrgb = D3DCOLOR_XRGB(color.0, color.1, color.2);
	let align = match align {
	    Align::Left => DT_LEFT,
	    Align::Center => DT_CENTER,
	    Align::Right => DT_RIGHT,
	};
	unsafe{
		(renderer.as_ref().unwrap().lpVtbl.as_ref().unwrap().DrawTextA)(renderer, ptr::null(), text, -1, rect, align, D3DCOLOR_XRGB(color.0,color.1,color.2));
	}
}

fn NewRect(left : i32, top : i32, right : i32, bottom : i32) -> RECT {
	let mut rect = RECT {left : 0, top : 0, right: 0, bottom: 0};
	unsafe{
		SetRect(&mut rect, left, top, right, bottom);
	}
	rect
}

fn UpdateRect(rect : &mut RECT,left : i32, top : i32, right : i32, bottom : i32 ){
	unsafe{
		SetRect(rect, left, top, right, bottom);
	}
}


const PositionX : i32 = 60;
const PositionY : i32 = 120;
const TitleColumnSize :i32 = 450;
const TextSize : i32 = 22;
const RowSpace : i32 = 0; //TODO

enum RenderingZone {
	ActiveConfig, ActiveFirst, ActiveSecond, ActiveThird,Version
}

#[derive(PartialEq, Eq)]
pub enum MenuMove {
	Up, Down, Left, Right
}

#[derive(PartialEq, Eq)]
enum MenuSelected {
	Main,Shaders,Effects
}

pub struct MenuState {
	active_config : MenuSelected,
	active_firstnode : String,
	active_secondnode : String,
	active_field : String,
	terminal : bool,
}

impl MenuState {
    pub fn new() -> MenuState {
		MenuState { active_config: MenuSelected::Main , active_firstnode: "".into() , active_secondnode: "".into(), active_field: "".into(), terminal : false }
	} 
	pub fn get_active_config(&self, zone : RenderingZone)-> &str{
		match zone {
			RenderingZone::ActiveConfig => match self.active_config  {
			    MenuSelected::Main => "Main",
				MenuSelected::Shaders => "Shaders",
				MenuSelected::Effects => "Effects"
			}
			RenderingZone::ActiveFirst => &self.active_firstnode,
			RenderingZone::ActiveSecond => &self.active_secondnode,
			RenderingZone::ActiveThird => &self.active_field,
			_ => ""
		}
	}
	
	pub fn get_active_mainconf(&self) -> &MenuSelected{
		&self.active_config
	}
	
	pub fn get_active_table(&self) -> &Table {
		unsafe{
			match self.active_config {
				MenuSelected::Main => CONFIG_TABLE.as_ref().unwrap(),
				MenuSelected::Shaders => SHADERS_TABLE.as_ref().unwrap(),
				MenuSelected::Effects => EFFECTS_TABLE.as_ref().unwrap()
			}
		}
	}
	
	fn move_menu_config(&mut self, mov : MenuMove){
		let repl = if mov == MenuMove::Right {
			match self.active_config {
				MenuSelected::Main => MenuSelected::Shaders,
				MenuSelected::Shaders => MenuSelected::Effects,
				MenuSelected::Effects => MenuSelected::Effects
			}
		}
		else {
			match self.active_config {
				MenuSelected::Main => MenuSelected::Main,
				MenuSelected::Shaders => MenuSelected::Main,
				MenuSelected::Effects => MenuSelected::Shaders
			}
		};
		self.active_config = repl;
	}
	
	fn get_next_state_key<'a>(&'a self, mov : &MenuMove, table : &'a Table, active_node : &str) -> Option<&String>{
		if *mov == MenuMove::Down{
			let mut found = false;
			let mut el : Option<&String> = None;
			for (key,val) in table {
				if found{
					el = Some(key);
				}
				found = active_node == key;
			}
			el
		}
		else if *mov == MenuMove::Up {
			let mut found = false;
			let mut el : Option<&String> = None;
			for (key,val) in table.iter().rev() {
				if found{
					el = Some(key);
				}
				found = active_node == key;
			}
			el
		}
		else {
			None
		}
	}
	pub fn is_terminal(&self) -> bool {
		self.terminal
	}
	
	pub fn move_menu_active_field(&mut self, mov : MenuMove) {
		let term = self.terminal;
		let table = self.get_active_table();
		if self.active_firstnode.is_empty(){
			if mov == MenuMove::Left || mov == MenuMove::Right{
				self.move_menu_config(mov);
			}
			else if mov == MenuMove::Down {
				let item = table.iter().next();
				self.active_firstnode = item.unwrap().0.into();
			}
		}
		else if self.active_secondnode.is_empty(){
			if mov == MenuMove::Up || mov == MenuMove::Down {
				match self.get_next_state_key(&mov, table , &self.active_firstnode ){
					None => {
						if mov == MenuMove::Up {
							self.active_firstnode = "".to_owned();
						}
					},
					Some(el) => {
						self.active_firstnode = el.to_owned();
					}
				}
			}
			else if mov == MenuMove::Right {
				let t = table.get(&self.active_firstnode).unwrap().as_table().unwrap();
				let activ = t.iter().next().unwrap();
				let act_key = activ.0.to_owned();
				let termin = !activ.1.is_table();
				self.active_secondnode = act_key;
				self.terminal = termin;
			}
		}
		else if self.active_field.is_empty(){
			let tab = table.get(&self.active_firstnode).unwrap().as_table().unwrap();
			if mov == MenuMove::Up || mov == MenuMove::Down {
				match self.get_next_state_key(&mov, tab , &self.active_secondnode ){
					None => {},
					Some(el) => {
						let b = !tab.get(&self.active_secondnode).unwrap().is_table();
						self.active_secondnode = el.to_owned();
						self.terminal = b;
					}
				}
			}
			else if mov == MenuMove::Right && !self.terminal{
				let t = tab.get(&self.active_secondnode).unwrap();
				if t.is_table() {
					self.active_field = t.as_table().unwrap().iter().next().unwrap().0.to_owned();
					self.terminal = false;
				}
				else{
					self.terminal = true;
				}
			}
			else if mov == MenuMove::Left{
				self.active_secondnode = "".to_owned();
				self.terminal = false;
			}
		}
		else {
			let tabl = table.get(&self.active_firstnode).unwrap().as_table().unwrap().get(&self.active_secondnode).unwrap();
			if tabl.is_table(){
				let tab = tabl.as_table().unwrap();
				
				if mov == MenuMove::Up || mov == MenuMove::Down {
					match self.get_next_state_key(&mov, tab , &self.active_field ){
						None => {},
						Some(el) => {
							self.active_field = el.to_owned();
							self.terminal = true;
						}
					}
				}
				else if mov == MenuMove::Left{
					self.active_field = "".to_owned();
					self.terminal = false;
				}
			}
		}
	}
}

pub static mut MENU_STATE : Lazy<MenuState> = Lazy::new(|| MenuState::new());

struct MenuRect {
	rect : RECT,
	save_rect : RECT,
	renderer : *mut ID3DXFont
}

impl MenuRect {
	pub fn new(renderer : *mut ID3DXFont) -> Self{
		MenuRect { rect: RECT {left : 0, top : 0, right: 0, bottom: 0},save_rect : RECT {left : 0, top : 0, right: 0, bottom: 0}, renderer }
	}
	
	pub fn new_with_coords(left : i32, top : i32, right : i32, bottom : i32, renderer : *mut ID3DXFont) -> Self{
		MenuRect { rect: NewRect(left, top , right , bottom ), save_rect: NewRect(left, top , right , bottom ), renderer }
	}
	
	pub fn next_row(&mut self) {
		let rect_bor = &mut self.rect;
		UpdateRect(rect_bor, rect_bor.left , rect_bor.bottom , rect_bor.right , rect_bor.bottom + TextSize );
	}
	
	pub fn next_column(&mut self){
		let rect_bor = &mut self.rect;
		UpdateRect(rect_bor, rect_bor.right , rect_bor.top , rect_bor.right + TitleColumnSize , rect_bor.bottom);

	}
	pub fn save(&mut self){
		self.save_rect = self.rect;
	}
	
	pub fn restore(&mut self){
		self.rect = self.save_rect;
	}
	
	fn is_active_zone(&self, rendering : &RenderingZone) -> bool {
		match rendering {
		    RenderingZone::ActiveConfig => {
				unsafe {
					MENU_STATE.get_active_config(RenderingZone::ActiveFirst).is_empty()	
				}
			},
		    RenderingZone::ActiveFirst => {
				unsafe {
					MENU_STATE.get_active_config(RenderingZone::ActiveSecond).is_empty()	
				}
			},
		    RenderingZone::ActiveSecond =>  {
				unsafe {
					MENU_STATE.get_active_config(RenderingZone::ActiveThird).is_empty()	
				}
			},
		    RenderingZone::ActiveThird =>  {
				true
			},
		    RenderingZone::Version => {false},
		}
	}
	
	pub fn draw<'a, S : Into<&'a str>>(&mut self, text : S, align : Align, rendering : RenderingZone) {
		let nulled = CString::new(text.into()).unwrap();
		let active_node =  self.is_active_zone(&rendering) && unsafe{
			MENU_STATE.get_active_config(rendering).eq_ignore_ascii_case(nulled.to_str().unwrap())
		};
		let color = if active_node {(10,240,180)} else {(250,240,180)};
		DrawText(self.renderer, &mut self.rect, nulled.as_ptr() as *const i8, color , align);
	}

	
	pub fn draw_opt<'a, S : Into<&'a str>>(&mut self, arg : S, opt : S,  align : Align, rendering : RenderingZone) {
		let it = arg.into().to_string();
		let nulled = CString::new(it.clone() + " = " + opt.into()).unwrap();
		let active_node = self.is_active_zone(&rendering) && unsafe{
			MENU_STATE.get_active_config(rendering).eq_ignore_ascii_case(it.as_str())
		};
		let color = if active_node {(10,240,180)} else {(250,240,180)};
		DrawText(self.renderer, &mut self.rect, nulled.as_ptr() as *const i8, color , align);
	}
}

pub fn WriteVersionString(width: i32, height : i32, string : *const i8){
	let font_render = unsafe {FontRenderer.unwrap()};
	let mut rect = NewRect(0, height - TextSize - 10, width, height + TextSize);
	
	DrawText(font_render , &mut rect, string ,(250,240,180), Align::Center);
}

pub fn RenderHeader() -> MenuRect{
	let font_render = unsafe {FontRenderer.unwrap()};
	let mut rect = MenuRect::new_with_coords(PositionX, PositionY, PositionX + TitleColumnSize, PositionY + TextSize, font_render);
	rect.draw("Oblivion Reloaded - Settings", Align::Center, RenderingZone::Version);
	rect.next_row();
	rect.save();
	rect.draw("Main", Align::Left, RenderingZone::ActiveConfig);	
	rect.next_column();
	rect.draw("Shaders", Align::Left,RenderingZone::ActiveConfig);
	rect.next_column();
	rect.draw("Effects", Align::Left,RenderingZone::ActiveConfig);
	rect.restore();
	rect
}

pub fn RenderMenu(width: i32, height : i32){
	let font_render = unsafe {FontRenderer.unwrap().as_ref().unwrap()};
	let mut rect = RenderHeader();
	let configtable = unsafe {
		match MENU_STATE.get_active_mainconf() {
			MenuSelected::Main => CONFIG_TABLE.as_ref().unwrap(),
			MenuSelected::Shaders => SHADERS_TABLE.as_ref().unwrap(),
			MenuSelected::Effects => EFFECTS_TABLE.as_ref().unwrap()
		}
	};
	
	rect.next_row();
	rect.save();
	for (key, value) in configtable {
		rect.draw(key.as_str(), Align::Left, RenderingZone::ActiveFirst);
		rect.next_row();
	}
	rect.restore();
	rect.next_column();
	rect.save();
	let first = unsafe {
		MENU_STATE.get_active_config(RenderingZone::ActiveFirst)
	};
	if !first.is_empty(){
		match configtable.get(first){
			None => {
				log(format!("[ERROR] Configuration Key {} not found", first));
			}
			Some(val) => {
				for (key,val) in val.as_table().unwrap() {
					if val.is_table(){
						rect.draw(key.as_str(), Align::Left ,RenderingZone::ActiveSecond);
					}
					else {
						rect.draw_opt(key.as_str(), &val.to_string(), Align::Left ,RenderingZone::ActiveSecond);
					}
					rect.next_row();
				}
			}
		}
	}
	rect.restore();
	rect.next_column();
	rect.save();
	let second = unsafe {
		MENU_STATE.get_active_config(RenderingZone::ActiveSecond)
	};
	if !second.is_empty(){
		match configtable.get(first).unwrap().get(second) {
			None => {
				log(format!("[ERROR] Configuration Key {} not found", second));
			}
			Some(val) => {
				if val.is_table(){ 
		//		log(format!("{} {}" , val, val.type_str()));
					for (key,val) in val.as_table().unwrap() {
						rect.draw_opt(key.as_str(), &val.to_string(), Align::Left ,RenderingZone::ActiveThird);
						rect.next_row();
					}
				}
			}
		}
	}

}

#[repr(C)]
#[derive(PartialEq)]
pub enum OperationSetting {
	Add, Sub
}

pub fn ChangeCurrentSetting(op : OperationSetting) -> Option<String> {
	if unsafe {MENU_STATE.is_terminal()} {
		let conf = unsafe {MENU_STATE.get_active_mainconf()};
		let mut configtable  : &mut Table = unsafe {
			match conf {
				MenuSelected::Main => CONFIG_TABLE.as_mut().unwrap(),
				MenuSelected::Shaders => SHADERS_TABLE.as_mut().unwrap(),
				MenuSelected::Effects => EFFECTS_TABLE.as_mut().unwrap()
			}
		};
		let first = unsafe { MENU_STATE.get_active_config(RenderingZone::ActiveFirst) };
		let second = unsafe { MENU_STATE.get_active_config(RenderingZone::ActiveSecond) };
		let third = unsafe { MENU_STATE.get_active_config(RenderingZone::ActiveThird) };
		let tabled = configtable.get_mut(first).unwrap().as_table_mut().unwrap().get_mut(second).unwrap();
		let tab : &mut Value = if tabled.is_table(){ tabled.as_table_mut().unwrap().get_mut(third).unwrap() } else {tabled};
		let modified = match tab {
		    Value::Integer(ref mut cont) => { if op == OperationSetting::Add { *cont += 1 } else { *cont -= 1 }; true},
		    Value::Float(ref mut cont) => {if op == OperationSetting::Add { *cont += 0.1 } else { *cont -= 0.1 }; true},
		    Value::Boolean(ref mut cont) => { *cont = !*cont; true },
		    _ => {false},
		};
		if modified {
			unsafe{
				match conf {
				    MenuSelected::Main => {*CONFIG.as_mut().unwrap() = crate::main_config::Config::deserialize(configtable.clone()).unwrap();},
				    MenuSelected::Shaders => {*SHADERS.as_mut().unwrap() = crate::shader_config::Shaders::deserialize(configtable.clone()).unwrap();},
				    MenuSelected::Effects => {*EFFECTS.as_mut().unwrap() = crate::effect_config::Effects::deserialize(configtable.clone()).unwrap();},
				}
			}
			if *conf == MenuSelected::Main {
				if first.eq_ignore_ascii_case("Shaders") || first.eq_ignore_ascii_case("Effects"){
					return Some(second.to_owned());
				}
			}
			return None;
		}
		return None;
	}
	return None;
}