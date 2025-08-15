// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SUSPENSION_MANAGER_HPP
#define KZ_SUSPENSION_MANAGER_HPP


#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/log/log_category.hpp>

#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>


/// Logging category for suspension.
#define KZ_LOG_CATEGORY_SUSPEND KZ_LOG_CREATE_CATEGORY(KZ_LOG_DISABLED_CATEGORY, "suspend")

namespace kanzi
{

/// Suspension manager implements logic for suspending the UI thread when there is no input, tasks or timed events.
/// This is a class used internally by Application.
class SuspensionManager
{
public:

    /// Constructor.
    explicit SuspensionManager();

    /// Destructor.
    ~SuspensionManager();

    /// Sets the native event handle that is used in waiting for task dispatcher.
    void setTaskDispatcherEventHandle(NativeEventHandle nativeHandle)
    {
        m_taskDispatcherEventHandle = nativeHandle;
    }

    /// Sets the native event handle that is used in waiting for input.
    void setInputEventHandle(NativeEventHandle nativeHandle)
    {
        m_inputEventHandle = nativeHandle;
    }    

    /// Checks if an event source needs polling.
    /// Polling is needed when an event source does not have the capability to abort suspension.
    /// \return True, when at least one event source needs polling.
    bool needsPolling() const
    {
        return needsPollingOverride();
    }

    /// Suspends the UI thread until any of the following conditions are met:
    /// - Input is available.
    /// - Native windowing system messages are available.
    /// - Tasks in the TaskScheduler of this thread are available.
    /// - Timeout expires.
    /// \param timeout Optional maximum suspend time.
    void suspend(optional<chrono::milliseconds> timeout)
    {
        suspendOverride(timeout);
    }

    /// Yields priority to other processes and threads for given amount of milliseconds.
    /// \param timeout Number of milliseconds to sleep. Sleeping for 0 milliseconds or returns immediately.
    void yield(chrono::milliseconds timeout)
    {
        yieldOverride(timeout);
    }

private:

    /// Platform-specific implementation of #suspend().
    /// \param timeout Optional maximum suspend time.
    void suspendOverride(optional<chrono::milliseconds> timeout);

    /// Platform-specific implementation of #yield()
    /// \param timeout Sleep time.
    void yieldOverride(chrono::milliseconds timeout);

    /// Platform-specific implementation of #needsPolling()
    bool needsPollingOverride() const;
    
        /// The native event handle that is used in waiting for task dispatcher.
    NativeEventHandle m_taskDispatcherEventHandle;
    /// The native event handle that is used in waiting for input.
    NativeEventHandle m_inputEventHandle;

    /// Suspend invocation counter for debugging purposes.
    unsigned int m_suspendCounter;
};

}

#endif
