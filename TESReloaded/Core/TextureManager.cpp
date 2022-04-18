#define WordWaterHeightMapBuffer "TESR_WaterHeightMapBuffer"

TextureRecord::TextureRecord() {

	Texture = NULL;
	SamplerStates[0] = 0; //This isn't used. Just to simplify  the matching between index and meaning
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

bool TextureRecord::LoadTexture(TextureRecordType Type, const char* Name) {

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

TextureRecord* TextureManager::LoadTexture(ID3DXBuffer* ShaderSourceBuffer, D3DXPARAMETER_TYPE ConstantType, LPCSTR ConstantName, UINT ConstantIndex, bool* HasRenderedBuffer, bool* HasDepthBuffer) {
	
	char SamplerValue[40] = { NULL };
	char SamplerState[20];
	const char* ParserStart = NULL;
	const char* ParserEnd = NULL;
	DWORD SamplerStateValue = 0xFFFFFFFF;
	TextureRecord* R = NULL;
	TextureRecord::TextureRecordType Type = TextureRecord::TextureRecordType::None;
	std::string Source = std::string((const char*) ShaderSourceBuffer->GetBufferPointer());
	std::string TexturePath;
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
		size_t SamplerPos = Source.find(("register ( s" + std::to_string(ConstantIndex) + " )"));
		if(SamplerPos == std::string::npos) {
			Logger::Log("[ERROR] %s  cannot be binded", ConstantName);
			return nullptr;
		}
		if(Type >= TextureRecord::TextureRecordType::PlanarBuffer && Type <= TextureRecord::TextureRecordType::CubeBuffer){
			//Only these samplers are bindable to an arbitrary texture
			size_t StartTexture = Source.find("<", SamplerPos +1);
			size_t EndTexture = Source.find(">", SamplerPos +1);
			if(StartTexture == std::string::npos || EndTexture == std::string::npos) {
				Logger::Log("[ERROR] %s  cannot be binded", ConstantName);
				return nullptr;
			}
			std::string TextureString = Source.substr(StartTexture +1, EndTexture - StartTexture - 1);
			TexturePath = GetFilenameForTexture(TextureString);
		}
		size_t StartStatePos = Source.find("sampler_state {", SamplerPos) -1;
		size_t EndStatePos = Source.find("}", SamplerPos) -1;
		if(EndStatePos == std::string::npos || StartStatePos == std::string::npos) {
			Logger::Log("[ERROR] %s  cannot be binded", ConstantName);
			return nullptr;
		}
		std::string SamplerString = Source.substr(StartStatePos + sizeof("sampler_state {"), EndStatePos - StartStatePos - sizeof("sampler_state {"));
//		Logger::Log("%s \n", SamplerString.c_str());
		TextureRecord* NewTextureRecord = new TextureRecord();
	    if(Type == TextureRecord::TextureRecordType::WaterHeightMapBuffer){
			WaterHeightMapTextures.push_back(NewTextureRecord);
			Logger::Log("Game Texture %s Attached", ConstantName); /*WaterHeightMap are provided from a game hook*/
		}
		else if(Type >= TextureRecord::TextureRecordType::PlanarBuffer && Type <= TextureRecord::TextureRecordType::CubeBuffer){ //Cache only non game textures
			IDirect3DBaseTexture9* cached = GetCachedTexture(TexturePath);
			if(!cached) {
				if (NewTextureRecord->LoadTexture(Type, TexturePath.c_str())) {
					if (NewTextureRecord->Texture){
						Logger::Log("Texture loaded: %s", TexturePath.c_str());
						Textures[TexturePath] = NewTextureRecord->Texture;
					}
				}
				else {
					Logger::Log("ERROR: Cannot load texture %s", TexturePath.c_str());
				}
			}
			else {
				NewTextureRecord->Texture = cached;
				Logger::Log("Texture linked: %s", TexturePath.c_str());
			}
		}
		else {
			if (NewTextureRecord->LoadTexture(Type, nullptr)) {
				Logger::Log("Game Texture %s Binded", ConstantName);
			}
		}
		return NewTextureRecord;
	}
	Logger::Log("[ERROR] Sampler %s doesn't have a valid type", ConstantName);
	return nullptr;
}

IDirect3DBaseTexture9* TextureManager::GetCachedTexture(std::string& pathS){
    TextureList::iterator t = Textures.find(pathS);
    if (t == Textures.end()) return nullptr;
    return t->second;
}

std::string TextureManager::GetFilenameForTexture(std::string& resourceSubstring){
	std::string PathS;
	if (resourceSubstring.find("ResourceName") != std::string::npos) {
		size_t StartPath = resourceSubstring.find("\"");
		size_t EndPath = resourceSubstring.rfind("\"");
		PathS = resourceSubstring.substr(StartPath + 1, EndPath - 1 - StartPath);
		PathS.insert(0, "Data\\Textures\\");
	}
	else{
		Logger::Log("[ERROR] Cannot parse bindable texture");
	}
	return PathS;
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
	for (WaterHeightMapList::iterator it = TheTextureManager->WaterHeightMapTextures.begin(); it != TheTextureManager->WaterHeightMapTextures.end(); it++){
		 (*it)->Texture = WaterHeightMap;
	}
}
