// BloodLens fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_BloodLensParams;
float4 TESR_BloodLensColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_BloodLensSampler : register(s1) < string ResourceName = "Effects\bloodlens.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float Shininess = 2.5;

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

float4 BloodLensPS (VSOUT IN) : COLOR
{
	float3 sColor = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	float2 texCoordWarp = tex2D(TESR_BloodLensSampler, IN.UVCoord + float2(TESR_BloodLensParams.x + 0.25, TESR_BloodLensParams.x - 0.25)).xy * TESR_BloodLensParams.z;
	
	float scaledNoise = saturate((tex2D(TESR_BloodLensSampler, IN.UVCoord + texCoordWarp + float2(TESR_BloodLensParams.x, -TESR_BloodLensParams.x)).w - TESR_BloodLensParams.y));
	scaledNoise = lerp(0, TESR_BloodLensParams.w, scaledNoise);

	float3 normals = normalize(float3(ddx(scaledNoise), ddy(scaledNoise), 0.1));
	normals = pow(abs(normals),3);
	
	float3 resultColor = saturate(sColor - scaledNoise) + (scaledNoise * TESR_BloodLensColor.rgb);
	float3 refColor = pow(normals.x, Shininess) * (TESR_BloodLensColor.rgb * 0.5);
	return float4(resultColor + refColor, 1);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BloodLensPS();
	}
}