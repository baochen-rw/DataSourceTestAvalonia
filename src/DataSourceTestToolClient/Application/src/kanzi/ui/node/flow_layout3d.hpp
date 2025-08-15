// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_FLOW_LAYOUT_H
#define KZU_UI_FLOW_LAYOUT_H

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/flow_layout.hpp>


namespace kanzi
{

// Forward declarations.
class FlowLayout3D;

/// FlowLayout shared pointer.
typedef shared_ptr<FlowLayout3D> FlowLayout3DSharedPtr;


/// Flow Layout 3D arranges 3D items along a line and continues to the next line when it
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
/// \see For a 2D flow %layout object, see FlowLayout2D.
///
/// Examples
/// ----
///
/// To create a Flow Layout 3D object:
/// \snippet test_flow_layout3d.cpp Create
///
/// To set the width of a flow layout:
/// \snippet test_flow_layout3d.cpp Set width
///
/// To add items to a flow layout:
/// \snippet test_flow_layout3d.cpp Create and add items

class KANZI_UI_API FlowLayout3D : public FlowLayoutConceptImpl<Node3D, FlowLayout3D>
{
public:

    /// Flow layout concept used to implement this class.
    typedef FlowLayoutConceptImpl<Node3D, FlowLayout3D> ConceptClass;

    /// Creates a flow layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the flow layout.
    static FlowLayout3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(FlowLayout3D, ConceptClass, "Kanzi.FlowLayout3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit FlowLayout3D(Domain* domain, string_view name);

    /// KzuUiComponent::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
    
    /// KzuUiComponent::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;

private:
    /// Layout function.
    void doLayout(const Vector3* availableSize, Vector3* out_measuredSize = 0);
};

}
#endif
#endif
