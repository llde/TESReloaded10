#pragma once
extern NiD3DVertexShader* (__thiscall* CreateVertexShader)(BSShader*, char*, char*, char*, char*);
NiD3DVertexShader* __fastcall CreateVertexShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName);

extern NiD3DPixelShader* (__thiscall* CreatePixelShader)(BSShader*, char*, char*, char*, char*);
NiD3DPixelShader* __fastcall CreatePixelShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName);

extern void(__cdecl* SetShaderPackage)(int, int, UInt8, int, char*, int);
void __cdecl SetShaderPackageHook(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6);