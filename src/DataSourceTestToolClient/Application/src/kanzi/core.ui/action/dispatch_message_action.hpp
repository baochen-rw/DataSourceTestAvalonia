// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_DISPATCH_MESSAGE_ACTION_H
#define KZU_DISPATCH_MESSAGE_ACTION_H

#include "forwarding_action.hpp"

namespace kanzi
{

struct Variant;
class Domain;

class DispatchMessageAction;
typedef shared_ptr<DispatchMessageAction> DispatchMessageActionSharedPtr;


/** Dispatch message action. */
class KANZI_API DispatchMessageAction : public ForwardingAction
{
public:

    /** Dispatch mode. */
    enum DispatchMode
    {
        DispatchModeNode,
        DispatchModeSend,
        DispatchModePost
    };

    /// \name Properties
    /// \{
#include "dispatch_message_action_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(DispatchMessageAction, ForwardingAction, "Kanzi.DispatchMessageAction")
        KZ_METACLASS_PROPERTY_TYPE(MessageTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(DispatchModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(RoutingTargetProperty)
        KZ_METACLASS_PROPERTY_TYPE(RoutingTargetLookupProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static DispatchMessageActionSharedPtr create(Domain* domain, string_view name);

protected:

    /** Create a dispatch message action. */
    explicit DispatchMessageAction(Domain* domain, string_view name);

    /** Attach dispatch message action */
    virtual void onAttach() KZ_OVERRIDE;

    virtual void onInvoke() KZ_OVERRIDE;
    virtual void onPrepareDelayedInvoke() KZ_OVERRIDE;
    virtual void onDelayedInvoke() KZ_OVERRIDE;

    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

    void onCopy(const DispatchMessageAction& other);

    virtual void setTarget(BindingSharedPtr, AbstractPropertyType targetArgument, PropertyField targetField) KZ_OVERRIDE;

private:

    /// Message type.
    AbstractMessageType m_messageType;
};

}

#endif
