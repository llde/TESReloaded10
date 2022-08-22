#define GAMMA2LINEAR(X) pow(abs(X), 2.2)
#define LINEAR2GAMMA(X) pow(abs(X), 1.0 / 2.2)





float2 scale_uv(float2 uv, float2 scale, float2 center) {
	return (uv - center) * scale + center;
}

float4 _tex2D(sampler2D sp, float2 uv) {
	return tex2Dlod(sp, float4(uv, 0.0, 0.0));
}

float3 screen(float3 a, float3 b, float w) {
	return lerp(a, 1.0 - (1.0 - a) * (1.0 - b), w);
}

float get_average(float3 col) {
	return dot(col, 0.333);
}

float get_luminosity(float3 col) {
	return max(col.r, max(col.g, col.b));
}

float get_luma(float3 col) {
	return max(dot(col, float3(0.299, 0.587, 0.114)), 0.001);
}

float get_luma_linear(float3 col) {
	return dot(col, float3(0.2126, 0.7152, 0.0722));
}

float3 GammaDecode(float3 color, float x) {
    const float barrier = 0.081, soffs = 0.099;
    const float invbfac = x, invsfac = 1.0 / (10 * invbfac);

    float3 fac =      color          *                 invsfac;
    float3 col = pow((color + soffs) / (1.0 + soffs),  invbfac);

    /* easier with a lerp than other way with cmp */
    return lerp(col, fac, color > barrier ? 0 : 1);
}

float3 GammaEncode(float3 color, float x) {
    const float barrier = 0.018, soffs = 0.099;
    const float bfac = 1.0 / x, sfac = 10 * bfac;

    float3 fac =                     color * sfac;
    float3 col = pow((1.0 + soffs) * color,  bfac) - soffs;

    /* easier with a lerp than other way with cmp */
    return lerp(col, fac, color > barrier ? 0 : 1);
}

float rand(float x)
{
    return frac(x * 0.024390243);
}
float permute(float x)
{
    return ((34.0 * x + 1.0) * x) % 289.0;
}

float3 LinToLog( float3 LinearColor )
{
    float3 LogColor = ( 300 * log10( LinearColor * (1 - .0108) + .0108 ) + 685 ) / 1023;    // Cineon
    LogColor = saturate( LogColor );

    return LogColor;
}

float3 t_uncharted2(float3 col, float exposure) {
	static const float A = 0.15;
	static const float B = 0.50;
	static const float C = 0.10;
	static const float D = 0.20;
	static const float E = 0.02;
	static const float F = 0.30;
	static const float W = 11.2;
	
	
	col = ((col * (A * col + C * B) + D * E) / (col * (A * col + B) + D * F)) - E / F;
	
	float white = ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F;
	col /= white  / exposure;

	return col;
}


//--------------------------------------------------------------------------------------
// Timothy Lottes tone mapper
//--------------------------------------------------------------------------------------
// General tonemapping operator, build 'b' term.
float ColToneB(float hdrMax, float contrast, float shoulder, float midIn, float midOut) 
{
    return
        -((-pow(midIn, contrast) + (midOut*(pow(hdrMax, contrast*shoulder)*pow(midIn, contrast) -
            pow(hdrMax, contrast)*pow(midIn, contrast*shoulder)*midOut)) /
            (pow(hdrMax, contrast*shoulder)*midOut - pow(midIn, contrast*shoulder)*midOut)) /
            (pow(midIn, contrast*shoulder)*midOut));
}

// General tonemapping operator, build 'c' term.
float ColToneC(float hdrMax, float contrast, float shoulder, float midIn, float midOut) 
{
    return (pow(hdrMax, contrast*shoulder)*pow(midIn, contrast) - pow(hdrMax, contrast)*pow(midIn, contrast*shoulder)*midOut) /
           (pow(hdrMax, contrast*shoulder)*midOut - pow(midIn, contrast*shoulder)*midOut);
}

// General tonemapping operator, p := {contrast,shoulder,b,c}.
float ColTone(float x, float4 p) 
{ 
    float z = pow(x, p.r); 
    return z / (pow(z, p.g)*p.b + p.a); 
}

float3 Lottes(float3 color, float white, float midOut, float contrast, float shoulder)
{
    static float hdrMax = 4.0; // How much HDR range before clipping. HDR modes likely need this pushed up to say 25.0.
    //static float contrast = 1.4; // Use as a baseline to tune the amount of contrast the tonemapper has.
    //static float shoulder = 0.995; // Likely don’t need to mess with this factor, unless matching existing tonemapper is not working well..
    static float midIn = 0.18; // most games will have a {0.0 to 1.0} range for LDR so midIn should be 0.18.
    //static float midOut = 0.18; // Use for LDR. For HDR10 10:10:10:2 use maybe 0.18/25.0 to start. For scRGB, I forget what a good starting point is, need to re-calculate.

    float b = ColToneB(hdrMax, contrast, shoulder, midIn, midOut);
    float c = ColToneC(hdrMax, contrast, shoulder, midIn, midOut);

    float peak = max(color.r, max(color.g, color.b));
    float3 ratio = color / peak;
    peak = ColTone(peak, float4(contrast, shoulder, b, c) );
    // then process ratio

    // probably want send these pre-computed (so send over saturation/crossSaturation as a constant)
    float crosstalk = 4.0; // controls amount of channel crosstalk
    float saturation = contrast; // full tonal range saturation control
    float crossSaturation = contrast*16.0; // crosstalk saturation

    //float white = 1.0;

    // wrap crosstalk in transform
    ratio = pow(abs(ratio), saturation / crossSaturation);
    ratio = lerp(ratio, white, pow(peak, crosstalk));
    ratio = pow(abs(ratio), crossSaturation);

    // then apply ratio to peak
    color = peak * ratio;
    return color;
}