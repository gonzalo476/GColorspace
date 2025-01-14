#ifndef COLOR_VALUES_H
#define COLOR_VALUES_H

#include "include/Constants.h"

#include <cmath>
#include <unordered_map>


// whitepoints Values
const std::unordered_map<int, std::array<float, 3>> whitePoints = {
    {Constants::WHITE_A, {1.09850f, 1.00000f, 0.35585f}},
    {Constants::WHITE_D65, {0.95047f, 1.00000f, 1.08883f}},
    {Constants::WHITE_D50, {0.96422f, 1.00000f, 0.82521f}},
    {Constants::WHITE_E, {1.00000f, 1.00000f, 1.00000f}}
};

// Primary Values
const std::unordered_map<int, std::array<std::array<float, 2>, 3>> primarySpaces = {
    {Constants::PRIM_COLOR_SRGB, {{{0.640f, 0.330f}, {0.300f, 0.600f}, {0.150f, 0.060f}}}},
    {Constants::PRIM_COLOR_NTSC_1953, {{{0.67f, 0.33f}, {0.21f, 0.71f}, {0.14f, 0.08f}}}},
    {Constants::PRIM_COLOR_REC_2020, {{{0.708f, 0.292f}, {0.170f, 0.797f}, {0.131f, 0.046f}}}}
};

#endif // COLOR_VALUES_H