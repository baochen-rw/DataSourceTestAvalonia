// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FOCUS_MANAGER_HPP
#define KZ_FOCUS_MANAGER_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>

namespace kanzi
{

/// FocusManager enables you to set and change the keyboard and logical focus
/// between attached nodes. Each domain can have only one instance of the focus
/// manager.
///
/// To set focus on a node:
/// -# Set the #FocusableProperty to \e true.
/// -# Set the #EnabledProperty to \e true.
/// -# Set the #VisibleProperty to \e true.
/// -# Attach the node to the scene graph. For example, the Screen or a Viewport2D
/// node. Kanzi can set focus to the nodes that are in the process of being attached
/// to the scene graph, but not to the nodes that are not attached.
/// -# Use one of the #trySetActiveFocus() methods to set the node as
/// active focus node. Set the appropriate focus reason code when setting the
/// focus on the node. If the reason is not known, use #UnknownReason, or call
/// the variant which has only one argument.
/// To retrieve the active focus node, use the getActiveFocus() method.
///
/// To indicate which node has active focus, Kanzi uses the Node::FocusedProperty.
/// For example, you can use this property as a controller property in a state manager
/// to change the look and behavior of the node that has active focus.
///
/// Examples
/// ----
///
/// To set active focus to a node:
/// \snippet snippets_focus_manager.cpp Set active focus
///
/// Focus messages
/// ----
/// When you call the #trySetActiveFocus() method, the focus manager sends pre-focus and
/// post-focus move messages. The pre-focus move messages, or pre-focus messages,
/// are preconditions for the focus moves. Rejecting any of these messages by the
/// message handlers stops moving the active focus. Post-focus move messages, or
/// post-focus messages, are informative messages. You can use these messages
/// to execute post-focus move actions. The pre-focus messages are #AboutToLoseFocusMessage
/// and #AboutToGainFocusMessage, and the post-focus messages are #FocusLostMessage
/// and #FocusGainedMessage.
///
/// Kanzi dispatches these messages in this order:
/// -# #AboutToGainFocusMessage. If the message is rejected by the message handlers,
/// the focus move stops and the previous active focus node is returned. Kanzi dispatches
/// this message only if you pass a valid node to #trySetActiveFocus() method.
/// -# #AboutToLoseFocusMessage. If the message is rejected by the message handlers,
/// the focus move stops and the previous active focus node is returned. Kanzi dispatches
/// this message only if there is a current active focus node.
/// -# #FocusGainedMessage. Kanzi dispatches this message to the new active focus node
/// handlers before the active focus node is effectively set, and only if the new active
/// focus node is a valid node.
/// -# #FocusLostMessage. Kanzi dispatches this message to the previous active focus node
/// handlers right after the new active focus node is set, and only if there was a previous
/// active node set.
///
/// This example shows how you can restrict a Button node to get active focus only on focus
/// chain navigation reason events and lose focus only when other focus reason is received.
/// The pre-focus message handlers are:
/// \snippet snippets_focus_manager.cpp Reject focus transfer handler
/// To move focus:
/// \snippet snippets_focus_manager.cpp Try set active focus
///
/// The impact of the #EnabledProperty and #VisibleProperty on the active focus
/// ----
/// When you set the #EnabledProperty to \e false, the Focus Manager removes the
/// active focus status of that node, but does not change the focused state of the
/// node. This means that the logical focus remains on that node until you set the
/// #EnabledProperty to \e true, or move the active focus to another node.
/// \snippet snippets_focus_manager.cpp Disable active focus
/// When you disable a node that has active focus, the FocusManager dispatches the
/// #FocusLostMessage with #DisabledFocusReason. When you re-enable the node, and
/// the focus is not moved to another node, the FocusManager dispatches the
/// #FocusGainedMessage with #EnabledFocusReason.
///
/// Changing #VisibleProperty value on a node affects the active focus status of the
/// node the same way as #EnabledProperty.
///
/// Focus chain for key navigation
/// ----
/// The focus chain is the sequence of nodes which defines the order in which
/// Kanzi applies focus to nodes when the user uses the focus chain navigation keys
/// to move the focus. You as application developer do not need to care about
/// the default navigation, unless you want to override the default behavior, or
/// you want to provide other triggers to move the active focus across the nodes.
/// You can override the default key navigation by handling the Keyboard::KeyDownMessage.
/// Other means of focus chain navigation you can use can be actions that are
/// triggered by property changes, state changes on nodes, and so on.
/// The default chain navigation keys are the Tab and backtab keys. The forward
/// direction chain order uses the pre-order traversal of the node hierarchy,
/// while the backwards direction chain order uses the reverse pre-order traversal.
///
/// Kanzi automatically includes in the focus chain all nodes that have the
/// #FocusableProperty property set to \e true. To move the active focus to the
/// next node in the focus chain, call one of the #tryMoveActiveFocus() methods.
///
/// When Tab and backtab keys are functional keys of a node, such as in a text
/// editor node, that node consumes the keys used by the focus chain navigation.
/// When such node receives focus, to capture the Tab and backtab keys and handle
/// them as normal keys, mark the Keyboard::KeyDownMessage as handled. When you do so,
/// the FocusManager does not react to these keys and keeps the focus on the
/// current active focus node.
///
/// To use keys to move focus from such node, you must handle this in the key
/// down message handler for that node, and call one of the #tryMoveActiveFocus()
/// methods to move the active focus to the next or previous focusable node.
///
/// To move active focus in focus chain from a node which consumes the Tab and
/// backtab keys:
/// \snippet snippets_focus_manager.cpp Tab consumer node
///
/// Overriding focus chain navigation
/// ---
/// You can manually set the order of nodes in the focus chain by setting the
/// #NextFocusNodePathProperty and #PreviousFocusNodePathProperty properties of
/// nodes in the focus chain. Use these properties to set the relative path to
/// the next and previous nodes for a node in the focus chain.
///
/// In addition to the focus chain navigation, Kanzi provides directional focus
/// navigation to move the focus between nodes based on their rendered position.
/// FocusManager maps up, down, left, and right arrow keys to the corresponding
/// #FocusChainDirection. You can override the default behavior the same way as
/// the Tab and backtab key navigation in the example above.
///
/// You can set the destination nodes for directional navigation by setting the
/// #UpNavigationNodePathProperty, #DownNavigationNodePathProperty,
/// #LeftNavigationNodePathProperty, and #RightNavigationNodePathProperty properties,
/// but these do not affect the default focus chain navigation by any means.
///
/// When the path to the destination node specified in the #NextFocusNodePathProperty
/// and #PreviousFocusNodePathProperty properties is invalid or is disabled, FocusManager
/// falls back to the default focus chain navigation. When the destination node does
/// not meet the focusability requirements, FocusManager continues to look for a
/// focusable node from the destination node onward, taking into account the property
/// values set on the destination nodes affecting the focus chain navigation.
///
/// Focus scopes
/// ----
/// Focus scopes, or scopes, are nodes which assist in focus chain navigation handling.
/// They act like a focus proxy, forwarding the active focus to one of their child nodes
/// which has the logical focus set. A node is a scope when it has the #FocusScopeProperty
/// property attached and set to \e true. Whereas any node can be a scope, there is no
/// reason to make a node a scope if it has no child nodes, and it does not have child
/// nodes attached during runtime.
///
/// A node is considered to have logical focus if its #LogicalFocusProperty is set to
/// \e true. When you focus a scope using the #trySetActiveFocus() method, the FocusManager
/// looks for a child node that has logical focus set, and moves the active focus to
/// that node. If a scope has several child nodes with logical focus set, only the
/// last of those child nodes stays with logical focus state set, for all the previous
/// child nodes that had logical focus, Kanzi resets the state to \e false.
///
/// To set the active focus on the last logical focus child node of a scope:
/// \snippet snippets_focus_manager.cpp FocusOnScope
///
/// When you move the active focus out from the scope, the scope preserves the logical
/// focus state of its last active focus child node. This way when you return the focus
/// on the scope using the #trySetActiveFocus() method, Kanzi restores the active focus
/// on this node, unless you change the logical focus on the preserved node by other means.
///
/// To move the active focus back on the preserved node of a scope:
/// \snippet snippets_focus_manager.cpp FocusBackOnScopePreservedNode
///
/// When you focus a scope using the focus chain navigation methods, such as #tryMoveActiveFocus()
/// and its overrides, depending on the direction given, the scope forwards the active
/// focus to the first or last focusable child node. This happens regardless of whether
/// the scope had a node with the preserved logical focus.
/// \snippet snippets_focus_manager.cpp NavigateOutFromScopeAndBack
///
/// Scopes can have nested scopes. These nested or inner scopes behave in the same
/// way as any other scope: they forward and preserve the logical focus of their
/// child node the same way, regardless of their nested state.
///
/// When a node gets active focus, all its ascendant scopes get their logical focus
/// state set. The scopes keep the logical state as long as the active focus node
/// remains in their scope. When the active focus node is moved out from a scope,
/// the topmost ancestor scope that is not holding the new active focus node loses
/// the logical focus state, and all its descendant scopes preserve the logical focus.
///
/// This example shows this scenario:
/// \snippet snippets_focus_manager.cpp NestedScopesPreservingLogicalFocusState
///
/// Scopes are "skipped" in the focus chain navigation, because they do not get
/// active focus as long as they have children that can get active focus. If the
/// scopes are disabled, their content cannot get active focus. However, if a scope
/// is marked as not focusable, meaning its #FocusableProperty is set to \e false,
/// the content of the scope can still get active focus under these conditions:
/// - You move the active focus with any reason, except the #FocusChainNavigationReason.
/// - You move the active focus with the #FocusChainNavigationReason and
/// there was no previous active focus set.
/// - You move the active focus with the #FocusChainNavigationReason and
/// the previous active focus node is in the same scope.
///
/// You can override the default focus chain navigation in the same way as for regular
/// focus nodes. When done, focus chain navigation follows the linked nodes
/// and focuses the nodes or scopes linked.
///
/// Focus fences
/// ----
/// Scopes that cannot be focused are called focus fences. Focus fences keep the
/// focus chain navigation inside the scope and do not allow the focus chain
/// navigation to enter nor to leave the scope.
///
/// Focus fences are useful when you do not want the focus chain navigation to leave
/// the scope boundaries. For example, use focus fences in overlays, where the focus
/// navigation must be kept within the overlay content.
///
/// This example shows the focus fence behavior:
/// \snippet snippets_focus_manager.cpp FocusFence
class KANZI_API FocusManager
{
public:
    KZ_STATIC_METACLASS_BEGIN(FocusManager, "Kanzi.FocusManager")
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(NextFocusNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(PreviousFocusNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(UpNavigationNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(DownNavigationNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(LeftNavigationNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(RightNavigationNodePathProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(FocusScopeProperty)
    KZ_METACLASS_END()

    /// Specifies the reason the node is focused.
    enum FocusReason
    {
        /// The focus reason is unknown.
        UnknownReason,
        /// The focus is moved as a result of navigation in the focus chain.
        FocusChainNavigationReason,
        /// The #EnabledProperty or #VisibleProperty of the node with the active focus
        /// was set to \e false. The value is only used in post-focus messages.
        DisabledFocusReason,
        /// The #EnabledProperty or #VisibleProperty of the node with the logical focus
        /// was set to \e true. The value is only used in post-focus messages.
        EnabledFocusReason,
        /// The focus is moved due to some other reason than Tab or backtab
        /// keys or tap or mouse button press.
        OtherFocusReason
    };

    /// Specifies the direction of the focus move.
    enum FocusChainDirection
    {
        /// The focus is moved to the previous focusable node.
        PreviousFocusable,
        /// The focus is moved to the next focusable node.
        NextFocusable,
        /// The focus is moved to the node set in #UpNavigationNodePathProperty property.
        UpFocusable,
        /// The focus is moved to the node set in #DownNavigationNodePathProperty property.
        DownFocusable,
        /// The focus is moved to the node set in #LeftNavigationNodePathProperty property.
        LeftFocusable,
        /// The focus is moved to the node set in #RightNavigationNodePathProperty property.
        RightFocusable
    };

    /// \name Properties
    /// {
    /// The property overrides the default focus chain navigation order for the
    /// #NextFocusable direction. The value must be a relative path to the destination
    /// node. To reset the override, set the value of the property to an empty string.
    static PropertyType<string> NextFocusNodePathProperty;
    /// Returns the value of the #NextFocusNodePathProperty property for the node
    /// on which you call this function.
    /// \param node A node that has the #NextFocusNodePathProperty property attached.
    /// \return The value of the #NextFocusNodePathProperty property.
    static string getNextFocusNodePath(const Node& node);
    /// Sets the value of the #NextFocusNodePathProperty property.
    /// \param node A node which has the #NextFocusNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param next The value of the #NextFocusNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setNextFocusNodePath(Node& node, string_view next);
    /// The property overrides the default focus chain navigation order for the
    /// #PreviousFocusable direction. The value must be a relative path to the
    /// destination node. To reset the override, set the value of the property
    /// to an empty string.
    static PropertyType<string> PreviousFocusNodePathProperty;
    /// Returns the value of the #PreviousFocusNodePathProperty property for the
    /// node on which you call this function.
    /// \param node A node that has the #PreviousFocusNodePathProperty property attached.
    /// \return The value of the #PreviousFocusNodePathProperty property.
    static string getPreviousFocusNodePath(const Node& node);
    /// Sets the value of the #PreviousFocusNodePathProperty property.
    /// \param node A node which has the #PreviousFocusNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param previous The value of the #PreviousFocusNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setPreviousFocusNodePath(Node& node, string_view previous);
    /// The property holds the path to the node to navigate from the node to which the
    /// property is attached, when you specify the #UpFocusable direction in the
    /// #tryMoveActiveFocus. The value must be a relative path to the destination node.
    static PropertyType<string> UpNavigationNodePathProperty;
    /// The property holds the path to the node to navigate from the node to which the
    /// property is attached, when you specify the #DownFocusable direction in the
    /// #tryMoveActiveFocus. The value must be a relative path to the destination node.
    static PropertyType<string> DownNavigationNodePathProperty;
    /// The property holds the path to the node to navigate from the node to which the
    /// property is attached, when you specify the #LeftFocusable direction in the
    /// #tryMoveActiveFocus. The value must be a relative path to the destination node.
    static PropertyType<string> LeftNavigationNodePathProperty;
    /// The property holds the path to the node to navigate from the node to which the
    /// property is attached, when you specify the #RightFocusable direction in the
    /// #tryMoveActiveFocus. The value must be a relative path to the destination node.
    static PropertyType<string> RightNavigationNodePathProperty;
    /// Returns the value of the #UpNavigationNodePathProperty on the node on which
    /// you call this function.
    /// \param node A node that has the #UpNavigationNodePathProperty property attached.
    /// \return The value of the #UpNavigationNodePathProperty property.
    static string getUpNavigationNodePath(const Node& node);
    /// Sets the value of the #UpNavigationNodePathProperty property.
    /// \param node A node which has the #UpNavigationNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param path The value of the #UpNavigationNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setUpNavigationNodePath(Node& node, string_view path);
    /// Returns the value of the #DownNavigationNodePathProperty on the node on which
    /// you call this function.
    /// \param node A node that has the #DownNavigationNodePathProperty property attached.
    /// \return The value of the #DownNavigationNodePathProperty property.
    static string getDownNavigationNodePath(const Node& node);
    /// Sets the value of the #DownNavigationNodePathProperty property.
    /// \param node A node which has the #DownNavigationNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param path The value of the #DownNavigationNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setDownNavigationNodePath(Node& node, string_view path);
    /// Returns the value of the #LeftNavigationNodePathProperty on the node on which
    /// you call this function.
    /// \param node A node that has the #LeftNavigationNodePathProperty property attached.
    /// \return The value of the #LeftNavigationNodePathProperty property.
    static string getLeftNavigationNodePath(const Node& node);
    /// Sets the value of the #LeftNavigationNodePathProperty property.
    /// \param node A node which has the #LeftNavigationNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param path The value of the #LeftNavigationNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setLeftNavigationNodePath(Node& node, string_view path);
    /// Returns the value of the #RightNavigationNodePathProperty on the node on which
    /// you call this function.
    /// \param node A node that has the #RightNavigationNodePathProperty property attached.
    /// \return The value of the #RightNavigationNodePathProperty property.
    static string getRightNavigationNodePath(const Node& node);
    /// Sets the value of the #RightNavigationNodePathProperty property.
    /// \param node A node which has the #RightNavigationNodePathProperty property attached
    /// and for which you want to set the value.
    /// \param path The value of the #RightNavigationNodePathProperty property you want
    /// to set. The value must be a relative path to the destination node.
    static void setRightNavigationNodePath(Node& node, string_view path);
    /// Specifies that the node to which the property is attached is a focus scope.
    static PropertyType<bool> FocusScopeProperty;
    /// Returns the value of the #FocusScopeProperty property for the node on which you
    /// call this function.
    /// \param node A node that has the #FocusScopeProperty property attached.
    /// \return The value of the #FocusScopeProperty property.
    static bool isFocusScope(const Node& node);
    /// Sets the value of the #FocusScopeProperty property for the \a node.
    /// \param node A node which gets the #FocusScopeProperty property attached and for
    /// which you want to set the value.
    /// \param isScope The value of the #FocusScopeProperty property you want
    /// to set.
    static void setFocusScope(Node& node, bool isScope);
    /// Returns true if the \a node is a focus fence.
    /// \param node The node to check for focus fence.
    /// \return \e true if the \e node is a fence, false otherwise.
    static bool isFocusFence(const Node& node);
    /// }

    /// Message arguments for post-focus messages. Contains the reason the
    /// focus move is initiated.
    class KANZI_API PostFocusMessageArguments : public MessageArguments
    {
    public:
        /// \name Properties
        /// \{
        /// The property that holds the reason for the focus move. Takes the values
        /// of the #FocusManager::FocusReason enumeration. The default value is
        /// \b #FocusManager::UnknownReason.
        /// \see setFocusReason(), getFocusReason()
        static PropertyType<int> FocusReasonProperty;
        /// \}
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PostFocusMessageArguments, MessageArguments, "Kanzi.FocusManager.PostFocusMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(FocusReasonProperty)
        KZ_METACLASS_END()

        /// Returns the stored value for the focus reason.
        FocusManager::FocusReason getFocusReason() const;
        /// Sets the focus reason value.
        /// \param reason The focus reason value.
        void setFocusReason(FocusManager::FocusReason reason);
    };

    /// Message arguments for the pre-focus messages. These arguments hold the
    /// information for the reason of the focus change and the acceptance flag.
    class KANZI_API PreFocusMessageArguments : public PostFocusMessageArguments
    {
    public:
        /// \name Properties
        /// \{
        /// The property that holds the state of the pre-focus message acceptance.
        /// If the value is \e true, the pre-focus step is accepted, otherwise
        /// the focus move is rejected. Defaults to \e true.
        /// \see setAccepted(), isAccepted();
        static PropertyType<bool> AcceptFocusProperty;
        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PreFocusMessageArguments, PostFocusMessageArguments, "Kanzi.FocusManager.PreFocusMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(AcceptFocusProperty)
        KZ_METACLASS_END()

        /// Sets the acceptance status. By default the pre-focus messages are in
        /// accepted state. You need to call this method if you want to deny the
        /// focus move.
        /// \param accepted The new acceptance status.
        /// \snippet snippets_focus_manager.cpp Reject focus transfer handler
        void setAccepted(bool accepted);
        /// Returns the focus acceptance status.
        bool isAccepted() const;
    };

    /// The message dispatched to the active focus node and its ascendants before
    /// losing focus. This is the first message that Kanzi dispatches when you
    /// move the focus from the active focus node to the next focusable node during the
    /// #trySetActiveFocus() call. The message handler can reject the focus move
    /// by calling PreFocusMessageArguments::setAccepted(false).
    static MessageType<PreFocusMessageArguments> AboutToLoseFocusMessage;
    /// The message dispatched to the next focusable node. Message handlers can reject
    /// focus move by calling PreFocusMessageArguments::setAccepted(false). To avoid
    /// unnecessary propagation of the message through the scene graph, it is good
    /// practice to set the message as handled at this time.
    static MessageType<PreFocusMessageArguments> AboutToGainFocusMessage;
    /// Informs the old active focus node about losing the active focus. The message
    /// handlers can use this message to perform the required tasks after a node loses
    /// the focus.
    static MessageType<PostFocusMessageArguments> FocusLostMessage;
    /// Informs the new active focus node about getting the active focus. The message
    /// handlers can use this message to perform the required tasks after a node gets
    /// the focus.
    static MessageType<PostFocusMessageArguments> FocusGainedMessage;

    /// Creates the property editor info for the FocusManager.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();


    /// Tries to set the active focus to the \a newFocusNode and specifies the \a reason
    /// for moving the focus. The action fails if the node is not yet attached, or if
    /// the #FocusableProperty of the node, or one of its ancestors, is not set to \e true.
    /// The action fails also if there is no focusable node found in the focus chain and
    /// the \a reason is #FocusChainNavigationReason. The method takes the next focus candidate from
    /// the focus chain in forward direction.
    /// \param newFocusNode The node which receives the active focus. If you pass an empty shared
    /// pointer, the method returns the active focus node.
    /// \param reason The reason the focus is moved. Use #UnknownReason if the
    /// reason is unknown.
    /// \return The node that has the active focus. This can be:
    /// - The node to which you set focus
    /// - One of its ancestors
    /// - If the method cannot set the active focus on any node, the current active focus node
    NodeSharedPtr trySetActiveFocus(NodeSharedPtr newFocusNode, FocusReason reason);
    /// An overload of trySetActiveFocus() using #UnknownReason to move the active focus.
    /// \param newFocusNode The node which receives the active focus. Use an empty shared
    /// pointer to remove the active focus.
    /// remove the active focus.
    /// \return The node that has the active focus. This can be:
    /// - The node to which you set focus
    /// - One of its ancestors
    /// - If the method cannot set the active focus on any node, the current active focus node
    NodeSharedPtr trySetActiveFocus(NodeSharedPtr newFocusNode);

    /// Tries to set the active focus to a node relative to the current active
    /// focus node using the focus chain navigation. The method takes the next
    /// focus candidate from the focus chain in the given \a direction.
    ///
    /// The action fails if:
    /// - The node is not yet attached.
    /// - The #FocusableProperty property of the node, or one of its ancestors, is not set to \e true.
    /// - No focusable node is found in the focus chain.
	///
    /// \param direction The direction to query the next focusable node.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocus(FocusChainDirection direction);
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in forward direction.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusForward();
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in backward direction.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusBackward();
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in upward direction. The move is
    /// possible only when the #UpNavigationNodePathProperty points to a valid node.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusUpward();
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in downward direction. The move is
    /// possible only when the #DownNavigationNodePathProperty points to a valid node.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusDownward();
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in left direction. The move is
    /// possible only when the #LeftNavigationNodePathProperty points to a valid node.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusLeft();
    /// The method is a specialization of #tryMoveActiveFocus(FocusChainDirection) moving
    /// active focus from the current active focus node in right direction. The move is
    /// possible only when the #RightNavigationNodePathProperty points to a valid node.
    /// \return The node that has active focus.
    NodeSharedPtr tryMoveActiveFocusRight();

    /// Returns the node that has active focus. If the function returns an empty shared pointer, the
    /// active focus is not set.
    NodeSharedPtr getActiveFocus() const;

private:
    friend class Node;
    friend class Domain;
    friend class InputManager;

    /// Creates a FocusManager instance.
    explicit FocusManager();

    /// Notifies FocusManager about Node detaching.
    void notifyNodeDetached(const Node& node);
    /// The node notifies the FocusManager about the change of the value of its EnabledProperty or VisibleProperty.
    void notifyNodeEnabledChange(Node& node);
    /// Transfers the focus from one node to the other.
    bool transferFocus(Node* oldFocusNode, Node* newFocusNode, FocusReason reason, bool suppressPreFocusMessages);
    /// Filters the key events that drive the focus navigation.
    void handleKeyCode(KzsInputKey keyCode, bool pressed);

    /// Holds the active focus node.
    NodeWeakPtr m_activeFocus;
    /// Recursive call counter for trySetActiveFocus() method.
    size_t m_callGuard;
    /// Holds the Shift key pressed state. Used in the default focus chain navigation.
    bool m_shiftPressed;
    /// The effective active focus state of the active focus node.
    bool m_effectiveActiveFocus;
};

/// Returns the logical focus node of the scope \a node. The function skips the
/// nested scopes and executes a fixup for the scope's logical focus nodes.
/// \param node The scope node that has logical focus children.
/// \return The node that has logical focus in the \e scope, null pointer if
/// the node is not a scope or it has no logical focus child.
KANZI_API Node* getScopeFocusedNode(Node& node);

/// Sets the logical \a focus node of the given \a scope node. Any previous node
/// in the scope that had logical focus will get the state cleared.
/// \param scope The scope to which the focus node is set.
/// \param focus The node to which the logical focus is set.
KANZI_API void setScopeFocusedNode(Node& scope, Node& focus);

} // namespace kanzi

#endif // KZ_FOCUS_MANAGER_HPP
