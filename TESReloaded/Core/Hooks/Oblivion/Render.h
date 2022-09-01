#pragma once
extern void(__thiscall* Render)(Main*, BSRenderedTexture*);
void __fastcall RenderHook(Main* This, UInt32 edx, BSRenderedTexture* RenderedTexture);

extern bool(__thiscall* EndTargetGroup)(BSShaderAccumulator*, NiCamera*, NiRenderTargetGroup*);
bool __fastcall EndTargetGroupHook(BSShaderAccumulator* This, UInt32 edx, NiCamera* Camera, NiRenderTargetGroup* TargetGroup);

extern void(__thiscall* HDRRender)(HDRShader*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void __fastcall HDRRenderHook(HDRShader* This, UInt32 edx, NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4);

extern void(__thiscall* WaterHeightMapRender)(WaterShaderHeightMap*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void __fastcall WaterHeightMapRenderHook(WaterShaderHeightMap* This, UInt32 edx, NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4);

extern float(__thiscall* FarPlane)(SceneGraph*);
float __fastcall FarPlaneHook(SceneGraph* This, UInt32 edx);

extern UInt32(__thiscall* SetupShaderPrograms)(NiShader*, NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
UInt32 __fastcall SetupShaderProgramsHook(NiShader* This, UInt32 edx, NiGeometry* Geometry, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* SkinPartition, NiGeometryBufferData* GeometryBufferData, NiPropertyState* PropertyState, NiDynamicEffectState* EffectState, NiTransform* WorldTransform, UInt32 WorldBound);

extern HRESULT(__thiscall* SetSamplerState)(NiDX9RenderState*, UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
HRESULT __fastcall SetSamplerStateHook(NiDX9RenderState* This, UInt32 edx, UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 Save);

extern void(__thiscall* RenderReflections)(WaterManager*, NiCamera*, ShadowSceneNode*);
void __fastcall RenderReflectionsHook(WaterManager* This, UInt32 edx, NiCamera* Camera, ShadowSceneNode* SceneNode);

extern void(__thiscall* WaterCullingProcess)(TESWaterCullingProcess*, NiAVObject*);
void __fastcall WaterCullingProcessHook(TESWaterCullingProcess* This, UInt32 edx, NiAVObject* Object);

extern NiPixelData* (__cdecl* SaveGameScreenshot)(int*, int*);
NiPixelData* __cdecl SaveGameScreenshotHook(int* pWidth, int* pHeight);

extern void(__cdecl* RenderObject)(NiCamera*, NiNode*, NiCullingProcess*, NiVisibleArray*);
void __cdecl RenderObjectHook(NiCamera* Camera, NiNode* Object, NiCullingProcess* CullingProcess, NiVisibleArray* VisibleArray);

extern void(__cdecl* ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*);
void __cdecl ProcessImageSpaceShadersHook(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2);

extern void* (__thiscall* ShowDetectorWindow)(DetectorWindow*, HWND, HINSTANCE, NiNode*, char*, int, int, int, int);
void* __fastcall ShowDetectorWindowHook(DetectorWindow* This, UInt32 edx, HWND Handle, HINSTANCE Instance, NiNode* RootNode, char* FormCaption, int X, int Y, int Width, int Height);


void RenderInterfaceHook();
void SkipFogPassHook();
void DetectorWindowCreateTreeViewHook();
void DetectorWindowDumpAttributesHook();
void DetectorWindowConsoleCommandHook();

void DetectorWindowSetNodeName(char* Buffer, char* Format, char* ClassName, char* Name, float LPosX, float LPosY, float LPosZ);