#define WordWaterHeightMapBuffer "TESR_WaterHeightMapBuffer"

TextureRecord::TextureRecord() {

	Texture = NULL;
	SamplerStates[0] = 0;
	SamplerStates[D3DSAMP_ADDRESSU] = D3DTADDRESS_WRAP;
	SamplerStates[D3DSAMP_ADDRESSV] = D3DTADDRESS_WRAP;
	SamplerStates[D3DSAMP_ADDRESSW] = D3DTADDRESS_WRAP;
	SamplerStates[D3DSAMP_BORDERCOLOR] = 0;
	SamplerStates[D3DSAMP_MAGFILTER] = D3DTEXF_POINT;
	SamplerStates[D3DSAMP_MINFILTER] = D3DTEXF_POINT;
	SamplerStates[D3DSAMP_MIPFILTER] = D3DTEXF_NONE;
	SamplerStates[D3DSAMP_MIPMAPLODBIAS] = 0;
	SamplerStates[D3DSAMP_MAXMIPLEVEL] = 0;
	SamplerStates[D3DSAMP_MAXANISOTROPY] = 1;
	SamplerStates[D3DSAMP_SRGBTEXTURE] = 0;

}

bool TextureRecord::LoadTexture(TextureRecordType Type) {

	IDirect3DTexture9* Tex = NULL;
	IDirect3DVolumeTexture9* TexV = NULL;
	IDirect3DCubeTexture9* TexC = NULL;

	switch (Type) {
		case PlanarBuffer:
			D3DXCreateTextureFromFileA(TheRenderManager->device, Name, &Tex);
			if (Tex == NULL) return false;
			Texture = Tex;
			break;
		case VolumeBuffer:
			D3DXCreateVolumeTextureFromFileA(TheRenderManager->device, Name, &TexV);
			if (TexV == NULL) return false;
			Texture = TexV;
			break;
		case CubeBuffer:
			D3DXCreateCubeTextureFromFileA(TheRenderManager->device, Name, &TexC);
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

TextureRecord* TextureManager::LoadTexture(const char* ShaderSource, D3DXPARAMETER_TYPE ConstantType, LPCSTR ConstantName, UINT ConstantIndex, bool* HasRenderedBuffer, bool* HasDepthBuffer) {
	
	char SamplerValue[40] = { NULL };
	char SamplerState[20];
	const char* ParserStart = NULL;
	const char* ParserEnd = NULL;
	DWORD SamplerStateValue = 0xFFFFFFFF;
	TextureRecord* R = NULL;
	TextureRecord::TextureRecordType Type = TextureRecord::TextureRecordType::None;
	TextureRecord* NewTextureRecord = new TextureRecord();

	Type = (ConstantType >= D3DXPT_SAMPLER && ConstantType <= D3DXPT_SAMPLER2D) ? TextureRecord::TextureRecordType::PlanarBuffer : Type;
	Type = ConstantType == D3DXPT_SAMPLER3D ? TextureRecord::TextureRecordType::VolumeBuffer : Type;
	Type = ConstantType == D3DXPT_SAMPLERCUBE ? TextureRecord::TextureRecordType::CubeBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_SourceBuffer") ? TextureRecord::TextureRecordType::SourceBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_RenderedBuffer") ? TextureRecord::TextureRecordType::RenderedBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_DepthBuffer") ? TextureRecord::TextureRecordType::DepthBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferNear") ? TextureRecord::TextureRecordType::ShadowMapBufferNear : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferFar") ? TextureRecord::TextureRecordType::ShadowMapBufferFar : Type;
	Type = !strcmp(ConstantName, "TESR_OrthoMapBuffer") ? TextureRecord::TextureRecordType::OrthoMapBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer0") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer0 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer1") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer1 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer2") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer2 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer3") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer3 : Type;
	Type = !strcmp(ConstantName, WordWaterHeightMapBuffer) ? TextureRecord::TextureRecordType::WaterHeightMapBuffer : Type;
	if (HasRenderedBuffer && !*HasRenderedBuffer) *HasRenderedBuffer = (Type == TextureRecord::TextureRecordType::RenderedBuffer);
	if (HasDepthBuffer && !*HasDepthBuffer) *HasDepthBuffer = (Type == TextureRecord::TextureRecordType::DepthBuffer);
	if (Type) {
		sprintf(SamplerState, "samplerState%i {", ConstantIndex);
		ParserStart = strstr(ShaderSource, SamplerState); if (ParserStart) ParserEnd = strstr(ParserStart, "}");
		if (Type <= TextureRecord::TextureRecordType::CubeBuffer) {
			GetSamplerStateValue(0, ParserStart, ParserEnd, SamplerValue);
			strcpy(NewTextureRecord->Name, "Data\\Textures\\");
			strcat(NewTextureRecord->Name, SamplerValue);
		}
		else {
			strcpy(NewTextureRecord->Name, ConstantName);
		}
		R = Textures.find(NewTextureRecord->Name);
		if (!R) {
			if (NewTextureRecord->LoadTexture(Type)) {
				if (NewTextureRecord->Texture) Logger::Log("Texture loaded: %s", NewTextureRecord->Name); else Logger::Log("Texture attached: %s", NewTextureRecord->Name);
			}
			else {
				Logger::Log("ERROR: Cannot load texture %s", NewTextureRecord->Name);
			}
		}
		else {
			NewTextureRecord->Texture = R->Texture;
			Logger::Log("Texture linked: %s", NewTextureRecord->Name);
		}
		for (int i = 1; i < SamplerStatesMax; i++) {
			memset(SamplerValue, NULL, sizeof(SamplerValue));
			SamplerStateValue = GetSamplerStateValue(i, ParserStart, ParserEnd, SamplerValue);
			if (SamplerStateValue != 0xFFFFFFFF) NewTextureRecord->SamplerStates[i] = SamplerStateValue;
		}
		Textures.push_back(NewTextureRecord);
	}
	return NewTextureRecord;

}

DWORD TextureManager::GetSamplerStateValue(UInt32 SamplerType, const char* ParserStart, const char* ParserEnd, char* SamplerValue) {

	const char* WordSamplerType[SamplerStatesMax] = { NULL };
	const char* WordTextureAddress[6] = { NULL };
	const char* WordTextureFilter[4] = { NULL };
	const char* WordRGB[2] = { NULL };
	const char* Parser = NULL;
	DWORD R = 0xFFFFFFFF;
	
	WordSamplerType[0] = "TEXTURE = ";
	WordSamplerType[D3DSAMP_ADDRESSU] = "ADDRESSU = ";
	WordSamplerType[D3DSAMP_ADDRESSV] = "ADDRESSV = ";
	WordSamplerType[D3DSAMP_ADDRESSW] = "ADDRESSW = ";
	WordSamplerType[D3DSAMP_BORDERCOLOR] = "BORDERCOLOR = ";
	WordSamplerType[D3DSAMP_MAGFILTER] = "MAGFILTER = ";
	WordSamplerType[D3DSAMP_MINFILTER] = "MINFILTER = ";
	WordSamplerType[D3DSAMP_MIPFILTER] = "MIPFILTER = ";
	WordSamplerType[D3DSAMP_MIPMAPLODBIAS] = "MIPMAPLODBIAS = ";
	WordSamplerType[D3DSAMP_MAXMIPLEVEL] = "MAXMIPLEVEL = ";
	WordSamplerType[D3DSAMP_MAXANISOTROPY] = "MAXANISOTROPY = ";
	WordSamplerType[D3DSAMP_SRGBTEXTURE] = "SRGBTEXTURE = ";
	WordTextureAddress[0] = "";
	WordTextureAddress[D3DTADDRESS_WRAP] = "WRAP";
	WordTextureAddress[D3DTADDRESS_MIRROR] = "MIRROR";
	WordTextureAddress[D3DTADDRESS_CLAMP] = "CLAMP";
	WordTextureAddress[D3DTADDRESS_BORDER] = "BORDER";
	WordTextureAddress[D3DTADDRESS_MIRRORONCE] = "MIRRORONCE";
	WordTextureFilter[D3DTEXF_NONE] = "NONE";
	WordTextureFilter[D3DTEXF_POINT] = "POINT";
	WordTextureFilter[D3DTEXF_LINEAR] = "LINEAR";
	WordTextureFilter[D3DTEXF_ANISOTROPIC] = "ANISOTROPIC";
	WordRGB[0] = "FALSE";
	WordRGB[1] = "TRUE";

	if (ParserStart && ParserEnd) {
		Parser = strstr(ParserStart, WordSamplerType[SamplerType]);
		if (Parser && Parser < ParserEnd) strncpy(SamplerValue, Parser + strlen(WordSamplerType[SamplerType]), strstr(Parser, ";") - (Parser + strlen(WordSamplerType[SamplerType])));
		if (strlen(SamplerValue) > 0) {
			if (SamplerType == 0) {
				R = 0;
			}
			else if (SamplerType >= D3DSAMP_ADDRESSU && SamplerType <= D3DSAMP_ADDRESSW) {
				for (int i = 1; i < 6; i++) {
					if (!strcmp(SamplerValue, WordTextureAddress[i])) {
						R = i;
						break;
					}
				}
			}
			else if (SamplerType >= D3DSAMP_MAGFILTER && SamplerType <= D3DSAMP_MIPFILTER) {
				for (int i = 0; i < 4; i++) {
					if (!strcmp(SamplerValue, WordTextureFilter[i])) {
						R = i;
						break;
					}
				}
			}
			else if (SamplerType == D3DSAMP_SRGBTEXTURE) {
				for (int i = 0; i < 2; i++) {
					if (!strcmp(SamplerValue, WordRGB[i])) {
						R = i;
						break;
					}
				}
			}
			else {
				R = atoi(SamplerValue);
			}
		}
	}
	return R;

}

void TextureManager::SetWaterHeightMap(IDirect3DBaseTexture9* WaterHeightMap) {
	
	for (TextureList::iterator Iter = Textures.begin(); Iter != Textures.end(); ++Iter) {
		if (!strcmp((*Iter)->Name, WordWaterHeightMapBuffer)) (*Iter)->Texture = WaterHeightMap;
	}

}