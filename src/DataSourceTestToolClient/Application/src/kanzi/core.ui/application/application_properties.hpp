// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_APPLICATION_PROPERTIES_HPP
#define KZ_APPLICATION_PROPERTIES_HPP

#include <kanzi/core.ui/application/fps_constraints.hpp>
#include <kanzi/core.ui/application/system_properties.hpp>
#include <kanzi/core.ui/application/performance_info_properties.hpp>
#include <kanzi/core.ui/input/event_source_properties.hpp>
#include <kanzi/core.ui/graphics/graphics_output.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core.ui/platform/windowing/common/window_properties.hpp>
#include <kanzi/core.ui/platform/windowing/common/desktop_properties.hpp>

#include <kanzi/core.ui/application/kzu_engine.h>

#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>


namespace kanzi
{


/// Configurable application properties.
struct KANZI_API ApplicationProperties
{
public:
    /// Performance info level.
    enum PerformanceInfoLevel
    {
        /// Disabled.
        PerformanceInfoLevelDisabled = 0,

        /// Show FPS only.
        PerformanceInfoLevelFPS = 1,

        /// Full info.
        PerformanceInfoLevelFull = 2,
    };

    /// Constructor.
    explicit ApplicationProperties();

     /// Default properties for desktop.
    NativeDesktopProperties defaultDesktopProperties;

    /// Default properties for application windows.
    NativeWindowProperties defaultWindowProperties;

    /// Default properties for the surfaces of the windows.
    KzsSurfaceProperties defaultSurfaceProperties;

    /// Default properties for the event sources.
    EventSourceProperties defaultEventSourceProperties;

    /// Path to either the binary config file listing all .kzb files that are loaded to project,
    /// or a path to a single .kzb file.
    string binaryName;

    /// List of modules to load.
    vector<string> moduleNames;

    /// Framerate limit as frames per second.
    /// Set to 0 to disable limiting the framerate altogether.
    int frameRateLimit;

    /// The number of background threads that are used to load resources. By default set to min(number of cores - 1, 3).
    /// Set to 0 to disable multithreaded loading and load everything in the main thread.
    unsigned int loadingThreadCount;

    /// The maximum number of resources that can be processed by the loading threads at the same time. The higher number can make the loading faster, but increases
    /// the peak memory usage during loading as more resources can be loaded to the memory before they are deployed to the GPU.
    /// If set to 0 (which is the default value), the value is set to the number of threads + 1.
    unsigned int maxPendingResources;

    /// Indicates whether memory mapping is used when loading KZB files.
    bool useMemoryMappedLoading;

    /// Width of the textures created for glyph caches.
    unsigned int glyphCacheWidth;

    /// Height of the textures created for glyph caches.
    unsigned int glyphCacheHeight;

    /// Performance info display level.
    PerformanceInfoLevel performanceInfoLevel;

    /// Properties of the performance info display.
    PerformanceInfoProperties performanceInfoProperties;

    /// Indicates whether the list of graphics related extensions printed when launching the application.
    /// It is useful for debugging which extensions are supported by platform.
    bool extensionOutputEnabled;

    /// Indicates whether the list of graphics related properties printed when launching the application, useful for debugging.
    bool propertyOutputEnabled;

    /// Indicates whether the list of graphics related information printed when launching the application, useful for debugging.
    bool informationOutputEnabled;

    /// Indicates whether graphics API calls should be logged, useful for debugging.
    bool graphicsLoggingEnabled;

    /// Profiling category filter.
    ///
    /// Use profiling category filters to set the state for profiling categories: 
    /// * "off" disables performance profiling.
    /// * "on" enables performance profiling.
    /// * "show" enables performance profiling, and if the profiler is registered within the Main Loop Task Profiler Registry, shows the profiler graph in the HUD. To use this state, set performanceInfoLevel to 2.
    /// To access the Main Loop Task Profiler Registry, use Domain::getMainLoopTaskProfilerRegistry().
    ///
    /// Each filter token consists of category name and state separated with the equal sign (=). Use semicolons (;) to separate multiple filter tokens. For example:
    ///
    /// "category1=on;category2=off;category3=show"
    ///
    /// To apply a setting for all profiling categories, use the asterisk (*). For example, to enable all categories:
    ///
    /// "*=on"
    ///
    /// The filter is evaluated from left to right, meaning that each setting overrides previous ones. For example, to disable all categories except category1:
    ///
    /// "*=off;category1=on"
    ///
    /// To set the same state for multiple categories, separate the categories with pipes (|). For example, to enable category1 and category2:
    ///
    /// "category1|category2=on"
    ///

    string profilingCategoryFilter;

    /// When an application is in the idle state, if there are no changes in the scene graph and rendering is not necessary, the application main loop waits for events, such as input.
    /// When you disable the application idle state, Kanzi extends this wait only until the next frame.
    /// When you enable the application idle state (the default setting), Kanzi waits until the application receives an event.
    /// Other threads may also post tasks to interrupt idle state.
    bool applicationIdleStateEnabled;

    /// Main loop profiling sample buffer count
    ///
    /// Optional override for the default size of sample buffers used by main loop profiling
    optional<size_t> mainLoopProfilingSampleBufferCount;
};


}


#endif
