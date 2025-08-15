/**
* \file
* Kanzi display, WSEGL implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

/* No platform specific functions. */

/** Gets EGL native display. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

#endif
