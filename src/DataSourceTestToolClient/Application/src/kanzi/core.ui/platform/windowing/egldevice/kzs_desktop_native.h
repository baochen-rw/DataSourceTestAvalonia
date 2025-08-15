// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>


struct KzsDesktopNative;
struct KzsWindowNative;


/// Get the EGL native display.
/// \param desktopNative Handle to desktop-native.
/// \return Handle to EGL native display.
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/// Get the EGL display of desktop.
/// \param desktopNative Handle to desktop-native.
/// \return EGLDisplay handle of the desktop.
EGLDisplay kzsDesktopNativeGetDisplay(const struct KzsDesktopNative* desktopNative);

/// Get the EGL output-layer for the display index.
/// \param desktopNative Handle to desktop-native.
/// \param displayID Index of the display.
/// \return Handle to EGL output-layer.
EGLOutputLayerEXT kzsDesktopNativeGetOutputLayer(const struct KzsDesktopNative* desktopNative, kzUint displayID);


#endif
