#pragma once
/*
static void WaterHeightMap(BSRenderedTexture* WaterHeightMap) {
	
	TheTextureManager->SetWaterHeightMap(WaterHeightMap->RenderedTexture->rendererData->dTexture);
//    TheRenderManager->CurrentWaterTexture = WaterHeightMap->RenderedTexture->rendererData->dTexture;
	
} */
static void (__thiscall* WaterSurfacePass)(WaterManager*, NiCamera*) = (void (__thiscall*)(WaterManager*, NiCamera*))Hooks::WaterSurfacePass;
static void __fastcall WaterSurfacePassHook(WaterManager* This, UInt32 edx, NiCamera* Camera) {
    
    (*WaterSurfacePass)(This,Camera);
    TheTextureManager->SetWaterHeightMap(This->HeightMap->RenderedTexture->rendererData->dTexture);
}
/*
static __declspec(naked) void WaterHeightMapHook() {
	__asm {
		call    Hooks::UnkSub7C2420
		push    eax
		call	WaterHeightMap
		pop     eax
		jmp		Jumpers::WaterHeightMap::Return
	}
}*/
