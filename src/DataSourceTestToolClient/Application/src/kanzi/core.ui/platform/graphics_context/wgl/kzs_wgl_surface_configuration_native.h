// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_WGL_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_WGL_SURFACE_CONFIGURATION_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>


struct KzsSurfaceConfigurationNativeWGL;

void kzsGetWGLSurfaceConfigurationNativeFunctions(struct kzsSurfaceConfigurationNativeFunctions* functions);

const KzsSurfaceProperties* kzsSurfaceConfigurationNativeGetSurfaceProperties_WGL(const struct KzsSurfaceConfigurationNativeWGL* configurationNative);


#endif