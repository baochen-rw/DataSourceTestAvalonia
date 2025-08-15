// Copyright 2008-2021 by Rightware. All rights reserved.

#if defined _MSC_VER || defined __MINGW32__

#include <kanzi/core.ui/platform/windowing/win32/kzs_window_native.h>

#elif defined QNX_SCREEN

#include <kanzi/core.ui/platform/windowing/qnx_screen/kzs_window_native.h>

#elif defined ANDROID || defined __ANDROID__

#include <kanzi/core.ui/platform/windowing/android/kzs_window_native.h>

#elif defined YUNOS

#include <kanzi/core.ui/platform/windowing/yunos/kzs_window_native.hpp>

#elif defined WAYLAND

#include <kanzi/core.ui/platform/windowing/wayland/kzs_window_native.h>

#elif defined EGL_API_FB

#include <kanzi/core.ui/platform/windowing/vivante_fbdev/kzs_window_native.h>

#elif defined MALI_FB

#include <kanzi/core.ui/platform/windowing/mali_fbdev/kzs_window_native.hpp>

#elif defined X11

#include <kanzi/core.ui/platform/windowing/x11/kzs_window_native.h>

#elif defined RWM

#include <kanzi/core.ui/platform/windowing/rwm/kzs_window_native.hpp>

#elif defined WFD

#include <kanzi/core.ui/platform/windowing/wfd/kzs_window_native.hpp>

#elif defined WIN_INTERFACE_CUSTOM

#include <kanzi/core.ui/platform/windowing/egldevice/kzs_window_native.h>

#elif defined WSEGL

#if defined INTEGRITY && defined WSEGL_USERMEM
#include <kanzi/core.ui/platform/windowing/ghs_fb_api/kzs_window_native.h>
#else
#include <kanzi/core.ui/platform/windowing/wsegl/kzs_window_native.h>
#endif

#elif defined __GBM__

#include <kanzi/core.ui/platform/windowing/gbm/kzs_window_native.hpp>

#endif
