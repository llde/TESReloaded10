#define	expand(v)	        (((v) - 0.5) / 0.5)  // from 0/1 to -1/1
#define	compress(v)         (((v) * 0.5) + 0.5)  // from -1/1 to 0/1 
#define	shade(n, l)         max(dot(n, l), 0)
#define	shades(n, l)        saturate(dot(n, l))
#define invlerp(a, b, t)    ((t-a)/(b-a))
#define invlerps(a, b, t)    saturate((t-a)/(b-a))
#define luma(color)         dot(color, float3(0.2126f, 0.7152f, 0.0722f)) // extract luma (BT.709)
// #define luma(color)         dot(color, float3(0.3f, 0.59f, 0.11f)) // extract luma (BT.601)
#define mix(colora, colorb) colora * colorb * 2 // mix two colors without darkening
#define	weight(v)           dot(v, 1)
#define	sqr(v)              ((v) * (v))
#define blendnormals(a, b)  float3(a.xy + b.xy, a.z)
#define rand(s)             (frac(sin(dot(s, float2(12.9898, 78.233))) * 43758.5453)) // pseudo random from https://gist.github.com/keijiro/ee7bc388272548396870
#define pows(a, b)          (pow(abs(a), b)) // no more pow/abs warning!