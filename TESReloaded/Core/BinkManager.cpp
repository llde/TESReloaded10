void BinkManager::Initialize() {

	Logger::Log("Starting the bink manager...");
	TheBinkManager = new BinkManager();
	
	TheBinkManager->VertexDefinition[0] = { 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 };
	TheBinkManager->VertexDefinition[1] = { 0, (4 * sizeof(float)), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };
	TheBinkManager->VertexDefinition[2] = D3DDECL_END();
	TheRenderManager->device->CreateVertexDeclaration(TheBinkManager->VertexDefinition, &TheBinkManager->VertexShaderDeclaration);
	TheBinkManager->Pixel = (ShaderRecordPixel*)ShaderRecord::LoadShader("Bink.pso", NULL);
	TheBinkManager->Bink = NULL;
	TheBinkManager->Textures = { NULL };

}

void BinkManager::CreateTextures() {
	
	IDirect3DDevice9* Device = TheRenderManager->device;
	BINKFRAMEBUFFERS* Buffers = &Textures.Buffers;

    for (int i = 0; i < Buffers->TotalFrames; ++i) {
		if (Buffers->Frames[i].YPlane.Allocate) {
			Device->CreateTexture(Buffers->YABufferWidth, Buffers->YABufferHeight, 1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &Textures.Textures[i].Y, NULL);
			Textures.Textures[i].Ysize = Buffers->YABufferWidth * Buffers->YABufferHeight;
		}
		if (Buffers->Frames[i].cRPlane.Allocate) {
			Device->CreateTexture(Buffers->cRcBBufferWidth, Buffers->cRcBBufferHeight, 1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &Textures.Textures[i].cR, NULL);
			Textures.Textures[i].cRsize = Buffers->cRcBBufferWidth * Buffers->cRcBBufferHeight;
		}
		if (Buffers->Frames[i].cBPlane.Allocate) {
			Device->CreateTexture(Buffers->cRcBBufferWidth, Buffers->cRcBBufferHeight, 1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &Textures.Textures[i].cB, NULL);
			Textures.Textures[i].cBsize = Buffers->cRcBBufferWidth * Buffers->cRcBBufferHeight;
		}
		if (Buffers->Frames[i].APlane.Allocate) {
			Device->CreateTexture(Buffers->YABufferHeight, Buffers->YABufferHeight, 1, 0, D3DFMT_A8, D3DPOOL_MANAGED, &Textures.Textures[i].A, NULL);
			Textures.Textures[i].Asize = Buffers->YABufferWidth * Buffers->YABufferHeight;
		}
    }

}

void BinkManager::LockTextures() {

	BINKFRAMETEXTURES* bt = Textures.Textures;
	BINKFRAMEPLANESET* bp = Textures.Buffers.Frames;
	D3DLOCKED_RECT r;
	UInt32 Flags = 0;

	for (int i = 0; i < Textures.Buffers.TotalFrames; ++i, ++bt, ++bp) {
		Flags = i == Textures.Buffers.FrameNum ? 0 : D3DLOCK_READONLY;
		bt->Y->LockRect(0, &r, NULL, Flags);
		bp->YPlane.Buffer = r.pBits;
		bp->YPlane.BufferPitch = r.Pitch;
		bt->cR->LockRect(0, &r, NULL, Flags);
		bp->cRPlane.Buffer = r.pBits;
		bp->cRPlane.BufferPitch = r.Pitch;
		bt->cB->LockRect(0, &r, NULL, Flags);
		bp->cBPlane.Buffer = r.pBits;
		bp->cBPlane.BufferPitch = r.Pitch;
		if (bt->A) {
			bt->A->LockRect(0, &r, NULL, Flags);
			bp->APlane.Buffer = r.pBits;
			bp->APlane.BufferPitch = r.Pitch;
		}
	}

}

void BinkManager::UnlockTextures() {

	BINKFRAMETEXTURES* bt = Textures.Textures;
	BINKFRAMEPLANESET* bp = Textures.Buffers.Frames;

	for (int i = 0; i < Textures.Buffers.TotalFrames; ++i, ++bt, ++bp) {
		bt->Y->UnlockRect(0);
		bp->YPlane.Buffer = NULL;
		bt->cR->UnlockRect(0);
		bp->cRPlane.Buffer = NULL;
		bt->cB->UnlockRect(0);
		bp->cBPlane.Buffer = NULL;
		if (bt->A) {
			bt->A->UnlockRect(0);
			bp->APlane.Buffer = NULL;
		}
	}

}

void BinkManager::FreeTextures() {

	BINKFRAMETEXTURES* abt[] = { &Textures.Textures[0], &Textures.Textures[1], &Textures.DrawingTextures };
	BINKFRAMETEXTURES* bt;

	for (int i = 0; i < sizeof(abt) / sizeof(*abt); ++i) {
		bt = abt[i];
		if (bt->Y) { bt->Y->Release(); bt->Y = NULL; }
		if (bt->cR) { bt->cR->Release(); bt->cR = NULL; }
		if (bt->cB) { bt->cB->Release(); bt->cB = NULL; }
		if (bt->A) { bt->A->Release(); bt->A = NULL; }
	}

}

void BinkManager::Draw() {

	POS_TC_VERTEX vertices[4];
	float ac[4];
	IDirect3DDevice9* Device = TheRenderManager->device;
	//NiDX9RenderState* RenderState = TheRenderManager->renderState;
	IDirect3DDevice9* RenderState = TheRenderManager->device;
	BINKFRAMEPLANESET* bp = &Textures.Buffers.Frames[Textures.Buffers.FrameNum];
	BINKFRAMETEXTURES* bt = &Textures.Textures[Textures.Buffers.FrameNum];

	ac[0] = 1.0f;
	ac[1] = ac[0];
	ac[2] = ac[0];
	ac[3] = 1.0f;
	RenderState->SetTexture(0, bt->Y);
	RenderState->SetTexture(1, bt->cR);
	RenderState->SetTexture(2, bt->cB);
	for (int i = 0; i < 4; i++) {
		TheRenderManager->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		TheRenderManager->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		TheRenderManager->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_CLAMP);
		TheRenderManager->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		TheRenderManager->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	}
	RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	RenderState->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
	RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
	Device->SetPixelShader(Pixel->ShaderHandle);
	Device->SetVertexDeclaration(VertexShaderDeclaration);
	Device->SetPixelShaderConstantF(0, ac, 1);
	vertices[0].sx = 0.0f;
	vertices[0].sy = 0.0f;
	vertices[0].sz = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].tu = 0.0f;
	vertices[0].tv = 0.0f;
	vertices[1] = vertices[0];
	vertices[1].sx = TheRenderManager->width;
	vertices[1].tu = 1.0f;
	vertices[2] = vertices[0];
	vertices[2].sy = TheRenderManager->height;
	vertices[2].tv = 1.0f;
	vertices[3] = vertices[1];
	vertices[3].sy = vertices[2].sy;
	vertices[3].tv = 1.0f;
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
}

void BinkManager::Render(const char* MovieFilename) {

	IDirect3DBaseTexture9* Texture0 = NULL;
	IDirect3DBaseTexture9* Texture1 = NULL;
	IDirect3DBaseTexture9* Texture2 = NULL;
	bool NewFrame = 0;
	IDirect3DDevice9* Device = TheRenderManager->device;
	char Filename[MAX_PATH] = { NULL };

	if (!Bink) {
		GetCurrentDirectoryA(MAX_PATH, Filename);
		strcat(Filename, MovieFilename);
		Bink = BinkOpen(Filename, BINKNOFRAMEBUFFERS);
		if (Bink) {
			BinkSetVolume(Bink, 0, 0);
			BinkGetFrameBuffersInfo(Bink, &Textures.Buffers);
			CreateTextures();
		}
	}
	if (Bink) {
		if (!BinkWait(Bink)) NewFrame = 1;
		if (NewFrame) {
			LockTextures();
			BinkRegisterFrameBuffers(Bink, &Textures.Buffers);
			BinkDoFrame(Bink);
			UnlockTextures();
		}
		if (Bink->FrameNum != Bink->Frames) {
			Device->GetTexture(0, &Texture0);
			Device->GetTexture(1, &Texture1);
			Device->GetTexture(2, &Texture2);
			Draw();
			Device->SetTexture(0, Texture0);
			Device->SetTexture(1, Texture1);
			Device->SetTexture(2, Texture2);
		}
		if (NewFrame) BinkNextFrame(Bink);
	}

}

void BinkManager::Close() {

	if (Bink) {
		BinkClose(Bink);
		FreeTextures();
		Bink = NULL;
	}

}