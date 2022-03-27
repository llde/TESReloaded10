#ifndef __RADBASEH__
  #define __RADBASEH__

  #define RADSTRUCT struct
  #define RADRESTRICT __restrict

  #define RADINLINE __inline

  #define RADTODO(str)
  #define RADLINK __stdcall
  #define RADEXPLINK __stdcall
  #define RADEXPFUNC RADDEFFUNC __declspec(dllimport)
  #define RADASMLINK __cdecl

  #define RADDEFFUNC extern "C"
  #define RADDEFSTART extern "C" {
  #define RADDEFEND }
  #define RADDEFINEDATA extern "C"
  #define RADDECLAREDATA extern "C"
  #define RADDEFAULT( val ) =val

  #define RAD_ALIGN(type,var,num) type __declspec(align(num)) var

  #define S8 signed char
  #define U8 unsigned char
  #define U32 unsigned int
  #define S32 signed int
  #define INTADDR int
  #define UINTADDR unsigned int
  #define SINTa signed int
  #define UINTa unsigned int
  #define F32 float
  #define F64 double
  #define U64 unsigned __int64
  #define S64 signed __int64
  #define PTR4
  #define U16 unsigned short
  #define S16 signed short

  #define RAD_UNUSED_VARIABLE(x) (void)(sizeof(x))

#endif
