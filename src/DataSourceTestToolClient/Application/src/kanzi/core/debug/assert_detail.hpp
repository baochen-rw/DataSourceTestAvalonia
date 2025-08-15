// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ASSERT_MACRO_HPP
#define KZ_ASSERT_MACRO_HPP

#include <kanzi/core/log/log.hpp>

#ifdef KANZI_DEBUG
/// Used internally. Enables specified macro invocation if KANZI_DEBUG is defined.
/// \param assertionMacro macro to be called when KANZI_DEBUG is defined.
#define KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(assertionMacro) assertionMacro
#else
/// Used internally. Enables specified macro invocation if KANZI_DEBUG is defined.
/// \param assertionMacro macro to be called when KANZI_DEBUG is defined.
#define KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(assertionMacro)
#endif

#ifndef KZ_LOG_CATEGORY_ASSERTION_ENABLED

// Enable assertion log category by default.
#define KZ_LOG_CATEGORY_ASSERTION_ENABLED       KZ_LOG_ENABLED_CATEGORY

#endif

/// Assertion Log Category.
///
/// This should be used to log assertion messages only.
#define KZ_LOG_CATEGORY_ASSERTION               KZ_LOG_CREATE_CATEGORY(KZ_LOG_CATEGORY_ASSERTION_ENABLED, "assertion")

/// Used internally by assertion subsystem to log assertion failure message.
///
/// You should not use it directly. Only assertion subsystem uses this macro to log messages. This macro logs failed expression (not it's value) as character string.
/// \param expression Failed assertion expression.
#define KZ_ASSERT_LOG_FAILURE_INTERNAL(expression) KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_ASSERTION, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(1, (("Assertion \"{}\" failed.", #expression))))

/// Used internally by assertion subsystem to log assertion failure with custom description message.
///
/// You should not use it directly. Only assertion subsystem uses this macro to log messages. This macro extends KZ_ASSERT_LOG_FAILURE() syntax with extra message parameter
/// that is appended to the log in order to clarify assertion failure.
/// \param expression Failed assertion expression.
/// \param message Assertion failure clarification message. It's format string bundled with format arguments. Should be surrounded with brackets.
#define KZ_ASSERT_LOG_FAILURE_MESSAGE_INTERNAL(expression, message) KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_ASSERTION, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(2, (("Assertion \"{}\" failed. ", #expression), message)))

/// Used internally by assertion subsystem to log unreachable code assertion.
///
/// You should not use it directly. Only assertion subsystem uses this macro to log messages. This macro is used to assert the code that is not supposed to be reached by valid code paths.
/// The error log message is issued when place of the code where this macro used is executed.
///
#define KZ_ASSERT_LOG_UNREACHABLE_INTERNAL() KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_ASSERTION, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(1, (("Unreachable code assertion failed."))))

/// Used internally by assertion subsystem to log unreachable code assertion.
///
/// You should not use it directly. Only assertion subsystem uses this macro to log messages. This macro is used to assert the code that is not supposed to be reached by valid code paths.
/// The error log message is issued when place of the code where this macro used is executed. Sole argument of this macro describing why asserted place in code could be reached.
///
/// \param message Assertion failure clarification message. It's format string bundled with format arguments. Should be surrounded with brackets.
#define KZ_ASSERT_LOG_UNREACHABLE_MESSAGE_INTERNAL(message) KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_ASSERTION, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(2, (("Unreachable code assertion failed. "), message)))

/// Used internally. See kzAssert().
#define KZ_ASSERT_INTERNAL(expression) KZ_MULTILINE_MACRO \
    if (!(expression)) \
    { \
        KZ_ASSERT_LOG_FAILURE_INTERNAL(expression); \
        ::kanzi::detail::terminateProgram(); \
    } \
    KZ_MULTILINE_MACRO_END

/// Used internally. See kzAssertMessage().
#define KZ_ASSERT_MESSAGE_INTERNAL(expression, message)  KZ_MULTILINE_MACRO \
    if (!(expression)) \
    { \
        KZ_ASSERT_LOG_FAILURE_MESSAGE_INTERNAL(expression, message); \
        ::kanzi::detail::terminateProgram(); \
    } \
    KZ_MULTILINE_MACRO_END

/// Used internally. See kzAssertUnreachable().
#define KZ_ASSERT_UNREACHABLE_INTERNAL() KZ_MULTILINE_MACRO \
    KZ_ASSERT_LOG_UNREACHABLE_INTERNAL(); \
    ::kanzi::detail::terminateProgram(); \
    KZ_MULTILINE_MACRO_END

/// Used internally. See kzAssertUnreachableMessage().
#define KZ_ASSERT_UNREACHABLE_MESSAGE_INTERNAL(message) KZ_MULTILINE_MACRO \
    KZ_ASSERT_LOG_UNREACHABLE_MESSAGE_INTERNAL(message); \
    ::kanzi::detail::terminateProgram(); \
    KZ_MULTILINE_MACRO_END

namespace kanzi
{

namespace detail
{

/// This function terminates program execution.
///
/// This function inserts breakpoint using kzDebugBreak() and then terminates program if execution continues after calling kzDebugBreak().
/// See kzDebugBreak() for more information on how breakpoint is inserted.
KANZI_API KZ_ATTRIBUTE_NO_RETURN void terminateProgram();

/// Used internally by assertion system in order to insert breakpoint if debugger is attached.
///
/// See kzDebugBreak() macro for details.
KANZI_API void debugBreak();

}

}
#endif
