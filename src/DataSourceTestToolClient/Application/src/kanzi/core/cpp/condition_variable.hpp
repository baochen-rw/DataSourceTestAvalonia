// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CONDITION_VARIABLE_HPP
#define KZ_CONDITION_VARIABLE_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_CONDITION_VARIABLE)

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include <boost/thread/condition_variable.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

namespace kanzi
{

using boost::condition_variable;

}

#else

#include <condition_variable>

namespace kanzi
{

using std::condition_variable;

}

#endif

#endif
