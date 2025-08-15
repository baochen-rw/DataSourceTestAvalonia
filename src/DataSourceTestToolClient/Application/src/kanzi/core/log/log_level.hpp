// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LOG_LEVEL_HPP
#define KZ_LOG_LEVEL_HPP

#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/// \file
///
///
/// \section LogLevelSection Log Level
///
/// The \ref LoggingSubsystemSection provides several log levels that you can use to classify log messages. See \ref LogLevels. Log levels are
/// ordered according to their severity. To implement the ordering, a distinct integer number is assigned to each level. The most severe log level is 
/// the error log level (\ref KZ_LOG_LEVEL_ERROR), which is assigned the value 1. The larger the log level value is, the less severe the message.
/// To get the integer value assigned to a log level, use the \ref KZ_LOG_GET_LEVEL_VALUE macro.
///
/// Each log level has a name, which is a short string describing the log level. For example, "error". A logger can use the name when writing a log message.
/// See kanzi::AbstractLogger. To get the name of a log level, use the \ref KZ_LOG_GET_LEVEL_NAME macro.
///
/// These are the log levels available in the Kanzi logging subsystem:
///
/// Log level                 | Severity value    | Name
/// --------------------------|-------------------|--------
/// \ref KZ_LOG_LEVEL_ERROR   | 1                 | error
/// \ref KZ_LOG_LEVEL_WARNING | 2                 | warning
/// \ref KZ_LOG_LEVEL_INFO    | 3                 | info
/// \ref KZ_LOG_LEVEL_TRACE   | 4                 | trace
///
/// The \ref KZ_LOG_LEVEL_ENABLED_THRESHOLD macro defines which log levels are enabled. A log level is enabled if it is the same 
/// or more severe than the log level that \ref KZ_LOG_LEVEL_ENABLED_THRESHOLD is set to. Otherwise the log level is disabled.
/// To check whether a particular log level is enabled, use the \ref KZ_LOG_IS_LEVEL_ENABLED macro. 
/// To learn how the state of the log level affects message filtering, see \ref LoggingMessageClassificationSection.
///
/// The integer value assigned to the log level along with its name are passed to the \ref KZ_LOG_CREATE_LEVEL macro when the log level is defined.
/// See \ref LogLevels for details.
///

/// \defgroup LogLevelMacros Log level utility macros
/// 
/// Use these macros to define new log levels and operate on defined log levels.
/// \{

///
/// Creates a log level.
///
/// Use the \p value parameter to assign to the new log level a unique integer value that is used to order the log levels.
/// This value is used in log message filtering. See \ref LoggingMessageClassificationSection.
///
/// Use the \p name parameter to provide the log level name, which the logger uses when writing messages to the log.
///
/// \param value Unique integer value used to implement the log level ordering. See \ref LogLevelSection.
/// \param name The name of the log level.
/// \see kanzi::AbstractLogger, \ref LogLevelSection, \ref LogLevels, \ref LoggingMessageClassificationSection
#define KZ_LOG_CREATE_LEVEL(value, name) (value, name)

/// Gets a log level value.
///
/// \param level The log level.
/// \return The value used to implement log level ordering.
/// \see \ref KZ_LOG_CREATE_LEVEL, \ref LogLevelSection
#define KZ_LOG_GET_LEVEL_VALUE(level)   BOOST_PP_TUPLE_ELEM(2, 0, level)

/// Gets a log level name.
///
/// \param level The level macro. For example, see \ref KZ_LOG_LEVEL_ERROR.
/// \return Short string describing the log level.
/// \see \ref KZ_LOG_CREATE_LEVEL, \ref LogLevelSection
#define KZ_LOG_GET_LEVEL_NAME(level)    BOOST_PP_TUPLE_ELEM(2, 1, level)

/// Checks whether a log level is enabled.
///
/// \param level The log level.
/// \return If the log level is enabled, 1, otherwise 0.
/// \see \ref KZ_LOG_CREATE_LEVEL, \ref LogLevelSection
#define KZ_LOG_IS_LEVEL_ENABLED(level) BOOST_PP_LESS_EQUAL(KZ_LOG_GET_LEVEL_VALUE(level), KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_ENABLED_THRESHOLD))
/// \}

/// \defgroup LogLevels Log levels
/// 
/// Use log levels to classify log messages based on the severity of the information that they carry.
///
/// These are the log levels available in the Kanzi logging subsystem:
///
/// Log level                 | Severity value    | Name
/// --------------------------|-------------------|--------
/// \ref KZ_LOG_LEVEL_ERROR   | 1                 | error
/// \ref KZ_LOG_LEVEL_WARNING | 2                 | warning
/// \ref KZ_LOG_LEVEL_INFO    | 3                 | info
/// \ref KZ_LOG_LEVEL_TRACE   | 4                 | trace
/// \{

/// Use the error log level to log critical malfunction messages. Because the purpose of error messages is to provide as much information
/// as possible needed to investigate the reported issue, it is recommended to make error messages very detailed.
#define KZ_LOG_LEVEL_ERROR      KZ_LOG_CREATE_LEVEL(1, "error")

/// Use the warning log level to log facts that require attention, but do not necessarily mean malfunction. For example, use a warning 
/// message to notify the user about something recoverable, such as a missing parameter that has the default value, or something that can
/// lead to performance degradation, but not failure.
#define KZ_LOG_LEVEL_WARNING    KZ_LOG_CREATE_LEVEL(2, "warning")

/// Use the info log level to log information messages that give a brief overview of what is happening in the system, log states
/// passed, static information about configuration, and so on.
#define KZ_LOG_LEVEL_INFO       KZ_LOG_CREATE_LEVEL(3, "info")

/// Use the trace log level to get the maximum amount of information about the system. This is the most verbose log level, mainly 
/// used to troubleshoot issues.
#define KZ_LOG_LEVEL_TRACE      KZ_LOG_CREATE_LEVEL(4, "trace")
/// \}

#ifndef KZ_LOG_LEVEL_ENABLED_THRESHOLD

/// To set the enabled log level threshold, define this macro to one of the existing log levels.
///
/// The log level set in the KZ_LOG_LEVEL_ENABLED_THRESHOLD macro and all the log levels with higher severity are enabled.
/// The log levels less severe than the one set in KZ_LOG_LEVEL_ENABLED_THRESHOLD are disabled.
/// If you do not define this macro before including this header, it is defined to the default value of \ref KZ_LOG_LEVEL_INFO.
/// To learn how KZ_LOG_LEVEL_ENABLED_THRESHOLD is used in message filtering, see \ref LogLevelSection.
#define KZ_LOG_LEVEL_ENABLED_THRESHOLD KZ_LOG_LEVEL_INFO
#endif

namespace kanzi
{
/// The log levels.
///
/// The LogLevel is used internally to convert integer log level value to enumeration type.
enum LogLevel
{
    /// The error log level. See \ref KZ_LOG_LEVEL_ERROR.
    LogLevelError = KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_ERROR),
    
    /// The warning log level. See \ref KZ_LOG_LEVEL_WARNING.
    LogLevelWarning = KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_WARNING),
    
    /// The info log level. See \ref KZ_LOG_LEVEL_INFO.
    LogLevelInfo = KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_INFO),
    
    /// The trace log level. See \ref KZ_LOG_LEVEL_TRACE.
    LogLevelTrace = KZ_LOG_GET_LEVEL_VALUE(KZ_LOG_LEVEL_TRACE),
};
}

#endif
