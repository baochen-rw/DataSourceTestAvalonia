// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DRAW_OBJECTS_WITH_MATERIAL_RENDER_PASS_HPP
#define KZ_DRAW_OBJECTS_WITH_MATERIAL_RENDER_PASS_HPP

#include <kanzi/core.ui/graphics3d/draw_objects_render_pass.hpp>
#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core.ui/graphics3d/material_renderer.hpp>

namespace kanzi
{

// Forward declaration.
class DrawObjectsWithMaterialRenderPass;

/// DrawObjectsWithMaterialRenderPass shared pointer type.
typedef shared_ptr<DrawObjectsWithMaterialRenderPass> DrawObjectsWithMaterialRenderPassSharedPtr;

/// Use the Draw Objects With %Material Render Pass to render nodes provided by an object source using a material.
///
/// The only difference between the Draw Objects With %Material Render Pass and Draw Objects Render Pass is
/// that the Draw Objects With %Material Render Pass renders content using a material you can set in the
/// #MaterialProperty.
///
/// For example, use the Draw Objects With %Material Render Pass to render all nodes in a scene using a shadow
/// map shader and render their distances from the light to a depth texture. You can then use this depth texture
/// to render shadows by using it as a property in a material.
class KANZI_API DrawObjectsWithMaterialRenderPass : public DrawObjectsRenderPass
{
public:
    /// \name Properties
    /// \{

    /// Use the #MaterialProperty to set the material that you want to use to render nodes.
    /// If you do not set the #MaterialProperty, or it points to an empty resource, Kanzi renders nodes using
    /// the materials set in each node or mesh.
    static PropertyType<ResourceSharedPtr> MaterialProperty;
    /// Gets the value of #MaterialProperty.
    /// \see setMaterial()
    MaterialSharedPtr getMaterial() const
    {
        return dynamic_pointer_cast<Material>(getProperty(MaterialProperty));
    }
    /// Sets the value of #MaterialProperty.
    /// \see getMaterial()
    void setMaterial(MaterialSharedPtr value)
    {
        setProperty(MaterialProperty, value);
    }

    /// \}

    KZ_METACLASS_BEGIN(DrawObjectsWithMaterialRenderPass, DrawObjectsRenderPass, "Kanzi.DrawObjectsWithMaterialRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Destructor.
    virtual ~DrawObjectsWithMaterialRenderPass();

    /// Create a Draw Objects With %Material Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Draw Objects With %Material Render Pass.
    /// \return The created Draw Objects With %Material Render Pass.
    static DrawObjectsWithMaterialRenderPassSharedPtr create(Domain* domain, string_view name);

    /// Gets the material renderer that a node uses.
    /// \param node The node for which you want to get the renderer.
    /// \return The material renderer that the node uses or 0 if the Draw Objects With %Material Render Pass has no corresponding material renderer for the node.
    MaterialRenderer* getMaterialRenderer(Node3DSharedPtr node)
    {
        MaterialRendererMap::iterator it = m_materialRenderers.find(node);
        if (it != m_materialRenderers.end())
        {
            return (*it).second.getMaterialRenderer();
        }
        return 0;
    }

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the Draw Objects With %Material Render Pass.
    explicit DrawObjectsWithMaterialRenderPass(Domain* domain, string_view name);

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

    /// RenderPass::renderMeshOverride() implementation.
    virtual void renderMeshOverride(Node3D& node, Morph* morph, Mesh& mesh, unsigned int clusterIndex, MaterialRenderer& materialRenderer) KZ_OVERRIDE;

    /// Clear material renderers.
    /// Called implicitly when material property changes.
    void clearMaterialRenderers();

protected:

    /// Container for material renderers.
    class MaterialRendererContainer
    {
    public:

        /// Empty constructor.
        explicit MaterialRendererContainer():
            m_counter(0u)
        {
        }

        /// Constructor.
        /// \param material The material to attach.
        /// \param node 3D node to which to attach the material.
        /// \param counter Current counter.
        explicit MaterialRendererContainer(MaterialSharedPtr material, Node3D& node, unsigned int counter);

        /// Move constructor.
        /// \param other Source object.
        MaterialRendererContainer(KZ_RV_REF(MaterialRendererContainer) other) :
            m_materialRenderer(kanzi::move(other.m_materialRenderer)),
            m_counter(other.m_counter)
        {
        }

        /// Gets the material renderer.
        /// Used internally to access the material renderer corresponding to a node.
        /// \return Pointer to material renderer.
        MaterialRenderer* getMaterialRenderer()
        {
            return m_materialRenderer.get();
        }

        /// Test if the counter matches given value.
        /// Used internally to determine if the material renderer is still required.
        /// \param counter The counter against which to check.
        /// \return True when the counter matches, otherwise false.
        bool counterMatches(unsigned int counter) const
        {
            return (m_counter == counter);
        }
        /// Update the counter to match given external number.
        /// Used internally to update the counter while rendering.
        /// \param counter The new counter value.
        void updateCounter(unsigned int counter)
        {
            m_counter = counter;
        }

        /// Move operator.
        /// \param other Source object.
        MaterialRendererContainer& operator=(KZ_RV_REF(MaterialRendererContainer) other)
        {
            m_materialRenderer = kanzi::move(other.m_materialRenderer);
            m_counter = other.m_counter;
            return *this;
        }

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(MaterialRendererContainer)

        /// Material renderer connecting to a Node3D.
        MaterialRendererPtr m_materialRenderer;

        /// Counter for when this material renderer was last used.
        unsigned int m_counter;
    };

    /// Mapping for storing material renderers when rendering nodes.
    typedef map<Node3DWeakPtr, MaterialRendererContainer, owner_less<Node3DWeakPtr> > MaterialRendererMap;

    /// Mapping of material renderers to rendered nodes.
    /// This map stores the material renderers so that the nodes do not have to handle the material renderers
    /// required because of the materials specified by Draw Objects With %Material Render Passes. Nodes still
    /// contain the material renderers corresponding to their own materials.
    MaterialRendererMap m_materialRenderers;

    /// Running ID for determining when material renderers become obsolete.
    unsigned int m_materialRendererCounter;

    /// %Material to be used for rendering. Updated when #MaterialProperty changes.
    MaterialSharedPtr m_material;
};

} // namespace kanzi

#endif // KZ_DRAW_OBJECTS_WITH_MATERIAL_RENDER_PASS_HPP