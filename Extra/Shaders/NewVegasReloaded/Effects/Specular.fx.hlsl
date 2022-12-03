// Ambient Occlusion fullscreen shader for Oblivion/Skyrim Reloaded

#define viewao 0

float4x4 TESR_ProjectionTransform;
float4x4 TESR_InvProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_AmbientOcclusionData;
float4 TESR_DepthConstants;
float4 TESR_CameraData;
float4 TESR_FogDistance; // x: fog start, y: fog end, z: weather percentage, w: sun glare
float4 TESR_FogColor;
float4 TESR_ScreenSpaceLightDir;

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
	float4 viewpos = mul(screenpos, TESR_InvProjectionTransform);
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
	// half3 viewNormal = normalize(cross(hDeriv, vDeriv));
	half3 viewNormal = normalize(cross(vDeriv, hDeriv));

	return viewNormal;
}


float4 Desaturate(float4 input)
{
	float greyscale = input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
	return float4(greyscale, greyscale, greyscale, input.a);
}

float fogCoeff(float depth){
	return clamp(invLerp(TESR_FogDistance.x, TESR_FogDistance.y, depth), 0.0, 1.0) / TESR_FogDistance.z;
}

float4 specularHighlight( VSOUT IN) : COLOR0
{
	float2 coord = IN.UVCoord;
	float3 origin = reconstructPosition(coord);
	// if (origin.z > endFade) return 1.0;

	float strength = 25;

	//reorient our sample kernel along the origin's normal
	float3 normal = GetNormal(IN.UVCoord);
	// float3 normal = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	float3 viewRay = normalize(origin);
	float3 reflection = reflect(TESR_ScreenSpaceLightDir, normal);

	float lighting = dot(normal, TESR_ScreenSpaceLightDir);
	float specular = pow(dot(viewRay, reflection), strength) * strength * strength;
	
	specular = lerp(specular, 0.0, origin.z/endFade);

	// return lighting;
	return specular.xxxx;
	// return specular + lighting;
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



float4 CombineSpecular(VSOUT IN) :COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float specular = tex2D(TESR_RenderedBuffer, IN.UVCoord).r;
	float luminance = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
	float white = 1.0;
	float black = 0.0;
	float lt = luminance - AOlumThreshold;
	specular = lerp(black, specular, luminance) * 5;

	// return specular.xxxx * color.xyzx * 5;

	color += specular*color * 5;

	return float4 (color, 1.0f);
}
 
technique
{

	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 specularHighlight();
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
		PixelShader = compile ps_3_0 CombineSpecular();
	}
}