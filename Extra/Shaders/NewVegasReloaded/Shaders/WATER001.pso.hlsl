// placed water surface shader 

float4 NotUsed0 : register(c0);
float4 EyePos : register(c1);
float4 ShallowColor : register(c2);
float4 DeepColor : register(c3);
float4 ReflectionColor : register(c4);
float4 FresnelRI : register(c5);
float4 BlendRadius : register(c6);
float4 NotUsed7 : register(c7);
float4 VarAmounts : register(c8);
float4 FogParam : register(c9);
float4 FogColor : register(c10);
float2 DepthFalloff : register(c11);
float4 SunDir : register(c12);
float4 SunColor : register(c13);

float4 TESR_WaveParams : register(c14); // x: choppiness, y:wave width, z: wave speed, w: reflectivity?
float4 TESR_WaterVolume : register(c15); // x: caustic strength, y:shoreFactor, w: turbidity, z: caustic strength S ?
float4 TESR_WaterSettings : register(c16); // x: caustic strength, y:depthDarkness, w: turbidity, z: caustic strength S ?
float4 TESR_GameTime : register(c17);
float4 TESR_HorizonColor : register(c18);
float4 TESR_SunDirection : register(c19);


sampler2D ReflectionMap : register(s0);
sampler2D RefractionMap : register(s1);
sampler2D NoiseMap : register(s2);
sampler2D DisplacementMap : register(s3);
sampler2D DepthMap : register(s4);

sampler2D TESR_samplerWater : register(s5) < string ResourceName = "Water\watercalm_NRM.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; ADDRESSW = WRAP; MAGFILTER = ANISOTROPIC; MINFILTER = ANISOTROPIC; MIPFILTER = ANISOTROPIC; } ;


#include "Includes/Water.hlsl"


PS_OUTPUT main(PS_INPUT IN, float2 PixelPos : VPOS) {
    PS_OUTPUT OUT;

    float alpha = IN.LTEXCOORD_6.w; // color alpha?

    float3 eyeVector = EyePos.xyz - IN.LTEXCOORD_0.xyz; // vector of camera position to point being shaded
    float3 eyeDirection = normalize(eyeVector);         // normalized eye to world vector (for lighting)
    float distance = length(eyeVector.xy);              // surface distance to eye
    float depth = length(eyeVector);                    // depth distance to eye

	float sunLuma = luma(SunColor);
	float placedWaterRefractionModifier = 0.7;		// reduce refraction because of the way placed depth is encoded
	float placedWaterDepthModifier = 0.7;			// reduce depth value for fog because of the way placed depth is encoded

    // calculate fog coeffs
    float4 screenPos = getScreenpos(IN);                // point coordinates in screen space for water surface
    float2 waterDepth = tex2Dproj(DepthMap, screenPos).xy;  // x= shallowfog, y = deepfog?
    float depthFog = saturate(invlerp(DepthFalloff.x, DepthFalloff.y, waterDepth.y));

    float2 fadedDepth = saturate(lerp(waterDepth, 1, invlerp(0, 4096, distance)));
    float2 depths = float2(fadedDepth.y + depth, depth); // deepfog
    depths = saturate((FogParam.x - depths) / FogParam.y); 

    float3 surfaceNormal = getWaveTexture(IN, distance);

    float refractionCoeff = (waterDepth.y * depthFog) * ((saturate(distance * 0.002) * (-4 + VarAmounts.w)) + 4);
    float4 reflectionPos = getReflectionSamplePosition(IN, surfaceNormal, refractionCoeff * placedWaterRefractionModifier );
    float4 reflection = tex2Dproj(ReflectionMap, reflectionPos);
    float4 refractionPos = reflectionPos;
    refractionPos.y = refractionPos.w - reflectionPos.y;
    float3 refractedDepth = tex2Dproj(DepthMap, refractionPos).rgb * placedWaterDepthModifier;

    float4 color = tex2Dproj(RefractionMap, refractionPos);
    color = getLightTravel(refractedDepth, ShallowColor, DeepColor, sunLuma, color);
    color = getTurbidityFog(refractedDepth, ShallowColor, sunLuma, color);
    color = getDiffuse(surfaceNormal, TESR_SunDirection.xyz, eyeDirection, distance, ShallowColor, color);
    color = getFresnel(surfaceNormal, eyeDirection, TESR_HorizonColor, color);
    color = getSpecular(surfaceNormal, TESR_SunDirection.xyz, eyeDirection, SunColor.rgb, color);

    OUT.color_0 = color;
    return OUT;
};
