/**
* \file
* Kanzi surface, native portion for the Linux-X11-GLX platform.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_GLX_SURFACE_NATIVE_H
#define KZS_GLX_SURFACE_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface.h>

struct KzsSurfaceNative;

kzsError kzsSurfaceNativeCreate_nogl(const struct KzsDesktop* desktop, const struct KzsDisplay* /*display*/,
                                     const struct KzsSurfaceConfiguration* /*configuration*/,
                                     const struct KzsWindow* /*window*/, struct KzsSurfaceNativeNoGL** out_surfaceNative);

kzsError kzsSurfaceNativeDelete_nogl(struct KzsSurfaceNative* surfaceNative);

kzsError kzsSurfaceNativeSetActive_nogl(struct KzsSurfaceNative* /*surfaceNative*/, kzBool /*active*/);

kzsError kzsSurfaceNativeUpdate_nogl(struct KzsSurfaceNative* /*surfaceNative*/);

kzsError kzsSurfaceNativeSetSwapInterval_nogl(struct KzsSurfaceNative* /*surfaceNative*/, kzInt /*interval*/);

kzsError kzsSurfaceNativeReadPixels_nogl(struct KzsSurfaceNative* /*surfaceNative*/, void* /*out_pixels*/);

void* kzsSurfaceNativeGetDesktop_nogl(struct KzsSurfaceNative* surfaceNative);

void* kzsSurfaceNativeGetContext_nogl(struct KzsSurfaceNative* /*nativeSurface*/);

kzsError kzsSurfaceGetUsedSurfaceNativeProperties_nogl(const struct KzsSurfaceNative* /*surfaceNative*/, struct KzsSurfaceProperties* out_surfaceProperties);

kzString kzsSurfaceNativeGetExtensions_nogl(struct KzsSurfaceNative* /*surfaceNative*/);

kzsError kzsNativeWindowSystemInitialize_nogl();

KANZI_API void kzsGetNoglSurfaceNativeFunctions(struct kzsSurfaceNativeFunctions* functions);


#endif
