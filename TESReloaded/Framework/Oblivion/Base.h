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
	static const UInt32 RenderObject				= 0x0070C0B0;
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
 	static const UInt32 UnkSub7C2420				= 0x007C2420;
    static const UInt32 LoadTextureData             = 0x00760DA0;
    static const UInt32 WaterSurfacePass            = 0x0049D7B0;
};

class Jumpers {
public:
	struct CreateDevice {
		static const UInt32 Hook	= 0x0076A542;
		static const UInt32 Return	= 0x0076A547;
	};
	struct SetRegionEditorName {
		static const UInt32 Hook	= 0x004A32A6;
		static const UInt32 Return	= 0x004A33A6;
	};
	struct SetWeatherEditorName {
		static const UInt32 Hook	= 0x004EE04E;
		static const UInt32 Return	= 0x004EE0EA;
	};
	struct SkipFogPass {
		static const UInt32 Hook	= 0x007AE6F5;
		static const UInt32 Return	= 0x007AE6FB;
	};
	struct DetectorWindow {
		static const UInt32 CreateTreeViewHook		= 0x00495E1F;
		static const UInt32 CreateTreeViewReturn	= 0x00495E27;
		static const UInt32 DumpAttributesHook		= 0x004967C7;
		static const UInt32 DumpAttributesReturn	= 0x004967CD;
		static const UInt32 ConsoleCommandHook		= 0x0040CC6C;
		static const UInt32 ConsoleCommandReturn	= 0x0040CC73;
		static const UInt32 SetNodeName				= 0x0049658E;
	};
	struct RenderInterface {
		static const UInt32 Hook	= 0x0057F3F3;
		static const UInt32 Return	= 0x0057F3F8;
		static const UInt32 Method	= 0x0070E0A0;
	};
	struct HitEvent {
		static const UInt32 Hook	= 0x005FF613;
		static const UInt32 Return	= 0x005FF618;
	};
	struct NewAnimSequenceSingle {
		static const UInt32 Hook	= 0x0047414D;
		static const UInt32 Return	= 0x00474157;
	};
	struct RemoveSequence {
		static const UInt32 Hook	= 0x004742B7;
		static const UInt32 Return1 = 0x004742BF;
		static const UInt32 Return2 = 0x004742CD;
	};
	struct Shadows {
		static const UInt32 RenderShadowMapHook			= 0x0040C919;
		static const UInt32 RenderShadowMapReturn		= 0x0040C920;
		static const UInt32 AddCastShadowFlagHook		= 0x004B1A25;
		static const UInt32 AddCastShadowFlagReturn		= 0x004B1A2A;
		static const UInt32 EditorCastShadowFlagHook	= 0x005498DD;
		static const UInt32 EditorCastShadowFlagReturn	= 0x005498E3;
	};
	struct WaterHeightMap {
		static const UInt32 Hook	= 0x0049D9FA;
		static const UInt32 Return	= 0x0049D9FF;
	};
	struct EndProcess {
		static const UInt32 Hook	= 0x0040F488;
	};
	struct Occlusion {
		static const UInt32 New1CollisionObjectHook			= 0x00564529;
		static const UInt32 New1CollisionObjectReturn		= 0x0056452E;
		static const UInt32 New2CollisionObjectHook			= 0x0089E989;
		static const UInt32 New2CollisionObjectReturn		= 0x0089E98E;
		static const UInt32 New3CollisionObjectHook			= 0x0089EA1C;
		static const UInt32 New3CollisionObjectReturn		= 0x0089EA21;
		static const UInt32 DisposeCollisionObjectHook		= 0x00532DD1;
		static const UInt32 DisposeCollisionObjectReturn	= 0x00532DD8;
		static const UInt32 MaterialPropertyHook			= 0x0089F7C6;
		static const UInt32 MaterialPropertyReturn1			= 0x0089F7CE;
		static const UInt32 MaterialPropertyReturn2			= 0x0089F8A0;
		static const UInt32 CoordinateJackHook				= 0x008A3101;
		static const UInt32 CoordinateJackReturn1			= 0x008A3107;
		static const UInt32 CoordinateJackReturn2			= 0x008A3165;
		static const UInt32 ObjectCullHook					= 0x007073D6;
		static const UInt32 ObjectCullReturn1				= 0x007073DC;
		static const UInt32 ObjectCullReturn2				= 0x007073E7;
	};
	struct Camera {
		static const UInt32 UpdateCameraHook		= 0x0066BE6E;
		static const UInt32 UpdateCameraReturn		= 0x0066BE7C;
		static const UInt32 SwitchCameraHook		= 0x00671AC9;
		static const UInt32 SwitchCameraReturn		= 0x00671AD0;
		static const UInt32 SwitchCameraPOVHook		= 0x00672FDA;
		static const UInt32 SwitchCameraPOVReturn	= 0x00672FE2;
		static const UInt32 HeadTrackingHook		= 0x0055D6A8;
		static const UInt32 HeadTrackingReturn		= 0x0055D6B5;
		static const UInt32 HeadTrackingReturn1		= 0x0055D7E6;
		static const UInt32 SpineTrackingHook		= 0x00603C55;
		static const UInt32 SpineTrackingReturn		= 0x00603C5E;
		static const UInt32 SpineTrackingReturn1	= 0x00603C95;
		static const UInt32 SetReticleOffsetHook	= 0x00580796;
		static const UInt32 SetReticleOffsetReturn	= 0x0058079C;
	};
	struct UpdateGrass {
		static const UInt32 Hook	= 0x004EBF87;
		static const UInt32 Return	= 0x004EC4E8;
	};
	struct Memory {
		static const UInt32 MemReallocHook					= 0x00401E66;
		static const UInt32 MemReallocReturn				= 0x00401EC7;
		static const UInt32 CreateTextureFromFileInMemory	= 0x007610D3;
	};
	struct Equipment {
		static const UInt32 PrnHook							= 0x0047927B;
		static const UInt32 PrnReturn						= 0x0047928A;
		static const UInt32 MenuMouseButtonHook				= 0x0058251B;
		static const UInt32 MenuMouseButtonReturn1			= 0x00582525;
		static const UInt32 MenuMouseButtonReturn2			= 0x0058264F;
		static const UInt32 UnequipTorchHook				= 0x0048A7AD;
		static const UInt32 UnequipTorchReturn				= 0x0048A7B5;
		static const UInt32 EquipItemWornHook				= 0x00489E0A;
		static const UInt32 EquipItemWornReturn				= 0x00489E13;
		static const UInt32 SetWeaponRotationPositionHook	= 0x006563F3;
		static const UInt32 SetWeaponRotationPositionReturn = 0x006563FC;
	};
	struct Mounted {
		static const UInt32 PlayerReadyWeaponHook			= 0x00671E37;
		static const UInt32 ActorReadyWeaponHook			= 0x005FDA4F;
		static const UInt32 ActorReadyWeaponSittingHook		= 0x005FD904;
		static const UInt32 ActorReadyWeaponSittingReturn	= 0x005FD910;
		static const UInt32 PlayerAttackHook				= 0x00672612;
		static const UInt32 PlayerAttackReturn				= 0x0067261F;
		static const UInt32 HittingMountedCreatureHook		= 0x005FF017;
		static const UInt32 HittingMountedCreatureReturn	= 0x005FF01C;
		static const UInt32 BowEquipHook					= 0x004E1AC4;
		static const UInt32 BowEquipReturn					= 0x004E1AC9;
		static const UInt32 AnimControllerHook				= 0x004732F4;
		static const UInt32 AnimControllerReturn1			= 0x004732FA;
		static const UInt32 AnimControllerReturn2			= 0x00473314;
		static const UInt32 HorsePaletteHook				= 0x007165B9;
		static const UInt32 HorsePaletteReturn1				= 0x007165C2;
		static const UInt32 HorsePaletteReturn2				= 0x0071661B;
		static const UInt32 BowUnequipHook					= 0x005F34AB;
		static const UInt32 BowUnequipReturn				= 0x005F34B0;
		static const UInt32 HideWeaponHook					= 0x00654DC8;
		static const UInt32 HideWeaponReturn				= 0x00654E5F;
	};
	struct Dodge {
		static const UInt32 JumpPressedHook		= 0x00672A79;
		static const UInt32 JumpPressedReturn1	= 0x00672A80;
		static const UInt32 JumpPressedReturn2	= 0x00672B94;
		static const UInt32 DoubleTapHook		= 0x006729DA;
		static const UInt32 DoubleTapReturn		= 0x006729EA;
	};
	struct FlyCam {
		static const UInt32 UpdateForwardFlyCamHook		= 0x0066446C;
		static const UInt32 UpdateForwardFlyCamReturn	= 0x0066447A;
		static const UInt32 UpdateBackwardFlyCamHook	= 0x00664489;
		static const UInt32 UpdateBackwardFlyCamReturn	= 0x00664497;
		static const UInt32 UpdateRightFlyCamHook		= 0x006644A6;
		static const UInt32 UpdateRightFlyCamReturn		= 0x006644B4;
		static const UInt32 UpdateLeftFlyCamHook		= 0x006644C3;
		static const UInt32 UpdateLeftFlyCamReturn		= 0x006644D1;
	};
	struct UpdateTimeInfo {
		static const UInt32 Hook	= 0x0040D8AB;
		static const UInt32 Return	= 0x0040D8B0;
	};
};

class CommandManagerBase {
public:
	
	void RegisterCommands(const PluginInterface* Interface, void** CommandExecuters, CommandInfo** CommandInfos, int CommandInfoSize, void** PapyrusCommands) {

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
	
	void SetTextureAndHDR(TESWeatherEx* WeatherEx, char* UpperLayer, char* LowerLayer, float* HDR) {
		
		WeatherEx->textureLayers[0].ddsPath.Set(UpperLayer);
		WeatherEx->textureLayers[1].ddsPath.Set(LowerLayer);
		memcpy(WeatherEx->hdrInfo, HDR, 0x38);

	}

	void SetWindowedMode(UInt8 Fullscreen) {

		if (!Fullscreen) {
			SafeWrite32(0x0040E7C0, WS_POPUP);
			SafeWrite32(0x0040E805, WS_POPUP | WS_VISIBLE);
		}

	}

};

class RenderManagerBase : public NiDX9Renderer {
public:

	IDirect3DSurface9* CreateHDRRenderTarget() {
        if (*Pointers::Settings::MultiSample >= 2) {
            Ni2DBuffer* Buffer = (Ni2DBuffer*)Pointers::Functions::MemoryAlloc(0x14); *(void**)Buffer = (void*)0x00A8098C; Buffer->m_uiRefCount = 1;
            NiDX92DBufferData* BufferData = (NiDX92DBufferData*)Pointers::Functions::MemoryAlloc(0x10); *(void**)BufferData = (void*)0x00A89818; BufferData->m_uiRefCount = 1; BufferData->ParentData = Buffer;
            Buffer->width = width;
            Buffer->height = height;
            Buffer->data = BufferData;
            device->CreateRenderTarget(width, height, D3DFMT_A16B16G16R16F, (D3DMULTISAMPLE_TYPE)(*Pointers::Settings::MultiSample), 0, false, &BufferData->Surface, NULL);
            defaultRTGroup->RenderTargets[1] = Buffer;
            return defaultRTGroup->RenderTargets[0]->data->Surface;
        }
        return NULL;
	}
};

class ShaderManagerBase {
public:

	static int GetShader(const char* Name, NiD3DVertexShader*** Shader, NiD3DVertexShader** AdditionalShader, int AdditionalShaderSize) {

		ShaderDefinition** Shaders = (ShaderDefinition**)0x00B42EC0;
		NiD3DVertexShader** PrecipitationVertexShaders = (NiD3DVertexShader**)0x00B466E0;
		NiD3DVertexShader** ShadowLightVertexShaders = (NiD3DVertexShader**)0x00B45364;
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
        else if (!strcmp(Name, "NightEye")) {
            NightEyeShader* NS = (NightEyeShader*)Shaders[18]->Shader;
            *Shader = NS->Vertex;
            Size = 1;
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

	static int GetShader(const char* Name, NiD3DPixelShader*** Shader, NiD3DPixelShader** AdditionalShader, int AdditionalShaderSize) {

		ShaderDefinition** Shaders = (ShaderDefinition**)0x00B42EC0;
		NiD3DPixelShader** PrecipitationPixelShaders = (NiD3DPixelShader**)0x00B46708;
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
		else if (!strcmp(Name, "NightEye")) {
            NightEyeShader* NS = (NightEyeShader*)Shaders[18]->Shader;
            *Shader = NS->Pixel;
            Size = 1;
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
		else if (!strcmp(Name, "Terrain") || !strcmp(Name, "ExtraShaders")) {
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

