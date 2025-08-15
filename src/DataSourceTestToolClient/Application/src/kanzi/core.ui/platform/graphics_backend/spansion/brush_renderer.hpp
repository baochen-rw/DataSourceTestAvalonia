// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BRUSH_RENDERER_HPP
#define KZ_BRUSH_RENDERER_HPP


#include <kanzi/graphics_backend/texture.hpp>
#include <kanzi/math/matrix4x4.hpp>
#include <kanzi/platform/memory.hpp>


// Forward declaration.
struct KzuTextFormat;
struct KzuTextRenderer;


namespace kanzi
{


// Forward declaration.
class Brush;
class Geometry;
class Renderer3D;

/// TODO: follow the NVI pattern, use xxxOverride protected funcs
/// Brush renderer class.
///
/// Just an interface, actual rendering will be implemented by specialized brush renderers.
class KANZI_API BrushRenderer
{
public:
    /// Enum signifying currently selected render mode.
    enum RenderMode
    {
        /// No selection.
        RenderModeNone,

        /// Invalid render mode - selection has been done but suitable render mode could not be selected.
        RenderModeInvalid,

        /// Opaque without content.
        RenderModeOpaqueNoContent,

        /// Translucent without content.
        RenderModeTranslucentNoContent,

        /// Opaque with content.
        RenderModeOpaque,

        /// Translucent with content.
        RenderModeTranslucent
    };

    /// Destructor.
    virtual ~BrushRenderer() {}

    /// Called from Node2D::updateRender(), prepare brush for rendering.
    ///
    /// \param forceOpaque Should opaque render mode be selected no matter what?
    /// \param translucencyHint Additional hint to use translucent rendering.
    void updateRender(bool forceOpaque, bool translucencyHint);

    /// Default parameter override for updateRender().
    ///
    /// Allows forcing opacity, in this situation translucency hint does not matter.
    ///
    /// \param forceOpaque Should opaque render mode be selected no matter what?
    void updateRender(bool forceOpaque)
    {
        updateRender(forceOpaque, false);
    }

    /// Default parameter override for updateRender().
    ///
    /// Opaqueness force and translucency hint are off.
    void updateRender()
    {
        updateRender(false, false);
    }

    /// Bind brush renderer for rendering.
    ///
    /// \param renderer Renderer to use.
    void bind(Renderer3D& renderer);

    /// Draw a brush using given quad.
    ///
    /// \param renderer Renderer to use.
    /// \param quad Quad to draw.
    /// \param transform Transform (4X4) to use.
    void draw(Renderer3D& renderer, const Geometry& quad, const Matrix4x4& transform) const;

    /// Overload for draw a brush using given quad.
    ///
    /// \param renderer Renderer to use.
    /// \param quad Quad to draw.
    /// \param transform Transform (3X3) to use.
    void draw(Renderer3D& renderer, const Geometry& quad, const Matrix3x3& transform) const
    {
        draw(renderer, quad, Matrix4x4::createFromHomogenousMatrix(transform));
    }

    /// Restore resources after suspend.
    void restoreResources();

    /// Access brush.
    ///
    /// \return Brush pointer.
    Brush* getBrush() const
    {
        return m_brush;
    }

    /// Access opacity.
    ///
    /// \return Current render opacity.
    float getRenderOpacity() const
    {
        return m_renderOpacity;
    }
    /// Set opacity to use for next attach.
    ///
    /// \param opacity New render opacity.
    void setRenderOpacity(float opacity)
    {
        m_renderOpacity = opacity;
    }

    /// Access content texture.
    ///
    /// \return Current content texture.
    TextureSharedPtr getContentTexture() const
    {
        return m_contentTexture;
    }
    /// Set a content texture.
    ///
    /// \param texture New render texture.
    void setContentTexture(TextureSharedPtr texture)
    {
        m_contentTexture = texture;
    }

    /// Access node.
    ///
    /// \return Node pointer.
    Node* getNode() const
    {
        return m_node;
    }

    /// Get currently selected render mode.
    ///
    /// \return Current render mode.
    RenderMode getRenderMode() const
    {
        return m_renderMode;
    }
    /// Tell if any (valid) render mode selection has been made.
    bool hasRenderMode() const
    {
        return (m_renderMode != RenderModeNone) && (m_renderMode != RenderModeInvalid);
    }
    /// Tell if selected render mode is opaque.
    bool hasOpaqueRenderMode() const
    {
        return (m_renderMode == RenderModeOpaque) || (m_renderMode == RenderModeOpaqueNoContent);
    }

protected:
    /// Constructor.
    ///
    /// \param node Node to attach to.
    /// \param brush Brush to attach to.
    explicit BrushRenderer(Brush* brush, Node* node) :
             m_contentTextureHandle(0),
             m_renderOpacityHandle(0),
             m_brush(brush),
             m_node(node),
             m_renderMode(RenderModeNone),
             m_renderOpacity(1.0f)
    {
    }

    /// Draw a clip quad.
    ///
    /// To be implemented by specific brush implementations.
    ///
    /// \param renderer Renderer to use.
    /// \param geometry Quad to draw.
    /// \param transform Transform to use.
    virtual void drawOverride(Renderer3D& renderer, const Geometry& geometry, const Matrix4x4& transform) const = 0;

    /// BrushRenderer-specific bind implementation.
    virtual void bindOverride(Renderer3D& renderer) = 0;

    /// BrushRenderer-specific opacity override implementation.
    ///
    /// \param forceOpaque Should opaque render mode be selected no matter what?
    /// \param translucencyHint Additional hint to use translucent rendering.
    virtual void updateRenderOverride(bool forceOpaque, bool translucencyHint) = 0;

    /// BrushRenderer-specific restore resources implementation.
    virtual void restoreResourcesOverride() = 0;

    /// Set render mode.
    ///
    /// \param selection New render mode selection.
    void setRenderMode(RenderMode selection)
    {
        m_renderMode = selection;
    }

    /// Render value handle.
    size_t m_contentTextureHandle;
    /// Render value handle.
    size_t m_renderOpacityHandle;

private:
    /// Brush attached to.
    Brush* m_brush;
    /// Node attached to.
    Node* m_node;

    /// Currently used render mode (or none if not selected).
    RenderMode m_renderMode;

    /// Content texture to issue on attach.
    TextureSharedPtr m_contentTexture;
    /// Opacity to issue on attach.
    float m_renderOpacity;
};


typedef unique_ptr<BrushRenderer> BrushRendererPtr;

}


#endif
