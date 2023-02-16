// Image space shadows shader for Oblivion Reloaded

float4x4 TESR_WorldTransform;
float4 TESR_ShadowData;
float4 TESR_ShadowFade;
float4 TESR_ShadowLightPosition0;
float4 TESR_ShadowLightPosition1;
float4 TESR_ShadowLightPosition2;
float4 TESR_ShadowLightPosition3;
float4 TESR_ShadowLightPosition4;
float4 TESR_ShadowLightPosition5;
float4 TESR_ShadowLightPosition6;
float4 TESR_ShadowLightPosition7;
float4 TESR_ShadowLightPosition8;
float4 TESR_ShadowLightPosition9;
float4 TESR_ShadowLightPosition10;
float4 TESR_ShadowLightPosition11;
float4 TESR_LightAttenuation0;
float4 TESR_LightAttenuation1;
float4 TESR_LightAttenuation2;
float4 TESR_LightAttenuation3;
float4 TESR_LightAttenuation4;
float4 TESR_LightAttenuation5;
float4 TESR_LightAttenuation6;
float4 TESR_LightAttenuation7;
float4 TESR_ShadowCubeMapBlend;
float4 TESR_ReciprocalResolution;
//sampler_state removed to avoid a artifact. TODO investigate
sampler2D TESR_RenderedBuffer : register(s0);// = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1);// = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2);// = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer0 : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer1 : register(s4) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer2 : register(s5) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer3 : register(s6) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer4 : register(s7) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer5 : register(s8) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer6 : register(s9) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer7 : register(s10) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer8 : register(s11) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer9 : register(s12) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer10: register(s13) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer11 : register(s14) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_NormalsBuffer : register(s15) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

#include "Includes/Blending.hlsl"
#include "Includes/Depth.hlsl"
#include "Includes/Normals.hlsl"


static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;
static const float BIAS = 0.005f;
static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);
static const float LIGHTRADIUS = 250;
static const float MAXDISTANCE = 4000;

struct VSOUT
{
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

struct VSIN
{
	float4 vertPos : POSITION0;
	float2 UVCoord : TEXCOORD0;
};

VSOUT FrameVS(VSIN IN)
{
	VSOUT OUT = (VSOUT)0.0f;
	OUT.vertPos = IN.vertPos;
	OUT.UVCoord = IN.UVCoord;
	return OUT;
}

#include "Includes/Blur.hlsl"

float GetLightAmountValue(samplerCUBE ShadowCubeMapBuffer, float3 LightDir, float Distance) {
	float lightDepth = texCUBE(ShadowCubeMapBuffer, LightDir).r;

	float Shadow = lightDepth + BIAS > Distance;

	return lerp(1, Shadow, lightDepth > 0.0f && lightDepth < 1.0f);
}

// returns a value from 0 to 1 based on the positions of a value between a min/max 
float invLerp(float from, float to, float value){
  return (value - from) / (to - from);
}

float GetLightAmount(samplerCUBE ShadowCubeMapBuffer, float4 WorldPos, float4 LightPos, float4 normal, float4 attenuation) {
	float LightAmount = 0.0f;
	float3 LightDir;
	float Distance;
	
	LightDir = LightPos.xyz - WorldPos.xyz;
	float3 LightUV = LightDir * float3(-1, -1, 1);

	Distance = length(LightDir);
	LightDir = normalize(LightDir);
	Distance = Distance / LightPos.w;

	float radius = 1;
	float atten = saturate(1/((Distance/radius + 1) * (Distance/radius + 1))) ;
	// float atten = saturate(1/(attenuation.x + Distance * attenuation.y + Distance * Distance * attenuation.z)) * 0.01;

	// return atten;

	// return GetLightAmountValue(ShadowCubeMapBuffer, LightDir, Distance);
	// float atten = saturate(1/(Distance * Distance)) * 0.5;
	float diffuse = dot(LightDir, normal);

	LightAmount = GetLightAmountValue(ShadowCubeMapBuffer, LightUV, Distance) * diffuse * atten;
	// LightAmount = lerp(1, GetLightAmountValue(ShadowCubeMapBuffer, LightDir, Distance) * atten, attenuation.w);
	// LightAmount = lerp(1, GetLightAmountValue(ShadowCubeMapBuffer, LightDir, Distance) * atten, attenuation.w);
	// LightAmount = GetLightAmountValue(ShadowCubeMapBuffer, LightDir, Distance) * atten;

	return saturate(LightAmount);
}


float4 Shadow( VSOUT IN ) : COLOR0 {

	float Shadow = 1.0f;
	float depth = readDepth(IN.UVCoord);
    float3 camera_vector = toWorld(IN.UVCoord) * depth;
    float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);	
	
	float4 pos = mul(world_pos, TESR_WorldTransform);

	float4 normal = float4(GetWorldNormal(IN.UVCoord), 1);

	Shadow = GetLightAmount(TESR_ShadowCubeMapBuffer0, pos, TESR_ShadowLightPosition0, normal, TESR_LightAttenuation0);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer1, pos, TESR_ShadowLightPosition1, normal, TESR_LightAttenuation1);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer2, pos, TESR_ShadowLightPosition2,normal,  TESR_LightAttenuation2);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer3, pos, TESR_ShadowLightPosition3, normal, TESR_LightAttenuation3);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer4, pos, TESR_ShadowLightPosition4, normal, TESR_LightAttenuation4);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer5, pos, TESR_ShadowLightPosition5, normal, TESR_LightAttenuation5);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer6, pos, TESR_ShadowLightPosition6, normal, TESR_LightAttenuation6);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer7, pos, TESR_ShadowLightPosition7, normal, TESR_LightAttenuation7);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer8, pos, TESR_ShadowLightPosition8, normal, TESR_LightAttenuation7);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer9, pos, TESR_ShadowLightPosition9, normal, TESR_LightAttenuation7);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer10, pos, TESR_ShadowLightPosition10, normal, TESR_LightAttenuation7);
	Shadow += GetLightAmount(TESR_ShadowCubeMapBuffer11, pos, TESR_ShadowLightPosition11, normal, TESR_LightAttenuation7);

	Shadow = lerp(Shadow, 1.0, saturate(invLerp(300, MAXDISTANCE, depth))); // fade shadows with distance
	
	return float4(Shadow, Shadow, Shadow, 1.0f);
	
}

float Luma(float3 input)
{
	return input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
}

float4 CombineShadow( VSOUT IN ) : COLOR0 {

	// combine Shadow pass and source using an overlay mode + alpha blending
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);

	//multiply by 2 to only use the lower half of values to impact darkness
	float4 Shadow = saturate(tex2D(TESR_RenderedBuffer, IN.UVCoord).r * 2);
    Shadow = saturate(lerp(1, Shadow, TESR_ShadowData.y * TESR_ShadowFade.y)); // shadow darkness (shadowFade.y is set to 0 when shadows are disabled)

	Shadow *= color;

	float lumaDiff = saturate(invLerp(Luma(Shadow), 1.0f, Luma(color)));
	return lerp(Shadow, color, lumaDiff); // bring back some of the original color based on luma (brightest lights will come through)
}

technique {
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Shadow();
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurRChannel(float2(1.0f, 0.0f), 1, 5, MAXDISTANCE);
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurRChannel(float2(0.0f, 1.0f), 1, 5, MAXDISTANCE);
	}
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 CombineShadow();
	}
	
}
