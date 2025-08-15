/**
* \file
* Kanzi surface configuration, GLX implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_GLX_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_GLX_SURFACE_CONFIGURATION_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>

#include <GL/glx.h>


void kzsGetGLXSurfaceConfigurationNativeFunctions(struct kzsSurfaceConfigurationNativeFunctions* functions);


/* Forward declarations. */
struct KzsSurfaceConfigurationNative;


/** Gets pointer to GLX visual info describing the surface configuration. */
XVisualInfo* kzsSurfaceConfigurationNativeGetGLXVisualInfo(const struct KzsSurfaceConfigurationNative* configurationNative);

/** Gets requested screen depth, even when GLX visual info is null. */
int kzsSurfaceConfigurationNativeGetGLXDepth(const struct KzsSurfaceConfigurationNative* configurationNative);


#endif
