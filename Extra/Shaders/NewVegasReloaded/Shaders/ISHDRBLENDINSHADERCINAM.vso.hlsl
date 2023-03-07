//
//
// Parameters:

float4 geometryOffset : register(c0);
float4 texOffset0 : register(c1);
float4 texOffset1 : register(c2);


// Registers:
//
//   Name           Reg   Size
//   -------------- ----- ----
//   geometryOffset const_0       1
//   texOffset0     const_1       1
//   texOffset1     const_2       1
//


// Structures:

struct VS_INPUT {
    float4 position : POSITION;
    float4 texcoord_0 : TEXCOORD0;
};

struct VS_OUTPUT {
    float4 position : POSITION;
    float2 texcoord_0 : TEXCOORD0;
    float2 texcoord_1 : TEXCOORD1;
};

// Code:

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;

    const int4 const_3 = {2, -2, 0, 0};

    OUT.position.xy = IN.position.xy - (const_3.xy * geometryOffset.xy);
    OUT.position.zw = IN.position.zw;
    OUT.texcoord_0.xy = IN.texcoord_0.xy + texOffset0.xy;
    OUT.texcoord_1.xy = IN.texcoord_0.xy + texOffset1.xy;

    return OUT;
};

// approximately 5 instruction slots used
