// Volumetric Fog fullscreen shader for Oblivion/Skyrim Reloaded

float4x4 TESR_ProjectionTransform; 
float4 TESR_FogColor;
float4 TESR_FogData;
float4 TESR_VolumetricFogData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float depthRange = nearZ - farZ;

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

float readDepth(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	return (2.0f * nearZ) / (nearZ + farZ - posZ * (farZ - nearZ));
}

float4 VolumetricFog(VSOUT IN) : COLOR0 {
	
	float3 color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
    float depth = readDepth(IN.UVCoord);
	float distance = depth * depthRange;
	float FogAmount = 1.0f - exp(-max(0.0f, distance - TESR_FogData.x) / ((TESR_FogData.y - TESR_FogData.x) * TESR_VolumetricFogData.x));
	
	color = lerp(color, TESR_FogColor.rgb * TESR_VolumetricFogData.y, FogAmount * TESR_VolumetricFogData.z);
	return float4(color, 1.0f);
	
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader  = compile ps_3_0 VolumetricFog();
	}
}