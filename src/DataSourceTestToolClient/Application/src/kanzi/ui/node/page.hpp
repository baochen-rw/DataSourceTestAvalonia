// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PAGE_HPP
#define KZ_PAGE_HPP

#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/page_transition_collection.hpp>

namespace kanzi
{

class Page;
typedef shared_ptr<Page> PageSharedPtr;
typedef weak_ptr<Page> PageWeakPtr;


/// Use Page nodes to create the structure of an application user interface. For example, you can create different parts of the user interface, such as Home, Media Browser, Navigation, or Settings screens, each in their own hierarchy of Page nodes.
///
/// Activating Page nodes
/// ----
/// When a Page node is active all its ancestor Page and PageHost nodes are active too. When a Page or a PageHost node is active all its content and content of all its ancestor Page and PageHost nodes is visible and users can interact with it.
/// In a simple use case only one Page node in a hierarchy is active. However, you can build a complex structure by activating more than one Page or PageHost node in a hierarchy at the same time. To achieve this set the auto-activate flag on all 
/// Page and PageHost nodes which you want to automatically activate. Such nodes become automatically active when their parent Page or PageHost node is active.
///
/// Navigating between Page nodes
/// ----
/// PageHost nodes handle the navigation and transitions between Page nodes. For this reason you must place a PageHost node as an ancestor of a Page node tree hierarchy.
/// To navigate between Page nodes request the navigation system to navigate to the selected page. When you navigate to a Page node, Kanzi transitions the node to a visible (activated) state and the contents of the node become visible to the user.
/// When you navigate away from a Page node, Kanzi transitions the node to an invisible (deactivated) state and the contents of the node are no longer visible to the user. Kanzi supports both animated (over-time) and instant (immediate) transitions between Page nodes.
///
/// \see PageHost
///
/// Examples
/// ----
///
/// To transition to the selected Page node:
/// \snippet test_page.cpp Navigate to given page
///
/// To transition instantly to the selected Page node:
/// \snippet test_page.cpp Navigate to given page immediately
class KANZI_UI_API Page : public Node2D
{
public:

    /// Represents message arguments of Navigate message.
    class KANZI_UI_API NavigateMessageArguments: public MessageArguments
    {
    public:
        static PropertyType<bool> ImmediateProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigateMessageArguments, MessageArguments, "Kanzi.Page.NavigateMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ImmediateProperty)
        KZ_METACLASS_END()

        bool isImmediate() const { return getArgument(ImmediateProperty); }
        void setImmediate(bool value) { setArgument(ImmediateProperty, value); }
    };

    /// Represents message arguments of NavigateParent message.
    class KANZI_UI_API NavigateParentMessageArguments: public NavigateMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigateParentMessageArguments, NavigateMessageArguments, "Kanzi.Page.NavigateParentMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of Activated message.
    class KANZI_UI_API ActivatedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ActivatedMessageArguments, MessageArguments, "Kanzi.Page.ActivatedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of Deactivated message.
    class KANZI_UI_API DeactivatedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(DeactivatedMessageArguments, MessageArguments, "Kanzi.Page.DeactivatedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Navigate message type.
    /// Use this message to request the navigation system to navigate to the Page node where the message is sent.
    static MessageType<NavigateMessageArguments> NavigateMessage;
    /// NavigateParent message type.
    /// Use this message to request the navigation system to navigate to the parent Page node of the Page node where the message is sent.
    static MessageType<NavigateParentMessageArguments> NavigateParentMessage;
    /// Activated message type.
    /// Use this message to find out whether the state of this Page node changed from inactive to active.
    static MessageType<ActivatedMessageArguments> ActivatedMessage;
    /// Deactivated message type.
    /// Use this message to find out whether the state of this Page node changed from active to inactive.
    static MessageType<DeactivatedMessageArguments> DeactivatedMessage;

protected:
    /// These messages are used by the page navigation logic internally.

    /// Represents message arguments of NavigationActivated message.
    class NavigationActivatedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigationActivatedMessageArguments, MessageArguments, "Kanzi.Page.NavigationActivatedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of NavigationDeactivated message.
    class NavigationDeactivatedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigationDeactivatedMessageArguments, MessageArguments, "Kanzi.Page.NavigationDeactivatedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of RegisterToNavigation message.
    class RegisterToNavigationMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(RegisterToNavigationMessageArguments, MessageArguments, "Kanzi.Page.RegisterToNavigationdMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of UnregisterFromNavigation message.
    class UnregisterFromNavigationMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(UnregisterFromNavigationMessageArguments, MessageArguments, "Kanzi.Page.UnregisterFromNavigationMessageArguments")
        KZ_METACLASS_END()
    };

    /// NavigationActivated message type. Used internally by the navigation system.
    static MessageType<NavigationActivatedMessageArguments> NavigationActivatedMessage;
    /// NavigationDeactivated message type. Used internally by the navigation system.
    static MessageType<NavigationDeactivatedMessageArguments> NavigationDeactivatedMessage;
    /// RegisterToNavigation message type. Used internally by the navigation system.
    static MessageType<RegisterToNavigationMessageArguments> RegisterToNavigationMessage;
    /// UnregisterFromNavigation message type. Used internally by the navigation system.
    static MessageType<UnregisterFromNavigationMessageArguments> UnregisterFromNavigationMessage;

public:
    /// Creates a Page node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static PageSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Page, Node2D, "Kanzi.Page")
        KZ_METACLASS_PROPERTY_TYPE(StateProperty)
        KZ_METACLASS_PROPERTY_TYPE(SlideOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScaleOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(RotationOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(AutoActivateProperty)
        KZ_METACLASS_PROPERTY_TYPE(TransitionPhaseProperty)

        KZ_METACLASS_MESSAGE_TYPE(NavigateMessage)
        KZ_METACLASS_MESSAGE_TYPE(NavigateParentMessage)
        KZ_METACLASS_MESSAGE_TYPE(ActivatedMessage)
        KZ_METACLASS_MESSAGE_TYPE(DeactivatedMessage)

        KZ_METACLASS_MESSAGE_TYPE(NavigationActivatedMessage)
        KZ_METACLASS_MESSAGE_TYPE(NavigationDeactivatedMessage)
    KZ_METACLASS_END()

    /// \name Properties
    /// \{
#include "page_properties.h"
    /// \}

    /// Returns the parent Page or PageHost node in the scene graph. Note that the parent Page is an ancestor of this Page node, but is not necessarily also the immediate parent node.
    /// \return True if the Page node is at the root of the tree, otherwise false.
    Page* getParentPage() const;

    /// Checks whether a Page node is a root of all the pages in the tree. The root Page node does not have a parent Page or PageHost node.
    /// \return True if the Page node is root of Page and PageHost nodes in the tree, otherwise false.
    bool isTreeRoot() const;

    /// Returns all immediate subpages in the scene graph. Note that the returned Page or PageHost nodes are descendants of this Page node, but are not necessarily also immediate child nodes of this node.
    /// \return A collection of subpage Page and PageHost nodes.
    vector<PageSharedPtr> findSubpages() const;

    /// Requests navigation to this Page or PageHost node by sending a message to the scene graph.
    /// \param immediate If true, the transition is instant.
    void navigate(bool immediate = false);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Page(Domain* domain, string_view name);

    /// Node2D::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

    /// onAttached() implementation.
    virtual void onAttached() KZ_OVERRIDE;
    /// onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Initializes this page.
    void initialize();

private:

    /// Performs recursive search in scene graph until finds a page from that branch.
    /// \param node Starting node for the search.
    /// \param result Array reference to gather search results.
    void findSubpagesRecursive(const Node2D* node, vector<PageSharedPtr>& result) const;

    /// Transition state enumeration, used to internally track whether there is ongoing transition.
    /// Allows page to properly notify navigation logic even if it is detached from the scene graph while transition is still in progress.
    enum TransitionState
    {
        /// Transition has not been started.
        TransitionIdle,
        /// Transition in progress: page is activating.
        TransitionIn,
        /// Transition in progrees: page is deactivating.
        TransitionOut
    };

    /// Sets a new state of transition for a page. This is used internally and user should not call it directly.
    /// \param state New state.
    void setTransitionState(TransitionState state);

    /// Retrieves current transition state of a page. This is used internally and user should not call it directly.
    /// \return Current state of transition.
    TransitionState getTransitionState() const;

    /// Sets a flag to indicate the state of the page. This is used internally and user should not call it directly.
    /// \param state New state value to cache.
    void setCachedActivationState(bool state);

    /// Checks whether the activation state was cached. This is used internally and user should not call it directly.
    /// \return Activation state that was cached.
    bool getCachedActivationState() const;

    /// Requests page to notify navigation system about it's state change. This is used internally and user should not call it directly.
    void notifyStateChanged();

private:

    friend class PageHost;
    friend class PageTransitionCollection;
    TransitionState m_transitionState;

    // Caches the activation state whenever it is changed by the navigation logic.
    // This is a work-around for issue, where the activation state sometime gets reset during the patching and pages lose their activation state.
    // The navigation logic will pick the state up whenever pages are re-attached to scene graph.
    bool m_cachedActivationState;
};

}

#endif
#endif