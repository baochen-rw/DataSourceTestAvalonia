// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CSTDIO_HPP
#define KZ_CSTDIO_HPP

#include <cstdio>
#include <kanzi/core/cpp/platform.hpp>

namespace kanzi
{

using std::fprintf;

}

#if defined (KZ_EMULATE_CXX11_STD) || defined (KZ_USE_C99_SNPRINTF)

namespace kanzi
{

using ::snprintf;

}

#else

#if defined (KZ_EMULATE_CXX11_SNPRINTF)

namespace kanzi
{

/// Emulates C++11 snprintf behavior.
KANZI_API int snprintf(char* buffer, size_t size, const char* format, ...);

}

#else

namespace kanzi
{

using std::snprintf;

}

#endif

#endif

#endif
