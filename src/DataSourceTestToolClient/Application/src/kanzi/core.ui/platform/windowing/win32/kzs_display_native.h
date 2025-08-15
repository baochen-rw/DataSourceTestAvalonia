/**
* \file
* Kanzi display, native portion for the win32 platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <kanzi/core/platform/cpp/win32/windows.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations. */
struct KzsDisplayNative;


/** Returns the name of the display adapter device. */
LPCTSTR kzsDisplayNativeGetDeviceName(const struct KzsDisplayNative* displayNative);

/** Returns the x coordinate of the display with respect to the desktop. */
kzUint kzsDisplayNativeGetCurrentX(const struct KzsDisplayNative* displayNative);
/** Returns the y coordinate of the display with respect to the desktop. */
kzUint kzsDisplayNativeGetCurrentY(const struct KzsDisplayNative* displayNative);


#endif
