// Snow accumulation fullscreen shader for Oblivion Reloaded

float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformOrtho;
float4 TESR_CameraPosition;
float4 TESR_SunDirection;
float4 TESR_SunColor;
float4 TESR_ReciprocalResolution;
float4 TESR_SnowAccumulationParams;
float4 TESR_WaterSettings;
float4 TESR_FogData;
float4 TESR_FogColor;
float4 TESR_OrthoData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_OrthoMapBuffer : register(s3) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SnowSampler : register(s4) < string ResourceName = "Precipitations\snow.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SnowNormSampler : register(s5) < string ResourceName = "Precipitations\snow_NRM.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float2 OffsetMaskH = float2(1.0f, 0.0f);
static const float2 OffsetMaskV = float2(0.0f, 1.0f);
static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;
static const int cKernelSize = 24;
static const float BIAS = 0.02f;

static const float BlurWeights[cKernelSize] = 
{
	0.019956226f,
	0.021463016f,
	0.032969806f,
	0.044476596f,
	0.055983386f,
	0.067490176f,
	0.078996966f,
	0.080503756f,
	0.092010546f,
	0.105024126f,
	0.116530916f,
	0.128037706f,
	0.128037706f,
	0.116530916f,
	0.105024126f,
	0.092010546f,
	0.080503756f,
	0.078996966f,
	0.067490176f,
	0.055983386f,
	0.044476596f,
	0.032969806f,
	0.021463016f,
	0.019956226f
};

static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-12.0f * TESR_ReciprocalResolution.x, -12.0f * TESR_ReciprocalResolution.y),
	float2(-11.0f * TESR_ReciprocalResolution.x, -11.0f * TESR_ReciprocalResolution.y),
	float2(-10.0f * TESR_ReciprocalResolution.x, -10.0f * TESR_ReciprocalResolution.y),
	float2( -9.0f * TESR_ReciprocalResolution.x,  -9.0f * TESR_ReciprocalResolution.y),
	float2( -8.0f * TESR_ReciprocalResolution.x,  -8.0f * TESR_ReciprocalResolution.y),
	float2( -7.0f * TESR_ReciprocalResolution.x,  -7.0f * TESR_ReciprocalResolution.y),
	float2( -6.0f * TESR_ReciprocalResolution.x,  -6.0f * TESR_ReciprocalResolution.y),
	float2( -5.0f * TESR_ReciprocalResolution.x,  -5.0f * TESR_ReciprocalResolution.y),
	float2( -4.0f * TESR_ReciprocalResolution.x,  -4.0f * TESR_ReciprocalResolution.y),
	float2( -3.0f * TESR_ReciprocalResolution.x,  -3.0f * TESR_ReciprocalResolution.y),
	float2( -2.0f * TESR_ReciprocalResolution.x,  -2.0f * TESR_ReciprocalResolution.y),
	float2( -1.0f * TESR_ReciprocalResolution.x,  -1.0f * TESR_ReciprocalResolution.y),
	float2(  1.0f * TESR_ReciprocalResolution.x,   1.0f * TESR_ReciprocalResolution.y),
	float2(  2.0f * TESR_ReciprocalResolution.x,   2.0f * TESR_ReciprocalResolution.y),
	float2(  3.0f * TESR_ReciprocalResolution.x,   3.0f * TESR_ReciprocalResolution.y),
	float2(  4.0f * TESR_ReciprocalResolution.x,   4.0f * TESR_ReciprocalResolution.y),
	float2(  5.0f * TESR_ReciprocalResolution.x,   5.0f * TESR_ReciprocalResolution.y),
	float2(  6.0f * TESR_ReciprocalResolution.x,   6.0f * TESR_ReciprocalResolution.y),
	float2(  7.0f * TESR_ReciprocalResolution.x,   7.0f * TESR_ReciprocalResolution.y),
	float2(  8.0f * TESR_ReciprocalResolution.x,   8.0f * TESR_ReciprocalResolution.y),
	float2(  9.0f * TESR_ReciprocalResolution.x,   9.0f * TESR_ReciprocalResolution.y),
	float2( 10.0f * TESR_ReciprocalResolution.x,  10.0f * TESR_ReciprocalResolution.y),
	float2( 11.0f * TESR_ReciprocalResolution.x,  11.0f * TESR_ReciprocalResolution.y),
	float2( 12.0f * TESR_ReciprocalResolution.x,  12.0f * TESR_ReciprocalResolution.y)
};

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

float readDepth(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	posZ = Zmul / ((posZ * Zdiff) - farZ);
	return posZ;
}

float readDepth01(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	return (2.0f * nearZ) / (nearZ + farZ - posZ * (farZ - nearZ));
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

float Lookup(float4 ShadowPos, float2 OffSet) {
	
	float Shadow = tex2D(TESR_OrthoMapBuffer, ShadowPos.xy + float2(OffSet.x * TESR_OrthoData.z, OffSet.y * TESR_OrthoData.z)).r;
	if (Shadow < ShadowPos.z - BIAS) return 0.25f;
	return 1.0f;
	
}

float GetOrtho(float4 OrthoPos) {
	
	float Ortho;
	float x;
	float y;
	
	OrthoPos.xyz /= OrthoPos.w;
    if (OrthoPos.x < -1.0f || OrthoPos.x > 1.0f ||
        OrthoPos.y < -1.0f || OrthoPos.y > 1.0f ||
        OrthoPos.z <  0.0f || OrthoPos.z > 1.0f)
		return 1.0f;
 
    OrthoPos.x = OrthoPos.x *  0.5f + 0.5f;
    OrthoPos.y = OrthoPos.y * -0.5f + 0.5f;
	for (y = -0.5f; y <= 0.5f; y += 0.25f) {
		for (x = -0.5f; x <= 0.5f; x += 0.25f) {
			Ortho += Lookup(OrthoPos, float2(x, y));
		}
	}
	Ortho /= 25.0f;	
	return Ortho;
	
}

float4 GetNormals( VSOUT IN ) : COLOR0
{
	float depth = readDepth(IN.UVCoord);
	float3 pos = getPosition(IN.UVCoord, depth);

    float3 left = pos - getPosition(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(-1, 0), readDepth(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(-1, 0)));
    float3 right = getPosition(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(1, 0), readDepth(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(1, 0))) - pos;
    float3 up = pos - getPosition(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(0, -1), readDepth(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(0, -1)));
    float3 down = getPosition(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(0, 1), readDepth(IN.UVCoord + TESR_ReciprocalResolution.xy * float2(0, 1))) - pos;
    float3 dx = length(left) < length(right) ? left : right;
    float3 dy = length(up) < length(down) ? up : down;
	float3 norm = normalize(cross(dx,dy));
	
	norm.z *= -1;

	return float4((norm + 1) / 2, 1);
}

//float4 GetNormals2( VSOUT IN ) : COLOR0
//{
//	float2 uv0 = IN.UVCoord;
//	float2 uv1 = IN.UVCoord + TESR_ReciprocalResolution.xy * float2(1, 0);
//	float2 uv2 = IN.UVCoord + TESR_ReciprocalResolution.xy * float2(0, -1);
//	float depth0 = readDepth(uv0);
//	float depth1 = readDepth(uv1);
//	float depth2 = readDepth(uv2);
//	float3 pos0 = getPosition(uv0, depth0);
//	float3 pos1 = getPosition(uv1, depth1);
//	float3 pos2 = getPosition(uv2, depth2);
//	float3 norm = normalize(cross(pos2 - pos0, pos1 - pos0));
//	
//	norm.z *= -1;
//	return float4((norm + 1) / 2, 1);
//
//}

float4 BlurNormals(VSOUT IN, uniform float2 OffsetMask) : COLOR0
{
	float WeightSum = 0.12f * saturate(1 - TESR_SnowAccumulationParams.x);
	float3 oColor = tex2D(TESR_RenderedBuffer,IN.UVCoord).rgb;
	float3 finalColor = oColor * WeightSum;
	float depth = readDepth01(IN.UVCoord);
	if (depth == 0.0f || depth >= 0.9f) discard;
	
	for (int i = 0; i < cKernelSize; i++) {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * TESR_SnowAccumulationParams.y * abs(log(depth));
		float3 Color = tex2D(TESR_RenderedBuffer, IN.UVCoord + uvOff).rgb;
		float weight = BlurWeights[i] * saturate(dot(Color.xyz * 2 - 1, oColor.xyz * 2 - 1) - TESR_SnowAccumulationParams.x * 0.75f);
		finalColor += weight * Color;
		WeightSum += weight;
	}
	
	finalColor /= WeightSum;
    return float4(finalColor, 1.0f);
}

float4 Snow( VSOUT IN ) : COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
	float3 world = toWorld(IN.UVCoord);
	
	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = world * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);
	float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);
	float4 ortho_pos = mul(pos, TESR_ShadowCameraToLightTransformOrtho);	
	float ortho = GetOrtho(ortho_pos);
	
    if (world_pos.z >= TESR_WaterSettings.x + 1) {
		float2 uv = world_pos.xy / 200.0f;
		float3 norm = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb * 2 - 1;
		float3 detail_norm = reflect(tex2D(TESR_SnowNormSampler, uv).rgb * 2 - 1, norm);
		detail_norm.z *= -1;
		
		float3 snow_tex = tex2D(TESR_SnowSampler, uv).rgb;
		float3 snow_light = TESR_FogColor.rgb + (min(TESR_FogData.z, 0.4) * TESR_SnowAccumulationParams.z) + (TESR_SunColor.rgb * TESR_SnowAccumulationParams.z) * dot(TESR_SunDirection.xyz, detail_norm);
		float3 snow_diffuse = snow_light * snow_tex;
		float sat = saturate(saturate(norm.z * ortho * TESR_SnowAccumulationParams.w) * 2 - 1) * saturate(lerp(1, 0, (depth * 0.5 - TESR_FogData.x) / (TESR_FogData.y - TESR_FogData.x)));

		color.rgb = color * (1 - sat) + snow_diffuse * sat;
    }
    return float4(color, 1.0f);
}

technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 GetNormals();
	}
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurNormals(OffsetMaskH);
	}
	pass
	{ 
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurNormals(OffsetMaskV);
	}
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Snow();
	}
}
