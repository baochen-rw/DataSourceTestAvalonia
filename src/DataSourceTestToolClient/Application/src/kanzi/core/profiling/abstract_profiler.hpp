// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_PROFILER_HPP
#define KZ_ABSTRACT_PROFILER_HPP

#include <kanzi/core/cpp/circular_buffer.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/variant.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/profiling/profiling_category.hpp>
#include <kanzi/core/profiling/profiler_registry.hpp>
#include <kanzi/core/string/immutable_string.hpp>

namespace kanzi
{

// Forward declaration of AbstractProfiler.
class AbstractProfiler;

/// \addtogroup Profiling
/// \{

/// The shared pointer to the abstract profiler source.
typedef shared_ptr<AbstractProfiler> AbstractProfilerSharedPtr;

/// AbstractProfilerRegistry declaration.
typedef ProfilerRegistry<AbstractProfiler> AbstractProfilerRegistry;

/// AbstractProfiler
///
/// This is the abstract base class of all profilers.
/// See derived class \ref AbstractValueProfiler for a concrete implementation.
///
/// See \ref ProfilingMacros on how to use your profilers.
///
/// Examples
/// ----
/// To extract profiler samples:
/// \snippet snippets_profiling.cpp To extract profiler samples
class KANZI_CORE_API AbstractProfiler
{
public:

    /// Supported profiling data field value types.
    enum DataType
    {
        /// Undefined data type.
        DataTypeNotDefined,
        /// Boolean.
        DataTypeBoolean,
        /// Unsigned 64 bit integer.
        DataTypeUint64,
        /// Float.
        DataTypeFloat,
        /// String.
        DataTypeString
    };

    /// Container for profiling data field value.
    typedef variant<monostate, bool, uint64_t, float, string> Value;

    /// Destructor.
    virtual ~AbstractProfiler();

    /// Gets the name of the profiler.
    /// \return The name of the profiler.
    string_view getName() const;

    /// Gets a reference to the profiling category assigned to the profiler.
    /// \return The profiling category assigned to the profiler.
    const ProfilingCategory& getCategory() const;

    /// Gets the number of aggregate data fields.
    ///
    /// Calls getAggregateDataFieldCountOverride() overriden in the derived profiler class.
    ///
    /// \return The number of aggregate data fields.
    size_t getAggregateDataFieldCount() const;

    /// Gets the name of an aggregate data field.
    ///
    /// Calls getAggregateDataFieldNameOverride() overriden in the derived profiler class.
    ///
    /// \param fieldIndex The index of the field.
    /// \return The name of the aggregate data field.
    string getAggregateDataFieldName(size_t fieldIndex) const;

    /// Gets the value of an aggregate profiling data field.
    ///
    /// Calls getAggregateDataFieldValueOverride() overriden in the derived profiler class.
    ///
    /// \param fieldIndex The index of the aggregate profiling data field.
    /// \return The value of the aggregate profiling data field.
    Value getAggregateDataFieldValue(size_t fieldIndex) const;

    /// Gets the number of sample data fields.
    ///
    /// Calls getSampleFieldCountOverride() overriden in the derived profiler class.
    ///
    /// \return The number of sample data fields.
    size_t getSampleFieldCount() const;

    /// Gets the name of a data sample field.
    ///
    /// Calls getSampleFieldNameOverride() overriden in the derived profiler class.
    ///
    /// \param fieldIndex The index of the sample field.
    /// \return The name of the sample field.
    string getSampleFieldName(size_t fieldIndex) const;

    /// Gets the number of collected profiling data samples.
    ///
    /// Calls getSampleCountOverride() overriden in the derived profiler class.
    ///
    /// \return The number of collected profiling data samples.
    size_t getSampleCount() const;

    /// Gets the value of a profiling data sample field.
    ///
    /// Calls getSampleFieldValueOverride() overriden in the derived profiler class.
    ///
    /// \param sampleIndex The index of the profiling data sample.
    /// \param fieldIndex The index of the field of the profiling data sample.
    /// \return The value of the profiling data sample field.
    Value getSampleFieldValue(size_t sampleIndex, size_t fieldIndex) const;

    /// Gets the type of the data stored in a profiling data field.
    /// \param value Profiling data field value.
    /// \return Type of the data stored in profiling data field.
    static DataType getDataType(const Value& value);

    /// Logs aggregate profiling data.
    void logAggregateData() const
    {
        logAggregateDataOverride();
    }

    /// Logs all profiling data.
    void logAllData() const
    {
        logAllDataOverride();
    }

protected:

    /// Constructor.
    /// \param name The name of the profiler.
    /// \param category The profiling category assigned to the profiler.
    explicit AbstractProfiler(string_view name, const ProfilingCategory& category);

    /// To provide the number of the aggregate data fields, override this function in the derived profiler class.
    /// \return The number of aggregate data fields.
    virtual size_t getAggregateDataFieldCountOverride() const = 0;

    /// To provide the name of aggregate data field with given index, override this function in the derived profiler class.
    /// \param fieldIndex The index of the field.
    /// \return The name of the aggregate data field.
    virtual string getAggregateDataFieldNameOverride(size_t fieldIndex) const = 0;

    /// To provide access to aggregate profiling data field values, override this function in the derived profiler class.
    /// \param fieldIndex The index of the aggregate profiling data field.
    /// \return The value of the aggregate profiling data field.
    virtual Value getAggregateDataFieldValueOverride(size_t fieldIndex) const = 0;

    /// To provide the number of sample fields, override this function in the derived profiler class.
    /// \return The number of sample fields.
    virtual size_t getSampleFieldCountOverride() const = 0;

    /// To provide the name of a sample field with a given index, override this function in the derived profiler class.
    /// \param fieldIndex The index of the field.
    /// \return The name of sample field.
    virtual string getSampleFieldNameOverride(size_t fieldIndex) const = 0;

    /// To provide access to profiling data sample fields of the derived profiler, override this function in the derived profiler class.
    /// \param sampleIndex The index of the profiling data sample.
    /// \param fieldIndex The index of the field of the profiling data sample.
    /// \return The value of the profiling data sample field.
    virtual Value getSampleFieldValueOverride(size_t sampleIndex, size_t fieldIndex) const = 0;

    /// To provide the number of profiling data samples stored in the derived profiler, override this function in the derived profiler class.
    /// \return The number of the profiling data samples stored in the derived profiler.
    virtual size_t getSampleCountOverride() const = 0;

    /// To implement your own logging of aggregate profiling data, override this function in the derived profiler class.
    virtual void logAggregateDataOverride() const;

    /// To implement your own logging of all profiling data, override this function in the derived profiler class.
    virtual void logAllDataOverride() const;
private:

    /// The name of the profiler.
    ImmutableString m_name;

    /// The profiling category reference.
    const ProfilingCategory& m_category;
};

/// \}

}
#endif
