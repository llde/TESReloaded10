// GodRays full screen shader for Oblivion/Skyrim Reloaded

// float4x4 TESR_ViewTransform;
// float4x4 TESR_ProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_CameraForward;
float4 TESR_SunDirection;
float4 TESR_GameTime;
float4 TESR_SunColor;
float4 TESR_SunAmount;
float4 TESR_GodRaysRay;
float4 TESR_GodRaysRayColor;
float4 TESR_GodRaysData;
float4 TESR_DebugVar;
float4 TESR_ViewSpaceLightDir;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

#include "Includes/Helpers.hlsl"
#include "Includes/Depth.hlsl"

static const float raspect = 1.0f / TESR_ReciprocalResolution.z;
static const float samples = 16;
static const float stepLength = 1/samples;
static const float scale = 0.5;


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

float4 SkyMask(VSOUT IN) : COLOR0 {
	
	float2 uv = IN.UVCoord / scale;
	clip((uv <= 1) - 1);

	float depth = (readDepth(uv) / farZ) > 0.98;
	float3 color = tex2D(TESR_SourceBuffer, uv).rgb * depth;

	return float4(color, 1.0f);
}


float4 LightMask(VSOUT IN) : COLOR0 {
	
	float2 uv = IN.UVCoord;
	clip((uv <= scale) - 1);

	float3 color;
	color = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-1, -1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-1, 1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(1, -1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(1, 1) * TESR_ReciprocalResolution.xy).rgb;

	color /= 4;

	float threshold = TESR_DebugVar.y; // 0.55
	float brightness = luma(color);

	float contribution = max(0.0, brightness - threshold);
	float nmax = 1;
	float bloomScale = TESR_DebugVar.z; //0.8

	float bloom = bloomScale * sqr(contribution) / brightness;

	return float4(bloom * color * 100, 1.0f);
}


float4 RadialBlur(VSOUT IN, uniform float step, uniform float attenuation) : COLOR0 {
	float2 uv = IN.UVCoord;
	clip((uv <= scale) - 1);
	uv /= scale; // restore uv scale to do calculations in [0, 1] space

	// calculate vector from pixel to sun along which we'll sample
	float2 sunPos = projectPosition(TESR_ViewSpaceLightDir.xyz * farZ).xy;
	float2 blurDirection = (sunPos.xy - uv) * float2(1.0f, raspect) * TESR_DebugVar.w; // apply aspect ratio correction
	float distance = length(blurDirection);
	clip((distance < 1) -1);

	float2 dir = blurDirection/distance;
	float maxStep = distance/step + 1;

	// sample the light clamped image from the pixel to the sun for the given amount of samples
	float2 samplePos = uv;
	float4 color = tex2D(TESR_RenderedBuffer, samplePos * scale);
	float total = 1;
	for (float i=1; i <= samples; i++){
		float length = min(step * i, distance); // clamp sampling vector to the distance from the pixel to the sun
		samplePos = uv + (dir * length / float2(1, raspect)); // apply aspect ratio correctly
		float doStep = (i <= maxStep && samplePos > 0 && samplePos < 1); // check if we haven't overshot the sun position or exited the screen
		
		color += tex2D(TESR_RenderedBuffer, samplePos * scale) * doStep;
		total += doStep;
	}
	color /= total;

	return float4(color.rgb, 1);
}


float3 BlendSoftLight(float3 a, float3 b)
{
	float3 c = 2.0f * a * b * (1.0f + a * (1.0f - b));
	float3 a_sqrt = sqrt(a);
	float3 d = (a + b * (a_sqrt - a)) * 2.0f - a_sqrt;
	return (b < 0.5f) ? c : d;
}

float4 Combine(VSOUT IN) : COLOR0
{
	float scale = 0.5;
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	float2 uv = IN.UVCoord * scale;
	float4 rays = tex2D(TESR_RenderedBuffer, uv);

	rays *= TESR_SunColor;


	return float4(color.rgb + rays.rgb, 1.0f);
}
 
technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 SkyMask(); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 LightMask(); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 RadialBlur(stepLength, 1); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 RadialBlur(stepLength * stepLength, 1); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		Pixelshader = compile ps_3_0 Combine();
	}
}