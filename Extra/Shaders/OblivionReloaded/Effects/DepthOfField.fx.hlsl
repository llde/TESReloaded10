// Depth of Field fullscreen shader for Oblivion/Skyrim Reloaded

float4x4 TESR_ProjectionTransform; 
float4 TESR_ReciprocalResolution;
float4 TESR_DepthOfFieldBlur;
float4 TESR_DepthOfFieldData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state {ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float nearZ = TESR_ProjectionTransform._43 / TESR_ProjectionTransform._33;
static const float farZ = (TESR_ProjectionTransform._33 * nearZ) / (TESR_ProjectionTransform._33 - 1.0f);
static const float depthRange = (nearZ - farZ) * 0.01;
static const float k = 0.00001;
static const float eps = 0.000001;
static const float FocusPoint = 60.0;
static const float FocusPower = 60.0;
static const float Accomodation = 10.0;
static const bool DistantBlur = bool(TESR_DepthOfFieldBlur.x);

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
	return (2.0f * nearZ) / (nearZ + farZ - posZ * (farZ - nearZ));
}
 
static float focus = readDepth(float2(0.5, 0.5));

static float2 taps[12] =
{
    float2(-0.326212, -0.405810),
    float2(-0.840144, -0.073580),
    float2(-0.695914,  0.457137),
    float2(-0.203345,  0.620716),
    float2( 0.962340, -0.194983),
    float2( 0.473434, -0.480026),
    float2( 0.519456,  0.767022),
    float2( 0.185461, -0.893124),
    float2( 0.507431,  0.064425),
    float2( 0.896420,  0.412458),
    float2(-0.321940, -0.932615),
    float2(-0.791559, -0.597710)
};

float4 DoF(VSOUT IN) : COLOR0
{
	float s = focus * depthRange;
	float z = readDepth(IN.UVCoord) * depthRange;

	float fpf = clamp(1 / s + FocusPoint, FocusPower, FocusPower + Accomodation);
	float c = TESR_DepthOfFieldData.z * (FocusPoint - fpf + 1 / z) / FocusPoint / k;
	c = sign(z-s) * min(abs(c), TESR_DepthOfFieldData.y) / (2 * TESR_DepthOfFieldData.y) * step(eps, z);
 
	if (DistantBlur) c = 0.5 * smoothstep(TESR_DepthOfFieldBlur.y, TESR_DepthOfFieldBlur.z, z);
 
	c *= smoothstep(TESR_DepthOfFieldData.w - 0.05, TESR_DepthOfFieldData.w, z);
	c += 0.5;
 
	return float4(c, c, c, c);
}
 
float4 SmartBlur(VSOUT IN) : COLOR0
{
    float3 color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
    float c = TESR_DepthOfFieldBlur.w * 2 * TESR_DepthOfFieldData.y * (tex2D(TESR_RenderedBuffer, IN.UVCoord).r - 0.5);
    float amount = 1;
 
    for (int i = 0; i < 12; i++)
    {
        float2 dir = taps[i];
        float2 s_tex = IN.UVCoord + TESR_ReciprocalResolution.xy * dir * c;
        float3 s_color = tex2D(TESR_SourceBuffer, s_tex).rgb;
        float s_c = (tex2D(TESR_RenderedBuffer, s_tex).r - 0.5) * 2 * TESR_DepthOfFieldData.y;
        float weight = min(exp2(-(c - s_c) / TESR_DepthOfFieldData.x), 2);
 
        color += s_color * weight;
        amount += weight;
    }

    return float4(color / amount, 1);
}
 
float4 BlurPS(VSOUT IN, uniform bool VertBlur) : COLOR0
{
	float3 color;
	float depth = readDepth(IN.UVCoord);
    float s = focus * depthRange;
    float z = depth * depthRange;
	
	if (!DistantBlur || depth < 1) {
		float fpf = clamp(1 / s + FocusPoint, FocusPower, FocusPower + Accomodation);
		float c = TESR_DepthOfFieldBlur.w * TESR_DepthOfFieldData.z * (FocusPoint - fpf + 1 / z) / FocusPoint / k;
		c = min(abs(c), TESR_DepthOfFieldData.y) * step(eps, z);
	 
		if (DistantBlur) c = TESR_DepthOfFieldData.y * smoothstep(TESR_DepthOfFieldBlur.y, TESR_DepthOfFieldBlur.z, z);
	 
		c *= smoothstep(TESR_DepthOfFieldData.w - 0.05, TESR_DepthOfFieldData.w, z);
		clip(c - 0.001);
	 
		float scale = c / 8;
		color = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb * 70;
		
		if (!VertBlur) {
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x - TESR_ReciprocalResolution.x * 1 * scale, IN.UVCoord.y)).rgb * 56;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x + TESR_ReciprocalResolution.x * 1 * scale, IN.UVCoord.y)).rgb * 56;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x - TESR_ReciprocalResolution.x * 2 * scale, IN.UVCoord.y)).rgb * 28;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x + TESR_ReciprocalResolution.x * 2 * scale, IN.UVCoord.y)).rgb * 28;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x - TESR_ReciprocalResolution.x * 3 * scale, IN.UVCoord.y)).rgb * 8;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x + TESR_ReciprocalResolution.x * 3 * scale, IN.UVCoord.y)).rgb * 8;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x - TESR_ReciprocalResolution.x * 4 * scale, IN.UVCoord.y)).rgb * 1;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x + TESR_ReciprocalResolution.x * 4 * scale, IN.UVCoord.y)).rgb * 1;
		}
		else {
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y - TESR_ReciprocalResolution.y * 1 * scale)).rgb * 56;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y + TESR_ReciprocalResolution.y * 1 * scale)).rgb * 56;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y - TESR_ReciprocalResolution.y * 2 * scale)).rgb * 28;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y + TESR_ReciprocalResolution.y * 2 * scale)).rgb * 28;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y - TESR_ReciprocalResolution.y * 3 * scale)).rgb * 8;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y + TESR_ReciprocalResolution.y * 3 * scale)).rgb * 8;
		 
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y - TESR_ReciprocalResolution.y * 4 * scale)).rgb * 1;
			color += tex2D(TESR_RenderedBuffer, float2(IN.UVCoord.x, IN.UVCoord.y + TESR_ReciprocalResolution.y * 4 * scale)).rgb * 1;
		}
			
		color = color / 256;
	}
	else
		color = tex2D(TESR_SourceBuffer, IN.UVCoord).rgb;
		
	return float4(color, 1.0f);
}

technique
{ 
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 DoF();
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 SmartBlur();
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(0);
	}
	
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BlurPS(1);
	}
}