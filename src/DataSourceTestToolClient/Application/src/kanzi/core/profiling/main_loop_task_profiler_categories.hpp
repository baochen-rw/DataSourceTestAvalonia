// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAIN_LOOP_TASK_PROFILER_CATEGORIES_HPP
#define KZ_MAIN_LOOP_TASK_PROFILER_CATEGORIES_HPP

#include <kanzi/core/profiling/profiling.hpp>

/// \defgroup MainLoopTaskProfiling Main loop task profiling

/// \ingroup Profiling MainLoopTaskProfiling
/// \{

/// Kanzi uses this category internally for buffer count of the Main Loop profilers
#define KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE 1024

/// Kanzi uses this category internally in the Main Loop Task to profile animation.
#define KZ_PROFILING_MAIN_LOOP_ANIMATION kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopAnimation", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile rendering.
#define KZ_PROFILING_MAIN_LOOP_RENDERING kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopRendering", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile application events handling.
#define KZ_PROFILING_MAIN_LOOP_APPLICATION_EVENTS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopApplicationEvents", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile #Application::update().
#define KZ_PROFILING_MAIN_LOOP_APP_UPDATE kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopAppUpdate", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile resource deployment.
#define KZ_PROFILING_MAIN_LOOP_RESOURCE_DEPLOYMENT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopResourceDeployment", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile graphics events handling.
#define KZ_PROFILING_MAIN_LOOP_GRAPHICS_EVENTS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopGraphicsEvents", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile input events handling.
#define KZ_PROFILING_MAIN_LOOP_INPUT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopInput", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile #Application::onUpdate().
#define KZ_PROFILING_MAIN_LOOP_USER_UPDATE kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopUserUpdate", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile resource manager update.
#define KZ_PROFILING_MAIN_LOOP_RESOURCE_MANAGER_UPDATE kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopResourceManagerUpdate", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile task dispatcher.
#define KZ_PROFILING_MAIN_LOOP_TASK_DISPATCHER kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTaskDispatcher", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile task scheduler.
#define KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTaskScheduler", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile layout.
#define KZ_PROFILING_MAIN_LOOP_LAYOUT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopLayout", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile screen layout.
#define KZ_PROFILING_MAIN_LOOP_SCREEN_LAYOUT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopScreenLayout", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile screen extract.
#define KZ_PROFILING_MAIN_LOOP_SCREEN_EXTRACT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopScreenExtract", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile HUD.
#define KZ_PROFILING_MAIN_LOOP_HUD kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopHUD", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile Internal Scheduler Tasks.
#define KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER_INTERNAL kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTaskSchedulerInternal", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile individual Internal Scheduler Task execution.
#define KZ_PROFILING_MAIN_LOOP_TASK_EXECUTION_INTERNAL kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTaskSchedulerInternalExecute", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile individual Task Dispatcher execution.
#define KZ_PROFILING_MAIN_LOOP_TASK_DISPATCH kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTaskDispatch", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile timer processing.
#define KZ_PROFILING_MAIN_LOOP_TIMER kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopTimer", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile graphics output presentation
#define KZ_PROFILING_MAIN_LOOP_PRESENT kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopPresent", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile yield
#define KZ_PROFILING_MAIN_LOOP_YIELD kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopYield", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile suspend
#define KZ_PROFILING_MAIN_LOOP_SUSPEND kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopSuspend", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// Kanzi uses this category internally in the Main Loop Task to profile frame
#define KZ_PROFILING_MAIN_LOOP_FRAME kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "MainLoopFrame", KZ_PROFILING_MAIN_LOOP_DEFAULT_BUFFER_SIZE)

/// \}

#ifndef KANZI_DOXYGEN

// Registration of categories above.
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_ANIMATION, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_RENDERING, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_APPLICATION_EVENTS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_APP_UPDATE, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_RESOURCE_DEPLOYMENT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_GRAPHICS_EVENTS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_INPUT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_USER_UPDATE, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_RESOURCE_MANAGER_UPDATE, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TASK_DISPATCHER, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_LAYOUT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_SCREEN_LAYOUT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_SCREEN_EXTRACT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_HUD, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TASK_SCHEDULER_INTERNAL, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TASK_EXECUTION_INTERNAL, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TASK_DISPATCH, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_TIMER, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_PRESENT, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_YIELD, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_SUSPEND, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_MAIN_LOOP_FRAME, KZ_PROFILING_ENABLED_CATEGORY)

#endif

#endif
