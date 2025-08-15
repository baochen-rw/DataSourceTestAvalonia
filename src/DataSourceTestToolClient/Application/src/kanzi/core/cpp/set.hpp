// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SET_HPP
#define KZ_SET_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/container/set.hpp>

namespace kanzi
{

using boost::container::set;
using boost::container::multiset;

}

#else

#include <set>

namespace kanzi
{

using std::set;
using std::multiset;

}

#endif

#endif
