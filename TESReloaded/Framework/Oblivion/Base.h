#pragma once

class Hooks {
public:
	static const UInt32 ReadSetting					= 0x004A8800;
	static const UInt32 WriteSetting				= 0x004A85F0;
	static const UInt32 LoadGame					= 0x00465860;
	static const UInt32 NewMain						= 0x00404A00;
	static const UInt32 InitializeRenderer			= 0x004052F0;
	static const UInt32 NewTES						= 0x00441970;
	static const UInt32 NewPlayerCharacter			= 0x0066A740;
	static const UInt32 NewSceneGraph				= 0x004114E0;
	static const UInt32 NewMainDataHandler			= 0x00446D80;
	static const UInt32 NewMenuInterfaceManager		= 0x005802B0;
	static const UInt32 NewQueuedModelLoader		= 0x0043E950;
	static const UInt32 CreateVertexShader			= 0x008014E0;
	static const UInt32 CreatePixelShader			= 0x00801C90;
	static const UInt32 SetShaderPackage			= 0x007B45F0;
	static const UInt32 Render						= 0x0040C830;
	static const UInt32 ProcessImageSpaceShaders	= 0x007B48E0;
	static const UInt32 ShowDetectorWindow			= 0x00496CB0;
	static const UInt32 SetupShaderPrograms			= 0x0077A1F0;
	static const UInt32 EndTargetGroup				= 0x007AAA30;
	static const UInt32 HDRRender					= 0x007BDFC0;
	static const UInt32 WaterHeightMapRender		= 0x007E17D0;
	static const UInt32 FarPlane					= 0x00410EE0;
	static const UInt32 SetSamplerState				= 0x0077B610;
	static const UInt32 RenderReflections			= 0x0049BEF0;
	static const UInt32 WaterCullingProcess			= 0x0049CBF0;
	static const UInt32 SaveGameScreenshot			= 0x00411B70;
	static const UInt32 LoadForm					= 0x00447050;
	static const UInt32 RunScript					= 0x004402F0;
	static const UInt32 NewActorAnimData			= 0x00473EB0;
	static const UInt32 DisposeActorAnimData		= 0x00475B60;
	static const UInt32 AddAnimation				= 0x00474070;
	static const UInt32 AddSingle					= 0x00470BA0;
	static const UInt32 AddMultiple					= 0x00471930;
	static const UInt32 GetAnimGroupSequenceSingle	= 0x00471710;
	static const UInt32 GetAnimGroupSequenceMultiple= 0x00470BF0;
	static const UInt32 NewAnimSequenceMultiple		= 0x00473D90;
	static const UInt32 ApplyActorAnimData			= 0x00471F20;
	static const UInt32 LoadAnimGroup				= 0x0051B490;
	static const UInt32 ToggleCamera				= 0x0066C580;
	static const UInt32 ToggleBody					= 0x00664F70;
	static const UInt32 SetDialogCamera				= 0x0066C6F0;
	static const UInt32 SetAimingZoom				= 0x00666670;
	static const UInt32 UpdateCameraCollisions		= 0x0065F080;
	static const UInt32 NewHighProcess				= 0x00628EE0;
	static const UInt32 ManageItem					= 0x005ABBC0;
	static const UInt32 ProcessAction				= 0x005FCAB0;
	static const UInt32 ProcessControlAttack		= 0x0065E960;
	static const UInt32 AttackHandling				= 0x005FEBF0;
	static const UInt32 GetEquippedWeaponData		= 0x0064B240;
	static const UInt32 SetEquippedWeaponData		= 0x00658550;
	static const UInt32 EquipItem					= 0x00489C30;
	static const UInt32 UnequipItem					= 0x0048A540;
	static const UInt32 EquipWeapon					= 0x004E1900;
	static const UInt32 UnequipWeapon				= 0x004DC5B0;
	static const UInt32 EquipShield					= 0x004E1B40;
	static const UInt32 EquipLight					= 0x004E1C70;
	static const UInt32 UnequipLight				= 0x004DCAB0;
	static const UInt32 GetEquippedLightData		= 0x0064B270;
	static const UInt32 HideEquipment				= 0x005E7230;
	static const UInt32 SaveGame					= 0x00485730;
	static const UInt32 ServeSentence				= 0x00670700;
	static const UInt32 RemoveWornItems				= 0x0064BAC0;
	static const UInt32 ProcessSleepWaitMenu		= 0x005D7090;
	static const UInt32 CloseSleepWaitMenu			= 0x005D6A10;
	static const UInt32 ShowSleepWaitMenu			= 0x0057B420;
	static const UInt32 UpdateFlyCam				= 0x006643A0;
};

class CommandManagerBase {
public:
	
	void RegisterCommands(const PluginInterface* Interface, void* CommandExecuters[], CommandInfo* CommandInfos[], int CommandInfoSize) {

		CommandTableInterface* CommandsInterface = (CommandTableInterface*)Interface->QueryInterface(PluginInterface::kInterface_CommandTable);

		CommandsInterface->GetByName("IsThirdPerson")->execute = CommandExecuters[0];
		Interface->SetOpcodeBase(0x3000);
		for (int i = 0; i < CommandInfoSize; i++) {
			Interface->RegisterCommand(CommandInfos[i]);
		}

	}

};

class SettingManagerBase {
public:

	bool IsMatching(char* Versioning) {

		return Versioning[0] == '1';

	}
	
	void SetTextureAndHDR(TESWeatherEx* WeatherEx, char* UpperLayer, char* LowerLayer, float* HDR) {
		
		WeatherEx->textureLayers[0].ddsPath.Set(UpperLayer);
		WeatherEx->textureLayers[1].ddsPath.Set(LowerLayer);
		memcpy(WeatherEx->hdrInfo, HDR, 0x38);

	}

	void SetWindowedMode(UInt8 Fullscreen) {

		if (!Fullscreen) {
			SafeWrite32(kRectStyle, WS_POPUP);
			SafeWrite32(kWindowStyle, WS_POPUP | WS_VISIBLE);
		}

	}

};

class RenderManagerBase : public NiDX9Renderer {
public:

	IDirect3DSurface9* CreateHDRRenderTarget() {
		
		Ni2DBuffer* Buffer = (Ni2DBuffer*)MemoryAlloc(0x14); *(void**)Buffer = (void*)0x00A8098C; Buffer->m_uiRefCount = 1;
		NiDX92DBufferData* BufferData = (NiDX92DBufferData*)MemoryAlloc(0x10); *(void**)BufferData = (void*)0x00A89818; BufferData->m_uiRefCount = 1; BufferData->ParentData = Buffer;
		Buffer->width = width;
		Buffer->height = height;
		Buffer->data = BufferData;
		device->CreateRenderTarget(width, height, D3DFMT_A16B16G16R16F, (D3DMULTISAMPLE_TYPE)(*SettingMultiSample), 0, false, &BufferData->Surface, NULL);
		defaultRTGroup->RenderTargets[1] = Buffer;
		return defaultRTGroup->RenderTargets[0]->data->Surface;

	}

};

class ShaderManagerBase {
public:

	static int GetShader(const char* Name, NiD3DVertexShader*** Shader, NiD3DVertexShader** AdditionalShader) {

		ShaderDefinition** Shaders = (ShaderDefinition**)0x00B42EC0;
		NiD3DVertexShader** PrecipitationVertexShaders = (NiD3DVertexShader**)0x00B466E0;
		NiD3DPixelShader** PrecipitationPixelShaders = (NiD3DPixelShader**)0x00B46708;
		NiD3DVertexShader** ShadowLightVertexShaders = (NiD3DVertexShader**)0x00B45364;
		NiD3DPixelShader** ShadowLightPixelShaders = (NiD3DPixelShader**)0x00B45144;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			WaterShaderHeightMap* S = (WaterShaderHeightMap*)Shaders[19]->Shader;
			*Shader = &S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "WaterDisplacement")) {
			WaterShaderDisplacement* S = (WaterShaderDisplacement*)Shaders[20]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "Grass")) {
			TallGrassShader* S = (TallGrassShader*)Shaders[2]->Shader;
			*Shader = S->Vertex2;
			Size = sizeof(S->Vertex2) / 4;
		}
		else if (!strcmp(Name, "Precipitations")) {
			*Shader = PrecipitationVertexShaders;
			Size = 4;
		}
		else if (!strcmp(Name, "HDR")) {
			HDRShader* S = (HDRShader*)Shaders[8]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "POM")) {
			ParallaxShader* S = (ParallaxShader*)Shaders[15]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "Skin")) {
			SkinShader* S = (SkinShader*)Shaders[14]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		else if (!strcmp(Name, "Terrain") || !strcmp(Name, "ExtraShaders")) {
			*Shader = ShadowLightVertexShaders;
			Size = 76;
		}
		else if (!strcmp(Name, "Blood")) {
			GeometryDecalShader* S = (GeometryDecalShader*)Shaders[16]->Shader;
			*Shader = S->Vertex;
			Size = sizeof(S->Vertex) / 4;
		}
		return Size;

	}

	static int GetShader(const char* Name, NiD3DPixelShader*** Shader, NiD3DPixelShader** AdditionalShader) {

		ShaderDefinition** Shaders = (ShaderDefinition**)0x00B42EC0;
		NiD3DVertexShader** PrecipitationVertexShaders = (NiD3DVertexShader**)0x00B466E0;
		NiD3DPixelShader** PrecipitationPixelShaders = (NiD3DPixelShader**)0x00B46708;
		NiD3DVertexShader** ShadowLightVertexShaders = (NiD3DVertexShader**)0x00B45364;
		NiD3DPixelShader** ShadowLightPixelShaders = (NiD3DPixelShader**)0x00B45144;
		int Size = 0;

		if (!strcmp(Name, "Water")) {
			WaterShader* S = (WaterShader*)Shaders[17]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "WaterHeightMap")) {
			WaterShaderHeightMap* S = (WaterShaderHeightMap*)Shaders[19]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "WaterDisplacement")) {
			WaterShaderDisplacement* S = (WaterShaderDisplacement*)Shaders[20]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "Grass")) {
			TallGrassShader* S = (TallGrassShader*)Shaders[2]->Shader;
			*Shader = S->Pixel2;
			Size = sizeof(S->Pixel2) / 4;
		}
		else if (!strcmp(Name, "Precipitations")) {
			*Shader = PrecipitationPixelShaders;
			Size = 2;
		}
		else if (!strcmp(Name, "HDR")) {
			HDRShader* S = (HDRShader*)Shaders[8]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "POM")) {
			ParallaxShader* S = (ParallaxShader*)Shaders[15]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "Skin")) {
			SkinShader* S = (SkinShader*)Shaders[14]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		else if (!strcmp(Name, "Terrain")) {
			*Shader = ShadowLightPixelShaders;
			Size = 82;
		}
		else if (!strcmp(Name, "Blood")) {
			GeometryDecalShader* S = (GeometryDecalShader*)Shaders[16]->Shader;
			*Shader = S->Pixel;
			Size = sizeof(S->Pixel) / 4;
		}
		return Size;

	}

};