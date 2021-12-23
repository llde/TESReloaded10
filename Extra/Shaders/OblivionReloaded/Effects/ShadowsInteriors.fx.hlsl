// Image space shadows shader for Oblivion Reloaded

float4x4 TESR_WorldTransform;
float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4 TESR_CameraPosition;
float4 TESR_ShadowData;
float4 TESR_ShadowLightPosition0;
float4 TESR_ShadowLightPosition1;
float4 TESR_ShadowLightPosition2;
float4 TESR_ShadowLightPosition3;
float4 TESR_ShadowCubeMapBlend;
float4 TESR_ReciprocalResolution;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer0 : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer1 : register(s4) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer2 : register(s5) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
samplerCUBE TESR_ShadowCubeMapBuffer3 : register(s6) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; ADDRESSW = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;
static const float BIAS = 0.0015f;
static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);

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

static const int cKernelSize = 7;

static const float BlurWeights[cKernelSize] = 
{
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
};
 
static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.y),
	float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.y),
	float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.y),
	float2( 0.0f * TESR_ReciprocalResolution.x,  0.0f * TESR_ReciprocalResolution.y),
	float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.y),
	float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.y),
	float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.y),
};

float readDepth(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	posZ = Zmul / ((posZ * Zdiff) - farZ);
	return posZ;
}

float3 toWorld(float2 tex)
{
    float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
    v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
    v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
    return v;
}

float Lookup(samplerCUBE ShadowCubeMapBuffer, float3 LightDir, float Distance, float Blend) {
	 
	float Shadow = texCUBE(ShadowCubeMapBuffer, LightDir).r;
	if (Shadow > 0.0f && Shadow < 1.0f && Shadow < Distance - BIAS) return Blend;
	return 1.0f;
	
}

float GetLightAmount(samplerCUBE ShadowCubeMapBuffer, float4 WorldPos, float4 LightPos, float Blend) {
	
	float Shadow = 0.0f;
	float3 LightDir;
	float Distance;
	
	LightDir = WorldPos.xyz - LightPos.xyz; 
	LightDir.z *= -1;
	Distance = length(LightDir);
	LightDir = LightDir / Distance;
	Distance = Distance / LightPos.w;
	Blend = max(1.0f - Blend, saturate(Distance) * TESR_ShadowData.y);
	return Lookup(ShadowCubeMapBuffer, LightDir, Distance, Blend);
	
}

float4 Shadow( VSOUT IN ) : COLOR0 {

	float Shadow = 1.0f;
	float depth = readDepth(IN.UVCoord);
    float3 camera_vector = toWorld(IN.UVCoord) * depth;
    float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);	
	
	float4 pos = mul(world_pos, TESR_WorldTransform);
	Shadow = GetLightAmount(TESR_ShadowCubeMapBuffer0, pos, TESR_ShadowLightPosition0, TESR_ShadowCubeMapBlend.x);
	if (TESR_ShadowLightPosition1.w) Shadow *= GetLightAmount(TESR_ShadowCubeMapBuffer1, pos, TESR_ShadowLightPosition1, TESR_ShadowCubeMapBlend.y);
	if (TESR_ShadowLightPosition2.w) Shadow *= GetLightAmount(TESR_ShadowCubeMapBuffer2, pos, TESR_ShadowLightPosition2, TESR_ShadowCubeMapBlend.z);
	if (TESR_ShadowLightPosition3.w) Shadow *= GetLightAmount(TESR_ShadowCubeMapBuffer3, pos, TESR_ShadowLightPosition3, TESR_ShadowCubeMapBlend.w);
    return float4(Shadow, Shadow, Shadow, 1.0f);
	
}

float4 BlurPass(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float3 Color = 0.0f;
	float w = 0.0f;

    for (int i = 0; i < cKernelSize; i++) {
		float2 uvOff = (BlurOffsets[i] * OffsetMask);
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff).rgb * BlurWeights[i];
		w += BlurWeights[i];
    }
	Color /= w;
    return float4(Color, 1.0f);
}

float4 CombineShadow( VSOUT IN ) : COLOR0 {

	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float Shadow = tex2D(TESR_RenderedBuffer, IN.UVCoord).r;
	
	color.rgb *= Shadow;
    return float4(color, 1.0f);
	
}

technique {
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Shadow();
	}
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass(OffsetMaskH);
	}
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass(OffsetMaskV);
	}
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 CombineShadow();
	}
	
}
