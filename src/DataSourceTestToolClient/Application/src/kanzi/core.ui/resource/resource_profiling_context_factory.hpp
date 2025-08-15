// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_CONTEXT_FACTORY_HPP
#define KZ_RESOURCE_PROFILING_CONTEXT_FACTORY_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

/// Do not use this macro. To create a new resource profiling context sampler use #kzResourceProfilingContextSampler().
///
/// \param className The class name of the context sampler.
/// \param localVariable The name of the local variable which holds the object of the sampler class.
/// \param constructorArguments The arguments which you must pass to the constructor of the sampler. Enclose the arguments in parentheses.
/// \see #kzResourceProfilingContextSampler()
#define KZ_DETAIL_RESOURCE_PROFILING_CONTEXT_SAMPLER(className, localVariable, constructorArguments) className localVariable constructorArguments

/// \ingroup ResourceProfiling
/// Creates a new resource profiling context sampler.
///
/// Call this macro in the scope in which you want to create a new resource profiling context sampler.
/// This macro produces no code if #KZ_PROFILING_RESOURCE_LOADING_CATEGORY profiling category is disabled at compile-time.
///
/// \param className The class name of the context sampler.
/// \param localVariable The name of the local variable which holds the object of the sampler class.
/// \param constructorArguments The arguments which you must pass to the constructor of the sampler. Enclose the arguments in parentheses.
/// \see kanzi::ResourceProfilingContext, kanzi::ResourceProfilingContextFactory
///
/// Example
/// -------
/// To create resource profiling samplers.
/// \snippet snippets_resource_profiling.cpp Resource profiling contexts and samplers usage
#define kzResourceProfilingContextSampler(className, localVariable, constructorArguments) KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED(KZ_PROFILING_RESOURCE_LOADING_CATEGORY, KZ_DETAIL_RESOURCE_PROFILING_CONTEXT_SAMPLER(className, localVariable, constructorArguments))

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_profiling_context.hpp>

namespace kanzi
{

// Forward declaration
class ResourceProfilingContextFactory;

/// The resource profiling context factory unique pointer type.
typedef unique_ptr<ResourceProfilingContextFactory> ResourceProfilingContextFactoryUniquePtr;

/// \ingroup ResourceProfiling
/// Resource profiling context factory.
class KANZI_API ResourceProfilingContextFactory
{
public:
    /// Abstract resource profiling context sampler.
    ///
    /// Base class for all context samplers. To create a sampler call the #kzResourceProfilingContextSampler() macro
    /// inside the scope which may trigger loading or deployment of resources during its execution. If the resource
    /// loading or deployment occurs during the execution of the scope, the sampler creates the corresponding context.
    ///
    /// \see #kzResourceProfilingContextSampler()
    class KANZI_API AbstractSampler
    {
    public:
        /// The constructor.
        ///
        /// \param factory The resource profiling context factory.
        explicit AbstractSampler(ResourceProfilingContextFactory& factory);

        /// Destructor.
        virtual ~AbstractSampler();

        /// Gets the resource profiling context created by this sampler.
        ///
        /// When this function is called for the first time, it creates the resource profiling context using the 
        /// #createContextOverride() function.
        ///
        /// \return The resource profiling context created by this sampler.
        /// \see #createContextOverride()
        ResourceProfilingContextSharedPtr getContext();

    private:
        /// Creates a resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        ResourceProfilingContextSharedPtr createContext(ResourceProfilingContext::TimeStamp entryTimeStamp)
        {
            return createContextOverride(entryTimeStamp);
        }

    protected:
        /// Creates a resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(ResourceProfilingContext::TimeStamp entryTimeStamp) = 0;

    private:
        /// The resource profiling context factory.
        ResourceProfilingContextFactory& m_factory;

        /// The resource profiling context created by this sampler.
        ResourceProfilingContextSharedPtr m_context;

        /// Flag indicating if profiling is enabled.
        const bool m_profilingEnabled;

        /// The scope entry timestamp.
        ResourceProfilingContext::TimeStamp m_entryTimeStamp;
    };

    /// Profiled resource container.
    typedef vector<ResourceProfilingContextSharedPtr> ProfiledResourceContextContainer;

    /// Gets the top-level contexts.
    ///
    /// \return Top-level contexts container.
    const ProfiledResourceContextContainer& getTopLevelContexts() const;

    /// Resets all profiling data.
    void resetProfilingData();

private:
    /// Pushes sampler to the top of the sampler stack.
    void push(AbstractSampler& sampler);

    /// Pops context sampler from the top of the sampler stack.
    void pop();

    /// Returns top of the context sampler's stack.
    AbstractSampler* top();

    /// Adds a new top-level context.
    ///
    /// \param context The new top-level context.
    void addTopLevelContext(ResourceProfilingContextSharedPtr context);

private:
    /// The top-level resource profiling contexts.
    ProfiledResourceContextContainer m_topLevelContexts;

    /// The stack of the samplers.
    vector<AbstractSampler*> m_samplerStack;
};
}

#endif
#endif