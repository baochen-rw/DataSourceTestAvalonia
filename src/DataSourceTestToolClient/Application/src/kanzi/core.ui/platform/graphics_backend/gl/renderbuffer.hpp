// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDERBUFFER_HPP
#define KZ_RENDERBUFFER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_renderbuffer_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/surface.hpp>

namespace kanzi
{

class Domain;
class Renderer;
class Framebuffer;
class Renderbuffer;

/// Renderbuffer shared pointer type.
typedef shared_ptr<Renderbuffer> RenderbufferSharedPtr;

/// Renderbuffers provide the images that can be rendered to by attaching them to the framebuffer as color or depth stencil images.
/// Unlike textures, you cannot access renderbuffers using the samplers from shaders. When you direct rendering to a framebuffer,
/// the depth and stencil tests require either renderbuffer or texture attached to the framebuffer.
///
/// You can read the content of renderbuffers with the ReadPixels() function.
class KANZI_API Renderbuffer : public Surface
{
public:
    /// Renderbuffer creation parameters
    struct KANZI_API CreateInfo
    {
        /// Status of Renderbuffer creation parameters, returned as result of validate()
        enum Status
        {
            /// Renderbuffer creation parameters use GraphicsFormat that is not supported by the graphics device.
            StatusUnsupportedFormat,

            /// Renderbuffer creation parameters request Renderbuffer with zero width and/or height. Minimum
            /// size of Renderbuffers is 1 by 1.
            StatusInvalidMinimumSize,

            /// Renderbuffer creation parameters request renderbuffer size that exceeds size supported by the graphics device.
            StatusInvalidMaximumSize,

            /// Renderbuffer creation parameters request number of samples that exceeds number of samples supported by the graphics device.
            StatusUnsupportedSampleCount,

            /// Rebderbuffer creation parameters are valid and can be used to create a Renderbuffer.
            StatusValid
        };

        /// Constructor for Renderbuffer creation parameters.
        explicit CreateInfo();

        /// Constructor for Renderbuffer creation parameters.
        /// \param width Width of renderbuffer in pixels.
        /// \param height Height of renderbuffer in pixels.
        /// \param format Requested GraphicsFormat for the Renderbuffer.
        /// \param sampleCount Number of multisample samples.
        explicit CreateInfo(unsigned int width, unsigned int height, GraphicsFormat format, unsigned int sampleCount);

        /// Constructor for Renderbuffer creation parameters.
        /// \param width Width of renderbuffer in pixels.
        /// \param height Height of renderbuffer in pixels.
        /// \param format Requested GraphicsFormat for the Renderbuffer.
        explicit CreateInfo(unsigned int width, unsigned int height, GraphicsFormat format);

        /// Perform validation of renderbuffer creation parameters.
        /// You can call validate() to see if renderbuffer creation parameters are valid before you pass the creation parameters to Renderbuffer::create().
        /// \param renderer Renderer to validate with.
        /// \return StatusValid if these creation parameters can be used to create a new Renderbuffer.
        ///         Otherwise a reason code for why this CreateInfo cannot be used to create a new Renderbuffer.
        Status validate(Renderer* renderer) const;

        /// Requested width for the Renderbuffer in pixels.
        unsigned int width;

        /// Requested height for the Renderbuffer in pixels.
        unsigned int height;

        /// Requested GraphicsFormat for the Renderbuffer.
        GraphicsFormat format;

        /// Requested number of samples for the Renderbuffer.
        unsigned int sampleCount;
    };

    /// Construct a Renderbuffer with specified creation parameters.
    /// \param domain Domain
    /// \param createInfo Renderbuffer creation parameters.
    /// \param name Name
    explicit Renderbuffer(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Create a Renderbuffer with the provided creation parameters.
    /// \param domain Domain
    /// \param createInfo Renderbuffer creation parameters.
    /// \param name
    /// \return Newly created Renderbuffer
    static RenderbufferSharedPtr create(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Create a Renderbuffer with the provided creation parameters.
    /// \param domain Domain
    /// \param createInfo Renderbuffer creation parameters.
    /// \return Newly created Renderbuffer
    static RenderbufferSharedPtr create(Domain* domain, const CreateInfo& createInfo);

    /// Query the graphics device handle of the Renderbuffer.
    /// \return Graphics device handle of the Renderbuffer.
    unsigned int getNativeHandle() const;

protected:
    // GPUResource interface
    virtual void invalidateOverride() KZ_OVERRIDE;

    virtual void attachOverride(Usage usage, APIAttachment apiAttachment, Face face, unsigned int mipmapLevel) KZ_OVERRIDE;
    virtual GraphicsFormat getFormatOverride() const KZ_OVERRIDE;
    virtual unsigned int getFeaturesOverride() const KZ_OVERRIDE;
    virtual unsigned int getRenderTargetSampleCountOverride() const KZ_OVERRIDE;
    virtual unsigned int getWidthOverride() const KZ_OVERRIDE;
    virtual unsigned int getHeightOverride() const KZ_OVERRIDE;
    virtual unsigned int getSliceCountOverride() const KZ_OVERRIDE;
    virtual unsigned int getFaceCountOverride() const KZ_OVERRIDE;
    virtual unsigned int getMipmapLevelCountOverride() const KZ_OVERRIDE;

    // GPUResource interface
    virtual bool isDeployedOverride() const KZ_OVERRIDE;

    /// Resource::reloadOverride() implementation.
    virtual void reloadOverride() KZ_OVERRIDE;

    virtual unsigned int getGPUMemoryUsageOverride() const KZ_OVERRIDE;

private:
    explicit Renderbuffer(const Renderbuffer&) KZ_DELETED_FUNCTION;
    Renderbuffer& operator=(const Renderbuffer&) KZ_DELETED_FUNCTION;

    friend void swap(Renderbuffer& buffer1, Renderbuffer& buffer2);

    /// Graphics device handle of the Renderbuffer.
    GLRenderbufferHandle m_glHandle;

    /// Number of multisample samples.
    unsigned int m_sampleCount;

    /// Surface graphics format.
    GraphicsFormat m_format;

    /// Surface features.
    unsigned int m_features;

    /// Surface width.
    unsigned int m_width;

    /// Surface height.
    unsigned int m_height;
};

inline void swap(Renderbuffer& buffer1, Renderbuffer& buffer2)
{
    using std::swap;
    swap(buffer1.m_glHandle, buffer2.m_glHandle);
    swap(buffer1.m_sampleCount, buffer2.m_sampleCount);
    swap(buffer1.m_format, buffer2.m_format);
    swap(buffer1.m_features, buffer2.m_features);
    swap(buffer1.m_width, buffer2.m_width);
    swap(buffer1.m_height, buffer2.m_height);
}

}

#endif
