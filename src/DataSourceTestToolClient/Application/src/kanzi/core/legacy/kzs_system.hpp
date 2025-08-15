/**
 * \file
 * System header.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_SYSTEM_H
#define KZS_SYSTEM_H

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

/** Initializes the system. */
KANZI_API kzsError kzsSystemInitialize(void);

/** Uninitializes the system. */
KANZI_API kzsException kzsSystemUninitialize(void);

/** Converts a 32-bit floating point number to 4 bytes in little-endian format. */
void kzsFloatToBytesLittleEndian(kzFloat floatValue, kanzi::byte* out_floatBytes);

/** Converts a 32-bit floating point number to 4 bytes in big-endian format. */
void kzsFloatToBytesBigEndian(kzFloat floatValue, kanzi::byte* out_floatBytes);

/** Converts 4 bytes of floating point value from little-endian format to a 32-bit floating point number. */
kzFloat kzsBytesToFloatLittleEndian(const kanzi::byte* floatBytes);

/** Converts 4 bytes of floating point value from big-endian format to a 32-bit floating point number. */
kzFloat kzsBytesToFloatBigEndian(const kanzi::byte* floatBytes);

/** Returns the Kanzi version string constant. */
kzString kzsGetVersionString(void);


#endif
