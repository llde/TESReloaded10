#pragma once
#define SamplerStatesMax 12
#define WordSourceBuffer "TESR_SourceBuffer"
#define WordRenderedBuffer "TESR_RenderedBuffer"
#define WordDepthBuffer "TESR_DepthBuffer"
#define WordShadowMapBufferNear "TESR_ShadowMapBufferNear"
#define WordShadowMapBufferFar "TESR_ShadowMapBufferFar"
#define WordOrthoMapBuffer "TESR_OrthoMapBuffer"
#define WordShadowCubeMapBuffer0 "TESR_ShadowCubeMapBuffer0"
#define WordShadowCubeMapBuffer1 "TESR_ShadowCubeMapBuffer1"
#define WordShadowCubeMapBuffer2 "TESR_ShadowCubeMapBuffer2"
#define WordShadowCubeMapBuffer3 "TESR_ShadowCubeMapBuffer3"
#define WordWaterHeightMapBuffer "TESR_WaterHeightMapBuffer"

enum TextureRecordType {
	TextureRecordType_None,
	TextureRecordType_PlanarBuffer,
	TextureRecordType_VolumeBuffer,
	TextureRecordType_CubeBuffer,
	TextureRecordType_SourceBuffer,
	TextureRecordType_RenderedBuffer,
	TextureRecordType_DepthBuffer,
	TextureRecordType_ShadowMapBufferNear,
	TextureRecordType_ShadowMapBufferFar,
	TextureRecordType_OrthoMapBuffer,
	TextureRecordType_ShadowCubeMapBuffer0,
	TextureRecordType_ShadowCubeMapBuffer1,
	TextureRecordType_ShadowCubeMapBuffer2,
	TextureRecordType_ShadowCubeMapBuffer3,
	TextureRecordType_WaterHeightMapBuffer,
	TextureRecordType_Max,
};

class TextureRecord {
public:
	TextureRecord();

	bool					LoadTexture(TextureRecordType Type, const char* Filename);
	void					SetSamplerState(D3DSAMPLERSTATETYPE SamplerType, DWORD Value);

	IDirect3DBaseTexture9*	Texture;
	DWORD					SamplerStates[SamplerStatesMax];
};

typedef std::map<std::string, TextureRecord*> TextureList;

class TextureManager { // Never disposed
public:
	TextureManager();

	TextureRecord*			LoadTexture(const char* ShaderSource, UInt32 RegisterIndex);
	
	TextureList				Textures;
};

void CreateTextureHook();