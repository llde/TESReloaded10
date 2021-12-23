// Low health and fatigue (stamina) fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_LowHFData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float3 LuminanceConv = { 0.2125f, 0.7154f, 0.0721f };

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

float4 HFPass(VSOUT IN) : COLOR0
{
	float3 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	
	if (TESR_LowHFData.y > 0)
	{
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord + TESR_LowHFData.y).rgb;
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord + TESR_LowHFData.y * 2).rgb;
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord - TESR_LowHFData.y).rgb;
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord - TESR_LowHFData.y * 2).rgb;
		Color = Color / 5;
	}	
	if (TESR_LowHFData.x > 0)
	{
		Color = lerp(Color, dot(Color, LuminanceConv), TESR_LowHFData.x);
	}
	if (TESR_LowHFData.z > 0)
	{
		float2 inTex = IN.UVCoord - 0.5;
		float vignette = 1 - dot(inTex, inTex);
		
		Color *= saturate(pow(abs(vignette), TESR_LowHFData.z) + TESR_LowHFData.w);
	}
	return float4(Color, 1.0f);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader  = compile ps_3_0 HFPass();
	}
}