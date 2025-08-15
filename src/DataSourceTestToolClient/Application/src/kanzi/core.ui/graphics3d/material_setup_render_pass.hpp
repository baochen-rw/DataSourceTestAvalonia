// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MATERIAL_SETUP_RENDER_PASS_HPP
#define KZ_MATERIAL_SETUP_RENDER_PASS_HPP

#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core.ui/graphics3d/render_pass.hpp>

namespace kanzi
{

// Forward declaration.
class MaterialSetupRenderPass;

/// MaterialSetupRenderPass shared pointer type.
typedef shared_ptr<MaterialSetupRenderPass> MaterialSetupRenderPassSharedPtr;

/// Use the %Material Setup Render Pass to set properties to a material for further render operations using that material.
///
/// Kanzi sets to the material all properties you add to a %Material Setup Render Pass, except the
/// MaterialSetupRenderPass.Material property.
///
/// Kanzi executes render passes in the depth-first order. This means that rendering changes you apply in a
/// %Material Setup Render Pass are effective in the sibling render passes that follow this render pass and
/// successive render passes in the render pass tree.
///
/// For example, use the %Material Setup Render Pass to set a depth texture as a property of a material. Then
/// rendering nodes using that material can use the depth texture as shadow map.
class KANZI_API MaterialSetupRenderPass : public RenderPass
{
public:
    /// \name Properties
    /// \{

    /// Use the #MaterialProperty to set the material to which you want to copy the properties.
    /// If you do not set the #MaterialProperty, or it points to an empty resource, %Material Setup Render Pass
    /// does not have any effect.
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

    KZ_METACLASS_BEGIN(MaterialSetupRenderPass, RenderPass, "Kanzi.MaterialSetupRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a %Material Setup Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the %Material Setup Render Pass.
    /// \return The created %Material Setup Render Pass.
    static MaterialSetupRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the %Material Setup Render Pass.
    explicit MaterialSetupRenderPass(Domain* domain, string_view name);

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

protected:

    /// The material to use for rendering.
    /// Kanzi updates the value when the #MaterialProperty changes.
    Material* m_material;
};

} // namespace kanzi

#endif // KZ_MATERIAL_SETUP_RENDER_PASS_HPP