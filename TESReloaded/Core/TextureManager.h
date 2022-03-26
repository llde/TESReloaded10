#pragma once
#define SamplerStatesMax 12
#define ShadowCubeMapsMax 4

class TextureRecord {
public:
	TextureRecord();
	
	enum TextureRecordType {
		None,
		PlanarBuffer,
		VolumeBuffer,
		CubeBuffer,
		SourceBuffer,
		RenderedBuffer,
		DepthBuffer,
		ShadowMapBufferNear,
		ShadowMapBufferFar,
		OrthoMapBuffer,
		ShadowCubeMapBuffer0,
		ShadowCubeMapBuffer1,
		ShadowCubeMapBuffer2,
		ShadowCubeMapBuffer3,
		WaterHeightMapBuffer,
	};

	bool					LoadTexture(TextureRecordType Type);

	IDirect3DBaseTexture9*	Texture;
	DWORD					SamplerStates[SamplerStatesMax];
	char					Name[80];
};

class TextureList : public std::list<TextureRecord*> {
public:
	
	TextureRecord* find(char* Name) {

		TextureRecord* R = NULL;

		for (TextureList::iterator Iter = this->begin(); Iter != this->end(); ++Iter) {
			if (!strcmp((*Iter)->Name, Name)) {
				R = *Iter;
				break;
			}
		}
		return R;

	}

};

class TextureManager { // Never disposed
public:
	static void				Initialize();

	TextureRecord*			LoadTexture(const char* ShaderSource, D3DXPARAMETER_TYPE ConstantType, LPCSTR ConstantName, UINT RegisterIndex, bool* HasRenderedBuffer, bool* HasDepthBuffer);
	DWORD					GetSamplerStateValue(UInt32 SamplerType, const char* ParserStart, const char* ParserEnd, char* SamplerValue);
	void					SetWaterHeightMap(IDirect3DBaseTexture9* WaterHeightMap);

	IDirect3DTexture9*		SourceTexture;
	IDirect3DSurface9*		SourceSurface;
	IDirect3DTexture9* 		RenderedTexture;
	IDirect3DSurface9*		RenderedSurface;
	IDirect3DTexture9*		DepthTexture;
	IDirect3DSurface9*		DepthSurface;
	IDirect3DTexture9*		ShadowMapTexture[3];
	IDirect3DSurface9*		ShadowMapSurface[3];
	IDirect3DSurface9*		ShadowMapDepthSurface[3];
	IDirect3DCubeTexture9*	ShadowCubeMapTexture[ShadowCubeMapsMax];
	IDirect3DSurface9*		ShadowCubeMapSurface[ShadowCubeMapsMax][6];
	IDirect3DSurface9*		ShadowCubeMapDepthSurface;
	TextureList				Textures;
};