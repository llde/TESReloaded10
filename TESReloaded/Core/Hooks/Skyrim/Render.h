#pragma once

extern void (__thiscall* Render)(Main*, BSRenderedTexture*, int, int);
void __fastcall RenderHook(Main* This, UInt32 edx, BSRenderedTexture* RenderedTexture, int Arg2, int Arg3);

extern bool (__cdecl* SetupRenderingPass)(UInt32, BSShader*);
bool __cdecl SetupRenderingPassHook(UInt32 PassIndex, BSShader* Shader);

extern void (__thiscall* RenderWorldSceneGraph)(Main*, Sun*, UInt8, UInt8);
void __fastcall RenderWorldSceneGraphHook(Main* This, UInt32 edx, Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame);

extern void (__thiscall* RenderFirstPerson)(Main*, NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8);
void __fastcall RenderFirstPersonHook(Main* This, UInt32 edx, NiDX9Renderer* Renderer, NiGeometry* Geo, Sun* SkySun, BSRenderedTexture* RenderedTexture, UInt8 IsMultiSample);

extern void (__cdecl* ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*);
void __cdecl ProcessImageSpaceShadersHook(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2);

void RenderInterfaceHook();
void RenderingGeometryHook();
void SetShadowDistanceHook();
void SetShadowDistanceShaderHook();
