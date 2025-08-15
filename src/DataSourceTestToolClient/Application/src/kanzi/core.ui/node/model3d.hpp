// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MODEL3D_HPP
#define KZ_MODEL3D_HPP

#include "node3d.hpp"
#include "resource_reference.hpp"

#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core.ui/graphics3d/material_renderer.hpp>
#include <kanzi/core.ui/graphics3d/mesh.hpp>
#include <kanzi/core.ui/graphics3d/morph.hpp>
#include <kanzi/core.ui/graphics3d/morph_runtime.hpp>
#include <kanzi/core.ui/graphics2d/texture.hpp>

namespace kanzi
{

// Forward declarations.
class Material;
class Model3D;

/// Mesh node shared pointer.
typedef shared_ptr<Model3D> Model3DSharedPtr;

/// Renders a mesh in 3D space.
///
/// Mesh node 
class KANZI_API Model3D : public Node3D
{
public:

    /// \name Properties
    /// \{

    /// Mesh property.
    /// The default value is ResourceSharedPtr().
    /// \see setMesh(), getMesh()
    static PropertyType<ResourceSharedPtr> MeshProperty;

    /// Material property.
    /// The default value is ResourceSharedPtr().
    /// \see setMaterial(), getMaterial()
    static PropertyType<ResourceSharedPtr> MaterialProperty;
    /// Gets the value of #MaterialProperty.
    /// \see setMaterial()
    ResourceSharedPtr getMaterial() const
    {
        return getProperty(MaterialProperty);
    }
    /// Sets the value of #MaterialProperty.
    /// \see getMaterial()
    void setMaterial(ResourceSharedPtr value)
    {
        setProperty(MaterialProperty, value);
    }

    /// DrawnAsBoundingBox property.
    /// The default value is false.
    /// \see setDrawnAsBoundingBox(), isDrawnAsBoundingBox()
    static PropertyType<bool> DrawnAsBoundingBoxProperty;
    /// Gets the value of #DrawnAsBoundingBoxProperty.
    /// \see setDrawnAsBoundingBox()
    bool isDrawnAsBoundingBox() const
    {
        return getProperty(DrawnAsBoundingBoxProperty);
    }
    /// Sets the value of #DrawnAsBoundingBoxProperty.
    /// \see isDrawnAsBoundingBox()
    void setDrawnAsBoundingBox(bool value)
    {
        setProperty(DrawnAsBoundingBoxProperty, value);
    }

    /// MeshMorphTargetWeight property.
    /// The default value is 1.0f.
    /// \see setMeshMorphTargetWeight(), getMeshMorphTargetWeight()
    static PropertyType<float> MeshMorphTargetWeightProperty;

    /// \}

    /// Gets the value of #MeshProperty.
    /// \see setMesh()
    MeshSharedPtr getMesh() const { return dynamic_pointer_cast<Mesh>(getProperty(MeshProperty)); }
    /// Sets the value of #MeshProperty.
    /// \see getMesh()
    void setMesh(ResourceSharedPtr value) { setProperty(MeshProperty, value); }
    
    /// Creates a mesh node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the mesh node.
    static Model3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Model3D, Node3D, "Kanzi.Model3D")
        KZ_METACLASS_PROPERTY_TYPE(MeshProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
        KZ_METACLASS_PROPERTY_TYPE(DrawnAsBoundingBoxProperty)
        KZ_METACLASS_PROPERTY_TYPE(MeshMorphTargetWeightProperty)
    KZ_METACLASS_END()

    /// Creates a mesh node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the mesh node.
    /// \param mesh Mesh resource that the node 
    static Model3DSharedPtr create(Domain* domain, string_view name, const MeshSharedPtr& mesh);

    static Model3DSharedPtr createCube(Domain* domain, string_view name, float size, ColorRGBA color);
    static Model3DSharedPtr createBox(Domain* domain, string_view name, Vector3 size, ColorRGBA color);
    static Model3DSharedPtr createSphere(Domain* domain, string_view name, float radius, unsigned int segments, unsigned int rows, ColorRGBA color);

    TextureSharedPtr getTexture(AbstractPropertyType propertyType) const;

    /// Gets property target object for morph weight for target at given index
    Object* getMorphTargetWeightPropertyObject(size_t index);

    /// Update bounding box for the model's mesh.
    /// \return Root transform of the armature root if mesh has skinning, empty optional otherwise.
    optional<Matrix4x4> updateBoundingBox(const KzcDynamicArray& transformedObjectList);

    /// Compare shaders of two models, used for sorting.
    /// \param first Left-hand-side operand.
    /// \param second Right-hand-side operand.
    static int compareShaders(const Model3D& first, const Model3D& second);

    /// Gets morph runtime.
    MorphRuntimeSharedPtr getMorphRuntime()
    {
        return m_morphWeights;
    }

    /// Access material renderer for given mesh cluster index.
    /// If index is out of range for material renderers, 0 will be returned.
    /// \param idx Mesh cluster index.
    /// \return Pointer to material renderer.
    MaterialRenderer* getMaterialRenderer(size_t idx)
    {
        if (idx >= m_materialRenderers.size())
        {
            return 0;
        }        
        return m_materialRenderers[idx].get();
    }

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Model3D(Domain* domain, string_view name);

    /// Node::onAttached() implementation.
    virtual void onAttached() KZ_OVERRIDE;

    /// Node::onAttached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Node::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Node3D::renderOverride() implementation.
    virtual void renderOverride(RenderPass& renderPass, const KzuTransformedObjectNode& transformedNode) KZ_OVERRIDE;

    /// Node3D::getBoundingVolume() implementation.
    virtual const KzuBoundingVolume* getBoundingVolume() const KZ_OVERRIDE;

    void acquireTextures();
    void acquireTextures(Material& material);
    void acquireTextures(Mesh& mesh);

    /// Re-initializes mesh-related data.
    /// Kanzi internally uses this function to reinitialize data related to a mesh when #MeshProperty changes.
    void meshChangeCallback();
    /// Re-initializes morph-related data.
    /// Kanzi internally uses this function to reinitialize data related to a morph when #MorphProperty changes.
    void morphChangeCallback();
    /// Kanzi internally uses this function to resize the array of material renderers to match the current number of mesh clusters when a mesh or morph changes.
    void reattachMaterialRenderers();

    friend class Morph;
    void applyMorph(Renderer* coreRenderer);

    /// Sets morph weight for target at specified index
    /// \param index Index of morph weight.
    /// \param weight Morph weight.
    void setMorphWeight(size_t index, float weight)
    {
        (*m_morphWeights)[index] = weight;
    }

    /// Bind mesh for rendering.
    /// \param cluster Cluster to bind.
    /// \param shader Shader to use.
    void bindMesh(unsigned int cluster, ShaderProgramSharedPtr shader);
    
private:
    typedef shared_ptr<ResourceReference<Texture> > TextureResourceReference;
    typedef map<AbstractPropertyType, TextureResourceReference> TextureResourceReferenceContainer;

    /// Cached textures for applying materials.
    TextureResourceReferenceContainer m_cachedTextures;

    /// Array of morph instance weights.
    vector<shared_ptr<Object> > m_morphWeightTargets;

    /// Material from #MaterialProperty.
    MaterialSharedPtr m_cachedMaterial;

    /// Mesh from #MeshProperty.
    MeshSharedPtr m_cachedMesh;
    /// Morph from #MorphProperty.
    MorphSharedPtr m_cachedMorph;

    /// Morph weights.
    MorphRuntimeSharedPtr m_morphWeights;

    /// Renderers for the model geometry.
    /// One per mesh cluster.
    vector<MaterialRendererPtr> m_materialRenderers;

    /// Overridden material renderer, only used if override has been used.
    /// Stored so material renderer does not need to be recreated.
    MaterialRendererPtr m_overrideMaterialRenderer;
};

}

#endif // KZ_MODEL3D_HPP
#endif  // KANZI_FEATURE_3D