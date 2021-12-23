// Bloom for Oblivion Reloaded

#define viewbloom 0

float4 TESR_ReciprocalResolution;
float4 TESR_BloomData;
float4 TESR_BloomValues;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

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

static const int cKernelSize = 13;

static const float BlurWeights[cKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};
 
static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-6.0f * TESR_ReciprocalResolution.x, -6.0f * TESR_ReciprocalResolution.y),
	float2(-5.0f * TESR_ReciprocalResolution.x, -5.0f * TESR_ReciprocalResolution.y),
	float2(-4.0f * TESR_ReciprocalResolution.x, -4.0f * TESR_ReciprocalResolution.y),
	float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.y),
	float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.y),
	float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.y),
	float2( 0.0f * TESR_ReciprocalResolution.x,  0.0f * TESR_ReciprocalResolution.y),
	float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.y),
	float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.y),
	float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.y),
	float2( 4.0f * TESR_ReciprocalResolution.x,  4.0f * TESR_ReciprocalResolution.y),
	float2( 5.0f * TESR_ReciprocalResolution.x,  5.0f * TESR_ReciprocalResolution.y),
	float2( 6.0f * TESR_ReciprocalResolution.x,  6.0f * TESR_ReciprocalResolution.y)
};

float3 AdjustSaturation(float3 color, float saturation)
{
	float grey = dot(color, float3(0.3, 0.59, 0.11));
	
	return lerp(grey, color, saturation);
}

float4 BloomPass(VSOUT IN) : COLOR0
{
    float3 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;

    Color *= TESR_BloomData.y / (TESR_BloomData.x + 0.001);
    Color *= (1 + (Color / (TESR_BloomData.z * TESR_BloomData.z)));
    Color -= 5;
    Color /= (10 + max(Color, 0));

    return float4(Color, 1);
}

float4 BlurPass(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float3 Color = 0;
 
    for (int i = 0; i < cKernelSize; i++)
    {
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord + BlurOffsets[i] * OffsetMask).rgb * BlurWeights[i];
    }

    return float4(Color, 1.0f);
}

float4 CombinePass(VSOUT IN) : COLOR0
{
	float3 bloomColor = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	float3 originalColor = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	
	bloomColor = AdjustSaturation(bloomColor, TESR_BloomValues.z) * TESR_BloomValues.x;
	originalColor = AdjustSaturation(originalColor, TESR_BloomValues.w) * TESR_BloomValues.y;
	originalColor *= (1 - saturate(bloomColor));
	
	#if viewbloom
		return float4(bloomColor, 1.0f);
	#endif
	
	return float4(originalColor + bloomColor, 1.0f);
}
 
technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BloomPass();
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass( OffsetMaskH );
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass( OffsetMaskV );
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 CombinePass();
	}
}