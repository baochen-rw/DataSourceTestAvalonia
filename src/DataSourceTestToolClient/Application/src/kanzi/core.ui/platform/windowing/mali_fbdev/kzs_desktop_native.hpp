// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_DESKTOP_NATIVE_HPP
#define KZS_DESKTOP_NATIVE_HPP


// Forward declarations.
struct KzsDesktopNative;


/// Set dimensions of desktop-native
/// \param desktopNative Handle to desktop-native.
/// \param width Desktop width
/// \param height Desktop height
/// \return ::KZS_SUCCESS on success.
kzsError kzsDesktopNativeSetDimensions(struct KzsDesktopNative* desktopNative, kzUint width, kzUint height);

#endif
