
float4 TESR_ShadowData : register(c0);
sampler2D DiffuseMap : register(s0);

struct VS_OUTPUT {
    float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

struct PS_OUTPUT {
    float4 color_0 : COLOR0;
};


PS_OUTPUT main(VS_OUTPUT IN) {
    PS_OUTPUT OUT;
	
	float4 r0;
	float r1;
	
	if (TESR_ShadowData.x == 2.0f || TESR_ShadowData.y == 1.0f) { // Leaves (Speedtrees) or alpha is required
		r0.rgba = tex2D(DiffuseMap, IN.texcoord_1.xy);
		if (r0.a > 0.2f) 
			r1 = IN.texcoord_0.z / IN.texcoord_0.w;
		else
			discard;
		OUT.color_0 = r1;
		return OUT;
	}
    OUT.color_0 = IN.texcoord_0.z / IN.texcoord_0.w;
    return OUT;
	
};