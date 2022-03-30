
#define TEX2D(value) tex2D(tex##value, In.T0)
#define EXTRA_TEXCOORD(value)
#define CONSTANT_SCALE(value) value
#define RESCALE(value)

float4 consta : register(c0);

sampler tex0 : register(s0);
sampler tex1 : register(s1);
sampler tex2 : register(s2);

struct VS_OUT
{
  float2 T0: TEXCOORD0; EXTRA_TEXCOORD(1) EXTRA_TEXCOORD(2)
};

float4 main( VS_OUT In ) : COLOR
{
  const float4 crc = { CONSTANT_SCALE(1.595794678f), -CONSTANT_SCALE(0.813476563f), 0, 0.0 };
  const float4 crb = { 0, -CONSTANT_SCALE(0.391448975f), CONSTANT_SCALE(2.017822266f), 0.0 };
  const float4 adj = { -CONSTANT_SCALE(0.87065506f), CONSTANT_SCALE(0.529705048f), -CONSTANT_SCALE(1.081668854f), 0 };
  float4 p;

  float y = TEX2D(0).a;
  float cr = TEX2D(1).a;
  float cb = TEX2D(2).a;

  p = y * CONSTANT_SCALE(1.164123535f);

  p += crc * cr;
  p += crb * cb;
  p += adj;

  RESCALE(p);

  p.w = 1.0;
  p *= consta;
  return p;
}