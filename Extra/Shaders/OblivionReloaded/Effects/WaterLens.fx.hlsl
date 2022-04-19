// WaterLens fullscreen shader for Oblivion Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_GameTime;
float4 TESR_WaterLensData;

struct VS_OUTPUT
{
	float4 pos : POSITION0;
	float2 texCoord  : TEXCOORD0;
	float4 noiseCoord : TEXCOORD1;
};

struct PS_INPUT
{
	float2 texCoord : TEXCOORD0;
	float4 noiseCoord : TEXCOORD1;
};

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { };
sampler2D TESR_waterlensSampler : register(s1) < string ResourceName = "Effects\water_NRM_lens.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float timea = TESR_GameTime.z * TESR_WaterLensData.x;
static const float timeb = TESR_GameTime.z * TESR_WaterLensData.y;

void convToImageSpace (float4 position, out float4 oPosition, out float2 oTexCoord)
{
	position.xy = sign(position.xy);
	oPosition = float4(position.xy, 0, 1);
	oTexCoord.x = 0.5 * (1 + position.x) + 0.5 / (1.0 / TESR_ReciprocalResolution.x);
	oTexCoord.y = 0.5 * (1 - position.y) + 0.5 / (1.0 / TESR_ReciprocalResolution.y);
}

VS_OUTPUT WaterLensVS (float4 position : POSITION)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;
	
	convToImageSpace(position, Output.pos, Output.texCoord);
	Output.noiseCoord.xy = (Output.texCoord * 0.5f) + float2(sin(0.25f * timea), -0.25f * timea);
	Output.noiseCoord.zw = Output.texCoord - float2(0.0f, timeb);

	return Output;
}

float4 WaterLensPS (PS_INPUT Input) : COLOR
{
	float4 normalColor = (tex2D(TESR_waterlensSampler, Input.noiseCoord.xy) * 2.0f) - 1.0f;
	float4 animColor = (tex2D(TESR_waterlensSampler, Input.noiseCoord.zw) * 2.0f) - 1.0f;

	normalColor.z += animColor.w;
	float3 normal = normalize(normalColor.xyz);
	float3 refractionVec = normalize(normal * float3(TESR_WaterLensData.z, TESR_WaterLensData.z, 1.0f));
	float3 screenColor = tex2D(TESR_RenderedBuffer, Input.texCoord - (refractionVec.xy * 0.2f * TESR_WaterLensData.w)).xyz;
	float2 refractHighlight = refractionVec.xy * TESR_WaterLensData.w;
	float3 refColor = (saturate(pow(refractHighlight.x, 6.0f)) + saturate(pow(refractHighlight.y, 6.0f))) * float3(0.85f, 0.85f, 1.0f);

	return float4(screenColor + refColor, 1.0f);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 WaterLensVS();
		PixelShader = compile ps_3_0 WaterLensPS();
	}
}