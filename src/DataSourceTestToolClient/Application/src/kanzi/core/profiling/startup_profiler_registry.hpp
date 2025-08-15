// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STARTUP_PROFILER_REGISTRY_HPP
#define KZ_STARTUP_PROFILER_REGISTRY_HPP

#include <kanzi/core/profiling/interval_profiler.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>
#include <kanzi/core/profiling/startup_profiler_categories.hpp>

namespace kanzi
{
// Forward declaraction
class StartupProfilerRegistry;

/// \ingroup Profiling StartupProfiling
/// The startup profiler registry unique ptr type.
typedef unique_ptr<StartupProfilerRegistry> StartupProfilerRegistryUniquePtr;

/// \ingroup Profiling StartupProfiling
/// The registry of startup profilers. Profilers in this class are available only in the \ref TheKanziProfilingBuild.
class StartupProfilerRegistry : public ProfilerRegistry<IntervalProfiler>
{
public:
    explicit StartupProfilerRegistry()
    {
#ifdef KANZI_PROFILING_BUILD
        m_loadPluginsProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_LOAD_PLUGINS), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_LOAD_PLUGINS), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_LOAD_PLUGINS));
        registerProfiler(m_loadPluginsProfiler);

        m_registerMetadataProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_REGISTER_METADATA), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_REGISTER_METADATA), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_REGISTER_METADATA));
        registerProfiler(m_registerMetadataProfiler);

        m_initializationProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_INITIALIZATION), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_INITIALIZATION), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_INITIALIZATION));
        registerProfiler(m_initializationProfiler);

        m_initializeGraphicsProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_INITIALIZE_GRAPHICS), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_INITIALIZE_GRAPHICS), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_INITIALIZE_GRAPHICS));
        registerProfiler(m_initializeGraphicsProfiler);

        m_initializeGLProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_INITIALIZE_GL), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_INITIALIZE_GL), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_INITIALIZE_GL));
        registerProfiler(m_initializeGLProfiler);

        m_loadPrefabProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_LOAD_PREFAB), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_LOAD_PREFAB), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_LOAD_PREFAB));
        registerProfiler(m_loadPrefabProfiler);

        m_instantiatePrefabProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_INSTANTIATE_PREFAB), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_INSTANTIATE_PREFAB), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_INSTANTIATE_PREFAB));
        registerProfiler(m_instantiatePrefabProfiler);

        m_registerDefaultResourcesProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_REGISTER_DEFAULT_RESOURCES), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_REGISTER_DEFAULT_RESOURCES), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_REGISTER_DEFAULT_RESOURCES));
        registerProfiler(m_registerDefaultResourcesProfiler);

        m_attachPrefabProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_ATTACH_PREFAB), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_ATTACH_PREFAB), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_ATTACH_PREFAB));
        registerProfiler(m_attachPrefabProfiler);

        m_resetRendererProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_RESET_RENDERER), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_RESET_RENDERER), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_RESET_RENDERER));
        registerProfiler(m_resetRendererProfiler);

        m_initializeLoadingThreadsProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_INITIALIZE_LOADING_THREADS), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_INITIALIZE_LOADING_THREADS), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_INITIALIZE_LOADING_THREADS));
        registerProfiler(m_initializeLoadingThreadsProfiler);

        m_registerRuntimeAssetsProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_REGISTER_RUNTIME_ASSETS), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_REGISTER_RUNTIME_ASSETS), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_REGISTER_RUNTIME_ASSETS));
        registerProfiler(m_registerRuntimeAssetsProfiler);

        m_openKzbProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_OPEN_KZB), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_OPEN_KZB), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_OPEN_KZB));
        registerProfiler(m_openKzbProfiler);

        m_createDomainProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_CREATE_DOMAIN), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_CREATE_DOMAIN), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_CREATE_DOMAIN));
        registerProfiler(m_createDomainProfiler);

        m_onProjectLoadedProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_ON_PROJECT_LOADED), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_ON_PROJECT_LOADED), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_ON_PROJECT_LOADED));
        registerProfiler(m_onProjectLoadedProfiler);

        m_resumeGLProfiler = IntervalProfiler::create(kzProfilingGetCategoryName(KZ_PROFILING_STARTUP_RESUME_GL), kzProfilingGetCategoryRuntimeReference(KZ_PROFILING_STARTUP_RESUME_GL), kzProfilingGetCategorySampleBufferSize(KZ_PROFILING_STARTUP_RESUME_GL));
        registerProfiler(m_resumeGLProfiler);
#endif
    }

#ifdef KANZI_PROFILING_BUILD

    /// Plugins loading profiler.
    ///
    /// On startup, measures the time used to load Kanzi Engine plugins.
    IntervalProfilerSharedPtr m_loadPluginsProfiler;

    /// Metadata registration profiler.
    ///
    /// On startup, the profiler measures the time used to register metadata.
    IntervalProfilerSharedPtr m_registerMetadataProfiler;

    /// Application initialization profiler.
    ///
    /// On startup, the profiler measures the time used to initialize an application.
    ///
    /// \see Application::initialize().
    IntervalProfilerSharedPtr m_initializationProfiler;

    /// Graphics initialization profiler.
    ///
    /// On startup, the profiler measures the time used to initialize the graphics stack.
    /// 
    /// \see GlGraphicsOutput.
    IntervalProfilerSharedPtr m_initializeGraphicsProfiler;

    /// Startup GL initialization profiler.
    ///
    /// On startup, the profiler measures the time used to initialize the graphics library.
    IntervalProfilerSharedPtr m_initializeGLProfiler;

    /// Default resource registration profiler.
    ///
    /// On startup, the profiler measures the time used to register the resource ids for the Kanzi default resources,
    /// such as BackgrounBrush, NullBrush, WhiteBrush, BlackBrush, and so on. This profiler measures only the amount of time it
    /// takes to register these resources, not the amount of time it takes to load these resources.
    ///
    /// \see registerDefaultResources().
    IntervalProfilerSharedPtr m_registerDefaultResourcesProfiler;

    /// Prefabs loading profiler.
    ///
    /// On startup, the profiler measures the time used to loading prefabs.
    ///
    /// \see PrefabTemplate.
    IntervalProfilerSharedPtr m_loadPrefabProfiler;

    /// Prefabs instantiation profiler.
    ///
    /// On startup, the profiler measures the time used to instantiate prefabs.
    ///
    /// \see PrefabTemplate.
    IntervalProfilerSharedPtr m_instantiatePrefabProfiler;

    /// Prefabs attachment profiler.
    ///
    /// On startup, the profiler measures the time used to attach prefabs to nodes.
    ///
    /// \see PrefabTemplate.
    IntervalProfilerSharedPtr m_attachPrefabProfiler;

    /// Renderer reset profiler.
    ///
    /// On startup, the profiler measures the time used by the Renderer3D::reset() method, which
    /// invalidates all the internal caches of the renderer for the GPU state.
    IntervalProfilerSharedPtr m_resetRendererProfiler;

    /// Loading threads initialization profiler.
    ///
    /// On startup, the profiler measures the time used to initialize loading threads.
    IntervalProfilerSharedPtr m_initializeLoadingThreadsProfiler;

    /// Runtime assets registration profiler.
    ///
    /// On startup, the profiler measures the time used to open the kzb file with the Kanzi runtime assets,
    /// which contains assets, such as the default shaders and materials for the default shaders.
    /// Kanzi runtime assets are embedded in the application executable. This profiler does not include the amount
    /// of time it takes to load these resources. Kanzi loads resources only when your application needs them.
    ///
    /// \see registerRuntimeAssets().
    IntervalProfilerSharedPtr m_registerRuntimeAssetsProfiler;

    /// Startup kzb file opening profiler.
    ///
    /// On startup, the profiler measures the time used to open the startup kzb file.
    IntervalProfilerSharedPtr m_openKzbProfiler;

    /// Domain creation profiler.
    ///
    /// On startup, the profiler measures the time used to create Domain
    IntervalProfilerSharedPtr m_createDomainProfiler;

    /// OnProjectLoaded profiler.
    ///
    /// On startup, the profiler measures the time used for OnProjectLoaded
    IntervalProfilerSharedPtr m_onProjectLoadedProfiler;

    /// ResumeGL profiler.
    ///
    /// On startup, the profiler measures the time used for ResumeGL
    IntervalProfilerSharedPtr m_resumeGLProfiler;

#endif

};

}
#endif
