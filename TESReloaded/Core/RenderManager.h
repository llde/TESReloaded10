#pragma once

class RenderManager: public RenderManagerBase {
public:
	void				Initialize();
	void				ResolveDepthBuffer();
	void				CreateD3DMatrix(D3DMATRIX* Matrix, NiTransform* Transform);
	void				GetScreenSpaceBoundSize(NiPoint2* BoundSize, NiBound* Bound, float ZeroTolerance = 1e-5f);
	void				UpdateSceneCameraData();
	void				SetupSceneCamera();
	void				CheckAndTakeScreenShot(IDirect3DSurface9* RenderTarget);

	D3DXMATRIX			WorldViewProjMatrix;
	D3DXMATRIX			ViewProjMatrix;
	D3DXMATRIX			InvViewProjMatrix;
	D3DXMATRIX			InvProjMatrix;
	D3DXVECTOR4			CameraForward;
	D3DXVECTOR4			CameraPosition;
	IDirect3DSurface9*	BackBuffer;
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
