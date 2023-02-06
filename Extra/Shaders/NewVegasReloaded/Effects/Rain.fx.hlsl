// Rain fullscreen shader for Oblivion Reloaded
#define RainLayers 20

float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformOrtho;
float4 TESR_ReciprocalResolution;
float4 TESR_GameTime;
float4 TESR_RainData;
float4 TESR_FogColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_OrthoMapBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float PI = 3.14159265;
static const float timetick = TESR_GameTime.z;
static const float hscale = 0.005f; // low values stretch the volume vertically
static const float3x3 p = float3x3(30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122);
static const float DEPTH = TESR_RainData.y; // distance step between each layer
static const float SPEED = TESR_RainData.z; // speed multiplier for falling animation 

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

// convert world position to a coordinate on a cylinder around the player
float2 cylindrical(float3 world)
{
	float u = -atan2(world.y, world.x) / PI; 
	float v = world.z / length(world.xy);
	return float2(0.5f * u + 0.5f, hscale * v);
}

// checks wether a point is underneath something occluding
float GetOrtho(float4 OrthoPos) {	
	OrthoPos.xyz /= OrthoPos.w;
    if (OrthoPos.x < -1.0f || OrthoPos.x > 1.0f ||
        OrthoPos.y < -1.0f || OrthoPos.y > 1.0f ||
        OrthoPos.z <  0.0f || OrthoPos.z > 1.0f)
		return 1.0f;
 
    OrthoPos.x = OrthoPos.x *  0.5f + 0.5f;
    OrthoPos.y = OrthoPos.y * -0.5f + 0.5f;
	float Ortho = tex2D(TESR_OrthoMapBuffer, OrthoPos.xy).r;
	return (Ortho > OrthoPos.z); 
}

float4 Rain( VSOUT IN ) : COLOR0
{
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	// float4 color = float4(0, 0, 0, 1);

	float3 world = toWorld(IN.UVCoord);
	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = world * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);
	float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);

	float4 ortho_pos = mul(pos, TESR_ShadowCameraToLightTransformOrtho);	
	float ortho = GetOrtho(ortho_pos); // get wether the shaded point is occluded
	
	if (ortho == 0.0f) {
		float stepdepth = (depth - nearZ) / 10.0f; 
		[unroll]
		// raymarch towards the point depth to find if any point between the camera and the point is occluded
		for (int i = 1; i <= 10; i++) {
			float3 camera_vectorS = world * (depth - stepdepth * i);
			float4 world_posS = float4(TESR_CameraPosition.xyz + camera_vectorS, 1.0f);
			float4 posS = mul(world_posS, TESR_WorldViewProjectionTransform);
			float4 ortho_posS = mul(posS, TESR_ShadowCameraToLightTransformOrtho);
			float orthoS = GetOrtho(ortho_posS);
			if (orthoS) {
				ortho = 1.0f;
				break;
			}
		}
	}
	if (ortho == 0.0f) discard;

	float2 noiseSurfacePosition;
	float3 m;
	float3 mp;
	float3 rainNoise;
	float2 s;
	float dropGradient;
	float edge;
	float totalRain = 0.0f;
	int iterations = TESR_RainData.x * RainLayers;
	float2 uv = cylindrical(world); // converts world coordinates to cylinder coordinates around the player
	
	// each iteration adds a cylindrical layer of drops 
	for (int i = 3; i < iterations; i++){
		noiseSurfacePosition = uv * (1.0f + i * DEPTH); // scale cylinder coordinates with iterations
		noiseSurfacePosition += float2(noiseSurfacePosition.y * (fmod(i * 107.238917f, 1.0f) - 0.5f), SPEED * timetick); // animate y offset, not sure what x does?

		m = float3(floor(noiseSurfacePosition), i); // places the drops at the same distance from the camera?
		mp = m/frac(mul(p, m)); // bayer matrix? grid of grey values stretch depending on the world positions
		rainNoise = frac(mp); //r.x is a random generated grid of different darknesses

        // determin drop shape
		s = abs(fmod(noiseSurfacePosition, 1.0f) + rainNoise.xy - 1.0f);
		s += 0.01f * abs(2.0f * frac(10.0f * noiseSurfacePosition.yx) - 1.0f); // s is a horizontal gradient on each square 
		dropGradient = 0.6f * max(s.x - s.y, s.x + s.y) + max(s.x, s.y) - 0.01f; // creates a circular gradient on each square of the noise grid to focus the drop
		edge = 0.005f + 0.05f * min(0.25f * i, 1.5f); // can't be 0 or smoothstep will fail. the smaller this value, the smaller the drops

		// add new drop influence to the fragment, by extracting the brightest spots in the gradients grid using the edge parameter
		float drop = smoothstep(edge, -edge, dropGradient) * (rainNoise.x / (1.0f + 0.01f * i * DEPTH)); // fade opacity with each iteration
		totalRain += drop;
	}

	color += (totalRain * (TESR_FogColor * 0.6));
	// color += (totalRain * (TESR_FogColor + 0.5f));
	return float4(color.rgb, 1.0f);

}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Rain();
	}
}