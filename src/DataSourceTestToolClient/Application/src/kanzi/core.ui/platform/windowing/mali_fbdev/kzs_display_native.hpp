// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DISPLAY_NATIVE_HPP
#define KZS_DISPLAY_NATIVE_HPP

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>


// Forward declarations.
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/// Get the EGL native display.
/// \param desktopNative Handle to desktop-native.
/// \param displayNative Handle to display-native.
/// \param windowNative Handle to window-native.
/// \return Handle to EGL native display.
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);


#endif
