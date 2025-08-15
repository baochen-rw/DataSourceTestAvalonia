// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_LOG_RECORD_HPP
#define KZ_LOG_RECORD_HPP

#include <kanzi/core/log/abstract_logger.hpp>
#include <kanzi/core/log/log_argument_type_eraser.hpp>
#include <kanzi/core/log/log_macro.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

namespace detail
{

/// This class represents a log record that accumulates multiple log messages and writes them to the logger as a single message when the object of this class is destroyed.
///
/// This class is used internally by the \ref LoggingSubsystemSection. The object of this class is to accumulate multiple log messages with the same log level
/// and log category. The log messages are written to the logger when the object is destroyed. You pass the logger to this class as a constructor parameter.
///
class KANZI_API LogRecord
{
public:

    /// Constructor.
    ///
    /// Constructs the Log Record object.
    ///
    /// \param logger The logger to be used to write the log messages.
    /// \param level The log level of the message.
    /// \param levelName The string representation of the log level.
    /// \param categoryName The string representation of the log category.
    /// \param fileName The name of the file from which the log message originated.
    /// \param lineNumber The number of the line on which the log message originated.
    explicit LogRecord(AbstractLogger& logger, LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber) : m_loggerReference(logger), m_level(level), m_levelName(levelName), m_categoryName(categoryName), m_fileName(fileName), m_lineNumber(lineNumber)
    {
    }

    /// Writes accumulated log messages to the logger.
    ~LogRecord()
    {
        m_loggerReference.write(m_level, m_levelName, m_categoryName, m_fileName, m_lineNumber, m_message);
    }

    /// Appends a single value message to the log storage.
    ///
    /// \param value The value to be converted to string and added to the log storage.
    template<typename T>
    void appendMessage(const T& value)
    {
        detail::LogArgumentTypeEraser argument(value);
        m_message += argument.convert("");
    }

    /// Appends formatted messages to the log.
    ///
    /// This is a series of template appendMessage() method overloads. They are used to append formatted messages to
    /// the log. The first argument of these methods is a format string that describes the structure of the message text.
    /// The format string consists of a plain message text and format argument references. When the message is written to the log,
    /// the format argument references in the format string are replaced with string representation of the corresponding argument value.
    ///
    /// Argument reference is an integer value enclosed in curly braces. The integer value enclosed in braces is a numerical value - the position of
    /// format argument. The first format argument following the format string has position 0, the next one has position 1, and so on.
    ///
    /// For example:
    /// \snippet test_log.cpp LogRecord usage
    ///
    /// \param format Format string that describes the structure of the log message.
    /// \param arg0-argN Format arguments referred in the format string.
    KZ_LOG_APPEND_MESSAGE_DEFINITION(1)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(2)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(3)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(4)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(5)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(6)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(7)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(8)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(9)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(10)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(11)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(12)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(13)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(14)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(15)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(16)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(17)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(18)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(19)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(20)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(21)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(22)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(23)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(24)
    KZ_LOG_APPEND_MESSAGE_DEFINITION(25)

private:

    /// Used to write formatted message to the logger.
    ///
    /// Template methods \ref appendMessage use this function to write log message after format arguments 
    /// are wrapped with \ref kanzi::detail::LogArgumentTypeEraser.
    ///
    /// \param formatString The format string describing structure of log message. See \ref LogMessageStructureSection section for details.
    /// \param formatArguments The array of wrapped format arguments of size \p argumentCount.
    /// \param argumentCount The number of format arguments.
    void appendFormattedMessage(string_view formatString, const detail::LogArgumentTypeEraser* formatArguments, size_t argumentCount);

    /// Used to append log message text to the message text storage.
    ///
    /// \param text The text to be added to message text storage.
    void appendMessageTextChunk(string_view text);

private:

    /// Logger reference.
    AbstractLogger& m_loggerReference;

    /// Log level.
    LogLevel m_level;

    /// Log level name.
    string_view m_levelName;

    /// Category name.
    string_view m_categoryName;

    /// Source file name.
    string_view m_fileName;

    /// Source file line.
    size_t m_lineNumber;

    /// Message text storage.
    string m_message;
};

}

}

#endif

#endif
