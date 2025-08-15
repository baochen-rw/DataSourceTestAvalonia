/**
* \file
* Kanzi window, YunOS implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#include <kanzi/core.ui/platform/windowing/common/kzs_native_handles.h>

/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;

/// Gets EGL native display.
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/// Gets EGL native window.
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/// Returns the YunOS Window handle.
NativeWindowHandle kzsWindowNativeGetPlatformWindow(const struct KzsWindowNative* windowNative);

#endif
