#define	expand(v)	        (((v) - 0.5) / 0.5)  // from 0/1 to -1/1
#define	shade(n, l)         max(dot(n, l), 0)
#define	shades(n, l)        saturate(dot(n, l))
#define invlerp(a, b, t)    (t-a)/(b-a)
#define luma(color)         color.r * 0.3f + color.g * 0.59f +color.b * 0.11f; // extract luma
#define mix(colora, colorb) colora * colorb * 2 // mix two colors without darkening


// Requires the following registers:
//
//   Name            Reg   Size
//   --------------- ----- ----
//   EyePos          const_1       1
//   ShallowColor    const_2       1
//   DeepColor       const_3       1
//   ReflectionColor const_4       1
//   FresnelRI       const_5       1  //x: reflectamount, y:fresnel, w: opacity, z:speed
//   BlendRadius     const_6       1
//   VarAmounts      const_8       1  // x: water glossiness y: reflectivity z: refrac, w: lod
//   FogParam        const_9       1
//   FogColor        const_10      1
//   DepthFalloff    const_11      1  // start / end depth fog
//   SunDir          const_12      1
//   SunColor        const_13      1
//   ReflectionMap   texture_0       1
//   RefractionMap   texture_1       1
//   NoiseMap        texture_2       1
//   DisplacementMap texture_3       1
//   DepthMap        texture_4       1
//   float4 TESR_WaveParams : register(c14); // x: choppiness, y:wave width, z: wave speed, w: reflectivity?
//   float4 TESR_WaterVolume : register(c15); // x: caustic strength, y:shoreFactor, w: turbidity, z: caustic strength S ?
//   float4 TESR_WaterSettings : register(c16); // x: caustic strength, y:depthDarkness, w: turbidity, z: caustic strength S ?
//   float4 TESR_GameTime : register(c17);
//   float4 TESR_SkyColor : register(c18);
//   float4 TESR_SunDirection : register(c19);
//   sampler2D TESR_samplerWater : register(s5);


struct PS_INPUT {
    float4 LTEXCOORD_0 : TEXCOORD0_centroid;     // world position of underwater points
    float4 LTEXCOORD_1 : TEXCOORD1_centroid;     // local position on plane object surface
    float4 LTEXCOORD_2 : TEXCOORD2_centroid;     // modelviewproj matrix 1st row 
    float4 LTEXCOORD_3 : TEXCOORD3_centroid;     // modelviewproj matrix 2nd row 
    float4 LTEXCOORD_4 : TEXCOORD4_centroid;     // modelviewproj matrix 3rd row 
    float4 LTEXCOORD_5 : TEXCOORD5_centroid;     // modelviewproj matrix 4th row 
    float4 LTEXCOORD_6 : TEXCOORD6;              // displacement sampling position
    float2 LTEXCOORD_7 : TEXCOORD7;              // waves sampling position
};

struct PS_OUTPUT {
    float4 color_0 : COLOR0;
};


float4 getScreenpos(PS_INPUT IN){
    float4 screenPos;  // point coordinates in screen space for water surface
    screenPos.x = dot(IN.LTEXCOORD_2, IN.LTEXCOORD_1);
    screenPos.w = dot(IN.LTEXCOORD_5, IN.LTEXCOORD_1);
    screenPos.y = screenPos.w - dot(IN.LTEXCOORD_3, IN.LTEXCOORD_1);
    screenPos.z = dot(IN.LTEXCOORD_4, IN.LTEXCOORD_1);
    
    return screenPos;
}

float4 getWaveTexture(PS_INPUT IN, float distance) {

    float2 texPos = IN.LTEXCOORD_7;

	float waveWidth = TESR_WaveParams.y;
    float choppiness = TESR_WaveParams.x;
    float speed = TESR_GameTime.x * 0.002 * TESR_WaveParams.z;
    float smallScale = 0.5;
    float bigScale = 2;
    float4 waveTexture = tex2D(TESR_samplerWater, texPos * smallScale * waveWidth + normalize(float2(1, 4)) * speed);
    float4 waveTextureLarge = tex2D(TESR_samplerWater, texPos * bigScale * waveWidth + normalize(float2(-3, -2)) * speed);

    // combine waves
    waveTexture = mix(waveTextureLarge, waveTexture);
    waveTexture = expand(waveTexture) * float4(1, 1, choppiness, 1);
    waveTexture = normalize(waveTexture);

    return waveTexture;
}

float4 getReflectionSamplePosition(PS_INPUT IN, float3 surfaceNormal, float refractionCoeff) {
    int4 const_7 = {0, 2, -1, 1}; // used to cancel/double/invert vector components

    float4 samplePosition;
    samplePosition.xy = ((refractionCoeff * surfaceNormal.xy)) + IN.LTEXCOORD_1.xy;
    // waveTexture.xy = ((refractionCoeff * surfaceNormal.xy) / IN.LTEXCOORD_0.w) + IN.LTEXCOORD_1.xy;
    samplePosition.zw = (IN.LTEXCOORD_1.z * const_7.wx) + const_7.xw;

    float4 reflectionPos = mul(float4x4(IN.LTEXCOORD_2, IN.LTEXCOORD_3, IN.LTEXCOORD_4, IN.LTEXCOORD_5), samplePosition); // convert local normal to view space

    return reflectionPos;
}

float3 getDisplacement(PS_INPUT IN, float blendRadius, float3 surfaceNormal){
    // sample displacement and mix with the wave texture
    float4 displacement = tex2D(DisplacementMap, IN.LTEXCOORD_6.xy);
    // float3 displacementCoeff = displacement;
    // float3 displacementCoeff = abs(displacement.z - 0.5);
    // float displacementCoeff = dot(displacement, float4(0, 0, 1, 1));

    displacement.xy = (displacement.zw - 0.5) * blendRadius / 2;
    displacement.z = 1;

    // sample displacement and mix with the wave texture
    float4 DisplacementNormal = normalize(displacement);
    // float4 DisplacementNormal = displacement;

    // surfaceNormal = normalize(saturate(DisplacementNormal.z * surfaceNormal - DisplacementNormal) + DisplacementNormal);
    // surfaceNormal = DisplacementNormal;
    surfaceNormal = surfaceNormal * 0.5 + 0.5;
    surfaceNormal = float3(surfaceNormal.xy + DisplacementNormal.xy,  surfaceNormal.z);
    surfaceNormal = expand(surfaceNormal);
    // surfaceNormal = lerp(surfaceNormal, normalize(surfaceNormal + DisplacementNormal * 0.5), displacementCoeff);
    // return displacementCoeff;
    // return displacementCoeff.xxx;
    return surfaceNormal;
}

float4 getLightTravel(float3 refractedDepth, float4 ShallowColor, float4 DeepColor, float sunLuma, float4 color){
    float4 waterColor = lerp(ShallowColor, DeepColor, refractedDepth.y); 
    // return color * waterColor * sunLuma / TESR_WaterSettings.y;
    float3 result = color.rgb * lerp(0.7, waterColor.rgb * sunLuma / TESR_WaterSettings.y, pow(abs(refractedDepth.x), TESR_WaterSettings.y)); //never reach 1 so that water is always absorbing some light
    return float4(result, 1);
}

float4 getTurbidityFog(float3 refractedDepth, float4 ShallowColor, float sunLuma, float4 color){
    float turbidity = max(0.00001, TESR_WaterVolume.z); // clamp minimum value to avoid division by 0
    float fogCoeff = 1 - saturate((FogParam.z - (refractedDepth.x * FogParam.z)) / FogParam.w);
    float3 fog = ShallowColor.rgb * sunLuma;

    float3 result = lerp(color.rgb, fog.rgb, saturate(fogCoeff * FogColor.a * turbidity));
    return float4(result, 1);
}

float4 getDiffuse(float3 surfaceNormal, float3 lightDir, float3 eyeDirection, float distance, float4 diffuseColor, float4 color){
    float verticalityFade =  (1 - shades(eyeDirection, float3(0, 0, 1)));
    float distanceFade = smoothstep(0, 1, distance * 0.001);
    float diffuse = shades(lightDir, surfaceNormal) * verticalityFade * distanceFade; // increase intensity with distance
    float3 result = lerp(color.rgb, diffuseColor.rgb, saturate(diffuse));

    return float4(result, 1);
}

float4 getFresnel(float3 surfaceNormal, float3 eyeDirection, float4 reflection, float4 color){
    float reflectivity = TESR_WaveParams.w;

    float fresnelCoeff = saturate(pow((1 - max(0, dot(eyeDirection, surfaceNormal))), 5));

    float4 reflectionColor = lerp (reflection * ReflectionColor, reflection, saturate(reflectivity));
    // float3 reflectionColor = VarAmounts.y * (reflection - ReflectionColor) + ReflectionColor.rgbb;
	float3 result = lerp(color.rgb, reflectionColor.rgb, saturate(fresnelCoeff * reflectivity));
    return float4(result, 1);
}

float4 getSpecular(float3 surfaceNormal, float3 lightDir, float3 eyeDirection, float3 specColor, float4 color){
    float2 scatteringConst = {-0.569999993, 0.819999993}; //scattering to simulate water coming through the waves
    float specularBoost = 2;
    float glossiness = 100;

    float specular = pow(abs(shades(reflect(-eyeDirection, surfaceNormal), lightDir)), VarAmounts.x);
    float scattering = pow(abs(saturate(dot(surfaceNormal.xz, scatteringConst))), glossiness);
    float3 result = color.rgb + (specular + scattering) * specColor * specularBoost;
    return float4(result, 1);
}


float4 getShoreFade(PS_INPUT IN, float depth, float4 color){
    color.a = 1 - pow(abs(1 - depth), FresnelRI.y);
    float scale = 20;
    float speed = 0.3;
    float shoreAnimation = sin(IN.LTEXCOORD_1.x/scale - TESR_GameTime * speed) * 0.4 + 0.8; //reframe sin() from -1/1 to 0.2/1.2 to ensure some fading happens 
    color.a = 1 - pow(abs(1 - depth), 60) * shoreAnimation;
    // return float2(color.a, 1).xxxy;
    return color;
}
