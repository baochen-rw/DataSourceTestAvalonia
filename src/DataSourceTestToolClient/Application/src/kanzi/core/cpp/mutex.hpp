// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MUTEX_HPP
#define KZ_MUTEX_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_MUTEX)

#include <boost/thread/lock_types.hpp>
#include <boost/thread/lock_guard.hpp>

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include <boost/thread/mutex.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif


namespace kanzi
{

using boost::lock_guard;
using boost::mutex;
using boost::unique_lock;

}

#else

#include <mutex>

namespace kanzi
{
    
using std::lock_guard;
using std::mutex;
using std::unique_lock;

}

#endif

#endif
