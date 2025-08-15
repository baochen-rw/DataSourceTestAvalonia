/**
* \file
* Kanzi window, native part for X11-GLX platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/windowing/common/kzs_window.h>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
# include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#endif

#include <X11/Xlib.h>


struct KzsWindowNative;


Window kzsWindowNativeGetWindow(const struct KzsWindowNative* windowNative);

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
/** Gets EGL native window type. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

#endif


#endif
