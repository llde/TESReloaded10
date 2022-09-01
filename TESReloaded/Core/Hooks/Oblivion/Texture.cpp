#include "Texture.h"
/*
static void WaterHeightMap(BSRenderedTexture* WaterHeightMap) {
	
	TheTextureManager->SetWaterHeightMap(WaterHeightMap->RenderedTexture->rendererData->dTexture);
//    TheRenderManager->CurrentWaterTexture = WaterHeightMap->RenderedTexture->rendererData->dTexture;
	
} */
void (__thiscall* WaterSurfacePass)(WaterManager*, NiCamera*) = (void (__thiscall*)(WaterManager*, NiCamera*))Hooks::WaterSurfacePass;
void __fastcall WaterSurfacePassHook(WaterManager* This, UInt32 edx, NiCamera* Camera) {
    
    (*WaterSurfacePass)(This,Camera);
    TheTextureManager->SetWaterHeightMap(This->HeightMap->RenderedTexture->rendererData->dTexture);
    if(This->ReflectionMap) TheTextureManager->SetWaterReflectionMap(This->ReflectionMap->RenderedTexture->rendererData->dTexture);
}
/*
__declspec(naked) void WaterHeightMapHook() {
	__asm {
		call    Hooks::UnkSub7C2420
		push    eax
		call	WaterHeightMap
		pop     eax
		jmp		Jumpers::WaterHeightMap::Return
	}
}*/
