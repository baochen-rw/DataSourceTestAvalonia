// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_STACK_LAYOUT_3D_H
#define KZU_STACK_LAYOUT_3D_H

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/stack_layout.hpp>

namespace kanzi
{


// Forward declarations.
class StackLayout3D;


/// StackLayout shared pointer.
typedef shared_ptr<StackLayout3D> StackLayout3DSharedPtr;


/// Stack Layout 3D arranges its items on a line along the axis you specify in the #DirectionProperty. The default value of the #DirectionProperty is x axis.
///
/// \see For a 2D stack node, see StackLayout2D.
///
/// Examples
/// ----
///
/// To create a Stack Layout 3D node:
/// \snippet test_stack_layout3d.cpp example
///
/// To control the direction of a stack layout:
/// \snippet test_stack_layout3d.cpp direction example
///
/// To add items to a stack layout:
/// \snippet test_stack_layout3d.cpp items example
///
/// To reverse the order in which a stack layout arranges its items:
/// \snippet test_stack_layout3d.cpp reversed example

class KANZI_UI_API StackLayout3D : public StackLayoutConceptImpl<Node3D, StackLayout3D>
{
public:

    /// Stack layout concept used to implement this class.
    typedef StackLayoutConceptImpl<Node3D, StackLayout3D> ConceptClass;

    /// Creates a stack layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the stack layout.
    static StackLayout3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(StackLayout3D, ConceptClass, "Kanzi.StackLayout3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit StackLayout3D(Domain* domain, string_view name);
    
    /// KzuUiComponent::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
    /// KzuUiComponent::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;
};

}
#endif

#endif
