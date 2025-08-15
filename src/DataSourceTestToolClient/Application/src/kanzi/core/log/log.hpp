// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_LOG_HPP
#define KZ_LOG_HPP

#include <kanzi/core/log/default_logger.hpp>
#include <kanzi/core/log/log_category.hpp>
#include <kanzi/core/log/log_level.hpp>
#include <kanzi/core/log/log_record.hpp>
#include <kanzi/core/log/log_specialization.hpp>

/// \file
///
/// \section LoggingSubsystemSection Logging subsystem
///
/// The Logging subsystem is responsible for writing messages to the log. To write log messages, use the \ref LoggingMacros provided by the subsystem.
///
/// To filter log messages at compile time, use log levels and log categories. See \ref LoggingMessageClassificationSection.
///
/// You can write both scalar values and formatted messages to the log. See \ref LogMessageFormattingSection.
///
/// \section LoggingMessageClassificationSection Classifying and filtering log messages
///
/// Use log levels to classify log messages based on the severity of the information that they contain. For example, to log critical problems, which occur
/// during application execution, use the error log level \ref KZ_LOG_LEVEL_ERROR. To log normal application activity, use the info log level
/// \ref KZ_LOG_LEVEL_INFO. See \ref LogLevelSection.
///
/// Use log categories to group messages that contain information about the same functionality. For example, to log messages related to the rendering 
/// engine activity, you can create the "Engine" log category. To group messages related to kzb file loading, you can create the "kzb loading" log category.
/// To learn how to create log categories, see \ref LogCategorySection.
/// 
/// Log message filtering is implemented in \ref LoggingMacros. Kanzi filters log messages at compile time using the log levels and log categories
/// that you assign to the messages. The preprocessor removes the call to the logging macro, if you disable the log level or category assigned to the message
/// in that macro call. Otherwise, the macro is replaced with the code that writes the message to the log.
/// To learn how to enable and disable log levels and categories, see \ref LogLevelSection and \ref LogCategorySection.
///
/// \note
/// Do not use application critical code in the logging macro calls. If you place application critical code as an argument to the logging macro call, and
/// during compilation you disable the log level or the log category assigned to the message in the call, the preprocessor removes the logging macro call
/// together with the application critical code.
///
/// Examples
/// --------
///
/// This example shows how you can filter log messages:
/// \snippet test_log.cpp Log message filtering
///
/// This example shows the danger of using application critical code in a call to the logging macro:
/// \snippet test_log.cpp Note on log message filtering
///

/// \defgroup LoggingMacros Logging macros
///
/// Use logging macros to write messages to the log. These macros are used to implement compile-time message filtering described in \ref LoggingMessageClassificationSection.
///
/// \{

/// Use the kzLog macro to write log messages using a custom logger.
///
/// This macro assigns the log \p level and the log \p category to the message and writes it to the log using the \p logger you provided. If you want to use
/// your logger to write all the application log messages, register your logger in \ref kanzi::DefaultLogger.
///
/// \param logger The logger you want to use to write the message to the log.
/// \param level The log level of the message.
/// \param category The log category of the message.
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Examples
/// --------
///
/// To implement your own logger:
/// \snippet snippets_log.cpp Simple logger implementation
///
/// To use your own logger to write a message to the log:
/// \snippet snippets_log.cpp Using custom logger explicitly
#define kzLog(logger, level, category, message) KZ_LOG_FILTER_MESSAGES_INTERNAL(logger, level, category, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(1, (message)))

/// To write error log messages with the Default Logger, use kzLogError macro.
///
/// This macro assigns \ref KZ_LOG_LEVEL_ERROR log level and the log \p category you provided to the message.
/// For more information about the Default Logger, see \ref kanzi::DefaultLogger.
///
/// \param category The log category assigned to the message.
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Example
/// -------
///
/// To write the error message to the log:
/// \snippet test_log.cpp Log simple error message
#define kzLogError(category, message) kzLog(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, category, message)

/// To write warning log messages with the Default Logger, use kzLogWarning macro.
///
/// This macro assigns \ref KZ_LOG_LEVEL_WARNING log level and the log \p category you provided to the message.
/// For more information about the Default Logger, see \ref kanzi::DefaultLogger.
///
/// \param category The log category assigned to the message.
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Example
/// -------
///
/// To write the warning message to the log:
/// \snippet test_log.cpp Log simple warning message
#define kzLogWarning(category, message) kzLog(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_WARNING, category, message)

/// To write info log messages with the Default Logger, use kzLogInfo macro.
///
/// This macro assigns \ref KZ_LOG_LEVEL_INFO log level and the log \p category you provided to the message.
/// For more information about the Default Logger, see \ref kanzi::DefaultLogger.
///
/// \param category The log category assigned to the message.
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Example
/// -------
///
/// To write the info message to the log:
/// \snippet test_log.cpp Log simple info message
#define kzLogInfo(category, message) kzLog(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_INFO, category, message)

/// To write trace log messages with the Default Logger, use kzLogTrace macro.
///
/// This macro assigns \ref KZ_LOG_LEVEL_TRACE log level and the log \p category you provided to the message.
/// For more information about the Default Logger, see \ref kanzi::DefaultLogger.
///
/// \param category The log category assigned to the message.
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Example
/// -------
///
/// To write the trace message to the log:
/// \snippet test_log.cpp Log simple trace message
#define kzLogTrace(category, message) kzLog(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_TRACE, category, message)

/// To write debug log messages with the Default Logger, use kzLogDebug macro.
///
/// This macro assigns \ref KZ_LOG_LEVEL_INFO log level and \ref KZ_LOG_CATEGORY_DEBUG log category to the message.
/// For more information about the Default Logger, see \ref kanzi::DefaultLogger.
///
/// \param message The log message.
/// \see \ref LogMessageFormattingSection
///
/// Example
/// -------
///
/// To write the debug message to the log:
/// \snippet test_log.cpp Log simple debug message
#define kzLogDebug(message) kzLogInfo(KZ_LOG_CATEGORY_DEBUG, message)
/// \}

#endif

#endif