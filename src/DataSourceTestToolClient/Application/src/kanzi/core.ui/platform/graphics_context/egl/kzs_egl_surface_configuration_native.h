// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_EGL_SURFACE_CONFIGURATION_NATIVE_H
#define KZS_EGL_SURFACE_CONFIGURATION_NATIVE_H

#include <kanzi/core.ui/platform/graphics_context/egl/kzs_egl.h>
#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>

// Determine the GLES bits for surface initialization.
#if (KZ_DLOAD_GLES_SYMBOLS >= 30) || (KZ_LINKED_GLES_SYMBOLS >= 30)
#if defined(EGL_OPENGL_ES3_BIT)
#define KZ_SURFACE_CONFIGURATION_GLES_BITS (EGL_OPENGL_ES2_BIT | EGL_OPENGL_ES3_BIT)
#elif defined(EGL_OPENGL_ES3_BIT_KHR)
#define KZ_SURFACE_CONFIGURATION_GLES_BITS (EGL_OPENGL_ES2_BIT | EGL_OPENGL_ES3_BIT_KHR)
#endif
#endif
#if !defined(KZ_SURFACE_CONFIGURATION_GLES_BITS)
// Fallback to just ES2.
#define KZ_SURFACE_CONFIGURATION_GLES_BITS EGL_OPENGL_ES2_BIT
#endif

void kzsGetEGLSurfaceConfigurationNativeFunctions(struct kzsSurfaceConfigurationNativeFunctions* functions);

/** Gets EGL configuration attribute array. */
const EGLint* kzsSurfaceConfigurationNativeGetEGLAttributeArray_EGL(const struct KzsSurfaceConfigurationNativeEGL* configurationNative);

/** Gets EGL configuration padding size. */
EGLint kzsSurfaceConfigurationNativeGetPaddingSize_EGL(const struct KzsSurfaceConfigurationNativeEGL* configurationNative);

/** Gets EGL API. */
EGLenum kzsSurfaceConfigurationNativeGetAPI_EGL(const struct KzsSurfaceConfigurationNativeEGL* configurationNativeEgl);


#endif
