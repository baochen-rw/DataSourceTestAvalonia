/**
* \file
* Kanzi desktop, native portion for the fbdev platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>


/** Overrides the dimensions of the desktop */
kzsError kzsDesktopNativeSetDimensions(struct KzsDesktopNative* desktopNative, kzUint width, kzUint height);


#endif
