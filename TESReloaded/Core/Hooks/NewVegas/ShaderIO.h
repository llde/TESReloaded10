#pragma once

static NiD3DVertexShader* (__thiscall* CreateVertexShader)(BSShader*, char*, char*, char*, char*) = (NiD3DVertexShader* (__thiscall*)(BSShader*, char*, char*, char*, char*))Hooks::CreateVertexShader;
static NiD3DVertexShader* __fastcall CreateVertexShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName) {

	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)(*CreateVertexShader)(This, FileName, Arg2, ShaderType, ShaderName);

	VertexShader->ShaderProg = NULL;
	VertexShader->ShaderProgE = NULL;
	VertexShader->ShaderProgI = NULL;
	VertexShader->ShaderHandleBackup = VertexShader->ShaderHandle;
	strcpy(VertexShader->ShaderName, ShaderName);
	if (!memcmp(VertexShader->ShaderName, "ISNOISESCROLLANDBLEND", 21)) {
		strcpy(VertexShader->ShaderName, "WATERHEIGHTMAP0.vso");
		TheShaderManager->WaterVertexShaders[0] = VertexShader;
	}
	else if (!memcmp(VertexShader->ShaderName, "ISNOISENORMALMAP", 16)) {
		strcpy(VertexShader->ShaderName, "WATERHEIGHTMAP1.vso");
		TheShaderManager->WaterVertexShaders[1] = VertexShader;
	}
	TheShaderManager->LoadShader(VertexShader);
	return (NiD3DVertexShader*)VertexShader;

}

static NiD3DPixelShader* (__thiscall* CreatePixelShader)(BSShader*, char*, char*, char*, char*) = (NiD3DPixelShader* (__thiscall*)(BSShader*, char*, char*, char*, char*))Hooks::CreatePixelShader;
static NiD3DPixelShader* __fastcall CreatePixelShaderHook(BSShader* This, UInt32 edx, char* FileName, char* Arg2, char* ShaderType, char* ShaderName) {

	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)(*CreatePixelShader)(This, FileName, Arg2, ShaderType, ShaderName);

	PixelShader->ShaderProg = NULL;
	PixelShader->ShaderProgE = NULL;
	PixelShader->ShaderProgI = NULL;
	PixelShader->ShaderHandleBackup = PixelShader->ShaderHandle;
	strcpy(PixelShader->ShaderName, ShaderName);
	if (!memcmp(PixelShader->ShaderName, "ISNOISESCROLLANDBLEND", 21)) {
		strcpy(PixelShader->ShaderName, "WATERHEIGHTMAP0.pso");
		TheShaderManager->WaterPixelShaders[0] = PixelShader;
	}
	else if (!memcmp(PixelShader->ShaderName, "ISNOISENORMALMAP", 16)) {
		strcpy(PixelShader->ShaderName, "WATERHEIGHTMAP1.pso");
		TheShaderManager->WaterPixelShaders[1] = PixelShader;
	}
	TheShaderManager->LoadShader(PixelShader);
	return (NiD3DPixelShader*)PixelShader;

}

static void (__cdecl* SetShaderPackage)(int, int, UInt8, int, char*, int) = (void (__cdecl*)(int, int, UInt8, int, char*, int))Hooks::SetShaderPackage;
static void __cdecl SetShaderPackageHook(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {
	
	UInt32* ShaderPackage = (UInt32*)0x011F91C0;
	UInt32* ShaderPackageMax = (UInt32*)0x011F91BC;

	SetShaderPackage(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	*ShaderPackage = 7;
	*ShaderPackageMax = 7;

}