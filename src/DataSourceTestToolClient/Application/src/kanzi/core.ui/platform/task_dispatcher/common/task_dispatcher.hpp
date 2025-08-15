// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TASK_DISPATCHER_HPP
#define KZ_TASK_DISPATCHER_HPP

#include <kanzi/core.ui/platform/task_dispatcher/common/task_dispatcher_base.hpp>
#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>
#include <kanzi/core.ui/platform/task_dispatcher/common/event.hpp>


namespace kanzi
{

/// Task dispatcher.
/// You can use TaskDispatcher to schedule execution of callbacks to the UI thread.
/// You can access Kanzi UI objects only on the thread that you create them on.
/// You can wrap code that accesses UI objects with tasks and submit them from any thread to the TaskDispatcher.
/// The UI thread will execute these tasks during its main loop.
class KANZI_API TaskDispatcher : public TaskDispatcherBase
{
public:

    /// Constructor.
    explicit TaskDispatcher()
    {
    }

    /// Returns the native handle that can be used to wait for available tasks.
    /// This is an internal function.
    NativeEventHandle getNativeEventHandle();

    /// TaskDispatcherBase::notifyTasksAvailable() implementation.
    virtual void notifyTasksAvailable() KZ_OVERRIDE;

    /// TaskDispatcherBase::notifyTasksConsumed() implementation.
    virtual void notifyTasksConsumed() KZ_OVERRIDE;

private:

    TaskDispatcher(const TaskDispatcher&) KZ_DELETED_FUNCTION;
    TaskDispatcher& operator=(const TaskDispatcher&) KZ_DELETED_FUNCTION;

    /// Waitable event.
    detail::Event m_event;
};

}

#endif
