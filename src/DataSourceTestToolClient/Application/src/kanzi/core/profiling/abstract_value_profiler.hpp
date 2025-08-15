// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_VALUE_PROFILER_HPP
#define KZ_ABSTRACT_VALUE_PROFILER_HPP

#include <kanzi/core/profiling/abstract_profiler.hpp>

#include <kanzi/core/cpp/functional.hpp>

namespace kanzi
{

/// \ingroup Profiling
/// \{

/// Abstract value profiler.
///
/// Derive from AbstractValueProfiler to implement your own profiler which uses a circular buffer to store profiling samples.
///
/// The AbstractValueProfiler is a template class which stores profiling data samples of arbitrary type
/// in a circular sample buffer. When the circular buffer runs out of space, new samples overwrite the oldest samples.
/// The size of the sample buffer is set in constructor AbstractValueProfiler::AbstractValueProfiler().
///
/// To add a new sample to the profiler use the #addSample() function in the derived class.
/// To get a sample reference use the #getSample() function in the derived class.
///
/// The #AbstractValueProfiler provides a placeholder for arbitrary aggregate profiling data.
/// You can access aggregate profiling data from the derived class through #m_aggregateProfilingData.
///
/// Since internal circular buffer of samples can overflow, callbacks compatible with #FullBufferCallback can be added
/// and get called after the #addSample() which completely fills the buffer.
/// In case there are callbacks, after invoking all of them, the buffer is cleared.
/// To add a callback use #addFullBufferCallback() and to remove use #removeFullBufferCallback().
///
/// Example:
/// \snippet snippets_profiling.cpp Add remove full buffer callbacks
///
/// See base class #AbstractProfiler on how to extract profiler samples.
template <typename TProfilingDataSample, typename TAggregateProfilingData>
class AbstractValueProfiler : public AbstractProfiler
{
public:
    /// The typedef used for full buffer callback
    typedef function<void(AbstractValueProfiler&)> FullBufferCallback;

    /// The typedef used for full buffer callback handle
    typedef weak_ptr<void> FullBufferCallbackHandle;

    /// Adds a new full buffer callback
    /// \param callback A full buffer callback.
    /// \return Handle to added full buffer callback, used to later remove the callback if needed
    FullBufferCallbackHandle addFullBufferCallback(FullBufferCallback callback)
    {
        FullBufferCallbackSharedPtr sharedCallback = make_shared<FullBufferCallback>(kanzi::move(callback));
        m_fullBufferCallbacks.push_back(sharedCallback);
        return sharedCallback;
    }

    /// Removes a full buffer callback
    /// \param callbackHandle Handle to the callback, returned from addFullBufferCallback
    void removeFullBufferCallback(const FullBufferCallbackHandle& callbackHandle)
    {
        if (FullBufferCallbackSharedPtr sharedCallback = static_pointer_cast<FullBufferCallback>(callbackHandle.lock()))
        {
            erase(m_fullBufferCallbacks, sharedCallback);
        }
    }

    /// Resets the aggregate profiling data and sample buffer.
    void resetSampleData()
    {
        m_aggregateProfilingData = AggregateProfilingDataType();
        m_sampleBuffer.clear();
    }

protected:
    /// The sample data type typedef used in derived classes.
    typedef TProfilingDataSample SampleDataType;

    /// The aggregate profiling data type typedef used in derived classes.
    typedef TAggregateProfilingData AggregateProfilingDataType;

    /// The typedef used for shared pointer to full buffer callback
    typedef shared_ptr<FullBufferCallback> FullBufferCallbackSharedPtr;

    /// The typedef used for container of full buffer callback shared pointers
    typedef vector<FullBufferCallbackSharedPtr> FullBufferCallbackContainer;

    /// Constructor.
    /// \param name The name of the profiler.
    /// \param category The profiling category assigned to the profiler.
    /// \param sampleBufferSize The maximum size of the sample buffer.
    explicit AbstractValueProfiler(string_view name, const ProfilingCategory& category, size_t sampleBufferSize) :
        AbstractProfiler(name, category),
        m_sampleBuffer(sampleBufferSize)
    {
    }

    /// Accesses a profiling data sample stored in the sample buffer.
    ///
    /// The sample buffer is zero-based, meaning that oldest sample is stored at index 0.
    ///
    /// \param index The index of the sample.
    /// \return The constant profiling data sample reference.
    const TProfilingDataSample& getSample(size_t index) const
    {
        return m_sampleBuffer.at(index);
    }

    /// Internal helper function used by #checkBufferFull
    static void invokeBufferFullCallback(AbstractValueProfiler& profiler, FullBufferCallbackSharedPtr& callback)
    {
        (*callback)(profiler);
    }

    /// Performs all buffer full callbacks and clears samples if buffer is full
    void checkBufferFull()
    {
        if (m_sampleBuffer.full() && !m_fullBufferCallbacks.empty())
        {
            for_each(begin(m_fullBufferCallbacks),
                     end(m_fullBufferCallbacks),
                     bind(&AbstractValueProfiler::invokeBufferFullCallback,
                          ref(*this), placeholders::_1));

            resetSampleData();
        }
    }

    /// Adds a new profiling data sample.
    /// \param sample The profiling data sample.
    void addSample(const TProfilingDataSample& sample)
    {
        m_sampleBuffer.push_back(sample);
        checkBufferFull();
    }

    /// Adds a new movable profiling data sample to the profiler.
    /// \param sample The profiling data sample.
    void addSample(KZ_RV_REF(TProfilingDataSample) sample)
    {
        m_sampleBuffer.push_back(kanzi::move(sample));
        checkBufferFull();
    }

    /// Override of #AbstractProfiler::getSampleCountOverride().
    /// \return The number of collected profiling data samples.
    virtual size_t getSampleCountOverride() const KZ_OVERRIDE
    {
        return m_sampleBuffer.size();
    }

    /// The aggregate profiling data.
    TAggregateProfilingData m_aggregateProfilingData;

private:
    /// The container of buffer full callbacks
    FullBufferCallbackContainer m_fullBufferCallbacks;

    /// The profiling data sample buffer.
    circular_buffer<TProfilingDataSample> m_sampleBuffer;
};

/// \}
}
#endif
