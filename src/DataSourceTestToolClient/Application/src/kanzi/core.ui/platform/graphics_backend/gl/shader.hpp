// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SHADER_HPP
#define KZ_SHADER_HPP

#include <kanzi/core.ui/graphics2d/texture.hpp>
#include <kanzi/core.ui/graphics3d/gpu_resource.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>
#include <kanzi/core.ui/node/light.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_program_handle.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_shader_handle.hpp>
#include <kanzi/core/cpp/array.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/utility.hpp>

struct KzcMemoryManager;
struct KzuStructPropertyType;
struct KzuPropertyTypeCollection;

namespace kanzi
{

// Forward declarations.
class ShaderProgram;

/// Shader program shared pointer type.
typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
/// Shader program weak pointer type.
typedef weak_ptr<ShaderProgram> ShaderProgramWeakPtr;

/// Specifies single texture uniform entry.
struct ShaderTextureUniform
{
    explicit ShaderTextureUniform():
        textureWidthUniformLocation(-1),
        textureHeightUniformLocation(-1),
        textureSizeUniformLocation(-1)
    {
    }

    /// Location of texture width uniform.
    int textureWidthUniformLocation;

    /// Location of texture height uniform.
    int textureHeightUniformLocation;

    /// Location of texture size uniform.
    int textureSizeUniformLocation;
};

/// ShaderProgram defines programmable vertex and fragment operations done by the GPU for a draw call.
///
/// For each draw call, graphics device executes a vertex shader for each vertex, rasterizes primitives,
/// and for each rasterized fragment, the fragment shader is executed.
///
/// In order to create a ShaderProgram, you must prepare ShaderProgram::CreateInfo structure and make
/// sure it is valid using CreateInfo::validate(), then create the ShaderProgram with ShaderProgram::create().
/// If ShaderProgram creation parameters are not valid, ShaderProgram::create() will throw an exception,
/// which can stop program execution.
/// \see ShaderProgram::CreateInfo
/// \see ShaderProgram::CreateInfoShaderSources
/// \see ShaderProgram::CreateInfoShaderBinary
/// \see ShaderProgram::CreateInfoProgramBinary
///
/// ShaderProgram consist of vertex shader, fragment shader, specification of vertex attributes
/// consumed by the vertex shader, and specification of property types that are used to control uniforms,
///
/// Shader programs consume per vertex attribute data, and per draw call values known as uniforms.
///
/// Vertex attribute data is typically sourced from Meshes.
/// Kanzi Shader lists a number of shader vertex attributes. Shader vertex attributes have name, semantic
/// and semantic type. When Kanzi prepares a draw call, a mesh is typically used as source for attribute data
/// that is consumed by the shader program. Each mesh has a number of mesh vertex attributes; these are
/// mapped to shader vertex attributes based on attribute semantic and semantic index.
///
/// Uniforms are typically sourced from properties, for example Material properties, or from engine.
/// Engine uniforms are for example final transform for the current Model3D node being drawn, camera
/// transformation, or positions and colors of lights in the scene. Engine uniforms are also called
/// "fixed uniforms" in Kanzi.
///
/// Values of uniforms can be transformed by Kanzi before they are sent to shader program.
/// Currently only color uniforms have transformations available. With linear to sRGB
/// transform, a linear color is convertex to sRGB when it is sent to uniform. With sRGB
/// to linear transform, a sRGB color value is transformed to linear when it is sent to
/// uniform.
class KANZI_API ShaderProgram : public GPUResource
{
public:
    KZ_ABSTRACT_METACLASS_BEGIN(ShaderProgram, Object, "Kanzi.ShaderProgram")
    KZ_METACLASS_END()

    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

    // "Fixed attributes" are used with Renderer::setVertexArrayData().
    typedef array<int, VertexAttribute::SemanticCount> FixedAttributeArray;
    typedef FixedAttributeArray::iterator FixedAttributeArrayIterator;
    typedef FixedAttributeArray::const_iterator FixedAttributeArrayConstIterator;

    /// Fixed uniform locations of the shader program.
    enum FixedUniform
    {
        /// Projection * camera * world matrix
        FixedUniformProjectionCameraWorldMatrix = 0,

        /// World matrix
        FixedUniformWorldMatrix,

        /// Projection matrix
        FixedUniformProjectionMatrix,

        /// Camera matrix
        FixedUniformCameraMatrix,

        /// Camera position
        FixedUniformCameraPosition,

        /// Viewport area
        FixedUniformViewport,

        /// Vec2 containing current window size.
        FixedUniformWindowSize,

        /// Normal matrix
        FixedUniformNormalMatrix,

        /// Camera * normal matrix (screenspace normal)
        FixedUniformCameraNormalMatrix,

        /// Camera * world matrix
        FixedUniformCameraWorldMatrix,

        /// Vec2 containing near and far plane
        FixedUniformNearFarPlane,

        /// Debug timer
        FixedUniformTime,

        /// Morph weights
        FixedUniformMorphWeights,

        /// Bone matrices
        FixedUniformMatrixPalette,
        FixedUniformDirectionalLightColor,
        FixedUniformPointLightColor,
        FixedUniformSpotLightColor,
        FixedUniformPointLightPosition,
        FixedUniformSpotLightPosition,
        FixedUniformDirectionalLightDirection,
        FixedUniformSpotLightDirection,
        FixedUniformPointLightRadius,
        FixedUniformPointLightAttenuation,
        FixedUniformSpotLightAttenuation,
        FixedUniformSpotLightCutoffAngle,
        FixedUniformSpotLightConeParameters,
        FixedUniformSpotLightExponent,

        /// Number of fixed uniforms.
        FixedUniformCount,
        FixedUniformInvalid
    };

    /// How value for uniform should be transformed when setting uniform value
    enum UniformTransformation
    {
        /// No transformation
        UniformTransformationPassThrough = 0,

        /// Convert cfrom sRGB to linear
        UniformTransformationSRgbToLinear,

        /// Convert from linear to sRGB
        UniformTransformationLinearToSRgb,

        /// Fixed uniform is not present
        UniformTransformationNotPresent,

        /// Number of uniform transformations
        UniformTransformationCount
    };

    enum UniformSourceType
    {
        /// User is responsible for setting the uniform value
        UniformSourceTypeManual = 0,

        /// The value is taken from the property looked up by name
        UniformSourceTypePropertyType,

        /// The value is a fixed uniform that is looked up by name
        UniformSourceTypeFixedUniformByUniformName
    };

    struct UniformProperty
    {
        explicit UniformProperty() :
            m_property(0),
            m_transformation(UniformTransformationPassThrough)
        {
        }

        explicit UniformProperty(AbstractPropertyType property, UniformTransformation transformation) :
            m_property(property),
            m_transformation(transformation)
        {
        }

        AbstractPropertyType m_property;
        UniformTransformation m_transformation;
    };

    typedef vector<UniformProperty> UniformContainer;
    typedef UniformContainer::const_iterator UniformContainerConstIterator;
    typedef vector<int> UniformLocationContainer;

    struct CreateInfo;
    struct CreateInfoShaderSources;
    struct CreateInfoShaderBinary;
    struct CreateInfoProgramBinary;

    explicit ShaderProgram(Domain* domain, const CreateInfo& createInfo, string_view name);

    static ShaderProgramSharedPtr create(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Get shader blending control.
    /// \see setBlendingControlEnabled()
    /// \return Shader blending control. If true, applying materials using this shader will set renderer blend mode.
    bool getBlendingControl() const
    {
        return m_blendingControl;
    }

    /// Gets property type from shader program by name. Returns 0 if not found.
    AbstractPropertyType getPropertyTypeByName(string_view propertyTypeName) const;

    UniformContainer::const_iterator beginPropertyTypes() const
    {
        return m_uniforms.begin();
    }
    UniformContainer::const_iterator endPropertyTypes() const
    {
        return m_uniforms.end();
    }

    /// Get shader program handle.
    /// \return Program handle.
    unsigned int getProgramHandle() const;

    const ShaderAttributeCollection& getVertexFormat() const;

    /// Binds the shader program for rendering.
    void bind() const;

    /// Return true if shader program has samplers that have no corresponding texture property.
    bool hasSamplersWithoutProperties() const;

    /// Returns texture size uniform locations from shader program.
    ShaderTextureUniform getTextureUniformLocation(unsigned int textureUnit) const;

    /// Get uniform location in shader program with property index.
    /// \param propertyIndex Index of property in shader. Must be valid index within the uniforms.
    /// \return Uniform location in shader program.
    int getUniformLocation(unsigned int propertyIndex);

    /// Get uniform location in the shader program by name.
    /// \param name Name of the uniform. Compared to the property name.
    /// \return Uniform location in shader program, or -1 if uniform was not found in the shader program.
    int getUniformLocationSlow(string_view name);

    /// Get uniform transformation for a fixed uniform.
    /// \param fixedUniform Fixed uniform to query.
    /// \return Uniform transformation for requested fixed uniform.
    UniformTransformation getFixedUniformTransformation(FixedUniform fixedUniform) const;

    void setStrictWarningLogged()
    {
        m_strictWarningLogged = true;
    }

    bool getStrictWarningLogged() const
    {
        return m_strictWarningLogged;
    }

    unsigned int getLightCount(Light::Type lightType) const
    {
        return m_lightCount[lightType];
    }

    /// For internal use. Do not use.
    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser) KZ_OVERRIDE;

    /// GpuResoucre::isDeployedOverride() implementation.
    virtual bool isDeployedOverride() const KZ_OVERRIDE;

    struct SamplerInfo
    {
        explicit SamplerInfo(int location, Texture::Type type) :
            uniformLocation(location),
            textureType(type)
        {
        }

        int uniformLocation;
        Texture::Type textureType;
    };

protected:
    /// Resource::reloadOverride() implementation.
    virtual void reloadOverride() KZ_OVERRIDE;

    /// GPUResource::invalidateOverride() implementation.
    virtual void invalidateOverride() KZ_OVERRIDE;

private:
    // ShaderProgram is not copyable
    explicit ShaderProgram(const ShaderProgram&) KZ_DELETED_FUNCTION;
    ShaderProgram& operator=(const ShaderProgram&) KZ_DELETED_FUNCTION;

    friend void swap(ShaderProgram& shader1, ShaderProgram& shader2);

    /// GL program handle. This is 0 if the shader program is invalid.
    GLProgramHandle m_programHandle;

    // This data comes directly from ShaderProgram::CreateInfo:

    /// List of property types that define this material type.
    UniformContainer m_uniforms;

    /// Blending control for shader program
    bool m_blendingControl;

    /// Fixed uniform transformations
    array<UniformTransformation, FixedUniformCount> m_fixedUniformTransformations;

    // This data is queried from driver, and swapped from DeploymentContext:

    // Indexed with property index
    vector<int> m_uniformLocations;

    /// Uniform locations for texture uniforms, one for each texture unit.
    array<ShaderTextureUniform, KANZI_RENDERER_MAX_TEXTURE_UNITS> m_textureUniformLocations;

    /// ShaderProgram vertex attributes
    ShaderAttributeCollection m_vertexFormat;

    /// Number of supported lights per light type
    array<unsigned int, Light::TypeCount> m_lightCount;

    /// Fixed engine uniform locations
    array<int, FixedUniformCount> m_fixedUniformLocations;

    /// Fixed engine attribute locations
    FixedAttributeArray m_fixedAttributeLocations;

    /// Samplers which have no properties
    vector<SamplerInfo> m_defaultTextureSamplers;

    /// Has warning about shader program been logged?
    bool m_strictWarningLogged;
};

inline void swap(ShaderProgram& shader1, ShaderProgram& shader2)
{
    using std::swap;
    swap(shader1.m_programHandle, shader2.m_programHandle);
    swap(shader1.m_uniforms, shader2.m_uniforms);
    swap(shader1.m_blendingControl, shader2.m_blendingControl);
    swap(shader1.m_uniformLocations, shader2.m_uniformLocations);
    swap(shader1.m_textureUniformLocations, shader2.m_textureUniformLocations);
    swap(shader1.m_vertexFormat, shader2.m_vertexFormat);
    swap(shader1.m_lightCount, shader2.m_lightCount);
    swap(shader1.m_fixedUniformLocations, shader2.m_fixedUniformLocations);
    swap(shader1.m_fixedUniformTransformations, shader2.m_fixedUniformTransformations);
    swap(shader1.m_fixedAttributeLocations, shader2.m_fixedAttributeLocations);
    swap(shader1.m_defaultTextureSamplers, shader2.m_defaultTextureSamplers);
    swap(shader1.m_strictWarningLogged, shader2.m_strictWarningLogged);
}

/// Gets FixedUniform from given string.
/// \param uniformName Name of fixed uniform.
/// \return FixedUniform corresponding to given name, or FixedUniformInvalid if name does not match any fixed uniform.
KANZI_API ShaderProgram::FixedUniform toFixedUniform(string_view uniformName);

} // namespace kanzi

#endif // KZ_SHADER_HPP
