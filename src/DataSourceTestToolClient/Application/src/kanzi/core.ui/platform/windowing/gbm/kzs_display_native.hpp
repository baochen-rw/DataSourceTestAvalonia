// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DISPLAY_NATIVE_HPP
#define KZS_DISPLAY_NATIVE_HPP

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;

EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);

/// Schedule a page-flip, swap-buffers should be called prior to this.
/// This function internally first schedules a page flip with kzsDisplayNativePageFlipInvoke(),
/// then waits for the synchronization using kzsDisplayNativePageFlipWait().
/// \param displayNative Handle to display-native.
/// \param fd File handle to drm device or control-device.
/// \param fbId Handle to the framebuffer.
/// \return ::KZS_SUCCESS on success.
kzsError kzsDisplayNativePageFlip(struct KzsDisplayNative* displayNative, int fd, int fbId);

/// Queues to page flip to happen on next vblank.
/// \param displayNative Handle to display-native.
/// \param fd File handle to drm device or control-device.
/// \param fbId Handle to the framebuffer.
/// \return ::KZS_SUCCESS on success.
kzsError kzsDisplayNativePageFlipInvoke(struct KzsDisplayNative* displayNative, int fd, int fbId);

/// Waits for vblank signal that is sent on page flip.
/// Must be called from the same thread as kzsDisplayNativePageFlipInvoke().
/// \param displayNative Handle to display-native.
/// \param fd File handle to drm device or control-device.
/// \return ::KZS_SUCCESS on success.
kzsError kzsDisplayNativePageFlipWait(struct KzsDisplayNative* displayNative, int fd);

/// Set the mode for the display.
/// \param displayNative Handle to display-native.
/// \param fd File handle to drm device or control-device.
/// \param fbId Handle to the framebuffer.
/// \return ::KZS_SUCCESS on success.
kzsError kzsDisplayNativeModeSet(struct KzsDisplayNative* displayNative, int fd, int fbId);

/// Restore original mode of the display.
/// \param displayNative Handle to display-native.
/// \param fd File handle to drm device or control-device.
/// \param fbId Handle to the framebuffer.
/// \return ::KZS_SUCCESS on success.
kzsError kzsDisplayNativeRestoreMode(struct KzsDisplayNative* displayNative, int fd);

/// Check if display is connected.
/// \param displayNative Handle to display-native.
/// \return true if display connected and usable, otherwise false.
bool kzsDisplayNativeIsConnected(struct KzsDisplayNative* displayNative);

#endif
