// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TRIGGER_HPP
#define KZ_TRIGGER_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node_component/node_component.hpp>

namespace kanzi
{

class Node;
class Action;
typedef shared_ptr<Action> ActionSharedPtr;
class Condition;
typedef shared_ptr<Condition> ConditionSharedPtr;

class Trigger;
typedef shared_ptr<Trigger> TriggerSharedPtr;


/// Trigger is the base class for defining events, conditions and actions for content-driven logic programming.
class KANZI_API Trigger : public NodeComponent
{
public:

    /// \name Properties
    /// \{
#include "trigger_properties.h"
    /// \}

    KZ_ABSTRACT_METACLASS_BEGIN(Trigger, NodeComponent, "Kanzi.Trigger")
        KZ_METACLASS_PROPERTY_TYPE(ForwardedMessageProperty)
    KZ_METACLASS_END()

    /// Creates a copy of trigger.
    TriggerSharedPtr copy() const;

    /// Adds an action to the trigger.
    void addAction(ActionSharedPtr action);
    /// Invokes actions in the trigger.
    void invokeActions() const;

    typedef vector<ActionSharedPtr> ActionContainer;
    typedef ActionContainer::const_iterator ActionIterator;
    ActionIterator beginActions() const;
    ActionIterator endActions() const;

    /// Adds a condition to the trigger.
    void addCondition(ConditionSharedPtr condition);
    /// Checks against all conditions in the trigger.
    bool checkConditions() const;

    typedef vector<ConditionSharedPtr> ConditionContainer;
    typedef ConditionContainer::const_iterator ConditionIterator;
    ConditionIterator beginConditions() const;
    ConditionIterator endConditions() const;

protected:

    explicit Trigger(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

private:

    /// Actions invoked when trigger is triggered.
    ActionContainer m_actions;
    /// Conditions evaluated when trigger is triggered.
    ConditionContainer m_conditions;
};

}


#endif
