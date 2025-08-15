/**
* \file
* Kanzi desktop, YunOS implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H

#include <kanzi/core/error/legacy_error.hpp>

struct KzsDesktopNative;
struct KzsWindowNative;

/// Sets native desktop dimensions. This setter is called within native window creation.
kzsError kzsDesktopNativeSetDimensions(struct KzsDesktopNative* desktopNative, kzUint width, kzUint height);

/// Sets the current active window for native input handling.
void kzsDesktopNativeSetActiveWindow(struct KzsDesktopNative* desktopNative, const struct KzsWindowNative* windowNative);

/// Gets the current active window of desktop.
const struct KzsWindowNative* kzsDesktopNativeGetActiveWindow(struct KzsDesktopNative* desktopNative);

#endif
