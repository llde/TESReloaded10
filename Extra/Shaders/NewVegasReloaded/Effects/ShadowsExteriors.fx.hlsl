// Image space shadows shader for Oblivion Reloaded

float4x4 TESR_WorldTransform;
float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformNear;
float4x4 TESR_ShadowCameraToLightTransformMiddle;
float4x4 TESR_ShadowCameraToLightTransformFar;
float4x4 TESR_ShadowCameraToLightTransformLod;
float4 TESR_CameraPosition;
float4 TESR_WaterSettings;
float4 TESR_ShadowData; // x: quality, y: darkness, z: nearmap resolution, w: farmap resolution
float4 TESR_SunAmount;
float4 TESR_SunDirection;
float4 TESR_ReciprocalResolution;
float4 TESR_ShadowRadius;
float4 TESR_FogDistance; // x: fog start, y: fog end, z: weather percentage, w: sun glare

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferNear : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferMiddle : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferFar : register(s4) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_ShadowMapBufferLod : register(s5) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = ANISOTROPIC; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s6) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;
static const float darkness = TESR_ShadowData.y;

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
	posZ = nearZ * farZ / ((posZ * (farZ - nearZ)) - farZ);
	return posZ;
}

float3 toWorld(float2 tex)
{
	float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
	v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
	v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
	return v;
}


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


float GetLightAmountValue(sampler2D shadowBuffer, float4x4 lightTransform, float4 coord)
{
	//returns wether the coordinates are in shadow (0), light (1) or penumbra.
	float4 LightSpaceCoord = mul(coord, lightTransform);

	// apply perspective and convert from -1/1 (perspective division) to range to 0/1 (shadowMap range);
	LightSpaceCoord.xyz /= LightSpaceCoord.w;
	LightSpaceCoord.x = LightSpaceCoord.x * 0.5f + 0.5f;
	LightSpaceCoord.y = LightSpaceCoord.y * -0.5f + 0.5f;

	float2 Moments = tex2D(shadowBuffer, LightSpaceCoord.xy).xy;

	return ChebyshevUpperBound(Moments, LightSpaceCoord.z);
}

float GetLightAmount(float4 coord, float3 camera_vector)
{
	// check distance to detect far or near shadows
	if (length(camera_vector) < TESR_ShadowRadius.x){
		return GetLightAmountValue(TESR_ShadowMapBufferNear, TESR_ShadowCameraToLightTransformNear, coord);
	}

	if (length(camera_vector) < TESR_ShadowRadius.y){
		return GetLightAmountValue(TESR_ShadowMapBufferMiddle, TESR_ShadowCameraToLightTransformMiddle, coord);
	}

	if (length(camera_vector) < TESR_ShadowRadius.z){
		return GetLightAmountValue(TESR_ShadowMapBufferFar, TESR_ShadowCameraToLightTransformFar, coord);
	}

	if (length(camera_vector) < TESR_ShadowRadius.w){
		return GetLightAmountValue(TESR_ShadowMapBufferLod, TESR_ShadowCameraToLightTransformLod, coord);
	}
	return 1.0;
}


// returns a value from 0 to 1 based on the positions of a value between a min/max 
float invLerp(float from, float to, float value){
  return (value - from) / (to - from);
}

float fogCoeff(float depth){
	return clamp(invLerp(TESR_FogDistance.x, TESR_FogDistance.y, depth), 0.0, 1.0);
}

float4 Shadow(VSOUT IN) : COLOR0
{
	// returns a shadow value from darkness setting value (full shadow) 
	// to 1 (full light) using variance maps algorithm

	// bypass during nighttime
	if (TESR_SunDirection.z < 0) return 1.0f;

	float Shadow = 1.0f;
	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = toWorld(IN.UVCoord) * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);

	// check if surface is above water
	if (world_pos.z > TESR_WaterSettings.x) {
		float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);

		Shadow = GetLightAmount(pos, camera_vector);

		// apply fog attenuation
		Shadow = saturate(Shadow + fogCoeff(depth) * 4);

		// brighten shadow value from 0 to darkness from config value
		Shadow = lerp(darkness, 1.0f, Shadow);
	}
	return float4(Shadow, Shadow, Shadow, 1.0f);
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
		PixelShader = compile ps_3_0 Shadow();
	}

//	pass {
//		VertexShader = compile vs_3_0 FrameVS();
//		PixelShader = compile ps_3_0 CombineShadow();
//	}

	pass {
		VertexShader = compile vs_3_0 FrameVS();
	 	PixelShader = compile ps_3_0 SimpleCombineShadow();
	}

}
