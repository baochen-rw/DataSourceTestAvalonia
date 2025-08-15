// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_ACQUIRE_CONTEXT_HPP
#define KZ_RESOURCE_PROFILING_ACQUIRE_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/named_resource_profiling_context.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// The profiling context of resource acquirement.
class KANZI_API ResourceProfilingAcquireContext : public NamedResourceProfilingContext
{
public:
    /// The context sampler.
    class KANZI_API Sampler : public ResourceProfilingContextFactory::AbstractSampler
    {
    public:
        /// Constructor.
        ///
        /// \param factory The sampler factory.
        /// \param url The URL of the resource being acquired.
        /// \param async The asynchronous resource loading flag.
        explicit Sampler(ResourceProfilingContextFactory& stack, string_view url, bool async);

    protected:
        /// Creates a new resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(TimeStamp entryTimeStamp) KZ_OVERRIDE;

    private:
        /// The URL of the profiled resource.
        string m_url;

        /// Asynchronous resource loading flag.
        const bool m_async;
    };

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param url The URL of the resource being acquired.
    /// \param async The asynchronous resource loading flag.
    explicit ResourceProfilingAcquireContext(TimeStamp entryTimeStamp, KZ_RV_REF(string) url, bool async);

    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param url The URL of the resource being acquired.
    /// \param async The asynchronous resource loading flag.
    explicit ResourceProfilingAcquireContext(TimeStamp entryTimeStamp, string_view url, bool async);

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// For more details on context attributes, see #getAttributes().
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// \see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const KZ_OVERRIDE;

private:
    /// The URL of the profiled resource.
    string m_url;

    /// Asynchronous resource loading flag.
    const bool m_async;
};
}

#endif
#endif
