// Copyright 2008 - 2017 by Rightware.All rights reserved.

#ifndef KZ_ANDROID_LOGGER_HPP
#define KZ_ANDROID_LOGGER_HPP

#include <kanzi/core/log/abstract_logger.hpp>

namespace kanzi
{
/// \ingroup DefaultLoggers
/// \{

/// This is a logger class that writes log messages to Android system log.
class AndroidLogger : public AbstractLogger
{
protected:
    /// See \ref kanzi::AbstractLogger::writeOverride.
    ///
    /// The messages with \p level = \ref LogLevelError are prepended with \p fileName and \p lineNumber.
    ///
    /// \param level The log level of the message.
    /// \param levelName The string representation of log level.
    /// \param categoryName The string representation of log category.
    /// \param fileName The name of the file log message is originated from.
    /// \param lineNumber The line number of the place in file where log message is originated.
    /// \param message The message being written to the log.
    virtual void writeOverride(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message) KZ_OVERRIDE;
};
/// \}

}

#endif