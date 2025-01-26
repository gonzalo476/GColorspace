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

    TODO: Dispatcher para el colormatrix

 */


#include "include/GColorspace.h"
#include "include/Constants.h"
#include "include/Dispatcher.h"
#include "include/Utils.h"
#include "include/aliases.h"
#include "include/ColorData.h"

#include <DDImage/Channel.h>
#include <DDImage/PixelIop.h>
#include <DDImage/NukeWrapper.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>
#include <array>

GColorspaceIop::GColorspaceIop(Node *n) : PixelIop(n)
{
    colorIn_index = Constants::COLOR_LINEAR;
    colorOut_index = Constants::COLOR_LINEAR;
    illumIn_index = Constants::WHITE_D65;
    illumOut_index = Constants::WHITE_D65;
    primaryIn_index = Constants::PRIM_COLOR_SRGB;
    primaryOut_index = Constants::PRIM_COLOR_SRGB;
    use_bradford_matrix = 0;
    outMat = matIdentity;
}

GColorspaceIop::~GColorspaceIop()
{
}

void GColorspaceIop::knobs(Knob_Callback f)
{
    Enumeration_knob(f, &colorIn_index, Constants::COLOR_CURVE, "colorspace_in", "in");
    Enumeration_knob(f, &illumIn_index, Constants::WHITEPOINT, "illuminant_in", "");
    Tooltip(f, "The whitepoint taken as a reference.");
    Enumeration_knob(f, &primaryIn_index, Constants::PRIMARY_RGB, "primary_in", "");
    Tooltip(f, "Defines how RGB values are mapped to CIEXYZ.");
    ClearFlags(f, Knob::STARTLINE);

    Enumeration_knob(f, &colorOut_index, Constants::COLOR_CURVE, "colorspace_out", "out");
    Enumeration_knob(f, &illumOut_index, Constants::WHITEPOINT, "illuminant_out", "");
    Enumeration_knob(f, &primaryOut_index, Constants::PRIMARY_RGB, "primary_out", "");
    ClearFlags(f, Knob::STARTLINE);

    Button(f, "swap", "swap in/out");
    SetFlags(f, Knob::STARTLINE);
    Bool_knob(f, &use_bradford_matrix, "bradford_matrix", "Bradford matrix");

    Divider(f, "color matrix output");
    Knob *MatKnob = Array_knob(f, &colormatrix, 3, 3, "colormatrix", "");
    MatKnob->set_values(outMat.data(), outMat.size());
    SetFlags(f, Knob::DISABLED);
}

int GColorspaceIop::knob_changed(Knob *k)
{
    if (k->is("colorspace_in") 
        || k->is("colorspace_out") 
        || k->is("bradford_matrix")
        || k->is("primary_in")
        || k->is("primary_out")
        || k->is("illuminant_in")
        || k->is("illuminant_out")
    )
    {
        Knob *k_colorspace_in = k->knob("colorspace_in");
        Knob *k_colorspace_out = k->knob("colorspace_out");
        Knob *k_primary_in = k->knob("primary_in");
        Knob *k_primary_out = k->knob("primary_out");
        Knob *k_illuminant_in = k->knob("illuminant_in");
        Knob *k_illuminant_out = k->knob("illuminant_out");
        Knob *k_colormatrix = k->knob("colormatrix");

        XYZMat matIn = MatrixInDispatcher(colorIn_index);
        k_colormatrix->set_values(matIn.data(), matIn.size());

        auto cs_in_value = k_colorspace_in->get_value();
        auto cs_out_value = k_colorspace_out->get_value();
        auto prim_in_value = k_primary_in->get_value();
        auto prim_out_value = k_primary_out->get_value();
        auto illum_in_value = k_illuminant_in->get_value();
        auto illum_out_value = k_illuminant_out->get_value();

        // Validate matrix
        if (
            isInXYZMatrix(cs_in_value) 
            || isInXYZMatrix(cs_out_value)
            || prim_in_value != prim_out_value
            || prim_out_value != prim_in_value
            || illum_in_value != illum_out_value
            || illum_out_value != illum_in_value
        )
        {
            k_colormatrix->enable();
        }
        else
        {
            k_colormatrix->disable();
            k_colormatrix->set_values(matIdentity.data(), matIdentity.size());
        }

        // Colorspace In validation knobs
        if (cs_in_value == Constants::COLOR_CIE_XYZ || cs_in_value == Constants::COLOR_CIE_YXY)
        {
            if (use_bradford_matrix == 0)
            {
                k_primary_in->disable();
                k_illuminant_in->disable();
            }
            else
            {
                k_primary_in->disable();
                k_illuminant_in->enable();
            }
        }
        else
        {
            k_primary_in->enable();
            k_illuminant_in->enable();
        }

        // Colorspace Out validation knobs
        if (cs_out_value == Constants::COLOR_CIE_XYZ || cs_out_value == Constants::COLOR_CIE_YXY)
        {
            if (use_bradford_matrix == 0)
            {
                k_primary_out->disable();
                k_illuminant_out->disable();
            }
            else
            {
                k_primary_out->disable();
                k_illuminant_out->enable();
            }
        }
        else
        {
            k_primary_out->enable();
            k_illuminant_out->enable();
        }

        // Validate In when the value is Lab space or Cie LCH
        if (cs_in_value == Constants::COLOR_LAB || cs_in_value == Constants::COLOR_CIE_LCH)
        {
            k_primary_in->disable();
            k_illuminant_in->enable();
        }

        // Validate Out when the value is Lab space or Cie LCH
        if (cs_out_value == Constants::COLOR_LAB || cs_out_value == Constants::COLOR_CIE_LCH)
        {
            k_primary_out->disable();
            k_illuminant_out->enable();
        }

        return 1;
    }

    if (k->is("swap"))
    {
        Knob *k_colorspace_in = k->knob("colorspace_in");
        Knob *k_colorspace_out = k->knob("colorspace_out");
        auto cs_in_value = k_colorspace_in->get_value();
        auto cs_out_value = k_colorspace_out->get_value();

        k_colorspace_in->set_value(cs_out_value);
        k_colorspace_out->set_value(cs_in_value);

        return 1;
    }
    
    return 0;
}

void GColorspaceIop::_validate(bool for_real)
{
    copy_info(0);
    set_out_channels(Mask_RGB);
}

void GColorspaceIop::in_channels(int, ChannelSet &mask) const
{
    ChannelSet done;
    foreach (c, mask)
    {
        if (colourIndex(c) < 3 && !(done & c))
        {
            done.addBrothers(c, 3);
        }
    }
    mask += done;
}

void GColorspaceIop::pixel_engine(
    const Row &in,
    int rowY,
    int rowX,
    int rowXBound,
    ChannelMask outputChannels,
    Row &out)
{
    int rowWidth = rowXBound - rowX;

    ChannelSet done;

    foreach (z, outputChannels)
    {
        // Dispatchers
        auto TransformIn = TransformInDispatcher(colorIn_index);
        auto TransformOut = TransformOutDispatcher(colorOut_index);

        if (done & z)
        {
            continue;
        }

        if (colourIndex(z) >= 3)
        {
            out.copy(in, z, rowX, rowXBound);
            continue;
        }

        Channel rChannel = brother(z, 0);
        Channel gChannel = brother(z, 1);
        Channel bChannel = brother(z, 2);

        done += rChannel;
        done += gChannel;
        done += bChannel;

        const float *rIn = in[rChannel] + rowX;
        const float *gIn = in[gChannel] + rowX;
        const float *bIn = in[bChannel] + rowX;

        float *rOut = out.writable(rChannel) + rowX;
        float *gOut = out.writable(gChannel) + rowX;
        float *bOut = out.writable(bChannel) + rowX;

        if (rOut != rIn)
            memcpy(rOut, rIn, sizeof(float) * rowWidth);
        if (gOut != gIn)
            memcpy(gOut, gIn, sizeof(float) * rowWidth);
        if (bOut != bIn)
            memcpy(bOut, bIn, sizeof(float) * rowWidth);

        const float *END = rIn + (rowXBound - rowX);

        // if the colorspace matches the output, simply output the entire image
        if (colorIn_index == colorOut_index && 
            illumIn_index == illumOut_index && 
            primaryIn_index == primaryOut_index)
        {
           continue;
        }

        while (rIn < END)
        {
            RGBcolor RGB = {*rIn++, *gIn++, *bIn++};

            auto RGBToLin = TransformIn(RGB);
            auto LinToRGB = TransformOut(RGBToLin);

            *rOut++ = LinToRGB[0];
            *gOut++ = LinToRGB[1];
            *bOut++ = LinToRGB[2];
        }
    }
}

const Op::Description GColorspaceIop::description("GColorspace", build);

const char *GColorspaceIop::Class() const
{
    return description.name;
}

const char *GColorspaceIop::displayName() const
{
    return description.name;
}

const char *GColorspaceIop::node_help() const
{
    return "GColorspace v1.0";
}

Op *build(Node *node)
{
    NukeWrapper *op = new NukeWrapper(new GColorspaceIop(node));
    op->channels(Mask_RGB);
    return op;
}