
row_major float4x4 TESR_ShadowWorldTransform : register(c0);
row_major float4x4 TESR_ShadowViewProjTransform : register(c4);
float4 TESR_ShadowData : register(c8);
float4 Bones[54] : register(c9);
float4 BillboardRight : register(c63);
float4 BillboardUp : register(c64);
float4 RockParams : register(c65);
float4 RustleParams : register(c66);
float4 WindMatrices[16] : register(c67);
float4 LeafBase[48] : register(c83);

struct VS_INPUT {
    float4 position : POSITION;
	float4 texcoord_0 : TEXCOORD0;
    float4 blendweight : BLENDWEIGHT;
    float4 blendindexes : BLENDINDICES;
};

struct VS_OUTPUT {
    float4 position : POSITION;
    float4 texcoord_0 : TEXCOORD0;
	float4 texcoord_1 : TEXCOORD1;
};

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;
	
#define	PI			3.14159274
#define	angler(v)		(((v) * (2 * PI)) - PI)
#define	weight(v)		dot(v, 1)
#define	sqr(v)			((v) * (v))

	const float4 const_0 = {1.0f, 765.01001f, 0.0f, 0.0f};
	const float4 const_4 = {(1.0 / (PI * 2)), 0.25, 0.5, 0};
	
	float4 offset;
    float4 q0;
	float4 q1;
	float4 q2;
	float4 q3;
    float4 q4;
    float4 q5;
    float4 q6;
    float4 q7;
    float4 q8;
	float4 q9;
	float4 q10;
	float4 q11;
	float4 q28;
	float4 q59;
	float4 r1;
	float4 r2;
	float4 r3;
	float4 r4;
	float4 r5;
	float4 r0 = IN.position;
	
	if (TESR_ShadowData.x == 1.0f) { // Skinned (Actors)
		offset.xyzw = IN.blendindexes.zyxw * const_0.y;
		r0.w = 1;
		q0.xyzw = (IN.position.xyzx * const_0.xxxz) + const_0.zzzx;
		q8.xyz = mul(float3x4(Bones[0 + offset.w].xyzw, Bones[1 + offset.w].xyzw, Bones[2 + offset.w].xyzw), q0.xyzw);
		q6.xyz = mul(float3x4(Bones[0 + offset.z].xyzw, Bones[1 + offset.z].xyzw, Bones[2 + offset.z].xyzw), q0.xyzw);
		q5.xyz = mul(float3x4(Bones[0 + offset.x].xyzw, Bones[1 + offset.x].xyzw, Bones[2 + offset.x].xyzw), q0.xyzw);
		q4.xyz = mul(float3x4(Bones[0 + offset.y].xyzw, Bones[1 + offset.y].xyzw, Bones[2 + offset.y].xyzw), q0.xyzw);
		q7.xyz = (IN.blendweight.z * q6.xyz) + ((IN.blendweight.x * q5.xyz) + (q4.xyz * IN.blendweight.y));
		r0.xyz = ((1 - weight(IN.blendweight.xyz)) * q8.xyz) + q7.xyz;
	}
	else if (TESR_ShadowData.x == 2.0f) { // Leaves (Speedtrees)
		q1.x = sqr(angler(frac((((IN.blendindexes.z / 48)) * 0.499999553) + 0.25)));
		q6.x = angler(frac((((IN.blendindexes.z / 48)) * 0.499999553) + 0.25));
		q7.x = sqr(q6.x);
		offset.x = IN.blendindexes.y;
		r1.zw = BillboardRight.zw;
		q10.z = 0;
		r3.z = 0;
		q8.x = (q7.x * ((q7.x * ((q7.x * -2.52398507e-007) + 2.47609005e-005)) - (1.0 / 72))) + (1.0 / 24);
		q2.x = (q1.x * ((q1.x * ((q1.x * -2.52398507e-007) + 2.47609005e-005)) - (1.0 / 72))) + (1.0 / 24);
		q9.xy = (((((q7.x * ((q7.x * q8.x) - 0.5)) + 1) * RustleParams.z) * RustleParams.x) / (PI * 2)) + const_4.yz;
		r1.xy = angler(frac(q9.xy)) * angler(frac(q9.xy));
		q3.xy = (((((q1.x * ((q1.x * q2.x) - 0.5)) + 1) * RockParams.z) * RockParams.x) / (PI * 2)) + const_4.yz;
		q10.xy = angler(frac(q3.xy)) * angler(frac(q3.xy));
		q11.xy = (((((-2.52398507e-007 * r1.xy) + 2.47609005e-005) * r1.xy) - (1.0 / 72)) * r1.xy) + (1.0 / 24);
		r3.xy = (q11.xy * r1.xy) - 0.5;
		r3.xw = (r1.yx * r3.yx) + 1;
		r3.y = -r3.w;
		r1.y = dot(r3.wxz, BillboardRight.xyz);
		r1.x = dot(r3.xyz, BillboardRight.xyz);
		q5.xy = (((((-2.52398507e-007 * q10.xy) + 2.47609005e-005) * q10.xy) - (1.0 / 72)) * q10.xy) + (1.0 / 24);
		r2.xy = (q5.xy * q10.xy) - 0.5;
		q10.xw = (q10.yx * r2.yx) + 1;
		r2.xyzw = IN.blendindexes.w * LeafBase[IN.blendindexes.z];
		q10.y = -q10.w;
		r4.x = dot(q10.zwx, r2.xyz);
		r5.x = dot(q10.zxy, r2.xyz);
		q10.y = dot(r3.wxz, BillboardUp.xyz);
		q10.x = dot(r3.xyz, BillboardUp.xyz);
		q10.zw = BillboardUp.zw;
		q59.xyzw = ((r4.x * q10.xyzw) + (r5.x * r1.xyzw)) + r0.xyzw;
		q28.xyzw = mul(float4x4(WindMatrices[0 + offset.x].xyzw, WindMatrices[1 + offset.x].xyzw, WindMatrices[2 + offset.x].xyzw, WindMatrices[3 + offset.x].xyzw), q59.xyzw);
		r0.xyzw = (IN.blendindexes.x * (q28.xyzw - q59.xyzw)) + q59.xyzw;
	}
    r0 = mul(r0, TESR_ShadowWorldTransform);
	r0 = mul(r0, TESR_ShadowViewProjTransform);
	OUT.position = r0;
    OUT.texcoord_0 = r0;
	OUT.texcoord_1 = IN.texcoord_0;
    return OUT;
	
};