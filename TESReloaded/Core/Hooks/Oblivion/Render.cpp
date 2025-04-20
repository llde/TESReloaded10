#pragma once

void (__thiscall* Render)(Main*, BSRenderedTexture*) = (void (__thiscall*)(Main*, BSRenderedTexture*))Hooks::Render;
void __fastcall RenderHook(Main* This, UInt32 edx, BSRenderedTexture* RenderedTexture) {
	
	ffi::Config* SettingsMain = TheSettingManager->Config;
	TheFrameRateManager->UpdatePerformance();
	TheCameraManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
#ifdef EXPERIMENTAL_FEATURE 
	if (SettingsMain->CullingProcess.EnableCulling) TheOcclusionManager->ManageDistantStatic();
	if (SettingsMain->OcclusionCulling.Enabled) TheOcclusionManager->PerformOcclusionCulling();
#endif
	if(TheRenderManager->BackBuffer) TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->defaultRTGroup->RenderTargets[1]->data->Surface;
	if (SettingsMain->Develop.TraceShaders && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None) && Global->OnKeyDown(SettingsMain->Develop.TraceShaders) && DWNode::Get() == NULL) DWNode::Create();
	(*Render)(This, RenderedTexture);
}

bool (__thiscall* EndTargetGroup)(BSShaderAccumulator*, NiCamera*, NiRenderTargetGroup*) = (bool (__thiscall*)(BSShaderAccumulator*, NiCamera*, NiRenderTargetGroup*))Hooks::EndTargetGroup;
bool __fastcall EndTargetGroupHook(BSShaderAccumulator* This, UInt32 edx, NiCamera* Camera, NiRenderTargetGroup* TargetGroup) {
 	if(TheRenderManager->BackBuffer) TargetGroup = TheRenderManager->defaultRTGroup;
	return (*EndTargetGroup)(This, Camera, TargetGroup);

}

void (__thiscall* HDRRender)(HDRShader*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8) = (void (__thiscall*)(HDRShader*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8))Hooks::HDRRender;
void __fastcall HDRRenderHook(HDRShader* This, UInt32 edx, NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4) {
	
	TheRenderManager->clearColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	(HDRRender)(This, ScreenElements, RenderedTexture1, RenderedTexture2, Arg4);

	if (TheRenderManager->currentRTGroup) TheShaderManager->RenderEffects(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface);

}

void (__thiscall* WaterHeightMapRender)(WaterShaderHeightMap*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8) = (void (__thiscall*)(WaterShaderHeightMap*, NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8))Hooks::WaterHeightMapRender;
void __fastcall WaterHeightMapRenderHook(WaterShaderHeightMap* This, UInt32 edx, NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4) {
	
	WaterShaderHeightMap* ShaderHeightMap = (WaterShaderHeightMap*)This;
	NiRenderTargetGroup* TargetGroup = NULL;
	NiViewport Viewport = { 0.0f, 1.0f, 1.0f, 0.0f };
	
	if (TheSettingManager->Config->Shaders.Water) { //TODO separate option. Currently the LOD and the Near water have a noticeable seam when coming closer with tfc. Lava LOD is darker then near Lava
		ShaderHeightMap->Unk090 = 1.0f;
		ShaderHeightMap->Unk094 = 1.0f;
		ShaderHeightMap->Unk098 = 0.5f / 256.0f;
		ShaderHeightMap->Unk09C = 0.5f / 256.0f;
		ShaderHeightMap->CurrentPixelIndex = 5;
		TargetGroup = (NiRenderTargetGroup*)ThisCall(0x007D6FE0, *RenderedTexture2);
		Pointers::Functions::BeginRendering(0, TargetGroup);
		if ((TheRenderManager->SceneState1 == 1 || TheRenderManager->SceneState2 == 1) && TheRenderManager->IsReady == 1) TheRenderManager->SetupScreenSpaceCamera(&Viewport);
		ThisCall(0x00709C60, ScreenElements, TheRenderManager);
		Pointers::Functions::EndRendering();
	}
	else { 
		(*WaterHeightMapRender)(This, ScreenElements, RenderedTexture1, RenderedTexture2, Arg4);
	}

}

float (__thiscall* FarPlane)(SceneGraph*) = (float (__thiscall*)(SceneGraph*))Hooks::FarPlane;
float __fastcall FarPlaneHook(SceneGraph* This, UInt32 edx) {
	
	float r = (*FarPlane)(This);

	if (TheSettingManager->Config->Main.FarPlaneDistance && r == 283840.0f) r = TheSettingManager->Config->Main.FarPlaneDistance;
	return r;

}


UInt32 (__thiscall* SetupShaderPrograms)(NiShader*, NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32) = (UInt32 (__thiscall*)(NiShader*, NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32))Hooks::SetupShaderPrograms;
UInt32 __fastcall SetupShaderProgramsHook(NiShader* This, UInt32 edx, NiGeometry* Geometry, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* SkinPartition, NiGeometryBufferData* GeometryBufferData, NiPropertyState* PropertyState, NiDynamicEffectState* EffectState, NiTransform* WorldTransform, UInt32 WorldBound) {
	
	D3DXVECTOR4* Toggles = (D3DXVECTOR4*)0x00B46688;
	NiD3DPass* Pass = ((NiD3DShader*)This)->CurrentPass;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;
	UInt32 PassIndex = *(UInt32*)0x00B42E90;
//    UInt8* IsLava = (UInt8*)0x00B47844;
//    *IsLava = 1;  Unlock pass 410 instead of 380/409
	if (VertexShader && PixelShader) {
		VertexShader->SetupShader(TheRenderManager->renderState->GetVertexShader());
		PixelShader->SetupShader(TheRenderManager->renderState->GetPixelShader());
        /*This was 1.0. This code is supposed to make the shader render the fog color on objects, however it lack depth, causing a "washed out" effect. 
         Also not all shaders consider this Toggle, so there are only some objects that are rnedered that way.
		 Using 0 it render the normal (non-fog) color, and in case use the volumetric fog shader to render the fog effect. */
		if(TheSettingManager->Config->Main.RemoveFogPass) Toggles->y = 0.0f; 
		if (DWNode::Get()) {
			char Name[256];
			sprintf(Name, "Pass %i %s, %s (%s %s)", PassIndex, Pointers::Functions::GetPassDescription(PassIndex), Geometry->m_pcName, VertexShader->ShaderName, PixelShader->ShaderName);
			if (VertexShader->ShaderHandle == VertexShader->ShaderHandleBackup) strcat(Name, " - Vertex: vanilla");
			if (PixelShader->ShaderHandle == PixelShader->ShaderHandleBackup) strcat(Name, " - Pixel: vanilla");
			DWNode::AddNode(Name, Geometry->m_parent, Geometry);
		}
	}
	UInt32 result = (*SetupShaderPrograms)(This, Geometry, SkinInstance, SkinPartition, GeometryBufferData, PropertyState, EffectState, WorldTransform, WorldBound);
	if (PassIndex == 380  || PassIndex == 409 || PassIndex == 410){ //WaterLOD
        //data[2] difuse, data[1] nothing
 //       Logger::Log("Pass %u : %u",  PassIndex, *IsLava);
    //    TheRenderManager->renderState->SetTexture(1, TheRenderManager->CurrentWaterTexture);
    }
    //if (PassIndex == 409 && Pass->Stages.numObjs == 1){
    //	if (TheKeyboardManager->OnKeyDown(44)) {
      //      NiTArray<NiD3DTextureStage*> stages = Pass->Stages;
        //    for(UInt32 i = 0; i < Pass->Stages.numObjs; i++){
          //      IDirect3DBaseTexture9* text = Pass->Stages.data[i]->Texture->rendererData->dTexture; 
       //         D3DXSaveTextureToFile(".\\0.jpg", D3DXIFF_JPG, text, NULL);
      //      }
     //   }
   // }
    return result;

}

HRESULT (__thiscall* SetSamplerState)(NiDX9RenderState*, UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8) = (HRESULT (__thiscall*)(NiDX9RenderState*, UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8))Hooks::SetSamplerState;
HRESULT __fastcall SetSamplerStateHook(NiDX9RenderState* This, UInt32 edx, UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 Save) {
	
	UInt16* TypeMap = (UInt16*)0x00B427B0;
	HRESULT r = D3D_OK;

	if (TheSettingManager->Config->Main.AnisotropicFilter >= 2) {
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
	if (TypeMap[Type] < 5)
		r = (*SetSamplerState)(This, Sampler, Type, Value, Save);
	else
		r = TheRenderManager->device->SetSamplerState(Sampler, Type, Value);
	return r;

}

void (__thiscall* RenderReflections)(WaterManager*, NiCamera*, ShadowSceneNode*) = (void (__thiscall*)(WaterManager*, NiCamera*, ShadowSceneNode*))Hooks::RenderReflections;
void __fastcall RenderReflectionsHook(WaterManager* This, UInt32 edx, NiCamera* Camera, ShadowSceneNode* SceneNode) {
	
	D3DXVECTOR4* ShadowData = &TheShaderManager->ShaderConst.Shadow.Data;
	D3DXVECTOR4* ParallaxData = &TheShaderManager->ShaderConst.POM.ParallaxData;
	float ShadowDataBackup = ShadowData->x;
	float ParallaxDataBackup = ParallaxData->y;

	if (DWNode::Get()) DWNode::AddNode("BEGIN REFLECTIONS RENDERING", NULL, NULL);
	if (!TheOcclusionManager->WaterOccluded) {
		ShadowData->x = -1.0f; // Disables the shadows rendering for water reflections (the geo is rendered with the same shaders used in the normal scene!)
		ParallaxData->y = -1.0f; // Disables the additional POM computation (the geo is rendered with the same shaders used in the normal scene!)
		(*RenderReflections)(This, Camera, SceneNode);
		ShadowData->x = ShadowDataBackup;
		ParallaxData->y = ParallaxDataBackup;
	}
	if (DWNode::Get()) DWNode::AddNode("END REFLECTIONS RENDERING", NULL, NULL);
//	TheShadowManager->RenderShadowMaps();

}



void (__thiscall* WaterCullingProcess)(TESWaterCullingProcess*, NiAVObject*) = (void (__thiscall*)(TESWaterCullingProcess*, NiAVObject*))Hooks::WaterCullingProcess;
void __fastcall WaterCullingProcessHook(TESWaterCullingProcess* This, UInt32 edx, NiAVObject* Object) {
	
	NiPoint2 BoundSize;
	float BoundBox = 0.0f;
	void* VFT = *(void**)Object;
	bool culled = false;
	if ((VFT == Pointers::VirtualTables::NiNode || VFT == Pointers::VirtualTables::BSFadeNode || VFT == Pointers::VirtualTables::BSFaceGenNiNode  && (Object->m_flags & NiAVObject::kFlag_AppCulled) == NiAVObject::kFlag_AppCulled)
		 && TheSettingManager->Config->Culling.EnableRelfectionCulling) {
		NiBound* Bound = Object->GetWorldBound();
		TheRenderManager->GetScreenSpaceBoundSize(&BoundSize, Bound);
		BoundBox = (BoundSize.x * 100.f) * (BoundSize.y * 100.0f);
	//	ThisCall(0x00707370,Object, 0.0f, true );
	//	Logger::Log("%f   %s", BoundBox, Object->m_pcName);
		if (BoundBox < TheSettingManager->Config->Culling.CullReflectionMinSize || Object->m_worldTransform.pos.z + Bound->Radius < TheShaderManager->ShaderConst.Water.waterSettings.x) {
		//	Object->OnVisible(This);
			return;
		}
	}
	(*WaterCullingProcess)(This, Object);
//	if (culled) Object->m_flags &= NiAVObject::kFlag_IsOccluded;

}

NiPixelData* (__cdecl* SaveGameScreenshot)(int*, int*) = (NiPixelData* (__cdecl*)(int*, int*))Hooks::SaveGameScreenshot;
NiPixelData* __cdecl SaveGameScreenshotHook(int* pWidth, int* pHeight) {
	
	NiPixelData* r = NULL;
	
	TheRenderManager->IsSaveGameScreenShot = 1;
	r = SaveGameScreenshot(pWidth, pHeight);
	TheRenderManager->IsSaveGameScreenShot = 0;
	return r;

}

void (__cdecl* RenderObject)(NiCamera*, NiNode*, NiCullingProcess*, NiVisibleArray*) = (void (__cdecl*)(NiCamera*, NiNode*, NiCullingProcess*, NiVisibleArray*))Hooks::RenderObject;
void __cdecl RenderObjectHook(NiCamera* Camera, NiNode* Object, NiCullingProcess* CullingProcess, NiVisibleArray* VisibleArray) {
#ifdef EXPERIMENTAL_FEATURE	
	bool CameraMode = TheSettingManager->Config->CameraMode.Enabled;
#else
	bool CameraMode = false;
#endif
	RenderObject(Camera, Object, CullingProcess, VisibleArray);
	if (Object == WorldSceneGraph && (CameraMode || !TheCameraManager->IsFirstPerson())) {
		TheRenderManager->ResolveDepthBuffer();
	}
	else if (Object == Player->firstPersonNiNode) {
		TheRenderManager->ResolveDepthBuffer();
		TheRenderManager->Clear(NULL, NiRenderer::kClear_ZBUFFER);
		RenderObject(Camera, Object, CullingProcess, VisibleArray);
	}
}

void (__cdecl* ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*) = (void (__cdecl*)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*))Hooks::ProcessImageSpaceShaders;
void __cdecl ProcessImageSpaceShadersHook(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2) {

	if(TheRenderManager->BackBuffer) TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->BackBuffer;

	ProcessImageSpaceShaders(Renderer, RenderedTexture1, RenderedTexture2);
	TheRenderManager->CheckAndTakeScreenShot(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface);
	if (TheRenderManager->IsSaveGameScreenShot) {
		if (Pointers::Generic::MenuRenderedTexture)
			TheRenderManager->device->StretchRect(Pointers::Generic::MenuRenderedTexture->RenderTargetGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
		else
			TheRenderManager->device->StretchRect(TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
	}

}

__declspec(naked) void RenderInterfaceHook() {
	
	__asm {
		call	Jumpers::RenderInterface::Method
		pushad
		mov		ecx, TheGameMenuManager
		call	GameMenuManager::Render
		popad
		jmp		Jumpers::RenderInterface::Return
	}

}


/*
 This works once, when the fog pass is on and is disabled (skipped). After that when trying to reenable the pass it crashes. Keep the settings only for startup and not for in game changes
 */
__declspec(naked) void SkipFogPassHook() {

	__asm {
        cmp     edi, 0x190
		jne		short loc_continue
		add		edi, 1
	loc_continue:
		cmp     edi, 0x198
		jmp		Jumpers::SkipFogPass::Return
	}

}

void* (__thiscall* ShowDetectorWindow)(DetectorWindow*, HWND, HINSTANCE, NiNode*, const char*, int, int, int, int) = (void* (__thiscall*)(DetectorWindow*, HWND, HINSTANCE, NiNode*, const char*, int, int, int, int))::Hooks::ShowDetectorWindow;
void* __fastcall ShowDetectorWindowHook(DetectorWindow* This, UInt32 edx, HWND Handle, HINSTANCE Instance, NiNode* RootNode, const char* FormCaption, int X, int Y, int Width, int Height) {
	
	NiAVObject* Object = NULL;
	void* r = NULL;

	r = (ShowDetectorWindow)(This, Handle, Instance, RootNode, "Pipeline detector by Alenet", X, Y, 1280, 1024);
	for (int i = 0; i < RootNode->m_children.end; i++) {
		NiNode* Node = (NiNode*)RootNode->m_children.data[i];
		Node->m_children.data[0] = NULL;
		Node->m_children.data[1] = NULL;
		Node->m_children.end = 0;
		Node->m_children.numObjs = 0;
	}
	return r;

}

void DetectorWindowSetNodeName(char* Buffer, char* Format, char* ClassName, char* Name, float LPosX, float LPosY, float LPosZ) {
	
	sprintf(Buffer, "%s", Name);

}

static void DetectorWindowCreateTreeView(HWND TreeView) {
	
	HFONT Font = CreateFontA(14, 0, 0, 0, FW_DONTCARE, NULL, NULL, NULL, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas");
	SendMessageA(TreeView, WM_SETFONT, (WPARAM)Font, TRUE);
	SendMessageA(TreeView, TVM_SETBKCOLOR, NULL, 0x001E1E1E);
	SendMessageA(TreeView, TVM_SETTEXTCOLOR, NULL, 0x00DCDCDC);
	
}

__declspec(naked) void DetectorWindowCreateTreeViewHook() {

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
		jmp		Jumpers::DetectorWindow::CreateTreeViewReturn
	}

}

static void DetectorWindowDumpAttributes(HWND TreeView, UInt32 Msg, WPARAM wParam, LPTVINSERTSTRUCTA lParam) {

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

__declspec(naked) void DetectorWindowDumpAttributesHook() {

	__asm {
		call	DetectorWindowDumpAttributes
		add		esp, 16
		movzx   ecx, word ptr [esi + 0x0A]
		jmp		Jumpers::DetectorWindow::DumpAttributesReturn
	}

}

__declspec(naked) void DetectorWindowConsoleCommandHook() {

	__asm {
		call	DWNode::Create
		jmp		Jumpers::DetectorWindow::ConsoleCommandReturn
	}

}
