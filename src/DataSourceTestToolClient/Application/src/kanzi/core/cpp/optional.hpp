// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_OPTIONAL_HPP
#define KZ_OPTIONAL_HPP

#include "platform.hpp"

#if __cplusplus >= 201703L || _MSC_VER >= 1910    // C++17 / Visual Studio 2017 or higher

#include <optional>

namespace kanzi
{

using std::optional;

using std::nullopt_t;
using std::nullopt;

}

#else

#include <boost/optional/optional.hpp>

namespace kanzi
{

using boost::optional;

namespace
{

// local to translation unit
const boost::none_t& nullopt = boost::detail::optional_detail::none_instance<boost::none_t>::instance;

}

}

#endif

#endif
