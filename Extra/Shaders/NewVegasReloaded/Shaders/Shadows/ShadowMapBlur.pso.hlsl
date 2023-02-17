float4 TESR_ReciprocalResolution  : register(c0);
float4 TESR_BlurDirection  : register(c1);
sampler2D SourceBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

struct VSOUT
{
	float4 vertPos : POSITION;
	float2 UVCoord : TEXCOORD0;
};

#define cKernelSize 12

float4 Blur(uniform float2 OffsetMask, uniform float2 uv)
{

  float blurRadius = 0.5;
  float BlurWeights[cKernelSize] = 
  {
    0.057424882f,
    0.058107773f,
    0.061460144f,
    0.071020611f,
    0.088092873f,
    0.106530916f,
    0.106530916f,
    0.088092873f,
    0.071020611f,
    0.061460144f,
    0.058107773f,
    0.057424882f
  };
  
  float2 BlurOffsets[cKernelSize] = 
  {
    float2(-6.0f * TESR_ReciprocalResolution.x, -6.0f * TESR_ReciprocalResolution.x),
    float2(-5.0f * TESR_ReciprocalResolution.x, -5.0f * TESR_ReciprocalResolution.x),
    float2(-4.0f * TESR_ReciprocalResolution.x, -4.0f * TESR_ReciprocalResolution.x),
    float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.x),
    float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.x),
    float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.x),
    float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.x),
    float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.x),
    float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.x),
    float2( 4.0f * TESR_ReciprocalResolution.x,  4.0f * TESR_ReciprocalResolution.x),
    float2( 5.0f * TESR_ReciprocalResolution.x,  5.0f * TESR_ReciprocalResolution.x),
    float2( 6.0f * TESR_ReciprocalResolution.x,  6.0f * TESR_ReciprocalResolution.x)
  };

	float WeightSum = 0.114725602f;
	float4 color = tex2D(SourceBuffer, uv) * WeightSum;

  for (int i = 0; i < cKernelSize; i++)
  {
		float2 uvOff = (BlurOffsets[i] * OffsetMask) * blurRadius;
		color += tex2D(SourceBuffer, uv + uvOff) * BlurWeights[i];
		WeightSum += BlurWeights[i];
  }

	color /= WeightSum;
  return color;
}

float4 main(VSOUT IN) : COLOR0
{
	return Blur(TESR_BlurDirection.xy, IN.UVCoord);
}
