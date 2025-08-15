// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_WATERMARK_HPP
#define KZ_WATERMARK_HPP

#ifndef SPANSION
#if 1 /* Set to 1 to enable watermark. The watermark is actually shown or not based on the Kanzi Studio license that was used when creating .KZB files. */
#define KZU_ENGINE_ENABLE_WATERMARK /**< Enables the watermark. */
#endif
#endif

#ifdef KZU_ENGINE_ENABLE_WATERMARK

#include <kanzi/core.ui/graphics2d/brush.hpp>
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>

namespace kanzi
{


// Forward declarations.
class Domain;
class Renderer;
class GraphicsOutput;
class Watermark;

/// Watermark
///
/// Rendered on top of 
class Watermark
{
public:
    /// Constructor.
    ///
    /// \param domain Domain to acquire resources from.
    explicit Watermark(Domain* domain);

    /// Render the watermark.
    ///
    /// \param renderer Renderer to use.
    /// \param graphicsOutput Graphics output to use.
    void render(Renderer3D& renderer, const GraphicsOutput& graphicsOutput);

private:
    /// Texture created from image.
    TextureSharedPtr m_texture;

    /// Brush.
    BrushSharedPtr m_brush;

    /// Brush renderer.
    BrushRendererPtr m_brushRenderer;
};


} // namespace kanzi 


#endif

#endif