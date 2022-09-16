float4 TESR_ReciprocalResolution;
sampler2D SourceBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

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


float4 BlurPass(VSOUT IN) : COLOR0
{
	float3 Color = 0.0f;
	float w = 0.0f;

    for (int i = 0; i < cKernelSize; i++) {
		float2 uvOffH = (BlurOffsets[i] * OffsetMaskH);
		float2 uvOffV = (BlurOffsets[i] * OffsetMaskV);
		Color += tex2D(SourceBuffer, IN.UVCoord + uvOffH).rgb * BlurWeights[i];
		Color += tex2D(SourceBuffer, IN.UVCoord + uvOffV).rgb * BlurWeights[i];
		w += 2 * BlurWeights[i];
    }
	Color /= w;
    return float4(Color, 1.0f);
}


technique {
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass();
	}


} 
