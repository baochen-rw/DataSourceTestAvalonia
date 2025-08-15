// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_ABSTRACT_LOGGER_HPP
#define KZ_ABSTRACT_LOGGER_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/log/log_level.hpp>

namespace kanzi
{

// Forward class declaration.
class AbstractLogger;
/// Typedef of the \ref kanzi::AbstractLogger unique pointer.
typedef unique_ptr<AbstractLogger> AbstractLoggerUniquePtr;

/// Inherit from this class to implement logger.
///
/// Make your logger class override the \ref writeOverride function. Kanzi invokes the \ref writeOverride function when the message is ready to be written to the log.
/// Your implementation of the \ref writeOverride function is responsible for final processing and storing of the log message.
///
/// To write log messages using your custom logger, use the \ref kzLog macro.  If you want to use a custom logger to write all the application log messages,
/// register the logger in \ref kanzi::DefaultLogger.
///
/// The logging system comes with several loggers. See \ref DefaultLoggers.
///
/// Examples
/// --------
///
/// To implement a logger:
/// \snippet snippets_log.cpp Simple logger implementation
///
/// To use a logger explicitly:
/// \snippet snippets_log.cpp Using custom logger explicitly
///
/// To use a logger in a logger chain:
/// \snippet snippets_log.cpp Adding custom logger to logger chain
///
/// To set your logger to handle all the log messages:
/// \snippet snippets_log.cpp Redirecting logs to custom logger exclusively
class KANZI_API AbstractLogger
{
public:

    /// Kanzi calls this function to store the message to the log.
    ///
    /// To store the log message, this function calls the \ref writeOverride() function implemented in the inherited class.
    ///
    /// \param level The log level of the message.
    /// \param levelName The string representation of the log level.
    /// \param categoryName The string representation of the log category.
    /// \param fileName The name of the file from which the log message originated.
    /// \param lineNumber The number of the line in the file from which the log message originated.
    /// \param message The log message.
    void write(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message)
    {
        writeOverride(level, levelName, categoryName, fileName, lineNumber, message);
    }

    /// Destructor.
    virtual ~AbstractLogger()
    {

    }

protected:

    /// To store the message to the log, implement this function in the inherited class.
    ///
    /// It is transparent to Kanzi how this function stores the messages to the log.
    ///
    /// \param level The log level of the message.
    /// \param levelName The string representation of the log level.
    /// \param categoryName The string representation of the log category.
    /// \param fileName The name of the file from which the log message originated.
    /// \param lineNumber The number of the line in the file from which the log message originated.
    /// \param message The log message.
    virtual void writeOverride(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message) = 0;
};

}

#endif

#endif
