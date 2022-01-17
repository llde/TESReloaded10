#pragma once

static void (__cdecl* ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*) = (void (__cdecl*)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*))Hooks::ProcessImageSpaceShaders;
static void __cdecl ProcessImageSpaceShadersHook(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2) {
	
	TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->BackBuffer;
	ProcessImageSpaceShaders(Renderer, RenderedTexture1, RenderedTexture2);
	if (!RenderedTexture2 && TheRenderManager->currentRTGroup) TheShaderManager->RenderEffects(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface);
	if (TheRenderManager->IsSaveGameScreenShot) {
		if (Pointers::Generic::MenuRenderedTexture)
			TheRenderManager->device->StretchRect(Pointers::Generic::MenuRenderedTexture->RenderTargetGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
		else
			TheRenderManager->device->StretchRect(TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
	}

}

static __declspec(naked) void RenderInterfaceHook() {
	
	__asm {
		call	Jumpers::RenderInterface::Method
		pushad
		mov		ecx, TheGameMenuManager
		call	GameMenuManager::Render
		popad
		jmp		Jumpers::RenderInterface::Return
	}

}