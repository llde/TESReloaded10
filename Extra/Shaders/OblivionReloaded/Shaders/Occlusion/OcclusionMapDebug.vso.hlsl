
row_major float4x4 TESR_OcclusionWorldViewProjTransform : register(c0);

struct VS_INPUT {
    float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
};

struct VS_OUTPUT {
    float4 position : POSITION;
    float4 texcoord_0 : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;
	
	float4 r0;

    r0.xyzw = mul(TESR_OcclusionWorldViewProjTransform, IN.position.xyzw);
	OUT.position.xyzw = r0.xyzw;
    OUT.texcoord_0.xyzw = IN.texcoord_0.xyzw;
    return OUT;
	
};