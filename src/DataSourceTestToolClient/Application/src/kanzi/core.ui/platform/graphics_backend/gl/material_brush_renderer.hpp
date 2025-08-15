// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SHADER_BRUSH_RENDERER_HPP
#define KZ_SHADER_BRUSH_RENDERER_HPP

#include "gl_brush_renderer.hpp"

#include "gl_render_value_binding.hpp"

namespace kanzi
{

/// Freeform shader brush renderer
class MaterialBrushRenderer : public GlBrushRenderer
{
public:

    /// Create a new shader brush renderer.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    static BrushRendererPtr create(Brush* brush, Node* node);

    /// Bind material brush using a specific object as opposed to the brush.
    void bind(Renderer3D& renderer, Object* object);

    /// BrushRenderer::bindOverride() implementation.
    virtual void bindOverride(Renderer3D& renderer) KZ_OVERRIDE
    {
        bind(renderer, getBrush());
    }

    /// BrushRenderer::updateRenderOverride() implementation.
    virtual void updateRenderOverride(bool forceOpaque, bool translucencyHint) KZ_OVERRIDE;

    /// Access render state.
    /// \return Reference to containded render state.
    GlRenderState& getRenderState()
    {
        return m_renderState;
    }

    /// Invalidate all render values.
    void invalidateRenderValues()
    {
        m_renderValueBinding.setAllPropertiesDirty();
    }

protected:

    /// Constructor.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    explicit MaterialBrushRenderer(Brush* brush, Node* node) :
        GlBrushRenderer(brush, node),
        m_contentTextureHandle(0),
        m_renderOpacityHandle(0),
        m_materialPropertyChangeCounter(0u)
    {
    }

    /// BrushRenderer::drawOverride() implementation.
    virtual void drawOverride(Renderer3D& renderer, const Geometry& quad, const Matrix4x4& transform) const KZ_OVERRIDE;

    /// BrushRenderer::restoreResourcesOverride() implementation.
    virtual void restoreResourcesOverride() KZ_OVERRIDE;

    /// Check if property change counter matches that of the brush.
    /// \param material Material currently used.
    /// \return True if matches and no update is necessary, false otherwise.
    bool isChangeCounterSame(Material& material) const
    {
        return BrushRenderer::isChangeCounterSame() && (material.getPropertyChangeCounter() == m_materialPropertyChangeCounter);
    }
    /// Update property change counter to match brush.
    /// \param material Material currently used.
    void updateChangeCounter(Material& material)
    {
        BrushRenderer::updateChangeCounter();
        m_materialPropertyChangeCounter = material.getPropertyChangeCounter();
    }

private:

    /// Attach custom material.
    ///
    /// Will internally call BrushRenderer::attachMaterial().
    ///
    /// \param material New material to attach.
    void attachMaterial(MaterialSharedPtr material);

    /// Contained render state.
    GlRenderState m_renderState;

    /// Property binding handler.
    GlRenderValueBinding m_renderValueBinding;

    /// Render value handle.
    int m_contentTextureHandle;
    /// Render value handle.
    int m_renderOpacityHandle;

    /// Property change counter to track material.
    unsigned int m_materialPropertyChangeCounter;
};

}

#endif