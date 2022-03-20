#pragma once

static void WaterHeightMap(BSRenderedTexture* WaterHeightMap) {
	
	Tes->waterManager->HeightMap = WaterHeightMap;
	TheTextureManager->SetWaterHeightMap(WaterHeightMap->RenderedTexture->rendererData->dTexture);
	
}

static __declspec(naked) void WaterHeightMapHook() {

	__asm {
		pushad
		push    eax
		call	WaterHeightMap
		pop     eax
		popad
		jmp		Jumpers::WaterHeightMap::Return
	}

}