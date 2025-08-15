// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SURFACE_HPP
#define KZ_SURFACE_HPP

#include <kanzi/core.ui/graphics3d/gpu_resource.hpp>
#include <kanzi/core.ui/graphics/format.hpp>

namespace kanzi
{

// Forward declarations.
class Domain;
class Renderer;
class Framebuffer;
class Surface;

/// Surface shared pointer type.
typedef shared_ptr<Surface> SurfaceSharedPtr;

/// Surfaces provide images for Framebuffers where to render to.
class KANZI_API Surface : public GPUResource
{
public:
    enum Usage
    {
        /// Framebuffer is used for rendering and potentially as multisample resolve source
        UsageRenderTarget,

        /// Framebuffer is used as multisample resolve destination
        UsageMultisampleResolveBlitDestination,
    };

    enum APIAttachment
    {
        /// Color buffer 0 GL attachment (OpenGL ES 2 compatible)
        APIAttachmentColor0,

        /// Color buffer 1 GL attachment (Requires OpenGL ES 3)
        APIAttachmentColor1,

        ///< Color buffer 2 GL attachment (Requires OpenGL ES 3)
        APIAttachmentColor2,

        /// Color buffer 3 GL attachment (Requires OpenGL ES 3) 
        APIAttachmentColor3,

        /// Depth buffer GL attachment
        APIAttachmentDepth,

        /// Stencil buffer GL attachment
        APIAttachmentStencil,

        APIAttachmentCount,

        /// Invalid GL attachment
        APIAttachmentInvalid
    };

    /// Texture face enumeration
    enum Face
    {
        /// Positive X
        FacePositiveX = 0,

        /// Negative X
        FaceNegativeX = 1,

        /// Positive Y
        FacePositiveY = 2,

        /// Negative Y
        FaceNegativeY = 3,

        /// Positive Z
        FacePositiveZ = 4,

        /// Negative Z
        FaceNegativeZ = 5,

        /// Default face, for non-cubemap textures
        FaceDefault = 0,
    };

    /// Attach surface to framebuffer
    /// \param framebuffer Framebuffer where Surface will be attached to.
    /// \param apiAttachment Attachment point in framebuffer where surface will be attached to.
    /// \param face Face of surface to attach. Ignored for non-cubemap texture or non-texture surfaces.
    /// \param mipmapLevel Mipmap level of surface to attach. Ignored for non-texture surfaces.
    void attach(Usage usage, APIAttachment apiAttachment, Face face, unsigned int mipmapLevel);

    /// Get GraphicsFormat of Surface
    GraphicsFormat getFormat() const;

    /// Get features for Surface.
    /// \see GraphicsFormatFeature
    unsigned int getFeatures() const;

    /// Get number of multisample samples for Surface
    unsigned int getRenderTargetSampleCount() const;

    /// Get width in pixels.
    unsigned int getWidth() const;

    /// Get height in pixels.
    unsigned int getHeight() const;

    /// Get number of slices
    unsigned int getSliceCount() const;

    /// Get number of faces. This should be six for cubemaps and one for everything else
    unsigned int getFaceCount() const;

    /// Get number of mipmap levels
    unsigned int getMipmapLevelCount() const;

protected:
    explicit Surface(Domain* domain, string_view name) :
        GPUResource(domain, name)
    {
    }

    virtual void attachOverride(Usage usage, APIAttachment apiAttachment, Face face, unsigned int mipmapLevel) = 0;
    virtual GraphicsFormat getFormatOverride() const = 0;
    virtual unsigned int getFeaturesOverride() const = 0;
    virtual unsigned int getRenderTargetSampleCountOverride() const = 0;
    virtual unsigned int getWidthOverride() const = 0;
    virtual unsigned int getHeightOverride() const = 0;
    virtual unsigned int getSliceCountOverride() const = 0;
    virtual unsigned int getFaceCountOverride() const = 0;
    virtual unsigned int getMipmapLevelCountOverride() const = 0;
};

} // namespace kanzi

#endif // KZ_SURFACE_HPP
