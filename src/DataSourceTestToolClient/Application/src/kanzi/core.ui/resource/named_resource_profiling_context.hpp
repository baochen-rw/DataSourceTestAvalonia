// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NAMED_RESOURCE_PROFILING_CONTEXT_HPP
#define KZ_NAMED_RESOURCE_PROFILING_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// Named resource profiling context.
class KANZI_API NamedResourceProfilingContext : public ResourceProfilingContext
{
public:
    /// The context sampler.
    class KANZI_API Sampler : public ResourceProfilingContextFactory::AbstractSampler
    {
    public:
        /// Constructor.
        ///
        /// \param factory The sampler factory.
        /// \param name The name of the context.
        explicit Sampler(ResourceProfilingContextFactory& factory, string_view name);

    protected:
        /// Creates a new resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(TimeStamp entryTimeStamp) KZ_OVERRIDE;

    private:
        /// The name of the context being created.
        string m_name;
    };

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param profiledResource The profiled resource.
    explicit NamedResourceProfilingContext(TimeStamp entryTimeStamp, KZ_RV_REF(string) name);

    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param profiledResource The profiled resource.
    explicit NamedResourceProfilingContext(TimeStamp entryTimeStamp, string_view name);

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// \see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const KZ_OVERRIDE;

    /// The name of the context.
    string m_name;
};
}

#endif
#endif
