//-----------------------------------------------------------------------------
// parallax.fx
//
//-----------------------------------------------------------------------------

////-----------------------------------------------------------------------------
//// Parameters
////-----------------------------------------------------------------------------
//float4x4 mWVP			: ModelViewProj;
//float4x4 mW			: World;
//float4x4 mVI			: ViewInverse;

static const bool in_DebugMode1 = true;
static const bool in_DebugMode2 = true;

/*bool in_JitterEnabled <
	string UIName = "Use Jitter";
	string UIWidget = "checkbox";
	//int MapChannel = 2;
> = false;

texture jitterTex
<
	string UIName = "Jitter Texture";
	string ResourceType = "2D";
>; //*/

/* Cloud Color */
static const float3 in_cloudBlend0 = {1.0f, 1.0f, 1.0f};
/* Cloud Alpha Multiplier */
static const float in_cloudBlend0_Alpha = 1.0;
/* Cloud Subdivision */
static const int in_cloudSubdivision = 16;
/* Cloud Mid-Plane */
static const float in_cloudMidplane = 0.3;
/* Cloud Volume Depth */
static const float in_cloudVolumeDepth = 0.3;
/* Number of Samples */
static const int in_NumSamples = 16;

/* Light properties */
//static const float3 cust_SunIntensity = float3(1.0, 0.960784, 0.949019);

/* Ambient Light */
static const float3 in_ambientLight = {0.1f, 0.1f, 0.1f};
/* Light Vector Multiplier */
static const float in_lightVectorMultiplier = 0.3;
/* Number of Lighting Samples */
static const int in_NumLightSamples = 8;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
/*sampler2D JitterSampler = sampler_state
{
	Texture = <jitterTex>;
	MinFilter = None;
	MagFilter = Linear;
	MipFilter = None;
	AddressU = Wrap;
    AddressV = Wrap;
}; //*/
//-----------------------------------------------------------------------------


////-----------------------------------------------------------------------------
//struct VS_INPUT
//{
//   	float4 position	: POSITION;
//   	float2 texcoord	: TEXCOORD0;
//   	float3 normal	: NORMAL;
//   	float3 tangent	: TANGENT;
//   	float3 binormal	: BINORMAL;
//};
////-----------------------------------------------------------------------------
//struct VS_OUTPUT
//{
//	float4 position	: POSITION;
//	float4 color    : COLOR0;
//	float2 texcoord	: TEXCOORD0;
//	float3 eye	: TEXCOORD1;
//	float3 normal   : TEXCOORD2;
//	float3 light	: TEXCOORD3;
//};
////-----------------------------------------------------------------------------
//struct PS_OUTPUT
//{
//	float4 color	: COLOR;
//};
////-----------------------------------------------------------------------------


////-----------------------------------------------------------------------------
//// Vertex Shader
////-----------------------------------------------------------------------------
//VS_OUTPUT VS( VS_INPUT IN )
//{
//    VS_OUTPUT OUT;
//
//	float4 VertexPositionWS = mul(IN.position, mW);
//
//	float3 P = VertexPositionWS.xyz;
//	float3 E = mVI[3].xyz - P;
//	float3 L = TESR_SunDirection - P;
//
//	// The per-VS_INPUT tangent, binormal, normal form the tangent to object space
//	// rotation matrix.  Multiply by the world matrix to form tangent to world space
//	// rotation matrix.  Then transpose the matrix to form the inverse tangent to
//	// world space, otherwise called the world to tangent space rotation matrix.
//	float3x3 tangentToWorldSpace = {IN.binormal,IN.tangent,IN.normal};
//
//	//float3x3 tangentToWorldSpace = {IN.tangent,IN.binormal,IN.normal};
//	tangentToWorldSpace = mul(tangentToWorldSpace,mW);
//
//	float3x3 worldToTangentSpace = transpose(tangentToWorldSpace);
//
//	OUT.color_0 = float4(in_cloudBlend0.rgb, in_cloudBlend0_Alpha);
//
//	OUT.position = mul( IN.position, mWVP );		// standard transformation to clip space
//	OUT.texcoord = IN.TexUV;								// pass through the original texcoords
//
//	OUT.eye    = mul( E,         worldToTangentSpace );	// pass through the TANGENT space eye vector (un-normalized)
//	OUT.normal = mul( IN.normal, worldToTangentSpace );	// pass through the TANGENT space normal vector (un-normalized)
//	OUT.light  = mul( L,         worldToTangentSpace );
//
//	return OUT;
//}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

// Calculates the gamma-corrected luminance of the PS_OUTPUT.
// Luminance is used to give character to clouds, even when just
// lit by ambient light, by darkening the output PS_OUTPUT.  It
// adjusts the outputted luminance by the alpha channel, which
// is used to determine cloud density.
float CalcLuminance(float4 sample) {
	float sampLum = (0.2126 * sample.r) + (0.7152 * sample.g) + (0.0722 * sample.b);

	// Due to the way this information is used (to darken pixels),
	// I'm actually going to INCREASE the outputted luminance,
	// as alpha is reduced.  Thinner clouds darken the output
	// LESS than denser clouds.  Makes sense, right?
	return 1.0 - ((1.0 - sampLum) * sample.a);
}

// Calculates and returns:
// X = The bottom position of the cloud.
// Y = The top position of the cloud.
// Z = The luminance in the cloud texture.
// W = The distributed vertical density of the cloud.
float4 CalcVolume(float4 sample, float Subdivisor) {
	// The vertical density of the cloud comes from the alpha channel.
	float4 retVal;

	// The luminance will be used to vary the cloud in ambient light.
	retVal.z = CalcLuminance(sample);

	// The thickness value of the cloud is derived from it's
	// red and green channels, averaged.  I don't use the blue because
	// alot of the transparent parts of the texture tend to be blue.
	float VThickness = ((sample.r + sample.g) / 2) * sample.a;

	// X1 is the lower boundary, displaced from the surface of the geometry.
	retVal.x = in_cloudMidplane * (1.0 - VThickness);
	// X2 is the top boundary, displaced from the surface of the geometry.
	retVal.y = retVal.x + VThickness;

	// We need to calculate the distributed density.
/*	if (sample.a > 0.005 && VThickness > 0.005)
		retVal.w = sample.a / Subdivisor;	*/

	retVal.w = sample.a / Subdivisor;

	// Return the information.
	return retVal;
}

/*float CalcSubsampling(float lastDDens, float curDDens) {
	return (lastDDens + ((curDDens - lastDDens) / 2)) * in_NumSubsamples;
}*/

float FixAngle(float angle) {
	if (angle > 1.57079633) {
		float temp = angle - 1.57079633;
		angle = 1.57079633 - temp;
	}

	return angle;
}

// Takes a RGB color, and outputs the color with full
// value, as bright as it can be.  Used for illuminating
// the cloud with sunlight.//	// The per-VS_INPUT tangent, binormal, normal form the tangent to object space
//	// rotation matrix.  Multiply by the world matrix to form tangent to world space
//	// rotation matrix.  Then transpose the matrix to form the inverse tangent to
//	// world space, otherwise called the world to tangent space rotation matrix.
//	float3x3 tangentToWorldSpace = {IN.binormal,IN.tangent,IN.normal};
//
//	//float3x3 tangentToWorldSpace = {IN.tangent,IN.binormal,IN.normal};
//	tangentToWorldSpace = mul(tangentToWorldSpace,mW);
//
//	float3x3 worldToTangentSpace = transpose(tangentToWorldSpace);

float3 SaturateColor(float3 inColor) {
	// Find the maximum in the color sample.
	float Max = max(max(inColor.x, inColor.y), inColor.z);
	if (Max <= 0.0)
		// Return white.
		return float3(1.0, 1.0, 1.0);

	return saturate(inColor * (1.0 / Max));
}
//*/

inline void RelativeSaturate(inout float v1, inout float v2) {
	float Max = max(v1, v2);
	if (Max > 1.0) {
		v1 *= (1.0 / Max);
		v2 *= (1.0 / Max);
	}
}

// Takes a RGB color, and reduces the output if one of
// the channels has a value greater than 1.  This helps
// prevent the sunlight from overexposing the image and
// making the cloud pure white in colored light.
float3 DesaturateColor(float3 inColor) {
	// Find the maximum in the color sample.
	float Max = max(max(inColor.x, inColor.y), inColor.z);
	if (Max > 1.0)
		// Return white.
		return saturate(inColor * (1.0 / Max));

	return inColor;
}
//*/

float4 SampleTextures(float2 UV, float2 BlendUV) {
	float4 samp1 = tex2D(TexMap,           UV);
	float4 samp2 = tex2D(TexMapBlend, BlendUV);

	return lerp(samp1, samp2, Params.x);
}

float4 SampleTexturesGrad(float2 UV, float2 BlendUV, float dx, float dy) {
	float4 samp1 = tex2Dgrad(TexMap,           UV, dx, dy);
	float4 samp2 = tex2Dgrad(TexMapBlend, BlendUV, dx, dy);

	return lerp(samp1, samp2, Params.x);
}

/*float lerp3 (float3 values, float interp) {
	interp *= 2;
	if (interp <= 1.0)
		return lerp(values.x, values.y, interp);

	return lerp(values.y, values.z, interp - 1.0);
}*/

// Performs a march across the cloud plane from a point in
// the clouds, towards the light source.
//
// Returns the total accumulated density during the march.
float DoLightingMarch(float2 UV, float2 BlendUV, float dx, float dy, float3 offset, float3 step) {
	// Now we're ready for the light ray march.
	// We will start at the first collision offset, and then
	// march off towards the light, accumilating density.
	// The greater the density, the weaker the light.
	float3 vCurrOffset = offset + step;
	float4 vCurrSample;

	float curDensity = 0.0;
	int nCurrSample = 0;

//	float light_cloudSubdivision = (float)in_cloudSubdivision;
//	float light_cloudSubdivision = (float)in_cloudSubdivision * ((float)in_NumLightSamples / (float)in_NumSamples);
	float light_cloudSubdivision = (float)in_cloudSubdivision * ((float)in_NumLightSamples / (float)in_NumSamples) * ((float)in_NumSamples / (float)in_cloudSubdivision);

	float3 vLastOffset = offset;
	float4 vLastSample = CalcVolume(
		SampleTexturesGrad(UV + offset.xy, BlendUV + offset.xy, dx, dy),
		in_cloudSubdivision
	);

	bool inCloud = false;

	[loop]
	while ((nCurrSample < in_NumLightSamples) &&
	       (vCurrOffset.z >= 0.0 && vCurrOffset.z <= 1.0) &&
	       (curDensity < 1.0)) {
		// Sample the current texcoord offset, then derive cloud information from it.
		vCurrSample = SampleTexturesGrad(UV + vCurrOffset.xy, BlendUV + vCurrOffset.xy, dx, dy);
		vCurrSample = CalcVolume(vCurrSample, light_cloudSubdivision);

		// If inside the cloud volume.
		if (vCurrOffset.z >= vCurrSample.x && vCurrOffset.z <= vCurrSample.y) {
			// Accumilate density.
			// curDensity += vCurrSample.w * (in_cloudVolumeDepth / 0.3);
			curDensity += vCurrSample.w;
			inCloud = true;
		}
		else if (inCloud) {
			// Calculate the linear intersection point.
			// Doing this relatively expensive step will greatly increase
			// the quality of the cloud's self-shadowing.
			float2 H = float2(vLastSample.x, vCurrSample.x);
			bool hitReverse = vCurrOffset.z > vCurrSample.y;
			if (hitReverse) {
				// We exited out through the top of the cloud instead of the bottom.
				H.x = vLastSample.y;
				H.y = vCurrSample.y;
			}

			float Ua = (H.x - vLastOffset.z) / ( step.z - (H.y - H.x));
			float3 temp = vLastOffset + Ua * step;
			H.x = (temp.z - vLastOffset.z) / (vCurrOffset.z - vLastOffset.z);
			curDensity += vLastSample.w * Ua;

			inCloud = false;
		}

		// increment to the next sample
		nCurrSample++;
		vLastOffset = vCurrOffset;
		vLastSample = vCurrSample;
		vCurrOffset += step;
	}

	return 1.0 - saturate(curDensity);
}

/*struct DirectLightSample {
   	float lightAmount;
	float obstructingDensity;
	bool set;
};*/

void VolClouds(in VS_OUTPUT IN, inout PS_OUTPUT OUT) {
	float3 temp;

//	DirectLightSample LS[2];
	float3 L;
	float3 N;

	// TODO:  Flatten the clouds as the get farther from the camera:
	// as the view angle acuteness to the normal increases.  This
	// will reduce artifacting at extremely acute angles.  Should
	// be able to do this by manipulating the following formula's
	// divisor.

	// ********Main Step Setup******** //

//	temp1 == fParallaxLimit
	// calculate the parallax offset vector max length
	temp.x = length(IN.CameraDir.xy) / (IN.CameraDir.z);
	// scale the vector according to height-map scale
	temp.x *= in_cloudVolumeDepth;
	temp.y = 1.0 / (float)in_NumSamples;

	float3 MaxOffset = float3(normalize(-IN.CameraDir.xy) * temp.x, 1.0);
	float3 StepRate_Main = MaxOffset * temp.y;

//	float fDensityMultiplier = (1 / length(StepRate_Main)) / 14;
	float fDensityMultiplier = length(MaxOffset);

	// ******Lighting Step Setup****** //
//	temp1 == angleCorrection
	temp.x = (1 / in_cloudVolumeDepth);

	N = TESR_SunDirection.xyz;
	N.z *= temp.x;
	L = normalize(N);
	N = L * in_lightVectorMultiplier;

	// Setup the new sampling rate.
	float3 StepRate_Light;

	StepRate_Light.xy = ( N.xy) / (float)in_NumLightSamples;
	StepRate_Light.z  = (-N.z ) / (float)in_NumLightSamples;

	//*******************************//

	// temp = angle between the view and light vectors.
	// 15 degrees  = 0.26179938 radians
	// 45 degrees  = 0.78539816 radians
	// 90 degrees  = 1.57079633 radians
	// 135 degrees = 2.35619449 radians
	// 180 degrees = 3.14159265 radians
	N = normalize(IN.CameraDir);
	temp.x = acos( dot( N, L ) );
	float scatterAmount = smoothstep(0.0, 1.57079633, FixAngle(temp.x));
//	scatterAmount = lerp(1.0, 0.65, scatterAmount);
	scatterAmount = lerp(0.1, 0.02, scatterAmount);

	// This multiplier will help reduce the effects of reduced
	// marching resolution at higher angles of attack.
	// float fDensityMultiplier = 1.0 / N.z;
	float fScatterLightMultiplier = temp.y;

	[branch]
	if (in_DebugMode1) {
		int minSam = 8;
		int maxSam = 32;

		temp.x = fDensityMultiplier * minSam;
		temp.y = clamp(temp.x, minSam, maxSam);
		temp.x = (temp.y - minSam) / (maxSam - minSam);

		if (temp.y <= 16)
			OUT.color_0 = float4(0.0, 0.0, temp.x, 1.0);
		else
			OUT.color_0 = float4(0.0, temp.x, 0.0, 1.0);

		return;
	}

	float2 dx, dy;

	dx = ddx(IN.TexUV);	// calculate the texcoord partial derivative in x in screen space for tex2Dgrad
	dy = ddy(IN.TexUV);	// calculate the texcoord partial derivative in y in screen space for tex2Dgrad

	float3 vCurrOffset = StepRate_Main;
	float4 vCurrSample;

	float3 vLastOffset = 0.0;
	float4 vLastSample = CalcVolume(SampleTextures(IN.TexUV, IN.TexBlendUV), in_cloudSubdivision);

	bool inCloud = false;

	float FinalDensity = 0.0;
	float Luminance = 1.0;
	float Sunlight = 0.0;

	int nCurrSample = 0;
	int nCloudSamplesTaken = 0;
	int HitCount = 0;

	// We'll multiply this in the lighting calcs.
	// We do this here so we don't have to calculate it over and over
	// while inside the loop.
//	temp.y = fScatterLightMultiplier * fDensityMultiplier * scatterAmount;
	temp.y = fScatterLightMultiplier * fDensityMultiplier * 2;

	[loop]
	while (nCurrSample < in_NumSamples && FinalDensity < 1.0) {
		// Sample the current texcoord offset, then derive cloud information from it.
		vCurrSample = SampleTexturesGrad(IN.TexUV + vCurrOffset.xy, IN.TexBlendUV + vCurrOffset.xy, dx, dy);
		temp.z = vCurrSample.a;
		vCurrSample = CalcVolume(vCurrSample, in_cloudSubdivision);

		float lightBleed;

		// If inside the cloud volume.
		[branch]
		if (vCurrOffset.z >= vCurrSample.x && vCurrOffset.z <= vCurrSample.y && vCurrSample.w > 0.0) {
			[branch]
			if (!inCloud) {
				//Calculate the linear intersection point.
				float2 H = float2( vLastSample.x, vCurrSample.x );
				bool hitReverse = vLastOffset.z > vLastSample.y;
				if (hitReverse) {
					//We entered through the top of the cloud instead of the bottom.
					H.x = vLastSample.y;
					H.y = vCurrSample.y;
				}

				float Ua = (H.x - vLastOffset.z) / ( StepRate_Main.z - (H.y - H.x));
				// N = LIP
				N = vLastOffset + Ua * StepRate_Main;

				vLastSample = SampleTexturesGrad(IN.TexUV + N.xy, IN.TexBlendUV + N.xy, dx, dy);
				H.x = vLastSample.a;
				vLastSample = CalcVolume(vLastSample, in_cloudSubdivision);

//				Luminance += vLastSample.z * Ua;
				Ua = 1 - Ua;

				temp.x = DoLightingMarch(IN.TexUV, IN.TexBlendUV, dx, dy, N, StepRate_Light);
				temp.x *= Ua * H.x * temp.y;
//				lightBleed = temp.x * scatterAmount;
//				temp.x -= lightBleed;

				/*if (HitCount < 2) {
					if (HitCount == 0) {
						// Perform light calculation.
						LS.x.lightAmount = temp.x;
						LS.x.obstructingDensity = FinalDensity;
						LS.x.set = true;
					}
					else {
						// Perform light calculation.
						LS.y.lightAmount = temp.x;
						LS.y.obstructingDensity = FinalDensity;
						LS.y.set = true;
					}

					HitCount++;
				}*/

				temp.x *= (1 - FinalDensity);
//				Sunlight += temp.x + lightBleed;
				Sunlight += temp.x;

				FinalDensity += vLastSample.w * Ua * fDensityMultiplier;

				inCloud = true;
			}

			// Perform light calculation.
			temp.x = DoLightingMarch(IN.TexUV, IN.TexBlendUV, dx, dy, vCurrOffset, StepRate_Light);
			temp.x *= temp.z * temp.y;
//			lightBleed = temp.x * scatterAmount;
//			temp.x -= lightBleed;
			temp.x *= (1 - FinalDensity);
//			Sunlight += temp.x + lightBleed;
			Sunlight += temp.x;

			FinalDensity += vCurrSample.w * fDensityMultiplier;

			Luminance += vCurrSample.z;
			nCloudSamplesTaken++;
		}
		else if (inCloud) {
			//Calculate the linear intersection point.
			float2 H = float2(vLastSample.y, vCurrSample.y);
			bool hitReverse = vCurrOffset.z < vCurrSample.x;
			if (hitReverse) {
				//We exited out through the top of the cloud instead of the bottom.
				H.x = vLastSample.x;
				H.y = vCurrSample.x;
			}

			float Ua = (H.x - vLastOffset.z) / ( StepRate_Main.z - (H.y - H.x));
			//N = LIP
			N = vLastOffset + Ua * StepRate_Main;

			vLastSample = SampleTexturesGrad(IN.TexUV + N.xy, IN.TexBlendUV + N.xy, dx, dy);
			temp.z = vLastSample.a;
			vLastSample = CalcVolume(vLastSample, in_cloudSubdivision);

//			Luminance += vLastSample.z * Ua;

			// Perform light calculation.
			temp.x = DoLightingMarch(IN.TexUV, IN.TexBlendUV, dx, dy, N, StepRate_Light);
			temp.x *= Ua * temp.z * temp.y;
//			lightBleed = temp.x * scatterAmount;
//			temp.x -= lightBleed;
			temp.x *= (1 - FinalDensity);
//			Sunlight += temp.x + lightBleed;
			Sunlight += temp.x;

			FinalDensity += vLastSample.w * Ua * fDensityMultiplier;

			inCloud = false;
		}

		// increment to the next sample
		nCurrSample++;
		// remember this texcoord offset for next time
		vLastOffset = vCurrOffset;
		// increment to the next texcoord offset
		vCurrOffset += StepRate_Main;
		vLastSample = vCurrSample;
	}

	Luminance /= (float)nCloudSamplesTaken;
	FinalDensity = saturate(FinalDensity);
	Sunlight *= 2.0;

	/*if (LS.y.set) {
		// Two hits...
		temp.y = (1 - LS.y.obstructingDensity);
		temp.x = (LS.y.obstructingDensity * LS.x.lightAmount) + (temp.y * LS.y.lightAmount);
		temp.y += 1.0;

//		Sunlight += temp.x;
//		Sunlight += LS.x.lightAmount;
	}
	else {
//		Sunlight += LS.x.lightAmount;
	}

	if(in_DebugMode1) {
//		Sunlight = (DirectSunlight / DirectDensity);
	}*/

	// Reusing the variable "N".
	N = IN.color_0.rgb;
	L = SaturateColor(IN.color_0.rgb) * cust_SunIntensity * Sunlight;

	// Return the final alpha'd cloud.
//	OUT.color_0.rgb = DesaturateColor((N * in_ambientLight) + L);
	OUT.color_0.rgb = (N * in_ambientLight) + L;
	OUT.color_0.a = saturate(IN.color_0.a * FinalDensity);
}
