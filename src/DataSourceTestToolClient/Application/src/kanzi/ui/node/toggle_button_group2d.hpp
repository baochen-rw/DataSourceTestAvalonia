// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TOGGLE_BUTTON_GROUP2D_HPP
#define KZ_TOGGLE_BUTTON_GROUP2D_HPP


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/toggle_button_group.hpp>


namespace kanzi
{

// Forward declarations.
class ToggleButtonGroup2D;

/// ToggleButtonGroup2D shared pointer.
typedef shared_ptr<ToggleButtonGroup2D> ToggleButtonGroup2DSharedPtr;


/// Toggle Button Group 2D allows users of your application to select only one option from a set of
/// options that are mutually exclusive. Toggle buttons in a toggle button group behave like radio
/// buttons, where only one toggle button can be active at a time. Use the #ToggledButtonIndexProperty
/// property to check which toggle button in the toggle button group is selected.
///
/// You can set whether Kanzi automatically keeps track of which toggle button in the toggle button
/// group is selected, or do it manually. See setButtonGroupIndex().
///
/// \see For a 3D toggle button group component, see ToggleButtonGroup3D.
///
/// Examples
/// ---
///
/// To create a Toggle Button Group 2D node with three toggle buttons:
/// \snippet test_toggle_button_group.cpp Example 2D


class KANZI_UI_API ToggleButtonGroup2D : public ToggleButtonGroupConceptImpl<Node2D, ToggleButtonGroup2D>
{
    typedef ToggleButtonGroupConceptImpl<Node2D, ToggleButtonGroup2D> ConceptClass;

public:
    KZ_METACLASS_BEGIN(ToggleButtonGroup2D, ConceptClass, "Kanzi.ToggleButtonGroup2D")
    KZ_METACLASS_END()

    /** Creates a toggle button group. */
    static ToggleButtonGroup2DSharedPtr create(Domain* domain, string_view name);

protected:

    explicit ToggleButtonGroup2D(Domain* domain, string_view name);
};

}

#endif
