#pragma once

class RenderManager: public RenderManagerBase {
public:
	void				Initialize();
	void				ResolveDepthBuffer();
	void				CreateD3DMatrix(D3DMATRIX* Matrix, NiTransform* Transform);
	void				GetScreenSpaceBoundSize(NiPoint2* BoundSize, NiBound* Bound, float ZeroTolerance = 1e-5f);
	void				GetScreenSpaceBoundSize(NiPoint2* BoundSize, NiBound* Bound, NiCamera* Camera, float ZeroTolerance = 1e-5f);
	void				UpdateSceneCameraData();
	void				SetupSceneCamera();
	void				CheckAndTakeScreenShot(IDirect3DSurface9* RenderTarget);
    float               GetObjectDistance(NiBound* Bound);
	float				GetObjectDistance(NiBound* Bound, NiCamera* Camera);
	bool				IsNode(NiAVObject* node);
	D3DXMATRIX			WorldViewProjMatrix;
	D3DXMATRIX			ViewProjMatrix;
	D3DXMATRIX			InvViewProjMatrix;
	D3DXMATRIX			InvProjMatrix;
	D3DXMATRIX			InvViewMatrix;
	D3DXMATRIX			ViewMatrix;
	D3DXVECTOR4			CameraData;
	D3DXVECTOR4			FOVData;
	D3DXVECTOR4			CameraForward;
	D3DXVECTOR4			CameraPosition;
	IDirect3DSurface9*	BackBuffer;
	D3DXVECTOR4			DepthConstants;
	RECT				SaveGameScreenShotRECT;
	bool				IsSaveGameScreenShot;
	bool				RESZ;
	UInt8				MaxRenderTargets;
};

class DWNode : public NiNode {
public:
	static void		Create();
	static DWNode*	Get();
	static void		AddNode(const char* Name, NiAVObject* Child0, NiAVObject* Child1);
};

constexpr static GUID IID_ID3D9VkInteropDevice{ 0x2eaa4b89, 0x0107, 0x4bdb, { 0x87, 0xf7, 0x0f, 0x54, 0x1c, 0x49, 0x3c, 0xe0 } };

interface ID3D9VkInteropDevice : public IUnknown {
	virtual void STDMETHODCALLTYPE GetVulkanHandles(
		void* pInstance,
		void* pPhysDevice,
		void* pDevice
	) = 0;
};