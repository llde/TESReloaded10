
static const float BIAS = 0.001f;

float LookupFar(float4 ShadowPos, float2 OffSet) {
	
	float Shadow = tex2D(TESR_ShadowMapBufferFar, ShadowPos.xy + float2(OffSet.x * TESR_ShadowData.w, OffSet.y * TESR_ShadowData.w)).r;
	if (Shadow < ShadowPos.z - BIAS) return TESR_ShadowData.y;
	return 1.0f;
	
}

float GetLightAmountFar(float4 ShadowPos) {
	
	float Shadow = 0.0f;
	float x;
	float y;
	
	ShadowPos.xyz /= ShadowPos.w;
    if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
        ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
        ShadowPos.z <  0.0f || ShadowPos.z > 1.0f)
		return 1.0f;

    ShadowPos.x = ShadowPos.x *  0.5f + 0.5f;
    ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;
	for (y = -0.5f; y <= 0.5f; y += 0.5f) {
		for (x = -0.5f; x <= 0.5f; x += 0.5f) {
			Shadow += LookupFar(ShadowPos, float2(x, y));
		}
	}
	Shadow /= 9.0f;
	return Shadow;
	
}

float Lookup(float4 ShadowPos, float2 OffSet) {
	
	float Shadow = tex2D(TESR_ShadowMapBufferNear, ShadowPos.xy + float2(OffSet.x * TESR_ShadowData.z, OffSet.y * TESR_ShadowData.z)).r;
	if (Shadow < ShadowPos.z - BIAS) return TESR_ShadowData.y;
	return 1.0f;
	
}

float GetLightAmount(float4 ShadowPos, float4 ShadowPosFar) {
	
	if (TESR_ShadowData.x == -1.0f) return 1.0f; // Shadows are applied in post processing (ShadowsExteriors.fx.hlsl)
	
	float Shadow = 0.0f;
	float x;
	float y;
	
	ShadowPos.xyz /= ShadowPos.w;
    if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
        ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
        ShadowPos.z <  0.0f || ShadowPos.z > 1.0f)
		return GetLightAmountFar(ShadowPosFar);
 
    ShadowPos.x = ShadowPos.x *  0.5f + 0.5f;
    ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;
	if (TESR_ShadowData.x == 0.0f) {
		for (y = -0.5f; y <= 0.5f; y += 0.5f) {
			for (x = -0.5f; x <= 0.5f; x += 0.5f) {
				Shadow += Lookup(ShadowPos, float2(x, y));
			}
		}
		Shadow /= 9.0f;
	}
	else if (TESR_ShadowData.x == 1.0f) {
		for (y = -1.5f; y <= 1.5f; y += 1.0f) {
			for (x = -1.5f; x <= 1.5f; x += 1.0f) {
				Shadow += Lookup(ShadowPos, float2(x, y));
			}
		}
		Shadow /= 16.0f;
	}
	else if (TESR_ShadowData.x == 2.0f) {
		for (y = -1.0f; y <= 1.0f; y += 0.5f) {
			for (x = -1.0f; x <= 1.0f; x += 0.5f) {
				Shadow += Lookup(ShadowPos, float2(x, y));
			}
		}
		Shadow /= 25.0f;
	}
	else {
		for (y = -2.5f; y <= 2.5f; y += 1.0f) {
			for (x = -2.5f; x <= 2.5f; x += 1.0f) {
				Shadow += Lookup(ShadowPos, float2(x, y));
			}
		}
		Shadow /= 36.0f;
	}
	return Shadow;
	
}

float GetLightAmountSkinFar(float4 ShadowPos) {
					
	float Shadow = 0.0f;
	float x;
	float y;
	
	ShadowPos.xyz /= ShadowPos.w;
    if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
        ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
        ShadowPos.z <  0.0f || ShadowPos.z > 1.0f)
		return 1.0f;
 
    ShadowPos.x = ShadowPos.x *  0.5f + 0.5f;
    ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;
	for (y = -0.5f; y <= 0.5f; y += 0.5f) {
		for (x = -0.5f; x <= 0.5f; x += 0.5f) {
			Shadow += Lookup(ShadowPos, float2(x, y));
		}
	}
	Shadow /= 9.0f;
	return Shadow;
	
}

float GetLightAmountSkin(float4 ShadowPos, float4 ShadowPosFar) {
	
	if (TESR_ShadowData.x == -1.0f) return 1.0f; // Shadows are applied in post processing (ShadowsExteriors.fx.hlsl)
	
	float Shadow = 0.0f;
	float x;
	float y;
	
	ShadowPos.xyz /= ShadowPos.w;
    if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
        ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
        ShadowPos.z <  0.0f || ShadowPos.z > 1.0f)
		return GetLightAmountSkinFar(ShadowPosFar);
 
    ShadowPos.x = ShadowPos.x *  0.5f + 0.5f;
    ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;
	for (y = -0.1f; y <= 0.1f; y += 0.05f) {
		for (x = -0.1f; x <= 0.1f; x += 0.05f) {
			Shadow += Lookup(ShadowPos, float2(x, y));
		}
	}
	Shadow /= 25.0f;
	return Shadow;
	
}

float GetLightAmountGrass(float4 ShadowPos) {
	
	if (TESR_ShadowData.x == -1.0f) return 1.0f; // Shadows are applied in post processing (ShadowsExteriors.fx.hlsl)
	
	float Shadow = 0.0f;
	float x;
	float y;
	
	ShadowPos.xyz /= ShadowPos.w;
    if (ShadowPos.x < -1.0f || ShadowPos.x > 1.0f ||
        ShadowPos.y < -1.0f || ShadowPos.y > 1.0f ||
        ShadowPos.z <  0.0f || ShadowPos.z > 1.0f)
		return 1.0f;
 
    ShadowPos.x = ShadowPos.x *  0.5f + 0.5f;
    ShadowPos.y = ShadowPos.y * -0.5f + 0.5f;
	Shadow = Lookup(ShadowPos, float2(0.0f, 0.0f));
	return Shadow;
	
}