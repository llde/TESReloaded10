#define cKernelSize 12

static const float BlurWeights[cKernelSize] = 
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
 
static const float2 BlurOffsets[cKernelSize] = 
{
	float2(-6.0f * TESR_ReciprocalResolution.x, -6.0f * TESR_ReciprocalResolution.y),
	float2(-5.0f * TESR_ReciprocalResolution.x, -5.0f * TESR_ReciprocalResolution.y),
	float2(-4.0f * TESR_ReciprocalResolution.x, -4.0f * TESR_ReciprocalResolution.y),
	float2(-3.0f * TESR_ReciprocalResolution.x, -3.0f * TESR_ReciprocalResolution.y),
	float2(-2.0f * TESR_ReciprocalResolution.x, -2.0f * TESR_ReciprocalResolution.y),
	float2(-1.0f * TESR_ReciprocalResolution.x, -1.0f * TESR_ReciprocalResolution.y),
	float2( 1.0f * TESR_ReciprocalResolution.x,  1.0f * TESR_ReciprocalResolution.y),
	float2( 2.0f * TESR_ReciprocalResolution.x,  2.0f * TESR_ReciprocalResolution.y),
	float2( 3.0f * TESR_ReciprocalResolution.x,  3.0f * TESR_ReciprocalResolution.y),
	float2( 4.0f * TESR_ReciprocalResolution.x,  4.0f * TESR_ReciprocalResolution.y),
	float2( 5.0f * TESR_ReciprocalResolution.x,  5.0f * TESR_ReciprocalResolution.y),
	float2( 6.0f * TESR_ReciprocalResolution.x,  6.0f * TESR_ReciprocalResolution.y)
};


// simple local average without weights
float4 BoxBlur (VSOUT IN) :COLOR0
{
	float3 io = float3(-1, 0, 1);

	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.xx * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.xy * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.xz * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.yx * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.yz * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.zx * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.zy * TESR_ReciprocalResolution.xy);
	color += tex2D(TESR_RenderedBuffer, IN.UVCoord + io.zz * TESR_ReciprocalResolution.xy);

	return color /= 9;
}


// perform depth aware 12 taps blur along the direction of the offsetmask
float4 BlurRChannel(VSOUT IN, uniform float2 OffsetMask, uniform float blurRadius,uniform float depthDrop,uniform float endFade) : COLOR0
{
	float WeightSum = 0.114725602f;
	float4 color1 = tex2D(TESR_RenderedBuffer, IN.UVCoord) * WeightSum;

	float depth1 = readDepth(IN.UVCoord);
	clip(endFade - depth1);

	[unroll]
    for (int i = 0; i < cKernelSize; i++)
    {
		float2 uv = IN.UVCoord + (BlurOffsets[i] * OffsetMask) * blurRadius;
		float4 color2 = tex2D(TESR_RenderedBuffer,  uv);
		float depth2 = readDepth(uv);
		float diff = abs(float(depth1 - depth2));

		int useForBlur = (diff <= depthDrop);
		color1 += BlurWeights[i] * color2 * useForBlur;
		WeightSum += BlurWeights[i] * useForBlur;
    }
	color1 /= WeightSum;
    return color1;
}