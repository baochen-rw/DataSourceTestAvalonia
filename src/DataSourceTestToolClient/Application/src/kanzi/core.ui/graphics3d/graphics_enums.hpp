// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_BACKEND_GRAPHICS_ENUMS_HPP
#define KZ_GL_GRAPHICS_BACKEND_GRAPHICS_ENUMS_HPP

#include <kanzi/core.ui/graphics/format.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>

/// Maximum number of supported texture units.
/// OpenGL ES 3 minimum requirements: 32 textures,
/// max 16 used in either vertex shader or fragment shader
#define KANZI_RENDERER_MAX_TEXTURE_UNITS          16

/// Null value for vertex and index buffers
#define KANZI_RENDERER_BUFFER_VALUE_NONE          0


/// Flag for rendering client vertex arrays using VBO.
#if 0
# define KANZI_RENDERER_RENDER_VERTEX_ARRAYS_VBO  1
#endif

/// Defines if uniform cache is enabled, can be disabled if CPU is bottleneck instead of GPU.
#if 1
# define KANZI_RENDERER_ENABLE_UNIFORM_CACHE      1
#endif

/// Is the GPU buffer manager in use.
#if 1
# define KANZI_GPU_BUFFER_MANAGER_ENABLED         1
#endif

namespace kanzi
{

/// Clear target options for renderer.
enum GraphicsClearTarget
{
    /// Clear target color buffer 0.
    GraphicsClearTargetColor0,

    /// Clear target color buffer 1.
    GraphicsClearTargetColor1,

    /// Clear target color buffer 2.
    GraphicsClearTargetColor2,

    /// Clear target color buffer 3.
    GraphicsClearTargetColor3,

    ///< Clear target depth.
    GraphicsClearTargetDepth,

    /// Clear target stencil.
    GraphicsClearTargetStencil,

    /// Clear target coverage buffer.
    GraphicsClearTargetCoverage
};

/// List of available cull modes.
enum GraphicsCullMode
{
    /// No culling.
    GraphicsCullModeNone,

    /// Backface culling.
    GraphicsCullModeBack,

    /// Frontface culling.
    GraphicsCullModeFront
};

/// List of active renderer scalars for fixed functionality.
enum GraphicsScalar
{
    /// Clear depth value.
    GraphicsScalarClearDepth = 0,

    /// Camera near plane distance.
    GraphicsScalarCameraNearPlane,

    /// Camera far plane distance.
    GraphicsScalarCameraFarPlane,

    /// Maximum amount of scalars.
    GraphicsScalarCount
};

/// Renderer stencil modes.
// NOTE: Values must match binary_format.xml "Stencil function"
enum GraphicsCompareFunction
{
    /// Always fails.
    GraphicsCompareFunctionNever = 0,

    /// Always passes.
    GraphicsCompareFunctionAlways = 1,

    /// (Ref & mask) < (stencil & mask).
    GraphicsCompareFunctionLess = 2,

    /// (Ref & mask) <= (stencil & mask).
    GraphicsCompareFunctionLessOrEqual = 3,

    /// (Ref & mask) > (stencil & mask).
    GraphicsCompareFunctionGreater = 4,

    /// (Ref & mask) >= (stencil & mask).
    GraphicsCompareFunctionGreaterOrEqual = 5,

    /// (Ref & mask) = (stencil & mask).
    GraphicsCompareFunctionEqual = 6,

    /// (Ref & mask) != (stencil & mask).
    GraphicsCompareFunctionNotEqual = 7,

    /// Compare/test is disabled.
    GraphicsCompareFunctionDisabled = 8,
};

/// Renderer stencil operations.
// NOTE: Values must match binary_format.xml "Stencil operation"
enum GraphicsStencilOperation
{
    /// Keeps the current stencil buffer value.
    GraphicsStencilOperationKeep = 0,

    /// Sets stencil buffer value to zero.
    GraphicsStencilOperationZero = 1,

    /// Set stencil buffer value to reference value, specified by StencilFunction.
    GraphicsStencilOperationReplace = 2,

    /// Increases current stencil buffer value.
    GraphicsStencilOperationIncrement = 3,

    /// Increases stencil buffer value, wraps to zero when reaching maximum.
    GraphicsStencilOperationIncrementWrap = 4,

    /// Decreases current stencil buffer value.
    GraphicsStencilOperationDecrement = 5,

    /// Decreases stencil buffer value, wraps to maximum - 1 when below 0.
    GraphicsStencilOperationDecrementWrap = 6,

    /// Inverts current stencil buffer value.
    GraphicsStencilOperationInvert = 7
};


/// List of color write modes.
enum GraphicsColorWriteMode
{
    /// No color write.
    GraphicsColorWriteModeNone = 0,

    /// Color write for RGB channels.
    GraphicsColorWriteModeRGB = 1,

    /// Color write for RGBA channels.
    GraphicsColorWriteModeRGBA = 2,

    /// Color write for red channel.
    GraphicsColorWriteModeR = 3,

    /// Color write for green channel.
    GraphicsColorWriteModeG = 4,

    /// Color write for blue channel.
    GraphicsColorWriteModeB = 5,

    /// Color write for cyan (green+blue).
    GraphicsColorWriteModeGB = 6,

    /// Color write for alpha channel.
    GraphicsColorWriteModeA = 7
};

/// List of renderer blend modes.
enum GraphicsBlendMode
{
    /// Opaque blend mode.
    GraphicsBlendModeOpaque,

    /// Regular alpha blend.
    GraphicsBlendModeAlpha,

    /// Additive blend mode.
    GraphicsBlendModeAdditive,

    /// Alpha blend of target, but source color has already been processed.
    GraphicsBlendModePremultipliedAlpha,

    /// Takes regular alpha input, but produces premultiplied output.
    GraphicsBlendModeMixedAlpha
};


/// Enumeration for index buffer primitive type.
enum GraphicsPrimitiveType
{
    /// Invalid primitive type.
    GraphicsPrimitiveTypeInvalid,

    /// Point primitive type.
    GraphicsPrimitiveTypePoints,

    /// Line primitive type.
    GraphicsPrimitiveTypeLines,

    /// Line loop primitive type.
    GraphicsPrimitiveTypeLineLoop,

    /// Line strip primitive type.
    GraphicsPrimitiveTypeLineStrip,

    /// Triangle primitive type.
    GraphicsPrimitiveTypeTriangles,

    /// Triangle strip primitive type.
    GraphicsPrimitiveTypeTriangleStrip,

    /// Triangle fan primitive type.
    GraphicsPrimitiveTypeTriangleFan
};

enum GraphicsFillMode
{
    /// Solid fill mode.
    GraphicsFillModeSolid = 0,

    /// Wireframe fill mode.
    GraphicsFillModeWireframe
};

/// List of shader types.
enum ShaderType
{
    /// Not a valid shader.
    ShaderTypeInvalid = 0,

    /// Vertex shader.
    ShaderTypeVertex,

    /// Fragment shader.
    ShaderTypeFragment
};

/// How GraphicsFormat is used
enum GraphicsFormatFeature
{
    /// Can be used as renderbuffer (0x1)
    GraphicsFormatFeatureRenderbuffer = (1 << 0),

    /// Can be sampled from (0x2)
    GraphicsFormatFeatureSampledImage = (1 << 1),

    /// Can be used with a sampler that uses linear filtering (0x4)
    GraphicsFormatFeatureSampledImageFilterLinear = (1 << 2),

    /// Can be used as a framebuffer color attachment and as an input attachment (0x8)
    GraphicsFormatFeatureColorAttachment = (1 << 3),

    /// Can be used as a framebuffer color attachment that supports blending and as an input attachment (0x10)
    GraphicsFormatFeatureColorAttachmentBlend = (1 << 4),

    /// Can be used as a framebuffer depth/stencil attachment and as an input attachment (0x20)
    GraphicsFormatFeatureDepthStencilAttachment = (1 << 5),

    /// Can be used as source image for blit operation (0x40)
    GraphicsFormatFeatureBlitSource = (1 << 6),

    /// Can be used as destination image for blit operation (0x80)
    GraphicsFormatFeatureBlitDestination = (1 << 7),

    // Buffer features bits
    GraphicsFormatFeatureVertexBuffer = (1 << 8),
    GraphicsFormatFeatureUniformTexelBuffer = (1 << 9),
    GraphicsFormatFeatureStorageTexelBuffer = (1 << 10),
    GraphicsFormatFeatureStorageTexelBufferAtomic = (1 << 11),

    /// Can be used as storage image
    GraphicsFormatFeatureStorageImage = (1 << 12),

    /// can be used as storage image that supports atomic operations
    GraphicsFormatFeatureStorageImageAtomic = (1 << 13),

    /// Combined mask for renderbuffer features.
    GraphicsFormatFeatureRenderbufferMask = (GraphicsFormatFeatureRenderbuffer |
                                             GraphicsFormatFeatureColorAttachment |
                                             GraphicsFormatFeatureColorAttachmentBlend |
                                             GraphicsFormatFeatureDepthStencilAttachment |
                                             GraphicsFormatFeatureBlitSource |
                                             GraphicsFormatFeatureBlitDestination),

    /// Combined mask for texture features.
    GraphicsFormatFeatureTextureMask = (GraphicsFormatFeatureSampledImage |
                                        GraphicsFormatFeatureSampledImageFilterLinear |
                                        GraphicsFormatFeatureColorAttachment |
                                        GraphicsFormatFeatureColorAttachmentBlend |
                                        GraphicsFormatFeatureDepthStencilAttachment |
                                        GraphicsFormatFeatureBlitSource |
                                        GraphicsFormatFeatureBlitDestination)
};

/// A base class for mesh and shader program vertex attributes.
///
/// Vertex attributes are used in model data (meshes) and material types (shader programs).
/// Draw calls that are sent to graphics device for execution must have, among other things,
/// both mesh and shader program attributes setup properly. VertexAttribute is a base class
/// for MeshVertexAttribute and ShaderVertexAttribute. VertexAttribute contains name,
/// semantic and semantic index. Derived classes MeshVertexAttribute and ShaderVertexAttribute
/// contain additional information that is specific to mesh / shader.
///
/// Each mesh has a number of attributes, which are repeated for every vertex.
/// For example, a mesh can have attributes such position, normal and texture coordinate.
/// Meshes provide values for each attribute for each vertex. Shaders consume some or
/// all of the attributes provided by mesh.
class VertexAttribute
{
public:
    /// Vertex attribute enumeration for engine.
    enum Semantic
    {
        /// Position.
        SemanticPosition = 0,

        /// Normal.
        SemanticNormal,

        /// Tangent.
        SemanticTangent,

        /// Texture coordinate.
        SemanticTextureCoordinate,

        /// Color.
        SemanticColor,

        /// Weight for matrix palette.
        SemanticWeight,

        /// Matrix palette.
        SemanticMatrixPalette,

        /// Number of fixed vertex attribute semantics.
        SemanticCount,

        /// Custom attribute semnatic.
        SemanticCustom,

        /// Invalid semantic.
        SemanticInvalid
    };

    /// Constructor.
    explicit VertexAttribute() :
        semantic(SemanticInvalid),
        semanticIndex(numeric_limits<unsigned int>::max())
    {
    }

    /// Constructor.
    /// \param name Name for vertex attribute.
    /// \param semantic Semantic for vertex attribute.
    /// \param semanticIndex Semantic index for vertex attribute.
    explicit VertexAttribute(string_view name, Semantic semantic, unsigned int semanticIndex) :
        name(name), semantic(semantic), semanticIndex(semanticIndex)
    {
    }

    friend void swap(VertexAttribute& attribute1, VertexAttribute& attribute2);

    /// Comparison operator.
    friend bool operator==(const VertexAttribute& attribute1, const VertexAttribute& attribute2)
    {
        return (attribute1.semantic == attribute2.semantic) &&
               (attribute1.semanticIndex == attribute2.semanticIndex);
    }

    /// Comparison operator.
    friend bool operator!=(const VertexAttribute& attribute1, const VertexAttribute& attribute2)
    {
        return !(attribute1 == attribute2);
    }

    /// Name of the attribute. Not currently used.
    string name;

    /// Attribute semantic.
    Semantic semantic;

    /// Semantic index.
    unsigned int semanticIndex;
};

/// MeshVertexAttribute describes how mesh vertex data is stored in memory.
/// As MeshVertexAttribute is derived from VertexAttribute, it has
/// name, semantic and semantic index. In addition to those, each mesh attribute
/// has data type, dimension, offset and stride. Together these specify how vertex
/// data is formatted in memory.
class MeshVertexAttribute : public VertexAttribute
{
public:
    /// Constructor.
    explicit MeshVertexAttribute() :
        dataType(GraphicsDataTypeNone),
        dimension(0),
        offset(0),
        stride(0)
    {
    }

    /// Constructor.
    /// \note Stride is not valid after constructor, and should be set afterwards.
    /// \param name Name of vertex attribute.
    /// \param semantic Semantic of vertex attribute.
    /// \param semanticIndex Semantic index of vertex attribute.
    /// \param dataType Datatype of vertex attribute.
    /// \param dimension Dimension of vertex attribute.
    /// \param offset Offset of vertex attribute.
    explicit MeshVertexAttribute(string_view name, Semantic semantic, unsigned int semanticIndex,
                                 GraphicsDataType dataType, unsigned int dimension, unsigned int offset) :
        VertexAttribute(name, semantic, semanticIndex),
        dataType(dataType),
        dimension(dimension),
        offset(offset),
        stride(~0u)
    {
    }

    friend void swap(MeshVertexAttribute& attribute1, MeshVertexAttribute& attribute2);

    friend bool operator==(const MeshVertexAttribute& attribute1, const MeshVertexAttribute& attribute2)
    {
        return operator==(static_cast<const VertexAttribute&>(attribute1), static_cast<const VertexAttribute&>(attribute2)) &&
               (attribute1.dataType == attribute2.dataType) &&
               (attribute1.dimension == attribute2.dimension) &&
               (attribute1.offset == attribute2.offset) &&
               (attribute1.stride == attribute2.stride);
    }

    friend bool operator!=(const MeshVertexAttribute& attribute1, const MeshVertexAttribute& attribute2)
    {
        return !(attribute1 == attribute2);
    }

    /// Attribute data type.
    GraphicsDataType dataType;

    /// Attribute dimension.
    unsigned int dimension;

    /// Attribute offset. This equals to offset of previous attribute + the size of it.
    unsigned int offset;

    /// Attribute stride.
    unsigned int stride;
};

/// ShaderVertexAttribute describes the attributes that shader program will read when executed by graphics device. 
///
/// Shader vertex attributes have assigned location. Graphics devices have a limited number of
/// locations (For example, OpenGL ES 2 has 8 attribute locations available, and OpenGL ES 3 has 16).
/// Within a shader program, each attribute must be assigned to unique location.
///
/// Shader vertex attributes also have element type, rows and columns. These indicate what kind of data
/// shader program is reading, and how many elements. The mesh vertex data may be stored in different
/// format in memory. Together with mesh vertex attribute data type and shader vertex attribute element
/// type, the graphics device sets up any necessary conversions.
class ShaderVertexAttribute : public VertexAttribute
{
public:
    /// Flags for shader attribute
    enum FlagBit
    {
        /// Flag to indicate that attribute is used in morphing.
        FlagBitMorph = 1u
    };

    /// Constructor.
    explicit ShaderVertexAttribute() :
        elementType(GraphicsElementTypeFLOAT),
        rows(0),
        columns(0),
        location(-1),
        flags(0)
    {
    }

    /// Constructor.
    /// \param name Name of vertex attribute.
    /// \param semantic Semantic of vertex attribute.
    /// \param semanticIndex Semantic index of vertex attribute.
    /// \param elementType Element type of vertex attribute. For example, vec3 attribute has float element type.
    /// \param rows Number of rows in vertex attribute. This is only used by matrices.
    /// \param columns Number of columns in vertex attribute. For example, vec3 attribute has 3 columns.
    /// \param location The location where attribute should be bound.
    /// \param flags Flags for vertex attribute.
    explicit ShaderVertexAttribute(string_view name, Semantic semantic, unsigned int semanticIndex,
                                   GraphicsElementType elementType, unsigned int rows, unsigned int columns, int location, unsigned int flags) :
        VertexAttribute(name, semantic, semanticIndex),
        elementType(elementType),
        rows(rows),
        columns(columns),
        location(location),
        flags(flags)
    {
    }

    friend void swap(ShaderVertexAttribute& attribute1, ShaderVertexAttribute& attribute2);

    friend bool operator==(const ShaderVertexAttribute& attribute1, const ShaderVertexAttribute& attribute2)
    {
        return operator==(static_cast<const VertexAttribute&>(attribute1), static_cast<const VertexAttribute&>(attribute2)) &&
               (attribute1.elementType == attribute2.elementType) &&
               (attribute1.rows == attribute2.rows) &&
               (attribute1.columns == attribute2.columns) &&
               (attribute1.location == attribute2.location);
    }

    friend bool operator!=(const ShaderVertexAttribute& attribute1, const ShaderVertexAttribute& attribute2)
    {
        return !(attribute1 == attribute2);
    }

    /// Indicates whether attribute is used for morphing.
    bool isMorph() const
    {
        return (flags & static_cast<unsigned int>(FlagBitMorph)) == static_cast<unsigned int>(FlagBitMorph);
    }

    /// Element type of vertex attribute./
    GraphicsElementType elementType;

    /// Number of rows in vertex attribute. This is only used by matrices.
    unsigned int rows;

    /// Number of columns in vertex attribute. For example, vec3 attribute has 3 columns.
    unsigned int columns;

    /// Location that is assigned for the attribute.
    int location;

    /// Flags for vertex attribute.
    unsigned int flags;
};

inline void swap(VertexAttribute& attribute1, VertexAttribute& attribute2)
{
    using std::swap;
    swap(attribute1.name, attribute2.name);
    swap(attribute1.semantic, attribute2.semantic);
    swap(attribute1.semanticIndex, attribute2.semanticIndex);
}

inline void swap(MeshVertexAttribute& attribute1, MeshVertexAttribute& attribute2)
{
    swap((VertexAttribute&)attribute1, (VertexAttribute&)attribute2);
    using std::swap;
    swap(attribute1.dataType, attribute2.dataType);
    swap(attribute1.dimension, attribute2.dimension);
    swap(attribute1.offset, attribute2.offset);
    swap(attribute1.stride, attribute2.stride);
}

inline void swap(ShaderVertexAttribute& attribute1, ShaderVertexAttribute& attribute2)
{
    swap((VertexAttribute&)attribute1, (VertexAttribute&)attribute2);
    using std::swap;
    swap(attribute1.elementType, attribute2.elementType);
    swap(attribute1.rows, attribute2.rows);
    swap(attribute1.columns, attribute2.columns);
    swap(attribute1.location, attribute2.location);
    swap(attribute1.flags, attribute2.flags);
}

typedef vector<MeshVertexAttribute> MeshAttributeCollection;
typedef MeshAttributeCollection::iterator MeshAttributeCollectionIterator;
typedef MeshAttributeCollection::const_iterator MeshAttributeCollectionConstIterator;

typedef vector<ShaderVertexAttribute> ShaderAttributeCollection;
typedef ShaderAttributeCollection::iterator ShaderAttributeCollectionIterator;
typedef ShaderAttributeCollection::const_iterator ShaderAttributeCollectionConstIterator;

/// Converts KZB vertex attribute semantic to runtime VertexAttribute::Semantic.
/// \param kzbVertexAttributeSemantic KZB vertex attribute semantic value.
/// \return Runtime VertexAttribute Semantic.
KANZI_API optional<VertexAttribute::Semantic> toVertexAttributeSemantic(unsigned int kzbVertexAttributeSemantic);

/// Returns human readable string for semantic.
/// \param semantic Vertex attribute semantic.
/// \return Human readable string for semantic.
KANZI_API FixedString toFixedString(VertexAttribute::Semantic semantic);

} // namespace kanzi

#endif // KZ_GRAPHICS_ENUMS_HPP
