// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_VIEWPORT_3D_HPP
#define KZ_VIEWPORT_3D_HPP

#include "model3d.hpp"

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/node/scene.hpp>

#include <kanzi/core.ui/node/kzu_transformed_scene.h>
#include <kanzi/core.ui/graphics2d/texture.hpp>


namespace kanzi
{

class Viewport3D;
typedef shared_ptr<Viewport3D> Viewport3DSharedPtr;


/// Use a Viewport 3D to set the size of a render target surface onto which content is projected.
/// Viewport 3D is a 3D node that can project 2D nodes.
///
/// Viewport 3D creates a plane mesh on which it renders the texture it creates from the 2D nodes
/// you want to the Viewport 3D to project. To render the texture you can use any material that
/// supports rendering of textures.
///
/// Examples
/// ----
///
/// To create a Viewport 3D node, create a prefab with 2D content, and set the Viewport 3D to render that prefab in a 3D environment:
/// \snippet test_viewport3d.cpp Using Viewport3D


class KANZI_API Viewport3D : public Node3D
{
public:

#include "viewport3d_properties.h"

    KZ_METACLASS_BEGIN(Viewport3D, Node3D, "Kanzi.Viewport3D")
        KZ_METACLASS_PROPERTY_TYPE(PrefabProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a viewport.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static Viewport3DSharedPtr create(Domain* domain, string_view name);

protected:

    explicit Viewport3D(Domain* domain, string_view name);

    /// Measure implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
    /// Arrange implementation.
    virtual void arrangeOverride(Vector3 availableSize) KZ_OVERRIDE;

    /// Called when a viewport layer becomes attached.
    virtual void onAttached() KZ_OVERRIDE;
    /// Called when a viewport layer becomes detached.
    virtual void onDetached() KZ_OVERRIDE;

    /// Property change handler.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Node3D::render() implementation.
    virtual void render(Renderer3D& renderer, const KzuTransformedObjectNode& transformedObjectNode, const Matrix4x4& worldTransformation) KZ_OVERRIDE;

    virtual NodeSharedPtr findAbstractChildOverride(string_view name) KZ_OVERRIDE;
    virtual VisitorResult visitAbstractChildOverride(const Visitor& visitor, VisitorOrder order) KZ_OVERRIDE;

private:

    void update2DNode();

    /// Model displaying the 2D scene graph.
    Model3DSharedPtr m_model;
    /// Material for rendering the 2D scene graph.
    MaterialSharedPtr m_material;
    /// Rendered root 2D node.
    Node2DSharedPtr m_node2d;
    ResourceID m_oldResourceID;
    /// Size given to 2D scene graph.
    Vector2 m_layoutSize2d;
    bool m_keepFlagSet;
    /// Texture the 2D scene graph is rendered into.
    TextureSharedPtr m_renderTarget;

    ClassPropertyDefaultValue<float> m_classValueLayoutWidth;
    ClassPropertyDefaultValue<float> m_classValueLayoutHeight;
};

}


#endif

#endif  // KANZI_FEATURE_3D