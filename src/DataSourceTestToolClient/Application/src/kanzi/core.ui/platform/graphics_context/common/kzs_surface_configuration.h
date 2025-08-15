/**
* \file
* Configuration for drawable surfaces and windows.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_SURFACE_CONFIGURATION_H
#define KZS_SURFACE_CONFIGURATION_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>


/* Forward declarations. */
struct KzsDesktop;
struct KzsSurfaceConfigurationNative;

/**
 * \struct KzsSurfaceConfiguration
 * Configuration data for surfaces and windows.
 */
struct KzsSurfaceConfiguration;

/// Indicates that the implementation can choose any value for a surface property.
#define KZS_SURFACE_PROPERTY_DONT_CARE -1


/// Graphics languages for a surface.
enum KzsSurfaceType
{
    /// Surface rendering API is unspecified.
    KZS_SURFACE_TYPE_DEFAULT,

    /// Surface is target for OpenVG rendering.
    KZS_SURFACE_TYPE_VG_ONLY,

    /// Surface is target for OpenGLES rendering.
    KZS_SURFACE_TYPE_GLES_ONLY,

    /// Surface is target for OpenGL rendering.
    KZS_SURFACE_TYPE_GL_ONLY,

    /// Reserved for future use.
    KZS_SURFACE_TYPE_VG_AND_GLES,
};

/// Window system integration used by Kanzi
enum KzsGraphicsContextAPI
{
    /// No graphics context API
    KZS_GRAPHICS_CONTEXT_API_NONE,

    /// Use WGL for graphics context
    KZS_GRAPHICS_CONTEXT_API_WGL,

    /// Use EGL for graphics context
    KZS_GRAPHICS_CONTEXT_API_EGL,
    
    /// Use GLX for graphics context
    KZS_GRAPHICS_CONTEXT_API_GLX
};

enum KzsSwapBehavior
{
    KZS_SWAP_BEHAVIOR_DONT_CARE,    /**< Buffer contents become undefined on swap. If whole screen is not redrawn each frame, there may be unexpected content. */
    KZS_SWAP_BEHAVIOR_COPY,         /**< Buffer contents are preserved on swap. */
    KZS_SWAP_BEHAVIOR_EXCHANGE,     /**< Older buffer is recycled on swap. */
};

/** Properties for a surface. */
struct KzsSurfaceProperties
{
    /// Constructor.
    explicit KzsSurfaceProperties();

    /// Graphics language for rendering on this surface.
    enum KzsSurfaceType type;
    /// Graphics API for context.
    enum KzsGraphicsContextAPI contextApi;

    /// Size of red color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsColorR;
    /// Size of green color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsColorG;
    /// Size of blue color channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsColorB;
    /// Size of alpha channel in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsAlpha;
    /// Size of padding in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    /// \note Most platforms don't support explicit definition of padding size.
    kzInt bitsPadding;

    /// Size of stencil buffer in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsStencil;
    /// Size of depth buffer in bits. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt bitsDepthBuffer;

    /// Number of anti-aliasing samples used. Use 0 to turn AA off. Set to KZS_SURFACE_PROPERTY_DONT_CARE for automatic selection.
    kzInt antiAliasing;
    /// \see SwapBehavior
    KzsSwapBehavior swapBehavior;
    /// Passes priority hint to surface creation. Won't be applied if set to KZS_SURFACE_PROPERTY_DONT_CARE.
    kzInt priority;
};


/** Gets default properties for surface. */
KANZI_API struct KzsSurfaceProperties kzsSurfaceGetDefaultProperties(void);

/** Logs the surface properties with info log level. */
kzsError kzsSurfacePropertiesLog(const struct KzsSurfaceProperties* properties, kzString prefix);

/** Creates a configuration for surfaces for a windows. */
kzsError kzsSurfaceConfigurationCreate(const struct KzsDesktop* desktop, const struct KzsSurfaceProperties* surfaceProperties,
                                       struct KzsSurfaceConfiguration** out_configuration);

/** Deletes a surface configuration and frees all memory allocated for it. */
kzsError kzsSurfaceConfigurationDestroy(struct KzsSurfaceConfiguration* configuration);

kzsError kzsSurfaceConfigurationGetSurfaceNativeFunctions(const struct KzsSurfaceConfiguration* configuration, struct kzsSurfaceNativeFunctions* functions);

enum KzsSurfaceType kzsSurfaceConfigurationGetSurfaceType(const struct KzsSurfaceConfiguration* configuration);

enum KzsGraphicsContextAPI kzsSurfaceConfigurationGetContextAPI(const struct KzsSurfaceConfiguration* configuration);

/** Gets native portion of a surface configuration. */
const struct KzsSurfaceConfigurationNative* kzsSurfaceConfigurationGetNative(const struct KzsSurfaceConfiguration* configuration);

KzsSwapBehavior kzsSurfaceConfigurationGetSwapBehavior(const struct KzsSurfaceConfiguration* configuration);

/** Get priority */
int kzsSurfaceConfigurationGetPriority(const struct KzsSurfaceConfiguration* configuration);

/** */
typedef kzsError (*kzsSurfaceConfigurationGetSurfaceNativeFunctionsFunction)(const struct KzsSurfaceConfigurationNative* configurationNative,
                                                                             struct kzsSurfaceNativeFunctions* functions);

/** Creates a native surface configuration. */
typedef kzsError (*kzsSurfaceConfigurationNativeCreateFunction)(const struct KzsDesktop* desktop,
                                                                const struct KzsSurfaceProperties* surfaceProperties,
                                                                struct KzsSurfaceConfigurationNative** out_configurationNative);

/** Deletes a native surface configuration and frees all memory allocated for it. */
typedef kzsError (*kzsSurfaceConfigurationNativeDestroyFunction)(struct KzsSurfaceConfigurationNative* configurationNative);

/** Get priority */
typedef int (*kzsSurfaceConfigurationNativeGetPriorityFunction)(const struct KzsSurfaceConfigurationNative* configurationNative);

typedef KzsSwapBehavior (*kzsSurfaceConfigurationNativeGetSwapBehavior)(const struct KzsSurfaceConfigurationNative* configurationNative);


struct kzsSurfaceConfigurationNativeFunctions
{
    kzsSurfaceConfigurationGetSurfaceNativeFunctionsFunction getSurfaceNativeFunctions;
    kzsSurfaceConfigurationNativeCreateFunction create;
    kzsSurfaceConfigurationNativeDestroyFunction destroy;
    kzsSurfaceConfigurationNativeGetSwapBehavior getSwapBehavior;
    kzsSurfaceConfigurationNativeGetPriorityFunction getPriority;
};


/* Lists native surface configurations for specifying image attributes, used in kzsSurfaceNativeCreateImage. */

#define KZS_SURFACE_TARGET_NATIVE_ANDROID 0x3140 /**< Native android surface target. */
#define KZS_SURFACE_TARGET_NATIVE_PIXMAP 0x30B0 /**< Native pixmap target. */
#define KZS_SURFACE_TARGET_TEXTURE_2D 0x30B1 /**< Texture2D target. */

#define KZS_SURFACE_ATTRIBUTE_WIDTH 0x3057 /**< Width attribute. */
#define KZS_SURFACE_ATTRIBUTE_HEIGHT 0x3056 /**< Height attribute. */
#define KZS_SURFACE_ATTRIBUTE_MATCH_FORMAT 0x3043 /**< Match format (color format) attribute. */
#define KZS_SURFACE_ATTRIBUTE_IMAGE_PRESERVED 0x30D2 /**< Is image preserved over frames. */
#define KZS_SURFACE_ATTRIBUTE_NONE 0x3038 /**< Ends the array specification. */

#define KZS_SURFACE_ATTRIBUTE_FORMAT_RGBA_8888 0x30C3 /**< RGBA8888 format. */
#define KZS_SURFACE_ATTRIBUTE_FORMAT_RGB_565 0x30C1 /**< RGB565 format. */

#define KZS_SURFACE_ATTRIBUTE_TEXTURE_LEVEL 0x30BC /**< Texture level. */


#endif
