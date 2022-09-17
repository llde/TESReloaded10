float4 TESR_ReciprocalResolution  : register(c0);
sampler2D SourceBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

struct VSOUT
{
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

// adapted from https://github.com/Jam3/glsl-fast-gaussian-blur
float4 blur9(sampler2D image, float2 uv, float2 resolution, float2 direction) {
  float4 color = float4(0.0, 0.0, 0.0, 1.0);
  float2 off1 = float2(1.3846153846, 1.3846153846) * direction * resolution*2;
  float2 off2 = float2(3.2307692308, 3.2307692308) * direction * resolution*2;
  color += tex2D(image, uv) * 0.2270270270;
  color += tex2D(image, uv + (off1)) * 0.3162162162;
  color += tex2D(image, uv - (off1)) * 0.3162162162;
  color += tex2D(image, uv + (off2)) * 0.0702702703;
  color += tex2D(image, uv - (off2)) * 0.0702702703;
  return color;
}

float4 main(VSOUT IN) : COLOR0
{
	return blur9(SourceBuffer, IN.UVCoord, TESR_ReciprocalResolution.xx, float2(1.0, 1.0));
}
