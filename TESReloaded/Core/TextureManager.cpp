TextureRecord::TextureRecord() {

	Texture = NULL;
	for (int i = 0; i < SamplerStatesMax; i++) SamplerStates[i] = 0;

}

bool TextureRecord::LoadTexture(TextureRecordType Type, const char* Filename) {

	IDirect3DTexture9* Tex = NULL;
	IDirect3DVolumeTexture9* TexV = NULL;
	IDirect3DCubeTexture9* TexC = NULL;

	switch (Type) {
		case TextureRecordType_PlanarBuffer:
			D3DXCreateTextureFromFileA(TheRenderManager->device, Filename, &Tex);
			if (Tex == NULL) return false;
			Texture = Tex;
			break;
		case TextureRecordType_VolumeBuffer:
			D3DXCreateVolumeTextureFromFileA(TheRenderManager->device, Filename, &TexV);
			if (TexV == NULL) return false;
			Texture = TexV;
			break;
		case TextureRecordType_CubeBuffer:
			D3DXCreateCubeTextureFromFileA(TheRenderManager->device, Filename, &TexC);
			if (TexC == NULL) return false;
			Texture = TexC;
			break;
		case TextureRecordType_SourceBuffer:
			Texture = TheShaderManager->SourceTexture;
			break;
		case TextureRecordType_RenderedBuffer:
			Texture = TheShaderManager->RenderedTexture;
			break;
		case TextureRecordType_DepthBuffer:
			Texture = TheRenderManager->DepthTexture;
			break;
		case TextureRecordType_ShadowMapBufferNear:
			Texture = TheShadowManager->ShadowMapTexture[ShadowManager::ShadowMapTypeEnum::MapNear];
			break;
		case TextureRecordType_ShadowMapBufferFar:
			Texture = TheShadowManager->ShadowMapTexture[ShadowManager::ShadowMapTypeEnum::MapFar];
			break;
		case TextureRecordType_OrthoMapBuffer:
			Texture = TheShadowManager->ShadowMapTexture[ShadowManager::ShadowMapTypeEnum::MapOrtho];
			break;
		case TextureRecordType_ShadowCubeMapBuffer0:
			Texture = TheShadowManager->ShadowCubeMapTexture[0];
			break;
		case TextureRecordType_ShadowCubeMapBuffer1:
			Texture = TheShadowManager->ShadowCubeMapTexture[1];
			break;
		case TextureRecordType_ShadowCubeMapBuffer2:
			Texture = TheShadowManager->ShadowCubeMapTexture[2];
			break;
		case TextureRecordType_ShadowCubeMapBuffer3:
			Texture = TheShadowManager->ShadowCubeMapTexture[3];
			break;
		case TextureRecordType_WaterHeightMapBuffer:
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
	TextureRecordType Type = TextureRecordType_None;

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
					Type = TextureRecordType_SourceBuffer;
					strcpy(Filename, WordSourceBuffer);
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordRenderedBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_RenderedBuffer;
						strcpy(Filename, WordRenderedBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordDepthBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_DepthBuffer;
						strcpy(Filename, WordDepthBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowMapBufferNear);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowMapBufferNear;
						strcpy(Filename, WordShadowMapBufferNear);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowMapBufferFar);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowMapBufferFar;
						strcpy(Filename, WordShadowMapBufferFar);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordOrthoMapBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_OrthoMapBuffer;
						strcpy(Filename, WordOrthoMapBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer0);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowCubeMapBuffer0;
						strcpy(Filename, WordShadowCubeMapBuffer0);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer1);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowCubeMapBuffer1;
						strcpy(Filename, WordShadowCubeMapBuffer1);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer2);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowCubeMapBuffer2;
						strcpy(Filename, WordShadowCubeMapBuffer2);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordShadowCubeMapBuffer3);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_ShadowCubeMapBuffer3;
						strcpy(Filename, WordShadowCubeMapBuffer3);
					}
				}
				if (!Type) {
					SamplerParser = strstr(Sampler, WordWaterHeightMapBuffer);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						Type = TextureRecordType_WaterHeightMapBuffer;
						strcpy(Filename, WordWaterHeightMapBuffer);
					}
				}
				if (!Type) {
					SamplerParser = strstr(SamplerRegister, WordTextureName);
					if (SamplerParser && SamplerParser < strstr(Sampler, WordSamplerDelimeter)) {
						strncpy(SamplerType, Sampler + strlen(WordSampler) - 2, 1);
						if (SamplerType[0] == '2')
							Type = TextureRecordType_PlanarBuffer;
						else if (SamplerType[0] == '3')
							Type = TextureRecordType_VolumeBuffer;
						else if (SamplerType[0] == 'C')
							Type = TextureRecordType_CubeBuffer;
						memset(Filename, NULL, sizeof(Filename));
						strncpy(Filename, SamplerParser + strlen(WordTextureName), strstr(SamplerParser, WordTextureNameDelimeter) - (SamplerParser + strlen(WordTextureName)));
					}
				}
				if (Type >= TextureRecordType_SourceBuffer && Type <= TextureRecordType_Max)
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