// Copyright 2008-2017 by Rightware.All rights reserved.

#ifndef KZ_DEFAULT_LOGGER_HPP
#define KZ_DEFAULT_LOGGER_HPP

#include <kanzi/core/log/chained_logger.hpp>

namespace kanzi
{
/// Use this class to access the Default Logger.
///
/// The Default Logger inherits from \ref kanzi::AbstractLogger. It is a container for an arbitrary number of other loggers. 
///
/// To add a logger to the Default Logger object, use \ref pushLogger.
/// The implementation of the AbstractLogger::writeOverride function in the Default Logger writes log messages to all the loggers that the Default Logger contains.
///
/// To remove the last added logger from the Default Logger, use \ref popLogger. To remove all loggers from the Default Logger, use \ref popAllLoggers.
///
/// To get the reference to the Default Logger object, use \ref get.
///
/// The \ref LoggingMacros use the Default Logger to write log messages.
class KANZI_API DefaultLogger
{
public:

    /// Pushes a custom logger to the Default Logger object and takes the ownership of that logger.
    ///
    /// Use this function to append a new custom logger to be used by the Default Logger to write log messages.
    /// \param logger New logger to be registered within the default logger.
    static void pushLogger(AbstractLoggerUniquePtr logger);

    /// Pushes a custom logger to the Default Logger object and takes the ownership of that logger.
    ///
    /// Use this function to append a new custom logger to be used by the Default Logger to write log messages.
    /// \param logger New logger to be registered within the default logger. You must allocate the logger dynamically with the new expression.
    /// \deprecated Use the overload with AbstractLoggerUniquePtr parameter.
    static void pushLogger(AbstractLogger* logger)
    {
        s_chainedLogger.push(logger);
    }

    /// Removes the last pushed logger from the Default Logger object.
    ///
    /// When you no longer need the logger which was last pushed to the Default Logger object, use this function to remove that logger.
    static void popLogger()
    {
        s_chainedLogger.pop();
    }

    /// Removes all custom loggers registered within the Default Logger object.
    ///
    /// When you call this function, all custom loggers that were pushed with pushLogger() are popped from the Default Logger object.
    /// After you call this function, the log messages written using the Default Logger object are not written anywhere.
    static void popAllLoggers()
    {
        s_chainedLogger.popAll();
    }

    /// Gets the reference to the Default Logger object.
    ///
    /// \return Default Logger object.
    static AbstractLogger& get()
    {
        return s_chainedLogger;
    }

private:

    /// Deleted copy constructor because we do not want this object to be copied.
    explicit DefaultLogger(const DefaultLogger& origin) KZ_DELETED_FUNCTION;

    /// Deleted assignment operator because we do not want this object to be assigned to other object.
    DefaultLogger& operator= (const DefaultLogger& origin) KZ_DELETED_FUNCTION;

    /// Chained logger object.
    static detail::ChainedLogger s_chainedLogger;
};

}

#endif
