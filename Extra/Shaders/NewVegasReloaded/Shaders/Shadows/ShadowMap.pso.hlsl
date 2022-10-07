
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
	float depth;

	if (TESR_ShadowData.x == 2.0f || TESR_ShadowData.y == 1.0f) { // Leaves (Speedtrees) or alpha is required
		r0.rgba = tex2D(DiffuseMap, IN.texcoord_1.xy);
		if (r0.a > 0.2f) 
			r1 = IN.texcoord_0.z / IN.texcoord_0.w;
		else
			discard;
		depth = r1;
	} else {
    	depth = IN.texcoord_0.z / IN.texcoord_0.w;
	}


	float k = 80;
	float esm = exp( 80 * depth);

	OUT.color_0 = float4(esm, esm - depth, 0.0f, 1.0f);
    return OUT;	
};