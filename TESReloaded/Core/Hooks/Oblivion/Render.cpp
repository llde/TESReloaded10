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

void LogEntry(NiD3DShaderConstantMapEntry* entry) {
	if (entry && entry->DataSource) {
		if (entry->DataSize == 4) {
			Logger::Log("%s %d %d %f", entry->Key, entry->RegisterCount, entry->ShaderRegister, *((float*)entry->DataSource));
		}
		if (entry->DataSize == 8) {
			Logger::Log("%s %d %d %f %f", entry->Key, entry->RegisterCount, entry->ShaderRegister, ((float*)entry->DataSource)[0], ((float*)entry->DataSource)[1]);
		}
		if (entry->DataSize == 12) {
			Logger::Log("%s %d %d %f %f %f %f", entry->Key, entry->RegisterCount, entry->ShaderRegister, ((float*)entry->DataSource)[0], ((float*)entry->DataSource)[1], ((float*)entry->DataSource)[2]);
		}
		if (entry->DataSize == 16) {
			Logger::Log("%s %d %d %f %f %f %f", entry->Key, entry->RegisterCount, entry->ShaderRegister, ((float*)entry->DataSource)[0], ((float*)entry->DataSource)[1], ((float*)entry->DataSource)[2], ((float*)entry->DataSource)[3]);
		}

	}
	/*else {
		Logger::Log("%s %d %d %d", entry->Key, entry->RegisterCount, entry->ShaderRegister, entry->DataSize);
	}*/

}


UInt32 (__thiscall* SetupShaderPrograms)(NiShader*, NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32) = (UInt32 (__thiscall*)(NiShader*, NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32))Hooks::SetupShaderPrograms;
UInt32 __fastcall SetupShaderProgramsHook(NiShader* This, UInt32 edx, NiGeometry* Geometry, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* SkinPartition, NiGeometryBufferData* GeometryBufferData, NiPropertyState* PropertyState, NiDynamicEffectState* EffectState, NiTransform* WorldTransform, UInt32 WorldBound) {
	
	D3DXVECTOR4* Toggles = (D3DXVECTOR4*)0x00B46688;
	NiD3DPass* Pass = ((NiD3DShader*)This)->CurrentPass;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;
	UInt32 PassIndex = *(UInt32*)0x00B42E90;
	//if (PassIndex == 390) return false;
//    UInt8* IsLava = (UInt8*)0x00B47844;
//    *IsLava = 1;  Unlock pass 410 instead of 380/409
	if (VertexShader && PixelShader) {
		VertexShader->SetupShader(TheRenderManager->renderState->GetVertexShader());
		PixelShader->SetupShader(TheRenderManager->renderState->GetPixelShader());
        /*This was 1.0. This code is supposed to make the shader render the fog color on objects, however it lack depth, causing a "washed out" effect. 
         Also not all shaders consider this Toggle, so there are only some objects that are rendered that way.
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
	//Temporary fix for SM3 passes to not properly clear the texture sampler 3, the shadow mask. 
	// This mask doesn't seems setted  or resetted, so when a shader bind sampler 3 before (not happen in vanilla)
	// the shadow mask is still setted, and the shader will use it instead of the correct texture.
	// unless the shader doesn't bind the mask at all????
	// Trying to stamp the texture show no texture for sampler 2 and 3
	if (PassIndex == 314 || PassIndex ==  322 || PassIndex == 316 /* TEST*/){
		TheRenderManager->renderState->SetTexture(3, nullptr);
		TheRenderManager->renderState->SetTexture(2, nullptr);
	}
	UInt32 result = (*SetupShaderPrograms)(This, Geometry, SkinInstance, SkinPartition, GeometryBufferData, PropertyState, EffectState, WorldTransform, WorldBound);
	if (PassIndex == 380  || PassIndex == 409 || PassIndex == 410){ //WaterLOD
        //data[2] difuse, data[1] nothing
 //       Logger::Log("Pass %u : %u",  PassIndex, *IsLava);
    //    TheRenderManager->renderState->SetTexture(1, TheRenderManager->CurrentWaterTexture);
    }
    // 381 sky
	if (PassIndex == 390 || PassIndex == 388 || PassIndex == 314 || PassIndex ==  322 || PassIndex == 316){
    	if (Global->OnKeyDown(44)) {
            NiTArray<NiD3DTextureStage*> stages = Pass->Stages;
            for(UInt32 i = 0; i < Pass->Stages.numObjs; i++){
				if(Pass->Stages.data[i] == nullptr || Pass->Stages.data[i]->Texture == nullptr) continue;
                IDirect3DBaseTexture9* text = Pass->Stages.data[i]->Texture->rendererData->dTexture;
				wchar_t num[20] = { 0 };
				wchar_t id[60] = { 0 };
				swprintf(id, 60, L"%hs", Geometry->m_pcName);
				swprintf(num,20, L"%d_%d", PassIndex, i);
				wchar_t buf[150] = L".\\test_";
				wcscat(buf, id);
				wcscat(buf, L"_");
				wcscat(buf, num);
				wcscat(buf, L".jpg");
                D3DXSaveTextureToFile(buf, D3DXIFF_JPG, text, NULL);
            }
		/*	ShadowLightShader* sh = (ShadowLightShader*)This;
			NiD3DShaderConstantMap* constMap = sh->PixelConstantMapSLS2;
			if (constMap) {
				Logger::Log("Pixel constant for shader %s", sh->Name);
				NiTArray<NiD3DShaderConstantMapEntry*>& Entries = constMap->Entries;
				for (UInt32 i = 0; i < Entries.numObjs; i++) {
					NiD3DShaderConstantMapEntry* entry = Entries.data[i];
					LogEntry(entry);
				}
			}
			constMap = sh->VertexConstantMapSLS2;
			if (constMap) {
				Logger::Log("Vertex constant for shader %s", sh->Name);
				NiTArray<NiD3DShaderConstantMapEntry*>& Entries = constMap->Entries;
				for (UInt32 i = 0; i < Entries.numObjs; i++) {
					NiD3DShaderConstantMapEntry* entry = Entries.data[i];
					LogEntry(entry);
				}
			}
			*/
        }
    }
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


/* These 2 function below belong to a game routine used to clean up texture samplers unused by the current pass.
 * This interfere with our setCT when using the renderState properly. 
 * This probably lies in the fact these shaders are rendered after the cleanup, that happen after our setCT.
 * Study it better, in a ideal world we may want to synchronize setCT AFTER the cleanup
 * or to extend the vanilla NiD3DPass to manager our textures and samplers too.
 */
void __declspec(naked) StubRemoveTexturesFromSampler() {
	__asm {
		mov eax , 0
		retn
	}
}

UInt32 kContinueLoc = 0x0077226E;
void __declspec(naked) StubRemoveTextureFromSampler() {
	__asm {
		test edi,edi
		jz loc_continue
		push edi 
		push eax
		call edx
		test edi,edi
	loc_continue:
		jmp [kContinueLoc]
	}
}

/* An alternative version,  if we prevent executing when pTexture is NULL then the bug doesn't occur
  Inverstigate a bit on the more solid version
  Both versions seems to trigger the bug of having canopy shadows on extraneous objects
  when the canopy shadows is enabled
*/
std::vector<void*>* holder1= new std::vector<void*>();
HRESULT __fastcall SetTexturePreventSettingNULL(NiDX9RenderState* state, UInt32 edx, DWORD Sampler, IDirect3DBaseTexture9 *pTexture) {
	void* caller = _ReturnAddress();

	if (pTexture == nullptr){
		if(std::find(holder1->begin(), holder1->end(), caller) == holder1->end()){
			Logger::Log("NiDX9RenderState::SetTexture caller %p", caller);
			holder1->push_back(caller);
		}		
		return  D3D_OK;
	}
	if(state->SourceTextures[Sampler] == pTexture) return  (HRESULT)Sampler;
	state->SourceTextures[Sampler] = pTexture;
	return state->Device->SetTexture(Sampler, pTexture);
}