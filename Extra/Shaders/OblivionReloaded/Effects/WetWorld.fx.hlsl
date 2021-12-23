// WetWorld fullscreen shader for Oblivion Reloaded

float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4 TESR_CameraPosition;
float4 TESR_SunDirection;
float4 TESR_ReciprocalResolution;
float4 TESR_GameTime;
float4 TESR_FogColor;
float4 TESR_SunColor;
float4 TESR_WetWorldCoeffs;
float4 TESR_WaterSettings;
float4 TESR_FogData;
float4 TESR_WetWorldData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_PuddleSampler : register(s3) < string ResourceName = "Precipitations\puddles.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_RippleSampler : register(s4) < string ResourceName = "Precipitations\ripples.dds"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float Zdiff = farZ - nearZ;
static const float depthRange = nearZ - farZ;
static const float PI = 3.14159265;
static const float time1 = TESR_GameTime.z * 1.1f;
static const float time2 = TESR_GameTime.z * 1.2f;
static const float time3 = TESR_GameTime.z * 1.3f;
static const float time4 = TESR_GameTime.z * 1.4f;

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

float3 ComputeRipple(float2 UV, float CurrentTime, float Weight)
{
    float4 Ripple = tex2D(TESR_RippleSampler, UV);
	
    Ripple.yz = Ripple.yz * 2 - 1;

    float DropFrac = frac(Ripple.w + CurrentTime);
    float TimeFrac = DropFrac - 1.0f + Ripple.x;
    float DropFactor = saturate(0.2f + Weight * 0.8f - DropFrac);
    float FinalFactor = DropFactor * Ripple.x * sin( clamp(TimeFrac * 9.0f, 0.0f, 3.0f) * PI);

    return float3(Ripple.yz * FinalFactor * 0.35f, 1.0f);
}

float4 Wet( VSOUT IN ) : COLOR0
{
	float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
    float3 screen_color = color;

    float depth = readDepth(IN.UVCoord);
    float3 camera_vector = toWorld(IN.UVCoord) * depth;
	float3 norm_camera_vector = normalize(camera_vector);
    float3 world_pos = TESR_CameraPosition.xyz + camera_vector;
	
    if ( (depth / depthRange < 1) && ( world_pos.z >= TESR_WaterSettings.x + 1 ) )
    {
		float3 norm = tex2D(TESR_RenderedBuffer, IN.UVCoord ).rgb * 2 - 1;
		float2 uv = world_pos.xy / 750.0f;
		float2 ruv = world_pos.xy / 160.0f;
		float4 Weights = float4(1, 0.75, 0.5, 0.25) * TESR_WetWorldData.y;
		Weights = saturate(Weights * 4);
		
		float3 Ripple1 = ComputeRipple(ruv + float2( 0.25f,0.0f), time1, Weights.x);
		float3 Ripple2 = ComputeRipple(ruv * 1.1 + float2(-0.55f,0.3f), time2, Weights.y);
		float3 Ripple3 = ComputeRipple(ruv * 1.3 + float2(0.6f, 0.85f), time3, Weights.z);
		float3 Ripple4 = ComputeRipple(ruv * 1.5 + float2(0.5f,-0.75f), time4, Weights.w);

		float4 Z = lerp(1, float4(Ripple1.z, Ripple2.z, Ripple3.z, Ripple4.z), Weights);
		float3 Normal = float3( Weights.x * Ripple1.xy + Weights.y * Ripple2.xy + Weights.z * Ripple3.xy + Weights.w * Ripple4.xy, Z.x * Z.y * Z.z * Z.w);
		float3 ripnorm = normalize(Normal) * 0.5 + 0.5;
		ripnorm = ripnorm * 2.0 - 1.0;
		float3 combnom = float3((norm.xy + 10 * ripnorm.xy), 1);
		float3 mudp = float3(0.62, 0.6, 0.54);
		
		float fresnel = dot(-norm_camera_vector, combnom);
		fresnel = 0.02 + pow(( 2 * (fresnel - 0.23)), 5) * 0.2;
		fresnel = saturate( 1-fresnel);

		float3 rain_diffuse = screen_color * lerp(1, 0.3, TESR_WetWorldData.x * 0.3);
		rain_diffuse = lerp(rain_diffuse, mudp, TESR_WetWorldData.x * 0.4);
		rain_diffuse = lerp(rain_diffuse * 0.6, TESR_FogColor.rgb * TESR_WetWorldCoeffs.xyz, fresnel * 0.7);
		
		float vdotr = dot(-norm_camera_vector, reflect(-TESR_SunDirection.xyz, ripnorm));
		vdotr = saturate(1.0025 * vdotr);
		float3 spec = TESR_SunColor.rgb * (pow(vdotr, 170) + 0.07 * pow(vdotr, 4));
		rain_diffuse += spec * TESR_WetWorldCoeffs.w;
		
		float hormask = smoothstep(0.92,1, norm.z);
		float puddlemask = tex2D(TESR_PuddleSampler, uv * 0.5).r;
		float pm2 = tex2D(TESR_PuddleSampler, uv * 1.5).r;
		float pm3 = tex2D(TESR_PuddleSampler, uv * 0.3).r;
		puddlemask = saturate(puddlemask * pm2 + pm3);	
		puddlemask = saturate(pow(puddlemask, lerp(4, 1, TESR_WetWorldData.x * 0.5)));		
		puddlemask += saturate(1 - hormask);
		puddlemask = saturate(puddlemask);		
  		rain_diffuse *= (1 - puddlemask);
		rain_diffuse += puddlemask * screen_color;
		screen_color *= 1 - (saturate(saturate(norm.z * TESR_WetWorldData.x) * 2 - 1) * saturate(lerp(1,0, (depth - TESR_FogData.x) / (TESR_FogData.y - TESR_FogData.x))));
		rain_diffuse *= saturate(saturate(norm.z * TESR_WetWorldData.x) * 2 - 1) * saturate(lerp(1,0, (depth - TESR_FogData.x) / (TESR_FogData.y - TESR_FogData.x)));
		
		color = screen_color + rain_diffuse;
		
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
		PixelShader = compile ps_3_0 Wet();
	}
}
