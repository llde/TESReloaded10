// Cinema fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_CinemaData;

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

float4 CinemaPass(VSOUT IN) : COLOR0
{
	float3 color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	
	if (TESR_CinemaData.y > 0)
	{
		float2 inTex = IN.UVCoord - 0.5;
		float vignette = 1 - dot(inTex, inTex);
		
		color *= saturate(pow(abs(vignette), TESR_CinemaData.y) + TESR_CinemaData.z);
	}
	if (TESR_CinemaData.x > 0)
	{
		float h = (1 - TESR_ReciprocalResolution.z / TESR_CinemaData.x) / 2;
		
		if (IN.UVCoord.y < h || IN.UVCoord.y > 1 - h) color *= 0;
	}
	
	return float4(color, 1.0f);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader  = compile ps_3_0 CinemaPass();
	}
}