/* MIT License
 * Copyright (c) 2025 Gonzalo Rojas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * GColorspace provides support for color-space transformations for Nuke
 */

#ifndef GCOLORSPACE_H
#define GCOLORSPACE_H

#include "include/aliases.h"

#include <DDImage/Channel.h>
#include <DDImage/Convolve.h>
#include <DDImage/Knobs.h>
#include <DDImage/NukeWrapper.h>
#include <DDImage/PixelIop.h>
#include <DDImage/Row.h>


using namespace DD::Image;

class GColorspaceIop : public PixelIop {
  int colorIn_index;
  int colorOut_index;
  int illumIn_index;
  int illumOut_index;
  int primaryIn_index;
  int primaryOut_index;
  bool use_bradford_matrix;
  ConvolveArray colormatrix;

 public:
  static const char* modes[];

  GColorspaceIop(Node* node);

  ~GColorspaceIop() override;

  static const DD::Image::Op::Description description;

  const char* Class() const override;

  const char* displayName() const override;

  const char* node_help() const override;

  void knobs(Knob_Callback f) override;

  int knob_changed(Knob* k) override;

  void in_channels(int n, ChannelSet& mask) const override;

  void pixel_engine(const Row& in, int rowY, int rowX, int rowXBound, ChannelMask outputChannels,
                    Row& out) override;

  void _validate(bool for_real) override;

  void setColorMatrix();
};

static DD::Image::Op* build(Node* node);

#endif  // GCOLORSPACE_H