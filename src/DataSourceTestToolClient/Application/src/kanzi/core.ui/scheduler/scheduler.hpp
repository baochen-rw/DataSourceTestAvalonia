// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SCHEDULER_HPP
#define KZ_SCHEDULER_HPP

#include <kanzi/core/cpp/platform.hpp>

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/utility.hpp>


namespace kanzi
{

class MainLoopTaskProfilerRegistry;

/// Scheduler class.
///
/// Represents an ordered set of tasks.
class KANZI_API Scheduler
{
public:

    /// Type for scheduled tasks.
    typedef function<void()> Task;

    // constructor
    explicit Scheduler();

    /// Submits a task for one-shot execution.
    /// \param name The name of the task. Establishes the task execution order.
    /// \param task The task to submit.
    /// \return True, if this function did not replace an existing task.
    bool submitTask(string_view name, Task task);

    /// Submits a task for recurring execution.
    /// \param name The name of the task. Establishes the task execution order.
    /// \param task The task to submit.
    /// \return True, if this function did not replace an existing task.
    bool insertRecurringTask(string_view name, Task task);

    /// Immediately removes a task from the scheduler.
    /// A task may not remove itself.
    /// \param name The name of the task to remove.
    /// \return True, if a task was removed.
    bool removeTask(string_view name);

    /// Removes a task from the scheduler after its execution (next or current) ends.
    /// \param name The name of the task to remove.
    /// \return True, if a task was marked for removal.
    bool removeTaskAfterExecution(string_view name);

    /// Executes all tasks in ascending alphabetical order and removes non-recurring tasks after their execution.
    /// Removal of tasks may be interleaved with execution of other tasks.
    void executeTasks();

    /// Prints the tasks to the log.
    void debugPrintTasks() const;

    /// Setter for profiler registry
    /// \param profiler Reference to a MainLoopTaskProfilerRegistry
    void setProfilerRegistry(MainLoopTaskProfilerRegistry& profiler);

private:
    typedef map<string, pair<bool, Task> > TaskMap;
    typedef pair<TaskMap::iterator, bool> WasKeyAbsent;

    TaskMap m_tasks;

    MainLoopTaskProfilerRegistry* m_profilerRegistry;
};

}


#endif
