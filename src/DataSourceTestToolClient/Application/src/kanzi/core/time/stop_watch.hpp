// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_STOP_WATCH_HPP
#define KZ_STOP_WATCH_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/chrono.hpp>


namespace kanzi
{

/// Stop watch class.
///
/// .
class KANZI_API StopWatch
{
public:
    /// Constructor.
    StopWatch();

    /// Returns the number of milliseconds since the last call to getDeltaTime(),
    /// or the number of milliseconds since the StopWatch was constructed
    /// if this is the first call to getDeltaTime().
    chrono::milliseconds getDeltaTime();

    /// Returns the number of milliseconds since the last call to getDeltaTime(),
    /// or the number of milliseconds since the StopWatch was constructed
    /// if getDeltaTime() has not been called.
    chrono::milliseconds peekDeltaTime() const;

protected:
    unsigned int m_previousTime;        ///< Time during last update.
};

/// Resets the stop watch.
/// This is a convenience function that calls StopWatch::getDeltaTime().
KZ_INLINE void resetStopWatch(StopWatch& stopWatch)
{
    stopWatch.getDeltaTime();
}

}


#endif
