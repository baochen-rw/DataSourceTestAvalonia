// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SET_FOCUS_ACTION_HPP
#define KZ_SET_FOCUS_ACTION_HPP

#include <kanzi/core.ui/action/action.hpp>

namespace kanzi
{

class SetFocusAction;
typedef shared_ptr<SetFocusAction> SetFocusActionSharedPtr;

/// Use the SetFocusAction action to transfer focus to any focusable item in a node tree.
///
/// This action invokes the FocusManager::trySetActiveFocus() method.
/// 
/// #SetFocusTargetItemProperty holds the information of the node to which the focus moves.
///
/// If #SetFocusTargetItemProperty does not point to a valid node or the node is not focusable, the
/// action fails silently.
class KANZI_API SetFocusAction : public Action
{
public:
    /// Holds the information of the node to which the focus is moved.
    static PropertyType<string> SetFocusTargetItemProperty;

    KZ_METACLASS_BEGIN(SetFocusAction, Action, "Kanzi.SetFocusAction")
        KZ_METACLASS_PROPERTY_TYPE(SetFocusTargetItemProperty)
    KZ_METACLASS_END()

    /// Provides editor info.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a SetFocusAction.
    /// \return A shared pointer to the created action.
    static SetFocusActionSharedPtr create(Domain* domain, string_view name);

protected:
    /// Constructor.
    explicit SetFocusAction(Domain* domain, string_view name);

    /// Called when the SetFocusAction action is invoked. Transfers the focus to the
    /// requested node.
    virtual void onInvoke() KZ_OVERRIDE;

    /// Clones the action.
    /// \return A clone from the action.
    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

    /// Calls Action::onDelayedInvoke and SetFocusAction::onInvoke().
    virtual void onDelayedInvoke() KZ_OVERRIDE;
};

}

#endif
