#include "ShaderIO.h"

NiD3DVertexShader* (__thiscall* CreateVertexShader)(BSShader*, char*, char*, char*, char*, UInt32, UInt32) = (NiD3DVertexShader* (__thiscall*)(BSShader*, char*, char*, char*, char*, UInt32, UInt32))Hooks::CreateVertexShader;
NiD3DVertexShader* __fastcall CreateVertexShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName, UInt32 Arg5, UInt32 Arg6) {

	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)(*CreateVertexShader)(This, FileName, Arg2, ShaderType, ShaderName, Arg5, Arg6);
	if (!VertexShader) {
		Logger::Log("[WARNING] Vertex Shader %s failed to load. This is caused by mods modifying shaderpackages by OBMM.", ShaderName);
		return VertexShader;
	}
	VertexShader->ShaderProg = NULL;
	VertexShader->ShaderProgE = NULL;
	VertexShader->ShaderProgI = NULL;
	VertexShader->ShaderHandleBackup = VertexShader->ShaderHandle;
	strcpy(VertexShader->ShaderName, ShaderName);
	TheShaderManager->LoadShader(VertexShader);
	return (NiD3DVertexShader*)VertexShader;

}

NiD3DPixelShader* (__thiscall* CreatePixelShader)(BSShader*, char*, char*, char*, char*, UInt32, UInt32) = (NiD3DPixelShader* (__thiscall*)(BSShader*, char*, char*, char*, char*, UInt32, UInt32))Hooks::CreatePixelShader;
NiD3DPixelShader* __fastcall CreatePixelShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName, UInt32 Arg5, UInt32 Arg6) {

	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)(*CreatePixelShader)(This, FileName, Arg2, ShaderType, ShaderName, Arg5, Arg6);
	if (!PixelShader) {
		Logger::Log("[WARNING] Pixel Shader %s failed to load. This is caused by mods modifying shaderpackages by OBMM.", ShaderName);
		return PixelShader;
	}
	PixelShader->ShaderProg = NULL;
	PixelShader->ShaderProgE = NULL;
	PixelShader->ShaderProgI = NULL;
	PixelShader->ShaderHandleBackup = PixelShader->ShaderHandle;
	strcpy(PixelShader->ShaderName, ShaderName);
	TheShaderManager->LoadShader(PixelShader);
	return (NiD3DPixelShader*)PixelShader;

}

void (__cdecl* SetShaderPackage)(int, int, UInt8, int, char*, int) = (void (__cdecl*)(int, int, UInt8, int, char*, int))Hooks::SetShaderPackage;
void __cdecl SetShaderPackageHook(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {
	
	UInt32* ShaderPackage = (UInt32*)0x00B42F48;
	UInt32* ShaderPackageMax = (UInt32*)0x00B42D74;
	Logger::Log("%u %u %u %u %s %u", Arg1,Arg2,Force1XShaders,Arg4, GraphicsName, Arg6);
	SetShaderPackage(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	*ShaderPackage = 7;
	*ShaderPackageMax = 7;

}