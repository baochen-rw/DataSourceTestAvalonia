// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_COMPOSITION_BRUSH_RENDERER_HPP
#define KZ_SPANSION_COMPOSITION_BRUSH_RENDERER_HPP


#include "spansion_brush_renderer.hpp"


namespace kanzi
{


class SpansionCompositionBrushRenderer : public SpansionBrushRenderer
{
public:
    static BrushRendererPtr create(Brush* brush, Node* node);

protected:
    explicit SpansionCompositionBrushRenderer(Brush* brush, Node* node) :
        SpansionBrushRenderer(brush, node)
    {
    }
};


}


#endif
