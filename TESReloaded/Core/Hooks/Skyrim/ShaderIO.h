#pragma once

extern int (__thiscall* CreateVertexShader)(NiD3DVertexShader*, BSIStream*, int);
int __fastcall CreateVertexShaderHook(NiD3DVertexShader* This, UInt32 edx, BSIStream* ShaderPackage, int Arg2);

extern int (__thiscall* CreatePixelShader)(NiD3DPixelShader*, BSIStream*, int);
int __fastcall CreatePixelShaderHook(NiD3DPixelShader* This, UInt32 edx, BSIStream* ShaderPackage, int Arg2);

extern bool (__thiscall* LoadBloodSplatterShader)(void*, BSIStream*);
bool __fastcall LoadBloodSplatterShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadDistantTreeShader)(void*, BSIStream*);
bool __fastcall LoadDistantTreeShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadGrassShader)(void*, BSIStream*);
bool __fastcall LoadGrassShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadParticleShader)(void*, BSIStream*);
bool __fastcall LoadParticleShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadSkyShader)(void*, BSIStream*);
bool __fastcall LoadSkyShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadEffectShader)(void*, BSIStream*);
bool __fastcall LoadEffectShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadLightingShader)(void*, BSIStream*);
bool __fastcall LoadLightingShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadUtilityShader)(void*, BSIStream*);
bool __fastcall LoadUtilityShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern bool (__thiscall* LoadWaterShader)(void*, BSIStream*);
bool __fastcall LoadWaterShaderHook(void* This, UInt32 edx, BSIStream* ShaderPackage);

extern int (__thiscall* LoadImageSpaceShaders)(void*);
int __fastcall LoadImageSpaceShadersHook(void* This, UInt32 edx);

extern int (__thiscall* LoadLightingShaderExtra)(void*);
int __fastcall LoadLightingShaderExtraHook(void* This, UInt32 edx);