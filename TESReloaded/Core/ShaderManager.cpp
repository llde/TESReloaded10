
/*
* Constructor of Animator class. Starts an animator for a given value.
*/
Animator::Animator() {
	time = TimeGlobals::Get();
	startValue = 0;
	endValue = 0;
	startTime = 0;
	endTime = 0;
	running = false;
	switched = false;
};


Animator::~Animator() {
};


void Animator::Initialize(float value) {
	startValue = value;
	endValue = value;
}

/*
* Starts the animator by setting a target value and a duration to reach it.
*/
void Animator::Start(float duration, float finalValue) {
	float currenttime = time->GameHour->data;

	startTime = currenttime;
	endTime = currenttime + duration;
	running = true;

	startValue = endValue;
	endValue = finalValue;
}


/*
* Gets the value for the animated value at the current time.
*/
float Animator::GetValue() {
	float currenttime = time->GameHour->data;
	if (!running) return startValue;
	
	if (currenttime > endTime) {
		running = false;
		startValue = endValue;
		return endValue;
	}

	running = true;
	currenttime = ShaderManager::invLerp(startTime, endTime, currenttime);
	return ShaderManager::lerp(startValue, endValue, currenttime);
};


ShaderProgram::ShaderProgram() {

	FloatShaderValues = NULL;
	TextureShaderValues = NULL;
	FloatShaderValuesCount = 0;
	TextureShaderValuesCount = 0;

}

ShaderProgram::~ShaderProgram() {

	if (FloatShaderValues) free(FloatShaderValues);
	if (TextureShaderValues) free(TextureShaderValues);

}

/* 
Declares the constants that can be accessed from the shader code from the Constant Table, and gives them a readable name.
*/
void ShaderProgram::SetConstantTableValue(LPCSTR Name, UInt32 Index) {
	
	if (!strcmp(Name, "TESR_ToneMapping"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.HDR.ToneMapping;
	else if (!strcmp(Name, "TESR_ParallaxData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.POM.ParallaxData;
	else if (!strcmp(Name, "TESR_GrassScale"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Grass.Scale;
	else if (!strcmp(Name, "TESR_TerrainData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Terrain.Data;
	else if (!strcmp(Name, "TESR_SkinData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Skin.SkinData;
	else if (!strcmp(Name, "TESR_SkinColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Skin.SkinColor;
	else if (!strcmp(Name, "TESR_ShadowData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Shadow.Data;
	else if (!strcmp(Name, "TESR_ShadowScreenSpaceData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Shadow.ScreenSpaceData;
	else if (!strcmp(Name, "TESR_ShadowRadius"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.ShadowMap.ShadowMapRadius;
	else if (!strcmp(Name, "TESR_OrthoData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Shadow.OrthoData;
	else if (!strcmp(Name, "TESR_RainData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Rain.RainData;
	else if (!strcmp(Name, "TESR_SnowData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Snow.SnowData;
	else if (!strcmp(Name, "TESR_WorldTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->worldMatrix;
	else if (!strcmp(Name, "TESR_ViewTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->viewMatrix;
	else if (!strcmp(Name, "TESR_ProjectionTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->projMatrix;
	else if (!strcmp(Name, "TESR_InvProjectionTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->InvProjMatrix;
	else if (!strcmp(Name, "TESR_WorldViewProjectionTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->WorldViewProjMatrix;
	else if (!strcmp(Name, "TESR_InvViewProjectionTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->InvViewProjMatrix;
	else if (!strcmp(Name, "TESR_ViewProjectionTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheRenderManager->ViewProjMatrix;
	else if (!strcmp(Name, "TESR_ViewSpaceLightDir"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ViewSpaceLightDir;
	else if (!strcmp(Name, "TESR_ScreenSpaceLightDir"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ScreenSpaceLightDir;
	else if (!strcmp(Name, "TESR_ShadowWorldTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowWorld;
	else if (!strcmp(Name, "TESR_ShadowViewProjTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowViewProj;
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight;
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransformNear"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight[0];
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransformMiddle"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight[1];
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransformFar"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight[2];
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransformLod"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight[3];
	else if (!strcmp(Name, "TESR_ShadowCameraToLightTransformOrtho"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowCameraToLight[4];
	else if (!strcmp(Name, "TESR_ShadowCubeMapLightPosition"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.ShadowMap.ShadowCubeMapLightPosition;
	else if (!strcmp(Name, "TESR_ShadowLightPosition"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition;
	else if (!strcmp(Name, "TESR_ShadowLightPosition0"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[0];
	else if (!strcmp(Name, "TESR_ShadowLightPosition1"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[1];
	else if (!strcmp(Name, "TESR_ShadowLightPosition2"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[2];
	else if (!strcmp(Name, "TESR_ShadowLightPosition3"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[3];
	else if (!strcmp(Name, "TESR_ShadowLightPosition4"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[4];
	else if (!strcmp(Name, "TESR_ShadowLightPosition5"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[5];
	else if (!strcmp(Name, "TESR_ShadowLightPosition6"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[6];
	else if (!strcmp(Name, "TESR_ShadowLightPosition7"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[7];
	else if (!strcmp(Name, "TESR_ShadowLightPosition8"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[8];
	else if (!strcmp(Name, "TESR_ShadowLightPosition9"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[9];
	else if (!strcmp(Name, "TESR_ShadowLightPosition10"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[10];
	else if (!strcmp(Name, "TESR_ShadowLightPosition11"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowMap.ShadowLightPosition[11];
	else if (!strcmp(Name, "TESR_LightPosition0"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[0];
	else if (!strcmp(Name, "TESR_LightPosition1"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[1];
	else if (!strcmp(Name, "TESR_LightPosition2"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[2];
	else if (!strcmp(Name, "TESR_LightPosition3"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[3];
	else if (!strcmp(Name, "TESR_LightPosition4"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[4];
	else if (!strcmp(Name, "TESR_LightPosition5"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[5];
	else if (!strcmp(Name, "TESR_LightPosition6"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[6];
	else if (!strcmp(Name, "TESR_LightPosition7"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightPosition[7];
	else if (!strcmp(Name, "TESR_LightAttenuation0"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[0];
	else if (!strcmp(Name, "TESR_LightAttenuation1"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[1];
	else if (!strcmp(Name, "TESR_LightAttenuation2"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[2];
	else if (!strcmp(Name, "TESR_LightAttenuation3"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[3];
	else if (!strcmp(Name, "TESR_LightAttenuation4"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[4];
	else if (!strcmp(Name, "TESR_LightAttenuation5"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[5];
	else if (!strcmp(Name, "TESR_LightAttenuation6"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[6];
	else if (!strcmp(Name, "TESR_LightAttenuation7"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->LightAttenuation[7];
	else if (!strcmp(Name, "TESR_ShadowCubeMapBlend"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.ShadowMap.ShadowCubeMapBlend;
	else if (!strcmp(Name, "TESR_OcclusionWorldViewProjTransform"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.OcclusionMap.OcclusionWorldViewProj;
	else if (!strcmp(Name, "TESR_ReciprocalResolution"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.ReciprocalResolution;
	else if (!strcmp(Name, "TESR_CameraForward"))
		FloatShaderValues[Index].Value = &TheRenderManager->CameraForward;
	else if (!strcmp(Name, "TESR_DepthConstants"))
		FloatShaderValues[Index].Value = &TheRenderManager->DepthConstants;
	else if (!strcmp(Name, "TESR_CameraData"))
		FloatShaderValues[Index].Value = &TheRenderManager->CameraData;
	else if (!strcmp(Name, "TESR_CameraPosition"))
		FloatShaderValues[Index].Value = &TheRenderManager->CameraPosition;
	else if (!strcmp(Name, "TESR_SunDirection"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.SunDir;
	else if (!strcmp(Name, "TESR_SunTiming"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.SunTiming;
	else if (!strcmp(Name, "TESR_SunAmount"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.SunAmount;
	else if (!strcmp(Name, "TESR_ShadowFade"))
		FloatShaderValues[Index].Value = (D3DXVECTOR4*)&TheShaderManager->ShaderConst.ShadowFade;
	else if (!strcmp(Name, "TESR_GameTime"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.GameTime;
	else if (!strcmp(Name, "TESR_WaterCoefficients"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.waterCoefficients;
	else if (!strcmp(Name, "TESR_WaveParams"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.waveParams;
	else if (!strcmp(Name, "TESR_WaterVolume"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.waterVolume;
	else if (!strcmp(Name, "TESR_WaterSettings"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.waterSettings;
	else if (!strcmp(Name, "TESR_WaterDeepColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.deepColor;
	else if (!strcmp(Name, "TESR_WaterShallowColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.shallowColor;
	else if (!strcmp(Name, "TESR_WaterShorelineParams"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Water.shorelineParams;
	else if (!strcmp(Name, "TESR_FogColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.fogColor;
	else if (!strcmp(Name, "TESR_HorizonColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.horizonColor;
	else if (!strcmp(Name, "TESR_SunColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.sunColor;
	else if (!strcmp(Name, "TESR_SkyColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.skyColor;
	else if (!strcmp(Name, "TESR_SunAmbient"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.sunColor;
	else if (!strcmp(Name, "TESR_FogData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.fogData;
	else if (!strcmp(Name, "TESR_FogDistance"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.fogDistance;
	else if (!strcmp(Name, "TESR_AmbientOcclusionAOData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.AmbientOcclusion.AOData;
	else if (!strcmp(Name, "TESR_AmbientOcclusionData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.AmbientOcclusion.Data;
	else if (!strcmp(Name, "TESR_BloodLensParams"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.BloodLens.Params;
	else if (!strcmp(Name, "TESR_BloodLensColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.BloodLens.BloodColor;
	else if (!strcmp(Name, "TESR_BloomData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Bloom.BloomData;
	else if (!strcmp(Name, "TESR_BloomValues"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Bloom.BloomValues;
	else if (!strcmp(Name, "TESR_CinemaData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Cinema.Data;
	else if (!strcmp(Name, "TESR_CinemaSettings"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Cinema.Settings;
	else if (!strcmp(Name, "TESR_ColoringColorCurve"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Coloring.ColorCurve;
	else if (!strcmp(Name, "TESR_ColoringEffectGamma"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Coloring.EffectGamma;
	else if (!strcmp(Name, "TESR_ColoringData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Coloring.Data;
	else if (!strcmp(Name, "TESR_ColoringValues"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Coloring.Values;
	else if (!strcmp(Name, "TESR_DepthOfFieldBlur"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.DepthOfField.Blur;
	else if (!strcmp(Name, "TESR_DepthOfFieldData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.DepthOfField.Data;
	else if (!strcmp(Name, "TESR_GodRaysRay"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.GodRays.Ray;
	else if (!strcmp(Name, "TESR_GodRaysRayColor"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.GodRays.RayColor;
	else if (!strcmp(Name, "TESR_GodRaysData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.GodRays.Data;
	else if (!strcmp(Name, "TESR_LowHFData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.LowHF.Data;
	else if (!strcmp(Name, "TESR_MotionBlurParams"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.MotionBlur.BlurParams;
	else if (!strcmp(Name, "TESR_MotionBlurData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.MotionBlur.Data;
	else if (!strcmp(Name, "TESR_SharpeningData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Sharpening.Data;
	else if (!strcmp(Name, "TESR_SpecularData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Specular.Data;
	else if (!strcmp(Name, "TESR_SpecularEffects"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.Specular.EffectStrength;
	else if (!strcmp(Name, "TESR_SnowAccumulationParams"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.SnowAccumulation.Params;
	else if (!strcmp(Name, "TESR_VolumetricFogData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.VolumetricFog.Data;
	else if (!strcmp(Name, "TESR_WaterLensData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.WaterLens.Time;
	else if (!strcmp(Name, "TESR_WetWorldCoeffs"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.WetWorld.Coeffs;
	else if (!strcmp(Name, "TESR_WetWorldData"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.WetWorld.Data;
	else if (!strcmp(Name, "TESR_DebugVar"))
		FloatShaderValues[Index].Value = &TheShaderManager->ShaderConst.DebugVar;
	else {
		Logger::Log("Custom constant found: %s", Name);
		D3DXVECTOR4 v; v.x = v.y = v.z = v.w = 0.0f;
		TheShaderManager->CustomConst[Name] = v;
		FloatShaderValues[Index].Value = &TheShaderManager->CustomConst[Name];
	}
}

ShaderRecord::ShaderRecord() {
	
	HasRenderedBuffer = false;
	HasDepthBuffer = false;

}
ShaderRecord::~ShaderRecord() { }

/**
* @param fileBin the name of the compiled shader file
* @param fileHlsl the name of the hlsl source file for this shader
* @param CompileStatus an integer for the status of the compilation. If set to 2, will compare file dates to return status. 
* @returns wether the shader should be compiled, from a given binary shader and corresponding hlsl.
*/
bool ShaderProgram::ShouldCompileShader(const char* fileBin, const char* fileHlsl, ShaderCompileType CompileStatus){
	if(CompileStatus == ShaderCompileType::AlwaysOn) return  true;
	if(CompileStatus == ShaderCompileType::AlwaysOff) return  false;

	if(CompileStatus == ShaderCompileType::RecompileInMenu) return TheShaderManager->IsMenuSwitch ? true : false;

	if(CompileStatus == ShaderCompileType::RecompileChanged) {
		WIN32_FILE_ATTRIBUTE_DATA attributesBin = {0};
		WIN32_FILE_ATTRIBUTE_DATA attributesSource = {0};
		BOOL hr = GetFileAttributesExA(fileBin, GetFileExInfoStandard, &attributesBin); // from winbase.h
		if(hr == FALSE) {
// 			Logger::Log("File %s not present, compile", fileHlsl);
			return true; //File not present compile
		}
		else{
			BOOL hr = GetFileAttributesExA(fileHlsl, GetFileExInfoStandard, &attributesSource); // from winbase.h
			if(hr == FALSE) {
//				Logger::Log("[ERROR] Can't open source %s", fileHlsl);
				return true; //BOH
			}

			ULARGE_INTEGER timeBin, timeSource;
			timeBin.LowPart = attributesBin.ftLastWriteTime.dwLowDateTime;
			timeBin.HighPart = attributesBin.ftLastWriteTime.dwHighDateTime;
			timeSource.LowPart = attributesSource.ftLastWriteTime.dwLowDateTime;
			timeSource.HighPart = attributesSource.ftLastWriteTime.dwHighDateTime;

			if(timeBin.QuadPart < timeSource.QuadPart){
				Logger::Log("Binary older then source, compile %s", fileHlsl);
				return true;
			}
		}
	}
	return false;
}

/* 
Loads the shader by name from a given subfolder (optionally). Shader will be compiled if needed.
@returns the ShaderRecord for this shader.
*/
ShaderRecord* ShaderRecord::LoadShader(const char* Name, const char* SubPath) {
	
	ShaderRecord* ShaderProg = NULL;
	ID3DXBuffer* ShaderSource = NULL;
	ID3DXBuffer* Shader = NULL;
	ID3DXBuffer* Errors = NULL;
	ID3DXConstantTable* ConstantTable = NULL;
	void* Function = NULL;
	UInt32 SourceSize = 0;
	char ShaderProfile[7];
	char FileName[MAX_PATH];
	char FileNameBinary[MAX_PATH];

	strcpy(FileName, ShadersPath);
	if (!memcmp(Name, "WATER", 5)) {
		if (!TheSettingManager->SettingsMain.Shaders.Water) return false;
	}
	else if (!memcmp(Name, "GRASS", 5)) {
		if (!TheSettingManager->SettingsMain.Shaders.Grass) return false;
	}
	else if (!memcmp(Name, "HDR", 3) || !memcmp(Name, "ISHDR", 5)) {
		// load tonemapping shaders, with different names between New vegas and Oblivion
		if (!TheSettingManager->SettingsMain.Shaders.HDR) return false;
	}
	else if (!memcmp(Name, "PAR", 3)) {
		if (!TheSettingManager->SettingsMain.Shaders.POM) return false;
	}
	else if (!memcmp(Name, "SKIN", 4)) {
		if (!TheSettingManager->SettingsMain.Shaders.Skin) return false;
	}
	else if (strstr(TerrainShaders, Name)) {
		if (!TheSettingManager->SettingsMain.Shaders.Terrain) return false;
	}
	else if (strstr(BloodShaders, Name)) {
		if (!TheSettingManager->SettingsMain.Shaders.Blood) return false;
	}
	else if (!memcmp(Name, "NIGHTEYE", 8)) {
		if (!TheSettingManager->SettingsMain.Shaders.NightEye) return false;
	}
	else if (!memcmp(Name, "Shadow", 6)) {
		strcat(FileName, "Shadows\\");
	}
	else if (!memcmp(Name, "Occlusion", 9)) {
		strcat(FileName, "Occlusion\\");
	}
	else if (!memcmp(Name, "Bink", 4)) {
		strcat(FileName, "Bink\\");
	}
	else if(!TheSettingManager->SettingsMain.Shaders.Extra) return false;
    
	if (SubPath) strcat(FileName, SubPath);
	strcat(FileName, Name);
	strcpy(FileNameBinary, FileName);
	strcat(FileName, ".hlsl");

    HRESULT prepass = D3DXPreprocessShaderFromFileA(FileName, NULL, NULL, &ShaderSource , &Errors);
	bool Compile = ShouldCompileShader(FileNameBinary, FileName, (ShaderCompileType) TheSettingManager->SettingsMain.Develop.CompileShaders);
	if (prepass == D3D_OK) {
		if (strstr(Name, ".vso"))
			strcpy(ShaderProfile, "vs_3_0");
		else if (strstr(Name, ".pso"))
			strcpy(ShaderProfile, "ps_3_0");
		if (Compile) {
			D3DXCompileShaderFromFileA(FileName, NULL, NULL, "main", ShaderProfile, NULL, &Shader, &Errors, &ConstantTable);
			if (Errors) Logger::Log((char*)Errors->GetBufferPointer());
			if (Shader) {
				Function = Shader->GetBufferPointer();
				std::ofstream FileBinary(FileNameBinary, std::ios::out | std::ios::binary);
				FileBinary.write((const char*)Function, Shader->GetBufferSize());
				FileBinary.flush();
				FileBinary.close();
				Logger::Log("Shader compiled: %s", FileName);
			}
		}
		else {
			std::ifstream FileBinary(FileNameBinary, std::ios::in | std::ios::binary | std::ios::ate);
			if (FileBinary.is_open()) {
				std::streamoff Size = FileBinary.tellg();
				D3DXCreateBuffer(Size, &Shader);
				FileBinary.seekg(0, std::ios::beg);
				Function = Shader->GetBufferPointer();
				FileBinary.read((char*)Function, Size);
				FileBinary.close();
				D3DXGetShaderConstantTable((const DWORD*)Function, &ConstantTable);
			}
			else {
				Logger::Log("ERROR: Shader %s not found. Try to enable the CompileShader option to recompile the shaders.", FileNameBinary);
			}
		}
		if (Shader) {
			if (ShaderProfile[0] == 'v') {
				ShaderProg = new ShaderRecordVertex();
				TheRenderManager->device->CreateVertexShader((const DWORD*)Function, &((ShaderRecordVertex*)ShaderProg)->ShaderHandle);
			}
			else {
				ShaderProg = new ShaderRecordPixel();
				TheRenderManager->device->CreatePixelShader((const DWORD*)Function, &((ShaderRecordPixel*)ShaderProg)->ShaderHandle);
			}
			ShaderProg->CreateCT(ShaderSource, ConstantTable);
			Logger::Log("Shader loaded: %s", FileNameBinary);
		}
	}
	else {
		if (Errors) Logger::Log((char*)Errors->GetBufferPointer());
	}

	if (ShaderSource) ShaderSource->Release();
	if (Shader) Shader->Release();
	if (Errors) Errors->Release();
	return ShaderProg;

}

/**
* Creates the constants table for the Shader.
* @param ShaderSource
* @param ConstantTable
*/
void ShaderRecord::CreateCT(ID3DXBuffer* ShaderSource, ID3DXConstantTable* ConstantTable) {

	D3DXCONSTANTTABLE_DESC ConstantTableDesc;
	D3DXCONSTANT_DESC ConstantDesc;
	D3DXHANDLE Handle;
	UINT ConstantCount = 1;
	UInt32 FloatIndex = 0;
	UInt32 TextureIndex = 0;

	ConstantTable->GetDesc(&ConstantTableDesc);
    for (UINT c = 0; c < ConstantTableDesc.Constants; c++) {
		Handle = ConstantTable->GetConstant(NULL, c);
		ConstantTable->GetConstantDesc(Handle, &ConstantDesc, &ConstantCount);
		if (ConstantDesc.RegisterSet == D3DXRS_FLOAT4 && !memcmp(ConstantDesc.Name, "TESR_", 5)) FloatShaderValuesCount += 1;
		if (ConstantDesc.RegisterSet == D3DXRS_SAMPLER && !memcmp(ConstantDesc.Name, "TESR_", 5)) TextureShaderValuesCount += 1;
    }
	if (FloatShaderValuesCount) FloatShaderValues = (ShaderValue*)malloc(FloatShaderValuesCount * sizeof(ShaderValue));
	if (TextureShaderValuesCount) TextureShaderValues = (ShaderValue*)malloc(TextureShaderValuesCount * sizeof(ShaderValue));
	for (UINT c = 0; c < ConstantTableDesc.Constants; c++) {
		Handle = ConstantTable->GetConstant(NULL, c);
		ConstantTable->GetConstantDesc(Handle, &ConstantDesc, &ConstantCount);
		if (!memcmp(ConstantDesc.Name, "TESR_", 5)) {
			switch (ConstantDesc.RegisterSet) {
				case D3DXRS_FLOAT4:
					SetConstantTableValue(ConstantDesc.Name, FloatIndex);
					FloatShaderValues[FloatIndex].RegisterIndex = ConstantDesc.RegisterIndex;
					FloatShaderValues[FloatIndex].RegisterCount = ConstantDesc.RegisterCount;
					FloatIndex++;
 					break;
				case D3DXRS_SAMPLER:
					TextureShaderValues[TextureIndex].Texture = TheTextureManager->LoadTexture(ShaderSource, ConstantDesc.Type, ConstantDesc.Name, ConstantDesc.RegisterIndex, &HasRenderedBuffer, &HasDepthBuffer);
					TextureShaderValues[TextureIndex].RegisterIndex = ConstantDesc.RegisterIndex;
					TextureShaderValues[TextureIndex].RegisterCount = 1;
					TextureIndex++;
					break;
			}
		}
	}

}

/* 
* Sets the Constant Table for the shader
*/
void ShaderRecord::SetCT() {
	
	ShaderValue* Value;

	if (HasRenderedBuffer) TheRenderManager->device->StretchRect(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, NULL, TheTextureManager->RenderedSurface, NULL, D3DTEXF_NONE);
	if (HasDepthBuffer) TheRenderManager->ResolveDepthBuffer();
	for (UInt32 c = 0; c < TextureShaderValuesCount; c++) {
		Value = &TextureShaderValues[c];
		if (Value->Texture->Texture) TheRenderManager->renderState->SetTexture(Value->RegisterIndex, Value->Texture->Texture);
		for (int i = 1; i < SamplerStatesMax; i++) {
			TheRenderManager->SetSamplerState(Value->RegisterIndex, (D3DSAMPLERSTATETYPE)i, Value->Texture->SamplerStates[i]);
		}
	}
	for (UInt32 c = 0; c < FloatShaderValuesCount; c++) {
		Value = &FloatShaderValues[c];
		SetShaderConstantF(Value->RegisterIndex, Value->Value, Value->RegisterCount);
	}

}

ShaderRecordVertex::ShaderRecordVertex() {
	
	ShaderHandle = NULL;

}

ShaderRecordVertex::~ShaderRecordVertex() {

	ShaderHandle->Release();

}

ShaderRecordPixel::ShaderRecordPixel() {
	
	ShaderHandle = NULL;

}

ShaderRecordPixel::~ShaderRecordPixel() {
	
	ShaderHandle->Release();

}

void ShaderRecordVertex::SetShaderConstantF(UInt32 RegisterIndex, D3DXVECTOR4* Value, UInt32 RegisterCount) {
	
	TheRenderManager->device->SetVertexShaderConstantF(RegisterIndex, (const float*)Value, RegisterCount);

}

void ShaderRecordPixel::SetShaderConstantF(UInt32 RegisterIndex, D3DXVECTOR4* Value, UInt32 RegisterCount) {
	
	TheRenderManager->device->SetPixelShaderConstantF(RegisterIndex, (const float*)Value, RegisterCount);

}

/*
* Class that wraps an effect shader, in order to load it/render it/set constants.
*/
EffectRecord::EffectRecord() {

	Enabled = false;
	Effect = NULL;

}
/*Shader Values arrays are freed in the superclass Destructor*/
EffectRecord::~EffectRecord() {
	if (Effect) Effect->Release();
	delete Path;
	delete SourcePath;
}

/*
 * Unload effects, allowing it to be reloaded from  a blank state.
 */
void EffectRecord::DisposeEffect(){
	if (Effect) Effect->Release();
	Effect = nullptr;
	if (FloatShaderValues) free(FloatShaderValues);
	FloatShaderValues = nullptr;
	if (TextureShaderValues) free(TextureShaderValues);
	TextureShaderValues = nullptr;
	Enabled = false;
}

/*
 * Compile and Load the Effect shader
 */
bool EffectRecord::LoadEffect(bool alwaysCompile){
	ID3DXBuffer* ShaderSource = NULL;
	ID3DXBuffer* Errors = NULL;
	ID3DXEffect* Effect = NULL;
	bool success = false;
    HRESULT prepass = D3DXPreprocessShaderFromFileA(SourcePath->data(), NULL, NULL, &ShaderSource , &Errors);
	ID3DXEffectCompiler* Compiler = NULL;
	ID3DXBuffer* EffectBuffer = NULL;
	if(alwaysCompile || ShouldCompileShader(Path->data(), SourcePath->data(), (ShaderCompileType)TheSettingManager->SettingsMain.Develop.CompileEffects) ){
		HRESULT comp  = D3DXCreateEffectCompilerFromFileA(SourcePath->data(), NULL, NULL, NULL, &Compiler, &Errors);
		if(FAILED(comp)) goto cleanup;
		if (Errors){
			Logger::Log((char*)Errors->GetBufferPointer());
			Errors->Release();
			Errors = nullptr;
		}

		HRESULT compiled = Compiler->CompileEffect(NULL, &EffectBuffer, &Errors);
		if(FAILED(compiled)) goto cleanup;
		if (Errors){
			Logger::Log((char*)Errors->GetBufferPointer());
			Errors->Release();
			Errors = nullptr;
		}

		if (EffectBuffer) {
			std::ofstream FileBinary(Path->data(), std::ios::out | std::ios::binary);
			FileBinary.write((char*)EffectBuffer->GetBufferPointer(), EffectBuffer->GetBufferSize());
			FileBinary.flush();
			FileBinary.close();
			Logger::Log("Effect compiled: %s", SourcePath->data());
		}
	}
	HRESULT load = D3DXCreateEffectFromFileA(TheRenderManager->device, Path->data(), NULL, NULL, NULL, NULL, &Effect, &Errors);
	if(FAILED(load)) goto cleanup;
	
	if (Errors) Logger::Log((char*)Errors->GetBufferPointer()); // LAst can be cleaned in the cleanup section
	if (Effect) {
		this->Effect = Effect;
		CreateCT(ShaderSource, NULL); //Recreate CT;
		Logger::Log("Effect loaded: %s", Path->data());
	}

	success = true;
cleanup:
	if (EffectBuffer) EffectBuffer->Release();
	if (Compiler) Compiler->Release();

	if (ShaderSource) ShaderSource->Release();
	if (Errors){
		Logger::Log((char*)Errors->GetBufferPointer());
		Errors->Release();
	}
	return success;
}
/**
* Loads an effect shader by name (The post process effects stored in the Effects folder)
* @param Name the name for the effect
* @returns an EffectRecord describing the effect shader.
*/
EffectRecord* EffectRecord::LoadEffect(const char* Name) {
	
	char FileName[MAX_PATH];

	strcpy(FileName, Name);
	strcat(FileName, ".hlsl");
	EffectRecord* EffectProg = new EffectRecord();
	EffectProg->Path = new std::string(Name); //TODO pass them to constructor for clean code 
	EffectProg->SourcePath = new std::string(FileName);
	EffectProg->LoadEffect();
	return EffectProg;
}

bool EffectRecord::IsLoaded(){
	return Effect != nullptr; 
}

/**
Creates the Constant Table for the Effect Record. 
*/
void EffectRecord::CreateCT(ID3DXBuffer* ShaderSource, ID3DXConstantTable* ConstantTable) {

	D3DXEFFECT_DESC ConstantTableDesc;
	D3DXPARAMETER_DESC ConstantDesc;
	D3DXHANDLE Handle;
	UINT ConstantCount = 1;
	UInt32 FloatIndex = 0;
	UInt32 TextureIndex = 0;

	Effect->GetDesc(&ConstantTableDesc);
	for (UINT c = 0; c < ConstantTableDesc.Parameters; c++) {
		Handle = Effect->GetParameter(NULL, c);
		Effect->GetParameterDesc(Handle, &ConstantDesc);
		if ((ConstantDesc.Class == D3DXPC_VECTOR || ConstantDesc.Class == D3DXPC_MATRIX_ROWS) && !memcmp(ConstantDesc.Name, "TESR_", 5)) FloatShaderValuesCount += 1;
		if (ConstantDesc.Class == D3DXPC_OBJECT && ConstantDesc.Type >= D3DXPT_SAMPLER && ConstantDesc.Type <= D3DXPT_SAMPLERCUBE && !memcmp(ConstantDesc.Name, "TESR_", 5)) TextureShaderValuesCount += 1;
	}
	if (FloatShaderValuesCount) FloatShaderValues = (ShaderValue*)malloc(FloatShaderValuesCount * sizeof(ShaderValue));
	if (TextureShaderValuesCount) TextureShaderValues = (ShaderValue*)malloc(TextureShaderValuesCount * sizeof(ShaderValue));
	for (UINT c = 0; c < ConstantTableDesc.Parameters; c++) {
		Handle = Effect->GetParameter(NULL, c);
		Effect->GetParameterDesc(Handle, &ConstantDesc);
		if (!memcmp(ConstantDesc.Name, "TESR_", 5)) {
			switch (ConstantDesc.Class) {
				case D3DXPC_VECTOR:
				case D3DXPC_MATRIX_ROWS:
					SetConstantTableValue(ConstantDesc.Name, FloatIndex);
					FloatShaderValues[FloatIndex].RegisterIndex = (UInt32)Handle;
					FloatShaderValues[FloatIndex].RegisterCount = ConstantDesc.Rows;
					FloatIndex++;
					break;
				case D3DXPC_OBJECT:
					if (ConstantDesc.Class == D3DXPC_OBJECT && ConstantDesc.Type >= D3DXPT_SAMPLER && ConstantDesc.Type <= D3DXPT_SAMPLERCUBE) {
						TextureShaderValues[TextureIndex].Texture = TheTextureManager->LoadTexture(ShaderSource, ConstantDesc.Type, ConstantDesc.Name, TextureIndex, NULL, NULL);
						TextureShaderValues[TextureIndex].RegisterIndex = TextureIndex;
						TextureShaderValues[TextureIndex].RegisterCount = 1;
						TextureIndex++;
					}
					break;
			}
		}
	}

}

/*
*Sets the Effect Shader constants table and texture registers.
*/
void EffectRecord::SetCT() {

	ShaderValue* Value;
	if (!Enabled || Effect == nullptr) return;
	for (UInt32 c = 0; c < TextureShaderValuesCount; c++) {
		Value = &TextureShaderValues[c];
		if (Value->Texture->Texture) TheRenderManager->device->SetTexture(Value->RegisterIndex, Value->Texture->Texture);
		for (int i = 1; i < SamplerStatesMax; i++) {
			TheRenderManager->SetSamplerState(Value->RegisterIndex, (D3DSAMPLERSTATETYPE)i, Value->Texture->SamplerStates[i]);
		}
	}
	for (UInt32 c = 0; c < FloatShaderValuesCount; c++) {
		Value = &FloatShaderValues[c];
		if (Value->RegisterCount == 1)
			Effect->SetVector((D3DXHANDLE)Value->RegisterIndex, Value->Value);
		else
			Effect->SetMatrix((D3DXHANDLE)Value->RegisterIndex, (D3DXMATRIX*)Value->Value);
	}

}

/*
 * Enable or Disable Effect, with reloading it if it's changed on disk
 */
void EffectRecord::SwitchEffect(){
	bool change = true;
	if (!IsLoaded() || (!Enabled && ShouldCompileShader(Path->data(), SourcePath->data(), ShaderCompileType::RecompileChanged)) ) {
		DisposeEffect();
		change = LoadEffect(true);
	}
	if(change) Enabled = !Enabled;
}

/**
* Renders the given effect shader.
*/
void EffectRecord::Render(IDirect3DDevice9* Device, IDirect3DSurface9* RenderTarget, IDirect3DSurface9* RenderedSurface, bool ClearRenderTarget) {

	UINT Passes;
	if (!Enabled || Effect == nullptr) return;
	Effect->Begin(&Passes, NULL);
	for (UINT p = 0; p < Passes; p++) {
		if (ClearRenderTarget) Device->Clear(0L, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0L);
		Effect->BeginPass(p);
		Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		Effect->EndPass();
		Device->StretchRect(RenderTarget, NULL, RenderedSurface, NULL, D3DTEXF_NONE);
	}
	Effect->End();
}

/**
* Initializes the Shader Manager Singleton.
* The Shader Manager creates and holds onto the Effects activated in the Settings Manager, and sets the constants.
*/
void ShaderManager::Initialize() {

	Logger::Log("Starting the shaders manager...");
	TheShaderManager = new ShaderManager();

	TheShaderManager->FrameVertex = NULL;
	TheShaderManager->UnderwaterEffect = NULL;
	TheShaderManager->WaterLensEffect = NULL;
	TheShaderManager->GodRaysEffect = NULL;
	TheShaderManager->DepthOfFieldEffect = NULL;
	TheShaderManager->AmbientOcclusionEffect = NULL;
	TheShaderManager->ColoringEffect = NULL;
	TheShaderManager->CinemaEffect = NULL;
	TheShaderManager->BloomEffect = NULL;
	TheShaderManager->SnowAccumulationEffect = NULL;
	TheShaderManager->BloodLensEffect = NULL;
	TheShaderManager->MotionBlurEffect = NULL;
	TheShaderManager->LowHFEffect = NULL;
	TheShaderManager->WetWorldEffect = NULL;
	TheShaderManager->SharpeningEffect = NULL;
	TheShaderManager->SpecularEffect = NULL;
	TheShaderManager->VolumetricFogEffect = NULL;
	TheShaderManager->RainEffect = NULL;
	TheShaderManager->SnowEffect = NULL;
	TheShaderManager->NormalsEffect = NULL;
	TheShaderManager->ShadowsExteriorsEffect = NULL;
	TheShaderManager->ShadowsInteriorsEffect = NULL;
	memset(TheShaderManager->WaterVertexShaders, NULL, sizeof(WaterVertexShaders));
	memset(TheShaderManager->WaterPixelShaders, NULL, sizeof(WaterPixelShaders));
	TheShaderManager->InitializeConstants();
	TheShaderManager->ShaderConst.ReciprocalResolution.x = 1.0f / (float)TheRenderManager->width;
	TheShaderManager->ShaderConst.ReciprocalResolution.y = 1.0f / (float)TheRenderManager->height;
	TheShaderManager->ShaderConst.ReciprocalResolution.z = (float)TheRenderManager->width / (float)TheRenderManager->height;
	TheShaderManager->ShaderConst.ReciprocalResolution.w = 0.0f; // Reserved to store the FoV
	TheShaderManager->CreateFrameVertex(TheRenderManager->width, TheRenderManager->height, &TheShaderManager->FrameVertex);

    TheShaderManager->PreviousCell = nullptr;
    TheShaderManager->IsMenuSwitch = false;

}

void ShaderManager::CreateFrameVertex(UInt32 Width, UInt32 Height, IDirect3DVertexBuffer9** FrameVertex) {
	
	void* VertexData = NULL;
	float OffsetX = (1.0f / (float)Width) * 0.5f;
	float OffsetY = (1.0f / (float)Height) * 0.5f;
	
	FrameVS FrameVertices[] = {
		{ -1.0f,  1.0f, 1.0f, 0.0f + OffsetX, 0.0f + OffsetY },
		{ -1.0f, -1.0f, 1.0f, 0.0f + OffsetX, 1.0f + OffsetY },
		{  1.0f,  1.0f, 1.0f, 1.0f + OffsetX, 0.0f + OffsetY },
		{  1.0f, -1.0f, 1.0f, 1.0f + OffsetX, 1.0f + OffsetY }
	};
	TheRenderManager->device->CreateVertexBuffer(4 * sizeof(FrameVS), D3DUSAGE_WRITEONLY, FrameFVF, D3DPOOL_DEFAULT, FrameVertex, NULL);
	(*FrameVertex)->Lock(0, 0, &VertexData, NULL);
	memcpy(VertexData, FrameVertices, sizeof(FrameVertices));
	(*FrameVertex)->Unlock();

}

/*
* Initializes the Effect Record for each effect activated in the settings.
*/
void ShaderManager::CreateEffects() {
	
	SettingsMainStruct::EffectsStruct* Effects = &TheSettingManager->SettingsMain.Effects;
	CreateEffect(EffectRecord::EffectRecordType::AmbientOcclusion);
	CreateEffect(EffectRecord::EffectRecordType::BloodLens);
	CreateEffect(EffectRecord::EffectRecordType::Bloom);
	CreateEffect(EffectRecord::EffectRecordType::Cinema);
	CreateEffect(EffectRecord::EffectRecordType::Coloring);
	CreateEffect(EffectRecord::EffectRecordType::DepthOfField);
	CreateEffect(EffectRecord::EffectRecordType::GodRays);
	CreateEffect(EffectRecord::EffectRecordType::LowHF);
	CreateEffect(EffectRecord::EffectRecordType::MotionBlur);
	CreateEffect(EffectRecord::EffectRecordType::Sharpening);
	CreateEffect(EffectRecord::EffectRecordType::SnowAccumulation);
	CreateEffect(EffectRecord::EffectRecordType::Underwater);
	CreateEffect(EffectRecord::EffectRecordType::VolumetricFog);
	CreateEffect(EffectRecord::EffectRecordType::WaterLens);
	CreateEffect(EffectRecord::EffectRecordType::WetWorld);
	CreateEffect(EffectRecord::EffectRecordType::Rain);
	CreateEffect(EffectRecord::EffectRecordType::Snow);
	CreateEffect(EffectRecord::EffectRecordType::ShadowsExteriors);
	CreateEffect(EffectRecord::EffectRecordType::ShadowsInteriors);
	CreateEffect(EffectRecord::EffectRecordType::Specular);
	CreateEffect(EffectRecord::EffectRecordType::Normals);
//	CreateEffect(EffectRecord::EffectRecordType::Extra);

	NormalsEffect->Enabled = true;
	if (Effects->AmbientOcclusion) AmbientOcclusionEffect->Enabled = true;
	if (Effects->BloodLens) BloodLensEffect->Enabled = true;
	if (Effects->Bloom) BloomEffect->Enabled = true;
	if (Effects->Cinema) CinemaEffect->Enabled = true;
	if (Effects->Coloring) ColoringEffect->Enabled = true;
	if (Effects->DepthOfField) DepthOfFieldEffect->Enabled = true;
	if (Effects->GodRays) GodRaysEffect->Enabled = true;
	if (Effects->LowHF) LowHFEffect->Enabled = true;
	if (Effects->MotionBlur) MotionBlurEffect->Enabled = true;
	if (Effects->Sharpening) SharpeningEffect->Enabled = true;
	if (Effects->SnowAccumulation) SnowAccumulationEffect->Enabled = true;
	if (Effects->Underwater) UnderwaterEffect->Enabled = true;
	if (Effects->VolumetricFog) VolumetricFogEffect->Enabled = true;
	if (Effects->WaterLens) WaterLensEffect->Enabled = true;
	if (Effects->WetWorld) WetWorldEffect->Enabled = true;
	if (Effects->Rain) RainEffect->Enabled = true;
	if (Effects->Snow) SnowEffect->Enabled = true;
	if (Effects->ShadowsExteriors) ShadowsExteriorsEffect->Enabled = true;
	if (Effects->ShadowsInteriors) ShadowsInteriorsEffect->Enabled = true;
	if (Effects->Specular) SpecularEffect->Enabled = true;
		
	/*TODO*/
	if (Effects->Extra) CreateEffect(EffectRecord::EffectRecordType::Extra);

}

void ShaderManager::InitializeConstants() {

	ShaderConst.pWeather = NULL;
	ShaderConst.WaterLens.Percent = 0.0f;
	ShaderConst.BloodLens.Percent = 0.0f;
	ShaderConst.SnowAccumulation.Params.w = 0.0f;
	ShaderConst.WetWorld.Data.x = 0.0f;
	ShaderConst.WetWorld.Data.y = 0.0f;
	ShaderConst.WetWorld.Data.z = 0.0f;
	ShaderConst.Rain.RainData.x = 0.0f;
	ShaderConst.Rain.RainData.y = 0.0f;
	ShaderConst.Rain.RainData.z = 0.0f;
	ShaderConst.Rain.RainData.w = 0.0f;

	ShaderConst.Animators.PuddlesAnimator.Initialize(0);
	ShaderConst.Animators.RainAnimator.Initialize(0);
	ShaderConst.Animators.SnowAnimator.Initialize(0);
	ShaderConst.Animators.SnowAccumulationAnimator.Initialize(0);
}


/*
Updates the values of the constants that can be accessed from shader code, with values representing the state of the game's elements.
*/
void ShaderManager::UpdateConstants() {
	
	bool IsThirdPersonView = !TheCameraManager->IsFirstPerson();
	Sky* WorldSky = Tes->sky;
	NiNode* SunRoot = WorldSky->sun->RootNode;
	TESClimate* currentClimate = WorldSky->firstClimate;
	TESWeather* currentWeather = WorldSky->firstWeather;
	TESWeather* previousWeather = WorldSky->secondWeather;
	TESObjectCELL* currentCell = Player->parentCell;
	TESWorldSpace* currentWorldSpace = Player->GetWorldSpace();
	TESRegion* currentRegion = Player->GetRegion();
	float weatherPercent = WorldSky->weatherPercent;
	float lastGameTime = ShaderConst.GameTime.y;
	
	TheRenderManager->UpdateSceneCameraData();
	TheRenderManager->SetupSceneCamera();

	// context variables
	bool isExterior = Player->GetWorldSpace() || Player->parentCell->flags0 & TESObjectCELL::kFlags0_BehaveLikeExterior;
	bool isUnderwater = WorldSky->GetIsUnderWater();
	bool isDialog = InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog);
	bool isPersuasion = InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion);

	bool isRainy = false;
	bool isSnow = false;
	if (currentWeather) {
		isRainy = currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy;
		isSnow = currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Snow;
	}

	TimeGlobals* GameTimeGlobals = TimeGlobals::Get();
	float GameHour = GameTimeGlobals->GameHour->data;
	float DaysPassed = GameTimeGlobals->GameDaysPassed ? GameTimeGlobals->GameDaysPassed->data : 1.0f;

	float SunriseStart = WorldSky->GetSunriseBegin();
	float SunriseEnd = WorldSky->GetSunriseEnd();
	float SunsetStart = WorldSky->GetSunsetBegin();
	float SunsetEnd = WorldSky->GetSunsetEnd();

	ShaderConst.GameTime.x = TimeGlobals::GetGameTime(); //time in milliseconds
	ShaderConst.GameTime.y = GameHour; //time in hours
	ShaderConst.GameTime.z = (float)TheFrameRateManager->Time;

	// get water height based on player position
	ShaderConst.Water.waterSettings.x = Tes->GetWaterHeight(Player, WorldSceneGraph);
	ShaderConst.Water.waterSettings.z = isUnderwater;

	float updateDelay = 0.01;

	if (currentCell) {
		ShaderConst.SunTiming.x = WorldSky->GetSunriseColorBegin();
		ShaderConst.SunTiming.y = SunriseEnd;
		ShaderConst.SunTiming.z = SunsetStart;
		ShaderConst.SunTiming.w = WorldSky->GetSunsetColorEnd();

		if (lastGameTime != ShaderConst.GameTime.y) {
			// update Sun position
			float deltaz = ShaderConst.SunDir.z;

			if (GameHour > SunsetEnd || GameHour < SunriseStart) {
				// use lighting direction at night time
				ShaderConst.SunDir.x = Tes->directionalLight->direction.x * -1;
				ShaderConst.SunDir.y = Tes->directionalLight->direction.y * -1;
				ShaderConst.SunDir.z = Tes->directionalLight->direction.z * -1;
			}
			else {
				ShaderConst.SunDir.x = SunRoot->m_localTransform.pos.x;
				ShaderConst.SunDir.y = SunRoot->m_localTransform.pos.y;
				ShaderConst.SunDir.z = SunRoot->m_localTransform.pos.z;
				D3DXVec4Normalize(&ShaderConst.SunDir, &ShaderConst.SunDir);
			}

		}

		// expose the light vector in view space for screen space lighting
		D3DXVec4Transform(&ShaderConst.ScreenSpaceLightDir, &ShaderConst.SunDir, &TheRenderManager->ViewProjMatrix);
		D3DXVec4Normalize(&ShaderConst.ScreenSpaceLightDir, &ShaderConst.ScreenSpaceLightDir);

		D3DXVec4Transform(&ShaderConst.ViewSpaceLightDir, &ShaderConst.SunDir, &TheRenderManager->ViewMatrix);
		D3DXVec4Normalize(&ShaderConst.ViewSpaceLightDir, &ShaderConst.ViewSpaceLightDir);

		ShaderConst.ShadowFade.x = 0;

		if (isExterior) {
			// fade shadows at sunrise/sunset
			float shadowFadeTime = 1.0f;
			if ((GameHour >= SunsetEnd - shadowFadeTime) && GameHour < SunsetEnd) { //sunset
				ShaderConst.ShadowFade.x = smoothStep(SunsetEnd - shadowFadeTime, SunsetEnd, GameHour);
			}
			else if (GameHour >= SunsetEnd && GameHour < SunsetEnd + shadowFadeTime) { //moonrise
				ShaderConst.ShadowFade.x = 1.0f - smoothStep(SunsetEnd, SunsetEnd + shadowFadeTime, GameHour);
			}
			else if (GameHour >= SunriseStart - shadowFadeTime && GameHour < SunriseStart) { //moonset
				ShaderConst.ShadowFade.x = smoothStep(SunriseStart - shadowFadeTime, SunriseStart, GameHour);
			}
			else if (GameHour >= SunriseStart && GameHour < SunriseStart + shadowFadeTime) { //sunrise
				ShaderConst.ShadowFade.x = 1.0f - smoothStep(SunriseStart, SunriseStart + shadowFadeTime, GameHour);
			}

			// at night time, fade based on moonphase
			if (GameHour > SunsetEnd || GameHour < SunriseStart) {
				// moonphase goes from 0 to 8
				float MoonPhase = (fmod(DaysPassed, 8 * currentClimate->phaseLength & 0x3F)) / (currentClimate->phaseLength & 0x3F);

				float PI = 3.1416; // use cos curve to fade moon light shadows strength
				MoonPhase = lerp(-PI, PI, MoonPhase / 8) - PI / 4; // map moonphase to 1/2PI/2PI + 1/2

				// map MoonVisibility to MinNightDarkness/1 range
				float MoonVisibility = lerp(0.0, TheSettingManager->SettingsShadows.Exteriors.NightMinDarkness, cos(MoonPhase) * 0.5 + 0.5);
				ShaderConst.ShadowFade.x = lerp(MoonVisibility, 1, ShaderConst.ShadowFade.x);
			}

			// pass the enabled/disabled property of the shadow maps to the shadowfade constant
			ShaderConst.ShadowFade.y = TheSettingManager->SettingsShadows.Exteriors.Enabled;
		}
		else {
			// pass the enabled/disabled property of the shadow maps to the shadowfade constant
			ShaderConst.ShadowFade.y = TheSettingManager->SettingsShadows.Interiors.Enabled;
		}

		//Logger::Log("exterior");

		// calculating fog color/fog amount based on sun amount
		ShaderConst.SunDir.w = 1.0f;
		if (ShaderConst.GameTime.y >= ShaderConst.SunTiming.y && ShaderConst.GameTime.y <= ShaderConst.SunTiming.z) {
			// Day time
			ShaderConst.SunAmount.x = 0.0f;
			ShaderConst.SunAmount.y = 1.0f;
			ShaderConst.SunAmount.z = 0.0f;
			ShaderConst.SunAmount.w = 0.0f;
		}
		else if ((ShaderConst.GameTime.y >= ShaderConst.SunTiming.w && ShaderConst.GameTime.y <= 23.59) || (ShaderConst.GameTime.y >= 0 && ShaderConst.GameTime.y <= ShaderConst.SunTiming.x)) {
			// Night time
			ShaderConst.SunAmount.x = 0.0f;
			ShaderConst.SunAmount.y = 0.0f;
			ShaderConst.SunAmount.z = 0.0f;
			ShaderConst.SunAmount.w = 1.0f;
		}
		else if (ShaderConst.GameTime.y >= ShaderConst.SunTiming.x && ShaderConst.GameTime.y <= ShaderConst.SunTiming.y) {
			// Sunrise
			float delta = 2.0f * invLerp(ShaderConst.SunTiming.x, ShaderConst.SunTiming.y, ShaderConst.GameTime.y); // from 0 (transition start) to 2 (transition end)

			if (delta <= 1.0f) {
				// first half: night is more prevalent than sun
				ShaderConst.SunAmount.x = delta;
				ShaderConst.SunAmount.y = 0.0f;
				ShaderConst.SunAmount.z = 0.0f;
				ShaderConst.SunAmount.w = 1.0f - delta;
			}
			else {
				// sun is more prevalent than night
				ShaderConst.SunAmount.x = 2.0f - delta;
				ShaderConst.SunAmount.y = delta - 1.0f;
				ShaderConst.SunAmount.z = 0.0f;
				ShaderConst.SunAmount.w = 0.0f;
			}
		}
		else if (ShaderConst.GameTime.y >= ShaderConst.SunTiming.z && ShaderConst.GameTime.y <= ShaderConst.SunTiming.w) {
			// Sunset
			float delta = 2.0f * invLerp(ShaderConst.SunTiming.w, ShaderConst.SunTiming.z, ShaderConst.GameTime.y); // from 0 (transition start) to 2 (transition end)

			if (delta <= 1.0f) {
				// first half, sun is more prevalent than night
				ShaderConst.SunAmount.x = 0.0f;
				ShaderConst.SunAmount.y = 1.0f - delta;
				ShaderConst.SunAmount.z = delta;
				ShaderConst.SunAmount.w = 0.0f;
			}
			else {
				// night is more prevalent than sun
				ShaderConst.SunAmount.x = 0.0f;
				ShaderConst.SunAmount.y = 0.0f;
				ShaderConst.SunAmount.z = 2.0f - delta;
				ShaderConst.SunAmount.w = delta - 1.0f;
			}
		}

		if (currentWeather) {
			ShaderConst.sunGlare = currentWeather->GetSunGlare() / 255.0f;
		}
		else {
			ShaderConst.sunGlare = 0.5f;
		}
		ShaderConst.windSpeed = WorldSky->windSpeed;

		ShaderConst.fogColor.x = WorldSky->fogColor.r;
		ShaderConst.fogColor.y = WorldSky->fogColor.g;
		ShaderConst.fogColor.z = WorldSky->fogColor.b;
		ShaderConst.fogColor.w = 1.0f;

		ShaderConst.horizonColor.x = WorldSky->Horizon.r;
		ShaderConst.horizonColor.y = WorldSky->Horizon.g;
		ShaderConst.horizonColor.z = WorldSky->Horizon.b;
		ShaderConst.horizonColor.w = 1.0f;

		ShaderConst.sunColor.x = WorldSky->sunDirectional.r;
		ShaderConst.sunColor.y = WorldSky->sunDirectional.g;
		ShaderConst.sunColor.z = WorldSky->sunDirectional.b;
		ShaderConst.sunColor.w = ShaderConst.sunGlare;

		ShaderConst.sunAmbient.x = WorldSky->sunAmbient.r;
		ShaderConst.sunAmbient.y = WorldSky->sunAmbient.g;
		ShaderConst.sunAmbient.z = WorldSky->sunAmbient.b;
		ShaderConst.sunAmbient.w = 1.0f;

		ShaderConst.skyColor.x = WorldSky->skyUpper.r;
		ShaderConst.skyColor.y = WorldSky->skyUpper.g;
		ShaderConst.skyColor.z = WorldSky->skyUpper.b;
		ShaderConst.skyColor.w = 1.0f;

		ShaderConst.fogData.x = WorldSky->fogNearPlane;
		ShaderConst.fogData.y = WorldSky->fogFarPlane;
		ShaderConst.fogData.z = ShaderConst.sunGlare;
		ShaderConst.fogData.w = WorldSky->fogPower;


		ShaderConst.fogDistance.x = ShaderConst.fogData.x;
		ShaderConst.fogDistance.y = ShaderConst.fogData.y;
		ShaderConst.fogDistance.z = 1.0f;
		ShaderConst.fogDistance.w = ShaderConst.sunGlare;

		//if (weatherPercent == 1.0f) ShaderConst.pWeather = currentWeather;

		//Logger::Log("Night? %f", ShaderConst.SunAmount.w);
		//Logger::Log("weather percent %f", weatherPercent);
		//Logger::Log("fog power %f", ShaderConst.fogData.w);
		//Logger::Log("fog near %f", ShaderConst.fogData.x);
		//Logger::Log("fog far %f", ShaderConst.fogData.y);
		//Logger::Log("sun r %f", ShaderConst.sunColor.x);
		//Logger::Log("sun g %f", ShaderConst.sunColor.y);
		//Logger::Log("sun b %f", ShaderConst.sunColor.z);
		//Logger::Log("sunglare %f", ShaderConst.fogData.z);
		//Logger::Log("sunglare %f", WorldSky->sun->glareScale);

		if (TheSettingManager->SettingsMain.Shaders.Water || TheSettingManager->SettingsMain.Effects.Underwater) {
			RGBA* rgba = NULL;
			SettingsWaterStruct* sws = NULL;
			TESWaterForm* currentWater = currentCell->GetWaterForm();
			
			if (currentWater) {
				UInt32 WaterType = currentWater->GetWaterType();
				if (WaterType == TESWaterForm::WaterType::kWaterType_Blood)
					sws = TheSettingManager->GetSettingsWater("Blood");
				else if (WaterType == TESWaterForm::WaterType::kWaterType_Lava)
					sws = TheSettingManager->GetSettingsWater("Lava");
				else if (!(sws = TheSettingManager->GetSettingsWater(currentCell->GetEditorName())) && currentWorldSpace) sws = TheSettingManager->GetSettingsWater(currentWorldSpace->GetEditorName());
			}
			if (!sws) sws = TheSettingManager->GetSettingsWater("Default");

			if (currentWater) {
				rgba = currentWater->GetDeepColor();
				ShaderConst.Water.deepColor.x = rgba->r / 255.0f;
				ShaderConst.Water.deepColor.y = rgba->g / 255.0f;
				ShaderConst.Water.deepColor.z = rgba->b / 255.0f;
				ShaderConst.Water.deepColor.w = rgba->a / 255.0f;
				rgba = currentWater->GetShallowColor();
				ShaderConst.Water.shallowColor.x = rgba->r / 255.0f;
				ShaderConst.Water.shallowColor.y = rgba->g / 255.0f;
				ShaderConst.Water.shallowColor.z = rgba->b / 255.0f;
				ShaderConst.Water.shallowColor.w = rgba->a / 255.0f;
			}

			ShaderConst.Water.waterCoefficients.x = sws->inExtCoeff_R;
			ShaderConst.Water.waterCoefficients.y = sws->inExtCoeff_G;
			ShaderConst.Water.waterCoefficients.z = sws->inExtCoeff_B;
			ShaderConst.Water.waterCoefficients.w = sws->inScattCoeff;

			ShaderConst.Water.waveParams.x = sws->choppiness;
			ShaderConst.Water.waveParams.y = sws->waveWidth;
			ShaderConst.Water.waveParams.z = sws->waveSpeed;
			ShaderConst.Water.waveParams.w = sws->reflectivity;

			ShaderConst.Water.waterSettings.y = sws->depthDarkness;

			ShaderConst.Water.waterVolume.x = sws->causticsStrength * ShaderConst.sunGlare;
			ShaderConst.Water.waterVolume.y = sws->shoreFactor;
			ShaderConst.Water.waterVolume.z = sws->turbidity;
			ShaderConst.Water.waterVolume.w = sws->causticsStrengthS;
			
			ShaderConst.Water.shorelineParams.x = sws->shoreMovement;
		}		

		if (isUnderwater) {
			ShaderConst.BloodLens.Percent = 0.0f;
			ShaderConst.WaterLens.Percent = -1.0f;
			ShaderConst.Animators.WaterLensAnimator.switched = true;
			ShaderConst.Animators.WaterLensAnimator.Start(0.0, 0);
		}

		if (TheSettingManager->SettingsMain.Effects.WaterLens) {

			if (!isUnderwater && ShaderConst.Animators.WaterLensAnimator.switched == true) {
				ShaderConst.Animators.WaterLensAnimator.switched = false;
				// start the waterlens effect and animate it fading
				ShaderConst.WaterLens.Time.x = TheSettingManager->SettingsWaterLens.TimeMultA;
				ShaderConst.WaterLens.Time.y = TheSettingManager->SettingsWaterLens.TimeMultB;
				ShaderConst.WaterLens.Time.z = TheSettingManager->SettingsWaterLens.Viscosity;
				ShaderConst.Animators.WaterLensAnimator.Initialize(1);
				ShaderConst.Animators.WaterLensAnimator.Start(0.01, 0);
			}
			ShaderConst.WaterLens.Percent = ShaderConst.Animators.WaterLensAnimator.GetValue();
			ShaderConst.WaterLens.Time.w = TheSettingManager->SettingsWaterLens.Amount * ShaderConst.WaterLens.Percent;
		}
			
		if (isExterior) {
			// Rain fall & puddles
			if (isRainy && ShaderConst.Animators.RainAnimator.switched == false) {
				// it just started raining
				ShaderConst.WetWorld.Data.y = 1.0f;
				ShaderConst.Animators.PuddlesAnimator.Start(0.3, 1);
				ShaderConst.Animators.RainAnimator.switched = true;
				ShaderConst.Animators.RainAnimator.Start(0.05, 1);
			}
			else if (!isRainy && ShaderConst.Animators.RainAnimator.switched) {
				// it just stopped raining
				ShaderConst.WetWorld.Data.y = 0.0f;
				ShaderConst.Animators.PuddlesAnimator.Start(1.2, 0);
				ShaderConst.Animators.RainAnimator.switched = false;
				ShaderConst.Animators.RainAnimator.Start(0.07, 0);
			}
			ShaderConst.WetWorld.Data.x = ShaderConst.Animators.RainAnimator.GetValue();
			ShaderConst.WetWorld.Data.z = ShaderConst.Animators.PuddlesAnimator.GetValue();

			ShaderConst.WetWorld.Coeffs.x = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_R;
			ShaderConst.WetWorld.Coeffs.y = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_G;
			ShaderConst.WetWorld.Coeffs.z = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_B;
			ShaderConst.WetWorld.Coeffs.w = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleSpecularMultiplier;

			ShaderConst.Rain.RainData.x = ShaderConst.Animators.RainAnimator.GetValue();
			ShaderConst.Rain.RainData.y = TheSettingManager->SettingsPrecipitations.Rain.VerticalScale;
			ShaderConst.Rain.RainData.z = TheSettingManager->SettingsPrecipitations.Rain.Speed;
			ShaderConst.Rain.RainData.w = TheSettingManager->SettingsPrecipitations.Rain.Opacity;

			if (TheSettingManager->SettingsMain.Effects.Snow) {
				// Snow fall
				if (isSnow && ShaderConst.Animators.SnowAnimator.switched == false) {
					// it just started snowing
					ShaderConst.Animators.PuddlesAnimator.Start(0.3, 0); // fade out any puddles if they exist
					ShaderConst.Animators.SnowAnimator.switched = true;
					ShaderConst.Animators.SnowAnimator.Initialize(0);
					ShaderConst.Animators.SnowAnimator.Start(0.5, 1);
				}
				else if (!isSnow && ShaderConst.Animators.SnowAnimator.switched) {
					// it just stopped snowing
					ShaderConst.Animators.SnowAnimator.switched = false;
					ShaderConst.Animators.SnowAnimator.Start(0.2, 0);
				}
				ShaderConst.Snow.SnowData.x = ShaderConst.Animators.SnowAnimator.GetValue();

				ShaderConst.Snow.SnowData.y = TheSettingManager->SettingsPrecipitations.Snow.DepthStep;
				ShaderConst.Snow.SnowData.z = TheSettingManager->SettingsPrecipitations.Snow.Speed;
				ShaderConst.Snow.SnowData.w = TheSettingManager->SettingsPrecipitations.Snow.Flakes;
			}

			if (TheSettingManager->SettingsMain.Effects.SnowAccumulation) {
				// Snow Accumulation
				if (isSnow && ShaderConst.Animators.SnowAccumulationAnimator.switched == false) {
					// it just started snowing
					ShaderConst.Animators.SnowAccumulationAnimator.switched = true;
					ShaderConst.Animators.SnowAccumulationAnimator.Initialize(0);
					ShaderConst.Animators.SnowAccumulationAnimator.Start(0.8, 1);
				}
				else if (!isSnow && ShaderConst.Animators.SnowAccumulationAnimator.switched) {
					// it just stopped snowing
					ShaderConst.Animators.SnowAccumulationAnimator.switched = false;
					ShaderConst.Animators.SnowAccumulationAnimator.Start(12, 0);
				}
				ShaderConst.SnowAccumulation.Params.x = TheSettingManager->SettingsPrecipitations.SnowAccumulation.BlurNormDropThreshhold;
				ShaderConst.SnowAccumulation.Params.y = TheSettingManager->SettingsPrecipitations.SnowAccumulation.BlurRadiusMultiplier;
				ShaderConst.SnowAccumulation.Params.z = TheSettingManager->SettingsPrecipitations.SnowAccumulation.SunPower;
				ShaderConst.SnowAccumulation.Params.w = ShaderConst.Animators.SnowAccumulationAnimator.GetValue();
			}
		}
		
		if (TheSettingManager->SettingsMain.Shaders.Grass) {
			ShaderConst.Grass.Scale.x = TheSettingManager->SettingsGrass.ScaleX;
			ShaderConst.Grass.Scale.y = TheSettingManager->SettingsGrass.ScaleY;
			ShaderConst.Grass.Scale.z = TheSettingManager->SettingsGrass.ScaleZ;
			switch (TheSettingManager->SettingsGrass.GrassDensity) {
				case 1:
					*Pointers::Settings::MinGrassSize = 240;
					*Pointers::Settings::TexturePctThreshold = 0.3f;
					break;
				case 2:
					*Pointers::Settings::MinGrassSize = 240;
					*Pointers::Settings::TexturePctThreshold = 0.2f;
					break;
				case 3:
					*Pointers::Settings::MinGrassSize = 120;
					*Pointers::Settings::TexturePctThreshold = 0.3f;
					break;
				case 4:
					*Pointers::Settings::MinGrassSize = 120;
					*Pointers::Settings::TexturePctThreshold = 0.2f;
					break;
				case 5:
					*Pointers::Settings::MinGrassSize = 80;
					*Pointers::Settings::TexturePctThreshold = 0.3f;
					break;
				case 6:
					*Pointers::Settings::MinGrassSize = 80;
					*Pointers::Settings::TexturePctThreshold = 0.2f;
					break;
				case 7:
					*Pointers::Settings::MinGrassSize = 20;
					*Pointers::Settings::TexturePctThreshold = 0.3f;
					break;
				case 8:
					*Pointers::Settings::MinGrassSize = 20;
					*Pointers::Settings::TexturePctThreshold = 0.2f;
					break;
				default:
					break;
			}
			*Pointers::Settings::GrassStartFadeDistance = TheSettingManager->SettingsGrass.MinDistance;
			*Pointers::Settings::GrassEndDistance = TheSettingManager->SettingsGrass.MaxDistance;
			if (TheSettingManager->SettingsGrass.WindEnabled) {
				*Pointers::Settings::GrassWindMagnitudeMax = *Pointers::ShaderParams::GrassWindMagnitudeMax = TheSettingManager->SettingsGrass.WindCoefficient * ShaderConst.windSpeed;
				*Pointers::Settings::GrassWindMagnitudeMin = *Pointers::ShaderParams::GrassWindMagnitudeMin = *Pointers::Settings::GrassWindMagnitudeMax * 0.5f;
			}
		}

		if (TheSettingManager->SettingsMain.Shaders.HDR) {
			ShaderConst.HDR.ToneMapping.x = TheSettingManager->SettingsHDR.ToneMapping;
			ShaderConst.HDR.ToneMapping.y = TheSettingManager->SettingsHDR.ToneMappingBlur;
			ShaderConst.HDR.ToneMapping.z = TheSettingManager->SettingsHDR.ToneMappingColor;
			ShaderConst.HDR.ToneMapping.w = TheSettingManager->SettingsHDR.Linearization;
		}

		if (TheSettingManager->SettingsMain.Shaders.POM) {
			ShaderConst.POM.ParallaxData.x = TheSettingManager->SettingsPOM.HeightMapScale;
			ShaderConst.POM.ParallaxData.y = TheSettingManager->SettingsPOM.MinSamples;
			ShaderConst.POM.ParallaxData.z = TheSettingManager->SettingsPOM.MaxSamples;
		}
	
		if (TheSettingManager->SettingsMain.Shaders.Terrain) {
			ShaderConst.Terrain.Data.x = TheSettingManager->SettingsTerrain.DistantSpecular;
			ShaderConst.Terrain.Data.y = TheSettingManager->SettingsTerrain.DistantNoise;
			ShaderConst.Terrain.Data.z = TheSettingManager->SettingsTerrain.NearSpecular;
			ShaderConst.Terrain.Data.w = TheSettingManager->SettingsTerrain.MiddleSpecular;
		}
	
		if (TheSettingManager->SettingsMain.Shaders.Skin) {
			ShaderConst.Skin.SkinData.x = TheSettingManager->SettingsSkin.Attenuation;
			ShaderConst.Skin.SkinData.y = TheSettingManager->SettingsSkin.SpecularPower;
			ShaderConst.Skin.SkinData.z = TheSettingManager->SettingsSkin.MaterialThickness;
			ShaderConst.Skin.SkinData.w = TheSettingManager->SettingsSkin.RimScalar;
			ShaderConst.Skin.SkinColor.x = TheSettingManager->SettingsSkin.CoeffRed;
			ShaderConst.Skin.SkinColor.y = TheSettingManager->SettingsSkin.CoeffGreen;
			ShaderConst.Skin.SkinColor.z = TheSettingManager->SettingsSkin.CoeffBlue;
		}

		if (TheSettingManager->SettingsMain.Effects.GodRays) {
			ShaderConst.GodRays.Ray.x = TheSettingManager->SettingsGodRays.RayIntensity;
			ShaderConst.GodRays.Ray.y = TheSettingManager->SettingsGodRays.RayLength;
			if (TheSettingManager->SettingsGodRays.SunGlareEnabled) {
				ShaderConst.GodRays.Ray.z = TheSettingManager->SettingsGodRays.RayDensity * ShaderConst.sunGlare;
				ShaderConst.GodRays.Ray.w = TheSettingManager->SettingsGodRays.RayVisibility * ShaderConst.sunGlare;
			}
			else {
				ShaderConst.GodRays.Ray.z = TheSettingManager->SettingsGodRays.RayDensity;
				ShaderConst.GodRays.Ray.w = TheSettingManager->SettingsGodRays.RayVisibility;
			}
			ShaderConst.GodRays.RayColor.x = TheSettingManager->SettingsGodRays.RayR;
			ShaderConst.GodRays.RayColor.y = TheSettingManager->SettingsGodRays.RayG;
			ShaderConst.GodRays.RayColor.z = TheSettingManager->SettingsGodRays.RayB;
			ShaderConst.GodRays.RayColor.w = TheSettingManager->SettingsGodRays.Saturate;
			ShaderConst.GodRays.Data.x = TheSettingManager->SettingsGodRays.LightShaftPasses;
			ShaderConst.GodRays.Data.y = TheSettingManager->SettingsGodRays.Luminance;
			ShaderConst.GodRays.Data.z = TheSettingManager->SettingsGodRays.GlobalMultiplier;
			ShaderConst.GodRays.Data.w = TheSettingManager->SettingsGodRays.TimeEnabled;
		}

		if (TheSettingManager->SettingsMain.Effects.AmbientOcclusion) {
			SettingsAmbientOcclusionStruct* sas = &TheSettingManager->SettingsAmbientOcclusionExteriors;

			if (!isExterior) sas = &TheSettingManager->SettingsAmbientOcclusionInteriors;
			ShaderConst.AmbientOcclusion.Enabled = sas->Enabled;
			if (ShaderConst.AmbientOcclusion.Enabled) {
				ShaderConst.AmbientOcclusion.AOData.x = sas->Samples;
				ShaderConst.AmbientOcclusion.AOData.y = sas->StrengthMultiplier;
				ShaderConst.AmbientOcclusion.AOData.z = sas->ClampStrength;
				ShaderConst.AmbientOcclusion.AOData.w = sas->Range;
				ShaderConst.AmbientOcclusion.Data.x = sas->AngleBias;
				ShaderConst.AmbientOcclusion.Data.y = sas->LumThreshold;
				ShaderConst.AmbientOcclusion.Data.z = sas->BlurDropThreshold;
				ShaderConst.AmbientOcclusion.Data.w = sas->BlurRadiusMultiplier;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.Bloom) {
			SettingsBloomStruct* sbs = &TheSettingManager->SettingsBloomExteriors;

			if (!isExterior) sbs = &TheSettingManager->SettingsBloomInteriors;
			ShaderConst.Bloom.BloomData.x = sbs->Luminance;
			ShaderConst.Bloom.BloomData.y = sbs->MiddleGray;
			ShaderConst.Bloom.BloomData.z = sbs->WhiteCutOff;
			ShaderConst.Bloom.BloomValues.x = sbs->BloomIntensity;
			ShaderConst.Bloom.BloomValues.y = sbs->OriginalIntensity;
			ShaderConst.Bloom.BloomValues.z = sbs->BloomSaturation;
			ShaderConst.Bloom.BloomValues.w = sbs->OriginalSaturation;
		}

		if (TheSettingManager->SettingsMain.Effects.Coloring) {
			SettingsColoringStruct* scs = TheSettingManager->GetSettingsColoring(currentCell->GetEditorName());

			if (!scs && isExterior) scs = TheSettingManager->GetSettingsColoring(currentWorldSpace->GetEditorName());
			if (!scs) scs = TheSettingManager->GetSettingsColoring("Default");
			ShaderConst.Coloring.Data.x = scs->Strength;
			ShaderConst.Coloring.Data.y = scs->BaseGamma;
			ShaderConst.Coloring.Data.z = scs->Fade;
			ShaderConst.Coloring.Data.w = scs->Contrast;
			ShaderConst.Coloring.Values.x = scs->Saturation;
			ShaderConst.Coloring.Values.y = scs->Bleach;
			ShaderConst.Coloring.Values.z = scs->BleachLuma;
			ShaderConst.Coloring.Values.w = scs->Linearization;
			ShaderConst.Coloring.ColorCurve.x = scs->ColorCurve;
			ShaderConst.Coloring.ColorCurve.y = scs->ColorCurveR;
			ShaderConst.Coloring.ColorCurve.z = scs->ColorCurveG;
			ShaderConst.Coloring.ColorCurve.w = scs->ColorCurveB;
			ShaderConst.Coloring.EffectGamma.x = scs->EffectGamma;
			ShaderConst.Coloring.EffectGamma.y = scs->EffectGammaR;
			ShaderConst.Coloring.EffectGamma.z = scs->EffectGammaG;
			ShaderConst.Coloring.EffectGamma.w = scs->EffectGammaB;
		}

		if (TheSettingManager->SettingsMain.Effects.BloodLens) {
			if (ShaderConst.BloodLens.Percent > 0.0f) {
				ShaderConst.BloodLens.Time.z = TheSettingManager->SettingsBloodLens.Time;
				if (ShaderConst.BloodLens.Percent == 1.0f) {
					ShaderConst.BloodLens.Time.w = 0.0f;
					srand(time(NULL));
					ShaderConst.BloodLens.Params.x = (double)rand() / (RAND_MAX + 1) * (0.75f - 0.25f) + 0.25f; //from 0.25 to 0.75
					ShaderConst.BloodLens.Params.y = (double)rand() / (RAND_MAX + 1) * (0.5f + 0.1f) - 0.1f; //from -0.1 to 0.5
					ShaderConst.BloodLens.Params.z = (double)rand() / (RAND_MAX + 1) * (2.0f + 2.0f) - 2.0f; //from -2 to 2
					ShaderConst.BloodLens.Params.w = TheSettingManager->SettingsBloodLens.Intensity;
				}
				ShaderConst.BloodLens.Time.w += 1.0f;
				ShaderConst.BloodLens.Percent = 1.0f - ShaderConst.BloodLens.Time.w / ShaderConst.BloodLens.Time.z;
				if (ShaderConst.BloodLens.Percent < 0.0f)
					ShaderConst.BloodLens.Percent = 0.0f;
				ShaderConst.BloodLens.Params.w = TheSettingManager->SettingsBloodLens.Intensity * ShaderConst.BloodLens.Percent;
				ShaderConst.BloodLens.BloodColor.x = TheSettingManager->SettingsBloodLens.ColorR;
				ShaderConst.BloodLens.BloodColor.y = TheSettingManager->SettingsBloodLens.ColorG;
				ShaderConst.BloodLens.BloodColor.z = TheSettingManager->SettingsBloodLens.ColorB;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.LowHF) {
			float PlayerHealthPercent = (float)Player->GetActorValue(Actor::ActorVal::kActorVal_Health) / (float)Player->GetBaseActorValue(Actor::ActorVal::kActorVal_Health);
			float PlayerFatiguePercent = (float)Player->GetActorValue(Actor::ActorVal::kActorVal_Stamina) / (float)Player->GetBaseActorValue(Actor::ActorVal::kActorVal_Stamina);

			ShaderConst.LowHF.Data.x = 0.0f;
			ShaderConst.LowHF.Data.y = 0.0f;
			ShaderConst.LowHF.Data.z = 0.0f;
			ShaderConst.LowHF.Data.w = 0.0f;
			if (Player->IsAlive()) {
				ShaderConst.LowHF.HealthCoeff = 1.0f - PlayerHealthPercent / TheSettingManager->SettingsLowHF.HealthLimit;
				ShaderConst.LowHF.FatigueCoeff = 1.0f - PlayerFatiguePercent / TheSettingManager->SettingsLowHF.FatigueLimit;
				if (PlayerHealthPercent < TheSettingManager->SettingsLowHF.HealthLimit) {
					ShaderConst.LowHF.Data.x = ShaderConst.LowHF.HealthCoeff * TheSettingManager->SettingsLowHF.LumaMultiplier;
					ShaderConst.LowHF.Data.y = ShaderConst.LowHF.HealthCoeff * 0.01f * TheSettingManager->SettingsLowHF.BlurMultiplier;
					ShaderConst.LowHF.Data.z = ShaderConst.LowHF.HealthCoeff * 20.0f * TheSettingManager->SettingsLowHF.VignetteMultiplier;
					ShaderConst.LowHF.Data.w = (1.0f - ShaderConst.LowHF.HealthCoeff) * TheSettingManager->SettingsLowHF.DarknessMultiplier;
				}
				if (!ShaderConst.LowHF.Data.x && PlayerFatiguePercent < TheSettingManager->SettingsLowHF.FatigueLimit) ShaderConst.LowHF.Data.x = ShaderConst.LowHF.FatigueCoeff * TheSettingManager->SettingsLowHF.LumaMultiplier;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.DepthOfField) {
			SettingsDepthOfFieldStruct* sds = NULL;

			if (TheCameraManager->IsVanity())
				sds = &TheSettingManager->SettingsDepthOfFieldVanityView;
			else if (IsThirdPersonView)
				sds = &TheSettingManager->SettingsDepthOfFieldThirdPersonView;
			else
				sds = &TheSettingManager->SettingsDepthOfFieldFirstPersonView;

			bool dofActive = sds->Enabled;
			switch (sds->Mode){
				case 1:
					if (isDialog || isPersuasion) dofActive = false;
					break;
				case 2:
					if (!isDialog) dofActive = false;
					break;
				case 3:
					if (!isPersuasion) dofActive = false;
					break;
				case 4:
					if (!isDialog && !isPersuasion) dofActive = false;
				default:
					break;
			}

			if (ShaderConst.DepthOfField.Enabled = dofActive) {
				ShaderConst.DepthOfField.Blur.x = sds->DistantBlur;
				ShaderConst.DepthOfField.Blur.y = sds->DistantBlurStartRange;
				ShaderConst.DepthOfField.Blur.z = sds->DistantBlurEndRange;
				ShaderConst.DepthOfField.Blur.w = sds->BaseBlurRadius;
				ShaderConst.DepthOfField.Data.x = sds->BlurFallOff;
				ShaderConst.DepthOfField.Data.y = sds->Radius;
				ShaderConst.DepthOfField.Data.z = sds->DiameterRange;
				ShaderConst.DepthOfField.Data.w = sds->NearBlurCutOff;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.Cinema) {
			UInt8 Mode = TheSettingManager->SettingsCinema.Mode;

			ShaderConst.Cinema.Data.x = TheSettingManager->SettingsCinema.AspectRatio;
			ShaderConst.Cinema.Data.y = TheSettingManager->SettingsCinema.VignetteRadius;
			switch (Mode) {
				case 1:
					if (isDialog || isPersuasion) Mode = -1; // disabled during dialog an persuation menus
					break;
				case 2:
					if (!isDialog) Mode = -1;
					break;
				case 3:
					if (!isPersuasion) Mode = -1;
					break;
				case 4:
					if (!isDialog && !isPersuasion) Mode = -1;
					break;
				default:
					break;
			}
			if (Mode == -1) {
				ShaderConst.Cinema.Data.x = TheShaderManager->ShaderConst.ReciprocalResolution.z; // set cinema aspect ratio to native ar
				ShaderConst.Cinema.Data.y = 0.0f;
			}
			ShaderConst.Cinema.Data.z = TheSettingManager->SettingsCinema.VignetteDarkness;
			ShaderConst.Cinema.Data.w = TheSettingManager->SettingsCinema.OverlayStrength;
			ShaderConst.Cinema.Settings.x = isUnderwater?0:TheSettingManager->SettingsCinema.DirtLensAmount; // disable dirt lens underwater
			ShaderConst.Cinema.Settings.y = TheSettingManager->SettingsCinema.FilmGrainAmount;
			ShaderConst.Cinema.Settings.z = TheSettingManager->SettingsCinema.ChromaticAberration;
		}

		// camera/position change data
		SettingsMotionBlurStruct* sms = NULL;

		if (IsThirdPersonView)
			sms = &TheSettingManager->SettingsMotionBlurThirdPersonView;
		else
			sms = &TheSettingManager->SettingsMotionBlurFirstPersonView;
		float AngleZ = D3DXToDegree(Player->rot.z);
		float AngleX = D3DXToDegree(Player->rot.x);
		float fMotionBlurAmtX = ShaderConst.MotionBlur.oldAngleZ - AngleZ;
		float fMotionBlurAmtY = ShaderConst.MotionBlur.oldAngleX - AngleX;
		float fBlurDistScratchpad = fMotionBlurAmtX + 360.0f;
		float fBlurDistScratchpad2 = (AngleZ - ShaderConst.MotionBlur.oldAngleZ + 360.0f) * -1.0f;

		if (abs(fMotionBlurAmtX) > abs(fBlurDistScratchpad))
			fMotionBlurAmtX = fBlurDistScratchpad;
		else if (abs(fMotionBlurAmtX) > abs(fBlurDistScratchpad2))
			fMotionBlurAmtX = fBlurDistScratchpad2;

		if (pow(fMotionBlurAmtX, 2) + pow(fMotionBlurAmtY, 2) < sms->BlurCutOff) {
			fMotionBlurAmtX = 0.0f;
			fMotionBlurAmtY = 0.0f;
		}

		ShaderConst.MotionBlur.Data.x = (ShaderConst.MotionBlur.oldoldAmountX + ShaderConst.MotionBlur.oldAmountX + fMotionBlurAmtX) / 3.0f;
		ShaderConst.MotionBlur.Data.y = (ShaderConst.MotionBlur.oldoldAmountY + ShaderConst.MotionBlur.oldAmountY + fMotionBlurAmtY) / 3.0f;
		ShaderConst.MotionBlur.oldAngleZ = AngleZ;
		ShaderConst.MotionBlur.oldAngleX = AngleX;
		ShaderConst.MotionBlur.oldoldAmountX = ShaderConst.MotionBlur.oldAmountX;
		ShaderConst.MotionBlur.oldoldAmountY = ShaderConst.MotionBlur.oldAmountY;
		ShaderConst.MotionBlur.oldAmountX = fMotionBlurAmtX;
		ShaderConst.MotionBlur.oldAmountY = fMotionBlurAmtY;
		ShaderConst.MotionBlur.BlurParams.x = sms->GaussianWeight;
		ShaderConst.MotionBlur.BlurParams.y = sms->BlurScale;
		ShaderConst.MotionBlur.BlurParams.z = sms->BlurOffsetMax;


		if (TheSettingManager->SettingsMain.Effects.Sharpening) {
			ShaderConst.Sharpening.Data.x = TheSettingManager->SettingsSharpening.Strength;
			ShaderConst.Sharpening.Data.y = TheSettingManager->SettingsSharpening.Clamp;
			ShaderConst.Sharpening.Data.z = TheSettingManager->SettingsSharpening.Offset;
		}

		ShaderConst.Shadow.ScreenSpaceData.x = TheSettingManager->SettingsShadows.ScreenSpace.Enabled;
		ShaderConst.Shadow.ScreenSpaceData.y = TheSettingManager->SettingsShadows.ScreenSpace.BlurRadius;
		ShaderConst.Shadow.ScreenSpaceData.z = TheSettingManager->SettingsShadows.ScreenSpace.RenderDistance;

		if (TheSettingManager->SettingsMain.Effects.Specular) {
			float rainyPercent = ShaderConst.Animators.RainAnimator.GetValue();
			SettingsSpecularStruct::ExteriorStruct* ext = &TheSettingManager->SettingsSpecular.Exterior;
			SettingsSpecularStruct::RainStruct* rain = &TheSettingManager->SettingsSpecular.Rain;

			// handle transition by interpolating previous and current weather settings
			ShaderConst.Specular.Data.x = lerp(ext->SpecLumaTreshold, rain->SpecLumaTreshold, rainyPercent);
			ShaderConst.Specular.Data.y = lerp(ext->BlurMultiplier, rain->BlurMultiplier, rainyPercent);
			ShaderConst.Specular.Data.z = lerp(ext->Glossiness, rain->Glossiness, rainyPercent);
			ShaderConst.Specular.Data.w = lerp(ext->DistanceFade, rain->DistanceFade, rainyPercent);
			ShaderConst.Specular.EffectStrength.x = lerp(ext->SpecularStrength, rain->SpecularStrength, rainyPercent);
			ShaderConst.Specular.EffectStrength.y = lerp(ext->SkyTintStrength, rain->SkyTintStrength, rainyPercent);
			ShaderConst.Specular.EffectStrength.z = lerp(ext->FresnelStrength, rain->FresnelStrength, rainyPercent);
			ShaderConst.Specular.EffectStrength.w = lerp(ext->SkyTintSaturation, rain->SkyTintSaturation, rainyPercent);
		}

		if (TheSettingManager->SettingsMain.Effects.VolumetricFog) {
			ShaderConst.VolumetricFog.Data.x = TheSettingManager->SettingsVolumetricFog.Exponent;
			ShaderConst.VolumetricFog.Data.y = TheSettingManager->SettingsVolumetricFog.ColorCoeff;
			ShaderConst.VolumetricFog.Data.z = TheSettingManager->SettingsVolumetricFog.Amount;
			ShaderConst.VolumetricFog.Data.w = TheSettingManager->SettingsVolumetricFog.MaxDistance;
			//if (weatherPercent == 1.0f && ShaderConst.fogData.y > TheSettingManager->SettingsVolumetricFog.MaxDistance) ShaderConst.VolumetricFog.Data.w = 0.0f;
		}
	}

	ShaderConst.DebugVar.x = TheSettingManager->SettingsMain.Develop.DebugVar1;
	ShaderConst.DebugVar.y = TheSettingManager->SettingsMain.Develop.DebugVar2;
	ShaderConst.DebugVar.z = TheSettingManager->SettingsMain.Develop.DebugVar3;
	ShaderConst.DebugVar.w = TheSettingManager->SettingsMain.Develop.DebugVar4;
}

void ShaderManager::CreateShader(const char* Name) {
	
	NiD3DVertexShader** Vertex = NULL;
	NiD3DPixelShader** Pixel = NULL;
	int WaterVertexShadersSize = sizeof(WaterVertexShaders) / 4;
	int WaterPixelShadersSize = sizeof(WaterPixelShaders) / 4;
	int Upperbound = 0;

	if (!strcmp(Name, "Terrain")) {
		Upperbound = GetShader(Name, &Vertex, NULL, 0);
		for (int i = 0; i < Upperbound; i++) if (Vertex[i] && strstr(TerrainShaders, ((NiD3DVertexShaderEx*)Vertex[i])->ShaderName)) LoadShader(Vertex[i]);
		Upperbound = GetShader(Name, &Pixel, NULL, 0);
		for (int i = 0; i < Upperbound; i++) if (Pixel[i] && strstr(TerrainShaders, ((NiD3DPixelShaderEx*)Pixel[i])->ShaderName)) LoadShader(Pixel[i]);
	}
	else if (!strcmp(Name, "ExtraShaders")) {
		Upperbound = GetShader(Name, &Vertex, NULL, 0);
		for (int i = 0; i < Upperbound; i++) if (Vertex[i] && !strstr(TerrainShaders, ((NiD3DVertexShaderEx*)Vertex[i])->ShaderName)) LoadShader(Vertex[i]);
		Upperbound = GetShader(Name, &Pixel, NULL, 0);
		for (int i = 0; i < Upperbound; i++) if (Pixel[i] && !strstr(TerrainShaders, ((NiD3DPixelShaderEx*)Pixel[i])->ShaderName)) LoadShader(Pixel[i]);
	}
	else {
		Upperbound = GetShader(Name, &Vertex, WaterVertexShaders, WaterVertexShadersSize);
		for (int i = 0; i < Upperbound; i++) if (Vertex[i]) LoadShader(Vertex[i]);
		Upperbound = GetShader(Name, &Pixel, WaterPixelShaders, WaterPixelShadersSize);
		for (int i = 0; i < Upperbound; i++) if (Pixel[i]) LoadShader(Pixel[i]);
		if (!strcmp(Name, "Water")) {
			Upperbound = GetShader("WaterHeightMap", &Vertex, WaterVertexShaders, WaterVertexShadersSize);
			for (int i = 0; i < Upperbound; i++) if (Vertex[i]) LoadShader(Vertex[i]);
			Upperbound = GetShader("WaterHeightMap", &Pixel, WaterPixelShaders, WaterPixelShadersSize);
			for (int i = 0; i < Upperbound; i++) if (Pixel[i]) LoadShader(Pixel[i]);
			Upperbound = GetShader("WaterDisplacement", &Vertex, WaterVertexShaders, WaterVertexShadersSize);
			for (int i = 0; i < Upperbound; i++) if (Vertex[i]) LoadShader(Vertex[i]);
			Upperbound = GetShader("WaterDisplacement", &Pixel, WaterPixelShaders, WaterPixelShadersSize);
			for (int i = 0; i < Upperbound; i++) if (Pixel[i]) LoadShader(Pixel[i]);
		}
	}

}

void ShaderManager::LoadShader(NiD3DVertexShader* Shader) {
	
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Shader;

	VertexShader->ShaderProg  = (ShaderRecordVertex*)ShaderRecord::LoadShader(VertexShader->ShaderName, NULL);
	VertexShader->ShaderProgE = (ShaderRecordVertex*)ShaderRecord::LoadShader(VertexShader->ShaderName, "Exteriors\\");
	VertexShader->ShaderProgI = (ShaderRecordVertex*)ShaderRecord::LoadShader(VertexShader->ShaderName, "Interiors\\");

}

void ShaderManager::LoadShader(NiD3DPixelShader* Shader) {

	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Shader;

	PixelShader->ShaderProg  = (ShaderRecordPixel*)ShaderRecord::LoadShader(PixelShader->ShaderName, NULL);
	PixelShader->ShaderProgE = (ShaderRecordPixel*)ShaderRecord::LoadShader(PixelShader->ShaderName, "Exteriors\\");
	PixelShader->ShaderProgI = (ShaderRecordPixel*)ShaderRecord::LoadShader(PixelShader->ShaderName, "Interiors\\");

}

void ShaderManager::DisposeShader(const char* Name) {

	NiD3DVertexShader** Vertex = NULL;
	NiD3DPixelShader** Pixel = NULL;
	int WaterVertexShadersSize = sizeof(WaterVertexShaders) / 4;
	int WaterPixelShadersSize = sizeof(WaterPixelShaders) / 4;
	int Upperbound = 0;

	if (!strcmp(Name, "Terrain")) {
		Upperbound = GetShader(Name, &Vertex, NULL, 0);
		for (int i = 0; i < GetShader(Name, &Vertex, NULL, 0); i++) if (Vertex[i] && strstr(TerrainShaders, ((NiD3DVertexShaderEx*)Vertex[i])->ShaderName)) ((NiD3DVertexShaderEx*)Vertex[i])->DisposeShader();
		Upperbound = GetShader(Name, &Pixel, NULL, 0);
		for (int i = 0; i < GetShader(Name, &Pixel, NULL, 0); i++) if (Pixel[i] && strstr(TerrainShaders, ((NiD3DPixelShaderEx*)Pixel[i])->ShaderName)) ((NiD3DPixelShaderEx*)Pixel[i])->DisposeShader();
	}
	else if (!strcmp(Name, "ExtraShaders")) {
		Upperbound = GetShader(Name, &Vertex, NULL, 0);
		for (int i = 0; i < GetShader(Name, &Vertex, NULL, 0); i++) if (Vertex[i] && !strstr(TerrainShaders, ((NiD3DVertexShaderEx*)Vertex[i])->ShaderName)) ((NiD3DVertexShaderEx*)Vertex[i])->DisposeShader();
		Upperbound = GetShader(Name, &Pixel, NULL, 0);
		for (int i = 0; i < GetShader(Name, &Pixel, NULL, 0); i++) if (Pixel[i] && !strstr(TerrainShaders, ((NiD3DPixelShaderEx*)Pixel[i])->ShaderName)) ((NiD3DPixelShaderEx*)Pixel[i])->DisposeShader();
	}
	else {
		Upperbound = GetShader(Name, &Vertex, WaterVertexShaders, WaterVertexShadersSize);
		for (int i = 0; i < GetShader(Name, &Vertex, WaterVertexShaders, WaterVertexShadersSize); i++) if (Vertex[i]) ((NiD3DVertexShaderEx*)Vertex[i])->DisposeShader();
		Upperbound = GetShader(Name, &Pixel, WaterPixelShaders, WaterPixelShadersSize);
		for (int i = 0; i < GetShader(Name, &Pixel, WaterPixelShaders, WaterPixelShadersSize); i++) if (Pixel[i]) ((NiD3DPixelShaderEx*)Pixel[i])->DisposeShader();
		if (!strcmp(Name, "Water")) {
			Upperbound = GetShader("WaterHeightMap", &Vertex, WaterVertexShaders, WaterVertexShadersSize);
			for (int i = 0; i < GetShader("WaterHeightMap", &Vertex, WaterVertexShaders, WaterVertexShadersSize); i++) if (Vertex[i]) ((NiD3DVertexShaderEx*)Vertex[i])->DisposeShader();
			Upperbound = GetShader("WaterHeightMap", &Pixel, WaterPixelShaders, WaterPixelShadersSize);
			for (int i = 0; i < GetShader("WaterHeightMap", &Pixel, WaterPixelShaders, WaterPixelShadersSize); i++) if (Pixel[i]) ((NiD3DPixelShaderEx*)Pixel[i])->DisposeShader();
			Upperbound = GetShader("WaterDisplacement", &Vertex, WaterVertexShaders, WaterVertexShadersSize);
			for (int i = 0; i < GetShader("WaterDisplacement", &Vertex, WaterVertexShaders, WaterVertexShadersSize); i++) if (Vertex[i]) ((NiD3DVertexShaderEx*)Vertex[i])->DisposeShader();
			Upperbound = GetShader("WaterDisplacement", &Pixel, WaterPixelShaders, WaterPixelShadersSize);
			for (int i = 0; i < GetShader("WaterDisplacement", &Pixel, WaterPixelShaders, WaterPixelShadersSize); i++) if (Pixel[i]) ((NiD3DPixelShaderEx*)Pixel[i])->DisposeShader();
		}
	}

}

/*
* Loads an Effect Shader from the corresponding fx file based on the Effect Record effect Type.
*/
void ShaderManager::CreateEffect(EffectRecord::EffectRecordType EffectType) {
	
	char Filename[MAX_PATH];
	SettingsMainStruct* SettingsMain = &TheSettingManager->SettingsMain;

	strcpy(Filename, EffectsPath);
	switch (EffectType) {
		case EffectRecord::EffectRecordType::Normals:
			strcat(Filename, "Normals.fx");
			NormalsEffect = EffectRecord::LoadEffect(Filename);
			break;
		case EffectRecord::EffectRecordType::Underwater:
			strcat(Filename, "Underwater.fx");
			UnderwaterEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Underwater = (SettingsMain->Effects.Underwater && UnderwaterEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::WaterLens:
			strcat(Filename, "WaterLens.fx");
			WaterLensEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.WaterLens = (SettingsMain->Effects.WaterLens && WaterLensEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::GodRays:
			strcat(Filename, "GodRays.fx");
			GodRaysEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.GodRays = (SettingsMain->Effects.GodRays && GodRaysEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::DepthOfField:
			strcat(Filename, "DepthOfField.fx");
			DepthOfFieldEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.DepthOfField = (SettingsMain->Effects.DepthOfField && DepthOfFieldEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::AmbientOcclusion:
			strcat(Filename, "AmbientOcclusion.fx");
			AmbientOcclusionEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.AmbientOcclusion = (SettingsMain->Effects.AmbientOcclusion && AmbientOcclusionEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Coloring:
			strcat(Filename, "Coloring.fx");
			ColoringEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Coloring = (SettingsMain->Effects.Coloring && ColoringEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Cinema:
			strcat(Filename, "Cinema.fx");
			CinemaEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Cinema = (SettingsMain->Effects.Cinema && CinemaEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Bloom:
			strcat(Filename, "Bloom.fx");
			BloomEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Bloom = (SettingsMain->Effects.Bloom && BloomEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::SnowAccumulation:
			strcat(Filename, "SnowAccumulation.fx");
			SnowAccumulationEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.SnowAccumulation = (SettingsMain->Effects.SnowAccumulation && SnowAccumulationEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::BloodLens:
			strcat(Filename, "BloodLens.fx");
			BloodLensEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.BloodLens = (SettingsMain->Effects.BloodLens && BloodLensEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::MotionBlur:
			strcat(Filename, "MotionBlur.fx");
			MotionBlurEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.MotionBlur = (SettingsMain->Effects.MotionBlur && MotionBlurEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::LowHF:
			strcat(Filename, "LowHF.fx");
			LowHFEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.LowHF = (SettingsMain->Effects.LowHF && LowHFEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::WetWorld:
			strcat(Filename, "WetWorld.fx");
			WetWorldEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.WetWorld = (SettingsMain->Effects.WetWorld && WetWorldEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Sharpening:
			strcat(Filename, "Sharpening.fx");
			SharpeningEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Sharpening = (SettingsMain->Effects.Sharpening && SharpeningEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Specular:
			strcat(Filename, "Specular.fx");
			SpecularEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Specular = (SettingsMain->Effects.Specular && SpecularEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::VolumetricFog:
			strcat(Filename, "VolumetricFog.fx");
			VolumetricFogEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.VolumetricFog = (SettingsMain->Effects.VolumetricFog && VolumetricFogEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Rain:
			strcat(Filename, "Rain.fx");
			RainEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Rain = ( SettingsMain->Effects.Rain && RainEffect->IsLoaded());
		case EffectRecord::EffectRecordType::Snow:
			strcat(Filename, "Snow.fx");
			SnowEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.Snow = (SettingsMain->Effects.Snow && SnowEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::ShadowsExteriors:
			strcat(Filename, "ShadowsExteriors.fx");
			ShadowsExteriorsEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.ShadowsExteriors = (SettingsMain->Effects.ShadowsExteriors && ShadowsExteriorsEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::ShadowsInteriors:
			strcat(Filename, "ShadowsInteriors.fx");
			ShadowsInteriorsEffect = EffectRecord::LoadEffect(Filename);
			SettingsMain->Effects.ShadowsInteriors = (SettingsMain->Effects.ShadowsInteriors && ShadowsInteriorsEffect->IsLoaded());
			break;
		case EffectRecord::EffectRecordType::Extra:
			WIN32_FIND_DATAA File;
			HANDLE H;
			char* cFileName = NULL;
			EffectRecord* ExtraEffect = NULL;

			if (SettingsMain->Develop.CompileEffects)
				strcat(Filename, "Extra\\*.hlsl");
			else
				strcat(Filename, "Extra\\*.fx");
			H = FindFirstFileA((LPCSTR)Filename, &File);
			if (H != INVALID_HANDLE_VALUE) {
				cFileName = (char*)File.cFileName;
				if (SettingsMain->Develop.CompileEffects) File.cFileName[strlen(cFileName) - 5] = '\0';
				strcpy(Filename, EffectsPath);
				strcat(Filename, "Extra\\");
				strcat(Filename, cFileName);
				ExtraEffect = EffectRecord::LoadEffect(Filename);
				if (ExtraEffect) ExtraEffects[std::string(cFileName).substr(0, strlen(cFileName) - 3)] = ExtraEffect;
				while (FindNextFileA(H, &File)) {
					cFileName = (char*)File.cFileName;
					if (SettingsMain->Develop.CompileEffects) File.cFileName[strlen(cFileName) - 5] = '\0';
					strcpy(Filename, EffectsPath);
					strcat(Filename, "Extra\\");
					strcat(Filename, cFileName);
					ExtraEffect = EffectRecord::LoadEffect(Filename);
					if (ExtraEffect) ExtraEffects[std::string(cFileName).substr(0, strlen(cFileName) - 3)] = ExtraEffect;
				}
				FindClose(H);
			}
			break;
	}

}

/*
* Deletes an Effect based on the Effect Record effect type. 
*/
void ShaderManager::DisposeEffect(EffectRecord::EffectRecordType EffectType) {

	switch (EffectType) {
		case EffectRecord::EffectRecordType::Normals:
			delete NormalsEffect; NormalsEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Underwater:
			delete UnderwaterEffect; UnderwaterEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::WaterLens:
			delete WaterLensEffect; WaterLensEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::GodRays:
			delete GodRaysEffect; GodRaysEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::DepthOfField:
			delete DepthOfFieldEffect; DepthOfFieldEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::AmbientOcclusion:
			delete AmbientOcclusionEffect; AmbientOcclusionEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Coloring:
			delete ColoringEffect; ColoringEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Cinema:
			delete CinemaEffect; CinemaEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Bloom:
			delete BloomEffect; BloomEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::SnowAccumulation:
			delete SnowAccumulationEffect; SnowAccumulationEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::BloodLens:
			delete BloodLensEffect; BloodLensEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::MotionBlur:
			delete MotionBlurEffect; MotionBlurEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::LowHF:
			delete LowHFEffect; LowHFEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::WetWorld:
			delete WetWorldEffect; WetWorldEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Sharpening:
			delete SharpeningEffect; SharpeningEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Specular:
			delete SharpeningEffect; SharpeningEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::VolumetricFog:
			delete VolumetricFogEffect; VolumetricFogEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Rain:
			delete RainEffect; RainEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Snow:
			delete SnowEffect; SnowEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::ShadowsExteriors:
			delete ShadowsExteriorsEffect; ShadowsExteriorsEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::ShadowsInteriors:
			delete ShadowsInteriorsEffect; ShadowsInteriorsEffect = NULL;
			break;
		case EffectRecord::EffectRecordType::Extra:
			ExtraEffectsList::iterator v = ExtraEffects.begin();
			while (v != ExtraEffects.end()) {
				delete v->second;
				v++;
			}
			ExtraEffects.clear();
			break;
	}

}

/*
* Renders the effect that have been set to enabled.
*/
void ShaderManager::RenderEffects(IDirect3DSurface9* RenderTarget) {
	
	SettingsMainStruct::EffectsStruct* Effects = &TheSettingManager->SettingsMain.Effects;
	IDirect3DDevice9* Device = TheRenderManager->device;
	IDirect3DSurface9* SourceSurface = TheTextureManager->SourceSurface;
	IDirect3DSurface9* RenderedSurface = TheTextureManager->RenderedSurface;
	TESWorldSpace* currentWorldSpace = Player->GetWorldSpace();
	TESObjectCELL* currentCell = Player->parentCell;
	Sky* WorldSky = Tes->sky;
	bool isExterior = Player->GetWorldSpace() || Player->parentCell->flags0 & TESObjectCELL::kFlags0_BehaveLikeExterior;
	bool isUnderwater = Tes->sky->GetIsUnderWater(); /*TODO do this work in interior????*/
	bool isDaytime = (ShaderConst.GameTime.y >= ShaderConst.SunTiming.x && ShaderConst.GameTime.y <= ShaderConst.SunTiming.w); // gametime is between sunrise start and sunset end
	bool isCellTransition = currentCell != PreviousCell;

	bool pipboyIsOn = InterfaceManager->IsActive(Menu::kMenuType_BigFour);
	bool VATSIsOn = InterfaceManager->IsActive(Menu::kMenuType_VATS);
	bool terminalIsOn = InterfaceManager->IsActive(Menu::kMenuType_Computers) || InterfaceManager->IsActive(Menu::kMenuType_LockPick);

	TheShaderManager->UpdateConstants();

	Device->SetStreamSource(0, FrameVertex, 0, sizeof(FrameVS));
	Device->SetFVF(FrameFVF);
	
	// render post process normals for use by shaders
	Device->SetRenderTarget(0, TheTextureManager->NormalsSurface);
	Device->StretchRect(TheTextureManager->NormalsSurface, NULL, TheTextureManager->NormalsSurface, NULL, D3DTEXF_NONE);
	NormalsEffect->SetCT();
	NormalsEffect->Render(Device, TheTextureManager->NormalsSurface, TheTextureManager->NormalsSurface, false);

	// prepare device for effects
	Device->SetRenderTarget(0, RenderTarget);
	Device->StretchRect(RenderTarget, NULL, RenderedSurface, NULL, D3DTEXF_NONE);
	Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);

	if (!terminalIsOn) {
		// disable these effects during terminal/lockpicking sequences because they bleed through the overlay

		// Snow must be rendered first so other effects appear on top
		if (SnowAccumulationEffect->Enabled && ShaderConst.SnowAccumulation.Params.w > 0.0f && isExterior && !isUnderwater) {
			Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
			SnowAccumulationEffect->SetCT();
			SnowAccumulationEffect->Render(Device, RenderTarget, RenderedSurface, false);
		}

		if (ShaderConst.AmbientOcclusion.Enabled) {
			Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
			AmbientOcclusionEffect->SetCT();
			AmbientOcclusionEffect->Render(Device, RenderTarget, RenderedSurface, false);
		}

		// Disable shadows during VATS
		if (!VATSIsOn) {
			if (isExterior && ShadowsExteriorsEffect->Enabled) {
				Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
				ShadowsExteriorsEffect->SetCT();
				ShadowsExteriorsEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
			else if (!isExterior && ShadowsInteriorsEffect->Enabled) {
				Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
				ShadowsInteriorsEffect->SetCT();
				ShadowsInteriorsEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
		}

		if (isUnderwater) {
			// underwater only effects
			if (UnderwaterEffect->Enabled && isUnderwater) {
				UnderwaterEffect->SetCT();
				UnderwaterEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
		}
		else {
			if (isExterior) {
				if (SpecularEffect->Enabled) {
					Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
					SpecularEffect->SetCT();
					SpecularEffect->Render(Device, RenderTarget, RenderedSurface, false);
				}
				if (WetWorldEffect->Enabled && ShaderConst.WetWorld.Data.z > 0.0f) {
					Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
					WetWorldEffect->SetCT();
					WetWorldEffect->Render(Device, RenderTarget, RenderedSurface, false);
				}
				if (RainEffect->Enabled && ShaderConst.Rain.RainData.x > 0.0f) {
					RainEffect->SetCT();
					RainEffect->Render(Device, RenderTarget, RenderedSurface, false);
				}
				if (SnowEffect->Enabled && ShaderConst.Snow.SnowData.x > 0.0f) {
					SnowEffect->SetCT();
					SnowEffect->Render(Device, RenderTarget, RenderedSurface, false);
				}
			}

			if (VolumetricFogEffect->Enabled && !pipboyIsOn) {
				VolumetricFogEffect->SetCT();
				VolumetricFogEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}

			if (GodRaysEffect->Enabled && isExterior && isDaytime) {
				Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
				GodRaysEffect->SetCT();
				GodRaysEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
		}
	}

	// screenspace coloring/blurring effects get rendered last
	if (ColoringEffect->Enabled) {
		ColoringEffect->SetCT();
		ColoringEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (BloomEffect->Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		BloomEffect->SetCT();
		BloomEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (DepthOfFieldEffect->Enabled && ShaderConst.DepthOfField.Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		DepthOfFieldEffect->SetCT();
		DepthOfFieldEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (MotionBlurEffect->Enabled && (ShaderConst.MotionBlur.Data.x || ShaderConst.MotionBlur.Data.y)) {
		MotionBlurEffect->SetCT();
		MotionBlurEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}

	// lens effects
	if (BloodLensEffect->Enabled && ShaderConst.BloodLens.Percent > 0.0f) {
		BloodLensEffect->SetCT();
		BloodLensEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (WaterLensEffect->Enabled && ShaderConst.WaterLens.Percent > 0.0f) {
		WaterLensEffect->SetCT();
		WaterLensEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (LowHFEffect->Enabled && ShaderConst.LowHF.Data.x) {
		LowHFEffect->SetCT();
		LowHFEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (SharpeningEffect->Enabled) {
		SharpeningEffect->SetCT();
		SharpeningEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (Effects->Extra) {
		for (ExtraEffectsList::iterator iter = ExtraEffects.begin(); iter != ExtraEffects.end(); ++iter) {
			if (iter->second->Enabled) {
				Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
				iter->second->SetCT();
				iter->second->Render(Device, RenderTarget, RenderedSurface, false);
			}
		}
	}

	// cinema effect gets rendered very last because of vignetting/letterboxing
	if (CinemaEffect->Enabled && (ShaderConst.Cinema.Data.x != 0.0f || ShaderConst.Cinema.Data.y != 0.0f)) {
		CinemaEffect->SetCT();
		CinemaEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	PreviousCell = currentCell;
}

/*
* Writes the settings corresponding to the shader/effect name, to switch it between enabled/disabled.*
* Also creates or deletes the corresponding Effect Record.
*/
void ShaderManager::SwitchShaderStatus(const char* Name) {
	
	SettingsMainStruct::EffectsStruct* Effects = &TheSettingManager->SettingsMain.Effects;
	SettingsMainStruct::ShadersStruct* Shaders = &TheSettingManager->SettingsMain.Shaders;
	IsMenuSwitch = true;

	if (!strcmp(Name, "Specular")) {
		SpecularEffect->SwitchEffect();
		Effects->Specular = SpecularEffect->Enabled;
	}
	if (!strcmp(Name, "AmbientOcclusion")) {
		AmbientOcclusionEffect->SwitchEffect();
		Effects->AmbientOcclusion = AmbientOcclusionEffect->Enabled;
	}
	else if (!strcmp(Name, "Blood")) {
		Shaders->Blood = !Shaders->Blood;
		DisposeShader(Name);
		if (Shaders->Blood) CreateShader(Name);
	}
	else if (!strcmp(Name, "BloodLens")) {
		BloodLensEffect->SwitchEffect();
		Effects->BloodLens = BloodLensEffect->Enabled;
	}
	else if (!strcmp(Name, "Bloom")) {
		BloomEffect->SwitchEffect();
		Effects->Bloom = BloomEffect->Enabled;
	}
	else if (!strcmp(Name, "Cinema")) {
		CinemaEffect->SwitchEffect();
		Effects->Cinema = CinemaEffect->Enabled;
	}
	else if (!strcmp(Name, "Coloring")) {
		ColoringEffect->SwitchEffect();
		Effects->Coloring = ColoringEffect->Enabled;
	}
	else if (!strcmp(Name, "DepthOfField")) {
		DepthOfFieldEffect->SwitchEffect();
		Effects->DepthOfField = DepthOfFieldEffect->Enabled;
	}
	else if (!strcmp(Name, "ExtraEffects")) { //TODO change to new effect switch
		Effects->Extra = !Effects->Extra;
		DisposeEffect(EffectRecord::EffectRecordType::Extra);
		if (Effects->Extra) CreateEffect(EffectRecord::EffectRecordType::Extra);
	}
	else if (!strcmp(Name, "ExtraShaders")) {
		Shaders->Extra = !Shaders->Extra;
		DisposeShader(Name);
		if (Shaders->Extra) CreateShader(Name);
	}
	else if (!strcmp(Name, "Grass")) {
		Shaders->Grass = !Shaders->Grass;
		DisposeShader(Name);
		if (Shaders->Grass) CreateShader(Name);
	}
	else if (!strcmp(Name, "GodRays")) {
		GodRaysEffect->SwitchEffect();
		Effects->GodRays = GodRaysEffect->Enabled;
	}
	else if (!strcmp(Name, "HDR")) {
		Shaders->HDR = !Shaders->HDR;
		DisposeShader(Name);
		if (Shaders->HDR) CreateShader(Name);
	}
	else if (!strcmp(Name, "LowHF")) {
		LowHFEffect->SwitchEffect();
		Effects->LowHF = LowHFEffect->Enabled;
	}
	else if (!strcmp(Name, "MotionBlur")) {
		MotionBlurEffect->SwitchEffect();
		Effects->MotionBlur = MotionBlurEffect->Enabled;
	}
	else if (!strcmp(Name, "NightEye")) {
		Shaders->NightEye = !Shaders->NightEye;
		DisposeShader(Name);
		if (Shaders->NightEye) CreateShader(Name);
	}
	else if (!strcmp(Name, "POM")) {
		Shaders->POM = !Shaders->POM;
		DisposeShader(Name);
		if (Shaders->POM) CreateShader(Name);
	}
	else if (!strcmp(Name, "Precipitations")) {
		RainEffect->SwitchEffect();
		Effects->Rain = RainEffect->Enabled;
	}
	else if (!strcmp(Name, "Snow")) {
		SnowEffect->SwitchEffect();
		Effects->Snow = SnowEffect->Enabled; 
	}
	else if (!strcmp(Name, "Skin")) {
		Shaders->Skin = !Shaders->Skin;
		DisposeShader(Name);
		if (Shaders->Skin) CreateShader(Name);
	}
	else if (!strcmp(Name, "SnowAccumulation")) {
		SnowAccumulationEffect->SwitchEffect();
		Effects->SnowAccumulation = SnowAccumulationEffect->Enabled;
	}
	else if (!strcmp(Name, "Terrain")) {
		Shaders->Terrain = !Shaders->Terrain;
		DisposeShader(Name);
		if (Shaders->Terrain) CreateShader(Name);
	}
	else if (!strcmp(Name, "Underwater")) {
		UnderwaterEffect->SwitchEffect();
		Effects->Underwater = UnderwaterEffect->Enabled;
	}
	else if (!strcmp(Name, "Water")) {
		Shaders->Water = !Shaders->Water;
		DisposeShader(Name);
		if (Shaders->Water) CreateShader(Name);
	}
	else if (!strcmp(Name, "WaterLens")) {
		WaterLensEffect->SwitchEffect();
		Effects->WaterLens = WaterLensEffect->Enabled;
	}
	else if (!strcmp(Name, "WetWorld")) {
		WetWorldEffect->SwitchEffect();
		Effects->WetWorld = WetWorldEffect->Enabled;
	}
	else if (!strcmp(Name, "Sharpening")) {
		SharpeningEffect->SwitchEffect();
		Effects->Sharpening = SharpeningEffect->Enabled;
	}
	else if (!strcmp(Name, "VolumetricFog")) {
		VolumetricFogEffect->SwitchEffect();
		Effects->VolumetricFog = VolumetricFogEffect->Enabled;
	}
	else if (!strcmp(Name, "ShadowsExteriors")) {
		ShadowsExteriorsEffect->SwitchEffect();
		Effects->ShadowsExteriors = ShadowsExteriorsEffect->Enabled;
	}
	else if (!strcmp(Name, "ShadowsInteriors")) {
		ShadowsInteriorsEffect->SwitchEffect();
		Effects->ShadowsInteriors = ShadowsInteriorsEffect->Enabled;
	}
	IsMenuSwitch = false;
}

void ShaderManager::SetCustomConstant(const char* Name, D3DXVECTOR4 Value) {
	
	CustomConstants::iterator v = CustomConst.find(std::string(Name));
	if (v != CustomConst.end()) v->second = Value;

}

void ShaderManager::SetExtraEffectEnabled(const char* Name, bool Value) {

	ExtraEffectsList::iterator v = ExtraEffects.find(std::string(Name));
	if (v != ExtraEffects.end()) v->second->Enabled = Value;

}

float ShaderManager::lerp(float a, float b, float t) {
	return (1 - t) * a + t * b;
}

float ShaderManager::invLerp(float a, float b, float t) {
	return(t - a) / (b - a);
}

float ShaderManager::clamp(float a, float b, float t) {
	return min(max(a, t), b);
}

float ShaderManager::smoothStep(float a, float b, float t) {
	t = clamp(0.0, 1.0, invLerp(a, b, t));
	return t * t * (3.0 - 2.0 * t);
}
