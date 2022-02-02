#define WordSampler2D "sampler2D"
#define WordSampler3D "sampler3D"
#define WordSamplerCUBE "samplerCU"
#define WordSamplerDelimeter "};"
#define WordSamplerStateDelimeter ";"
#define WordRegister "register(s"
#define WordRegisterDelimeter ")"
#define WordTextureName "string ResourceName = \x22"
#define WordTextureNameDelimeter "\x22;"

TextureRecord::TextureRecord() {

	Texture = NULL;
	for (int i = 0; i < SamplerStatesMax; i++) SamplerStates[i] = 0;

}

bool TextureRecord::LoadTexture(TextureRecordType Type, const char* Filename) {

	IDirect3DTexture9* Tex = NULL;
	IDirect3DVolumeTexture9* TexV = NULL;
	IDirect3DCubeTexture9* TexC = NULL;

	switch (Type) {
		case PlanarBuffer:
			D3DXCreateTextureFromFileA(TheRenderManager->device, Filename, &Tex);
			if (Tex == NULL) return false;
			Texture = Tex;
			break;
		case VolumeBuffer:
			D3DXCreateVolumeTextureFromFileA(TheRenderManager->device, Filename, &TexV);
			if (TexV == NULL) return false;
			Texture = TexV;
			break;
		case CubeBuffer:
			D3DXCreateCubeTextureFromFileA(TheRenderManager->device, Filename, &TexC);
			if (TexC == NULL) return false;
			Texture = TexC;
			break;
		case SourceBuffer:
			Texture = TheTextureManager->SourceTexture;
			break;
		case RenderedBuffer:
			Texture = TheTextureManager->RenderedTexture;
			break;
		case DepthBuffer:
			Texture = TheTextureManager->DepthTexture;
			break;
		case ShadowMapBufferNear:
			Texture = TheTextureManager->ShadowMapTexture[ShadowManagerBase::ShadowMapTypeEnum::MapNear];
			break;
		case ShadowMapBufferFar:
			Texture = TheTextureManager->ShadowMapTexture[ShadowManagerBase::ShadowMapTypeEnum::MapFar];
			break;
		case OrthoMapBuffer:
			Texture = TheTextureManager->ShadowMapTexture[ShadowManagerBase::ShadowMapTypeEnum::MapOrtho];
			break;
		case ShadowCubeMapBuffer0:
			Texture = TheTextureManager->ShadowCubeMapTexture[0];
			break;
		case ShadowCubeMapBuffer1:
			Texture = TheTextureManager->ShadowCubeMapTexture[1];
			break;
		case ShadowCubeMapBuffer2:
			Texture = TheTextureManager->ShadowCubeMapTexture[2];
			break;
		case ShadowCubeMapBuffer3:
			Texture = TheTextureManager->ShadowCubeMapTexture[3];
			break;
		case WaterHeightMapBuffer:
			Texture = NULL;
			break;
	}	
	return true;

}

void TextureRecord::SetSamplerState(D3DSAMPLERSTATETYPE SamplerType, DWORD Value) {

	SamplerStates[0] = 1;
	SamplerStates[SamplerType] = Value;

}

void TextureManager::Initialize() {

	Logger::Log("Starting the textures manager...");
	TheTextureManager = new TextureManager();
	
	IDirect3DDevice9* Device = TheRenderManager->device;
	UInt32 Width = TheRenderManager->width;
	UInt32 Height = TheRenderManager->height;
	SettingsShadowStruct::ExteriorsStruct* ShadowsExteriors = &TheSettingManager->SettingsShadows.Exteriors;
	SettingsShadowStruct::InteriorsStruct* ShadowsInteriors = &TheSettingManager->SettingsShadows.Interiors;
	UINT ShadowMapSize = 0;
	UINT ShadowCubeMapSize = ShadowsInteriors->ShadowCubeMapSize;

	TheTextureManager->SourceTexture = NULL;
	TheTextureManager->SourceSurface = NULL;
	TheTextureManager->RenderedTexture = NULL;
	TheTextureManager->RenderedSurface = NULL;
	TheTextureManager->DepthTexture = NULL;
	TheTextureManager->DepthSurface = NULL;
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TheTextureManager->SourceTexture, NULL);
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TheTextureManager->RenderedTexture, NULL);
	TheTextureManager->SourceTexture->GetSurfaceLevel(0, &TheTextureManager->SourceSurface);
	TheTextureManager->RenderedTexture->GetSurfaceLevel(0, &TheTextureManager->RenderedSurface);
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_DEPTHSTENCIL, (D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z'), D3DPOOL_DEFAULT, &TheTextureManager->DepthTexture, NULL);
	for (int i = 0; i < 3; i++) {
		ShadowMapSize = ShadowsExteriors->ShadowMapSize[i];
		Device->CreateTexture(ShadowMapSize, ShadowMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &TheTextureManager->ShadowMapTexture[i], NULL);
		TheTextureManager->ShadowMapTexture[i]->GetSurfaceLevel(0, &TheTextureManager->ShadowMapSurface[i]);
		Device->CreateDepthStencilSurface(ShadowMapSize, ShadowMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &TheTextureManager->ShadowMapDepthSurface[i], NULL);
	}
	for (int i = 0; i < ShadowCubeMapsMax; i++) {
		Device->CreateCubeTexture(ShadowCubeMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &TheTextureManager->ShadowCubeMapTexture[i], NULL);
		for (int j = 0; j < 6; j++) {
			TheTextureManager->ShadowCubeMapTexture[i]->GetCubeMapSurface((D3DCUBEMAP_FACES)j, 0, &TheTextureManager->ShadowCubeMapSurface[i][j]);
		}
	}
	Device->CreateDepthStencilSurface(ShadowCubeMapSize, ShadowCubeMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &TheTextureManager->ShadowCubeMapDepthSurface, NULL);
	
}

TextureRecord* TextureManager::LoadTexture(const char* ShaderSource, UInt32 RegisterIndex) {
	
	TextureRecord* NewTextureRecord = NULL;
	char Path[MAX_PATH];
	char Filename[80];
	char Register[3];
	char WordSampler[10];
	char SamplerState[20];
	char SamplerType[2] = { 0 };
	const char* Sampler = NULL;
	const char* SamplerRegister = NULL;
	const char* SamplerParser = NULL;
	const char* Word = NULL;
	std::string WordSamplerType[SamplerStatesMax];
	std::string WordTextureAddress[6];
	std::string WordTextureFilterType[4];
	std::string WordSRGBType[2];
	std::string PathS;
	TextureRecord::TextureRecordType Type = TextureRecord::TextureRecordType::None;

	WordSamplerType[0] = "";
	WordSamplerType[D3DSAMP_ADDRESSU] = "ADDRESSU";
	WordSamplerType[D3DSAMP_ADDRESSV] = "ADDRESSV";
	WordSamplerType[D3DSAMP_ADDRESSW] = "ADDRESSW";
	WordSamplerType[D3DSAMP_BORDERCOLOR] = "BORDERCOLOR";
	WordSamplerType[D3DSAMP_MAGFILTER] = "MAGFILTER";
	WordSamplerType[D3DSAMP_MINFILTER] = "MINFILTER";
	WordSamplerType[D3DSAMP_MIPFILTER] = "MIPFILTER";
	WordSamplerType[D3DSAMP_MIPMAPLODBIAS] = "MIPMAPLODBIAS";
	WordSamplerType[D3DSAMP_MAXMIPLEVEL] = "MAXMIPLEVEL";
	WordSamplerType[D3DSAMP_MAXANISOTROPY] = "MAXANISOTROPY";
	WordSamplerType[D3DSAMP_SRGBTEXTURE] = "SRGBTEXTURE";
	WordTextureAddress[0] = "";
	WordTextureAddress[D3DTADDRESS_WRAP] = "WRAP";
	WordTextureAddress[D3DTADDRESS_MIRROR] = "MIRROR";
	WordTextureAddress[D3DTADDRESS_CLAMP] = "CLAMP";
	WordTextureAddress[D3DTADDRESS_BORDER] = "BORDER";
	WordTextureAddress[D3DTADDRESS_MIRRORONCE] = "MIRRORONCE";
	WordTextureFilterType[D3DTEXF_NONE] = "NONE";
	WordTextureFilterType[D3DTEXF_POINT] = "POINT";
	WordTextureFilterType[D3DTEXF_LINEAR] = "LINEAR";
	WordTextureFilterType[D3DTEXF_ANISOTROPIC] = "ANISOTROPIC";
	WordSRGBType[0] = "FALSE";
	WordSRGBType[1] = "TRUE";

	for (int i = 0; i < 3; i++) {
		if (i == 0) strcpy(WordSampler, WordSampler2D);
		if (i == 1) strcpy(WordSampler, WordSampler3D);
		if (i == 2) strcpy(WordSampler, WordSamplerCUBE);
		Sampler = strstr(ShaderSource, WordSampler);
		while (Sampler) {
			SamplerRegister = strstr(Sampler, WordRegister);
			memset(Register, NULL, sizeof(Register));
			strncpy(Register, SamplerRegister + strlen(WordRegister), strstr(SamplerRegister, WordRegisterDelimeter) - (SamplerRegister + strlen(WordRegister)));
			if (atoi(Register) == RegisterIndex) {
				SamplerParser = strstr(Sampler, WordSourceBuffer);
				if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
					Type = TextureRecord::TextureRecordType::SourceBuffer;
					strcpy(Filename, WordSourceBuffer);
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordRenderedBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::RenderedBuffer;
						strcpy(Filename, WordRenderedBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordDepthBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::DepthBuffer;
						strcpy(Filename, WordDepthBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowMapBufferNear);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowMapBufferNear;
						strcpy(Filename, WordShadowMapBufferNear);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowMapBufferFar);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowMapBufferFar;
						strcpy(Filename, WordShadowMapBufferFar);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordOrthoMapBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::OrthoMapBuffer;
						strcpy(Filename, WordOrthoMapBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer0);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowCubeMapBuffer0;
						strcpy(Filename, WordShadowCubeMapBuffer0);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer1);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowCubeMapBuffer1;
						strcpy(Filename, WordShadowCubeMapBuffer1);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer2);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowCubeMapBuffer2;
						strcpy(Filename, WordShadowCubeMapBuffer2);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer3);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::ShadowCubeMapBuffer3;
						strcpy(Filename, WordShadowCubeMapBuffer3);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordWaterHeightMapBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecord::TextureRecordType::WaterHeightMapBuffer;
						strcpy(Filename, WordWaterHeightMapBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(SamplerRegister, WordTextureName);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						strncpy(SamplerType, Sampler + strlen(WordSampler) - 2, 1);
						if (SamplerType[0] == '2')
							Type = TextureRecord::TextureRecordType::PlanarBuffer;
						else if (SamplerType[0] == '3')
							Type = TextureRecord::TextureRecordType::VolumeBuffer;
						else if (SamplerType[0] == 'C')
							Type = TextureRecord::TextureRecordType::CubeBuffer;
						memset(Filename, NULL, sizeof(Filename));
						strncpy(Filename, SamplerParser + strlen(WordTextureName), strstr(SamplerParser, WordTextureNameDelimeter) - (SamplerParser + strlen(WordTextureName)));
					}
				}
				if (Type >= TextureRecord::TextureRecordType::SourceBuffer && Type <= TextureRecord::TextureRecordType::WaterHeightMapBuffer)
					strcpy(Path, Filename);
				else {
					strcpy(Path, "Data\\Textures\\");
					strcat(Path, Filename);
				}
				PathS = std::string(Path);
				TextureList::iterator t = Textures.find(PathS);
				if (t == Textures.end()) {
					NewTextureRecord = new TextureRecord();
					if (NewTextureRecord->LoadTexture(Type, Path)) {
						Textures[PathS] = NewTextureRecord;
						if (NewTextureRecord->Texture)
							Logger::Log("Texture loaded: %s", Path);
						else
							Logger::Log("Texture attached: %s", Path);
					}
					else
						Logger::Log("ERROR: Cannot load texture %s", Path);
				}
				else {
					NewTextureRecord = t->second;
					Logger::Log("Texture linked: %s", Path);
				}
				SamplerParser = strstr(SamplerRegister, WordRegister);
				for (int s = 1; s < SamplerStatesMax; s++) {
					Word = WordSamplerType[s].c_str();
					SamplerParser = strstr(SamplerRegister, Word);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						memset(SamplerState, NULL, sizeof(SamplerState));
						strncpy(SamplerState, SamplerParser + strlen(Word), strstr(SamplerParser, WordSamplerStateDelimeter) - (SamplerParser + strlen(Word)));
						for (int v = 1; v < 6; v++) {
							Word = WordTextureAddress[v].c_str();
							if (strstr(SamplerState, Word)) {
								NewTextureRecord->SetSamplerState((D3DSAMPLERSTATETYPE)s, v);
								break;
							}
						}
						for (int v = 0; v < 4; v++) {
							Word = WordTextureFilterType[v].c_str();
							if (strstr(SamplerState, Word)) {
								NewTextureRecord->SetSamplerState((D3DSAMPLERSTATETYPE)s, v);
								break;
							}
						}
						for (int v = 0; v < 2; v++) {
							Word = WordSRGBType[v].c_str();
							if (strstr(SamplerState, Word)) {
								NewTextureRecord->SetSamplerState((D3DSAMPLERSTATETYPE)s, v);
								break;
							}
						}
					}
				}
				break;
			}
			Sampler = strstr(SamplerRegister, WordSampler);
		}
		if (Type) break;
	}
	return NewTextureRecord;

}