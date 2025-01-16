/*
  GColorspace Plugin for Nuke
  ------------------------------
  Copyright (c) 2025 Gonzalo Rojas
  This plugin is free to use, modify, and distribute.
  Provided "as is" without any warranty.
*/

#ifndef GCOLORSPACE_H
#define GCOLORSPACE_H

#include <DDImage/Channel.h>
#include <DDImage/PixelIop.h>
#include <DDImage/NukeWrapper.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>
#include <DDImage/Matrix3.h>
#include <DDImage/Convolve.h>

using namespace DD::Image;

class GColorspaceIop : public PixelIop
{
  int colorIn_index;
  int colorOut_index;
  int illumIn_index;
  int illumOut_index;
  int primaryIn_index;
  int primaryOut_index;
  bool use_bradford_matrix;
  Matrix3 colormatrix;
  ConvolveArray out_colormatrix;
public:
  static const char *modes[];

  GColorspaceIop(Node *node);

  ~GColorspaceIop() override;

  static const DD::Image::Op::Description description;

  const char *Class() const override;

  const char *displayName() const override;

  const char *node_help() const override;

  void knobs(Knob_Callback f) override;
  int knob_changed(Knob *k) override;

  void in_channels(int n, ChannelSet &mask) const override;

  void pixel_engine(
      const Row &in,
      int rowY, int rowX, int rowXBound,
      ChannelMask outputChannels,
      Row &out) override;

  void _validate(bool for_real) override;
};

static DD::Image::Op* build(Node *node);

#endif // GCOLORSPACE_H