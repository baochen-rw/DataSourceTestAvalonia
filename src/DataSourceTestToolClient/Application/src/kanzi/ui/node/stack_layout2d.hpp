// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_STACK_LAYER_H
#define KZU_STACK_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/stack_layout.hpp>


namespace kanzi
{

class StackLayout2D;

/// Stack layout shared pointer.
typedef shared_ptr<StackLayout2D> StackLayout2DSharedPtr;


/// Stack Layout 2D arranges its items on a line along the axis you specify in the #DirectionProperty. The default value of the #DirectionProperty is x axis.
///
/// \see For a 3D stack node, see StackLayout3D.
///
/// Examples
/// ----
///
/// To create a Stack Layout 2D node:
/// \snippet test_stack_layout2d.cpp Create
///
/// To control the direction of a stack layout:
/// \snippet test_stack_layout2d.cpp Set direction
///
/// To add items to a stack layout:
/// \snippet test_stack_layout2d.cpp Create and add items
///
/// To reverse the order in which a stack layout arranges its items:
/// \snippet test_stack_layout2d.cpp Reverse order

class KANZI_UI_API StackLayout2D : public StackLayoutConceptImpl<Node2D, StackLayout2D>
{
public:

    typedef StackLayoutConceptImpl<Node2D, StackLayout2D> ConceptClass;

    /// Creates a stack layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the stack layout.
    static StackLayout2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(StackLayout2D, ConceptClass, "Kanzi.StackLayout2D")
    KZ_METACLASS_END()

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit StackLayout2D(Domain* domain, string_view name);

    /// KzuLayer::measureOverride() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;
    /// KzuLayer::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

private:

    /// Class default value for ClipChildrenProperty.
    ClassPropertyDefaultValue<bool> m_clipChildrenClassDefaultValue;

    bool m_hasUnboundedChild;
};

}

#endif
