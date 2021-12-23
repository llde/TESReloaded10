#pragma once

#if defined(OBLIVION)
#define kDetectorWindowNode 0x00B42CF4
#elif defined(SKYRIM)
#define kDetectorWindowNode 0x00000000
#endif

class NiD3DVertexShaderEx : public NiD3DVertexShader {
public:
	void					SetupShader(IDirect3DVertexShader9* CurrentVertexHandle);
	void					DisposeShader();

	ShaderRecordVertex*		ShaderProg;
	ShaderRecordVertex*		ShaderProgE;
	ShaderRecordVertex*		ShaderProgI;
	IDirect3DVertexShader9*	ShaderHandleBackup;
	char					ShaderName[40];
};

class NiD3DPixelShaderEx : public NiD3DPixelShader {
public:
	void					SetupShader(IDirect3DPixelShader9* CurrentPixelHandle);
	void					DisposeShader();

	ShaderRecordPixel*		ShaderProg;
	ShaderRecordPixel*		ShaderProgE;
	ShaderRecordPixel*		ShaderProgI;
	IDirect3DPixelShader9*	ShaderHandleBackup;
	char					ShaderName[40];
};

class RenderManager: public NiDX9Renderer {
public:
	void				Initialize();
	void				ResolveDepthBuffer();
	void				CreateD3DMatrix(D3DMATRIX* Matrix, NiTransform* Transform);
	void				GetScreenSpaceBoundSize(NiPoint2* BoundSize, NiBound* Bound, float ZeroTolerance = 1e-5f);
	void				UpdateSceneCameraData();
	void				SetupSceneCamera();

	D3DXMATRIX			WorldViewProjMatrix;
	D3DXMATRIX			ViewProjMatrix;
	D3DXMATRIX			InvViewProjMatrix;
	D3DXVECTOR4			CameraForward;
	D3DXVECTOR4			CameraPosition;
	IDirect3DSurface9*	BackBuffer;
	IDirect3DSurface9*	DepthSurface;
	IDirect3DTexture9*	DepthTexture;
	IDirect3DTexture9*	DepthTextureINTZ;
	RECT				SaveGameScreenShotRECT;
	bool				IsSaveGameScreenShot;
	bool				RESZ;
};

class DWNode : public NiNode {
public:
	static void		Create();
	static DWNode*	Get();
	static void		AddNode(char* Name, NiAVObject* Child0, NiAVObject* Child1);
};