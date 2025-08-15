/**
* \file
* Kanzi desktop, native portion for the X11 platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#endif

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_GLX)
#include <kanzi/core.ui/platform/graphics_context/glx/kzs_glx.h>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>


struct KzsDesktopNative;
struct KzsDisplayNative;
struct KzsWindowNative;


/** Return the X11 display. */
Display* kzsDesktopNativeGetX11Display(const struct KzsDesktopNative* desktopNative);
XContext kzsDesktopNativeGetX11Context(const struct KzsDesktopNative* desktopNative);

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_EGL)
/** Gets EGL native display type. */
EGLNativeDisplayType kzsEGLGetNativeDisplay(const struct KzsDesktopNative* desktopNative,
                                            const struct KzsDisplayNative* displayNative,
                                            const struct KzsWindowNative* windowNative);
#endif

#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_GLX)
XVisualInfo* kzsDisplayNativeGetGLXVisualInfo(struct KzsDesktopNative* desktopNative);
#endif


#endif
