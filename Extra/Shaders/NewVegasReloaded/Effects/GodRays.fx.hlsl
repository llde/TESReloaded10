// GodRays full screen shader for Oblivion/Skyrim Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_GameTime;
float4 TESR_SunColor;
float4 TESR_SunAmount;
float4 TESR_GodRaysRay; // x: intensity, y:length, z: density, w: visibility
float4 TESR_GodRaysRayColor; // x:r, y:g, z:b, w:saturate
float4 TESR_GodRaysData; // x: passes amount, y: luminance, z:multiplier, w: time enabled
float4 TESR_DebugVar;
float4 TESR_ViewSpaceLightDir; // view space light vector
float4 TESR_SunDirection; // worldspace sun vector
float4 TESR_ShadowFade; // attenuation factor of sunsets/sunrises and moon phases

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

#include "Includes/Helpers.hlsl"
#include "Includes/Depth.hlsl"

static const float raspect = 1.0f / TESR_ReciprocalResolution.z;
static const float samples = 10;
static const float stepLength = 1/samples;
static const float scale = 0.5;

static const float lumTreshold = TESR_GodRaysData.y;
static const float multiplier = TESR_GodRaysData.z;
static const float intensity = TESR_GodRaysRay.x;
static const float stepLengthMult = TESR_GodRaysRay.y;
static const float glareReduction = TESR_GodRaysRay.z;
static const float godrayCurve = TESR_GodRaysRay.w;


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

	float depth = (readDepth(uv) / farZ) > 0.98; //only pixels belonging to the sky will register
	float3 sunGlare = pows(dot(TESR_ViewSpaceLightDir.rgb, normalize(reconstructPosition(uv))), 18) * 500; // fake sunglare computed from light direction
	float sunSetFade = 1 - TESR_ShadowFade.x; //grows to 1 at the height of sunset
	float3 color = (1 - saturate(tex2D(TESR_SourceBuffer, uv).rgb) +  sunGlare * TESR_SunColor.rgb) * depth * sunSetFade;
	// float3 color = sunGlare ;

	return float4(color, 1.0f);
}


float4 LightMask(VSOUT IN) : COLOR0 {
	
	float2 uv = IN.UVCoord;
	clip((uv <= scale) - 1);

	// quick average lum with 4 samples at corner pixels
	float3 color;
	color = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-1, -1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-1, 1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(1, -1) * TESR_ReciprocalResolution.xy).rgb;
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(1, 1) * TESR_ReciprocalResolution.xy).rgb;
	color /= 4;

	float threshold = lumTreshold * luma(TESR_SunColor.rgb); // scaling the luma treshold with sun intensity
	float brightness = luma(color);
	float bloomScale = intensity;

	float bloom = bloomScale * sqr(max(0.0, brightness - threshold)) / brightness;

	return float4(bloom * color * 100, 1.0f);
}


float4 RadialBlur(VSOUT IN, uniform float step) : COLOR0 {
	float2 uv = IN.UVCoord;
	clip((uv <= scale) - 1);
	uv /= scale; // restore uv scale to do calculations in [0, 1] space
	uv += 0.5 * TESR_ReciprocalResolution.xy;

	// calculate vector from pixel to sun along which we'll sample
	float2 sunPos = projectPosition(TESR_ViewSpaceLightDir.xyz * farZ).xy;

	float2 blurDirection = (sunPos.xy - uv) * float2(1.0f, raspect); // apply aspect ratio correction
	float distance = length(blurDirection);
	if (distance > 1 || expand(dot(TESR_ViewSpaceLightDir, float4(0, 0, 1, 1))) < 0) return float4(0, 0, 0, 1);

	float2 dir = blurDirection/distance;

	float stepSize = step * stepLengthMult;
	float maxStep = distance/stepSize;

	// sample the light clamped image from the pixel to the sun for the given amount of samples
	float2 samplePos = uv;
	float4 color = float4(0, 0, 0, 1);
	float total = 1;
	for (float i=0; i < samples; i++){
		float length = min(stepSize * i, distance); // clamp sampling vector to the distance from the pixel to the sun
		samplePos = uv + (dir * length / float2(1, raspect)); // apply aspect ratio correction
		float doStep = (i <= maxStep && samplePos.x > 0 && samplePos.y > 0 && samplePos.x < 1 && samplePos.y < 1); // check if we haven't overshot the sun position or exited the screen
		
		color += tex2D(TESR_RenderedBuffer, samplePos * scale) * doStep;
		total += doStep;
	}
	color /= total;

	return float4(color.rgb, 1);
}


float4 Combine(VSOUT IN) : COLOR0
{
	float scale = 0.5;
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	float2 uv = IN.UVCoord;

	// calculate vector from pixel to sun along which we'll sample
	float2 sunPos = projectPosition(TESR_ViewSpaceLightDir.xyz * farZ).xy;
	float2 blurDirection = (sunPos.xy - uv) * float2(1.0f, raspect); // apply aspect ratio correction
	float distance = length(blurDirection);
	uv *= scale;

	float4 rays = tex2D(TESR_RenderedBuffer, uv);

	// attentuate intensity with distance from sun to fade the edges and reduce sunglare only on second pass
	float heightAttenuation = lerp(0.2, 1, (1 - dot(TESR_SunDirection.xyz, float3(0, 0, 1))));
	float glareAttenuation = max(0.3, pows(saturate(distance), glareReduction));
	float attenuation = saturate(pows(1 - distance, 1.5)) * glareAttenuation * heightAttenuation * 2;

	rays = pows(rays, godrayCurve); // increase response curve to extract more definition from godray pass
	rays = rays * attenuation;

	rays.rgb *= multiplier * lerp(TESR_SunColor.rgb, TESR_GodRaysRayColor.rgb, TESR_GodRaysRayColor.w);


	rays = lerp(rays, float4(0.0, 0.0, 0.0, 1), saturate(attenuation));

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
		PixelShader = compile ps_3_0 RadialBlur(stepLength); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 RadialBlur(stepLength * stepLength); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 RadialBlur(stepLength * stepLength * stepLength); 
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		Pixelshader = compile ps_3_0 Combine();
	}
}