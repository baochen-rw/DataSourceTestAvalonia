// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_GL_MESH_HPP
#define KZ_GL_MESH_HPP

#include <kanzi/core.ui/graphics3d/gpu_resource.hpp>

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gpu_buffer_manager.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_buffer_handle.hpp>

#include <kanzi/core/legacy/kzu_bounding_volume.hpp>
#include <kanzi/core/math/box.hpp>


struct KzcDynamicArray;

namespace kanzi
{

class Material;
class ShaderProgram;
class Node;
class ResourceManager;
class Mesh;
class ShaderProgram;

typedef shared_ptr<Material> MaterialSharedPtr;
typedef shared_ptr<Mesh> MeshSharedPtr;
typedef shared_ptr<const Mesh> MeshConstSharedPtr;
typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
typedef shared_ptr<Buffer> BufferSharedPtr;
typedef unique_ptr<Buffer> BufferUniquePtr;
typedef unordered_map<ShaderProgram*, vector<int> > ShaderProgramToAttributeMapSet;


/// Mesh stores the geometry data for rendering Model3d nodes. Each mesh has one or more clusters. Each cluster has
/// material and primitives. Primitives are typically triangles, they are stored as vertex data and index data.
///
/// You can load a mesh resource from a .kzb file or create it with the Mesh::create() function.
///
/// Once Mesh has been created with constructor, all primitive data is uploaded to GPU memory and no longer stored
/// in CPU memory in Mesh.
///
/// \see MeshCreateInfo
class KANZI_API Mesh : public GPUResource
{
public:
    struct KANZI_API CreateInfo;

    /// Definition of mesh bone, that is used for mesh skinning.
    struct KANZI_API Bone
    {
        explicit Bone(string_view path) :
            boneNode(0),
            childJoint(0),
            path(path)
        {
        }

        /// Reference to bone object node.
        Node3D* boneNode;

        /// Reference to child bone object node.
        Node3D* childJoint;

        /// Relative path to mesh node.
        string path;

        /// Inverse bind matrix for the bone, that is needed to calculate skin matrices for shader.
        Matrix4x4 inverseBindMatrix;
    };

    /// Shared pointer type for Bone.
    typedef shared_ptr<Bone> BoneSharedPtr;

    /// Skeleton is for animating mesh with bones.
    /// Bone animation uses shader based matrix palette skinning.
    struct KANZI_API Skeleton
    {

    public:

        explicit Skeleton() :
            bones(),
            bindShapeMatrix(),
            inverseRootTransform(),
            originalBoundingBox()
        {
        }

        /// Copy constructor.
        ///
        /// \param other Source skeleton.
        Skeleton(const Skeleton& other) :
            bones(other.bones),
            bindShapeMatrix(other.bindShapeMatrix),
            originalBoundingBox(other.originalBoundingBox)
        {
        }

        /// Copy operator.
        ///
        /// \param other Source skeleton.
        Skeleton& operator=(const Skeleton& other)
        {
            // This handwritten implementation is required to work around compiler limitations.
            bones = other.bones;
            bindShapeMatrix = other.bindShapeMatrix;
            originalBoundingBox = other.originalBoundingBox;
            return *this;
        }

        /// Array of bones.
        vector<BoneSharedPtr> bones;

        /// Bind shape matrix used for mesh skinning.
        Matrix4x4 bindShapeMatrix;

        /// Inverse transform for the skeleton root.
        /// Calculated during scene extract.
        Matrix4x4 inverseRootTransform;

        /// Original bounding volume of the mesh.
        Box originalBoundingBox;
    };

    /// Cluster has a material, primitive type (currently always triangles), and handle for GPU memory
    /// buffer where primitive indices are stored.
    struct KANZI_API Cluster
    {
        explicit Cluster() :
            primitiveType(GraphicsPrimitiveTypeInvalid),
            indexCount(0)
        {
        }

        Cluster(KZ_RV_REF(Cluster) other) :
            primitiveType(other.primitiveType),
            indexCount(other.indexCount),
            material(kanzi::move(other.material)),
            indexBuffer(kanzi::move(other.indexBuffer))
        {
            other.primitiveType = GraphicsPrimitiveTypeInvalid;
            other.indexCount = 0;
        }

        Cluster& operator=(KZ_RV_REF(Cluster) other)
        {
            primitiveType = other.primitiveType;
            indexCount = other.indexCount;
            material = kanzi::move(other.material);
            indexBuffer = kanzi::move(other.indexBuffer);
            other.primitiveType = GraphicsPrimitiveTypeInvalid;
            other.indexCount = 0;
            return *this;
        }

        /// Primitive type for this cluster
        GraphicsPrimitiveType primitiveType;

        /// Number of indices. Stored in a separate variable since indexData array can be freed to save memory.
        unsigned int indexCount;

        /// Vector containing the index data. May be empty.
        vector<uint16_t> indexData;

        /// Material for this cluster.
        MaterialSharedPtr material;

        /// Handle for GPU memory buffer where primitive indices are stored.
        BufferUniquePtr indexBuffer;

    private:
        KZ_MOVABLE_BUT_NOT_COPYABLE(Cluster)
    };

    KZ_ABSTRACT_METACLASS_BEGIN(Mesh, Object, "Kanzi.Mesh")
    KZ_METACLASS_END()

    /// Creates a mesh with specified mesh creation parameters.
    /// 
    /// In order to create a mesh, you will need a Mesh::CreateInfo structure that is
    /// filled with mesh creation parameters.
    ///
    /// Primitive data (vertex and index data) is always deployed to GPU memory when Mesh is created.
    ///
    /// \param domain Domain for the mesh.
    /// \param createInfo Mesh creation parameters.
    /// \param name Name for the mesh.
    ///
    /// \return Mesh shared pointer.
    static MeshSharedPtr create(Domain* domain, const CreateInfo& createInfo, string_view name);

    /// Creates a mesh with a sphere shape in a single cluster.
    ///
    /// \param radius Radius of the sphere
    /// \param segmentCount Number of segments for the shape
    /// \param rowCount Number of rows for the shape
    /// \param material Material pointer for the cluster. If set, leave the materialURL parameter empty.
    /// \param materialURL Resource address for the cluster material. If set, leave material empty.
    /// 
    /// \return Mesh shared pointer.
    static MeshSharedPtr createSphere(Domain* domain, float radius, unsigned int segmentCount, unsigned int rowCount, string_view name, MaterialSharedPtr material = MaterialSharedPtr());

    /// Creates a mesh with a box shape in a single cluster.
    ///
    /// \param width Width of the box (size along the x axis)
    /// \param height Height of the box (size along the y axis)
    /// \param depth Depth of the box (size along z axis)
    /// \param material Material pointer for the cluster. If set, leave the materialURL parameter empty.
    /// \param materialURL Resource address for the cluster material. If set, leave the material parameter empty.
    ///
    /// \return Mesh shared pointer.
    static MeshSharedPtr createBox(Domain* domain, Vector3 size, string_view name, MaterialSharedPtr material = MaterialSharedPtr());

    /// Creates a plane shape.
    ///
    /// \param width Width of the plane (size along the x axis)
    /// \param height Height of the plane (size along the y axis)
    /// \param invertU If true, the first texture coordinate is inverted
    /// \param invertV If true, the second texture coordinate is inverted
    /// \param material Material pointer for the cluster. If set, leave the materialURL parameter empty.
    /// \param materialURL Resource address for the cluster material. If set, leave the material parameter empty.
    ///
    /// \return Mesh shared pointer.
    static MeshSharedPtr createPlane(Domain* domain, float width, float height, bool invertU, bool invertV, string_view name, MaterialSharedPtr material = MaterialSharedPtr());

    /// Prepares a cluster from the mesh for rendering with the specified shader.
    /// \param clusterIndex Which cluster to render.
    /// \param shaderProgram Which ShaderProgram to render with.
    void bind(size_t clusterIndex, ShaderProgramSharedPtr shaderProgram);

    /// Returns the bounding volume of the mesh.
    /// \return Bounding volume for the mesh.
    const KzuBoundingVolume* getBoundingVolume() const;

    /// Returns the vertex count of the mesh.
    /// \return Number of vertices in mesh.
    size_t getVertexCount() const
    {
        return m_vertexCount;
    }

    /// Gets the number of the vertex attributes in the mesh.
    /// \return Number of vertex attributes in mesh.
    size_t getVertexAttributeCount() const
    {
        return m_vertexFormat.size();
    }

    /// Gets size of one vertex in bytes.
    /// \return Size of vertex in bytes.
    size_t getVertexSize() const
    {
        return m_vertexSize;
    }

    /// Gets raw vertex data.
    /// User is responsible for casting the data to proper format for reading.
    /// \return Raw vertex data or 0  if data was not preserved in RAM.
    const void* getVertexData() const
    {
        if (m_vertexData.empty())
        {
            return 0;
        }
        return m_vertexData.data();
    }

    /// Gets the number of clusters in the mesh.
    /// \return Number of clusters in the mesh.
    size_t getClusterCount() const
    {
        return m_clusters.size();
    }

    /// Gets the number of indices in a specified cluster.
    /// \param clusterIndex Which cluster to query
    /// \return Number of indices in the cluster.
    size_t getClusterIndexCount(size_t clusterIndex) const;

    /// Gets the primitive type for the cluster.
    /// \param clusterIndex Which cluster to query
    /// \return The primitive type for the cluster.
    GraphicsPrimitiveType getClusterPrimitiveType(size_t clusterIndex) const;

    /// Gets the cluster material.
    /// \param clusterIndex Which cluster to query
    /// \return The material for the cluster.
    MaterialSharedPtr getClusterMaterial(size_t clusterIndex) const;

    /// Sets the cluster material.
    /// \param clusterIndex The cluster for which to set the material
    /// \param material The material to apply to the cluster
    void setClusterMaterial(size_t clusterIndex, MaterialSharedPtr material);

    /// Gets index data for given cluster.
    /// \param clusterIndex Which cluster to query
    /// \return Raw cluster index data or 0 if data was not preserved in RAM.
    const uint16_t* getClusterIndexData(size_t clusterIndex) const;

    /// Updates bounding box of mesh with bones from given model.
    /// \param baseNode Node from which bones are located from.
    /// \param transformedObjectList List of transformed objects, from which bones are retrieved from.
    /// \return Armature root transform if mesh has skinning enable, empty optional otherwise.
    optional<Matrix4x4> updateBoundingBox(Node3D* baseNode, const KzcDynamicArray& transformedObjectList);

    /// Gets number of bones in mesh.
    /// \return number of bones in mesh.
    size_t getBoneCount() const;

    /// Gets node for bone. The node is looked up from the latest node that was
    /// attached to the mesh with attach() function.
    /// \see attach()
    /// \param boneIndex index of bone.
    /// \return Node for bone.
    Node3D* getBoneNode(size_t boneIndex) const;

    /// Gets child node for skeletal animation bone. The node is looked up from the latest node that was
    /// attached to the mesh with attach() function.
    /// \see attach()
    /// \param boneIndex index of bone.
    /// \return Node for bone.
    Node3D* getBoneChildJoint(size_t boneIndex) const;

    /// Attaches a root node for bone node lookup functions.
    /// \see getBoneNode()
    /// \see getBoneChildJoint()
    /// \param baseNode Root node for bone node lookups.
    void attach(Node* baseNode);

    /// Detaches root node, making bone node lookups no longer available.
    /// \see attach()
    void detach();

    /// Gets attribute map for given shader program. In attribute map keys to are mesh attribute indices and
    /// values are shader attribute indices.
    /// \param shaderProgram Shader program.
    /// \return Attribute map (mesh attribute index -> shader attribute index).
    const vector<int>& acquireAttributeMap(ShaderProgramSharedPtr shaderProgram);

    /// Applies bone animation, updating matrix palette transformation uniforms.
    /// \param baseNode Root node for bones.
    /// \param transformedObjectList Transformed nodes.
    void applySkeleton(Node* baseNode, const KzcDynamicArray* transformedObjectList);

    /// Gets mesh vertex attribute with given mesh attribute index.
    /// \param index Mesh vertex attribute index.
    /// \return Mesh vertex attribute.
    const MeshVertexAttribute& getVertexAttribute(int index) const;

    /// Takes one mesh vertex attribute from mesh and makes it usable with (current) shader.
    /// \param renderer Renderer.
    /// \param shaderAttributeIndex Shader attribute index. This is the target, where attribute data is directed.
    /// \param meshVertexAttributeIndex Mesh attribute index. This is the source, where attibute data is taken from.
    void bindAttribute(Renderer* renderer, unsigned int shaderAttributeIndex, int meshVertexAttributeIndex);

    /// Makes all mesh vertex attributes available with a shader program.
    /// \param shaderProgram Shader program
    /// \return Bitfield: nth bit indicates that nth shader attribute was sourced from the mesh.
    unsigned int bindAttributes(ShaderProgramSharedPtr shaderProgram);

    /// Makes mesh cluster indices available to the next draw call.
    /// \param clusterIndex Index of cluster to prepare.
    void bindIndices(size_t clusterIndex);

    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:
    /// Resource::reloadOverride() implementation.
    virtual void reloadOverride() KZ_OVERRIDE;

    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Resource::reloadFromKzbOverride() implementation.
    virtual void reloadFromKzbOverride(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser) KZ_OVERRIDE;

    /// GPUResource::invalidateOverride() implementation.
    virtual void invalidateOverride() KZ_OVERRIDE;

    /// GpuResource::isDeployed() implementation.
    virtual bool isDeployedOverride() const KZ_OVERRIDE;

    /// GpuResource::getGPUMemoryUsageOverride() implementation.
    virtual unsigned int getGPUMemoryUsageOverride() const KZ_OVERRIDE;

    explicit Mesh(Domain* domain, const CreateInfo& createInfo, string_view name);

private:
    // Mesh is not copyable
    explicit Mesh(const Mesh&) KZ_DELETED_FUNCTION;
    Mesh& operator=(const Mesh&) KZ_DELETED_FUNCTION;

    friend void swap(Mesh& mesh1, Mesh& mesh2);

    /// Array of clusters in mesh.
    vector<Cluster> m_clusters;

    /// Bounding volume for mesh.
    KzuBoundingVolume m_boundingVolume;

    /// Skeleton (skinned meshes).
    Skeleton m_skeleton;

    /// Boolean specifying if insufficient bone count has already been logged, to prevent performance drop when logging it per-frame basis.
    bool m_insufficientBoneCountLogged;

    /// Map from shader attribute location to mesh attribute index
    vector<int> m_attributeMap;

    /// Mesh vertex attributes.
    MeshAttributeCollection m_vertexFormat;

    /// Size of one vertex, that is, all attributes summed.
    size_t m_vertexSize;

    /// Vertex count for this vertex buffer.
    size_t m_vertexCount;

    /// Raw vertex data.
    vector<byte> m_vertexData;
        
    /// ShaderProgram pointer -> (shader attribute location -> mesh vertex attribute index)
    ShaderProgramToAttributeMapSet m_shaderProgramAttributeMaps;

    /// Vertex buffer.
    BufferUniquePtr m_vertexBuffer;
};

inline void swap(Mesh::Skeleton& skeleton1, Mesh::Skeleton& skeleton2)
{
    using std::swap;
    swap(skeleton1.bones, skeleton2.bones);
    swap(skeleton1.bindShapeMatrix, skeleton2.bindShapeMatrix);
    swap(skeleton1.originalBoundingBox, skeleton2.originalBoundingBox);
}

inline void swap(Mesh::Cluster& cluster1, Mesh::Cluster& cluster2)
{
    using std::swap;
    swap(cluster1.primitiveType, cluster2.primitiveType);
    swap(cluster1.indexCount, cluster2.indexCount);
    swap(cluster1.material, cluster2.material);
    swap(cluster1.indexBuffer, cluster2.indexBuffer);
}

inline void swap(Mesh& mesh1, Mesh& mesh2)
{
    using std::swap;
    swap(mesh1.m_clusters, mesh2.m_clusters);
    swap(mesh1.m_boundingVolume, mesh2.m_boundingVolume);
    swap(mesh1.m_skeleton, mesh2.m_skeleton);
    swap(mesh1.m_insufficientBoneCountLogged, mesh2.m_insufficientBoneCountLogged);
    swap(mesh1.m_attributeMap, mesh2.m_attributeMap);
    swap(mesh1.m_vertexFormat, mesh2.m_vertexFormat);
    swap(mesh1.m_vertexSize, mesh2.m_vertexSize);
    swap(mesh1.m_vertexCount, mesh2.m_vertexCount);
    swap(mesh1.m_shaderProgramAttributeMaps, mesh2.m_shaderProgramAttributeMaps);
    swap(mesh1.m_vertexBuffer, mesh2.m_vertexBuffer);
}

} // namespace kanzi

#endif // KZ_MESH_HPP

#endif // KANZI_FEATURE_3D
