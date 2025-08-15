// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_SYSTEM_ERROR_HPP
#define KZ_SYSTEM_ERROR_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/system/system_error.hpp>

namespace kanzi
{

using boost::system::error_code;
using boost::system::errc::make_error_code;

namespace errc
{

using namespace boost::system::errc;

}

}
#else

#include <system_error>

namespace kanzi
{

using std::error_code;
using std::make_error_code;
using std::errc;

}

#endif

#endif

#endif
