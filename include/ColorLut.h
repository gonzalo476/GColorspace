// in: LinToColor
// out: ColorToLin

#ifndef COLORLUT_H
#define COLORLUT_H

#include "include/ColorData.h"

#include <cmath>
#include <algorithm>
#include <array>

#include "DDImage/DDMath.h"
#include "DDImage/HSV.h"

constexpr float CIN_BLACKPOINT = 95.0f;
constexpr float CIN_WHITEPOINT = 685.0f;
constexpr float CIN_GAMMA = 0.6f;

using RGBcolor = std::array<float, 3>;


RGBcolor LinToCIEXyz(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = p[0];
    float g = p[1];
    float b = p[2];

    // D65 whitepoint
    rgb[0] = 0.4124564f * r + 0.3575761f * g + 0.1804375f * b;
    rgb[1] = 0.2126729f * r + 0.7151522f * g + 0.0721750f * b;
    rgb[2] = 0.0193339f * r + 0.1191920f * g + 0.9503041f * b;

    return rgb;
}

RGBcolor CIEXyzToLin(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float x = p[0];
    float y = p[1];
    float z = p[2];

    // D65 whitepoint
    rgb[0] = 3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
    rgb[1] = -0.9692660f * x + 1.8760108f * y + 0.0415560f* z;
    rgb[2] = 0.0556434f * x - 0.2040259f * y + 1.0572252f * z;

    return rgb;
}

// Gamma 1.8
RGBcolor Gamma180ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 1.0f / 1.80f);
    }

    return rgb;
}

RGBcolor LinToGamma180(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 1.80f);
    }

    return rgb;
}

// Gamma 2.2
RGBcolor Gamma220ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 1.0f / 2.20f);
    }

    return rgb;
}

RGBcolor LinToGamma220(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 2.20f);
    }

    return rgb;
}

// Gamma 2.4
RGBcolor Gamma240ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 1.0f / 2.40f);
    }

    return rgb;
}

RGBcolor LinToGamma240(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 2.40f);
    }

    return rgb;
}

// Gamma 2.6
RGBcolor Gamma260ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 1.0f / 2.60f);
    }

    return rgb;
}

RGBcolor LinToGamma260(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(p[i], 2.60f);
    }

    return rgb;
}

// Rec 709
RGBcolor LinToRec709(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.081f)
            rgb[i] = v / 4.5f;
        else
            rgb[i] = std::powf((v + 0.099f) / 1.099f, 1.0f / 0.45f);
    }

    return rgb;
}

RGBcolor Rec709ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.018f)
            rgb[i] = v * 4.5f;
        else
            rgb[i] = 1.099f * std::powf(v, 0.45f) - 0.099f;
    }

    return rgb;
}

// sRGB
RGBcolor sRGBToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.0031308f)
            rgb[i] = 12.92f * v;
        else
            rgb[i] = 1.055f * std::powf(v, 1.0f / 2.4f) - 0.055f;
    }

    return rgb;
}

RGBcolor LinTosRGB(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.04045f)
            rgb[i] = v / 12.92f;
        else
            rgb[i] = std::powf((v + 0.055f) / 1.055f, 2.4f);
    }

    return rgb;
}

// Cineon
RGBcolor LinToCineon(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float offset = std::powf(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];

        rgb[i] = gain  * (std::powf(10.f, (1023.f * v - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA) - offset);
    }

    return rgb;
}

RGBcolor CineonToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float offset = std::powf(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        
        rgb[i] = (std::log10f(v / gain + offset) / (0.002f / CIN_GAMMA) + CIN_WHITEPOINT) / 1023.f;
    }

    return rgb;
}

// HSV
RGBcolor HSVToLin(const RGBcolor& p)
{
    RGBcolor in =  sRGBToLin(p);
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = in[0];
    float g = in[1];
    float b = in[2];

    float cmax = std::max({r, g, b});
    float cmin = std::min({r, g, b});
    float delta = cmax - cmin;

    if (delta == 0.f)
        rgb[0] = 0.f;
    else if (cmax == r)
        rgb[0] = std::fmod((60.0f * ((g - b) / delta) + 360.0f), 360.0f) / 360.0f;
    else if (cmax == g)
        rgb[0] = std::fmod((60.0f * ((b - r) / delta) + 120.0f), 360.0f) / 360.0f;
    else if (cmax == b)
        rgb[0] = std::fmod((60.0f * ((r - g) / delta) + 240.0f), 360.0f) / 360.0f;

    rgb[1] = (cmax == 0.f) ? 0.f : (delta / cmax);
    rgb[2] = cmax;

    return rgb;
}

RGBcolor LinToHSV(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float h = p[0] * 360.0f;
    float s = p[1];
    float v = p[2];

    float c = v * s;
    float x = c * (1 - std::fabs(std::fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    if (h >= 0 && h < 60) {
        rgb[0] = c + m;
        rgb[1] = x + m;
        rgb[2] = m;
    } else if (h >= 60 && h < 120) {
        rgb[0] = x + m;
        rgb[1] = c + m;
        rgb[2] = m;
    } else if (h >= 120 && h < 180) {
        rgb[0] = m;
        rgb[1] = c + m;
        rgb[2] = x + m;
    } else if (h >= 180 && h < 240) {
        rgb[0] = m;
        rgb[1] = x + m;
        rgb[2] = c + m;
    } else if (h >= 240 && h < 300) {
        rgb[0] = x + m;
        rgb[1] = m;
        rgb[2] = c + m;
    } else if (h >= 300 && h < 360) {
        rgb[0] = c + m;
        rgb[1] = m;
        rgb[2] = x + m;
    }

    return LinTosRGB(rgb);
}

// HSL
RGBcolor LinToHSL(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = p[0] * 360.0f; // h
    float g = p[1];          // s
    float b = p[2];          // l

    float c = (1.0f - std::fabs(2.0f * b - 1.0f)) * g; // chroma
    float x = c * (1.0f - std::fabs(std::fmod(r / 60.0f, 2.0f) - 1.0f));
    float m = b - c / 2.0f;

    if (r >= 0 && r < 60) {
        rgb[0] = c + m;
        rgb[1] = x + m;
        rgb[2] = m;
    } else if (r >= 60 && r < 120) {
        rgb[0] = x + m;
        rgb[1] = c + m;
        rgb[2] = m;
    } else if (r >= 120 && r < 180) {
        rgb[0] = m;
        rgb[1] = c + m;
        rgb[2] = x + m;
    } else if (r >= 180 && r < 240) {
        rgb[0] = m;
        rgb[1] = x + m;
        rgb[2] = c + m;
    } else if (r >= 240 && r < 300) {
        rgb[0] = x + m;
        rgb[1] = m;
        rgb[2] = c + m;
    } else if (r >= 300 && r < 360) {
        rgb[0] = c + m;
        rgb[1] = m;
        rgb[2] = x + m;
    }

    return LinTosRGB(rgb);
}

RGBcolor HSLToLin(const RGBcolor& p)
{
    RGBcolor in = sRGBToLin(p);
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = in[0];
    float g = in[1];
    float b = in[2];

    float cmax = std::max({r, g, b});
    float cmin = std::min({r, g, b});
    float delta = cmax - cmin;

    // h
    if (delta == 0.0f)
        rgb[0] = 0.0f;
    else if (cmax == r)
        rgb[0] = std::fmod((60.0f * ((g - b) / delta) + 360.0f), 360.0f) / 360.0f;
    else if (cmax == g)
        rgb[0] = (60.0f * ((b - r) / delta) + 120.0f) / 360.0f;
    else if (cmax == b)
        rgb[0] = (60.0f * ((r - g) / delta) + 240.0f) / 360.0f;

    // l
    rgb[2] = (cmax + cmin) / 2.0f;

    // s
    rgb[1] = (delta == 0.0f) ? 0.0f : (delta / (1.0f - std::fabs(2.0f * rgb[2] - 1.0f)));

    return rgb;
}

// YPbPr
RGBcolor LinToYPbPr(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    
    float r = p[0]; // y
    float g = p[1]; // pb
    float b = p[2]; // pr

    rgb[0] = r + 1.5748f * b;
    rgb[1] = r - 0.1873f * g - 0.4681f * b;
    rgb[2] = r + 1.8556f * g;

    return LinTosRGB(rgb);
}

RGBcolor YPbPrToLin(const RGBcolor& p)
{
    RGBcolor in =  sRGBToLin(p);
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = in[0];
    float g = in[1];
    float b = in[2];

    rgb[0] = 0.2126f * r + 0.7152f * g + 0.0722f * b;        // Y
    rgb[1] = -0.1146f * r - 0.3854f * g + 0.5f * b;          // Pb
    rgb[2] = 0.5f * r - 0.4542f * g - 0.0458f * b;           // Pr

    return rgb;
}

// * YCbCr BT.709
RGBcolor LinToYCbCr(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float Y  = p[0];
    float Cb = p[1] - 0.5f;  
    float Cr = p[2] - 0.5f;

    rgb[0] = Y + 1.57480f * Cr;
    rgb[1] = Y - 0.18733f * Cb - 0.46813f * Cr;
    rgb[2] = Y + 1.85560f * Cb;

    return LinTosRGB(rgb);
}

RGBcolor YCbCrToLin(const RGBcolor& p)
{
    RGBcolor in = sRGBToLin(p);
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float r = in[0];
    float g = in[1];
    float b = in[2];

    rgb[0] = 0.2126f   * r + 0.7152f   * g + 0.0722f   * b;     // Y
    rgb[1] = -0.11457f * r - 0.38543f * g + 0.5f       * b + 0.5f; // Cb
    rgb[2] =  0.5f     * r - 0.45415f * g - 0.04585f   * b + 0.5f; // Cr

    return rgb;
}

// Panalog
RGBcolor PanalogToLin(const RGBcolor& p) // to_func_Panalog
{
    RGBcolor rgb = { 0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (444.0f * std::log10f(0.0408f + (1.0f - 0.0408f) * p[i]) + 681.0f) / 1023.0f;
    }

    return rgb;
}

RGBcolor LinToPanalog(const RGBcolor& p) // from_func_Panalog
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (std::powf(10.0f, (1023.0f * p[i] - 681.0f) / 444.0f) - 0.0408f) / (1.0f - 0.0408f);
    }

    return rgb;
}

// REDLog
RGBcolor REDLogToLin(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (511.0f * std::log10f(0.01f + (1.0f - 0.01f) * p[i]) + 1023.0f) / 1023.0f;
    }

    return rgb;
}

RGBcolor LinToREDLog(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (std::powf(10.0f, (1023.f * p[i] - 1023.0f) / 511.0f) - 0.01f) / (1.0f - 0.01f);
    }

    return rgb;
}

// ViperLog
RGBcolor ViperLogToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (500.0f * std::log10f(p[i]) + 1023.0f) / 1023.0f;;
    }

    return rgb;
}

RGBcolor LinToViperLog(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(10.f, (1023.f * p[i] - 1023.f) / 500.f);;
    }

    return rgb;
}

// AlexaV3LogC
// "ALEXA LOG C Curve-Usage in VFX"
RGBcolor AlexaV3LogCToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v > 0.010591f)
            rgb[i] =  0.247190f * std::log10f(5.555556f * v + 0.052272f) + 0.385537f;
        else
            rgb[i] = v * 5.367655f + 0.092809f;
    }
    return rgb;
}

RGBcolor LinToAlexaV3LogC(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v > 0.1496582f)
            rgb[i] = std::powf(10.f, (v - 0.385537f) / 0.2471896f) * 0.18f - 0.00937677f;
        else
            rgb[i] = ( v / 0.9661776f - 0.04378604f) * 0.18f - 0.00937677f;
    }

    return rgb;
}

// PLogLin
RGBcolor LinToPLog(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = 0.18f * std::powf( 10.0f, (p[i] * 1023. - 445.0f) * 0.002f / 0.6f );
    }

    return rgb;
}

RGBcolor PLogToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (445.0f + std::log10f(std::max(p[i], 1e-10f) / 0.18f) * 0.6f / 0.002f) / 1023.0f;
    }

    return rgb;
}

// SLog
RGBcolor SlogToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (0.432699f * std::log10f(p[i] + 0.037584f) + 0.616596f) + 0.03f;
    }

    return rgb;
}

RGBcolor LinToSlog(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::powf(10.0f, ((p[i] - 0.616596f - 0.03f) / 0.432699f)) - 0.037584f;
    }

    return rgb;
}


// SLog-1
RGBcolor Slog1ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= -0.00008153227156f)
            rgb[i] = ((std::log10f((v / 0.9f) + 0.037584f) * 0.432699f +0.616596f+0.03f)*(940.0f-64.0f) + 64.0f)/1023.0f;
        else
            rgb[i] = (((v / 0.9f) * 5.0f + 0.030001222851889303f)*(940.0f-64.0f) + 64.0f)/1023.0f;
    }

    return rgb;
}

RGBcolor LinToSlog1(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= 90.0f/1023.0f)
            rgb[i] = (std::powf( 10., (((v*1023.0f-64.0f)/(940.0f-64.0f)-0.616596f-0.03f)/0.432699f))-0.037584f)*0.9f;
        else
            rgb[i] = ((v*1023.0f-64.0f)/(940.0f-64.0f)-0.030001222851889303f)/5.0f*0.9f;
    }

    return rgb;
}


// SLog-2
RGBcolor Slog2ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= -0.00008153227156f)
            rgb[i] = ((std::log10f((v / 0.9f) * 155.0f / 219.0f + 0.037584f) * 0.432699f +0.616596f+0.03f)*(940.0f-64.0f) + 64.0f)/1023.0f;
        else
            rgb[i] = (((v / 0.9f) * 3.53881278538813f + 0.030001222851889303f)*(940.0f-64.0f) + 64.0f)/1023.0f;
    }

    return rgb;
}

RGBcolor LinToSlog2(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= 90.0f/1023.0f)
            rgb[i] = 219.0 * (std::powf( 10.0f, (((v*1023.0f-64.0f)/(940.0f-64.0f)-0.616596f-0.03f)/0.432699f))-0.037584f)/155.0f*0.9f;
        else
            rgb[i] = ((v*1023.0f-64.0f)/(940.0f-64.0f)-0.030001222851889303f)/3.53881278538813f*0.9f;
    }

    return rgb;
}

// SLog-3
RGBcolor Slog3ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= 0.01125000f)
            rgb[i] = (420.0f + std::log10f((v + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f;
        else
            rgb[i] = (v * (171.2102946929f - 95.0f)/0.01125000f + 95.0f) / 1023.0f;
    }

    return rgb;
}

RGBcolor LinToSlog3(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for(size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v >= 171.2102946929f / 1023.0f)
            rgb[i] = std::powf(10.0f, ((v * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f;
        else
            rgb[i] = (v * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
    }

    return rgb;
}

// CLog 10bit
// https://downloads.canon.com/nw/learn/white-papers/cinema-eos/WhitePaper_Clog_optoelectronic.pdf
RGBcolor ClogToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v < -0.0452664f || v > 8.00903f) {
            rgb[i] = 0.0f;
        } else if (v < 0.0f) {
            rgb[i] = -0.529136f * std::log10f(1.0f - 10.1596f * v) + 0.0730597f;
        } else {
            rgb[i] = 0.529136f * std::log10f(10.1596f * v + 1.0f) + 0.0730597f;
        }
    }

    return rgb;
}

RGBcolor LinToClog(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v < -0.0684932f || v > 1.08676f) {
            rgb[i] = 0.0f;
        } else if (v < 0.0730597f) {
            rgb[i] = (1.0f - std::powf(10.0f, (0.0730597f - v) / 0.529136f)) / 10.1596f;
        } else {
            rgb[i] = (std::powf(10.0f, (v - 0.0730597f) / 0.529136f) - 1.0f) / 10.1596f;
        }
    }

    return rgb;
}

// Log3G10 10 stops over mid grey
RGBcolor LinToLog3G10(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float a = 0.224282f;
    float b = 155.975327f;
    float c = 0.01f;
    float g = 15.1927f;

    for(size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v < 0.0f)
            rgb[i] = (v / g) - c;
        else
            rgb[i] = ((std::powf(10.f, (v / a)) - 1.0f) / b) - c;
    }

    return rgb;
}

RGBcolor Log3G10ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float a = 0.224282f;
    float b = 155.975327f;
    float c = 0.01f;
    float g = 15.1927f;

    for(size_t i = 0; i < 3; ++i)
    {
        float v = p[i] + c;
        if (v < 0.0f)
            rgb[i] = v * g;
        else
            rgb[i] = a * std::log10f((v * b) + 1.0f);
    }

    return rgb;
}

// Log3G12 12 stops over mid grey
RGBcolor LinToLog3G12(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float a = 0.184904f;
    float b = 347.189667f;
    float c = 0.0f;
    float g = 15.1927f;

    for(size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v < 0.0f)
            rgb[i] = (v / g) - c;
        else
            rgb[i] = ((std::powf(10.f, (v / a)) - 1.0f) / b) - c;
    }

    return rgb;
}

RGBcolor Log3G12ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float a = 0.184904f;
    float b = 347.189667f;
    float c = 0.0f;
    float g = 15.1927f;

    for(size_t i = 0; i < 3; ++i)
    {
        float v = p[i] + c;
        if (v < 0.0f)
            rgb[i] = v * g;
        else
            rgb[i] = a * std::log10f((v * b) + 1.0f);
    }

    return rgb;
}

#endif // COLORLUT_H