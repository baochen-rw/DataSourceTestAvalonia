// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_TEXTURE_BRUSH_RENDERER_HPP
#define KZ_GL_TEXTURE_BRUSH_RENDERER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_brush_renderer.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_value.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/render_value_property_notification_handler.hpp>

namespace kanzi
{

/// Texture brush renderer class.
class TextureBrushRenderer : public GlBrushRenderer
{
public:

    /// Create a new texture brush renderer.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    static BrushRendererPtr create(Brush* brush, Node* node);

    /// BrushRenderer::bindOverride() implementation.
    virtual void bindOverride(Renderer3D& renderer) KZ_OVERRIDE;

    /// BrushRenderer::updateRenderOverride() implementation.
    virtual void updateRenderOverride(bool forceOpaque, bool translucencyHint) KZ_OVERRIDE;

    /// Gets the last used blend mode value.
    /// \return Blend mode.
    GraphicsBlendMode getBlendModeValue() const
    {
        return m_blendModeValue.get();
    }

    /// Gets the last used render opacity value.
    /// \return Floating point value.
    float getRenderOpacityValue() const
    {
        return m_renderOpacityValue.get();
    }

    /// Gets the last used render modulate color value.
    /// \return Color.
    ColorRGBA getModulateColorValue() const
    {
        return m_modulateColorValue.get();
    }

    /// Gets the last used content texture value.
    /// \return Shared pointer to texture.
    TextureSharedPtr getContentTextureValue() const
    {
        return m_contentTextureValue.get();
    }

    /// Gets the last used render texture value.
    /// \return Shared pointer to texture.
    TextureSharedPtr getRenderTextureValue() const
    {
        return m_renderTextureValue.get();
    }

protected:

    /// Constructor.
    ///
    /// \param brush Brush to use.
    /// \param node Node to attach to.
    explicit TextureBrushRenderer(Brush* brush, Node* node) :
             GlBrushRenderer(brush, node) {}

    /// BrushRenderer::drawOverride() implementation.
    virtual void drawOverride(Renderer3D& renderer, const Geometry& quad, const Matrix4x4& transform) const KZ_OVERRIDE;

    /// BrushRenderer::restoreResourcesOverride() implementation.
    virtual void restoreResourcesOverride() KZ_OVERRIDE;

private:

    /// Recreate all render value structures from current material.
    void recreateRenderValues();

    /// Currently selected material.
    MaterialSharedPtr m_material;

    /// Render value.
    GlRenderValue<GraphicsBlendMode> m_blendModeValue;
    /// Render value.
    GlRenderValue<TextureSharedPtr> m_contentTextureValue;
    /// Render value.
    GlRenderValue<ColorRGBA> m_modulateColorValue;
    /// Render value.
    GlRenderValue<float> m_renderOpacityValue;
    /// Render value.
    GlRenderValue<TextureSharedPtr> m_renderTextureValue;

    /// Property listener.
    RenderValuePropertyNotificationHandler<GraphicsBlendMode> m_blendModeProperty;
    /// Property listener.
    RenderValuePropertyNotificationHandler<ColorRGBA> m_modulateColorProperty;
    /// Property listener.
    RenderValuePropertyNotificationHandler<TextureSharedPtr> m_textureProperty;
};

}

#endif
