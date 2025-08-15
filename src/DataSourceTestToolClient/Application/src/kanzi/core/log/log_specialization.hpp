// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LOG_SPECIALIZATION_HPP
#define KZ_LOG_SPECIALIZATION_HPP

#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/log/log_argument_format.hpp>
#include <kanzi/core/string/fixed_string.hpp>
#include <kanzi/core/string/immutable_string.hpp>
#include <kanzi/core/string/shared_immutable_string.hpp>

namespace kanzi
{
/// \defgroup SpecializedLogArgumentToString Default logArgumentToString specializations
///
/// \ref LoggingSubsystemSection specialization of \ref logArgumentToString for user-defined types.
/// \{

/// Used by logging system to convert standard exception type objects to string.
///
/// See template logArgumentToString().
template<>
inline string logArgumentToString(const std::exception& exception)
{
    return exception.what();
}

/// Used by logging system to convert fixed strings to string.
///
/// See template logArgumentToString().
template<>
inline string logArgumentToString(const FixedString& fixedString)
{
    return string(fixedString.c_str());
}

/// Used by logging system to convert immutable strings to string.
///
/// See template logArgumentToString().
template<>
inline string logArgumentToString(const ImmutableString& immutableString)
{
    return string(immutableString.c_str());
}

/// Used by logging system to convert shared immutable strings to string.
///
/// See template logArgumentToString().
template<>
inline string logArgumentToString(const SharedImmutableString& sharedImmutableString)
{
    return string(sharedImmutableString.c_str());
}

/// Used by logging system to convert string_view to string.
///
/// See template logArgumentToString().
template<>
inline string logArgumentToString(const string_view& stringView)
{
    return string(stringView);
}

/// Used by logging system to convert bool to string.
///
/// See template logArgumentToString().
template <>
inline string logArgumentToString(const bool& value)
{
    return value ? "true" : "false";
}

/// \}

}

#endif
