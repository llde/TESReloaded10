float4 TESR_ReciprocalResolution  : register(c0);
float4 TESR_BlurDirection  : register(c1);
sampler2D SourceBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

struct VSOUT
{
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};


// adapted from https://github.com/Jam3/glsl-fast-gaussian-blur
float4 blur9(sampler2D image, float2 uv, float2 direction) {
  float4 color = float4(0.0, 0.0, 0.0, 1.0);

  float weights[5] = {
    0.2270270270,
    0.3162162162,
    0.3162162162,
    0.0702702703,
    0.0702702703,
  };

  // precalculate sampling offsets to use linear filtering
  float off1 = 1.3846153846;
  float off2 = 3.2307692308;
  float2 offsets[5];
  offsets[0] = float2(0.0f, 0.0f);
  offsets[1] = float2(off1, off1) * direction * TESR_ReciprocalResolution.xy;
  offsets[2] = float2(-off1, -off1) * direction * TESR_ReciprocalResolution.xy;
  offsets[3] = float2(off2, off2) * direction * TESR_ReciprocalResolution.xy;
  offsets[4] = float2(-off2, -off2) * direction * TESR_ReciprocalResolution.xy;

  for (int i=0; i<5; i++){
    color += tex2D(image, uv + offsets[i]) * weights[i];
  }

  return color;
}

float4 main(VSOUT IN) : COLOR0
{
	return blur9(SourceBuffer, IN.UVCoord, TESR_BlurDirection.xy);
}
