// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CHAINED_LOGGER_HPP
#define KZ_CHAINED_LOGGER_HPP

#include <kanzi/core/log/abstract_logger.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{
namespace detail
{

/// Provides interface to write log messages to multiple loggers.
class ChainedLogger : public AbstractLogger
{
public:
    /// Typedef of the \ref kanzi::AbstractLogger unique pointer.
    typedef unique_ptr<AbstractLogger> AbstractLoggerUniquePtr;

    /// Typedef of vector holding \ref kanzi::AbstractLogger unique pointers.
    typedef vector<AbstractLoggerUniquePtr> AbstractLoggerVector;

    /// Registers a new logger and takes the ownership of that logger.
    ///
    /// \param logger New logger.
    void push(AbstractLoggerUniquePtr logger);

    /// Registers a new logger and takes the ownership of that logger.
    ///
    /// \param logger New logger. You must allocate the logger dynamically with the new expression.
    /// \deprecated Use the overload with AbstractLoggerUniquePtr parameter.
    void push(AbstractLogger* logger);

    /// Removes last registered logger.
    void pop()
    {
        if (m_loggers.empty())
        {
            return;
        }

        m_loggers.pop_back();
    }

    /// Removes all registered loggers.
    void popAll()
    {
        m_loggers.clear();
    }

protected:
    /// Writes log message using registered loggers.
    ///
    /// See \ref kanzi::AbstractLogger::writeOverride for details.
    ///
    /// \param level The log level of the message.
    /// \param levelName The string representation of log level.
    /// \param categoryName The string representation of log category.
    /// \param fileName The name of the file log message is originated from.
    /// \param lineNumber The line number of the place in file where log message is originated.
    /// \param message The message being written to the log.
    virtual void writeOverride(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message) KZ_OVERRIDE;

private:

    /// Container for logger objects.
    AbstractLoggerVector m_loggers;
};

}
}

#endif
