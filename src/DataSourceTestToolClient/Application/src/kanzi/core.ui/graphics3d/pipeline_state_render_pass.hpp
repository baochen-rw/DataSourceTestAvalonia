// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PIPELINE_STATE_RENDER_PASS_HPP
#define KZ_PIPELINE_STATE_RENDER_PASS_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/renderer.hpp>
#include <kanzi/core.ui/graphics3d/render_pass.hpp>

namespace kanzi
{

// Forward declaration.
class PipelineStateRenderPass;

/// PipelineStateRenderPass shared pointer type.
typedef shared_ptr<PipelineStateRenderPass> PipelineStateRenderPassSharedPtr;

/// Use the Pipeline State Render Pass to set for its child render passes the depth
/// and stencil testing, transparency, and culling. This render pass sets the rendering
/// state before passing the control to its descendants. After the descendant render passes
/// of a Pipeline State Render Pass execute, Kanzi restores the rendering state.
/// If a Pipeline State Render Pass does not have any descendants, Kanzi does not apply
/// the rendering state you set in that render pass.
/// 
/// You change the rendering state by setting the properties in a Pipeline State Render Pass.
/// The default settings in a Pipeline State Render Pass that you can set are:
/// - #BlendModeProperty property is set to Premultiplied alpha
/// - #ColorWriteModeProperty property is set to RGBA
/// - Depth test is enabled and set to Less
/// - #DepthWriteEnabledProperty property is enabled
/// - #CullModeProperty property is enabled and set to Back
/// - #StencilTestFunctionProperty property is disabled
/// - #ViewportProperty property is set to the complete size of #Viewport2D node or
/// of the current composition target set by a #CompositionTargetRenderPass
/// - #ScissorProperty property is disabled, unless the current Viewport 2D node
/// does not fill the whole composition target area
///
/// Kanzi groups the rendering state combinations that a Pipeline State Render Pass applies
/// into these state stacks:
/// - Color and blend state
/// - Depth and stencil state
/// - Composition (viewport and scissor) state
/// - Rasterization state
///
/// If you do not set a property, Kanzi uses the default or previously set value. See CompositionStack.
///
/// Examples
/// ====
/// To turn on stencil test and only render where stencil buffer value is not 0:
/// \snippet test_render_pass_snippets.cpp Pipeline state render pass stencil test
///
/// To render only the back faces of objects:
/// \snippet test_render_pass_snippets.cpp Pipeline state render pass cull mode
///
/// To turn off alpha blending:
/// \snippet test_render_pass_snippets.cpp Pipeline state render pass blend mode
class KANZI_API PipelineStateRenderPass : public RenderPass
{
public:

    enum ViewportMode
    {
        /// Absolute viewport - pixel coordinates.
        ViewportModeAbsolute = 0,

        /// Relative viewport - percentage of current render context size.
        ViewportModeRelative = 1,
    };

    /// \name Properties
    /// \{

    /// Use the Blend Mode property to override the blend mode set in each node that this render pass renders.
    /// The default value is GraphicsBlendModeOpaque.
    /// \see setBlendMode(), getBlendMode()
    static PropertyType<GraphicsBlendMode> BlendModeProperty;
    /// Gets the value of the #BlendModeProperty property.
    /// \see setBlendMode()
    GraphicsBlendMode getBlendMode() const
    {
        return getProperty(BlendModeProperty);
    }
    /// Sets the value of the #BlendModeProperty property.
    /// \see getBlendMode()
    void setBlendMode(GraphicsBlendMode value)
    {
        setProperty(BlendModeProperty, value);
    }

    /// Use the Color Write Mode property to set which channels the render pass writes to the color buffer.
    /// To disable the color write, set the property to None.
    /// The default value is GraphicsColorWriteModeRGBA.
    /// \see setColorWriteMode(), getColorWriteMode()
    static PropertyType<GraphicsColorWriteMode> ColorWriteModeProperty;
    /// Gets the value of the #ColorWriteModeProperty property.
    /// \see setColorWriteMode()
    GraphicsColorWriteMode getColorWriteMode() const
    {
        return getProperty(ColorWriteModeProperty);
    }
    /// Sets the value of the #ColorWriteModeProperty property.
    /// \see getColorWriteMode()
    void setColorWriteMode(GraphicsColorWriteMode value)
    {
        setProperty(ColorWriteModeProperty, value);
    }

    /// Use the Depth Test Function property to control whether the depth test discards a fragment.
    /// The default value is GraphicsCompareFunctionLess.
    /// \see setDepthTestFunction(), getDepthTestFunction()
    static PropertyType<GraphicsCompareFunction> DepthTestFunctionProperty;
    /// Gets the value of the #DepthTestFunctionProperty property.
    /// \see setDepthTestFunction()
    GraphicsCompareFunction getDepthTestFunction() const
    {
        return getProperty(DepthTestFunctionProperty);
    }
    /// Sets the value of the #DepthTestFunctionProperty property.
    /// \see getDepthTestFunction()
    void setDepthTestFunction(GraphicsCompareFunction value)
    {
        setProperty(DepthTestFunctionProperty, value);
    }

    /// Use the Depth Write Enabled property to set whether the render pass writes to the depth buffer.
    /// The default value is True.
    /// \see setDepthWriteEnabled(), isDepthWriteEnabled()
    static PropertyType<bool> DepthWriteEnabledProperty;
    /// Gets the value of the #DepthWriteEnabledProperty property.
    /// \see setDepthWriteEnabled()
    bool isDepthWriteEnabled() const
    {
        return getProperty(DepthWriteEnabledProperty);
    }
    /// Sets the value of the #DepthWriteEnabledProperty property.
    /// \see isDepthWriteEnabled()
    void setDepthWriteEnabled(bool value)
    {
        setProperty(DepthWriteEnabledProperty, value);
    }

    /// Use the Stencil Test Function property to control whether the stencil test discards a fragment.
    /// The default value is GraphicsCompareFunctionDisabled.
    /// \see setStencilTestFunction(), getStencilTestFunction(), #StencilReferenceValueProperty
    static PropertyType<GraphicsCompareFunction> StencilTestFunctionProperty;
    /// Gets the value of the #StencilTestFunctionProperty property.
    /// \see setStencilTestFunction()
    GraphicsCompareFunction getStencilTestFunction() const
    {
        return getProperty(StencilTestFunctionProperty);
    }
    /// Sets the value of the #StencilTestFunctionProperty property.
    /// \see getStencilTestFunction()
    void setStencilTestFunction(GraphicsCompareFunction value)
    {
        setProperty(StencilTestFunctionProperty, value);
    }

    /// Use the Stencil Reference Value property to set the reference value for the stencil test.
    /// The default value is 0.
    /// \see setStencilReferenceValue(), getStencilReferenceValue(), #StencilTestFunctionProperty
    static PropertyType<int> StencilReferenceValueProperty;
    /// Gets the value of the #StencilReferenceValueProperty property.
    /// \see setStencilReferenceValue()
    int getStencilReferenceValue() const
    {
        return getProperty(StencilReferenceValueProperty);
    }
    /// Sets the value of the #StencilReferenceValueProperty property.
    /// \see getStencilReferenceValue()
    void setStencilReferenceValue(int value)
    {
        setProperty(StencilReferenceValueProperty, value);
    }

    /// Use the Stencil Mask property to set a mask on which the AND operation is executed with both the reference value
    /// and the stored stencil value when the test is done.
    /// The default value is 255.
    /// \see setStencilMask(), getStencilMask()
    static PropertyType<int> StencilMaskProperty;
    /// Gets the value of the #StencilMaskProperty property.
    /// \see setStencilMask()
    int getStencilMask() const
    {
        return getProperty(StencilMaskProperty);
    }
    /// Sets the value of the #StencilMaskProperty property.
    /// \see getStencilMask()
    void setStencilMask(int value)
    {
        setProperty(StencilMaskProperty, value);
    }

    /// Use the Stencil Fail Operation property to set the operation that the render pass
    /// performs when the stencil test fails.
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilFailOperation(), getStencilFailOperation()
    static PropertyType<GraphicsStencilOperation> StencilFailOperationProperty;
    /// Gets the value of the #StencilFailOperationProperty property.
    /// \see setStencilFailOperation()
    GraphicsStencilOperation getStencilFailOperation() const
    {
        return getProperty(StencilFailOperationProperty);
    }
    /// Sets the value of the #StencilFailOperationProperty property.
    /// \see getStencilFailOperation()
    void setStencilFailOperation(GraphicsStencilOperation value)
    {
        setProperty(StencilFailOperationProperty, value);
    }

    /// Use the Stencil Pass Depth Fail Operation property to set the operation that the render pass
    /// performs when the stencil test passes, but the depth test fails.
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilPassDepthFailOperation(), getStencilPassDepthFailOperation()
    static PropertyType<GraphicsStencilOperation> StencilPassDepthFailOperationProperty;
    /// Gets the value of the #StencilPassDepthFailOperationProperty property.
    /// \see setStencilPassDepthFailOperation()
    GraphicsStencilOperation getStencilPassDepthFailOperation() const
    {
        return getProperty(StencilPassDepthFailOperationProperty);
    }
    /// Sets the value of the #StencilPassDepthFailOperationProperty property.
    /// \see getStencilPassDepthFailOperation()
    void setStencilPassDepthFailOperation(GraphicsStencilOperation value)
    {
        setProperty(StencilPassDepthFailOperationProperty, value);
    }

    /// Use the Stencil Pass Depth Pass Operation property to set the operation that the render pass
    /// performs when both, the stencil and the depth test, pass.
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilPassDepthPassOperation(), getStencilPassDepthPassOperation()
    static PropertyType<GraphicsStencilOperation> StencilPassDepthPassOperationProperty;
    /// Gets the value of the #StencilPassDepthPassOperationProperty property.
    /// \see setStencilPassDepthPassOperation()
    GraphicsStencilOperation getStencilPassDepthPassOperation() const
    {
        return getProperty(StencilPassDepthPassOperationProperty);
    }
    /// Sets the value of the #StencilPassDepthPassOperationProperty property.
    /// \see getStencilPassDepthPassOperation()
    void setStencilPassDepthPassOperation(GraphicsStencilOperation value)
    {
        setProperty(StencilPassDepthPassOperationProperty, value);
    }

    /// Use the Stencil Write Enabled property to set whether to enable writing to the stencil buffer.
    /// The default value is True.
    /// \see setStencilWriteEnabled(), isStencilWriteEnabled()
    static PropertyType<bool> StencilWriteEnabledProperty;
    /// Gets the value of the #StencilWriteEnabledProperty property.
    /// \see setStencilWriteEnabled()
    bool isStencilWriteEnabled() const
    {
        return getProperty(StencilWriteEnabledProperty);
    }
    /// Sets the value of the #StencilWriteEnabledProperty property.
    /// \see isStencilWriteEnabled()
    void setStencilWriteEnabled(bool value)
    {
        setProperty(StencilWriteEnabledProperty, value);
    }

    /// Use the Cull Mode property to set the culling of the triangle faces in the rendered meshes. Set to:
    /// - Back to render the triangles whose normal points towards a Camera node
    /// - Front to render the triangles whose normal points away from a Camera node
    /// The default value is GraphicsCullModeBack.
    /// \see setCullMode(), getCullMode()
    static PropertyType<GraphicsCullMode> CullModeProperty;
    /// Gets the value of the #CullModeProperty property.
    /// \see setCullMode()
    GraphicsCullMode getCullMode() const
    {
        return getProperty(CullModeProperty);
    }
    /// Sets the value of the #CullModeProperty property.
    /// \see getCullMode()
    void setCullMode(GraphicsCullMode value)
    {
        setProperty(CullModeProperty, value);
    }

    /// Use the Viewport property to modify the current rendering Viewport 2D node.
    /// You can define the Viewport 2D node in either relative or absolute coordinates,
    /// the default is relative. Use the #ViewportModeProperty property to set the coordinate type.
    /// \see setViewport(), getViewport(), #ViewportModeProperty
    static PropertyType<Vector4> ViewportProperty;
    /// Gets the value of the #ViewportProperty property.
    Vector4 getViewport() const
    {
        return getProperty(ViewportProperty);
    }
    /// Sets the value of the #ViewportProperty property.
    void setViewport(Vector4 value)
    {
        setProperty(ViewportProperty, value);
    }

    /// Use the Viewport Mode property to set the coordinate type for the Viewport 2D node.
    /// \see setViewportMode(), getViewportMode(), ViewportProperty
    static PropertyType<ViewportMode> ViewportModeProperty;
    /// Gets the value of the #ViewportModeProperty property.
    ViewportMode getViewportMode() const
    {
        return getProperty(ViewportModeProperty);
    }
    /// Sets the value of the #ViewportModeProperty property.
    void setViewportMode(ViewportMode value)
    {
        setProperty(ViewportModeProperty, value);
    }

    /// Use the Scissor property to set the scissor test within the current rendering Viewport 2D node.
    /// You can define the scissor in either relative or absolute coordinates, the default is relative.
    /// Use the #ScissorModeProperty property to set the coordinate type.
    /// \see setScissor(), getScissor(), #ScissorModeProperty
    static PropertyType<Vector4> ScissorProperty;
    /// Gets the value of the #ScissorProperty property.
    Vector4 getScissor() const
    {
        return getProperty(ScissorProperty);
    }
    /// Sets the value of the #ScissorProperty property.
    void setScissor(Vector4 value)
    {
        setProperty(ScissorProperty, value);
    }

    /// Use the Scissor Mode property to set the scissor test coordinate mode.
    /// \see setScissorMode(), getScissorMode(), #ScissorProperty
    static PropertyType<ViewportMode> ScissorModeProperty;
    /// Gets the value of the #ScissorModeProperty property.
    ViewportMode getScissorMode() const
    {
        return getProperty(ScissorModeProperty);
    }
    /// Sets the value of the #ScissorModeProperty property.
    void setScissorMode(ViewportMode value)
    {
        setProperty(ScissorModeProperty, value);
    }

    /// \}

    KZ_METACLASS_BEGIN(PipelineStateRenderPass, RenderPass, "Kanzi.PipelineStateRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(BlendModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColorWriteModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(CullModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthTestFunctionProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthWriteEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScissorProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScissorModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilTestFunctionProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilReferenceValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilMaskProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilFailOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilPassDepthFailOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilPassDepthPassOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilWriteEnabledProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a Pipeline State Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Pipeline State Render Pass.
    /// \return The created Pipeline State Render Pass.
    static PipelineStateRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name of the Pipeline State Render Pass.
    explicit PipelineStateRenderPass(Domain* domain, string_view name);

    /// Push the color or blend state into the composition stack.
    /// \param compositionStack Composition stack to use.
    /// \return True if state was pushed.
    bool pushColorBlend(CompositionStack& compositionStack);

    /// Push the depth or stencil state into the composition stack.
    /// \param compositionStack Composition stack to use.
    /// \return True if state was pushed.
    bool pushDepthStencil(CompositionStack& compositionStack);

    /// Push the rasterization state into the composition stack.
    /// \param compositionStack Composition stack to use.
    /// \return True if state was pushed.
    bool pushRasterization(CompositionStack& compositionStack);

    /// Push the Viewport 2D scissor state into the composition stack.
    /// Effectively pushes new composition area.
    /// \param compositionStack Composition stack to use.
    /// \return True if state was pushed.
    bool pushViewportScissor(CompositionStack& compositionStack);

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

    /// RenderPass::requiresDepthBuffer() implementation.
    virtual CompositionRequirements getCompositionRequirements() const KZ_OVERRIDE;
};

} // namespace kanzi

#endif // KZ_PIPELINE_STATE_RENDER_PASS_HPP

#endif
