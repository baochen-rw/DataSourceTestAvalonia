// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LIST_HPP
#define KZ_LIST_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/container/list.hpp>

namespace kanzi
{

using boost::container::list;

}

#else


#include <list>

namespace kanzi
{

using std::list;

}

#endif

#endif
