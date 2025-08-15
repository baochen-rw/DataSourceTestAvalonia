// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_OPENGL_DEBUG_H
#define KZS_OPENGL_DEBUG_H

#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>


struct KzsGlGraphicsContext;

KANZI_API void kzsOpenGLDebugInstallCallback(struct KzsGlGraphicsContext* context);
KANZI_API void kzsOpenGLDebugUninstallCallback(struct KzsGlGraphicsContext* context);
KANZI_API void kzsOpenGLDebugDumpState(struct KzsGlGraphicsContext* context);
KANZI_API void kzsOpenGLDebugSetAttribPointer(unsigned int index, const void* pointer);
KANZI_API void kzsOpenGLDebugConfigure(enum KzsOpenGlVendor vendor, enum KzsSurfaceType surfaceType, enum KzsGraphicsContextAPI graphicsContextApi, const unsigned int* filterList);
KANZI_API const void* kzsOpenGLDebugGetAttribPointer(unsigned int index);
KANZI_API const char* kzsOpenGLEnumString(unsigned int e);


#endif
