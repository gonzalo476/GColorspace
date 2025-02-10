#ifndef DISPATCHER_H
#define DISPATCHER_H

// in: LinToColor
// out: ColorToLin

#include <DDImage/Knobs.h>

#include <array>

#include "include/ColorData.h"
#include "include/ColorLut.h"
#include "include/Constants.h"
#include "include/aliases.h"

const float* CatDispatcher(int i)
{
  switch(i) {
    case Constants::CAT_CAT02:
      return cat02;
    case Constants::CAT_BRADFORD:
      return bradford;
    default:
      return matIdentity;
  }
}

const float* WhitepointDispatcher(int i)
{
  switch(i) {
    case Constants::WHITE_A:
      return white_A;
    case Constants::WHITE_B:
      return white_B;
    case Constants::WHITE_C:
      return white_C;
    case Constants::WHITE_D50:
      return white_D50;
    case Constants::WHITE_D55:
      return white_D55;
    case Constants::WHITE_D58:
      return white_d58;
    case Constants::WHITE_D65:
      return white_D65;
    case Constants::WHITE_D75:
      return white_D75;
    case Constants::WHITE_9300:
      return white_9300;
    case Constants::WHITE_E:
      return white_E;
    case Constants::WHITE_F2:
      return white_F7;
    case Constants::WHITE_F11:
      return white_F11;
    case Constants::WHITE_DCI_P3:
      return white_DCIP3;
    case Constants::WHITE_ACES:
      return white_ACES;
    default:
      return white_D65;
  }
}

const float* MatrixInDispatcher(int i)
{
  switch(i) {
    case Constants::COLOR_CIE_XYZ:
      return matSRGBToXYZ;
    case Constants::COLOR_CIE_YXY:
      return matSRGBToXYZ;
    case Constants::COLOR_LAB:
      return matSRGBToXYZ_B;
    case Constants::COLOR_CIE_LCH:
      return matSRGBToXYZ_B;
    default:
      return matIdentity;
  }
}

const float* MatrixOutDispatcher(int i)
{
  switch(i) {
    case Constants::COLOR_CIE_XYZ:
      return matXYZToSRGB;
    case Constants::COLOR_CIE_YXY:
      return matXYZToSRGB;
    case Constants::COLOR_LAB:
      return matXYZToSRGB_B;
    case Constants::COLOR_CIE_LCH:
      return matXYZToSRGB_B;
    default:
      return matIdentity;
  }
}

static TransformDispatcher TransformInDispatcher(int i)
{
  switch(i) {
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
    case Constants::COLOR_CIE_YXY:
      return &LinToCIEYxy;
    case Constants::COLOR_LAB:
      return &LinToCIELab;
    case Constants::COLOR_CIE_LCH:
      return &LinToCIELCh;
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
      return [](const RGBcolor& in) { return in; };  // lambda
    default:
      return [](const RGBcolor& in) { return in; };  // lambda
  }
}

static TransformDispatcher TransformOutDispatcher(int i)
{
  switch(i) {
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
    case Constants::COLOR_CIE_YXY:
      return &CIEYxyToLin;
    case Constants::COLOR_LAB:
      return &CIELabToLin;
    case Constants::COLOR_CIE_LCH:
      return &CIELChToLin;
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
      return [](const RGBcolor& in) { return in; };  // lambda
    default:
      return [](const RGBcolor& in) { return in; };  // lambda
  }
}

#endif  // DISPATCHER_H