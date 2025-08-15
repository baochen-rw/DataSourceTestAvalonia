// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MOVE_FOCUS_ACTION_HPP
#define KZ_MOVE_FOCUS_ACTION_HPP

#include <kanzi/core.ui/action/action.hpp>
#include <kanzi/core.ui/input/focus_manager.hpp>

namespace kanzi
{

class MoveFocusAction;
typedef shared_ptr<MoveFocusAction> MoveFocusActionSharedPtr;

/// Use the MoveFocusAction action to transfer focus from the currently focused item
/// to another focusable item in the focus navigation chain.

/// This action invokes the FocusManager::tryMoveActiveFocus() method.
///
/// Use the #DirectionProperty property to determine the direction to which you request the focus to move
/// in the focus navigation chain.
///
/// To assign navigation links for nodes use these methods:
/// FocusManager::setNextFocusNodePath, FocusManager::setPreviousFocusNodePath
/// FocusManager::setUpNavigationNodePath, FocusManager::setDownNavigationNodePath,
/// FocusManager::setLeftNavigationNodePath and FocusManager::setRightNavigationNodePath.
///
/// If no node is focused or Kanzi for some other reason cannot move focus to the
/// requested direction, the action fails silently.
class KANZI_API MoveFocusAction : public Action
{
public:
    /// Defines the direction to which focus is requested to move
    /// from the currently focused item in the focus navigation chain.
    static PropertyType<FocusManager::FocusChainDirection> DirectionProperty;

    KZ_METACLASS_BEGIN(MoveFocusAction, Action, "Kanzi.MoveFocusAction")
        KZ_METACLASS_PROPERTY_TYPE(DirectionProperty)
    KZ_METACLASS_END()

    /// Provides the editor info.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a MoveFocusAction instance.
    /// \return A shared pointer to the created action.
    static MoveFocusActionSharedPtr create(Domain* domain, string_view name);

protected:
    /// Constructor.
    explicit MoveFocusAction(Domain* domain, string_view name);

    /// Called when the MoveFocusAction action is invoked. 
    virtual void onInvoke() KZ_OVERRIDE;

    /// Clones the action.
    /// \return A clone from the action.
    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

    /// Calls Action::onDelayedInvoke and MoveFocusAction::onInvoke().
    virtual void onDelayedInvoke() KZ_OVERRIDE;
};

}

#endif
