// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_ON_ATTACHED_TRIGGER_H
#define KZU_ON_ATTACHED_TRIGGER_H

#include "trigger.hpp"


namespace kanzi
{

class OnAttachedTrigger;
typedef shared_ptr<OnAttachedTrigger> OnAttachedTriggerSharedPtr;

/** On Attached Trigger. */
class KANZI_API OnAttachedTrigger : public Trigger
{
public:

    KZ_METACLASS_BEGIN(OnAttachedTrigger, Trigger, "Kanzi.OnAttachedTrigger")
    KZ_METACLASS_END()

    static OnAttachedTriggerSharedPtr create(Domain* domain, string_view name);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    explicit OnAttachedTrigger(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
};

}


#endif
