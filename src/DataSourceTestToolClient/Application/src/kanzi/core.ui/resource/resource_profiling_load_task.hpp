// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_LOAD_TASK_HPP
#define KZ_RESOURCE_PROFILING_LOAD_TASK_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core.ui/resource/resource_profiling_data_sample.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/legacy/thread/kzs_thread.hpp>

namespace kanzi
{

// Forward declaration.
class ResourceProfilingLoadTask;

/// Profiled load task shared pointer type.
typedef shared_ptr<ResourceProfilingLoadTask> ProfiledLoadTaskSharedPtr;

/// \ingroup ResourceProfiling
/// Resource profiling wrapper for load task
///
/// Use this wrapper to measure the time that the loading task spends loading and deploying resources.
/// The wrapper derives from ResourceManager::LoadTask and implements the load task interface.
/// The original loading task object is passed to the constructor of this class and stored in \p m_loadTask.
/// The #loadFunction() and #finishFunction() functions call the corresponding functions of the original object
/// and measure the execution time which is then passed to the corresponding resource profiling contexts.
class ResourceProfilingLoadTask : public ResourceManager::LoadTask
{
public:
    /// Creates a new resource profiling load task.
    ///
    /// \param profilingDataSample The profiling data sample.
    /// \param loadTask The original load task.
    static ProfiledLoadTaskSharedPtr wrapTask(ResourceProfilingDataSampleSharedPtr profilingDataSample, ResourceManager::LoadTaskSharedPtr loadTask)
    {
        ProfiledLoadTaskSharedPtr task(new ResourceProfilingLoadTask(profilingDataSample, loadTask));
        return task;
    }

    /// Calls loadFunction() of the \p m_loadTask object and measures its execution time.
    ///
    /// \param context The context of the loading thread.
    virtual void loadFunction(const ResourceLoaderThreadContext* context) KZ_OVERRIDE;

    /// Calls finishFunction() of the \p m_loadTask object and measures its execution time.
    ///
    /// \param context The context of the deploying thread.
    virtual void finishFunction(const ResourceLoaderThreadContext* context) KZ_OVERRIDE;

    /// Gets the deployed resource.
    ///
    /// \return The deployed resource.
    virtual ResourceSharedPtr getResult() KZ_OVERRIDE;

private:
    /// Constructor.
    ///
    /// \param profilingDataSample The profiling data sample.
    /// \param loadTask The original load task.
    explicit ResourceProfilingLoadTask(ResourceProfilingDataSampleSharedPtr profilingDataSample, ResourceManager::LoadTaskSharedPtr profiledLoadTask);

    /// The profiling data sample.
    ResourceProfilingDataSampleSharedPtr m_profilingDataSample;

    /// The original load task.
    ResourceManager::LoadTaskSharedPtr m_loadTask;

    /// The deployed resource.
    ResourceSharedPtr m_loadedResource;
};
}

#endif
#endif
