// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CLEAR_RENDER_PASS_HPP
#define KZ_CLEAR_RENDER_PASS_HPP

#ifdef KANZI_FEATURE_3D

#include <kanzi/core.ui/graphics3d/render_pass.hpp>

namespace kanzi
{

// Forward declaration.
class ClearRenderPass;

/// ClearRenderPass shared pointer type.
typedef shared_ptr<ClearRenderPass> ClearRenderPassSharedPtr;

/// Use a Clear Render Pass to clear the color, depth, and stencil buffers of the current render context
/// before passing the control to the descendants of this render pass.
///
/// When you create a Clear Render Pass using the API, it does not clear any buffers.
/// However, when you create a Clear Render Pass in Kanzi Studio, the render pass clears
/// the depth buffer.
///
/// You control which buffers a Clear Render Pass clears by setting in the render pass
/// the properties for those buffers. To disable the clearing of a buffer, remove from
/// that render pass the property for the buffer the clearing of which you want to disable.
///
/// Clear values
/// ============
///
/// Valid value for the #ClearColorProperty property is any RGBA color. Values for each color range from 0.0f to 1.0f.
/// When using the Clear Render Pass in Kanzi Studio, the most common use cases include clearing to either transparent
/// black or any given opaque color. ColorRGBA::TransparentBlack is synonymous to ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f)
/// and provided for convenience.
///
/// Valid range for values in the #ClearDepthProperty property is from 0.0f to 1.0f. 1.0f represents the largest possible
/// value in the depth buffer and is the most commonly used value. Unless you want to achieve a very specific effect,
/// set the value of the #ClearDepthProperty property to either 1.0f or do not set the value at all.
///
/// Valid range for values for the #ClearStencilProperty property is from 0 to 255. Since the stencil buffer is usually
/// 8 bits, this means any 8-bit unsigned integer. For example, use the #ClearStencilProperty property, to reset the
/// stencil buffer before masking areas in it.
///
/// Examples
/// ========
///
/// To create a Clear Render Pass and set it to clear buffers:
/// \snippet test_render_pass_snippets.cpp Clear render pass
class KANZI_API ClearRenderPass : public RenderPass
{
public:

    /// \name Properties
    /// \{

    /// Use the Clear Color property to set the color that you want the Clear Render Pass to use to clear the color buffer.
    /// The default value is ColorRGBA(0.4f, 0.4f, 0.4f, 1.0f).
    /// \see setClearColor(), getClearColor()
    static PropertyType<ColorRGBA> ClearColorProperty;
    /// Gets the value of the #ClearColorProperty property.
    /// \see setClearColor()
    ColorRGBA getClearColor() const { return getProperty(ClearColorProperty); }
    /// Sets the value of the #ClearColorProperty property.
    /// \see getClearColor()
    void setClearColor(ColorRGBA value) { setProperty(ClearColorProperty, value); }

    /// Use the Clear Depth property to set the depth that you want the Clear Render Pass to use to clear the depth buffer.
    /// The default value is 1.0f.
    /// \see setClearDepth(), getClearDepth()
    static PropertyType<float> ClearDepthProperty;
    /// Gets the value of the #ClearDepthProperty property.
    /// \see setClearDepth()
    float getClearDepth() const { return getProperty(ClearDepthProperty); }
    /// Sets the value of the #ClearDepthProperty property.
    /// \see getClearDepth()
    void setClearDepth(float value) { setProperty(ClearDepthProperty, value); }

    /// Use the Clear Stencil property to set the clear stencil that you want the Clear Render Pass to use to clear the stencil buffer.
    /// The default value is 0.
    /// \see setClearStencil(), getClearStencil()
    static PropertyType<int> ClearStencilProperty;
    /// Gets the value of the #ClearStencilProperty property.
    /// \see setClearStencil()
    int getClearStencil() const { return getProperty(ClearStencilProperty); }
    /// Sets the value of the #ClearStencilProperty property.
    /// \see getClearStencil()
    void setClearStencil(int value) { setProperty(ClearStencilProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(ClearRenderPass, RenderPass, "Kanzi.ClearRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(ClearColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(ClearDepthProperty)
        KZ_METACLASS_PROPERTY_TYPE(ClearStencilProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a Clear Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Clear Render Pass.
    /// \return The created Clear Render Pass.
    static ClearRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the Clear Render Pass.
    explicit ClearRenderPass(Domain* domain, string_view name);

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

    /// RenderPass::requiresDepthBuffer() implementation.
    virtual CompositionRequirements getCompositionRequirements() const KZ_OVERRIDE;
};

} // namespace kanzi

#endif

#endif // KZ_CLEAR_RENDER_PASS_HPP

