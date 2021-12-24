#include <CommCtrl.h>
#include "RenderHook.h"

#if defined(OBLIVION)
#define kRender 0x0040C830
#define kProcessImageSpaceShaders 0x007B48E0
#define kMenuRenderedTexture 0x00B333E8
#define kDetectorWindowScale 0x004965A8
#define kDetectorWindowScaleReturn 0x0049660F
static const UInt32 kRenderInterface = 0x0057F3F3;
static const UInt32 kRenderInterfaceReturn = 0x0057F3F8;
static const UInt32 kRenderInterfaceMethod = 0x0070E0A0;
static const UInt32 kSkipFogPass = 0x007AE6F5;
static const UInt32 kSkipFogPassReturn = 0x007AE6FB;
static const UInt32 kDetectorWindowSetNodeName = 0x0049658E;
static const UInt32 kDetectorWindowCreateTreeView = 0x00495E1F;
static const UInt32 kDetectorWindowCreateTreeViewReturn = 0x00495E27;
static const UInt32 kDetectorWindowDumpAttributes = 0x004967C7;
static const UInt32 kDetectorWindowDumpAttributesReturn = 0x004967CD;
static const UInt32 kDetectorWindowConsoleCommand = 0x0040CC6C;
static const UInt32 kDetectorWindowConsoleCommandReturn = 0x0040CC73;
#elif defined(SKYRIM)
#define kRender 0x0069BDF0
#define kProcessImageSpaceShaders 0x00C70DA0
#define kMenuRenderedTexture 0x01B2E8D8
static const UInt32 kRenderInterface = 0x00A5CB57;
static const UInt32 kRenderInterfaceReturn = 0x00A5CB5C;
static const UInt32 kRenderInterfaceMethod = 0x00A623F0;
static const UInt32 kRenderingGeometry = 0x00CAFFC0;
static const UInt32 kRenderingGeometryReturn = 0x00CAFFC5;
static const UInt32 kSetShadowDistance = 0x00CBB140;
static const UInt32 kSetShadowDistanceReturn = 0x00CBB146;
static const UInt32 kSetShadowDistanceShader = 0x00CB7365;
static const UInt32 kSetShadowDistanceShaderReturn = 0x00CB736D;
static NiGeometry* Geometry = NULL;
#endif

class RenderHook {
public:
#if defined (OBLIVION)
	void*	TrackShowDetectorWindow(HWND, HINSTANCE, NiNode*, char*, int, int, int, int);
	void	TrackRender(BSRenderedTexture*);
	bool	TrackEndTargetGroup(NiCamera*, NiRenderTargetGroup*);
	void	TrackHDRRender(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
	void	TrackWaterHeightMapRender(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
	UInt32	TrackSetupShaderPrograms(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
	float	TrackFarPlane();
	HRESULT TrackSetSamplerState(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
	void	TrackRenderReflections(NiCamera*, ShadowSceneNode*);
	void	TrackWaterCullingProcess(NiAVObject*);
#elif defined(SKYRIM)
	void	TrackRender(BSRenderedTexture*, int, int);
	void	TrackRenderWorldSceneGraph(Sun*, UInt8, UInt8);
	void	TrackRenderFirstPerson(NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8);
#endif

};

#if defined(OBLIVION)
void* (__thiscall RenderHook::* ShowDetectorWindow)(HWND, HINSTANCE, NiNode*, char*, int, int, int, int);
void* (__thiscall RenderHook::* TrackShowDetectorWindow)(HWND, HINSTANCE, NiNode*, char*, int, int, int, int);
void* RenderHook::TrackShowDetectorWindow(HWND Handle, HINSTANCE Instance, NiNode* RootNode, char* FormCaption, int X, int Y, int Width, int Height) {
	
	NiAVObject* Object = NULL;
	void* r = NULL;

	r = (this->*ShowDetectorWindow)(Handle, Instance, RootNode, "Pipeline detector by Alenet", X, Y, 1280, 1024);
	for (int i = 0; i < RootNode->m_children.end; i++) {
		NiNode* Node = (NiNode*)RootNode->m_children.data[i];
		Node->m_children.data[0] = NULL;
		Node->m_children.data[1] = NULL;
		Node->m_children.end = 0;
		Node->m_children.numObjs = 0;
	}
	return r;

}

void (__thiscall RenderHook::* Render)(BSRenderedTexture*);
void (__thiscall RenderHook::* TrackRender)(BSRenderedTexture*);
void RenderHook::TrackRender(BSRenderedTexture* RenderedTexture) {
	
	SettingsMainStruct* SettingsMain = &TheSettingManager->SettingsMain;
	
	TheFrameRateManager->UpdatePerformance();
	TheCameraManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (SettingsMain->OcclusionCulling.Enabled) TheOcclusionManager->PerformOcclusionCulling();
	TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->defaultRTGroup->RenderTargets[1]->data->Surface;
	if (SettingsMain->Develop.TraceShaders && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None) && TheKeyboardManager->OnKeyDown(SettingsMain->Develop.TraceShaders) && DWNode::Get() == NULL) DWNode::Create();
	(this->*Render)(RenderedTexture);

}

bool (__thiscall RenderHook::* EndTargetGroup)(NiCamera*, NiRenderTargetGroup*);
bool (__thiscall RenderHook::* TrackEndTargetGroup)(NiCamera*, NiRenderTargetGroup*);
bool RenderHook::TrackEndTargetGroup(NiCamera* Camera, NiRenderTargetGroup* TargetGroup) {

	TargetGroup = TheRenderManager->defaultRTGroup;
	return (this->*EndTargetGroup)(Camera, TargetGroup);

}

void (__thiscall RenderHook::* HDRRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void (__thiscall RenderHook::* TrackHDRRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void RenderHook::TrackHDRRender(NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4) {
	
	TheRenderManager->clearColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	(this->*HDRRender)(ScreenElements, RenderedTexture1, RenderedTexture2, Arg4);

}

void (__thiscall RenderHook::* WaterHeightMapRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void (__thiscall RenderHook::* TrackWaterHeightMapRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void RenderHook::TrackWaterHeightMapRender(NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4) {
	
	WaterShaderHeightMap* ShaderHeightMap = (WaterShaderHeightMap*)this;
	NiRenderTargetGroup* TargetGroup = NULL;
	NiViewport Viewport = { 0.0f, 1.0f, 1.0f, 0.0f };
	
	if (TheSettingManager->SettingsMain.Shaders.Water) {
		ShaderHeightMap->Unk090 = 1.0f;
		ShaderHeightMap->Unk094 = 1.0f;
		ShaderHeightMap->Unk098 = 0.5f / 256.0f;
		ShaderHeightMap->Unk09C = 0.5f / 256.0f;
		ShaderHeightMap->CurrentPixelIndex = 5;
		TargetGroup = (NiRenderTargetGroup*)ThisCall(0x007D6FE0, *RenderedTexture2);
		BeginRendering(0, TargetGroup);
		if ((TheRenderManager->SceneState1 == 1 || TheRenderManager->SceneState2 == 1) && TheRenderManager->IsReady == 1) TheRenderManager->SetupScreenSpaceCamera(&Viewport);
		ThisCall(0x00709C60, ScreenElements, TheRenderManager);
		EndRendering();
	}
	else {
		(this->*WaterHeightMapRender)(ScreenElements, RenderedTexture1, RenderedTexture2, Arg4);
	}

}

float (__thiscall RenderHook::* FarPlane)();
float (__thiscall RenderHook::* TrackFarPlane)();
float RenderHook::TrackFarPlane() {
	
	float r = (this->*FarPlane)();

	if (TheSettingManager->SettingsMain.Main.FarPlaneDistance && r == 283840.0f) r = TheSettingManager->SettingsMain.Main.FarPlaneDistance;
	return r;

}

UInt32 (__thiscall RenderHook::* SetupShaderPrograms)(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
UInt32 (__thiscall RenderHook::* TrackSetupShaderPrograms)(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
UInt32 RenderHook::TrackSetupShaderPrograms(NiGeometry* Geometry, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* SkinPartition, NiGeometryBufferData* GeometryBufferData, NiPropertyState* PropertyState, NiDynamicEffectState* EffectState, NiTransform* WorldTransform, UInt32 WorldBound) {
	
	D3DXVECTOR4* Toggles = (D3DXVECTOR4*)0x00B46688;
	NiD3DPass* Pass = ((NiD3DShader*)this)->CurrentPass;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;
	UInt32 PassIndex = *(UInt32*)0x00B42E90;
	
	if (VertexShader && PixelShader) {
		VertexShader->SetupShader(TheRenderManager->renderState->GetVertexShader());
		PixelShader->SetupShader(TheRenderManager->renderState->GetPixelShader());
		Toggles->y = 1.0f;
		if (DWNode::Get()) {
			char Name[256];
			sprintf(Name, "Pass %i %s, %s (%s %s)", PassIndex, GetPassDescription(PassIndex), Geometry->m_pcName, VertexShader->ShaderName, PixelShader->ShaderName);
			if (VertexShader->ShaderHandle == VertexShader->ShaderHandleBackup) strcat(Name, " - Vertex: vanilla");
			if (PixelShader->ShaderHandle == PixelShader->ShaderHandleBackup) strcat(Name, " - Pixel: vanilla");
			DWNode::AddNode(Name, Geometry->m_parent, Geometry);
		}
	}
	return (this->*SetupShaderPrograms)(Geometry, SkinInstance, SkinPartition, GeometryBufferData, PropertyState, EffectState, WorldTransform, WorldBound);
}

HRESULT (__thiscall RenderHook::* SetSamplerState)(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
HRESULT (__thiscall RenderHook::* TrackSetSamplerState)(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
HRESULT RenderHook::TrackSetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 Save) {

	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) {
		if (Type == D3DSAMP_MAGFILTER) {
			if (Value != D3DTEXF_NONE && Value != D3DTEXF_POINT) Value = D3DTEXF_LINEAR;
		}
		if (Type == D3DSAMP_MINFILTER) {
			if (Value != D3DTEXF_NONE && Value != D3DTEXF_POINT) Value = D3DTEXF_ANISOTROPIC;
		}
		if ((Type == D3DSAMP_MIPFILTER) && ((Value == D3DTEXF_POINT) || (Value == D3DTEXF_LINEAR))) {
			Value = D3DTEXF_LINEAR;
		}
	}
	return (this->*SetSamplerState)(Sampler, Type, Value, Save);

}

void (__thiscall RenderHook::* RenderReflections)(NiCamera*, ShadowSceneNode*);
void (__thiscall RenderHook::* TrackRenderReflections)(NiCamera*, ShadowSceneNode*);
void RenderHook::TrackRenderReflections(NiCamera* Camera, ShadowSceneNode* SceneNode) {
	
	D3DXVECTOR4* ShadowData = &TheShaderManager->ShaderConst.Shadow.Data;
	D3DXVECTOR4* ParallaxData = &TheShaderManager->ShaderConst.POM.ParallaxData;
	float ShadowDataBackup = ShadowData->x;
	float ParallaxDataBackup = ParallaxData->y;

	if (DWNode::Get()) DWNode::AddNode("BEGIN REFLECTIONS RENDERING", NULL, NULL);
	if (!TheOcclusionManager->WaterOccluded) {
		ShadowData->x = -1.0f; // Disables the shadows rendering for water reflections (the geo is rendered with the same shaders used in the normal scene!)
		ParallaxData->y = -1.0f; // Disables the additional POM computation (the geo is rendered with the same shaders used in the normal scene!)
		(this->*RenderReflections)(Camera, SceneNode);
		ShadowData->x = ShadowDataBackup;
		ParallaxData->y = ParallaxDataBackup;
	}
	if (DWNode::Get()) DWNode::AddNode("END REFLECTIONS RENDERING", NULL, NULL);

}

void (__thiscall RenderHook::* WaterCullingProcess)(NiAVObject*);
void (__thiscall RenderHook::* TrackWaterCullingProcess)(NiAVObject*);
void RenderHook::TrackWaterCullingProcess(NiAVObject* Object) {
	
	NiPoint2 BoundSize;
	float BoundBox = 0.0f;
	void* VFT = *(void**)Object;
	
	if (VFT == VFTBSFadeNode && TheSettingManager->SettingsMain.OcclusionCulling.Enabled) {
		NiBound* Bound = Object->GetWorldBound();
		TheRenderManager->GetScreenSpaceBoundSize(&BoundSize, Bound);
		BoundBox = (BoundSize.x * 100.f) * (BoundSize.y * 100.0f);
		if (Object->m_flags & NiAVObject::kFlag_IsOccluded || BoundBox < TheSettingManager->SettingsMain.OcclusionCulling.OccludedReflectionsMin || Object->m_worldTransform.pos.z + Bound->Radius < TheShaderManager->ShaderConst.Water.waterSettings.x) return;
	}
	(this->*WaterCullingProcess)(Object);

}

NiPixelData* (__cdecl * SaveGameScreenshot)(int*, int*) = (NiPixelData* (__cdecl *)(int*, int*))0x00411B70;
NiPixelData* __cdecl TrackSaveGameScreenshot(int* pWidth, int* pHeight) {
	
	NiPixelData* r = NULL;
	
	TheRenderManager->IsSaveGameScreenShot = 1;
	r = SaveGameScreenshot(pWidth, pHeight);
	TheRenderManager->IsSaveGameScreenShot = 0;
	return r;

}

void (__cdecl * SetShaderPackage)(int, int, UInt8, int, char*, int) = (void (__cdecl *)(int, int, UInt8, int, char*, int))0x007B45F0;
void __cdecl TrackSetShaderPackage(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {
	
	UInt32* ShaderPackage = (UInt32*)0x00B42F48;
	UInt32* ShaderPackageMax = (UInt32*)0x00B42D74;

	SetShaderPackage(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	*ShaderPackage = 7;
	*ShaderPackageMax = 7;

}

static __declspec(naked) void SkipFogPassHook() {

	__asm {
		cmp		edi, 0x190
		jnz		short loc_continue
		add		edi, 1
	loc_continue:
		cmp     edi, 0x198
		jmp		kSkipFogPassReturn
	}

}

#elif defined(SKYRIM)
void (__thiscall RenderHook::* Render)(BSRenderedTexture*, int, int);
void (__thiscall RenderHook::* TrackRender)(BSRenderedTexture*, int, int);
void RenderHook::TrackRender(BSRenderedTexture* RenderedTexture, int Arg2, int Arg3) {
	
	TheRenderManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("START FRAME LOG");
	(this->*Render)(RenderedTexture, Arg2, Arg3);

}

bool (__cdecl * SetupRenderingPass)(UInt32, BSShader*) = (bool (__cdecl *)(UInt32, BSShader*))0x00CAF9C0;
bool __cdecl TrackSetupRenderingPass(UInt32 PassIndex, BSShader* Shader) {
	
	bool r = SetupRenderingPass(PassIndex, Shader);

	NiD3DVertexShaderEx* VertexShader = *(NiD3DVertexShaderEx**)0x01BABFB4;
	NiD3DPixelShaderEx* PixelShader = *(NiD3DPixelShaderEx**)0x01BABFB0;

	if (VertexShader && PixelShader) {
		if (VertexShader->ShaderProg) VertexShader->ShaderProg->SetCT();
		if (PixelShader->ShaderProg) PixelShader->ShaderProg->SetCT();
	}
	return r;

}

void (__thiscall RenderHook::* RenderWorldSceneGraph)(Sun*, UInt8, UInt8);
void (__thiscall RenderHook::* TrackRenderWorldSceneGraph)(Sun*, UInt8, UInt8);
void RenderHook::TrackRenderWorldSceneGraph(Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame) {
	
	bool CameraMode = TheSettingManager->SettingsMain.CameraMode.Enabled;

	(this->*RenderWorldSceneGraph)(SkySun, IsFirstPerson, WireFrame);
	if (CameraMode || Player->IsThirdPersonView(CameraMode, TheRenderManager->FirstPersonView)) TheRenderManager->ResolveDepthBuffer();

}

void (__thiscall RenderHook::* RenderFirstPerson)(NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8);
void (__thiscall RenderHook::* TrackRenderFirstPerson)(NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8);
void RenderHook::TrackRenderFirstPerson(NiDX9Renderer* Renderer, NiGeometry* Geo, Sun* SkySun, BSRenderedTexture* RenderedTexture, UInt8 IsMultiSample) {
	
	(this->*RenderFirstPerson)(Renderer, Geo, SkySun, RenderedTexture, IsMultiSample);
	TheRenderManager->ResolveDepthBuffer();
	TheRenderManager->Clear(NULL, NiRenderer::kClear_ZBUFFER);
	ThisCall(0x00697E50, Global);
	(this->*RenderFirstPerson)(Renderer, Geo, SkySun, RenderedTexture, IsMultiSample);

}

static __declspec(naked) void RenderingGeometryHook() {

	__asm {
		mov     ebx, [esi]
		mov     ebp, [esi + 8]
		mov     Geometry, ebp
		jmp		kRenderingGeometryReturn
	}

}

void SetShadowDistanceValue(float* Distance, UInt32 Pass) {

	if (Pass == 0) *Distance /= TheSettingManager->SettingsMain.ShadowMode.NearQuality;

}

static __declspec(naked) void SetShadowDistance()
{
	__asm
	{
		faddp   st(1), st
		fstp	dword ptr [esp + 0x4C]
		lea		ecx, [esp + 0x4C]
		mov		edx, [esp + 0x74]
		pushad
		pushfd
		push	edx
		push	ecx
		call	SetShadowDistanceValue
		add		esp, 8
		popfd
		popad
		jmp		kSetShadowDistanceReturn
	}
}

static __declspec(naked) void SetShadowDistanceShader()
{
	__asm
	{
		lea		ecx, [esp + 0xE0 - 0xC4 + 4]
		pushad
		pushfd
		push	0
		push	ecx
		call	SetShadowDistanceValue
		add		esp, 8
		popfd
		popad
		mov		ecx, [esp + 0xE0 - 0xC4 + 4]
		mov		[esp + esi * 4 + 0xE0 - 0x98], ecx
		jmp		kSetShadowDistanceShaderReturn
	}
}
#endif

void (__cdecl* ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*) = (void (__cdecl*)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*))kProcessImageSpaceShaders;
void __cdecl TrackProcessImageSpaceShaders(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2) {
	
	BSRenderedTexture* MenuRenderedTexture = *(BSRenderedTexture**)kMenuRenderedTexture;
	
	TheRenderManager->ResolveDepthBuffer();
	TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->BackBuffer;
	ProcessImageSpaceShaders(Renderer, RenderedTexture1, RenderedTexture2);
	if (!RenderedTexture2 && TheRenderManager->currentRTGroup) TheShaderManager->RenderEffects(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface);
	if (TheRenderManager->IsSaveGameScreenShot) {
		if (MenuRenderedTexture)
			TheRenderManager->device->StretchRect(MenuRenderedTexture->RenderTargetGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
		else
			TheRenderManager->device->StretchRect(TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
	}

}

static __declspec(naked) void RenderInterface() {
	
	__asm {
		call	kRenderInterfaceMethod
		pushad
		mov		ecx, TheGameMenuManager
		call	GameMenuManager::Render
		popad
		jmp		kRenderInterfaceReturn
	}

}

#if defined(OBLIVION)
void DetectorWindowSetNodeName(char* Buffer, char* Format, char* ClassName, char* Name, float LPosX, float LPosY, float LPosZ) {
	
	sprintf(Buffer, "%s", Name);

}

void DetectorWindowCreateTreeView(HWND TreeView) {
	
	HFONT Font = CreateFontA(14, 0, 0, 0, FW_DONTCARE, NULL, NULL, NULL, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas");
	SendMessageA(TreeView, WM_SETFONT, (WPARAM)Font, TRUE);
	SendMessageA(TreeView, TVM_SETBKCOLOR, NULL, 0x001E1E1E);
	SendMessageA(TreeView, TVM_SETTEXTCOLOR, NULL, 0x00DCDCDC);
	
}

static __declspec(naked) void DetectorWindowCreateTreeViewHook() {

	__asm {
		pushad
		push	eax
		call	DetectorWindowCreateTreeView
		pop		eax
		popad
		pop     edi
		mov		[esi + 0x0C], eax
		pop     esi
		add     esp, 0x40
		jmp		kDetectorWindowCreateTreeViewReturn
	}

}

void DetectorWindowDumpAttributes(HWND TreeView, UInt32 Msg, WPARAM wParam, LPTVINSERTSTRUCTA lParam) {

	TVITEMEXA Item = { NULL };
	char T[260] = { '\0' };

	Item.pszText = T;
	Item.mask = TVIF_TEXT;
	Item.hItem = (HTREEITEM)SendMessageA(TreeView, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)lParam->hParent);
	Item.cchTextMax = 260;
	SendMessageA(TreeView, TVM_GETITEMA, 0, (LPARAM)&Item);
	if (!memcmp(Item.pszText, "Pass", 4))
		SendMessageA(TreeView, TVM_DELETEITEM, 0, (LPARAM)lParam->hParent);
	else
		if (strlen(Item.pszText)) SendMessageA(TreeView, Msg, wParam, (LPARAM)lParam);

}

static __declspec(naked) void DetectorWindowDumpAttributesHook() {

	__asm {
		call	DetectorWindowDumpAttributes
		add		esp, 16
		movzx   ecx, word ptr [esi + 0x0A]
		jmp		kDetectorWindowDumpAttributesReturn
	}

}

static __declspec(naked) void DetectorWindowConsoleCommandHook() {

	__asm {
		call	DWNode::Create
		jmp		kDetectorWindowConsoleCommandReturn
	}

}
#endif

void CreateRenderHook() {

	*((int*)&Render)						= kRender;
	TrackRender								= &RenderHook::TrackRender;
#if defined(OBLIVION)
	*((int*)&ShowDetectorWindow)			= 0x00496CB0;
	TrackShowDetectorWindow					= &RenderHook::TrackShowDetectorWindow;
	*((int*)&SetupShaderPrograms)			= 0x0077A1F0;
	TrackSetupShaderPrograms				= &RenderHook::TrackSetupShaderPrograms;
	*((int*)&EndTargetGroup)				= 0x007AAA30;
	TrackEndTargetGroup						= &RenderHook::TrackEndTargetGroup;
	*((int*)&HDRRender)						= 0x007BDFC0;
	TrackHDRRender							= &RenderHook::TrackHDRRender;
	*((int*)&WaterHeightMapRender)			= 0x007E17D0;
	TrackWaterHeightMapRender				= &RenderHook::TrackWaterHeightMapRender;
	*((int*)&FarPlane)						= 0x00410EE0;
	TrackFarPlane							= &RenderHook::TrackFarPlane;
	*((int*)&SetSamplerState)				= 0x0077B610;
	TrackSetSamplerState					= &RenderHook::TrackSetSamplerState;
	*((int*)&RenderReflections)				= 0x0049BEF0;
	TrackRenderReflections					= &RenderHook::TrackRenderReflections;
	*((int*)&WaterCullingProcess)			= 0x0049CBF0;
	TrackWaterCullingProcess				= &RenderHook::TrackWaterCullingProcess;
#elif defined(SKYRIM)
	*((int*)&RenderWorldSceneGraph)			= 0x00692290;
	TrackRenderWorldSceneGraph				= &RenderHook::TrackRenderWorldSceneGraph;
	*((int*)&RenderFirstPerson)				= 0x00698B30;
	TrackRenderFirstPerson					= &RenderHook::TrackRenderFirstPerson;
#endif

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Render,						*((PVOID*)&TrackRender));
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders,				  &TrackProcessImageSpaceShaders);
#if defined(OBLIVION)
	DetourAttach(&(PVOID&)ShowDetectorWindow,			*((PVOID*)&TrackShowDetectorWindow));
	DetourAttach(&(PVOID&)SetupShaderPrograms,			*((PVOID*)&TrackSetupShaderPrograms));
	DetourAttach(&(PVOID&)EndTargetGroup,				*((PVOID*)&TrackEndTargetGroup));
	DetourAttach(&(PVOID&)HDRRender,					*((PVOID*)&TrackHDRRender));
	DetourAttach(&(PVOID&)WaterHeightMapRender,			*((PVOID*)&TrackWaterHeightMapRender));
	DetourAttach(&(PVOID&)FarPlane,						*((PVOID*)&TrackFarPlane));
	DetourAttach(&(PVOID&)SetSamplerState,				*((PVOID*)&TrackSetSamplerState));
	DetourAttach(&(PVOID&)RenderReflections,			*((PVOID*)&TrackRenderReflections));
	DetourAttach(&(PVOID&)WaterCullingProcess,			*((PVOID*)&TrackWaterCullingProcess));
	DetourAttach(&(PVOID&)SaveGameScreenshot,					  &TrackSaveGameScreenshot);
	DetourAttach(&(PVOID&)SetShaderPackage,						  &TrackSetShaderPackage);
#elif defined(SKYRIM)
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,		*((PVOID*)&TrackRenderWorldSceneGraph));
	DetourAttach(&(PVOID&)RenderFirstPerson,			*((PVOID*)&TrackRenderFirstPerson));
	DetourAttach(&(PVOID&)SetupRenderingPass,					  &TrackSetupRenderingPass);
#endif
    DetourTransactionCommit();

	SafeWriteJump(kRenderInterface,					(UInt32)RenderInterface);
#if defined(OBLIVION)
	SafeWriteCall(kDetectorWindowSetNodeName,		(UInt32)DetectorWindowSetNodeName);
	SafeWriteJump(kDetectorWindowCreateTreeView,	(UInt32)DetectorWindowCreateTreeViewHook);
	SafeWriteJump(kDetectorWindowDumpAttributes,	(UInt32)DetectorWindowDumpAttributesHook);
	SafeWriteJump(kDetectorWindowConsoleCommand,	(UInt32)DetectorWindowConsoleCommandHook);
	SafeWriteJump(kDetectorWindowScale,	kDetectorWindowScaleReturn); // Avoids to add the scale to the node description in the detector window
#endif
#if defined(OBLIVION)
	SafeWrite32(0x0049BFAF, WaterReflectionMapSize); // Constructor
	SafeWrite32(0x007C1045, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C104F, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C10F9, WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C1103, WaterReflectionMapSize); // RenderedSurface
	SafeWrite8(0x00A38280, 0x5A); // Fixes the "purple water bug"
	SafeWriteJump(0x00553EAC, 0x00553EB2); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x007D1BC4, 0x007D1BFD); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x007D1BCD, 0x007D1BFD); // Patches the use of Lighting30Shader only for the hair
	SafeWriteJump(0x0049C3A2, 0x0049C41D); // Avoids to manage the cells culling for reflections
	SafeWriteJump(0x0049C8CB, 0x0049C931); // Avoids to manage the cells culling for reflections
	SafeWriteJump(kSkipFogPass, (UInt32)SkipFogPassHook);
	if (TheSettingManager->SettingsMain.Shaders.Water) {
		*LocalWaterHiRes = 1;
		SafeWriteJump(0x0053B16F, 0x0053B20C); // Avoids to change atmosphere colors when underwater
		SafeWriteJump(0x00542F63, 0x00542FC1); // Avoids to remove the sun over the scene when underwater
		SafeWrite8(0x0049EBAC, 0); // Avoids to change the shader for the skydome when underwater
	}
	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) {
		SafeWrite8(0x007BE1D3, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
		SafeWrite8(0x007BE32B, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
	}
	if (TheSettingManager->SettingsMain.Main.RemovePrecipitations) SafeWriteJump(0x00543167, 0x00543176);
#elif defined(SKYRIM)
	WriteRelJump(kRenderingGeometry,		(UInt32)RenderingGeometryHook);
	if (TheSettingManager->SettingsMain.ShadowMode.NearQuality) {
		WriteRelJump(kSetShadowDistance,		(UInt32)SetShadowDistance);
		WriteRelJump(kSetShadowDistanceShader,	(UInt32)SetShadowDistanceShader);
	}
	SafeWrite8(0x00698BBB, 0); // Stops to clear the depth buffer when rendering the 1st person node
#endif

}
