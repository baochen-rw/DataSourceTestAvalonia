// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_TEXTURE_CREATE_INFO_HPP
#define KZ_GL_TEXTURE_CREATE_INFO_HPP

#include <kanzi/core.ui/graphics2d/texture.hpp>
#include <kanzi/core.ui/graphics2d/native_deployment_target.hpp>

namespace kanzi
{

/// Struct which contains all the parameters that are needed for texture creation.
/// \see Texture
/// \see Texture::CreateInfo2D
/// \see Texture::CreateInfoHostCopy2D
/// \see Texture::CreateInfoNode2DRenderTarget
/// \see Texture::CreateInfoRenderpassRenderTarget
/// \see Texture::CreateInfoCubemap 
struct KANZI_API Texture::CreateInfo
{
    friend class Texture;

public:
    /// Status tells if texture creation parameters can be used to create a texture.
    /// If status is not StatusValid, create info must not be passed to Texture::create().
    enum Status
    {
        /// Invalid texture type. See Texture::Type for valid texture types.
        StatusInvalidType,

        /// Requested Texture type is not supported.
        StatusTypeNotSupported,

        /// Requested rendertarget mode is not valid.
        StatusInvalidRenderTargetMode,

        /// Wrong number of images. Two dimensional textures must have 0 or 1 image, cubemap textures must have 0 or 6 images.
        StatusInvalidImageCount,

        /// Not all images were properly defined.
        StatusMissingImages,

        /// Mipmaps are required, but the image is missing them.
        StatusImageMissingMipmaps,

        /// Sizes of images are inconsistent.
        StatusInvalidImageSize,

        /// Image size must be at least 1 x 1
        StatusInvalidMinimumSize,

        /// Image size cannot exceed size supported by the GL device.
        StatusInvalidMaximumSize,

        /// Image mipmap size was not correctly derived from base image.
        StatusInvalidMipmapSize,

        /// Unsupported image format.
        StatusUnsupportedGraphicsFormat,

        /// Requested filtering mode is not supported for requested graphics format.
        StatusUnsupportedTextureFilter,

        /// Requested graphics format features are not valid for texture.
        StatusInvalidFeatures,

        /// Multisample textures do not support filtering.
        StatusUnsupportedMultisampleFilter,

        /// Multisample textures do not support mipmaps.
        StatusUnsupportedMultisampleMipmaps,

        /// Multisample textures must have a valid number of samples.
        StatusUnsupportedMultisampleSamples,

        /// Textures with rendertarget mode set to RenderTargetModeInternal do not support multisampling.
        StatusUnsupportedInternalRenderTargetSampleCount,

        /// Requested number of multisample sample exceeds number of multisample samples supported by the graphics device.
        StatusUnsupportedSampleCount,

        /// Inconsistent image formats.
        StatusImageFormatMismatch,
            
        /// Image incompatible with target device.
        StatusImageIncompatibleWithDevice,

        /// Requested depth comparison mode is not supported by graphics device.
        StatusUnsupportedDepthComparisonMode,

        /// CreateInfo is valid and can be used to create Texture.
        StatusValid
    };

    /// Default constructor for texture create info.
    ///
    /// After the CreateInfo constructor:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    /// \li Texture rendertarget mode is set to RenderTargetModeNone, so resulting texture cannot be set as rendertarget
    ///     for neither 2d nodes nor renderpasses. If you want to render to the resulting texture, change rendertarget mode.
    ///
    /// If you use this constructor, then you must fill in at least type, format, width
    /// and height before CreateInfo can be used to create texture.
    ///
    /// \note If you specify images after the constructor, you still need to set format,
    ///       width, height and mipmapLevelCount correctly, You can simply do this by setting
    ///       desired mipmapMode and the calling updateShapeAndFormatFromImages().
    ///
    /// \note You can use CreateInfo2D, CreateInfoHostCopy2D, CreateInfoNode2DRenderTarget,
    ///       :CreateInfoRenderpassRenderTarget and CreateInfoCubemap derived struct constructors
    ///       to create initialize texture creation parameters for specific purpose.
    explicit CreateInfo();

    /// Perform validation of texture creation parameters.
    /// You can call validate() to see if texture creation parameters are valid before you pass create info to Texture::create().
    /// \param renderer Renderer to validate with.
    /// \return StatusValid if these creation parameters can be used to create a texture.
    ///         Otherwise a reason code for why this CreateInfo cannot be used to create a texture.
    Status validate(const Renderer& renderer) const;

    /// Validates and applies adjustments to some texture creation parameters in case of avoidable error conditions.
    /// Some error conditions cause adjustments instead of resulting in an error. These include:
    ///  - Missing flags in the surface feature requirements based on given surface format specifications.
    ///  - Applying for a surface format that is not supported by the current hardware.
    ///  - Missing or invalid mipmaps.
    /// This function should be called when the texture create info should survive from the error cases above.
    /// In most use cases it is advisable to call this function regardless before passing the CreateInfo forward.
    /// It is not necessary to call validate() separately if using this function.
    /// The return value of this function is directly the return value of validate() after all possible adjustments have been made.
    /// \param renderer Renderer to validate with.
    /// \param name A name to be used for this texture in possible warning log messages.
    /// \return Status value for the validity of this descriptor after possible adjustments.
    Status adjust(const Renderer& renderer, string_view name);

    /// Create a texture create info structure for a black 1x1 texture.
    /// \param renderer Renderer to use for feature queries.
    /// \param textureType The type of the texture.
    /// \return Texture::CreateInfo object that can be used for creating the texture.
    static CreateInfo createSubstitutePattern(const Renderer& renderer, Type type);

    /// Use updateShapeAndFormatFromImages() to fill in format, width, height from images.
    /// Those parameters must match images in order for Texture::create() to accept CreateInfo.
    void updateShapeAndFormatFromImages();

public:
    /// Images that are used to create the texture.
    ///
    /// If you set texture type to two dimensional, images must contain zero or one image.
    /// If you set texture type to cube map, images must contain zero or six images.
    ///
    /// Default CreateInfo constructor initializes this to empty.
    ///
    /// \see updateShapeAndFormatFromImages()
    vector<BitmapImageSharedPtr> images;

    /// Format for texture.
    ///
    /// Default CreateInfo constructor initializes this to GraphicsFormatNone, which is not valid value for Texture::create().
    ///
    /// \note Not all devices support all texture formats, and not all formats support all features.
    ///       You can check with validate() that create info has combination of format and features
    ///       that are supported by your graphics driver.
    GraphicsFormat format;

    /// DepthStencil format. This is only used when you set renderTargetMode to RenderTargetModeInternal.
    ///
    /// Default CreateInfo constructor initializes this to GraphicsFormatNone, meaning there will be no depth/stencil
    /// for native framebuffer that is created if you set renderTargetMode to RenderTargetModeInternal.
    ///
    /// \note Only GraphicsFormatNone or formats with depth and/or stencil component are valid.
    ///
    /// \see GraphicsFormat.
    GraphicsFormat depthStencilFormat;

    /// Required format features.
    ///
    /// Default CreateInfo constructor initializes this to GraphicsFormatFeatureSampledImage.
    ///
    /// \note Not all devices support all texture formats, and not all formats support all features.
    ///       You can check with validate() that create info has combination of format and features
    ///       that are supported by your graphics driver.
    ///
    /// \see GraphicsFormatFeature
    unsigned int features;

    /// Texture type.
    ///
    /// Default CreateInfo constructor initializes this to TypeInvalid, which is not valid value for Texture::create().
    ///
    /// \see Type
    Type type;

    /// Width for the base level of texture.
    ///
    /// Default CreateInfo constructor initializes this to 0, which is not valid value for Texture::create().
    ///
    /// \note Combination of mipmapMode, mipmapLevelCount, width and height must be valid when calling Texture::create().
    unsigned int width;

    /// Height for the base level of texture.
    ///
    /// Default CreateInfo constructor initializes this to 0, which is not valid value for Texture::create().
    ///
    /// \note Combination of mipmapMode, mipmapLevelCount, width and height must be valid when calling Texture::create().
    unsigned int height;

    /// Automatic size determination divisor for width, 0 when not automatic.
    ///
    /// Default CreateInfo constructor initializes this to 0.
    unsigned int widthDivisor;

    /// Automatic size determination divisor for height, 0 when not automatic.
    ///
    /// Default CreateInfo constructor initializes this to 0.
    unsigned int heightDivisor;

    /// Reserved for future use. Set to 1.
    ///
    /// Depth for the base level of texture.
    ///
    /// Default CreateInfo constructor initializes this to 1.
    unsigned int depth;

    /// Specifies number of samples for the draw renderbuffer when RenderTargetMode is RenderTargetModeExternal.
    ///
    /// Default CreateInfo constructor initializes this to 0, meaning no multisample samples.
    unsigned int renderTargetSampleCount;

    /// Number of mipmap levels for the texture.
    ///
    /// Default CreateInfo constructor initializes this to 1, meaning there is
    /// only base level image and no mipmap images.
    ///
    /// \note Combination of mipmapMode, mipmapLevelCount, width and height must be valid when calling Texture::create().
    unsigned int mipmapLevelCount;

    /// Memory type for the texture. If Gpu is not included, texture will not be deployed when created.
    ///
    /// If Ram is not included, texture will not contain images after it has been deployed.
    ///
    /// Default CreateInfo constructor initializes this to GpuOnly.
    ///
    /// \see MemoryType
    MemoryType memoryType;

    /// Native deployment target to use for memory storage if supported by the backend.
    ///
    /// Default CreateInfo constructor initializes this to None.
    ///
    /// \see NativeDeploymentTarget
    NativeDeploymentTarget nativeDeploymentTarget;

    /// RenderTarget mode for the texture.
    ///
    /// Default CreateInfo constructor initializes this to RenderTargetModeNone.
    ///
    /// \see RenderTargetMode
    RenderTargetMode renderTargetMode;

    /// Mipmap mode for the texture.
    ///
    /// Default CreateInfo constructor initializes this to Sampler::MipmapModeBase.
    ///
    /// \note Default setting for mipmap and filter settings are optimized for textures that are shown without scaling.
    ///       If your texture is shown with scaling, consider changing mipmapMode and filter settings to minimize aliasing.
    ///
    /// \note Combination of mipmapMode, mipmapLevelCount, width and height must be valid when calling Texture::create().
    ///
    /// \see Sampler::MipmapMode
    Sampler::MipmapMode mipmapMode;

    /// Texture magnification filter.
    ///
    /// Default CreateInfo constructor initializes this to Sampler::FilterNearest.
    ///
    /// \note Default setting for mipmap and filter settings are optimized for textures that are shown without scaling.
    ///       If your texture is shown with scaling, consider changing mipmapMode and filter settings to minimize aliasing.
    ///
    /// \see Sampler::Filter
    Sampler::Filter minificationFilter;

    /// Texture minification filter.
    ///
    /// Default CreateInfo constructor initializes this to Sampler::FilterNearest.
    ///
    /// \note Default setting for mipmap and filter settings are optimized for textures that are shown without scaling.
    ///       If your texture is shown with scaling, consider changing mipmapMode and filter settings to minimize aliasing.
    ///
    /// \see Sampler::Filter
    Sampler::Filter magnificationFilter;

    /// Texture addressing mode.
    ///
    /// Default CreateInfo constructor initializes this to Sampler::AddressingModeClamp.
    ///
    /// \note Default setting for addressingMode makes the texture not repeat. If you want texture to repeat,
    ///       you must change addressingMode.
    ///
    /// \see Sampler::AddressingMode
    Sampler::AddressingMode addressingMode;

    /// Texture anisotropy.
    /// Default CreateInfo constructor initializes this to 1.0 (no anisotropy).
    ///
    /// \note Use of anisotropic texture filter requires GL extension.
    float anisotropy;

    /// Depth comparison function.
    /// Default CreateInfo constructor initializes this to GraphicsCompareFunctionLessOrEqual.
    GraphicsCompareFunction depthCompareFunction;

    /// Reserved for future use. Set to 0.0f.
    /// Texture mipmap level of detail bias. 
    /// Default CreateInfo constructor initializes this to 0.
    ///
    /// \note Using texture Lod controls requires OpenGL ES 3.0.
    float mipLodBias;

    /// Reserved for future use. Set to -1000.0f.
    /// Minimum texture level of detail.
    /// Default CreateInfo constructor initializes this to -1000.0f (effectively no clamping for level of detail).
    ///
    /// \note Using texture Lod controls requires OpenGL ES 3.0.
    float minLod;

    /// Reserved for future use.
    /// Maximum texture level of detail.
    /// Default CreateInfo constructor initializes this to 1000 (effectively no clamping for level of detail).
    ///
    /// \note Using texture Lod controls requires OpenGL ES 3.0.
    float maxLod;

protected:

    /// Test if given set of images can be used to create Texture
    /// \param renderer Renderer to validate with.
    /// \return Status if images can be used to create Texture, otherwise reason why images cannot be used to create Texture.
    Status validateImages(const Renderer& renderer) const;

    /// Validates texture format and features.
    /// \param renderer Renderer to validate with.
    /// \return StatusValid if texture format is valid, otherwise reason why texture format and features is not valid.
    Status validateFormat(const Renderer& renderer) const;

    /// Validates texture size against minimum valid texture size (1x1) and maximum supported by graphics adapter.
    /// \param renderer Renderer to validate with.
    /// \return StatusValid if image size is valid, otherwise reason why texture size is not valid.
    Status validateSize(const Renderer& renderer) const;

    /// Checks for known device incompatibilities, for example with texture formats and size.
    /// \param renderer Renderer to validate with.
    /// \return StatusValid if there is no known target compatibility issue with texture size or other parameters.
    Status validateTargetCompatibility(const Renderer& renderer) const;
};

/// Texture creation parameters for two dimensional texture.
/// You can use resulting texture as content in Image2D nodes or texture brushes,
/// or in materials for 3D rendering or material brushes.
struct KANZI_API Texture::CreateInfo2D : public Texture::CreateInfo
{
    /// CreateInfo2D constructor for texture creation parameters, for creating a two dimensional texture that is initialized from an image.
    ///
    /// After the CreateInfo2D constructor:
    /// \li Image is stored in create info.
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is determined from the image.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If you show resulting texture content with scaling, there will be noticable aliasing.
    ///       Adjust filter and mipmap settings after constructor to reduce aliasing.
    ///
    /// \note Texture::create() takes ownership of images you pass in the create info, \see Texture::create().
    ///
    /// \see Image
    ///
    /// \param image Source image for texture.
    explicit CreateInfo2D(BitmapImageUniquePtr image);

	/// CreateInfo2D constructor that also takes in mipmap mode.
    /// For details, see #CreateInfo(ImageUniquePtr)
	/// \param mipmaps Mipmap mode.
	explicit CreateInfo2D(Sampler::MipmapMode mipmaps, BitmapImageUniquePtr image);

    /// CreateInfo2D constructor for texture creation parameters, for creating a two dimensional texture with specified format and size.
    ///
    /// After the CreateInfo2D constructor:
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is set according to constructor parameters.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    /// \li Texture rendertarget mode is set to RenderTargetModeNone, so resulting texture cannot be set as rendertarget
    ///     for neither 2d nodes nor renderpasses. If you want to render to the resulting texture, change rendertarget mode.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If you show resulting texture content with scaling, there will be noticable aliasing.
    ///       Adjust filter and mipmap settings after constructor to reduce aliasing.
    ///
    /// \note When you create texture from CreateInfo that has no images, texture contents are initially
    ///       undefined. Use Texture::setData() to specify texture contents, or render to the texture.
    ///
    /// \param width Width for the texture
    /// \param height Height for the texture
    /// \param format Format for the texture
    explicit CreateInfo2D(unsigned int width, unsigned int height, GraphicsFormat format);
};

/// Texture creation parameters for two dimensional texture that is updated from the CPU.
///
/// You can use CreateInfoHostCopy2D to initialize texture creation parameters for textures
/// that you update from the CPU. Textures will be created with specified format and size,
/// and texture will maintain CPU accessible copy of texture content. Use Texture::getHostCopyImage()
/// to access copy of texture data. Use this kind of texture is when you update texture
/// contents only from the CPU, and you nead read access to the texture data. For example
/// glyph cache for font rendering is a plausible use case.
///
/// \note When you create texture from CreateInfoHostCopy2D, texture contents are initially
/// undefined. Use Texture::setData() to specify texture contents.
///
/// \see Texture::getHostCopyImage()
/// \see Texture::setData()
struct KANZI_API Texture::CreateInfoHostCopy2D : public Texture::CreateInfo2D
{
    /// Constructor for CreateInfoHostCopy2D.
    ///
    /// After the CreateInfoHostCopy2D constructor:
    /// \li Texture memoryType is set to GpuAndRam
    ///
    /// The following (from CreateInfo2D constructor) also applies:
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is set according to constructor parameters.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If you show resulting texture content with scaling, there will be noticable aliasing.
    ///       Adjust filter and mipmap settings after constructor to reduce aliasing.
    ///
    /// \param width Width for the texture
    /// \param height Height for the texture
    /// \param format Format for the texture
    explicit CreateInfoHostCopy2D(unsigned int width, unsigned int height, GraphicsFormat format);
};

/// Texture creation parameters for texture that can be used as render target for 2D nodes.
/// You can use the resulting texture as content in Image2D nodes or texture brushes.
/// You can also use resulting texture in materials for 3D rendering or material brushes.
struct KANZI_API Texture::CreateInfoNode2DRenderTarget : public Texture::CreateInfo2D
{
    /// Constructor for CreateInfoNode2DRenderTarget.
    ///
    /// After the CreateInfoNode2DRenderTarget constructor:
    /// \li Texture features is set to GraphicsFormatFeatureSampledImage and then OR'd with GraphicsFormatFeatureColorAttachment or GraphicsFormatFeatureDepthStencilAttachment depending on format.
    /// \li Texture rendertarget mode is set to RenderTargetModeInternal, so Node2d::RenderTargetProperty can use the resulting texture.
    ///
    /// The following (from CreateInfo2D constructor) also applies:
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is set according to constructor parameters.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If resulting texture is shown with scaling, there will be noticable aliasing. You
    ///       can adjust settings in the create info structure after constructor before passing it to Texture::create() if default
    ///       settings are not ideal for you.
    ///
    /// \note Not all texture formats support rendering to (GraphicsFormatFeatureColorAttachment).
    ///       Make sure you use texture format that your device supports rendering to.
    ///
    /// When you create texture from CreateInfoNode2DRenderTarget, texture contents are initially
    /// undefined. Set texture as rendertarget for a node, and arrange node to be rendered before
    /// using the texture as content.
    ///
    /// \see Node2D::RenderTargetProperty
    /// \see Node2D::OffscreenRenderingProperty
    ///
    /// \param width Width for the texture.
    /// \param height Height for the texture.
    /// \param format Format for the texture.
    explicit CreateInfoNode2DRenderTarget(unsigned int width, unsigned int height, GraphicsFormat format);
};

/// Texture creation parameters for texture that can be used as render target for renderpasses.
/// You can use the resulting texture as content in Image2D nodes or texture brushes.
/// You can also use the resulting texture in materials for 3D rendering or material brushes.
struct KANZI_API Texture::CreateInfoRenderpassRenderTarget : public Texture::CreateInfo2D
{
    /// Constructor for CreateInfoRenderpassRenderTarget - non-multisample version.
    ///
    /// After the CreateInfoRenderpassRenderTarget constructor:
    /// \li Texture features is set to GraphicsFormatFeatureSampledImage | GraphicsFormatFeatureColorAttachment.
    /// \li Texture rendertarget mode is set to RenderTargetModeExternal, so renderpasses can use the resulting texture.
    ///
    /// The following (from CreateInfo2D constructor) also applies:
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is set according to constructor parameters.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If resulting texture is shown with scaling, there will be noticable aliasing. You
    ///       can adjust settings in the create info structure after constructor before passing it to Texture::create() if default
    ///       settings are not ideal for you.
    ///
    /// \note Not all texture formats support rendering to (GraphicsFormatFeatureColorAttachment).
    ///       Make sure you use texture format that your device supports rendering to.
    ///
    /// When you create texture from CreateInfoRenderpassRenderTarget, texture contents are initially
    /// undefined. Set texture as rendertarget for a renderpass, and arrange viewport node to be rendered
    /// with the renderpass before using the texture as content.
    ///
    /// \see Scene::RenderPassProperty
    ///
    /// \param width Width for the texture.
    /// \param height Height for the texture.
    /// \param format Format for the texture.
    explicit CreateInfoRenderpassRenderTarget(unsigned int width, unsigned int height, GraphicsFormat format);

    /// Constructor for CreateInfoRenderpassRenderTarget - multisample version.
    ///
    /// Use this CreateInfoRenderpassRenderTarget to create a texture which can be used
    /// in renderpasses with multisample anti aliasing.
    ///
    /// \note CreateInfoRenderpassRenderTarget constructor will throw an exception, which may
    ///       stop program execution, if graphics device does not support multisample renderbuffers.
    ///
    /// After the CreateInfoRenderpassRenderTarget constructor:
    /// \li Texture features will have GraphicsFormatFeatureSampledImage and GraphicsFormatFeatureColorAttachment bits set.
    ///     If graphics device supports multisampled render to texture extension, GraphicsFormatFeatureColorAttachment bit
    ///     will be set in features. Else, if any other multisample technique is supported by graphics device,
    ///     GraphicsFormatFeatureBlitDestination bit will be set in features.
    /// \li Texture rendertarget mode is set to RenderTargetModeExternal, so renderpasses can use the resulting texture.
    /// \li Texture renderTargetSampleCount is set to requested number of samples
    ///
    /// The following (from CreateInfo2D constructor) also applies:
    /// \li Texture type is set to TypeTwoDimensional.
    /// \li Texture size and format is set according to constructor parameters.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If resulting texture is shown with scaling, there will be noticable aliasing. You
    ///       can adjust settings in the create info structure after constructor before passing it to Texture::create() if default
    ///       settings are not ideal for you.
    ///
    /// \note Not all texture formats support rendering to (GraphicsFormatFeatureColorAttachment).
    ///       Make sure you use texture format that your device supports rendering to.
    ///
    /// When you create texture from CreateInfoRenderpassRenderTarget, texture contents are initially
    /// undefined. Set texture as rendertarget for a renderpass, and arrange a viewport node to be rendered
    /// with the renderpass before using the texture as content.
    ///
    /// \note The resulting texture is not a multisample texture. For all sampling purposes, the resulting texture does
    ///       not have multiple samples. Rendering to the texture happens through either a multisample renderbuffer or
    ///       implicit resolve (multisampled render to texture extension)
    ///
    /// \see Scene::RenderPassProperty
    ///
    /// \param Renderer Renderer, to provide multisample path.
    /// \param sampleCount Number of samples.
    /// \param width Width for the texture.
    /// \param height Height for the texture.
    /// \param format Format for the texture.
    explicit CreateInfoRenderpassRenderTarget(Renderer* renderer, unsigned int sampleCount, unsigned int width, unsigned int height, GraphicsFormat format);
};

/// Texture creation parameters for cubemap texture that is initialized from six images.
/// Texture size, format and mipmap mode is determined from the images.
/// You can use texture created with CreateInfoCubemap as content in materials for 3D rendering or material brushes.
struct KANZI_API Texture::CreateInfoCubemap : public Texture::CreateInfo
{
    /// CreateInfoCubemap constructor for texture creation parameters, for creating a cube map texture that is initialized from six images.
    ///
    /// After the CreateInfoCubemap constructor:
    /// \li Images are stored in create info.
    /// \li Texture type is set to TypeCubeMap.
    /// \li Texture size and format is determined from the images.
    ///
    /// The following (from CreateInfo constructor) also applies:
    /// \li Texture minification and magnification filter settings are set to FilterNearest.
    /// \li Texture wrap mode is set to AddressingModeClamp, so texture will not repeat.
    /// \li Texture mipmap mode is set to MipmapModeBase, and mipmapLevelCount is set to 1,
    ///     so texture will have only base image, no mipmaps.
    ///
    /// \note After constructor, due to filter settings and lack of mipmaps, the resulting texture should only be used when texture
    ///       content is shown without scaling. If you show resulting texture content with scaling, there will be noticable aliasing.
    ///       Adjust filter and mipmap settings after constructor to reduce aliasing.
    ///
    /// \note TextureTexture::create() takes ownership of images you pass in the create info, \see Texture::create().
    ///
    /// \see Image
    ///
    /// \param images Source images. There must be six images in the vector.
    explicit CreateInfoCubemap(BitmapImageVector images);

    /// CreateInfoCubemap constructor that also takes in mipmap mode.
    /// For details, see #CreateInfoCubemap(ImageVector)
    /// \param mipmaps Mipmap mode.
    explicit CreateInfoCubemap(Sampler::MipmapMode mipmapMode, BitmapImageVector images);

private:
    /// CreateInfoCubemap is not copyable, since Texture::create() takes ownership of images.
    CreateInfoCubemap(const CreateInfoCubemap&) KZ_DELETED_FUNCTION;
    CreateInfoCubemap& operator=(const CreateInfoCubemap&) KZ_DELETED_FUNCTION;
};


inline void swap(Texture::CreateInfo& info1, Texture::CreateInfo& info2)
{
    using std::swap;
    swap(info1.images, info2.images);
    swap(info1.format, info2.format);
    swap(info1.depthStencilFormat, info2.depthStencilFormat);
    swap(info1.features, info2.features);
    swap(info1.type, info2.type);
    swap(info1.width, info2.width);
    swap(info1.height, info2.height);
    swap(info1.widthDivisor, info2.widthDivisor);
    swap(info1.heightDivisor, info2.heightDivisor);
    swap(info1.depth, info2.depth);
    swap(info1.renderTargetSampleCount, info2.renderTargetSampleCount);
    swap(info1.mipmapLevelCount, info2.mipmapLevelCount);
    swap(info1.memoryType, info2.memoryType);
    swap(info1.nativeDeploymentTarget, info2.nativeDeploymentTarget);
    swap(info1.renderTargetMode, info2.renderTargetMode);
    swap(info1.mipmapMode, info2.mipmapMode);
    swap(info1.minificationFilter, info2.minificationFilter);
    swap(info1.magnificationFilter, info2.magnificationFilter);
    swap(info1.addressingMode, info2.addressingMode);
    swap(info1.anisotropy, info2.anisotropy);
    swap(info1.depthCompareFunction, info2.depthCompareFunction);
    swap(info1.mipLodBias, info2.mipLodBias);
    swap(info1.minLod, info2.minLod);
    swap(info1.maxLod, info2.maxLod);
}

/// Load texture create info from KZB file.
/// \param domain Domain
/// \param kzbFile KZB file
/// \param file File
/// \param parser Memory parser
/// \return Texture create info
Texture::CreateInfo loadTextureCreateInfo(Domain* domain, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

/// Load texture create info from legacy KZB file.
/// \param domain Domain
/// \param inputStream Input strea
/// \param file File
/// \return Texture create info
Texture::CreateInfo loadTextureCreateInfo(Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

/// Returns human readable description for CreateInfo status.
/// \param status Status
/// \return human readable description for status.
KANZI_API FixedString getVerboseDescription(Texture::CreateInfo::Status status);

/// Loads an image from KZB file.
/// \param domain Domain.
/// \param imageUrl URL of the image.
/// \param isInCubemap Whether the loaded image will be used as a cubemap face.
/// \return The loaded image.
KANZI_API BitmapImageUniquePtr loadImage(Domain* domain, string_view imageUrl, bool isInCubemap);

} // namespace kanzi

#endif
