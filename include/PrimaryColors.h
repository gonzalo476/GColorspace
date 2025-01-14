#ifndef PRIMARYCOLORS_H
#define PRIMARYCOLORS_H

#include "include/Constants.h"

#include <cmath>
#include <unordered_map>

struct WhitePoint {
    float x, y, z;
};

struct Primaries {
    float rX, rY;
    float gX, gY;
    float bX, bY;
};

#endif // PRIMARYCOLORS_H