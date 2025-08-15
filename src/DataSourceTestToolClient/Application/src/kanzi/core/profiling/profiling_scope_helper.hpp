// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILING_SCOPE_HELPER_HPP
#define KZ_PROFILING_SCOPE_HELPER_HPP

#include <kanzi/core/core_api.hpp>
#include <kanzi/core/cpp/memory.hpp>

namespace kanzi
{

/// \ingroup Profiling
/// \{

/// The profiling scope helper.
///
/// Do not use this class directly. It is used internally by \ref ProfilingMacros.
///
/// The #ProfilingScopeHelper is used in scope profiling. The profiling macros (\ref ProfilingMacros) create a local variable
/// of #ProfilingScopeHelper to profile the execution time of the enclosing scope. For example, see #kzProfileScope(). 
///
/// Since the profiling helper variable is local to the profiled scope, ProfilingScopeHelper::ProfilingScopeHelper() constructor
/// is called every time the scope is entered. The destructor ProfilingScopeHelper::~ProfilingScopeHelper() is called just before
/// scope is left.
///
/// The sample data object passed to constructor ProfilingScopeHelper::ProfilingScopeHelper() collects sample data. The #ProfilingScopeHelper
/// calls sampler object methods to start and stop profiling, to collect sample data, and to pass the data to the profiler.
///
/// The constructor ProfilingScopeHelper::ProfilingScopeHelper() starts profiling the scope by calling the start() method of the sampler object.
/// The destructor ProfilingScopeHelper::~ProfilingScopeHelper() stops profiling the scope by calling the stop() method of the sampler object.
/// To get sample data the destructor ProfilingScopeHelper::~ProfilingScopeHelper() calls the getSampleData() method of the sampler object and adds that 
/// data to the profiler.
class KANZI_CORE_API ProfilingScopeHelper
{
public:
    /// The pointer to the template function instantiation for profiler and sampler types passed to the ProfilingScopeHelper::ProfilingScopeHelper().
    typedef void (*CollectSampleFunctionType)(void*, void*);

    /// Constructor.
    ///
    /// This constructor is called on entry to the scope, where local variable of #ProfilingScopeHelper is defined.
    /// The constructor initializes #m_collectFunction with pointer to #collectSample() instantiated
    /// with the \p profiler and \p sampler types. This function is used later in destructor on scope exit.
    /// The pointers to sampler and profiler are stored in #m_sampler and #m_profiler to pass these values to
    /// the #m_collectFunction in the destructor.
    ///
    /// If the profiling category assigned to the profiler is disabled then this constructor 
    /// does nothing and stores 0 pointer in m_collectFunction.
    ///
    /// \param profiler The profiler shared pointer to add samples to.
    /// \param sampler The sampler to collect sample data.
    template<typename TProfiler, typename TProfilingSampler>
    explicit ProfilingScopeHelper(const shared_ptr<TProfiler>& profiler, TProfilingSampler& sampler) :
        m_profiler(static_cast<void*>(profiler.get())), m_sampler(static_cast<void*>(&sampler)), m_collectFunction(0)
    {
        if (profiler->getCategory().isEnabled())
        {
            m_collectFunction = &collectSample<TProfiler, TProfilingSampler>;
            sampler.start();
        }
    }

    /// Destructor.
    ///
    /// This destructor is called on the exit from the scope, where local variable of #ProfilingScopeHelper is defined.
    /// The destructor calls #m_collectFunction with #m_profiler and #m_sampler to collect sample and add it to the profiler.
    ///
    /// If the #m_collectFunction is 0 this destructor does nothing.
    ~ProfilingScopeHelper()
    {
        if (m_collectFunction)
        {
            m_collectFunction(m_profiler, m_sampler);
        }
    }

private:
    /// Stops collecting sample data and adds collected sample to the profiler.
    ///
    /// \param profilerPtr The pointer to the profiler to add sample to.
    /// \param samplerPtr The pointer to the sampler which collects sample data.
    template<typename TProfiler, typename TProfilingSampler>
    static void collectSample(void* profilerPtr, void* samplerPtr)
    {
        TProfiler& profiler = *static_cast<TProfiler*>(profilerPtr);
        TProfilingSampler& sampler = *static_cast<TProfilingSampler*>(samplerPtr);

        sampler.stop();
        profiler.addSample(sampler.getSampleData());
    }

    /// The pointer to the profiler to add sample to.
    void* m_profiler;

    /// The pointer to the sampler, which collects sample data.
    void* m_sampler;

    /// The pointer to the #collectSample instantiated with types of profiler and sampler, or 0 if sample should not be collected.
    CollectSampleFunctionType m_collectFunction;
};

/// \}

}

#endif
