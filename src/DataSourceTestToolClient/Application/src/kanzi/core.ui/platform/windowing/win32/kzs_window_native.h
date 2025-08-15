/**
* \file
* Kanzi window, native portion for the win32 platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_NATIVE_H
#define KZS_WINDOW_NATIVE_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core.ui/platform/windowing/common/kzs_native_handles.h>

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#endif

#include <kanzi/core/platform/cpp/win32/windows.hpp>


/* Forward declarations. */
struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsEventQueue;
struct NativeWindowProperties;


/** 
 * \struct KzsWindowNative Native window for Win32.
 */
struct KzsWindowNative;


/** Creates empty wrapper window for a given window handle. */
KANZI_API kzsError kzsWindowNativeCreateWrapper(NativeWindowHandle windowHandle, struct NativeWindowProperties* out_windowProperties, struct KzsWindowNative** out_windowNative);

/** Returns the win32 window handle. */
KANZI_API HWND kzsWindowNativeGetHandle(const struct KzsWindowNative* windowNative);

/** Sets touch state for native window. */
KANZI_API void kzsWindowNativeSetTouchState(struct KzsWindowNative* windowNative, kzBool inTouch);

/** Gets touch state for native window. */
KANZI_API kzBool kzsWindowNativeGetTouchState(struct KzsWindowNative* windowNative);

/** Returns the win32 device context handle. */
KANZI_API HDC kzsWindowNativeGetHDC(const struct KzsWindowNative* windowNative);

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
/** Gets EGL native window type. */
KANZI_API EGLNativeWindowType kzsEGLGetNativeWindow(const struct KzsWindowNative* windowNative);

/** Gets EGL native display type. */
KANZI_API EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                                      const struct KzsDisplayNative* displayNative,
                                                      const struct KzsWindowNative* windowNative);
#endif


#endif
