// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILER_REGISTRY_HPP
#define KZ_PROFILER_REGISTRY_HPP

#include <kanzi/core/core_api.hpp>

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>

namespace kanzi
{

/// \defgroup Profiling Profiling
///
/// This group of classes implements the profiling used internally by \ref ProfilingMacros.
/// Use \ref ProfilingMacros to instrument your code for execution time profiling.
///
/// \{

/// Profiler registry.
///
/// Use the profiler registry to store profilers. To get begin/end iterators to the profiler container, use #beginProfilers()/#endProfilers().
template<typename TProfiler>
class KANZI_CORE_TEMPLATE_API ProfilerRegistry
{
public:

    /// The profiler shared point type.
    typedef shared_ptr<TProfiler> ProfilerSharedPtr;

    /// The profiler container type.
    typedef unordered_set<ProfilerSharedPtr> ProfilerContainer;

    /// Adds a new profiler to the registry.
    /// \param profiler The #ProfilerSharedPtr pointing to the profiler being added.
    void registerProfiler(ProfilerSharedPtr profiler)
    {
        m_registeredProfilers.emplace(profiler);
    }

    /// Removes a profiler from the registry.
    /// \param profiler The #ProfilerSharedPtr pointing to the profiler being removed.
    void unregisterProfiler(ProfilerSharedPtr profiler)
    {
        typename ProfilerContainer::const_iterator pos = m_registeredProfilers.find(profiler);

        if (pos == cend(m_registeredProfilers))
        {
            return;
        }

        m_registeredProfilers.erase(profiler);
    }

    /// Gets iterator to the begging of the profiler container.
    /// \return The iterator to the begging of the profiler container.
    typename ProfilerContainer::const_iterator beginProfilers() const
    {
        return cbegin(m_registeredProfilers);
    }
    
    /// Gets iterator to the end of the profiler container.
    /// \return The iterator to the end of the profiler container.
    typename ProfilerContainer::const_iterator endProfilers() const
    {
        return cend(m_registeredProfilers);
    }

protected:

    /// The registered profilers.
    ProfilerContainer m_registeredProfilers;
};

/// \}

}
#endif
