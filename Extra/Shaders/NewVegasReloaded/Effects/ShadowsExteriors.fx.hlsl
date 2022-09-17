// Image space shadows shader for Oblivion Reloaded

float4x4 TESR_WorldTransform;
float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformNear;
float4x4 TESR_ShadowCameraToLightTransformFar;
float4 TESR_CameraPosition;
float4 TESR_WaterSettings;
float4 TESR_ShadowData;
float4 TESR_SunAmount;
float4 TESR_SunDirection;;
float4 TESR_ReciprocalResolution;
float4 TESR_ShadowBiasDeferred;
float4 TESR_FogData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferNear : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferFar : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s4) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;

static const float darkness = TESR_ShadowData.y;
static const float deferredNormBias = -0.035f;
static const float deferredFarNormBias = -0.035f;
//static const float deferredSlopeConstBias = 0.0004f;
static const float deferredConstBias = 0.0005f;
static const float deferredFarConstBias = 0.001f;
static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);


struct VSOUT
{
	float4 vertPos : POSITION;
	float4 normal : TEXCOORD1;
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
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	posZ = Zmul / ((posZ * Zdiff) - farZ);
	return posZ;
}

float3 toWorld(float2 tex)
{
	float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
	v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
	v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
	return v;
}

float3 getPosition(in float2 tex, in float depth)
{
	return (TESR_CameraPosition.xyz + toWorld(tex) * depth);
}

float4 getNormals(float2 UVCoord)
{
	float depth = readDepth(UVCoord);
	float3 pos = getPosition(UVCoord, depth);

	float3 left = pos - getPosition(UVCoord + TESR_ReciprocalResolution.xy * float2(-1, 0), readDepth(UVCoord + TESR_ReciprocalResolution.xy * float2(-1, 0)));
	float3 right = getPosition(UVCoord + TESR_ReciprocalResolution.xy * float2(1, 0), readDepth(UVCoord + TESR_ReciprocalResolution.xy * float2(1, 0))) - pos;
	float3 up = pos - getPosition(UVCoord + TESR_ReciprocalResolution.xy * float2(0, -1), readDepth(UVCoord + TESR_ReciprocalResolution.xy * float2(0, -1)));
	float3 down = getPosition(UVCoord + TESR_ReciprocalResolution.xy * float2(0, 1), readDepth(UVCoord + TESR_ReciprocalResolution.xy * float2(0, 1))) - pos;
	float3 dx = length(left) < length(right) ? left : right;
	float3 dy = length(up) < length(down) ? up : down;
	float3 norm = normalize(cross(dx, dy));

	norm.z *= -1;

	return float4((norm + 1) / 2, 1);
}

float Lookup(sampler2D ShadowBuffer, float3 ShadowPos, float bias) {
	// returns a binary lookup 0 = in shadow, 1 = in light.
	float ShadowDepth = tex2D(ShadowBuffer, ShadowPos.xy).r;
	return (ShadowDepth > ShadowPos.z - bias);
}

float4 PCFSampling(sampler2D ShadowBuffer, float4 coordinates, float bias, float areaSize, float step)
{
	// samples values around the position to soften shadows
	float x, y;
	float4 value = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float halfSize = (areaSize * step)/2;

	for (x = -halfSize; x <= halfSize; x += step){
		for (y = -halfSize; y<= halfSize; y += step){
			value += Lookup(ShadowBuffer, float3 (coordinates.xy + float2(x, y) * TESR_ShadowData.w, coordinates.z), bias);
		}
	}

	return value /= areaSize * areaSize;
}


float GetLightAmountFar(float4 ShadowPos) {
	// check distance where shadows are still displayed
	ShadowPos.xyz /= ShadowPos.w;
	if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
		ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
		ShadowPos.z < 0.0f || ShadowPos.z > 1.0f)
		return 1.0f;

	ShadowPos.x = ShadowPos.x * 0.5f + 0.5f ;//+ TESR_ShadowData.w;
	ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;// + TESR_ShadowData.w;

	float Shadow = PCFSampling(TESR_ShadowMapBufferFar, ShadowPos, deferredFarConstBias, 3, 1.0).r;

	return Shadow;
}

float GetLightAmount(float4 ShadowPos, float4 ShadowPosFar) {
	// apply perspective
	ShadowPos.xyz /= ShadowPos.w;

	// check distance to detect far or near shadows
	if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
		ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
		ShadowPos.z < 0.0f || ShadowPos.z > 1.0f)
		return GetLightAmountFar(ShadowPosFar);

	//convert from -1/1 (perspective division) to range to 0/1 (shadowMap range);
	ShadowPos.x = ShadowPos.x * 0.5f + 0.5f ;//+ TESR_ShadowData.z;
	ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;// + TESR_ShadowData.z;

	float Shadow = PCFSampling(TESR_ShadowMapBufferNear, ShadowPos, deferredConstBias, 5, 0.2).r;
	
	return Shadow;
}

// float AddProximityLight(float4 WorldPos, float4 ExternalLightPos) {

// 	if (ExternalLightPos.w) {
// 		float distToExternalLight = distance(WorldPos.xyz, ExternalLightPos.xyz);
// 		return (saturate(1.000f - (distToExternalLight / (ExternalLightPos.w))));
// 	}
// 	return 0.0f;
// }

float linstep(float low, float high, float t)
{
	// clamped linear interpolation
	return clamp((t - low)/(high-low), 0.0f, 1.0f);
}

float4 ChebyshevUpperBound(float2 moments, float distance)
{
	// get traditional shadow value
	float p = (moments.x > distance); //0: in shadow, 1: in light

	// Compute variance.    
	float Variance = moments.y - moments.x * moments.x;
	Variance = max(Variance, 0.00001);

	// Compute the Chebyshev upper bound.
	float d = distance - moments.x;
	float p_max = linstep(0.2, 1.0, Variance / (Variance + d*d));
	return max(p, p_max);
}

float GetLightAmountVarianceFar(float4 coordinates)
{
	// apply perspective
	coordinates.xyz /= coordinates.w;
	
	// check distance to detect if shadows are out of far range
	if (coordinates.x < -1.0f || coordinates.x > 1.0f ||
		coordinates.y < -1.0f || coordinates.y > 1.0f ||
		coordinates.z < 0.0f || coordinates.z > 1.0f)
		return 1.0f;

	//convert from -1/1 (perspective division) to range to 0/1 (shadowMap range);
	coordinates.x = coordinates.x * 0.5f + 0.5f; //+ TESR_ShadowData.w;
	coordinates.y = coordinates.y * -0.5f + 0.5f; //+ TESR_ShadowData.w;

	float2 Moments = tex2D(TESR_ShadowMapBufferFar, coordinates.xy).xy;

	return ChebyshevUpperBound(Moments, coordinates.z);
}


float GetLightAmountVariance(float4 coordinates, float4 coordinatesFar)
{
	// apply perspective
	coordinates.xyz /= coordinates.w;

	// check distance to detect far or near shadows
	if (coordinates.x < -1.0f || coordinates.x > 1.0f ||
		coordinates.y < -1.0f || coordinates.y > 1.0f ||
		coordinates.z < 0.0f || coordinates.z > 1.0f)
		return GetLightAmountVarianceFar(coordinatesFar);

	//convert from -1/1 (perspective division) to range to 0/1 (shadowMap range);
	coordinates.x = coordinates.x * 0.5f + 0.5f;// + TESR_ShadowData.z;
	coordinates.y = coordinates.y * -0.5f + 0.5f;// + TESR_ShadowData.z;

	float2 Moments = tex2D(TESR_ShadowMapBufferNear, coordinates.xy).xy;

	return ChebyshevUpperBound(Moments, coordinates.z);
}


float fogCoeff(float3 world_pos){
	return saturate((distance(world_pos.xyz, TESR_CameraPosition.xyz) - ((TESR_FogData.y- 2000))) / 1000) + 1.0f;
}

float4 VarianceShadow(VSOUT IN) : COLOR0
{
	// returns a shadow value from darkness setting value (full shadow) 
    // to 1 (full light) using variance maps algorithm
	
    // bypass during nighttime
	if (TESR_SunDirection.z < 0) return 1.0f;
	float3 color = float3(1.0f, 1.0f, 1.0f);
	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = toWorld(IN.UVCoord) * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);

	// check if surface is above water
	if (world_pos.z > TESR_WaterSettings.x) {
		float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);
		float4 farPos = pos;

		float4 ShadowPosNear = mul(pos, TESR_ShadowCameraToLightTransformNear);
		float4 ShadowPosFar = mul(farPos, TESR_ShadowCameraToLightTransformFar);
		float Shadow = saturate(GetLightAmountVariance(ShadowPosNear, ShadowPosFar));

		// apply fog attenuation
		Shadow = saturate(Shadow * fogCoeff(world_pos.xyz));

		// brighten shadow value from 0 to darkness from config value
		Shadow = lerp(darkness, 1.0f, Shadow);

		color *= Shadow;
	}
	return float4(color, 1.0f);
}


float4 Shadow(VSOUT IN) : COLOR0
{
	float3 color = float3(1.0f, 1.0f, 1.0f);

	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = toWorld(IN.UVCoord) * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);

	if (world_pos.z > TESR_WaterSettings.x) {
		float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);
		float4 farPos = pos;
		float4 normal = getNormals(IN.UVCoord);
		
		//Slope Scale
		/*
		float4 lightDir = abs(TESR_SunDirection);
		float3 n = normalize(normal);
		float3 l = normalize(lightDir);
		float cosTheta = clamp(dot(n, l), 0, 1);
		float bias = deferredSlopeConstBias * tan(acos(cosTheta));
		*/

		float bias = deferredConstBias;
		pos.xyz = pos.xyz + (normal.xyz * deferredNormBias);
		farPos.xyz = farPos.xyz + (normal.xyz * deferredFarNormBias);

		float4 ShadowNear = mul(pos, TESR_ShadowCameraToLightTransformNear);
		float4 ShadowFar = mul(farPos, TESR_ShadowCameraToLightTransformFar);
		float Shadow = GetLightAmount(ShadowNear, ShadowFar);

		// apply fog attenuation
		Shadow = saturate(Shadow * fogCoeff(world_pos.xyz));

		// brighten shadow value from 0 to darkness from config value
		Shadow = lerp(darkness, 1.0f, Shadow);
		color *= Shadow;
	}
	return float4(color, 1.0f);
}


static const int cKernelSize = 7;

static const float BlurWeights[cKernelSize] = 
{
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
};
 
static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.y),
	float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.y),
	float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.y),
	float2( 0.0f * TESR_ReciprocalResolution.x,  0.0f * TESR_ReciprocalResolution.y),
	float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.y),
	float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.y),
	float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.y),
};

float4 BlurPass(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float3 Color = 0.0f;
	float w = 0.0f;

    for (int i = 0; i < cKernelSize; i++) {
		float2 uvOff = (BlurOffsets[i] * OffsetMask);
		Color += tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff).rgb * BlurWeights[i];
		w += BlurWeights[i];
    }
	Color /= w;
    return float4(Color, 1.0f);
}


float4 alphaBlend(float4 base, float4 blend)
{
	return base*base.a +(1-base.a)*blend;
}

float4 Desaturate(float4 input)
{
	float greyscale = input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
	return float4(greyscale, greyscale, greyscale, input.a);
}

// photoshop overlay blend mode code from https://www.ryanjuckett.com/photoshop-blend-modes-in-hlsl/
float BlendMode_Overlay(float base, float blend)
{
	return (base <= 0.5f) ? 2.0f*base*blend : 1.0f - 2.0f*(1.0f-base)*(1.0f-blend);
}

float4 BlendMode_Overlay(float4 base, float4 blend)
{
	float4 result = float4(0,0,0,0);
	result.r = BlendMode_Overlay(base.r, blend.r);
	result.g = BlendMode_Overlay(base.g, blend.g);
	result.b = BlendMode_Overlay(base.b, blend.b);
	result.a = blend.a;

	return alphaBlend(result, base);
}

float4 CombineShadow( VSOUT IN ) : COLOR0 
{
	// combine Shadow pass and source using an overlay mode + alpha blending
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	color.a = 1.0f;
	float shadow = 1.0f - tex2D(TESR_RenderedBuffer, IN.UVCoord).r;
	float4 shadowColor = float4(color.rgb, shadow);

	return BlendMode_Overlay(color, Desaturate(shadowColor));
}

float4 SimpleCombineShadow (VSOUT IN) : COLOR0 
{
	// old style multiply blending (for testing)
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	return tex2D(TESR_RenderedBuffer, IN.UVCoord).r * color; 
}

technique {

	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 VarianceShadow();
	}

	// pass {
	// 	VertexShader = compile vs_3_0 FrameVS();
	// 	PixelShader = compile ps_3_0 Shadow();
	// }
/*
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass(OffsetMaskH);
	}
	
	pass {
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPass(OffsetMaskV);
	}
*/
//	pass {
//		VertexShader = compile vs_3_0 FrameVS();
//		PixelShader = compile ps_3_0 CombineShadow();
//	}
	pass {
		VertexShader = compile vs_3_0 FrameVS();
	 	PixelShader = compile ps_3_0 SimpleCombineShadow();
	}

}
