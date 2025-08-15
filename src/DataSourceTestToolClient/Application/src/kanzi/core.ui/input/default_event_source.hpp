// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_DEFAULT_EVENT_SOURCE_HPP
#define KZ_DEFAULT_EVENT_SOURCE_HPP

#include <kanzi/core/cpp/optional.hpp>

#include <kanzi/core.ui/input/event_source.hpp>
#include <kanzi/core.ui/input/event_filter.hpp>
#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>


struct KzsDesktop;
struct KzsInputDevice;

namespace kanzi
{

class KANZI_API DefaultEventSource : public EventSource
{
public:
    /// Constructor.
    explicit DefaultEventSource(struct KzsDesktop* desktop, const EventSourceProperties& properties);

    /// Destructor.
    virtual ~DefaultEventSource();

    virtual void gatherEvents(struct KzsEventQueue& queue) KZ_OVERRIDE;

    virtual optional<NativeEventHandle> getEventHandle() KZ_OVERRIDE;

protected:
    struct KzsInputDevice* m_device;              ///< Actual input device.
    EventFilter m_eventFilter;                    ///< Filter for input events.
};

}

#endif
