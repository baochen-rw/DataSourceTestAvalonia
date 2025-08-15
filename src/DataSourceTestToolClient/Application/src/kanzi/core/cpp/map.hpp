// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MAP_HPP
#define KZ_MAP_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_MAP)

#include <boost/container/map.hpp>

namespace kanzi
{

using boost::container::map;
using boost::container::multimap;

}

#else

#include <map>

namespace kanzi
{

using std::map;
using std::multimap;

}

#endif

#endif
