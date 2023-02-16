// A collection of functions that allow to query depth of a given pixel and also to reconstruct/project a point from screen to view space
// requires the shader to get access to the TESR_DepthBuffer sampler before the include.

float4x4 TESR_ProjectionTransform;
float4x4 TESR_InvProjectionTransform;
float4x4 TESR_ViewTransform;
float4 TESR_DepthConstants;
float4 TESR_CameraData;
float4 TESR_CameraPosition;

static const float nearZ = TESR_CameraData.x;
static const float farZ = TESR_CameraData.y;
static const float Q = farZ/(farZ - nearZ);

float readDepth(in float2 coord : TEXCOORD0)
{
	float Depth = tex2D(TESR_DepthBuffer, coord).x;;
    float ViewZ = (-nearZ *Q) / (Depth - Q);
	return ViewZ;
}

float3 reconstructPosition(float2 uv)
{
    float4 screenpos = float4(uv * 2.0 - 1.0f, tex2D(TESR_DepthBuffer, uv).x, 1.0f);
    screenpos.y = -screenpos.y;
    float4 viewpos = mul(screenpos, TESR_InvProjectionTransform);
    viewpos.xyz /= viewpos.w;
    return viewpos.xyz;
}

float3 projectPosition(float3 position){
	float4 projection = mul(float4 (position, 1.0), TESR_ProjectionTransform);
	projection.xyz /= projection.w;

	projection.x = projection.x * 0.5 + 0.5;
	projection.y = 0.5 - 0.5 * projection.y;

	return projection.xyz;
}


float3 toWorld(float2 tex)
{
	float3 v = float3(TESR_ViewTransform[0][2], TESR_ViewTransform[1][2], TESR_ViewTransform[2][2]);
	v += (1 / TESR_ProjectionTransform[0][0] * (2 * tex.x - 1)).xxx * float3(TESR_ViewTransform[0][0], TESR_ViewTransform[1][0], TESR_ViewTransform[2][0]);
	v += (-1 / TESR_ProjectionTransform[1][1] * (2 * tex.y - 1)).xxx * float3(TESR_ViewTransform[0][1], TESR_ViewTransform[1][1], TESR_ViewTransform[2][1]);
	return v;
}

float4 reconstructWorldPosition(float2 uv){
    // float4 screenpos = float4(uv * 2.0 - 1.0f, tex2D(TESR_DepthBuffer, uv).x, 1.0f);
    // screenpos.y = -screenpos.y;
    // float4 viewpos = mul(screenpos, TESR_InvWorldViewProjectionTransform);
    // viewpos.xyz /= viewpos.w;
    // return viewpos;


	float depth = readDepth(uv);
	float3 camera_vector = toWorld(uv) * depth;
	float4 world_pos = float4(TESR_CameraPosition.xyz + camera_vector, 1.0f);
	return world_pos;
}