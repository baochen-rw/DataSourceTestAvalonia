// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_CONTEXT_HPP
#define KZ_RESOURCE_PROFILING_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_profiling_attributes.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/variant.hpp>
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{
// Forward class declaration.
class ResourceProfilingContext;

// Unique pointer to resource profiling context.
typedef shared_ptr<ResourceProfilingContext> ResourceProfilingContextSharedPtr;

/// \ingroup ResourceProfiling
/// The resource profiling context.
///
/// The resource profiling context represents a scope that executes code path which at some point triggers resource
/// loading or deployment. Only resource profiling context samplers create resource profiling contexts. A sampler 
/// creates a context only when the execution of the scope where the sampler is defined triggers resource loading or
/// deployment. For example, when the ResourceManager::acquireResource() function is called for a resource that is 
/// already loaded and deployed, the sampler does not create a context.
///
/// To create a resource profiling context sampler call the #kzResourceProfilingContextSampler() macro in the scope
/// where you want to create the sampler. See ResourceProfilingContextFactory::AbstractSampler.
///
/// The scope where you define the resource profiling context sampler may execute code path that triggers the execution
/// of another scope for which you also defined a resource profiling sampler context. For example, scope A for which 
/// you defined the sampler samplerA executes code path which triggers the execution of scope B for which you defined 
/// the sampler samplerB. If the code path in scope B triggers resource loading or deployment, SamplerB creates a
/// resource profiling context which is a dependency context for the context created by SamplerA. To get all dependency
/// contexts for a specific resource profiling context use the #getDependencyContexts() function.
///
/// The duration of a resource profiling context is equal to the duration of the resource loading or deployment 
/// triggered by the execution of the corresponding scope. Scope execution may trigger the loading or deployment of
/// multiple resources.
///
/// In scopes where resources are loaded and deployed Kanzi creates samplers for the corresponding loading and
/// deployment contexts kanzi::ResourceProfilingLoadContext and kanzi::ResourceProfilingDeployContext.
class KANZI_API ResourceProfilingContext
{
public:
    /// The duration type.
    typedef chrono::nanoseconds Duration;

    /// The timepoint type.
    typedef chrono::high_resolution_clock::time_point TimePoint;

    /// The timestamp.
    typedef Duration TimeStamp;

    /// The resource profiling context container.
    typedef vector<ResourceProfilingContextSharedPtr> ResourceProfilingContextContainer;

    /// Destructor.
    virtual ~ResourceProfilingContext();

    /// Adds a dependency context.
    ///
    /// To get all dependency contexts use the #getDependencyContexts() function.
    ///
    /// \param context The dependency context.
    /// \see #getDependencyContexts()
    void addDependencyContext(ResourceProfilingContextSharedPtr context);

    /// Retrieves the attributes of the context.
    ///
    /// The attributes object you pass with the \p attributes parameter is filled out with attributes of this context.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    void getAttributes(ResourceProfilingAttributes& attributes) const;


    /// Gets the current timestamp.
    ///
    /// Every invocation of this function returns a timestamp greater than or equal to the values previously returned 
    /// by this function.
    ///
    /// \return The current timestamp.
    static TimeStamp getCurrentTimeStamp();

    /// Gets the current timepoint.
    ///
    /// The timepoint is returned by high-resolution timer.
    ///
    /// \return The current timepoint.
    static TimePoint getCurrentTimePoint();

    /// Gets dependency contexts container.
    ///
    /// \return The container of the dependency contexts.
    const ResourceProfilingContextContainer& getDependencyContexts() const
    {
        return m_dependencyContexts;
    }

    /// Gets the unique identifier of the context.
    ///
    /// Use the identifier to tell apart contexts of the same type.
    ///
    /// \return The unique identifier of the context.
    uint64_t getID() const;

    /// Gets the entry timestamp of the context.
    ///
    /// The timestamp is calculated at entry to the scope where the context is created. The value is deduced from 
    /// incrementing high-resolution timer. If context A is created before context B, the timestamp of A is less than
    /// or equal to the timestamp of B.
    ///
    /// \return The measurement timestamp.
    TimeStamp getEntryTimeStamp() const
    {
        return m_entryTimeStamp;
    }

    /// Records exit timestamp on the context.
    void recordExitTimeStamp();

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The resource profiling context entry timestamp.
    /// \see #getEntryTimeStamp()
    explicit ResourceProfilingContext(TimeStamp entryTimeStamp) :
        m_entryTimeStamp(entryTimeStamp),
        m_exitTimeStamp(0),
        m_dependenciesDuration(0)
    {
    }

    /// Gets the total duration of all dependency contexts.
    ///
    /// \return The total duration of all dependency contexts.
    Duration getDependenciesDuration() const
    {
        return m_dependenciesDuration;
    }

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// \see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const;

    /// Gets the duration of the context.
    ///
    /// The duration of the context is the sum of the duration of resource loading and deployment that occurred in the
    /// scope of this context and the dependency contexts.
    ///
    /// \return The duration of the context.
    virtual Duration getDurationOverride() const
    {
        return getDependenciesDuration();
    }

private:
    /// The timestamp evaluated at entry to the resource profiling context scope.
    Duration m_entryTimeStamp;

    /// The timestamp evaluated at exit from the resource profiling context scope.
    Duration m_exitTimeStamp;

    /// The total duration of dependency contexts.
    Duration m_dependenciesDuration;

    /// The dependency contexts.
    ResourceProfilingContextContainer m_dependencyContexts;
};
}

#endif
#endif
