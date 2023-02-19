// Rain fullscreen shader for Oblivion Reloaded
#define RainLayers 15

float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformOrtho;
float4 TESR_ReciprocalResolution;
float4 TESR_GameTime;
float4 TESR_RainData; // x:rain amount, set by weather (0 to 1), y: vertical scale, z: speed of rainfall w: opacity
float4 TESR_FogColor;
float4 TESR_SunDirection;
float4 TESR_SunColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_OrthoMapBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float PI = 3.14159265;
static const float timetick = TESR_GameTime.z;
static const float hscale = 0.004f * TESR_RainData.y; // low values stretch the volume vertically
static const float3x3 p = float3x3(30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122);
static const float DEPTH = 100; // distance step between each layer
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
#include "Includes/Helpers.hlsl"

// convert world position to a coordinate on a cylinder around the player
float2 cylindrical(float3 world)
{
	float u = -atan2(world.y, world.x) / PI; 
	float v = world.z / length(world.xy);
	return float2(compress(u), hscale * v);
}

// checks wether a point is underneath something occluding
float GetOrtho(float4 OrthoPos) {	
	OrthoPos.xyz /= OrthoPos.w;
    float outofbounds = (OrthoPos.x < -1.0f || OrthoPos.x > 1.0f ||
        OrthoPos.y < -1.0f || OrthoPos.y > 1.0f ||
        OrthoPos.z <  0.0f || OrthoPos.z > 1.0f);
 
    OrthoPos.x = OrthoPos.x *  0.5f + 0.5f;
    OrthoPos.y = OrthoPos.y * -0.5f + 0.5f;
	float Ortho = tex2D(TESR_OrthoMapBuffer, OrthoPos.xy).r;
	return (Ortho > OrthoPos.z - 0.0001) * (1 - outofbounds); 
}

float4 Rain( VSOUT IN ) : COLOR0
{
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	int iterations = RainLayers;

	// calculating the ray along which the  volumetric rain will be calculated
	float3 world = toWorld(IN.UVCoord);
	float4 rayStart = float4(TESR_CameraPosition.xyz + world, 1.0f);
	float4 rayStartPos = mul(rayStart, TESR_WorldViewProjectionTransform);
	float4 orthoStart = mul(rayStartPos, TESR_ShadowCameraToLightTransformOrtho);	
	float3 camera_vectorS = world * (DEPTH * iterations);
	float4 rayEnd = float4(TESR_CameraPosition.xyz + camera_vectorS, 1.0f);
	float4 rayEndPos = mul(rayEnd, TESR_WorldViewProjectionTransform);
	float4 orthoEnd = mul(rayEndPos, TESR_ShadowCameraToLightTransformOrtho);
	float4 step = (orthoEnd - orthoStart) / iterations;
	
	// each iteration adds a cylindrical layer of drops 
	float2 uv = cylindrical(world); // converts world coordinates to cylinder coordinates around the player
	float depth = readDepth(IN.UVCoord);
	float totalRain = 0.0f;

	[unroll]
	for (int i = 1; i < iterations; i++){
		float2 noiseSurfacePosition = uv * (1.0f + i * DEPTH); // scale cylinder coordinates with iterations
		noiseSurfacePosition += float2(noiseSurfacePosition.y * (fmod(i * 107.238917f, 1.0f) - 0.5f), SPEED * timetick); // animate y offset, not sure what x does?

		// creating the noise with magic
		float3 m = float3(floor(noiseSurfacePosition), i); // places the drops at the same distance from the camera?
		float3 mp = m/frac(mul(p, m)); // bayer matrix? grid of grey values stretch depending on the world positions
		float3 rainNoise = frac(mp); //r.x is a random generated grid of different darknesses

        // determin drop shape
		float2 shape = abs(fmod(noiseSurfacePosition, 1.0f) + rainNoise.xy - 1.0f);
		shape += 0.01f * abs(2.0f * frac(10.0f * noiseSurfacePosition.yx) - 1.0f); // shape is a horizontal gradient on each square 
		float dropGradient = 0.6f * max(shape.x - shape.y, shape.x + shape.y) + max(shape.x, shape.y) - 0.01f; // creates a circular gradient on each square of the noise grid to focus the drop
		float edge = 0.005f + 0.05f * min(1.0f * i, 4.0f * TESR_RainData.x); // can't be 0 or smoothstep will fail. the smaller this value, the smaller the drops

		// add new drop influence to the fragment, by extracting the brightest spots in the gradients grid using the edge parameter
		float drop = smoothstep(edge, -edge, dropGradient) * (rainNoise.x / (1.0f + 0.2f * i)); // fade opacity with each iteration
		drop *= GetOrtho(orthoStart + step * i) * (depth > DEPTH * i); // depth and ortho check for rain
		totalRain += drop;
	}

	float4 rainColor = lerp(float(0.5).xxxx, TESR_SunColor * 2, pow(shades(normalize(world), TESR_SunDirection.xyz), 2));

	color = lerp(color, rainColor, totalRain * TESR_RainData.w);
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