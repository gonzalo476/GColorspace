#ifndef COLOR_DATA_H
#define COLOR_DATA_H

#include "include/Constants.h"
#include "include/aliases.h"

#include <cmath>
#include <unordered_map>
#include <array>

const XYZMat sRGBToXYZ = {
    0.4124564f, 0.3575761f, 0.1804375f,
    0.2126729f, 0.7151522f, 0.0721750f,
    0.0193339f, 0.1191920f, 0.9503041f
};

#endif // COLOR_DATA_H