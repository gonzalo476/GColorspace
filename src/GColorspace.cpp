/*
  GColorspace Plugin for Nuke
  ------------------------------
  Copyright (c) 2025 Gonzalo Rojas
  This plugin is free to use, modify, and distribute.
  Provided "as is" without any warranty.
*/

#include <array>

#include "include/GColorspace.h"
#include "include/Colorspaces.h"
#include "include/Constants.h"
#include "include/PrimaryColors.h"

#include <DDImage/Channel.h>
#include <DDImage/PixelIop.h>
#include <DDImage/NukeWrapper.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>

GColorspaceIop::GColorspaceIop(Node *n) : PixelIop(n)
{
    colorIn_index = Constants::COLOR_LINEAR;
    colorOut_index = Constants::COLOR_LINEAR;
    illumIn_index = Constants::WHITE_D65;
    illumOut_index = Constants::WHITE_D65;
    primaryIn_index = Constants::PRIM_COLOR_SRGB;
    primaryOut_index = Constants::PRIM_COLOR_SRGB;
    use_bradford_matrix = 0;
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

    Bool_knob(f, &use_bradford_matrix, "bradford_matrix", "Bradford matrix");
    SetFlags(f, Knob::STARTLINE);
}

int GColorspaceIop::knob_changed(Knob *k)
{
    if (k->is("colorspace_in") || k->is("colorspace_out") || k->is("bradford_matrix"))
    {
        Knob *k_colorspace_in = k->knob("colorspace_in");
        Knob *k_colorspace_out = k->knob("colorspace_out");
        Knob *k_primary_in = k->knob("primary_in");
        Knob *k_primary_out = k->knob("primary_out");
        Knob *k_illuminant_in = k->knob("illuminant_in");
        Knob *k_illuminant_out = k->knob("illuminant_out");

        auto cs_in_value = k_colorspace_in->get_value();
        auto cs_out_value = k_colorspace_out->get_value();

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

        if (cs_in_value == Constants::COLOR_LAB || cs_in_value == Constants::COLOR_CIE_LCH)
        {
            k_primary_in->disable();
            k_illuminant_in->enable();
        }

        if (cs_out_value == Constants::COLOR_LAB || cs_out_value == Constants::COLOR_CIE_LCH)
        {
            k_primary_out->disable();
            k_illuminant_out->enable();
        }

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

static inline std::array<float, 3> OutputColorspace(
    const std::array<float, 3> &inRGB,
    int colorOut_index,
    int use_bradford_matrix)
{
    std::array<float, 3> outRGB = {0.0f, 0.0f, 0.0f};
    switch (colorOut_index)
    {
    case Constants::COLOR_CIE_XYZ:
        outRGB = toCIEXyz(inRGB);
        break;
    case Constants::COLOR_LINEAR:
        outRGB = inRGB;
        break;
    default:
        break;
    }

    return outRGB;
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

        if (colorIn_index == colorOut_index)
        {
            while (rIn < END) {
                *rOut++ = *rIn++;
                *gOut++ = *gIn++;
                *bOut++ = *bIn++;  
            }
        }
        
        switch (colorIn_index)
        {
        case Constants::COLOR_CIE_XYZ:
            while (rIn < END)
            {
                std::array<float, 3> inRGB = {*rIn++, *gIn++, *bIn++};
                auto cieXYZ = fromCIEXyz(inRGB);
                auto outRGB = OutputColorspace(cieXYZ, colorOut_index, use_bradford_matrix);
                *rOut++ = outRGB[0];
                *gOut++ = outRGB[1];
                *bOut++ = outRGB[2];
            }
            break;

        case Constants::COLOR_LINEAR:
            while (rIn < END)
            {
                std::array<float, 3> inRGB = {*rIn++, *gIn++, *bIn++};
                auto outRGB = OutputColorspace(inRGB, colorOut_index, use_bradford_matrix);
                *rOut++ = outRGB[0];
                *gOut++ = outRGB[1];
                *bOut++ = outRGB[2];
            }
            break;

        default:
            break;
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