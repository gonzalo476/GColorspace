#ifndef WHITEPOINT_H
#define WHITEPOINT_H

#include <DDImage/DDMath.h>
#include <DDImage/Matrix3.h>
#include <DDImage/Vector3.h>

#include <algorithm>
#include <array>
#include <cmath>

#include "include/ColorData.h"
#include "include/aliases.h"

Matrix3 transpose(Matrix3 m)
{
  return Matrix3(m.array()[0], m.array()[1], m.array()[2], m.array()[3],
                 m.array()[4], m.array()[5], m.array()[6], m.array()[7],
                 m.array()[8]);
}

Matrix3 setMatrix(const float* m)
{
  return Matrix3(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]);
}

Matrix3 diag(Vector3 v)
{
  return Matrix3(v[0], 0.0f, 0.0f, 0.0f, v[1], 0.0f, 0.0f, 0.0f, v[2]);
}

Vector3 xyY_to_XYZ(const float* xyY)
{
  Vector3 XYZ;
  float x = xyY[0];
  float y = xyY[1];
  float Y = 0.0f;
  size_t xyYSize = sizeof(xyY) / sizeof(xyY[0]);

  if(xyYSize == 2) {
    Y = 1.0f;
  }
  else {
    Y = xyY[2];
  }

  XYZ.set(x * Y / MAX(y, 1e-10f), Y, (1.0f - x - y) * Y / MAX(y, 1e-10f));

  return XYZ;
}

Matrix3 calcWhite(const float* srcWhite, const float* dstWhite,
                  const float* catMat)
{
  Matrix3 crmtx;
  Vector3 srcXYZ;
  Vector3 dstXYZ;
  Vector3 srcCrmtx;
  Vector3 dstCrmtx;
  Matrix3 vonKriesMatrix;
  Matrix3 catMatrix;

  if(catMat == nullptr) {
    catMatrix.makeIdentity();
    return catMatrix;
  }

  crmtx = setMatrix(catMat);

  // Get XYZ values from xy chromaticity coords
  srcXYZ = xyY_to_XYZ(srcWhite);
  dstXYZ = xyY_to_XYZ(dstWhite);

  // Calculate source and destination cone response matrices
  srcCrmtx = transpose(crmtx) * srcXYZ;
  dstCrmtx = transpose(crmtx) * dstXYZ;

  vonKriesMatrix = diag(dstCrmtx / srcCrmtx);

  catMatrix = crmtx * (vonKriesMatrix * crmtx.inverse());

  return catMatrix;
}

#endif  // WHITEPOINT_H