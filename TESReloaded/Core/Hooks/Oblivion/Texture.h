#pragma once

static void WaterHeightMap(BSRenderedTexture* WaterHeightMap) {
	
	TextureList::iterator t = TheTextureManager->Textures.find(WordWaterHeightMapBuffer);

	Tes->waterManager->HeightMap = WaterHeightMap;
	if (t != TheTextureManager->Textures.end()) t->second->Texture = WaterHeightMap->RenderedTexture->rendererData->dTexture;
	
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