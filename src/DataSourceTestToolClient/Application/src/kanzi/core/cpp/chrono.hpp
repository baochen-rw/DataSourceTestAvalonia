// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CHRONO_HPP
#define KZ_CHRONO_HPP

#include "platform.hpp"

#if (defined KZ_EMULATE_CXX11_STD) || (defined KZ_USE_BOOST_CHRONO)

#ifdef _MSC_VER
// Boost Chrono headers include windows.h.
#include <kanzi/core/platform/cpp/win32/pre_windows.hpp>
#endif

#include <boost/chrono/chrono.hpp>

#ifdef _MSC_VER
#include <kanzi/core/platform/cpp/win32/post_windows.hpp>
#endif

namespace kanzi
{

namespace chrono
{

using boost::chrono::duration;
using boost::chrono::duration_cast;
using boost::chrono::duration_values;
#ifndef SPANSION
using boost::chrono::high_resolution_clock;
#endif
using boost::chrono::hours;
using boost::chrono::microseconds;
using boost::chrono::milliseconds;
using boost::chrono::minutes;
using boost::chrono::nanoseconds;
using boost::chrono::seconds;
//using boost::chrono::steady_clock;
// Kanzi Lite does support system_clock.
#ifndef SPANSION
using boost::chrono::system_clock;
#endif
using boost::chrono::time_point;
using boost::chrono::time_point_cast;

}

}

#else

#include <chrono>

namespace kanzi
{

namespace chrono
{

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::duration_values;
using std::chrono::high_resolution_clock;
using std::chrono::hours;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::minutes;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::time_point_cast;

}

}

#endif

#endif
