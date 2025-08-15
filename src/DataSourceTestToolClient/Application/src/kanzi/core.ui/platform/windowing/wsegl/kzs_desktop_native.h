/**
* \file
* Kanzi desktop, WSEGL implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

struct KzsDesktopNative;
struct KzsWindowNative;


/** Gets EGL native display type. */
NativeDisplayType kzsWindowNativeGetEGLNativeDisplayType(const struct KzsDesktopNative* desktopNative, const struct KzsWindowNative* windowNative);

kzsError kzsDesktopNativeSetDimensions(struct KzsDesktopNative* desktopNative, kzUint width, kzUint height);



#endif
