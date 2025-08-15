// Copyright 2008 - 2017 by Rightware.All rights reserved.

#ifndef KZ_WIN32_DEBUG_LOGGER_HPP
#define KZ_WIN32_DEBUG_LOGGER_HPP

#include <kanzi/core/log/abstract_logger.hpp>

namespace kanzi
{
/// \ingroup DefaultLoggers
/// \{

/// This logger class writes log messages to the Windows debugger console.
///
class KANZI_API Win32DebugLogger : public AbstractLogger
{
protected:
    
    /// See \ref kanzi::AbstractLogger::writeOverride.
    ///
    /// Writes the \p levelName and the \p categoryName followed by the \p message to the log.
    /// For error messages writes also the \p fileName and \p lineNumber.
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