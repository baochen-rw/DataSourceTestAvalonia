// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAIN_LOOP_RESOURCE_PROFILING_CONTEXT_HPP
#define KZ_MAIN_LOOP_RESOURCE_PROFILING_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/named_resource_profiling_context.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// The main loop resource profiling context.
class KANZI_API ResourceProfilingMainLoopContext : public NamedResourceProfilingContext
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
        explicit Sampler(ResourceProfilingContextFactory& stack, size_t mainLoopCounter);

    protected:
        /// Creates a new resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(TimeStamp entryTimeStamp) KZ_OVERRIDE;

    private:
        /// The main loop counter.
        const size_t m_mainLoopCounter;
    };

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param mainLoopCounter The main loop counter.
    explicit ResourceProfilingMainLoopContext(TimeStamp entryTimeStamp, size_t mainLoopCounter);

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// \see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const KZ_OVERRIDE;

private:
    /// The main loop counter.
    const size_t m_mainLoopCounter;
};
}

#endif
#endif
