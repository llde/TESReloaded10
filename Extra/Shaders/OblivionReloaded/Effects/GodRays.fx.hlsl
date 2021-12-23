// GodRays full screen shader for Oblivion/Skyrim Reloaded

float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_CameraForward;
float4 TESR_SunDirection;
float4 TESR_GameTime;
float4 TESR_SunColor;
float4 TESR_SunAmount;
float4 TESR_GodRaysRay;
float4 TESR_GodRaysRayColor;
float4 TESR_GodRaysData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float4 sp = TESR_SunDirection * 999999;
static const float2 texproj = 0.5f * float2(1.0f, -TESR_ReciprocalResolution.y / TESR_ReciprocalResolution.x) / tan(radians(TESR_ReciprocalResolution.w) * 0.5f);
static const float d = dot(TESR_CameraForward, sp);
static const float2 sunview_v = mul(sp / d, TESR_ViewTransform).xy;
static const float2 sunview = float2(0.5f, 0.5f) + sunview_v.xy * texproj;
static const float raspect = 1.0f / TESR_ReciprocalResolution.z;

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float forward = dot(-TESR_SunDirection, TESR_CameraForward);
static const int ShaftPasses = int(TESR_GodRaysData.x);
 
struct VSOUT {
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};
 
struct VSIN {
	float4 vertPos : POSITION0;
	float2 UVCoord : TEXCOORD0;
};
 
VSOUT FrameVS(VSIN IN) {
	VSOUT OUT = (VSOUT)0.0f;
	OUT.vertPos = IN.vertPos;
	OUT.UVCoord = IN.UVCoord;
	return OUT;
}

float readDepth01(in float2 coord : TEXCOORD0) {
	
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	return (2.0f * nearZ) / (nearZ + farZ - posZ * (farZ - nearZ));
	
}

float4 RayMask(VSOUT IN) : COLOR0 {
	
	float3 color = 0.0f;
	
	if (forward < 0.0f) {
		float depth = readDepth01(IN.UVCoord);
		color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb * depth * TESR_GodRaysData.y;
	}
	return float4(color, 1.0f);
}

float4 LightShaft(VSOUT IN) : COLOR0 {
	
	float2 DeltaTexCoord = IN.UVCoord - sunview.xy;
	float screendist = length(DeltaTexCoord * float2(1.0f, raspect));
	DeltaTexCoord /= screendist;
    DeltaTexCoord *= 0.5f * min(0.3f, screendist) * (1.0f / TESR_GodRaysData.x) * TESR_GodRaysRay.z;
	float3 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	float IlluminationDecay = 1.0f;
    float2 samplepos = IN.UVCoord;
	
	[unroll(100)]
	for (int i = 0; i < ShaftPasses; i++) {
		samplepos -= DeltaTexCoord;
		float3 Sample = tex2D(TESR_RenderedBuffer, samplepos).rgb;
		Sample *= IlluminationDecay * TESR_GodRaysRay.w;
		Color += Sample;
		IlluminationDecay *= TESR_GodRaysRay.y;
	}
	Color *= TESR_GodRaysRay.x / TESR_GodRaysData.x;
	return float4(Color, 1.0f);
}

float3 BlendSoftLight(float3 a, float3 b)
{
	float3 c = 2.0f * a * b * (1.0f + a * (1.0f - b));
	float3 a_sqrt = sqrt(a);
	float3 d = (a + b * (a_sqrt - a)) * 2.0f - a_sqrt;
	return (b < 0.5f) ? c : d;
}

float4 SunCombine(VSOUT IN) : COLOR0
{
	float Amount = 1.0f;
	if (TESR_GodRaysData.w) Amount = (TESR_GameTime.y < 12.00f) ? TESR_SunAmount.x : TESR_SunAmount.z;
	float4 ori = tex2D(TESR_SourceBuffer, IN.UVCoord);
	float4 shaft = tex2D(TESR_RenderedBuffer, IN.UVCoord) * TESR_GodRaysData.z * Amount;
	float3 ray = TESR_SunColor.rgb * TESR_GodRaysRayColor.rgb;
	shaft.rgb *= (-forward) * ray * saturate(1.0f - ori.rgb);

	float4 color = ori + shaft;
	color.rgb = BlendSoftLight(color.rgb, (ray * TESR_GodRaysRayColor.a * Amount + 0.5f));
	return float4(color.rgb, 1.0f);
}
 
technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 RayMask(); 
	}
 
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		Pixelshader = compile ps_3_0 LightShaft(); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		Pixelshader = compile ps_3_0 SunCombine();
	}
}