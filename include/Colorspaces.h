#ifndef COLORSPACES_H
#define COLORSPACES_H

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
RGBcolor LinToGamma180(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 1.0f / 1.80f);
    }

    return rgb;
}

RGBcolor Gamma180ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 1.80f);
    }

    return rgb;
}

// Gamma 2.2
RGBcolor LinToGamma220(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 1.0f / 2.20f);
    }

    return rgb;
}

RGBcolor Gamma220ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 2.20f);
    }

    return rgb;
}

// Gamma 2.4
RGBcolor LinToGamma240(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 1.0f / 2.40f);
    }

    return rgb;
}

RGBcolor Gamma240ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 2.40f);
    }

    return rgb;
}

// Gamma 2.6
RGBcolor LinToGamma260(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 1.0f / 2.60f);
    }

    return rgb;
}

RGBcolor Gamma260ToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = std::pow(p[i], 2.60f);
    }

    return rgb;
}

// Rec 709
RGBcolor Rec709toLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.081f)
            rgb[i] = v / 4.5f;
        else
            rgb[i] = std::pow((v + 0.099f) / 1.099f, 1.0f / 0.45f);
    }

    return rgb;
}

RGBcolor LinToRec709(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.018f)
            rgb[i] = v * 4.5f;
        else
            rgb[i] = 1.099f * std::pow(v, 0.45f) - 0.099f;
    }

    return rgb;
}

// sRGB
RGBcolor LinTosRGB(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.0031308f)
            rgb[i] = 12.92f * v;
        else
            rgb[i] = 1.055f * std::pow(v, 1.0f / 2.4f) - 0.055f;
    }

    return rgb;
}

RGBcolor sRGBToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.04045f)
            rgb[i] = v / 12.92f;
        else
            rgb[i] = std::pow((v + 0.055f) / 1.055f, 2.4f);
    }

    return rgb;
}

// Cineon
RGBcolor CineonToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float offset = std::pow(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];

        rgb[i] = gain  * (std::pow(10.f, (1023.f * v - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA) - offset);
    }

    return rgb;
}

RGBcolor LinToCineon(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    float offset = std::pow(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        
        rgb[i] = (std::log10(v / gain + offset) / (0.002f / CIN_GAMMA) + CIN_WHITEPOINT) / 1023.f;
    }

    return rgb;
}

// HSV
RGBcolor LinToHSV(const RGBcolor& p)
{
    RGBcolor in =  LinTosRGB(p);
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

RGBcolor HSVToLin(const RGBcolor& p)
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

    return sRGBToLin(rgb);
}

// HSL
RGBcolor HSLToLin(const RGBcolor& p)
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

    return sRGBToLin(rgb);
}

RGBcolor LinToHSL(const RGBcolor& p)
{
    RGBcolor in = LinTosRGB(p);
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
RGBcolor YPbPrToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};
    
    float r = p[0]; // y
    float g = p[1]; // pb
    float b = p[2]; // pr

    rgb[0] = r + 1.5748f * b;
    rgb[1] = r - 0.1873f * g - 0.4681f * b;
    rgb[2] = r + 1.8556f * g;

    return sRGBToLin(rgb);
}

RGBcolor LinToYPbPr(const RGBcolor& p)
{
    RGBcolor in =  LinTosRGB(p);
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
RGBcolor YCbCrToLin(const RGBcolor& p)
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float Y  = p[0];
    float Cb = p[1] - 0.5f;  
    float Cr = p[2] - 0.5f;

    rgb[0] = Y + 1.57480f * Cr;
    rgb[1] = Y - 0.18733f * Cb - 0.46813f * Cr;
    rgb[2] = Y + 1.85560f * Cb;

    return sRGBToLin(rgb);
}

RGBcolor LinToYCbCr(const RGBcolor& p)
{
    RGBcolor in = LinTosRGB(p);
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
RGBcolor LinToPanalog(const RGBcolor& p) // to_func_Panalog
{
    RGBcolor rgb = { 0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (444.0f * std::log10(0.0408f + (1.0f - 0.0408f) * p[i]) + 681.0f) / 1023.0f;
    }

    return rgb;
}

RGBcolor PanalogToLin(const RGBcolor& p) // from_func_Panalog
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (std::pow(10.0f, (1023.0f * p[i] - 681.0f) / 444.0f) - 0.0408f) / (1.0f - 0.0408f);
    }

    return rgb;
}

// REDLog
RGBcolor LinToREDLog(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (511.0f * std::log10(0.01f + (1.0f - 0.01f) * p[i]) + 1023.0f) / 1023.0f;
    }

    return rgb;
}

RGBcolor REDLogToLin(const RGBcolor& p) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        rgb[i] = (std::pow(10.0f, (1023.f * p[i] - 1023.0f) / 511.0f) - 0.01f) / (1.0f - 0.01f);
    }

    return rgb;
}

#endif // COLORSPACES_H