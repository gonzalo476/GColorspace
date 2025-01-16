#ifndef OUTPUT_COLOR_H
#define OUTPUT_COLOR_H

#include "include/Colorspaces.h"

#include <array>

static inline std::array<float, 3> OutputColorspace(
    const std::array<float, 3> &inRGB,
    int colorOut_index,
    int use_bradford_matrix)
{
    std::array<float, 3> outRGB = {0.0f, 0.0f, 0.0f};
    switch (colorOut_index)
    {
    case Constants::COLOR_GAMMA_1_80:
        outRGB = LinToGamma180(inRGB);
        break;
    case Constants::COLOR_GAMMA_2_20:
        outRGB = LinToGamma220(inRGB);
        break;
    case Constants::COLOR_GAMMA_2_40:
        outRGB = LinToGamma240(inRGB);
        break;
    case Constants::COLOR_GAMMA_2_60:
        outRGB = LinToGamma260(inRGB);
        break;
    case Constants::COLOR_REC709:
        outRGB = LinToRec709(inRGB);
        break;
    case Constants::COLOR_CIE_XYZ:
        outRGB = LinToCIEXyz(inRGB);
        break;
    case Constants::COLOR_LINEAR:
        outRGB = inRGB;
        break;
    default:
        break;
    }

    return outRGB;
}

#endif // OUTPUT_COLOR_H