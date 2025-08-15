// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILER_REGISTRATION_HELPER_HPP
#define KZ_PROFILER_REGISTRATION_HELPER_HPP

#include <kanzi/core/profiling/abstract_profiler.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>

namespace kanzi
{
namespace detail
{

/// Registered profiler instance.
/// Do not use this structure directly. \ref ProfilingMacros use it internally for profiling.
///
/// This template structure encapsulates shared pointer to the arbitrary profiler. It is used
/// to create object of the profiler class and register it within the profiler registry in single expression.
/// This is used in \ref ProfilingMacros when profiling scope or function to create local static objects of the profiler.
template <typename TProfiler>
struct ProfilerRegistrationHelper
{
    /// The profiler shared pointer type.
    typedef shared_ptr<TProfiler> ProfilerSharedPtr;

    /// Constructor.
    ///
    /// Registers new profiler withing profiler registry provided by you through \p registry.
    /// The shared pointer to the profiler is kept in stucture and is accessible through #m_profiler.
    ///
    /// \param registry The reference to the profiler registry where to add \p profiler.
    /// \param profiler The shared pointer to the profiler to add to new registry.
    template<typename TRegistryType>
    explicit ProfilerRegistrationHelper(TRegistryType& registry, ProfilerSharedPtr profiler) : m_profiler(profiler)
    {
        registry.registerProfiler(m_profiler);
    }

    /// The registered profiler.
    ProfilerSharedPtr m_profiler;
};

}
}
#endif
