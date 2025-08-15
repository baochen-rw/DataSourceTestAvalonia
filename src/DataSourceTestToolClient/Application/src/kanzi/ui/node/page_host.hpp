// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PAGE_HOST_HPP
#define KZ_PAGE_HOST_HPP

#include <kanzi/ui/node/page.hpp>
#include <kanzi/core.ui/node/node_property_notification_handler.hpp>

namespace kanzi
{

class PageHost;
typedef shared_ptr<PageHost> PageHostSharedPtr;

/// Use a PageHost node to group Page and PageHost nodes, and to manage navigation requests and transitions in a tree of Page nodes under a PageHost node.
///
/// The role of PageHost nodes in navigation
/// ----
/// When you set a PageHost node as an ancestor of a Page node, that PageHost node listens for navigation requests from its descendant Page nodes. When a PageHost node receives a navigation request, 
/// it starts the navigation process to the Page node which dispatched the message.
/// The navigation process involves resolving the route from the currently active Page or PageHost node to the target Page or PageHost node, and then performing transitions between Page nodes in the navigation route until the target Page or PageHost node is activated.
/// Each PageHost node manages the navigation within its own scope and does not interfere with other PageHost nodes.
///
/// Activation tracking
/// ----
/// PageHost nodes keep track of the currently active Page or PageHost node within their scope. When you activate a PageHost node, that PageHost node automatically activates the currently active Page 
/// or PageHost node in its scope. This allows the PageHost node to remember and restore its state during activation to the state before it was deactivated.
///
/// Navigating between subpages
/// ----
/// PageHost nodes contain the functionality to navigate between the next and previous Page and PageHost nodes within their scope. This allows you to build support for navigation using key input.
/// You can further configure this functionality to set whether you want a PageHost node to loop from the last to the first or the first to the last Page node when navigating to the next and the previous Page and PageHost.
///
/// Nesting PageHost nodes
/// ----
/// You can nest PageHost nodes to create the structure of an application user interface. For example, you can have one PageHost node managing the root-level navigation in the application user interface, such as transitions between 
/// the Home, Media Browser, Navigation, and Settings, and add to it child PageHost nodes, each of which manages its own hierarchy of Page nodes, such as Media Browser's own Page nodes.
/// \see Page
///
/// Examples
/// ----
///
/// To transition to the selected Page node:
/// \snippet test_page.cpp Navigate to given page
///
/// To transition instantly to the selected Page node:
/// \snippet test_page.cpp Navigate to given page immediately
///
/// To get the currently active Page or PageHost descendant node:
/// \snippet test_page.cpp Retrieve current subpage
///
/// To transition from the current subpage to the next subpage:
/// \snippet test_page.cpp Navigate to next subpage
class KANZI_UI_API PageHost : public Page
{
public:

    /// Represents message arguments of NavigationStarted message.
    class KANZI_UI_API NavigationStartedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigationStartedMessageArguments, MessageArguments, "Kanzi.Page.NavigationStartedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of NavigationFinished message.
    class KANZI_UI_API NavigationFinishedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigationFinishedMessageArguments, MessageArguments, "Kanzi.Page.NavigationFinishedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of NavigateNext message.
    class KANZI_UI_API NavigateNextMessageArguments: public NavigateMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigateNextMessageArguments, NavigateMessageArguments, "Kanzi.Page.NavigateNextMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of NavigatePrevious message.
    class KANZI_UI_API NavigatePreviousMessageArguments: public NavigateMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NavigatePreviousMessageArguments, NavigateMessageArguments, "Kanzi.Page.NavigatePreviousMessageArguments")
        KZ_METACLASS_END()
    };

    /// Navigation started message type.
    /// Use this notification message to find out that the navigation process is about to start.
    /// Kanzi always dispatches this message before any navigation progress messages like, for example, Page.ActivatedMessage or Page.DeactivatedMessage.
    static MessageType<NavigationStartedMessageArguments> NavigationStartedMessage;
    /// Navigation finished message type.
    /// Use this notification message to find out that the navigation process is about to end.
    /// Kanzi always dispatches this message after navigation progress messages like, for example, Page.ActivatedMessage or Page.DeactivatedMessage.
    static MessageType<NavigationFinishedMessageArguments> NavigationFinishedMessage;
    /// NavigateNext message type.
    /// Use this message to tell a PageHost node to navigate from the currently active subpage to the next subpage.
    static MessageType<NavigateNextMessageArguments> NavigateNextMessage;
    /// NavigatePrevious message type.
    /// Use this message to tell a PageHost node to navigate from the currently active subpage to the previous subpage.
    static MessageType<NavigatePreviousMessageArguments> NavigatePreviousMessage;

public:
    /// Creates a PageHost node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static PageHostSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(PageHost, Page, "Kanzi.PageHost")
        KZ_METACLASS_PROPERTY_TYPE(TransitionsProperty)
        KZ_METACLASS_PROPERTY_TYPE(DefaultSubPageProperty)
        KZ_METACLASS_PROPERTY_TYPE(LoopSubPagesProperty)

        KZ_METACLASS_MESSAGE_TYPE(NavigationStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(NavigationFinishedMessage)
        KZ_METACLASS_MESSAGE_TYPE(NavigateNextMessage)
        KZ_METACLASS_MESSAGE_TYPE(NavigatePreviousMessage)
    KZ_METACLASS_END()

    /// \name Properties
    /// \{
#include "page_host_properties.h"
    /// \}

    /// PageHost nodes keep track of their default or the currently active subpage. This function returns the currently active subpage.
    /// \return Shared pointer to the currently active subpage. If none of the PageHost child nodes are active, the return value is an empty pointer.
    PageSharedPtr getDefaultChild() const;

    /// Sets the default or the currently active subpage. Kanzi automatically activates the default subpage when this PageHost is activated.
    /// \param page Page to activate.
    void setDefaultChild(PageSharedPtr page);

    /// Requests to navigate to the given Page node.
    /// \param page The Page node to which you want to navigate.
    /// \param immediate If true, the transition is instant.
    /// \return Returns true if the navigation request is successful.
    bool navigateTo(Page& page, bool immediate);

    /// Checks whether there is an ongoing transition between Page nodes.
    /// \return Returns true if there is an ongoing transition, otherwise returns false.
    bool isTransitionInProgress() const;

    /// Retrieves transitions used in the scope of this PageHost node.
    /// \return Pointer to the page transition collection.
    PageTransitionCollectionSharedPtr getTransitionCollection() const;

    /// Set transitions to be used by this PageHost node.
    /// When transitioning between pages, the PageHost determines the most suitable transition from the given collection and uses it to transition pages in and out.
    /// \param transitions Transition group to use for transitions in the scope of this PageHost node.
    void setTransitionCollection(PageTransitionCollectionSharedPtr transitions);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit PageHost(Domain* domain, string_view name);

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

    void initialize();

    /// Node::onPropertyChanged implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

private:

    /// Requests to navigate to given page.
    /// \param page Target page for navigation.
    /// \param immediate If true, does not play any transitions.
    /// \param activateOnly If true, does not perform deactivation.
    /// \param reportActivation Is this page activated intentionally, and should activation send messages.
    /// \return Returns true if navigation request was successful.
    bool navigateTo(Page& page, bool immediate, bool activateOnly, bool reportActivation);

    /// Starts the navigation to the selected Page node and populates the internal navigation route.
    /// \param page Target page.
    /// \param immediate If true, ignores all transition animations and makes the transition instantly.
    /// \param activateOnly If true, only performs the activation phase of the transition route.
    /// \param reportActivation Is this page activated intentionally, and should activation send messages.
    void startNavigation(Page& page, bool immediate, bool activateOnly, bool reportActivation);

    /// Finishes the navigation and clears the internal navigation route.
    void finishNavigation();

    /// Entry within navigation level, represents activation/deactivation of single element during navigation.
    class NavigationEntry
    {
    public:
        /// Describes the operation(s) that need to be performed when processing a navigation entry.
        enum Operation
        {
            /// Transitioning from subpage to parent. Navigation logic needs to deactivate the 'from' page and keep 'to' page intact. 
            Deactivate,
            /// Transitioning from parent to subpage. Navigation logic needs to activate 'to' page and keep 'from' page intact.
            Activate,
            /// Transitioning between sibling pages, Navigation logic needs to deactivate 'from' page and activate 'to' page.
            DeactivateAndActivate
        };

        /// Describes the state of this navigation entry. Allows navigation system to keep track of the navigation progress.
        enum State
        {
            /// Transition route has been resolved, but this entry has not been processed by the navigation system.
            Inactive,
            /// Navigation system is currently processing this entry in the navigation route (waiting it to complete before progressing to next step in the route).
            Active,
            /// Navigation system has already processed this entry in the navigation route and progressed to the next step in the navigation route.
            Completed
        };

        /// Constructor.
        NavigationEntry(PageSharedPtr source, PageSharedPtr target, Operation op) 
            : from(source), to(target), fromState(Inactive), toState(Inactive), operation(op) {}

        bool isActive() const
        {
            return fromState == NavigationEntry::Active || toState == NavigationEntry::Active;
        }

        PageWeakPtr from;
        PageWeakPtr to;

        PageSharedPtr fromLocked;
        PageSharedPtr toLocked;

        State fromState;
        State toState;

        Operation operation;
    };

    /// Container for navigation entries.
    typedef shared_ptr<NavigationEntry> NavigationEntryPtr;

    /// Instructions for navigation request.
    typedef vector<NavigationEntryPtr> NavigationRoute;

    /// Runtime data for a registered page. All pages are registered to the nearest ancestor page host.
    class PageRuntimeData : public NodePropertyNotificationHandler
    {
    public:

        /// Constructor.
        explicit PageRuntimeData(PageHost* host, Page* node);

        /// Returns the page.
        Page* getPage() const;

        /// Listens to the changes in AutoActivateProperty.
        virtual void onPropertyChanged(PropertyNotificationReason reason) KZ_OVERRIDE;

        /// Stores a page transition collection runtime.
        void attachTransitionRuntime(PageTransitionCollection::RuntimeSharedPtr runtime);

        /// Removes the page transition collection runtime.
        void detachTransitionRuntime();

        /// Makes the stored page transition collection runtime start a transition.
        /// \return True if a transition was started; false otherwise.
        bool startTransition(PageTransitionCollection::Transition* transition, bool active, bool wasActive);

    private:
        PageHost* m_host;
        PageTransitionCollection::RuntimeSharedPtr m_runtime;
    };
    typedef shared_ptr<PageRuntimeData> PageRuntimeDataSharedPtr;

    /// Starts all transitions in one point of the navigation route, returns true if there was valid entries to start.
    /// \param iterator Current navigation entry to start.
    /// \param immediate If true, ignores transition animations and performs instant transition.
    bool startNavigationEntry(NavigationRoute::iterator iterator, bool immediate);
    /// Progress navigation entry.
    bool progressNavigationEntry(NavigationEntry& entry, Page& completed);
    /// Cleans up any allocations / subscriptions that were made when transitions were started in a point of navigation route.
    void finishNavigationEntry(NavigationRoute::iterator iterator);

    /// Checks whether navigation entry is valid.
    bool isValidNavigationEntry(const NavigationEntry& entry);

    /// Clears navigation route and terminates current navigation.
    void clearNavigationRoute();

    /// Activates or deactivates a page.
    /// \param page Page to transition.
    /// \param activate If true, transitions from inactive to active.
    /// \param immediate If true, ignores transition animations and performs instant transition.
    /// \param from Defines the Page that is currently seen by the viewer.
    /// \param to Defines the page that is to be seen by the viewer.
    /// \return true if animations were successfully started.
    bool playTransition(Page& page, bool activate, bool immediate = true, Node2D* from = 0, Node2D* to = 0);

    /// Updates the default subpage of a PageHost node.
    /// \param page Page that is changing state.
    /// \param state New state of the page.
    void updateDefaultPage(Page& page, bool state);

    /// Is called when navigation entry completes.
    /// \return If true, either progressed navigation or finished it.
    bool navigationEntryCompleted(Page& completed);

    /// Callback to register a Page node to the scope of this PageHost node.
    void onPageRegisterToNavigation(RegisterToNavigationMessageArguments& message);
    /// Callback to unregister a Page node from the scope of this PageHost node.
    void onPageUnregisterFromNavigation(UnregisterFromNavigationMessageArguments& message);

    /// Callback for page navigation state change (activation).
    void onPageNavigationActivated(NavigationActivatedMessageArguments& message);
    /// Callback for page navigation state change (deactivation).
    void onPageNavigationDeactivated(NavigationDeactivatedMessageArguments& message);

    /// Callback for navigation request to page.
    void onPageNavigate(NavigateMessageArguments& message);
    /// Callback for navigation request to next sub-page.
    void onPageNavigateNext(NavigateNextMessageArguments& message);
    /// Callback for navigation request to previous sub-page.
    void onPageNavigatePrevious(NavigatePreviousMessageArguments& message);
    /// Callback for navigation request to parent page.
    void onPageNavigateParent(NavigateParentMessageArguments& message);

    /// Container used to group pages when gathering navigation route.
    typedef vector<PageSharedPtr> PageContainer;
    /// Container used when gathering navigation route.
    typedef map<unsigned int, PageContainer> NavigationIterations;

    /// Tries to merge two navigation entries as one cross-transition.
    /// \param current First entry to be executed.
    /// \param next Second entry to be executed after first entry.
    /// \return If true, successfully combined the two entries in to current. Next is no longer needed.
    static bool mergeNavigationEntries(NavigationEntry& current, NavigationEntry& next);

    /// Function to collect all pages which need to be deactivated in order to navigate to target page.
    /// \param page Page to process.
    /// \param target Target for navigation.
    /// \param result Collection of navigation iterations, new iterations are added here during the recursion.
    /// \param level Depth of recursion.
    /// \param parentRemainsActive Indication that the parent of this page remains active even if we are collecting deactivations.
    static void collectPagesToDeactivate(Page& page, Page& target, NavigationIterations& result, unsigned int level, bool parentRemainsActive);

    /// Function to collect all pages which need to be activated in order to navigate to target page.
    /// \param page Page to process.
    /// \param target Target for navigation.
    /// \param result Collection of navigation iterations, new iterations are added here during the recursion.
    /// \param level Depth of recursion.
    /// \param parentIsActive Indication that the parent of this page will be active.
    static void collectPagesToActivate(Page& page, Page& target, NavigationIterations& result, unsigned int level, bool parentIsActive);

    /// Applies state of a page according to 'keep active' property.
    /// \param page Page to process.
    /// \return If true, changed state of this page to active.
    bool applyAutoActivationState(Page& page);

    /// Applies initial state to page when attached to tree.
    /// \param page Page to process.
    void applyInitialState(Page& page);

    /// Provides access to runtime data of given page.
    /// \return Pointer to runtime data.
    PageRuntimeDataSharedPtr getRuntimeData(Page& page) const;

    /// Initialize all transitions according to transition collection resource.
    void initializeTransitions();
    /// Uninitialize all transitions and cleanup.
    void uninitializeTransitions();

    /// Write whole navigation route to log.
    void outputNavigationRouteToLog();
    /// Write single navigation entry to log.
    void outputNavigationEntryToLog(NavigationEntryPtr entry, bool immediate);

    /// Current position of the navigation route, during the navigation process.
    NavigationRoute::iterator m_current;

    /// Current navigation route, during the navigation process.
    NavigationRoute m_route;

    /// Allows to protect against nested navigation requests.
    bool m_isPerformingNavigationRequest;

    /// Message subscription to listen for page state activation during navigation.
    MessageSubscriptionToken m_navigationActivatedMessageSubscription;

    /// Message subscription to listen for page state deactivation during navigation.
    MessageSubscriptionToken m_navigationDeactivatedMessageSubscription;

    /// Default child reference. The active child in tracked by the user reference.
    NodeReference<Page> m_defaultChild;

    /// Type for runtime data container.
    typedef vector<PageRuntimeDataSharedPtr> PageRuntimeCollection;

    /// Runtime data for all pages in navigation scope.
    PageRuntimeCollection m_runtimes;

    /// Transitions.
    PageTransitionCollectionSharedPtr m_cachedTransitionCollection;
};

}

#endif

#endif
