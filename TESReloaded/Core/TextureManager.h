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

	bool					LoadTexture(TextureRecordType Type, const char* Filename);
	void					SetSamplerState(D3DSAMPLERSTATETYPE SamplerType, DWORD Value);

	IDirect3DBaseTexture9*	Texture;
	DWORD					SamplerStates[SamplerStatesMax];
};

typedef std::map<std::string, TextureRecord*> TextureList;

class TextureManager { // Never disposed
public:
	static void				Initialize();

	TextureRecord*			LoadTexture(const char* ShaderSource, D3DXPARAMETER_TYPE ConstantType, LPCSTR ConstantName, UINT RegisterIndex, bool* HasRenderedBuffer, bool* HasDepthBuffer);
	DWORD					GetSamplerValue(UInt32 SamplerType, const char* ParserStart, const char* ParserEnd, char* SamplerValue);

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