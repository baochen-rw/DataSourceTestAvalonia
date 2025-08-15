/**
* \file
* Kanzi window, native part for fbdev.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>


struct KzsWindowNative;


/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);


#endif
