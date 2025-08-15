// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PLATFORM_VARIANT_HPP
#define KZ_PLATFORM_VARIANT_HPP

#include "platform.hpp"

#if defined _MSC_VER
#pragma warning(push)

// C4345: behavior change : an object of POD type constructed with an initializer of the form() will be default - initialized
#pragma warning(disable : 4345)

// Without this there is huge amount of warnings from when exceptions are disabled:
// C4127: conditional expression is constant
#pragma warning(disable : 4127)

// Without this the MSVC 2017 static analysis gives warnings:
// C26495 : Variable 'boost::variant<...>::which_' is uninitialized.Always initialize a member variable(type .6).
#pragma warning(disable : 26495)

#endif

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

namespace kanzi
{

using boost::variant;
using boost::get;

typedef boost::blank monostate;

}

#endif
