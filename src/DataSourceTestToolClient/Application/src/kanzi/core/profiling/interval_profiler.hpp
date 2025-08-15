// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTERVAL_PROFILER_HPP
#define KZ_INTERVAL_PROFILER_HPP

#include <kanzi/core/profiling/interval_profiler_sample.hpp>
#include <kanzi/core/profiling/interval_profiler_sample_statistics.hpp>
#include <kanzi/core/profiling/abstract_value_profiler.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>

namespace kanzi
{

// Forward declaration.
class IntervalProfiler;

/// \addtogroup Profiling
/// \{

/// The shared pointer to the interval profiler.
typedef shared_ptr<IntervalProfiler> IntervalProfilerSharedPtr;

/// The interval profiler registry type.
typedef ProfilerRegistry<IntervalProfiler> IntervalProfilerRegistry;

/// The interval profiler.
///
/// Use \ref ProfilingMacros to profile codepath execution time.
///
/// The interval profiler collects samples of #IntervalProfilerSampleData type which include information about interval duration and start point.
/// For details on the information included in the sample, see #IntervalProfilerSampleData. 
/// For an example of how interval profiling sample is collected in scope profiling, see #IntervalProfilerSampler.
///
/// To add the collected sample to the profiler, use the #addSample() function.
///
/// The #IntervalProfiler keeps samples in a circular sample buffer. Whenever a new sample is added to the profiler, the statistics data 
/// is updated. To access the statistics data, use #getProfilingStatistics().
class KANZI_API IntervalProfiler : public AbstractValueProfiler<IntervalProfilerSampleData, IntervalProfilerSampleStatistics>
{
public:

    /// The typedef of the base value profiler class.
    typedef AbstractValueProfiler<IntervalProfilerSampleData, IntervalProfilerSampleStatistics> BaseValueProfiler;

    /// Creates a new interval profiler.
    ///
    /// \param name The name of the new profiler.
    /// \param category The profiling category assigned to the profiler.
    /// \param sampleBufferSize The maximum size of the profiling sample buffer.
    /// \return The #IntervalProfilerSharedPtr pointing to new profiler.
    static IntervalProfilerSharedPtr create(string_view name, const ProfilingCategory& category, size_t sampleBufferSize);

    /// Adds a new profiling data sample to the profiler.
    /// \param sample The profiling data sample.
    void addSample(IntervalProfilerSampleData sample);

    /// Accesses a profiling data sample stored in the sample buffer.
    ///
    /// \param index The index of the sample.
    /// \return The profiling data sample.
    const IntervalProfilerSampleData& getSample(size_t index) const
    {
        return BaseValueProfiler::getSample(index);
    }

    /// Gets a reference to interval profiling statistics.
    /// \return The reference to interval profiling statistics.
    const IntervalProfilerSampleStatistics& getProfilingStatistics() const
    {
        return m_aggregateProfilingData;
    }

protected:
    /// Constructor.
    /// \param name The name of the profiler.
    /// \param category The category assigned to the profiler.
    /// \param sampleBufferSize The maximum size of the sample buffer.
    explicit IntervalProfiler(string_view name, const ProfilingCategory& category, size_t sampleBufferSize);

    /// Deleted copy constructor, preventing copying of the object.
    explicit IntervalProfiler(const IntervalProfiler& rhs) KZ_DELETED_FUNCTION;

    /// Deleted assignment operator, preventing assignment of the object.
    IntervalProfiler& operator=(const IntervalProfiler& rhs) KZ_DELETED_FUNCTION;

    /// The override of AbstractProfiler::getAggregateDataFieldCountOverride().
    /// \return The number of aggregate data fields.
    virtual size_t getAggregateDataFieldCountOverride() const KZ_OVERRIDE;

    /// The override of AbstractProfiler::getAggregateDataFieldNameOverride().
    /// \param fieldIndex The index of the field.
    /// \return The number of aggregate data fields.
    virtual string getAggregateDataFieldNameOverride(size_t fieldIndex) const KZ_OVERRIDE;

    /// The override of AbstractProfiler::getSampleFieldCountOverride().
    /// \return The number of sample data fields.
    virtual size_t getSampleFieldCountOverride() const KZ_OVERRIDE;

    /// The override of AbstractProfiler::getSampleFieldNameOverride().
    /// \param fieldIndex The index of the sample field.
    /// \return The name of the sample field.
    virtual string getSampleFieldNameOverride(size_t fieldIndex) const KZ_OVERRIDE;

    /// The override of AbstractProfilerRegistry::getAggregateDataFieldValueOverride().
    /// \param fieldIndex The index of the aggregate profiling data field.
    /// \return The value of the aggregate profiling data field.
    virtual Value getAggregateDataFieldValueOverride(size_t fieldIndex) const KZ_OVERRIDE;

    /// The override of AbstractProfilerRegistry::getSampleFieldValueOverride().
    ///
    /// \param sampleIndex The index of the profiling data sample.
    /// \param fieldIndex The index of the profiling data sample field.
    /// \return The value of the profiling data sample field.
    virtual Value getSampleFieldValueOverride(size_t sampleIndex, size_t fieldIndex) const KZ_OVERRIDE;
};

/// \}

}

#endif
