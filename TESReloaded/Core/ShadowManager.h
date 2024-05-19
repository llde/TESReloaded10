#pragma once

class ShadowManager { // Never disposed
public:
	static void Initialize();
    
#define ShadowMapsNumber ShadowMapTypeEnum::MapOrtho +1
#define BlurShadowMaps  ShadowMapTypeEnum::MapOrtho
	
	enum ShadowMapTypeEnum {
		MapNear = 0,
		MapMiddle = 1,
		MapFar = 2,
		MapLod = 3,
		MapOrtho = 4,
	};

	enum PlaneEnum {
		PlaneNear	= 0,
		PlaneFar	= 1,
		PlaneLeft	= 2,
		PlaneRight	= 3,
		PlaneTop	= 4,
		PlaneBottom	= 5,
	};
	enum ShadowMapVisibility {
		None = 0x0,
		Near = 0x1,
		Middle = 0x10,
		Far = 0x100,
		Lod = 0x1000,
		Ortho = 0x10000
	};

	struct ShadowMapFeatures {
		float MinRadius;
	};
	void					SetFrustum(ShadowMapTypeEnum ShadowMapType, D3DMATRIX* Matrix);
	bool					InFrustum(ShadowMapTypeEnum ShadowMapType, NiAVObject* Node);
	bool					IsOutAllFrustums(NiNode* node);
	bool					IsVisible(ShadowMapTypeEnum type, UInt32 visibility);
	bool					ExcludeFromAllRadius(NiAVObject* node);
	TESObjectREFR*			GetRef(TESObjectREFR* Ref, ffi::ShadowFormsStruct* Forms);
	void					AccumulateGeometry(NiAVObject* accum);
	void					SelectGeometry(NiGeometry* geo);
	void					RenderInterior(NiAVObject* Object, float MinRadius);
	void					RenderGeometry(NiGeometry* Geo);
	void					Render(NiGeometry* Geo);
	void					RenderNormalPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType);
	void					RenderAlphaPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType);
	void					RenderSkinnedPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType);
	void					RenderSkinnedAlphaPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType);
	void					RenderSpeedTreePass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType);

	void					ClearShadowsMaps();
	void					RenderShadowExteriorMaps(ffi::ShadowsExteriorStruct* ShadowsExteriors, D3DXVECTOR3* At);
	void					RenderShadowCubeMap(NiPointLight** Lights, int LightIndex, ffi::ShadowsInteriorStruct* ShadowsInteriors);
	bool					RenderShadowMaps();
	void					CalculateBlend(NiPointLight** Lights, int LightIndex);
    void                    BlurShadowMap(ShadowMapTypeEnum ShadowMapType);    
	D3DXMATRIX				GetCascadeViewProj(ShadowMapTypeEnum ShadowMapType, ffi::ShadowsExteriorStruct* ShadowsExteriors, D3DXMATRIX View);
	void					GetCascadeDepths();
	static float			lerp(float a, float b, float t);

    ShaderRecordVertex*		ShadowMapVertex;
	ShaderRecordPixel*		ShadowMapPixel;
	D3DVIEWPORT9			ShadowMapViewPort[ShadowMapsNumber];
	D3DXPLANE				ShadowMapFrustum[ShadowMapsNumber][6];
	NiVector4				BillboardRight;
	NiVector4				BillboardUp;
	ShaderRecordVertex*		ShadowCubeMapVertex;
	ShaderRecordPixel*		ShadowCubeMapPixel;
    
	float					ShadowCascadesDepth[3];

    ShaderRecordVertex*		ShadowMapBlurVertex;
	ShaderRecordPixel*		ShadowMapBlurPixel;
    IDirect3DVertexBuffer9* BlurShadowVertex[BlurShadowMaps];
    float                   ShadowMapInverseResolution[ShadowMapsNumber];
	float					ShadowMapRadius[ShadowMapsNumber];
	ShadowMapFeatures		ShadowMapsFeatures[ShadowMapsNumber];
	D3DVIEWPORT9			ShadowCubeMapViewPort;
	NiPointLight*			ShadowCubeMapLights[BlurShadowMaps];
	ShaderRecordVertex*		CurrentVertex;
	ShaderRecordPixel*		CurrentPixel;
	bool					AlphaEnabled;
	bool					WasEnabledExt;
	bool					WasEnabledInt;
	NiRenderedTexture*      BackupCanopyMap;
	NiRenderedTexture*      StubCanopyMap;
	std::vector<std::tuple<NiGeometry*, UInt32>> alphaObjects;
	std::vector<std::tuple<NiGeometry*, UInt32>> speedtreeObjects;
	std::vector<std::tuple<NiGeometry*, UInt32>> normalObjects;
	std::vector<std::tuple<NiGeometry*, UInt32>> skinnedObjects;
	std::vector<std::tuple<NiGeometry*, UInt32>> skinnedAlphaObjects;

};