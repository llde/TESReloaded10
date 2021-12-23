// Motion Blur fullscreen shader for Oblivion/Skyrim Reloaded

#define BlurSamples 24

float4 TESR_ReciprocalResolution;
float4 TESR_MotionBlurParams;
float4 TESR_MotionBlurData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

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

float4 MotionBlurPS(VSOUT IN) : COLOR0
{
    float2 offsetBlurDirection;
    float3 blurredColor = 0;
	float gaussianSum = 0;
	
    offsetBlurDirection.x = clamp(TESR_MotionBlurData.x, -TESR_MotionBlurParams.z, TESR_MotionBlurParams.z);
    offsetBlurDirection.y = clamp(TESR_MotionBlurData.y, -TESR_MotionBlurParams.z, TESR_MotionBlurParams.z);

    for(int i = 0; i < BlurSamples / 2; i++)
    {
        float2 lookup;
        float4 offsetColor;
        float weight = exp((i*i) / (5.0 * TESR_MotionBlurParams.x * TESR_MotionBlurParams.x)) / TESR_MotionBlurParams.x;
 
        lookup = offsetBlurDirection * TESR_ReciprocalResolution.xy * TESR_MotionBlurParams.y;
        lookup = lookup * i / BlurSamples + IN.UVCoord; 
        offsetColor = tex2D(TESR_RenderedBuffer, lookup);
        gaussianSum += weight;
        blurredColor += (offsetColor.rgb * weight);
 
        lookup = -offsetBlurDirection * TESR_ReciprocalResolution.xy * TESR_MotionBlurParams.y;
        lookup = lookup * i / BlurSamples + IN.UVCoord;
        offsetColor = tex2D(TESR_RenderedBuffer, lookup);
        gaussianSum += weight;
        blurredColor += (offsetColor.rgb * weight);
    }
 
	blurredColor = blurredColor / gaussianSum;
	return float4(blurredColor, 1);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 MotionBlurPS();
	}
 
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 MotionBlurPS();
	}
}
