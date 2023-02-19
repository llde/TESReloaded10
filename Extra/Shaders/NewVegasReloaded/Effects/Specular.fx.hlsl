// Specular multiplier fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_SpecularData;					// x: luma treshold, y:blurMultiplier, z:glossiness, w:drawDistance
float4 TESR_SpecularEffects;				// x: specular strength, y:sky tint strenght, z:fresnel strength
float4 TESR_ViewSpaceLightDir;
float4 TESR_SunDirection;
float4 TESR_SunColor;
float4 TESR_SkyColor;
float4 TESR_FogColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_NormalsBuffer : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = NONE; MINFILTER = NONE; MIPFILTER = NONE; };

static const float LumTreshold = TESR_SpecularData.x;
static const float BlurRadius = TESR_SpecularData.y;
static const float Glossiness = TESR_SpecularData.z;
static const float DrawDistance = TESR_SpecularData.w;
static const float SpecStrength = TESR_SpecularEffects.x;
static const float SkyStrength = TESR_SpecularEffects.y;
static const float FresnelStrength = TESR_SpecularEffects.z;


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
#include "Includes/Normals.hlsl"
#include "Includes/Blur.hlsl"

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
	// float3 normal = GetNormal(coord);
	// float3 worldNormal = mul(TESR_ViewTransform, float4(normal, 1)).xyz;
	float3 worldNormal = GetWorldNormal(coord);
	float3 viewRay = normalize(toWorld(IN.UVCoord) * -1);

	// blinn phong specular
	float3 halfwayDir = normalize(TESR_SunDirection.xyz + viewRay);
	float specular = pow(shades(worldNormal, halfwayDir), Glossiness);
	float skyLight = shades(worldNormal, float3(0, 0, 1));

	// float fresnel = (dot(viewRay, halfwayDir));
	float fresnel = pow(1 - dot(viewRay, worldNormal), 5);
	float reflectance = 0.04;
	fresnel = fresnel + reflectance * (1 - fresnel);

	float3 result = float3(specular, skyLight, fresnel);
	result = lerp(result, 0.0, smoothstep(0, DrawDistance, origin.z));

	return float4(result, 1.0);
}


float4 CombineSpecular(VSOUT IN) :COLOR0
{
	// float4 color = float(0).xxxx;
	float4 color = tex2D(TESR_SourceBuffer, IN.UVCoord);
	float4 light = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	float luminance = luma(color);

	float4 result = color;

	// skylight
	result += light.g * TESR_SkyColor * 0.1 * SkyStrength * saturate(smoothstep(0.4, 0, luminance)); // skylight is more pronounced in darker areas

	// fresnel
	result += light.b * color * saturate(luminance * 2) * FresnelStrength; //fresnel scales with the luminance, but reaches full power at half max luminance

	// specular
	result += lerp(0, light.r * SpecStrength * TESR_SunColor, saturate(invlerp(LumTreshold, 1, luminance))) * light.b; // specular will boost areas above treshold

	return float4 (result.rgb, 1.0f);
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
		PixelShader = compile ps_3_0 BlurRChannel(float2(1.0f, 0.0f), BlurRadius, 1, DrawDistance);
	}
	
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurRChannel(float2(0.0f, 1.0f), BlurRadius, 1, DrawDistance);
	}

	// pass
	// { 
	// 	VertexShader = compile vs_3_0 FrameVS();
	// 	PixelShader = compile ps_3_0 BoxBlur();
	// }

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 CombineSpecular();
	}
}