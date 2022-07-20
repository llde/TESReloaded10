#pragma once

class OcclusionManager { // Never disposed
public:
	static void Initialize();

	bool					InFrustum(NiNode* Node);
	TESObjectREFR*			GetRef(TESObjectREFR* Ref);
	void					RenderStatic(NiAVObject* Object, float MinBoundSize, float MaxBoundSize, bool PerformOcclusion);
	void					RenderImmediate(NiAVObject* Object, bool PerformOcclusion);
	void					RenderTerrain(NiAVObject* Object);
	void					RenderWater(NiAVObject* Object);
	void					Render(NiGeometry* Geo);
	void					ManageDistantStatic();
	void					ManageDistantStatic(NiAVObject* Object, float MaxBoundSize);
	void					RenderDistantStatic(NiAVObject* Object);
	void					RenderOcclusionMap(SettingsMainStruct::OcclusionCullingStruct* OcclusionCulling);
	void					PerformOcclusionCulling();
	
	ShaderRecordVertex*		OcclusionMapVertex;
	ShaderRecordPixel*		OcclusionMapPixel;
	IDirect3DQuery9*		OcclusionQuery;
	IDirect3DTexture9*		OcclusionMapTexture;
	IDirect3DSurface9*		OcclusionMapSurface;
	IDirect3DSurface9*		OcclusionMapDepthSurface;
	D3DVIEWPORT9			OcclusionMapViewPort;
	IDirect3DTexture9*		WaterTexture;
	bool					WaterOccluded;
};