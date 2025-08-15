// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CSTDINT_HPP
#define KZ_CSTDINT_HPP

#if defined(KZ_USE_BOOST_STDINT) && !defined(_MSC_VER)

#include <boost/cstdint.hpp>

#elif _MSC_VER // Visual Studio

#include <cstdint>

#elif __cplusplus < 201103L

#include <stdint.h>

#else

#include <cstdint>

#endif

#endif
