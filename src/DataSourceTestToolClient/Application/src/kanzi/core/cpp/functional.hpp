// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FUNCTIONAL_HPP
#define KZ_FUNCTIONAL_HPP

#include "platform.hpp"

#include <functional>

namespace kanzi
{

using std::equal_to;

} // End of kanzi namespace.


#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_BIND)

#include <boost/bind.hpp>

namespace kanzi
{
using boost::bind;

namespace placeholders
{
using boost::placeholders::_1;
using boost::placeholders::_2;
using boost::placeholders::_3;
using boost::placeholders::_4;
using boost::placeholders::_5;
using boost::placeholders::_6;
using boost::placeholders::_7;
using boost::placeholders::_8;
using boost::placeholders::_9;
} // End of placeholders namespace.

} // End of kanzi namespace.

#else

namespace kanzi
{
using std::bind;

namespace placeholders
{
using namespace std::placeholders;
} // End of placeholders namespace.

} // End of kanzi namespace.

#endif


#if defined(KZ_EMULATE_CXX11_STD)

#include <boost/function.hpp>
#include <boost/functional/hash.hpp>
#include <boost/mem_fn.hpp>

namespace kanzi
{

using boost::cref;
using boost::function;
using boost::ref;

using boost::mem_fn;

using boost::hash;

} // End of kanzi namespace.

#else

namespace kanzi
{

using std::cref;
using std::function;
using std::ref;

using std::mem_fn;

using std::hash;

} // End of kanzi namespace.

#endif

#endif // KZ_FUNCTIONAL_HPP
