// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_VECTOR_HPP
#define KZ_VECTOR_HPP

#include "platform.hpp"
#include "algorithm.hpp"

#if defined KZ_EMULATE_CXX11_STD || defined KZ_USE_BOOST_VECTOR

#if (_NTO_VERSION < 660)
namespace boost {
    using ::intptr_t;
    using ::uintptr_t;
}
#endif

#include <boost/container/vector.hpp>

namespace kanzi
{

using boost::container::vector;

}

#else

#include <vector>

namespace kanzi
{

using std::vector;

}

#endif

namespace kanzi
{

template <typename T, typename A, typename U>
void erase(vector<T, A>& c, const U& value)
{
    c.erase(remove(c.begin(), c.end(), value), c.end());
}

template <typename T, typename A, typename U>
void erase_if(vector<T, A>& c, const U& predicate)
{
    c.erase(remove_if(c.begin(), c.end(), predicate), c.end());
}

template <typename T, typename A, typename U>
bool contains(const vector<T, A>& c, const U& value)
{
    return find(c.begin(), c.end(), value) != c.end();
}

}

#endif
