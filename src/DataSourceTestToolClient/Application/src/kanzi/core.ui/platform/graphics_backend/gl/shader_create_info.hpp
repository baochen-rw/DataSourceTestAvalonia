// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SHADER_CREATE_INFO_HPP
#define KZ_SHADER_CREATE_INFO_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/shader.hpp>

struct KzcInputStream;

namespace kanzi
{

class Domain;

/// Struct which contains all the parameters that are needed for Shader creation.
/// \see Shader
struct KANZI_API ShaderProgram::CreateInfo
{
    /// Status tells if shader creation parameters can be used to create a shader.
    /// If status is not StatusValid, create info must not be passed to ShaderProgram::create().
    enum Status
    {
        /// Shader binary format is not supported.
        StatusUnsupportedFormat,

        /// Shader fails compilation.
        StatusCompileError,

        /// Shader fails linking.
        StatusLinkError,

        /// Shader has invalid vertex attribute locations.
        StatusInvalidAttributeLocation,

        /// CreateInfo is valid and can be used to create Shader.
        StatusValid
    };

    /// Constructs empty create info structure for shader program creation.
    ///
    /// Members of the structure must be filled in before the structure can be used
    /// in ShaderProgram::create().
    explicit CreateInfo();

    /// Perform validation of shader creation parameters.
    /// You can call validate() to see if shader creation parameters are valid before you pass create info to ShaderProgram::create().
    /// \param renderer Renderer to validate with.
    /// \return StatusValid if these creation parameters can be used to create a shader.
    ///         Otherwise a reason code for why this CreateInfo cannot be used to create a shader.
    Status validate(const Renderer& renderer) const;

    /// Adds a property type uniform to shader.
    /// \param propertyType Property type.
    /// \param transform Uniform transformation. See UniformTransformation.
    void addUniform(AbstractPropertyType propertyType, UniformTransformation transform = UniformTransformationPassThrough);

    /// Vertex shader source code.
    string vertexShaderSource;

    /// Fragment shader source code.
    string fragmentShaderSource;

    /// Format for program binary.
    unsigned int programBinaryFormat;

    /// Program binary data.
    string programBinaryData;

    /// Format for combined shader binary.
    unsigned int combinedShaderBinaryFormat;

    /// Combined shader binary data.
    string combinedShaderBinaryData;

    /// Format for separate shader binaries.
    unsigned int separateShaderBinaryFormat;

    /// Vertex shader binary data when using separate shader binaries.
    string separateShaderBinaryVertexData;

    /// Fragment shader binary data when using separate shader binaries.
    string separateShaderBinaryFragmentData;

    /// Uniforms.
    UniformContainer uniforms;

    /// Shader vertex attributes.
    ShaderAttributeCollection vertexFormat;

    /// Uniform transformations for fixed engine uniforms.
    array<UniformTransformation, FixedUniformCount> fixedUniformTransformations;

    /// Indicates whether ShaderProgram created from this createInfo should be able to change blending mode.
    /// When blending control is enabled, materials using a ShaderProgram can set renderer blend mode.
    /// If blending control is disabled, materials using a ShaderProgram will leave blend mode unchanged.
    bool blendingControl;
};

/// ShaderProgram creation parameters for initialized from shader source code strings.
struct KANZI_API ShaderProgram::CreateInfoShaderSources : public ShaderProgram::CreateInfo
{
    /// Construct a create info structure for shader program creation from vertex and fragment shader source code.
    /// \note After constructing the create info, you must insert used attributes to the
    ///       createInfo.vertexFormat.
    /// \param vertexShaderSourceCode Source code for vertex shader.
    /// \param fragmentShaderSourceCode Source code for fragment shader.
    explicit CreateInfoShaderSources(const char* vertexShaderSourceCode, const char* fragmentShaderSourceCode);
};

/// ShaderProgram creation parameters for initialized from vendor specific GL shader binary.
struct KANZI_API ShaderProgram::CreateInfoShaderBinary : public ShaderProgram::CreateInfo
{
    /// Construct a create info structure for shader program creation from precompiled
    /// shader binary.
    /// \note Supported shader binary formats are vendor specific. Each vendor uses their own
    ///       shader binary formats. Use Renderer::isGlShaderBinaryFormatSupported() to verify
    ///       that shaderBinaryFormat is supported.
    /// \note After constructing the create info, you must insert used attributes to createInfo.vertexFormat.
    /// \param shaderBinaryFormat GL shader binary format.
    /// \param dataSize Size of shader binary data in bytes.
    /// \param data Pointer to shader binary data.
    explicit CreateInfoShaderBinary(unsigned int shaderBinaryFormat, unsigned int dataSize, void* data);

    /// Construct a create info structure for shader program creation from precompiled shader binary data.
    /// This version takes in two data blobs, one for vertex shader and another one for fragment shader.
    /// \note Supported shader binary formats are vendor specific. Each vendor uses their own
    ///       shader binary formats. Use Renderer::isGlShaderBinaryFormatSupported() to verify
    ///       that shaderBinaryFormat is supported.
    /// \note After constructing the create info, you must insert used attributes to createInfo.vertexFormat.
    /// \param shaderBinaryFormat GL shader binary format.
    /// \param vertexShaderBinaryByteCount Size of vertex shader binary data in bytes.
    /// \param vertexShaderBinary Pointer to vertex shader binary data.
    /// \param fragmentShaderBinaryByteCount Size of fragment shader binary data in bytes.
    /// \param fragmentShaderBinary Pointer to fragment shader binary data.
    explicit CreateInfoShaderBinary(unsigned int shaderBinaryFormat, unsigned int vertexShaderBinaryByteCount, void* vertexShaderBinary,
                                    unsigned int fragmentShaderBinaryByteCount, void* fragmentShaderBinary);
};

/// ShaderProgram creation parameters for initialized from vendor specific GL program binary.
struct KANZI_API ShaderProgram::CreateInfoProgramBinary : public ShaderProgram::CreateInfo
{
    /// Construct a create info structure for shader program creation from precompiled program binary.
    /// \note After constructing the create info, you must insert used attributes to createInfo.vertexFormat.
    /// \param programBinaryFormat GL program binary format.
    /// \param dataSize Size of shader binary data in bytes.
    /// \param data Pointer to shader binary data.
    explicit CreateInfoProgramBinary(unsigned int programBinaryFormat, unsigned int dataSize, void* data);
};

inline void swap(ShaderProgram::CreateInfo& createInfo1, ShaderProgram::CreateInfo& createInfo2)
{
    using std::swap;
    swap(createInfo1.vertexShaderSource, createInfo2.vertexShaderSource);
    swap(createInfo1.fragmentShaderSource, createInfo2.fragmentShaderSource);
    swap(createInfo1.programBinaryFormat, createInfo2.programBinaryFormat);
    swap(createInfo1.programBinaryData, createInfo2.programBinaryData);
    swap(createInfo1.combinedShaderBinaryFormat, createInfo2.combinedShaderBinaryFormat);
    swap(createInfo1.combinedShaderBinaryData, createInfo2.combinedShaderBinaryData);
    swap(createInfo1.separateShaderBinaryFormat, createInfo2.separateShaderBinaryFormat);
    swap(createInfo1.separateShaderBinaryVertexData, createInfo2.separateShaderBinaryVertexData);
    swap(createInfo1.separateShaderBinaryFragmentData, createInfo2.separateShaderBinaryFragmentData);
    swap(createInfo1.uniforms, createInfo2.uniforms);
    swap(createInfo1.vertexFormat, createInfo2.vertexFormat);
    swap(createInfo1.fixedUniformTransformations, createInfo2.fixedUniformTransformations);
    swap(createInfo1.blendingControl, createInfo2.blendingControl);
}

/// Load shader program create info from KZB file.
/// \param domain Domain
/// \param kzbFile KZB file
/// \param file File
/// \param parser Memory parser
/// \return Texture create info
ShaderProgram::CreateInfo loadShaderProgramCreateInfo(Domain* domain, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser, string_view name);

/// Load shader program create info from legacy KZB file.
/// \param domain Domain
/// \param inputStream Input strea
/// \param file File
/// \return Texture create info
ShaderProgram::CreateInfo loadShaderProgramCreateInfo(Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

/// Returns human readable description for ShaderProgram CreateInfo status.
/// \param status Status
/// \return Human readable description for status.
KANZI_API FixedString getVerboseDescription(ShaderProgram::CreateInfo::Status status);


} // namespace kanzi

#endif
