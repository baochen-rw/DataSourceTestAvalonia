// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAIN_LOOP_TASK_PROFILER_REGISTRY_HPP
#define KZ_MAIN_LOOP_TASK_PROFILER_REGISTRY_HPP

#include <kanzi/core/profiling/main_loop_task_profiler.hpp>
#include <kanzi/core/profiling/main_loop_task_profiler_categories.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>

namespace kanzi
{

// Forward declaration.
class MainLoopTaskProfilerRegistry;

/// \ingroup Profiling MainLoopTaskProfiling
/// The main loop task profiler registry unique ptr type.
typedef unique_ptr<MainLoopTaskProfilerRegistry> MainLoopTaskProfilerRegistryUniquePtr;

/// \ingroup Profiling MainLoopTaskProfiling
/// The registry of main loop task profilers.
class MainLoopTaskProfilerRegistry : public ProfilerRegistry<MainLoopTaskProfiler>
{
public:
    /// Constructor.
    explicit MainLoopTaskProfilerRegistry() : m_mainLoopCounter(0)
    {
    }

    void initialize(optional<size_t> bufferSizeOverride)
    {

#ifdef KANZI_PROFILING_BUILD

        size_t bufferSize = bufferSizeOverride.value_or(KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE);

        m_animationProfiler = MainLoopTaskProfiler::create("Main loop: animation", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_ANIMATION), bufferSize);
        registerProfiler(m_animationProfiler);

        m_renderingProfiler = MainLoopTaskProfiler::create("Main loop: rendering", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_RENDERING), bufferSize);
        registerProfiler(m_renderingProfiler);

        m_applicationEventsProfiler = MainLoopTaskProfiler::create("Main loop: application events", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_APPLICATION_EVENTS), bufferSize);
        registerProfiler(m_applicationEventsProfiler);

        m_appUpdateProfiler = MainLoopTaskProfiler::create("Main loop: application update", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_APP_UPDATE), bufferSize);
        registerProfiler(m_appUpdateProfiler);

        m_resourceDeploymentProfiler = MainLoopTaskProfiler::create("Main loop: resource deployment", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_RESOURCE_DEPLOYMENT), bufferSize);
        registerProfiler(m_resourceDeploymentProfiler);

        m_graphicsEventsProfiler = MainLoopTaskProfiler::create("Main loop: graphics events", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_GRAPHICS_EVENTS), bufferSize);
        registerProfiler(m_graphicsEventsProfiler);

        m_inputProfiler = MainLoopTaskProfiler::create("Main loop: input", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_INPUT), bufferSize);
        registerProfiler(m_inputProfiler);

        m_userUpdateProfiler = MainLoopTaskProfiler::create("Main loop: user update", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_USER_UPDATE), bufferSize);
        registerProfiler(m_userUpdateProfiler);

        m_resourceManagerUpdateProfiler = MainLoopTaskProfiler::create("Main loop: resource manager update", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_RESOURCE_MANAGER_UPDATE), bufferSize);
        registerProfiler(m_resourceManagerUpdateProfiler);

        m_taskDispatcherProfiler = MainLoopTaskProfiler::create("Main loop: task dispatcher", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TASK_DISPATCHER), bufferSize);
        registerProfiler(m_taskDispatcherProfiler);

        m_taskSchedulerProfiler = MainLoopTaskProfiler::create("Main loop: task scheduler", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER), bufferSize);
        registerProfiler(m_taskSchedulerProfiler);

        m_layoutProfiler = MainLoopTaskProfiler::create("Main loop: layout", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_LAYOUT), bufferSize);
        registerProfiler(m_layoutProfiler);

        m_screenLayoutProfiler = MainLoopTaskProfiler::create("Main loop: screen layout", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_SCREEN_LAYOUT), bufferSize);
        registerProfiler(m_screenLayoutProfiler);

        m_screenExtractProfiler = MainLoopTaskProfiler::create("Main loop: screen extract", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_SCREEN_EXTRACT), bufferSize);
        registerProfiler(m_screenExtractProfiler);

        m_hudProfiler = MainLoopTaskProfiler::create("Main loop: HUD", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_HUD), bufferSize);
        registerProfiler(m_hudProfiler);

        m_taskSchedulerInternalProfiler = MainLoopTaskProfiler::create("Main loop: task scheduler internal", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER_INTERNAL), bufferSize);
        registerProfiler(m_taskSchedulerInternalProfiler);

        m_taskExecutionInternalProfiler = MainLoopTaskProfiler::create("Main loop: task execution internal", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TASK_EXECUTION_INTERNAL), bufferSize);
        registerProfiler(m_taskExecutionInternalProfiler);

        m_taskDispatchProfiler = MainLoopTaskProfiler::create("Main loop: task dispatch", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TASK_DISPATCH), bufferSize);
        registerProfiler(m_taskDispatchProfiler);

        m_timerProfiler = MainLoopTaskProfiler::create("Main loop: timer", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_TIMER), bufferSize);
        registerProfiler(m_timerProfiler);

        m_presentProfiler = MainLoopTaskProfiler::create("Main loop: present", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_PRESENT), bufferSize);
        registerProfiler(m_presentProfiler);

        m_yieldProfiler = MainLoopTaskProfiler::create("Main loop: yield", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_YIELD), bufferSize);
        registerProfiler(m_yieldProfiler);

        m_suspendProfiler = MainLoopTaskProfiler::create("Main loop: suspend", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_SUSPEND), bufferSize);
        registerProfiler(m_suspendProfiler);

        m_frameProfiler = MainLoopTaskProfiler::create("Main loop: frame", kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_MAIN_LOOP_FRAME), bufferSize);
        registerProfiler(m_frameProfiler);

#endif

        KZ_MAYBE_UNUSED(bufferSizeOverride);

    }

    /// To get the value of the main loop counter, use getMainLoopCounter().
    size_t getMainLoopCounter() const
    {
        return m_mainLoopCounter;
    }

    /// Increments the main loop counter.
    ///
    /// Do not use this function directly. The Kanzi main loop calls it internally.
    void incrementMainLoopCounter()
    {
        ++m_mainLoopCounter;
    }

#ifdef KANZI_PROFILING_BUILD

    /// Main loop animation profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent rendering animation.
    ///
    /// \see TimelinePlayback
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_animationProfiler;

    /// Main loop rendering profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent rendering the screen in Application::renderOverride().
    ///
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_renderingProfiler;

    /// Main loop application events profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent gathering and handling events from all available event sources, such as keyboard, mouse, and other available manipulators.
    /// 
    /// \see EventSource
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_applicationEventsProfiler;

    /// Main loop application update profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent inside the user-provided Application::update() override.
    ///
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_appUpdateProfiler;

    /// Main loop resource deployment profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent processing asynchronous task deployment queue.
    /// 
    /// \see Application::progressDeploymentQueue()
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_resourceDeploymentProfiler;

    /// Main loop graphics events profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent processing events that affect graphics output, such as #KZS_EVENT_WINDOW_RESIZED and #KZS_EVENT_WINDOW_RESIZE_REQUESTED.
    /// 
    /// \see GraphicsOutput, KzsEventType
    /// \note The profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_graphicsEventsProfiler;

    /// Main loop input profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent by InputManager in processing various input events, including input events from keyboard and mouse.
    /// 
    /// \see InputManager::processEvents()
    /// \note Available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_inputProfiler;

    /// The user update profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing user-provided update logic callback Application::onUpdate().
    ///
    /// \note Available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_userUpdateProfiler;

    /// Main loop resource manager update profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time consumed by the resource manager to process load and deployment queues.
    /// 
    /// \see ResourceManager::update()
    /// \note Available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_resourceManagerUpdateProfiler;

    /// Main loop task dispatcher profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing tasks added to KzuTaskScheduler.
    /// 
    /// \see TaskDispatcherBase::executeTasks()
    /// \note Available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_taskDispatcherProfiler;

    /// Main loop task scheduler profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing periodic tasks added to TaskDispatcher, including animation.
    /// 
    /// \see kzuTaskSchedulerExecuteAllTasks()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_taskSchedulerProfiler;

    /// Main loop layout profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the performance of the layout pass.
    /// 
    /// \see Application::update2()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_layoutProfiler;

    /// Main loop screen layout profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the performance of the screen layout.
    ///
    /// \see Node2D, Node2D::layout()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_screenLayoutProfiler;

    /// Main loop screen extract profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the performance of the screen extract.
    ///
    /// \see Node2D, Node2D::extract()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_screenExtractProfiler;

    /// Main loop HUD profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the overhead caused by rendering the HUD information.
    ///
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_hudProfiler;

    /// Main loop internal task scheduler profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing periodic tasks added to Scheduler
    ///
    /// \see Scheduler::executeTasks()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_taskSchedulerInternalProfiler;

    /// Main loop internal task execution profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing individual tasks added to Scheduler
    ///
    /// \see Scheduler::executeTasks()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_taskExecutionInternalProfiler;

    /// Main loop task dispatch profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing an individual task added to KzuTaskScheduler.
    ///
    /// \see kzuTaskSchedulerExecuteAllTasks()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_taskDispatchProfiler;

    /// Main loop timer profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent executing timer callbacks.
    ///
    /// \see kzuMessageDispatcherDispatchQueuedMessages()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_timerProfiler;

    /// Main loop present profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent presenting graphics output
    ///
    /// \see GraphicsOutput::present()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_presentProfiler;

    /// Main loop yield profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent yielded
    ///
    /// \see Application::yield()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_yieldProfiler;

    /// Main loop suspend profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the time spent suspended
    ///
    /// \see Application::suspend()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_suspendProfiler;

    /// Main loop frame profiler.
    ///
    /// On every Kanzi main loop iteration, the profiler measures the total time spent per frame
    ///
    /// \see Application::runOverride()
    /// \note This profiler is available in \ref TheKanziProfilingBuild only.
    MainLoopTaskProfilerSharedPtr m_frameProfiler;

#endif

private:
    /// Main loop counter.
    size_t m_mainLoopCounter;
};

}

#endif
