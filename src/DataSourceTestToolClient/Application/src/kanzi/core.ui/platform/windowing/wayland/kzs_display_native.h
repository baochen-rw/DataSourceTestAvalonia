/**
* \file
* Kanzi display, Wayland implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <wayland-client.h>


struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;

struct wl_output* kzsDisplayNativeGetOutput(const struct KzsDisplayNative* displayNative);


#endif
