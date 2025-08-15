// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION


#ifndef KZ_COUT_LOGGER_HPP
#define KZ_COUT_LOGGER_HPP

#include <kanzi/core/log/abstract_logger.hpp>

namespace kanzi
{

/// \defgroup DefaultLoggers Default loggers
///
/// The default loggers.
/// \{
    
/// This logger class writes log messages to standard output.
///
class KANZI_API CoutLogger : public AbstractLogger
{
protected:

    /// See \ref kanzi::AbstractLogger::writeOverride.
    ///
    /// Every log message is prefixed with \p levelName and \p categoryName.
    /// The messages with \p level = \ref LogLevelError are prefixed with \p fileName and \p lineNumber.
    ///
    /// \param level The log level of the message.
    /// \param levelName The string representation of the log level.
    /// \param categoryName The string representation of the log category.
    /// \param fileName The name of the file from which the log message originated.
    /// \param lineNumber The number of the line in the file from which the log message originated.
    /// \param message The message being written to the log.
    virtual void writeOverride(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message) KZ_OVERRIDE;
};
/// \}

}

#endif

#endif
