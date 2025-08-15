// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE2D_COMPOSITOR_HPP
#define KZ_NODE2D_COMPOSITOR_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/texture.hpp>
#include <kanzi/core.ui/graphics2d/composition_brush.hpp>
#include <kanzi/core/cpp/bitset.hpp>
#include <kanzi/core/cpp/tuple.hpp>

namespace kanzi
{

// Forward declaration.
class CompositionStack;
class Node2D;
class QuadDescription;
class CompositionManager;

/// Composition functionality for 2D nodes.
class KANZI_API NodeCompositor2D
{
private:
    NodeCompositor2D(const NodeCompositor2D& other) KZ_DELETED_FUNCTION;
    NodeCompositor2D& operator = (const NodeCompositor2D& other) KZ_DELETED_FUNCTION;

public:
    /// Enum for children compositing bit flags.
    enum ComposeChildrenBits
    {
        /// Caching.
        ChildrenCompositingBitCache =   0,
        /// Request from code.
        ChildrenCompositingBitRequest = 1,
        /// Number of options.
        ChildrenCompositingBitCount =   2,
    };

    /// Enum for final result compositing bit flags.
    enum ComposeFinalBits
    {
        /// Caching.
        FinalCompositingBitCache =     0,
        /// Force composition from property.
        FinalCompositingBitForce =     1,
        /// Offscreen rendering.
        FinalCompositingBitOffscreen = 2,
        /// Composition due to opacity and children.
        FinalCompositingBitOpacity =   3,
        /// Request from code.
        FinalCompositingBitRequest =   4,
        /// Number of options.
        FinalCompositingBitCount =     5,
    };

    /// Enum for self compositing bit flags.
    enum ComposeSelfBits
    {
        /// Caching.
        SelfCompositingBitCache =   0,
        /// Request from code.
        SelfCompositingBitRequest = 1,
        /// Number of options.
        SelfCompositingBitCount =   2,
    };

protected:
    /// Managed composition target container.
    struct ManagedCompositionTarget
    {
        /// Constructor.
        ManagedCompositionTarget() :
            m_cacheValid(false) { }

        /// Access composition target.
        ///
        /// \return Current composition target.
        TextureSharedPtr getCompositionTarget() const
        {
            return m_compositionTarget;
        }
        /// Tell if a managed composition target has been allocated.
        ///
        /// \return True if yes, false if no.
        bool hasCompositionTarget() const
        {
            return static_cast<bool>(m_compositionTarget);
        }
        /// Update composition target.
        ///
        /// Will implicitly invalidate cache status.
        ///
        /// \param framebuffer New framebuffer.
        void setCompositionTarget(TextureSharedPtr framebuffer)
        {
            m_compositionTarget = framebuffer;
            setCacheValid(false);
        }

        /// Tell if cache is valid.
        ///
        /// \return True if yes, false if no.
        bool isCacheValid() const
        {
            return m_cacheValid;
        }
        /// Set cache as valid.
        void setCacheValid(bool valid)
        {
            m_cacheValid = valid;
        }

        /// Reset current composition target allocation.
        void reset()
        {
            m_compositionTarget.reset();
            setCacheValid(false);
        }

    private:
        /// Current framebuffer.
        TextureSharedPtr m_compositionTarget;

        /// Is cache active?
        bool m_cacheValid;
    };

    /// Perspective transform container.
    struct PerspectiveTransformParameters
    {
        /// Constructor.
        PerspectiveTransformParameters(const Matrix4x4& transformParam) :
            transform(transformParam)
        {
        }

        /// Actual 3D perspective transform.
        Matrix4x4 transform;

        /// Viewport offset for composition spaces.
        optional<Vector4> offset;
    };

    /// Update a managed composition target to match current requirements.
    ///
    /// If the composition target does not exist or the settings required from it have been changed, it is (re)created.
    ///
    /// \param node Node to attach to.
    /// \param managedCompositionTarget Existing composition target container.
    /// \param requiredSize Size required of the composition target.
    /// \param alphaRequired Alpha requirement.
    /// \param depthRequired Depth requirement.
    /// \param stencilRequired Stencil requirement.
    /// \return True if composition target was updated, false if not.
    bool updatePersistentCompositionTarget(Node2D& node, ManagedCompositionTarget& managedCompositionTarget, Vector2 requiredSize,
                                           bool alphaRequired, bool depthRequired, bool stencilRequired);

public:
    /// Constructor.
    NodeCompositor2D()
    {
    }

    /// Begin final composition.
    ///
    /// \param compositionStack Composition stack to use.
    /// \param compositionManager Composition manager to use.
    /// \param requiredSize Size required of the composition target.
    /// \param alphaRequired Alpha requirement.
    /// \param depthRequired Depth requirement.
    /// \param stencilRequired Stencil requirement.
    /// \return Tuple of render target to use and whether or not to perform actual render.
    tuple<TextureSharedPtr, bool> beginFinalComposition(CompositionStack& compositionStack, CompositionManager* compositionManager,
                                                        Vector2 requiredSize, bool alphaRequired, bool depthRequired, bool stencilRequired);
    /// End final composition.
    ///
    /// \param compositionStack Composition stack to use.
    void endFinalComposition(CompositionStack& compositionStack);
    /// Blit final composition.
    ///
    /// \param renderer Renderer to use.
    /// \param compositionStack Composition stack to use.
    /// \param compositionManager Composition manager to use.
    /// \param renderTargetTexture Render target texture used.
    /// \param backgroundQuad Clip quad for background area.
    /// \param transform Transform used for rendering.
    /// \param quadSize Rendered quad size.
    void blitFinalComposition(Renderer3D& renderer, CompositionStack& compositionStack, CompositionManager* compositionManager,
                              TextureSharedPtr renderTargetTexture, QuadDescription& backgroundQuad, const Matrix3x3& transform, Vector2 quadSize);

    /// Begin self composition.
    ///
    /// \param compositionStack Composition stack to use.
    /// \param requiredSize Size required of the composition target.
    /// \return Tuple of render target to use and whether or not to perform actual render.
    tuple<TextureSharedPtr, bool> beginSelfComposition(CompositionStack& compositionStack, Vector2 requiredSize);
    ///
    /// \param compositionStack Composition stack to use.
    /// Begin self composition.
    void endSelfComposition(CompositionStack& compositionStack);
    /// Blit self composition.
    ///
    /// \param renderer Renderer to use.
    /// \param compositionStack Composition stack to use.
    /// \param texture Texture used.
    /// \param backgroundQuad Clip quad for background area.
    /// \param transform Transform used for rendering.
    /// \param quadSize Rendered quad size.
    void blitSelfComposition(Renderer3D& renderer, CompositionStack& compositionStack, Texture& texture, QuadDescription& backgroundQuad,
                             const Matrix3x3& transform, Vector2 quadSize);

    /// Begin children composition.
    ///
    /// \param compositionStack Composition stack to use.
    /// \param requiredSize Size required of the composition target.
    /// \return Tuple of render target to use and whether or not to perform actual render.
    tuple<TextureSharedPtr, bool> beginChildrenComposition(CompositionStack& compositionStack, Vector2 requiredSize);
    ///
    /// \param compositionStack Composition stack to use.
    /// Begin self composition.
    void endChildrenComposition(CompositionStack& compositionStack);
    /// Blit self composition.
    ///
    /// \param renderer Renderer to use.
    /// \param compositionStack Composition stack to use.
    /// \param texture Texture used.
    /// \param backgroundQuad Clip quad for background area.
    /// \param transform Transform used for rendering.
    /// \param quadSize Rendered quad size.
    void blitChildrenComposition(Renderer3D& renderer, CompositionStack& compositionStack, Texture& texture, QuadDescription& backgroundQuad,
                                 const Matrix3x3& transform, Vector2 quadSize);

    /// Render composition quad.
    ///
    /// \param renderer Renderer to use.
    /// \param compositionStack Composition stack to use.
    /// \param texture Texture used.
    /// \param backgroundQuad Clip quad for background area.
    /// \param renderTransform Transform used for rendering.
    /// \param quadSize Rendered quad size.
    void renderCompositionQuad(Renderer3D& renderer, BrushRenderer& brushRenderer, const Texture& texture, QuadDescription& backgroundQuad,
                               const Matrix4x4& transform, Vector2 quadSize);

    /// Create composition brush renderer.
    ///
    /// \param node Node to attach to.
    /// \param brush Brush to create from.
    /// \param texture Texture to use.
    void createCompositionBrushRenderer(Node& node, Brush& brush, TextureSharedPtr texture);

    /// Access cache composition target for Node2D's children.
    ///
    /// Will only function if Node2D has been transformed.
    /// Will deploy the composition target if necessary.
    ///
    /// \return Render target pointer.
    TextureSharedPtr getCacheChildrenCompositionTarget() const;
    /// Access cache composition target for Node2D itself.
    ///
    /// Will only function if Node2D has been transformed.
    /// Will deploy the composition target if necessary.
    ///
    /// \return Render target pointer.
    TextureSharedPtr getCacheSelfCompositionTarget() const;
    /// Access 'final' managed composition target.
    ///
    /// Will deploy the composition target if necessary.
    TextureSharedPtr getFinalCompositionTarget() const;

    /// Resize automatic sizes in user composition target if necessary.
    /// \param compositionSize Composition size to resize to.
    void resizeUserCompositionTarget(Vector2 compositionSize);

    /// Run when node owning the compositor becomes detached.
    void onDetached();

    /// Restore resources.
    /// Will restore all GL resources and resize render targets with automatic size.
    /// \param compositionSize Composition size to resize to.
    void restoreResources(Vector2 compositionSize);

    /// Update for rendering, recreating composition targets and brush renderers as needed.
    ///
    /// \param node Node to attach to.
    /// \param actualSize Size required of the composition target.
    /// \param alphaRequired Alpha requirement.
    /// \param depthRequired Depth requirement.
    /// \param stencilRequired Stencil requirement.
    /// \param opacity Opacity value that should be used for rendering.
    /// \param opaquenessHint Should opaque rendering especially be used?
    /// \param translucencyHint Should translucent rendering especially be used?
    void updateRender(Node2D& node, Vector2 actualSize, bool alphaRequired, bool depthRequired, bool stencilRequired,
                      float opacity, bool opaquenessHint, bool translucencyHint);

    /// Access cache children brush renderer.
    BrushRenderer* getCacheChildrenBrushRenderer() const
    {
        return m_cacheChildrenBrushRenderer.get();
    }
    /// Access cache self brush renderer.
    BrushRenderer* getCacheSelfBrushRenderer() const
    {
        return m_cacheSelfBrushRenderer.get();
    }
    /// Access composition brush renderer.
    BrushRenderer* getCompositionBrushRenderer() const
    {
        return m_compositionBrushRenderer.get();
    }
    /// Tell if composition brush renderer has been created.
    bool hasCompositionBrushRenderer() const
    {
        return static_cast<bool>(m_compositionBrushRenderer);
    }

    /// Tell if managed composition target has been created.
    bool hasManagedCompositionTargetFinal() const
    {
        return static_cast<bool>(m_finalCompositionTarget.getCompositionTarget());
    }
    /// Set user composition brush.
    void setUserCompositionBrush(BrushSharedPtr brush)
    {
        if(m_userCompositionBrush != brush)
        {
            m_userCompositionBrush = brush;
            invalidateCompositionBrush();
        }
    }

    /// Get size of user composition target.
    ///
    /// \return Size of composition target or zero vector.
    Vector2 getUserCompositionTargetSize() const
    {
        if (m_userCompositionTarget)
        {
            float userWidth = m_userCompositionTarget->hasAutomaticWidth() ? 0.0f : static_cast<float>(m_userCompositionTarget->getWidth());
            float userHeight = m_userCompositionTarget->hasAutomaticHeight() ? 0.0f : static_cast<float>(m_userCompositionTarget->getHeight());

            return Vector2(userWidth, userHeight);
        }
        return Vector2(0.0f, 0.0f);
    }
    /// Set user composition target.
    void setUserCompositionTarget(TextureSharedPtr texture)
    {
        if(m_userCompositionTarget != texture)
        {
            m_userCompositionTarget = texture;
            invalidateCompositionBrush();
        }
    }

    /// Tell if cache children has been set.
    bool isCacheChildren() const
    {
        return m_childrenComposeMask[ChildrenCompositingBitCache];
    }
    /// Set cache children state.
    ///
    /// \param enabled New cache children state.
    void setCacheChildren(bool enabled)
    {
        if(isCacheChildren() != enabled)
        {
            resetManagedCompositionTargetCacheChildren();
            m_childrenComposeMask[ChildrenCompositingBitCache] = enabled;
        }
    }
    /// Tell if cache result has been set.
    bool isCacheResult() const
    {
        return m_finalComposeMask[FinalCompositingBitCache];
    }
    /// Set cache result state.
    ///
    /// \param enabled New cache result state.
    void setCacheResult(bool enabled)
    {
        if(isCacheResult() != enabled)
        {
            resetManagedCompositionTargetFinal();
            m_finalComposeMask[FinalCompositingBitCache] = enabled;
        }
    }
    /// Tell if cache self has been set.
    bool isCacheSelf() const
    {
        return m_selfComposeMask[SelfCompositingBitCache];
    }
    /// Set cache self state.
    ///
    /// \param enabled New cache children state.
    void setCacheSelf(bool enabled)
    {
        if(isCacheSelf() != enabled)
        {
            resetManagedCompositionTargetCacheSelf();
            m_selfComposeMask[SelfCompositingBitCache] = enabled;
        }
    }

    /// Invalidate composition brush.
    void invalidateCompositionBrush()
    {
        m_managedCompositionBrush.reset();
        m_compositionBrushRenderer.reset();
    }

    /// Tell if children cache is valid.
    bool isCacheChildrenValid() const
    {
        return m_cacheChildrenCompositionTarget.isCacheValid();
    }
    /// Mark self cache as valid.
    ///
    /// \param valid New validity status.
    void setCacheChildrenValid(bool valid)
    {
        m_cacheChildrenCompositionTarget.setCacheValid(valid);
        kzAssert(!valid || m_cacheChildrenCompositionTarget.hasCompositionTarget());
    }
    /// Tell if final cache is valid.
    bool isCacheFinalValid() const
    {
        return m_finalCompositionTarget.isCacheValid();
    }
    /// Mark final cache as valid.
    ///
    /// \param valid New validity status.
    void setCacheFinalValid(bool valid)
    {
        m_finalCompositionTarget.setCacheValid(valid);
    }
    /// Tell if self cache is valid.
    bool isCacheSelfValid() const
    {
        return m_cacheSelfCompositionTarget.isCacheValid();
    }
    /// Mark self cache as valid.
    ///
    /// \param valid New validity status.
    void setCacheSelfValid(bool valid)
    {
        m_cacheSelfCompositionTarget.setCacheValid(valid);
        kzAssert(!valid || m_cacheSelfCompositionTarget.hasCompositionTarget());
    }

    /// Tell if compositing children is required.
    bool isChildrenCompositionRequired() const
    {
        return m_childrenComposeMask.any();
    }
    /// Tell if compositing final result is required.
    bool isFinalCompositionRequired() const
    {
        return m_finalComposeMask.any() || static_cast<bool>(m_userCompositionTarget) || static_cast<bool>(m_perspective);
    }
    /// Tell if compositing self is required.
    bool isSelfCompositionRequired() const
    {
        return m_selfComposeMask.any();
    }

    /// Is compositing requested from code?
    bool isFinalCompositionRequested() const
    {
        return m_finalComposeMask[FinalCompositingBitRequest];
    }
    /// Set compositing request.
    void setFinalCompositionRequested(bool enabled)
    {
        m_finalComposeMask[FinalCompositingBitRequest] = enabled;
    }
    /// Is force composition on?
    bool isForceComposition() const
    {
        return m_finalComposeMask[FinalCompositingBitForce];
    }
    /// Set force composition.
    void setForceComposition(bool enabled)
    {
        m_finalComposeMask[FinalCompositingBitForce] = enabled;
    }
    /// Is offscreen rendering on?
    bool isOffscreenRendering() const
    {
        return m_finalComposeMask[FinalCompositingBitOffscreen];
    }
    /// Set offscreen rendering flag.
    void setOffscreenRendering(bool enabled)
    {
        m_finalComposeMask[FinalCompositingBitOffscreen] = enabled;
    }
    /// Is Opacity composition request flag on?
    bool isOpacityCompositionRequest() const
    {
        return m_finalComposeMask[FinalCompositingBitOpacity];
    }
    /// Set opacity composition request flag.
    void setOpacityCompositionRequested(bool enabled)
    {
        m_finalComposeMask[FinalCompositingBitOpacity] = enabled;
    }

    /// Reset cache children managed composition target.
    void resetManagedCompositionTargetCacheChildren()
    {
        m_cacheChildrenCompositionTarget.reset();
    }
    /// Reset cache self managed composition target.
    void resetManagedCompositionTargetCacheSelf()
    {
        m_cacheSelfCompositionTarget.reset();
    }
    /// Reset final managed composition target.
    void resetManagedCompositionTargetFinal()
    {
        m_finalCompositionTarget.reset();
    }

    /// Access perspective transform.
    ///
    /// \return Perspective transform set, may be null if not set.
    const Matrix4x4* getPerspectiveTransform() const
    {
        return m_perspective ? &(m_perspective->transform) : 0;
    }
    /// Reset perspective transform.
    void resetPerspectiveTransform()
    {
        m_perspective.reset();
    }
    /// Set perspective transform.
    ///
    /// \param transform Perspective transform to use.
    void setPerspectiveTransform(const Matrix4x4& transform)
    {
        if(!m_perspective)
        {
            m_perspective.reset(new PerspectiveTransformParameters(transform));
        }
        else
        {
            m_perspective->transform = transform;
        }
    }

    /// Access world perspective transform.
    ///
    /// \return Perspective transform set, may be null if not set.
    const Vector4* getWorldPerspectiveOffset() const
    {
        return m_perspective && m_perspective->offset ? &(*(m_perspective->offset)) : 0;
    }
    /// Reset world perspective transform.
    void resetWorldPerspectiveOffset()
    {
        if(m_perspective)
        {
            m_perspective->offset.reset();
        }
    }
    /// Set world perspective transform.
    ///
    /// \param transform World perspective transform to use.
    void setWorldPerspectiveOffset(const Vector4& offset)
    {
        kzAssert(m_perspective);
        m_perspective->offset = offset;
    }

protected:
    /// Managed composition target for complete node composition.
    ManagedCompositionTarget m_finalCompositionTarget;
    /// Managed composition target for caching children.
    ManagedCompositionTarget m_cacheChildrenCompositionTarget;
    /// Managed composition target for caching node contents.
    ManagedCompositionTarget m_cacheSelfCompositionTarget;

    /// User-set composition brush.
    BrushSharedPtr m_userCompositionBrush;
    /// User-set composition target.
    TextureSharedPtr m_userCompositionTarget;

    /// Brush used to render cached children.
    CompositionBrushSharedPtr m_cacheChildrenBrush;
    /// Cache children brush renderer.
    BrushRendererPtr m_cacheChildrenBrushRenderer;
    /// Brush used to render cached node itself.
    CompositionBrushSharedPtr m_cacheSelfBrush;
    /// Cache self brush renderer.
    BrushRendererPtr m_cacheSelfBrushRenderer;
    /// Composition brush managed by node.
    CompositionBrushSharedPtr m_managedCompositionBrush;
    /// Composition brush renderer.
    BrushRendererPtr m_compositionBrushRenderer;

    /// Perspective components.
    unique_ptr<PerspectiveTransformParameters> m_perspective;

    /// Bit mask for states affecting whether or not the node should compose its children.
    bitset<ChildrenCompositingBitCount> m_childrenComposeMask;
    /// Bit mask for states affecting whether or not the node should compose itself and its children.
    bitset<FinalCompositingBitCount> m_finalComposeMask;
    /// Bit mask for states affecting whether or not the node should compose itself.
    bitset<SelfCompositingBitCount> m_selfComposeMask;
};

}

#endif