/**
* \file
* Kanzi window, nogl implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/windowing/common/kzs_window.h>

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
# include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#endif


struct KzsWindowNative;


#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#endif


#endif
