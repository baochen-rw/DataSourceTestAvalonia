/**
 * \file
 * Native window system handle types.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_NATIVE_HANDLE_H
#define KZS_NATIVE_HANDLE_H


#if defined _MSC_VER || defined __MINGW32__

// Win32
struct HWND__;
typedef struct HWND__* HWND;
typedef HWND NativeWindowHandle;

#elif defined ANDROID

// Android
#include <android/native_window.h>
typedef ANativeWindow* NativeWindowHandle;

#elif defined X11

// X11
#include <X11/X.h>
typedef Window NativeWindowHandle;


#elif defined YUNOS

#include <kanzi/core/cpp/memory.hpp>
#include <yunos/RenderSurface.h>

typedef kanzi::shared_ptr<yunos::RenderSurface> NativeWindowHandle;

// Needs to be before EGL_API_FB.
#elif defined WAYLAND

// Wayland
#include <wayland-egl.h>
typedef struct wl_egl_window* NativeWindowHandle;

#elif defined EGL_API_FB

// iMX6
#include <EGL/eglvivante.h>
typedef struct _FBWindow * NativeWindowHandle;

#elif defined WFD

struct wfd_window_t;
typedef wfd_window_t* NativeWindowHandle;

#elif defined MALI_FB

// Mali fbdev
#include <EGL/fbdev_window.h>
typedef struct fbdev_window* NativeWindowHandle;

#elif defined QNX_SCREEN

// QNX
#include <screen/screen.h>
typedef screen_window_t NativeWindowHandle;

#elif defined __GBM__

// Linux gbm-buffers
#include <stddef.h>
#include <gbm.h>
typedef struct gbm_surface* NativeWindowHandle;

#elif defined WSEGL || defined __WINSCW__

// PVR nullws
typedef void* NativeWindowHandle;

#elif defined INTEGRITY

#include <device/fbdriver.h>
typedef struct _FBWindow *  NativeWindowHandle;

#elif defined SPANSION

typedef void* NativeWindowHandle;

#else

#error NativeWindowHandle not defined for this platform.

#endif

#endif
