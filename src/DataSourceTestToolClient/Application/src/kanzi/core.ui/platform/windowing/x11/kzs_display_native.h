/**
* \file
* Kanzi display, native portion for the Linux-X11-GLX platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <X11/Xlib.h>


/* Forward declarations. */
struct KzsDisplayNative;


/** Returns the X11 Screen object for this display. */
Screen* kzsDisplayNativeGetX11Screen(const struct KzsDisplayNative* displayNative);


#endif
