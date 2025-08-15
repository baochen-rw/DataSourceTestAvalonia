// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_TEXTURE_HPP
#define KZ_GL_TEXTURE_HPP

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_texture_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_framebuffer_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_renderbuffer_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/sampler.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/surface.hpp>
#include <kanzi/core.ui/graphics2d/native_deployment_target.hpp>


namespace kanzi
{

// Forward declaration.
class Domain;
class Framebuffer;
class Renderbuffer;
class Renderer;
class Texture;
typedef shared_ptr<Renderbuffer> RenderbufferSharedPtr;

/// Texture shared pointer type.
typedef shared_ptr<Texture> TextureSharedPtr;

/// Textures provide images that can be used with image nodes, texture brushes and materials for 
/// use in 3D rendering or material brushes.
///
/// Textures can be set as render target. Texture can be set to as render target for either 2d node or render
/// pass, but not both.
///
/// \see For details on the render target texture, see #RenderTargetMode, #CreateInfoNode2DRenderTarget, and
///      #CreateInfoRenderpassRenderTarget. Note that the #CreateInfoRenderpassRenderTarget is intended for use
///      with the deprecated #LegacyRenderPass. For all other render passes, use #CreateInfoNode2DRenderTarget,
///      or to acquire the composition targets use the #CompositionManager.
///
/// Texture can optionally maintain CPU accessible copy of texture data. \see See #CreateInfoHostCopy2D
/// for CPU accessible texture data details.
///
/// In order to create a texture, you must prepare Texture::CreateInfo structure and make sure it is
/// valid using CreateInfo::validate(), then create the texture with Texture::create(). If texture
/// creation parameters are not valid, Texture::create() will throw an exception, which can stop
/// program execution.
///
/// Two dimensional textures can be created from Image or by specifying size, format and features.
/// Cubemap textures can be created from six Images or by specifying size, format and features.
///
/// You must specify texture filtering, addressing mode (also known as wrap mode), and mipmap settings
/// in Texture::CreateInfo before you create the texture.
/// Two dimensional textures which are shown without scaling can be created with default texture creation
/// parameters, which improve performance and reduce memory usage.
/// If you show texture content with scaling, consider using linear filtering and prefiltered mipmaps
/// to reduce aliasing, with some performance and memory cost.
///
/// Examples - Creating Textures with Kanzi C++ API
/// ----
///
/// To create a two dimensional texture from image:
/// \snippet test_texture.cpp image texture example
///
/// To load image from file and create texture:
/// \snippet test_texture.cpp create texture from image file
///
/// To access the image data after you create a texture:
/// \snippet test_texture.cpp Get host copy image for a texture
///
/// To create a two dimensional texture from image with custom sampler settings:
/// \snippet test_texture.cpp image texture example with sampler settings
///
/// To create a cubemap texture from 6 face images:
/// \snippet test_texture.cpp cubemap image texture example
///
/// Examples - Loading textures with Kanzi C++ API using ResourceManager
///
/// To load texture with ResourceManager using file URL:
/// \snippet test_texture.cpp load texture with resource manager file url example
///
/// To load texture with ResourceManager:
/// \snippet test_texture.cpp load texture with resource manager example
///
/// Examples - Updating texture data with Kanzi C++ API
/// ----
///
/// To update texture data of two dimensional texture base level image:
/// \snippet test_texture.cpp texture setData base image example
///
/// To update texture data of cubemap texture all mipmap level images:
/// \snippet test_texture.cpp texture setData cubemap mipmaps example
///
/// Examples - Use texture as render target for node 2D or renderpass using Kanzi C++ API
/// ----
///
/// To use texture as render target for 2D node:
/// \snippet test_texture.cpp texture node 2d rendertarget example
///
/// To use texture as render target for renderpass:
/// \snippet test_texture.cpp texture renderpass example
/// 
/// Examples - Render to texture with framebuffer (OpenGL and OpenGL ES only) using Kanzi C++ API
/// ----
///
/// To create a two dimensional texture and render to it through framebuffer:
/// \snippet test_texture.cpp render to texture example
/// 
/// To create a two dimensional texture with mipmaps and render to it through framebuffer:
/// \snippet test_texture.cpp render to texture example with mipmaps
///
/// To create a cubemap texture with mipmaps and render to it through framebuffers:
/// \snippet test_texture.cpp cubemap render to texture example
class KANZI_API Texture : public Surface
{
    // Needed by ResourceManager::fileProtocolHandler() which does new Texture.
    friend class ResourceManager;

public:

    struct CreateInfo;
    struct CreateInfo2D;
    struct CreateInfoHostCopy2D;
    struct CreateInfoNode2DRenderTarget;
    struct CreateInfoRenderpassRenderTarget;
    struct CreateInfoCubemap;

    /// Texture type
    enum Type
    {
        /// Two dimensional texture
        TypeTwoDimensional = 0,

        /// Reserved for future use. Do not use.
        /// Two dimensional array texture
        TypeTwoDimensionalArray,

        /// Reserved for future use. Do not use.
        /// Two dimensional multisample texture
        TypeTwoDimensionalMultisample,

        /// Reserved for future use. Do not use.
        /// Two dimensional multisample array texture
        TypeTwoDimensionalMultisampleArray,

        /// Reserved for future use. Do not use.
        /// Three dimensionla texture
        TypeThreeDimensional,

        /// Cubemap texture
        TypeCubeMap,

        /// Reserved for future use. Do not use.
        /// Cubemap array texture
        TypeCubeMapArray,

        /// External texture.
        /// \note External textures are specific to OpenGL ES and EGL.
        TypeExternal,

        /// Number of valid texture targets
        TypeCount,

        /// Invalid texture target
        TypeInvalid
    };

    /// RenderTarget mode for Texture. Rendering to a Texture may require extra
    /// resources (such as framebuffer when using OpenGL or OpenGL ES). RenderTargetMode
    /// specifies who manages these resources.
    enum RenderTargetMode
    {
        /// When texture has rendertarget mode RenderTargetModeNone, that texture cannot be rendered to.
        /// You must not set such texture as render target for 2D nodes.
        /// You should not set such texture as render target for renderpasses.
        RenderTargetModeNone,

        /// RenderTargetModeInternal allows texture to be rendered to without externally managed resources.
        ///
        /// You can set such texture as render target for 2D nodes.
        /// You should not set such texture as render target for renderpasses.
        ///
        /// \note Implementation details:
        ///       When you create texture with renderTargetMode set to RenderTargetModeInternal, texture
        ///       will internally maintain necessary resources that are required to perform rendering to
        ///       the texture. When such texture is created, the texture will also maintain a GL framebuffer
        ///       and optional depth stencil renderbuffer.
        ///
        /// \note Use getNativeFramebufferHandle() to get handle to the framebuffer object in the texture.
        RenderTargetModeInternal,

        /// RenderTargetModeExternal allows texture to be rendered to with externally managed resources.
        ///
        /// You can set texture as render target for renderpasses.
        /// You must not set texture as render target for 2D nodes.
        ///
        /// When you create texture with renderTargetMode set to RenderTargetModeExternal, an external
        /// entity such as renderpass is responsible for creating necessary resources that are
        /// required to perform rendering to the texture.
        RenderTargetModeExternal
    };

    KZ_ABSTRACT_METACLASS_BEGIN(Texture, Surface, "Kanzi.Texture")
    KZ_METACLASS_END()

    /// Creates a texture with specified texture creation parameters.
    ///
    /// In order to create a texture, you will need a CreateInfo structure that is
    /// filled with valid combination of texture creation parameters. You can use
    /// CreateInfo, CreateInfo2D, CreateInfoHostCopy2D, CreateInfoNode2DRenderTarget,
    /// CreateInfoRenderpassRenderTarget and CreateInfoCubemap constructors to create
    /// and initialize a texture creation parameter structure. After calling the constructor
    /// you can fine tune texture creation parameters.
    ///
    /// You can check that parameters are valid by calling CreateInfo::validate().
    ///
    /// If you pass CreateInfo that is not valid, Texture::create() will throw an exception
    /// and program execution may will terminate. To avoid exceptions for recoverable errors,
    /// use Renderer::adjust() on the create info prior to calling this function.
    ///
    /// If createInfo memory type includes Gpu, texture will be deployed.
    ///
    /// If createInfo memory type includes Ram, host copy of texture data will be made accessible.
    /// Otherwise, texture host copy will not be accessible.
    /// 
    /// \note create() takes ownership of images you pass in the create info.
    ///       You must not delete images that you pass to Texture::create() in createInfos.
    ///       You must immediately discard any CreateInfo which contains images after first call to create().
    ///       The images in createInfo are no longer valid, and such CreateInfo cannot be reused.
    ///
    /// \param domain Domain for the texture.
    /// \param createInfo Texture creation parameters.
    /// \param name Name for the texture.
    ///
    /// \return Texture shared pointer.
    static TextureSharedPtr create(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Creates texture from a pre-existing GL texture object. Optionally, kanzi::Texture
    /// can take ownership of the provided GL texture object, in which case destroying
    /// kanzi::Texture will also destroy the GL texture object. If ownership is not passed
    /// to kanzi::Texture, then GL texture must be deleted after kanzi::Texture. Do not
    /// delete GL texture object while kanzi::Texture exists.
    /// \note Caller should always provide accurate information in format, mipmapLevelCount, width and height.
    /// \param domain Domain.
    /// \param type Texture type.
    /// \param nativeHandle Pre-existing native handle that identifies a valid GL texture object.
    /// \param takeOwnership If true, texture will take ownership of the native resource (GL texture object).
    /// \param format Format of the texture.
    /// \param mipmapLevelCount Number of mipmap levels in the texture.
    /// \param width Width of the texture.
    /// \param height Height of the texture.
    /// \param name Name.
    /// \return Texture shared pointer.
    static TextureSharedPtr create(Domain* domain, Type type, int nativeHandle, bool takeOwnership, GraphicsFormat format,
                                   unsigned int mipmapLevelCount, unsigned int width, unsigned int height, string_view name);

    /// Returns the Sampler used by the texture.
    const Sampler& getSampler() const;

    /// Returns type of the texture.
    Type getType() const;

    /// Returns the native deployment target.
    NativeDeploymentTarget getNativeDeploymentTarget() const;

    /// Reattaches the internal framebuffer object.
    /// Only renderbuffers and the color texture within the texture object will be used.
    void reattachFramebuffer();

    /// Reattaches the internal framebuffer object and includes the renderbuffer given as parameter.
    /// The texture does not take ownership of the renderbuffer.
    /// The texture must not have an internal color texture.
    /// \param colorRenderbuffer Renderbuffer to use as the color target in the framebuffer.
    void reattachFramebuffer(RenderbufferSharedPtr colorRenderbuffer);

    /// Reattaches the internal framebuffer object and includes the depth texture given as parameter.
    /// The texture does not take ownership of the depth texture.
    /// The texture must not have an internal depth render buffer.
    /// \param depthTexture Depth texture to use as the depth target in the framebuffer.
    void reattachFramebuffer(TextureSharedPtr depthTexture);

    /// Generates the mipmaps from the base level image.
    /// This reads from Gpu texture data from the base level images, and only updates Gpu texture data of the remaining
    /// mipmap images. If texture has host copy data, it remains unchanged.
    void generateMipmaps();

    /// Sets the texture data for the specified area in a texture. The texture data
    /// is updated to the GPU memory, and to the CPU accessible copy of the texture,
    /// if the texture is created with such storage.
    /// 
    /// \note The format of the data must match the format of the texture.
    ///
    /// \param face Which texture face to update.
    /// \param mipmapLevel Which mipmap level to update.
    /// \param x, y, width, height Specifies the rectangle to update.
    /// \param data Texture data.
    void setData(Face face, unsigned int mipmapLevel, unsigned int x, unsigned int y, unsigned int width, unsigned int height, const kanzi::byte* data);

    /// Sets the texture data for the specified area in the texture. The texture data
    /// is updated to the GPU memory, and to the CPU accessible copy of the texture,
    /// if the texture is created with such storage.
    /// 
    /// \note The format of the data must match the format of the texture.
    ///
    /// \param mipmapLevel Which mip level to update.
    /// \param x, y, width, height Specifies the rectangle to update.
    /// \param data Texture data.
    void setData(unsigned int mipmapLevel, unsigned int x, unsigned int y, unsigned int width, unsigned int height, const kanzi::byte* data);

    /// Sets the texture data for base level of a non-cubemap texture.
    /// \param data Texture data.
    void setData(const kanzi::byte* data);

    /// Gets native texture handle for the texture.
    /// \return Native texture handle.
    unsigned int getNativeHandle() const;

    /// Gets native framebuffer handle for the texture.
    /// \note Only textures created with RenderTargetMode set to RenderTargetInternal will have native framebuffer handle.
    /// \return Native framebuffer handle, or 0 if texture was created with rendertarget mode other than RenderTargetInternal.
    unsigned int getNativeFramebufferHandle() const;

    /// Returns depthStencil format of the texture.
    /// \note Only textures created with RenderTargetMode set to RenderTargetInternal will have depth stencil buffer.
    /// \return Graphics format of depth stencil buffer, or GraphicsFormatNone if texture does not have depth stencil buffer.
    GraphicsFormat getDepthStencilFormat() const;

    /// Returns the host-side memory copy of texture data as an image, if available.
    ///
    /// Returns as an image the copy of the host-side memory of the texture data, but does not create a copy
    /// of that image. Use this function only to retrieve data that was sent to the GPU from the CPU memory.
    /// To retrieve data rendered to a texture by the GPU use #kzcScreenCaptureToImage().
    ///
    /// \param face The texture face for which you want to get the data. For single textures, this value is
    ///             #FaceDefault. For cube-map textures use a valid face for the texture. For example,
    ///             #FacePositiveX, or #FaceNegativeZ. If you try to access an invalid texture face, the
    ///             function throws an exception.
    /// \param slice The texture slice for which you want to get the data. Slice applies to array and 3D
    ///              textures. Currently this parameter must always be 0. If you access an invalid texture
    ///              slice, the function throws an exception.
    /// \return When you create a texture with the #MemoryType property set to #GpuAndRam or #RamOnly, returns
    ///         the host-side image uploaded to to the GPU. If you create a texture with the #MemoryType
    ///         property set to #GpuOnly, or try to retrieve a composition target texture, returns a null
    ///         pointer.
    BitmapImageSharedPtr getHostCopyImage(Face face, unsigned int slice) const;

    /// Returns the host-side memory copy of a non-cubemap texture, if available.
    ///
    /// Returns as an image the copy of the host-side memory of the default face of a single texture data,
    /// but it does not create a copy of that image.
    ///
    /// \return When you create a texture with the #MemoryType property set to #GpuAndRam or #RamOnly, returns
    ///         the host-side image uploaded to to the GPU. If you create a texture with the #MemoryType
    ///         property set to #GpuOnly, try to retrieve a composition target texture, or a face from a
    ///         cube-map texture, returns a null pointer.
    BitmapImageSharedPtr getHostCopyImage() const;

    /// Returns rendertarget mode of the texture.
    /// \return Rendertarget mode. \see RenderTargetMode.
    RenderTargetMode getRenderTargetMode() const
    {
        return m_renderTargetMode;
    }

    /// Changes the size of the texture.
    ///
    /// Texture contents are undefined after resizing, user should assume they are destroyed.
    /// Specifying size identical to current size will cause resizing not to happen.
    ///
    /// NOTE: Internal API and subject to change or removal.
    ///
    /// \param width New width.
    /// \param height New height.
    void resize(unsigned width, unsigned height);

    /// Tell if width is or should be automatically calculated.
    bool hasAutomaticWidth() const
    {
        return (m_widthDivisor > 0);
    }

    /// Tell if height is or should be automatically calculated.
    bool hasAutomaticHeight() const
    {
        return (m_heightDivisor > 0);
    }

    /// Get height divisor for automatic sizes.
    unsigned int getHeightDivisor() const
    {
        return m_heightDivisor;
    }

    /// Get width divisor for automatic sizes.
    unsigned int getWidthDivisor() const
    {
        return m_widthDivisor;
    }

    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:
    /// Resource::reloadOverride() implementation.
    virtual void reloadOverride() KZ_OVERRIDE;

    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser) KZ_OVERRIDE;

    /// Resource::reloadFromFileOverride() implementation.
    virtual void reloadFromFileOverride(string_view filePath) KZ_OVERRIDE;

    /// Resource::getCPUMemoryUsageOverride() implementation.
    virtual unsigned int getCPUMemoryUsageOverride() const KZ_OVERRIDE;

    /// Validates the CreateInfo texture descriptor, creates a new texture and swaps it in place.
    /// \param createInfo The texture descriptor.
    void recreate(CreateInfo& createInfo);


    /// GPUResource::invalidateOverride() implementation.
    virtual void invalidateOverride() KZ_OVERRIDE;

    /// GpuResource::isDeployed() implementation.
    virtual bool isDeployedOverride() const KZ_OVERRIDE;

    /// GpuResource::getGPUMemoryUsageOverride() implementation.
    virtual unsigned int getGPUMemoryUsageOverride() const KZ_OVERRIDE;


    /// Surface::attachOverride() implementation.
    virtual void attachOverride(Usage usage, APIAttachment apiAttachment, Face face, unsigned int mipmapLevel) KZ_OVERRIDE;

    /// Surface::getFormatOverride() implementation.
    virtual GraphicsFormat getFormatOverride() const KZ_OVERRIDE;

    /// Surface::getFeaturesOverride() implementation.
    virtual unsigned int getFeaturesOverride() const KZ_OVERRIDE;

    /// Surface::getRenderTargetSampleCountOverride() implementation.
    virtual unsigned int getRenderTargetSampleCountOverride() const KZ_OVERRIDE;

    /// Surface::getWidthOverride() implementation.
    virtual unsigned int getWidthOverride() const KZ_OVERRIDE;

    /// Surface::getHeightOverride() implementation.
    virtual unsigned int getHeightOverride() const KZ_OVERRIDE;

    /// Surface::getSliceCountOverride() implementation.
    virtual unsigned int getSliceCountOverride() const KZ_OVERRIDE;

    /// Surface::getFaceCountOverride() implementation.
    virtual unsigned int getFaceCountOverride() const KZ_OVERRIDE;

    /// Surface::getMipmapLevelCountOverride() implementation.
    virtual unsigned int getMipmapLevelCountOverride() const KZ_OVERRIDE;

    /// Creates texture from CreateInfo. Texture will be deployed, if createInfo memory type includes Gpu.
    /// \param Domain Domain for texture.
    /// \param createInfo Texture creation parameters.
    /// \param name Name for texture.
    explicit Texture(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Creates texture from an existing GL object handle. Caller must also provide texture format,
    /// and size. glHandle should be a valid GL texture object.
    /// Optionally, kanzi::Texture can take ownership of the provided GL texture object,
    /// in which case destroying kanzi::Texture will also destroy the GL texture object.
    /// If ownership is not passed to kanzi::Texture, then GL texture must be deleted after
    /// kanzi::Texture. Do not delete GL texture object while kanzi::Texture exists.
    /// \note Caller should always provide accurate information in format, mipmapLevelCount, width and height.
    /// \param Domain Domain for texture.
    /// \param type Texture type.
    /// \param glHandle Pre-existing valid GL texture object name.
    /// \param format Format of the texture.
    /// \param mipmapLevelCount Mipmap level count of the texture.
    /// \param width Width of the texture.
    /// \param height Height of the texture.
    /// \param takeOwnership Should kanzi::Texture take ownership of provided GL texture object
    /// \param name Name
    explicit Texture(Domain* domain, Type type, int glHandle, bool takeOwnership, GraphicsFormat format,
                     unsigned int mipmapLevelCount, unsigned int width, unsigned int height, string_view name);

    /// Helper function to allocate host images. There are three cases:
    /// 1. Texture is created with GpuOnly memory type, empty vector will be returned.
    /// 2. Texture is created with RamOnly or GpuAndRam memory type, and create info contains images.
    ///    A vector containing those images from create info will be returned.
    /// 3. Texture is created with RamOnly or GpuAndRam memory type, create info did not contain images.
    ///    A vector conatining newly allocated images will be returned.
    /// \param createInfo Texture create info.
    /// \return Vector of images. It will be empty if texture memory type is GpuOnly, otherwise it will have
    ///         images from createInfo if it has images, and if not, it will return newly allocated images.
    static vector<BitmapImageSharedPtr> makeHostCopyImages(const CreateInfo& createInfo);

    /// Helper function to create GL texture object. Only dummy handle will be created
    /// if create info specifies RamOnly texture in memoryType.
    /// \param renderer Renderer.
    /// \param createInfo Texture create info.
    /// \return Texture handle.
    static GLTextureHandle makeTexture(Renderer* renderer, const CreateInfo& createInfo);

    /// Helper function to create GL framebuffer object. Only dummy handle will be created
    /// if create info specifies RamOnly texture, or if texture rendertarget mode is not
    /// RenderTargetModeInternal.
    /// \param renderer Renderer.
    /// \param createInfo Texture create info.
    /// \return Framebuffer handle.
    static GLFramebufferHandle makeFramebuffer(Renderer* renderer, const CreateInfo& createInfo);

    /// Helper function to create GL renderbuffer object for color or depth/stencil buffer.
    /// Only dummy handle will be created if create info specifies RamOnly texture, or if texture rendertarget mode is not
    /// RenderTargetModeInternal.
    /// \param renderer Renderer.
    /// \param createInfo Texture create info.
    /// \return Renderbuffer handle.
    static GLRenderbufferHandle makeRenderbufferHandle(Renderer* renderer, const CreateInfo& createInfo);

    /// Helper function to setup GL texture object state and initial data.
    /// Called as part of texture construction.
    /// Texture internal variables must already be initialized.
    /// \param images Images to deploy.
    /// \param renderer Renderer.
    void deployImages(Renderer& renderer, const vector<BitmapImageSharedPtr>& images);

    /// Helper function to setup GL framebuffer and renderbuffer state
    /// Called as part of texture construction.
    /// Texture internal variables must already be initialized.
    /// \param renderer Renderer.
    /// \param colorRenderbuffer Color renderbuffer not owned by the texture to attach.
    /// \param depthTexture Depth texture not owned by this texture to attach.
    void deployInternalFramebuffers(Renderer& renderer, RenderbufferSharedPtr colorRenderbuffer, TextureSharedPtr depthTexture);

private:

    // Texture is not copyable
    explicit Texture(const Texture&) KZ_DELETED_FUNCTION;
    Texture& operator=(const Texture&) KZ_DELETED_FUNCTION;

    friend void swap(Texture& texture1, Texture& texture2);

private:

    /// GL texture object name
    GLTextureHandle m_textureHandle;

    /// GL framebuffer object name when m_renderTargetMode is RenderTargetModeInternal.
    GLFramebufferHandle m_framebufferHandle;

    /// GL renderbuffer object name when m_renderTargetUsage is RenderTargetModeInternal.
    GLRenderbufferHandle m_depthStencilRenderbufferHandle;

    /// Color render buffer attached to the framebuffer.
    weak_ptr<Renderbuffer> m_attachedColorRenderbuffer;
    /// Depth texture attached to the framebuffer.
    weak_ptr<Texture> m_attachedDepthTexture;

    /// Format of the texture handle.
    /// This is either a color format or a depth format.
    /// Stencil format should never be used.
    GraphicsFormat m_format;

    /// Features of format. \see GraphicsFormatFeature.
    unsigned int m_features;

    /// Texture width.
    unsigned int m_width;

    /// Texture height.
    unsigned int m_height;

    /// Divisor for automatic width determination, 0 for no automatic height.
    unsigned int m_widthDivisor;

    /// Divisor for automatic height determination, 0 for no automatic height.
    unsigned int m_heightDivisor;

    /// Reserved for future use. Always set to 1. 
    /// Number of texture slices.
    unsigned int m_sliceCount;

    /// Number of texture faces. 1 for 2D textures, and 6 for cubemap textures
    unsigned int m_faceCount;

    /// Number of mipmap levels in the texture.
    unsigned int m_mipmapLevelCount;

    /// Sampler configuration
    Sampler m_sampler;

    /// Copy of texture data, provides host CPU access without reading back from GPU.
    vector<BitmapImageSharedPtr> m_images;

    /// RenderTarget mode for texture.
    RenderTargetMode m_renderTargetMode;

    /// Memory type for texture.
    MemoryType m_memoryType;

    /// Native memory storage for the texture.
    NativeDeploymentTarget m_nativeDeploymentTarget;

    /// Texture type.
    Type m_type;

    /// Number of implicit multisample samples.
    /// \note Only for textures with m_renderTargetMode set to RenderTargetModeExternal.
    unsigned int m_rendertargetSampleCount;

    /// DepthStencil format.
    /// This is depth/stencil format of the additional render buffer in addition to the format in #m_format.
    /// Both format and depth/stencil format cannot have depth.
    GraphicsFormat m_depthStencilFormat;
};

inline void swap(Texture& texture1, Texture& texture2)
{
    using std::swap;
    swap(texture1.m_textureHandle, texture2.m_textureHandle);
    swap(texture1.m_framebufferHandle, texture2.m_framebufferHandle);
    swap(texture1.m_depthStencilRenderbufferHandle, texture2.m_depthStencilRenderbufferHandle);
    swap(texture1.m_format, texture2.m_format);
    swap(texture1.m_features, texture2.m_features);
    swap(texture1.m_width, texture2.m_width);
    swap(texture1.m_height, texture2.m_height);
    swap(texture1.m_widthDivisor, texture2.m_widthDivisor);
    swap(texture1.m_heightDivisor, texture2.m_heightDivisor);
    swap(texture1.m_sliceCount, texture2.m_sliceCount);
    swap(texture1.m_faceCount, texture2.m_faceCount);
    swap(texture1.m_mipmapLevelCount, texture2.m_mipmapLevelCount);
    swap(texture1.m_sampler, texture2.m_sampler);
    swap(texture1.m_images, texture2.m_images);
    swap(texture1.m_renderTargetMode, texture2.m_renderTargetMode);
    swap(texture1.m_memoryType, texture2. m_memoryType);
    swap(texture1.m_nativeDeploymentTarget, texture2. m_nativeDeploymentTarget);
    swap(texture1.m_type, texture2.m_type);
    swap(texture1.m_rendertargetSampleCount, texture2.m_rendertargetSampleCount);
    swap(texture1.m_depthStencilFormat, texture2.m_depthStencilFormat);
}

KANZI_API unsigned int getFaceCount(Texture::Type type);
KANZI_API unsigned int getGLTextureImageTarget(Texture::Type type, unsigned int face);
KANZI_API unsigned int getGLTextureTarget(Texture::Type type);

/// Loads a new image from memory and creates a texture out of it.
/// \param domain Domain to use.
/// \param width Width of the image.
/// \param height Height of the image.
/// \param sourceFormat Graphics surface format of the source data.
/// \param data Pointer to the source data in memory.
/// \param destinationFormat Graphics surface format to convert image data to. Use sourceFormat to skip surface format conversion.
/// \param name Name for the texture.
/// \return A shared pointer to the created texture.
KANZI_API TextureSharedPtr createTextureFromMemory(Domain* domain, unsigned int width, unsigned int height, GraphicsFormat sourceFormat, const void* data, GraphicsFormat destinationFormat, string_view name);

/// Calculates number of mipmap levels for provided image size.
/// \param width Width of the image.
/// \param height Height of the image.
/// \return Number of mipmap levels for image of given size.
KANZI_API unsigned int calculateMipmapLevelCount(unsigned int width, unsigned int height);

} // namespace kanzi

#endif // KZ_TEXTURE_HPP
