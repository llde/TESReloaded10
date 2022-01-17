#define RESZ_CODE 0x7FA05000

void RenderManager::CreateD3DMatrix(D3DMATRIX* Matrix, NiTransform* Transform) {

	NiMatrix33* Rot = &Transform->rot;
	NiPoint3* Pos = &Transform->pos;
	float Scale = Transform->scale;

	Matrix->_11 = Rot->data[0][0] * Scale;
	Matrix->_12 = Rot->data[1][0] * Scale;
	Matrix->_13 = Rot->data[2][0] * Scale;
	Matrix->_14 = 0.0f;
	Matrix->_21 = Rot->data[0][1] * Scale;
	Matrix->_22 = Rot->data[1][1] * Scale;
	Matrix->_23 = Rot->data[2][1] * Scale;
	Matrix->_24 = 0.0f;
	Matrix->_31 = Rot->data[0][2] * Scale;
	Matrix->_32 = Rot->data[1][2] * Scale;
	Matrix->_33 = Rot->data[2][2] * Scale;
	Matrix->_34 = 0.0f;
	Matrix->_41 = Pos->x - CameraPosition.x;
	Matrix->_42 = Pos->y - CameraPosition.y;
	Matrix->_43 = Pos->z - CameraPosition.z;
	Matrix->_44 = 1.0f;

}

void RenderManager::GetScreenSpaceBoundSize(NiPoint2* BoundSize, NiBound* Bound, float ZeroTolerance) {
		
	NiCamera* Camera = WorldSceneGraph->camera;
	NiMatrix33* WorldRotate = &Camera->m_worldTransform.rot;
	NiPoint3 BoundPos = { Bound->Center.x - Camera->m_worldTransform.pos.x, Bound->Center.y - Camera->m_worldTransform.pos.y, Bound->Center.y - Camera->m_worldTransform.pos.y };
	NiPoint3 CameraDirection = { WorldRotate->data[0][0], WorldRotate->data[1][0], WorldRotate->data[2][0] };
	float BoundViewDist = BoundPos * CameraDirection;
	float Ratio = Bound->Radius;

	if (BoundViewDist < ZeroTolerance) {
		if (BoundViewDist > -ZeroTolerance) {
			BoundSize->x = FLT_MAX;
			BoundSize->y = FLT_MAX;
			return;
		}
		BoundViewDist = -BoundViewDist;
	}

	if (!Camera->Frustum.Ortho) Ratio /= BoundViewDist;
	BoundSize->x = Ratio * 2.0f / (Camera->Frustum.Right - Camera->Frustum.Left);
	BoundSize->y = Ratio * 2.0f / (Camera->Frustum.Top - Camera->Frustum.Bottom);

}

void RenderManager::UpdateSceneCameraData() {

	NiCamera* Camera = WorldSceneGraph->camera;

	if (Camera) {
		NiMatrix33* WorldRotate = &Camera->m_worldTransform.rot;
		NiPoint3* WorldTranslate = &Camera->m_worldTransform.pos;
		
		CameraForward.x = WorldRotate->data[0][0];
		CameraForward.y = WorldRotate->data[1][0];
		CameraForward.z = WorldRotate->data[2][0];
		CameraPosition.x = WorldTranslate->x;
		CameraPosition.y = WorldTranslate->y;
		CameraPosition.z = WorldTranslate->z;
	}

}

void RenderManager::SetupSceneCamera() {

	NiCamera* Camera = WorldSceneGraph->camera;

	if (Camera) {
		NiPoint3 Loc = *Pointers::Generic::CameraLocation;
		NiPoint3 Forward = { 0.0f, 0.0f, 0.0f };
		NiPoint3 Up = { 0.0f, 0.0f, 0.0f };
		NiPoint3 Right = { 0.0f, 0.0f, 0.0f };
		D3DXMATRIX InvProj;
		NiMatrix33* WorldRotate = &Camera->m_worldTransform.rot;
		NiPoint3* WorldTranslate = &Camera->m_worldTransform.pos;
		NiFrustum* Frustum = &Camera->Frustum;
		float RmL = Frustum->Right - Frustum->Left;
		float RpL = Frustum->Right + Frustum->Left;
		float TmB = Frustum->Top - Frustum->Bottom;
		float TpB = Frustum->Top + Frustum->Bottom;
		float InvFmN = 1.0f / (Frustum->Far - Frustum->Near);

		memcpy(Pointers::Generic::CameraWorldTranslate, WorldTranslate, 0x0C);

		Forward.x = WorldRotate->data[0][0];
		Forward.y = WorldRotate->data[1][0];
		Forward.z = WorldRotate->data[2][0];
		Up.x = WorldRotate->data[0][1];
		Up.y = WorldRotate->data[1][1];
		Up.z = WorldRotate->data[2][1];
		Right.x = WorldRotate->data[0][2];
		Right.y = WorldRotate->data[1][2];
		Right.z = WorldRotate->data[2][2];

		// We set up the world matrix always to default (image space) because we use it only in image space shaders
		worldMatrix._11 = 1.0f;
		worldMatrix._12 = 0.0f;
		worldMatrix._13 = 0.0f;
		worldMatrix._14 = 0.0f;
		worldMatrix._21 = 0.0f;
		worldMatrix._22 = 1.0f;
		worldMatrix._23 = 0.0f;
		worldMatrix._24 = 0.0f;
		worldMatrix._31 = 0.0f;
		worldMatrix._32 = 0.0f;
		worldMatrix._33 = 1.0f;
		worldMatrix._34 = 0.0f;
		worldMatrix._41 = -WorldTranslate->x;
		worldMatrix._42 = -WorldTranslate->y;
		worldMatrix._43 = -WorldTranslate->z;
		worldMatrix._44 = 1.0f;

		viewMatrix._11 = Right.x;
		viewMatrix._12 = Up.x;
		viewMatrix._13 = Forward.x;
		viewMatrix._14 = 0.0f;
		viewMatrix._21 = Right.y;
		viewMatrix._22 = Up.y;
		viewMatrix._23 = Forward.y;
		viewMatrix._24 = 0.0f;
		viewMatrix._31 = Right.z;
		viewMatrix._32 = Up.z;
		viewMatrix._33 = Forward.z;
		viewMatrix._34 = 0.0f;
		viewMatrix._41 = -(Right * Loc);
		viewMatrix._42 = -(Up * Loc);
		viewMatrix._43 = -(Forward * Loc);
		viewMatrix._44 = 1.0f;

		invViewMatrix._11 = Right.x;
		invViewMatrix._12 = Right.y;
		invViewMatrix._13 = Right.z;
		invViewMatrix._14 = 0.0f;
		invViewMatrix._21 = Up.x;
		invViewMatrix._22 = Up.y;
		invViewMatrix._23 = Up.z;
		invViewMatrix._24 = 0.0f;
		invViewMatrix._31 = Forward.x;
		invViewMatrix._32 = Forward.y;
		invViewMatrix._33 = Forward.z;
		invViewMatrix._34 = 0.0f;
		invViewMatrix._41 = Loc.x;
		invViewMatrix._42 = Loc.y;
		invViewMatrix._43 = Loc.z;
		invViewMatrix._44 = 1.0f;

		projMatrix._11 = 2.0f / RmL;
		projMatrix._12 = 0.0f;
		projMatrix._13 = 0.0f;
		projMatrix._14 = 0.0f;
		projMatrix._21 = 0.0f;
		projMatrix._22 = 2.0f / TmB;
		projMatrix._23 = 0.0f;
		projMatrix._24 = 0.0f;
		projMatrix._31 = -RpL / RmL;
		projMatrix._32 = -TpB / TmB;
		projMatrix._33 = Frustum->Far * InvFmN;
		projMatrix._34 = 1.0f;
		projMatrix._41 = 0.0f;
		projMatrix._42 = 0.0f;
		projMatrix._43 = -(Frustum->Near * Frustum->Far * InvFmN);
		projMatrix._44 = 0.0f;

		WorldViewProjMatrix = worldMatrix * viewMatrix * projMatrix;
		ViewProjMatrix = viewMatrix * projMatrix;
		D3DXMatrixInverse(&InvProj, NULL, &projMatrix);
		InvViewProjMatrix = InvProj * invViewMatrix;

		CameraForward.x = Forward.x;
		CameraForward.y = Forward.y;
		CameraForward.z = Forward.z;
		CameraPosition.x = WorldTranslate->x;
		CameraPosition.y = WorldTranslate->y;
		CameraPosition.z = WorldTranslate->z;
	}

}

void RenderManager::Initialize() {

	IDirect3D9* D3D = NULL;
	D3DDISPLAYMODE currentDisplayMode;

	Logger::Log("Extending the render manager...");
	CameraForward = { 0.0f, 0.0f, 0.0f, 0.0f };
	CameraPosition = { 0.0f, 0.0f, 0.0f, 0.0f };
	BackBuffer = NULL;
	DepthSurface = NULL;
	DepthTexture = NULL;
	DepthTextureINTZ = NULL;
	SaveGameScreenShotRECT = { 0, 0, 256, 144 };
	IsSaveGameScreenShot = false;
	device->CreateTexture(width, height, 1, D3DUSAGE_DEPTHSTENCIL, (D3DFORMAT)MAKEFOURCC('I','N','T','Z'), D3DPOOL_DEFAULT, &DepthTexture, NULL);
	device->GetDirect3D(&D3D);
	D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &currentDisplayMode);
	RESZ = D3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, currentDisplayMode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, (D3DFORMAT)MAKEFOURCC('R','E','S','Z')) == D3D_OK;
	if (RESZ)
		Logger::Log("AMD/Intel detected: RESZ supported.");
	else if (NvAPI_Initialize() == NVAPI_OK)
		Logger::Log("NVIDIA detected: NVAPI supported.");
	else
		Logger::Log("ERROR: Cannot initialize the render manager. Graphics device not supported.");
	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
	BackBuffer = CreateHDRRenderTarget();
}

void RenderManager::ResolveDepthBuffer() {

	if (RESZ) {
		IDirect3DBaseTexture9 *pCurrTX = NULL;
		IDirect3DVertexShader9 *pCurrVS = NULL;
		IDirect3DPixelShader9 *pCurrPS = NULL;
		IDirect3DVertexBuffer9 *pCurrVX = NULL;
		UINT32 dCurrVO;
		UINT32 dCurrVS;
		DWORD dCurrZE;
		DWORD dCurrZW;
		DWORD dCurrCW;
		D3DXVECTOR3 vDummyPoint(0.0f, 0.0f, 0.0f);

		device->GetTexture(0, &pCurrTX);
		device->GetVertexShader(&pCurrVS);
		device->GetPixelShader(&pCurrPS);
		device->GetStreamSource(0, &pCurrVX, &dCurrVO, &dCurrVS);

		device->GetRenderState(D3DRS_ZENABLE, &dCurrZE);
		device->GetRenderState(D3DRS_ZWRITEENABLE, &dCurrZW);
		device->GetRenderState(D3DRS_COLORWRITEENABLE, &dCurrCW);
		device->SetVertexShader(NULL);
		device->SetPixelShader(NULL);
		device->SetFVF(D3DFVF_XYZ);
		device->SetTexture(0, DepthTexture);
		device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, NULL);
		device->DrawPrimitiveUP(D3DPT_POINTLIST, 1, vDummyPoint, sizeof(D3DXVECTOR3));
		device->SetRenderState(D3DRS_ZENABLE, dCurrZE);
		device->SetRenderState(D3DRS_ZWRITEENABLE, dCurrZW);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, dCurrCW);
		device->SetRenderState(D3DRS_POINTSIZE, RESZ_CODE);
		device->SetRenderState(D3DRS_POINTSIZE, NULL);

		device->SetTexture(0, pCurrTX);
		device->SetVertexShader(pCurrVS);
		device->SetPixelShader(pCurrPS);
		device->SetStreamSource(0, pCurrVX, dCurrVO, dCurrVS);
		
		if (pCurrTX) pCurrTX->Release();
		if (pCurrVX) pCurrVX->Release();
	}
	else {
		if (!DepthSurface) {
			D3DSURFACE_DESC desc;
			device->GetDepthStencilSurface(&DepthSurface);
			DepthSurface->GetDesc(&desc);
			if (desc.Format == (D3DFORMAT)MAKEFOURCC('I','N','T','Z')) {
				void *Container = NULL;
				DepthSurface->GetContainer(IID_IDirect3DTexture9, &Container);
				DepthTextureINTZ = (IDirect3DTexture9*)Container;
				NvAPI_D3D9_RegisterResource(DepthTextureINTZ);
			}
			else
				NvAPI_D3D9_RegisterResource(DepthSurface);
			NvAPI_D3D9_RegisterResource(DepthTexture);
		}
		if (!DepthTextureINTZ)
			NvAPI_D3D9_StretchRectEx(device, DepthSurface, NULL, DepthTexture, NULL, D3DTEXF_NONE);
		else
			NvAPI_D3D9_StretchRectEx(device, DepthTextureINTZ, NULL, DepthTexture, NULL, D3DTEXF_NONE);
	}

}

void NiD3DVertexShaderEx::SetupShader(IDirect3DVertexShader9* CurrentVertexHandle) {

	if (ShaderProgE && Player->GetWorldSpace()) {
		ShaderHandle = ShaderProgE->ShaderHandle;
		if (CurrentVertexHandle != ShaderHandle) ShaderProgE->SetCT();
	}
	else if (ShaderProgI && !Player->GetWorldSpace()) {
		ShaderHandle = ShaderProgI->ShaderHandle;
		if (CurrentVertexHandle != ShaderHandle) ShaderProgI->SetCT();
	}
	else if (ShaderProg) {
		ShaderHandle = ShaderProg->ShaderHandle;
		if (CurrentVertexHandle != ShaderHandle) ShaderProg->SetCT();
	}
	else {
		ShaderHandle = ShaderHandleBackup;
	}

}

void NiD3DVertexShaderEx::DisposeShader() {
	
	if (ShaderProgE) delete ShaderProgE; ShaderProgE = NULL;
	if (ShaderProgI) delete ShaderProgI; ShaderProgI = NULL;
	if (ShaderProg) delete ShaderProg; ShaderProg = NULL;

}

void NiD3DPixelShaderEx::SetupShader(IDirect3DPixelShader9* CurrentPixelHandle) {

	if (ShaderProgE && Player->GetWorldSpace()) {
		ShaderHandle = ShaderProgE->ShaderHandle;
		if (CurrentPixelHandle != ShaderHandle) ShaderProgE->SetCT();
	}
	else if (ShaderProgI && !Player->GetWorldSpace()) {
		ShaderHandle = ShaderProgI->ShaderHandle;
		if (CurrentPixelHandle != ShaderHandle) ShaderProgI->SetCT();
	}
	else if (ShaderProg) {
		ShaderHandle = ShaderProg->ShaderHandle;
		if (CurrentPixelHandle != ShaderHandle) ShaderProg->SetCT();
	}
	else {
		ShaderHandle = ShaderHandleBackup;
	}

}

void NiD3DPixelShaderEx::DisposeShader() {
	
	if (ShaderProgE) delete ShaderProgE; ShaderProgE = NULL;
	if (ShaderProgI) delete ShaderProgI; ShaderProgI = NULL;
	if (ShaderProg) delete ShaderProg; ShaderProg = NULL;

}

void DWNode::Create() { 
	
	DWNode* Node = (DWNode*)Pointers::Functions::MemoryAlloc(sizeof(DWNode)); Node->New(2048);

	Node->SetName("Passes...");
	Pointers::Generic::DetectorWindowNode = Node;

}

DWNode* DWNode::Get() {
	
	return (DWNode*)Pointers::Generic::DetectorWindowNode;

}

void DWNode::AddNode(char* Name, NiAVObject* Child0, NiAVObject* Child1) {

	NiNode* Node = (NiNode*)Pointers::Functions::MemoryAlloc(sizeof(NiNode)); Node->New(2);

	Node->SetName(Name);
	Node->m_children.Add(&Child0); // We do not use the AddObject to avoid to alter the original object
	Node->m_children.Add(&Child1); // Same as above
	Pointers::Generic::DetectorWindowNode->AddObject(Node, 1);

}
