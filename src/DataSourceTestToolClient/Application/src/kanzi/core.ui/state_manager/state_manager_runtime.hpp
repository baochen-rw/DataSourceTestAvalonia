// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STATE_MANAGER_RUNTIME_HPP
#define KZ_STATE_MANAGER_RUNTIME_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{

class KANZI_API StateManager::StateManagerRuntime
{
public:

    /// Constructor.
    /// \param stateManager State manager this runtime is using.
    /// \param domain Domain.
    /// \param groups List of state groups in state manager.
    /// \param objectNode Node owning the state manager.
    static StateManagerRuntimeSharedPtr create(StateManagerSharedPtr stateManager, Domain* domain, const StateGroupContainer& groups, Node& objectNode);

    /// Destructor.
    virtual ~StateManagerRuntime();

    /// Detach state manager runtime.
    void detach();

    Domain* m_domain;
    Node& m_objectNode;
    StateGroupRuntimeContainer m_groupRuntimes;
    StateManagerSharedPtr m_stateManager;

protected:

    /// Constructor.
    /// \param stateManager State manager this runtime is using.
    /// \param domain Domain.
    /// \param objectNode Node owning the state manager.
    explicit StateManagerRuntime(StateManagerSharedPtr stateManager, Domain* domain, Node& objectNode) :
        m_domain(domain),
        m_objectNode(objectNode),
        m_stateManager(stateManager)
    {
    }

    /// Remove handlers from state manager runtime.
    void removeHandlers();
    /// Unapply and delete styles recursively.
    void unapplyStyles();
    /// Stop transitions recursively.
    void stopTransitions();
    /// Stops tracking target objects.
    void releaseTargetObjects();

    typedef shared_ptr<TargetObject> TargetObjectSharedPtr;
    typedef vector<TargetObjectSharedPtr> TargetObjectVector;

    /// Collection of target objects.
    TargetObjectVector m_targetObjects;

    /// Starts tracking target objects.
    void captureTargetObjects();

    /** Subscription to StateManagerGoToState messages. */
    Node::MessageSubscriptionToken m_goToStateMessageSubscription;
    /** Subscription to StateManagerGoToNextDefinedState messages. */
    Node::MessageSubscriptionToken m_goToNextDefinedStateMessageSubscription;
    /** Subscription to StateManagerGoToPreviousDefinedState messages. */
    Node::MessageSubscriptionToken m_goToPreviousDefinedStateMessageSubscription;
};

}

#endif