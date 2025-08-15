// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_LOG_ARGUMENT_TYPE_ERASER_HPP
#define KZ_LOG_ARGUMENT_TYPE_ERASER_HPP

#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/log/log_argument_format.hpp>

namespace kanzi
{

namespace detail
{

/// Log argument reference holder.
///
/// Keeps void pointer to log format argument and pointer to the function used to convert the pointer to string. Template function being used for conversion is
/// deduced from type of the argument.
class LogArgumentTypeEraser
{
public:
    /// Determines function being used to convert void argument value pointer to string.
    template<typename T>
    explicit LogArgumentTypeEraser(const T& value) :
        m_valueReference(&value),
        m_conversionFunction(&LogArgumentFormat::convertToString<T>)
    {
    }

    /// Converts the argument value to string according to the supplied format string.
    /// \param formatString The format string.
    /// \return The referenced argument converted to a string according to the supplied format string.
    string convert(string_view formatString) const
    {
        return m_conversionFunction(formatString, m_valueReference);
    }

private:
    /// Pointer to the argument value.
    const void* m_valueReference;

    /// Function for converting argument value pointer to string.
    LogArgumentFormat::ConversionFunction m_conversionFunction;
};
}
}

#endif

#endif
