#pragma once

static void WaterHeightMap(BSRenderedTexture* WaterHeightMap) {
	
	TheTextureManager->SetWaterHeightMap(WaterHeightMap->RenderedTexture->rendererData->dTexture);
	
}

static __declspec(naked) void WaterHeightMapHook() {
	__asm {
		call    Hooks::UnkSub7C2420
		push    eax
		call	WaterHeightMap
		pop     eax
		jmp		Jumpers::WaterHeightMap::Return
	}
}
