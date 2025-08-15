// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_DATA_SAMPLE_HPP
#define KZ_RESOURCE_PROFILING_DATA_SAMPLE_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_profiling_context.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>

namespace kanzi
{
/// Forward class declaration.
class ResourceProfilingDataSample;

/// Profiled resource shared pointer type.
typedef shared_ptr<ResourceProfilingDataSample> ResourceProfilingDataSampleSharedPtr;

/// \ingroup ResourceProfiling
/// The resource profiling data sample.
class KANZI_API ResourceProfilingDataSample
{
public:
    /// The resource factory.
    class KANZI_API Factory
    {
    public:
        /// The profiled resource container type.
        typedef unordered_set<ResourceProfilingDataSampleSharedPtr> ResourceProfilingDataSampleContainer;

        /// Creates a resource profiling data sample.
        ///
        /// \param acquireContext The acquire context of the resource.
        /// \param url The URL of the profiled resource.
        ResourceProfilingDataSampleSharedPtr createResourceProfilingDataSample(ResourceProfilingContextSharedPtr acquireContext, string_view url);

        /// Gets the created profiled resource container.
        ///
        /// \return The created profiled resource container.
        const ResourceProfilingDataSampleContainer& getResourceProfilingDataSamples() const;

        /// Resets all profiling data.
        void resetProfilingData();

    private:
        /// The profiled resource container.
        ResourceProfilingDataSampleContainer m_resources;
    };

    /// Gets the duration of resource loading.
    ///
    /// \return The duration of resource loading.
    ResourceProfilingContext::Duration getLoadingDuration() const;

    /// Gets the duration of resource deployment.
    ///
    /// \return The duration of resource deployment.
    ResourceProfilingContext::Duration getDeploymentDuration() const;

    /// Gets the URL of the profiled resource.
    ///
    /// \return The URL of the profiled resource.
    string getUrl() const;

    /// Gets the type of the profiled resource.
    ///
    /// \return The type of the profiled resource.
    /// \see #setResourceType()
    string getType() const;

    /// Gets the ID of the profiled resource.
    ///
    /// \return The ID of the profiled resource.
    uint64_t getID() const;

    /// Gets the loading status of the profiled resource.
    ///
    /// \return The loading status of the profiled resource.
    bool getSuccess() const;

    /// Adds to the resource profiling data sample the duration of resource loading and the loading context.
    ///
    /// \param loadingContext The loading context.
    /// \param duration The loading duration.
    /// \see #getLoadingContext(), #getLoadingDuration()
    void addLoadingDuration(ResourceProfilingContextSharedPtr loadingContext, ResourceProfilingContext::Duration duration);

    /// Adds to the resource profiling data sample the duration of resource deployment and the deployment context.
    ///
    /// \param deploymentContext The deployment context.
    /// \param duration The deployment duration.
    /// \see #getDeploymentContext(), #getDeploymentDuration()
    void addDeploymentDuration(ResourceProfilingContextSharedPtr deploymentContext, ResourceProfilingContext::Duration duration);

    /// Sets the type of the profiled resource.
    ///
    /// \param type The type of the profiled resource.
    /// \see #getType()
    void setResourceType(string_view type);

    /// Sets the loading status of the profiled resource.
    ///
    /// \param type The loading status of the profiled resource.
    /// \see #getSuccess()
    void setSuccess(bool success);

    /// Gets the acquire resource context.
    ///
    /// \return The acquire resource context.
    const ResourceProfilingContext* getAcquireContext() const
    {
        return m_acquireContext.get();
    }

    /// Gets the loading context.
    ///
    /// \return The loading context.
    const ResourceProfilingContext* getLoadingContext() const
    {
        return m_loadingContext.get();
    }

    /// Gets the deployment context.
    ///
    /// \return The deployment context.
    const ResourceProfilingContext* getDeploymentContext() const
    {
        return m_deploymentContext.get();
    }

    /// Gets the attributes of the profiled resource.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the profiled resource.
    void getAttributes(ResourceProfilingAttributes& attributes) const;

protected:
    /// Constructor.
    ///
    /// \param acquireContext The acquire context.
    /// \param url The URL of the profiled context.
    explicit ResourceProfilingDataSample(ResourceProfilingContextSharedPtr acquireContext, string_view url);

private:
    /// The acquire context.
    ResourceProfilingContextSharedPtr m_acquireContext;

    /// The loading context.
    ResourceProfilingContextSharedPtr m_loadingContext;

    /// The deployment context.
    ResourceProfilingContextSharedPtr m_deploymentContext;

    /// The loading duration.
    ResourceProfilingContext::Duration m_loadingDuration;

    /// The deployment duration.
    ResourceProfilingContext::Duration m_deploymentDuration;

    /// The URL of the profiled resource.
    string m_url;

    /// The type of the profiled resource.
    string m_resourceType;

    /// The loading status of the profiled resource. True: success, False: failure
    bool m_success;
};
}

#endif
#endif
