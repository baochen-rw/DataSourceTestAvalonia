// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COMPOSITION_TARGET_RENDER_PASS_HPP
#define KZ_COMPOSITION_TARGET_RENDER_PASS_HPP

#include <kanzi/core.ui/graphics3d/render_pass.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/composition_manager.hpp>

namespace kanzi
{

// Forward declaration.
class CompositionTargetRenderPass;
class Texture;
typedef shared_ptr<Texture> TextureSharedPtr;

/// LegacyRenderpass shared pointer type.
typedef shared_ptr<CompositionTargetRenderPass> CompositionTargetRenderPassSharedPtr;

/// Use the Composition Target Render Pass to set a composition target and render all
/// descendant render passes to the composition target that the Composition Target Render
/// Pass created. After Kanzi renders the descendant render passes of a Composition Target
/// Render Pass, the Composition Target Render Pass restores the earlier composition settings.
///
/// Configuring the composition target
/// ======================
///
/// Composition Target Render Pass by default creates a composition target whose size is the same
/// as the size of the current Viewport 2D node using the RGBA pixel format and depth buffer.
/// To configure the composition target, you can:
/// - Set the pixel format of the composition target with the #PixelFormatProperty.
/// \snippet test_render_pass_snippets.cpp Composition target render pass pixel format
/// - Set the size of the composition target in relation to the size of the current Viewport 2D node with the 
/// #ResolutionMultiplierProperty and #ResolutionDivisorProperty properties. These properties set a fractional number
/// (rational number) which Kanzi uses to multiply the size of the current Viewport 2D node.
/// \snippet test_render_pass_snippets.cpp Composition target render pass size
/// - Set the addressing mode of the composition target with the #AddressingModeProperty property.
/// - Set the number of samples for each pixel or disable multisampling with the #MultisampleLevelProperty.
///
/// Using custom render target textures
/// =============================
///
/// You can set a Composition Target Render Pass to use a composition target texture that you create somwhere else
/// with the #CompositionTargetProperty. The render pass for which you set the composition target texture with this
/// property does not create its own render target.
/// \snippet test_render_pass_snippets.cpp Composition target render pass custom render target
///
/// For example, to use a custom render target texture, bind the #CompositionTargetProperty property of a
/// Composition Target Render Pass to properties of other render passes. See #BlitRenderPass.
///
/// Accessing the composition target result
/// ==================
///
/// You can access the result of a Composition Target Render Pass:
/// \snippet test_render_pass_snippets.cpp Composition target render pass result
///
/// The texture that the #getCompositionResult() method returns is not necessarily the texture that
/// a Composition Target Render Pass rendered, or the texture set to the #CompositionTargetProperty.
/// For example, if you use multisampling, the #getCompositionResult() method returns the target,
/// where it resolves multiple samples into a 2D texture.
///
/// If a Composition Target Render Pass was not executed, the result of the #getCompositionResult() method is
/// undefined.
///
/// Examples
/// ========
///
/// To use a Composition Target Render Pass with a custom render target with automatic size:
/// \snippet test_texture.cpp node2d render target automatic size render target example
class KANZI_API CompositionTargetRenderPass : public RenderPass
{
public:

    /// \name Properties
    /// \{

    /// Use the Composition Target property to set the target to which you want to render the result of this render pass.
    /// The default value is ResourceSharedPtr().
    /// \see setCompositionTarget(), getCompositionTarget()
    static PropertyType<ResourceSharedPtr> CompositionTargetProperty;
    /// Gets the value of the #CompositionTargetProperty property.
    /// \return The value of the Composition Target property.
    /// \see setCompositionTarget()
    TextureSharedPtr getCompositionTarget() const
    {
        return dynamic_pointer_cast<Texture>(getProperty(CompositionTargetProperty));
    }
    /// Sets the value of the #CompositionTargetProperty property.
    /// \param value The new value of the Composition Target property.
    /// \see getCompositionTarget()
    void setCompositionTarget(TextureSharedPtr value)
    {
        setProperty(CompositionTargetProperty, static_pointer_cast<Resource>(value));
    }

    /// Use the Resolution Multiplier property to set the resolution multiplier for the automatically
    /// created composition target textures, which together with the #ResolutionDivisorProperty property,
    /// sets the size of the composition target in relation to the size of the current Viewport 2D node.
    /// The default value is 1.
    /// \see getResolutionMultiplier(), getResolutionMultiplier(), #ResolutionDivisorProperty
    static PropertyType<int> ResolutionMultiplierProperty;
    /// Gets the value of the #ResolutionMultiplierProperty property.
    /// \return The value of the Resolution Multiplier property.
    /// \see setResolutionMultiplier()
    int getResolutionMultiplier() const
    {
        return getProperty(ResolutionMultiplierProperty);
    }
    /// Sets the value of the #ResolutionMultiplierProperty property.
    /// \param value The new value of the Resolution Multiplier property.
    /// \see getResolutionMultiplier()
    void setResolutionMultiplier(int value)
    {
        setProperty(ResolutionMultiplierProperty, value);
    }

    /// Use the Resolution Divisor property to set the resolution divisor for the automatically
    /// created composition target textures, which together with the #ResolutionMultiplierProperty property,
    /// sets the size of the composition target in relation to the size of the current Viewport 2D node.
    /// The default value is 1.
    /// \see setResolutionDivisor(), getResolutionDivisor(), #ResolutionMultiplierProperty
    static PropertyType<int> ResolutionDivisorProperty;
    /// Gets the value of the #ResolutionDivisorProperty property.
    /// \return The value of the Resolution Divisor property.
    /// \see setResolutionDivisor
    int getResolutionDivisor() const
    {
        return getProperty(ResolutionDivisorProperty);
    }
    /// Sets the value of the #ResolutionDivisorProperty property.
    /// \param value The new value of the Resolution Divisor property.
    /// \see getResolutionDivisor
    void setResolutionDivisor(int value)
    {
        setProperty(ResolutionDivisorProperty, value);
    }

    /// Use the Pixel Format property to set on the GPU the target pixel format of the automatically
    /// created composition target textures.
    /// The default value is RGBA.
    /// \see getPixelFormat(), setPixelFormat()
    static PropertyType<GraphicsFormat> PixelFormatProperty;
    /// Gets the value of the #PixelFormatProperty property.
    /// \return The value of the Pixel Format property.
    /// \see setPixelFormat()
    GraphicsFormat getPixelFormat() const
    {
        return getProperty(PixelFormatProperty);
    }
    /// Sets value of the #PixelFormatProperty property.
    /// \param value The new value of the Pixel Format property.
    /// \see getPixelFormat()
    void setPixelFormat(GraphicsFormat value)
    {
        setProperty(PixelFormatProperty, value);
    }

    /// DepthTextureFormat property.
    /// If set, defines the format for the depth texture.
    /// If not set, depth texture will not be used and depth renderbuffer will be used if necessary.
    static PropertyType<GraphicsFormat> DepthTextureFormatProperty;
    /// Gets value of #DepthTextureFormatProperty.
    /// \return Property value.
    GraphicsFormat getDepthTextureFormat() const
    {
        return getProperty(DepthTextureFormatProperty);
    }
    /// Sets value of #DepthTextureFormatProperty.
    /// \param value New property value.
    void setDepthTextureFormat(GraphicsFormat value)
    {
        setProperty(DepthTextureFormatProperty, value);
    }

    /// Use the Addressing Mode property to set how Kanzi handles the texture coordinates
    /// the automatically generated composition target textures outside of the [0, 0] - [1, 1] rectangle:
    /// - #AddressingModeClamp confines the texture to the these coordinates and outside of these
    /// texture coordinates repeats the edge texels of the texture. This is the default value.
    /// - #AddressingModeWrap sets the texture to repeat outside of these coordinates.
    static PropertyType<Sampler::AddressingMode> AddressingModeProperty;

    /// Use the Filter Mode property to set how texels are sampled when using the composition target as a texture.
    /// - #FilterNearest means the color is taken from nearest texture sample.
    /// - #FilterLinear means the color is interpolated from neighboring texture samples.
    static PropertyType<Sampler::Filter> FilterModeProperty;
    /// Gets value of #FilterModeProperty.
    /// \return Property value.
    Sampler::Filter getFilterMode() const
    {
        return getProperty(FilterModeProperty);
    }
    /// Sets value of #FilterModeProperty.
    /// \param value New property value.
    void setFilterMode(Sampler::Filter value)
    {
        setProperty(FilterModeProperty, value);
    }

    /// MipmapMode property.
    /// The default value is #MipmapModeBase.
    static PropertyType<Sampler::MipmapMode> MipmapModeProperty;
    /// Gets value of #MipmapModeProperty.
    /// \return Property value.
    Sampler::MipmapMode getMipmapMode() const
    {
        return getProperty(MipmapModeProperty);
    }
    /// Sets value of #MipmapModeProperty.
    /// \param value New property value.
    void setMipmapMode(Sampler::MipmapMode value)
    {
        setProperty(MipmapModeProperty, value);
    }

    /// Use the Multisample Level property to set the number of samples you want to use for each
    /// output pixel of the automatically generated composition target textures.
    /// To disable multisampling, remove the property or set the property value to 1.
    /// The default value is 1.
    static PropertyType<int> MultisampleLevelProperty;
    /// Gets value of #MultisampleLevelProperty.
    /// \return Property value.
    int getMultisampleLevel() const
    {
        return getProperty(MultisampleLevelProperty);
    }
    /// Sets value of #MultisampleLevelProperty.
    /// \param value New property value.
    void setMultisampleLevel(int value)
    {
        setProperty(MultisampleLevelProperty, value);
    }

    /// Use the Resolve Immediately property to instruct the composition target render pass to resolve
    /// multisampling and generate mipmaps immediately after rendering as opposed to delaying resolve
    /// operations until the result composition target is referenced.
    /// The default value is false.
    static PropertyType<bool> ResolveImmediatelyProperty;
    /// Gets value of #ResolveImmediatelyProperty.
    /// \return Property value.
    bool isResolveImmediately() const
    {
        return getProperty(ResolveImmediatelyProperty);
    }
    /// Sets value of #ResolveImmediatelyProperty.
    /// \param value New property value.
    void setResolveImmediately(bool value)
    {
        setProperty(ResolveImmediatelyProperty, value);
    }

    /// Use the Depth Compare Function property to determine which function is used when comparing
    /// depth values with comparison samplers.
    /// The default value is GraphicsCompareFunctionDisabled.
    static PropertyType<GraphicsCompareFunction> DepthCompareFunctionProperty;
    /// Gets the value of #DepthCompareFunctionProperty.
    /// \return The value of the Depth Compare Function property.
    GraphicsCompareFunction getDepthCompareFunction() const
    {
        return getProperty(DepthCompareFunctionProperty);
    }
    /// Sets the value of the #DepthCompareFunctionProperty.
    /// \param value The value of the Depth Compare Function property.
    void setDepthCompareFunction(GraphicsCompareFunction value)
    {
        setProperty(DepthCompareFunctionProperty, value);
    }

    /// \}
    
    KZ_METACLASS_BEGIN(CompositionTargetRenderPass, RenderPass, "Kanzi.CompositionTargetRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(CompositionTargetProperty)
        KZ_METACLASS_PROPERTY_TYPE(ResolutionMultiplierProperty)
        KZ_METACLASS_PROPERTY_TYPE(ResolutionDivisorProperty)
        KZ_METACLASS_PROPERTY_TYPE(PixelFormatProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthTextureFormatProperty)
        KZ_METACLASS_PROPERTY_TYPE(AddressingModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(FilterModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(MipmapModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(MultisampleLevelProperty)
        KZ_METACLASS_PROPERTY_TYPE(ResolveImmediatelyProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthCompareFunctionProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a Composition Target Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Composition Target Render Pass.
    /// \return The created Composition Target Render Pass.
    static CompositionTargetRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the Composition Target Render Pass.
    explicit CompositionTargetRenderPass(Domain* domain, string_view name);

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

    /// RenderPass::getCompositionTarget() implementation.
    virtual TextureSharedPtr getCompositionResultOverride(Framebuffer::AttachmentPoint attachmentPoint) KZ_OVERRIDE;

    /// RenderPass::restoreResources() implementation.
    virtual void restoreResources() KZ_OVERRIDE;

    /// RenderPass::requiresDepthBuffer() implementation.
    virtual CompositionRequirements getCompositionRequirements() const KZ_OVERRIDE;

    /// Update temporary multisample draw target allocated.
    /// \param width Required width.
    /// \param height Required height.
    /// \param requiresDepth True if depth buffer is required, otherwise false.
    /// \param requiresStencil True if stencil buffer is required, otherwise false.
    /// \param samples The number of multisampling samples.
    void updateMultisampleDrawTarget(unsigned int width, unsigned int height, bool requiresDepth, bool requiresStencil, unsigned int samples);

    /// Update persistent result target allocated.
    /// \param width Required width.
    /// \param height Required height.
    /// \param requiresDepth True if depth buffer is required, otherwise false.
    /// \param requiresStencil True if stencil buffer is required, otherwise false.
    /// \param samples The number of multisampling samples. Mostly 0, unless using multisample extensions that do not need a separate resolve target.
    void updateResultTarget(unsigned int width, unsigned int height, bool requiresDepth, bool requiresStencil, unsigned int samples);

private:

    /// Composition target used as multisample resolve target.
    /// Created implicitly if #CompositionTargetProperty is not set or if it uses multisampling. 
    optional<CompositionManager::Target> m_resultTarget;
    /// Composition target used for drawing if multisampling is enabled.
    /// Acquired implicitly if #CompositionTargetProperty is not set and multisampling is enabled.
    optional<CompositionManager::Target> m_multisampleDrawTarget;

    /// Composition width used that will be resolved into composition target.
    unsigned int m_compositionWidth;
    /// Composition height used that will be resolved into composition target.
    unsigned int m_compositionHeight;
    /// Flag for whether the result target has been processed (if it needs processing).
    bool m_resultProcessed;
};

} // namespace kanzi

#endif // KZ_COMPOSITION_TARGET_RENDER_PASS_HPP
