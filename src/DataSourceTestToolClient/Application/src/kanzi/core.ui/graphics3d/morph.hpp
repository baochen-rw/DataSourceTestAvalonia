// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MORPH_HPP
#define KZ_MORPH_HPP

#include "gpu_resource.hpp"

namespace kanzi
{

// Forward declarations.
class Domain;
class KzbFile;
class KzbMemoryParser;
class Mesh;
class Morph;
class ReadOnlyMemoryFile;
class Renderer3D;
class ShaderProgram;
typedef shared_ptr<Mesh> MeshSharedPtr;
typedef shared_ptr<Morph const> MorphSharedConstPtr;
typedef shared_ptr<Morph> MorphSharedPtr;
typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
typedef weak_ptr<ShaderProgram> ShaderProgramWeakPtr;

extern kzsError kzuResourceManagerLoadMorph_internal(Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file, Resource** out_resource);

class KANZI_API Morph : public Resource
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(Morph, Resource, "Kanzi.Morph")
    KZ_METACLASS_END()

    static MorphSharedPtr create(Domain* domain, string_view name = "");
    static MorphSharedPtr create(Domain* domain, size_t size, string_view name = "");

    size_t getTargetCount() const;

    MeshSharedPtr getMesh(size_t index) const;

    float getDefaultWeight(size_t index) const;

    void bind(Node* baseNode, unsigned int clusterIndex, ShaderProgramSharedPtr shaderProgram);

    bool isRenderable() const;

    void add(MeshSharedPtr target, float defaultWeight);

    // Resource interface
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    static MorphSharedPtr loadFromKZB(Domain*domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

protected:
    struct MeshAttribute
    {
        Mesh* mesh;
        int meshVertexAttributeIndex;
    };

    typedef vector<MeshAttribute> AttributeMap;
    typedef map<ShaderProgramWeakPtr, AttributeMap, owner_less<ShaderProgramWeakPtr> > StringToAttributeMap;

    Morph(Domain* domain, string_view name);

    /// Acquires attribute map by shader program.
    /// The shader program key is shared so it can be detected when it has become obsolete.
    /// \param sharedShaderProgram Shader program to acquire by.
    /// \return Related attribute map.
    const AttributeMap& acquireAttributeMap(ShaderProgramSharedPtr sharedShaderProgram);

private:
    struct Entry
    {
        Entry(MeshSharedPtr mesh_, float defaultWeight_) :
            mesh(mesh_),
            defaultWeight(defaultWeight_)
        {
        }

        MeshSharedPtr mesh;
        float defaultWeight;
    };

    vector<Entry> m_targets;
    StringToAttributeMap m_attributeMaps;
};

} // namespace kanzi

#endif // KZ_MORPH_HPP

#endif // KANZI_FEATURE_3D
