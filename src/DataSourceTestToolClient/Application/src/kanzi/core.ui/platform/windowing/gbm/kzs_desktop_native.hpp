// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DESKTOP_NATIVE_HPP
#define KZS_DESKTOP_NATIVE_HPP

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <xf86drmMode.h>


struct KzsDesktopNative;
struct KzsWindowNative;


/// Get DRM device native handle.
/// \param desktopNative Handle to desktop-native.
/// \return File descriptor for DRM device.
int kzsDesktopNativeGetHandle(const struct KzsDesktopNative* desktopNative);

/// Get DRM resource list.
/// \param desktopNative Handle to desktop-native.
/// \return Pointer to Structure of DRM resources.
drmModeRes* kzsDesktopNativeGetResources(const struct KzsDesktopNative* desktopNative);

/// Get name of the DRM driver module.
/// \param desktopNative Handle to desktop-native.
/// \return Name of the DRM driver, null if not known.
const char* kzsDesktopNativeGetDriverName(const struct KzsDesktopNative* desktopNative);

/// Set dimensions of desktop-native
/// \param desktopNative Handle to desktop-native.
/// \param width Desktop width
/// \param height Desktop height
/// \return ::KZS_SUCCESS on success.
kzsError kzsDesktopNativeSetDimensions(struct KzsDesktopNative* desktopNative, kzUint width, kzUint height);

#endif
