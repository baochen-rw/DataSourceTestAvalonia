// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_COMPOSITION_MANAGER_HPP
#define KZ_GL_COMPOSITION_MANAGER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/framebuffer.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/texture.hpp>

namespace kanzi
{

// Forward declarations.
class Renderer;
class ResourceManager;

/// Composition manager.
///
/// Used for storing and managing composition targets and keeping track of their use.
/// The rationale is to minimize memory used by composition targets.
class KANZI_API CompositionManager
{
public:

    /// Composition request class.
    /// Packs all attributes of a composition request.
    class Request
    {
    public:

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param depthStencilFormat Depth/stencil buffer format.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat) :
            m_width(width),
            m_height(height),
            m_samples(0),
            m_colorFeatures(GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(depthStencilFormat),
            m_addressingMode(Sampler::AddressingModeClamp),
            m_filterMode(Sampler::FilterLinear),
            m_mipmapMode(Sampler::MipmapModeBase),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param samples Requested multisample level.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, unsigned int samples) :
            m_width(width),
            m_height(height),
            m_samples(samples),
            m_colorFeatures((samples > 1) ? GraphicsFormatFeatureRenderbufferMask : GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(GraphicsFormatNone),
            m_addressingMode(Sampler::AddressingModeClamp),
            m_filterMode((samples > 1) ? Sampler::FilterNearest : Sampler::FilterLinear),
            m_mipmapMode(Sampler::MipmapModeBase),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
            kzAssert(!hasDepth(colorFormat));
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param depthStencilFormat Depth/stencil buffer format.
        /// \param samples Requested multisample level.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat, unsigned int samples) :
            m_width(width),
            m_height(height),
            m_samples(samples),
            m_colorFeatures((samples > 1) ? GraphicsFormatFeatureRenderbufferMask : GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(depthStencilFormat),
            m_addressingMode(Sampler::AddressingModeClamp),
            m_filterMode((samples > 1) ? Sampler::FilterNearest : Sampler::FilterLinear),
            m_mipmapMode(Sampler::MipmapModeBase),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFeatures Requested color features.
        /// \param colorFormat Color buffer format.
        /// \param depthFeatures Requested depth features.
        /// \param depthStencilFormat Depth/stencil buffer format.
        /// \param samples Requested multisample level.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormatFeature colorFeatures, GraphicsFormat colorFormat, GraphicsFormatFeature depthFeatures,
                GraphicsFormat depthStencilFormat, unsigned int samples) :
            m_width(width),
            m_height(height),
            m_samples(samples),
            m_colorFeatures(colorFeatures),
            m_colorFormat(colorFormat),
            m_depthFeatures(depthFeatures),
            m_depthStencilFormat(depthStencilFormat),
            m_addressingMode(Sampler::AddressingModeClamp),
            m_filterMode((samples > 1) ? Sampler::FilterNearest : Sampler::FilterLinear),
            m_mipmapMode(Sampler::MipmapModeBase),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param addressingMode Addressing mode used.
        /// \param mipmapMode Mipmap mode used.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, Sampler::AddressingMode addressingMode, Sampler::Filter filterMode,
                         Sampler::MipmapMode mipmapMode) :
            m_width(width),
            m_height(height),
            m_samples(0),
            m_colorFeatures(GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(GraphicsFormatNone),
            m_addressingMode(addressingMode),
            m_filterMode(filterMode),
            m_mipmapMode(mipmapMode),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
            kzAssert(!hasDepth(colorFormat));
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param depthStencilFormat Depth/stencil buffer format.
        /// \param addressingMode Addressing mode used.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat, Sampler::AddressingMode addressingMode) :
            m_width(width),
            m_height(height),
            m_samples(0),
            m_colorFeatures(GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(depthStencilFormat),
            m_addressingMode(addressingMode),
            m_filterMode(Sampler::FilterLinear),
            m_mipmapMode(Sampler::MipmapModeBase),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
        }

        /// Constructor.
        /// \param width Requested width.
        /// \param height Requested height.
        /// \param colorFormat Color buffer format.
        /// \param depthStencilFormat Depth/stencil buffer format.
        /// \param addressingMode Addressing mode used.
        /// \param mipmapMode Mipmap mode used.
        /// \param samples Requested multisample level.
        explicit Request(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat,
                                        Sampler::AddressingMode addressingMode, Sampler::MipmapMode mipmapMode, unsigned int samples) :
            m_width(width),
            m_height(height),
            m_samples(samples),
            m_colorFeatures((samples > 1) ? GraphicsFormatFeatureRenderbufferMask : GraphicsFormatFeatureTextureMask),
            m_colorFormat(colorFormat),
            m_depthFeatures(GraphicsFormatFeatureRenderbufferMask),
            m_depthStencilFormat(depthStencilFormat),
            m_addressingMode(addressingMode),
            m_filterMode((samples > 1) ? Sampler::FilterNearest : Sampler::FilterLinear),
            m_mipmapMode(mipmapMode),
            m_depthCompareFunction(GraphicsCompareFunctionDisabled)
        {
        }

        /// Gets required width.
        /// \return Width.
        unsigned int getWidth() const
        {
            return m_width;
        }
        /// Gets required height.
        /// \return Height.
        unsigned int getHeight() const
        {
            return m_height;
        }

        /// Gets required samples.
        /// \return Samples.
        unsigned int getSamples() const
        {
            return m_samples;
        }
        /// Sets required samples.
        /// \param samples Sample count.
        void setSamples(unsigned int samples)
        {
            m_samples = samples;
        }

        /// Gets required color format.
        /// \return Color format.
        GraphicsFormat getColorFormat() const
        {
            return m_colorFormat;
        }
        /// Gets required depth/stencil format.
        /// \return Depth/stencil format.
        GraphicsFormat getDepthStencilFormat() const
        {
            return m_depthStencilFormat;
        }

        /// Tells if color texture is required.
        /// \return True if yes, false if not.
        bool isColorTextureRequired() const
        {
            return (m_colorFormat != GraphicsFormatNone) && (m_colorFeatures == GraphicsFormatFeatureTextureMask);
        }
        /// Tells if color render buffer is required.
        /// \return True if yes, false if not.
        bool isColorRenderbufferRequired() const
        {
            return (m_colorFormat != GraphicsFormatNone) && (m_colorFeatures == GraphicsFormatFeatureRenderbufferMask);
        }
        /// Tells if depth texture is required.
        /// \return True if yes, false if not.
        bool isDepthTextureRequired() const
        {
            return (m_depthStencilFormat != GraphicsFormatNone) && (m_depthFeatures == GraphicsFormatFeatureTextureMask);
        }
        /// Tells if depth render buffer is required.
        /// \return True if yes, false if not.
        bool isDepthRenderbufferRequired() const
        {
            return (m_depthStencilFormat != GraphicsFormatNone) && (m_depthFeatures == GraphicsFormatFeatureRenderbufferMask);
        }

        /// Gets required addressing mode.
        /// \return Addressing mode.
        Sampler::AddressingMode getAddressingMode() const
        {
            return m_addressingMode;
        }
        /// Gets the required filter mode.
        /// \return Filter mode.
        Sampler::Filter getFilterMode() const
        {
            return m_filterMode;
        }
        /// Gets required mipmap mode.
        /// \return Mipmap mode.
        Sampler::MipmapMode getMipmapMode() const
        {
            return m_mipmapMode;
        }

        /// Gets the depth comparison function.
        /// \return The function to be used in depth comparisons.
        GraphicsCompareFunction getDepthCompareFunction() const
        {
            return m_depthCompareFunction;
        }
        /// Sets the depth comparison function.
        /// \param function The function to be used for depth comparisons.
        void setDepthCompareFunction(GraphicsCompareFunction function)
        {
            m_depthCompareFunction = function;
        }

        /// Sets color renderbuffer format.
        /// Color features will be set to renderbuffer mask.
        /// \param colorFormat Color format.
        void setColorRenderbufferFormat(GraphicsFormat colorFormat)
        {
            m_colorFormat = colorFormat;
            m_colorFeatures = GraphicsFormatFeatureRenderbufferMask;
        }
        /// Sets color texture format.
        /// Color features will be set to texture mask.
        /// \param colorFormat Color format.
        void setColorTextureFormat(GraphicsFormat colorFormat)
        {
            m_colorFormat = colorFormat;
            m_colorFeatures = GraphicsFormatFeatureTextureMask;
        }

        /// Sets depth/stencil renderbuffer format.
        /// Depth features will be set to renderbuffer mask.
        /// \param depthStencilFormat Depth/stencil format.
        void setDepthStencilRenderbufferFormat(GraphicsFormat depthStencilFormat)
        {
            m_depthStencilFormat = depthStencilFormat;
            m_depthFeatures = GraphicsFormatFeatureRenderbufferMask;
        }
        /// Sets depth/stencil texture format.
        /// Depth features will be set to texture mask.
        /// \param depthStencilFormat Depth/stencil format.
        void setDepthStencilTextureFormat(GraphicsFormat depthStencilFormat)
        {
            m_depthStencilFormat = depthStencilFormat;
            m_depthFeatures = GraphicsFormatFeatureTextureMask;
        }

    private:

        /// Width.
        unsigned int m_width;
        /// Height.
        unsigned int m_height;
        /// Multisample level.
        unsigned int m_samples;
        /// Color buffer features.
        GraphicsFormatFeature m_colorFeatures;
        /// Color buffer format.
        GraphicsFormat m_colorFormat;
        /// Depth buffer features.
        GraphicsFormatFeature m_depthFeatures;
        /// Depth/stencil buffer format.
        GraphicsFormat m_depthStencilFormat;
        /// Addressing mode.
        Sampler::AddressingMode m_addressingMode;
        /// Filter mode.
        Sampler::Filter m_filterMode;
        /// Mipmap mode.
        Sampler::MipmapMode m_mipmapMode;
        /// Depth comparison function.
        GraphicsCompareFunction m_depthCompareFunction;
    };

    /// Composition target.
    /// Collection of different elements managed by the composition manager.
    class Target
    {
    private:

        typedef void (Target::*bool_type)() const;
        void this_type_does_not_support_comparisons() const
        {
        }

    public:

        /// Empty constructor.
        /// Target created in this way is not valid.
        explicit Target()
        {
        }

        /// Constructor.
        /// Only texture is defined.
        explicit Target(TextureSharedPtr texture) :
            m_texture(texture)
        {
            texture->reattachFramebuffer();
        }

        /// Constructor.
        /// Specify all components and reattach framebuffers.
        /// \param texture Main texture.
        /// \param colorRenderBuffer Color render buffer.
        /// \param depthTexture Depth texture.
        explicit Target(TextureSharedPtr texture, RenderbufferSharedPtr colorRenderBuffer, TextureSharedPtr depthTexture) :
            m_texture(texture),
            m_colorRenderBuffer(colorRenderBuffer),
            m_depthTexture(depthTexture)
        {
            if (texture)
            {
                if (colorRenderBuffer)
                {
                    kzAssert(!depthTexture);
                    texture->reattachFramebuffer(colorRenderBuffer);
                }
                if (depthTexture)
                {
                    texture->reattachFramebuffer(depthTexture);
                }
                texture->reattachFramebuffer();
            }
            else
            {
                kzAssert(!colorRenderBuffer);
                kzAssert(depthTexture);
                depthTexture->reattachFramebuffer();
            }
        }

        /// Gets the main texture.
        /// Main texture may exist even if its graphics format is #GraphicsFormatNone.
        /// \return Shared pointer to texture.
        TextureSharedPtr getTexture() const
        {
            return m_texture;
        }
        /// Gets the color renderbuffer.
        /// \return Shared pointer to renderbuffer. May be empty.
        RenderbufferSharedPtr getColorRenderbuffer() const
        {
            return m_colorRenderBuffer;
        }
        /// Gets the depth texture.
        /// \return Shared pointer to texture.
        TextureSharedPtr getDepthTexture() const
        {
            return m_depthTexture;
        }

        /// Gets the width of the texture that has the framebuffer.
        /// \return Composition target width.
        unsigned int getWidth() const
        {
            if (m_texture)
            {
                kzAssert(!m_depthTexture || (m_depthTexture->getWidth() == m_texture->getWidth()));
                return m_texture->getWidth();
            }
            kzAssert(m_depthTexture);
            return m_depthTexture->getWidth();
        }
        /// Gets the height of the texture that has the framebuffer.
        /// \return Composition target height.
        unsigned int getHeight() const
        {
            if (m_texture)
            {
                kzAssert(!m_depthTexture || (m_depthTexture->getHeight() == m_texture->getHeight()));
                return m_texture->getHeight();
            }
            kzAssert(m_depthTexture);
            return m_depthTexture->getHeight();
        }
        /// Gets the sample count for the composition target.
        /// This is either the sample count for the texture with the framebuffer or for the color render buffer.
        /// \return Sample count as unsigned integer. Values <= 1 mean multisampling is disabled.
        unsigned int getSampleCount() const
        {
            if (m_colorRenderBuffer)
            {
                kzAssert(m_texture->getRenderTargetSampleCount() == m_colorRenderBuffer->getRenderTargetSampleCount());
                return m_colorRenderBuffer->getRenderTargetSampleCount();
            }
            if (m_depthTexture)
            {
                kzAssert(!m_texture || (m_texture->getRenderTargetSampleCount() == m_depthTexture->getRenderTargetSampleCount()));
                return m_depthTexture->getRenderTargetSampleCount();
            }
            kzAssert(m_texture);
            return m_texture->getRenderTargetSampleCount();
        }
        /// Gets the addressing mode of the composition target.
        /// All textures in the composition target have the same sampling mode.
        /// \return Addressing mode.
        Sampler::AddressingMode getAddressingMode() const
        {
            if (m_depthTexture)
            {
                kzAssert(!m_texture || (m_texture->getSampler().getAddressingMode() == m_depthTexture->getSampler().getAddressingMode()));
                return m_depthTexture->getSampler().getAddressingMode();
            }
            kzAssert(m_texture);
            return m_texture->getSampler().getAddressingMode();
        }
        /// Gets the filter mode of the composition target.
        /// All textures in the composition target have the same filter mode.
        /// \return Filter mode.
        Sampler::Filter getFilterMode() const
        {
            if (m_depthTexture)
            {
                kzAssert(!m_texture || (m_texture->getSampler().getMagnificationFilter() == m_depthTexture->getSampler().getMagnificationFilter()));
                kzAssert(!m_texture || (m_texture->getSampler().getMagnificationFilter() == m_texture->getSampler().getMinificationFilter()));
                kzAssert(m_depthTexture->getSampler().getMagnificationFilter() == m_depthTexture->getSampler().getMinificationFilter());
                return m_depthTexture->getSampler().getMagnificationFilter();
            }
            kzAssert(m_texture);
            kzAssert(m_texture->getSampler().getMagnificationFilter() == m_texture->getSampler().getMinificationFilter());
            return m_texture->getSampler().getMagnificationFilter();
        }
        /// Gets the mipmap mode of the composition target.
        /// All textures in the composition target have the same mipmap mode.
        /// \return Mipmap mode.
        Sampler::MipmapMode getMipmapMode() const
        {
            if (m_depthTexture)
            {
                kzAssert(!m_texture || (m_texture->getSampler().getMipmapMode() == m_depthTexture->getSampler().getMipmapMode()));
                return m_depthTexture->getSampler().getMipmapMode();
            }
            kzAssert(m_texture);
            return m_texture->getSampler().getMipmapMode();
        }
        /// Gets the color format.
        /// This is either the color format of the color render buffer, or that of the texture.
        /// \return Graphics format. May be GraphicsFormatNone if only depth texture has meaning.
        GraphicsFormat getColorFormat() const
        {
            if (m_colorRenderBuffer)
            {
                kzAssert(!m_texture || (m_texture->getFormat() == GraphicsFormatNone));
                return m_colorRenderBuffer->getFormat();
            }
            else if (m_texture)
            {
                return m_texture->getFormat();
            }
            return GraphicsFormatNone;
        }

        /// Gets the depth/stencil format.
        /// Depth/stencil format is combined from the format of the texture and potentially of the depth texture.
        /// \return Graphics format.
        GraphicsFormat getDepthStencilFormat() const
        {
            if (m_depthTexture)
            {
                GraphicsFormat stencilFormat = m_depthTexture->getDepthStencilFormat();
                kzAssert((stencilFormat == GraphicsFormatNone) || (stencilFormat == GraphicsFormatS8_UINT));
                if (stencilFormat != GraphicsFormatNone)
                {
                    return GraphicsFormatD24_UNORM_S8_UINT;
                }
                return m_depthTexture->getFormat();
            }
            kzAssert(m_texture);
            return m_texture->getDepthStencilFormat();
        }

        /// Gets the texture used for composition.
        /// \return Shared pointer to texture.
        TextureSharedPtr getCompositionTexture() const
        {
            return m_texture ? m_texture : m_depthTexture;
        }

        /// Get the information for resolve target.
        /// \return Triplet of resolve framebuffer and boolean flags for whether color and depth are resolved.
        tuple<TextureSharedPtr, bool, bool> getResolveSettings() const
        {
            kzAssert(!m_colorRenderBuffer);
            if (m_texture)
            {
                return make_tuple(m_texture, true, static_cast<bool>(m_depthTexture));
            }
            return make_tuple(m_depthTexture, false, true);
        }

        /// Gets the texture corresponding to a given attachment point.
        /// \param attachmentPoint Attachment point to get.
        /// \return Shared pointer to texture or an empty shared pointer if no corresponding attachment point.
        TextureSharedPtr getAttachmentPointTexture(Framebuffer::AttachmentPoint attachmentPoint) const
        {
            switch(attachmentPoint)
            {
                case Framebuffer::AttachmentPointColor0:
                {
                    return m_texture;
                }
                case Framebuffer::AttachmentPointDepthStencil:
                {
                    return m_depthTexture;
                }
                case Framebuffer::AttachmentPointColor1:
                case Framebuffer::AttachmentPointColor2:
                case Framebuffer::AttachmentPointColor3:
                default:
                {
                    break;
                }
            }
            return TextureSharedPtr();
        }

        /// Generate mipmaps for all textures in the composition target.
        void generateMipmaps()
        {
            kzAssert(m_texture || m_depthTexture);
            if (m_texture)
            {
                m_texture->generateMipmaps();
            }
            if (m_depthTexture)
            {
                m_depthTexture->generateMipmaps();
            }
        }

        /// Clear all memory used by the composition target.
        void reset()
        {
            m_texture.reset();
            m_colorRenderBuffer.reset();
            m_depthTexture.reset();
        }

    public:

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
        explicit operator bool() const
        {
            bool valid = m_texture || m_depthTexture;
            return valid;
        }
#else
        operator bool_type() const
        {
            bool valid = m_texture || m_depthTexture;
            return valid ? &Target::this_type_does_not_support_comparisons : 0;
        }
#endif

    private:

        /// Texture and framebuffer object.
        /// Unless the composition target only houses the depth texture, this texture contains the framebuffer object for composition.
        TextureSharedPtr m_texture;

        /// Color render buffer.
        /// Used when the texture does not have a color texture. In this case, when multisampling is used without multisample texture.
        RenderbufferSharedPtr m_colorRenderBuffer;

        /// Depth texture.
        TextureSharedPtr m_depthTexture;
    };

    /// Constructor.
    ///
    /// \param resourceManager Resource manager owning this composition manager.
    /// \param renderer Renderer to query capabilities from.
    explicit CompositionManager(ResourceManager* resourceManager);

    /// Destructor.
    virtual ~CompositionManager()
    {
    }

    /// Initialize composition manager.
    /// Should be run after Renderer is initialized.
    /// \param renderer Renderer to retrieve information about supported composition types from.
    void initialize(Renderer& renderer);

    /// Remove all allocated temporary composition targets.
    void clear();

    /// Request a composition target.
    /// \param compositionReq Request details.
    /// \return Composition target that fulfills the requirements.
    virtual Target acquireTemporaryCompositionTarget(const Request& compositionReq);

    /// Request a composition target.
    /// Only the color texture element is returned.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param colorFormat Color buffer format.
    /// \param depthStencilFormat Depth/stencil buffer format.
    /// \return Framebuffer that fulfills the requirements.
    TextureSharedPtr acquireTemporaryCompositionTarget(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat);
    /// Request a composition target.
    /// Only the color texture element is returned.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param alpha Is alpha channel requested?
    /// \param depth Is depth buffer requested?
    /// \param stencil Is stencil buffer requested?
    /// \return Framebuffer that fulfills the requirements.
    TextureSharedPtr acquireTemporaryCompositionTarget(unsigned int width, unsigned int height, bool alpha, bool depth, bool stencil)
    {
        GraphicsFormat colorFormat = getColorFormat(alpha);
        GraphicsFormat depthStencilFormat = getDepthStencilFormat(depth, stencil);
        return acquireTemporaryCompositionTarget(width, height, colorFormat, depthStencilFormat);
    }

    /// Release an earlier composition target.
    /// This, released composition target may be re-used by successive requests.
    /// \param target Target to release.
    virtual void releaseTemporaryCompositionTarget(const Target& target);

    /// Create a persistent composition target.
    /// Caller has ownership of all the components of this composition target, it is not stored within the composition manager.
    /// \param compositionReq Request details.
    /// \return Composition target that fulfills the requirements.
    virtual Target createPersistentCompositionTarget(const Request& compositionReq);

    /// Create a persistent composition target.
    /// Only the color texture element is returned.
    /// Caller has ownership of this composition target, it is not stored within the composition manager. 
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param colorFormat Color buffer format.
    /// \param depthStencilFormat Depth/stencil buffer format.
    /// \param addressingMode Addressing mode (wrap/clamp/etc.).
    /// \param mipmapMode Mipmap mode (base/nearest/etc.).
    /// \return Composition target that fulfills the requirements.
    TextureSharedPtr createPersistentCompositionTarget(unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat, Sampler::AddressingMode addressingMode);
    /// Create a persistent composition target.
    /// Only the color texture element is returned.
    /// Caller has ownership of this composition target, it is not stored within the composition manager. 
    /// Determines color, depth and stencil formats from on/off boolean values.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param alpha Alpha channel requirement.
    /// \param depth Depth buffer requirement.
    /// \param stencil Stencil buffer requirement.
    /// \return Composition target that fulfills the requirements.
    TextureSharedPtr createPersistentCompositionTarget(unsigned int width, unsigned int height, bool alpha, bool depth, bool stencil)
    {
        GraphicsFormat colorFormat = getColorFormat(alpha);
        GraphicsFormat depthStencilFormat = getDepthStencilFormat(depth, stencil);

        // Stencil may be not supported. If it isn't, just throw an error.
        if (stencil && !hasStencil(depthStencilFormat))
        {
            kzThrowException(runtime_error("CompositionManager::createPersistentCompositionTarget: stencil buffer not supported by GPU"));
        }

        return createPersistentCompositionTarget(width, height, colorFormat, depthStencilFormat, Sampler::AddressingModeClamp);
    }

    /// Create a persistent color texture.
    /// Note that the color format of this texture may be #GraphicsFormatNone.
    /// \param compositionReq Request details.
    /// \return New color texture according to requirements.
    TextureSharedPtr createPersistentTexture(const CompositionManager::Request& compositionReq);
    /// Create a persistent color renderbuffer.
    /// \param compositionReq Request details.
    /// \return New color renderbuffer according to requirements.
    RenderbufferSharedPtr createPersistentColorRenderbuffer(const CompositionManager::Request& compositionReq);
    /// Create a persistent depth texture.
    /// \param compositionReq Request details.
    /// \return New depth texture according to requirements.
    TextureSharedPtr createPersistentDepthTexture(const CompositionManager::Request& compositionReq);

    /// Checks if a given composition target is an acceptable match for given requirements.
    /// \param target Composition target to test.
    /// \param compositionReq Request details.
    /// \param downScaleLimit Limit for matching against smaller composition targets.
    /// \return True if acceptable, false if not.
    bool compositionTargetMatches(const Target& target, const Request& compositionReq, float downScaleLimit) const;
    /// Checks if a given composition target texture is an acceptable match for given requirements.
    /// \param target Composition target to test.
    /// \param compositionReq Request details.
    /// \param downScaleLimit Limit for matching against smaller composition targets.
    /// \return True if acceptable, false if not.
    bool compositionTargetMatches(const Target& target, const Request& compositionReq) const
    {
        return compositionTargetMatches(target, compositionReq, 0.25f);
    }
    /// Checks if a given composition target texture is an acceptable match for given requirements.
    /// Tolerance for how much smaller composition targets are accepted is determined automatically.
    /// \param texture Composition target texture to test.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param colorFormat Color buffer format.
    /// \param depthStencilFormat Depth/stencil buffer format.
    /// \return True if acceptable, false if not.
    bool compositionTargetMatches(TextureSharedPtr texture, unsigned int width, unsigned int height, GraphicsFormat colorFormat, GraphicsFormat depthStencilFormat) const
    {
        return compositionTargetMatches(Target(texture), Request(width, height, colorFormat, depthStencilFormat));
    }
    /// Checks if a given composition target texture is an acceptable match for given requirements.
    /// Determines color, depth and stencil formats from on/off boolean values.
    /// \param texture Composition target texture to test.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param alpha Alpha channel requirement.
    /// \param depth Depth buffer requirement.
    /// \param stencil Stencil buffer requirement.
    /// \param downScaleLimit Limit for matching against smaller composition targets.
    /// \return True if acceptable, false if not.
    bool compositionTargetMatches(TextureSharedPtr texture, unsigned int width, unsigned int height, bool alpha, bool depth, bool stencil, float downScaleLimit) const
    {
        GraphicsFormat colorFormat = getColorFormat(alpha);
        GraphicsFormat depthStencilFormat = getDepthStencilFormat(depth, stencil);
        return compositionTargetMatches(Target(texture), Request(width, height, colorFormat, depthStencilFormat), downScaleLimit);
    }
    /// Checks if a given composition target texture is an acceptable match for given requirements.
    /// Determines color, depth and stencil formats from on/off boolean values.
    /// Tolerance for how much smaller composition targets are accepted is determined automatically.
    /// \param target Composition target to test.
    /// \param width Requested width.
    /// \param height Requested height.
    /// \param alpha Alpha channel requirement.
    /// \param depth Depth buffer requirement.
    /// \param stencil Stencil buffer requirement.
    /// \return True if acceptable, false if not.
    bool compositionTargetMatches(TextureSharedPtr texture, unsigned int width, unsigned int height, bool alpha, bool depth, bool stencil) const
    {
        return compositionTargetMatches(texture, width, height, alpha, depth, stencil, 0.25f);
    }

    /// Tell if given color texture matches composition requirements.
    /// \param texture Texture to test.
    /// \param compositionReq Request details.
    /// \return True if match, false otherwise.
    bool colorTextureMatches(const Texture& texture, const Request& compositionReq) const
    {
        return (getTextureMatchLevel(texture, compositionReq) > 0);
    }
    /// Tell if given color render buffer matches composition requirements.
    /// \param renderbuffer Renderbuffer to test.
    /// \param compositionReq Request details.
    bool colorRenderbufferMatches(const Renderbuffer& renderbuffer, const Request& compositionReq) const
    {
        return (getColorRenderbufferMatchLevel(renderbuffer, compositionReq) > 0);
    }
    /// Tell if given depth texture matches composition requirements.
    /// \param texture Texture to test.
    /// \param compositionReq Request details.
    /// \return True if match, false otherwise.
    bool depthTextureMatches(const Texture& texture, const Request& compositionReq) const
    {
        return (getDepthTextureMatchLevel(texture, compositionReq) > 0);
    }

    /// Gets color texture format format depending on alpha requirement.
    /// \param alpha Is alpha required?
    /// \return Color texture format.
    GraphicsFormat getColorFormat(bool alpha) const
    {
        return alpha ? m_alphaColorTextureFormat : m_opaqueColorTextureFormat;
    }
    /// Gets format for depth textures.
    /// \return Depth texture format.
    GraphicsFormat getDepthTextureFormat() const
    {
        return m_depthTextureFormat;
    }
    /// Gets depth/stencil renderbuffer format depending on requirements.
    /// \param depth Is depth required?
    /// \param stencil Is stencil required?
    /// \return Depth/stencil renderbuffer format.
    GraphicsFormat getDepthStencilFormat(bool depth, bool stencil) const
    {
        if (depth)
        {
            return stencil ? getDepthStencilRenderbufferFormat() : getDepthRenderbufferFormat();
        }
        return stencil ? getStencilRenderbufferFormat() : GraphicsFormatNone;
    }
    /// Gets depth renderbuffer format.
    /// \return Depth renderbuffer format.
    GraphicsFormat getDepthRenderbufferFormat() const
    {
        return m_depthRenderbufferFormat;
    }
    /// Gets depth + stencil format.
    /// \return Depth + stencil renderbuffer format.
    GraphicsFormat getDepthStencilRenderbufferFormat() const
    {
        return m_depthStencilRenderbufferFormat;
    }
    /// Gets stencil renderbuffer format.
    /// \return Stencil renderbuffer format.
    GraphicsFormat getStencilRenderbufferFormat() const
    {
        return m_stencilRenderbufferFormat;
    }

protected:

    /// Create a temporary composition target.
    /// Called internally from within #acquireTemporaryCompositionTarget() if suitable existing elements are not found.
    /// Adds the components of the temporary composition target to the arrays of resources in use.
    /// \param compositionReq Request details.
    /// \param texture Existing main texture most closely matching the requirements.
    /// \param colorRenderbuffer Existing color renderbuffer most closely matching the requirements.
    /// \param depthTexture Existing depth texture most closely matching the requirements.
    /// \return Composition target that fulfills the requirements.
    Target createTemporaryCompositionTarget(const CompositionManager::Request& compositionReq, TextureSharedPtr texture,
                                            RenderbufferSharedPtr colorRenderbuffer, TextureSharedPtr depthTexture);

    /// Get color texture match level for given requirements.
    /// \param texture Texture to test.
    /// \param compositionReq Request details.
    /// \return 0 if no match, 1 if exact match, greater values if size of texture exceeds requested size.
    unsigned int getTextureMatchLevel(const Texture& texture, const Request& compositionReq) const;
    /// Get color renderbuffer match level for given requirements.
    /// \param renderbuffer Renderbuffer to test.
    /// \param compositionReq Request details.
    /// \return 0 if no match, 1 if exact match, greater values if size of renderbuffer exceeds requested size.
    unsigned int getColorRenderbufferMatchLevel(const Renderbuffer& renderbuffer, const Request& compositionReq) const;
    /// Get depth texture match level for given requirements.
    /// \param texture Texture to test.
    /// \param compositionReq Request details.
    /// \return 0 if no match, 1 if exact match, greater values if size of texture exceeds requested size.
    unsigned int getDepthTextureMatchLevel(const Texture& texture, const Request& compositionReq) const;

    /// Finds the color texture most closely matching given composition requirement.
    /// \param compositionReq Request details.
    /// \return Color texture most closely matching given requirements or an empty shared pointer.
    TextureSharedPtr findClosestTexture(const CompositionManager::Request& compositionReq);
    /// Finds the renderbuffer most closely matching given composition requirement.
    /// \param compositionReq Request details.
    /// \return Color renderbuffer most closely matching given requirements or an empty shared pointer.
    RenderbufferSharedPtr findClosestColorRenderbuffer(const CompositionManager::Request& compositionReq);
    /// Finds the depth texture most closely matching given composition requirement.
    /// \param compositionReq Request details.
    /// \return Depth texture most closely matching given requirements or an empty shared pointer.
    TextureSharedPtr findClosestDepthTexture(const CompositionManager::Request& compositionReq);

    /// Mark given color texture as used.
    /// The texture must exist in available color textures.
    /// \param texture Texture to mark as used.
    void markTextureUsed(TextureSharedPtr texture);
    /// Mark given color renderbuffer as used.
    /// The renderbuffer must exist in available color renderbuffers.
    /// \param colorRenderbuffer Renderbuffer to mark as used.
    void markColorRenderbufferUsed(RenderbufferSharedPtr colorRenderbuffer);
    /// Mark given depth texture as used.
    /// The texture must exist in available depth textures.
    /// \param depthTexture Texture to mark as used.
    void markDepthTextureUsed(TextureSharedPtr depthTexture);

    /// Mark given color texture as available.
    /// The texture must exist in used color textures.
    /// \param texture Texture to mark as used.
    void markTextureUnused(TextureSharedPtr texture);
    /// Mark given color renderbuffer as available.
    /// The renderbuffer must exist in used color renderbuffers.
    /// \param colorRenderbuffer Renderbuffer to mark as used.
    void markColorRenderbufferUnused(RenderbufferSharedPtr colorRenderbuffer);
    /// Mark given depth texture as available.
    /// The texture must exist in used depth textures.
    /// \param depthTexture Texture to mark as used.
    void markDepthTextureUnused(TextureSharedPtr depthTexture);

private:

    /// Temporary composition target textures available.
    vector<TextureSharedPtr> m_availableTextures;
    /// Composition target textures currently in use.
    vector<TextureSharedPtr> m_usedTextures;
    /// Temporary color render buffers available.
    vector<RenderbufferSharedPtr> m_availableColorRenderBuffers;
    /// Color render buffers currently in use.
    vector<RenderbufferSharedPtr> m_usedColorRenderBuffers;
    /// Temporary depth textures available.
    vector<TextureSharedPtr> m_availableDepthTextures;
    /// Depth textures currently in use.
    vector<TextureSharedPtr> m_usedDepthTextures;

    /// Owning resource manager.
    ResourceManager* m_resourceManager;

    /// Alpha color graphics format.
    GraphicsFormat m_alphaColorTextureFormat;
    /// Opaque color graphics format.
    GraphicsFormat m_opaqueColorTextureFormat;
    /// Depth format for depth textures.
    GraphicsFormat m_depthTextureFormat;
    /// Depth format for renderbuffers.
    GraphicsFormat m_depthRenderbufferFormat;
    /// Depth + stencil format for renderbuffers.
    GraphicsFormat m_depthStencilRenderbufferFormat;
    /// Stencil format for renderbuffers.
    GraphicsFormat m_stencilRenderbufferFormat;
    /// Is multisampling support implicit.
    bool m_implicitMultisample;
};

}

#endif
