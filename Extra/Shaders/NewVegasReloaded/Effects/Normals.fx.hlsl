float4 TESR_ReciprocalResolution;
sampler2D TESR_DepthBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

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

#include "Includes/Depth.hlsl"
#include "Includes/Helpers.hlsl"

float4 ComputeNormals(VSOUT IN) :COLOR0
{
	return float4 (compress(GetNormal(IN.UVCoord)), 1.0);
}
 
technique
{
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 ComputeNormals();
	}
}