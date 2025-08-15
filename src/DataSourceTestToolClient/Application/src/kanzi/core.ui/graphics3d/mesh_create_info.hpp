// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MESH_CREATE_INFO_HPP
#define KZ_MESH_CREATE_INFO_HPP

#include <kanzi/core.ui/graphics3d/mesh.hpp>
#include <kanzi/core.ui/kzb/kzb_memory_parser.hpp>

namespace kanzi
{

/// Use Mesh::CreateInfo to describe and create meshes. Vertex and index listings define meshes. Indices refer
/// to vertices which define the faces of a mesh.
///
/// To define a mesh, you need:
/// - Vertex format definition. This definition describes the components that define a vertex. This includes
///   information about the vertex position, texture coordinates, normal, and tangent.
/// - List of vertices. Each vertex contains components that the format definition describes.
/// - List of indices. Indices describe polygons by referring to each vertex by index. When triangles describe
///   a polygon, three indices describe a triangle. You can use several index listings, each of which uses a
///   material.
///
/// In Kanzi a mesh can have at most 65536 vertices, a limit set by GLES2. If you need more vertices, create
/// additional meshes.
///
/// Examples
/// ========
///
/// To create a cube mesh:
/// \snippet mesh_snippets.cpp Creating a mesh manually
///
/// \see #Mesh
struct KANZI_API Mesh::CreateInfo
{
    typedef pair<AbstractPropertyType, Variant> PropertyEntry;
    typedef vector<PropertyEntry> PropertyContainer;

    /// Parameters for Mesh::Cluster creation
    struct KANZI_API Cluster
    {
        /// Default constructor
        explicit Cluster() :
            primitiveType(GraphicsPrimitiveTypeInvalid)
        {
        }

        /// Constructor
        /// \param primitiveType Primitive type for cluster.
        /// \param indexCount Number of indices for cluster.
        /// \param material Material (pointer).
        /// \param materialURL URL to material resource.
        explicit Cluster(GraphicsPrimitiveType primitiveType, unsigned int indexCount, MaterialSharedPtr material, string_view materialURL) :
            primitiveType(primitiveType),
            material(material),
            materialURL(materialURL)
        {
            indexData.resize(indexCount);
        }

        /// Primitive type for the cluster.
        GraphicsPrimitiveType primitiveType;

        /// Index data.
        vector<uint16_t> indexData;

        /// Material for this cluster.
        MaterialSharedPtr material;

        /// Temporary resource URL during loading, from which the material resource is acquired during finishing of loading.
        string materialURL;
    };

    /// Default constructor for mesh create info.
    explicit CreateInfo();

    /// Memory type for the texture. If Gpu is not included, texture will not be deployed when created.
    /// If Ram is not included, texture will not contain images after it has been deployed.
    /// Default value is #GpuOnly.
    /// \see MemoryType
    MemoryType memoryType;

    /// Clusters
    vector<Mesh::CreateInfo::Cluster> clusters;

    /// Bounding box for mesh.
    Box boundingBox;

    /// Mesh skeleton for bone animations.
    Skeleton skeleton;

    /// Mesh vertex attributes.
    MeshAttributeCollection vertexFormat;

    /// Size of one vertex in bytes. This is sum of all mesh vertex attributes sizes.
    size_t vertexSize;

    /// Number of vertices in the mesh.
    size_t vertexCount;
    
    /// Vertex buffer data.
    vector<byte> vertexData;

    /// Properties to copy to the mesh.
    /// Currently they are not used.
    PropertyContainer properties;
};

inline void swap(Mesh::CreateInfo::Cluster& cluster1, Mesh::CreateInfo::Cluster& cluster2)
{
    using std::swap;
    swap(cluster1.primitiveType, cluster2.primitiveType);
    swap(cluster1.indexData, cluster2.indexData);
    swap(cluster1.material, cluster2.material);
    swap(cluster1.materialURL, cluster2.materialURL);
}

inline void swap(Mesh::CreateInfo& createInfo1, Mesh::CreateInfo& createInfo2)
{
    using std::swap;
    swap(createInfo1.memoryType, createInfo2.memoryType);
    swap(createInfo1.clusters, createInfo2.clusters);
    swap(createInfo1.boundingBox, createInfo2.boundingBox);
    swap(createInfo1.skeleton, createInfo2.skeleton);
    swap(createInfo1.vertexFormat, createInfo2.vertexFormat);
    swap(createInfo1.vertexSize, createInfo2.vertexSize);
    swap(createInfo1.vertexCount, createInfo2.vertexCount);
    swap(createInfo1.vertexData, createInfo2.vertexData);
}

/// Writes one float attribute component to vertex data.
/// \note Only attributes with normalized or floating point data type are supported, packed data types are not supported by this function.
/// \param createInfo Mesh create info to edit.
/// \param vertexIndex Vertex to modify.
/// \param attributeIndex Vertex attribute to modify.
/// \param component Index of attribute component to modify.
/// \param v Value for vertex attribute component.
KANZI_API void writeVertexAttribute(Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, size_t component, float v);

/// Writes one float attribute value to vertex data.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to edit.
/// \param vertexIndex Vertex to modify.
/// \param attributeIndex Vertex attribute to modify.
/// \param v Value for vertex attribute.
KANZI_API void writeVertexAttribute(Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, float v);

/// Writes one Vector2 attribute value to vertex data.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to edit.
/// \param vertexIndex Vertex to modify.
/// \param attributeIndex Vertex attribute to modify.
/// \param v Value for vertex attribute.
KANZI_API void writeVertexAttribute(Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, Vector2 v);

/// Writes one Vector3 attribute value to vertex data.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to edit.
/// \param vertexIndex Vertex to modify.
/// \param attributeIndex Vertex attribute to modify.
/// \param v Value for vertex attribute.
KANZI_API void writeVertexAttribute(Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, Vector3 v);

/// Writes one Vector3 attribute value to vertex data.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to edit.
/// \param vertexIndex Vertex to modify.
/// \param attributeIndex Vertex attribute to modify.
/// \param v Value for vertex attribute.
KANZI_API void writeVertexAttribute(Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, Vector4 v);

/// Reads one attribute component of given vertex from mesh create info.
/// \note Only attributes with normalized or floating point data type are supported. Packed data types are not supported by this function.
/// \param createInfo Mesh create info to read.
/// \param vertexIndex Vertex to read.
/// \param attributeIndex Vertex attribute to read.
/// \param component Index of attribute component to read.
/// \return Value of vertex attribute of given vertex.
KANZI_API float readVertexAttributeComponent(const Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex, size_t component);

/// Reads float attribute of given vertex from mesh.
/// \note Only attributes with normalized or floating point data type are supported. Packed data types are not supported by this function.
/// \param createInfo Mesh create info to read.
/// \param vertexIndex Vertex to read.
/// \param attributeIndex Vertex attribute to read.
/// \return Value of float attribute of given vertex.
KANZI_API float readVertexAttributeFloat(const Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex);

/// Reads Vector2 attribute of given vertex from mesh.
/// \note Only attributes with normalized or floating point data type are supported. Packed data types are not supported by this function.
/// \param createInfo Mesh create info to read.
/// \param vertexIndex Vertex to read.
/// \param attributeIndex Vertex attribute to read.
/// \return Value of Vector2 attribute of given vertex.
KANZI_API Vector2 readVertexAttributeVector2(const Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex);

/// Reads Vector3 attribute of given vertex from mesh.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to read.
/// \param vertexIndex Vertex to read.
/// \param attributeIndex Vertex attribute to read.
/// \return Value of Vector3 attribute of given vertex.
KANZI_API Vector3 readVertexAttributeVector3(const Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex);

/// Reads Vector4 attribute of given vertex from mesh.
/// \note Only attributes with normalized or floating point data type are supported.
/// \param createInfo Mesh create info to read.
/// \param vertexIndex Vertex to read.
/// \param attributeIndex Vertex attribute to read.
/// \return Value of Vector4 attribute of given vertex.
KANZI_API Vector4 readVertexAttributeVector4(const Mesh::CreateInfo& createInfo, size_t vertexIndex, size_t attributeIndex);

/// Loads mesh create info from legacy KZB.
/// \param domain Domain for mesh.
/// \param inputStream Legacy KZB input stream.
/// \param file Legacy KZB file.
/// \return Mesh create info.
KANZI_API Mesh::CreateInfo loadMeshCreateInfo(Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

/// Loads mesh create info from KZB.
/// \param domain Domain for mesh.
/// \param kzbFile KZB file to load from.
/// \param file Memory file corresponding to KZB file.
/// \param parser KZB data parser.
/// \return Mesh create info.
KANZI_API Mesh::CreateInfo loadMeshCreateInfo(Domain* domain, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

/// Calculates bounding box from mesh vertex data.
/// \param createInfo Mesh create info.
/// \return Bounding box for mesh vertex attributes with Position semantic.
KANZI_API Box calculateBoundingVolume(const Mesh::CreateInfo& createInfo);

/// Sets offsets for vertex attributes in mesh create info.
/// \param createInfo Mesh create info.
KANZI_API void updateVertexAttributeOffsetsAndVertexSize(Mesh::CreateInfo& createInfo);

/// Calculates vertex format size and updates stride to all vertex attributes in mesh create info.
/// \param createInfo Mesh create info.
KANZI_API void updateVertexAttributeStrides(Mesh::CreateInfo& createInfo);

/// For each cluster in mesh create info, get material URL, if set.
/// \param createInfo Mesh create info.
/// \return Container with material URLs.
KANZI_API ResourceManager::UrlContainer collectResourceUrls(const Mesh::CreateInfo& createInfo);

/// For each cluster in mesh create info, load material from materialURL, if set.
/// \param Domain domain for mesh.
/// \param createInfo Mesh create info.
KANZI_API void acquireResources(Domain* domain, Mesh::CreateInfo& createInfo);

/// Makes mesh create info for box primitive mesh.
/// The box will have position, normal and texture coordinate attributes in one cluster, using specified material.
/// \param width Width for the box.
/// \param height Height for the box.
/// \param depth Depth for the box.
/// \param useHalfFloat If true, vertex attributes will use half float data type, otherwise vertex attributes will use float data type.
/// \param material Material (pointer).
/// \param materialURL URL for material resource.
/// \return Mesh create info for box.
KANZI_API Mesh::CreateInfo generateBox(Vector3 size, bool useHalfFloat, bool generateNormals, bool generateTangents,
                                       MaterialSharedPtr material, string_view materialURL, GPUResource::MemoryType memoryType);

/// Makes mesh create info for sphere primitive mesh.
/// The sphere will have position, normal and texture coordinate attributes in one cluster, using specified material.
/// \param radius Radius for the sphere.
/// \param segmentCount Number of segments in the sphere.
/// \param rowCount Number of rows in the sphere.
/// \param useHalfFloat If true, vertex attributes will use half float data type, otherwise vertex attributes will use float data type.
/// \param material Material (pointer).
/// \param materialURL URL for material resource.
/// \return Mesh create info for sphere.
KANZI_API Mesh::CreateInfo generateSphere(float radius, unsigned int segmentCount, unsigned int rowCount, bool useHalfFloat, bool generateNormals, bool generateTangents,
                                          MaterialSharedPtr material, string_view materialURL, GPUResource::MemoryType memoryType);

/// Makes mesh create info for plane primitive mesh.
/// The plane will have position, normal and texture coordinate attributes in one cluster, using specified material.
/// \param width Width for the plane.
/// \param height Height for the plane.
/// \param invertU If true, U texture coordinate will be inverted.
/// \param invertV If true, V texture coordinate will be inverted.
/// \param useHalfFloat If true, vertex attributes will use half float data type, otherwise vertex attributes will use float data type.
/// \param material Material (pointer).
/// \param materialURL URL for material resource.
/// \return Mesh create info for plane.
KANZI_API Mesh::CreateInfo generatePlane(float width, float height, bool invertU, bool invertV, bool useHalfFloat, bool generateNormals, bool generateTangents,
                                         MaterialSharedPtr material, string_view materialURL, GPUResource::MemoryType memoryType);

} // namespace kanzi

#endif // KZ_MESH_CREATE_INFO_HPP

#endif // KANZI_FEATURE_3D
