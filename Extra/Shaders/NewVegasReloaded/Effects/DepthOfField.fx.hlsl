// Depth of Field fullscreen shader for Oblivion/Skyrim Reloaded

float4 TESR_ReciprocalResolution;
float4 TESR_DepthOfFieldBlur; //x: distant blur, y:distant blur start, z: distant blur end, w: base blur radius
float4 TESR_DepthOfFieldData; //x: blur fallout y:radius z:diameterRange w:nearblur cutoff
float4 TESR_MotionBlurData;
float4 TESR_DebugVar;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state {ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_DepthBuffer : register(s1) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_SourceBuffer : register(s2) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

#include "Includes/Helpers.hlsl"
#include "Includes/Depth.hlsl"

// static const float k = 0.00001;
// static const float eps = 0.000001;
// static const float FocusPoint = 100.0 * TESR_DebugVar.x;
// static const float FocusPower = 100.0 * TESR_DebugVar.y;
// static const float Accomodation = 10.0;

static const bool DistantBlur = bool(TESR_DepthOfFieldBlur.x);
static const float DistantStart = TESR_DepthOfFieldBlur.y;
static const float DistantEnd = TESR_DepthOfFieldBlur.z;
static const float BaseBlurRadius = TESR_DepthOfFieldBlur.w;

static const float FocusDistance = TESR_DepthOfFieldData.x; //1.5
static const float BlurRadius = TESR_DepthOfFieldData.y;
static const float BokehTreshold = TESR_DepthOfFieldData.z;
static const float NearBlurCutoff = TESR_DepthOfFieldData.w;

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


float getFocalDistance() {
	// gets the autofocus depth based on a local average, scaled with player movement speed (to avoid flicker during fast movement)
	float2 speed = saturate(abs(float2(TESR_MotionBlurData.x, TESR_MotionBlurData.y))) + 0.1;

	float2 center = float2(0.5, 0.5);
	float depth = readDepth(center);
	float centerDepth = depth;
	float2 samplingRange = speed;
	for (int i=0; i<12; i++){
		depth += readDepth(center + 0.3 * taps[i] * samplingRange);
	}
	depth /= 12;
	return centerDepth > depth ? centerDepth:depth; //if pixel at the center is farther than the average, we use that value (fix for some iron sights)
}

// returns a vector of 4 booleans for each quadrants to signify which quadrant the uv belong to
float4 getQuadrants(float2 uv){
	float topLeftQuadrant = (uv.x < 0.5 && uv.y < 0.5); // near field blurred
	float topRightQuadrant = (uv.x > 0.5 && uv.y < 0.5); // far field blurred
	float bottomLeftQuadrant = (uv.x < 0.5 && uv.y > 0.5); // bottom quadrants will be low res copies of the blur amount passes
	float bottomRightQuadrant = (uv.x > 0.5 && uv.y > 0.5); // bottom quadrants will be low res copies of the blur amount passes

	float4 quadrants = float4(topLeftQuadrant, topRightQuadrant, bottomLeftQuadrant, bottomRightQuadrant);
	return quadrants;
}

// remaps the coordinate to [0, 1] relative to the quadrant it belongs to
float2 remapFromQuadrant(float2 uv, float4 quadrants){
	float2 offset = 0.5;
	float2 newX = float2(uv.x, uv.x - offset.x);
	float2 newY = float2(uv.y, uv.y - offset.y);

	uv.x = dot(newX.xyxy, quadrants);
	uv.y = dot(newY.xxyy, quadrants);

	uv *= 2;
	return uv;
}


float4 DoF(VSOUT IN) : COLOR0
{
	float depth = readDepth(IN.UVCoord);

	float HyperFocalDistance = 1000 * FocusDistance; // the distance at which DOF is greatest (infinite towards the distance and closest to the camera)
	float focalLength = 0.01; // mostly negligible and used here to avoid dividing by 0; In real life this value influences the HFD
	float focalDistance = min(HyperFocalDistance, getFocalDistance()); // focal distance is maxed at the hyper focal distance as with perfect autofocus

	// calculating near and far plane based on hyperfocal distance (http://www.waloszek.de/gen_dof_e.php) (DOF is infinite at that distance)
	float nearPlane =  focalDistance * (HyperFocalDistance - focalLength)/(HyperFocalDistance  + focalDistance - 2 * focalLength);
	float farPlane = focalDistance * (HyperFocalDistance - focalLength)/(HyperFocalDistance - focalDistance);

	// float nearblur = invlerps(focalDistance, nearPlane, depth);
	float nearblur = invlerps(nearPlane, 0, depth);
	float farBlur = invlerps(farPlane, farPlane * 2, depth) * 0.8;

	nearblur *= invlerps(0, NearBlurCutoff, depth); // attenuate near blur to reveal gun
	farBlur = saturate(farBlur + invlerps(DistantStart, DistantEnd, depth) * DistantBlur); // add in distance constant blur

	return float4(nearblur, farBlur, 1, 1);
}

// places the different things to blur separately into separate quadrants of the screen
float4 halfRes(VSOUT IN) : COLOR0
{
	float2 uv = IN.UVCoord;

	// remap uv to [0, 1] for each quadrant
	float4 quadrants = getQuadrants(uv);
	uv = remapFromQuadrant(uv, quadrants);

	float4 blur = tex2D(TESR_RenderedBuffer, uv);	
	float4 color = tex2D(TESR_SourceBuffer, uv);
	color = lerp(color, float4(blur.rg, 1, 1), (quadrants.z || quadrants.w)); // only show the blur for both bottom quadrants

	return color;
}

float4 BokehBlur(VSOUT IN, uniform float useBokeh) : COLOR0
{
	float2 uv = IN.UVCoord;
	float4 quadrants = getQuadrants(uv);

	if (quadrants.w) 
		return tex2D(TESR_RenderedBuffer, uv); // perform no blur in this quadrant

	// remap uv to [0, 1] for each quadrant
	uv = remapFromQuadrant(uv, quadrants);

	float nearBlurAmount = tex2D(TESR_RenderedBuffer, uv * 0.5 + float2(0.0, 0.5)).r;
	float farBlurAmount = tex2D(TESR_RenderedBuffer, uv * 0.5 + float2(0.5, 0.5)).g;

	// float blur = dot(float3(nearBlurAmount, farBlurAmount, 1), blurSelection.xyz);
	float centerBlur = dot(float3(1, farBlurAmount, 1), quadrants.xyz);

	// disc based blur
	float4 color = tex2D(TESR_RenderedBuffer, IN.UVCoord);
	float4 bokehColor = color; // will accumulate as bokeh-like dilation
	float amount = 1;
	float radius = lerp(BlurRadius, BaseBlurRadius, useBokeh); // select the bokeh radius or post blur radius
    for (int i = 1; i < 12; i++)
    {
		float2 offset = TESR_ReciprocalResolution.xy * taps[i] * radius * centerBlur; //scale taps based on coc of pixel
        float2 samplePos = IN.UVCoord + offset;

		// sample blur in the relative space of the bottom quadrant
        float2 blurSamplePos = uv + offset * 2;
		// nearBlurAmount = tex2D(TESR_RenderedBuffer, blurSamplePos * 0.5 + float2(0.0, 0.5)).r;
		farBlurAmount = tex2D(TESR_RenderedBuffer, blurSamplePos * 0.5 + float2(0.5, 0.5)).g;
		float blur = dot(float3(1, farBlurAmount, 1), quadrants.xyz); //chose a blur mask or not based on quadrant

		// check that the sampling position is in the same quadrant to prevent edge bleeding
		float4 sampleQuadrants = getQuadrants(samplePos);
		float isValid = dot(quadrants, sampleQuadrants) * blur; // check if sample is in the right quadrant

        float4 sampleColor = isValid?tex2D(TESR_RenderedBuffer, samplePos):float4(0, 0, 0, 0);
		sampleColor *= isValid;
		color += sampleColor; // only accumulate valid pixels (within blur mask and quadrant)

		bokehColor = (luma(sampleColor.rgb)>luma(bokehColor.rgb))? sampleColor: bokehColor; // bokeh dilation blur
		amount += isValid;
     }

	color /= amount;
	return lerp(color, bokehColor, (luma(bokehColor.rgb) > BokehTreshold) * useBokeh); // select a bokeh effect or normal blur based on luma
}

float4 Combine(VSOUT IN) : COLOR0
{
	float2 uv = IN.UVCoord;

	// sample from 4 quadrants, and clamp by half a pixel to avoid leaking bottom quadrants into the top ones
	float2 halfPixel =  TESR_ReciprocalResolution.xy * 1.5;
	float2 nearImageUV = clamp(uv * 0.5, float2(0, 0), float2(0.5, 0.5 - halfPixel.y));
	float2 nearBlurUV = clamp(uv * 0.5 + float2(0, 0.5), float2(0, 0.5 + halfPixel.y), float2(0.5 + halfPixel.x, 1));
	float2 farImageUV = clamp(uv * 0.5 + float2(0.5, 0), float2(0.5 + halfPixel.x, 0), float2(1, 0.5 - halfPixel.y));
	float2 farBlurUV = clamp( uv * 0.5 + float2(0.5, 0.5), float2(0.5 +halfPixel.x, 0.5 + halfPixel.y), float2(1, 1));

	float4 nearBlurImage = tex2D(TESR_RenderedBuffer, nearImageUV);
	float4 farBlurImage = tex2D(TESR_RenderedBuffer, farImageUV);
	float nearBlurAmount = tex2D(TESR_RenderedBuffer, nearBlurUV).r; // near field is blurred
	float farBlurAmount = tex2D(TESR_RenderedBuffer, farBlurUV).g;

	// blend the different layers based on blur amounts
	float4 baseColor = tex2D(TESR_SourceBuffer, uv);	
	float4 color = lerp(baseColor, farBlurImage, farBlurAmount);
	color = lerp(color, nearBlurImage, nearBlurAmount);

	return color;
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
		PixelShader = compile ps_3_0 halfRes();
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BokehBlur(float(1.0f));
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BokehBlur(float(1.0f));
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 BokehBlur(float(0.0f));
	}

	pass
	{
		VertexShader = compile vs_3_0 FrameVS();
		PixelShader = compile ps_3_0 Combine();
	}
}