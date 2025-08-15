// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIME_CONVERSION_HPP
#define KZ_TIME_CONVERSION_HPP

#include <kanzi/core/cpp/chrono.hpp>

#include <sys/time.h>


namespace kanzi
{

/// Converts C++ milliseconds to POSIX native nanosecond format.
timespec millisecondsToTimespec(chrono::milliseconds ms);

/// Converts C++ milliseconds to POSIX native microsecond format.
timeval millisecondsToTimeval(chrono::milliseconds ms);

}


#endif

