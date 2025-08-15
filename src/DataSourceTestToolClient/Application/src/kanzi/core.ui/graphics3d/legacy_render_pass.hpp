// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LEGACY_RENDER_PASS_HPP
#define KZ_LEGACY_RENDER_PASS_HPP

#ifdef KANZI_FEATURE_3D

#include <kanzi/core.ui/platform/graphics_backend/gl/renderer3d.hpp>
#include <kanzi/core.ui/graphics3d/render_pass.hpp>

/// Default value for render pass depth clear.
#define KZU_RENDER_PASS_DEFAULT_DEPTH_CLEAR_VALUE 1.0f

namespace kanzi
{

// Forward declaration.
struct KzuScissor;
class LegacyRenderPass;

/// LegacyRenderpass shared pointer type.
typedef shared_ptr<LegacyRenderPass> LegacyRenderPassSharedPtr;

/// Enumeration for viewport coordinate unit type (exact pixel coordinates / percentages from window)
enum KzuViewportCoordinateType
{
    // Note that these values must be synchronized with the corresponding enums in the tool.
    KZU_VIEWPORT_COORDINATE_ABSOLUTE = 0, ///< Absolute viewport coordinates, i.e. pixel values.
    KZU_VIEWPORT_COORDINATE_RELATIVE = 1  ///< Relative viewport coordinates, i.e. percentages of render target width & height.
};

/// Structure for viewport.
struct KzuViewport
{
    float x;                                  ///< X coordinate of view port
    float y;                                  ///< Y coordinate of view port
    float width;                              ///< Width of view port
    float height;                             ///< Height of view port
    KzuViewportCoordinateType coordinateType; ///< Type of viewport coordinates
};

/// Legacy Render Pass is phased out in favor of specialized render passes that perform
/// individual operations, which are combined in a Legacy Render Pass into a single render pass.
///
/// \see #BlitRenderPass, #ClearRenderPass, #CompositionTargetRenderPass, #DrawObjectsRenderPass,
/// #PipelineStateRenderPass
class KANZI_API LegacyRenderPass : public RenderPass
{
public:
    /// Framebuffer target for set framebuffers.
    enum FramebufferTarget
    {
        /// Framebuffer that is used for rendering to in the render pass
        FramebufferTargetDraw = 0,

        /// Framebuffer that is multisample resolve destination after render pass
        FramebufferTargetMultisampleResolve,

        /// Number of valid values for FramebufferTarget enum
        FramebufferTargetCount
    };

    /// RenderTargetTexture attachments to invalidate after Renderpass
    enum InvalidateAttachments
    {
        /// Do not invalidate any attachments
        InvalidateAttachmentsNone = 0,

        /// Invalidate color attachments
        InvalidateAttachmentsColor = 1,

        /// Invalidate depth/stencil attachment
        InvalidateAttachmentsDepthStencil = 2,

        /// Invalidate all attachments
        InvalidateAttachmentsAll = 3
    };

    /// \name Properties
    /// \{
#include "legacy_render_pass_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(LegacyRenderPass, RenderPass, "Kanzi.LegacyRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(FlushAfterRenderProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassCameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassObjectSourceProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassMaterialProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetColor0Property)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetColor1Property)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetColor2Property)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetColor3Property)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetDepthStencilProperty)
        KZ_METACLASS_PROPERTY_TYPE(FrustumCullingOnProperty)
        KZ_METACLASS_PROPERTY_TYPE(CullModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderOnceProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color0IntegerClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color0FloatClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color1IntegerClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color1FloatClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color2IntegerClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color2FloatClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color3IntegerClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color3FloatClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColorBufferClearColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color1ColorClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color2ColorClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(Color3ColorClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColorBufferClearEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColorWriteModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthBufferClearEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthBufferClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthBufferTestEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthBufferWriteEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilBufferClearEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilBufferClearValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilFailOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilPassDepthFailOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilPassDepthPassOperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilFunctionProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilFunctionReferenceValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilFunctionReferenceMaskProperty)
        KZ_METACLASS_PROPERTY_TYPE(StencilBufferTestEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorXProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorYProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassScissorTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetMipmapLevelProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetGenerateMipmapProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetResolveProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassRenderTargetInvalidateAttachmentsProperty)
        KZ_METACLASS_PROPERTY_TYPE(ComposerEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportXProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportYProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(ViewportTypeProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a render pass.
    ///
    /// \param domain Domain to use.
    /// \param name Render pass name.
    /// \return Newly created render pass.
    static LegacyRenderPassSharedPtr create(Domain* domain, string_view name = "");

    void applyBufferSettingsAndCulling(Renderer3D& userRenderer) const;

    /// Sets an object source for render pass.
    void setObjectSource(ObjectSourceSharedPtr objectSource);

    /// Gets object source from render pass.
    KzuObjectSource* getObjectSource() const;

    // Sets a color buffer for render pass.
    void setColorBuffer(bool clearEnabled, ColorRGBA clearColor, GraphicsColorWriteMode writeMode);

    /// Sets a depth buffer for render pass.
    /// \param depthClearEnabled Is depth buffer cleared on beginning of this renderpass.
    /// \param clearValue clearValue clear value used if clearing enabled, use KZU_RENDER_PASS_DEFAULT_DEPTH_CLEAR_VALUE by default.
    /// \param depthTestEnabled Depth testing enabled / disabled.
    /// \param depthWriteEnabled Writing to depth buffer enabled / disabled.
    void setDepthBuffer(bool depthClearEnabled, float clearValue, bool depthTestEnabled, bool depthWriteEnabled);

    /// Sets a stencil buffer for render pass.
    void setStencilBuffer(
        bool stencilClearEnabled, unsigned int clearValue, bool stencilTestEnabled, 
        GraphicsStencilOperation stencilModeSfail,
        GraphicsStencilOperation stencilModeDPfail,
        GraphicsStencilOperation stencilModeDPpass,
        GraphicsCompareFunction stencilFunction
    );

    /// Sets the view port's size in absolute coordinates (pixels)
    void setViewportAbsolute(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    /// Sets the view port's size in coordinates relative to screen size (0.f = left, 1.f = right) (0.f = top, 1.f = bottom)
    void setViewportRelative(float x, float y, float width, float height);

    void iterateTransformedObjects(Renderer3D& renderer, const KzcDynamicArray* transformedObjects, Renderer3D::ApplyNodeFunction applyFunction);

    // Resource interface

    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// RenderPass::onLoaded() implementation.
    virtual void onLoaded() KZ_OVERRIDE;

    /// Initialize render pass. Applies object source and framebuffer settings.
    void initialize();

    /// Obsolete composer interface.
    void applyOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack);
    bool getResolveAfter() const { return isRenderPassRenderTargetResolve(); }
    bool getGenerateMipmapAfter() const { return isRenderPassRenderTargetGenerateMipmap(); }
    unsigned int getMipmapLevel() const { return static_cast<unsigned int>(getRenderPassRenderTargetMipmapLevel()); }
    InvalidateAttachments getInvalidateAttachments() const { return InvalidateAttachmentsNone; }
    void reset();
    void setFramebuffer(FramebufferTarget target, FramebufferSharedPtr framebuffer);
    FramebufferSharedPtr getFramebuffer(FramebufferTarget target) const;

    /// RenderPass::requiresDepthBuffer() implementation.
    virtual CompositionRequirements getCompositionRequirements() const KZ_OVERRIDE;

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name Name of the Legacy Render Pass.
    explicit LegacyRenderPass(Domain* domain, string_view name = "");

    /// Apply camera and viewport for a render pass.
    ///
    /// \param userRenderer Renderer to use.
    /// \param transformedCameraNode Camera node.
    /// \param compositionStack Current composition stack.
    /// \param viewport Render pass viewport settings.
    /// \param scissor Render pass scissor settings.
    void applyCameraAndViewport(Renderer3D& userRenderer, const KzuTransformedObjectNode* transformedCameraNode,
                                CompositionStack& compositionStack, const KzuViewport* viewport, const KzuScissor& scissor);

    /// Updates framebuffer based on render target texture property
    void updateFramebuffer();

    ColorRGBA getColorClearValueColor(unsigned int buffer) const;
    Vector4 getColorClearValueInteger(unsigned int buffer) const;
    Vector4 getColorClearValueFloat(unsigned int buffer) const;
    ResourceSharedPtr getRenderPassRenderTargetColorResourceID(unsigned int buffer) const;

    void addColorBufferClear(Renderer* renderer, unsigned int drawBuffer, SurfaceSharedPtr surface) const;

    /// Calculate projection matrix.
    ///
    /// \param cameraNode Camera to use.
    /// \param viewportSize Current viewport size.
    virtual Matrix4x4 calculateProjectionMatrixOverride(Camera& cameraNode, Vector2 viewportSize);

    static void applyLight(Renderer3D& renderer, RenderPass& renderPass, KzuTransformedObjectNode& transformedNode);

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;
    /// RenderPass::renderMeshOverride() implementation.
    virtual void renderMeshOverride(Node3D& node, Morph* morph, Mesh& mesh, unsigned int clusterIndex, MaterialRenderer& materialRenderer) KZ_OVERRIDE;

private:
    // Data members
    ObjectSourceSharedPtr   m_objectSource;                             ///< Object source for render pass.
    bool                    m_frameBufferViewportCalculatedFromWindow;  ///< Is frame buffer viewport calculated from window or framebuffer dimensions.
    bool                    m_renderOnce;                               ///< If true render pass is in state where it is rendered once and disabled after that.

    // Filters for getting only certain types of objects from the main object source.
    FilterObjectSourceSharedPtr m_lodObjectSource;          ///< LOD object source.
    FilterObjectSourceSharedPtr m_lightObjectSource;        ///< Light object source.
    FilterObjectSourceSharedPtr m_renderableObjectSource;   ///< Renderable object source.
    FilterObjectSourceSharedPtr m_frustumCullObjectSource;  ///< Frustum cull object source for renderables.
    bool                        m_renderingAllowed;         ///< Specifies if rendering for this render pass is allowed. Can be false if for example render once is enabled, and 1 frame has passed.

    /// Legacy render pass explicit render target.
    FramebufferSharedPtr m_renderTarget;
    /// Legacy render pass framebuffers.
    array<FramebufferSharedPtr, FramebufferTargetCount> m_framebuffers;
};

} // namespace kanzi

#endif

#endif // KZ_LEGACY_RENDER_PASS_HPP
