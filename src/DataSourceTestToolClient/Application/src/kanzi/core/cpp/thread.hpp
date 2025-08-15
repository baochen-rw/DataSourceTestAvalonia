// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_THREAD_HPP
#define KZ_THREAD_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_THREAD)

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include <boost/thread/thread.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif


namespace kanzi
{

using boost::thread;

namespace this_thread
{

using boost::this_thread::get_id;

}

}

#else

#include <thread>

namespace kanzi
{

using std::thread;

namespace this_thread
{

using std::this_thread::get_id;

}

}

#endif

#endif
