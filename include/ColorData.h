#ifndef COLOR_DATA_H
#define COLOR_DATA_H

// Nuke XYZ chromatic adaptation matrices
const float matIdentity[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};

const float matXYZToSRGB[] = {0.41241086f, 0.35758454f, 0.18045381f,
                              0.21264936f, 0.71516907f, 0.07218152f,
                              0.01933176f, 0.1191948f,  0.95038998f};

const float matSRGBToXYZ[] = {3.24081278f,  -1.53730845f, -0.49858657f,
                              -0.96924323f, 1.87596655f,  0.04155507f,
                              0.05563836f,  -0.20400739f, 1.05712962f};

const float matXYZToSRGB_B[] = {0.4339115f,  0.37622687f, 0.1898616f,
                                0.21264936f, 0.71516907f, 0.07218152f,
                                0.01775321f, 0.10946182f, 0.87278491f};

const float matSRGBToXYZ_B[] = {3.08022809f,  -1.53730845f, -0.54291916f,
                                -0.92121649f, 1.87596655f,  0.04525001f,
                                0.05288144f,  -0.20400739f, 1.15112591f};

// CIE 1931 2deg
const float white_A[] = {0.44757f, 0.40745f};
const float white_B[] = {0.34842f, 0.35161f};
const float white_C[] = {0.31006f, 0.31616f};
const float white_D50[] = {0.34567f, 0.35850f};
const float white_D55[] = {0.33242f, 0.34743f};
const float white_d58[] = {0.32577f, 0.34152f};
const float white_D65[] = {0.31271f, 0.32902f};
const float white_D75[] = {0.29902f, 0.31485f};
const float white_9300[] = {0.28329f, 0.29640f};
const float white_E[] = {1.f / 3.f, 1.f / 3.f};
const float white_F2[] = {0.37208f, 0.37529f};
const float white_F7[] = {0.31292f, 0.32933f};
const float white_F11[] = {0.38052f, 0.37713f};
const float white_DCIP3[] = {0.31400f, 0.35100f};
const float white_ACES[] = {0.32168f, 0.33767f};

// Cone Response Matrices
const float cat02[] = {0.7328f, 0.4296f, -0.1624f, -0.7036f, 1.6975f,
                       0.0061f, 0.003f,  0.0136f,  0.9834f};
const float bradford[] = {0.8951f, 0.2664f, -0.1614f, -0.7502f, 1.7135f,
                          0.0367f, 0.0389f, -0.0685f, 1.0296f};

#endif  // COLOR_DATA_H