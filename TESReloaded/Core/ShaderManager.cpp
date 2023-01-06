
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
	else if (!strcmp(Name, "TESR_SunColor"))
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
	else if (!memcmp(Name, "HDR", 3)) {
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
//	CreateEffect(EffectRecord::EffectRecordType::Extra);

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

	bool isExterior = Player->GetWorldSpace() || Player->parentCell->flags0 & TESObjectCELL::kFlags0_BehaveLikeExterior;

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

	if (currentCell) {
		ShaderConst.SunTiming.x = WorldSky->GetSunriseColorBegin();
		ShaderConst.SunTiming.y = SunriseEnd;
		ShaderConst.SunTiming.z = SunsetStart;
		ShaderConst.SunTiming.w = WorldSky->GetSunsetColorEnd();

		if (lastGameTime != ShaderConst.GameTime.y) {
			// update Sun position
			float deltaz = ShaderConst.SunDir.z;
			ShaderConst.SunDir.x = Tes->directionalLight->direction.x * -1;
			ShaderConst.SunDir.y = Tes->directionalLight->direction.y * -1;
			ShaderConst.SunDir.z = Tes->directionalLight->direction.z * -1;
		}

		// expose the light vector in view space for screen space lighting
		D3DXVec4Transform(&ShaderConst.ScreenSpaceLightDir, &ShaderConst.SunDir, &TheRenderManager->ViewProjMatrix);
		D3DXVec4Normalize(&ShaderConst.ScreenSpaceLightDir, &ShaderConst.ScreenSpaceLightDir);

		D3DXVec4Transform(&ShaderConst.ViewSpaceLightDir, &ShaderConst.SunDir, &TheRenderManager->ViewMatrix);
		D3DXVec4Normalize(&ShaderConst.ViewSpaceLightDir, &ShaderConst.ViewSpaceLightDir);

		// fade shadows at sunrise/sunset
		float shadowFadeTime = 1.0f;
		ShaderConst.ShadowFade.x = 0;
		if ((GameHour >= SunsetEnd - shadowFadeTime) && GameHour < SunsetEnd) { //sunset
			ShaderConst.ShadowFade.x = smoothStep(SunsetEnd - shadowFadeTime, SunsetEnd, GameHour);
		}
		else if (GameHour >= SunsetEnd && GameHour < SunsetEnd + shadowFadeTime) { //moonrise
			ShaderConst.ShadowFade.x = 1.0f - smoothStep(SunsetEnd, SunsetEnd + shadowFadeTime, GameHour);
		}
		else if(GameHour >= SunriseStart - shadowFadeTime && GameHour < SunriseStart){ //moonset
			ShaderConst.ShadowFade.x = smoothStep(SunriseStart - shadowFadeTime, SunriseStart, GameHour);
		}
		else if(GameHour >= SunriseStart && GameHour < SunriseStart + shadowFadeTime){ //sunrise
			ShaderConst.ShadowFade.x = 1.0f - smoothStep(SunriseStart, SunriseStart + shadowFadeTime, GameHour);
		}

		// at night time, fade based on moonphase
		if (GameHour > SunsetEnd || GameHour < SunriseStart) {
			// moonphase goes from 0 to 8
			float MoonPhase = (fmod(DaysPassed, 8 * currentClimate->phaseLength & 0x3F)) / (currentClimate->phaseLength & 0x3F);

			float PI = 3.1416; // use cos curve to fade moon light shadows strength
			MoonPhase = lerp(-PI, PI, MoonPhase / 8) - PI/4; // map moonphase to 1/2PI/2PI + 1/2

			// map MoonVisibility to MinNightDarkness/1 range
			float MoonVisibility = lerp(0.0, TheSettingManager->SettingsShadows.Exteriors.NightMinDarkness, cos(MoonPhase) * 0.5 + 0.5);
			ShaderConst.ShadowFade.x = lerp(MoonVisibility, 1, ShaderConst.ShadowFade.x);
		}

		if (isExterior) {
			// pass the enabled/disabled property of the shadow maps to the shadowfade constant
			ShaderConst.ShadowFade.y = !TheSettingManager->SettingsShadows.Exteriors.Enabled;

			if (currentWeather) {
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

				if (ShaderConst.pWeather == NULL) ShaderConst.pWeather = currentWeather;

				for (int t = TESWeather::eTime_Sunrise; t <= TESWeather::eTime_Night ; t++) {
					RGBA color = currentWeather->colors[TESWeather::eColor_Fog].colors[t];
					switch (t)
					{
						case TESWeather::eTime_Sunrise:
							ShaderConst.fogColor.x = color.r / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.fogColor.y = color.g / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.fogColor.z = color.b / 255.0f * ShaderConst.SunAmount.x;
							break;
						case TESWeather::eTime_Day:
							ShaderConst.fogColor.x += color.r / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.fogColor.y += color.g / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.fogColor.z += color.b / 255.0f * ShaderConst.SunAmount.y;
							break;
						case TESWeather::eTime_Sunset:
							ShaderConst.fogColor.x += color.r / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.fogColor.y += color.g / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.fogColor.z += color.b / 255.0f * ShaderConst.SunAmount.z;
							break;
						case TESWeather::eTime_Night:
							ShaderConst.fogColor.x += color.r / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.fogColor.y += color.g / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.fogColor.z += color.b / 255.0f * ShaderConst.SunAmount.w;
							break;
					}
				}
				for (int t = TESWeather::eTime_Sunrise; t <= TESWeather::eTime_Night ; t++) {
					RGBA color = ShaderConst.pWeather->colors[TESWeather::eColor_Fog].colors[t];
					switch (t)
					{
						case TESWeather::eTime_Sunrise:
							ShaderConst.oldfogColor.x = color.r / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.oldfogColor.y = color.g / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.oldfogColor.z = color.b / 255.0f * ShaderConst.SunAmount.x;
							break;
						case TESWeather::eTime_Day:
							ShaderConst.oldfogColor.x += color.r / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.oldfogColor.y += color.g / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.oldfogColor.z += color.b / 255.0f * ShaderConst.SunAmount.y;
							break;
						case TESWeather::eTime_Sunset:
							ShaderConst.oldfogColor.x += color.r / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.oldfogColor.y += color.g / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.oldfogColor.z += color.b / 255.0f * ShaderConst.SunAmount.z;
							break;
						case TESWeather::eTime_Night:
							ShaderConst.oldfogColor.x += color.r / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.oldfogColor.y += color.g / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.oldfogColor.z += color.b / 255.0f * ShaderConst.SunAmount.w;
							break;
					}
				}

				for (int t = TESWeather::eTime_Sunrise; t <= TESWeather::eTime_Night ; t++) {
					RGBA color = currentWeather->colors[TESWeather::eColor_Sun].colors[t];
					switch (t)
					{
						case TESWeather::eTime_Sunrise:
							ShaderConst.sunColor.x = color.r / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.sunColor.y = color.g / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.sunColor.z = color.b / 255.0f * ShaderConst.SunAmount.x;
							break;
						case TESWeather::eTime_Day:
							ShaderConst.sunColor.x += color.r / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.sunColor.y += color.g / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.sunColor.z += color.b / 255.0f * ShaderConst.SunAmount.y;
							break;
						case TESWeather::eTime_Sunset:
							ShaderConst.sunColor.x += color.r / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.sunColor.y += color.g / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.sunColor.z += color.b / 255.0f * ShaderConst.SunAmount.z;
							break;
						case TESWeather::eTime_Night:
							ShaderConst.sunColor.x += color.r / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.sunColor.y += color.g / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.sunColor.z += color.b / 255.0f * ShaderConst.SunAmount.w;
							break;
					}
				}
				for (int t = TESWeather::eTime_Sunrise; t <= TESWeather::eTime_Night ; t++) {
					RGBA color = ShaderConst.pWeather->colors[TESWeather::eColor_Sun].colors[t];
					switch (t)
					{
						case TESWeather::eTime_Sunrise:
							ShaderConst.oldsunColor.x = color.r / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.oldsunColor.y = color.g / 255.0f * ShaderConst.SunAmount.x;
							ShaderConst.oldsunColor.z = color.b / 255.0f * ShaderConst.SunAmount.x;
							break;
						case TESWeather::eTime_Day:
							ShaderConst.oldsunColor.x += color.r / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.oldsunColor.y += color.g / 255.0f * ShaderConst.SunAmount.y;
							ShaderConst.oldsunColor.z += color.b / 255.0f * ShaderConst.SunAmount.y;
							break;
						case TESWeather::eTime_Sunset:
							ShaderConst.oldsunColor.x += color.r / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.oldsunColor.y += color.g / 255.0f * ShaderConst.SunAmount.z;
							ShaderConst.oldsunColor.z += color.b / 255.0f * ShaderConst.SunAmount.z;
							break;
						case TESWeather::eTime_Night:
							ShaderConst.oldsunColor.x += color.r / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.oldsunColor.y += color.g / 255.0f * ShaderConst.SunAmount.w;
							ShaderConst.oldsunColor.z += color.b / 255.0f * ShaderConst.SunAmount.w;
							break;
					}
				}

				if (ShaderConst.SunAmount.w == 1.0f) {
					ShaderConst.currentfogStart = currentWeather->GetFogNightNear();
					ShaderConst.currentfogEnd = currentWeather->GetFogNightFar();
					ShaderConst.oldfogStart = ShaderConst.pWeather->GetFogNightNear();
					ShaderConst.oldfogEnd = ShaderConst.pWeather->GetFogNightFar();
				}
				else {
					ShaderConst.currentfogStart = currentWeather->GetFogDayNear();
					ShaderConst.currentfogEnd = currentWeather->GetFogDayFar();
					ShaderConst.oldfogStart = ShaderConst.pWeather->GetFogDayNear();
					ShaderConst.oldfogEnd = ShaderConst.pWeather->GetFogDayFar();
				}

				ShaderConst.fogDistance.x = ShaderConst.currentfogStart;
				ShaderConst.fogDistance.y = ShaderConst.currentfogEnd;
				ShaderConst.fogDistance.z = weatherPercent;
				ShaderConst.fogDistance.w = currentWeather->GetSunGlare();
				ShaderConst.oldsunGlare = ShaderConst.pWeather->GetSunGlare();
				ShaderConst.oldwindSpeed = ShaderConst.pWeather->GetWindSpeed();
				ShaderConst.currentsunGlare = (ShaderConst.oldsunGlare - ((ShaderConst.oldsunGlare - currentWeather->GetSunGlare()) * weatherPercent)) / 255.0f;
				ShaderConst.currentwindSpeed = (ShaderConst.oldwindSpeed - ((ShaderConst.oldwindSpeed - currentWeather->GetWindSpeed()) * weatherPercent)) / 255.0f;

				ShaderConst.fogColor.x = ShaderConst.oldfogColor.x - ((ShaderConst.oldfogColor.x - ShaderConst.fogColor.x) * weatherPercent);
				ShaderConst.fogColor.y = ShaderConst.oldfogColor.y - ((ShaderConst.oldfogColor.y - ShaderConst.fogColor.y) * weatherPercent);
				ShaderConst.fogColor.z = ShaderConst.oldfogColor.z - ((ShaderConst.oldfogColor.z - ShaderConst.fogColor.z) * weatherPercent);
				ShaderConst.fogColor.w = 1.0f;

				ShaderConst.sunColor.x = ShaderConst.oldsunColor.x - ((ShaderConst.oldsunColor.x - ShaderConst.sunColor.x) * weatherPercent);
				ShaderConst.sunColor.y = ShaderConst.oldsunColor.y - ((ShaderConst.oldsunColor.y - ShaderConst.sunColor.y) * weatherPercent);
				ShaderConst.sunColor.z = ShaderConst.oldsunColor.z - ((ShaderConst.oldsunColor.z - ShaderConst.sunColor.z) * weatherPercent);
				ShaderConst.sunColor.w = ShaderConst.SunAmount.w;

				ShaderConst.fogData.x = ShaderConst.oldfogStart - ((ShaderConst.oldfogStart - ShaderConst.currentfogStart) * weatherPercent);
				ShaderConst.fogData.y = ShaderConst.oldfogEnd - ((ShaderConst.oldfogEnd - ShaderConst.currentfogEnd) * weatherPercent);
				ShaderConst.fogData.z = ShaderConst.currentsunGlare;

				if (weatherPercent == 1.0f) ShaderConst.pWeather = currentWeather;
			}
		}
		else {
			ShaderConst.SunDir.w = 0.0f;
			ShaderConst.SunAmount.x = 0.0f;
			ShaderConst.SunAmount.y = 1.0f;
			ShaderConst.SunAmount.z = 0.0f;
			ShaderConst.SunAmount.w = 0.0f;
			ShaderConst.currentsunGlare = 0.5f;
			TESObjectCELL::LightingData* LightData = currentCell->lighting;
			ShaderConst.fogColor.x = LightData->fog.r / 255.0f;
			ShaderConst.fogColor.y = LightData->fog.g / 255.0f;
			ShaderConst.fogColor.z = LightData->fog.b / 255.0f;
			ShaderConst.fogColor.w = 1.0f;

			ShaderConst.sunColor.x = LightData->ambient.r / 255.0f;
			ShaderConst.sunColor.y = LightData->ambient.g / 255.0f;
			ShaderConst.sunColor.z = LightData->ambient.b / 255.0f;
			ShaderConst.sunColor.w = ShaderConst.SunAmount.w;

			ShaderConst.fogData.x = LightData->fogNear;
			ShaderConst.fogData.y = LightData->fogFar;
			ShaderConst.fogData.z = ShaderConst.currentsunGlare;

			ShaderConst.fogDistance.x = ShaderConst.currentfogStart;
			ShaderConst.fogDistance.y = ShaderConst.currentfogEnd;
			ShaderConst.fogDistance.z = 1.0f;
			ShaderConst.fogDistance.w = ShaderConst.currentsunGlare;
		}

		if (TheSettingManager->SettingsMain.Shaders.Water || TheSettingManager->SettingsMain.Effects.Underwater) {
			RGBA* rgba = NULL;
			SettingsWaterStruct* sws = NULL;
			TESWaterForm* currentWater = Tes->GetWaterForm();
			
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

			ShaderConst.Water.waterSettings.x = Tes->GetWaterHeight(Player);
			ShaderConst.Water.waterSettings.y = sws->depthDarkness;

			ShaderConst.Water.waterVolume.x = sws->causticsStrength * ShaderConst.currentsunGlare;
			ShaderConst.Water.waterVolume.y = sws->shoreFactor;
			ShaderConst.Water.waterVolume.z = sws->turbidity;
			ShaderConst.Water.waterVolume.w = sws->causticsStrengthS;
			
			ShaderConst.Water.shorelineParams.x = sws->shoreMovement;

			if (TheSettingManager->SettingsMain.Effects.Underwater && TheSettingManager->SettingsMain.Effects.WaterLens) {
				ShaderConst.WaterLens.Time.x = TheSettingManager->SettingsWaterLens.TimeMultA;
				ShaderConst.WaterLens.Time.y = TheSettingManager->SettingsWaterLens.TimeMultB;
				ShaderConst.WaterLens.Time.z = TheSettingManager->SettingsWaterLens.Viscosity;
				if (ShaderConst.WaterLens.Percent == -1.0f) {
					ShaderConst.WaterLens.TimeAmount = 0.0f;
					ShaderConst.WaterLens.Time.w = TheSettingManager->SettingsWaterLens.Amount;
				}
				else if (ShaderConst.WaterLens.Percent > 0.0f) {
					ShaderConst.WaterLens.TimeAmount += 1.0f;
					ShaderConst.WaterLens.Percent = 1.0f - ShaderConst.WaterLens.TimeAmount / TheSettingManager->SettingsWaterLens.Time;
					if (ShaderConst.WaterLens.Percent < 0.0f) ShaderConst.WaterLens.Percent = 0.0f;
					ShaderConst.WaterLens.Time.w = TheSettingManager->SettingsWaterLens.Amount * ShaderConst.WaterLens.Percent;
				}
			}

		}		

		if (TheSettingManager->SettingsMain.Effects.SnowAccumulation && currentWeather) {
			if (currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Snow) {
				if (ShaderConst.SnowAccumulation.Params.w < TheSettingManager->SettingsPrecipitations.SnowAccumulation.Amount) ShaderConst.SnowAccumulation.Params.w = ShaderConst.SnowAccumulation.Params.w + TheSettingManager->SettingsPrecipitations.SnowAccumulation.Increase;
			}
			else if (!previousWeather || (previousWeather && previousWeather->GetWeatherType() == TESWeather::WeatherType::kType_Snow)) {
				if (ShaderConst.SnowAccumulation.Params.w > 0.0f)
					ShaderConst.SnowAccumulation.Params.w = ShaderConst.SnowAccumulation.Params.w - TheSettingManager->SettingsPrecipitations.SnowAccumulation.Decrease;
				else if (ShaderConst.SnowAccumulation.Params.w < 0.0f)
					ShaderConst.SnowAccumulation.Params.w = 0.0f;
			}
			ShaderConst.SnowAccumulation.Params.x = TheSettingManager->SettingsPrecipitations.SnowAccumulation.BlurNormDropThreshhold;
			ShaderConst.SnowAccumulation.Params.y = TheSettingManager->SettingsPrecipitations.SnowAccumulation.BlurRadiusMultiplier;
			ShaderConst.SnowAccumulation.Params.z = TheSettingManager->SettingsPrecipitations.SnowAccumulation.SunPower;
		}
			
		if ((TheSettingManager->SettingsMain.Effects.WetWorld || TheSettingManager->SettingsMain.Shaders.Water) && currentWeather) {
			if (currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy) {
				ShaderConst.WetWorld.Data.y = 1.0f;
				if (ShaderConst.WetWorld.Data.x < TheSettingManager->SettingsPrecipitations.WetWorld.Amount) ShaderConst.WetWorld.Data.x = ShaderConst.WetWorld.Data.x + TheSettingManager->SettingsPrecipitations.WetWorld.Increase;
			}
			else if (!previousWeather || (previousWeather && previousWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy)) {
				ShaderConst.WetWorld.Data.y = 0.3f - weatherPercent;
				if (ShaderConst.WetWorld.Data.y <= 0.0f) ShaderConst.WetWorld.Data.y = 0.05f;
				if (ShaderConst.WetWorld.Data.x > 0.0f)
					ShaderConst.WetWorld.Data.x = ShaderConst.WetWorld.Data.x - TheSettingManager->SettingsPrecipitations.WetWorld.Decrease;
				else if (ShaderConst.WetWorld.Data.x < 0.0f)
					ShaderConst.WetWorld.Data.x = 0.0f;
			}
			ShaderConst.WetWorld.Coeffs.x = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_R;
			ShaderConst.WetWorld.Coeffs.y = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_G;
			ShaderConst.WetWorld.Coeffs.z = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleCoeff_B;
			ShaderConst.WetWorld.Coeffs.w = TheSettingManager->SettingsPrecipitations.WetWorld.PuddleSpecularMultiplier;
		}
		
		if (currentWeather) {
			if (currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy)
				ShaderConst.Rain.RainData.x = weatherPercent;
			else if (!previousWeather || (previousWeather && previousWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy))
				ShaderConst.Rain.RainData.x = 1.0f - weatherPercent;
			ShaderConst.Rain.RainData.y = TheSettingManager->SettingsPrecipitations.Rain.DepthStep;
			ShaderConst.Rain.RainData.z = TheSettingManager->SettingsPrecipitations.Rain.Speed;
			if (currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Snow)
				ShaderConst.Snow.SnowData.x = weatherPercent;
			else if (!previousWeather || (previousWeather && previousWeather->GetWeatherType() == TESWeather::WeatherType::kType_Snow))
				ShaderConst.Snow.SnowData.x = 1.0f - weatherPercent;
			ShaderConst.Snow.SnowData.y = TheSettingManager->SettingsPrecipitations.Snow.DepthStep;
			ShaderConst.Snow.SnowData.z = TheSettingManager->SettingsPrecipitations.Snow.Speed;
			ShaderConst.Snow.SnowData.w = TheSettingManager->SettingsPrecipitations.Snow.Flakes;
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
				*Pointers::Settings::GrassWindMagnitudeMax = *Pointers::ShaderParams::GrassWindMagnitudeMax = TheSettingManager->SettingsGrass.WindCoefficient * ShaderConst.currentwindSpeed;
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
				ShaderConst.GodRays.Ray.z = TheSettingManager->SettingsGodRays.RayDensity * ShaderConst.currentsunGlare;
				ShaderConst.GodRays.Ray.w = TheSettingManager->SettingsGodRays.RayVisibility * ShaderConst.currentsunGlare;
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

			if (!currentWorldSpace) sas = &TheSettingManager->SettingsAmbientOcclusionInteriors;
			ShaderConst.AmbientOcclusion.Enabled = sas->Enabled;
			if (ShaderConst.AmbientOcclusion.Enabled) {
				ShaderConst.AmbientOcclusion.AOData.x = sas->Samples;
				ShaderConst.AmbientOcclusion.AOData.y = sas->StrengthMultiplier;
				ShaderConst.AmbientOcclusion.AOData.z = sas->ClampStrength;
				ShaderConst.AmbientOcclusion.AOData.w = sas->Range;
				ShaderConst.AmbientOcclusion.Data.x = sas->AngleBias;
				ShaderConst.AmbientOcclusion.Data.y = sas->LumThreshold * ShaderConst.SunAmount.y;
				ShaderConst.AmbientOcclusion.Data.z = sas->BlurDropThreshold;
				ShaderConst.AmbientOcclusion.Data.w = sas->BlurRadiusMultiplier;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.Bloom) {
			SettingsBloomStruct* sbs = &TheSettingManager->SettingsBloomExteriors;

			if (!currentWorldSpace) sbs = &TheSettingManager->SettingsBloomInteriors;
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

			if (!scs && currentWorldSpace) scs = TheSettingManager->GetSettingsColoring(currentWorldSpace->GetEditorName());
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
			if (sds->Mode == 1) {
				if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog) || InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) sds->Enabled = false;
			}
			else if (sds->Mode == 2) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog)) sds->Enabled = false;
			}
			else if (sds->Mode == 3) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) sds->Enabled = false;
			}
			else if (sds->Mode == 4) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog) && !InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) sds->Enabled = false;
			}
			if (ShaderConst.DepthOfField.Enabled = sds->Enabled) {
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
			if (Mode == 1) {
				if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog) || InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) Mode = -1;
			}
			else if (Mode == 2) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog)) Mode = -1;
			}
			else if (Mode == 3) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) Mode = -1;
			}
			else if (Mode == 4) {
				if (!InterfaceManager->IsActive(Menu::MenuType::kMenuType_Dialog) && !InterfaceManager->IsActive(Menu::MenuType::kMenuType_Persuasion)) Mode = -1;
			}
			if (Mode == -1) {
				ShaderConst.Cinema.Data.x = 0.0f;
				ShaderConst.Cinema.Data.y = 0.0f;
			}
			ShaderConst.Cinema.Data.z = TheSettingManager->SettingsCinema.VignetteDarkness;
		}

		if (TheSettingManager->SettingsMain.Effects.MotionBlur) {
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

			if (sms->Enabled) {
				ShaderConst.MotionBlur.Data.x = (ShaderConst.MotionBlur.oldoldAmountX + ShaderConst.MotionBlur.oldAmountX + fMotionBlurAmtX) / 3.0f;
				ShaderConst.MotionBlur.Data.y = (ShaderConst.MotionBlur.oldoldAmountY + ShaderConst.MotionBlur.oldAmountY + fMotionBlurAmtY) / 3.0f;
			}
			else {
				ShaderConst.MotionBlur.Data.x = 0.0f;
				ShaderConst.MotionBlur.Data.y = 0.0f;
			}
			ShaderConst.MotionBlur.oldAngleZ = AngleZ;
			ShaderConst.MotionBlur.oldAngleX = AngleX;
			ShaderConst.MotionBlur.oldoldAmountX = ShaderConst.MotionBlur.oldAmountX;
			ShaderConst.MotionBlur.oldoldAmountY = ShaderConst.MotionBlur.oldAmountY;
			ShaderConst.MotionBlur.oldAmountX = fMotionBlurAmtX;
			ShaderConst.MotionBlur.oldAmountY = fMotionBlurAmtY;
			ShaderConst.MotionBlur.BlurParams.x = sms->GaussianWeight;
			ShaderConst.MotionBlur.BlurParams.y = sms->BlurScale;
			ShaderConst.MotionBlur.BlurParams.z = sms->BlurOffsetMax;
		}

		if (TheSettingManager->SettingsMain.Effects.Sharpening) {
			ShaderConst.Sharpening.Data.x = TheSettingManager->SettingsSharpening.Strength;
			ShaderConst.Sharpening.Data.y = TheSettingManager->SettingsSharpening.Clamp;
			ShaderConst.Sharpening.Data.z = TheSettingManager->SettingsSharpening.Offset;
		}

		ShaderConst.Shadow.ScreenSpaceData.x = TheSettingManager->SettingsShadows.ScreenSpace.Enabled;
		ShaderConst.Shadow.ScreenSpaceData.y = TheSettingManager->SettingsShadows.ScreenSpace.BlurRadius;
		ShaderConst.Shadow.ScreenSpaceData.z = TheSettingManager->SettingsShadows.ScreenSpace.RenderDistance;

		if (TheSettingManager->SettingsMain.Effects.Specular) {
			D3DXVECTOR4 exteriorData;
			D3DXVECTOR4 rainData;
			D3DXVECTOR4* previousData;
			D3DXVECTOR4* currentData;

			exteriorData.x = TheSettingManager->SettingsSpecular.Exterior.Strength;
			exteriorData.y = TheSettingManager->SettingsSpecular.Exterior.BlurMultiplier;
			exteriorData.z = TheSettingManager->SettingsSpecular.Exterior.Glossiness;
			exteriorData.w = TheSettingManager->SettingsSpecular.Exterior.DistanceFade;
			rainData.x = TheSettingManager->SettingsSpecular.Rain.Strength;
			rainData.y = TheSettingManager->SettingsSpecular.Rain.BlurMultiplier;
			rainData.z = TheSettingManager->SettingsSpecular.Rain.Glossiness;
			rainData.w = TheSettingManager->SettingsSpecular.Rain.DistanceFade;

			bool currentIsRainy = false;
			if (currentWeather) currentIsRainy = currentWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy;

			bool previousIsRainy = false;
			if (previousWeather) previousIsRainy = (previousWeather->GetWeatherType() == TESWeather::WeatherType::kType_Rainy);

			if (currentIsRainy) currentData = &rainData;
			else currentData = &exteriorData;

			if (weatherPercent > 0 && weatherPercent < 1 && (currentIsRainy != previousIsRainy)) {
				// handle transition by interpolating previous and current weather settings
				if (previousIsRainy) previousData = &rainData;
				else previousData = &exteriorData;
				
				ShaderConst.Specular.Data.x = smoothStep(previousData->x, currentData->x, weatherPercent);
				ShaderConst.Specular.Data.y = smoothStep(previousData->y, currentData->y, weatherPercent);
				ShaderConst.Specular.Data.z = smoothStep(previousData->z, currentData->z, weatherPercent);
				ShaderConst.Specular.Data.w = smoothStep(previousData->w, currentData->w, weatherPercent);
			}
			else {
				ShaderConst.Specular.Data = *currentData;
			}
		}

		if (TheSettingManager->SettingsMain.Effects.VolumetricFog) {
			ShaderConst.VolumetricFog.Data.x = TheSettingManager->SettingsVolumetricFog.Exponent;
			ShaderConst.VolumetricFog.Data.y = TheSettingManager->SettingsVolumetricFog.ColorCoeff;
			ShaderConst.VolumetricFog.Data.z = TheSettingManager->SettingsVolumetricFog.Amount;
			ShaderConst.VolumetricFog.Data.w = 1.0f;
			if (weatherPercent == 1.0f && ShaderConst.fogData.y > TheSettingManager->SettingsVolumetricFog.MaxDistance) ShaderConst.VolumetricFog.Data.w = 0.0f;
		}
	}

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
	bool isExterior = Player->GetWorldSpace() || Player->parentCell->flags0 & TESObjectCELL::kFlags0_BehaveLikeExterior;

	TheShaderManager->UpdateConstants();

	Device->SetStreamSource(0, FrameVertex, 0, sizeof(FrameVS));
	Device->SetFVF(FrameFVF);
	Device->StretchRect(RenderTarget, NULL, RenderedSurface, NULL, D3DTEXF_NONE);

	if (WetWorldEffect->Enabled && currentWorldSpace && ShaderConst.WetWorld.Data.x > 0.0f) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		WetWorldEffect->SetCT();
		WetWorldEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	else if (SnowAccumulationEffect->Enabled && currentWorldSpace && ShaderConst.SnowAccumulation.Params.w > 0.0f) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		SnowAccumulationEffect->SetCT();
		SnowAccumulationEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (AmbientOcclusionEffect->Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		AmbientOcclusionEffect->SetCT();
		AmbientOcclusionEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (ShadowsExteriorsEffect->Enabled && isExterior) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		ShadowsExteriorsEffect->SetCT();
		ShadowsExteriorsEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}else if (ShadowsInteriorsEffect->Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		ShadowsInteriorsEffect->SetCT();
		ShadowsInteriorsEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (ColoringEffect->Enabled) {
		ColoringEffect->SetCT();
		ColoringEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (SpecularEffect->Enabled && isExterior) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		SpecularEffect->SetCT();
		SpecularEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (BloomEffect->Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		BloomEffect->SetCT();
		BloomEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
 	bool isCellTransition = currentCell != PreviousCell;
	if (UnderwaterEffect->Enabled && Tes->sky->GetIsUnderWater() /*TODO do this work in interior????*/) {
		if (!isCellTransition && TheRenderManager->CameraPosition.z < ShaderConst.Water.waterSettings.x) {
			ShaderConst.BloodLens.Percent = 0.0f;
			ShaderConst.WaterLens.Percent = -1.0f;
		}
		UnderwaterEffect->SetCT();
		UnderwaterEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	else {
		if (ShaderConst.WaterLens.Percent == -1.0f) ShaderConst.WaterLens.Percent = 1.0f;
		if (currentWorldSpace) {
			if (RainEffect->Enabled && ShaderConst.Rain.RainData.x > 0.0f) {
				RainEffect->SetCT();
				RainEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
			if (SnowEffect->Enabled && ShaderConst.Snow.SnowData.x > 0.0f) {
				SnowEffect->SetCT();
				SnowEffect->Render(Device, RenderTarget, RenderedSurface, false);
			}
		}
		if (GodRaysEffect->Enabled && currentWorldSpace) {
			Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
			GodRaysEffect->SetCT();
			GodRaysEffect->Render(Device, RenderTarget, RenderedSurface, false);
		}
		if (VolumetricFogEffect->Enabled && currentWorldSpace && ShaderConst.VolumetricFog.Data.w) {
			VolumetricFogEffect->SetCT();
			VolumetricFogEffect->Render(Device, RenderTarget, RenderedSurface, false);
		}
	}
	if (DepthOfFieldEffect->Enabled && ShaderConst.DepthOfField.Enabled) {
		Device->StretchRect(RenderTarget, NULL, SourceSurface, NULL, D3DTEXF_NONE);
		DepthOfFieldEffect->SetCT();
		DepthOfFieldEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (BloodLensEffect->Enabled && ShaderConst.BloodLens.Percent > 0.0f) {
		BloodLensEffect->SetCT();
		BloodLensEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (WaterLensEffect->Enabled && ShaderConst.WaterLens.Percent > 0.0f) {
		WaterLensEffect->SetCT();
		WaterLensEffect->Render(Device, RenderTarget, RenderedSurface, false);
	}
	if (MotionBlurEffect->Enabled && (ShaderConst.MotionBlur.Data.x || ShaderConst.MotionBlur.Data.y)) {
		MotionBlurEffect->SetCT();
		MotionBlurEffect->Render(Device, RenderTarget, RenderedSurface, false);
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
	else if (!strcmp(Name, "Rain")) {
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
