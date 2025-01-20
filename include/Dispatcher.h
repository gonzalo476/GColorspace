#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "include/Colorspaces.h"
#include "include/Constants.h"

#include <array>

using TransformDispatcher = std::array<float, 3>(*)(const std::array<float, 3>&);

static TransformDispatcher TransformInDispatcher(int i)
{
    switch (i)
    {
    case Constants::COLOR_GAMMA_1_80:
        return &Gamma180ToLin;
    case Constants::COLOR_GAMMA_2_20:
        return &Gamma220ToLin;
    case Constants::COLOR_GAMMA_2_40:
        return &Gamma240ToLin;
    case Constants::COLOR_GAMMA_2_60:
        return &Gamma260ToLin;
    case Constants::COLOR_REC709:
        return &Rec709toLin;
    case Constants::COLOR_SRGB:
        return &sRGBToLin;
    case Constants::COLOR_CINEON:
        return &CineonToLin;
    case Constants::COLOR_HSV:
        return &HSVToLin;
    case Constants::COLOR_HSL:
        return &HSLToLin;
    case Constants::COLOR_Y_PB_PR:
        return &YPbPrToLin;
    case Constants::COLOR_Y_CB_CR:
        return &YCbCrToLin;
    case Constants::COLOR_CIE_XYZ:
        return &CIEXyzToLin;
    case Constants::COLOR_PANALOG:
        return &PanalogToLin;
    case Constants::COLOR_REDLOG:
        return &REDLogToLin;
    case Constants::COLOR_LINEAR:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    default:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    }
}

static TransformDispatcher TransformOutDispatcher(int i)
{
    switch (i)
    {
    case Constants::COLOR_GAMMA_1_80:
        return &LinToGamma180;
    case Constants::COLOR_GAMMA_2_20:
        return &LinToGamma220;
    case Constants::COLOR_GAMMA_2_40:
        return &LinToGamma240;
    case Constants::COLOR_GAMMA_2_60:
        return &LinToGamma260;
    case Constants::COLOR_REC709:
        return &LinToRec709;
    case Constants::COLOR_SRGB:
        return &LinTosRGB;
    case Constants::COLOR_CINEON:
        return &LinToCineon;
    case Constants::COLOR_HSV:
        return &LinToHSV;
    case Constants::COLOR_HSL:
        return &LinToHSL;
    case Constants::COLOR_Y_PB_PR:
        return &LinToYPbPr;
    case Constants::COLOR_Y_CB_CR:
        return &LinToYCbCr;
    case Constants::COLOR_CIE_XYZ:
        return &LinToCIEXyz;
    case Constants::COLOR_PANALOG:
        return &LinToPanalog;
    case Constants::COLOR_REDLOG:
        return &LinToREDLog;
    case Constants::COLOR_LINEAR:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    default:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    } 
}

#endif // DISPATCHER_H