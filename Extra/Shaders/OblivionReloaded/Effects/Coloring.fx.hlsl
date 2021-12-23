// Coloring fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_ColoringColorCurve;
float4 TESR_ColoringEffectGamma;
float4 TESR_ColoringData;
float4 TESR_ColoringValues;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float3x3 XYZ_RGB  = {{0.412453, 0.357580, 0.180423},
								  {0.212671, 0.715160, 0.072169},
								  {0.019334, 0.119193, 0.950227}};		 
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

float GetLuminance( const float3 rgb )
{
    return dot( XYZ_RGB[1], rgb );
}

float4 ColorPass(VSOUT IN) : COLOR0
{
	float3 color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	float3 H = 0.01;
	
	float3 lumCoeff = float3(0.25, 0.65,0.1);
	float lum = saturate(dot(lumCoeff, color));
	float L = saturate(10 * (lum - 0.45));
	float3 result1 = min(2.0f * color * lum, 65504);
	float3 result2 = 1.0f - 2.0f * (1.0f - lum) * (1.0f - color);
	float3 newColor = lerp(result1, result2, L);
	color = lerp(color, newColor, TESR_ColoringValues.z);

	color = pow(abs(color), TESR_ColoringValues.w);
	color = lerp(H, color, TESR_ColoringData.w);

	float y = 1.0 / (1.0 + exp(TESR_ColoringColorCurve.y / 2.0));
	float z = 1.0 / (1.0 + exp(TESR_ColoringColorCurve.z / 2.0));
	float w = 1.0 / (1.0 + exp(TESR_ColoringColorCurve.w / 2.0));
	float v = 1.0 / (1.0 + exp(TESR_ColoringColorCurve.x / 2.0));
	
	float3 luminance = GetLuminance(color);
	luminance.r = (1.0 / (1.0 + exp(-TESR_ColoringColorCurve.y * (luminance.r - 0.5))) - y) / (1.0 - 2.0 * y);
	luminance.g = (1.0 / (1.0 + exp(-TESR_ColoringColorCurve.z * (luminance.g - 0.5))) - z) / (1.0 - 2.0 * z);
	luminance.b = (1.0 / (1.0 + exp(-TESR_ColoringColorCurve.w * (luminance.b - 0.5))) - w) / (1.0 - 2.0 * w);
	luminance = pow(abs(luminance), 1.0 / TESR_ColoringEffectGamma.x);

	float3 luminancei = 1.0 - luminance;
	luminance = lerp(luminance, luminancei, TESR_ColoringValues.y);
	luminance.r = pow(abs(luminance.r), 1.0 / TESR_ColoringEffectGamma.y);
	luminance.g = pow(abs(luminance.g), 1.0 / TESR_ColoringEffectGamma.z);
	luminance.b = pow(abs(luminance.b), 1.0 / TESR_ColoringEffectGamma.w);
	
	color = pow(abs(color), 1.0 / TESR_ColoringData.y);
	float3 color2 = color;

	if (luminance.r < 0.5)
		color2.r = (2.0 * luminance.r - 1.0) * (color.r - color.r * color.r) + color.r;
	else
		color2.r = (2.0 * luminance.r - 1.0) * (sqrt(color.r) - color.r) + color.r;

	if (luminance.g < 0.5)
		color2.g = (2.0 * luminance.g - 1.0) * (color.g - color.g * color.g) + color.g;
	else
		color2.g = (2.0 * luminance.g - 1.0) * (sqrt(color.g) - color.g) + color.g;

	if (luminance.b < 0.5)
		color2.b = (2.0 * luminance.b - 1.0) * (color.b - color.b * color.b) + color.b;
	else
		color2.b = (2.0 * luminance.b - 1.0) * (sqrt(color.b) - color.b) + color.b;

	float3 color3 = lerp(color, color2, TESR_ColoringData.x);
	color3 = (1.0 / (1.0 + exp(-TESR_ColoringColorCurve.x * (color3 - 0.5))) - v) / (1.0 - 2.0 * v);

	float r2R = 1.0 - TESR_ColoringValues.x;
	float g2R = 0.0 + TESR_ColoringValues.x;
	float b2R = 0.0 + TESR_ColoringValues.x;

	float r2G = 0.0 + TESR_ColoringValues.x;
	float g2G = (1.0 - TESR_ColoringData.z) - TESR_ColoringValues.x;
	float b2G = (0.0 + TESR_ColoringData.z) + TESR_ColoringValues.x;

	float r2B = 0.0 + TESR_ColoringValues.x;
	float g2B = (0.0 + TESR_ColoringData.z) + TESR_ColoringValues.x;
	float b2B = (1.0 - TESR_ColoringData.z) - TESR_ColoringValues.x;

	color3.r = (color3.r * r2R + color3.g * g2R + color3.b * b2R);
	color3.g = (color3.r * r2G + color3.g * g2G + color3.b * b2G);
	color3.b = (color3.r * r2B + color3.g * g2B + color3.b * b2B);

	float luminance2 = GetLuminance(color3);
	float3 color4 = color3;

	if (luminance2 < 0.5)
		color4 = (2.0 * luminance2 - 1.0) * (color3 - color3 * color3) + color3;
	else
		color4 = (2.0 * luminance2 - 1.0) * (sqrt(color3) - color3) + color3;

	color4 = pow(abs(color4), 1.0 / TESR_ColoringValues.w);

	return float4(lerp(color, color4, TESR_ColoringData.x), 1.0f);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader  = compile ps_3_0 ColorPass();
	}
}