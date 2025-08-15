/**
* \file
* Kanzi desktop, native portion for the Screen platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <screen/screen.h>

/* Forwards declarations. */
struct KzsDesktopNative;


/** Gets native Screen context. */
screen_context_t* kzsDesktopNativeGetScreenContext(struct KzsDesktopNative* desktopNative);


#endif
