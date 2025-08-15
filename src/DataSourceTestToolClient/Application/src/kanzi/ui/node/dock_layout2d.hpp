// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_DOCK_LAYER_H
#define KZU_DOCK_LAYER_H

#include <kanzi/ui/node/concept/dock_layout.hpp>
#include <kanzi/core.ui/node/node2d.hpp>


namespace kanzi
{

// Forward declarations.
class DockLayout2D;

typedef shared_ptr<DockLayout2D> DockLayout2DSharedPtr;

/// Use the Dock Layout 2D node to place nodes relative to each other along the sides of a Dock Layout 2D node. 
/// To set the side along which you want to place a node in a Dock Layout 2D node, use the 
/// DockLayoutConcept::SideProperty property.
///
/// A Dock Layout 2D node arranges its items in a subtractive way: after positioning the first node, the Dock Layout
/// 2D node uses the remaining space to position the next node, and so on. When arranging its child nodes, a Dock 
/// Layout 2D node uses its entire size.
/// \see DockLayout3D
class KANZI_UI_API DockLayout2D : public DockLayoutConceptImpl<Node2D, DockLayout2D>
{
public:

    typedef DockLayoutConceptImpl<Node2D, DockLayout2D> ConceptClass;
    
    virtual ~DockLayout2D();

    static DockLayout2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(DockLayout2D, ConceptClass, "Kanzi.DockLayout2D")
    KZ_METACLASS_END()

protected:

    explicit DockLayout2D(Domain* domain, string_view name);

    /** Dock layer measure implementation. */
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;
    /** Dock layer arrange implementation. */
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

private:

    /// Class default value for ClipChildrenProperty.
    ClassPropertyDefaultValue<bool> m_clipChildrenClassDefaultValue;
};

}

#endif
