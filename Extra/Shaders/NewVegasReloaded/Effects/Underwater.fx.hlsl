// Underwater fullscreen shader for Oblivion Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_SunDirection;
float4 TESR_GameTime;
float4 TESR_WaterCoefficients; // r g b scattering
float4 TESR_SunColor;
float4 TESR_FogColor;
float4 TESR_FogData;
float4 TESR_WaterVolume;
float4 TESR_WaveParams;
float4 TESR_WaterSettings;
float4 TESR_WaterShallowColor;
float4 TESR_WaterDeepColor;
float4 TESR_DebugVar;
float4 TESR_HorizonColor;
float4 TESR_SkyColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_WavesSampler : register(s2) < string ResourceName = "Water\water_NRM.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; ADDRESSW = WRAP; MAGFILTER = ANISOTROPIC; MINFILTER = ANISOTROPIC; MIPFILTER = ANISOTROPIC; } ;
sampler2D TESR_NormalsBuffer : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

static const float frame = TESR_GameTime.z * TESR_WaveParams.z * 1.5;
static const float4x4 ditherMat = { 0.0588, 0.5294, 0.1765, 0.6471,
									0.7647, 0.2941, 0.8824, 0.4118,
									0.2353, 0.7059, 0.1176, 0.5882,
									0.9412, 0.4706, 0.8235, 0.3259 };

static const float causticsStrength = TESR_WaterVolume.x;
static const float shoreFactor = TESR_WaterVolume.y;
static const float turbidity = TESR_WaterVolume.z;
static const float3 extCoeff = TESR_WaterCoefficients.xyz;// * turbidity;
static const float scattCoeff = TESR_WaterCoefficients.w;// * turbidity;
static const float waveWidth = TESR_WaveParams.y;
static const float depthDarkness = TESR_WaterSettings.y;

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


float4 getSkyColor(float3 eyeDirection){
    float3 skyColor = lerp(TESR_HorizonColor, TESR_SkyColor, pow(shade(eyeDirection, float3(0, 0, 1)), 0.5));
    skyColor += TESR_SunColor.rgb * pow(shades(eyeDirection, TESR_SunDirection.xyz), 12);
    return float4(skyColor, 1);
}

float4 Water( VSOUT IN ) : COLOR0 {
	float3 color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
    float depth = readDepth(IN.UVCoord);
    float3 eyeVector = toWorld(IN.UVCoord);
	float3 eyeDirection = normalize(eyeVector);
    float3 worldPos = TESR_CameraPosition.xyz + eyeVector * depth;
	float3 eyePos = TESR_WaterSettings.x - TESR_CameraPosition.xyz;
	float fogDepth = length(eyeVector * depth);
	float waterDepth = TESR_WaterSettings.x - worldPos.z; 

	float density = 0.08;// * TESR_DebugVar.x;  // 8
	float falloff = 0.00225;// * TESR_DebugVar.y;  // 2.25

	//vertical exponential depth fog used to darken bottom
	float fogAmount = saturate((density/falloff) * exp(-TESR_CameraPosition.z*falloff) * (1.0 - exp( -fogDepth*eyeDirection.z*falloff ))/eyeDirection.z);

	// horizontal scattering
	float3 skyColor = getSkyColor(eyeDirection);
	// interpolate fog color between shallow and deep water based on viewing angle. Shallow waters get tinted with the sky
	float3 fogColor = lerp(TESR_WaterDeepColor, TESR_WaterShallowColor + skyColor * 0.2, saturate(compress(dot(eyeDirection, float3(0, 0, 1))* 5))) ;
	float3 scattering = pow(invlerp(TESR_FogData.x, TESR_FogData.y, fogDepth).xxx, TESR_FogData.w * fogColor * extCoeff * scattCoeff);
	float linearFog = saturate(invlerp(TESR_FogData.x, TESR_FogData.y, fogDepth));

	color *= lerp(1, TESR_WaterDeepColor, fogAmount); // surface light absorption
	color = lerp(color, fogColor * scattering, linearFog); // scattering absorption
	color = lerp(color, fogColor, saturate(pow(linearFog, 80))); // lod hiding

		//Caustics
		
		
		
		
		
	
	
	
}

float4 WaterDistortion( VSOUT IN ) : COLOR0 {
	IN.UVCoord.x += sin(frame * 3 + IN.UVCoord.x * 20) * 0.002f;
	IN.UVCoord.y += cos(frame * 3 + IN.UVCoord.y * 20) * 0.002f;
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