// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILER_HPP
#define KZ_RESOURCE_PROFILER_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>
#include <kanzi/core.ui/resource/resource_profiling_data_sample.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>

/// \defgroup ResourceProfiling Resource profiling
///
/// Use the resource profiling subsystem to measure during runtime how long it takes to load and deploy resources.
/// Resource profiling is available only in the \ref TheKanziProfilingBuild.

namespace kanzi
{

// Forward class declaration
class ResourceProfiler;

/// The resource profiler unique ptr type.
typedef unique_ptr<ResourceProfiler> ResourceProfilerUniquePtr;

/// \ingroup ResourceProfiling
/// The resource profiler.
class KANZI_API ResourceProfiler
{
public:
    /// The context factory container key.
    ///
    /// The key is a thread context of the loading thread for which the factory is created.
    typedef const ResourceLoaderThreadContext* ContextFactoryContainerKey;

    /// The context factory container type.
    typedef unordered_map<ContextFactoryContainerKey, ResourceProfilingContextFactoryUniquePtr> ContextFactoryContainer;

    /// Gets the container of context factories.
    ///
    /// \return The container of context factories.
    const ContextFactoryContainer& getResourceProfilingContexts() const;

    /// Gets a context factory.
    ///
    /// \param key The key of the factory to return.
    ResourceProfilingContextFactory& getContextFactory(ContextFactoryContainerKey key);

    /// Gets the main thread context factory.
    ///
    /// \return The main thread context factory.
    ResourceProfilingContextFactory& getMainThreadContextFactory();

    /// Creates a context factory.
    ///
    /// \param key The key value for new factory.
    ResourceProfilingContextFactory& createContextFactory(ContextFactoryContainerKey key);

    /// Gets a resource profiling data sample factory.
    ///
    /// \return The resource profiling data sample factory.
    const ResourceProfilingDataSample::Factory& getResourceProfilingDataSampleFactory() const
    {
        return m_resourceFactory;
    }

    /// Creates a resource profiling data sample.
    ///
    /// \param acquireContext The acquire context of the profiled resource.
    /// \param url The URL of the profiled resource.
    /// \return The resource profiling data sample.
    ResourceProfilingDataSampleSharedPtr createResourceProfilingDataSample(ResourceProfilingContextSharedPtr acquireContext, string_view url)
    {
        return m_resourceFactory.createResourceProfilingDataSample(acquireContext, url);
    }

    /// Gets resource profiling data samples.
    ///
    /// \returns The resource profiling data samples container.
    const ResourceProfilingDataSample::Factory::ResourceProfilingDataSampleContainer& getResourceProfilingDataSamples() const
    {
        return m_resourceFactory.getResourceProfilingDataSamples();
    }

    /// Creates profiler singleton.
    ///
    /// \param mainThreadContext The main thread context.
    static ResourceProfilerUniquePtr createProfiler(ContextFactoryContainerKey mainThreadContext);

    /// Resets profiling data.
    void resetProfilingData();

private:
    /// Constructor.
    ///
    /// \param mainThreadContext The main thread context.
    explicit ResourceProfiler(ContextFactoryContainerKey mainThreadContext);

    /// Deleted copy constructor.
    ResourceProfiler(const ResourceProfiler&) KZ_DELETED_FUNCTION;

    /// Deleted assignment operator
    ResourceProfiler& operator=(const ResourceProfiler& copy) KZ_DELETED_FUNCTION;

private:
    /// The context factories, one factory for each loading thread.
    ContextFactoryContainer m_contextFactories;

    /// The main loading(rendering) thread factory.
    ResourceProfilingContextFactory* m_mainThreadFactory;

    /// The resource factory.
    ResourceProfilingDataSample::Factory m_resourceFactory;
};
}

#endif
#endif
