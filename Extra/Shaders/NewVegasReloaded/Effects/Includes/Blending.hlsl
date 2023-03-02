float4 alphaBlend(float4 base, float4 blend)
{
	return base*base.a +(1-base.a)*blend;
}

float Luma(float4 input)
{
	float greyscale = input.r * 0.3f + input.g * 0.59f +input.b * 0.11f;
	return greyscale;
}

float4 Desaturate(float4 input)
{
	float greyscale = Luma(input);
	return float4(greyscale, greyscale, greyscale, input.a);
}


// photoshop overlay blend mode code from https://www.ryanjuckett.com/photoshop-blend-modes-in-hlsl/
float BlendMode_Overlay(float base, float blend)
{
	return (base <= 0.5f) ? 2.0f*base*blend : 1.0f - 2.0f*(1.0f-base)*(1.0f-blend);
}

float4 BlendMode_Overlay(float4 base, float4 blend)
{
	float4 result = float4(0,0,0,0);
	result.r = BlendMode_Overlay(base.r, blend.r);
	result.g = BlendMode_Overlay(base.g, blend.g);
	result.b = BlendMode_Overlay(base.b, blend.b);
	result.a = blend.a;

	return alphaBlend(result, base);
}


float4 BlendMode_SoftLight(float4 base, float4 blend)
{
	float4 lowValues = 2.0f * base * blend * (1.0f + base * (1.0f - blend));
	float4 a_sqrt = sqrt(base);
	float4 highValues = (base + blend * (a_sqrt - base)) * 2.0f - a_sqrt;
	float4 result = (blend < 0.5f) ? lowValues : highValues;
	result.a = blend.a;

	return alphaBlend(result, base);
}