/* ***** BEGIN LICENSE BLOCK *****
 * (C) 2025 Gonzalo Rojas.
 *
 * GColorspace is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version.
 *
 * GColorspace is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with GColorspace. If not, see <http://www.gnu.org/licenses/gpl-2.0.html>.
 * ***** END LICENSE BLOCK *****
 */

/*
 * GColorspace provides support for color-space transformations in Nuke.
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