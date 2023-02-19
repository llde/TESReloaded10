float3 GetNormal( float2 uv)
{
	return tex2D (TESR_NormalsBuffer, uv).xyz * 2 - 1;
}


float3 GetWorldNormal( float2 uv)
{
	float4 normal = float4(GetNormal(uv), 1);
	return mul(TESR_ViewTransform, normal).xyz;
}