// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_TIMER_TRIGGER_H
#define KZU_TIMER_TRIGGER_H

#include <kanzi/core/cpp/chrono.hpp>
#include "trigger.hpp"
#include <kanzi/core.ui/message/message_arguments.hpp>

namespace kanzi
{

class TimerTrigger;
typedef shared_ptr<TimerTrigger> TimerTriggerSharedPtr;

/** Timer Trigger. */
class KANZI_API TimerTrigger : public Trigger
{
public:

#include "timer_trigger_properties.h"

    KZ_METACLASS_BEGIN(TimerTrigger, Trigger, "Kanzi.TimerTrigger")
        KZ_METACLASS_PROPERTY_TYPE(IntervalProperty)
    KZ_METACLASS_END()

    chrono::milliseconds getInterval() const { return chrono::milliseconds(getProperty(IntervalProperty)); }
    void setInterval(chrono::milliseconds interval) { setProperty(IntervalProperty, static_cast<int>(interval.count())); }

    static TimerTriggerSharedPtr create(Domain* domain, string_view name)
    {
        return make_polymorphic_shared_ptr<Trigger>(new TimerTrigger(domain, name));
    }

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    explicit TimerTrigger(Domain* domain, string_view name);
    
    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;
    
    static kzsError timerHandler(MessageArguments* message, void* data);
};

}

#endif
