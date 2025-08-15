// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_TRAJECTORY_LIST_BOX3D_HPP
#define KZ_TRAJECTORY_LIST_BOX3D_HPP

#include <kanzi/ui/node/trajectory_layout3d.hpp>
#include <kanzi/ui/node/scroll_view3d.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_trajectory_presenter.hpp>
#include <kanzi/ui/node/concept/list_box.hpp>
#include <kanzi/ui/node/concept/list_box/list_box_item_container_generator.hpp>


namespace kanzi
{

class TrajectoryListBox3D;

typedef shared_ptr<TrajectoryListBox3D> TrajectoryListBox3DSharedPtr;

class KANZI_UI_API TrajectoryListBox3DTraits
{
public:
    typedef ScrollView3D TScrollViewClass;
    typedef Node3D TItemClass;
    typedef ListBoxItemContainer3D TItemContainerClass;
    typedef ListBoxTrajectoryPresenter<TrajectoryListBox3D, TrajectoryLayout3D, ListBoxItemContainer3D, ScrollView3D> TPresenterClass;
    typedef ListBoxItemGenerator3D TItemGeneratorClass;
    typedef ListBoxItemContainerGenerator3D TItemContainerGeneratorClass;
};


/// Represents a node that layouts its list of 3D items on a trajectory.
///
/// The trajectory list box measures the width of its items and displays as many items
/// as fits on the trajectory. To add empty space between items, the #SpacingProperty
/// can be used, or the items can be made artificially wider.
/// If the list is looping and all items fit to the trajectory, the spacing is automatically
/// increased so that the items are distributed evenly on the trajectory.
///
/// The trajectory list box has a \em cursor that is by default in the middle of the trajectory,
/// but it can be moved with the #CursorOffsetProperty. When the user is not giving input to
/// the list box and the list box scrolling has slowed down, the list box selects the nearest item and
/// snaps it to the cursor.
///
/// To handle input, internally the list box uses ScrollView3D. In order for the input to work, the list box
/// must be placed in front of the camera in such orientation that the scroll plane is perpendicular to the
/// camera view ray. In addition, the list box size must be specified as the scroll view uses that area to collect
/// input. To configure the scroll view, the scroll view properties set to the list box are forwarded to the scroll view.
///
/// \see For general documentation about list boxes, see ListBoxConceptImpl.
///
/// Examples
/// ----
///
/// To create a Trajectory List Box 3D:
/// \snippet test_trajectory_list_box3d.cpp example
///
/// To set the trajectory you want the list box to use:
/// \snippet test_trajectory_list_box3d.cpp trajectory example
///
/// To add items to the list box:
/// \snippet test_trajectory_list_box3d.cpp items example
///
/// To make the list box loop:
/// \snippet test_trajectory_list_box3d.cpp looping example
///
/// To set selection behavior:
/// \snippet test_trajectory_list_box3d.cpp selection example
class KANZI_UI_API TrajectoryListBox3D : public ListBoxConceptImpl<Node3D, TrajectoryListBox3D, TrajectoryListBox3DTraits>
{
    typedef ListBoxConceptImpl<Node3D, TrajectoryListBox3D, TrajectoryListBox3DTraits> ConceptClass;

public:

    /// Creates a grid listbox node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the node.
    static TrajectoryListBox3DSharedPtr create(Domain* domain, string_view name);

    /// \name Properties
    /// \{
#include "trajectory_list_box3d_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(TrajectoryListBox3D, ConceptClass, "Kanzi.TrajectoryListBox3D")
        KZ_METACLASS_PROPERTY_TYPE(TrajectoryProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaBeginProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaEndProperty)
        KZ_METACLASS_PROPERTY_TYPE(AlignToTangentProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpacingProperty)
        KZ_METACLASS_PROPERTY_TYPE(CursorOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollAxisProperty)
        KZ_METACLASS_PROPERTY_TYPE(RecognitionThresholdProperty)
        KZ_METACLASS_PROPERTY_TYPE(MinimumNumberOfTouchesProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaximumNumberOfTouchesProperty)
        KZ_METACLASS_PROPERTY_TYPE(SensitivityProperty)
        KZ_METACLASS_PROPERTY_TYPE(SlidingAccelerationCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(SlidingDragCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingAccelerationCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingDragCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingImpulseFactorProperty)
        KZ_METACLASS_PROPERTY_TYPE(SwipeDistanceProperty)
        KZ_METACLASS_PROPERTY_TYPE(LoopingProperty)
        KZ_METACLASS_PROPERTY_TYPE(AllowedScrollAxisProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    explicit TrajectoryListBox3D(Domain* domain, string_view name);

    void initialize();

    virtual void onAttached() KZ_OVERRIDE;

private:


    ScrollView3DSharedPtr m_scrollView;
    TrajectoryLayout3DSharedPtr m_layout;
    ConceptClass::PresenterSharedPtr m_presenter;
};

}

#endif
#endif
