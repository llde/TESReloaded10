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

	struct ShadowMapFeatures {
		float MinRadius;
	};

	void					SetFrustum(ShadowMapTypeEnum ShadowMapType, D3DMATRIX* Matrix);
	bool					InFrustum(ShadowMapTypeEnum ShadowMapType, NiNode* Node);
	TESObjectREFR*			GetRef(TESObjectREFR* Ref, ffi::ShadowFormsStruct* Forms);
	void					RenderExterior(NiAVObject* Object, float MinRadius);
	void					RenderInterior(NiAVObject* Object, float MinRadius);
	void					RenderTerrain(NiAVObject* Object, ShadowMapTypeEnum ShadowMapType);
	void					RenderLod(NiAVObject* Object, ShadowMapTypeEnum ShadowMapType);
	void					RenderGeometry(NiGeometry* Geo);
	void					Render(NiGeometry* Geo);
	void					RenderShadowMap(ShadowMapTypeEnum ShadowMapType, ffi::ShadowsExteriorStruct* ShadowsExteriors, D3DXVECTOR3* At, D3DXVECTOR4* SunDir);
	void					RenderShadowCubeMap(NiPointLight** Lights, int LightIndex, ffi::ShadowsInteriorStruct* ShadowsInteriors);
	void					RenderShadowMaps();
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
};