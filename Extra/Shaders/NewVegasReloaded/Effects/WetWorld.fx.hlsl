// WetWorld fullscreen shader for Oblivion/NewVegas Reloaded
//----------------------------------------------------------
//Todo:
//----------------------------------------------------------
// Fix viewmodel issue
// Look into adding code from refraction for better looking water(?)
// Reflection buffer(?)
// Make better ripple normal(?)
// Add ripples to other water sources(?)
// Add world spec multi(?)
//----------------------------------------------------------
// Boomstick was here

float4 TESR_SunDirection;
float4 TESR_ReciprocalResolution;
float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformOrtho;

float4 TESR_GameTime;
float4 TESR_SkyColor;
float4 TESR_HorizonColor;
float4 TESR_SunColor;
float4 TESR_WetWorldCoeffs; // Puddle color R, G, B + spec multiplier
float4 TESR_WaterSettings; // for water height to avoid rendering puddles underwater
float4 TESR_WetWorldData; // x: current rain amount, y: max rain amount z: puddle amount

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_RippleSampler : register(s3) < string ResourceName = "Precipitations\ripples.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_OrthoMapBuffer : register(s4) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };


//------------------------------------------------------
// Custimizable
//------------------------------------------------------
static const float PI = 3.14159265; //changes intensity of the ripples normal
static const float time1 = TESR_GameTime.z * 0.96f; // Ripple timing, make sure to offset each by atleast a few
static const float time2 = TESR_GameTime.z * 0.97f; // Ripple timing, original 1.0-1.4
static const float time3 = TESR_GameTime.z * 0.98f; // Ripple timing
static const float time4 = TESR_GameTime.z * 0.99f; // Ripple timing
static const float DrawD = 2000.0f; // Max draw distance for puddles 0-1000000
//------------------------------------------------------

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

#include "Includes/Helpers.hlsl"
#include "Includes/Depth.hlsl"
#include "Includes/Blur.hlsl"


float3 ComputeRipple(float2 UV, float CurrentTime, float Weight)
{
    float4 Ripple = tex2D(TESR_RippleSampler, UV);
	
    Ripple.yz = expand(Ripple.yz); // convert from 0/1 to -1/1 

    float period = frac(Ripple.w + CurrentTime);
    float TimeFrac = period - 1.0f + Ripple.x;
    float DropFactor = saturate(0.2f + Weight * 0.8f - period);
    float FinalFactor = DropFactor * Ripple.x * sin( clamp(TimeFrac * 9.0f, 0.0f, 3.0f) * PI);

    return float3(Ripple.yz * FinalFactor * 0.35f, 1.0f);
}


float4 ScreenCoordToTexCoord(float4 coord, float mult){
	// apply perspective (perspective division) and convert from -1/1 to range to 0/1 (shadowMap range);
	coord.xyz /= coord.w;
	coord.x = coord.x * 0.5f + 0.5f;
	coord.y = coord.y * -0.5f + 0.5f;
	coord *= mult;

	return coord;
}


float4 WetMap (VSOUT IN ) : COLOR0
{
	// sample the ortho map and detect pockets by sampling around the center and comparing depth
	float2 uv = IN.UVCoord;
	float4 color = tex2D(TESR_SourceBuffer, uv);
	float bias = 0.000001;

	float radius = 0.05 * TESR_WetWorldData.z;// radius will increase with rain status
	float center = tex2D(TESR_OrthoMapBuffer, IN.UVCoord).r - bias;
	float left = tex2D(TESR_OrthoMapBuffer, IN.UVCoord + normalize(float2(-1, -0.3)) * radius).r;
	float right = tex2D(TESR_OrthoMapBuffer, IN.UVCoord + normalize(float2(1, -0.3)) * radius).r;
	float top = tex2D(TESR_OrthoMapBuffer, IN.UVCoord + float2(0, 1) * radius).r;

	float crease = (center > left && center > right && center > top);

	return float4(crease, center, 0, 1);
}


float4 BlurWetMap(VSOUT IN, uniform float2 OffsetMask, uniform float blurRadius) : COLOR0
{
	// blur puddles using a gaussian blur
	float WeightSum = 0.114725602f;
	float2 uv = IN.UVCoord;
	float color = tex2D(TESR_RenderedBuffer, uv).r * WeightSum;

    for (int i = 0; i < cKernelSize; i++)
    {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * blurRadius;
		color += BlurWeights[i] * tex2D(TESR_RenderedBuffer, uv + uvOff).r;
		WeightSum += BlurWeights[i];
    }
	color /= WeightSum;
    return color;
}

float4 Wet( VSOUT IN ) : COLOR0
{
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);

	float depth = readDepth(IN.UVCoord);
	float3 eyeDirection = toWorld(IN.UVCoord);
	float3 camera_vector = eyeDirection * depth;
	float4 worldPos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);
	float3 normal = GetWorldNormal(IN.UVCoord);
	float3 up = float3(0, 0, 1);
	float floorAngle = smoothstep(0.94,1, dot(normal, up));
	eyeDirection = normalize(eyeDirection);

	// early out to avoid computing pixels that aren't puddles
    if (depth > DrawD || worldPos.z < TESR_WaterSettings.x || floorAngle == 0) return color;

	float LODfade = smoothstep(0, DrawD, depth);
	float thickness = 0.003; // thickness of the valid areas around the ortho map depth that will receive the effect (cancels out too far above or below ortho value)

	// get puddle mask from ortho map
	float4 pos = mul(worldPos, TESR_WorldViewProjectionTransform);
	float4 ortho_pos = mul(pos, TESR_ShadowCameraToLightTransformOrtho);
	float puddles = tex2D(TESR_RenderedBuffer, ScreenCoordToTexCoord(ortho_pos, 1).xy).r; // puddles, ortho height
	float ortho = tex2D(TESR_OrthoMapBuffer, ScreenCoordToTexCoord(ortho_pos, 1).xy).r; // puddles, ortho height

	float puddlemask = lerp(pow(puddles * 2, 3), 0, LODfade); // fade out puddles
	// puddlemask *= ((ortho_pos.z < ortho + thickness) && (ortho_pos.z > ortho - thickness)); 
	puddlemask *= (ortho_pos.z > ortho - thickness); 

	// sample and combine rain ripples
	float2 rippleUV = worldPos.xy / 160.0f;
	float4 Weights = float4(1, 0.75, 0.5, 0.25) * TESR_WetWorldData.x;
	Weights = saturate(Weights * 4);
	float3 Ripple1 = ComputeRipple(rippleUV + float2( 0.25f,0.0f), time1, Weights.x);
	float3 Ripple2 = ComputeRipple(rippleUV * 1.1 + float2(-0.55f,0.3f), time2, Weights.y);
	float3 Ripple3 = ComputeRipple(rippleUV * 1.3 + float2(0.6f, 0.85f), time3, Weights.z);
	float3 Ripple4 = ComputeRipple(rippleUV * 1.5 + float2(0.5f,-0.75f), time4, Weights.w);

	float4 Z = lerp(1, float4(Ripple1.z, Ripple2.z, Ripple3.z, Ripple4.z), Weights);
	float3 ripple = float3( Weights.x * Ripple1.xy + Weights.y * Ripple2.xy + Weights.z * Ripple3.xy + Weights.w * Ripple4.xy, Z.x * Z.y * Z.z * Z.w);
	float3 ripnormal = normalize(ripple);
	float3 combnom = float3(ripnormal.xy, 1);

	// calculate puddle color
	float4 puddleColor = color * 0.5; // base color is just darkened ground color
	float4 fresnelColor = TESR_HorizonColor * 0.8;
	float glossiness = 100;
	float fresnel = saturate(pow(1 - shade(-eyeDirection, combnom), 5));
	float specular = saturate(pow(shade(eyeDirection, reflect(TESR_SunDirection.xyz, combnom)), glossiness));

	puddleColor = lerp(puddleColor, fresnelColor, fresnel);
	puddleColor += specular * TESR_SunColor * 2;
	
    return lerp(color, puddleColor, saturate(puddlemask));
}


technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 WetMap();
	}
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurWetMap(float2(1.0f, 0.0f), 2);
	}
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurWetMap(float2(0.0f, 1.0f), 2);
	}
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Wet();
	}
}
