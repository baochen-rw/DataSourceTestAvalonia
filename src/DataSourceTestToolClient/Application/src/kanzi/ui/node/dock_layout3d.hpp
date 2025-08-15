// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_DOCK_LAYOUT_H
#define KZU_UI_DOCK_LAYOUT_H

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/dock_layout.hpp>


namespace kanzi
{

// Forward declarations.
class DockLayout3D;

/// DockLayout shared pointer.
typedef shared_ptr<DockLayout3D> DockLayout3DSharedPtr;


/// Use the Dock Layout 3D node to place nodes relative to each other along the sides of a Dock Layout 3D node. 
/// To set the side along which you want to place a node in a Dock Layout 3D node, use the 
/// DockLayoutConcept::SideProperty property.
///
/// A Dock Layout 3D node arranges its items in a subtractive way: after positioning the first node, the Dock Layout
/// 3D node uses the remaining space to position the next node, and so on. When arranging its child nodes, a Dock 
/// Layout 3D node uses its entire size.
/// \see DockLayout2D
class KANZI_UI_API DockLayout3D : public DockLayoutConceptImpl<Node3D, DockLayout3D>
{
public:

    typedef DockLayoutConceptImpl<Node3D, DockLayout3D> ConceptClass;

    /// Creates a dock layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the dock layout.
    static DockLayout3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(DockLayout3D, ConceptClass, "Kanzi.DockLayout3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit DockLayout3D(Domain* domain, string_view name);

    /// KzuUiComponent::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
    /// KzuUiComponent::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;
};

}

#endif

#endif
