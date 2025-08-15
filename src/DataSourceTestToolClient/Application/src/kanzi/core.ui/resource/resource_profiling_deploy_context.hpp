// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_DEPLOY_CONTEXT_HPP
#define KZ_RESOURCE_PROFILING_DEPLOY_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/named_resource_profiling_context.hpp>
#include <kanzi/core.ui/resource/resource_profiling_data_sample.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// The profiling context of resource deployment.
class KANZI_API ResourceProfilingDeployContext : public NamedResourceProfilingContext
{
public:
    /// The context sampler.
    class KANZI_API Sampler : public ResourceProfilingContextFactory::AbstractSampler
    {
    public:
        /// Constructor.
        ///
        /// \param factory The sampler factory.
        /// \param profiledResource The profiled resource related to this context.
        explicit Sampler(ResourceProfilingContextFactory& factory, ResourceProfilingDataSampleSharedPtr profiledResource);

    protected:
        /// Creates a new resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(TimeStamp entryTimeStamp) KZ_OVERRIDE;

    private:
        /// The profiled resource.
        const ResourceProfilingDataSampleSharedPtr m_profiledResource;
    };

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param profiledResource The profiled resource.
    explicit ResourceProfilingDeployContext(TimeStamp entryTimeStamp, ResourceProfilingDataSampleSharedPtr profiledResource);

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// \see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const KZ_OVERRIDE;

    /// Gets the duration of the context.
    ///
    /// The duration of the context is the sum of the duration of resource loading and deployment that occurred in the
    /// scope of this context and the dependency contexts.
    ///
    /// \return The duration of the context.
    virtual Duration getDurationOverride() const KZ_OVERRIDE;

private:
    /// Profiled resource.
    ResourceProfilingDataSampleSharedPtr m_profiledResource;
};
}

#endif
#endif
