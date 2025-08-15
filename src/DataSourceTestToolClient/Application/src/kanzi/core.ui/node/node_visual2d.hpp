// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_VISUAL2D_HPP
#define KZ_NODE_VISUAL2D_HPP

#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core.ui/graphics2d/geometry_frame.hpp>
#include <kanzi/core.ui/graphics2d/geometry_quad.hpp>
#include <kanzi/core.ui/graphics2d/frame_description.hpp>
#include <kanzi/core.ui/graphics2d/quad_description.hpp>
#include <kanzi/core.ui/graphics2d/brush.hpp>
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core/cpp/tuple.hpp>

namespace kanzi
{

// Forward declaration.
class Node2D;

/// Composition functionality for 2D nodes.
class KANZI_API NodeVisual2D
{
public:

    /// Constructor.
    explicit NodeVisual2D()
    {
    }

    /// Calculate foreground content stretch.
    ///
    /// \param contentStretch Content stretch mode, of type Node2D::ContentStretch.
    /// \param renderSize Render size.
    /// \param contentSize Content size.
    /// \return Tuple of foreground quad and clipping result mask.
    tuple<QuadDescription, unsigned int> calculateContentStretch(int contentStretch, Vector2 renderSize, Vector2 contentSize);

    /// Render using background brush.
    ///
    /// \param renderer Renderer to use.
    /// \param quad Quad to render.
    /// \param transform Transform for the quad.
    void renderBackground(Renderer3D& renderer, const Geometry& geometry, const Matrix4x4& transform);
    /// Render using background brush wrapper.
    void renderBackground(Renderer3D& renderer, const Geometry& geometry, const Matrix3x3& transform)
    {
        renderBackground(renderer, geometry, Matrix4x4::createFromHomogenousMatrix(transform));
    }
    /// Render using background brush.
    ///
    /// Uses background quad from visual.
    ///
    /// \param renderer Renderer to use.
    /// \param transform Transform for the quad.
    void renderBackground(Renderer3D& renderer, const Matrix4x4& transform);
    /// Render using background brush wrapper.
    void renderBackground(Renderer3D& renderer, const Matrix3x3& transform)
    {
        renderBackground(renderer, Matrix4x4::createFromHomogenousMatrix(transform));
    }

    /// Render using foreground brush.
    ///
    /// \param renderer Renderer to use.
    /// \param quad Quad to render.
    /// \param transform Transform for the quad.
    void renderForeground(Renderer3D& renderer, const Matrix4x4& transform);
    /// Render using foreground brush wrapper.
    void renderForeground(Renderer3D& renderer, const Matrix3x3& transform)
    {
        renderForeground(renderer, Matrix4x4::createFromHomogenousMatrix(transform));
    }

    /// Restore resources to GPU, if applicable.
    void restoreResources();

    /// Run updateRender() on foreground and background brush elements.
    ///
    /// \param layoutOpacity Final, layouted opacity of calling node.
    /// \param selfInCompositionTarget Is node rendered to a composition target.
    /// \param foregroundOpaquenessHint True if node foreground should use opaque render mode if possible.
    /// \param translucencyHint True if node should use translucent render mode if opaque render mode is not used.
    void updateRender(float layoutOpacity, bool selfInCompositionTarget, bool foregroundOpaquenessHint, bool translucencyHint);

    /// Get background brush renderer.
    BrushRenderer* getBackgroundBrushRenderer() const
    {
        return m_backgroundBrushRenderer.get();
    }
    /// Create background brush renderer.
    ///
    /// \param node Node to attach to.
    /// \param brush Brush to create from.
    void setBackgroundBrush(BrushSharedPtr brush, Node& node)
    {
        m_backgroundBrush = brush;
        m_backgroundBrushRenderer = brush->createBrushRenderer(&node);
    }
    /// Reset background brush renderer.
    void resetBackgroundBrush()
    {
        m_backgroundBrush.reset();
        m_backgroundBrushRenderer.reset();
    }

    /// Get foreground brush renderer.
    BrushRenderer* getForegroundBrushRenderer() const
    {
        return m_foregroundBrushRenderer.get();
    }
    /// Create foreground brush renderer.
    ///
    /// \param node Node to attach to.
    /// \param brush Brush to create from.
    void setForegroundBrushRenderer(BrushSharedPtr brush, Node& node)
    {
        m_foregroundBrush = brush;
        m_foregroundBrushRenderer = brush->createBrushRenderer(&node);
    }
    /// Reset foreground brush renderer.
    void resetForegroundBrush()
    {
        m_foregroundBrush.reset();
        m_foregroundBrushRenderer.reset();
    }

    /// Access foreground quad.
    GeometryQuad* getForegroundGeometry() const
    {
        return m_foregroundGeometry.get();
    }
    /// Set foreground quad with full data.
    ///
    /// \param offset Offset.
    /// \param size Size.
    /// \param textureOffset size Size.
    void setForegroundGeometry(const QuadDescription& quad)
    {
        // Avoid memory allocation if possible.
        if (m_foregroundGeometry)
        {
            m_foregroundGeometry->setGeometry(quad, getForegroundTiling());
        }
        else
        {
            m_foregroundGeometry.reset(new GeometryQuad(quad, getForegroundTiling()));
        }
    }
    /// Reset foreground geometry.
    void resetForegroundGeometry()
    {
        m_foregroundGeometry.reset();
    }

    /// Get background tiling from brush if present.
    Vector2 getBackgroundTiling() const
    {
        if (m_backgroundBrush)
        {
            return m_backgroundBrush->getTiling();
        }
        return Vector2(1.0f, 1.0f);
    }
    /// Get foreground tiling from brush if present.
    Vector2 getForegroundTiling() const
    {
        if (m_foregroundBrush)
        {
            return m_foregroundBrush->getTiling();
        }
        return Vector2(1.0f, 1.0f);
    }
    /// Tell if background brush is present and is opaque.
    bool isBackgroundOpaque() const
    {
        return m_backgroundBrush && m_backgroundBrush->isOpaque();
    }
    /// Tell if foreground brush is present and is opaque.
    bool isForegroundOpaque() const
    {
        return m_foregroundBrush && m_foregroundBrush->isOpaque();
    }

    /// Create background quad.
    ///
    /// Creates a complete background quad.
    ///
    /// \param quad Quad description.
    void createBackgroundGeometry(const QuadDescription& quad)
    {
        m_backgroundGeometry.reset(static_cast<GeometryPtr::pointer>(new GeometryQuad(quad, getBackgroundTiling())));
    }
    /// Create the outside area quad.
    ///
    /// Creates a frame that does not include the foreground area.
    ///
    /// \param quad Whole background area quad.
    /// \param clippingResult Clipping result.
    void createBackgroundGeometry(const QuadDescription& bg, const QuadDescription& fg, unsigned int clippingResult)
    {
        FrameDescription frame(bg, fg, clippingResult);
        m_backgroundGeometry.reset(static_cast<GeometryPtr::pointer>(new GeometryFrame(frame, getBackgroundTiling())));
    }
    /// Access background geometry.
    Geometry* getBackgroundGeometry() const
    {
        return m_backgroundGeometry.get();
    }
    /// Reset outside area quad.
    void resetBackgroundGeometry()
    {
        m_backgroundGeometry.reset();
    }

    /// Update content texture in foreground brush renderer, if it exists.
    void updateContentTexture(TextureSharedPtr texture)
    {
        if(m_foregroundBrushRenderer)
        {
            m_foregroundBrushRenderer->setContentTexture(texture);
        }
    }

private:

    NodeVisual2D(const NodeVisual2D& other) KZ_DELETED_FUNCTION;
    NodeVisual2D& operator = (const NodeVisual2D& other) KZ_DELETED_FUNCTION;

    /// Background quad.
    GeometryPtr m_backgroundGeometry;
    /// Foreground clipping quad.
    unique_ptr<GeometryQuad> m_foregroundGeometry;

    /// Brush for background.
    BrushSharedPtr m_backgroundBrush;
    /// Brush for foreground.
    BrushSharedPtr m_foregroundBrush;

    /// Brush renderer for background.
    BrushRendererPtr m_backgroundBrushRenderer;
    /// Brush renderer for foreground.
    BrushRendererPtr m_foregroundBrushRenderer;
};

}

#endif // KZ_NODE_VISUAL2D_HPP