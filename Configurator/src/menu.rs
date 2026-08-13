#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
//#![allow(nonstandard_style)]
use bevy_reflect::array::Array;
use bevy_reflect::enums::{Enum, DynamicVariant};
use bevy_reflect::structs::Struct;
use bevy_reflect::{NamedField, PartialReflect, Reflect};
use bevy_reflect::OpaqueInfo;

use serde::Deserialize;
use strum::AsRefStr;
use winapi::shared::guiddef::{GUID, IID};
use winapi::shared::minwindef::{BOOL, BYTE, DWORD, FLOAT, INT, UINT};
use winapi::um::unknwnbase::{IUnknown, IUnknownVtbl};
use winapi::shared::ntdef::{LPCWSTR,LPCSTR, HRESULT};
use winapi::shared::d3d9::LPDIRECT3DDEVICE9;
use winapi::shared::d3d9types::{D3DCOLOR, D3DCOLOR_XRGB};
use winapi::um::wingdi::{FW_NORMAL,DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,FF_DONTCARE};
use winapi::shared::windef::{HDC,LPRECT,RECT};
use winapi::um::winuser::{SetRect,DT_CENTER, DT_LEFT,DT_RIGHT};

use std::any::TypeId;
use std::marker::PhantomData;
use std::ptr;
use std::ffi::CString;
use std::fmt::Write;
use std::cell::{Ref, RefCell, RefMut};

use winapi::RIDL;
use winapi::DEFINE_GUID;

use once_cell::sync::Lazy;
use toml::{Table, Value};
use crate::effect_config::Effects;
use crate::main_config::Config;
use crate::shader_config::Shaders;
use crate::sys_string::SysString;
use crate::{get_static_ref, get_static_ref_const, log, menu, static_mut_insert, CONFIG, CONFIG_TABLE, EFFECTS, EFFECTS_TABLE, SHADERS, SHADERS_TABLE};

#[link(name = "d3dx9")]
unsafe extern "system" {
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

pub static mut FontRenderer : *mut ID3DXFont = ptr::null_mut();


pub fn CreateFontRender(device: LPDIRECT3DDEVICE9) {
	let mut font : *mut ID3DXFont = ptr::null_mut();
	let font_src = CString::new("Calibri").unwrap();
	let res = unsafe{
		D3DXCreateFontA(device, 22 , 0 , FW_NORMAL , 1 , false , DEFAULT_CHARSET , OUT_DEFAULT_PRECIS , ANTIALIASED_QUALITY , FF_DONTCARE , font_src.as_ptr() , &mut font as *mut *mut ID3DXFont)
	};

	log(format!("Create font renderer {}  {:?}", res, font));
	unsafe {
		FontRenderer  = font;
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
		(renderer.as_ref().unwrap().lpVtbl.as_ref().unwrap().DrawTextA)(renderer, ptr::null(), text, -1, rect, align, xrgb);
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

#[derive(PartialEq, Eq)]
enum RenderingZone {
	ActiveConfig, ActiveFirst, ActiveSecond, ActiveThird,Version
}

#[derive(PartialEq, Eq)]
pub enum MenuMove {
	Up, Down, Left, Right
}

#[derive(PartialEq, Eq, AsRefStr)]
enum MenuSelected {
	Main,Shaders,Effects
}

#[derive(PartialEq, Eq)]
enum ActiveColumn {
	None, First,Second,Third
}

impl PartialEq<RenderingZone> for ActiveColumn{
    fn eq(&self, other: &RenderingZone) -> bool {
        if *self == ActiveColumn::None && *other == RenderingZone::ActiveConfig {
			true
		}
		else if *self == ActiveColumn::First && *other == RenderingZone::ActiveFirst {
			true
		}
		else if *self == ActiveColumn::Second && *other == RenderingZone::ActiveSecond {
			true
		}
		else if *self == ActiveColumn::Third && *other == RenderingZone::ActiveThird {
			true
		}
		else {
			false
		}
    }
}

pub struct MenuState<'a> {
	active_config : RefCell<MenuSelected>,
	first_element : RefCell<Option<(&'a dyn PartialReflect,usize)>>,
	second_element : RefCell<Option<(&'a dyn PartialReflect,usize)>>,
	third_element : RefCell<Option<(&'a dyn PartialReflect,usize)>>,
	edit_holder : RefCell<Option<String>>
}

impl <'a>  MenuState<'a> {
    pub fn new() -> MenuState<'a> {
		MenuState { active_config: RefCell::new(MenuSelected::Main), first_element : RefCell::new(None),second_element:RefCell::new(None), third_element : RefCell::new(None), edit_holder : RefCell::new(None) }
	}

	pub fn get_active_configuration(&self) -> Ref<'_,MenuSelected>{
		self.active_config.borrow()
	}

	pub fn get_active_for_zone(&'a self, col : ActiveColumn) -> Ref<'a, Option<(&'a dyn PartialReflect, usize)>>{
		match col {
			ActiveColumn::None => unreachable!() /*This is handled serparately, becouse is not a RefCell borrow*/,
			ActiveColumn::First => self.first_element.borrow(),
			ActiveColumn::Second => self.second_element.borrow(),
			ActiveColumn::Third => self.third_element.borrow()
		}
	}

	pub fn is_editor_mode(&self) -> bool {
		self.edit_holder.borrow().is_some()
	}

	pub fn set_editor_mode(&self){
		if self.get_terminal_field().is_some(){
			self.edit_holder.replace(Some(String::new()));
		}
	}

	pub fn add_character_to_edit(&self, ch : char){
		self.edit_holder.borrow_mut().as_mut().unwrap().push(ch);
	}


	pub fn close_editor_mode(&self) {
		let terminal_field = self.get_terminal_field();
		if let Some((term, _)) = terminal_field {
			match term.get_represented_type_info().unwrap(){
				bevy_reflect::TypeInfo::Opaque(opaque_info) => {
					let id = opaque_info.type_id();
					if id  == TypeId::of::<u32>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<u32>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
					else if id  == TypeId::of::<u8>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<u8>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
					else if id  == TypeId::of::<u16>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<u16>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
					else if id  == TypeId::of::<u64>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<u64>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
					else if id  == TypeId::of::<f32>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<f32>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
					else if id  == TypeId::of::<f64>() {
						match self.edit_holder.borrow().as_ref().unwrap().parse::<f64>() {
							Ok(ref res) => term.apply(res),
							Err(_) => {},
						}
					}
				},
				_ => {}
			}
		}
		self.edit_holder.replace(None);
	}

	pub fn get_editor_string(&'a self) -> Ref<'a, Option<String>> {
		self.edit_holder.borrow()
	}

	pub fn get_active_table(&self) -> &dyn Struct {
		match *self.active_config.borrow() {
			MenuSelected::Main => get_static_ref_const::<Config>(&raw const CONFIG) as &dyn Struct,
			MenuSelected::Shaders => get_static_ref_const::<Shaders>(&raw const SHADERS) as &dyn Struct,
			MenuSelected::Effects => get_static_ref_const::<Effects>(&raw const EFFECTS) as &dyn Struct
		}
	}

	pub fn get_terminal_field(&self) -> Option<(&mut dyn PartialReflect, Option<&'static str>)>{
		let current_table = match *self.active_config.borrow() {
			MenuSelected::Main => get_static_ref::<Config>(&raw mut CONFIG) as &mut dyn Struct,
			MenuSelected::Shaders => get_static_ref::<Shaders>(&raw mut SHADERS) as &mut dyn Struct,
			MenuSelected::Effects => get_static_ref::<Effects>(&raw mut EFFECTS) as &mut dyn Struct
		};
		if let Some(ref inner) = *self.first_element.borrow(){
			let name = current_table.get_represented_type_info().unwrap().as_struct().unwrap().field_at(inner.1).unwrap().name();
			let inner_struct = current_table.field_at_mut(inner.1).unwrap();
			if  let Some(ref second_inner) = *self.second_element.borrow(){
				let name_field = inner_struct.get_represented_type_info().unwrap().as_struct().unwrap().field_at(second_inner.1).unwrap().name();
				let second_level_struct = inner_struct.reflect_mut().as_struct().unwrap().field_at_mut(second_inner.1).unwrap();
				if let Some(ref third_inner) = *self.third_element.borrow(){
					second_level_struct.reflect_mut().as_struct().unwrap().field_at_mut(third_inner.1).map( | opt | (opt, None))
				}
				else{
					if second_level_struct.reflect_mut().as_struct().is_err(){
						if *self.active_config.borrow() == MenuSelected::Main && (name.eq_ignore_ascii_case("Effects")  || name.eq_ignore_ascii_case("Shaders")){
							Some((second_level_struct, Some(name_field)))
						}
						else{
							Some((second_level_struct, None))
						}
					}
					else{
						None
					}
				}
			}
			else {
				None
			}
		}
		else{
			None
		}
	}

	fn move_menu_config(&self, mov : MenuMove){
		let repl = if mov == MenuMove::Right {
				match *self.active_config.borrow() {
					MenuSelected::Main => MenuSelected::Shaders,
					MenuSelected::Shaders => MenuSelected::Effects,
					MenuSelected::Effects => MenuSelected::Effects
				}
			}
			else if mov == MenuMove::Left {
				match *self.active_config.borrow() {
					MenuSelected::Main => MenuSelected::Main,
					MenuSelected::Shaders => MenuSelected::Main,
					MenuSelected::Effects => MenuSelected::Shaders
				}
			} else { unreachable!()};
		self.active_config.replace(repl);
	}

	pub fn get_active_element_column(&self) -> ActiveColumn{
		if let Some(_) = *self.third_element.borrow(){
			ActiveColumn::Third
		}
		else if let Some(_) = *self.second_element.borrow(){
			ActiveColumn::Second
		}
		else if let Some(_) = *self.first_element.borrow(){
			ActiveColumn::First
		}
		else {
			ActiveColumn::None
		}
	}

	pub fn is_node_active(&self, node : &str, zone : RenderingZone ) -> bool{
		let col = self.get_active_element_column();
		if col  == zone {
			match col{
				ActiveColumn::None => (*self.active_config.borrow()).as_ref() ==  node,
				ActiveColumn::First => {
					let active_conf = self.get_active_table();
					let id = self.first_element.borrow().unwrap().1;
					active_conf.name_at(id).unwrap() == node
				},
				ActiveColumn::Second => {
					let id = self.second_element.borrow().unwrap().1;
					self.first_element.borrow().unwrap().0.reflect_ref().as_struct().unwrap().name_at(id).unwrap() == node
				},
				ActiveColumn::Third => {
					let id = self.third_element.borrow().unwrap().1;
					self.second_element.borrow().unwrap().0.reflect_ref().as_struct().unwrap().name_at(id).unwrap() == node
				}
			}
		}
		else {
			false
		}
	}

	pub fn move_menu_active_field(&'a self, mov : MenuMove) {
		let table = self.get_active_table();
		let col = self.get_active_element_column();
		match col {
			ActiveColumn::None => {
			//The config selectors only are selected, not a menu member proper
				match mov {
					MenuMove::Up  => {/*NO OP*/},
					MenuMove::Down => {
						self.first_element.replace(Some((table.field_at(0).unwrap(),0)));
					},
					MenuMove::Left | MenuMove::Right => self.move_menu_config(mov)
				}
			},
			ActiveColumn::First => {
				let cur_idx = self.first_element.borrow().unwrap().1; //TEST is borrow going out of scope here?
				match mov {
					MenuMove::Up  => {
						if cur_idx == 0 {
							self.first_element.replace(None);
						}
						else {
							self.first_element.replace(Some((table.field_at(cur_idx -1).unwrap(),cur_idx -1)));
						}
					},
					MenuMove::Down => {
						if (cur_idx + 1) <  table.field_len() {
							self.first_element.replace(Some((table.field_at(cur_idx +1).unwrap(),cur_idx +1)));
						}
					},
					MenuMove::Right => {
						let el = self.first_element.borrow().unwrap().0.reflect_ref().as_struct().unwrap();
						self.second_element.replace(Some((el.field_at(0).unwrap(),0)));
					},
					MenuMove::Left => {/* NO OP */}
				}
			},
			ActiveColumn::Second => {
				let cur_idx = self.second_element.borrow().unwrap().1; //TEST is borrow going out of scope here?
				let first_el = self.first_element.borrow().unwrap().0.reflect_ref().as_struct().unwrap();
				match mov {
					MenuMove::Up  => {
						if cur_idx > 0 {
							self.second_element.replace(Some((first_el.field_at(cur_idx -1).unwrap(),cur_idx -1)));
						}
					},
					MenuMove::Down => {
						if (cur_idx +1) < first_el.field_len(){
							self.second_element.replace(Some((first_el.field_at(cur_idx +1).unwrap(),cur_idx +1)));
						}
					},
					MenuMove::Right => {
						let el = self.second_element.borrow().unwrap().0.reflect_ref().as_struct();
						match el{
							Ok(ref element) => {
								self.third_element.replace(Some((element.field_at(0).unwrap(),0)));
							},
							Err(_) => {},
						}
					},
					MenuMove::Left => {
						self.second_element.replace(None);
					}
				}
			},
			ActiveColumn::Third => {
				let cur_idx = self.third_element.borrow().unwrap().1; //TEST is borrow going out of scope here?
				let second_el = self.second_element.borrow().unwrap().0.reflect_ref().as_struct().unwrap();
				match mov {
					MenuMove::Up  => {
						if cur_idx > 0 {
							self.third_element.replace(Some((second_el.field_at(cur_idx -1).unwrap(),cur_idx -1)));
						}
					},
					MenuMove::Down => {
						if (cur_idx +1) < second_el.field_len(){
							self.third_element.replace(Some((second_el.field_at(cur_idx +1).unwrap(),cur_idx +1)));
						}
					},
					MenuMove::Right => {/*End of menu. No OP*/ },
					MenuMove::Left => {
						self.third_element.replace(None);
					}
				}
			}
		}
	}
}

pub static mut MENU_STATE : Lazy<MenuState<'static>> = Lazy::new(|| MenuState::new());

pub fn get_active_config_from_global_state(zone : RenderingZone) -> &'static str{
	unsafe{
		""
	}
}

pub fn get_global_menu_state() -> &'static MenuState<'static>{
	unsafe{
		& *(&raw const MENU_STATE)
	}
}

pub fn get_global_menu_state_mut() -> &'static mut MenuState<'static>{
	unsafe{
		&mut *(&raw mut MENU_STATE)
	}
}

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

	pub fn draw<'a, S : Into<&'a str>>(&mut self, text : S, align : Align, rendering : RenderingZone) {
		let nulled = CString::new(text.into()).unwrap();
		let active_node =  get_global_menu_state().is_node_active(nulled.to_str().unwrap(), rendering);
		let color = if active_node {(10,240,180)} else {(250,240,180)};
		DrawText(self.renderer, &mut self.rect, nulled.as_ptr() as *const i8, color , align);
	}


	pub fn draw_opt<'a, S : Into<&'a str>>(&mut self, arg : S, opt : S,  align : Align, rendering : RenderingZone) {
		let it = arg.into().to_string();
		let active_node =  get_global_menu_state().is_node_active(&it, rendering);
		let nulled = if active_node {
			if let Some(ref edit) = (*get_global_menu_state().get_editor_string()){
				CString::new(it.clone() + " = " + edit ).unwrap()
			}
			else{
				CString::new(it.clone() + " = " + opt.into()).unwrap()
			}
		}
		else {
			 CString::new(it.clone() + " = " + opt.into()).unwrap()
		};
		let color = if active_node {(10,240,180)} else {(250,240,180)};
		DrawText(self.renderer, &mut self.rect, nulled.as_ptr() as *const i8, color , align);
	}
}

pub fn WriteVersionString(width: i32, height : i32, string : *const i8){
	let font_render = unsafe {FontRenderer};
	let mut rect = NewRect(0, height - TextSize - 10, width, height + TextSize);

	DrawText(font_render , &mut rect, string ,(250,240,180), Align::Center);
}

pub fn RenderHeader() -> MenuRect{

	let mut rect = MenuRect::new_with_coords(PositionX, PositionY, PositionX + TitleColumnSize, PositionY + TextSize, unsafe{ FontRenderer} );
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


fn downcast_type(opaque_info : OpaqueInfo, field: &dyn PartialReflect) -> String {
	let id = opaque_info.type_id();
	if id  == TypeId::of::<u32>() {
		field.try_downcast_ref::<u32>().unwrap().to_string()
	}
	else if id  == TypeId::of::<u8>() {
		field.try_downcast_ref::<u8>().unwrap().to_string()
	}
	else if id  == TypeId::of::<u16>() {
		field.try_downcast_ref::<u16>().unwrap().to_string()
	}
	else if id  == TypeId::of::<u64>() {
		field.try_downcast_ref::<u64>().unwrap().to_string()
	}
	else if id  == TypeId::of::<bool>() {
		field.try_downcast_ref::<bool>().unwrap().to_string()
	}
	else if id  == TypeId::of::<f32>() {
		field.try_downcast_ref::<f32>().unwrap().to_string()
	}
	else if id  == TypeId::of::<f64>() {
		field.try_downcast_ref::<f64>().unwrap().to_string()
	}
	else if id  == TypeId::of::<SysString>() {
		field.try_downcast_ref::<SysString>().unwrap().to_string()
	}
	else {
	//	log(format!("{:?}", namedField));
		"<opaque>".to_owned()
	}
}

fn render_reflected_struct(namedField: &str, field: &dyn PartialReflect, zone : RenderingZone, rect : &mut MenuRect){
	match field.get_represented_type_info().unwrap(){
		bevy_reflect::TypeInfo::Struct(_struct_info) => {
			rect.draw(namedField, Align::Left ,zone);
		}
		bevy_reflect::TypeInfo::TupleStruct(tuple_struct_info) => todo!(),
		bevy_reflect::TypeInfo::Tuple(tuple_info) => todo!(),
		bevy_reflect::TypeInfo::List(list_info) => todo!(),
		bevy_reflect::TypeInfo::Array(array_info) => {
			let cap = array_info.capacity();
			let text = match cap {
				3 => {
					let arr = field.try_downcast_ref::<[u8;3]>().unwrap();
					let mut text = String::new();
					write!(&mut text, "{:?}", arr).expect("Could not format");
					text
				}
				_ => {
					log(format!("{}", namedField));
					"<Array>".to_owned()
				}
			};
			rect.draw_opt(namedField, &text,  Align::Left ,zone);
		}
		bevy_reflect::TypeInfo::Map(_map_info) => todo!(),
		bevy_reflect::TypeInfo::Set(_set_info) => todo!(),
		bevy_reflect::TypeInfo::Enum(_enum_info) => {
			let variant = field.reflect_ref().as_enum().unwrap();
			rect.draw_opt(namedField, variant.variant_name() ,  Align::Left ,zone);
		},
		bevy_reflect::TypeInfo::Opaque(opaque_info) => {
			let id = opaque_info.type_id();
			let v : String = if id  == TypeId::of::<u32>() {
				field.try_downcast_ref::<u32>().unwrap().to_string()
			}
			else if id  == TypeId::of::<u8>() {
				field.try_downcast_ref::<u8>().unwrap().to_string()
			}
			else if id  == TypeId::of::<u16>() {
				field.try_downcast_ref::<u16>().unwrap().to_string()
			}
			else if id  == TypeId::of::<u64>() {
				field.try_downcast_ref::<u64>().unwrap().to_string()
			}
			else if id  == TypeId::of::<bool>() {
				field.try_downcast_ref::<bool>().unwrap().to_string()
			}
			else if id  == TypeId::of::<f32>() {
				field.try_downcast_ref::<f32>().unwrap().to_string()
			}
			else if id  == TypeId::of::<f64>() {
				field.try_downcast_ref::<f64>().unwrap().to_string()
			}
			else if id  == TypeId::of::<SysString>() {
				field.try_downcast_ref::<SysString>().unwrap().to_string()
			}
			else {
				log(format!("{}", namedField));
				"<opaque>".to_owned()
			};
			rect.draw_opt(namedField, &v,  Align::Left ,zone);
		}
	}
}

pub fn RenderMenu(width: i32, height : i32){
	let mut rect = RenderHeader();
	let configtable : &dyn Struct  = get_global_menu_state().get_active_table();
	rect.next_row();
	rect.save();
	let type_info = configtable.get_represented_type_info().unwrap().as_struct().unwrap();
	for namedField in  type_info.iter() {
		rect.draw(namedField.name(), Align::Left, RenderingZone::ActiveFirst);
		rect.next_row();
	}
	rect.restore();
	rect.next_column();
	rect.save();
	let first = get_global_menu_state().get_active_for_zone(ActiveColumn::First);
	if let Some(ref first_col) = *first {
		let stru = first_col.0.reflect_ref().as_struct().unwrap();
		let type_first_selected = stru.get_represented_type_info().unwrap().as_struct().unwrap();
		for  (namedField, field) in stru.iter_fields() {
			render_reflected_struct(namedField, field, RenderingZone::ActiveSecond, &mut rect );
			rect.next_row();
		}
	}
	rect.restore();
	rect.next_column();
	rect.save();
	let second = get_global_menu_state().get_active_for_zone(ActiveColumn::Second);
	if let Some(ref second_col) = *second {
		match second_col.0.reflect_ref().as_struct() {
			Ok(structure) =>{
				let type_first_selected = structure.get_represented_type_info().unwrap().as_struct().unwrap();
				for  (namedField, field) in structure.iter_fields() {
					render_reflected_struct(namedField, field, RenderingZone::ActiveThird, &mut rect );
					rect.next_row();
				}
			},
			Err(_) => {},
		}
	}
}

#[repr(C)]
#[derive(PartialEq)]
pub enum OperationSetting {
	Add, Sub
}

fn update_selected_value(op: OperationSetting, value : &mut dyn PartialReflect){
	match value.reflect_mut() {
		bevy_reflect::ReflectMut::Struct(_) => {},
		bevy_reflect::ReflectMut::Array(array) => log(format!("Not supported modifications for Array types")),
		bevy_reflect::ReflectMut::Enum(enum_value) => {
			let enum_type = enum_value.get_represented_enum_info().unwrap();
			let idx = enum_value.variant_index();
			let bound = enum_type.variant_len();
			let new_val = match  op {
				OperationSetting::Add => (idx +1) % bound,
				OperationSetting::Sub => (idx -1) % bound,
			};
			let new_variant = enum_type.variant_at(new_val).unwrap();
			let mut dyn_enum = enum_value.to_dynamic_enum();
			dyn_enum.set_variant_with_index(new_val, new_variant.name(), DynamicVariant::Unit );
			enum_value.apply(dyn_enum.as_partial_reflect());
		},
		bevy_reflect::ReflectMut::Opaque(opaque_value) => {
			let id = opaque_value.get_represented_type_info().unwrap().type_id();
			if id  == TypeId::of::<u32>() {
				let mut val = opaque_value.try_downcast_ref::<u32>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => val +1,
					OperationSetting::Sub => val -1,
				};
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<u8>() {
				let val =  opaque_value.try_downcast_ref::<u8>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => val +1,
					OperationSetting::Sub => val -1,
				};
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<u16>() {
				let val =  opaque_value.try_downcast_ref::<u16>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => val +1,
					OperationSetting::Sub => val -1,
				};
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<u64>() {
				let val =  opaque_value.try_downcast_ref::<u64>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => val +1,
					OperationSetting::Sub => val -1,
				};
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<bool>() {
				let val =  opaque_value.try_downcast_ref::<bool>().unwrap();
				let new_val = !val;
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<f32>() {
				let val =  opaque_value.try_downcast_ref::<f32>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => ((val * 100.0f32).round()  + 1.0f32) / 100.0f32,
					OperationSetting::Sub => ((val * 100.0f32).round()  - 1.0f32) / 100.0f32,
				};
				opaque_value.apply(&new_val);
			}
			else if id  == TypeId::of::<f64>() {
				let val =  opaque_value.try_downcast_ref::<f64>().unwrap();
				let new_val = match  op {
					OperationSetting::Add => ((val * 100.0f64).round()  + 1.0f64) / 100.0f64,
					OperationSetting::Sub => ((val * 100.0f64).round()  - 1.0f64) / 100.0f64,
				};
				opaque_value.apply(&new_val);
			}
			else {
				log(format!("Cannot change element of type {:?}", opaque_value))
			}
		},
		_ => todo!()
	}
}


pub fn ChangeCurrentSetting(op : OperationSetting) -> Option<String> {
	match get_global_menu_state().get_terminal_field(){
		None => {None},
		Some((element, name)) => {
			update_selected_value(op,element);
			name.map(|name| name.to_owned())
		},
	}
}

pub fn IsEditorMode() -> bool {
	get_global_menu_state().is_editor_mode()
}

pub fn EnterEditorMode() {
	get_global_menu_state().set_editor_mode();
}

pub fn CloseEditorMode() {
	get_global_menu_state().close_editor_mode();
}

pub fn AddCharacterToEditorMode(ascii_c : std::ascii::Char) {
	get_global_menu_state().add_character_to_edit(ascii_c.to_char());
}

