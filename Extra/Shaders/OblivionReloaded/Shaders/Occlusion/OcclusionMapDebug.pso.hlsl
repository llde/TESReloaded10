
sampler2D BaseMap : register(s0);

struct VS_OUTPUT {
    float4 texcoord_0 : TEXCOORD0;
};

struct PS_OUTPUT {
    float4 color_0 : COLOR0;
};


PS_OUTPUT main(VS_OUTPUT IN) {
    PS_OUTPUT OUT;
	
	float4 r0;
	
	r0.xyzw = tex2D(BaseMap, IN.texcoord_0.xy);
	OUT.color_0.a = 1.0f;
    OUT.color_0.rgb = r0.xyz;
    return OUT;
	
};