// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DEFAULT_PROFILER_REGISTRY_HPP
#define KZ_DEFAULT_PROFILER_REGISTRY_HPP

#include <kanzi/core/profiling/abstract_profiler.hpp>

namespace kanzi
{

/// \ingroup Profiling
/// The default profiler registry placeholder.
/// 
/// Use DefaultProfilerRegistry to access the default profiler registry instance.
class KANZI_API DefaultProfilerRegistry
{
public:

    /// Sets the default profiler registry to custom profiler registry.
    /// \param profiler New defaut profiler.
    void setProfilerRegistry(AbstractProfilerRegistry* registry)
    {
        m_customProfilerRegistry = registry;
    }

    /// Resets the default profiler registry to the original value.
    void resetToDefaultProfiler()
    {
        m_customProfilerRegistry = 0;
    }

    /// Gets the default profiler registry instance.
    /// \return The default profiler registry instance.
    AbstractProfilerRegistry& getProfilerRegistry()
    {
        return m_customProfilerRegistry ? *m_customProfilerRegistry : m_defaultProfilerRegistry;
    }

    /// Gets the reference to singleton instance of DefaultProfilerRegistry.
    /// \return The reference to singleton instance of DefaultProfilerRegistry.
    static DefaultProfilerRegistry& get();

private:

    /// Private constructor prevents creation of the object outside of class methods scope.
    explicit DefaultProfilerRegistry();

    /// Private copy constructor prevents copying of the object.
    explicit DefaultProfilerRegistry(const DefaultProfilerRegistry&) KZ_DELETED_FUNCTION;

    /// Private assignment operator prevents assignment of the object.
    DefaultProfilerRegistry& operator = (const DefaultProfilerRegistry&) KZ_DELETED_FUNCTION;

    /// Destructor.
    virtual ~DefaultProfilerRegistry();

private:

    /// The reference to the custom profiler registry.
    AbstractProfilerRegistry* m_customProfilerRegistry;

    /// The default profiler registry.
    AbstractProfilerRegistry m_defaultProfilerRegistry;
};

}

#endif
