// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ATOMIC_HPP
#define KZ_ATOMIC_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_THREAD)

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#include <boost/atomic.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

namespace kanzi
{

using boost::atomic;

}

#else

#include <atomic>

namespace kanzi
{

using std::atomic;

}

#endif

#endif