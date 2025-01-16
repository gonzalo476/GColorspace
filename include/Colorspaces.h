#ifndef COLORSPACES_H
#define COLORSPACES_H

#include "include/ColorData.h"

#include <cmath>
#include <algorithm>
#include <array>

#include "DDImage/DDMath.h"
#include "DDImage/Matrix3.h"

/**
 * @brief Converts RGB values to CIE_XYZ.
 * @param rgb <float, 3> array.
 * @return A array containing the adjusted x, y, and z (r, g, b).
 */
static inline std::array<float, 3> LinToCIEXyz(
    const std::array<float, 3>& rgb
) {

    std::array<float, 3> xyz = {0.0f, 0.0f, 0.0f};

    float r = rgb[0];
    float g = rgb[1];
    float b = rgb[2];

    // D65 whitepoint
    xyz[0] = 0.4124564f * r + 0.3575761f * g + 0.1804375f * b;
    xyz[1] = 0.2126729f * r + 0.7151522f * g + 0.0721750f * b;
    xyz[2] = 0.0193339f * r + 0.1191920f * g + 0.9503041f * b;

    return xyz;
}

/**
 * @brief Converts CIE_XYZ values to rgb.
 * @param xyz <float, 3> array.
 * @return A array containing the adjusted r, g, and b (X, Y, Z).
 */
static inline std::array<float, 3> CIEXyzToLin(
    const std::array<float, 3>& xyz
) {
    std::array<float, 3> rgb = {0.0f, 0.0f, 0.0f};

    float x = xyz[0];
    float y = xyz[1];
    float z = xyz[2];

    // D65 whitepoint
    rgb[0] = 3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
    rgb[1] = -0.9692660f * x + 1.8760108f * y + 0.0415560f* z;
    rgb[2] = 0.0556434f * x - 0.2040259f * y + 1.0572252f * z;

    return rgb;
}

std::array<float, 3> LinToGamma180(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 1.80f);
    }

    return c;
}

std::array<float, 3> Gamma180ToLin(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.80f);
    }

    return c;
}

std::array<float, 3> LinToGamma220(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.20f);
    }

    return c;
}

std::array<float, 3> Gamma220ToLin(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.20f);
    }

    return c;
}

std::array<float, 3> LinToGamma240(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.40f);
    }

    return c;
}

std::array<float, 3> Gamma240ToLin(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.40f);
    }

    return c;
}

std::array<float, 3> LinToGamma260(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 1.0f / 2.60f);
    }

    return c;
}

std::array<float, 3> Gamma260ToLin(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < 3; ++i)
    {
        c[i] = std::pow(p[i], 2.60f);
    }

    return c;
}

std::array<float, 3> Rec709toLin(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

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

std::array<float, 3> LinToRec709(
    const std::array<float, 3>& p
)
{
    std::array<float, 3> c = {0.0f, 0.0f, 0.0f};

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

std::array<float, 3> XyzToLin(
    const std::array<float, 3>& rgb, 
    int primaryIndex
)
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