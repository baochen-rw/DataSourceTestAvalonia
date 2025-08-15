// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAIN_LOOP_TASK_PROFILER_SAMPLE_HPP
#define KZ_MAIN_LOOP_TASK_PROFILER_SAMPLE_HPP

#include <kanzi/core/profiling/interval_profiler_sample.hpp>

namespace kanzi
{

/// \ingroup Profiling
/// \{

/// The main loop task profiler data sample.
///
/// Use \ref ProfilingMacros to profile main loop tasks.
///
/// This structure extends #IntervalProfilerSampleData with main loop counter value. Use this structure to profile main loop tasks when
/// you want to identify each sample with the value of the main loop counter at the time the sample was collected.
/// To profile the execution time of the main loop task create a sample object of #MainLoopTaskProfilerSampleData structure
/// and call the #start() method at the beginning of the task. At the end of the task call #stop() and
/// pass the sample to the #MainLoopTaskProfiler object.
struct KANZI_API MainLoopTaskProfilerSampleData : public IntervalProfilerSampleData
{
    /// Use this constructor when you need to initialize main loop counter with custom value.
    /// \param mainLoopCounter Initial main loop counter value. 
    explicit MainLoopTaskProfilerSampleData(chrono::high_resolution_clock::time_point startPoint, chrono::nanoseconds timeSpent, size_t counter) :
        IntervalProfilerSampleData(startPoint, timeSpent), m_mainLoopCounter(counter)
    {
    }

    /// Main loop counter value.
    ///
    /// Note that the value is not constant because it can be set after the sample object is created.
    size_t m_mainLoopCounter;
};

/// The main loop task profiling sampler collects interval measurement to produce #MainLoopTaskProfilerSampleData sample.
///
/// The #ProfilingScopeHelper uses sampler class to measure time spent executing scope which is profiled.
/// For detailed information on how the sampler is used in scope profiling, refer to #ProfilingScopeHelper.
class KANZI_API MainLoopTaskProfilingSampler : public IntervalProfilingSampler
{
public:

    /// Constructor.
    ///
    /// Initializes main loop counter to include it into #MainLoopTaskProfilerSampleData sample.
    ///
    /// \param counter The main loop counter.
    explicit MainLoopTaskProfilingSampler(size_t counter) : m_counter(counter)
    {
    }

    /// Returns #MainLoopTaskProfilerSampleData sample including interval measurement data and main loop counter.
    ///
    /// \return The main loop task profiling sample.
    MainLoopTaskProfilerSampleData getSampleData()
    {
        return MainLoopTaskProfilerSampleData(m_startTimePoint, m_endTimePoint - m_startTimePoint, m_counter);
    }

private:

    /// The main loop counter.
    const size_t m_counter;
};

/// \}

}

#endif
