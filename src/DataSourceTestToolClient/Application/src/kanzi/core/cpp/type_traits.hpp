// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TYPE_TRAITS_HPP
#define KZ_TYPE_TRAITS_HPP

#include "platform.hpp"

// QNX type_traits is not fully c++11 compliant.
// GCC type_traits before 5.0.0 is not C++11 compliant.
#if defined KZ_EMULATE_CXX11_STD || defined QNX || (defined KZ_GCC_VERSION && KZ_GCC_VERSION < 50000)

#include <boost/type_traits.hpp>

namespace kanzi
{

using boost::has_trivial_destructor;
using boost::is_base_of;
using boost::is_enum;
using boost::is_nothrow_move_constructible;
using boost::has_trivial_copy;
using boost::is_pointer;
using boost::is_arithmetic;
using boost::is_floating_point;
using boost::is_array;
using boost::is_void;

template<bool _Test,
class _Type = void>
struct enable_if
{
};

template<class _Type>
struct enable_if<true, _Type>
{
    typedef _Type type;
};

}

#define KZ_IS_TRIVIALLY_COPYABLE        has_trivial_copy
#define KZ_IS_TRIVIALLY_DESTRUCTIBLE    has_trivial_destructor

#else

#include <type_traits>

namespace kanzi
{

using std::is_trivially_destructible;
using std::is_base_of;
using std::is_enum;
using std::is_nothrow_move_constructible;
using std::is_trivially_copyable;
using std::enable_if;
using std::is_pointer;
using std::is_arithmetic;
using std::is_floating_point;
using std::is_array;
using std::is_void;

}

#define KZ_IS_TRIVIALLY_COPYABLE        is_trivially_copyable
#define KZ_IS_TRIVIALLY_DESTRUCTIBLE    is_trivially_destructible

#endif

#endif
