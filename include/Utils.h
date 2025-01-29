#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <array>
#include <unordered_set>

#include "include/Constants.h"
#include "include/aliases.h"

bool isInXYZMatrix(double cs)
{
  static const std::unordered_set<ColorLut> colors = {
      ColorLut::COLOR_CIE_XYZ, ColorLut::COLOR_CIE_YXY, ColorLut::COLOR_LAB,
      ColorLut::COLOR_CIE_LCH};

  return std::find(colors.begin(), colors.end(), cs) != colors.end();
}

#endif  // UTILS_H