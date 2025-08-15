// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


// Forward declarations.
struct KzsWindowNative;


/// Get the EGL native window.
/// \param windowNative Handle to window-native.
/// \return Handle to EGL native window.
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/// Realizes the window using a given graphics configuration.
/// \param windowNative Handle to window-native.
/// \param eglDisplay Handle to egl display.
/// \param eglConfiguration Handle to eglConfiguration.
/// \param paddingSize Size of padding per pixel.
kzsError kzsWindowNativeRealize(struct KzsWindowNative* windowNative, EGLDisplay eglDisplay, EGLConfig eglConfiguration, EGLint paddingSize);


#endif
