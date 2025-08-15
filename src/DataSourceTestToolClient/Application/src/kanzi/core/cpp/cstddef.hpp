// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CSTDDEF_HPP
#define KZ_CSTDDEF_HPP

#include <cstddef>


namespace kanzi
{

using std::size_t;

}

#if __cplusplus < 201703L

namespace kanzi
{

typedef unsigned char byte;

}

#else

namespace kanzi
{

using std::byte;

}

#endif

#endif // KZ_CSTDDEF_HPP
