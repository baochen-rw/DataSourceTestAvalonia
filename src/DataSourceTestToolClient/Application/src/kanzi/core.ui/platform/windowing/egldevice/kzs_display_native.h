// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DISPLAY_NATIVE_H
#define KZS_DISPLAY_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>


/// Get the EGL output-layer for the display.
/// \param displayNative Handle to display-native.
/// \return Handle to EGL output-layer.
EGLOutputLayerEXT kzsDisplayNativeGetOutputLayer(const struct KzsDisplayNative* displayNative);


#endif
