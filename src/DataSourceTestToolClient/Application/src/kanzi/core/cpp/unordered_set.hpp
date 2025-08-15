// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_UNORDERED_SET_HPP
#define KZ_UNORDERED_SET_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/unordered_set.hpp>

namespace kanzi
{

using boost::unordered_set;

}

#else

#include <unordered_set>

namespace kanzi
{

using std::unordered_set;

}

#endif

#endif
