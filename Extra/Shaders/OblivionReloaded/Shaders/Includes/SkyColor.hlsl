#define PI 3.14159265359
#define	HORIZONT_BIAS	11.0

float4 TESR_CameraPosition: register(c63);
float4 TESR_SunDirection : register(c64);




float saturatedDot( in float3 a, in float3 b )
{
	return max( dot( a, b ), 0.0 );   
}

float3 YxyToXYZ( in float3 Yxy )
{
	float Y = Yxy.r;
	float x = Yxy.g;
	float y = Yxy.b;

	float X = x * ( Y / y );
	float Z = ( 1.0 - x - y ) * ( Y / y );

	return float3(X,Y,Z);
}

float3 XYZToRGB( in float3 XYZ )
{
	// CIE/E
	float3x3 M = float3x3 
	(
		 2.3706743, -0.9000405, -0.4706338,
		-0.5138850,  1.4253036,  0.0885814,
 		 0.0052982, -0.0146949,  1.0093968
	);

	return mul(M, XYZ);
}


float3 YxyToRGB( in float3 Yxy )
{
	float3 XYZ = YxyToXYZ( Yxy );
	float3 RGB = XYZToRGB( XYZ );
	return RGB;
}

void calculatePerezDistribution( in float t, out float3 A, out float3 B, out float3 C, out float3 D, out float3 E )
{
	A = float3(  0.1787 * t - 1.4630, -0.0193 * t - 0.2592, -0.0167 * t - 0.2608 );
	B = float3( -0.3554 * t + 0.4275, -0.0665 * t + 0.0008, -0.0950 * t + 0.0092 );
	C = float3( -0.0227 * t + 5.3251, -0.0004 * t + 0.2125, -0.0079 * t + 0.2102 );
	D = float3(  0.1206 * t - 2.5771, -0.0641 * t - 0.8989, -0.0441 * t - 1.6537 );
	E = float3( -0.0670 * t + 0.3703, -0.0033 * t + 0.0452, -0.0109 * t + 0.0529 );
}

float3 calculateZenithLuminanceYxy( in float t, in float thetaS )
{
	float chi  	 	= ( 4.0 / 9.0 - t / 120.0 ) * ( PI - 2.0 * thetaS );
	float Yz   	 	= ( 4.0453 * t - 4.9710 ) * tan( chi ) - 0.2155 * t + 2.4192;

	float theta2 	= thetaS * thetaS;
    float theta3 	= theta2 * thetaS;
    float T 	 	= t;
    float T2 	 	= t * t;

	float xz =
      ( 0.00165 * theta3 - 0.00375 * theta2 + 0.00209 * thetaS + 0.0)     * T2 +
      (-0.02903 * theta3 + 0.06377 * theta2 - 0.03202 * thetaS + 0.00394) * T +
      ( 0.11693 * theta3 - 0.21196 * theta2 + 0.06052 * thetaS + 0.25886);

    float yz =
      ( 0.00275 * theta3 - 0.00610 * theta2 + 0.00317 * thetaS + 0.0)     * T2 +
      (-0.04214 * theta3 + 0.08970 * theta2 - 0.04153 * thetaS + 0.00516) * T +
      ( 0.15346 * theta3 - 0.26756 * theta2 + 0.06670 * thetaS + 0.26688);

	return float3( Yz, xz, yz );
}

float3 calculatePerezLuminanceYxy( in float theta, in float gamma, in float3 A, in float3 B, in float3 C, in float3 D, in float3 E )
{
	return ( 1.0 + A * exp( B / cos( theta ) ) ) * ( 1.0 + C * exp( D * gamma ) + E * cos( gamma ) * cos( gamma ) );
}

float3 calculateSkyLuminanceRGB( in float3 s, in float3 e, in float t )
{
	float3 A, B, C, D, E;
	calculatePerezDistribution( t, A, B, C, D, E );

	float thetaS = acos( saturatedDot( s, float3(0,0,1) ) );
	float thetaE = acos( saturatedDot( e, float3(0,0,1) ) );
	float gammaE = acos( saturatedDot( s, e )		   );

	float3 Yz = calculateZenithLuminanceYxy( t, thetaS );

	float3 fThetaGamma = calculatePerezLuminanceYxy( thetaE, gammaE, A, B, C, D, E );
	float3 fZeroThetaS = calculatePerezLuminanceYxy( 0.0,    thetaS, A, B, C, D, E );

	float3 Yp = Yz * ( fThetaGamma / fZeroThetaS );

	return YxyToRGB( Yp );
}

float3 preetham(float3 SunDirection, float3 skypos, float turbidity)
{
 float3 skyLuminance 	= calculateSkyLuminanceRGB(normalize(SunDirection), normalize(skypos), turbidity );
 return (skyLuminance.rgb * 0.05);
 }
 
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

	float3 t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

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

#define	SUN_SIZE	(1024)
#define	SUN_BRIGHTNESS	(40) //???shot in the dark

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
	return (1.0f - exp(-2.8f * x - 0.8f)) * ONEmEPINV;
}

float hash(float n)
{
    return frac(sin(n)*43758.5453);
}

float noise(in float3 x)
{
    float3 p = floor(x);
    float3 f = frac(x);

    f = f * f * (3.0 - 2.0 * f);
 
    float n = p.x + p.y * 57.0 + 113.0 * p.z;

    float res = lerp(lerp(lerp( hash(n+  0.0), hash(n+  1.0),f.x),
                        lerp( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
                    lerp(lerp( hash(n+113.0), hash(n+114.0),f.x),
                        lerp( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
    return res;
}

float fbm(float3 p)
{
    float f;
    f  = 0.5000*noise( p ); p = p*2.02;
    f += 0.2500*noise( p ); p = p*2.03;
    f += 0.1250*noise( p ); p = p*2.01;
    f += 0.06250*noise( p ); p = p*2.04;
    f += 0.03125*noise( p );
    return f/0.984375;
}
