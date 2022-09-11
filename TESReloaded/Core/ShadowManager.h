#pragma once

class ShadowManager : public ShadowManagerBase { // Never disposed
public:
	static void Initialize();

	enum PlaneEnum {
		PlaneNear	= 0,
		PlaneFar	= 1,
		PlaneLeft	= 2,
		PlaneRight	= 3,
		PlaneTop	= 4,
		PlaneBottom	= 5,
	};

	void					SetFrustum(ShadowMapTypeEnum ShadowMapType, D3DMATRIX* Matrix);
	bool					InFrustum(ShadowMapTypeEnum ShadowMapType, NiNode* Node);
	TESObjectREFR*			GetRef(TESObjectREFR* Ref, SettingsShadowStruct::FormsStruct* Forms, SettingsShadowStruct::ExcludedFormsList* ExcludedForms);
	void					RenderExterior(NiAVObject* Object, float MinRadius);
	void					RenderInterior(NiAVObject* Object, float MinRadius);
	void					RenderTerrain(NiAVObject* Object, ShadowMapTypeEnum ShadowMapType);
	void					RenderGeometry(NiGeometry* Geo);
	void					Render(NiGeometry* Geo);
	void					RenderShadowMap(ShadowMapTypeEnum ShadowMapType, SettingsShadowStruct::ExteriorsStruct* ShadowsExteriors, D3DXVECTOR3* At, D3DXVECTOR4* SunDir);
	void					RenderShadowCubeMap(NiPointLight** Lights, int LightIndex, SettingsShadowStruct::InteriorsStruct* ShadowsInteriors);
	void					RenderShadowMaps();
	void					CalculateBlend(NiPointLight** Lights, int LightIndex);

	ShaderRecordVertex*		ShadowMapVertex;
	ShaderRecordPixel*		ShadowMapPixel;
	D3DVIEWPORT9			ShadowMapViewPort[3];
	D3DXPLANE				ShadowMapFrustum[3][6];
	NiVector4				BillboardRight;
	NiVector4				BillboardUp;
	ShaderRecordVertex*		ShadowCubeMapVertex;
	ShaderRecordPixel*		ShadowCubeMapPixel;
	D3DVIEWPORT9			ShadowCubeMapViewPort;
	NiPointLight*			ShadowCubeMapLights[4];
	ShaderRecordVertex*		CurrentVertex;
	ShaderRecordPixel*		CurrentPixel;
	D3DXVECTOR3				LookAtPosition;
	bool					AlphaEnabled;
};