/**
* \file
* Window handling.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_WINDOW_H
#define KZS_WINDOW_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core.ui/platform/windowing/common/window_properties.hpp>
#include <kanzi/core.ui/platform/windowing/common/kzs_native_handles.h>


/* Forward declarations. */
struct KzsDisplay;
struct KzsSurface;
struct KzsInputEventPointer;
struct KzsInputEventKey;
struct KzsWindowNative;
struct KzsSurfaceConfigurationNative;


/**
 * \struct KzsWindow
 * Kanzi window structure.
 */
struct KzsWindow;


/** Creates a window with a previously created native window. Takes ownership of the native window. */
KANZI_API kzsError kzsWindowCreateFromNative(struct KzsWindowNative* windowNative, struct KzsWindow** out_window);
/** Creates a window and returns it. */
KANZI_API kzsError kzsWindowCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
                         const struct NativeWindowProperties* windowPropertiesRequested,
                         const struct KzsSurfaceConfiguration* configuration, struct KzsWindow** out_window);
/** Creates a window from a native handle. */
KANZI_API kzsError kzsWindowCreateWrapper(NativeWindowHandle windowHandle, const struct KzsDesktop* desktop, struct KzsWindow** out_window);

/** Deletes a window. */
KANZI_API kzsError kzsWindowDelete(struct KzsWindow* window);

/** Resizes the window, if applicable and supported by the platform. */
KANZI_API kzsError kzsWindowResize(struct KzsWindow* window, kzUint width, kzUint height);

/** Sets the absolute position the window, if supported by the platform. */
KANZI_API kzsError kzsWindowSetPositionAbsolute(const struct KzsWindow* window, kzUint x, kzUint y);

/** Makes newly created window visible. */
KANZI_API kzsError kzsWindowShow(struct KzsWindow* window);

/** Sets the title bar string for the window, if supported by the platform. */
KANZI_API kzsError kzsWindowSetTitle(const struct KzsWindow* window, kzString titleText);

/** Gets the width of the window. */
KANZI_API kzUint kzsWindowGetCurrentWidth(const struct KzsWindow* window);
/** Gets the height of the window. */
KANZI_API kzUint kzsWindowGetCurrentHeight(const struct KzsWindow* window);

/** Gets the native window. */
KANZI_API struct KzsWindowNative* kzsWindowGetNative(const struct KzsWindow* window);


/** Creates a native window. */
KANZI_API kzsError kzsWindowNativeCreate(const struct KzsDesktop* desktop, const struct KzsDisplay* display,
    const struct NativeWindowProperties* windowPropertiesRequested,
    const struct KzsSurfaceConfiguration* surfaceConfiguration,
    struct NativeWindowProperties* out_windowProperties, struct KzsWindowNative** out_windowNative);
/** Creates a native window from a native handle. */
KANZI_API kzsError kzsWindowNativeCreateWrapper(NativeWindowHandle windowHandle, const struct KzsDesktop* desktop, struct NativeWindowProperties* out_windowProperties, struct KzsWindowNative** out_windowNative);

/** Initializes window. Called after creating window and native window. */
KANZI_API kzsError kzsWindowNativeInitialize(struct KzsWindowNative* windowNative, struct KzsWindow* window);

/** Deletes a native window. */
KANZI_API kzsError kzsWindowNativeDelete(struct KzsWindowNative* windowNative);

/** Resizes the window, if applicable and supported by the platform. Native implementation. */
KANZI_API kzsError kzsWindowNativeResize(struct KzsWindowNative* windowNative, kzUint width, kzUint height);

/** Sets the absolute position the window, if supported by the platform. Native implementation. */
KANZI_API kzsError kzsWindowNativeSetPositionAbsolute(const struct KzsWindowNative* windowNative, kzUint x, kzUint y);

/** Makes newly created window visible. */
KANZI_API kzsError kzsWindowNativeShow(struct KzsWindowNative* windowNative);

/** Sets the title bar string for the window, if supported by the platform. Native implementation. */
KANZI_API kzsError kzsWindowNativeSetTitle(const struct KzsWindowNative* windowNative, kzString titleText);

/** Gets the width of the window. */
KANZI_API kzUint kzsWindowNativeGetCurrentWidth(const struct KzsWindowNative* windowNative);
/** Gets the height of the window. */
KANZI_API kzUint kzsWindowNativeGetCurrentHeight(const struct KzsWindowNative* windowNative);

/** Sets the window Z order, if supported by the platform. */
KANZI_API kzsError kzsWindowNativeSetOrder(const struct KzsWindowNative* windowNative, kzInt order);

/** Outputs the properties of the window to the log. */
KANZI_API void kzsWindowLogProperties(const struct KzsWindow* window);


#endif
