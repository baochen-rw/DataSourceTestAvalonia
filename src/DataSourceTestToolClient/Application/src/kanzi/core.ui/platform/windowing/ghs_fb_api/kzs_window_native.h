/**
* \file
* Kanzi window, GHS FB API implementation.
*
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <kanzi/core/legacy/debug/kzs_error.hpp>


#define __WSEGL__

/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Gets EGL native window. */
EGLNativeWindowType kzsEGLGetNativeWindow(struct KzsWindowNative* windowNative);

/** Gets EGL native display. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/** . */
kzsError kzsWindowNativeSetEGLSurface(struct KzsWindowNative* windowNative, EGLSurface* surface, EGLDisplay* display);


#endif
