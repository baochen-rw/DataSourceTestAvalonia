// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_GRAPHICS_CONTEXT_H
#define KZS_GL_GRAPHICS_CONTEXT_H

#include "kzs_opengl.h"
#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>

struct KzsGlGraphicsContext;

namespace kanzi
{

class GlGraphicsAdapter;

}

KANZI_API kzsError kzsGlGraphicsContextCreate(struct KzsSurface* surface, struct KzsGlGraphicsContext** out_glGraphicsContext);

KANZI_API kzsError kzsGlGraphicsContextDestroy(struct KzsGlGraphicsContext* context);

KANZI_API void kzsGlGraphicsContextSetActive(const struct KzsGlGraphicsContext* context);

KANZI_API kanzi::GlGraphicsAdapter* kzsGlGraphicsContextGetAdapter(const struct KzsGlGraphicsContext* context);

KANZI_API bool kzsGlGraphicsContextIsKhrDebugSupported(const struct KzsGlGraphicsContext* context);

KANZI_API enum KzsOpenGlVendor kzsGlGraphicsContextGetVendor(const struct KzsGlGraphicsContext* context);

KANZI_API enum KzsSurfaceType kzsGlGraphicsContextGetSurfaceType(const struct KzsGlGraphicsContext* context);

KANZI_API enum KzsGraphicsContextAPI kzsGlGraphicsContextGetAPI(const struct KzsGlGraphicsContext* context);

KANZI_API bool kzsGlIsExtensionSupported(const struct KzsGlGraphicsContext* context, kzString extension);

KANZI_API struct KzsSurface* kzsGlGraphicsContextGetSurface(struct KzsGlGraphicsContext* context);

KANZI_API struct KzsDynamicLibrary* kzsGlGraphicsContextOpenLibrary(struct KzsGlGraphicsContext* context, kzString libraryName);

/// Set OpenGL API call logging on/off
KANZI_API void kzsGlGraphicsContextSetLogging(struct KzsGlGraphicsContext* context, bool enabled, bool dumpStateOnDrawCalls);

/// Return current OpenGL API call logging setting
KANZI_API bool kzsGlGraphicsContextGetLogging(struct KzsGlGraphicsContext* context);

KANZI_API bool kzsGlGraphicsContextGetDumpStateOnDrawCalls(struct KzsGlGraphicsContext* context);

/// Set OpenGL API call error checking on/off
KANZI_API void kzsGlGraphicsContextSetErrorChecking(struct KzsGlGraphicsContext* context, bool enabled);

/// Set OpenGL API call debug callback on/off
KANZI_API void kzsGlGraphicsContextSetDebugCallback(struct KzsGlGraphicsContext* context, bool enabled);

// protected or private

void kzsGlGraphicsContextGetGlesSymbols(struct KzsGlGraphicsContext* glGraphicsContext);
void kzsGlGraphicsContextGetOpenGlSymbols(struct KzsGlGraphicsContext* glGraphicsContext);


#endif

