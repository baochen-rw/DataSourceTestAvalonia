// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_FLOW_LAYER_H
#define KZU_FLOW_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/flow_layout.hpp>


namespace kanzi
{


class FlowLayout2D;

typedef shared_ptr<FlowLayout2D> FlowLayout2DSharedPtr;


/// Flow Layout 2D arranges 2D items along a line and continues to the next line when it
/// runs out of space.
///
/// You can use a flow layout to arrange the content the same way you would arrange it
/// on a page. The layout iterates through its items in the order you add them to
/// the flow layout and first arranges them along the line of the primary direction
/// you set in the #PrimaryDirectionProperty property. When a flow layout runs out of
/// available space in the primary direction it creates a new line along the secondary
/// direction you set in the #SecondaryDirectionProperty property.
///
/// If you do not set the size of a flow layout or its parent layout, the flow layout
/// arranges items on a single line in the primary direction.
///
/// For example, to arrange items according to the rules used in:
/// - Left-to-right languages, set the #PrimaryDirectionProperty property to #DirectionLeftToRight
/// and #SecondaryDirectionProperty property to #DirectionTopToBottom
/// - Right-to-left languages, set the #PrimaryDirectionProperty property to #DirectionRightToLeft
/// and #SecondaryDirectionProperty property to #DirectionTopToBottom
/// - Traditional Chinese writing layout, set the #PrimaryDirectionProperty property to
/// #DirectionTopToBottom and #SecondaryDirectionProperty property to #DirectionRightToLeft
///
/// \see For a 3D flow %layout object, see FlowLayout3D.
///
/// Examples
/// ----
///
/// To create a Flow Layout 3D object:
/// \snippet test_flow_layout2d.cpp Create
///
/// To set the width of a flow layout:
/// \snippet test_flow_layout2d.cpp Set width
///
/// To add items to a flow layout:
/// \snippet test_flow_layout2d.cpp Create and add items


class KANZI_UI_API FlowLayout2D : public FlowLayoutConceptImpl<Node2D, FlowLayout2D>
{
public:

    typedef FlowLayoutConceptImpl<Node2D, FlowLayout2D> ConceptClass;

    virtual ~FlowLayout2D() KZ_OVERRIDE;
    
    /// Creates a FlowLayout2D node.
    /// \param domain The UI domain to use.
    /// \param name The name of the node.
    /// \return The created node.
    static FlowLayout2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(FlowLayout2D, ConceptClass, "Kanzi.FlowLayout2D")
    KZ_METACLASS_END()

protected:

    explicit FlowLayout2D(Domain* domain, string_view name);

    /// Flow layer measure implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;
    /// Flow layer arrange implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

private:

    /// Layout function.
    Vector2 doLayout(const Vector2& availableSize, bool measure);

private:

    /// Class default value for ClipChildrenProperty.
    ClassPropertyDefaultValue<bool> m_clipChildrenClassDefaultValue;
};

}

#endif
