#define DEBUGOC 0

void OcclusionManager::Initialize() {
	Logger::Log("Starting the occlusion manager...");
	TheOcclusionManager = new OcclusionManager();
#ifdef EXPERIMENTAL_FEATURE	

	IDirect3DDevice9* Device = TheRenderManager->device;
	UINT OcclusionMapSizeX = TheRenderManager->width / TheSettingManager->Config->OcclusionCulling.OcclusionMapRatio;
	UINT OcclusionMapSizeY = TheRenderManager->height / TheSettingManager->Config->OcclusionCulling.OcclusionMapRatio;
#if !DEBUGOC	
	char* VertexShaderName = "OcclusionMap.vso";
	char* PixelShaderName = "OcclusionMap.pso";
#else
	char* VertexShaderName = "OcclusionMapDebug.vso";
	char* PixelShaderName = "OcclusionMapDebug.pso";
#endif

	TheOcclusionManager->WaterOccluded = false;
	TheOcclusionManager->WaterTexture = NULL;

	TheOcclusionManager->OcclusionMapVertex = (ShaderRecordVertex*)ShaderRecord::LoadShader(VertexShaderName, NULL);
	TheOcclusionManager->OcclusionMapPixel = (ShaderRecordPixel*)ShaderRecord::LoadShader(PixelShaderName, NULL);

	Device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &TheOcclusionManager->OcclusionQuery);
	Device->CreateTexture(OcclusionMapSizeX, OcclusionMapSizeY, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &TheOcclusionManager->OcclusionMapTexture, NULL);
	TheOcclusionManager->OcclusionMapTexture->GetSurfaceLevel(0, &TheOcclusionManager->OcclusionMapSurface);
	Device->CreateDepthStencilSurface(OcclusionMapSizeX, OcclusionMapSizeY, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, true, &TheOcclusionManager->OcclusionMapDepthSurface, NULL);
	TheOcclusionManager->OcclusionMapViewPort = { 0, 0, OcclusionMapSizeX, OcclusionMapSizeY, 0.0f, 1.0f };
#endif
}
bool OcclusionManager::InFrustum(NiNode* Node) {
	
	NiCullingProcess* Process = WorldSceneGraph->cullingProcess;
	UInt32 ActivePlanes = Process->Planes.ActivePlanes;
	NiBound* Bound = Node->GetWorldBound();
	UInt32 Side = 0;
	UInt32 i = 0;
	bool Result = false;

	if (ActivePlanes > 0) {
		for (i = 0; i < NiFrustumPlanes::MaxPlanes; i++) {
			if (ActivePlanes & (1 << i)) {
				Side = Bound->WhichSide(&Process->Planes.CullingPlanes[i]);
				if (Side == NiPlane::NegativeSide) break;
				if (Side == NiPlane::PositiveSide) Process->Planes.ActivePlanes &= ~(1 << i);
			}
		}
		if (i == NiFrustumPlanes::MaxPlanes) Result = true;
		Process->Planes.ActivePlanes = ActivePlanes;
	}
	return Result;

}
#ifdef EXPERIMENTAL_FEATURE
TESObjectREFR* OcclusionManager::GetRef(TESObjectREFR* Ref) {
	
	TESObjectREFR* R = NULL;

	if (Ref && Ref->niNode) {
		UInt8 TypeID = Ref->baseForm->formType;
		if (TypeID >= TESForm::FormType::kFormType_Stat && TypeID <= TESForm::FormType::kFormType_MoveableStatic && 1) R = Ref;
	}
	return R;

}

void OcclusionManager::RenderStatic(NiAVObject* Object, float MinBoundSize, float MaxBoundSize, bool PerformOcclusion) {
	
	NiPoint2 BoundSize;
	float BoundBox = 0.0f;

	if (Object) {
		NiBound* Bound = Object->GetWorldBound();
		if (!(Object->m_flags & NiAVObject::kFlag_AppCulled) && Object->m_worldTransform.pos.z + Bound->Radius > TheShaderManager->ShaderConst.Water.waterSettings.x) {
			TheRenderManager->GetScreenSpaceBoundSize(&BoundSize, Bound);
			BoundBox = (BoundSize.x * 100.f) * (BoundSize.y * 100.0f);
			if (BoundBox >= MinBoundSize && BoundBox <= MaxBoundSize) {
				void* VFT = *(void**)Object;
				if (VFT == Pointers::VirtualTables::NiNode || VFT == Pointers::VirtualTables::BSFadeNode) {
					if (VFT == Pointers::VirtualTables::BSFadeNode && ((BSFadeNode*)Object)->FadeAlpha < 0.9f) return;
					NiNode* Node = (NiNode*)Object;
					if (bhkCollisionObjectEx* CollisionObject = (bhkCollisionObjectEx*)Node->m_spCollision) {
						VFT = *(void**)CollisionObject;
						if (VFT == Pointers::VirtualTables::bhkCollisionObject) {
							if (!CollisionObject->GeoNode) {
								if (bhkRigidBody* RigidBody = CollisionObject->bRigidBody) {
									NiNode* GeoNode = (NiNode*)Pointers::Functions::MemoryAlloc(sizeof(NiNode)); GeoNode->New(1); GeoNode->SetName("bhkColDisp"); GeoNode->m_flags |= NiAVObject::kFlag_IsOCNode;
									GeoNode->m_localTransform.scale = fabs(1.0f / Node->m_worldTransform.scale);
									Node->AddObject(GeoNode, 1);
									GeoNode->UpdateDownwardPass(0.0f, false);
									NiNode* GeoNodeR = RigidBody->CreateNiGeometry(GeoNode);
									GeoNodeR->UpdateDownwardPass(0.0f, false);
									Node->RemoveObject((NiAVObject**)&GeoNode, GeoNode);
									CollisionObject->GeoNode = GeoNode;
								}
							}
							RenderImmediate(CollisionObject->GeoNode, PerformOcclusion);
						}
					}
					else {
						for (int i = 0; i < Node->m_children.end; i++) {
							RenderStatic(Node->m_children.data[i], MinBoundSize, MaxBoundSize, PerformOcclusion);
						}
					}
				}
			}
		}
	}

}

void OcclusionManager::RenderImmediate(NiAVObject* Object, bool PerformOcclusion) {
	
	DWORD Pixels = 0;
	
	if (Object) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode) {
			NiNode* Node = (NiNode*)Object;
			for (int i = 0; i < Node->m_children.end; i++) {
				RenderImmediate(Node->m_children.data[i], PerformOcclusion);
			}
		}
		else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
			NiGeometry* Geo = (NiGeometry*)Object;
			if (!Geo->geomData->BuffData) TheRenderManager->unsharedGeometryGroup->AddObject(Geo->geomData, NULL, NULL);
			if (PerformOcclusion) OcclusionQuery->Issue(D3DISSUE_BEGIN);
			Render(Geo);
			if (PerformOcclusion) {
				OcclusionQuery->Issue(D3DISSUE_END);
				while (OcclusionQuery->GetData((void*)&Pixels, sizeof(DWORD), D3DGETDATA_FLUSH) == S_FALSE);
				if (Pixels <= 10)
					Geo->m_flags |= NiAVObject::kFlag_IsOccluded;
				else
					Geo->m_flags &= ~NiAVObject::kFlag_IsOccluded;
			}
		}
	}

}

void OcclusionManager::RenderTerrain(NiAVObject* Object) {

	if (Object && !(Object->m_flags & NiAVObject::kFlag_AppCulled)) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode) {
			NiNode* Node = (NiNode*)Object;
			if (InFrustum(Node)) {
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderTerrain(Node->m_children.data[i]);
				}
			}
		}
		else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
			NiGeometry* Geo = (NiGeometry*)Object;
			if (Geo->geomData->BuffData) Render(Geo);
		}
	}

}

void OcclusionManager::RenderWater(NiAVObject* Object) {
	
	DWORD Pixels = 0;

	if (Object && !(Object->m_flags & NiAVObject::kFlag_AppCulled)) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode) {
			NiNode* Node = (NiNode*)Object;
			if (InFrustum(Node)) {
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderWater(Node->m_children.data[i]);
				}
			}
		}
		else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
			NiGeometry* Geo = (NiGeometry*)Object;
			if (Geo->geomData->BuffData) {
				OcclusionQuery->Issue(D3DISSUE_BEGIN);
				Render(Geo);
				OcclusionQuery->Issue(D3DISSUE_END);
				while (OcclusionQuery->GetData((void*)&Pixels, sizeof(DWORD), D3DGETDATA_FLUSH) == S_FALSE);
				if (Pixels <= 10) {
					Geo->m_flags |= NiAVObject::kFlag_IsOccluded;
				}
				else {
					WaterOccluded = false;
					Geo->m_flags &= ~NiAVObject::kFlag_IsOccluded;
				}
			}
		}
	}

}

void OcclusionManager::Render(NiGeometry* Geo) {

	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	int StartIndex = 0;
	int PrimitiveCount = 0;
	int StartRegister = 9;
	NiGeometryData* ModelData = Geo->geomData;
	NiGeometryBufferData* GeoData = ModelData->BuffData;
	NiD3DShaderDeclaration* ShaderDeclaration = (Geo->shader ? Geo->shader->ShaderDeclaration : NULL);
	D3DXMATRIX WorldMatrix;

	TheRenderManager->CreateD3DMatrix(&WorldMatrix, &Geo->m_worldTransform);
	D3DXMatrixMultiplyTranspose(&TheShaderManager->ShaderConst.OcclusionMap.OcclusionWorldViewProj, &WorldMatrix, &TheRenderManager->ViewProjMatrix);
	if (TheSettingManager->Config->Develop.DebugMode) {
		BSShaderProperty* ShaderProperty = (BSShaderProperty*)Geo->GetProperty(NiProperty::PropertyType::kType_Shade);
		if (ShaderProperty) {
			if (ShaderProperty->IsLightingProperty()) {
				if (NiTexture* Texture = *((BSShaderPPLightingProperty*)ShaderProperty)->textures[0]) {
					RenderState->SetTexture(0, Texture->rendererData->dTexture);
					RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
					RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
					RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
					RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
					RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
				}
			}
			else if (ShaderProperty->IsWaterProperty()) {
				if (!WaterTexture) D3DXCreateTextureFromFileA(TheRenderManager->device, ".\\Data\\Textures\\Water\\water00.dds", &WaterTexture);
				RenderState->SetTexture(0, WaterTexture);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
				RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
				RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
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
	OcclusionMapVertex->SetCT();
	OcclusionMapPixel->SetCT();
	for (UInt32 i = 0; i < GeoData->NumArrays; i++) {
		if (GeoData->ArrayLengths)
			PrimitiveCount = GeoData->ArrayLengths[i] - 2;
		else
			PrimitiveCount = GeoData->TriCount;
		Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
		StartIndex += PrimitiveCount + 2;
	}

}

void OcclusionManager::ManageDistantStatic(NiAVObject* Object, float MaxBoundSize) {

	NiPoint2 BoundSize;
	float BoundBox = 0.0f;

	if (Object && !(Object->m_flags & NiAVObject::kFlag_AppCulled)) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode) {
			NiNode* Node = (NiNode*)Object;
			if (InFrustum(Node)) {
				for (int i = 0; i < Node->m_children.end; i++) {
					ManageDistantStatic(Node->m_children.data[i], MaxBoundSize);
				}
			}
		}
		else if (VFT == Pointers::VirtualTables::BSFadeNode) {
			if (!TheSettingManager->Config->OcclusionCulling.OccludedDistantStaticIC && !memcmp(Object->m_pcName + 18, "ImperialCity", 12)) return;
			NiBound* Bound = Object->GetWorldBound();
			TheRenderManager->GetScreenSpaceBoundSize(&BoundSize, Bound);
			BoundBox = (BoundSize.x * 100.f) * (BoundSize.y * 100.0f);
			if (BoundBox <= MaxBoundSize)
				Object->m_flags |= NiAVObject::kFlag_IsOccluded;
			else
				Object->m_flags &= ~NiAVObject::kFlag_IsOccluded;
		}
	}

}
void OcclusionManager::ManageDistantStatic() {
	NiNode* DistantRefLOD = *(NiNode**)0x00B34424;
	SettingsMainStruct::CullingProcessStruct* CullingProcess = &TheSettingManager->Config->CullingProcess;
	if (Player->GetWorldSpace() && !Player->isMovingToNewSpace && DistantRefLOD) {
		for (int i = 1; i < DistantRefLOD->m_children.end; i++) {
			NiNode* ChildNode = (NiNode*)DistantRefLOD->m_children.data[i];
			ManageDistantStatic(ChildNode, CullingProcess->CullMinSize);
		}
	}
}

void OcclusionManager::RenderDistantStatic(NiAVObject* Object) {

	if (Object && !(Object->m_flags & NiAVObject::kFlag_AppCulled) && !(Object->m_flags & NiAVObject::kFlag_IsOccluded)) {
		void* VFT = *(void**)Object;
		if (VFT == Pointers::VirtualTables::NiNode || VFT == Pointers::VirtualTables::BSFadeNode) {
			NiNode* Node = (NiNode*)Object;
			if (InFrustum(Node)) {
				for (int i = 0; i < Node->m_children.end; i++) {
					RenderDistantStatic(Node->m_children.data[i]);
				}
			}
		}
		else if (VFT == Pointers::VirtualTables::NiTriShape || VFT == Pointers::VirtualTables::NiTriStrips) {
			NiGeometry* Geo = (NiGeometry*)Object;
			if (Geo->geomData->BuffData) Render(Geo);
		}
	}

}

void OcclusionManager::RenderOcclusionMap(ffi::ShadowsExteriorStruct* OcclusionCulling) {
#ifdef EXPERIMENTAL_FEATURE
	NiNode* WaterRoot = *(NiNode**)0x00B35230;
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	GridCellArray* CellArray = Tes->gridCellArray;
	UInt32 CellArraySize = CellArray->size * CellArray->size;
	float OccludingStaticMin = OcclusionCulling->OccludingStaticMin;
	float OccludedStaticMin = OcclusionCulling->OccludedStaticMin;
	float OccludedStaticMax = OcclusionCulling->OccludedStaticMax;

	Device->SetRenderTarget(0, OcclusionMapSurface);
	Device->SetDepthStencilSurface(OcclusionMapDepthSurface);
	Device->SetViewport(&OcclusionMapViewPort);
	Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0L);
	RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
	RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
	RenderState->SetVertexShader(OcclusionMapVertex->ShaderHandle, false);
	RenderState->SetPixelShader(OcclusionMapPixel->ShaderHandle, false);
	Device->BeginScene();
#if !DEBUGOC
	RenderState->SetRenderState(D3DRS_COLORWRITEENABLE, D3DZB_FALSE, RenderStateArgs);
#endif
	for (UInt32 i = 0; i < CellArraySize; i++) {
		if (TESObjectCELL* Cell = CellArray->GetCell(i)) {
			NiNode* CellNode = Cell->niNode;
			for (int i = 2; i < 6; i++) {
				NiNode* ChildNode = (NiNode*)CellNode->m_children.data[i];
				if (ChildNode->m_children.end) RenderTerrain(ChildNode->m_children.data[0]);
			}
			if (OcclusionCulling->OccludingStatic && InFrustum(CellNode)) {
				TList<TESObjectREFR>::Entry* Entry = &Cell->objectList.First;
				while (Entry) {
					if (TESObjectREFR* Ref = GetRef(Entry->item)) {
						NiNode* RefNode = Ref->niNode;
						if (InFrustum(RefNode)) RenderStatic(RefNode, OccludingStaticMin, FLT_MAX, false);
					}
					Entry = Entry->next;
				}
			}
		}
	}

	if (TheSettingManager->config->Develop.DebugMode) {
		NiNode* DistantRefLOD = *(NiNode**)0x00B34424;
		for (int i = 1; i < DistantRefLOD->m_children.end; i++) {
			NiNode* ChildNode = (NiNode*)DistantRefLOD->m_children.data[i];
			RenderDistantStatic(ChildNode);
		}
	}

	RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE, RenderStateArgs);
	WaterOccluded = true;
	RenderWater(WaterRoot);
	if (OcclusionCulling->OccludedStatic) {
		for (UInt32 i = 0; i < CellArraySize; i++) {
			if (TESObjectCELL* Cell = CellArray->GetCell(i)) {
				NiNode* CellNode = Cell->niNode;
				if (InFrustum(CellNode)) {
					TList<TESObjectREFR>::Entry* Entry = &Cell->objectList.First;
					while (Entry) {
						if (TESObjectREFR* Ref = GetRef(Entry->item)) {
							NiNode* RefNode = Ref->niNode;
							if (InFrustum(RefNode)) RenderStatic(RefNode, OccludedStaticMin, OccludedStaticMax, true);
						}
						Entry = Entry->next;
					}
				}
			}
		}
	}

	if (TheSettingManager->config->Develop.DebugMode) {
		RenderState->SetRenderState(D3DRS_COLORWRITEENABLE, D3DZB_TRUE, RenderStateArgs);
	}
	Device->EndScene();
#endif
}

void OcclusionManager::PerformOcclusionCulling() {
#ifdef EXPERIMENTAL_FEATURE
	IDirect3DDevice9* Device = TheRenderManager->device;
	IDirect3DSurface9* DepthSurface = NULL;
	SettingsMainStruct::OcclusionCullingStruct* OcclusionCulling = &TheSettingManager->Config->OcclusionCulling;

	if (Player->GetWorldSpace() && !Player->isMovingToNewSpace) {
		Device->GetDepthStencilSurface(&DepthSurface);
		TheRenderManager->SetupSceneCamera();
		RenderOcclusionMap(OcclusionCulling);
		Device->SetDepthStencilSurface(DepthSurface);
	}

	if (TheSettingManager->config->Develop.DebugMode) {
		if (Global->OnKeyDown(26)) D3DXSaveSurfaceToFileA(".\\Test\\occlusionmap.jpg", D3DXIFF_JPG, OcclusionMapSurface, NULL, NULL);
	}
#endif
}

#endif