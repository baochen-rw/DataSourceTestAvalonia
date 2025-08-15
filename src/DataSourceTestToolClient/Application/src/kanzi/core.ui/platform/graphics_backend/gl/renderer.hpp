// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDERER_HPP
#define KZ_RENDERER_HPP

#include <kanzi/core.ui/graphics/format.hpp>
#include <kanzi/core.ui/graphics3d/mesh.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/framebuffer.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/renderbuffer.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/sampler.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/shader.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/shader_create_info.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/surface.hpp>
#include <kanzi/core.ui/graphics2d/texture.hpp>
#include <kanzi/core.ui/graphics2d/texture_create_info.hpp>
#include <kanzi/core/math/rectangle.hpp>
#include <kanzi/core/cpp/array.hpp>
#include <kanzi/core/cpp/bitset.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/set.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/platform/windowing/common/kzs_window.h>
#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/graphics_swizzle_mask.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_opengl.h>
#include <kanzi/core/legacy/kzs_types.hpp>

// Forward declaration.
struct KzcGPUBufferManager;
struct KzcMemoryManager;
struct KzsSurface;
struct KzuWindow;
struct KzsGlGraphicsContext;

namespace kanzi
{

/// Viewport rectangle definition.
typedef Rectangle<int> ViewportRectangle;

typedef map<string, int>                     AttributeNameToIndex;
typedef AttributeNameToIndex::iterator       AttributeNameToIndexIterator;
typedef AttributeNameToIndex::const_iterator AttributeNameToIndexConstIterator;

class Renderer;
class GlGraphicsOutput;
typedef shared_ptr<Renderer> RendererSharedPtr;

class KANZI_API RendererStatisticsScope
{
public:
    explicit RendererStatisticsScope(Renderer* renderer);
    ~RendererStatisticsScope();

private:
    Renderer* m_renderer;
};

/// Specifies stream to GL buffer object.
class BufferObjectStream
{
public:
    BufferObjectStream(Renderer* renderer, bool isVBO);
    ~BufferObjectStream();

    void uploadData(Renderer* renderer, const void* data, unsigned int dataSize, unsigned int* out_vertexDataOffset);
    void bind(Renderer* renderer) const;

private:
    Renderer*       m_renderer;
    unsigned int    m_bufferHandle;  ///< Buffer object handle.
    bool            m_isVBO;         ///< Indicates if this is a stream to VBO or IBO.
    unsigned int    m_bufferSize;    ///< The size of buffer object storage.
    unsigned int    m_bufferCursor;  ///< Offset to unused memory in buffer object.
};
typedef shared_ptr<BufferObjectStream> BufferObjectStreamSharedPtr;

class KANZI_API Renderer
{
public:
    /// Multisample support code path in Renderer
    enum Multisample
    {
        /// No multisample support
        MultisampleNone = 0,

        /// Multisample using desktop OpenGL
        MultisampleARB,

        /// Multisample using NVidia extensions for OpenGL ES 2
        MultisampleES2NVidia,

        /// Multisample using OpenGL ES 3 BlitFramebuffer
        MultisampleES3,

        /// Multisample using OpenGL ES 2 multivendor extension
        MultisampleES2Ext,

        /// Multisample using Imagination Technologies extension for OpenGL ES 2
        MultisampleES2Img
    };

    /// Tell if multisample support is of implicit type.
    /// Implicit multisample does not require a separate resolve and does not have explicitly accessible samples.
    /// \param multisampleSupport Multisample support.
    /// \return True if implicit multisample support, false if not.
    static bool isImplicitMultisampleSupport(Multisample multisampleSupport)
    {
        return (multisampleSupport == Renderer::MultisampleES2Ext) || (multisampleSupport == Renderer::MultisampleES2Img);
    }

    /// Program binary support code path in Renderer
    enum ProgramBinary
    {
        /// No program binary support
        ProgramBinaryNone = 0,

        /// Program binary using desktop OpenGL
        ProgramBinaryARB,

        /// Program binary using OpenGL ES 3
        ProgramBinaryES3,

        /// Program binary using OpenGL ES 2 multivendor extension
        ProgramBinaryES2Ext
    };

    /// Half float texture support code path in Renderer
    enum HalfFloatTexture
    {
        /// No support for half float textures
        HalfFloatTextureNone = 0,

        /// Half float textures supported using desktop OpenGL
        HalfFloatTextureARB,

        /// Half float textures supported using OpenGL ES 3
        HalfFloatTextureES3,

        /// Half float textures supported using OpenGL ES 2 multivendor extension
        HalfFloatTextureES2Ext
    };

    /// Float texture support code path in Renderer.
    enum FloatTexture
    {
        /// No support for float textures
        FloatTextureNone = 0,

        /// Float textures supported using desktop OpenGL
        FloatTextureARB,

        /// Float textures supported using OpenGL ES 3
        FloatTextureES3,

        /// Float textures supported using OpenGL ES 2 multivendor extension
        FloatTextureES2Ext
    };

    enum TexStorage
    {
        TexStorageNone,
        TexStorageMultisampleARB,   // 4.3 TexStorage1D, TexStorage2D, TexStorage3D, TexStorage2DMultisample, TexStorage3DMultisample
        TexStorageARB,              // 4.2 TexStorage1D, TexStorage2D, TexStorage3D
        TexStorageES2Ext,           //     TexStorage1DEXT, TexStorage2DEXT, TexStorage3DEXT
        TexStorageES3,              // 3.0 TexStorage2D, TexStorage3D
        TexStorageES31,             // 3.1 TexStorage2DMultisample
        TexStorageES32              // 3.2 TexStorage3DMultisample
    };

    /// Framebuffer invalidation support code path in Renderer
    enum InvalidateFramebuffer
    {
        /// No support for framebuffer invalidation
        InvalidateFramebufferNone,

        /// Framebuffer invalidation supported using desktop OpenGL
        InvalidateFramebufferARB,

        /// Framebuffer invalidation supported using OpenGL ES 3
        InvalidateFramebufferES3,

        /// Framebuffer invalidation supported using OpenGL ES 2 multivendor extension
        InvalidateFramebufferES2Ext
    };

    /// Renderer state enumerations.
    enum State
    {
        /// Renderer state for depth testing.
        StateDepthTest = 0,

        /// Renderer state for cull face.
        StateCullFace,

        /// Renderer state for blending.
        StateBlend,

        /// Renderer state for depth write.
        StateDepthWrite,

        /// Renderer state for stencil test.
        StateStencilTest,

        /// Renderer state for stencil write.
        StateStencilWrite,

        /// Renderer state for multi-sampling.
        StateMultisample,

        /// Renderer state for scissor test.
        StateScissorTest,

        /// Renderer state for coverage write.
        StateCoverageWrite,

        /// Maximum count of renderer states.
        StateCount
    };

    /// List of active matrices renderer keeps track of.
    enum FixedMatrix
    {
        FixedMatrixProjection = 0,          ///< Projection matrix.
        FixedMatrixCamera,                  ///< Camera matrix.
        FixedMatrixWorld,                   ///< Current world matrix.
        FixedMatrixCameraWorld,             ///< Current camera * world matrix.
        FixedMatrixProjectionCameraWorld,   ///< Current projection * camera * world matrix.
        FixedMatrixCount                    ///< Maximum amount of matrices.
    };

    enum Support
    {
        SupportHalfFloatVertexAttribute = 0,
        SupportHalfFloatTextureFormatLinear,
        SupportHalfFloatColorAttachment,
        SupportNPOTTextureFilter,
        SupportRenderToMipmapLevels,
        SupportDepth16Renderbuffer,
        SupportDepth16Texture,
        SupportDepth24Renderbuffer,
        SupportDepth24Texture,
        SupportDepth24Stencil8Renderbuffer,
        SupportDepth24Stencil8Texture,
        SupportDepth32Renderbuffer,
        SupportDepth32fRenderbuffer,
        SupportDepth32fTexture,
        SupportStencil8Renderbuffer,
        SupportStencil8Texture,
        SupportExternalTexture,
        SupportTextureFilterAnisotropic,
        SupportTextureSwizzle,          // GL_ARB_texture_swizzle or GL_EXT_texture_swizzle.
        SupportSeamlessCubeMap,
        SupportRGB8Renderbuffer,
        SupportRG8Formats,              // OpenGL ES 3
        SupportRGFormats,               // OpenGL ES 2 with GL_EXT_texture_rg or ES 3.0+
        SupportIntegerFormats,          // OpenGL ES 3
        SupportRGB8Texture,
        SupportRGBA8Renderbuffer,
        SupportRGBA8Texture,
        SupportDiscardFramebuffer,
        SupportInvalidateFramebuffer,
        SupportImplementationColorRead,
        SupportKHRDebug,
        SupportShaderBinary,
        SupportMultipleRenderTargets,
        SupportSRGB,
        SupportSRGB8Texture,
        SupportSRGB8TexStorage,
        SupportETC1NPOT,
        Support10_10_10_2VertexAttribute,
        SupportDepthComparison,
        SupportSNORMFormats,              // OpenGL ES 3
        SupportFloatTextureFormatLinear,  // OpenGL ES 2 with GL_OES_texture_float_linear or ES 3.0+
        SupportFloatColorAttachment,
        SupportTextureNorm16Formats,      // OpenGL ES 3 with EXT_texture_norm16
        SupportCount
    };

    enum Information
    {
        InformationGLVendor                   = (1u <<  0u),
        InformationGLRenderer                 = (1u <<  1u),
        InformationGLVersion                  = (1u <<  2u),
        InformationGLShadingLanguageVersion   = (1u <<  3u),
        InformationGLExtensions               = (1u <<  4u),
        InformationFormatSupport              = (1u <<  5u),
        InformationShaderBinarySupport        = (1u <<  6u),
        InformationProgramBinarySupport       = (1u <<  7u),
        InformationFeatureSupport             = (1u <<  8u),
        InformationImplementationDependent    = (1u <<  9u),
        InformationDebug                      = (1u << 10u),
        InformationAll                        = (~0u)
    };

    /// Creates a new renderer object.
    Renderer(const KzcMemoryManager* memoryManager);
    ~Renderer();

    /// Resets frame for core renderer, that is, counters for logging rendering infos (triangle count etc.).
    void resetFrame();

    /// Resets renderer, e.g. resets its caches and states and syncs renderer variables with actual GL states.
    void reset();

    /// Initializes renderer object. Requires graphics context.
    void initialize(kzUint vertexBufferPoolSize, kzUint indexBufferPoolSize);

    /// Uninitializes renderer object.
    void uninitialize();

    /// Tells whether the renderer is initialized.
    /// \return True if the renderer is initialized.
    bool isInitialized() const;

    /// Sets active surface context for renderer.
    void setActiveGraphicsOutput(GlGraphicsOutput* glGraphicsOutput);

    /// Gets active surface context from renderer.
    GlGraphicsOutput* getActiveGraphicsOutput() const;

    KzsWindow* getActiveWindow() const;
    KzsSurface* getActiveSurface() const;
    KzsGlGraphicsContext* getActiveGraphicsContext() const;

    enum KzsSurfaceType getActiveSurfaceType() const;

    ::KzsOpenGlVendor getActiveSurfaceVendor() const;

    /// Enables a specific renderer state.
    void enableState(State state);

    /// Disables a specific renderer state.
    void disableState(State state);

    /// Enables or disables the state of a specific renderer state.
    void setState(State state, bool enable);

    /// Returns state of a specific renderer state.
    bool getState(State state) const;

    /// Clears currently bound framebuffer with requested buffers.
    /// Buffers can be requested to be clered with addClearTarget()
    /// and addClearColor() functions.
    void clear();

    /// Resets clear targets for renderer.
    void resetClearTarget();

    /// Sets a clearing target for renderer.
    /// \see addClearColor()
    /// \note You must use addClearColor to clear color buffers 1..3 (GraphicsClearTargetColor1..3)
    /// \param target The buffer to clear, must be GraphicsClearTargetColor0,  GraphicsClearTargetDepth or  GraphicsClearTargetStencil
    void addClearTarget(GraphicsClearTarget target);

    /// Per color buffer clear setting
    enum ClearMode
    {
        /// Color buffer will not be cleared
        ClearModeDisabled,

        /// Clear color with unsigned normalized color
        ClearModeUnsignedNormalized,

        /// Clear color buffer with unsigned integer value
        /// \note Integer color buffers require OpenGL ES 3
        ClearModeUnsignedInteger,

        /// Clesr color buffer with signed integer value
        /// \note Integer color buffers require OpenGL ES 3
        ClearModeSignedInteger,

        /// Clear color buffer with float value
        /// \note Float color buffers require OpenGL ES 3.2 or EXT_color_buffer_half_float extension
        ClearModeFloat
    };

    static ClearMode getClearMode(GraphicsFormat format);

    /// Register color clear for unsigned integer color buffer.
    /// All registered clears are performed when clear() is called.
    /// \note OpenGL ES 3 is required for integer color buffers.
    /// \see clear()
    /// \param drawBuffer Index of color buffer to clear (0..3).
    /// \param red Clear color red channel value.
    /// \param green Clear color green channel value.
    /// \param blue Clear color blue channel value.
    /// \param alpha Clear color alpha channel value.
    void addClearColor(unsigned int drawBuffer, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha);

    /// Register color clear for signed integer color buffer.
    /// All registered clears are performed when clear() is called.
    /// \note OpenGL ES 3 is required for integer color buffers.
    /// \see clear()
    /// \param drawBuffer Index of color buffer to clear (0..3).
    /// \param red Clear color red channel value.
    /// \param green Clear color green channel value.
    /// \param blue Clear color blue channel value.
    /// \param alpha Clear color alpha channel value.
    void addClearColor(unsigned int drawBuffer, int32_t red, int32_t green, int32_t blue, int32_t alpha);

    /// Register color clear for float color buffer.
    /// All registered clears are performed when clear() is called.
    /// \note OpenGL ES 3.2 or EXT_color_buffer_half_float is required for float color buffers.
    /// \note OpenGL ES 3.0 is required for drawBuffer > 0
    /// \see clear()
    /// \param drawBuffer Index of color buffer to clear (0..3 for OpenGL ES 3, must be 0 for OpenGL ES 2).
    /// \param red Clear color red channel value.
    /// \param green Clear color green channel value.
    /// \param blue Clear color blue channel value.
    /// \param alpha Clear color alpha channel value.
    void addClearColor(unsigned int drawBuffer, float red, float green, float blue, float alpha);

    /// Register color clear for unsigned normalized color buffer.
    /// All registered clears are performed when clear() is called.
    /// \note OpenGL ES 3.0 is required for drawBuffer > 0
    /// \see clear()
    /// \param drawBuffer Index of color buffer to clear (0..3 for OpenGL ES 3, must be 0 for OpenGL ES 2).
    /// \param red Clear color red channel value.
    /// \param green Clear color green channel value.
    /// \param blue Clear color blue channel value.
    /// \param alpha Clear color alpha channel value.
    void addClearColor(unsigned int drawBuffer, ColorRGBA colorRGBA);

    /// Register color clear with value 0.
    /// All registered clears are performed when clear() is called.
    /// \note OpenGL ES 3.0 is required for drawBuffer > 0
    /// \see clear()
    /// \param drawBuffer Index of color buffer to clear (0..3 for OpenGL ES 3, must be 0 for OpenGL ES 2).
    /// \param clearMode ClearMode of the color buffer.
    void addClearColor(unsigned int drawBuffer, ClearMode clearMode);

    /// Removes a clearing target for renderer.
    void removeClearTarget(GraphicsClearTarget target);

    /// Sees if renderer has specific clear target.
    bool hasClearTarget(GraphicsClearTarget target) const;

    /// See if clear is enabled.
    bool isClearEnabled() const;

    /// Set clear color for renderer.
    void setClearColor(ColorRGBA colorRGBA);

    /// Set a color write mode for renderer.
    void setColorWriteMode(GraphicsColorWriteMode colorWriteMode);

    /// Gets current color write mode from renderer.
    GraphicsColorWriteMode getColorWriteMode() const;

    /// Sets scissor test state and optional rectangle for renderer.
    void setScissorTest(optional<ViewportRectangle> scissor);

    /// Set clear depth for renderer.
    void setClearDepthValue(float clearDepthValue);

    /// Set clear stencil for renderer.
    void setClearStencil(int stencilClearValue);

    /// Sets an active view port for renderer.
    void setViewport(ViewportRectangle viewport);

    /// Sets a vertex buffer for renderer.
    void setVertexBuffer(unsigned int vertexBuffer);

    /// Sets an index buffer for renderer.
    void setIndexBuffer(unsigned int indexBuffer);

    /// Render buffers that are currently bound.
    void drawBuffers();

    /// Sets vertex count for renderer.
    void setVertexCount(unsigned int vertexCount);

    /// Sets the index count for renderer.
    void setIndexCount(unsigned int indexCount);

    /// Sets index data for renderer.
    void setIndexData(void* indexData);

    /// Sets the primitive type for renderer.
    void setPrimitiveType(GraphicsPrimitiveType prmitiveType);


    /// Finds uniform location for given uniform from active shader.
    /// The data will be stored to uniform cache and fetched from in subsequent calls.
    /// \note Comparing strings is expensive, so avoid calling this function.
    //        Use ShaderProgram::getUniformLocation() instead when possible.
    int getUniformLocationSlow(const string& uniformName) const;

    /// Returns array uniform length for given uniform. If uniform with
    /// given name is not found, returns 0. If uniform is not an array, returns 1.
    unsigned int getUniformArrayLength(const char* uniformName) const;

    /// Sets integer uniform for renderer, using currently bound shader.
    void setUniformInteger(int value, int uniformLocation);

    /// Sets float uniform for renderer, using currently bound shader.
    void setUniformFloat(float value, int uniformLocation);

    /// Sets uniform float array for renderer.
    void setUniformFloatArray(ShaderProgram::FixedUniform fixedUniform, size_t count, const float* values);

    /// Sets uniform float array for renderer.
    void setUniformFloatArray(int uniformLocation, size_t count, const float* values);

    /// Sets uniform vec2 for renderer, using currently bound shader.
    void setUniformVec2(Vector2 value, int uniformLocation);

    /// Sets uniform vec3 for renderer, using currently bound shader.
    void setUniformVec3(Vector3 value, int uniformLocation);

    /// Sets uniform vec4 for renderer, using currently bound shader.
    void setUniformVec4(Vector4 value, int uniformLocation);

    /// Sets arbitrary vector array with dimension to renderer, using currently bound shader.
    void setUniformVecArray(ShaderProgram::FixedUniform fixedUniform, size_t count, const Vector3* values);

    /// Sets arbitrary vector array with dimension to renderer, using currently bound shader.
    void setUniformVecArray(int uniformLocation, size_t count, const Vector3* values);

    /// Sets arbitrary vector array with dimension to renderer, using currently bound shader.
    void setUniformVecArray(ShaderProgram::FixedUniform fixedUniform, size_t count, const Vector4* values);

    /// Sets arbitrary vector array with dimension to renderer, using currently bound shader.
    void setUniformVecArray(int uniformLocation, size_t count, const Vector4* values);

    /// Sets uniform colorRGBA for renderer, using currently bound shader.
    void setUniformColorRGBA(ColorRGBA value, int uniformLocation);

    /// Sets matrix3x3 uniform for renderer, using currently bound shader.
    void setUniformMatrix3x3(Matrix3x3 value, int uniformLocation);

    /// Sets matrix4x4 uniform for renderer, using currently bound shader.
    void setUniformMatrix4x4(Matrix4x4 value, int uniformLocation);


    /// Switches an scalar value for renderer if necessary, e.g. depth clear value.
    void setActiveScalar(GraphicsScalar scalar, float value);

    /// Returns a current scalar value from renderer.
    float getActiveScalar(GraphicsScalar scalar) const;


    /// Sets a blend mode for renderer.
    void setBlendMode(GraphicsBlendMode blendMode);

    /// Gets a blend mode for renderer.
    GraphicsBlendMode getBlendMode() const;

    /// Sets a cull mode for renderer.
    void setCullMode(GraphicsCullMode cullMode);

    /// Gets a cull mode for renderer.
    GraphicsCullMode getCullMode() const;

    /// Sets a depth pass mode for renderer.
    void setDepthTest(GraphicsCompareFunction depthMode);

    /// Gets a depth pass mode for renderer.
    GraphicsCompareFunction getDepthTest() const;

    /// Sets a stencil function for renderer.
    void setStencilFunction(GraphicsCompareFunction stencilCompareFunction, unsigned int referenceValue,
                            unsigned int maskValue);

    /// Sets a stencil operation for renderer.
    void setStencilOperation(GraphicsStencilOperation stencilFailOperation,
                             GraphicsStencilOperation stencilPassDepthFailOperation,
                             GraphicsStencilOperation stencilPassDepthPassOperation);

    /// Gets stencil function from renderer.
    void getStencilFunction(GraphicsCompareFunction* out_stencilCompareFunction, unsigned int* out_referenceValue,
                            unsigned int* out_maskValue) const;

    /// Gets a stencil operation from renderer.
    void getStencilOperation(GraphicsStencilOperation* out_stencilFailOperation,
                             GraphicsStencilOperation* out_stencilPassDepthFailOperation,
                             GraphicsStencilOperation* out_stencilPassDepthPassOperation) const;


    /// Sets matrix for a renderer.
    void setMatrix(FixedMatrix matrixType, Matrix4x4 matrix);

    /// Gets a matrix from renderer.
    Matrix4x4 getMatrix(FixedMatrix matrixType) const;

    /// Calculates projection * camera * world matrix.
    void calculateProjectionCameraWorldMatrix();

    /// Applies transformations from renderer to GPU.
    void applyTransformation();


    /// Sets texture unit active.
    void setActiveTextureUnit(unsigned int textureUnit);

    /// Applies texture uniforms for the renderer.
    void applyTextureSizeUniforms(ShaderTextureUniform textureUniforms, unsigned int textureWidth, unsigned int textureHeight);

    /// Applies texture for renderer using currently bound shader (required) and texture uniform (required).
    void applyTexture(int textureUniformLocation, unsigned int textureHandle, Texture::Type type);

    /// Sets texture uniform location for renderer, effectively used for
    /// storing the integer in renderer to retrieve it when binding textures.
    void setUniformTexture(int uniformLocation);

    /// Gets texture uniform location from renderer.
    int getUniformTexture() const;


    /// Detaches texture handle from all texture units it has been applied for.
    void detachTextureHandle(unsigned int textureHandle);

    /// Detaches texture from rendering.
    void detachTexture();

    /// Invalidates texture handle from renderer without affecting GL state.
    void invalidateTextureHandle(unsigned int textureHandle);

    /// Binds specified texture of specified type to currently active texture unit.
    /// \param type Type of texture to bind.
    /// \param texture Texture object handle to bind.
    /// \return Texture type and object handle that was previously bound to the currently active texture unit.
    pair<Texture::Type, unsigned int> bindTexture(Texture::Type type, unsigned int texture);

    /// Generates new texture for renderer.
    unsigned int generateTexture();

    /// Uploads texture data to GPU.
    void setTextureImage2D(unsigned int glTextureImageTarget, unsigned int mipmapLevel,
                           GraphicsFormat format, unsigned int width, unsigned int height, const void* data);

    /// Uploads texture subimage data to GPU.
    void setTextureSubImage2D(unsigned int glTextureImageTarget, unsigned int mipmapLevel,
                              GraphicsFormat format, unsigned int x, unsigned int y,
                              unsigned int width, unsigned int height, const void* data);

    /// Specifies immutable texture format and shape.
    void textureStorage(Texture::Type type, int sampleCount, int mipmapLevelCount, GraphicsFormat format,
                        unsigned int width, unsigned int height, unsigned int depth, bool fixedSampleLocations);

    /// Generates mipmaps for currently bound texture.
    void generateMipmaps(Texture::Type textureType);

    /// Deletes texture via renderer.
    void deleteTexture(unsigned int textureHandle);

    /// Sets wrap mode for currently bound texture in current texture unit.
    void setTextureAddressingMode(Texture::Type type, Sampler::AddressingMode texAddress);

    /// Sets texture filter for currently bound texture in current texture unit.
    /// \param type Selects which texture to edit (current 2d, cubemap etc.)
    /// \param minificationFilter Minification filter for texture.
    /// \param magnificationFilter Magnification filter for texture.
    /// \param anisotropy Anisotropic filtering level for texture. Values <= 1.0f disable the feature.
    void setTextureFilter(Texture::Type type, Sampler::Filter mininificationFilter, Sampler::Filter magnificationFilter,
                          Sampler::MipmapMode mipmapMode, float anisotropy);

    /// Sets texture swizzle mask for currently bound alpha only texture in current texture unit.
    /// This method makes all the color channels map to the alpha channel.
    /// Note: Use this method only for GraphicsFormatALPHA8_UNORM texture format,
    /// and if the native OpenGL driver supports \e GL_ARB_texture_swizzle or \e GL_EXT_texture_swizzle extension.
    /// \param type Selects which texture to edit (current 2d, cubemap etc.)
    /// \param mask Swizzle mask for the texture.
    ///             This can be a custom swizzle mask or chosen from the predefined ones:
    ///             MaskRedWithAlpha, MaskGreenWithAlpha, MaskBlueWithAlpha or MaskAllWithAlpha.
    void setTextureSwizzleMask(Texture::Type target, const TextureSwizzleMask& mask);

    /// Sets texture comparison function for currently bound texture in current texture unit.
    /// \param type Selects which texture to edit (current 2d, cubemap etc.)
    /// \param type isEnabled If true, depth comparison mode will be enabled for the texture, otherwide depth comparison will be disabled.
    /// \param textureCompareFunction Selects which texture comparison function to use.
    void setTextureCompare(Texture::Type type, bool isEnabled, GraphicsCompareFunction textureCompareFunction);

    /// Sets pack storage for renderer. Specifies how the pixel data is aligned.
    void setPixelStorePack(unsigned int packBytes);

    /// Sets unpack storage for renderer. Specifies how the pixel data is aligned.
    void setPixelStoreUnpack(unsigned int unpackBytes);

    /// Creates shader.
    unsigned int createShader(ShaderType type);

    /// Creates shader program. Returns the handle to the program.
    unsigned int createShaderProgram();

    /// Refreshes render context to contain all proper states.
    void refreshRenderContext(bool geometryRendering);

    /// Attaches shader to program.
    void attachShaderToProgram(unsigned int programHandle, unsigned int shaderHandle);

    /// Detaches shader from program.
    void detachShaderFromProgram(unsigned int programHandle, unsigned int shaderHandle);

    /// Binds attribute to given location index, for example "kzPosition" to 0.
    void bindAttributeToLocation(unsigned int programHandle, unsigned int locationIndex, kzString attributeName);

    /// Links shader program with given handle.
    bool linkShaderProgram(unsigned int programHandle, kzString shaderName);

    /// Compiles source shader and deploys it to GPU.
    bool compileSourceShader(ShaderType shaderType, unsigned int shaderHandle, const char* const shaderCode,
                             string_view shaderName);

    /// Deploys binary shaders.
    ///
    /// \return true if binary shader was accepted by the graphics driver.
    bool deployBinaryShader(unsigned int count, const unsigned int* shaders, unsigned int binaryFormat,
                            const void* data, unsigned int dataSize);

    /// Initializes shader program from program binary data. Program binaries are vendor, device and driver version specific.
    /// If deployBinaryProgram() succeeds, program is in linked state. If deployBinaryProgram() fails, program remains in
    /// previous state.
    /// See \see isProgramBinaryFormatSupported to check if specific program binary format is supported by graphics device.
    /// See \see getProgramBinary to query back program binary of a previously linked GL shader program from graphics device.
    /// \param program GL shader program name to initialize from program binary data.
    /// \param binaryFormat Binary format for data.
    /// \param data Program binary data.
    /// \param dataSize Number of bytes in data.
    /// \return true if shader program was successfully initialized from program binary data, otherwise false.
    bool deployBinaryProgram(unsigned int program, unsigned int binaryFormat, const void* data, unsigned int dataSize);

    /// Gets binary representation for GL shader program. Program binaries are vendor, device and driver version specific.
    /// \see isProgramBinaryFormatSupported
    /// \see deployBinaryProgram
    /// \param program GL shader program name to get program binary from.
    /// \param binaryFormat GL program binary format will be returned here, or KZS_GL_NONE if no program binary format was supported by graphics device.
    /// \return Program binary data. If no program binary format was supported by graphics device, size of data will be 0.
    string getProgramBinary(unsigned int program, unsigned int& binaryFormat);

    /// Deletes shader program and attached shaders.
    void deleteShaderProgram(unsigned int programHandle);

    /// Deletes shader
    void deleteShader(unsigned int shaderHandle);

    /// Returns fixed shader uniform location of given fixed uniform.
    ///
    /// \return uniform location of the fixed uniform, -1 if uniform is not present.
    int getFixedUniformLocation(ShaderProgram::FixedUniform fixedUniform) const;

    /// Generates new texture for renderer.
    unsigned int generateFramebuffer();

    /// Deletes framebuffer.
    void deleteFramebuffer(unsigned int frameBufferHandle);

    /// Binds framebuffer.
    void bindFramebuffer(unsigned int frameBufferHandle);

    /// Checks if the framebuffer status is complete.
    /// If framebuffer status is not complete, error code will be logged.
    /// \note Detailed error condition is only available in debug builds.
    /// \note Avoid calling isFramebufferComplete() in release builds, as this may cause graphics driver to slow down.
    /// \return True if status is framebuffer complete, otherwise false.
    bool isFramebufferComplete();

    /// Invalidates framebuffer attachments.
    /// After invalidation, contents of specified attachments are undefined.
    /// The graphics driver may perform performance and memory optimizations
    /// when it knows that contents of specific attachments are no longer needed.
    /// \param target Framebuffer target to invalidate.
    /// \param attachments Bits from Framebuffer::AttachmentBit to specify attachments to invalidate. Surfaces that are attached to these attachment points will be invalidated.
    void invalidateFramebufferAttachments(Framebuffer::Target target, bitset<Surface::APIAttachmentCount> attachments) const;

    /// Attaches texture to the currently active Framebuffer.
    /// \param imageTarget GL texture image target. For cubemap texture this specifies the cubemap face.
    /// \param attachment Framebuffer attachment point where texture should be attached to.
    /// \param textureHandle GL texture object name to attach.
    /// \param mipmapLevel Mipmap level of texture to attach.
    /// \param implicitSampleCount When implicit multisample textures are used, this specifies the number of samples to use.
    ///                            When implicit multisample textures are not used, value here must be 0.
    void framebufferTexture2D(unsigned int glTextureImageTarget, Surface::APIAttachment attachment,
                              unsigned int textureHandle, unsigned int mipmapLevel, unsigned int implicitSampleCount);

    /// Attaches renderbuffer to the currently active Framebuffer.
    /// \param attachment Framebuffer attachment point where renderbuffer should be attached to.
    /// \param renderbuffer GL renderbuffer object name to attach.
    void framebufferRenderbuffer(Surface::APIAttachment attachment, unsigned int renderbuffer);

    /// Generates new texture for renderer.
    /// \return Newly allocated GL renderbuffer object name.
    unsigned int generateRenderbuffer();

    /// Deletes framebuffer.
    /// \param renderbuffer GL renderbuffer object name to delete.
    void deleteRenderbuffer(unsigned int renderbuffer);

    /// Binds framebuffer for editing.
    /// \param renderbuffer Gl renderbuffer object name to bind.
    void bindRenderbuffer(unsigned int renderbuffer);

    /// Sets storage for currently bound renderbuffer.
    /// \param format GraphicsFormat for the renderbuffer.
    /// \param width Width for the renderbuffer in pixels.
    /// \param height Height for the renderbuffer in pixels.
    /// \param explicitSampleCount Number of multisample samples.
    void renderbufferStorage(GraphicsFormat format, unsigned int width, unsigned int height, unsigned int explicitSampleCount);

    /// Generates new index or vertex buffer or uniform buffer object name.
    unsigned int generateBuffer();

    /// Sets static vertex buffer data.
    void setVertexBufferData(unsigned int dataSize, const void* data);

    /// Sets static index buffer data.
    void setIndexBufferData(unsigned int dataSize, const void* data);

    /// Uploads vertex buffer subdata with given offset and size.
    void setVertexBufferSubData(unsigned int offset, unsigned int size, const void* data);

    /// Uploads index buffer subdata with given offset and size.
    void setIndexBufferSubData(unsigned int offset, unsigned int size, const void* data);

    /// Deletes vertex or index buffer.
    void deleteBuffer(unsigned int handle);

    /// Sets vertex attribute array to be enabled.
    /// \deprecated Implicitly handled by beginVertexArray() and setVertexBufferPointer().
    /// \param attributeHandle index to attribute to enable
    void enableVertexAttributeArray(unsigned int attributeHandle);

    /// Sets vertex attribute array to be disabled.
    /// \deprecated Implicitly handled by beginVertexArray() and setVertexBufferPointer().
    /// \param attributeHandle index to attribute to disable
    void disableVertexAttributeArray(unsigned int attributeHandle);

    /// Update vertex attribute configurations to the graphics driver.
    /// This should be called before each draw call if vertex attribute configuration has been changed with any of
    /// enableVertexAttributeArray(), disableVertexAttributeArray() or setVertexBufferPointer().
    void applyVertexAttributeArrays();

    /// Sets attribute data source for currently enabled vertex attribute array.
    /// \note Attribute will be sourced from the vertex buffer (GPU memory) which is current at the time
    ///       of call to setVertexBufferPointer(). If current vertex buffer is zero, attribute data is
    ///       sourced from CPU memory (also known as "client side data" in OpenGL).
    /// \param location Attribute location.
    /// \param dimension Number of vector components in the attribute. Valid values are 1, 2, 3 and 4.
    /// \param attributeDataType Data type for attribute.
    /// \param stride Stride, number of bytes to get from one vertex to the next vertex. Valid values are positive integers.
    /// \param data If current vertex buffer is non-zero, this is offset in bytes to current vertex buffer GPU memory.
    ///             If current vertex buffer is zero, this is CPU memory address to attribute data.
    void setVertexBufferPointer(unsigned int location, int dimension, GraphicsDataType attributeDataType, int stride, const void* data);

    /// Sets active shader for renderer.
    void setActiveShaderHandle(unsigned int activeShaderHandle, int const* fixedUniformMap,
                               const int* vertexAttributeMap);

    /// Gets active shader handle from renderer.
    unsigned int getActiveShaderHandle() const;

    /// Gets active vertex attribute map from renderer.
    const int* getActiveShaderAttributeMap() const;

    /// Gets active fixed uniform map from renderer.
    const int* getActiveFixedUniformMap() const;

    /// Specifies default frame buffer (screen) for renderer.
    void setDefaultFramebuffer(unsigned int frameBufferHandle);

    /// Sets active frame buffer for renderer.
    void setActiveFramebuffer(unsigned int frameBufferHandle);

    /// Sets the number of draw buffers for currently active framebuffer.
    /// \note OpenGL ES 3 is required for drawBufferCount > 1
    /// \param drawBufferCount Number of color attachments
    void setColorBufferCount(unsigned int drawBufferCount);

    /// Resets active frame buffer for renderer to default (screen).
    void resetActiveFramebuffer();

    /// Callback prototype for setActiveFramebuffer.
    typedef void (*FramebufferCallback)(unsigned int frameBufferHandle);

    /// Sets callback function that is called after setActiveFramebuffer.
    void setActiveFramebufferCallback(FramebufferCallback callbackFunction);

    /// Gets active frame buffer handle from.
    unsigned int getActiveFramebuffer() const;

    /// Reads the pixels from the current frame buffer.
    void readPixels(int x, int y, int width, int height, GraphicsFormat format, void* pixels);

    /// Returns native pixel read format from renderer.
    GraphicsFormat getNativePixelReadFormat();

    /// Begins a material for renderer.
    void beginMaterialSetup();

    /// Ends a material for renderer.
    void endMaterialSetup();

    /// Begins set of vertex arrays.
    void beginVertexArray();

    /// Sets vertex array data.
    void setVertexArrayData(VertexAttribute::Semantic attribute, const void* data);

    void setVertexArrayData(VertexAttribute::Semantic attribute, GraphicsDataType dataType, const void* data);

    /// Ends vertex array. Renders the specified vertex lists and finishes the usage.
    void endVertexArray(GraphicsPrimitiveType primitiveType, unsigned int count);

    /// Gets the current vertex array flags from renderer.
    unsigned int getCurrentVertexArrayFlags() const;

    /// Gets current vertex array data from renderer. Reset when switching the shader.
    const void* getCurrentVertexArrayAttributeData(VertexAttribute::Semantic attribute) const;

    /// Sets line rendering width for renderer.
    void setLineWidth(float lineWidth);

    /// Flushes the GPU pipeline, forces all commands to be executed in finite time.
    void flush() const;

    void pushStatistics();

    void popStatistics();

    /// Gets index count from renderer.
    unsigned int getIndexCount() const;

    /// Gets triangle count from renderer.
    unsigned int getTriangleCount() const;

    /// Gets vertex count from renderer.
    unsigned int getVertexCount() const;

    /// Gets batch count from renderer (number of draw calls, such as drawElements and drawArrays).
    unsigned int getBatchCount() const;

    /// Gets shader switches.
    unsigned int getShaderSwitchCount() const;

    /// Gets uniform sending count from renderer.
    unsigned int getUniformSendCount() const;

    /// Gets number of texture switches from renderer.
    unsigned int getTextureSwitchCount() const;

    /// Gets number of framebuffer switches from renderer.
    unsigned int getFramebufferSwitchCount() const;

    /// Gets number of buffer switches (VBO + IBO) from renderer.
    unsigned int getBufferSwitchCount() const;

    /// Returns potential heavyweight calls such as buffer or texture updates
    /// and glFinish from renderer. Potential due to GPU implementation may
    /// decide when heavyweight occurs (e.g. reading cannot be performed before
    /// write operation finishes).
    unsigned int getHeavyweightCallCount() const;

    /// Checks if GL shader binary format is supported
    /// \param glShaderBinaryFormat GL shader binary format to check
    /// \return True if shader binary format is supported.
    bool isShaderBinaryFormatSupported(unsigned int glShaderBinaryFormat) const;

    /// Checks if GL program binary format is supported
    /// \param glProgramBinaryFormat GL program binary format to check
    /// \return True if program binary format is supported.
    bool isProgramBinaryFormatSupported(unsigned int glProgramBinaryFormat) const;

    /// Sets GPU calls enabled / disabled.
    void setGPUCallsEnabled(bool enabled);

    /// Checks if GPU calls are enabled.
    bool GPUCallsIsEnabled() const;

    /// Is coverage buffer supported or not.
    bool isSupported(Support feature) const;

    /// Return support for multisample textures and renderbuffers.
    Multisample getMultisampleSupport() const;

    /// Return support for program binaries
    ProgramBinary getProgramBinarySupport() const;

    /// Return support for half float texture format
    HalfFloatTexture getHalfFloatTextureSupport() const;

    /// Return support for float texture format
    FloatTexture getFloatTextureSupport() const;

    /// Return support for tex storage
    TexStorage getTexStorageSupport() const;

    /// Return support for tex storage
    bool getTexStorageSupport(Texture::Type type, unsigned int samples) const;

    /// Creates image object, returns NULL if no hardware support. Image object can be
    /// bound as texture input.  Requires surface to be set for renderer via setSurface,
    /// otherwise throws an error.
    void* createImageObject(void* dataPointer, int target, int* attributes);

    /// Deletes image object created with createImageObject.
    void deleteImageObject(void* imageObject);

    /// Sets image object bound to currently bound texture (type).
    void setImageTargetTexture(Texture::Type type, void* imageObject);

    /// Gets maximum anisotropy.
    float getMaximumAnisotropy() const;

    /// Gets maximum texture side size.
    unsigned int getMaximumTextureSize(Texture::Type textureType) const;

    /// Gets maximum renderbuffer size.
    unsigned int getMaximumRenderbufferSize() const;

    /// Gets maximum viewport width.
    unsigned int getMaximumViewportWidth() const;

    /// Gets maximum viewport height.
    unsigned int getMaximumViewportHeight() const;

    /// Gets maximum vertex attribute count.
    unsigned int getMaximumVertexAttributeCount() const;

    /// Gets maximum sample count for multisample.
    unsigned int getMaximumSampleCount() const;

    // TODO These depend on currently bound read framebuffer

    /// Returns GL constant for the color read format used in reading back data from framebuffer (RendererReadPixels).
    int getColorReadFormat();

    /// Returns GL constant for the color read type used in reading back data from framebuffer (RendererReadPixels).
    int getColorReadType();


    /// Invalidates all handles from renderer without affecting GL state.
    void invalidateAllocations();

    /// Gets GPU buffer manager from renderer.
    ::KzcGPUBufferManager* getGPUBufferManager() const;

    /// Logs information about renderer capabilities.
    void logOpenGLInformation(unsigned int flags) const;

    /// Resolve multisample framebuffer.
    /// Performs a blit from source framebuffer into destination framebuffer. This has implicit effect of resolving multisample samples.
    /// \param sourceFramebuffer Source framebuffer ID.
    /// \param destinationFramebuffer Destination framebuffer ID.
    /// \param srcOffsetX Copied area x offset in source framebuffer.
    /// \param srcOffsetX Copied area y offset in source framebuffer.
    /// \param srcWidth Copied area width in source framebuffer.
    /// \param srcHeight Copied area height in source framebuffer.
    /// \param dstOffsetX Copied area x offset in destination framebuffer.
    /// \param dstOffsetX Copied area y offset in destination framebuffer.
    /// \param dstWidth Copied area width in destination framebuffer.
    /// \param dstHeight Copied area height in destination framebuffer.
    /// \param color Set to true to resolve color channel.
    /// \param depth Set to true to resolve depth channel.
    /// \param stencil Set to true to resolve stencil channel.
    void resolveMultisample(unsigned int sourceFramebuffer, unsigned int destinationFramebuffer, unsigned int srcOffsetX, unsigned int srcOffsetY, unsigned int srcWidth, unsigned int srcHeight,
                            unsigned int dstOffsetX, unsigned int dstOffsetY, unsigned int dstWidth, unsigned int dstHeight, bool color, bool depth, bool stencil);

    /// Resolve multisample framebuffer.
    /// Performs a blit from source framebuffer into destination framebuffer. This has implicit effect of resolving multisample samples.
    /// Only resolves color buffer.
    /// \param sourceFramebuffer Source framebuffer ID.
    /// \param destinationFramebuffer Destination framebuffer ID.
    /// \param srcOffsetX Copied area x offset in source framebuffer.
    /// \param srcOffsetX Copied area y offset in source framebuffer.
    /// \param srcWidth Copied area width in source framebuffer.
    /// \param srcHeight Copied area height in source framebuffer.
    /// \param dstOffsetX Copied area x offset in destination framebuffer.
    /// \param dstOffsetX Copied area y offset in destination framebuffer.
    /// \param dstWidth Copied area width in destination framebuffer.
    /// \param dstHeight Copied area height in destination framebuffer.
    void resolveMultisample(unsigned int sourceFramebuffer, unsigned int destinationFramebuffer, unsigned int srcOffsetX, unsigned int srcOffsetY, unsigned int srcWidth, unsigned int srcHeight,
                            unsigned int dstOffsetX, unsigned int dstOffsetY, unsigned int dstWidth, unsigned int dstHeight)
    {
        resolveMultisample(sourceFramebuffer, destinationFramebuffer, srcOffsetX, srcOffsetY, srcWidth, srcHeight, dstOffsetX, dstOffsetY, dstWidth, dstHeight, true, false, false);
    }

    /// Resolve multisample samples from source texture into destination texture.
    /// \param src Source texture (with multisampling enabled).
    /// \param dst Destination texture (with multisampling disabled).
    /// \param width Width of the area to be copied from source to destination.
    /// \param height Height of the area to be copied from source to destination.
    /// \param color Set to true to resolve color channel.
    /// \param depth Set to true to resolve depth channel.
    void resolveMultisample(Texture& src, Texture& dst, unsigned int offsetX, unsigned int offsetY, unsigned int width, unsigned int height, bool color, bool depth);
    /// Resolve multisample samples from source texture into destination texture.
    /// Only resolves color buffer.
    /// \param src Source texture (with multisampling enabled).
    /// \param dst Destination texture (with multisampling disabled).
    /// \param width Width of the area to be copied from source to destination.
    /// \param height Height of the area to be copied from source to destination.
    /// \param color Set to true to resolve color channel.
    /// \param depth Set to true to resolve depth channel.
    void resolveMultisample(Texture& src, Texture& dst, unsigned int offsetX, unsigned int offsetY, unsigned int width, unsigned int height)
    {
        resolveMultisample(src, dst, offsetX, offsetY, width, height, true, false);
    }

    /// Gets current viewport rectangle from renderer.
    ViewportRectangle getViewport() const
    {
        return m_viewport;
    }

    /// Gets current scissor rectangle from renderer.
    /// The rectangle is returned even if scissor test is not enabled. In this situation it is the last set scissor rectangle.
    ViewportRectangle getScissor() const
    {
        return m_scissor;
    }

    enum Workaround
    {
        /// Disable support for half float vertex attributes on Mali devices
        WorkaroundMaliHalfFloatTextureCoordinate = 0,

        /// Enable color buffer half float on Tegra 3
        WorkaroundTegra3ColorBufferHalfFloat,

        /// Enable color buffer half float on Adreno 330
        WorkaroundAdreno330ColorBufferHalfFloat,

        /// VirtualBox/Chromium incorrectly reports number of image units
        WorkaroundChromiumTextureImageUnitCount,

        /// Disable half float vertex attributes
        WorkaroundPVRFrameAMDHost,

        /// Disable tex storage
        WorkaroundAMDCompressedTexStorage,

        /// Disable 32f depth buffer format
        WorkaroundPVRFrameDepth32f,

        /// Disable 32f depth buffer format
        WorkaroundVivanteDepth32f,

        /// Disable GL_OES_required_internalformat when vendor is known to have drivers with related issues
        WorkaroundFaultyRequiredInternalformat,

        WorkaroundCount
    };

    /// Enable a renderer workaround
    void enableWorkaround(Workaround workaround)
    {
        m_workaroundEnable[workaround] = true;
    }

    /// Disable a renderer workaround
    void disableWorkaround(Workaround workaround)
    {
        m_workaroundEnable[workaround] = false;
    }

    /// Return if workaround is enabled or not
    bool isWorkaroundEnabled(Workaround workaround) const
    {
        return m_workaroundEnable[workaround];
    }

    /// Set workaround enable state to true or false
    void setWorkaroundEnable(Workaround workaround, bool enabled)
    {
        m_workaroundEnable[workaround] = enabled;
    }

    const KzcMemoryManager* getMemoryManager() const { return m_memoryManager; }

    /// Find a valid texture format which is supported by graphics adapter and is
    /// compatible with specified format. Returned format must be binary compatible with
    /// the format parameter. For example, input ETC1 format can return ETC2 format).
    /// \param format Format that result format should be compatible with.
    /// \param features Usage bits that should be supported by the format.
    /// \return Format which is compatible with requested format, or GraphicsFormatNone if no such format exists.
    GraphicsFormat findValidTextureFormat(GraphicsFormat format, unsigned int features) const;

    /// Describes what the specified format can be used for in the specified renderer.
    unsigned int getFeatures(GraphicsFormat format) const;

    /// Returns whether format supports requested features
    bool supports(GraphicsFormat format, unsigned int features) const;

    /// Returns whether format can be used as texture by the specified renderer.
    bool supportsTexture(GraphicsFormat format) const;

    /// Returns whether format can be used as renderbuffer by the specified renderer.
    bool supportsRenderbuffer(GraphicsFormat format) const;

    /// Returns whether format can be used as color attachment in framebuffers.
    bool supportsColorAttachment(GraphicsFormat format) const;

    /// Returns whether format can be used as depth/stencil attachment in framebuffers.
    bool supportsDepthStencilAttachment(GraphicsFormat format) const;

    /// Returns a fallback format which supports specified usage flags.
    GraphicsFormat getFallback(GraphicsFormat format, unsigned int usageFlags) const;

    /// Returns a depth/stencil renderbuffer format which is supported by renderer.
    GraphicsFormat getDepthStencilFormatForRenderbuffer(bool depth, bool stencil) const;

    /// Returns a depth/stencil texture format which is supported by renderer.
    GraphicsFormat getDepthStencilFormatForTexture(bool depth, bool stencil) const;

    /// For given vertex attribute, specified by attribute location, configures attribute
    /// dimension, datatype, stride and starting offset in current vertex buffer.
    /// \note Attribute data is sourced from the vertex buffer GPU memory which is current at
    ///       the time of applyAttributePointer() call. If current vertex buffer is 0, attribute
    ///       data is sourced from CPU memory (also known as "client side data" in OpenGL).
    /// \param location Attribute location to modify.
    /// \param dimension Dimension for attribute. Valid values are 1, 2, 3 and 4.
    /// \param dataType Data type for attribute.
    /// \param stride Stride for attribute. Valid values are positive integers.
    /// \param data Starting offset in current vertex buffer GPU memory for attribute data.
    ///             If current vertex buffer is 0, this is starting address in CPU memory for attribute data.
    void applyAttributePointer(unsigned int location, int dimension, GraphicsDataType dataType, int stride, const void* data) const;

    /// Returns GL API format, internal format, type triplet for given Format.
    void getGLFormatTriplet(GraphicsFormat format, unsigned int features,
                            unsigned int* out_glFormat, unsigned int* out_glInternalFormat, unsigned int* out_glType) const;

    /// Returns true if graphics format supports texture storage
    bool supportsTexStorage(GraphicsFormat format, unsigned int features) const;

    /** Free memory used by uniform caches. */
    void clearUniformCaches();

    /// Advances renderer wall clock with time delta.
    /// \param deltaTime Wall clock delta time.
    void advanceGlobalTime(chrono::milliseconds deltaTime);

    /// Gets wall clock time in milliseconds since program start.
    /// \param Wall clock time since program start.
    chrono::milliseconds getGlobalTime() const;

    /// Returns supported OpenGL ES version number.
    /// Version is encoded into integer with the following formula:
    /// major version times 100 plus minor version times ten.
    /// For example, value 310 would mean version 3.1.
    /// \return OpenGL ES version number.
    int getGlesVersion() const;

private:
    array<bool, WorkaroundCount> m_workaroundEnable;

    /// Default textures. These are lazily created on demand.
    array<TextureSharedPtr, Texture::TypeCount> m_defaultTextures;

    // Helpers
    bool checkGLSupport(kzString glExtension, int minGl) const;
    bool checkGLESSupport(kzString glesExtension, int minGles) const;
    void resetGPUStates();
    void setDefaultValues();

    /// Updates the statistic when a batch is rendered.
    void batchRendered(unsigned int indexCount, unsigned int vertexCount, unsigned int primitiveType);

    Renderer(const Renderer&) KZ_DELETED_FUNCTION;
    Renderer& operator=(const Renderer&) KZ_DELETED_FUNCTION;

    /// Counters for rendering events that happen during one frame.
    struct DebugInfo
    {
        /// Constructor.
        explicit DebugInfo() :
            indexCount(0u),
            triangleCount(0u),
            vertexCount(0u),
            batchCount(0u),
            shaderSwitches(0u),
            textureSwitches(0u),
            uniformSendings(0u),
            framebufferSwitches(0u),
            bufferSwitches(0u),
            heavyweightCalls(0u)
        {
        }

        /// Index count.
        unsigned int indexCount;
        /// Triangle count.
        unsigned int triangleCount;
        /// Vertex count.
        unsigned int vertexCount;
        /// Batch count.
        unsigned int batchCount;
        /// Shader switches count.
        unsigned int shaderSwitches;
        /// Texture switches count.
        unsigned int textureSwitches;
        /// Number of uniform sendings for frame.
        unsigned int uniformSendings;
        /// Number of frame buffer switches.
        unsigned int framebufferSwitches;
        /// Index & vertex buffer switches.
        unsigned int bufferSwitches;
        /// Potential heavyweight calls (glBuffer(Sub)Data, glFinish, glTex(Sub)Image2D.
        unsigned int heavyweightCalls;
    };

    /// Structure to hold settings for vertex attribute
    struct VertexAttributePointerState
    {
        /// Default constructor.
        explicit VertexAttributePointerState() :
            enabled(false),
            bufferHandle(0u),
            dimension(0),
            dataType(GraphicsDataTypeNone),
            stride(0),
            data(0)
        {
        }

        /// Copy constructor.
        /// \param other Source attrib pointer structure.
        VertexAttributePointerState& operator=(const VertexAttributePointerState& other)
        {
            enabled = other.enabled;
            bufferHandle = other.bufferHandle;
            dimension = other.dimension;
            dataType = other.dataType;
            stride = other.stride;
            data = other.data;
            return *this;
        }

        /// Returns true if other pointer has equal settings, ignoring enabled.
        /// \note This ignores 'enabled' member.
        bool settingsDiffer(const VertexAttributePointerState& other) const
        {
            return (bufferHandle != other.bufferHandle) || (dimension != other.dimension) || 
                   (dataType != other.dataType) || (stride != other.stride) || (data != other.data);
        }

        /// Sets attribute pointer settings
        void set(unsigned int bufferHandleIn, unsigned int dimensionIn, GraphicsDataType dataTypeIn, unsigned int strideIn,
                 const void* dataIn)
        {
            bufferHandle = bufferHandleIn;
            dimension = dimensionIn;
            dataType = dataTypeIn;
            stride = strideIn;
            data = dataIn;
        }

        bool enabled;
        unsigned int bufferHandle;
        int dimension;
        GraphicsDataType dataType;
        int stride;
        const void* data;
    };

    /// Structure for settings of enabled/disabled and effective/requested state of vertex attrib pointers.
    struct VertexAttributePointerInfo
    {
        /// Actual current setting.
        VertexAttributePointerState effective;
        /// Requested setting.
        VertexAttributePointerState requested;
    };

    /// Fixed function material states.
    struct MaterialState
    {
        bool blendApplied;    ///< Boolean for if blend is applied.
    };

#if defined(KANZI_RENDERER_ENABLE_UNIFORM_CACHE)
    /// Container for uniform cache, contains all different data types
    /// that can be cached. Uniform cache is implementation for caching
    /// OpenGL uniform values, if value hasn't changed, not sending to GPU.
    typedef unordered_map<int, int> IntegerUniformCache;
    typedef unordered_map<int, float> FloatUniformCache;
    typedef unordered_map<int, Vector2> Vector2UniformCache;
    typedef unordered_map<int, Vector3> Vector3UniformCache;
    typedef unordered_map<int, Vector4> Vector4UniformCache;
    typedef unordered_map<int, Matrix3x3> Matrix3x3UniformCache;
    typedef unordered_map<int, Matrix4x4> Matrix4x4UniformCache;
    typedef unordered_map<int, vector<float> > FloatArrayUniformCache;
    typedef unordered_map<int, vector<Vector3> > Vector3ArrayUniformCache;
    typedef unordered_map<int, vector<Vector4> > Vector4ArrayUniformCache;
    typedef unordered_map<string, int> UniformLocationCache;
    struct UniformCache
    {
        UniformCache() : programHandle (0) { } 
        explicit UniformCache(unsigned int programHandle) : programHandle(programHandle) { }

        unsigned int programHandle;
        IntegerUniformCache integerCache;
        FloatUniformCache floatCache;
        Vector2UniformCache vector2Cache;
        Vector3UniformCache vector3Cache;
        Vector4UniformCache vector4Cache;
        Matrix3x3UniformCache matrix3x3Cache;
        Matrix4x4UniformCache matrix4x4Cache;
        FloatArrayUniformCache floatArrayCache;
        Vector3ArrayUniformCache vector3ArrayCache;
        Vector4ArrayUniformCache vector4ArrayCache;
        UniformLocationCache locationCache;
    };
#endif

    array<bool, StateCount> m_renderState; /// Render states

    /// Information about the supported hardware features.
    struct SupportedFeatures
    {
        explicit SupportedFeatures():
            multisample(MultisampleNone),
            programBinary(ProgramBinaryNone),
            halfFloatTexture(HalfFloatTextureNone),
            floatTexture(FloatTextureNone),
            texStorage(TexStorageNone),
            invalidateFramebuffer(InvalidateFramebufferNone)
        {
            fill(begin(features), end(features), false);
        }

        /// Set of supported graphics formats with texture compression.
        set<GraphicsFormat> compressedGraphicsFormats;
        Multisample multisample;
        ProgramBinary programBinary;
        HalfFloatTexture halfFloatTexture;
        FloatTexture floatTexture;
        TexStorage texStorage;
        InvalidateFramebuffer invalidateFramebuffer;
        array<bool, SupportCount> features;
        vector<unsigned int> compressedTextureFormats;
        vector<unsigned int> shaderBinaryFormats;
        vector<unsigned int> programBinaryFormats;
        vector<string> extensions;
    };

    /// Supported hardware features.
    SupportedFeatures m_supported;

    /// Maximum anisotropy.
    float m_maximumAnisotropy;

    /// Number of texture image units.
    int m_textureImageUnitCount;

    /// Maximum 2D texture size.
    int m_maximumTextureSize;

    /// Maximum cubemap texture size.
    int m_maximumCubemapTextureSize;

    /// Maximum renderbuffer size.
    int m_maximumRenderbufferSize;

    /// Maximum viewport size.
    int m_maximumViewportSize[2];

    /// Maximum number of multisample samples.
    int m_maximumSampleCount;

    /// Maximum vertex attribute count
    int m_maximumVertexAttributeCount;

    /// Maximum stencil buffer bits.
    int m_stencilBufferBits;

    /// Indicates whether the renderer is in an initialized state.
    bool m_initialized;

    GlGraphicsOutput*           m_activeGraphicsOutput;

    /// Color buffer clear settings
    struct ClearColor
    {
        /// Constructor.
        explicit ClearColor():
            mode(),
            intValue(),
            floatValue()
        {
        }

        /// Clear modes for color buffers
        array<ClearMode, 4> mode;

        /// Integer clear values for color buffers
        array<uint32_t[4], 4> intValue;

        /// Float clear values for color buffer
        array<ColorRGBA, 4> floatValue;
    };

    /// Current clear color value.
    ClearColor m_clearColor;

    /// Depth clear value for renderer.
    float m_clearDepthValue;

    /// Stencil clear value for renderer.
    int m_clearStencilValue;

    /// Clear target flag for renderer.
    unsigned int m_clearTarget;

    array<Matrix4x4, FixedMatrixCount> m_activeMatrix;   ///< Active matrices for renderer, e.g. current projection or camera matrices.
    MaterialState               m_materialState;            ///< Defines material state for renderer.

    array<float, GraphicsScalarCount> m_activeScalar;       ///< Active scalar that renderer contains.
    unsigned int                m_activeShaderHandle;       ///< Active shader handle.

    GraphicsBlendMode           m_activeBlendMode;          ///< Active blend mode for renderer.
    GraphicsBlendMode           m_currentBlendFunc;         ///< Current blend func.
    GraphicsCullMode            m_activeCullMode;           ///< Active culling mode for renderer.
    unsigned int                m_currentGLCullFace;        ///< Current cull face.
    GraphicsCompareFunction     m_activeDepthTest;          ///< Active depth mode for renderer.
    unsigned int                m_currentGLDepthFunc;       ///< Current depth func.
    GraphicsCompareFunction     m_activeStencilFunction;    ///< Active stencil mode for renderer.
    GraphicsStencilOperation    m_activeStencilOperationStencilFail;            ///< Active stencil fail operation for renderer.
    GraphicsStencilOperation    m_activeStencilOperationStencilPassDepthFail;   ///< Active stencil pass depth fail operation for renderer.
    GraphicsStencilOperation    m_activeStencilOperationStencilPassDepthPass;   ///< Active stencil pass depth pass operation for renderer.
    int                         m_activeStencilRefValue;    ///< Ref value for stencil.
    unsigned int                m_activeStencilMaskValue;   ///< Mask value for stencil.

    ViewportRectangle           m_viewport;                 ///< Viewport area for rendering.
    ViewportRectangle            m_scissor;                  ///< Scissor area for rendering.

    unsigned int                m_currentVertexCount;       ///< Current vertex count in vertex buffer.
    unsigned int                m_currentIndexCount;        ///< Number of indices currently bound index buffer contains.
    void*                       m_currentIndexData;         ///< Current index buffer data.
    unsigned int                m_currentGLIndexPrimitiveType; ///< Type of the currently bound index buffer.

    unsigned int                m_activeTextureUnit;                ///< Current texture unit for renderer.
    int                         m_currentTextureUniformLocation;    ///< Current texture uniform location.
    const int*                  m_vertexAttributeMap;               ///< Attribute map of the currently bound shader. <RendererVertexAttribute, bindIndex>.
    array<unsigned int, KANZI_RENDERER_MAX_TEXTURE_UNITS>       m_currentTextureHandle; ///< Current texture handle.
    array<Texture::Type, KANZI_RENDERER_MAX_TEXTURE_UNITS>    m_currentTextureType; ///< Current texture type.

    unsigned int                m_currentVertexBuffer;      ///< Currently bound vertex buffer.
    unsigned int                m_currentIndexBuffer;       ///< Currently bound index buffer.
    unsigned int                m_currentUniformBuffer;     ///< Currently bound uniform buffer.

    unsigned int                m_currentVertexArrayFlags;  ///< Currently bound vertex array flags.

    unsigned int                m_defaultFramebufferHandle; ///< Default framebuffer (screen), usually 0.
    unsigned int                m_activeFramebufferHandle;  ///< Currently bound framebuffer, 0 if none.

#if defined(KANZI_RENDERER_ENABLE_UNIFORM_CACHE)
    KzcMemoryManager*           m_cacheMemoryManager;       ///< Memory manager for uniform cache.

    /// Renderer uniform caches for all shaders.
    typedef unordered_map<int, UniformCache> UniformCacheDictionary;
    UniformCacheDictionary      m_uniformCaches;
    UniformCache*               m_currentUniformCache;      ///< Current uniform cache, queried from shader handle.
#endif

    DebugInfo                   m_debugInfo;                ///< Renderer debug info.
    DebugInfo                   m_debugInfoStore;

    FramebufferCallback         m_framebufferCallback;      ///< Framebuffer callback when changed.

    unsigned int                m_pixelStorePack;           ///< Pixel pack storage.
    unsigned int                m_pixelStoreUnpack;         ///< Pixel unpack storage.

    GraphicsColorWriteMode      m_colorWriteMode;           ///< Color write mode.
    unsigned int                m_changeStateFlags;         ///< Change state flags.

    float                       m_lineWidth;                ///< Width for lines.

    /// Currently active fixed uniform locations.
    const int* m_currentFixedUniformLocations;
    /// List of vertex attributes whether they're enabled or disabled. Used on VBOs.
    vector<VertexAttributePointerInfo> m_vertexAttribPointers;

    bool                        m_gpuCallsEnabled;                  ///< GPU calls enabled / disabled.
    const KzcMemoryManager*     m_memoryManager;

#if defined(KANZI_GPU_BUFFER_MANAGER_ENABLED)
    KzcGPUBufferManager*        m_bufferManager;                ///< Manager for GPU buffer pools.
#endif

#if defined(KANZI_RENDERER_RENDER_VERTEX_ARRAYS_VBO)
    array<const void*, VertexAttribute::SemanticCount> m_vertexArrayData; ///< List of default vertex arrays specified by user. Indices are values from RendererVertexAttribute enum.

    BufferObjectStreamSharedPtr m_vertexArrayDataStream;        ///< Buffer object stream for uploading vertex array data to VBO.

    void*                       m_vertexArrayBuffer;            ///< Intermediate buffer where vertex array being copied before upload.
    unsigned int                m_vertexArrayBufferSize;        ///< Size of intermediate buffer where vertex array being copied before upload.

    BufferObjectStreamSharedPtr m_vertexArrayIndicesStream;     ///< Buffer object stream for uploading index data for vertex arrays to IBO.
    void*                       m_vertexArrayIndicesBuffer;     ///< Intermediate buffer where vertex array being copied before upload.
    unsigned int                m_vertexArrayIndicesBufferSize; ///< Size of intermediate buffer where vertex array being copied before upload.
    unsigned int                m_lastVertexArrayIndexCount;    ///< Index count from last rendering of vertex arrays.
    unsigned int                m_lastVertexArrayIndicesOffset; ///< Offset to index data in IBO from last rendering of vertex arrays.
#endif

    int                         m_glVersion;

    chrono::milliseconds        m_globalTime;

}; // class Renderer

KANZI_API unsigned int getAttributeDimension(VertexAttribute::Semantic attribute);

} // namespace kanzi

#endif // KZ_RENDERER_HPP
