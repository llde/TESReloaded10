
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

	OUT.color_0 = float4(0.0f, 0.0f, 0.0f, 1.0f);

	// TESR_ShadowData.w : shadow technique
	// 0: disabled
	// 1: VSM
	// 2: simple ESM
	// 3: filtered ESM
	// 4: PCF or Orthomap
	float4 shadowMode = {TESR_ShadowData.w == 1.0f, TESR_ShadowData.w == 2.0f, TESR_ShadowData.w == 3.0f, (TESR_ShadowData.w == 4.0f)};
	shadowMode = (1 - TESR_ShadowData.z) * shadowMode + float4(0, 0, 0, 1) * TESR_ShadowData.z; //will cancel out shadowData.w if ortho map and replace by PCF mode

	// VSM
	//cheat to reduce shadow acne in variance maps
	float dx = ddx(depth);
	float dy = ddy(depth);
	float moment2 = depth * depth + 0.25 * (dx * dx + dy * dy);
	OUT.color_0 += float4(depth, moment2, 0.0f, 1.0f) * shadowMode.x; 

	// PCF/simple ESM
	OUT.color_0 += float4(depth, 0.0f, 0.0f, 1.0f) * (shadowMode.y + shadowMode.w);

	// ESSM
	float k = 80;
	float esm = exp( 80 * depth);
	OUT.color_0 += float4(esm, esm - depth, 0.0f, 1.0f) * shadowMode.z;

	return OUT;	
};