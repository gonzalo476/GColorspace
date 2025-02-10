/* MIT License
 * Copyright (c) 2025 Gonzalo Rojas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 * GColorspace provides support for color-space transformations for Nuke

 */

#include "include/GColorspace.h"

#include <DDImage/ArrayKnobI.h>
#include <DDImage/Channel.h>
#include <DDImage/Enumeration_KnobI.h>
#include <DDImage/Knobs.h>
#include <DDImage/Matrix3.h>
#include <DDImage/NukeWrapper.h>
#include <DDImage/PixelIop.h>
#include <DDImage/Row.h>

#include <stdexcept>

#include "include/ColorData.h"
#include "include/Constants.h"
#include "include/DebugTools.h"
#include "include/Dispatcher.h"
#include "include/Utils.h"
#include "include/Whitepoint.h"
#include "include/aliases.h"

static float _defaultMatValues[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f};

GColorspaceIop::GColorspaceIop(Node* n) : PixelIop(n)
{
  colorIn_index = Constants::COLOR_LINEAR;
  colorOut_index = Constants::COLOR_LINEAR;
  whiteIn_index = Constants::WHITE_D65;
  whiteOut_index = Constants::WHITE_D65;
  primaryIn_index = Constants::PRIM_COLOR_SRGB;
  primaryOut_index = Constants::PRIM_COLOR_SRGB;
  use_bradford_matrix = 0;
  currentMatrix.makeIdentity();
  colormatrix.set(3, 3, _defaultMatValues);
}

GColorspaceIop::~GColorspaceIop()
{
}

void GColorspaceIop::knobs(Knob_Callback f)
{
  Enumeration_knob(f, &colorIn_index, Constants::COLOR_CURVE, "colorspace_in",
                   "in");
  Enumeration_knob(f, &whiteIn_index, Constants::WHITEPOINT, "illuminant_in",
                   "");
  Tooltip(f, "The whitepoint taken as a reference.");
  Enumeration_knob(f, &primaryIn_index, Constants::PRIMARY_RGB, "primary_in",
                   "");
  Tooltip(f, "Defines how RGB values are mapped to CIEXYZ.");
  ClearFlags(f, Knob::STARTLINE);

  Enumeration_knob(f, &colorOut_index, Constants::COLOR_CURVE, "colorspace_out",
                   "out");
  Enumeration_knob(f, &whiteOut_index, Constants::WHITEPOINT, "illuminant_out",
                   "");
  Enumeration_knob(f, &primaryOut_index, Constants::PRIMARY_RGB, "primary_out",
                   "");
  ClearFlags(f, Knob::STARTLINE);

  Button(f, "swap", "swap in/out");
  SetFlags(f, Knob::STARTLINE);
  Bool_knob(f, &use_bradford_matrix, "bradford_matrix", "Bradford matrix");

  Divider(f, "color matrix output");
  Array_knob(f, &colormatrix, colormatrix.width, colormatrix.height,
             "colormatrix", "");
  SetFlags(f, Knob::DISABLED | Knob::OUTPUT_ONLY);
}

void GColorspaceIop::setColorMatrix()
{
  // Values
  const int inColorspaceValue = knob("colorspace_in")->get_value();
  const int outColorspaceValue = knob("colorspace_out")->get_value();
  const int inWhiteValue = knob("illuminant_in")->get_value();
  const int outWhiteValue = knob("illuminant_out")->get_value();
  const int inPrimaryValue = knob("primary_in")->get_value();
  const int outPrimaryValue = knob("primary_out")->get_value();

  // Dispatchers
  const float* inXyzMat = MatrixInDispatcher(inColorspaceValue);
  const float* outXyzMat = MatrixOutDispatcher(outColorspaceValue);
  const float* srcWhite = WhitepointDispatcher(Constants::WHITE_D65);
  const float* dstWhite = WhitepointDispatcher(whiteIn_index);
  const float* catMat = CatDispatcher(use_bradford_matrix);
  Matrix3 whiteMtx = calcWhite(srcWhite, dstWhite, catMat);
  // knob("colormatrix")->set_values(mtx.array(), 9);

  if(inColorspaceValue != outColorspaceValue || inWhiteValue != outWhiteValue ||
     inPrimaryValue != outPrimaryValue) {
    knob("colormatrix")->set_values(whiteMtx.array(), 9);
    knob("colormatrix")->enable();
  }
  else if(isInXYZMatrix(inColorspaceValue) &&
          !isInXYZMatrix(outColorspaceValue)) {
    knob("colormatrix")->set_values(inXyzMat, 9);
    knob("colormatrix")->enable();
  }
  else if(isInXYZMatrix(outColorspaceValue) &&
          !isInXYZMatrix(inColorspaceValue)) {
    knob("colormatrix")->set_values(outXyzMat, 9);
    knob("colormatrix")->enable();
  }
  else if(isInXYZMatrix(inColorspaceValue) &&
          outColorspaceValue == Constants::COLOR_CIE_YXY) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->disable();
  }
  else if(isInXYZMatrix(outColorspaceValue) &&
          inColorspaceValue == Constants::COLOR_CIE_YXY) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->disable();
  }
  else if(isInXYZMatrix(inColorspaceValue) &&
          outColorspaceValue == Constants::COLOR_CIE_LCH) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->disable();
  }
  else if(isInXYZMatrix(outColorspaceValue) &&
          inColorspaceValue == Constants::COLOR_CIE_LCH) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->disable();
  }
  else if(isInXYZMatrix(inColorspaceValue) &&
          outColorspaceValue == Constants::COLOR_LAB) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->enable();
  }
  else if(isInXYZMatrix(outColorspaceValue) &&
          inColorspaceValue == Constants::COLOR_LAB) {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->enable();
  }
  else {
    knob("colormatrix")->set_values(matIdentity, 9);
    knob("colormatrix")->disable();
  }
}

int GColorspaceIop::knob_changed(Knob* k)
{
  if(k->is("colorspace_in") || k->is("colorspace_out") ||
     k->is("bradford_matrix") || k->is("primary_in") || k->is("primary_out") ||
     k->is("illuminant_in") || k->is("illuminant_out")) {
    Knob* k_colorspace_in = knob("colorspace_in");
    Knob* k_colorspace_out = knob("colorspace_out");
    Knob* k_primary_in = knob("primary_in");
    Knob* k_primary_out = knob("primary_out");
    Knob* k_white_in = knob("illuminant_in");
    Knob* k_white_out = knob("illuminant_out");
    Knob* k_colormatrix = knob("colormatrix");

    const int inColorspaceValue = k_colorspace_in->get_value();
    const int outColorspaceValue = k_colorspace_out->get_value();
    const int inPrimaryValue = k_primary_in->get_value();
    const int outPrimaryValue = k_primary_out->get_value();
    const int inIlluminantValue = k_white_in->get_value();
    const int outIlluminantValue = k_white_out->get_value();

    const bool inColorspaceError =
        (k_colorspace_in->enumerationKnob()->getError() != nullptr);
    const bool outColorspaceError =
        (k_colorspace_out->enumerationKnob()->getError() != nullptr);
    const bool inPrimaryError =
        (k_primary_in->enumerationKnob()->getError() != nullptr);
    const bool outPrimaryError =
        (k_primary_out->enumerationKnob()->getError() != nullptr);
    const bool inWhiteError =
        (k_white_in->enumerationKnob()->getError() != nullptr);
    const bool outWhiteError =
        (k_white_out->enumerationKnob()->getError() != nullptr);

    if(!inColorspaceError && !outColorspaceError && !inPrimaryError &&
       !outPrimaryError && !inWhiteError && !outWhiteError) {
      // Set Color Matrix
      setColorMatrix();

      // in colorspace validation state
      if(inColorspaceValue == Constants::COLOR_CIE_XYZ ||
         inColorspaceValue == Constants::COLOR_CIE_YXY) {
        if(use_bradford_matrix == 0) {
          k_primary_in->disable();
          k_white_in->disable();
        }
        else {
          k_primary_in->disable();
          k_white_in->enable();
        }
      }
      else {
        k_primary_in->enable();
        k_white_in->enable();
      }

      // out colorspace validation state
      if(outColorspaceValue == Constants::COLOR_CIE_XYZ ||
         outColorspaceValue == Constants::COLOR_CIE_YXY) {
        if(use_bradford_matrix == 0) {
          k_primary_out->disable();
          k_white_out->disable();
        }
        else {
          k_primary_out->disable();
          k_white_out->enable();
        }
      }
      else {
        k_primary_out->enable();
        k_white_out->enable();
      }

      // Validate In when the value is Lab space or Cie LCH
      if(inColorspaceValue == Constants::COLOR_LAB ||
         inColorspaceValue == Constants::COLOR_CIE_LCH) {
        k_primary_in->disable();
        k_white_in->enable();
      }

      // Validate Out when the value is Lab space or Cie LCH
      if(outColorspaceValue == Constants::COLOR_LAB ||
         outColorspaceValue == Constants::COLOR_CIE_LCH) {
        k_primary_out->disable();
        k_white_out->enable();
      }
    }
  }

  if(k->is("swap")) {
    const bool inColorspaceError =
        (knob("colorspace_in")->enumerationKnob()->getError() != nullptr);
    const bool outColorspaceError =
        (knob("colorspace_out")->enumerationKnob()->getError() != nullptr);

    if(!inColorspaceError && !outColorspaceError) {
      const int inColorspaceValue = knob("colorspace_in")->get_value();
      const int outColorspaceValue = knob("colorspace_out")->get_value();
      const float* xyzMat = MatrixInDispatcher(inColorspaceValue);

      knob("colorspace_in")->set_value(outColorspaceValue);
      knob("colorspace_out")->set_value(inColorspaceValue);

      setColorMatrix();
    }
  }

  return 1;
}

void GColorspaceIop::_validate(bool for_real)
{
  set_out_channels(Mask_All);
  PixelIop::_validate(for_real);
}

void GColorspaceIop::in_channels(int, ChannelSet& mask) const
{
  ChannelSet done;
  foreach(c, mask) {
    const bool isRGB = colourIndex(c) < 3;
    if(isRGB) {
      const bool have = done & c;
      if(!have) {
        // because the colour conversion needs R, G *and* B from any
        // layer-channel-set, expand the channels list to include the
        // other corresponding R, G or B channels for that. i.e. if
        // 'mask' has a layer 'CustomLayer' and only contain has R & G,
        // after this call it will also contain B
        done.addBrothers(c, 3);
      }
    }
  }
  mask += done;
}

RGBcolor GColorspaceIop::ToInColorspace(const RGBcolor& p)
{
  // Dispatchers
  auto TransformIn = TransformInDispatcher(colorIn_index);
  const float* srcWhite = WhitepointDispatcher(Constants::WHITE_D65);
  const float* dstWhite = WhitepointDispatcher(whiteIn_index);
  const float* catMat = CatDispatcher(use_bradford_matrix);

  Matrix3 mtx = calcWhite(srcWhite, dstWhite, catMat);

  auto rgb = TransformIn(p);

  // rgb to CIE XYZ
  auto toWhitepoint = toXYZMat(mtx.array(), rgb);
  // CIE XYZ to rgb

  return toWhitepoint;
}

RGBcolor GColorspaceIop::ToOutColorspace(const RGBcolor& p)
{
  auto TransformOut = TransformOutDispatcher(colorOut_index);
  auto rgb = TransformOut(p);

  return rgb;
}

void GColorspaceIop::pixel_engine(const Row& in, int rowY, int rowX,
                                  int rowXBound, ChannelMask outputChannels,
                                  Row& out)
{
  int rowWidth = rowXBound - rowX;

  ChannelSet done;

  foreach(z, outputChannels) {
    if(done & z) {
      continue;
    }

    if(colourIndex(z) >= 3) {
      out.copy(in, z, rowX, rowXBound);
      continue;
    }

    Channel rChannel = brother(z, 0);
    Channel gChannel = brother(z, 1);
    Channel bChannel = brother(z, 2);

    done += rChannel;
    done += gChannel;
    done += bChannel;

    const float* rIn = in[rChannel] + rowX;
    const float* gIn = in[gChannel] + rowX;
    const float* bIn = in[bChannel] + rowX;

    float* rOut = out.writable(rChannel) + rowX;
    float* gOut = out.writable(gChannel) + rowX;
    float* bOut = out.writable(bChannel) + rowX;

    if(rOut != rIn) memcpy(rOut, rIn, sizeof(float) * rowWidth);
    if(gOut != gIn) memcpy(gOut, gIn, sizeof(float) * rowWidth);
    if(bOut != bIn) memcpy(bOut, bIn, sizeof(float) * rowWidth);

    const float* END = rIn + (rowXBound - rowX);

    // if the colorspace matches the output, simply output the entire image
    if(colorIn_index == colorOut_index && whiteIn_index == whiteOut_index &&
       primaryIn_index == primaryOut_index) {
      continue;
    }

    while(rIn < END) {
      RGBcolor RGB = {*rIn++, *gIn++, *bIn++};

      auto colorspaceIn = ToInColorspace(RGB);
      auto colorspaceOut = ToOutColorspace(colorspaceIn);

      auto filteredRGB = removeExp(colorspaceOut);

      *rOut++ = filteredRGB[0];
      *gOut++ = filteredRGB[1];
      *bOut++ = filteredRGB[2];
    }
  }
}

const Op::Description GColorspaceIop::description("GColorspace", build);

const char* GColorspaceIop::Class() const
{
  return description.name;
}

const char* GColorspaceIop::displayName() const
{
  return description.name;
}

const char* GColorspaceIop::node_help() const
{
  return "GColorspace v1.0";
}

Op* build(Node* node)
{
  NukeWrapper* op = new NukeWrapper(new GColorspaceIop(node));
  op->channels(Mask_RGB);
  return op;
}