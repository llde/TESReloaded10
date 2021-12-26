#pragma once

static void (__thiscall* Render)(Main*, BSRenderedTexture*, int, int) = (void (__thiscall*)(Main*, BSRenderedTexture*, int, int))Hooks::Render;
static void __fastcall RenderHook(Main* This, UInt32 edx, BSRenderedTexture* RenderedTexture, int Arg2, int Arg3) {
	
	SettingsMainStruct* SettingsMain = &TheSettingManager->SettingsMain;

	TheCameraManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (SettingsMain->Develop.TraceShaders && InterfaceManager->IsActive(Menu::MenuType::kMenuType_None) && TheKeyboardManager->OnKeyDown(SettingsMain->Develop.TraceShaders)) Logger::Log("START FRAME LOG");
	(*Render)(This, RenderedTexture, Arg2, Arg3);

}

static bool (__cdecl* SetupRenderingPass)(UInt32, BSShader*) = (bool (__cdecl*)(UInt32, BSShader*))Hooks::SetupRenderingPass;
static bool __cdecl SetupRenderingPassHook(UInt32 PassIndex, BSShader* Shader) {
	
	bool r = SetupRenderingPass(PassIndex, Shader);

	NiD3DVertexShaderEx* VertexShader = *(NiD3DVertexShaderEx**)0x01BABFB4;
	NiD3DPixelShaderEx* PixelShader = *(NiD3DPixelShaderEx**)0x01BABFB0;

	if (VertexShader && PixelShader) {
		if (VertexShader->ShaderProg) VertexShader->ShaderProg->SetCT();
		if (PixelShader->ShaderProg) PixelShader->ShaderProg->SetCT();
	}
	return r;

}

static void (__thiscall* RenderWorldSceneGraph)(Main*, Sun*, UInt8, UInt8) = (void (__thiscall*)(Main*, Sun*, UInt8, UInt8))Hooks::RenderWorldSceneGraph;
static void __fastcall RenderWorldSceneGraphHook(Main* This, UInt32 edx, Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame) {
	
	bool CameraMode = TheSettingManager->SettingsMain.CameraMode.Enabled;

	(*RenderWorldSceneGraph)(This, SkySun, IsFirstPerson, WireFrame);
	if (CameraMode || Player->IsThirdPersonView(CameraMode, TheCameraManager->FirstPersonView)) TheRenderManager->ResolveDepthBuffer();

}

static void (__thiscall* RenderFirstPerson)(Main*, NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8) = (void (__thiscall*)(Main*, NiDX9Renderer*, NiGeometry*, Sun*, BSRenderedTexture*, UInt8))Hooks::RenderFirstPerson;
static void __fastcall RenderFirstPersonHook(Main* This, UInt32 edx, NiDX9Renderer* Renderer, NiGeometry* Geo, Sun* SkySun, BSRenderedTexture* RenderedTexture, UInt8 IsMultiSample) {
	
	(RenderFirstPerson)(This, Renderer, Geo, SkySun, RenderedTexture, IsMultiSample);
	TheRenderManager->ResolveDepthBuffer();
	TheRenderManager->Clear(NULL, NiRenderer::kClear_ZBUFFER);
	ThisCall(0x00697E50, Global);
	(*RenderFirstPerson)(This, Renderer, Geo, SkySun, RenderedTexture, IsMultiSample);

}

static __declspec(naked) void RenderingGeometryHook() {

	__asm {
		mov     ebx, [esi]
		mov     ebp, [esi + 8]
		mov     Geometry, ebp
		jmp		kRenderingGeometryReturn
	}

}

static void SetShadowDistance(float* Distance, UInt32 Pass) {

	if (Pass == 0) *Distance /= TheSettingManager->SettingsMain.ShadowMode.NearQuality;

}

static __declspec(naked) void SetShadowDistanceHook() {
	
	__asm {
		faddp   st(1), st
		fstp	dword ptr [esp + 0x4C]
		lea		ecx, [esp + 0x4C]
		mov		edx, [esp + 0x74]
		pushad
		pushfd
		push	edx
		push	ecx
		call	SetShadowDistance
		add		esp, 8
		popfd
		popad
		jmp		kSetShadowDistanceReturn
	}
}

static __declspec(naked) void SetShadowDistanceShaderHook() {
	
	__asm {
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