#pragma once

static void (__thiscall* Render)(Main*, BSRenderedTexture*, int, int) = (void (__thiscall*)(Main*, BSRenderedTexture*, int, int))Hooks::Render;
static void __fastcall RenderHook(Main* This, UInt32 edx, BSRenderedTexture* RenderedTexture, int Arg2, int Arg3) {
	
	SettingsMainStruct* SettingsMain = &TheSettingManager->SettingsMain;

	TheFrameRateManager->UpdatePerformance();
	TheCameraManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (SettingsMain->Develop.TraceShaders && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None) && Global->OnKeyDown(SettingsMain->Develop.TraceShaders) && DWNode::Get() == NULL) DWNode::Create();
	(*Render)(This, RenderedTexture, Arg2, Arg3);

}

static void (__cdecl* SetupRenderingPass)(UInt32, BSShader*) = (bool (__cdecl*)(UInt32, BSShader*))Hooks::SetupRenderingPass;
static void __cdecl SetupRenderingPassHook(UInt32 PassIndex, BSShader* Shader) {
	
	IDirect3DVertexShader9* CurrentVertexHandle = TheRenderManager->renderState->GetVertexShader();
	IDirect3DPixelShader9* CurrentPixelHandle = TheRenderManager->renderState->GetPixelShader();

	SetupRenderingPass(PassIndex, Shader);

	NiGeometry* Geometry = *(NiGeometry**)(*(void**)0x011F91E0);
	NiD3DPass* Pass = *(NiD3DPass**)0x0126F74C;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;

	if (VertexShader && PixelShader) {
		VertexShader->SetupShader(CurrentVertexHandle);
		PixelShader->SetupShader(CurrentPixelHandle);
		if (DWNode::Get()) {
			char Name[256];
			sprintf(Name, "Pass %i %s, %s (%s %s)", PassIndex, Pointers::Functions::GetPassDescription(PassIndex), Geometry->m_pcName, VertexShader->ShaderName, PixelShader->ShaderName);
			if (VertexShader->ShaderHandle == VertexShader->ShaderHandleBackup) strcat(Name, " - Vertex: vanilla");
			if (PixelShader->ShaderHandle == PixelShader->ShaderHandleBackup) strcat(Name, " - Pixel: vanilla");
			DWNode::AddNode(Name, Geometry->m_parent, Geometry);
		}
	}

}

static void (__thiscall* RenderWorldSceneGraph)(Main*, Sun*, UInt8, UInt8, UInt8) = (void (__thiscall*)(Main*, Sun*, UInt8, UInt8, UInt8))Hooks::RenderWorldSceneGraph;
static void __fastcall RenderWorldSceneGraphHook(Main* This, UInt32 edx, Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame, UInt8 Arg4) {
	
	bool CameraMode = TheSettingManager->SettingsMain.CameraMode.Enabled;

	(*RenderWorldSceneGraph)(This, SkySun, IsFirstPerson, WireFrame, Arg4);
	if (CameraMode || !TheCameraManager->IsFirstPerson()) TheRenderManager->ResolveDepthBuffer();

}

static void (__thiscall* RenderFirstPerson)(Main*, NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*) = (void (__thiscall*)(Main*, NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*))Hooks::RenderFirstPerson;
static void __fastcall RenderFirstPersonHook(Main* This, UInt32 edx, NiDX9Renderer* Renderer, NiGeometry* Geo, Sun* SkySun, BSRenderedTexture* RenderedTexture) {
	
	(*RenderFirstPerson)(This, Renderer, Geo, SkySun, RenderedTexture);
	TheRenderManager->ResolveDepthBuffer();
	TheRenderManager->Clear(NULL, NiRenderer::kClear_ZBUFFER);
	ThisCall(0x00874C10, Global);
	(*RenderFirstPerson)(This, Renderer, Geo, SkySun, RenderedTexture);

}

static void (__thiscall* RenderReflections)(WaterManager*, NiCamera*, ShadowSceneNode*) = (void (__thiscall*)(WaterManager*, NiCamera*, ShadowSceneNode*))Hooks::RenderReflections;
static void __fastcall RenderReflectionsHook(WaterManager* This, UInt32 edx, NiCamera* Camera, ShadowSceneNode* SceneNode) {
	
	D3DXVECTOR4* ShadowData = &TheShaderManager->ShaderConst.Shadow.Data;
	float ShadowDataBackup = ShadowData->x;

	if (DWNode::Get()) DWNode::AddNode("BEGIN REFLECTIONS RENDERING", NULL, NULL);
	ShadowData->x = -1.0f; // Disables the shadows rendering for water reflections (the geo is rendered with the same shaders used in the normal scene!)
	(*RenderReflections)(This, Camera, SceneNode);
	ShadowData->x = ShadowDataBackup;
	if (DWNode::Get()) DWNode::AddNode("END REFLECTIONS RENDERING", NULL, NULL);

}

static void (__thiscall* RenderPipboy)(Main*, NiGeometry*, NiDX9Renderer*) = (void (__thiscall*)(Main*, NiGeometry*, NiDX9Renderer*))Hooks::RenderPipboy;
static void __fastcall RenderPipboyHook(Main* This, UInt32 edx, NiGeometry* Geo, NiDX9Renderer* Renderer) {
	
	WorldSceneGraph->SetCameraFOV(Player->firstPersonFoV);
	(*RenderPipboy)(This, Geo, Renderer);

}

float (__thiscall* GetWaterHeightLOD)(TESWorldSpace*) = (float (__thiscall*)(TESWorldSpace*))Hooks::GetWaterHeightLOD;
float __fastcall GetWaterHeightLODHook(TESWorldSpace* This, UInt32 edx) {
	
	float r = This->waterHeight;

	if (*(void**)This == (void*)0x0103195C) r = Tes->GetWaterHeight(Player);
	return r;

}

static void RenderMainMenuMovie() {

	if (TheSettingManager->SettingsMain.Main.ReplaceIntro && InterfaceManager->IsActive(Menu::MenuType::kMenuType_Main))
		Binker::Render(TheRenderManager->device, MainMenuMovie, TheRenderManager->width, TheRenderManager->height);
	else
		Binker::Close(TheRenderManager->device);

}

static void SetTileShaderAlpha() {
	
	float ViewProj[16];
	NiVector4 TintColor = { 1.0f, 1.0f, 1.0f, 0.0f };

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Main)) {
		TheRenderManager->device->GetVertexShaderConstantF(0, ViewProj, 4);
		if ((int)ViewProj[3] == -1 && (int)ViewProj[7] == 1 && (int)ViewProj[15] == 1) TheRenderManager->device->SetPixelShaderConstantF(0, (const float*)&TintColor, 1);
	}

}

static __declspec(naked) void SetTileShaderConstants() {

	__asm {
		pushad
		call	SetTileShaderAlpha
		popad
		cmp		byte ptr [esi + 0xAC], 0
		jmp		kSetTileShaderConstantsReturn
	}

}

static float MultiBoundWaterHeightFix() {

	return Player->pos.z;

}