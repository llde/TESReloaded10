#define	expand(v)	        (((v) - 0.5) / 0.5)  // from 0/1 to -1/1
#define	compress(v)         (((v) * 0.5) + 0.5)  // from -1/1 to 0/1 
#define	shade(n, l)         max(dot(n, l), 0)
#define	shades(n, l)        saturate(dot(n, l))
#define invlerp(a, b, t)    (t-a)/(b-a)
#define luma(color)         color.r * 0.3f + color.g * 0.59f +color.b * 0.11f // extract luma
#define mix(colora, colorb) colora * colorb * 2 // mix two colors without darkening
#define	weight(v)           dot(v, 1)
#define	sqr(v)              ((v) * (v))
#define blendnormals(a, b)  float3(a.xy + b.xy, a.z)