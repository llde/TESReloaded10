// Underwater fullscreen shader for Oblivion Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_SunDirection;
float4 TESR_GameTime;
float4 TESR_WaterCoefficients; // r g b scattering
float4 TESR_SunColor;
float4 TESR_FogColor;
float4 TESR_FogData; // x: near fog distance, y:far fog distance, z: sun glare, w: fog power
float4 TESR_WaterVolume; // x; causticsStrength, y:shore factor, z:turbidity, w: causticsStrengthS
float4 TESR_WaveParams;
float4 TESR_WaterSettings; // x: water plane height, y: depth darkness
float4 TESR_WaterShallowColor; // Shallow color used by the game for water
float4 TESR_WaterDeepColor; // Deep color used by the game for water
float4 TESR_DebugVar;
float4 TESR_HorizonColor;
float4 TESR_SkyColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_WavesSampler : register(s2) < string ResourceName = "Water\water_NRM.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; ADDRESSW = WRAP; MAGFILTER = ANISOTROPIC; MINFILTER = ANISOTROPIC; MIPFILTER = ANISOTROPIC; } ;
sampler2D TESR_NormalsBuffer : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };
sampler2D TESR_BlueNoiseSampler : register(s4) < string ResourceName = "Effects\bluenoise256.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

static const float frame = TESR_GameTime.z * TESR_WaveParams.z * 1.5;
static const float4x4 ditherMat = {{0.0588, 0.5294, 0.1765, 0.6471},
									{0.7647, 0.2941, 0.8824, 0.4118},
									{0.2353, 0.7059, 0.1176, 0.5882},
									{0.9412, 0.4706, 0.8235, 0.3259}};

static const float causticsStrength = TESR_WaterVolume.x;
static const float shoreFactor = TESR_WaterVolume.y;
static const float turbidity = TESR_WaterVolume.z;
static const float3 extCoeff = TESR_WaterCoefficients.xyz;// * turbidity;
static const float scattCoeff = TESR_WaterCoefficients.w;// * turbidity;
static const float waveWidth = TESR_WaveParams.y;
static const float depthDarkness = TESR_WaterSettings.y;
static const float3 up = float3(0, 0, 1);

#include "Includes/Helpers.hlsl"
#include "Includes/Depth.hlsl"
#include "Includes/Normals.hlsl"


struct VSOUT {
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

struct VSIN {
	float4 vertPos : POSITION0;
	float2 UVCoord : TEXCOORD0;
};

VSOUT FrameVS(VSIN IN) {
	VSOUT OUT = (VSOUT)0.0f;
	OUT.vertPos = IN.vertPos;
	OUT.UVCoord = IN.UVCoord;
	return OUT;
}


float3 random(float2 seed)
{
	return tex2D(TESR_BlueNoiseSampler, (seed/256 + 0.5) / TESR_ReciprocalResolution.xy).xyz;
}

float4 getSkyColor(float3 eyeDirection){
    float3 skyColor = lerp(TESR_HorizonColor, TESR_SkyColor, pow(shade(eyeDirection, float3(0, 0, 1)), 0.5));
    skyColor += TESR_SunColor.rgb * pow(shades(eyeDirection, TESR_SunDirection.xyz), 12);
    return float4(skyColor, 1);
}

float4 getWaveTexture(float2 uv) {
    float2 texPos = uv;

	float waveWidth = TESR_WaveParams.y;
    float choppiness = TESR_WaveParams.x;
    float speed = TESR_GameTime.x * 0.002 * TESR_WaveParams.z;
    float smallScale = 0.5;
    float bigScale = 2;
    float4 waveTexture = expand(tex2D(TESR_WavesSampler, texPos * smallScale * waveWidth + normalize(float2(1, 4)) * speed));
    float4 waveTextureLarge = expand(tex2D(TESR_WavesSampler, texPos * bigScale * waveWidth + normalize(float2(-3, -2)) * speed));

    // combine waves
    waveTexture = float4(waveTextureLarge.xy + waveTexture.xy,  1, 1);
    waveTexture.xy *= choppiness;

    waveTexture = normalize(waveTexture);
    return waveTexture;
}

float getCaustics(float3 pos){
	float depth = TESR_WaterSettings.z - pos.z;
	pos += (depth/TESR_SunDirection.z) * TESR_SunDirection.xyz; // we go to the surface in the direction of the sun to sample

	return pow(1 - shade(getWaveTexture(pos.xy * 0.0005).xyz, up), 10) * 100000 * causticsStrength;
}


float4 Water( VSOUT IN ) : COLOR0 {
	float depth = readDepth(IN.UVCoord);
    float3 eyeVector = toWorld(IN.UVCoord);
	float3 eyeDirection = normalize(eyeVector);
    float3 worldPos = TESR_CameraPosition.xyz + eyeVector * depth;
	float3 eyePos = TESR_WaterSettings.x - TESR_CameraPosition.xyz;
	float fogDepth = length(eyeVector * depth); // a depth measure that's at the same distance from the camera at all angles
	float waterDepth = TESR_WaterSettings.x - worldPos.z; 
	float sunLuma = luma(TESR_SunColor);
	float3 floorNormal = GetWorldNormal(IN.UVCoord);

	float3 color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;

	//vertical exponential depth fog used to darken bottom
	float density = 0.08;// * TESR_DebugVar.x;  // 8
	float falloff = 0.00225;// * TESR_DebugVar.y;  // 2.25 // tie to darkness setting?
	float fogAmount = saturate((density/falloff) * exp(-TESR_CameraPosition.z*falloff) * (1.0 - exp( -fogDepth*eyeDirection.z*falloff ))/eyeDirection.z);

	// horizontal scattering
	float3 skyColor = getSkyColor(eyeDirection);

	// interpolate fog color between shallow and deep water based on viewing angle. Shallow waters get tinted with the sky
	float verticalFade = saturate(compress(dot(eyeDirection, up) * 3)); // fade from deep to shallow based on viewing angle
	float sunDirFade = compress(dot(eyeDirection.xyz, TESR_SunDirection.xyz)); // fade based on proximity to the sun angle

	float3 fogColor = lerp(TESR_WaterDeepColor.rgb, TESR_WaterShallowColor.rgb + skyColor * 0.2, verticalFade); // mix in some sky color into shallow fog
	fogColor *= sunLuma * (0.4 + (1 - 0.4) * sunDirFade) * extCoeff; //scale fog brightness with sunluma/sun direction and apply user setting modifiers
	float3 scattering = pow(invlerp(TESR_FogData.x, TESR_FogData.y, fogDepth).xxx, TESR_FogData.w * fogColor * scattCoeff); // lerp colors at different speed
	float linearFog = saturate(invlerp(TESR_FogData.x, TESR_FogData.y, fogDepth));

	float floorAngle = (smoothstep(0.5,1, dot(floorNormal, up)) + smoothstep(0.8,1, dot(floorNormal, TESR_SunDirection.xyz))) / 2;
	float depthFade = smoothstep(800, 0, waterDepth);
	float distanceFade = smoothstep(6000, 0, fogDepth);

	float caustics = getCaustics(worldPos); // x: 0.9
	color += caustics * TESR_SunColor * depthFade * floorAngle * distanceFade * sunLuma; //y: 0.30

	// blend fog layers colors
	color *= lerp(1, TESR_WaterDeepColor, fogAmount); // surface light absorption
	color = lerp(color, fogColor * scattering, linearFog); // scattering absorption
	color = lerp(color, fogColor, saturate(pow(linearFog, 10))); // lod hiding

	// volumetric god rays
	float godraysMaxDistance = 1000;
	float3 godrayDepthVector = (eyeVector * min(fogDepth, godraysMaxDistance));
	float3 samplingEnd = TESR_CameraPosition.xyz + godrayDepthVector;
	float3 step = godrayDepthVector / 50;

	[unroll]
	for (int i=1; i<32; i++){
		float3 samplingVector = step * lerp(0.8, 1, random(IN.UVCoord + TESR_ReciprocalResolution.xy * i)) * i;
		float3 samplingUV = samplingEnd - samplingVector;
		float samplingDepthFade = smoothstep(500, 0, TESR_WaterSettings.x - samplingUV.z);
		float distance = length(samplingVector);
		float samplingDistanceFade = saturate(invlerp(godraysMaxDistance, 0, distance));
		color += getCaustics(samplingUV) * lerp(fogColor, TESR_SunColor, samplingDistanceFade) * sunLuma * 0.008 * samplingDepthFade * samplingDistanceFade;
	}

	// reduce banding
	float2 uv = IN.UVCoord.xy / TESR_ReciprocalResolution.xy;
	color += ditherMat[ (uv.x)%4 ][ (uv.y)%4 ] / 255;
    return float4(color, 1);
	
}

float4 WaterDistortion( VSOUT IN ) : COLOR0 {
	IN.UVCoord.x += sin(frame * 3 + IN.UVCoord.x * 60) * 0.001f;
	IN.UVCoord.y += cos(frame * 3 + IN.UVCoord.y * 60) * 0.001f;
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	color.a = 1;
    return color;
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Water();
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 WaterDistortion();
	}	
}