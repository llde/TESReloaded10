
/* ############################################################################# */

/* Light properties */
#ifndef	SUN_VARSb
#if	defined(vs) && !defined(vshi)
float4 TESR_SunDirection : register(c7);

#define	SUN_VARSb
#else
float4 TESR_SunDirection : register(c64);

#define	SUN_VARSb
#endif
#endif

#if	defined(SAMPLER_SKY) || defined(SAMPLER_SUN)

float4 TESR_SunTiming : register(c65);
float4 TESR_GameTime : register(c66);
float4 TESR_CameraPosition : register(c67);
//float4 obolv_TexData0 : register(c68);//sm->GlobalConst.pTexture[0].vals.texture.data;

sampler1D TESR_samplerAmbient : register(s6) < string ResourceName = "sky\pcs\AmbSc_1D_ho.dds"; > = sampler_state
{
	AddressU  = MIRROR;
	AddressV  = MIRROR;
	AddressW  = MIRROR;

	MIPFILTER = NONE;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};


sampler2D TESR_samplerSun : register(s2) < string ResourceName = "sky\pcs\Sun_1k.dds"; > = sampler_state
{
	AddressU  = CLAMP;
	AddressV  = CLAMP;
	AddressW  = CLAMP;

	MIPFILTER = NONE;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

sampler2D TESR_samplerOpticalDepth : register(s3) < string ResourceName = "sky\pcs\OptDpta_2D.dds"; > = sampler_state
{
	AddressU  = CLAMP;
	AddressV  = CLAMP;

	MIPFILTER = NONE;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;

	Bordercolor = 0.0f;
	sRGBTexture = false;
};

sampler3D TESR_samplerScatterH : register(s4) < string ResourceName = "sky\pcs\HTD_3D_ho.dds"; > = sampler_state
{
    AddressU  = CLAMP;
    AddressV  = CLAMP;
    AddressW  = CLAMP;

    MIPFILTER = NONE;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;

    sRGBTexture = false;
};

// either 1D or 2D
sampler TESR_samplerScatteringPhase : register(s5)  < string ResourceName = "sky\pcs\ScPh_1D.dds"; > = sampler_state
{
    AddressU  = CLAMP;
    AddressV  = CLAMP;

    MIPFILTER = NONE;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;

    sRGBTexture = false;
};

#endif

/* Light properties */
static const float3 cust_SunIntensity = float3(1.0, 0.960784, 0.949019);

/* */
#define	Oblivion2Reality	5
#define Units2Centimeters	0.1428767293691635
#define Units2Meters		0.01428767293691635
#define	Meters2World(z)		((z) / (Units2Meters      * Oblivion2Reality))
#define	World2Centimeters(z)	((z) * (Units2Centimeters * Oblivion2Reality))
#define	World2Meters(z)		((z) * (Units2Meters      * Oblivion2Reality))
#define	WorldHeightMeters1(z)	float3(0.0, 0.0, fPlanetRadius + World2Meters(max(z, 0)))
#define	WorldHeightMeters2(z,xy)float3(World2Meters(xy.x), World2Meters(xy.y), fPlanetRadius + World2Meters(max(z, 0)))

/* A&P dimensions */
static const float fCoverDimension   =          25000.0;
static const float fAtmosphereRadius =        6432797.0;
static const float fCloudRadius      =                       25000.0 + 6372797.0;
static const float fPlanetRadius     =                                 6372797.0;
static const float fThickness        =       (6432797.0 -              6372797.0);
static const float fThicknessInv     = 1.0 / (6432797.0 -              6372797.0);
static const float fDistanceInv      =        6397797.0 / (6397797.0 - 6372797.0);

float3 mtsSea  = {0.01, 0.2, 0.20};
float3 mtsLand = {0.30, 0.0, 0.15};

//#define	SUN_SIZE	(1024 - (256 * pow(abs(1.0 - (TESR_SunDirection.z)), 0.125)))
#define	SUN_SIZE	(1024 - (256 * (1.0 - abs(TESR_SunDirection.z))))
//#define	SUN_SIZE	(1024)
#define	SUN_BRIGHTNESS	2
#define	HORIZONT_BIAS	0.0

/* NOTES regarding simulating Haze:
 *
 * Variation in visibility is traditionally described using the parameter turbidity.
 * Turbidity is a measure of the clearness of the atmosphere and
 * describes the haziness of a given day. It relates the amount of scattering
 * due to aerosols to the amount of scattering due to molecules, or, the
 * amount of Rayleigh scattering to the amount of Mie scattering. More formally,
 * turbidity is the ratio of the optical thickness of the atmosphere on a
 * given day (molecules and aerosols) to the optical depth of a theoretical unpolluted
 * atmosphere, consisting exclusively of molecules. This relationship
 * is expressed as.
 *
 *     tm + ta
 * T = -------
 *       tm
 *
 * Where T is the turbidity and tm is the vertical optical thickness of a pure
 * molecular atmosphere and tm + ta is the vertical optical thickness of the
 * combined atmosphere of molecules and aerosols [20].
 */

#define	VARYING_EFFICIENTS

#define	SUNRSE_IndRay	2.5000
#define	MIDDAY_IndRay	1.0000
#define	SUNSET_IndRay	1.5000

#define	SUNRSE_IndMie	0.5000
#define	MIDDAY_IndMie	1.0000
#define	SUNSET_IndMie	4.0000

#define	SUNRSE_MieCSB	0.0015
#define	MIDDAY_MieCSB	0.0025
#define	SUNSET_MieCSB	0.0085

/* ############################################################################# */

float nonpreciseangle_cosine(float3 Pos, float3 Vec, float t, float Prod) {
	/* the cosine of very narrow angles is near 1
	 * this fixes the exponent and in effect limits the precision
	 * to a 23 bits fixed point number
	 */
	return dot(normalize(Pos), normalize(Pos + Vec * t));
}

float2 nonpreciseangle_cosine(float3 Pos, float2x3 Vec, float2 t, float Prod) {
	return float2(
		dot(normalize(Pos), normalize(Pos + Vec[0] * t.x)),
		dot(normalize(Pos), normalize(Pos + Vec[1] * t.y))
	);
}

float3 nonpreciseangle_cosine(float3 Pos, float3x3 Vec, float3 t, float Prod) {
	return float3(
		dot(normalize(Pos), normalize(Pos + Vec[0] * t.x)),
		dot(normalize(Pos), normalize(Pos + Vec[1] * t.y)),
		dot(normalize(Pos), normalize(Pos + Vec[2] * t.z))
	);
}

float preciseangle_sine(float3 Pos, float3 Vec, float t, float Prod) {
	/* the sine of very narrow angles is near 0
	 * the exponent can be lowered when needed and we get all
	 * advantages of floating-point
	 */
	return length(cross(Pos, Pos + Vec * t)) / Prod;
}

float2 preciseangle_sine(float3 Pos, float2x3 Vec, float2 t, float Prod) {
	return float2(
		length(cross(Pos, Pos + Vec[0] * t.x)) / Prod,
		length(cross(Pos, Pos + Vec[1] * t.y)) / Prod
	);
}

float3 preciseangle_sine(float3 Pos, float3x3 Vec, float3 t, float Prod) {
	return float3(
		length(cross(Pos, Pos + Vec[0] * t.x)) / Prod,
		length(cross(Pos, Pos + Vec[1] * t.y)) / Prod,
		length(cross(Pos, Pos + Vec[2] * t.z)) / Prod
	);
}

float preciselength_arcsine(float sine) {
	/* the sine of very narrow angles is near 0
	 * the approximation to arcsine breaks down near 0
	 */
	return (sine <= 0.005 ? sine : asin(sine));
}

float2 preciselength_arcsine(float2 sine) {
	/* the sine of very narrow angles is near 0
	 * the approximation to arcsine breaks down near 0
	 */
	return (sine <= 0.005 ? sine : asin(sine));
}

float3 preciselength_arcsine(float3 sine) {
	/* the sine of very narrow angles is near 0
	 * the approximation to arcsine breaks down near 0
	 */
	return (sine <= 0.005 ? sine : asin(sine));
}

float intersection_rayXsphere_inside(float3 Pos, float3 Vec, float Rad) {
	/* ray:
	 *
	 *  P = O + Dt
	 *  P = Pos + Vec * t
	 */

	/* sphere:
	 *
	 *  (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
	 *  (x -  0 )^2 + (y -  0 )^2 + (z -  0 )^2 = Rad^2
	 */

	/* variables:
	 *
	 * a = D dot D = 1
	 * b = 2(O-C) dot D
	 * c = (O-C) dot O + (O-C) dot (-C) - r^2 = (O-C) dot (O-C) - r^2
	 *
	 * a = Vec dot Vec = 1
	 * b = 2(Pos-0) dot Vec
	 * c = (Pos-0) dot Pos + (Pos-0) dot (-0) - Rad^2 = (Pos-0) dot (Pos-0) - Rad^2
	 *
	 * a = 1
	 * b = 2Pos dot Vec
	 * c = Pos dot Pos + Pos dot 0 - Rad^2 = Pos dot Pos - Rad^2
	 */
	float a = 1;
	float b = 2 * dot(Pos, Vec);
	float c =     dot(Pos, Pos) - Rad * Rad;

	float t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

	return t;
}

float2 intersection_rayXsphere_inside(float3 Pos, float2x3 Vec, float Rad) {
	float a  = 1;
	float2 b = float2(
		   2 * dot(Pos, Vec[0]),
		   2 * dot(Pos, Vec[1]));
	float c  =     dot(Pos, Pos    ) - Rad * Rad;

	float2 t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

	return t;
}

float3 intersection_rayXsphere_inside(float3 Pos, float3x3 Vec, float Rad) {
	float a  = 1;
	float3 b = float3(
		   2 * dot(Pos, Vec[0]),
		   2 * dot(Pos, Vec[1]),
		   2 * dot(Pos, Vec[2]));
	float c  =     dot(Pos, Pos    ) - Rad * Rad;

	float3 t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);// Structures:


	return t;
}

float intersection_rayXsphere(float3 P, float3 v, float radius)
{
	float b = 2.0f * dot(P, v);
	float c =        dot(P, P) - radius * radius;

	float discriminant = (b * b) - (4.0 * c);
	float disc_rt = sqrt(discriminant);

	float t1 = (-b + disc_rt) * 0.5;
	float t2 = (-b - disc_rt) * 0.5;

	return min(t1, t2);
}

/* ############################################################################# */

inline float getHeightCoefficient(float3 Pos, float fPlanetRadius, float fAtmosphereRadius)
{
	float r = length(Pos);
	return
		sqrt(                r * r                 - fPlanetRadius * fPlanetRadius) /
		sqrt(fAtmosphereRadius * fAtmosphereRadius - fPlanetRadius * fPlanetRadius);
}

#define ONEmEPINV 1.0280912f
inline float getSunACoefficient(float x)
{
	// 1 / (1.0f - exp(-3.6f))
	return (1.0f - exp(-2.8f * x - 0.8f)) * ONEmEPINV;
}

#if	defined(SAMPLER_SKY) || defined(SAMPLER_GEO)
float4 getPhaseRM(float3 L, float3 V, float cust_fMieCoefSB, bool color) {
	// phase function
	float dLVinv = (dot(L, -V) * 0.5 + 0.5);
	float4 phaseRM;

	if (color) {
  	  phaseRM.rgb  = tex1D(TESR_samplerScatteringPhase,              dLVinv                        ).rgb;
  	  phaseRM.a    = tex2D(TESR_samplerScatteringPhase, float2(4.0 * dLVinv - 3.0, cust_fMieCoefSB)).a;
	//  phaseRM.rgba = tex2D(TESR_samplerScatteringPhase, float2(4.0 * dLVinv - 3.0, cust_fMieCoefSB));
  	}
  	else {
  	  phaseRM.rgb  = 1;
  	  phaseRM.a    = tex2D(TESR_samplerScatteringPhase, float2(4.0 * dLVinv - 3.0, cust_fMieCoefSB)).a;
//	  phaseRM.rgba = tex2D(TESR_samplerScatteringPhase, float2(4.0 * dLVinv - 3.0, cust_fMieCoefSB));
  	}

	return phaseRM;
}

/* Texture dimensions */
static const int cust_SCATTER_RES_Z = 32;	// default 32
static const int cust_SCATTER_RES_W = 8;	// default 8

float4 getScatter(float3 L, float3 V, float3 nEye, float height, float offs = 0.0) {
	float3 scatterCoords;

	scatterCoords.x = 1.0f - getSunACoefficient(dot(nEye, -L));	// light angle
	scatterCoords.y = dot(nEye, -V) * 0.5 + 0.5;			// view angle
	scatterCoords.z = saturate(height * 0.25);

	float h = saturate(height + 1.0 / cust_SCATTER_RES_Z);		// saturate(0 + 1 / 32) => 1 / 32
	float qH = h * (cust_SCATTER_RES_Z - 1.0);			// 1 / 32 * (32 - 1) => 31 / 32
	float fqH = floor(qH); qH = qH - fqH;

	scatterCoords.z = (fqH + offs + 0.0) / cust_SCATTER_RES_Z;
	float4 colorRaw1 = tex3D(TESR_samplerScatterH, scatterCoords);

	scatterCoords.z = (fqH + offs + 1.0) / cust_SCATTER_RES_Z;
	float4 colorRaw2 = tex3D(TESR_samplerScatterH, scatterCoords);

	return lerp(colorRaw1, colorRaw2, qH);
}

float4 getScatterAzimuth(float3 L, float3 V, float3 nEye, float height) {
	// get azimuth
	float3 Pr1 = cross(L, nEye);
	float3 Pr2 = cross(V, nEye);
	float azimuth = dot(Pr1, Pr2) * 0.5 + 0.5;
	float azimuthA = azimuth;

	// shrink azimuth to not influence LERP
	azimuth = (1.0 - 1.0 / cust_SCATTER_RES_W) * azimuth + 0.5 / cust_SCATTER_RES_W;

	return getScatter(L, V, nEye, height, azimuth);
}
#endif

/* ############################################################################# */

float4 CoEffsVS() {
	float3 L = -TESR_SunDirection.xyz;

    /* scattering shader ------------------------------------- */

	float cust_fIndRay    = MIDDAY_IndRay;
	float cust_fIndMie    = MIDDAY_IndMie;
	float cust_fMieCoefSB = MIDDAY_MieCSB;
	float3 T = normalize(float3(-L.x, 0, -L.z));
	float noon = sqrt(1.0 - (T.x * T.x));//T.z;//saturate(dot(float3(0, 0, 1), T));

#ifdef	VARYING_EFFICIENTS
	/*  morning:   1.5, 4.0, 0.0085
	 *  noon:      1.0, 1.0, 0.0025
	 *  afternoon: 2.0, 0.5, 0.0015
	 */

	if (T.x < 0) {
		cust_fIndRay    = lerp(SUNSET_IndRay, cust_fIndRay   , noon);
		cust_fIndMie    = lerp(SUNSET_IndMie, cust_fIndMie   , noon);
		cust_fMieCoefSB = lerp(SUNSET_MieCSB, cust_fMieCoefSB, noon);
	}
	else {
		cust_fIndRay    = lerp(SUNRSE_IndRay, cust_fIndRay   , noon);
		cust_fIndMie    = lerp(SUNRSE_IndMie, cust_fIndMie   , noon);
		cust_fMieCoefSB = lerp(SUNRSE_MieCSB, cust_fMieCoefSB, noon);
	}
#endif

	/* return in a vector */
	float4 coeffs;

	coeffs.x = cust_fIndRay;
	coeffs.y = cust_fIndMie;
	coeffs.z = cust_fMieCoefSB;
	coeffs.w = noon;

	return coeffs;
}

/* ############################################################################# */

#if defined(SAMPLER_SUN) || defined(SAMPLER_SKY)
float4 SunColor(in VS_OUTPUT IN, float4 AtmosphereCoef) {

	float3 L = -TESR_SunDirection.xyz;
	float3 V = normalize(IN.location.xyz);

    /* scattering shader ------------------------------------- */
#define	cust_fIndRay		AtmosphereCoef.x
#define	cust_fIndMie		AtmosphereCoef.y
#define	cust_fMieCoefSB		AtmosphereCoef.z
#define	cust_Saturation		AtmosphereCoef.w
    /* sun color ----------------------------------------------------------- */

	/* the reflections' pass camera is below surface, we could
	 * intersect the view-vector with the planet's surface to get an individual
	 * view-vector per pixel, though I don't know if the few hundret meters we
	 * can go around really affect the sky's appearance
	 *
	 * IN.location.xyz is relative to TESR_CameraPosition
	 * we maintain xy as [0,0] origin
	 */
	float3 Eye = WorldHeightMeters1(TESR_CameraPosition.z);

	// new parameterization
	// if we are directly on the planet-surface this is 0 and 1 for above atmosphere
	// range [0.0, 1.0] or more
	float height = getHeightCoefficient(Eye, fPlanetRadius, fAtmosphereRadius);

	/* eye-normal */
	float3 nEye = normalize(Eye);
	float dotEP = 0.5 * dot(nEye, -V) + 0.5;
	/* zenith:   dot([0,0,1], [0,0,-1]) = -1 = 0.0
	 * horizont: dot([0,0,1], [0,-1,0]) =  0 = 0.5
	 */
	float4 tl = tex2D(TESR_samplerOpticalDepth, float2(height, dotEP));

	float4 cust_SunColor = tex2D(TESR_samplerSun, float2(0.5, (dot(L, -V) - 1.0) * SUN_SIZE + 0.5));

	float3 sunIntensityAtt = cust_SunIntensity * exp(
		-cust_fIndRay * tl.xyz
		-cust_fIndMie * tl.aaa
	);

	float4 sunColor = float4(2* SUN_BRIGHTNESS * cust_SunColor.rgb * sunIntensityAtt, cust_SunColor.g);

    return sunColor;
}
#endif

/* ############################################################################# */

#ifdef SAMPLER_SKY
float4 SkyColor(in VS_OUTPUT IN, float4 AtmosphereCoef) {

    /* scattering shader ------------------------------------- */

	/* as long as we got no horizont */
//	if (IN.location.z <= 0.0)
//	    IN.location.z = 0.0;

#define	cust_fIndRay		AtmosphereCoef.x
#define	cust_fIndMie		AtmosphereCoef.y
#define	cust_fMieCoefSB		AtmosphereCoef.z
#define	cust_Saturation		AtmosphereCoef.w

	/* the reflections' pass camera is below surface, we could
	 * intersect the view-vector with the planet's surface to get an individual
	 * view-vector per pixel, though I don't know if the few hundret meters we
	 * can go around really affect the sky's appearance
	 *
	 * IN.location.xyz is relative to TESR_CameraPosition
	 * we maintain xy as [0,0] origin
	 */
	float3 Eye = WorldHeightMeters1(TESR_CameraPosition.z);
	float3 V = normalize(IN.location.xyz);
	float3 L = -TESR_SunDirection.xyz;
	/* if we are directly on the planet-surface this is 0 and 1 for above atmosphere
	 * range [0.0, 1.0] or more
	 */
	float height = getHeightCoefficient(Eye, fPlanetRadius, fAtmosphereRadius);
	/* we can not go outside the atmosphere! */
	if (0 && (height > 1.0))
		Eye += V * intersection_rayXsphere(Eye, V, fAtmosphereRadius);

	/* eye-normal */
	float3 nEye = normalize(Eye);
	float dotEP = 0.5 * dot(nEye, -V) + 0.5;

	/* zenith:   dot([0,0,1], [0,0,-1]) = -1 = 0.0
	 * horizont: dot([0,0,1], [0,-1,0]) =  0 = 0.5
	 */
	float4 tl = tex2D(TESR_samplerOpticalDepth, float2(height, dotEP));

	float3 lightIntensityAtt = cust_SunIntensity * exp(
		-cust_fIndRay * tl.xyz
		-cust_fIndMie * tl.aaa
	);

	// phase function
	float4 phaseRM = getPhaseRM(L, V, cust_fMieCoefSB, false);
	float4 colorRaw = getScatterAzimuth(L, V, nEye, height);

	float4 color = float4((
		cust_fIndRay * phaseRM.rgb * colorRaw.rgb +
		cust_fIndMie * phaseRM.aaa * colorRaw.aaa * lightIntensityAtt.rgb
	), 1.0);
	float3 skyColor = 1.00 * (1.0 - exp(-(0.5 + 0.5 * cust_Saturation) * color.xyz));

//	sunColor = float4(2* SUN_BRIGHTNESS * cust_SunColor.rgb * sunIntensityAtt, cust_SunColor.g);
    return float4(skyColor,1);
}

#endif

/* ############################################################################# */
#ifdef SAMPLER_GEO
void GeoColor(in VS_OUTPUT IN, in float3 Normal, out float3 ambColor, out float4 geoColor) {

    /* scattering shader ------------------------------------- */

#define	cust_fIndRay		IN.coeffs.atmosphere.x
#define	cust_fIndMie		IN.coeffs.atmosphere.y
#define	cust_fMieCoefSB		IN.coeffs.atmosphere.z
#define	cust_Saturation		IN.coeffs.atmosphere.w

	/* the reflections' pass camera is below surface, we could
	 * intersect the view-vector with the planet's surface to get an individual
	 * view-vector per pixel, though I don't know if the few hundret meters we
	 * can go around really affect the sky's appearance
	 *
	 * IN.location.xyz is relative to TESR_CameraPosition
	 * we maintain xy as [0,0] origin
	 */
	float3 Eye = WorldHeightMeters1(TESR_CameraPosition.z);
	float3 Pos = WorldHeightMeters2(TESR_CameraPosition.z + IN.location.z, IN.location.xy);
	float3 V = normalize(IN.location.xyz);
	float3 L = -TESR_SunDirection.xyz;
	float3 N = normalize(Normal.xyz);

	/* always choose the lower point as origin */
	if (TESR_CameraPosition.z > TESR_CameraPosition.z + IN.location.z) {
		Eye = Pos;
		Pos = WorldHeightMeters1(TESR_CameraPosition.z);
		V = -V;
	}

	/* if we are directly on the planet-surface this is 0 and 1 for above atmosphere
	 * range [0.0, 1.0] or more
	 */
	float height = getHeightCoefficient(Eye, fPlanetRadius, fAtmosphereRadius);
	float altitd = getHeightCoefficient(Pos, fPlanetRadius, fAtmosphereRadius);
	/* we can not go outside the atmosphere! */
	//if (0 && (height > 1.0))
//		Eye += V * intersection_rayXsphere(Eye.z, V, fAtmosphereRadius);
	//if (0 && (altitd > 1.0))
//		Pos += V * intersection_rayXsphere(Pos.z, V, fAtmosphereRadius);

	/* eye-normal */
	float3 nEye = normalize(Eye);
	float3 nPos = normalize(Pos);
	float dotPL = 0.5 * dot(nPos, L) + 0.5;

	/* zenith:   dot([0,0,1], [0,0,-1]) = -1 = 0.0
	 * horizont: dot([0,0,1], [0,-1,0]) =  0 = 0.5
	 */
	float4 tl = tex2D(TESR_samplerOpticalDepth, float2(altitd, dotPL));


	float3 lightIntensityAtt = cust_SunIntensity * exp(
		-cust_fIndRay * tl.xyz
		-cust_fIndMie * tl.aaa
	);

	// phase function
	float4 phaseRM = float4(getPhaseRM(L, V, cust_fMieCoefSB, true).xyz, 1.0);
//	float4 colorRaw1 = getScatter       (L, V, nEye, height);
	float4 colorRaw1 = getScatterAzimuth(L, V, nEye, height);
//	float4 colorRaw2 = getScatter       (L, V, nPos, altitd);
	float4 colorRaw2 = getScatterAzimuth(L, V, nPos, altitd);

	// eye -> frag extinction
	float3 color1 = float3(
		cust_fIndRay * phaseRM.rgb * colorRaw1.rgb +
		cust_fIndMie * phaseRM.aaa * colorRaw1.aaa * lightIntensityAtt.rgb
	);

	// frag -> light extinction
	float3 color2 = float3(
		cust_fIndRay * phaseRM.rgb * colorRaw2.rgb +
		cust_fIndMie * phaseRM.aaa * colorRaw2.aaa * lightIntensityAtt.rgb
	);

	float3 color = saturate(color1 - color2 - 0.05);
	float occlusionFactor = 0.5f * (dot(N, nPos) + 1.0f);

	// ambient
	float4 ambRaw = tex1D(TESR_samplerAmbient, dotPL).rgba;
	float3 ambient = float3(
		cust_fIndRay * ambRaw.rgb +
		cust_fIndMie * ambRaw.aaa * lightIntensityAtt.rgb
	);

	float4 tv = tex2D(TESR_samplerOpticalDepth, float2( 0.0f , 0.5f + 0.5f * (min(dot(nPos, V), -0.01f))));
	float4 tc = tex2D(TESR_samplerOpticalDepth, float2(height, 0.5f + 0.5f * (    dot(nEye, V)         )));
	tv -= tc; //due to sampling of optical depth, this subtraction can lead to tv reaching negative values,
	tv = max(tv, 0.0f.rrrr); //making some pixels on the horizon strongly oversaturated, because exp(-(tv<0)) can >> 1

	// attenuation
	float3 sunIntensityAtt = cust_SunIntensity * exp(
		-cust_fIndRay * tv.xyz
		-cust_fIndMie * tl.aaa
	);

	ambColor = float3(ambient);
	geoColor = float4(color, occlusionFactor);

}
#endif
