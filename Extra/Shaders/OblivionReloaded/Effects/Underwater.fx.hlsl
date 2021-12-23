// Underwater fullscreen shader for Oblivion Reloaded

float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_CameraPosition;
float4 TESR_SunDirection;
float4 TESR_GameTime;
float4 TESR_WaterCoefficients;
float4 TESR_SunColor;
float4 TESR_FogColor;
float4 TESR_WaterVolume;
float4 TESR_WaveParams;
float4 TESR_WaterSettings;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_WaterHeightMapBuffer : register(s2) = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = NONE; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float rangeZ = farZ - nearZ;
static const float frame = TESR_GameTime.z * TESR_WaveParams.z * 1.5;

static const float4x4 ditherMat = { 0.0588, 0.5294, 0.1765, 0.6471,
									0.7647, 0.2941, 0.8824, 0.4118,
									0.2353, 0.7059, 0.1176, 0.5882,
									0.9412, 0.4706, 0.8235, 0.3259 };
									
struct VSOUT {
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

struct VSIN {
	float4 vertPos : POSITION0;
	float2 UVCoord : TEXCOORD0;
};

VSOUT FrameVS(VSIN IN) {
	VSOUT OUT = (VSOUT)0.0f;
	OUT.vertPos = IN.vertPos;
	OUT.UVCoord = IN.UVCoord;
	return OUT;
}

float3 toWorld(float2 tex) {
	
    float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
    v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
    v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
    return v;
	
}

float readDepth(in float2 coord : TEXCOORD0) {
	
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	posZ = Zmul / ((posZ * rangeZ) - farZ);
	return posZ;
	
}

float4 Water( VSOUT IN ) : COLOR0 {
	
	float3 eyepos = float3(TESR_CameraPosition.x, TESR_CameraPosition.y, TESR_CameraPosition.z - TESR_WaterSettings.x);	
	
    float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
    float depth = readDepth(IN.UVCoord);
    float3 camera_vector = toWorld(IN.UVCoord);
	float3 norm_camera_vector = normalize(camera_vector);
	
	float causticsStrength = TESR_WaterVolume.x;
	float shoreFactor = TESR_WaterVolume.y;
	float turbidity = TESR_WaterVolume.z;
	float3 extCoeff = TESR_WaterCoefficients.xyz * turbidity;
	float scattCoeff = TESR_WaterCoefficients.w * turbidity;
	float waveWidth = TESR_WaveParams.y;
	float depthDarkness = TESR_WaterSettings.y;
	
    float3 world_pos = eyepos + camera_vector * depth;
	float uw_pos = world_pos.z / camera_vector.z;
	float2 screenPos = IN.UVCoord / TESR_ReciprocalResolution.xy;
	float eyeDist = eyepos.z / camera_vector.z;
	bool clipping = eyeDist > nearZ;
	
	float4 water_result = color;
	
	if (clipping && world_pos.z < 0 && eyepos.z >= 0) {
		//Caustics
		float3 dx = ddx(world_pos);
    	float3 dy = ddy(world_pos);
    	float3 waterfloorNorm = normalize(cross(dx,dy));
		float3 causticsPos = world_pos - TESR_SunDirection.xyz * (world_pos.z / TESR_SunDirection.z);
		float caustics = causticsStrength * tex2D(TESR_WaterHeightMapBuffer, causticsPos.xy / (624 * waveWidth)).b;
		caustics += causticsStrength * 0.6 * tex2D(TESR_WaterHeightMapBuffer, causticsPos.xy / (1248 * waveWidth)).b;
		float causticsAngle = saturate(dot(-waterfloorNorm, TESR_SunDirection.xyz));
		water_result.rgb *= 1 + caustics * causticsAngle * TESR_SunColor.rgb;
		
		//Volume color
		float SinBoverSinA = -norm_camera_vector.z;
		float3 waterVolColor = scattCoeff * TESR_FogColor.xyz / (extCoeff * (1 + SinBoverSinA));
		waterVolColor *= 1 - exp(-extCoeff * (1 + SinBoverSinA) * uw_pos / 70);
		
		//Refraction
		water_result.rgb *= exp(-extCoeff * (uw_pos - world_pos.z) / 70);
		water_result.rgb += waterVolColor;	
	}
	else if (eyepos.z < 0) {
		//Caustics
		if (world_pos.z < 0) {
			float sunDist = max(-world_pos.z / TESR_SunDirection.z, 0);
			float3 dx = ddx(world_pos);
			float3 dy = ddy(world_pos);
			float3 waterfloorNorm = normalize(cross(dx,dy));
			float3 causticsPos = world_pos + TESR_SunDirection.xyz * sunDist;
			float caustics = causticsStrength * tex2D(TESR_WaterHeightMapBuffer, causticsPos.xy / (624 * waveWidth)).b;
			caustics += causticsStrength * 0.6 * tex2D(TESR_WaterHeightMapBuffer, causticsPos.xy / (1248 * waveWidth)).b;
			float causticsAngle = saturate(dot(-waterfloorNorm, TESR_SunDirection.xyz));
			water_result.rgb *= 1 + caustics * causticsAngle * TESR_SunColor.rgb;
		}
		
		//Volume color
		float SinBoverSinA = abs(norm_camera_vector.z);
		float3 waterVolColor = scattCoeff * TESR_FogColor.xyz / (extCoeff * (1 + SinBoverSinA));
		waterVolColor *= 1 - exp(-extCoeff * (1 + SinBoverSinA) * depth / 70);
		waterVolColor *= exp(extCoeff * (1 + SinBoverSinA) * eyepos.z * depthDarkness / 70) - exp(-extCoeff * (1 + SinBoverSinA) * depth / 70);
		
		//Refraction
		water_result.rgb *= exp(-extCoeff * depth / (100 * depthDarkness));
		water_result.rgb += waterVolColor;
		
		if (clipping && world_pos.z > 0) water_result.rgb = color.rgb;
	}
	
	water_result.rgb += ditherMat[ screenPos.x%4 ][ screenPos.y%4 ] / 255;
	
	color.rgb = water_result.rgb;
	color.a = 1;
    return color;
	
}

float4 WaterDistortion( VSOUT IN ) : COLOR0 {
	
	float3 eyepos = float3(TESR_CameraPosition.x, TESR_CameraPosition.y, TESR_CameraPosition.z - TESR_WaterSettings.x);	
	
	if (eyepos.z < 0) {
		IN.UVCoord.x += sin(frame * 3 + IN.UVCoord.x * 20) * 0.002f;
		IN.UVCoord.y += cos(frame * 3 + IN.UVCoord.y * 20) * 0.002f;
	}
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	color.a = 1;
    return color;
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Water();
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 WaterDistortion();
	}	
}