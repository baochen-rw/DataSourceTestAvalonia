// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EVENT_HPP
#define KZ_EVENT_HPP

#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>
#include <kanzi/core/cpp/platform.hpp>


namespace kanzi
{

namespace detail
{

/// Event object.
/// Represents an event in either signaled or non-signaled state.
/// The signaled state allows a thread waiting on the native event handle to proceed.
/// When used from different threads, signaling changes need to be externally synchronized.
class Event
{
public:
    /// Constructor.
    /// Creates an event in non-signaled state.
    explicit Event();

    /// Destructor.
    ~Event();

    /// Sets event to signaled state.
    void signal();

    /// Sets event to non-signaled state.
    void clear();

    /// Returns native event handle for this event.
    NativeEventHandle getNativeEventHandle() const;

private:
    Event(const Event&) KZ_DELETED_FUNCTION;
    Event& operator=(const Event&) KZ_DELETED_FUNCTION;

    /// Win32 implementation signals using event object.
    NativeEventHandle m_event;
};

}

}

#endif
