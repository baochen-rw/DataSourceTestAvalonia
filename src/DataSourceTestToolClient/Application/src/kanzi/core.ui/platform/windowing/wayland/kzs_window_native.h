/**
* \file
* Kanzi window, Wayland implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H

#define __WAYLAND__

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>

#include <wayland-client.h>
#include <wayland-egl.h>


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;
struct wl_surface;


/** Gets EGL native window. */
EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/** Gets WL native surface. */
struct wl_surface* kzsWindowNativeGetWLSurface(const struct KzsWindowNative* windowNative);

/** Sets if surface frame is available.
 *  This function is thread safe.
 */
void kzsWindowNativeSetSurfaceFrameAvailable(struct KzsWindowNative* windowNative, bool value);

/** Checks if surface frame is available.
 *  This function is thread safe.
 */
bool kzsWindowNativeGetSurfaceFrameAvailable(const struct KzsWindowNative* windowNative);

/** Marks surface frame available.
 *  This function is thread safe.
 */
void kzsWindowNativeMarkSurfaceFrameAvailable(struct KzsWindowNative* windowNative);

/** Marks surface frame unavailable.
 *  This function is thread safe.
 */
void kzsWindowNativeMarkSurfaceFrameConsumed(struct KzsWindowNative* windowNative);

#endif
