/**
* \file
* Kanzi window, native part for Android platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Foward declarations. */
struct ANativeWindow;
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Creates native window from Android window. */
kzsError kzsWindowNativeCreateWrapper(ANativeWindow* windowHandle, struct KzsWindowNative** out_windowNative);

/** Retrieve Android window (originates from Java side Surface) from native window. */
ANativeWindow* kzsWindowNativeGetAndroidWindow(const struct KzsWindowNative* windowNative);
/** Pass Android window (originates from Java side Surface) to native window. */
kzsError kzsWindowNativeSetAndroidNativeWindow(struct KzsWindowNative* windowNative, ANativeWindow* androidNativeWindow);

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);
/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#endif


#endif
