// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_MESSAGE_HANDLER_TRIGGER_H
#define KZU_MESSAGE_HANDLER_TRIGGER_H

#include "trigger.hpp"

#include <kanzi/core.ui/node/node.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

class Domain;

class MessageTrigger;
typedef shared_ptr<MessageTrigger> MessageTriggerSharedPtr;

/** Message handler trigger. */
class KANZI_API MessageTrigger : public Trigger
{
public:

    /// \name Properties
    /// \{
#include "message_trigger_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(MessageTrigger, Trigger, "Kanzi.MessageTrigger")
        KZ_METACLASS_PROPERTY_TYPE(MessageTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(SetHandledProperty)
        KZ_METACLASS_PROPERTY_TYPE(RoutingModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(MessageSourceProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static MessageTriggerSharedPtr create(Domain* domain, string_view name)
    {
        return make_polymorphic_shared_ptr<Trigger>(new MessageTrigger(domain, name));
    }

protected:

    explicit MessageTrigger(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

    void messageNotification(MessageArguments&);

private:
    
    Node::MessageSubscriptionToken m_messageSubscription;

};

}

#endif
