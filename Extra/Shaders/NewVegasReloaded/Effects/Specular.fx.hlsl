// Specular multiplier fullscreen shader for Oblivion/Skyrim Reloaded

float4x4 TESR_ProjectionTransform;
float4x4 TESR_InvProjectionTransform;
float4 TESR_ReciprocalResolution;
float4 TESR_SpecularData;					// x: strength, y:blurMultiplier, z:glossiness, w:drawDistance
float4 TESR_CameraData;  					// x: nearZ, y: farZ, z: aspect ratio, w: fov
float4 TESR_ScreenSpaceLightDir;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_CameraData.x;
static const float farZ = TESR_CameraData.y;
static const float Q = farZ/(farZ - nearZ);

static const float Strength = TESR_SpecularData.x;
static const float BlurRadius = TESR_SpecularData.y;
static const float Glossiness = TESR_SpecularData.z;
static const float DrawDistance = TESR_SpecularData.w;
static const float2 texelSize = float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y);
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


float4 specularHighlight( VSOUT IN) : COLOR0
{
	float2 coord = IN.UVCoord;
	float3 origin = reconstructPosition(coord);
	if (origin.z > DrawDistance) return 0.0;

	//reorient our sample kernel along the origin's normal
	float3 normal = GetNormal(IN.UVCoord);
	float3 viewRay = normalize(origin);
	float3 reflection = reflect(TESR_ScreenSpaceLightDir.xyz, normal);

	// float diffuse = dot(normal, TESR_ScreenSpaceLightDir.xyz);
	float specular = pow(dot(viewRay, reflection), Glossiness) * Glossiness * Glossiness;
	
	specular = lerp(specular, 0.0, origin.z/DrawDistance);

	// return diffuse;
	return specular.xxxx;
	// return specular + diffuse;
}


// perform depth aware 12 taps blur along the direction of the offsetmask
float4 BlurPS(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float WeightSum = 0.114725602f;
	float4 color1 = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	color1.r = color1.r * WeightSum;

	float depth1 = readDepth(IN.UVCoord);
	clip(DrawDistance - depth1); //don't process pixels further away than effect fade distance

	int i = 0;
    for (i = 0; i < cKernelSize; i++)
    {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * BlurRadius;
		float4 color2 = tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff);
		float depth2 = readDepth(IN.UVCoord + uvOff);
		float diff = abs(float(depth1 - depth2));
 
		// only factor it pixels that are close in terms of depth
		if(diff <= 1)
		{
			color1.r += BlurWeights[i] * color2.r;
			WeightSum += BlurWeights[i];
		}
    }
	color1.r /= WeightSum;
    return color1.rrrr;
}


float4 CombineSpecular(VSOUT IN) :COLOR0
{
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	float specular = tex2D(TESR_RenderedBuffer, IN.UVCoord).r;
	float luminance = Desaturate(color).r;
	float lt = luminance;

	// scale effect with scene luminance
	specular = lerp(0.0, specular, luminance) * TESR_SpecularData.x;
	color += specular * color * TESR_SpecularData.x;

	return float4 (color.rgb, 1.0f);
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