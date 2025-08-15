// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FUTURE_HPP
#define KZ_FUTURE_HPP

#include "platform.hpp"

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_FUTURE)

#include <boost/thread/future.hpp>

namespace kanzi
{

using boost::async;
using boost::promise;
using boost::future;

}

#else

#include <future>

namespace kanzi
{

using std::async;
using std::promise;
using std::future;

}

#endif

#endif
