/**
* \file
* Kanzi desktop, Wayland implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <wayland-client.h>


struct KzsDesktopNative;
struct KzsWindowNative;
struct KzsDisplayNative;

struct ivi_application;
struct xdg_shell;
struct ias_shell;


/// Dispatch the wayland default queue.
/// \param desktopNative Handle to desktop-native.
void kzsDesktopNativeDispatch(const struct KzsDesktopNative* desktopNative);

/// Dispatch wayland queue.
/// \param desktopNative Handle to desktop-native.
/// \param queue The wayland-queue to be dispatched.
void kzsDesktopNativeDispatchQueue(const struct KzsDesktopNative* desktopNative, struct wl_event_queue* queue);

/// Get the wayland compositor.
/// \param desktopNative Handle to desktop-native.
struct wl_compositor* kzsDesktopNativeGetCompositor(const struct KzsDesktopNative* desktopNative);

/// Get the wayland shell.
/// \param desktopNative Handle to desktop-native.
struct wl_shell* kzsDesktopNativeGetShell(const struct KzsDesktopNative* desktopNative);

/// Get the ias shell.
/// \param desktopNative Handle to desktop-native.
struct ias_shell* kzsDesktopNativeGetIasShell(const struct KzsDesktopNative* desktopNative);

/// Get the xdg-shell.
/// \param desktopNative Handle to desktop-native.
struct xdg_shell* kzsDesktopNativeGetXdgShell(const struct KzsDesktopNative* desktopNative);

/// Get the ivi-application.
/// \param desktopNative Handle to desktop-native.
struct ivi_application* kzsDesktopNativeGetIVIApplication(const struct KzsDesktopNative* desktopNative);

/// Get the wayland display.
/// \param desktopNative Handle to desktop-native.
struct wl_display* kzsDesktopNativeGetDisplay(const struct KzsDesktopNative* desktopNative);

/// Get wayland handle for an input seat.
/// \param desktopNative Handle to desktop-native.
/// \param seatIndex index of the seat
/// \return The wayland handle for the seatIndex specified in parameters, nullptr if seatIndex is out of range.
struct wl_seat* kzsDesktopNativeGetSeat(const struct KzsDesktopNative *desktopNative, size_t seatIndex);

/// Get number of input seats
/// \param desktopNative Handle to desktop-native.
size_t kzsDesktopNativeGetSeatCount(const struct KzsDesktopNative* desktopNative);

/// Get wayland handle for a display.
/// \param desktopNative Handle to desktop-native.
/// \param displayID The index of the display.
/// \return The wayland handle for the displayID specified in parameters, nullptr if displayID is out of range.
struct wl_output* kzsDesktopNativeGetOutput(const struct KzsDesktopNative* desktopNative, kzUint displayID);

/// Get input-queue for a display.
/// \param desktopNative Handle to desktop-native.
/// \param displayID The index of the display.
/// \return The wayland-queue for the displayID specified in parameters, nullptr if displayID is out of range.
struct wl_event_queue* kzsDesktopNativeGetDisplayQueue(const struct KzsDesktopNative* desktopNative, kzUint displayID);

/// Store the input-device handle.
/// \param desktopNative Handle to desktop-native.
/// \return A wayland-queue reserved for input-related events.
struct wl_event_queue* kzsDesktopNativeGetInputQueue(const struct KzsDesktopNative* desktopNative);

/// Store the input-device handle.
/// This function is thread safe.
/// \param desktopNative Handle to desktop-native.
/// \param device The input device native to be stored.
void kzsDesktopNativeSetInputDeviceNative(struct KzsDesktopNative* desktop, struct KzsInputDeviceNative* device);

/// Get the current input-device handle.
/// This function is thread safe.
/// \param desktopNative Handle to desktop-native.
/// \return The input device native that has been set previously, nullptr if not set.
struct KzsInputDeviceNative* kzsDesktopNativeGetInputDeviceNative(const struct KzsDesktopNative* desktopNative);

/// Store the window handle.
/// This function is thread safe.
/// \param desktopNative Handle to desktop-native.
/// \param windowNative The window to be stored.
void kzsDesktopNativeSetWindowNative(struct KzsDesktopNative* desktopNative, KzsWindowNative* windowNative);

/// Get the current window handle.
/// This function is thread safe.
/// \param desktopNative Handle to desktop-native.
/// \return The window that has been set previously, nullptr if not set.
KzsWindowNative* kzsDesktopNativeGetWindowNative(const struct KzsDesktopNative* desktopNative);

//// Gets EGL native display.
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative, const struct KzsDisplayNative* displayNative, const struct KzsWindowNative* windowNative);


#endif
