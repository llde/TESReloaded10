void BinkManager::Initialize() {

	Logger::Log("Starting the bink manager...");
	TheBinkManager = new BinkManager();

	HBINK Bink = NULL;
	BINKTEXTURESET BinkTextures = { NULL };
	Create_Bink_shaders(TheRenderManager->device);

}

void BinkManager::Open(const char* MovieFilename) {
	
	char Filename[MAX_PATH] = { NULL };

	if (Bink) Close();
	GetCurrentDirectoryA(MAX_PATH, Filename);
	strcat(Filename, MovieFilename);
	Bink = BinkOpen(Filename, BINKNOFRAMEBUFFERS);
	if (Bink) {
		BinkSetVolume(Bink, 0, 0);
		BinkGetFrameBuffersInfo(Bink, &BinkTextures.bink_buffers);
		Create_Bink_textures(TheRenderManager->device, &BinkTextures);
	}

}

void BinkManager::Render() {

	IDirect3DBaseTexture9* Texture0 = NULL;
	IDirect3DBaseTexture9* Texture1 = NULL;
	IDirect3DBaseTexture9* Texture2 = NULL;
	bool NewFrame = 0;
	IDirect3DDevice9* Device = TheRenderManager->device;

	if (Bink) {
		if (!BinkWait(Bink)) NewFrame = 1;
		if (NewFrame) {
			Lock_Bink_textures(&BinkTextures);
			BinkRegisterFrameBuffers(Bink, &BinkTextures.bink_buffers);
			BinkDoFrame(Bink);
			Unlock_Bink_textures(Device, &BinkTextures, Bink);
		}
		if (Bink->FrameNum != Bink->Frames) {
			Device->GetTexture(0, &Texture0);
			Device->GetTexture(1, &Texture1);
			Device->GetTexture(2, &Texture2);
			Draw_Bink_textures(Device, &BinkTextures, TheRenderManager->width, TheRenderManager->height, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
			Device->SetTexture(0, Texture0);
			Device->SetTexture(1, Texture1);
			Device->SetTexture(2, Texture2);
		}
		if (NewFrame) BinkNextFrame(Bink);
	}

}

void BinkManager::Close() {

	if (Bink) {
		Free_Bink_textures(TheRenderManager->device, &BinkTextures);
		BinkClose(Bink);
		Bink = NULL;
	}

}
