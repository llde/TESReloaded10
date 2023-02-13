// Ambient Occlusion fullscreen shader for Oblivion/Skyrim Reloaded

#define viewao 1
#define halfres 0
#define kernelSize 12

float4 TESR_AmbientOcclusionAOData;
float4 TESR_AmbientOcclusionData;
float4 TESR_ReciprocalResolution;
float4 TESR_FogData; // x: fog start, y: fog end, z: sun glare, w: fog power
float4 TESR_FogColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_NoiseSampler : register(s3) < string ResourceName = "Effects\noise.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

static const float AOsamples = TESR_AmbientOcclusionAOData.x;
static const float AOstrength = TESR_AmbientOcclusionAOData.y;
static const float AOclamp = TESR_AmbientOcclusionAOData.z;
static const float AOrange = TESR_AmbientOcclusionAOData.w;
static const float AOangleBias = TESR_AmbientOcclusionData.x;
static const float AOlumThreshold = TESR_AmbientOcclusionData.y;
static const float blurDrop = TESR_AmbientOcclusionData.z;
static const float blurRadius = TESR_AmbientOcclusionData.w;
static const int startFade = 2000;
static const int endFade = 8000;
 
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
 
#include "Includes/Depth.hlsl"
#include "Includes/Blur.hlsl"

// returns a semi random float3 between 0 and 1 based on the given seed.
// tailored to return a different value for each uv coord of the screen.
float3 random(float2 seed)
{
	return tex2D(TESR_NoiseSampler, (seed/255 + 0.5) / TESR_ReciprocalResolution.xy).xyz;
}

// returns a value from 0 to 1 based on the positions of a value between a min/max 
float invLerp(float from, float to, float value){
  return (value - from) / (to - from);
}



float unpackDepth(float2 depth)
{
    return depth.x + ((depth.y - 0.5) / 255.0);
}

float2 packDepth(float depth)
{
    return float2(depth, frac(depth * 255.0 - 0.5));
}

float4 Desaturate(float4 input)
{
	float greyscale = input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
	return float4(greyscale, greyscale, greyscale, input.a);
}

float fogCoeff(float depth){
	return saturate(invLerp(TESR_FogData.x, TESR_FogData.y, depth));
}

float4 SSAO(VSOUT IN) : COLOR0
{
	float2 uv = IN.UVCoord.xy;

#if halfres
	clip ((IN.UVCoord.x < 0.5 && IN.UVCoord.y < 0.5)-1); // discard half the screen to render at half resolution
	uv *= 2;
#endif
	
	// generate the sampling kernel with random points in a hemisphere
	// int kernelSize = clamp(AOsamples, 0, 32);
	// int kernelSize = 20;
	// float3 kernel[20]; // max supported kernel size is 20 samples
	float uRadius = abs(AOrange);
	float bias = saturate(AOangleBias);

	float3 origin = reconstructPosition(uv);
	if (origin.z > endFade) return 1.0;

	//reorient our sample kernel along the origin's normal
	float3 normal = GetNormal(uv);

	// calculate occlusion by sampling depth of each point from the kernel
	float occlusion = 0.0;
	[unroll]
	for (int i = 0; i < kernelSize; ++i) {

		// generate random samples in a unit sphere (random vector coordinates from -1 to 1);
		float3 rand = random(uv * i);
		float3 sampleVector = float3 (rand.x * 2 - 1, rand.y * 2 - 1, rand.z);
		sampleVector = normalize(sampleVector);

		//randomize points distance to sphere center, making them more concentrated towards the center
		sampleVector *= random(uv * i/2);
		float scale = 1 - float(i) / float(kernelSize);
		scale = lerp(bias, 1.0f, scale * scale);
		sampleVector *= scale; 

		// get sample positions around origin:
		sampleVector *= dot(normal, sampleVector) < 0.0 ? -1.0 : 1.0; // if our sample vector goes inside the geometry, we flip it
		float3 samplePoint = origin + sampleVector * uRadius;
		
		// compare depth of the projected sample with the value from depthbuffer
		float3 screenSpaceSample = projectPosition (samplePoint);
		float sampleDepth = readDepth(screenSpaceSample.xy);
		float actualDepth = samplePoint.z;

		// range check & accumulate:
		float distance = abs(actualDepth - sampleDepth);
		float rangeCheck = distance < uRadius ? 1.0 : 0.0;
		float influence = (sampleDepth < actualDepth ? 1.0 : 0.0 ) * rangeCheck;

		// stronger strength curve in close vectors (replacing an if statement with a lerp)
		influence *= lerp(1.0 - distance * distance/(uRadius * uRadius), 1.0 - distance /uRadius, i < kernelSize / 4);
		occlusion += influence;
	}
	
	occlusion = 1.0 - occlusion/kernelSize * AOstrength;

	float fogColor = Desaturate(TESR_FogColor).x;
	float darkness = clamp(lerp(occlusion, fogColor, fogCoeff(origin.z)), occlusion, 1.0);

	darkness = lerp(darkness, 1.0, saturate(invLerp(0.0, endFade, origin.z)));
	// darkness = lerp(darkness, 1.0, saturate(invLerp(startFade, endFade, origin.z)));

	return float4(darkness, packDepth(origin.z), 1.0);
}


float4 Normal(VSOUT IN) : COLOR0
{
	return float4(GetNormal(IN.UVCoord), readDepth(IN.UVCoord));
}

float4 Expand(VSOUT IN) : COLOR0
{
	float2 coord = IN.UVCoord * 0.5;
	return tex2D(TESR_RenderedBuffer, coord);
}

float4 Combine(VSOUT IN) : COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float ao = lerp(AOclamp, 1.0, tex2D(TESR_RenderedBuffer, IN.UVCoord).r);

	float luminance = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
	float white = 1.0;
	float black = 0.0;
	float lt = luminance - AOlumThreshold;
	luminance = clamp(max(black, lt) + max(black, lt) + max(black, lt), 0.0, 1.0);
	ao = lerp(ao, white, luminance);
	color *= ao;
	
    #if viewao
		return float4(ao, ao, ao, 1);
	#endif
	
	return float4(color, 1.0f);
   
}
 
technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 SSAO();
	}

#if halfres
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Expand();
	}
#endif
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurRChannel(float2(1.0f, 0.0f), blurRadius, blurDrop, endFade);
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurRChannel(float2(0.0f, 1.0f), blurRadius, blurDrop, endFade);
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Combine();
	}
}