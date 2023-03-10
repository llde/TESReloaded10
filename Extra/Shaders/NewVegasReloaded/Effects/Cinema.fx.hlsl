// Cinema Shader For TESReloaded
//--------------------------------------------------
// Boomstick was h3r3

float4 TESR_GameTime;
float4 TESR_FilmGrainData;
float4 TESR_LetterBoxData;
float4 TESR_LetterBoxColor;
float4 TESR_VignetteData;
float4 TESR_PhotoShopOverlayData;
float4 TESR_DirtLensData;
float4 ChromaticAbrrationData01;
float4 ChromaticAbrrationData02;

sampler2D TESR_RenderedBuffer : register(s0) = sampler_state { ADDRESSU = CLAMP; ADDRESSV = CLAMP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };
sampler2D TESR_LensSampler : register(s1) < string ResourceName = "effects\dirtlens.png"; > = sampler_state { ADDRESSU = WRAP; ADDRESSV = WRAP; MAGFILTER = LINEAR; MINFILTER = LINEAR; MIPFILTER = LINEAR; };

// Film grain parameters
static const float time = TESR_GameTime.z; // The time in seconds since the start of the application
static const float grainSize = TESR_FilmGrainData.x; // Controls the size of the grain
static const float grainSpeed = TESR_FilmGrainData.y; // Controls the speed of the grain animation
static const float grainAmount = TESR_FilmGrainData.z; // Controls the amount of grain to add

// Letter box parameters              R    G    B
static const float3 letterboxColor = (0.0, 0.0, 0.0); // The color of letterbox
static const float letterboxHeight = 0.9888; // Height of the letterbox, as a fraction of the screen
static const float letterboxOpacity = 0.8; // Opacity of the letterbox

// Vignette parameters  
static const float radius = 1; // Radius of the vignette effect
static const float softness = 1; // Softness of the vignette transition
static const float intensity = 0; // Intensity of the vignette effect

// Photoshop overlay parameters  
static const float overlayInt = 0.7; // Intensity of the overlay amount

// Dirt lens parameters  
static const float dirtAmount = 0.8; // The overall intensity of the dirt texture
static const float2 dirtTexelSize = 0; // Scales the dirt texture

// Chromatic aberration parameters                  X-axis Y-axis
static const float2 chromaticAberrationOffsetRed = { 0.0003, 0.0 }; // The offset of red
static const float2 chromaticAberrationOffsetGreen = { 0.0, 0.0 }; // The offset of green
static const float2 chromaticAberrationOffsetBlue = { -0.0003, 0.0 }; // The offset of blue

// The vertex shader just passes through the position and texture coordinates
struct VertexShaderInput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

VertexShaderOutput mainVS(VertexShaderInput input)
{
    VertexShaderOutput output;
    output.position = input.position;
    output.texCoord = input.texCoord;
    return output;
}

//Film grain 
//--------------------------------------------------
float4 filmGrain(float2 texCoord : TEXCOORD) : COLOR
{
    // Sample the input texture at the current texCoord
    float4 color = tex2D(TESR_RenderedBuffer, texCoord);

    // Generate a random value between -1 and 1 based on the texCoord and time
    float randomValue = frac(sin(dot(texCoord, float2(12.9898, 78.233)) + time * grainSpeed) * 43758.5453);

    // Add the grain by multiplying the color by a value between 1 and 1 + grainAmount
    color *= 1 + grainAmount * (randomValue - 0.5);

    return color;
}

//Letter box 
//--------------------------------------------------
float4 letterBox(float2 texCoord : TEXCOORD) : COLOR
{
    float4 color = tex2D(TESR_RenderedBuffer, texCoord);

    // Calculate the y coordinate of the top and bottom of the letterbox
    float letterboxTop = (1.0 - letterboxHeight) / 2.0;
    float letterboxBottom = 1.0 - letterboxTop;

    // Check if the current pixel is within the letterbox region
    if (texCoord.y < letterboxTop || texCoord.y > letterboxBottom)
    {
        // Set the pixel color to black with the desired opacity
        color = float4(letterboxColor, 0.8);
    }

    return color;
}

//Vignette
//--------------------------------------------------
float4 vignette(float2 texCoord : TEXCOORD) : COLOR
{
    float2 center = { 0.5, 0.5 };
    
    // Calculate the distance from the center of the vignette effect
    float dist = length(texCoord - center);

    // Calculate the vignette intensity based on the distance
    float vignette = smoothstep(radius, radius - softness, dist);

    // Apply the vignette effect to the input texture
    float4 color = tex2D(TESR_RenderedBuffer, texCoord);
    color.rgb *= vignette * intensity + (1 - intensity);

    return color;
}

//Photoshop overlay
//--------------------------------------------------
float4 photoshopOverlay(float2 texCoord : TEXCOORD) : COLOR
{
    // Sample the input and overlay textures
    float4 inputColor = tex2D(TESR_RenderedBuffer, texCoord);
    float4 overlayColor = tex2D(TESR_RenderedBuffer, texCoord);

    // Multiply the input color by the overlay color, then blend with the original input color
    float4 color = lerp(inputColor, inputColor * overlayColor, overlayInt);

    return color;
}

//Dirt lens
//--------------------------------------------------
float4 dirtLens(float2 texCoord : TEXCOORD) : COLOR
{
    // Sample the main texture and the dirt texture
    float4 color = tex2D(TESR_RenderedBuffer, texCoord);
    float4 dirtColor = tex2D(TESR_LensSampler, texCoord * dirtTexelSize);
    
    // Calculate the luma of the main texture
    float luma = dot(color.rgb, float3(0.299, 0.587, 0.114));
    
    // Blend the main texture and the dirt texture using the luma and the dirt intensity
    color = lerp(color, dirtColor, luma * dirtAmount);
    
    return color;
}

// Chromatic aberration
//--------------------------------------------------
float4 chromaticAberration(float2 uv : TEXCOORD) : COLOR
{
    // Sample the input texture for the red, green, and blue channels
    float4 colorRed = tex2D(TESR_RenderedBuffer, uv + chromaticAberrationOffsetRed);
    float4 colorGreen = tex2D(TESR_RenderedBuffer, uv + chromaticAberrationOffsetGreen);
    float4 colorBlue = tex2D(TESR_RenderedBuffer, uv + chromaticAberrationOffsetBlue);

    // Combine the colors to create the final output color
    float4 color = float4(colorRed.r, colorGreen.g, colorBlue.b, 1.0);

    return color;
}

/*
float4 combinePass(float2 texCoord: TEXCOORD) : COLOR
{
    // Get effects
    float4 dirtLens = dirtLens;
    float4 filmGrain = filmGrain;
    float4 vignette = vignette;
    
    // Combine effects into single output
    float4 color = (dirtLens, filmGrain, vignette);
    return color;
}
*/

technique
{
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 dirtLens();

    }
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 vignette();
    }
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 filmGrain();
    }
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 photoshopOverlay();
    }
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 chromaticAberration();
    }
    pass
    {
        VertexShader = compile vs_3_0 mainVS();
        PixelShader = compile ps_3_0 letterBox();
    }
}