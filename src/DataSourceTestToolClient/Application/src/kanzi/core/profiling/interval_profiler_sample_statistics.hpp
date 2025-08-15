// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTERVAL_PROFILER_SAMPLE_STATISTICS_HPP
#define KZ_INTERVAL_PROFILER_SAMPLE_STATISTICS_HPP

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/profiling/interval_profiler_sample.hpp>

namespace kanzi
{

/// \ingroup Profiling
/// \{

/// Interval profiler sample statistics.
struct KANZI_API IntervalProfilerSampleStatistics
{
    /// Constructor.
    explicit IntervalProfilerSampleStatistics() :
        m_totalDuration(chrono::nanoseconds::zero()),
        m_longestInterval(chrono::nanoseconds::zero()),
        m_shortestInterval(chrono::nanoseconds::max()),
        m_numIntervals(0)
    {
    }

    /// Calculates the average duration of the interval.
    chrono::nanoseconds calculateAverage() const
    {
        if (m_numIntervals == 0)
        {
            return chrono::nanoseconds::zero();
        }

        return m_totalDuration / m_numIntervals;
    }

    /// The total duration of all intervals.
    chrono::nanoseconds m_totalDuration;
    
    /// The longest interval.
    chrono::nanoseconds m_longestInterval;

    /// The shortest interval.
    chrono::nanoseconds m_shortestInterval;

    /// Total number of intervals measured.
    uint64_t m_numIntervals;
};

/// \}

}

#endif
