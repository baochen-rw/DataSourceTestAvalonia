/**
 * \file
 * Exact Kanzi types - 8 bit, 16 bit, 32 bit, 64 bit
 *
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_STDINT_H
#define KZS_STDINT_H

#ifdef _MSC_VER
#include <cstdint>
#else
#include <boost/cstdint.hpp>
#endif
#include <stdint.h>

/*
We use boost/cstdint to detect current platform's integer types.
If this fails on some platform, type definitions should be added into this header.
On Windows with Visual Studio, we use standard <cstdint> instead of Boost.
*/

/** Unsigned 8-bit type. */
typedef uint8_t kzU8;
/** Signed 8-bit type. */
typedef int8_t kzS8;

/** Unsigned 16-bit type. */
typedef uint16_t kzU16;
/** Signed 16-bit type. */
typedef int16_t kzS16;

/** Unsigned 32-bit type. */
typedef uint32_t kzU32;
/** Signed 32-bit type. */
typedef int32_t kzS32;

/** Unsigned 64-bit type. */
typedef uint64_t kzU64;
/** Signed 64-bit type. */
typedef int64_t kzS64;

#endif
