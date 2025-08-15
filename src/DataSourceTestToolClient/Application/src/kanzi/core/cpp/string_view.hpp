// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STRING_VIEW_HPP
#define KZ_STRING_VIEW_HPP

#include "platform.hpp"

#if __cplusplus >= 201703L || _MSC_VER >= 1910    // C++17 / Visual Studio 2017 or higher

#include <string_view>

namespace kanzi
{

using std::basic_string_view;
using std::string_view;
using std::wstring_view;

}

#else

#include "iterator.hpp"
#include "functional.hpp"

#include <boost/utility/string_view.hpp>

namespace kanzi
{

using boost::basic_string_view;
using boost::string_view;
using boost::wstring_view;

}


KZ_CPP_SPECIALIZE_TR1_BEGIN

/// Hash for string_view.
/// Taken from http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
template<>
struct hash<kanzi::string_view>
{
public:

    size_t operator()(const kanzi::string_view& s) const
    {
        size_t hash = 0;
        for (kanzi::string_view::const_iterator it = kanzi::cbegin(s), end = kanzi::cend(s); it != end; ++it)
        {
            hash = hash * 101 + *it;
        }

        return hash;
    }
};

KZ_CPP_SPECIALIZE_TR1_END

#endif

#endif
