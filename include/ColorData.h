#ifndef COLOR_DATA_H
#define COLOR_DATA_H

const float matIdentity[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};

const float matXYZToSRGB[] = {0.41241086f, 0.35758454f, 0.18045381f,
                              0.21264936f, 0.71516907f, 0.07218152f,
                              0.01933176f, 0.1191948f,  0.95038998f};

const float matSRGBToXYZ[] = {3.24081278f,  -1.53730845f, -0.49858657f,
                              -0.96924323f, 1.87596655f,  0.04155507f,
                              0.05563836f,  -0.20400739f, 1.05712962f};

#endif  // COLOR_DATA_H