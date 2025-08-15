// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PAGE_TRANSITION_COLLECTION_HPP
#define KZ_PAGE_TRANSITION_COLLECTION_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core.ui/state_manager/state_manager.hpp>
#include <kanzi/core.ui/node/node.hpp>

#include <kanzi/core/cpp/chrono.hpp>

namespace kanzi
{

class Page;

class PageTransitionCollection;
typedef shared_ptr<PageTransitionCollection> PageTransitionCollectionSharedPtr;

/// Transition collection is used to define transitions within a Page Host.
class KANZI_UI_API PageTransitionCollection : public Resource
{
public:
    /// Entry in transition animation array.
    class TransitionAnimation
    {
    public:
        /// Property to be animated in this transition animation entry.
        AbstractPropertyType propertyType;
        /// Start value for the property.
        Variant startValue;
        /// End value for the property.
        Variant endValue;
    };
    /// Shared ptr declaration for transition animation.
    typedef shared_ptr<TransitionAnimation> TransitionAnimationSharedPtr;
    /// Container class for transition animations.
    typedef vector<TransitionAnimationSharedPtr> TransitionAnimationContainer;

    /// Describes transition from one page to another.
    class Transition
    {
    public:
        /// Enumeration that describes the direction of the transition.
        enum Direction
        {
            /// Transition is two-way.
            Bidirectional,
            /// Transition is one-way from source to target.
            Unidirectional
        };

        /// Defines target for animation.
        enum AnimationTarget
        {
            /// Animation targets to item that is transitioning in.
            PageIn,
            /// Animation targets to item that is transitioning out.
            PageOut
        };

        explicit Transition() : direction(Bidirectional), duration(chrono::milliseconds::zero()) {}

        /// Direction of the transition.
        Direction direction;
        /// Selection criteria for a state: Path to source page (relative to context).
        string from;
        /// Selection criteria for a state : Path to target page(relative to context).
        string to;
        /// Named state for this transition.
        string stateId;
        /// Duration of the transition in ms.
        chrono::milliseconds duration;

        /// Animations in this transition.
        TransitionAnimationContainer animationsIn;
        /// Animations in this transition.
        TransitionAnimationContainer animationsOut;
    };

    /// Shared ptr declaration for transition definition.
    typedef shared_ptr<Transition> TransitionSharedPtr;

    /// \name Properties
    /// \{
#include "page_transition_collection_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(PageTransitionCollection, Resource, "Kanzi.PageTransitionCollection")
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionDurationProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionFromProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionToProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionDirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionAnimationAnimationTargetProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionAnimationPropertyTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionAnimationStartValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(PageTransitionAnimationEndValueProperty)
    KZ_METACLASS_END()

    static PageTransitionCollectionSharedPtr create(Domain* domain, string_view name = "");

    virtual ~PageTransitionCollection() KZ_OVERRIDE;

    /// Add transition to transition group, needs to be called before transition group is attached to scene graph.
    /// \param transition Transition to add.
    void addTransition(TransitionSharedPtr transition);
    
    /// Remove transition from transition group, needs to be called before transition group is attached to scene graph.
    /// \param transition Transition to remove.
    void removeTransition(TransitionSharedPtr transition);

    /// Container & iterator types for transitions.
    typedef vector<TransitionSharedPtr> TransitionContainer;
    typedef TransitionContainer::const_iterator TransitionConstIterator;

    /// Returns iterator to start of the transition container.
    /// \return Iterator at the beginning of the container.
    TransitionConstIterator beginTransitions() const;

    /// Returns iterator to end of the transition container.
    /// \return Iterator at the end of the container.
    TransitionConstIterator endTransitions() const;

    /// Finds matching transition definition for given parameters, falls back to default.
    /// \param source Transition source, relative path to page host.
    /// \param target Transition target, relative path to page host.
    /// \return The transition definition which has best match for this scenario.
    TransitionSharedPtr findTransition(string_view source, string_view target);

    /// Runtime class that is instantiated per page. Drives the internal state manager that is used to animate transitions.
    // Contains all data that is required to manage the runtime state transitions of attached page.
    class Runtime
    {
    public:

        explicit Runtime() :
            m_stateGroup(),
            m_attachedPage()
        {
        }

        /// Starts transition to active / inactive state.
        /// \param transition Transition to start.
        /// \param active If true, transitions attached page to active state.
        /// \param wasActive Previous state of the page.
        void startTransition(Transition* transition, bool active, bool wasActive);
        /// Finishes transition.
        void finishTransition();

    private:
        friend class PageTransitionCollection;

        /// Applies transition definition to given state pair.
        /// \param start Starting state.
        /// \param end Ending state
        /// \param definition The transition definition to be applied.
        void applyTransitionAnimations(Node* node, StateManager::State* start, StateManager::State* end, const PageTransitionCollection::Transition* definition);

        /// Applies transition to internal state manager.
        /// \param transition Transition to be applied.
        void applyTransition(Node* node, PageTransitionCollection::Transition* transition);

        /// Sets up default values for transitions.
        void applyTransitionsToDefault(Node* node, const TransitionContainer& transitions);

        /// Handler for state transition finished message.
        void onStateTransitionFinished(StateManager::TransitionFinishedMessageArguments& message);

        /// State logic for attached page.
        StateManagerSharedPtr m_stateManager;
        /// State group that contains all transition states of a page.
        StateManager::StateGroup* m_stateGroup;
        /// Runtime for state manager.
        StateManager::StateManagerRuntimeSharedPtr m_pageStateManagerRuntime;
        /// Message subscriptions to track transition progress.
        Node::MessageSubscriptionTokenVector m_stateTransitionFinishedMessageSubscriptions;
        /// Attached page.
        Page* m_attachedPage;
    };

    typedef shared_ptr<Runtime> RuntimeSharedPtr;

    /// Attach transitions to Page component.
    /// \param page Page to attach transitions in to.
    /// \return Runtime object that manages page transitions.
    RuntimeSharedPtr attach(Page* page);

    /// Detach transitions from Page component.
    /// \param transitionGroupRuntime Transitions to detach.
    static void detach(RuntimeSharedPtr transitionGroupRuntime);

    // Resource interface.
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Loads page transition collection from KZB and returns it.
    ///
    /// \param domain Domain.
    /// \param name Name of page transition collection.
    /// \param kzbFile KZB to read page transition collection from.
    /// \param file File entry in KZB which contains page transition collection data.
    /// \param parser Parser to parse page transition collection data.
    /// \return Loaded page transition collection.
    static PageTransitionCollectionSharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

protected:
    friend class ResourceManager;
    friend class Page;

    explicit PageTransitionCollection(Domain* domain, string_view name = "");

private:
    // For now, PageTransition is not copyable.
    PageTransitionCollection(const PageTransitionCollection&) KZ_DELETED_FUNCTION;
    PageTransitionCollection& operator=(const PageTransitionCollection&) KZ_DELETED_FUNCTION;

    /// Transitions, describing the transition rules within this group.
    TransitionContainer m_transitions;
};

} // namespace kanzi

#endif // KZ_PAGE_TRANSITION_HPP

#endif
