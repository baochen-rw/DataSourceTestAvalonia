/**
* \file
* Kanzi display, GHS FB API implementation.
*
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <kanzi/core/legacy/kzs_types.hpp>

struct KzsDisplayNative;

/** Returns the id of given native display */
kzUint kzsDisplayNativeGetDisplayID(const struct KzsDisplayNative* displayNative);


#endif
