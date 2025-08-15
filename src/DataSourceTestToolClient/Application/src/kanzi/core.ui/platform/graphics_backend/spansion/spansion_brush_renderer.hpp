// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_BRUSH_RENDERER_HPP
#define KZ_SPANSION_BRUSH_RENDERER_HPP


#include "brush_renderer.hpp"

#include <kanzi/graphics_backend/render_state_property_notification_handler.hpp>


namespace kanzi
{


class SpansionBrushRenderer : public BrushRenderer
{
public:

    static BrushRendererPtr create(Brush* brush, Node* node);

    virtual void bindOverride(Renderer3D& renderer) KZ_OVERRIDE;

    virtual void updateRenderOverride(bool forceOpaque, bool translucencyHint) KZ_OVERRIDE;


    virtual void restoreResourcesOverride() KZ_OVERRIDE
    {
    }

protected:

    explicit SpansionBrushRenderer(Brush* brush, Node* node):
        BrushRenderer(brush, node)
    {
    }

    virtual void drawOverride(Renderer3D& renderer, const Geometry& geometry, const Matrix4x4& transform) const KZ_OVERRIDE;

    RenderStatePropertyNotificationHandler m_blendModeProperty;

    RenderStatePropertyNotificationHandler m_colorProperty;
};


}


#endif
