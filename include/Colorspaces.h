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


RGBcolor LinToCIEXyz(const RGBcolor& rgb) 
{
    RGBcolor xyz = {0.0f, 0.0f, 0.0f};

    float r = rgb[0];
    float g = rgb[1];
    float b = rgb[2];

    // D65 whitepoint
    xyz[0] = 0.4124564f * r + 0.3575761f * g + 0.1804375f * b;
    xyz[1] = 0.2126729f * r + 0.7151522f * g + 0.0721750f * b;
    xyz[2] = 0.0193339f * r + 0.1191920f * g + 0.9503041f * b;

    return xyz;
}

RGBcolor CIEXyzToLin(const RGBcolor& xyz) 
{
    RGBcolor rgb = {0.0f, 0.0f, 0.0f};

    float x = xyz[0];
    float y = xyz[1];
    float z = xyz[2];

    // D65 whitepoint
    rgb[0] = 3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
    rgb[1] = -0.9692660f * x + 1.8760108f * y + 0.0415560f* z;
    rgb[2] = 0.0556434f * x - 0.2040259f * y + 1.0572252f * z;

    return rgb;
}

RGBcolor LinToGamma180(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 1.80f);
    }

    return c;
}

RGBcolor Gamma180ToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.80f);
    }

    return c;
}

RGBcolor LinToGamma220(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.20f);
    }

    return c;
}

RGBcolor Gamma220ToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.20f);
    }

    return c;
}

RGBcolor LinToGamma240(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.40f);
    }

    return c;
}

RGBcolor Gamma240ToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.40f);
    }

    return c;
}

RGBcolor LinToGamma260(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.60f);
    }

    return c;
}

RGBcolor Gamma260ToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.60f);
    }

    return c;
}

RGBcolor Rec709toLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.081f)
            c[i] = v / 4.5f;
        else
            c[i] = std::pow((v + 0.099f) / 1.099f, 1.0f / 0.45f);
    }

    return c;
}

RGBcolor LinToRec709(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.018f)
            c[i] = v * 4.5f;
        else
            c[i] = 1.099f * std::pow(v, 0.45f) - 0.099f;
    }

    return c;
}

RGBcolor LinTosRGB(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.0031308f)
            c[i] = v * 12.92f;
        else
            c[i] = 1.055f * (std::pow(v, 1.f / 2.4f) - 0.055f);
    }

    return c;
}

RGBcolor sRGBToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        if (v <= 0.04045f)
            c[i] = v / 12.92f;
        else
            c[i] = std::pow((v + 0.055f) / 1.055f, 2.4f);
    }

    return c;
}

RGBcolor CineonToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};
    float offset = std::pow(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];

        c[i] = gain  * (std::pow(10.f, (1023.f * v - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA) - offset);
    }

    return c;
}

RGBcolor LinToCineon(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};
    float offset = std::pow(10.f, (CIN_BLACKPOINT - CIN_WHITEPOINT) * 0.002f / CIN_GAMMA);
    float gain = 1.f / (1.f - offset);

    for (size_t i = 0; i < 3; ++i)
    {
        float v = p[i];
        
        c[i] = (std::log10(v / gain + offset) / (0.002f / CIN_GAMMA) + CIN_WHITEPOINT) / 1023.f;
    }

    return c;
}

RGBcolor HSVToLin(const RGBcolor& p)
{
    RGBcolor c = {0.0f, 0.0f, 0.0f};

    float r = p[0];
    float g = p[1];
    float b = p[2];

    float cmax = std::max({r, g, b});
    float cmin = std::min({r, g, b});
    float delta = cmax - cmin;

    if (delta == 0.f)
        c[0] = 0.f;
    else if (cmax == r)
        c[0] = std::fmod((60.0f * ((g - b) / delta) + 360.0f), 360.0f) / 360.0f;
    else if (cmax == g)
        c[0] = std::fmod((60.0f * ((b - r) / delta) + 120.0f), 360.0f) / 360.0f;
    else if (cmax == b)
        c[0] = std::fmod((60.0f * ((r - g) / delta) + 240.0f), 360.0f) / 360.0f;

    c[1] = (cmax == 0.f) ? 0.f : (delta / cmax);
    c[2] = cmax;

    return c;
}

RGBcolor XyzToLin(RGBcolor& rgb, int primaryIndex)
{
    const auto& p = primarySpaces.at(primaryIndex);

    // calc z coords
    float rZ = 1.0f - (p[0][0] + p[0][1]);
    float gZ = 1.0f - (p[1][0] + p[1][1]);
    float bZ = 1.0f - (p[2][0] + p[2][1]);

    // rgb to CIEXYZ
     std::array<std::array<float, 3>, 3> matrix = {{
        {p[0][0], p[1][0], p[2][0]},
        {p[0][1], p[1][1], p[2][1]},
        {rZ, gZ, bZ}
     }};

    // multiply rgb to matrix
    std::array<float, 3> xyz = {0.0f, 0.0f, 0.0f};
    for (int i = 0; i <3; ++i) {
        xyz[0] += matrix[0][i] * rgb[i];
        xyz[1] += matrix[1][i] * rgb[i];
        xyz[2] += matrix[2][i] * rgb[i];
    }

    return xyz;
}



#endif // COLORSPACES_H