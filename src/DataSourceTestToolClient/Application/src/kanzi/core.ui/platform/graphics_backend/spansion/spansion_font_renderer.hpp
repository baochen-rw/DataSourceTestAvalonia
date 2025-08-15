// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDERING_SPANSION_FONT_RENDERER_HPP
#define KZ_RENDERING_SPANSION_FONT_RENDERER_HPP

#include <kanzi/graphics_backend/renderer3d.hpp>

#include <system/kzs_types.h>
#include <kanzi/math/color_rgba.hpp>
#include <kanzi/math/matrix4x4.hpp>
#include <kanzi/math/rectangle.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


struct KzuTextLayout;

namespace kanzi
{

class Texture;

/// Spansion 2D accelerated helper function for Freetype font rendering.
void drawSpansionOffscreenBuffer(Renderer3D& renderer, Texture* texture,
                                 ColorRGBA color,
                                 const FT_Face face,
                                 const KzuTextLayout* textLayout,
                                 const kzFloat offsetX,
                                 const kzFloat offsetY,
                                 const Matrix4x4* transform,
                                 const Rectangle<float>* clipRect);
}

#endif
