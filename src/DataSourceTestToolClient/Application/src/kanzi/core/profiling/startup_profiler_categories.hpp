// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STARTUP_PROFILER_CATEGORIES_HPP
#define KZ_STARTUP_PROFILER_CATEGORIES_HPP

#include <kanzi/core/profiling/profiling.hpp>

/// \defgroup StartupProfiling Startup profiling

/// \ingroup Profiling StartupProfiling
/// \{

/// Kanzi uses this category internally to profile loading plugins at startup.
#define KZ_PROFILING_STARTUP_LOAD_PLUGINS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupLoadPlugins", 1)

/// Kanzi uses this category internally to profile metadata registration at startup.
#define KZ_PROFILING_STARTUP_REGISTER_METADATA kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupRegisterMetadata", 1)

/// Kanzi uses this category internally to profile application initialization at startup.
#define KZ_PROFILING_STARTUP_INITIALIZATION kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupInitialization", 1)

/// Kanzi uses this category internally to profile graphics initialization at startup.
#define KZ_PROFILING_STARTUP_INITIALIZE_GRAPHICS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupInitializeGraphics", 1)

/// Kanzi uses this category internally to profile startup GL initialization.
#define KZ_PROFILING_STARTUP_INITIALIZE_GL kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupInitializeGL", 1)

/// Kanzi uses this category internally to profile prefab loading at startup.
#define KZ_PROFILING_STARTUP_LOAD_PREFAB kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupLoadPrefab", 1)

/// Kanzi uses this category internally to profile prefab instantiation at startup.
#define KZ_PROFILING_STARTUP_INSTANTIATE_PREFAB kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupInstantiatePrefab", 1)

/// Kanzi uses this category internally to profile default resource registration at startup.
#define KZ_PROFILING_STARTUP_REGISTER_DEFAULT_RESOURCES kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupRegisterDefaultResources", 1)

/// Kanzi uses this category internally to profile prefab attach at startup.
#define KZ_PROFILING_STARTUP_ATTACH_PREFAB kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupAttachPrefab", 1)

/// Kanzi uses this category internally to profile renderer reset at startup.
#define KZ_PROFILING_STARTUP_RESET_RENDERER kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupResetRenderer", 1)

/// Kanzi uses this category internally to profile threads initialization at startup.
#define KZ_PROFILING_STARTUP_INITIALIZE_LOADING_THREADS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupInitializeLoadingThreads", 1)

/// Kanzi uses this category internally to profile runtime assets registration at startup.
#define KZ_PROFILING_STARTUP_REGISTER_RUNTIME_ASSETS kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupRegisterRuntimeAssets", 1)

/// Kanzi uses this category internally to profile KZB(s) opening at startup.
#define KZ_PROFILING_STARTUP_OPEN_KZB kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupOpenKzb", KZ_PROFILING_DEFAULT_SAMPLE_BUFFER_SIZE)

/// Kanzi uses this category internally to profile domain creation at startup.
#define KZ_PROFILING_STARTUP_CREATE_DOMAIN kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupCreateDomain", 1)

/// Kanzi uses this category internally to profile onProjectLoaded call at startup.
#define KZ_PROFILING_STARTUP_ON_PROJECT_LOADED kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupOnProjectLoaded", 1)

/// Kanzi uses this category internally to profile ResumeGL at startup.
#define KZ_PROFILING_STARTUP_RESUME_GL kzProfilingCreateCategory(KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(KZ_PROFILING_ENABLED_CATEGORY), "StartupResumeGL", 1)

/// \}

#ifndef KANZI_DOXYGEN

// Registration of profiling categories above.
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_LOAD_PLUGINS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_REGISTER_METADATA, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_INITIALIZATION, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_INITIALIZE_GRAPHICS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_INITIALIZE_GL, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_LOAD_PREFAB, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_INSTANTIATE_PREFAB, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_REGISTER_DEFAULT_RESOURCES, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_ATTACH_PREFAB, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_RESET_RENDERER, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_INITIALIZE_LOADING_THREADS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_REGISTER_RUNTIME_ASSETS, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_OPEN_KZB, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_CREATE_DOMAIN, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_ON_PROJECT_LOADED, KZ_PROFILING_ENABLED_CATEGORY)
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_STARTUP_RESUME_GL, KZ_PROFILING_ENABLED_CATEGORY)

#endif

#endif
