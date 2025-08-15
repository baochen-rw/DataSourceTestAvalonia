// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DESKTOP_NATIVE_H
#define KZS_DESKTOP_NATIVE_H


#include <wfd.h>

/// Get WFD device native handle.
/// \param desktopNative Handle to desktop-native.
/// \return File descriptor for WFD device.
WFDDevice kzsDesktopNativeGetHandle(const struct KzsDesktopNative* desktopNative);

/// Get port number for display.
/// \param desktopNative Handle to desktop-native.
/// \return Port handle.
WFDint kzsDesktopNativeGetPortID(const struct KzsDesktopNative* desktopNative, unsigned int displayID);


#endif
