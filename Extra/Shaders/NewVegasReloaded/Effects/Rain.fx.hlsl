// Rain fullscreen shader for Oblivion Reloaded
#define RainLayers 40

float4x4 TESR_WorldViewProjectionTransform;
float4x4 TESR_ViewTransform;
float4x4 TESR_ProjectionTransform;
float4x4 TESR_ShadowCameraToLightTransformOrtho;
float4 TESR_CameraPosition;
float4 TESR_GameTime;
float4 TESR_RainData;
float4 TESR_FogColor;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_OrthoMapBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float PI = 3.14159265;
static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float Zmul = nearZ * farZ;
static const float rangeZ = farZ - nearZ;
static const float timetick = TESR_GameTime.z;
static const float hscale = 0.025f;
static const float3x3 p = float3x3(30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122,30.323122);
static const float DEPTH = TESR_RainData.y;
static const float SPEED = TESR_RainData.z;

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

float3 toWorld(float2 tex)
{
    float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
    v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
    v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
    return v;
}

float readDepth(in float2 coord : TEXCOORD0)
{
	float posZ = tex2D(TESR_DepthBuffer, coord).x;
	posZ = Zmul / ((posZ * rangeZ) - farZ);
	return posZ;
}

float2 cylindrical(float3 world)
{
	float u = -atan2(world.y, world.x) / PI;
	float v = world.z / length(world.xy);
	return float2(0.5f * u + 0.5f, hscale * v);
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
	Ortho = tex2D(TESR_OrthoMapBuffer, OrthoPos.xy).r;
	if (Ortho < OrthoPos.z) return 0.0f;
	return 1.0f;
	
}

float4 Rain( VSOUT IN ) : COLOR0
{
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	float3 world = toWorld(IN.UVCoord);
	
	float depth = readDepth(IN.UVCoord);
	float3 camera_vector = world * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);
	float4 pos = mul(world_pos, TESR_WorldViewProjectionTransform);
	float4 ortho_pos = mul(pos, TESR_ShadowCameraToLightTransformOrtho);	
	float ortho = GetOrtho(ortho_pos);
	
	if (ortho == 0.0f) {
		float stepdepth = (depth - nearZ) / 10.0f;
		[unroll]
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
	
	float2 q;
	float3 n;
	float3 m;
	float3 mp;
	float3 r;
	float2 s;
	float d;
	float edge;
	float sn = 0.0f;
	int l = TESR_RainData.x * RainLayers;
	float2 uv = cylindrical(world);
	
	for (int i = 3; i < l; i++) {
		q = uv * (1.0f + i * DEPTH);
		q += float2(q.y * (fmod(i * 107.238917f, 1.0f) - 0.5f), SPEED * timetick);
		n = float3(floor(q), i);
		m = floor(n) + frac(n);
		mp = m / frac(mul(p, m));
		r = frac(mp);
		s = abs(fmod(q, 1.0f) + r.xy - 1.0f);
		s += 0.01f * abs(2.0f * frac(10.0f * q.yx) - 1.0f); 
		d = 0.6f * max(s.x - s.y, s.x + s.y) + max(s.x, s.y) - 0.01f;
		edge = 0.005f + 0.05f * min(0.25f * i, 1.5f);
		sn += smoothstep(edge, -edge, d) * (r.x / (1.0f + 0.01f * i * DEPTH));
	}
	color += (sn * (TESR_FogColor + 0.5f));
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