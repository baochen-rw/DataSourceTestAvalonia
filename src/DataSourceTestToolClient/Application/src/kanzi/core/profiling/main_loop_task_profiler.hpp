// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAIN_LOOP_TASK_PROFILER_HPP
#define KZ_MAIN_LOOP_TASK_PROFILER_HPP

#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/profiling/interval_profiler_sample_statistics.hpp>
#include <kanzi/core/profiling/main_loop_profiler_sample.hpp>
#include <kanzi/core/profiling/abstract_value_profiler.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>

namespace kanzi
{

// Forward declaration.
class MainLoopTaskProfiler;

/// \ingroup Profiling
/// The main loop task profiler shared pointer type.
typedef shared_ptr<MainLoopTaskProfiler> MainLoopTaskProfilerSharedPtr;

/// \ingroup Profiling
/// Profiles the execution time of main loop tasks.
///
/// The main loop task profiler collects samples of type MainLoopTaskProfilerSampleData, which include information about interval duration, start point, and main loop counter
/// identifying the main loop iteration when the interval was measured.
///
/// For details on the information included in the sample, see MainLoopTaskProfilerSampleData. For an example of 
/// how the profiling sample is collected in main loop task profiling, see MainLoopTaskProfilingSampler.
///
/// The MainLoopTaskProfilerSampleData keeps samples in a circular sample buffer. Every time a new sample is added to the profiler, the statistics data 
/// is updated. To access the statistics data, use #getProfilingStatistics().
class KANZI_API MainLoopTaskProfiler : public AbstractValueProfiler<MainLoopTaskProfilerSampleData, IntervalProfilerSampleStatistics>
{
public:

    /// The typedef of the base value profiler class.
    typedef AbstractValueProfiler<MainLoopTaskProfilerSampleData, IntervalProfilerSampleStatistics> BaseValueProfiler;

    /// Creates a new main loop task profiler.
    ///
    /// \param name The name of the new profiler.
    /// \param category The profiling category assigned to the profiler.
    /// \param sampleBufferSize The maximum size of the profiling sample buffer.
    /// \return The unique pointer to the new profiler.
    static MainLoopTaskProfilerSharedPtr create(string_view name, const ProfilingCategory& category, size_t sampleBufferSize);

    /// Adds a new profiling data sample to the profiler.
    /// \param sample The profiling data sample.
    void addSample(MainLoopTaskProfilerSampleData sample);

    /// Resets sample data.
    ///
    /// Clears sample buffer and resets sample statistics.
    void resetSampleData();

    /// Accesses a profiling data sample stored in the sample buffer.
    ///
    /// \param index The index of the sample.
    /// \return The profiling data sample.
    const MainLoopTaskProfilerSampleData& getSample(size_t index) const
    {
        return BaseValueProfiler::getSample(index);
    }

    /// Gets a reference to main loop task profiling statistics.
    /// \return The reference to main loop task profiling statistics.
    const IntervalProfilerSampleStatistics& getProfilingStatistics() const
    {
        return m_aggregateProfilingData;
    }

protected:
    /// Constructor.
    /// \param name The name of the profiler.
    /// \param category The category assigned to the profiler.
    /// \param sampleBufferSize The maximum size of the sample buffer.
    explicit MainLoopTaskProfiler(string_view name, const ProfilingCategory& category, size_t sampleBufferSize);

    /// Deleted copy constructor, preventing copying of the object.
    explicit MainLoopTaskProfiler(const MainLoopTaskProfiler& rhs) KZ_DELETED_FUNCTION;

    /// Deleted assignment operator, preventing assignment of the object.
    MainLoopTaskProfiler& operator=(const MainLoopTaskProfiler& rhs) KZ_DELETED_FUNCTION;

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

    /// The override of AbstractProfiler::getAggregateDataFieldValueOverride().
    /// \param fieldIndex The index of the aggregate profiling data field.
    /// \return The value of the aggregate profiling data field.
    virtual Value getAggregateDataFieldValueOverride(size_t fieldIndex) const KZ_OVERRIDE;

    /// The override of AbstractProfiler::getSampleFieldValueOverride().
    /// \param sampleIndex The index of the profiling data sample.
    /// \param fieldIndex The index of the profiling data sample field.
    /// \return The value of the profiling data sample field.
    virtual Value getSampleFieldValueOverride(size_t sampleIndex, size_t fieldIndex) const KZ_OVERRIDE;
};

}
#endif
