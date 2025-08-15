/**
* \file
* Kanzi desktop, native portion for the win32 platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <kanzi/core/legacy/kzs_types.hpp>


#if defined(KZ_SUPPORT_GRAPHICS_CONTEXT_API_WGL)
struct KzsDesktopNative;
struct WglLibrary;

KANZI_API struct WglLibrary* kzsDesktopNativeGetWglLibrary(const struct KzsDesktopNative* desktopNative);

#endif


#endif
