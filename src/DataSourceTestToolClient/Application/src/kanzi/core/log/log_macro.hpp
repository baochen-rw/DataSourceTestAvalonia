// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LOG_MACRO_HPP
#define KZ_LOG_MACRO_HPP

#include <kanzi/core/log/log_category.hpp>
#include <kanzi/core/log/log_level.hpp>
#include <kanzi/core/cpp/cstddef.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>


/// Bundles multiple formatted messages for the \ref LoggingSubsystemSection to use internally.
///
/// Do not use this macro directly. Only the \ref LoggingSubsystemSection uses this macro. This macro bundles several formatted messages into a sequence to be
/// passed to KZ_LOG_FILTER_MESSAGES_INTERNAL() as messages argument. See kzLog().
///
/// \param numberOfMessages Number of formatted messages in a bundle.
/// \param messages Messages to be bundled.
#define KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(numberOfMessages, messages) BOOST_PP_TUPLE_TO_SEQ(numberOfMessages, messages)

/// Filters messages by log level and category and, if the messages pass the filter, appends them to the log.
///
/// This macro filters log messages based on enabled level and category. For a message to pass the filter, both level and category
/// must be enabled.
///
/// \param logger Logger to which to write messages.
/// \param level The log level of the message.
/// \param category The log category of the message.
/// \param message Log message. See kzLog() macro for details.
#define KZ_LOG_FILTER_MESSAGES_INTERNAL(logger, level, category, messages) \
    BOOST_PP_EXPR_IF(KZ_LOG_ARE_LEVEL_AND_CATEGORY_ENABLED(level, category), \
                     KZ_LOG_APPEND_FILTERED_MESSAGES_INTERNAL(logger, level, category, messages))

/// Tests whether level and category are enabled.
#define KZ_LOG_ARE_LEVEL_AND_CATEGORY_ENABLED(level, category) \
    BOOST_PP_AND(KZ_LOG_IS_LEVEL_ENABLED(level), KZ_LOG_IS_CATEGORY_ENABLED(category))

/// Helper macro.
#define KZ_LOG_APPEND_SINGLE_MESSAGE_INTERNAL(unsusedParameter, method, value) method value;

/// Logs message after filter is passed. See KZ_LOG_APPLY_FILTER_INTERNAL() for details.
#define KZ_LOG_APPEND_FILTERED_MESSAGES_INTERNAL(logger, level, category, messages) \
    KZ_MULTILINE_MACRO \
    ::kanzi::detail::LogRecord record(logger, ::kanzi::detail::IntegerToLogLevel<KZ_LOG_GET_LEVEL_VALUE(level)>::value, KZ_LOG_GET_LEVEL_NAME(level), KZ_LOG_GET_CATEGORY_NAME(category), __FILE__, __LINE__); \
    BOOST_PP_SEQ_FOR_EACH(KZ_LOG_APPEND_SINGLE_MESSAGE_INTERNAL, record.appendMessage, messages); \
    KZ_MULTILINE_MACRO_END

/// Helper macro.
#define KZ_LOG_TYPENAME_TN_INTERNAL(notUsed, argNum, maxArgNum) \
    typename T##argNum BOOST_PP_COMMA_IF(BOOST_PP_LESS(argNum, maxArgNum))

/// Helper macro.
#define KZ_LOG_CONST_REF_TN_INTERNAL(notUsed, argNum, maxArgNum) \
    const T##argNum& arg##argNum BOOST_PP_COMMA_IF(BOOST_PP_LESS(argNum, maxArgNum))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_TEMPLATE_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_TYPENAME_TN_INTERNAL, BOOST_PP_DEC(numArgs))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_CONST_REF_TN_INTERNAL, BOOST_PP_DEC(numArgs))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_PASS_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_APPEND_MESSAGE_PASS_ARGUMENT_INTERNAL, BOOST_PP_DEC(numArgs))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_WRAP_ONE_ARGUMENT_INTERNAL(notUsed, argNum, maxArgNum) \
    const detail::LogArgumentTypeEraser wrappedArgument ## argNum(arg ## argNum);

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_WRAP_ALL_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_APPEND_MESSAGE_WRAP_ONE_ARGUMENT_INTERNAL, BOOST_PP_DEC(numArgs))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_ENUM_ONE_WRAPPED_ARGUMENT_INTERNAL(notUsed, argNum, maxArgNum) \
    detail::LogArgumentTypeEraser(arg ## argNum) BOOST_PP_COMMA_IF(BOOST_PP_LESS(argNum, maxArgNum))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_ENUM_ALL_WRAPPED_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_APPEND_MESSAGE_ENUM_ONE_WRAPPED_ARGUMENT_INTERNAL, BOOST_PP_DEC(numArgs))

/// Helper macro.
#define KZ_LOG_APPEND_MESSAGE_WRAP_ARGUMENTS_INTERNAL(numArgs) \
    BOOST_PP_REPEAT(numArgs, KZ_LOG_WRAP_ONE_ARGUMENT_INTERNAL, BOOST_PP_DEC(numArgs))

/// Creates definition of template appendMessage() method with specified number of template arguments.
///
/// \param numArgs The number of template arguments.
#define KZ_LOG_APPEND_MESSAGE_DEFINITION(numArgs) \
    template < KZ_LOG_APPEND_MESSAGE_TEMPLATE_ARGUMENTS_INTERNAL(numArgs) > \
    void appendMessage(string_view formatString, KZ_LOG_APPEND_MESSAGE_ARGUMENTS_INTERNAL(numArgs)) \
    { \
       const detail::LogArgumentTypeEraser arguments[] = { KZ_LOG_APPEND_MESSAGE_ENUM_ALL_WRAPPED_ARGUMENTS_INTERNAL(numArgs) }; \
       appendFormattedMessage(formatString, arguments, sizeof(arguments) / sizeof(arguments[0])); \
    }

namespace kanzi
{

namespace detail
{

/// Converts integer representation of log level to enumeration.
///
/// This template is used internally by \ref LoggingSubsystemSection to convert integer
/// value assigned to log level to \ref LogLevel enum
template<size_t>
struct IntegerToLogLevel
{

};

/// Converts integer representation of error log level to enumeration.
template<>
struct IntegerToLogLevel<KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_ERROR)>
{
    static const LogLevel value = LogLevelError;
};

/// Converts integer value of warning log level to enumeration.
template<>
struct IntegerToLogLevel<KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_WARNING)>
{
    static const LogLevel value = LogLevelWarning;
};

/// Converts integer value of info log level to enumeration.
template<>
struct IntegerToLogLevel<KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_INFO)>
{
    static const LogLevel value = LogLevelInfo;
};

/// Converts integer value of trace log level to enumeration.
template<>
struct IntegerToLogLevel<KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_TRACE)>
{
    static const LogLevel value = LogLevelTrace;
};

}

}

#endif
