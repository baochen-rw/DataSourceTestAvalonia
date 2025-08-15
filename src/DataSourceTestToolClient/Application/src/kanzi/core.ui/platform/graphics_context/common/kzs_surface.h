/**
* \file
* Drawable surface.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_H
#define KZS_SURFACE_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>


/* Forward declarations. */
struct KzsDesktop;
struct KzsDisplay;
struct KzsSurfaceNative;
struct KzsSurfaceProperties;
struct KzsSurfaceConfiguration;
struct KzsSurfaceConfigurationNative;
struct KzsWindow;
struct KzsWindowNative;


/**
 * \struct KzsSurface
 * Surface for graphics output.
 */
struct KzsSurface;
struct KzsGlGraphicsContext;

typedef void (*kzsGLProcPointer)();

/**
 * Creates a drawable surface for a window. Graphics context of the new surface is shared with the currently
 * active surface if the rendering APIs match. This function may change the active surface.
 */
KANZI_API kzsError kzsSurfaceCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
                                    const struct KzsSurfaceConfiguration* configuration,
                                    const struct KzsWindow* window, struct KzsSurface** out_surface);

/** Deletes a surface and frees all memory allocated for it. */
KANZI_API kzsError kzsSurfaceDestroy(struct KzsSurface* surface);

/** Makes a surface active for drawing or deactivates it. Only one surface can be active at a time. */
KANZI_API kzsError kzsSurfaceSetActive(struct KzsSurface* surface, kzBool active);

/** Updates the buffer to the screen. */
KANZI_API kzsError kzsSurfaceUpdate(struct KzsSurface* surface);

/** Resizes the surface. */
KANZI_API kzsError kzsSurfaceResize(struct KzsSurface* surface, kzUint width, kzUint height);

/**
 * Specifies the minimum number of video frame periods per buffer swap.
 * Negative interval values are reserved for platform-specific special cases.
 */
KANZI_API kzsError kzsSurfaceSetSwapInterval(struct KzsSurface* surface, kzInt interval);

/** Reads pixels from the surface. */
KANZI_API kzsError kzsSurfaceReadPixels(const struct KzsSurface* surface, void* out_pixels);

#ifdef OSX
/** Resizes the surface. */
KANZI_API kzsError kzsSurfaceNativeResize(struct KzsSurfaceNative* surfaceNative, kzUint width, kzUint height);
#endif

/** Function for creating native image object, which can be shared between client APIs. */
KANZI_API kzsError kzsSurfaceCreateImage(const struct KzsSurface* surface, void* display, void* context, int target, void* data, int* attributes, void** out_image);

/** Function for deleting native image object. */
KANZI_API kzsError kzsSurfaceDeleteImage(const struct KzsSurface* surface, void* display, void* image);

/** Sets used surface settings to the given surface properties struct. */
KANZI_API kzsError kzsSurfaceGetUsedSurfaceProperties(struct KzsSurface* surface, struct KzsSurfaceProperties* out_surfaceProperties);

/** Outputs the properties of the surface to the log. */
KANZI_API void kzsSurfaceLogProperties(struct KzsSurface* surface);

/** Get GL procedure address */
KANZI_API kzsGLProcPointer kzsSurfaceGetProcAddress(struct KzsSurface* surface, kzString functionName);

KANZI_API struct KzsGlGraphicsContext* kzsSurfaceGetGraphicsContext(const struct KzsSurface* surface);

KANZI_API void* kzsSurfaceGetDisplay(const struct KzsSurface* surface);

KANZI_API void* kzsSurfaceGetContext(const struct KzsSurface* surface);

/** Get list of native surface extensions. */
KANZI_API kzString kzsSurfaceGetExtensions(const struct KzsSurface* surface);

/**
 * Attaches native surface to a window.
 * This function needs not to be called unless the window specified in kzsSurfaceCreate() is to be changed.
 */
KANZI_API kzsError kzsSurfaceAttachToWindow(struct KzsSurface* surface, const struct KzsWindow* window);

/**
 * Detaches native surface from a window.
 * This function needs not to be called unless the window specified in kzsSurfaceCreate() is to be changed.
 */
KANZI_API kzsError kzsSurfaceDetachFromWindow(struct KzsSurface* surface);

/** Creates a native surface. */
typedef kzsError (*kzsSurfaceNativeCreateFunction)(const KzsDesktop* desktop, const KzsDisplay* display,
                                                   const KzsSurfaceConfiguration* configuration,
                                                   const KzsWindow* window,
                                                   KzsSurfaceNative** out_surfaceNative);

/** Deletes a native surface and frees all memory allocated for it. */
typedef kzsError (*kzsSurfaceNativeDeleteFunction)(struct KzsSurfaceNative* surfaceNative);

/** Sets surface active. */
typedef kzsError (*kzsSurfaceNativeSetActiveFunction)(struct KzsSurfaceNative* surfaceNative, kzBool active);

/** Updates the surface. */
typedef kzsError (*kzsSurfaceNativeUpdateFunction)(struct KzsSurfaceNative* surfaceNative);

/**
 * Specifies the minimum number of video frame periods per buffer swap.
 * Negative interval values are reserved for platform-specific special cases.
 */
typedef kzsError (*kzsSurfaceNativeSetSwapIntervalFunction)(struct KzsSurfaceNative* surfaceNative, int interval);

/** Copy color buffer data to the preallocated buffer out_pixels. */
typedef kzsError (*kzsSurfaceNativeReadPixelsFunction)(struct KzsSurfaceNative* surfaceNative, void* out_pixels);

/** Gets the display from native surface. */
typedef void* (*kzsSurfaceNativeGetDisplayFunction)(struct KzsSurfaceNative* surfaceNative);

/** Gets the context from native surface. */
typedef void* (*kzsSurfaceNativeGetContextFunction)(struct KzsSurfaceNative* surfaceNative);

/** Sets used surface settings to the given surface properties struct. */
typedef kzsError (*kzsSurfaceGetUsedSurfaceNativePropertiesFunction)(const struct KzsSurfaceNative* surfaceNative, struct KzsSurfaceProperties* out_surfaceProperties);

/** Get list of native surface extensions. */
typedef kzString (*kzsSurfaceNativeGetExtensionsFunction)(const struct KzsSurfaceNative* surfaceNative);

/** Return GL procedure address. */
typedef kzsGLProcPointer (*kzsSurfaceNativeGetProcAddressFunction)(const struct KzsSurfaceNative* surfaceNative, kzString functionName);

typedef kzsError (*kzsSurfaceNativeCreateImageFunction)(const struct KzsSurfaceNative* surfaceNative, void* display, void* context, int target, void* data, int* attributes, void** out_image);

typedef kzsError (*kzsSurfaceNativeDeleteImageFunction)(const struct KzsSurfaceNative* surfaceNative, void* display, void* image);

/** Attaches native surface to the given window. */
typedef kzsError (*kzsSurfaceNativeAttachToWindowFunction)(struct KzsSurfaceNative*, const KzsWindow* window);

/** Detaches native surface from the window. */
typedef kzsError (*kzsSurfaceNativeDetachFromWindowFunction)(struct KzsSurfaceNative* surfaceNative);

struct kzsSurfaceNativeFunctions
{
    kzsSurfaceNativeCreateFunction create;
    kzsSurfaceNativeDeleteFunction destroy;
    kzsSurfaceNativeSetActiveFunction setActive;
    kzsSurfaceNativeUpdateFunction update;
    kzsSurfaceNativeSetSwapIntervalFunction setSwapInterval;
    kzsSurfaceNativeReadPixelsFunction readPixels;
    kzsSurfaceNativeGetDisplayFunction getDisplay;
    kzsSurfaceNativeGetContextFunction getContext;
    kzsSurfaceGetUsedSurfaceNativePropertiesFunction getUsedSurfaceProperties;
    kzsSurfaceNativeGetExtensionsFunction getExtensions;
    kzsSurfaceNativeGetProcAddressFunction getProcAddress;
    kzsSurfaceNativeCreateImageFunction createImage;
    kzsSurfaceNativeDeleteImageFunction deleteImage;
    kzsSurfaceNativeAttachToWindowFunction attachToWindow;
    kzsSurfaceNativeDetachFromWindowFunction detachFromWindow;
};


#endif
