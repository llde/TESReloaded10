#pragma once

static NiD3DVertexShader* (__thiscall* CreateVertexShader)(BSShader*, char*, char*, char*, char*, UInt32, UInt32) = (NiD3DVertexShader* (__thiscall*)(BSShader*, char*, char*, char*, char*, UInt32, UInt32))Hooks::CreateVertexShader;
static NiD3DVertexShader* __fastcall CreateVertexShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName, UInt32 Arg5, UInt32 Arg6) {

	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)(*CreateVertexShader)(This, FileName, Arg2, ShaderType, ShaderName, Arg5, Arg6);

	VertexShader->ShaderProg = NULL;
	VertexShader->ShaderProgE = NULL;
	VertexShader->ShaderProgI = NULL;
	VertexShader->ShaderHandleBackup = VertexShader->ShaderHandle;
	strcpy(VertexShader->ShaderName, ShaderName);
	TheShaderManager->LoadShader(VertexShader);
	return (NiD3DVertexShader*)VertexShader;

}

static NiD3DPixelShader* (__thiscall* CreatePixelShader)(BSShader*, char*, char*, char*, char*, UInt32, UInt32) = (NiD3DPixelShader* (__thiscall*)(BSShader*, char*, char*, char*, char*, UInt32, UInt32))Hooks::CreatePixelShader;
static NiD3DPixelShader* __fastcall CreatePixelShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName, UInt32 Arg5, UInt32 Arg6) {

	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)(*CreatePixelShader)(This, FileName, Arg2, ShaderType, ShaderName, Arg5, Arg6);

	PixelShader->ShaderProg = NULL;
	PixelShader->ShaderProgE = NULL;
	PixelShader->ShaderProgI = NULL;
	PixelShader->ShaderHandleBackup = PixelShader->ShaderHandle;
	strcpy(PixelShader->ShaderName, ShaderName);
	TheShaderManager->LoadShader(PixelShader);
	return (NiD3DPixelShader*)PixelShader;

}

static void (__cdecl* SetShaderPackage)(int, int, UInt8, int, char*, int) = (void (__cdecl*)(int, int, UInt8, int, char*, int))Hooks::SetShaderPackage;
static void __cdecl SetShaderPackageHook(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {
	
	UInt32* ShaderPackage = (UInt32*)0x00B42F48;
	UInt32* ShaderPackageMax = (UInt32*)0x00B42D74;

	SetShaderPackage(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	*ShaderPackage = 7;
	*ShaderPackageMax = 7;

}