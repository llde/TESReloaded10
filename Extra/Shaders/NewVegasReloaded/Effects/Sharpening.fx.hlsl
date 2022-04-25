//Sharpening fullscreen shader for Oblivion/Skyrim Reloaded

#define viewsharpening 0
#define pattern 6

float4 TESR_ReciprocalResolution;
float4 TESR_SharpeningData;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

static const float3 CoefLuma = {0.2126, 0.7152, 0.0722};

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
	return (OUT);
}

float4 LumaSharpenPass(VSOUT IN) : COLOR0 {

	float3 ori = tex2D(TESR_RenderedBuffer, IN.UVCoord).rgb;
	float3 sharp_strength_luma = (CoefLuma * TESR_SharpeningData.x);
	#if pattern == 1	//A (fast) 7 tap gaussian using only 2+1 texture fetches.
		float3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + (float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) / 3.0) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + (float2(-TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y) / 3.0) * TESR_SharpeningData.z).rgb;
		blur_ori /= 2;
		sharp_strength_luma *= 1.5;
	#endif
	#if pattern == 2	//A 9 tap gaussian using 4+1 texture fetches.
		float3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y) * 0.5 * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y) * 0.5 * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * 0.5 * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * 0.5 * TESR_SharpeningData.z).rgb;
		blur_ori *= 0.25;
	#endif
	#if pattern == 3	//An experimental 17 tap gaussian using 4+1 texture fetches.
		float3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0.4 * TESR_ReciprocalResolution.x, -1.2 * TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-1.2 * TESR_ReciprocalResolution.x, -0.4 * TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(1.2 * TESR_ReciprocalResolution.x, 0.4 * TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-0.4 * TESR_ReciprocalResolution.x, 1.2 * TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori *= 0.25;
		sharp_strength_luma *= 0.51;
	#endif
	#if pattern == 4	//A 9 tap high pass (TESR_ReciprocalResolution.yramid filter) using 4+1 texture fetches.
		float3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0.5 * TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y * TESR_SharpeningData.z)).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_SharpeningData.z * -TESR_ReciprocalResolution.x, 0.5 * -TESR_ReciprocalResolution.y)).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_SharpeningData.z * TESR_ReciprocalResolution.x, 0.5 * TESR_ReciprocalResolution.y)).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0.5 * -TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y * TESR_SharpeningData.z)).rgb;
		blur_ori /= 4.0;
		sharp_strength_luma *= 0.666;
	#endif
	#if pattern == 5	//A (slower) 9 tap gaussian using 9 texture fetches.
		half3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y)  * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		half3 blur_ori2 = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori2 += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori2 += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, 0) * TESR_SharpeningData.z).rgb;
		blur_ori2 += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, 0) * TESR_SharpeningData.z).rgb;
		blur_ori2 *= 2.0;
		blur_ori += blur_ori2;
		blur_ori += (ori * 4);
		blur_ori /= 16.0;
	#endif
	#if pattern == 6	//A (slower) 9 tap high pass using 9 texture fetches.
		float3 blur_ori = tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, -TESR_ReciprocalResolution.y)  * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += ori.rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0, TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(0, -TESR_ReciprocalResolution.y) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(-TESR_ReciprocalResolution.x, 0) * TESR_SharpeningData.z).rgb;
		blur_ori += tex2D(TESR_RenderedBuffer, IN.UVCoord + float2(TESR_ReciprocalResolution.x, 0) * TESR_SharpeningData.z).rgb;
		blur_ori /= 9;
	#endif
	
	float3 sharp = ori - blur_ori;
	float4 sharp_strength_luma_clamp = float4(sharp_strength_luma * (0.5 / TESR_SharpeningData.y), 0.5);
	float sharp_luma = saturate(dot(float4(sharp, 1.0), sharp_strength_luma_clamp));
	sharp_luma = (TESR_SharpeningData.y * 2.0) * sharp_luma - TESR_SharpeningData.y;
	ori.rgb = ori.rgb + sharp_luma;
	
	#if viewsharpening
		return float4(saturate(0.5 + (sharp_luma * 4)).rrr, 1);
	#endif
	
	return float4(saturate(ori.rgb), 1);
}
	
technique
{
	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader  = compile ps_3_0 LumaSharpenPass();
	}
}
