#include <string>
#include <regex>
#include <algorithm>

#define WordWaterHeightMapBuffer "TESR_WaterHeightMapBuffer"
#define WordWaterReflectionMapBuffer "TESR_WaterReflectionMapBuffer"

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

	// assigning shadow cube maps
	for (int i = 0; i < ShadowCubeMapsMax; i++) {
		if (Type == ShadowCubeMapBuffer0 + i) {
			Texture = TheTextureManager->ShadowCubeMapTexture[i];
			return true;
		}
	}

	// other buffers
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
		case NormalsBuffer:
			Texture = TheTextureManager->NormalsTexture;
			break;
		case ShadowMapBufferNear:
			Texture = TheTextureManager->ShadowMapTextureBlurred[ShadowManager::ShadowMapTypeEnum::MapNear];
			break;
		case ShadowMapBufferMiddle:
			Texture = TheTextureManager->ShadowMapTextureBlurred[ShadowManager::ShadowMapTypeEnum::MapMiddle];
			break;
		case ShadowMapBufferFar:
			Texture = TheTextureManager->ShadowMapTextureBlurred[ShadowManager::ShadowMapTypeEnum::MapFar];
			break;
		case ShadowMapBufferLod:
			Texture = TheTextureManager->ShadowMapTextureBlurred[ShadowManager::ShadowMapTypeEnum::MapLod];
			break;
		case OrthoMapBuffer:
			Texture = TheTextureManager->ShadowMapTexture[ShadowManager::ShadowMapTypeEnum::MapOrtho];
			break;
        default:
            return false; //Texture is invalid or not assigned here.
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
	TheTextureManager->NormalsTexture = NULL;
	TheTextureManager->NormalsSurface = NULL;
	TheTextureManager->DepthTexture = NULL;
	TheTextureManager->DepthSurface = NULL;
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TheTextureManager->SourceTexture, NULL);
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TheTextureManager->RenderedTexture, NULL);
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TheTextureManager->NormalsTexture, NULL);
	TheTextureManager->SourceTexture->GetSurfaceLevel(0, &TheTextureManager->SourceSurface);
	TheTextureManager->RenderedTexture->GetSurfaceLevel(0, &TheTextureManager->RenderedSurface);
	TheTextureManager->NormalsTexture->GetSurfaceLevel(0, &TheTextureManager->NormalsSurface);
	Device->CreateTexture(Width, Height, 1, D3DUSAGE_DEPTHSTENCIL, (D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z'), D3DPOOL_DEFAULT, &TheTextureManager->DepthTexture, NULL);

	for (int i = 0; i <= ShadowManager::ShadowMapTypeEnum::MapOrtho; i++) {
		// create one texture per Exterior ShadowMap type
		float multiple = i == ShadowManager::ShadowMapTypeEnum::MapLod ? 2.0f : 1.0f; // double the size of lod map only
		ShadowMapSize = ShadowsExteriors->ShadowMapResolution * multiple;
		
		Device->CreateTexture(ShadowMapSize, ShadowMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_G32R32F, D3DPOOL_DEFAULT, &TheTextureManager->ShadowMapTexture[i], NULL);
		TheTextureManager->ShadowMapTexture[i]->GetSurfaceLevel(0, &TheTextureManager->ShadowMapSurface[i]);
		Device->CreateDepthStencilSurface(ShadowMapSize, ShadowMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &TheTextureManager->ShadowMapDepthSurface[i], NULL);
        if (i != TheShadowManager->ShadowMapTypeEnum::MapOrtho){ //Don't blur orthomap
            // create a texture to receive the surface contents
			Device->CreateTexture(ShadowMapSize, ShadowMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_G32R32F, D3DPOOL_DEFAULT, &TheTextureManager->ShadowMapTextureBlurred[i], NULL);
            // set the surface level to the texture.
			TheTextureManager->ShadowMapTextureBlurred[i]->GetSurfaceLevel(0, &TheTextureManager->ShadowMapSurfaceBlurred[i]);
        }
    }
	for (int i = 0; i < ShadowCubeMapsMax; i++) {
		Device->CreateCubeTexture(ShadowCubeMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &TheTextureManager->ShadowCubeMapTexture[i], NULL);
		for (int j = 0; j < 6; j++) {
			TheTextureManager->ShadowCubeMapTexture[i]->GetCubeMapSurface((D3DCUBEMAP_FACES)j, 0, &TheTextureManager->ShadowCubeMapSurface[i][j]);
		}
	}

	Device->CreateDepthStencilSurface(ShadowCubeMapSize, ShadowCubeMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &TheTextureManager->ShadowCubeMapDepthSurface, NULL);

}

/*
* Binds texture buffers to a given register name
*/
TextureRecord* TextureManager::LoadTexture(ID3DXBuffer* ShaderSourceBuffer, D3DXPARAMETER_TYPE ConstantType, LPCSTR ConstantName, UINT ConstantIndex, bool* HasRenderedBuffer, bool* HasDepthBuffer) {
	
	TextureRecord::TextureRecordType Type = TextureRecord::TextureRecordType::None;
	std::string Source = std::string((const char*) ShaderSourceBuffer->GetBufferPointer());
	std::string TexturePath;
	Type = (ConstantType >= D3DXPT_SAMPLER && ConstantType <= D3DXPT_SAMPLER2D) ? TextureRecord::TextureRecordType::PlanarBuffer : Type;
	Type = ConstantType == D3DXPT_SAMPLER3D ? TextureRecord::TextureRecordType::VolumeBuffer : Type;
	Type = ConstantType == D3DXPT_SAMPLERCUBE ? TextureRecord::TextureRecordType::CubeBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_SourceBuffer") ? TextureRecord::TextureRecordType::SourceBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_RenderedBuffer") ? TextureRecord::TextureRecordType::RenderedBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_DepthBuffer") ? TextureRecord::TextureRecordType::DepthBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_NormalsBuffer") ? TextureRecord::TextureRecordType::NormalsBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferNear") ? TextureRecord::TextureRecordType::ShadowMapBufferNear : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferMiddle") ? TextureRecord::TextureRecordType::ShadowMapBufferMiddle : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferFar") ? TextureRecord::TextureRecordType::ShadowMapBufferFar : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowMapBufferLod") ? TextureRecord::TextureRecordType::ShadowMapBufferLod : Type;
	Type = !strcmp(ConstantName, "TESR_OrthoMapBuffer") ? TextureRecord::TextureRecordType::OrthoMapBuffer : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer0") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer0 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer1") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer1 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer2") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer2 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer3") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer3 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer4") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer4 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer5") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer5 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer6") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer6 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer7") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer7 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer8") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer8 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer9") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer9 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer10") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer10 : Type;
	Type = !strcmp(ConstantName, "TESR_ShadowCubeMapBuffer11") ? TextureRecord::TextureRecordType::ShadowCubeMapBuffer11 : Type;

	Type = !strcmp(ConstantName, WordWaterHeightMapBuffer) ? TextureRecord::TextureRecordType::WaterHeightMapBuffer : Type;
	Type = !strcmp(ConstantName, WordWaterReflectionMapBuffer) ? TextureRecord::TextureRecordType::WaterReflectionMapBuffer : Type;

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
		size_t StartStatePos = Source.find("{", SamplerPos);
		size_t EndStatePos = Source.find("}", SamplerPos);
		if(EndStatePos == std::string::npos || StartStatePos == std::string::npos) {
			Logger::Log("[ERROR] %s  cannot be binded", ConstantName);
			return nullptr;
		}
		std::string SamplerString = Source.substr(StartStatePos + 1, EndStatePos - StartStatePos - 1);
//		Logger::Log("%s \n", SamplerString.c_str());
		TextureRecord* NewTextureRecord = new TextureRecord();
        if(Type >= TextureRecord::TextureRecordType::WaterHeightMapBuffer){ /*Texture assigned after init*/
            if(Type == TextureRecord::TextureRecordType::WaterHeightMapBuffer){
                NewTextureRecord->Texture = WaterHeightMapB; 
                WaterHeightMapTextures.push_back(NewTextureRecord);
            }
            else if(Type == TextureRecord::TextureRecordType::WaterReflectionMapBuffer){
                NewTextureRecord->Texture = WaterReflectionMapB; 
                WaterHeightMapTextures.push_back(NewTextureRecord);
            }
            Logger::Log("Game Texture %s Attached", ConstantName);
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
			else {
                Logger::Log("ERROR: Cannot bind texture %s", ConstantName);
            }
		}

		GetSamplerStates(SamplerString, NewTextureRecord);
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

std::string ltrim(const std::string& s) {
	return std::regex_replace(s, std::regex("^\\s+"), "");
}
std::string rtrim(const std::string& s) {
	return std::regex_replace(s, std::regex("\\s+$"), "");
}

std::string trim(const std::string& s ) {
	return ltrim(rtrim(s));
}

std::string TextureManager::GetFilenameForTexture(std::string& resourceSubstring){
	std::string PathS;
	if (resourceSubstring.find("ResourceName") != std::string::npos) {
		size_t StartPath = resourceSubstring.find("\"");
		size_t EndPath = resourceSubstring.rfind("\"");
		PathS = trim(resourceSubstring.substr(StartPath + 1, EndPath - 1 - StartPath));
		PathS.insert(0, "Data\\Textures\\");
	}
	else{
		Logger::Log("[ERROR] Cannot parse bindable texture");
	}
	return PathS;
}


void TextureManager::GetSamplerStates(std::string& samplerStateSubstring, TextureRecord* textureRecord ) {
	std::string WordSamplerType[SamplerStatesMax];
	std::string WordTextureAddress[6];
	std::string WordTextureFilterType[4];
	std::string WordSRGBType[2];
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
    WordSamplerType[D3DSAMP_ELEMENTINDEX] = "";
    WordSamplerType[D3DSAMP_DMAPOFFSET] = "";
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

	std::stringstream samplerSettings = std::stringstream(trim(samplerStateSubstring));
	std::string setting;
	while (std::getline(samplerSettings, setting, ';')) {
		size_t newlinePos = setting.find("\n");
		if (newlinePos != std::string::npos) setting.erase(newlinePos, 1);
		std::string opt = trim(setting.substr(0, setting.find("=") - 1));
		std::string val = trim(setting.substr(setting.find("=") + 1, setting.length()));
        std::transform(opt.begin(), opt.end(),opt.begin(), ::toupper);
        std::transform(val.begin(), val.end(),val.begin(), ::toupper);
	//	Logger::Log("%s : %s", opt.c_str(), val.c_str());
		size_t optIdx = 0;
		for (size_t i = 1; i < 12; i++) {
			if (opt == WordSamplerType[i]) {
				optIdx = i;
				break;
			}
		}
		if (optIdx >= D3DSAMP_ADDRESSU && optIdx <= D3DSAMP_ADDRESSW) {
			for (size_t i = 1; i < 6; i++) {
				if (val == WordTextureAddress[i]) {
					textureRecord->SamplerStates[(D3DSAMPLERSTATETYPE)optIdx] = i;
					break;
				}
			}
		}
		else if (optIdx >= D3DSAMP_MAGFILTER && optIdx <= D3DSAMP_MIPFILTER) {
			for (size_t i = 0; i < 4; i++) {
				if (val == WordTextureFilterType[i]) {
					textureRecord->SamplerStates[(D3DSAMPLERSTATETYPE)optIdx] = i;
					break;
				}
			}
		}
		else if (optIdx == D3DSAMP_SRGBTEXTURE) {
			for (size_t i = 0; i < 2; i++) {
				if (val == WordSRGBType[i]) {
					textureRecord->SamplerStates[(D3DSAMPLERSTATETYPE)optIdx] = i;
					break;
				}
			}
		}
		else if(optIdx == D3DSAMP_BORDERCOLOR){
            float va = std::stof(val);
			textureRecord->SamplerStates[(D3DSAMPLERSTATETYPE)optIdx] = *((DWORD*)&va);
        }
		else if(optIdx == D3DSAMP_MAXANISOTROPY){
			textureRecord->SamplerStates[(D3DSAMPLERSTATETYPE)optIdx] = std::stoi(val);
        }
	}
}

void TextureManager::SetWaterHeightMap(IDirect3DBaseTexture9* WaterHeightMap) {
    if (WaterHeightMapB == WaterHeightMap) return;
    WaterHeightMapB = WaterHeightMap;  //This may cause crashes on certain conditions
//    Logger::Log("Binding %0X", WaterHeightMap);
	for (WaterMapList::iterator it = TheTextureManager->WaterHeightMapTextures.begin(); it != TheTextureManager->WaterHeightMapTextures.end(); it++){
		 (*it)->Texture = WaterHeightMap;
	}
}

void TextureManager::SetWaterReflectionMap(IDirect3DBaseTexture9* WaterReflectionMap) {
    if (WaterReflectionMapB == WaterReflectionMap) return;
    WaterReflectionMapB = WaterReflectionMap;
//    Logger::Log("Binding %0X", WaterReflectionMap);
	for (WaterMapList::iterator it = TheTextureManager->WaterReflectionMapTextures.begin(); it != TheTextureManager->WaterReflectionMapTextures.end(); it++){
		 (*it)->Texture = WaterReflectionMap;
	}
}