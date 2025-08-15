/**
* \file
* Kanzi surface configuration, GLX implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_GLX_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_GLX_SURFACE_CONFIGURATION_NATIVE_H


#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>

/* Forward declarations. */
struct KzsSurfaceConfigurationNativeNoGL;

kzsError kzsSurfaceConfigurationNativeCreate_nogl(const struct KzsDesktop* /*desktop*/,
                                                  const struct KzsSurfaceProperties* /*surfaceProperties*/,
                                                  struct KzsSurfaceConfigurationNativeNoGL** out_configurationNative);

kzsError kzsSurfaceConfigurationNativeDelete_nogl(struct KzsSurfaceConfigurationNativeNoGL* configurationNative);


/** Gets pointer to GLX visual info describing the surface configuration. */
void* kzsSurfaceConfigurationNativeGetGLXVisualInfo_nogl(const struct KzsSurfaceConfigurationNativeNoGL* configurationNative);

/** Gets requested screen depth, even when GLX visual info is null. */
int kzsSurfaceConfigurationNativeGetGLXDepth_nogl(const struct KzsSurfaceConfigurationNativeNoGL* configurationNative);


void kzsGetNoGLSurfaceConfigurationNativeFunctions(struct kzsSurfaceConfigurationNativeFunctions* functions);

#endif
