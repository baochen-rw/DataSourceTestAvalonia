// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <wfd.h>

/// Get the EGL native display.
/// \param desktopNative Handle to desktop-native.
/// \param displayNative Handle to display-native.
/// \param windowNative Handle to window-native.
/// \return Handle to EGL native display.
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/// Get WFD port native handle.
/// \param displayNative Handle to display-native.
/// \return WFD port handle.
WFDPort kzsDisplayNativeGetHandle(const struct KzsDisplayNative* displayNative);


/// Get WFD port mode handle.
/// \param displayNative Handle to display-native.
/// \return WFD mode handle.
WFDPortMode kzsDisplayNativeGetMode(const struct KzsDisplayNative* displayNative);

#endif
