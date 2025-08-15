// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TUPLE_HPP
#define KZ_TUPLE_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
#endif

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

namespace kanzi
{

using boost::tuple;
using boost::make_tuple;
using boost::tie;
using boost::get;

}

#else

#include <tuple>

namespace kanzi
{

using std::tuple;
using std::make_tuple;
using std::tie;
using std::get;

}

#endif

#endif
