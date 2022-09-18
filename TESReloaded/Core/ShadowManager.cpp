#define DEBUGSH 1

/*
* Initializes the Shadow Manager by grabbing the relevant settings and shaders, and setting up map sizes.
*/
void ShadowManager::Initialize() {
	
	Logger::Log("Starting the shadows manager...");
	TheShadowManager = new ShadowManager();

	SettingsShadowStruct::ExteriorsStruct* ShadowsExteriors = &TheSettingManager->SettingsShadows.Exteriors;
	SettingsShadowStruct::InteriorsStruct* ShadowsInteriors = &TheSettingManager->SettingsShadows.Interiors;
	UINT ShadowMapSize = 0;
	UINT ShadowCubeMapSize = ShadowsInteriors->ShadowCubeMapSize;

	TheShadowManager->ShadowMapVertex = (ShaderRecordVertex*)ShaderRecord::LoadShader("ShadowMap.vso", NULL);
	TheShadowManager->ShadowMapPixel = (ShaderRecordPixel*)ShaderRecord::LoadShader("ShadowMap.pso", NULL);
	TheShadowManager->ShadowCubeMapVertex = (ShaderRecordVertex*)ShaderRecord::LoadShader("ShadowCubeMap.vso", NULL);
	TheShadowManager->ShadowCubeMapPixel = (ShaderRecordPixel*)ShaderRecord::LoadShader("ShadowCubeMap.pso", NULL);

	// Store Shadow map sizes in Constants to pass to the Shaders

	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.x = ShadowsExteriors->ShadowMapRadius[0];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.y = ShadowsExteriors->ShadowMapRadius[1];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.z = ShadowsExteriors->ShadowMapRadius[2];
	TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius.w = ShadowsExteriors->ShadowMapRadius[3];

    TheShadowManager->ShadowMapBlurVertex = (ShaderRecordVertex*) ShaderRecord::LoadShader("ShadowMapBlur.vso", NULL);
    TheShadowManager->ShadowMapBlurPixel = (ShaderRecordPixel*) ShaderRecord::LoadShader("ShadowMapBlur.pso", NULL);

    if (TheShadowManager->ShadowMapVertex == nullptr || TheShadowManager->ShadowMapPixel == nullptr  || TheShadowManager->ShadowMapBlurVertex  == nullptr
        || TheShadowManager->ShadowCubeMapVertex == nullptr || TheShadowManager->ShadowCubeMapPixel == nullptr || TheShadowManager->ShadowMapBlurPixel  == nullptr ){
        Logger::Log("[ERROR]: Could not load one or more of the ShadowMap generation shaders. Reinstall the mod.");
    }
	for (int i = 0; i < 5; i++) {
		ShadowMapSize = ShadowsExteriors->ShadowMapSize[i];
		if (i<4) TheShaderManager->CreateFrameVertex(ShadowMapSize, ShadowMapSize, &TheShadowManager->BlurShadowVertex[i]);
		TheShadowManager->ShadowMapViewPort[i] = { 0, 0, ShadowMapSize, ShadowMapSize, 0.0f, 1.0f };
        TheShadowManager->ShadowMapInverseResolution[i] = 1.0f / (float) ShadowMapSize;
	}
	TheShadowManager->ShadowCubeMapViewPort = { 0, 0, ShadowCubeMapSize, ShadowCubeMapSize, 0.0f, 1.0f };
	memset(TheShadowManager->ShadowCubeMapLights, NULL, sizeof(ShadowCubeMapLights));

}

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
* Checks wether the given node is in the frustrum for the current type of Shadow map.
*/
bool ShadowManager::InFrustum(ShadowMapTypeEnum ShadowMapType, NiNode* Node) {
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
		if (ShadowMapType == MapFar && R) { // Ensures to not be fully in the near frustum
			for (int i = 0; i < 6; ++i) {
				Distance = D3DXPlaneDotCoord(&ShadowMapFrustum[MapNear][i], &Position);
				if (Distance <= -Bound->Radius || std::fabs(Distance) < Bound->Radius) {
					R = false;
					break;
				}
			}
			R = !R;
		}
	}
	return R;

}

TESObjectREFR* ShadowManager::GetRef(TESObjectREFR* Ref, SettingsShadowStruct::FormsStruct* Forms, SettingsShadowStruct::ExcludedFormsList* ExcludedForms) {
	
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
				(TypeID >= TESForm::FormType::kFormType_NPC && TypeID <= TESForm::FormType::kFormType_LeveledCreature && Forms->Actors))
				R = Ref;
			if (R && ExcludedForms->size() > 0 && std::binary_search(ExcludedForms->begin(), ExcludedForms->end(), Form->refID)) R = NULL;
		}
	}
	return R;

}

void ShadowManager::RenderExterior(NiAVObject* Object, float MinRadius) {
	
	if (Object) {
		float Radius = Object->GetWorldBoundRadius();
		if (!(Object->m_flags & NiAVObject::kFlag_AppCulled) && Radius >= MinRadius && Object->m_worldTransform.pos.z + Radius > TheShaderManager->ShaderConst.Water.waterSettings.x) {
			void* VFT = *(void**)Object;
			if (VFT == Pointers::VirtualTables::NiNode || VFT == Pointers::VirtualTables::BSFadeNode || VFT == Pointers::VirtualTables::BSFaceGenNiNode || VFT == Pointers::VirtualTables::BSTreeNode) {
				if (VFT == Pointers::VirtualTables::BSFadeNode && ((BSFadeNode*)Object)->FadeAlpha < 0.75f) return;
				NiNode* Node = (NiNode*)Object;
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderExterior(Node->m_children.data[i], MinRadius);
				}
			}
			else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
				RenderGeometry((NiGeometry*)Object);
			}
		}
	}

}

void ShadowManager::RenderInterior(NiAVObject* Object, float MinRadius) {
	
	if (Object) {
		float Radius = Object->GetWorldBoundRadius();
		if (!(Object->m_flags & NiAVObject::kFlag_AppCulled) && Radius >= MinRadius) {
			void* VFT = *(void**)Object;
			if (VFT == Pointers::VirtualTables::NiNode || VFT == Pointers::VirtualTables::BSFadeNode || VFT == Pointers::VirtualTables::BSFaceGenNiNode) {
				NiNode* Node = (NiNode*)Object;
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderInterior(Node->m_children.data[i], MinRadius);
				}
			}
			else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
				RenderGeometry((NiGeometry*)Object);
			}
		}
	}

}

void ShadowManager::RenderTerrain(NiAVObject* Object, ShadowMapTypeEnum ShadowMapType) {

	if (Object && !(Object->m_flags & NiAVObject::kFlag_AppCulled)) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode) {
			NiNode* Node = (NiNode*)Object;
			if (InFrustum(ShadowMapType, Node)) {
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderTerrain(Node->m_children.data[i], ShadowMapType);
				}
			}
		}
		else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
			RenderGeometry((NiGeometry*)Object);
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
			if (AlphaEnabled) {
				NiAlphaProperty* AProp = (NiAlphaProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Alpha);
				if (AProp->flags & NiAlphaProperty::AlphaFlags::ALPHA_BLEND_MASK || AProp->flags & NiAlphaProperty::AlphaFlags::TEST_ENABLE_MASK) {
					if (NiTexture* Texture = *((BSShaderPPLightingProperty*)ShaderProperty)->textures[0]) {
						TheShaderManager->ShaderConst.Shadow.Data.y = 1.0f;
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
		for (UInt32 i = 0; i < GeoData->StreamCount; i++) {
			Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
		}
		Device->SetIndices(GeoData->IB);
		if (GeoData->FVF)
			Device->SetFVF(GeoData->FVF);
		else
			Device->SetVertexDeclaration(GeoData->VertexDeclaration);
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
	else {
		TheShaderManager->ShaderConst.Shadow.Data.x = 1.0f;
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
				Device->SetFVF(GeoData->FVF);
			else
				Device->SetVertexDeclaration(GeoData->VertexDeclaration);
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

void ShadowManager::RenderShadowMap(ShadowMapTypeEnum ShadowMapType, SettingsShadowStruct::ExteriorsStruct* ShadowsExteriors, D3DXVECTOR3* At, D3DXVECTOR4* SunDir) {
	
	ShaderConstants::ShadowMapStruct* ShadowMap = &TheShaderManager->ShaderConst.ShadowMap;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	GridCellArray* CellArray = Tes->gridCellArray;
	UInt32 CellArraySize = CellArray->size * CellArray->size;
	float FarPlane = ShadowsExteriors->ShadowMapFarPlane;
	float Radius = ShadowsExteriors->ShadowMapRadius[ShadowMapType];
	float MinRadius = ShadowsExteriors->Forms[ShadowMapType].MinRadius;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX View, Proj;
	D3DXVECTOR3 Eye;

	AlphaEnabled = ShadowsExteriors->AlphaEnabled[ShadowMapType];

	Eye.x = At->x - FarPlane * SunDir->x * -1;
	Eye.y = At->y - FarPlane * SunDir->y * -1;
	Eye.z = At->z - FarPlane * SunDir->z * -1;
	D3DXMatrixLookAtRH(&View, &Eye, At, &Up);
	D3DXMatrixOrthoRH(&Proj, 2.0f * Radius, (1 + SunDir->z) * Radius, 0.0f, 2.0f * FarPlane);
	ShadowMap->ShadowViewProj = View * Proj;
	ShadowMap->ShadowCameraToLight[ShadowMapType] = TheRenderManager->InvViewProjMatrix * ShadowMap->ShadowViewProj;
	BillboardRight = { View._11, View._21, View._31, 0.0f };
	BillboardUp = { View._12, View._22, View._32, 0.0f };
	SetFrustum(ShadowMapType, &ShadowMap->ShadowViewProj);
	Device->SetRenderTarget(0, TheTextureManager->ShadowMapSurface[ShadowMapType]);
	Device->SetDepthStencilSurface(TheTextureManager->ShadowMapDepthSurface[ShadowMapType]);
	Device->SetViewport(&ShadowMapViewPort[ShadowMapType]);
	Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
	if (SunDir->z > 0.0f) {
		RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
		RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
		RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
		RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
		RenderState->SetVertexShader(ShadowMapVertex->ShaderHandle, false);
		RenderState->SetPixelShader(ShadowMapPixel->ShaderHandle, false);
		Device->BeginScene();
		for (UInt32 i = 0; i < CellArraySize; i++) {
			if (TESObjectCELL* Cell = CellArray->GetCell(i)) {
				if (ShadowsExteriors->Forms[ShadowMapType].Terrain) {
					NiNode* CellNode = Cell->GetNode();
					for (int i = 2; i < 6; i++) {
						NiNode* TerrainNode = (NiNode*)CellNode->m_children.data[i];
						if (TerrainNode->m_children.end) RenderTerrain(TerrainNode->m_children.data[0], ShadowMapType);
					}
				}
				TList<TESObjectREFR>::Entry* Entry = &Cell->objectList.First;
				while (Entry) {
					if (TESObjectREFR* Ref = GetRef(Entry->item, &ShadowsExteriors->Forms[ShadowMapType], &ShadowsExteriors->ExcludedForms)) {
						NiNode* RefNode = Ref->GetNode();
						if (InFrustum(ShadowMapType, RefNode)) RenderExterior(RefNode, MinRadius);
					}
					Entry = Entry->next;
				}
			}
		}
		Device->EndScene();
	}

}

void ShadowManager::RenderShadowCubeMap(NiPointLight** Lights, int LightIndex, SettingsShadowStruct::InteriorsStruct* ShadowsInteriors) {
	
	ShaderConstants::ShadowMapStruct* ShadowMap = &TheShaderManager->ShaderConst.ShadowMap;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	float Radius = 0.0f;
	float MinRadius = ShadowsInteriors->Forms.MinRadius;
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
				Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
				Device->BeginScene();
				RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
				Device->SetViewport(&ShadowCubeMapViewPort);
				RenderState->SetVertexShader(ShadowCubeMapVertex->ShaderHandle, false);
				RenderState->SetPixelShader(ShadowCubeMapPixel->ShaderHandle, false);
				TList<TESObjectREFR>::Entry* Entry = &Player->parentCell->objectList.First;
				while (Entry) {
					if (TESObjectREFR* Ref = GetRef(Entry->item, &ShadowsInteriors->Forms, &ShadowsInteriors->ExcludedForms)) {
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
void ShadowManager::RenderShadowMaps() {
	
	SettingsMainStruct::EquipmentModeStruct* EquipmentModeSettings = &TheSettingManager->SettingsMain.EquipmentMode;
	SettingsShadowStruct::ExteriorsStruct* ShadowsExteriors = &TheSettingManager->SettingsShadows.Exteriors;
	SettingsShadowStruct::InteriorsStruct* ShadowsInteriors = &TheSettingManager->SettingsShadows.Interiors;
	SettingsShadowStruct::FormsStruct* ShadowsInteriorsForms = &ShadowsInteriors->Forms;
	SettingsShadowStruct::ExcludedFormsList* ShadowsInteriorsExcludedForms = &ShadowsInteriors->ExcludedForms;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	if (!ShadowsExteriors->Enabled && !ShadowsInteriors->Enabled) return;
	IDirect3DSurface9* DepthSurface = NULL;
	IDirect3DSurface9* RenderSurface = NULL;
	D3DVIEWPORT9 viewport;
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
    
	TheRenderManager->SetupSceneCamera();
	if (Player->GetWorldSpace() && ShadowsExteriors->Enabled) {
		D3DXVECTOR4* SunDir = &TheShaderManager->ShaderConst.SunDir;
		D3DXVECTOR4 OrthoDir = D3DXVECTOR3(0.05f, 0.05f, 1.0f);
		NiNode* PlayerNode = Player->GetNode();
		D3DXVECTOR3 At;

		At.x = PlayerNode->m_worldTransform.pos.x - TheRenderManager->CameraPosition.x;
		At.y = PlayerNode->m_worldTransform.pos.y - TheRenderManager->CameraPosition.y;
		At.z = PlayerNode->m_worldTransform.pos.z - TheRenderManager->CameraPosition.z;

		CurrentVertex = ShadowMapVertex;
		CurrentPixel = ShadowMapPixel;
		RenderShadowMap(MapNear, ShadowsExteriors, &At, SunDir);
		RenderShadowMap(MapMiddle, ShadowsExteriors, &At, SunDir);
		RenderShadowMap(MapFar, ShadowsExteriors, &At, SunDir);
		RenderShadowMap(MapLod, ShadowsExteriors, &At, SunDir);
		RenderShadowMap(MapOrtho, ShadowsExteriors, &At, &OrthoDir);
		ShadowData->z = ShadowMapInverseResolution[MapNear];
		ShadowData->w = ShadowMapInverseResolution[MapFar];
		OrthoData->z = ShadowMapInverseResolution[MapOrtho];
        BlurShadowMap(MapNear);
        BlurShadowMap(MapMiddle);
        BlurShadowMap(MapFar);
		BlurShadowMap(MapLod);

		ShadowData->x = ShadowsExteriors->Quality;
		if (TheSettingManager->SettingsMain.Effects.ShadowsExteriors) ShadowData->x = -1; // Disable the forward shadowing
		ShadowData->y = ShadowsExteriors->Darkness;
		if (SunDir->z < 0.1f) {
			if (ShadowData->y == 0.0f) ShadowData->y = 0.1f;
			ShadowData->y += log(SunDir->z) / -10.0f;
			if (ShadowData->y > 1.0f) ShadowData->y = 1.0f;
		}
	}
	else if(ShadowsInteriors->Enabled){
		std::map<int, NiPointLight*> SceneLights;
		NiPointLight* Lights[ShadowCubeMapsMax] = { NULL };
		int LightIndex = -1;
		bool TorchOnBeltEnabled = EquipmentModeSettings->Enabled && EquipmentModeSettings->TorchKey != 255;

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
		AlphaEnabled = ShadowsInteriors->AlphaEnabled;
		RenderShadowCubeMap(Lights, LightIndex, ShadowsInteriors);
		CalculateBlend(Lights, LightIndex);

		ShadowData->x = ShadowsInteriors->Quality;
		if (TheSettingManager->SettingsMain.Effects.ShadowsInteriors) ShadowData->x = -1; // Disable the forward shadowing
		ShadowData->y = ShadowsInteriors->Darkness;
		ShadowData->z = 1.0f / (float)ShadowsInteriors->ShadowCubeMapSize;
	}
	Device->SetDepthStencilSurface(DepthSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->SetViewport(&viewport);

#if DEBUGSH
	if (Global->OnKeyDown(0x17)) {
		char Filename[MAX_PATH];

		time_t CurrentTime = time(NULL);
		GetCurrentDirectoryA(MAX_PATH, Filename);
        strcat(Filename, "\\Test");
		if (GetFileAttributesA(Filename) == INVALID_FILE_ATTRIBUTES) CreateDirectoryA(Filename, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap0.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurface[MapNear], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap1.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurface[MapMiddle], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap2.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurface[MapFar], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap3.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurface[MapLod], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap4.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurface[MapOrtho], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap0B.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurfaceBlurred[0], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap1B.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurfaceBlurred[1], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap2B.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurfaceBlurred[2], NULL, NULL);
		D3DXSaveSurfaceToFileA(".\\Test\\shadowmap3B.jpg", D3DXIFF_JPG, TheTextureManager->ShadowMapSurfaceBlurred[3], NULL, NULL);

		InterfaceManager->ShowMessage("Textures taken!");
	}
#endif

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
void ShadowManager::BlurShadowMap(ShadowMapTypeEnum ShadowMapType) {
    IDirect3DDevice9* Device = TheRenderManager->device;
    NiDX9RenderState* RenderState = TheRenderManager->renderState;
    IDirect3DTexture9* SourceShadowMap = TheTextureManager->ShadowMapTexture[ShadowMapType];
    IDirect3DSurface9* TargetShadowMap = TheTextureManager->ShadowMapSurfaceBlurred[ShadowMapType];
    
    Device->SetDepthStencilSurface(NULL);
    RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE, RenderStateArgs);
    RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE, RenderStateArgs);
    RenderState->SetVertexShader(ShadowMapBlurVertex->ShaderHandle, false);
    RenderState->SetPixelShader(ShadowMapBlurPixel->ShaderHandle, false);

	Device->SetFVF(FrameFVF);
	Device->SetStreamSource(0, BlurShadowVertex[ShadowMapType], 0, sizeof(FrameVS));
    Device->SetRenderTarget(0, TargetShadowMap);
 //   Device->Clear(0L, NULL, D3DCLEAR_TARGET, D3DXCOLOR(0, 0, 0, 0), 1.0f, 0L);
    Device->SetTexture(0, SourceShadowMap);
    //ShadowMapBlurVertex->SetCT(); Just screenspace. No constants
    ShadowMapBlurPixel->SetCT();
    D3DXVECTOR4 inverseRes = { ShadowMapInverseResolution[ShadowMapType] ,ShadowMapInverseResolution[ShadowMapType], 0.0f, 0.0f}; 
    ShadowMapBlurPixel->SetShaderConstantF(0, &inverseRes, 1);
   // ShadowMapBlur->Effect->SetVector(0, &TheShaderManager->ShaderConst.ReciprocalResolution);
    Device->BeginScene();
//	Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    Device->EndScene();
}

