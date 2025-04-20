#include "ShadowManager.h"
/*
* Initializes the Shadow Manager by grabbing the relevant settings and shaders, and setting up map sizes.
*/
void ShadowManager::Initialize() {
	
	Logger::Log("Starting the shadows manager...");
	TheShadowManager = new ShadowManager();

	// initializes the settings
	ffi::ShadowsExteriorStruct* ShadowsExteriors = &TheSettingManager->Config->ShadowsExterior;
	ffi::ShadowsInteriorStruct* ShadowsInteriors = &TheSettingManager->Config->ShadowsInterior;
	UINT ShadowMapSize = ShadowsExteriors->ShadowMapResolution;
	UINT ShadowCubeMapSize = ShadowsInteriors->ShadowCubeMapResolution;
	TheShadowManager->GetCascadeDepths();
	TheShadowManager->ShadowMapRadius[MapOrtho] = ShadowMapSize;

	// load the shaders
	TheShadowManager->ShadowMapVertex = (ShaderRecordVertex*)ShaderRecord::LoadShader("ShadowMap.vso", NULL);
	TheShadowManager->ShadowMapPixel = (ShaderRecordPixel*)ShaderRecord::LoadShader("ShadowMap.pso", NULL);
	TheShadowManager->ShadowCubeMapVertex = (ShaderRecordVertex*)ShaderRecord::LoadShader("ShadowCubeMap.vso", NULL);
	TheShadowManager->ShadowCubeMapPixel = (ShaderRecordPixel*)ShaderRecord::LoadShader("ShadowCubeMap.pso", NULL);

    TheShadowManager->ShadowMapBlurVertex = (ShaderRecordVertex*) ShaderRecord::LoadShader("ShadowMapBlur.vso", NULL);
    TheShadowManager->ShadowMapBlurPixel = (ShaderRecordPixel*) ShaderRecord::LoadShader("ShadowMapBlur.pso", NULL);

    if (TheShadowManager->ShadowMapVertex == nullptr || TheShadowManager->ShadowMapPixel == nullptr  || TheShadowManager->ShadowMapBlurVertex  == nullptr
        || TheShadowManager->ShadowCubeMapVertex == nullptr || TheShadowManager->ShadowCubeMapPixel == nullptr || TheShadowManager->ShadowMapBlurPixel  == nullptr ){
        Logger::Log("[ERROR]: Could not load one or more of the ShadowMap generation shaders. Reinstall the mod.");
    }

	// initialize the frame vertices for future shadow blurring
	for (int i = 0; i <= MapOrtho; i++) {
		float multiple = i == MapLod ? 2.0f : 1.0f; // double the size of lod map only
		ShadowMapSize = ShadowsExteriors->ShadowMapResolution * multiple;

		if (i != MapOrtho) TheShaderManager->CreateFrameVertex(ShadowMapSize, ShadowMapSize, &TheShadowManager->BlurShadowVertex[i]);
		TheShadowManager->ShadowMapViewPort[i] = { 0, 0, ShadowMapSize, ShadowMapSize, 0.0f, 1.0f };
        TheShadowManager->ShadowMapInverseResolution[i] = 1.0f / (float) ShadowMapSize;
	}
	TheShadowManager->ShadowCubeMapViewPort = { 0, 0, ShadowCubeMapSize, ShadowCubeMapSize, 0.0f, 1.0f };
	memset(TheShadowManager->ShadowCubeMapLights, NULL, sizeof(ShadowCubeMapLights));
}

/*
* Calculates the radius for each shadow map
*/
void ShadowManager::GetCascadeDepths() {
	ffi::ShadowsExteriorStruct* ShadowsExteriors = &TheSettingManager->Config->ShadowsExterior;
	float camFar = ShadowsExteriors->ShadowMapRadius;
	float logFactor = 0.9f;
	float camNear = 10.0f;
	int cascadeCount = 4;
	float cascadeNum = 0.0f;

	for (int i = 0; i < cascadeCount; i++) {
		// formula for cascade ratios adapted from https://www.asawicki.info/news_1283_cascaded_shadow_mapping
		cascadeNum += 1.0f;
		ShadowMapRadius[i] = lerp(
			camNear + (cascadeNum / cascadeCount) * (camFar - camNear),
			camNear * powf(camFar / camNear, cascadeNum / cascadeCount),
			logFactor);

		// filtering objects occupying less than 10 pixels in the shadow map
		ShadowMapsFeatures[i].MinRadius = 10.0f * ShadowMapRadius[i] / ShadowsExteriors->ShadowMapResolution;
	}
	ShadowMapRadius[cascadeCount] = camFar;

	// Store Shadow map sizes in Constants to pass to the Shaders
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.x = ShadowMapRadius[MapNear];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.y = ShadowMapRadius[MapMiddle];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.z = ShadowMapRadius[MapFar];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.w = ShadowMapRadius[MapLod];
}

/**
* Generates the Frustrum planes from a matrix
*/
void ShadowManager::SetFrustum(ShadowMapTypeEnum ShadowMapType, D3DMATRIX* Matrix) {

	ShadowMapFrustum[ShadowMapType][PlaneNear].a = Matrix->_13;
	ShadowMapFrustum[ShadowMapType][PlaneNear].b = Matrix->_23;
	ShadowMapFrustum[ShadowMapType][PlaneNear].c = Matrix->_33;
	ShadowMapFrustum[ShadowMapType][PlaneNear].d = Matrix->_43;
	ShadowMapFrustum[ShadowMapType][PlaneFar].a = Matrix->_14 - Matrix->_13;
	ShadowMapFrustum[ShadowMapType][PlaneFar].b = Matrix->_24 - Matrix->_23;
	ShadowMapFrustum[ShadowMapType][PlaneFar].c = Matrix->_34 - Matrix->_33;
	ShadowMapFrustum[ShadowMapType][PlaneFar].d = Matrix->_44 - Matrix->_43;
	ShadowMapFrustum[ShadowMapType][PlaneLeft].a = Matrix->_14 + Matrix->_11;
	ShadowMapFrustum[ShadowMapType][PlaneLeft].b = Matrix->_24 + Matrix->_21;
	ShadowMapFrustum[ShadowMapType][PlaneLeft].c = Matrix->_34 + Matrix->_31;
	ShadowMapFrustum[ShadowMapType][PlaneLeft].d = Matrix->_44 + Matrix->_41;
	ShadowMapFrustum[ShadowMapType][PlaneRight].a = Matrix->_14 - Matrix->_11;
	ShadowMapFrustum[ShadowMapType][PlaneRight].b = Matrix->_24 - Matrix->_21;
	ShadowMapFrustum[ShadowMapType][PlaneRight].c = Matrix->_34 - Matrix->_31;
	ShadowMapFrustum[ShadowMapType][PlaneRight].d = Matrix->_44 - Matrix->_41;
	ShadowMapFrustum[ShadowMapType][PlaneTop].a = Matrix->_14 - Matrix->_12;
	ShadowMapFrustum[ShadowMapType][PlaneTop].b = Matrix->_24 - Matrix->_22;
	ShadowMapFrustum[ShadowMapType][PlaneTop].c = Matrix->_34 - Matrix->_32;
	ShadowMapFrustum[ShadowMapType][PlaneTop].d = Matrix->_44 - Matrix->_42;
	ShadowMapFrustum[ShadowMapType][PlaneBottom].a = Matrix->_14 + Matrix->_12;
	ShadowMapFrustum[ShadowMapType][PlaneBottom].b = Matrix->_24 + Matrix->_22;
	ShadowMapFrustum[ShadowMapType][PlaneBottom].c = Matrix->_34 + Matrix->_32;
	ShadowMapFrustum[ShadowMapType][PlaneBottom].d = Matrix->_44 + Matrix->_42;
	for (int i = 0; i < 6; ++i) {
		D3DXPLANE Plane(ShadowMapFrustum[ShadowMapType][i]);
		D3DXPlaneNormalize(&ShadowMapFrustum[ShadowMapType][i], &Plane);
	}

}

/*
* Checks wether the given node is in the frustrum using its radius for the current type of Shadow map.
*/
bool ShadowManager::InFrustum(ShadowMapTypeEnum ShadowMapType, NiAVObject* Node) {
	float Distance = 0.0f;
	bool R = false;
	NiBound* Bound = Node->GetWorldBound();

	if (Bound) {
		D3DXVECTOR3 Position = { Bound->Center.x - TheRenderManager->CameraPosition.x, Bound->Center.y - TheRenderManager->CameraPosition.y, Bound->Center.z - TheRenderManager->CameraPosition.z };
		
		R = true;
		for (int i = 0; i < 6; ++i) {
			Distance = D3DXPlaneDotCoord(&ShadowMapFrustum[ShadowMapType][i], &Position);
			if (Distance <= -Bound->Radius) {
				R = false;
				break;
			}
		}

		//if (ShadowMapType > MapNear && ShadowMapType < MapOrtho && R) { // Ensures to not be fully in the near frustum
		//	for (int i = 0; i < 6; ++i) {
		//		Distance = D3DXPlaneDotCoord(&ShadowMapFrustum[ShadowMapType - 1][i], &Position);
		//		if (Distance <= -Bound->Radius || std::fabs(Distance) < Bound->Radius) {
		//			R = false;
		//			break;
		//		}
		//	}
		//	R = !R;
		//}
	}
	return R;

}
/*
* Return true if the NiNode is outsidethe frustum of all shadowmaps
*/
bool ShadowManager::IsOutAllFrustums(NiNode* node)
{
	return !InFrustum(ShadowMapTypeEnum::MapLod,node) && !InFrustum(ShadowMapTypeEnum::MapOrtho, node);
}

bool ShadowManager::ExcludeFromAllRadius(NiAVObject* node)
{
	return  node->GetWorldBoundRadius() <  this->ShadowMapRadius[ShadowMapTypeEnum::MapNear];
}

/*
* Returns the given object ref if it passes the test for excluded form types, otherwise returns NULL.
*/
TESObjectREFR* ShadowManager::GetRef(TESObjectREFR* Ref, ffi::ShadowFormsStruct* Forms) {
	
	TESObjectREFR* R = NULL;

	if (Ref && Ref->GetNode()) {
		TESForm* Form = Ref->baseForm;
		ExtraRefractionProperty* RefractionExtraProperty = (ExtraRefractionProperty*)Ref->extraDataList.GetExtraData(BSExtraData::ExtraDataType::kExtraData_RefractionProperty);
		float Refraction = RefractionExtraProperty ? (1 - RefractionExtraProperty->refractionAmount) : 0.0f;

		if (!(Ref->flags & TESForm::FormFlags::kFormFlags_NotCastShadows) && Refraction <= 0.5) {
			UInt8 TypeID = Form->formType;
			if ((TypeID == TESForm::FormType::kFormType_Activator && Forms->Activators) ||
				(TypeID == TESForm::FormType::kFormType_Apparatus && Forms->Apparatus) ||
				(TypeID == TESForm::FormType::kFormType_Book && Forms->Books) ||
				(TypeID == TESForm::FormType::kFormType_Container && Forms->Containers) ||
				(TypeID == TESForm::FormType::kFormType_Door && Forms->Doors) ||
				(TypeID == TESForm::FormType::kFormType_Misc && Forms->Misc) ||
				(TypeID >= TESForm::FormType::kFormType_Stat && TypeID <= TESForm::FormType::kFormType_MoveableStatic && Forms->Statics) ||
				(TypeID == TESForm::FormType::kFormType_Tree && Forms->Trees) ||
				(TypeID == TESForm::FormType::kFormType_Furniture && Forms->Furniture) ||
                (TypeID == TESForm::FormType::kFormType_Land && Forms->Terrain) ||
				(TypeID >= TESForm::FormType::kFormType_NPC && TypeID <= TESForm::FormType::kFormType_LeveledCreature && Forms->Actors))
				R = Ref;
		}
	}
	return R;

}

void ShadowManager::SelectGeometry(NiGeometry* Geo, bool IsFaceGen) {
	if (!Geo->shader  || !Geo->shader->ShaderDeclaration) return;

	UInt32 visibility = ShadowMapVisibility::None;
	if (InFrustum(ShadowMapTypeEnum::MapNear, Geo)) visibility = ShadowMapVisibility::Near;
	else if (InFrustum(ShadowMapTypeEnum::MapMiddle, Geo)) visibility = ShadowMapVisibility::Middle;
	else if (InFrustum(ShadowMapTypeEnum::MapFar, Geo)) visibility = ShadowMapVisibility::Far;
	else if (InFrustum(ShadowMapTypeEnum::MapLod, Geo)) visibility = ShadowMapVisibility::Lod;
	if (InFrustum(ShadowMapTypeEnum::MapOrtho, Geo)) visibility |= ShadowMapVisibility::Ortho;
	if(visibility == ShadowMapVisibility::None) return;
	visibility |= ShadowMapVisibility::FaceGenQuirk;

	BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
	bool haveLightingProperty = ShaderProperty && ShaderProperty->IsLightingProperty();
	NiTexture* materialText = nullptr;
	if (haveLightingProperty) { /*Leaves don't have a shade property or is not a LightingProperty*/
		BSShaderPPLightingProperty* lightProperty = (BSShaderPPLightingProperty*)ShaderProperty;
		materialText = lightProperty->textures[0]  ? *lightProperty->textures[0] : nullptr;
		/*Oblivion: Only seen 0.0 or 0.208. IS the structure actually corrrect?*/
		if (lightProperty->IsRefractive()) return; //Configure,also check for actors, they are skinned
	}

	bool alphaObject = false;
	if (AlphaEnabled) {
		NiAlphaProperty* AProp = (NiAlphaProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Alpha);
		if (AProp->flags & NiAlphaProperty::AlphaFlags::ALPHA_BLEND_MASK || AProp->flags & NiAlphaProperty::AlphaFlags::TEST_ENABLE_MASK) alphaObject = true;
	}
	if(Geo->skinInstance && !Geo->geomData->BuffData  && Geo->skinInstance->SkinPartition->Partitions[0].BuffData) {
		if (!materialText) return;
		if (alphaObject) skinnedAlphaObjects.push_back(std::make_tuple(Geo, visibility));
		else skinnedObjects.push_back(std::make_tuple(Geo, visibility));
		return;
	}
	else if(Geo->skinInstance && !Geo->geomData->BuffData){
//		Logger::Log("Skinned but no partition: %s   %s", Geo->m_pcName, Geo->m_parent ? Geo->m_parent->m_pcName : "<No parent>");
		return;
	}
	if(Geo->geomData->BuffData){
		if (Geo->m_parent->m_pcName && !memcmp(Geo->m_parent->m_pcName, "Leaves", 6)) speedtreeObjects.push_back(std::make_tuple(Geo, visibility));
		else if (alphaObject  && materialText) alphaObjects.push_back(std::make_tuple(Geo, visibility));
		else normalObjects.push_back(std::make_tuple(Geo, visibility));
	}
}

void ShadowManager::AccumulateGeometry(NiAVObject* accum, bool IsFaceGenNode){
	if (accum) {
		if (!(accum->m_flags & NiAVObject::kFlag_AppCulled)) {
			void* VFT = *(void**)accum;
			if (TheRenderManager->IsNode(accum) || VFT == Pointers::VirtualTables::BSFaceGenNiNode)  {
				if (VFT == Pointers::VirtualTables::BSFadeNode && ((BSFadeNode*)accum)->FadeAlpha < 0.75f) return;
				NiNode* Node = (NiNode*)accum;
				if (Node) {
					for (int i = 0; i < Node->m_children.numObjs; i++) {
						AccumulateGeometry(Node->m_children.data[i], (VFT == Pointers::VirtualTables::BSFaceGenNiNode) || (IsFaceGenNode == true) ? true : false);
					}
				}
			}
			else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
				SelectGeometry((NiGeometry*)accum, IsFaceGenNode);

			}
			else if (VFT != Pointers::VirtualTables::NiPointLight /*TODO attenuaton map?Test for the affecedNode list*/ && VFT != Pointers::VirtualTables::NiParticleSystem	)
			{
				Logger::Log("Unknown %0X", VFT);
			}
		}
	}
}

void ShadowManager::RenderInterior(NiAVObject* Object, float MinRadius) {
	
	if (Object) {
		float Radius = Object->GetWorldBoundRadius();
		if (!(Object->m_flags & NiAVObject::kFlag_AppCulled) && Radius >= MinRadius) {
			void* VFT = *(void**)Object;
			if (TheRenderManager->IsNode(Object)) {
				NiNode* Node = (NiNode*)Object;
				for (int i = 0; i < Node->m_children.numObjs; i++) {
					RenderInterior(Node->m_children.data[i], MinRadius);
				}
			}
			else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
				RenderGeometry((NiGeometry*)Object);
			}
		}
	}

}

void ShadowManager::RenderGeometry(NiGeometry* Geo) {

	NiGeometryBufferData* GeoData = NULL;

	if (Geo->shader) {
		GeoData = Geo->geomData->BuffData;
		if (GeoData) {
			Render(Geo);
		}
		else if (Geo->skinInstance && Geo->skinInstance->SkinPartition && Geo->skinInstance->SkinPartition->Partitions) {
			GeoData = Geo->skinInstance->SkinPartition->Partitions[0].BuffData;
			if (GeoData) Render(Geo);
		}
	}

}
void ShadowManager::Render(NiGeometry* Geo) {
	
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	int StartIndex = 0;
	int PrimitiveCount = 0;
	int StartRegister = 9;
	NiGeometryData* ModelData = Geo->geomData;
	NiGeometryBufferData* GeoData = ModelData->BuffData;
	NiSkinInstance* SkinInstance = Geo->skinInstance;
	NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);

	if (Geo->m_pcName && !memcmp(Geo->m_pcName, "Torch", 5)) return; // No torch geo, it is too near the light and a bad square is rendered.
	
	TheShaderManager->ShaderConst.Shadow.Data.x = 0.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
	TheShaderManager->ShaderConst.Shadow.Data.y = 0.0f; // Alpha control
	if (GeoData) {
		TheRenderManager->CreateD3DMatrix(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, &Geo->m_worldTransform);
		if (Geo->m_parent->m_pcName && !memcmp(Geo->m_parent->m_pcName, "Leaves", 6)) {
			SpeedTreeLeafShaderProperty* STProp = (SpeedTreeLeafShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
			BSTreeNode* Node = (BSTreeNode*)Geo->m_parent->m_parent;
			NiDX9SourceTextureData* Texture = (NiDX9SourceTextureData*)Node->TreeModel->LeavesTexture->rendererData;

			TheShaderManager->ShaderConst.Shadow.Data.x = 2.0f;
			Device->SetVertexShaderConstantF(63, (float*)&BillboardRight, 1);
			Device->SetVertexShaderConstantF(64, (float*)&BillboardUp, 1);
			Device->SetVertexShaderConstantF(65, Pointers::ShaderParams::RockParams, 1);
			Device->SetVertexShaderConstantF(66, Pointers::ShaderParams::RustleParams, 1);
			Device->SetVertexShaderConstantF(67, Pointers::ShaderParams::WindMatrixes, 16);
			Device->SetVertexShaderConstantF(83, STProp->leafData->leafBase, 48);
			RenderState->SetTexture(0, Texture->dTexture);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
		}
		else {
			BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
			if (!ShaderProperty || !ShaderProperty->IsLightingProperty()) return;
			BSShaderPPLightingProperty* lightProperty = (BSShaderPPLightingProperty*)ShaderProperty;
			/*Only seen 0.0 or 0.208. IS the structure actually corrrect?*/
			if (lightProperty->refractionPower >= 0.1f) return; //Configure,also check for actors, they are skinned
			if (AlphaEnabled) {
				NiAlphaProperty* AProp = (NiAlphaProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Alpha);
				if (AProp->flags & NiAlphaProperty::AlphaFlags::ALPHA_BLEND_MASK || AProp->flags & NiAlphaProperty::AlphaFlags::TEST_ENABLE_MASK) {
					if (NiTexture* Texture = *(lightProperty->textures[0])) {
						TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
						RenderState->SetTexture(0, Texture->rendererData->dTexture);
						RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
						RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
						RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
						RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
						RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
					}
				}
			}
		}
		TheRenderManager->PackGeometryBuffer(GeoData, ModelData, NULL, ShaderDeclaration);
		if(GeoData->StreamCount != 1) Logger::Log("%s %s  %i", Geo->m_pcName, Geo->m_parent->m_pcName, GeoData->StreamCount);
		for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
			Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
		}
		Device->SetIndices(GeoData->IB);
		if (GeoData->FVF)
			RenderState->SetFVF(GeoData->FVF, false);
		else
			RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
		CurrentVertex->SetCT();
		CurrentPixel->SetCT();
		if(GeoData->NumArrays != 1) Logger::Log("%i   %i", GeoData->NumArrays, GeoData->ArrayLengths);
		for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
			if (GeoData->ArrayLengths)
				PrimitiveCount = GeoData->ArrayLengths[i] - 2;
			else
				PrimitiveCount = GeoData->TriCount;
			Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
			StartIndex += PrimitiveCount + 2;
		}
	}
	else {
		TheShaderManager->ShaderConst.Shadow.Data.x = 1.0f;
		BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
		if (ShaderProperty && ShaderProperty->IsLightingProperty()) {
			BSShaderPPLightingProperty* lightProperty = (BSShaderPPLightingProperty*)ShaderProperty;
			if (lightProperty->refractionPower >= 0.1f) return; //Configure,also check for actors, they are skinned
			if (AlphaEnabled) {
				NiAlphaProperty* AProp = (NiAlphaProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Alpha);
				if (AProp->flags & NiAlphaProperty::AlphaFlags::ALPHA_BLEND_MASK || AProp->flags & NiAlphaProperty::AlphaFlags::TEST_ENABLE_MASK) {
					if (NiTexture* Texture = *(lightProperty->textures[0])) {
						TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
						RenderState->SetTexture(0, Texture->rendererData->dTexture);
						RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
						RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
						RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
						RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
						RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
					}
				}
			}
		}
		NiSkinPartition* SkinPartition = SkinInstance->SkinPartition;
		D3DPRIMITIVETYPE PrimitiveType = (SkinPartition->Partitions[0].Strips == 0) ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP;
		TheRenderManager->CalculateBoneMatrixes(SkinInstance, &Geo->m_worldTransform);
		if (SkinInstance->SkinToWorldWorldToSkin) memcpy(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, SkinInstance->SkinToWorldWorldToSkin, 0x40);
		for (UInt32 p = 0; p < SkinPartition->PartitionsCount; p++) {
            if (!SkinInstance->IsPartitionEnabled(p)) continue;

			StartIndex = 0;
			StartRegister = 9;
			NiSkinPartition::Partition* Partition = &SkinPartition->Partitions[p];
			for (int i = 0; i < Partition->Bones; i++) {
				UInt16 NewIndex = (Partition->pBones == NULL) ? i : Partition->pBones[i];
				Device->SetVertexShaderConstantF(StartRegister, ((float*)SkinInstance->BoneMatrixes) + (NewIndex * 3 * 4), 3);
				StartRegister += 3;
			}
			GeoData = Partition->BuffData;
			TheRenderManager->PackSkinnedGeometryBuffer(GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration);
			for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
				Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
			}
			Device->SetIndices(GeoData->IB);
			if (GeoData->FVF)
				RenderState->SetFVF(GeoData->FVF, false);
			else
				RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
			CurrentVertex->SetCT();
			CurrentPixel->SetCT();
			for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
				if (GeoData->ArrayLengths)
					PrimitiveCount = GeoData->ArrayLengths[i] - 2;
				else
					PrimitiveCount = GeoData->TriCount;
				Device->DrawIndexedPrimitive(PrimitiveType, GeoData->BaseVertexIndex, 0, Partition->Vertices, StartIndex, PrimitiveCount);
				StartIndex += PrimitiveCount + 2;
			}
		}
	}
}

D3DXMATRIX ShadowManager::GetCascadeViewProj(ShadowMapTypeEnum ShadowMapType, ffi::ShadowsExteriorStruct* ShadowsExteriors, D3DXMATRIX View) {
	D3DXMATRIX Proj;
	float FarPlane = ShadowsExteriors->ShadowMapFarPlane;
	float Radius = ShadowMapRadius[ShadowMapType];

	// calculating the size of the shadow cascade
	float znear;
	float zfar;
	switch (ShadowMapType) {
	case ShadowMapTypeEnum::MapNear:
		znear = 0.0f;
		zfar = ShadowMapRadius[ShadowMapTypeEnum::MapNear];
		break;
	case ShadowMapTypeEnum::MapMiddle:
		znear = ShadowMapRadius[ShadowMapTypeEnum::MapNear] * 0.8;
		zfar = ShadowMapRadius[ShadowMapTypeEnum::MapMiddle];
		break;
	case ShadowMapTypeEnum::MapFar:
		znear = ShadowMapRadius[ShadowMapTypeEnum::MapMiddle] * 0.8;
		zfar = ShadowMapRadius[ShadowMapTypeEnum::MapFar];
		break;
	case ShadowMapTypeEnum::MapLod:
		znear = ShadowMapRadius[ShadowMapTypeEnum::MapFar]* 0.8;
		zfar = ShadowMapRadius[ShadowMapTypeEnum::MapLod];
		break;
	default:
		D3DXMatrixOrthoOffCenterRH(&Proj, -Radius, Radius, -Radius, Radius, 0.0f, 2.0f * FarPlane);
		return View * Proj;
	}

	float safety = 1.0f;
	NiCamera* Camera = WorldSceneGraph->camera;
	float w = Camera->Frustum.Right - Camera->Frustum.Left;
	float h = Camera->Frustum.Top - Camera->Frustum.Bottom;

	float ar = h / w;

	float fov = TheRenderManager->FOVData.z;
	float fovY = TheRenderManager->FOVData.w;

	float tanHalfHFOV = tanf(fov * 0.5f) * safety;
	float tanHalfVFOV = tanf(fovY * 0.5f) * safety;

	float xn = znear * tanHalfHFOV;
	float xf = zfar * tanHalfHFOV;
	float yn = znear * tanHalfVFOV;
	float yf = zfar * tanHalfVFOV;

	D3DXVECTOR4 frustrumPoints[8];

	// near face
	frustrumPoints[0] = D3DXVECTOR4(xn, yn, znear, 1.0);
	frustrumPoints[1] = D3DXVECTOR4(-xn, yn, znear, 1.0);
	frustrumPoints[2] = D3DXVECTOR4(xn, -yn, znear, 1.0);
	frustrumPoints[3] = D3DXVECTOR4(-xn, -yn, znear, 1.0);

	// far face
	frustrumPoints[4] = D3DXVECTOR4(xf, yf, zfar, 1.0);
	frustrumPoints[5] = D3DXVECTOR4(-xf, yf, zfar, 1.0);
	frustrumPoints[6] = D3DXVECTOR4(xf, -yf, zfar, 1.0);
	frustrumPoints[7] = D3DXVECTOR4(-xf, -yf, zfar, 1.0);

	// values of the final light frustrum
	float left = 0.0f;
	float right = 0.0f;
	float bottom = 0.0f;
	float top = 0.0f;

	// transform from camera to world then to light space
	D3DXMATRIX m = TheRenderManager->InvViewMatrix * View;
	D3DXVECTOR4 p;
	for (int i = 0; i < 8; i++) {
		D3DXVec4Transform(&p, &frustrumPoints[i], &m);

		// extend frustrum to include all corners
		if (p.x < left || left == 0.0f) left = p.x;
		if (p.x > right || right == 0.0f) right = p.x;
		if (p.y > top || top == 0.0f) top = p.y;
		if (p.y < bottom || bottom == 0.0f) bottom = p.y;
	}


	D3DXMatrixOrthoOffCenterRH(&Proj, left, right, bottom, top, FarPlane * 0.6f, 1.4f * FarPlane);
	return View * Proj;
}

void CreateViewFrom(D3DXMATRIX* View, D3DXVECTOR3* At, D3DXVECTOR4* Dir, float FarPlane) {
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 Eye;
	Eye.x = At->x - FarPlane * Dir->x * -1;
	Eye.y = At->y - FarPlane * Dir->y * -1;
	Eye.z = At->z - FarPlane * Dir->z * -1;

	// calculating the projection matrix for point of view of the light
	D3DXMatrixLookAtRH(View, &Eye, At, &Up);

}
bool ShadowManager::IsVisible(ShadowMapTypeEnum type, UInt32 visibility) {
	visibility &= ~ShadowMapVisibility::FaceGenQuirk;
	if (type == ShadowMapTypeEnum::MapOrtho) return (visibility & ShadowMapVisibility::Ortho) == ShadowMapVisibility::Ortho;
	ShadowMapVisibility clean = (ShadowMapVisibility)(visibility & ~ShadowMapVisibility::Ortho);
	if (type == ShadowMapTypeEnum::MapLod) return  clean != ShadowMapVisibility::None;
	if (type == ShadowMapTypeEnum::MapFar) return  clean <= ShadowMapVisibility::Far && clean != ShadowMapVisibility::None;
	if (type == ShadowMapTypeEnum::MapMiddle) return  clean <= ShadowMapVisibility::Middle && clean != ShadowMapVisibility::None;
	if (type == ShadowMapTypeEnum::MapNear) return  clean == ShadowMapVisibility::Near;
	return false;
}

void ShadowManager::ClearShadowsMaps() {
	bool clearExt = WasEnabledExt || TheSettingManager->Config->ShadowsExterior.Enabled;
	bool clearInt = WasEnabledInt || TheSettingManager->Config->ShadowsInterior.Enabled;
	IDirect3DDevice9* Device = TheRenderManager->device;
	BSTextureManager* manager = *BSTextureManager::Singleton;
	int id = 0;
	Device->BeginScene();

	for (NiTList<BSRenderedTexture>::Entry* i = manager->unk30.start; i != nullptr; i = i->next, id++) {
		if (id > 0 && id % TheRenderManager->MaxRenderTargets  == 0) Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0L);
		HRESULT hr = Device->SetRenderTarget(id % TheRenderManager->MaxRenderTargets, i->data->RenderedTexture->buffer->data->Surface);
		if (FAILED(hr))Logger::Log("%08X", hr);
		if(id == 0)Device->SetDepthStencilSurface(i->data->RenderTargetGroup->DepthStencilBuffer->data->Surface); //Once, buffers seems the same surface
		//Logger::Log("%08X", i->data->RenderTargetGroup->DepthStencilBuffer->data->Surface);
	}
	if(id > 0) Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0L);
	for (int i = 0; i < TheRenderManager->MaxRenderTargets; i++) {
		Device->SetRenderTarget(i, NULL);
	}
	/*std::string filename = std::string("shadowMaps") + std::to_string(0x00B4310C);
	filename += ".jpg";
	if (ni && TheSettingManager->Config->ShadowsExterior.Enabled) {
		TheDebugManager->SaveRenderTarget(filename, ni->buffer->data->Surface);
		Device->SetRenderTarget(0, ni->buffer->data->Surface);
		Device->Clear(0L, NULL, D3DCLEAR_TARGET, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0L);
		
	}*/
	NiRenderedTexture** ni = (NiRenderedTexture**)0x00B4310C;
	if (*ni) {
		if (*ni != TheShadowManager->BackupCanopyMap && *ni != TheShadowManager->StubCanopyMap) {
			TheShadowManager->BackupCanopyMap = *ni;
		}
		if (TheSettingManager->Config->ShadowsExterior.Enabled) Pointers::Functions::SetTextureCanopyMap(TheShadowManager->StubCanopyMap);
		else Pointers::Functions::SetTextureCanopyMap(TheShadowManager->BackupCanopyMap);
	}

	if (clearExt) {
		for (UInt32 i = ShadowMapTypeEnum::MapNear; i <= ShadowMapTypeEnum::MapOrtho; i++) {
			Device->SetDepthStencilSurface(TheTextureManager->ShadowMapDepthSurface[i]);
			Device->SetViewport(&ShadowMapViewPort[i]);

			if ( i == MapOrtho) {
				Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurface[i]);
				Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);

			}
			else {
				Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurface[i]);
				Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
				Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurfaceBlurred[i]);
				Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
			}

		}
	}
	if (clearInt) {
		Device->SetDepthStencilSurface(TheTextureManager->ShadowCubeMapDepthSurface);
		for (int L = 0; L < ShadowCubeMapsMax; L++) {
			for (int Face = 0; Face < 6; Face++) {
				Device->SetRenderTarget(0, TheTextureManager->ShadowCubeMapSurface[L][Face]);
				Device->SetViewport(&ShadowCubeMapViewPort);
				Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
			}
		}
	}
	Device->EndScene();
}


void ShadowManager::RenderShadowExteriorMaps(ffi::ShadowsExteriorStruct* ShadowsExteriors, D3DXVECTOR3* At) {
	
	ShaderConstants::ShadowMapStruct* ShadowMap = &TheShaderManager->ShaderConst.ShadowMap;
	ffi::ShadowFormsStruct* Forms = &TheSettingManager->Config->ShadowsForm;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	GridCellArray* CellArray = Tes->gridCellArray;
	UInt32 CellArraySize = CellArray->size * CellArray->size;
	float FarPlane = ShadowsExteriors->ShadowMapFarPlane;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX ViewSun, ViewOrtho;
	D3DXVECTOR4 OrthoDir = D3DXVECTOR4(0.05f, 0.05f, 1.0f, 0.0f);
	D3DXVECTOR4* SunDir = &TheShaderManager->ShaderConst.SunDir;
	CreateViewFrom(&ViewSun, At, SunDir, FarPlane);
	CreateViewFrom(&ViewOrtho, At, &OrthoDir, FarPlane);
	AlphaEnabled = TheSettingManager->Config->ShadowsForm.Alpha;

	for (UInt32 i = ShadowMapTypeEnum::MapNear; i < ShadowMapTypeEnum::MapOrtho; i++) {
		D3DMATRIX ViewProj = GetCascadeViewProj((ShadowMapTypeEnum)i, ShadowsExteriors, ViewSun);
		SetFrustum((ShadowMapTypeEnum)i, &ViewProj);
	}
	D3DMATRIX ViewProj = GetCascadeViewProj(ShadowMapTypeEnum::MapOrtho, ShadowsExteriors, ViewOrtho);
	SetFrustum(ShadowMapTypeEnum::MapOrtho, &ViewProj);


	normalObjects.clear();
	alphaObjects.clear();
	speedtreeObjects.clear();
	skinnedObjects.clear();
	skinnedAlphaObjects.clear();

	for (UInt32 i = 0; i < CellArraySize; i++) {
		if (TESObjectCELL* Cell = CellArray->GetCell(i)) {
			std::vector<NiNode*> TerrainNodes = Cell->GetTerrainNodes();
			for (NiNode* node : TerrainNodes) {
				AccumulateGeometry(node, false);
			}
			//			if (ShadowsExteriors->Forms[ShadowMapType].Lod) RenderLod(Tes->landLOD, ShadowMapType); //Render terrain LOD
			/*for (UInt32 i = 2; i < Cell->GetNode()->m_children.numObjs; i++) {
				//For NewVegas: 0 Actor, 2 Land, 3 Static, 4 Dynamic,5 Multibound, 1 Marker 
				//For Oblivion: 0 Actor, 2-5 Static Terrain is in subnode 0 of every 2-5 node. Node 0 seems to be unstable, some actors aren't rendered sometimes (not present in the node?)
				NiNode* TerrainNode = (NiNode*)Cell->GetNode()->m_children.data[i];
				AccumulateGeometry(TerrainNode);
			} */
			TList<TESObjectREFR>::Entry* Entry = &Cell->objectList.First;
			while (Entry) {
				if (TESObjectREFR* Ref = GetRef(Entry->item, Forms)) {
					NiNode* RefNode = Ref->GetNode();
					AccumulateGeometry(RefNode, false);
				}
				Entry = Entry->next;
			}
		}
	}


	RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
	//	RenderState->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS, RenderStateArgs);

	RenderState->SetVertexShader(ShadowMapVertex->ShaderHandle, false);
	RenderState->SetPixelShader(ShadowMapPixel->ShaderHandle, false);
	Device->BeginScene();

	for (UInt32 i = ShadowMapTypeEnum::MapNear; i <= ShadowMapTypeEnum::MapOrtho; i++) {
		if (i == MapOrtho) {
			BillboardRight = { ViewOrtho._11, ViewOrtho._21, ViewOrtho._31, 0.0f };
			BillboardUp = { ViewOrtho._12, ViewOrtho._22, ViewOrtho._32, 0.0f };
		}
		else {
			BillboardRight = { ViewSun._11, ViewSun._21, ViewSun._31, 0.0f };
			BillboardUp = { ViewSun._12, ViewSun._22, ViewSun._32, 0.0f };
		}
		if (ShadowsExteriors->BlurShadowMaps || i == MapOrtho) {
			Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurface[i]);
		}
		else{
			Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurfaceBlurred[i]);
		}
		Device->SetDepthStencilSurface(TheTextureManager->ShadowMapDepthSurface[i]);
		Device->SetViewport(&ShadowMapViewPort[i]);

		ShadowMap->ShadowViewProj = GetCascadeViewProj((ShadowMapTypeEnum)i, ShadowsExteriors, i == ShadowMapTypeEnum::MapOrtho ? ViewOrtho : ViewSun); // calculating the size of the shadow cascade
		ShadowMap->ShadowCameraToLight[i] = TheRenderManager->InvViewProjMatrix * ShadowMap->ShadowViewProj;
		if ((SunDir->z > 0.0f && i <= ShadowMapTypeEnum::MapLod) || i == ShadowMapTypeEnum::MapOrtho) {
			RenderNormalPass(normalObjects, (ShadowMapTypeEnum) i);
			RenderAlphaPass(alphaObjects, (ShadowMapTypeEnum)i);
			RenderSpeedTreePass(speedtreeObjects, (ShadowMapTypeEnum)i);
			RenderSkinnedPass(skinnedObjects, (ShadowMapTypeEnum)i);
			RenderSkinnedAlphaPass(skinnedAlphaObjects, (ShadowMapTypeEnum)i);

		}
	}


	Device->EndScene();
}

void ShadowManager::RenderShadowCubeMap(NiPointLight** Lights, int LightIndex, ffi::ShadowsInteriorStruct* ShadowsInteriors) {
	
	ShaderConstants::ShadowMapStruct* ShadowMap = &TheShaderManager->ShaderConst.ShadowMap;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	ffi::ShadowFormsStruct* Forms = &TheSettingManager->Config->ShadowsForm;
	float Radius = 0.0f;
	float MinRadius = 0.0f; //ShadowsInteriors->Forms.MinRadius;
	NiPoint3* LightPos = NULL;
	D3DXMATRIX View, Proj;
	D3DXVECTOR3 Eye, At, Up;

	Device->SetDepthStencilSurface(TheTextureManager->ShadowCubeMapDepthSurface);
	for (int L = 0; L < ShadowCubeMapsMax; L++) {
		TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[L].w = 0.0f;
		if (L <= LightIndex) {
			LightPos = &Lights[L]->m_worldTransform.pos;
			Radius = Lights[L]->Spec.r * ShadowsInteriors->LightRadiusMult;
			if (Lights[L]->CanCarry) Radius = 256.0f;
			Eye.x = LightPos->x - TheRenderManager->CameraPosition.x;
			Eye.y = LightPos->y - TheRenderManager->CameraPosition.y;
			Eye.z = LightPos->z - TheRenderManager->CameraPosition.z;
			ShadowMap->ShadowCubeMapLightPosition.x = ShadowMap->ShadowLightPosition[L].x = Eye.x;
			ShadowMap->ShadowCubeMapLightPosition.y = ShadowMap->ShadowLightPosition[L].y = Eye.y;
			ShadowMap->ShadowCubeMapLightPosition.z = ShadowMap->ShadowLightPosition[L].z = Eye.z;
			ShadowMap->ShadowCubeMapLightPosition.w = ShadowMap->ShadowLightPosition[L].w = Radius;
			TheShaderManager->ShaderConst.Shadow.Data.z = Radius;
			D3DXMatrixPerspectiveFovRH(&Proj, D3DXToRadian(90.0f), 1.0f, 1.0f, Radius);
			for (int Face = 0; Face < 6; Face++) {
				At.x = Eye.x;
				At.y = Eye.y;
				At.z = Eye.z;
				switch (Face) {
				case D3DCUBEMAP_FACE_POSITIVE_X:
					At += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
					Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_X:
					At += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
					Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					break;
				case D3DCUBEMAP_FACE_POSITIVE_Y:
					At += D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_Y:
					At += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
					Up = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					break;
				case D3DCUBEMAP_FACE_POSITIVE_Z:
					At += D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_Z:
					At += D3DXVECTOR3(0.0f, 0.0f, 1.0f);
					Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					break;
				}
				D3DXMatrixLookAtRH(&View, &Eye, &At, &Up);
				ShadowMap->ShadowViewProj = View * Proj;
				Device->SetRenderTarget(0, TheTextureManager->ShadowCubeMapSurface[L][Face]);
				Device->SetViewport(&ShadowCubeMapViewPort);
				Device->BeginScene();
				RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
				RenderState->SetVertexShader(ShadowCubeMapVertex->ShaderHandle, false);
				RenderState->SetPixelShader(ShadowCubeMapPixel->ShaderHandle, false);
				TList<TESObjectREFR>::Entry* Entry = &Player->parentCell->objectList.First;
				while (Entry) {
					if (TESObjectREFR* Ref = GetRef(Entry->item, Forms)) {
						NiNode* RefNode = Ref->GetNode();
						if (RefNode->GetDistance(LightPos) <= Radius * 1.2f) RenderInterior(RefNode, MinRadius);
					}
					Entry = Entry->next;
				}
				Device->EndScene();
			}
		}
	}
	
}


//static 	NiDX9RenderState::NiRenderStateSetting* RenderStateSettings = nullptr;

/*
* Renders the different shadow maps: Near, Far, Ortho.
*/
bool ShadowManager::RenderShadowMaps() {
	
	ffi::ShadowsExteriorStruct* ShadowsExteriors = &TheSettingManager->Config->ShadowsExterior;
	ffi::ShadowsInteriorStruct* ShadowsInteriors = &TheSettingManager->Config->ShadowsInterior;
	ffi::ShadowFormsStruct* ShadowsInteriorsForms = &TheSettingManager->Config->ShadowsForm;
	ffi::ShadowsExteriorShaderStruct* ShadowsExteriorShader = &TheSettingManager->Shaders->Shadows.ShadowsExterior;
	ffi::ShadowsInteriorShaderStruct* ShadowsInteriorShader = &TheSettingManager->Shaders->Shadows.ShadowsInterior;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	IDirect3DSurface9* DepthSurface = NULL;
	IDirect3DSurface9* RenderSurface = NULL;
	D3DVIEWPORT9 viewport;
	bool TESRshadowsRendered = false;
	/*	if(RenderStateSettings == nullptr){
		RenderStateSettings = (NiDX9RenderState::NiRenderStateSetting*)malloc(sizeof(NiDX9RenderState::NiRenderStateSetting) * 256);
		memcpy(RenderStateSettings, RenderState->RenderStateSettings, sizeof(NiDX9RenderState::NiRenderStateSetting) * 256);
	}
	else{
		bool print = false;
		for(size_t i = 0; i < 256; i++){
			if(RenderStateSettings[i].CurrentValue != RenderState->RenderStateSettings[i].CurrentValue){
				Logger::Log("Different state between iterations: State %0X was %u is %0X",i, RenderStateSettings[i].CurrentValue, RenderState->RenderStateSettings[i].CurrentValue);
				RenderStateSettings[i].CurrentValue = RenderState->RenderStateSettings[i].CurrentValue;
				print = true;

			}
		}
		if(print) Logger::Log("End");
	} */

	D3DXVECTOR4* ShadowData = &TheShaderManager->ShaderConst.Shadow.Data;
	D3DXVECTOR4* OrthoData = &TheShaderManager->ShaderConst.Shadow.OrthoData;
	Device->GetDepthStencilSurface(&DepthSurface);
	Device->GetRenderTarget(0, &RenderSurface);
	Device->GetViewport(&viewport);	

	RenderState->SetRenderState(D3DRS_STENCILENABLE , 0 ,RenderStateArgs);
	RenderState->SetRenderState(D3DRS_STENCILREF , 0 ,RenderStateArgs);
 	RenderState->SetRenderState(D3DRS_STENCILFUNC , 8 ,RenderStateArgs);
	ClearShadowsMaps();
	Device->SetDepthStencilSurface(DepthSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->SetViewport(&viewport);

	WasEnabledExt = ShadowsExteriors->Enabled;
	WasEnabledInt = ShadowsInteriors->Enabled;
	TheRenderManager->SetupSceneCamera();
	if (Player->GetWorldSpace() && ShadowsExteriors->Enabled) {
		ShadowData->w = ShadowsExteriors->ShadowMode;	// Mode (0:off, 1:VSM, 2:ESM, 3: ESSM);
		NiNode* PlayerNode = Player->GetNode();
		D3DXVECTOR3 At;

		At.x = PlayerNode->m_worldTransform.pos.x - TheRenderManager->CameraPosition.x;
		At.y = PlayerNode->m_worldTransform.pos.y - TheRenderManager->CameraPosition.y;
		At.z = PlayerNode->m_worldTransform.pos.z - TheRenderManager->CameraPosition.z;

		CurrentVertex = ShadowMapVertex;
		CurrentPixel = ShadowMapPixel;
		// render ortho map
		RenderShadowExteriorMaps(ShadowsExteriors, &At);

		// Render all other shadow maps
		for (int i = MapNear; i < MapOrtho; i++) {
			if(ShadowsExteriors->BlurShadowMaps) BlurShadowMap((ShadowMapTypeEnum)i);
		}

		// Update constants used by shadow shaders: x=quality, y=darkness
		ShadowData->x = ShadowsExteriorShader->Quality;
		if (TheSettingManager->Config->Effects.ShadowsExteriors) ShadowData->x = -1; // Disable the forward shadowing
		ShadowData->y = ShadowsExteriorShader->Darkness;
		TESRshadowsRendered = true;
		// fade shadows when sun is nearing the horizon
		/*if (SunDir->z < 0.1f) {
			if (ShadowData->y == 0.0f) ShadowData->y = 0.1f;
			ShadowData->y += log(SunDir->z) / -10.0f;
			if (ShadowData->y > 1.0f) ShadowData->y = 1.0f;
		}*/
	}
	else if(ShadowsInteriors->Enabled){
		std::map<int, NiPointLight*> SceneLights;
		NiPointLight* Lights[ShadowCubeMapsMax] = { NULL };
		int LightIndex = -1;
#ifdef EXPERIMENTAL_FEATURE
		bool TorchOnBeltEnabled = EquipmentModeSettings->Enabled && EquipmentModeSettings->TorchKey != 255;
#else
		bool TorchOnBeltEnabled = false;
#endif
		NiTList<ShadowSceneLight>::Entry* Entry = SceneNode->lights.start;
		while (Entry) {
			NiPointLight* Light = Entry->data->sourceLight;
			int Distance = (int)Light->GetDistance(&Player->pos);
			while (SceneLights[Distance]) { --Distance; }
			SceneLights[Distance] = Light;
			Entry = Entry->next;
		}

		std::map<int, NiPointLight*>::iterator v = SceneLights.begin();
		while (v != SceneLights.end()) {
			NiPointLight* Light = v->second;
			bool CastShadow = true;
			if (TorchOnBeltEnabled && Light->CanCarry == 2) {
				HighProcessEx* Process = (HighProcessEx*)Player->process;
				if (Process->OnBeltState == HighProcessEx::State::In) CastShadow = false;
			}
			if (Light->CastShadows && CastShadow) {
				LightIndex += 1;
				Lights[LightIndex] = Light;
			}
			if (LightIndex == ShadowsInteriors->LightPoints - 1 || LightIndex == 3) break;
			v++;
		}

		CurrentVertex = ShadowCubeMapVertex;
		CurrentPixel = ShadowCubeMapPixel;
		AlphaEnabled = TheSettingManager->Config->ShadowsForm.Alpha;
		RenderShadowCubeMap(Lights, LightIndex, ShadowsInteriors);
		CalculateBlend(Lights, LightIndex);

		ShadowData->x = ShadowsInteriorShader->Quality;
		if (TheSettingManager->Config->Effects.ShadowsInteriors) ShadowData->x = -1; // Disable the forward shadowing
		ShadowData->y = ShadowsInteriorShader->Darkness;
		ShadowData->z = 1.0f / (float)ShadowsInteriors->ShadowCubeMapResolution;
		TESRshadowsRendered = true;
	}
	Device->SetDepthStencilSurface(DepthSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->SetViewport(&viewport);
	/*for (int i = MapNear; i < MapLod; i++) {
		std::string filename = "shadowmap" + std::to_string(i);
		filename += ".jpg";
		TheDebugManager->SaveRenderTarget(filename, TheTextureManager->ShadowMapSurface[i]);
		std::string filename1 = "shadowmap" + std::to_string(i);
		filename += "B.jpg";
		TheDebugManager->SaveRenderTarget(filename, TheTextureManager->ShadowMapSurfaceBlurred[i]);

	}*/
	if (TheSettingManager->Config->Develop.DebugMode) {
		if (Global->OnKeyDown(0x17)) { // TODO: setting for debug key ?
			for (size_t i = 0; i < 256; i++) {
					Logger::Log("Different state between iterations: State %u is %0X", i, RenderState->RenderStateSettings[i].CurrentValue);
			}

			InterfaceManager->ShowMessage("Textures taken!");
		}
	}
	return TESRshadowsRendered;

}

void ShadowManager::CalculateBlend(NiPointLight** Lights, int LightIndex) {

	D3DXVECTOR4* ShadowCubeMapBlend = &TheShaderManager->ShaderConst.ShadowMap.ShadowCubeMapBlend;
	float* Blend = NULL;
	bool Found = false;

	if (memcmp(Lights, ShadowCubeMapLights, 16)) {
		for (int i = 0; i <= LightIndex; i++) {
			for (int j = 0; j <= LightIndex; j++) {
				if (Lights[i] == ShadowCubeMapLights[j]) {
					Found = true;
					break;
				}
			}
			if (i == 0)
				Blend = &ShadowCubeMapBlend->x;
			else if (i == 1)
				Blend = &ShadowCubeMapBlend->y;
			else if (i == 2)
				Blend = &ShadowCubeMapBlend->z;
			else if (i == 3)
				Blend = &ShadowCubeMapBlend->w;
			if (!Found) *Blend = 0.0f;
			Found = false;
		}
		memcpy(ShadowCubeMapLights, Lights, 16);
	}
	else {
		if (ShadowCubeMapBlend->x < 1.0f) ShadowCubeMapBlend->x += 0.1f;
		if (ShadowCubeMapBlend->y < 1.0f) ShadowCubeMapBlend->y += 0.1f;
		if (ShadowCubeMapBlend->z < 1.0f) ShadowCubeMapBlend->z += 0.1f;
		if (ShadowCubeMapBlend->w < 1.0f) ShadowCubeMapBlend->w += 0.1f;
	}
	
}


float ShadowManager::lerp(float a, float b, float t) {
	return (1 - t) * a + t * b;
}

//static bool gen = true;
bool ShadowManager::SetupGeometryRender(NiGeometry* Geo){
	/*
	 Somehow adding a geometry to a geometry group cause all sort of issues when then we call PackGeometryBuffers if reflections are disabled or some critical node is culled on reflection pass
	 That call seems required only for BSFaceGenNodes and only when relfections are off for some reasons
	 */
//	gen = true;
	if (!Geo->geomData->BuffData) {
		//TheRenderManager->BatchRenderShape(Geo);
		if((Geo->geomData->DataFlags & NiGeometryData::Consistency::CONSISTENCY_MASK) == NiGeometryData::Consistency::VOLATILE  ) {
//			gen = false;
			return false;
		}
//		TheRenderManager->unsharedGeometryGroup->AddObject(Geo->geomData, nullptr, nullptr);  //TODO Oblivion only for now. Find new vegas?
//		for(int i = 0; i < Geo->geomData->BuffData->StreamCount; i++){
//			TheRenderManager->unsharedGeometryGroup->CreateChip(Geo->geomData->BuffData, i);
//		}
	//	TheRenderManager->PrecacheGeometryData(Geo, 0,0 ,Geo->shader->ShaderDeclaration);
	//	TheRenderManager->BatchRenderShape(Geo);
		return true;
	}
	return false;
}

void ShadowManager::RenderNormalPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType) {
	for (std::tuple<NiGeometry*, UInt32>& obj : geometries) {
		NiGeometry* Geo = obj._Myfirst._Val;
		UInt32 visibility = obj._Get_rest()._Myfirst._Val;
		if (IsVisible(ShadowMapType,visibility) && Geo->geomData->BuffData) {
			TheShaderManager->ShaderConst.Shadow.Data.x = 0.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
			TheShaderManager->ShaderConst.Shadow.Data.y = 0.0f; // Alpha control
			TheRenderManager->CreateD3DMatrix(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, &Geo->m_worldTransform);
			IDirect3DDevice9* Device = TheRenderManager->device;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			int StartIndex = 0;
			int PrimitiveCount = 0;
		//	bool generated = SetupGeometryRender(Geo);
			NiGeometryData* ModelData = Geo->geomData;
			NiGeometryBufferData* GeoData = ModelData->BuffData;
//Pack doesn't seems required when reflections are off'
		   if((visibility & ShadowMapVisibility::FaceGenQuirk) == ShadowMapVisibility::FaceGenQuirk) 	TheRenderManager->PackGeometryBuffer(Geo->geomData->BuffData, Geo->geomData, NULL, Geo->shader->ShaderDeclaration);

			for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
				Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
			}
//			Logger::Log("%s %s  %08X", Geo->m_pcName, Geo->m_parent, GeoData->VBChip[0]->VB);
			Device->SetIndices(GeoData->IB);
			if (GeoData->FVF)
				RenderState->SetFVF(GeoData->FVF, false);
			else
				RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
			CurrentVertex->SetCT();
			CurrentPixel->SetCT();
			for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
				if (GeoData->ArrayLengths)
					PrimitiveCount = GeoData->ArrayLengths[i] - 2;
				else
					PrimitiveCount = GeoData->TriCount;
				Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
				StartIndex += PrimitiveCount + 2;
			}
		}
	}
}

void ShadowManager::RenderSpeedTreePass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType) {
	IDirect3DDevice9* Device = TheRenderManager->device;

	for (std::tuple<NiGeometry*, UInt32>& obj : geometries) {
		NiGeometry* Geo = obj._Myfirst._Val;
		if (IsVisible(ShadowMapType, obj._Get_rest()._Myfirst._Val)) {
			TheShaderManager->ShaderConst.Shadow.Data.x = 2.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
			TheShaderManager->ShaderConst.Shadow.Data.y = 0.0f; // Alpha control
			TheRenderManager->CreateD3DMatrix(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, &Geo->m_worldTransform);
			SpeedTreeLeafShaderProperty* STProp = (SpeedTreeLeafShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
			BSTreeNode* Node = (BSTreeNode*)Geo->m_parent->m_parent;
			NiDX9SourceTextureData* Texture = (NiDX9SourceTextureData*)Node->TreeModel->LeavesTexture->rendererData;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			int StartIndex = 0;
			int PrimitiveCount = 0;
			NiGeometryData* ModelData = Geo->geomData;
			NiGeometryBufferData* GeoData = ModelData->BuffData;
			NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);
	//		TheRenderManager->PackGeometryBuffer(Geo->geomData->BuffData, Geo->geomData, NULL, Geo->shader->ShaderDeclaration);

			Device->SetVertexShaderConstantF(63, (float*)&BillboardRight, 1);
			Device->SetVertexShaderConstantF(64, (float*)&BillboardUp, 1);
			Device->SetVertexShaderConstantF(65, Pointers::ShaderParams::RockParams, 1);
			Device->SetVertexShaderConstantF(66, Pointers::ShaderParams::RustleParams, 1);
			Device->SetVertexShaderConstantF(67, Pointers::ShaderParams::WindMatrixes, 16);

			Device->SetVertexShaderConstantF(83, STProp->leafData->leafBase, 48);
			RenderState->SetTexture(0, Texture->dTexture);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);

			for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
				Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
			}
			Device->SetIndices(GeoData->IB);
			if (GeoData->FVF)
				RenderState->SetFVF(GeoData->FVF, false);
			else
				RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
			CurrentVertex->SetCT();
			CurrentPixel->SetCT();
			for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
				if (GeoData->ArrayLengths)
					PrimitiveCount = GeoData->ArrayLengths[i] - 2;
				else
					PrimitiveCount = GeoData->TriCount;
				Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
				StartIndex += PrimitiveCount + 2;
			}
		}
	}
}
void ShadowManager::RenderAlphaPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType) {
	for (std::tuple<NiGeometry*, UInt32>& obj : geometries) {
		NiGeometry* Geo = obj._Myfirst._Val;
		UInt32 visibility = obj._Get_rest()._Myfirst._Val;
		if (IsVisible(ShadowMapType,visibility) && Geo->geomData->BuffData) {
			TheShaderManager->ShaderConst.Shadow.Data.x = 0.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
			TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
			TheRenderManager->CreateD3DMatrix(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, &Geo->m_worldTransform);
			IDirect3DDevice9* Device = TheRenderManager->device;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			int StartIndex = 0;
			int PrimitiveCount = 0;
		//	bool shouldAvoidPack = SetupGeometryRender(Geo);

			NiGeometryData* ModelData = Geo->geomData;
			NiGeometryBufferData* GeoData = ModelData->BuffData;
			NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);
			if((visibility & ShadowMapVisibility::FaceGenQuirk) == ShadowMapVisibility::FaceGenQuirk) 	TheRenderManager->PackGeometryBuffer(Geo->geomData->BuffData, Geo->geomData, NULL, Geo->shader->ShaderDeclaration);

			for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
				Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
			}
			Device->SetIndices(GeoData->IB);
			if (GeoData->FVF)
				RenderState->SetFVF(GeoData->FVF, false);
			else
				RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
			CurrentVertex->SetCT();
			CurrentPixel->SetCT();
			BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
			BSShaderPPLightingProperty* lightProperty = (BSShaderPPLightingProperty*)ShaderProperty;
			if (lightProperty->textures[0] &&  *(lightProperty->textures[0])) {
				TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
				NiTexture* Texture = *(lightProperty->textures[0]);
				RenderState->SetTexture(0, Texture->rendererData->dTexture);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
			}
			
			for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
				if (GeoData->ArrayLengths)
					PrimitiveCount = GeoData->ArrayLengths[i] - 2;
				else
					PrimitiveCount = GeoData->TriCount;
				Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
				StartIndex += PrimitiveCount + 2;
			}
		}
	}
}
void ShadowManager::RenderSkinnedAlphaPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType) {
	for (std::tuple<NiGeometry*, UInt32>& obj : geometries) {
		NiGeometry* Geo = obj._Myfirst._Val;
		if (IsVisible(ShadowMapType, obj._Get_rest()._Myfirst._Val)) {
			TheShaderManager->ShaderConst.Shadow.Data.x = 1.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
			TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
			IDirect3DDevice9* Device = TheRenderManager->device;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			int StartIndex = 0;
			int PrimitiveCount = 0;
			int StartRegister = 9;
			NiGeometryData* ModelData = Geo->geomData;
			NiGeometryBufferData* GeoData = ModelData->BuffData;
			NiSkinInstance* SkinInstance = Geo->skinInstance;
			NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);
			NiSkinPartition* SkinPartition = SkinInstance->SkinPartition;
			D3DPRIMITIVETYPE PrimitiveType = (SkinPartition->Partitions[0].Strips == 0) ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP;
			TheRenderManager->CalculateBoneMatrixes(SkinInstance, &Geo->m_worldTransform);
			if (SkinInstance->SkinToWorldWorldToSkin) memcpy(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, SkinInstance->SkinToWorldWorldToSkin, 0x40);
			BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
			BSShaderPPLightingProperty* lightProperty = (BSShaderPPLightingProperty*)ShaderProperty;
			if (NiTexture* Texture = *(lightProperty->textures[0])) {
				TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f; // Alpha Control
				RenderState->SetTexture(0, Texture->rendererData->dTexture);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
			}

			for (UInt32 p = 0; p < SkinPartition->PartitionsCount; p++) {

				if (!SkinInstance->IsPartitionEnabled(p)) continue;

				StartIndex = 0;
				StartRegister = 9;
				NiSkinPartition::Partition* Partition = &SkinPartition->Partitions[p];
				for (int i = 0; i < Partition->Bones; i++) {
					UInt16 NewIndex = (Partition->pBones == NULL) ? i : Partition->pBones[i];
					Device->SetVertexShaderConstantF(StartRegister, ((float*)SkinInstance->BoneMatrixes) + (NewIndex * 3 * 4), 3);
					StartRegister += 3;
				}
				GeoData = Partition->BuffData;
				TheRenderManager->PackSkinnedGeometryBuffer(GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration);
				for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
					Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
				}
				Device->SetIndices(GeoData->IB);
				if (GeoData->FVF)
					RenderState->SetFVF(GeoData->FVF, false);
				else
					RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
				CurrentVertex->SetCT();
				CurrentPixel->SetCT();
				for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
					if (GeoData->ArrayLengths)
						PrimitiveCount = GeoData->ArrayLengths[i] - 2;
					else
						PrimitiveCount = GeoData->TriCount;
					Device->DrawIndexedPrimitive(PrimitiveType, GeoData->BaseVertexIndex, 0, Partition->Vertices, StartIndex, PrimitiveCount);
					StartIndex += PrimitiveCount + 2;
				}
			}
		}
	}
}

void ShadowManager::RenderSkinnedPass(std::vector<std::tuple<NiGeometry*, UInt32>>& geometries, ShadowMapTypeEnum ShadowMapType) {
	for (std::tuple<NiGeometry*, UInt32>& obj : geometries) {
		NiGeometry* Geo = obj._Myfirst._Val;
		if (IsVisible(ShadowMapType, obj._Get_rest()._Myfirst._Val)) {
			TheShaderManager->ShaderConst.Shadow.Data.x = 1.0f; // Type of geo (0 normal, 1 actors (skinned), 2 speedtree leaves)
			TheShaderManager->ShaderConst.Shadow.Data.y = 0.0f; // Alpha control
			IDirect3DDevice9* Device = TheRenderManager->device;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			int StartIndex = 0;
			int PrimitiveCount = 0;
			int StartRegister = 9;
			NiGeometryData* ModelData = Geo->geomData;
			NiGeometryBufferData* GeoData = ModelData->BuffData;
			NiSkinInstance* SkinInstance = Geo->skinInstance;
			NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);
			NiSkinPartition* SkinPartition = SkinInstance->SkinPartition;
			D3DPRIMITIVETYPE PrimitiveType = (SkinPartition->Partitions[0].Strips == 0) ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP;
			TheRenderManager->CalculateBoneMatrixes(SkinInstance, &Geo->m_worldTransform);
			if (SkinInstance->SkinToWorldWorldToSkin) memcpy(&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld, SkinInstance->SkinToWorldWorldToSkin, 0x40);
			for (UInt32 p = 0; p < SkinPartition->PartitionsCount; p++) {

				if (!SkinInstance->IsPartitionEnabled(p)) continue;

				StartIndex = 0;
				StartRegister = 9;
				NiSkinPartition::Partition* Partition = &SkinPartition->Partitions[p];
				for (int i = 0; i < Partition->Bones; i++) {
					UInt16 NewIndex = (Partition->pBones == NULL) ? i : Partition->pBones[i];
					Device->SetVertexShaderConstantF(StartRegister, ((float*)SkinInstance->BoneMatrixes) + (NewIndex * 3 * 4), 3);
					StartRegister += 3;
				}
				GeoData = Partition->BuffData;
				TheRenderManager->PackSkinnedGeometryBuffer(GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration);
				for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
					Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
				}
				Device->SetIndices(GeoData->IB);
				if (GeoData->FVF) 
					RenderState->SetFVF(GeoData->FVF, false);
				else 
					RenderState->SetVertexDeclaration(GeoData->VertexDeclaration, false);
				CurrentVertex->SetCT();
				CurrentPixel->SetCT();
				for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
					if (GeoData->ArrayLengths)
						PrimitiveCount = GeoData->ArrayLengths[i] - 2;
					else
						PrimitiveCount = GeoData->TriCount;
					Device->DrawIndexedPrimitive(PrimitiveType, GeoData->BaseVertexIndex, 0, Partition->Vertices, StartIndex, PrimitiveCount);
					StartIndex += PrimitiveCount + 2;
				}
			}
		}
	}
}
/*
* Filters the Shadow Map of given index using a 2 pass gaussian blur
*/
void ShadowManager::BlurShadowMap(ShadowMapTypeEnum ShadowMapType) {
    IDirect3DDevice9* Device = TheRenderManager->device;
    NiDX9RenderState* RenderState = TheRenderManager->renderState;
    IDirect3DTexture9* SourceShadowMap = TheTextureManager->ShadowMapTexture[ShadowMapType];
    IDirect3DSurface9* TargetShadowMap = TheTextureManager->ShadowMapSurfaceBlurred[ShadowMapType];
	IDirect3DTexture9* BlurredShadowTexture = TheTextureManager->ShadowMapTextureBlurred[ShadowMapType];

    Device->SetDepthStencilSurface(NULL);
    RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE, RenderStateArgs);
    RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE, RenderStateArgs);
    RenderState->SetVertexShader(ShadowMapBlurVertex->ShaderHandle, false);
    RenderState->SetPixelShader(ShadowMapBlurPixel->ShaderHandle, false);
	RenderState->SetFVF(FrameFVF, false);
	Device->SetStreamSource(0, BlurShadowVertex[ShadowMapType], 0, sizeof(FrameVS));
	RenderState->SetTexture(0, SourceShadowMap);
	Device->SetRenderTarget(0, TargetShadowMap);
	
	// Pass map resolution to shader as a constant
//	ShadowMapBlurPixel->SetCT();
	D3DXVECTOR4 inverseRes = { ShadowMapInverseResolution[ShadowMapType], ShadowMapInverseResolution[ShadowMapType], 0.0f, 0.0f };
	ShadowMapBlurPixel->SetShaderConstantF(0, &inverseRes, 1);

	// blur in two passes, vertically and horizontally
	D3DXVECTOR4 Blur[2] = {
		D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f),
		D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f),
	};

	for (int i = 0; i < 2; i++) {
		// set blur direction shader constants
		ShadowMapBlurPixel->SetShaderConstantF(1, &Blur[i], 1);

		// draw call to execute the shader
		Device->BeginScene();
		Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		Device->EndScene();

		// move texture to render device for next pass
		RenderState->SetTexture(0, BlurredShadowTexture);
	}
    RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
    RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
}

