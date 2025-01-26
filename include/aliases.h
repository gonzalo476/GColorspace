#ifndef ALIASES_H
#define ALIASES_H

#include "include/Constants.h"
#include <array>

using ColorLut = Constants::Colorspaces;
using RGBcolor = std::array<float, 3>;
using XYZMat = std::array<float, 9>;

#endif // ALIASES_H