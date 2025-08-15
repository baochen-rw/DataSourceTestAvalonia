// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FRAMEBUFFER_HPP
#define KZ_FRAMEBUFFER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_framebuffer_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/renderbuffer.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/surface.hpp>
#include <kanzi/core/cpp/array.hpp>

namespace kanzi
{

// Forward declarations.
class Domain;
class Framebuffer;
class Texture;
typedef shared_ptr<Texture> TextureSharedPtr;

/// Framebuffer shared pointer type.
typedef shared_ptr<Framebuffer> FramebufferSharedPtr;

/// Framebuffer allows the rendering to the user-specified texture or renderbuffer, instead of rendering directly to the window.
/// Framebuffer must have at least one Surface (Texture or Renderbuffer) attached to it.
/// Depth and stencil tests require that a Surface (typically Renderbuffer) is attached to the depth and stencil attachment point.
class KANZI_API Framebuffer : public GPUResource
{
public:
    enum AttachmentPoint
    {
        /// Color buffer 0 framebuffer attachment point (OpenGL ES 2 compatible)
        AttachmentPointColor0,

        /// Color buffer 1 framebuffer attachment point (Requires OpenGL ES 3)
        AttachmentPointColor1,

        /// Color buffer 2 framebuffer attachment point (Requires OpenGL ES 3)
        AttachmentPointColor2,

        /// Color buffer 3 framebuffer attachment point (Requires OpenGL ES 3)
        AttachmentPointColor3,

        /// Depth and stencil framebuffer attachment point
        AttachmentPointDepthStencil,

        /// Number of attachment points in Framebuffer
        AttachmentPointCount
    };

    /// Framebuffer attachment settings
    struct Attachment
    {
        explicit Attachment();

        /// Construct Attachment from 2D Texture base level image.
        /// \param texture Texture to use.
        explicit Attachment(TextureSharedPtr texture);

        /// Construct Attachment from a 2D texture.
        /// \param texture Texture to use.
        /// \param mipmapLevel Mipmap level of texture to use.
        explicit Attachment(TextureSharedPtr texture, unsigned int mipmapLevel);

        /// Construct Attachment from a 2D texture.
        /// \param texture Texture to use.
        /// \param mipmapLevel Mipmap level of texture to use.
        explicit Attachment(TextureSharedPtr texture, Surface::Face face, unsigned int mipmapLevel);

        /// Construct Attachment from Renderbuffer.
        /// \param renderbuffer Renderbuffer to use.
        explicit Attachment(RenderbufferSharedPtr renderbuffer);

        /// Surface. This can be either Texture or Renderbuffer.
        SurfaceSharedPtr surface;

        /// For cubemap textures, the cubemap face to use.
        Surface::Face face;

        /// Mipmap level to use, for Textures.
        unsigned int mipmapLevel;
    };

    enum AttachmentBit
    {
        AttachmentBitColor0 = (1u << AttachmentPointColor0),
        AttachmentBitColor1 = (1u << AttachmentPointColor1),
        AttachmentBitColor2 = (1u << AttachmentPointColor2),
        AttachmentBitColor3 = (1u << AttachmentPointColor3),
        AttachmentBitDepthStencil = (1u << AttachmentPointDepthStencil)
    };

    /// Framebuffer target selects draw or read framebuffer, or both
    enum Target
    {
        /// Both read and draw framebuffers.
        TargetReadAndDraw = 0,

        /// Read framebuffe
        TargetRead,

        /// Draw framebuffer
        TargetDraw
    };

    /// Framebuffer creation parameters
    struct KANZI_API CreateInfo
    {
        /// Status of Framebuffer creation parameters, returned as result of validate().
        enum Status
        {
            /// Color buffers must be attached without gaps in used attachment points.
            StatusMissingColorAttachments,

            /// Multiple rendertargets are not supported by graphics device.
            /// \note OpenGL ES 3 is required for multiple render targets.
            StatusMultipleRenderTargetsNotSupported,

            /// Attachment uses graphics format which is not supported.
            StatusAttachmentUnsupportedFormat,

            /// An attachment has non-existent cubemap face setting.
            StatusInvalidFace,

            /// An attachment has non-existent mipmap level setting.
            StatusInvalidMipmapLevel,

            /// Requested Framebuffer usage is not valid.
            StatusInvalidUsage,

            /// Number of samples in creation parameters do not match.
            StatusSampleCountMismatch,

            /// Framebuffer creation parameters are valid and can be used to create a new Framebuffer.
            StatusValid
        };

        explicit CreateInfo(Surface::Usage usage);

        /// Set attachment, cloning existing attachment.
        /// \param attachmentPoint Attachment point to set.
        /// \param attachment Existing attachment.
        void setAttachment(AttachmentPoint attachmentPoint, const Attachment& attachment);

        /// Set attachment for specified attachment point. The surface is assumed to be non-cubemap
        /// Texture or Renderbuffer. If surface is Texture, the base level will be used.
        /// \param attachmentPoint Attachment point to set.
        /// \param surface Surface to place in the attachment point. This can be either Texture or Renderbuffer.
        void setAttachment(AttachmentPoint attachmentPoint, SurfaceSharedPtr surface);

        /// Set attachment for specified attachment point.
        /// \param attachmentPoint Attachment point to set.
        /// \param texture Texture to place in the attachment point.
        /// \param mipmapLevel Mipmap level of texture to place in the attachment point.
        void setAttachment(AttachmentPoint attachmentPoint, TextureSharedPtr texture, unsigned int mipmapLevel);

        /// Set attachment for specified attachment point.
        /// \param attachmentPoint Attachment point to set.
        /// \param texture Texture to place in the attachment point. This should be a cubemap texture.
        /// \param face Cubemap face.
        /// \param mipmapLevel Mipmap level of texture to place in the attachment point.
        void setAttachment(AttachmentPoint attachmentPoint, TextureSharedPtr texture, Surface::Face face, unsigned int mipmapLevel);

        /// Get surface for specified attachment point.
        /// \param attachmentPoint Attachment point to query.
        /// \return Surface set to the attachmentpoint.
        SurfaceSharedPtr getSurface(AttachmentPoint attachmentPoint) const;

        /// Get attachment information for specified attachment point.
        /// \param attachmentPoint Attachment point to query.
        /// \return Surface set to the attachmentpoint.
        Attachment getAttachment(AttachmentPoint attachmentPoint) const;

        /// Perform validation of framebuffer creation parameters.
        /// You can call validate() to see if framebuffer creation parameters are valid before you pass the creation parameters to Framebuffer::create().
        /// \param renderer Renderer to validate with.
        /// \return StatusValid if these creation parameters can be used to create a new Framebuffer.
        ///         Otherwise a reason code for why this CreateInfo cannot be used to create a new Framebuffer.
        Status validate(Renderer* renderer) const;

        /// How Framebuffer will be used.
        Surface::Usage usage;

        array<Attachment, AttachmentPointCount> attachments;
    };

    explicit Framebuffer(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Creates the framebuffer from specified attachments.
    /// The framebuffer is deployed and ready to use.
    /// 
    /// \param domain Domain for the graphics resource
    /// \param createInfo Width of the framebuffer
    /// \param name Name
    /// 
    /// \return The created framebuffer
    static FramebufferSharedPtr create(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Creates the framebuffer from specified attachments.
    /// The framebuffer is deployed and ready to use.
    /// 
    /// \param domain Domain for the graphics resource
    /// \param createInfo Width of the framebuffer
    /// 
    /// \return The created framebuffer
    static FramebufferSharedPtr create(Domain* domain, const CreateInfo& createInfo);

    /// Returns the attachment from the framebuffer for the specified attachment point.
    ///
    /// \param attachment Attachment point to examine
    ///
    /// \return The attachment for the specified attachment point in the framebuffer
    SurfaceSharedPtr getAttachment(AttachmentPoint attachment) const;

    /// Returns the attachment as texture from the framebuffer.
    ///
    /// \param attachment Attachment point to query from the framebuffer. For OpenGL ES 2, either Framebuffer::AttachmentColor0 or Framebuffer::AttachmentDepthStencil.
    ///
    /// \return Texture attached to the specified attachment point, or empty if there is no texture.
    TextureSharedPtr getTexture(AttachmentPoint attachment) const;

    /// Returns the common width of the framebuffer.
    ///
    /// \return The width of the framebuffer in pixels
    unsigned int getCommonWidth() const;

    /// Returns the common height of the framebuffer
    ///
    /// \return The height of the framebuffer in pixels
    unsigned int getCommonHeight() const;

    /// Returns the common sample count of the framebuffer.
    ///
    /// \return The number of multisample samples in the framebuffer. In OpenGL ES 2 this is zero.
    unsigned int getCommonSampleCount() const;

    /// Returns Framebuffer usage.
    /// \return Usage for framebuffer.
    Surface::Usage getUsage() const;

    /// Returns the GL API object handle for the framebuffer.
    ///
    /// \return GL API framebuffer object handle
    unsigned int getNativeHandle() const;

    // Resource interface
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Tell if framebuffer has given attachment.
    ///
    /// \param attachment Attachment to check for.
    /// \return True if yes, false if no.
    bool hasAttachment(AttachmentPoint attachmentPoint) const
    {
        return getAttachment(attachmentPoint) ? true : false;
    }

protected:
    // GPUResource interface
    virtual void invalidateOverride() KZ_OVERRIDE;

    virtual bool isDeployedOverride() const KZ_OVERRIDE;

    /// Resource::reloadOverride() implementation.
    virtual void reloadOverride() KZ_OVERRIDE;

private:
    // Helper functions
    static void addClearColor(Renderer* renderer, unsigned int drawBuffer, SurfaceSharedPtr surface);

    static void deploy(Renderer* renderer, const CreateInfo& createInfo, unsigned int framebuffer);

    /// GL framebuffer object name
    GLFramebufferHandle m_glHandle;

    /// Maximum width that is supported by all attachments (width of the attachment that has smallest width).
    unsigned int m_commonWidth;

    /// Maximum height that is supported by all attachment (height of the attachment that has smallest height).
    unsigned int m_commonHeight;

    /// Number of samples, shared by all attachments
    unsigned int m_commonSampleCount;

    /// Information about attachments
    array<Attachment, AttachmentPointCount> m_attachments;

    Surface::Usage m_usage;
};

/// Returns a human readable description for Framebuffer::CreateInfo::Status.
FixedString toFixedString(Framebuffer::CreateInfo::Status status);

/// Checks if size is valid framebuffer size
KANZI_API bool isValidFramebufferSize(float size);
KANZI_API bool isValidFramebufferSize(Vector2 const &size);
KANZI_API bool isValidFramebufferSize(float width, float height);

KANZI_API unsigned toValidFramebufferSize(float size);

KANZI_API unsigned int getFeatures(Framebuffer::AttachmentPoint attachmentPoint);

} // namespace kanzi

#endif // KZ_FRAMEBUFFER_HPP
