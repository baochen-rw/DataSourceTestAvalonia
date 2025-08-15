// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTERVAL_PROFILER_SAMPLE_HPP
#define KZ_INTERVAL_PROFILER_SAMPLE_HPP

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// \addtogroup Profiling
/// \{

/// The interval profiler data sample.
///
/// Use \ref ProfilingMacros to profile codepath execution time.
///
/// This structure keeps interval measurement data. Use this structure together with IntervalProfiler to profile the execution time of arbitrary codepaths.
/// To profile the execution time of a codepath create a sample object of type #IntervalProfilerSampleData
/// and call the #start() method in the beginning of the codepath. At the end of the codepath call #stop() and
/// pass the sample to the IntervalProfiler object.
struct KANZI_API IntervalProfilerSampleData
{
    /// Constructor.
    ///
    /// \param startTimePoint The point in time when measurement started.
    /// \param duration The interval duration.
    explicit IntervalProfilerSampleData(chrono::high_resolution_clock::time_point startTimePoint, chrono::nanoseconds duration) :
        m_startTimePoint(startTimePoint), m_duration(duration)
    {
    }

    /// The point in time when interval measurement started.
    chrono::high_resolution_clock::time_point m_startTimePoint;

    /// The duration of the interval.
    chrono::nanoseconds m_duration;
};

/// The main loop task profiling sampler collects interval measurement to produce IntervalProfilerSampleData sample.
///
/// The ProfilingScopeHelper uses sampler class to measure time spent executing scope which is profiled.
///
/// For information on how the sampler is used in scope profiling, See ProfilingScopeHelper.
class KANZI_API IntervalProfilingSampler
{
public:

    /// Starts measuring time interval duration
    void start()
    {
        m_startTimePoint = chrono::high_resolution_clock::now();
    }

    /// Finishes measuring time interval duration
    void stop()
    {
        m_endTimePoint = chrono::high_resolution_clock::now();
    }

    /// Returns IntervalProfilerSampleData sample including interval measurement data.
    ///
    /// \return The interval measurement sample.
    IntervalProfilerSampleData getSampleData()
    {
        return IntervalProfilerSampleData(m_startTimePoint, m_endTimePoint - m_startTimePoint);
    }

protected:

    /// The point in time when interval measurement started.
    chrono::high_resolution_clock::time_point m_startTimePoint;

    /// The point in time when interval measurement finished.
    chrono::high_resolution_clock::time_point m_endTimePoint;
};

/// \}

}

#endif
