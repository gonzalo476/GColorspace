#ifndef DISPATCHER_H
#define DISPATCHER_H

// in: LinToColor
// out: ColorToLin

#include "include/ColorLut.h"
#include "include/Constants.h"

#include <array>

using TransformDispatcher = std::array<float, 3>(*)(const std::array<float, 3>&);

static TransformDispatcher TransformInDispatcher(int i)
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
    case Constants::COLOR_VIPERLOG:
        return &LinToViperLog;
    case Constants::COLOR_ALEXAV3LOGC:
        return &LinToAlexaV3LogC;
    case Constants::COLOR_PLOGLIN:
        return &LinToPLog;
    case Constants::COLOR_SLOG:
        return &LinToSlog;
    case Constants::COLOR_SLOG1:
        return &LinToSlog1;
    case Constants::COLOR_SLOG2:
        return &LinToSlog2;
    case Constants::COLOR_SLOG3:
        return &LinToSlog3;
    case Constants::COLOR_CLOG:
        return &LinToClog;
    case Constants::COLOR_LOG3G10:
        return &LinToLog3G10;
    case Constants::COLOR_LOG3G12:
        return &LinToLog3G12;
    case Constants::COLOR_HYBRID_LOG_GAMMA:
        return &LinToHybridLogGamma;
    case Constants::COLOR_PROTUNE:
        return &LinToProtune;
    case Constants::COLOR_BT1886:
        return &LinToBT1886;
    case Constants::COLOR_ST2084:
        return &LinToSt2084;
    case Constants::COLOR_BLACKMAGIC_GEN5:
        return &LinToBFG5;
    case Constants::COLOR_ARRI_LOG_C4:
        return &LinToARRILogC4;
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
        return &Gamma180ToLin;
    case Constants::COLOR_GAMMA_2_20:
        return &Gamma220ToLin;
    case Constants::COLOR_GAMMA_2_40:
        return &Gamma240ToLin;
    case Constants::COLOR_GAMMA_2_60:
        return &Gamma260ToLin;
    case Constants::COLOR_REC709:
        return &Rec709ToLin;
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
    case Constants::COLOR_VIPERLOG:
        return &ViperLogToLin;
    case Constants::COLOR_ALEXAV3LOGC:
        return &AlexaV3LogCToLin;
    case Constants::COLOR_PLOGLIN:
        return &PLogToLin;
    case Constants::COLOR_SLOG:
        return &SlogToLin;
    case Constants::COLOR_SLOG1:
        return &Slog1ToLin;
    case Constants::COLOR_SLOG2:
        return &Slog2ToLin;
    case Constants::COLOR_SLOG3:
        return &Slog3ToLin;
    case Constants::COLOR_CLOG:
        return &ClogToLin;
    case Constants::COLOR_LOG3G10:
        return &Log3G10ToLin;
    case Constants::COLOR_LOG3G12:
        return &Log3G12ToLin;
    case Constants::COLOR_HYBRID_LOG_GAMMA:
        return &HybridLogGammaToLin;
    case Constants::COLOR_PROTUNE:
        return &ProtuneToLin;
    case Constants::COLOR_BT1886:
        return &BT1886ToLin;
    case Constants::COLOR_ST2084:
        return &St2084ToLin;
    case Constants::COLOR_BLACKMAGIC_GEN5:
        return &BFG5ToLin;
    case Constants::COLOR_ARRI_LOG_C4:
        return &ARRILogC4ToLin;
    case Constants::COLOR_LINEAR:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    default:
        return [](const std::array<float, 3>& in) { return in; }; // lambda
    } 
}


#endif // DISPATCHER_H