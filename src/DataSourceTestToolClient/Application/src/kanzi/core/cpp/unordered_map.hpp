// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_UNORDERED_MAP_HPP
#define KZ_UNORDERED_MAP_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/unordered_map.hpp>

namespace kanzi
{

using boost::unordered_map;

}

#else

#include <unordered_map>

namespace kanzi
{

using std::unordered_map;

}

#endif

namespace kanzi
{

template <class K, class T, class H, class P, class A, class Predicate>
void erase_if(unordered_map<K, T, H, P, A>& c, Predicate pred)
{
    for (typename unordered_map<K, T, H, P, A>::iterator it = c.begin(), endIt = c.end(); it != endIt; )
    {
        if (pred(*it))
        {
            it = c.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

}

#endif
