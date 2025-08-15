// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_EVENT_SOURCE_HPP
#define KZ_EVENT_SOURCE_HPP

#include <kanzi/core/cpp/platform.hpp>

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/optional.hpp>

#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>


// Forward declarations
struct KzsEventQueue;

namespace kanzi
{

class EventSource;


typedef shared_ptr<EventSource> EventSourceSharedPtr;


/// EventSource class.
///
/// Base class for event sources.
class KANZI_API EventSource
{
public:
    /// Constructor.
    explicit EventSource();

    /// Destructor.
    virtual ~EventSource();

    /// Fills the given event queue with events received so far.
    ///
    /// \param queue Event queue to be filled. Do not clear or assume to be empty.
    virtual void gatherEvents(struct KzsEventQueue& queue);

    /// Returns a waitable event handle for this event source, if available.
    virtual optional<NativeEventHandle> getEventHandle()
    {
        return optional<NativeEventHandle>();
    }
};

}

#endif
