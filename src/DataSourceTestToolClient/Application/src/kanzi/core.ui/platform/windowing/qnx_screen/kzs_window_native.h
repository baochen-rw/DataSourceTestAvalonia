/**
* \file
* Kanzi window, native part for Screen platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <screen/screen.h>

/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Realizes the window using a given graphics configuration and padding size. */
kzsError kzsWindowNativeRealize(struct KzsWindowNative* windowNative, EGLDisplay eglDisplay, EGLConfig eglConfiguration, EGLint paddingSize);
/// Returns the native Screen window.
screen_window_t* kzsWindowNativeGetScreenWindow(struct KzsWindowNative* windowNative);
/// Returns the window group name.
const char* kzsWindowNativeGetWindowGroupName(struct KzsWindowNative* windowNative);
/** Returns the native EGL window. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);
/** Returns the native EGL display. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);


#endif
