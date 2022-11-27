// Ambient Occlusion fullscreen shader for Oblivion/Skyrim Reloaded

#define viewao 0

float4x4 TESR_RealProjectionTransform;
float4x4 TESR_RealInvProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_AmbientOcclusionAOData;
float4 TESR_AmbientOcclusionData;
float4 TESR_DepthConstants;
float4 TESR_CameraData;
float4 TESR_FogDistance; // x: fog start, y: fog end, z: weather percentage, w: sun glare
float4 TESR_FogColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_NoiseSampler : register(s3) < string ResourceName = "Effects\noise.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

static const float nearZ = TESR_CameraData.x;
static const float farZ = TESR_CameraData.y;
static const float aspectRatio = TESR_CameraData.z;
static const float fov = TESR_CameraData.w;
static const float depthRange = farZ - nearZ;
static const float halfFOV = radians(fov*0.5);
static const float Q = farZ/(farZ - nearZ);

static const float AOsamples = TESR_AmbientOcclusionAOData.x;
static const float AOstrength = TESR_AmbientOcclusionAOData.y;
static const float AOclamp = TESR_AmbientOcclusionAOData.z;
static const float AOrange = TESR_AmbientOcclusionAOData.w;
static const float AOangleBias = TESR_AmbientOcclusionData.x;
static const float AOlumThreshold = TESR_AmbientOcclusionData.y;
static const float AOblurDrop = TESR_AmbientOcclusionData.z;
static const float AOblurRadius = TESR_AmbientOcclusionData.w;
static const float2 texelSize = float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y);
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
 

// returns a semi random float3 between 0 and 1 based on the given seed.
// tailored to return a different value for each uv coord of the screen.
float3 random(float2 seed)
{
	return tex2D(TESR_NoiseSampler, (seed/255 + 0.5) / texelSize).xyz;
}

// returns a value from 0 to 1 based on the positions of a value between a min/max 
float invLerp(float from, float to, float value){
  return (value - from) / (to - from);
}
 
float readDepth(in float2 coord : TEXCOORD0)
{
	float Depth = tex2D(TESR_DepthBuffer, coord).x;;
    float ViewZ = (-nearZ *Q) / (Depth - Q);
	return ViewZ;
}


float3 reconstructPosition(float2 uv)
{
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

float3 GetNormal( float2 uv)
{
	// improved normal reconstruction algorithm from 
	// https://gist.github.com/bgolus/a07ed65602c009d5e2f753826e8078a0

	// store coordinates at 1 and 2 pixels from center in all directions
	float4 rightUv = uv.xyxy + float4(1.0, 0.0, 2.0, 0.0) * texelSize.xyxy; 
	float4 leftUv = uv.xyxy + float4(-1.0, 0.0, -2.0, 0.0) * texelSize.xyxy; 
	float4 bottomUv = uv.xyxy + float4(0.0, 1.0, 0.0, 2.0) * texelSize.xyxy; 
	float4 topUv =uv.xyxy + float4(0.0, -1.0, 0.0, -2.0) * texelSize.xyxy; 

	float depth = readDepth(uv);

	// get depth values at 1 & 2 pixels offsets from current along the horizontal axis
	half4 H = half4(
		readDepth(rightUv.xy),
		readDepth(leftUv.xy),
		readDepth(rightUv.zw),
		readDepth(leftUv.zw)
	);

	// get depth values at 1 & 2 pixels offsets from current along the vertical axis
	half4 V = half4(
		readDepth(topUv.xy),
		readDepth(bottomUv.xy),
		readDepth(topUv.zw),
		readDepth(bottomUv.zw)
	);

	half2 he = abs((2 * H.xy - H.zw) - depth);
	half2 ve = abs((2 * V.xy - V.zw) - depth);

	// pick horizontal and vertical diff with the smallest depth difference from slopes
	float3 centerPoint = reconstructPosition(uv);
	float3 rightPoint = reconstructPosition(rightUv.xy);
	float3 leftPoint = reconstructPosition(leftUv.xy);
	float3 topPoint = reconstructPosition(topUv.xy);
	float3 bottomPoint = reconstructPosition(bottomUv.xy);
	float3 left = centerPoint - leftPoint;
	float3 right = rightPoint - centerPoint;
	float3 down = centerPoint - bottomPoint;
	float3 up = topPoint - centerPoint;

	half3 hDeriv = he.x < he.y ? left : right;
	half3 vDeriv = ve.x < ve.y ? down : up;

	// get view space normal from the cross product of the best derivatives
	half3 viewNormal = normalize(cross(hDeriv, vDeriv));
	// half3 viewNormal = normalize(cross(vDeriv, hDeriv));

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

float4 Desaturate(float4 input)
{
	float greyscale = input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
	return float4(greyscale, greyscale, greyscale, input.a);
}

float fogCoeff(float depth){
	return clamp(invLerp(TESR_FogDistance.x, TESR_FogDistance.y, depth), 0.0, 1.0) / TESR_FogDistance.z;
}

float4 SSAO(VSOUT IN) : COLOR0
{
	float2 coord = IN.UVCoord;

	// generate the sampling kernel with random points in a hemisphere
	int kernelSize = clamp(int(AOsamples), 0, 32);
	float3 kernel[32]; // max supported kernel size is 32 samples
	float uRadius = abs(AOrange);
	float bias = saturate(AOangleBias);

	for (int i = 0; i < kernelSize; ++i) {
		// generate random samples in a unit sphere (random vector coordinates from -1 to 1);
		float3 rand = random(coord * i);
		kernel[i] = float3 (rand.x * 2 - 1, rand.y * 2 - 1, rand.z);
		normalize(kernel[i]);

		//randomize points distance to sphere center, making them more concentrated towards the center
		kernel[i] *= random(coord * i/2);
		float scale = 1 - float(i) / float(kernelSize);
		scale = lerp(bias, 1.0f, scale * scale);
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
				// stronger strength curve in close vectors
				influence = 1.0 - distance * distance/(uRadius * uRadius);
			} else {
				influence = 1.0 - distance /uRadius;
			}
			occlusion += influence;
		}
	}
	
	occlusion = 1.0 - occlusion/kernelSize * AOstrength;

	float fogColor = Desaturate(TESR_FogColor).x;
	float darkness = clamp(lerp(occlusion, fogColor, fogCoeff(origin.z)), occlusion, 1.0);

	if (origin.z > startFade){
		darkness = lerp(darkness, 1.0, saturate(invLerp(0.0, endFade, origin.z)));
	}

	return float4(darkness, packDepth(origin.z), 1.0);
}

 
// perform depth aware 12 taps blur along the direction of the offsetmask
float4 BlurPS(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float WeightSum = 0.114725602f;
	float4 ao = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	ao.r = ao.r * WeightSum;

	// float Depth1 = unpackDepth(ao.gb);
	float Depth1 = readDepth(IN.UVCoord);
	clip(endFade - Depth1);

	int i = 0;
    for (i = 0; i < cKernelSize; i++)
    {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * AOblurRadius;
		float4 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff);
		float Depth2 = readDepth(IN.UVCoord + uvOff);
		// float Depth2 = unpackDepth(Color.gb);
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
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(float2(1.0f, 0.0f));
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(float2(0.0f, 1.0f));
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Combine();
	}
}