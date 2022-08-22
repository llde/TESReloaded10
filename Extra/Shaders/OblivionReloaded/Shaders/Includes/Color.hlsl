static const
float3 WhitePointE = {0.959456f, 1.00f, 1.088754f};

static const
float3 BlueShift = {1.05f, 0.97f, 1.27f};

static const
float3x3 XYZ_RGB  = {{+ 0.412453, +	0.357580, + 0.180423},
			 {+ 0.212671, +	0.715160, + 0.072169},
			 {+ 0.019334, +	0.119193, + 0.950227}};

static const
float3x3 RGB_XYZ  = {{+ 3.240479  , - 1.537150  , - 0.498535	 },
			 {- 0.969256  , + 1.875992  , + 0.041556	 },
			 {+ 0.055648  , - 0.204043  , + 1.057311	 }};

float GetLuminance( const float3 rgb )
{
    return max(dot( XYZ_RGB[1], rgb ), 0.001);
}

float3 GetXYZfromRGB( const float3 rgb )
{
    return mul( XYZ_RGB, rgb );
}

float3 GetRGBfromXYZ( const float3 xyz )
{
    return mul( RGB_XYZ, xyz );
}

float3 GetWhitePoint()
{
    return mul( RGB_XYZ, WhitePointE );
}

static const float3x3 YUVs_RGB  = {{+ 0.29900, + 0.58700	 , + 0.11400	},
								   {- 0.14740, - 0.28950	 , + 0.43690	},
								   {+ 0.61500, - 0.51500	 , - 0.10000	}};
								   
static const float3x3 RGB_YUVs  = {{+ 1	     , + 0.000	     , + 1.13980	},
								   {+ 1	     , - 0.39380     , - 0.58050	},
								   {+ 1	     , + 2.02790     , + 0.000	    }};
			
float3 GetYUV( const float3 rgb )
{
    return mul( YUVs_RGB, rgb );
}

float3 GetRGB( const float3 yuv )
{
    return mul( RGB_YUVs, yuv );
}