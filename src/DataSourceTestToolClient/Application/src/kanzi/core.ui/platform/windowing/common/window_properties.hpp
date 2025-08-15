// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_WINDOW_PROPERTIES_HPP
#define KZ_WINDOW_PROPERTIES_HPP

#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/cpp/string.hpp>

#include <climits>

/// List of window orientation angles.
enum KzsDisplayOrientationAngle
{
    /// No rotation.
    KZS_DISPLAY_ORIENTATION_ANGLE_0,

    /// 180-degree rotation.
    KZS_DISPLAY_ORIENTATION_ANGLE_180
};

/// Enumeration for different window styles.
enum KzsWindowStyle
{
    /// A window that cannot be resized.
    KZS_WINDOW_STYLE_FIXED,

    /// A window that can be resized.
    KZS_WINDOW_STYLE_RESIZABLE,

    /// Window occupies the whole screen.
    KZS_WINDOW_STYLE_FULL_SCREEN,

    /// No borders or other decorations.
    KZS_WINDOW_STYLE_BORDERLESS,

    /// Docked window with external message handling. Should only be used by Kanzi Studio.
    KZS_WINDOW_STYLE_STUDIO_PREVIEW,

    /// Let the system choose the appropriate window style for the platform.
    KZS_WINDOW_STYLE_DEFAULT
};

/// Properties for a window.
/// Position is defined as the distance from the top-left corner of the desktop to the top-left corner of the window, measured towards the center of the desktop.
/// If style is set to KZS_WINDOW_STYLE_FULL_SCREEN, the window position is ignored and the primary screen resolution is changed to match the requested window size.
/// If both width and height is set to zero, no change of resolution is attempted.
struct KANZI_API NativeWindowProperties
{
    /// Special values for NativeWindowProperties::x, NativeWindowProperties::y and NativeWindowProperties::order.
    enum WindowPositionSpecifiers
    {
        /// Lets system specify position for a window.
        WindowPositionUnspecified = INT_MIN
    };

    /// Special values for NativeWindowProperties::width and NativeWindowProperties::height.
    enum WindowSizeSpecifiers
    {
        /// Lets system specify size for a window.
        WindowSizeUnspecified = 0,

        /// Automatically sizes the window to fill visible screen.
        WindowSizeFullscreen = UINT_MAX
    };

    /// Constructor.
    explicit NativeWindowProperties();

    /// X position of the window (in pixels). Use WindowPositionUnspecified to let the system choose the position.
    kzInt x;
    /// Y position of the window (in pixels). Use WindowPositionUnspecified to let the system choose the position.
    kzInt y;
    /// Z order of the window (target platform specific value). Use WindowPositionUnspecified to let the system choose the position.
    kzInt order;

    /// Width of the window (in pixels). Use WindowSizeFullscreen to use the maximum width available on the primary screen.
    /// Use WindowSizeUnspecified to let the system choose the size.
    kzUint width;
    /// Height of the window (in pixels). Use WindowSizeFullscreen to use the maximum height available on the primary screen.
    /// Use WindowSizeUnspecified to let the system choose the size.
    kzUint height;

    /// Number of window buffers to be requested from windowing system at native window initialization.
    /// Use 0 to let the system choose the target platform specific default value.
    unsigned int bufferCount;
    
    /// Style properties of the window.
    enum KzsWindowStyle style;

    /// Title for ias-shell.
    kanzi::string windowTitle;

    /// Index of default display for full-screen windows.
    kzUint defaultDisplayIndex;

    /// Window group name.
    /// Not all windowing systems use the group name.
    kanzi::optional<kanzi::string> groupName;

    /// Controls whether the application should try to to do platform-specific initializations like starting graphics-driver or displays. Only applicable on some platforms.
    bool initializePlatform;

    /// Outputs the window properties to the log.
    void log() const;
};

#endif
