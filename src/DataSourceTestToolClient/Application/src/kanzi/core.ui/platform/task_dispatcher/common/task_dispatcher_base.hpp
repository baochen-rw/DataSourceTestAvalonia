// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TASK_DISPATCHER_BASE_HPP
#define KZ_TASK_DISPATCHER_BASE_HPP

#include <kanzi/core/legacy/thread/kzs_thread.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

// Forward declarations.
class TaskDispatcherBaseImpl;
class MainLoopTaskProfilerRegistry;

/// Base class for TaskDispatcher implementation.
class KANZI_API TaskDispatcherBase
{
public:

    /// Task is a callback that is dispatched by TaskDispatcher and executed on a specific UI thread.
    typedef function<void()> Task;

    /// Submits a task.
    /// The task will be dispatched to and executed on the UI thread that this task dispatcher belongs to.
    /// You can call this function from any thread.
    void submit(Task task);

    /// Executes the tasks that have been dispatched to the UI thread.
    /// Kanzi calls this function automatically.
    /// This function can only be called from the UI thread that this dispatcher belongs to.
    /// Tasks will be removed after execution.
    /// New tasks added during the execution will not be executed.
    /// \return Number of tasks that were executed.
    size_t executeTasks();

    /// Clean up tasks until no tasks remain.
    /// Sets the quitting flag, that the tasks can use to check if new tasks should be posted.
    void cleanupTasks();

    /// Notifies this class that tasks are available.
    /// This is an internal function.
    virtual void notifyTasksAvailable() = 0;

    /// Notifies this class that tasks have been consumed.
    /// This is an internal function.
    virtual void notifyTasksConsumed() = 0;

    /// Setter for profiler registry
    /// \param profiler Reference to a MainLoopTaskProfilerRegistry
    void setProfilerRegistry(MainLoopTaskProfilerRegistry& profiler);

    /// Indicates whether the task dispatcher is quitting.
    /// This flag is set before the emptying of the task queue begins.
    /// \return True if quitting, false if not.
    bool isQuitting() const;
    /// Set the quitting flag state.
    /// Called by the system before emptying the task dispatcher.
    /// \param flag New quitting flag state.
    void setQuitting(bool flag);

protected:

    /// Constructor.
    explicit TaskDispatcherBase();

    /// Destructor.
    virtual ~TaskDispatcherBase();

private:

    TaskDispatcherBase(const TaskDispatcherBase&) KZ_DELETED_FUNCTION;
    TaskDispatcherBase& operator=(const TaskDispatcherBase&) KZ_DELETED_FUNCTION;

    /// Pointer to implementation.
    /// Needed because including <mutex> is not possible from CLR. Implementation class can hide it.
    unique_ptr<TaskDispatcherBaseImpl> m_impl;
};

}

#endif
