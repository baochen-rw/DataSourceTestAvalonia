// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_OPENGL_H
#define KZS_OPENGL_H

#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_opengl_enum.h>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_es_20.h> // These handle both dynamic backend and direct linking.
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_es_30.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_es_31.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_es_32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_es_ext.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_ext.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_gl_try.h>

// The GLES API version is selected using API version setting for statically linked (KZ_LINKED_GLES_SYMBOLS) symbols
// and symbols dynamically loaded at runtime (KZ_DLOAD_GLES_SYMBOLS).
// The GLES API version is used by renderer even if GLES API is not configured as supported (KZ_SUPPORT_GRAPHICS_API_GLES is not defined).
// This is why GLES API version should be properly set even in case when only OpenGL API is used.
#if defined(KZ_SUPPORT_GRAPHICS_API_GLES) || defined(KZ_SUPPORT_GRAPHICS_API_OPENGL)

// Set GLES API version based on API version set by KZ_LINKED_GLES_SYMBOLS/KZ_DLOAD_GLES_SYMBOLS.
#   if defined(KZ_LINKED_GLES_SYMBOLS) && defined(KZ_DLOAD_GLES_SYMBOLS)

        // Choose maximum GLES API available.
#       if KZ_DLOAD_GLES_SYMBOLS < KZ_LINKED_GLES_SYMBOLS
#           define KZ_GLES_API_VERSION KZ_LINKED_GLES_SYMBOLS
#       else
#           define KZ_GLES_API_VERSION KZ_DLOAD_GLES_SYMBOLS
#       endif

#   elif defined(KZ_DLOAD_GLES_SYMBOLS)

        // Set API version to GLES API configured for dynamically loaded symbols.
#       define KZ_GLES_API_VERSION KZ_DLOAD_GLES_SYMBOLS

#   elif defined(KZ_LINKED_GLES_SYMBOLS)

        // Set API version to GLES API configured for statically linked symbols.
#       define KZ_GLES_API_VERSION KZ_LINKED_GLES_SYMBOLS

#   else
#       error Please define KZ_DLOAD_GLES_SYMBOLS and/or KZ_LINKED_GLES_SYMBOLS.
#   endif

#else
#error Can not select GLES API version.
#endif


// Possible values for KZ_OPENGL_PLATFORM
#define KZ_PLATFORM_TEGRA 1 ///< Value for Tegra platform.

enum KzsOpenGlVendor
{
    KZS_OPENGL_VENDOR_UNKNOWN,
    KZS_OPENGL_VENDOR_IMAGINATION,
    KZS_OPENGL_VENDOR_CHROMIUM,
    KZS_OPENGL_VENDOR_BROADCOM,
    KZS_OPENGL_VENDOR_QUALCOMM,
    KZS_OPENGL_VENDOR_VIVANTE,
    KZS_OPENGL_VENDOR_NVIDIA,
    KZS_OPENGL_VENDOR_INTEL,
    KZS_OPENGL_VENDOR_AMD,
    KZS_OPENGL_VENDOR_ARM
};

namespace kanzi {

class GlGraphicsAdapter;

}

KANZI_API void kzsGlGraphicsAdapterSetRoot(kanzi::GlGraphicsAdapter* root);

KANZI_API void kzsGlErrorNotify(unsigned int error);

KANZI_API void kzsGlErrorTest();


#endif

