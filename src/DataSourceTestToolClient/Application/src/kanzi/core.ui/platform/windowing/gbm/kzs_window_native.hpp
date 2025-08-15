// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_WINDOW_NATIVE_HPP
#define KZS_WINDOW_NATIVE_HPP

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/// Get the EGL native window.
/// \param windowNative Handle to window-native.
/// \return Handle to EGL native window.
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/// Schedule a page-flip, window-surface should be swapped prior to this.
/// \param windowNative Handle to window-native.
/// \return ::KZS_SUCCESS on success.
kzsError kzsWindowNativeFlipPage(struct KzsWindowNative* windowNative);


#endif
