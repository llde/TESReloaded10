#pragma once

static char ShaderPrefix[8] = "SHADER";
static int VertexShaderCounter = 0;
static int PixelShaderCounter = 0;

int (__thiscall* CreateVertexShader)(NiD3DVertexShader*, BSIStream*, int) = (int (__thiscall*)(NiD3DVertexShader*, BSIStream*, int))Hooks::CreateVertexShader;
int __fastcall CreateVertexShaderHook(NiD3DVertexShader* This, UInt32 edx, BSIStream* ShaderPackage, int Arg2) {
	
	int r = (*CreateVertexShader)(This, ShaderPackage, Arg2);
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)This;
	char Counter[8];

	VertexShader->ShaderProg = NULL;
	VertexShader->ShaderProgE = NULL;
	VertexShader->ShaderProgI = NULL;
	VertexShader->ShaderHandleBackup = VertexShader->ShaderHandle;
	VertexShaderCounter += 1;
	_itoa(VertexShaderCounter, Counter, 10);
	strcpy(VertexShader->ShaderName, ShaderPrefix);
	strcat(VertexShader->ShaderName, Counter);
	strcat(VertexShader->ShaderName, ".vso");
	TheShaderManager->LoadShader(VertexShader);
	if (!memcmp(VertexShader->ShaderName, "WATER", 5)) TheShaderManager->WaterVertexShaders[VertexShaderCounter - 1] = VertexShader;
	return r;

}

int (__thiscall* CreatePixelShader)(NiD3DPixelShader*, BSIStream*, int) = (int (__thiscall*)(NiD3DPixelShader* , BSIStream*, int))Hooks::CreatePixelShader;
int __fastcall CreatePixelShaderHook(NiD3DPixelShader* This, UInt32 edx, BSIStream* ShaderPackage, int Arg2) {

	int r = (*CreatePixelShader)(This, ShaderPackage, Arg2);
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)This;
	char Counter[8];
	
	PixelShader->ShaderProg = NULL;
	PixelShader->ShaderProgE = NULL;
	PixelShader->ShaderProgI = NULL;
	PixelShader->ShaderHandleBackup = PixelShader->ShaderHandle;
	PixelShaderCounter += 1;
	_itoa(PixelShaderCounter, Counter, 10);
	strcpy(PixelShader->ShaderName, ShaderPrefix);
	strcat(PixelShader->ShaderName, Counter);
	strcat(PixelShader->ShaderName, ".pso");
	TheShaderManager->LoadShader(PixelShader);
	if (!memcmp(PixelShader->ShaderName, "WATER", 5)) TheShaderManager->WaterPixelShaders[PixelShaderCounter - 1] = PixelShader;
	return r;

}

bool (__thiscall* LoadBloodSplatterShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadBloodSplatterShader;
bool __fastcall LoadBloodSplatterShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "BLOOD");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadBloodSplatterShader)(This, ShaderPackage);

}

bool (__thiscall* LoadDistantTreeShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadDistantTreeShader;
bool __fastcall LoadDistantTreeShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "DTREE");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (LoadDistantTreeShader)(This, ShaderPackage);

}

bool (__thiscall* LoadGrassShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadGrassShader;
bool __fastcall LoadGrassShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "GRASS");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadGrassShader)(This, ShaderPackage);

}

bool (__thiscall* LoadParticleShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadParticleShader;
bool __fastcall LoadParticleShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "PARTIC");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadParticleShader)(This, ShaderPackage);

}

bool (__thiscall* LoadSkyShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadSkyShader;
bool __fastcall LoadSkyShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "SKY");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadSkyShader)(This, ShaderPackage);

}

bool (__thiscall* LoadEffectShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadEffectShader;
bool __fastcall LoadEffectShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "EFFECT");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadEffectShader)(This, ShaderPackage);

}

bool (__thiscall* LoadLightingShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadLightingShader;
bool __fastcall LoadLightingShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "LIGHT");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadLightingShader)(This, ShaderPackage);

}

bool (__thiscall* LoadUtilityShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadUtilityShader;
bool __fastcall LoadUtilityShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "UTIL");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadUtilityShader)(This, ShaderPackage);

}

bool (__thiscall* LoadWaterShader)(void*, BSIStream*) = (bool (__thiscall*)(void*, BSIStream*))Hooks::LoadWaterShader;
bool __fastcall LoadWaterShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage) {

	strcpy(ShaderPrefix, "WATER");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadWaterShader)(This, ShaderPackage);

}

int (__thiscall* LoadImageSpaceShaders)(void*) = (int (__thiscall*)(void*))Hooks::LoadImageSpaceShaders;
int __fastcall LoadImageSpaceShadersHook(void* This, UInt32 edx) {

	strcpy(ShaderPrefix, "IMAGE");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadImageSpaceShaders)(This);

}

int (__thiscall* LoadLightingShaderExtra)(void*) = (int (__thiscall*)(void*))Hooks::LoadLightingShaderExtra;
int __fastcall LoadLightingShaderExtraHook(void* This, UInt32 edx) {

	strcpy(ShaderPrefix, "LIGHTE");
	VertexShaderCounter = 0;
	PixelShaderCounter = 0;
	return (*LoadLightingShaderExtra)(This);

}