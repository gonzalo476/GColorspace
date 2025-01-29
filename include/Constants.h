#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace Constants
{

  enum Colorspaces {
    COLOR_GAMMA_1_80,
    COLOR_GAMMA_2_20,
    COLOR_GAMMA_2_40,
    COLOR_GAMMA_2_60,
    COLOR_REC709,
    COLOR_SRGB,
    COLOR_CINEON,
    COLOR_LINEAR,
    COLOR_HSV,
    COLOR_HSL,
    COLOR_Y_PB_PR,
    COLOR_Y_CB_CR,
    COLOR_CIE_XYZ,
    COLOR_CIE_YXY,
    COLOR_LAB,
    COLOR_CIE_LCH,
    COLOR_PANALOG,
    COLOR_REDLOG,
    COLOR_VIPERLOG,
    COLOR_ALEXAV3LOGC,
    COLOR_PLOGLIN,
    COLOR_SLOG,
    COLOR_SLOG1,
    COLOR_SLOG2,
    COLOR_SLOG3,
    COLOR_CLOG,
    COLOR_LOG3G10,
    COLOR_LOG3G12,
    COLOR_HYBRID_LOG_GAMMA,
    COLOR_PROTUNE,
    COLOR_BT1886,
    COLOR_ST2084,
    COLOR_BLACKMAGIC_GEN5,
    COLOR_ARRI_LOG_C4,
    COLORSPACE_COUNT
  };

  enum Whitepoint {
    WHITE_A,
    WHITE_B,
    WHITE_C,
    WHITE_D50,
    WHITE_D55,
    WHITE_D58,
    WHITE_D65,
    WHITE_D75,
    WHITE_9300,
    WHITE_E,
    WHITE_F2,
    WHITE_F7,
    WHITE_F11,
    WHITE_DCI_P3,
    WHITE_ACES,
    WHITE_COUNT
  };

  enum PrimaryColorspaces {
    PRIM_COLOR_ADOBE_1998,
    PRIM_COLOR_APPLE,
    PRIM_COLOR_BEST_RGB,
    PRIM_COLOR_BETA_RGB,
    PRIM_COLOR_BRUCE_RGB,
    PRIM_COLOR_CIE_1931,
    PRIM_COLOR_COLORMATCH,
    PRIM_COLOR_DCI_P3,
    PRIM_COLOR_DON_RGB_4,
    PRIM_COLOR_ECI_RGB,
    PRIM_COLOR_EKTA_SPACE_PS5,
    PRIM_COLOR_NTSC_1953,
    PRIM_COLOR_PAL_SECAM,
    PRIM_COLOR_PROPHOTO,
    PRIM_COLOR_SMPTE_C,
    PRIM_COLOR_SRGB,
    PRIM_COLOR_WIDE_GAMUT,
    PRIM_COLOR_ALEXAV3LOGC,
    PRIM_COLOR_SONY_S_GAMUT,
    PRIM_COLOR_ACES,
    PRIM_COLOR_REC_2020,
    PRIM_COLOR_ARRI_WIDE_GAMUT4,
    PRIM_COLOR_COUNT
  };

  static const char* const COLOR_CURVE[] = {"gamma 1.80",
                                            "gamma 2.20",
                                            "gamma 2.40",
                                            "gamma 2.60",
                                            "rec709 (~1.95)",
                                            "sRGB (~2.20)",
                                            "Cineon",
                                            "Linear",
                                            "HSV",
                                            "HSL",
                                            "YPbPr",
                                            "YCbCr",
                                            "CIE-XYZ",
                                            "CIE-Yxy",
                                            "L*a*b*",
                                            "CIE-LCH",
                                            "Panalog",
                                            "REDLog",
                                            "ViperLog",
                                            "AlexaV3LogC",
                                            "PLogLin",
                                            "SLog",
                                            "SLog1",
                                            "SLog2",
                                            "SLog3",
                                            "CLog",
                                            "Log3G10",
                                            "Log3G12",
                                            "HybridLogGamma",
                                            "Protune",
                                            "BT1886",
                                            "st2084",
                                            "Blackmagic Film Generation 5",
                                            "ARRILogC4",
                                            0};

  static const char* const WHITEPOINT[] = {
      "A",    "B", "C",  "D50", "D55", "d58",    "D65",  "D75",
      "9300", "E", "F2", "F7",  "F11", "DCI-P3", "ACES", 0};

  static const char* const PRIMARY_RGB[] = {"Adobe (1998)",
                                            "Apple",
                                            "Best RGB",
                                            "Beta RGB",
                                            "Bruce RGB",
                                            "CIE (1931)",
                                            "ColorMatch",
                                            "DCI-P3",
                                            "Don RGB 4",
                                            "ECI RGB",
                                            "Ekta Space PS5",
                                            "NTSC (1953)",
                                            "PAL/SECAM",
                                            "ProPhoto",
                                            "SMPTE-C",
                                            "sRGB",
                                            "Wide Gamut",
                                            "AlexaV3LogC",
                                            "Sony S-Gamut",
                                            "ACES",
                                            "Rec.2020",
                                            "ARRI Wide Gamut 4",
                                            0};
}  // namespace Constants

#endif  // CONSTANTS_H