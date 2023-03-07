//
//
#define	ScreenSpace	Src0
// Parameters:

float3 BlurScale : register(c2);
float4 Cinematic : register(c19);
sampler2D DestBlend : register(s1);
float4 Fade : register(c22);
float4 HDRParam : register(c1);
sampler2D ScreenSpace : register(s0);
float4 Tint : register(c20);
float4 UseAlphaMask : register(c23);


// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   HDRParam     const_1       1
//   BlurScale    const_2       1
//   Cinematic    const_19      1
//   Tint         const_20      1
//   Fade         const_22      1
//   UseAlphaMask const_23      1
//   ScreenSpace         texture_0       1
//   DestBlend    texture_1       1
//


// Structures:

struct VS_INPUT {
    float2 ScreenOffset : TEXCOORD0;
    float2 texcoord_1 : TEXCOORD1;
};

struct VS_OUTPUT {
    float4 color_0 : COLOR0;
};

// Code:

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;

    const float4 const_0 = {0.299, 0.587000012, 0.114, 0};

    float1 q0;
    float3 q1;
    float1 q2;
    float3 q3;
    float3 q4;
    float3 q5;
    float4 r0;
    float4 r1;
    float4 r2;

    r0.xyzw = tex2D(ScreenSpace, IN.ScreenOffset.xy);
    r1.xyzw = tex2D(DestBlend, IN.texcoord_1.xy);
    r2.xyzw = tex2D(DestBlend, IN.ScreenOffset.xy);
    q0.x = 1.0 / max(r0.w, HDRParam.x);
    q1.xyz = ((q0.x * HDRParam.x) * r1.xyz) + max(r0.xyz * (q0.x * 0.5), 0);
    q2.x = dot(q1.xyz, const_0.xyz);
    q3.xyz = lerp(q2.x, q1.xyz, Cinematic.x);
    q4.xyz = (Cinematic.w * ((Tint.a * ((q2.x * Tint.rgb) - q3.xyz)) + q3.xyz)) - Cinematic.y;
    q5.xyz = lerp(r2.xyz, lerp((Cinematic.z * q4.xyz) + Cinematic.y, Fade.xyz, Fade.w), UseAlphaMask.w);
    OUT.color_0.a = BlurScale.z;
    OUT.color_0.rgb = (r2.w == 0 ? r2.xyz : q5.xyz);

    return OUT;
};

// approximately 22 instruction slots used (3 texture, 19 arithmetic)
