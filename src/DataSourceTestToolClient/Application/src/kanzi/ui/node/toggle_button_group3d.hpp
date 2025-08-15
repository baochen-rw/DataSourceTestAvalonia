// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TOGGLE_BUTTON_GROUP3D_HPP
#define KZ_TOGGLE_BUTTON_GROUP3D_HPP

#ifdef KANZI_FEATURE_3D

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/toggle_button_group.hpp>


namespace kanzi
{

// Forward declarations.
class ToggleButtonGroup3D;

/// ToggleButtonGroup3D shared pointer.
typedef shared_ptr<ToggleButtonGroup3D> ToggleButtonGroup3DSharedPtr;


/// Toggle Button Group 3D allows users of your application to select only one option from a set of
/// options that are mutually exclusive. Toggle buttons in a toggle button group behave like radio
/// buttons, where only one toggle button can be active at a time. Use the #ToggledButtonIndexProperty
/// property to check which toggle button in the toggle button group is selected.
///
/// You can set whether Kanzi automatically keeps track of which toggle button in the toggle button
/// group is selected, or do it manually. See setButtonGroupIndex().
///
/// \see For a 2D toggle button group component, see ToggleButtonGroup2D.
///
/// Examples
/// ---
///
/// To create a Toggle Button Group 3D node with three toggle buttons:
/// \snippet test_toggle_button_group.cpp Example 3D


class KANZI_UI_API ToggleButtonGroup3D : public ToggleButtonGroupConceptImpl<Node3D, ToggleButtonGroup3D>
{
    typedef ToggleButtonGroupConceptImpl<Node3D, ToggleButtonGroup3D> ConceptClass;

public:
    KZ_METACLASS_BEGIN(ToggleButtonGroup3D, ConceptClass, "Kanzi.ToggleButtonGroup3D")
    KZ_METACLASS_END()

    /** Creates a toggle button group. */
    static ToggleButtonGroup3DSharedPtr create(Domain* domain, string_view name);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:
    explicit ToggleButtonGroup3D(Domain* domain, string_view name);
};
}

#endif
#endif
