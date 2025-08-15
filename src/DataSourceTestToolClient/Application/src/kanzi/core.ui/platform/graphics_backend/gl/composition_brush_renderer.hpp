// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_COMPOSITION_BRUSH_RENDERER_HPP
#define KZ_GL_COMPOSITION_BRUSH_RENDERER_HPP


#include "content_brush_renderer.hpp"


namespace kanzi
{


/// OpenGL texture brush renderer class.
class CompositionBrushRenderer : public ContentBrushRenderer
{
public:

    /// Create a new composition brush renderer.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    static BrushRendererPtr create(Brush* brush, Node* node);

protected:

    /// Constructor.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    explicit CompositionBrushRenderer(Brush* brush, Node* node) :
             ContentBrushRenderer(brush, node) {}
};


}


#endif
