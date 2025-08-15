/**
* \file
* Kanzi display, native portion for the Screen platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <screen/screen.h>


/* Forward declarations. */
struct KzsDisplayNative;


/** Returns native Screen display. */
screen_display_t* kzsDisplayNativeGetScreenDisplay(struct KzsDisplayNative* displayNative);


#endif
