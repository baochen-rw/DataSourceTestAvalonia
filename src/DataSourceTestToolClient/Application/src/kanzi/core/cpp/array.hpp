// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ARRAY_HPP
#define KZ_ARRAY_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/array.hpp>

namespace kanzi
{

using boost::array;

}

#else

#include <array>

namespace kanzi
{

using std::array;

}

#endif

namespace kanzi
{

template <typename T, size_t Size, typename U>
bool contains(const array<T, Size>& c, const U& value)
{
    return find(cbegin(c), cend(c), value) != cend(c);
}

}

#endif
