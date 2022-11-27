// Ambient Occlusion fullscreen shader for Oblivion/Skyrim Reloaded

#define viewao 0

float4x4 TESR_RealProjectionTransform;
float4x4 TESR_RealInvProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_AmbientOcclusionAOData;
float4 TESR_AmbientOcclusionData;
float4 TESR_DepthConstants;
float4 TESR_CameraData;
float4 TESR_FogDistance;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_CameraData.x;
static const float farZ = TESR_CameraData.y;
static const float aspectRatio = TESR_CameraData.z;
static const float fov = TESR_CameraData.w;
static const float depthRange = farZ - nearZ;
static const float halfFOV = radians(fov*0.5);
static const float Q = farZ/(farZ - nearZ);

static const float AOradius = TESR_AmbientOcclusionAOData.x;
static const float AOstrength = TESR_AmbientOcclusionAOData.y;
static const float AOclamp = TESR_AmbientOcclusionAOData.z;
static const float AOrange = TESR_AmbientOcclusionAOData.w;
// static const float AOangleBias = TESR_AmbientOcclusionData.x;
static const float AOlumThreshold = TESR_AmbientOcclusionData.y;
static const float AOblurDrop = TESR_AmbientOcclusionData.z;
static const float AOblurRadius = TESR_AmbientOcclusionData.w;
static const float2 texelSize = float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y);
static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);
static const int cKernelSize = 12;
static const int startFade = 2000;
static const int endFade = 8000;

static const float BlurWeights[cKernelSize] = 
{
	0.057424882f,
	0.058107773f,
	0.061460144f,
	0.071020611f,
	0.088092873f,
	0.106530916f,
	0.106530916f,
	0.088092873f,
	0.071020611f,
	0.061460144f,
	0.058107773f,
	0.057424882f
};
 
static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-6.0f * TESR_ReciprocalResolution.x, -6.0f * TESR_ReciprocalResolution.y),
	float2(-5.0f * TESR_ReciprocalResolution.x, -5.0f * TESR_ReciprocalResolution.y),
	float2(-4.0f * TESR_ReciprocalResolution.x, -4.0f * TESR_ReciprocalResolution.y),
	float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.y),
	float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.y),
	float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.y),
	float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.y),
	float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.y),
	float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.y),
	float2( 4.0f * TESR_ReciprocalResolution.x,  4.0f * TESR_ReciprocalResolution.y),
	float2( 5.0f * TESR_ReciprocalResolution.x,  5.0f * TESR_ReciprocalResolution.y),
	float2( 6.0f * TESR_ReciprocalResolution.x,  6.0f * TESR_ReciprocalResolution.y)
};
 
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
 
// from https://gist.github.com/keijiro/ee7bc388272548396870
// returns a semi random float between 0 and 1 based on the given seed.
float random(float2 seed)
{
    return frac(sin(dot(seed, float2(12.9898, 78.233))) * 43758.5453);
}

// returns a value from 0 to 1 based on the positions of a value between a min/max 
float invLerp(float from, float to, float value){
  return (value - from) / (to - from);
}
 
float readDepth(in float2 coord : TEXCOORD0)
{
	float Depth = tex2D(TESR_DepthBuffer, coord).x; //* 2.0f - 1.0f;
    float ViewZ = (-nearZ *Q) / (Depth - Q);
	return ViewZ;
}


float3 reconstructPosition(float2 uv)
{
	//float4 screenpos = float4(uv, tex2D(TESR_DepthBuffer, uv).x, 1.0f) * 2.0 - 1.0f;
	float4 screenpos = float4(uv * 2.0 - 1.0f, tex2D(TESR_DepthBuffer, uv).x, 1.0f);
	screenpos.y = -screenpos.y;
	float4 viewpos = mul(screenpos, TESR_RealInvProjectionTransform);
	viewpos.xyz /= viewpos.w;
	return viewpos.xyz;
}

float3 projectPosition(float3 position){
	float4 projection = mul(float4 (position, 1.0), TESR_RealProjectionTransform);
	projection.xyz /= projection.w;
	projection.x = projection.x * 0.5 + 0.5;
	projection.y = 0.5 - 0.5 * projection.y;

	return projection.xyz;
}

float3 GetNormal( float2 coord)
{
	// improved normal reconstruction algorithm from 
	// https://gist.github.com/bgolus/a07ed65602c009d5e2f753826e8078a0

	float2 uv = coord; // center
	float2 rightUv = uv + float2(1, 0) * texelSize; 
	float2 rightUv2 = uv + float2(2, 0) * texelSize;
	float2 leftUv = uv + float2(-1, 0) * texelSize;
	float2 leftUv2 = uv + float2(-2, 0) * texelSize;
	float2 bottomUv = uv + float2(0, 1) * texelSize;
	float2 bottomUv2 = uv + float2(0, 2) * texelSize;
	float2 topUv = uv + float2(0, -1) * texelSize;
	float2 topUv2 = uv + float2(0, -2) * texelSize;

	float3 centerPoint = reconstructPosition(uv);
	float3 rightPoint = reconstructPosition(rightUv);
	float3 bottomPoint = reconstructPosition(bottomUv);
	float3 leftPoint = reconstructPosition(leftUv);
	float3 topPoint = reconstructPosition(topUv);

	// get the difference between the current and each offset position
	float3 left = centerPoint - leftPoint;
	float3 right = rightPoint - centerPoint;
	float3 down = centerPoint - bottomPoint;
	float3 up = topPoint - centerPoint;

	float depth = readDepth(uv);

	// get depth values at 1 & 2 pixels offsets from current along the horizontal axis
	half4 H = half4(
		readDepth(rightUv),
		readDepth(leftUv),
		readDepth(rightUv2),
		readDepth(leftUv2)
	);

	// get depth values at 1 & 2 pixels offsets from current along the vertical axis
	half4 V = half4(
		readDepth(topUv),
		readDepth(bottomUv),
		readDepth(topUv2),
		readDepth(bottomUv2)
	);


	half2 he = abs((2 * H.xy - H.zw) - depth);
	half2 ve = abs((2 * V.xy - V.zw) - depth);

	// pick horizontal and vertical diff with the smallest depth difference from slopes
	half3 hDeriv = he.x < he.y ? left : right;
	half3 vDeriv = ve.x < ve.y ? down : up;

	// get view space normal from the cross product of the best derivatives
	// half3 viewNormal = normalize(cross(hDeriv, vDeriv));
	half3 viewNormal = normalize(cross(vDeriv, hDeriv));

	return viewNormal;
}


float unpackDepth(float2 depth)
{
    return depth.x + ((depth.y - 0.5) / 255.0);
}

float2 packDepth(float depth)
{
    return float2(depth, frac(depth * 255.0 - 0.5));
}

float4 SSAO(VSOUT IN) : COLOR0
{
	float2 coord = IN.UVCoord;

	// generate the sampling kernel with random points in a hemisphere
	// #define size 16
	uint kernelSize = 24;
	float3 kernel[32]; // max supported kernel size is 32 samples
	float uRadius = 80;

	for (uint i = 0; i < kernelSize; ++i) {
		// generate random samples in a unit sphere
		// kernel[i] = float3 (nrand(float2(-1.0f, 1.0f)), nrand(float2(-1.0f, 1.0f)), nrand(float2(-1.0f, 1.0f)));
		float rand = random(coord * i);
		kernel[i] = float3 (random(coord * i * rand) * 2 - 1 , random(coord * -0.02 * i * rand) * 2 - 1 , random(coord * 0.03 * i * rand) );
		normalize(kernel[i]);

		//randomize points distance to sphere center, making them more concentrated towards the center
		kernel[i] *= random(float2(rand, -1.0 * rand)); 
		float scale = 1 - float(i) / float(kernelSize);
		scale = lerp(0.3f, 1.0f, scale * scale);
		kernel[i] *= scale; 
	}

	//reorient our sample kernel along the origin's normal
	float3 normal = GetNormal(coord);

	// calculate occlusion by sampling depth of each point from the kernel
	float3 origin = reconstructPosition(coord);

	float occlusion = 0.0;
	for (i = 0; i < kernelSize; ++i) {
		// get sample positions around origin:
		if (dot(normal, kernel[i]) < 0.0) kernel[i] *= -1.0; // if our sample vector goes inside the geometry, we flip it
		float3 samplePoint = origin + kernel[i] * uRadius;
		
		// compare depth of the projected sample with the value from depthbuffer
		float3 screenSpaceSample = projectPosition (samplePoint);
		float sampleDepth = readDepth(screenSpaceSample.xy);
		float actualDepth = samplePoint.z;

		// range check & accumulate:
		float distance = abs(actualDepth - sampleDepth);
		float rangeCheck = distance < uRadius ? 1.0 : 0.0;
		float influence = (sampleDepth < actualDepth ? 1.0 : 0.0 ) * rangeCheck;

		if (influence){
			if ( i < kernelSize / 4) {
				influence = 1.0 - distance * distance/(uRadius * uRadius);
			} else {
				influence = 1.0 - distance /uRadius;
			}
			occlusion += influence;
		}
	}
	
	occlusion = 1.0 - occlusion/kernelSize * AOstrength;

	if (origin.z > startFade){
		occlusion = lerp(occlusion, 1.0, saturate(invLerp(startFade, endFade, origin.z)));
	}

	return float4(occlusion, packDepth(readDepth(IN.UVCoord)), 1.0);
}

 
// perform depth aware 12 taps blur along the direction of the offsetmask
float4 BlurPS(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float WeightSum = 0.114725602f;
	float4 ao = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	ao.r = ao.r * WeightSum;

	float Depth1 = readDepth(IN.UVCoord);
	clip(endFade - Depth1);

	int i = 0;
    for (i = 0; i < cKernelSize; i++)
    {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * AOblurRadius;
		float4 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff);
		float Depth2 = readDepth(IN.UVCoord + uvOff);
		float diff = abs(float(Depth1 - Depth2));
 
		if(diff <= AOblurDrop)
		{
			ao.r += BlurWeights[i] * Color.r;
			WeightSum += BlurWeights[i];
		}
    }
	ao.r /= WeightSum;
    return ao;
}


float4 Normal(VSOUT IN) : COLOR0
{
	return float4(GetNormal(IN.UVCoord), readDepth(IN.UVCoord));
}

float4 Combine(VSOUT IN) : COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float ao = lerp(AOclamp, 1.0, tex2D(TESR_RenderedBuffer, IN.UVCoord).r);

	// float luminance = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
	// float white = 1.0;
	// float black = 0.0;
	// float lt = luminance - AOlumThreshold;
	// luminance = clamp(max(black, lt) + max(black, lt) + max(black, lt), 0.0, 1.0);
	// ao = lerp(ao, white, luminance);
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
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(OffsetMaskH);
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(OffsetMaskV);
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Combine();
	}
}