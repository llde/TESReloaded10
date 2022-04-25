// Ambient Occlusion fullscreen shader for Oblivion/Skyrim Reloaded

#define viewao 0

float4x4 TESR_ProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_AmbientOcclusionAOData;
float4 TESR_AmbientOcclusionData;
float4 TESR_FogData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const int samples = 5;
static const int rings = 2;
static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float2 g_InvFocalLen = { tan(0.5 * radians(TESR_ReciprocalResolution.w)) * (1.0f / TESR_ReciprocalResolution.z), tan(0.5 * radians(TESR_ReciprocalResolution.w)) };
static const float depthRange = nearZ - farZ;
static const float depthConstant = depthRange / 20000;
static const float aoMultiplier = 500.0;
static const float angleBiasRadians = radians(TESR_AmbientOcclusionData.x);
static const float cosAngleBias = cos(angleBiasRadians);
static const float sinAngleBias = sin(angleBiasRadians);
static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);
static const float PI = 3.14159265;
static const int cKernelSize = 12;

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
 
float2 rand(in float2 uv)
{
	float noiseX = frac(sin(dot(uv ,float2(12.9898, 78.233))) * 43758.5453);
	float noiseY = frac(sin(dot(uv ,float2(12.9898, 78.233) * 2.0)) * 43758.5453);
	return float2(noiseX, noiseY) * 0.004;
}
 
float readDepth(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	return (2.0f * nearZ) / (nearZ + farZ - posZ * (farZ - nearZ));
}
 
float3 getPosition(in float2 uv, in float eye_z)
{
   uv = (uv * float2(2.0, -2.0) - float2(1.0, -1.0));
   float3 pos = float3(uv * g_InvFocalLen * eye_z, eye_z );
   return pos;
}
 
float2 packDepth(float depth)
{
    return float2(depth, frac(depth * 255.0 - 0.5));
}
 
float unpackDepth(float2 depth)
{
    return depth.x + ((depth.y - 0.5) / 255.0);
}
 
float compareDepths(float depth1, float depth2)
{
	float diff = sqrt(saturate(1.0 - (depth1 - depth2) / (TESR_AmbientOcclusionAOData.w / depthRange)));
	float dist = (depth1 - depth2) * depthConstant;
	float ao = min(1, dist * aoMultiplier) * diff;
	float depth1Pos = depth1 * depthRange;
	
	if (depth1Pos >= 8000) ao *= saturate(lerp(1, 0, (depth1Pos - 8000) / 12500));
 
	return float(ao);
}
 
float4 AOPass(VSOUT IN) : COLOR0
{
	float depth = readDepth(IN.UVCoord);
	float3 pos = getPosition(IN.UVCoord, depth);
	float depthPos = depth * depthRange;
	float dx = normalize(ddx(pos)).z * g_InvFocalLen.x;
	float dy = normalize(ddy(pos)).z * g_InvFocalLen.y;
	float cosdx = dx * cosAngleBias;
	float cosdy = dy * cosAngleBias;
	float sindx = sqrt(1 - dx * dx) * sinAngleBias;
	float sindy = sqrt(1 - dy * dy) * sinAngleBias;
	float d;
	float depth_pred;
	float ao = 0.0;
	float s = 0.0;
 
	if (depth >= 1) {
		ao = 1;
	}
	else {
		float2 noise = rand(IN.UVCoord);
		float w = (noise.x * (1.0 - noise.x)) / (g_InvFocalLen.x * depthPos / (TESR_ReciprocalResolution.x * 200000));
		float h = (noise.y * (1.0 - noise.y)) / (g_InvFocalLen.y * depthPos / (TESR_ReciprocalResolution.y * 200000)); 
		float pw;
		float ph;

		for (int i = 0; i < rings; i++)
		{
			[unroll]
			for (int j = 0; j < samples * i; j++)
			{
				float step = PI * 2.0 / float(samples * i);
				pw = (cos(float(j) * step) * float(i)) * TESR_AmbientOcclusionAOData.x;
				ph = (sin(float(j) * step) * float(i)) * TESR_AmbientOcclusionAOData.x * TESR_ReciprocalResolution.z;
				float new_x = IN.UVCoord.x + pw * w;
				float new_y = IN.UVCoord.y + ph * h;
				float anglebias_dx = cosdx + sign(pw) * sindx;
				float anglebias_dy = cosdy + sign(ph) * sindy;
				depth_pred = depth + depth * anglebias_dx * pw * w + depth * anglebias_dy * ph * h;
				d = readDepth(float2(new_x, new_y));
				float aoresult = compareDepths(depth_pred, d);
				ao += aoresult;
				s += 1;
			}
		}
		ao /= s;
		if (TESR_FogData.y > TESR_FogData.x && depthPos >= TESR_FogData.x) ao *= saturate(lerp(1, 0, (depthPos - TESR_FogData.x) / (TESR_FogData.y - TESR_FogData.x)));
		ao = 1.0 - ao * TESR_AmbientOcclusionAOData.y;
	}
	
	return float4(clamp(ao * ao, TESR_AmbientOcclusionAOData.z, 1), packDepth(depth), 1);
}

float4 BlurPS(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float WeightSum = 0.114725602f;
	float4 ao = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	ao.r = ao.r * WeightSum;
 
	float Depth1 = unpackDepth(ao.gb);
	clip(0.9999 - Depth1);
 
	int i = 0;
    for (i = 0; i < cKernelSize; i++)
    {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * TESR_AmbientOcclusionData.w;
		float4 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff);
		float Depth2 = unpackDepth(Color.gb);
		float diff = abs(float(Depth1 - Depth2) * depthRange);
 
		if(diff <= TESR_AmbientOcclusionData.z)
		{
			ao.r += BlurWeights[i] * Color.r;
			WeightSum += BlurWeights[i];
		}
    }
	ao.r /= WeightSum;
    return ao;
}
 
float4 Combine(VSOUT IN) : COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float ao = tex2D(TESR_RenderedBuffer, IN.UVCoord).r;
	float luminance = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
	float white = 1.0;
	float black = 0.0;
	float lt = luminance - TESR_AmbientOcclusionData.y;
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
		PixelShader = compile ps_3_0 AOPass();
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