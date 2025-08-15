/**
* \file
* Kanzi display, native portion for fbdev.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <kanzi/core/legacy/kzs_types.hpp>


struct KzsDisplayNative;

/** Get the index number of the framebuffer device. */
kzUint kzsDisplayNativeGetDisplayIndex(const struct KzsDisplayNative* displayNative);


#endif
