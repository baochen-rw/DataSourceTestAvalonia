// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_APPLICATION_HPP
#define KZ_APPLICATION_HPP

#include <kanzi/core.ui/application/application_properties.hpp>
#include <kanzi/core.ui/application/fps_constraints.hpp>
#include <kanzi/core.ui/application/kzu_engine.h>
#include <kanzi/core.ui/application/system_properties.hpp>
#include <kanzi/core.ui/graphics/graphics_output.hpp>
#include <kanzi/core.ui/input/event_source.hpp>
#include <kanzi/core.ui/input/event_source_properties.hpp>
#include <kanzi/core.ui/platform/application/common/suspension_manager.hpp>
#include <kanzi/core.ui/scheduler/scheduler.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/module/module.hpp>
#include <kanzi/core/time/stop_watch.hpp>

#include <kanzi/core/legacy/kzs_error_codes.hpp>
#include <kanzi/core/legacy/thread/kzs_thread.hpp>
#include <kanzi/core/profiling/startup_profiler_registry.hpp>

// Forward declarations.
struct KzuEngine;

namespace kanzi
{

// Forward declarations.
class PreviewApplication;
class PerformanceInfo;

/// Application class.
///
/// Base class for application logic.
class KANZI_API Application : public Module
{
public:

    /// Enumeration for different application states.
    enum State
    {
        Uninitialized,    ///< The application is not yet initialized.
        Running,          ///< The application is running normally.
        Sleeping,         ///< The application is sleeping. The OpenGL graphics context is destroyed.
        Quitting,         ///< The application is in the process of quitting without errors.
        Error             ///< The application has encountered an error and exits immediately.
    };

    // Initialization functions.

    /// Constructs the application object.
    explicit Application();

    /// Destructs the application object.
    virtual ~Application();

    /// Initializes the application to a consistent state.
    /// 
    /// This is the first function called by the application framework
    /// after constructing the application.
    /// This function tries to read the file application.cfg and shouldn't
    /// be called before the file system of the operating system has been
    /// initialized.
    ///
    /// The default behavior can be changed by overriding initializeOverride().
    ///
    /// \param systemProperties Command line parameters of the program.
    void initialize(const SystemProperties& systemProperties);

    /// Uninitializes the application.
    ///
    /// This is the last function called by the application framework before destruction.
    ///
    /// The default behavior can be changed by overriding uninitializeOverride().
    void uninitialize();

    /// Initializes the graphics language subsystem.
    /// 
    /// This function is called by the application framework before entering
    /// the program main loop, but after a GL context has been activated.
    /// It initializes OpenGL-related subsystems.
    ///
    /// The default behavior can be changed by overriding initializeGLOverride().
    void initializeGL();

    /// Uninitializes the graphics language subsystem.
    /// 
    /// This function is called by the application framework after exiting
    /// the program main loop, but before a GL context has been deactivated.
    /// It undeploys all GPU resources.
    ///
    /// The default behavior can be changed by overriding uninitializeGLOverride().
    void uninitializeGL();

    /// Suspends the graphics language subsystem.
    /// 
    /// This function is called by the application framework during application suspension,
    /// on systems where the graphics language resources are not guaranteed to be retained
    /// until the application resumes.
    /// It undeploys all GPU resources and reschedules them for redeployment.
    ///
    /// When your applications suspends, the GPU resources not stored in a .kzb file become invalid.
    /// Destroy these resources and recreate them on resume. Make sure that after recreating a resource
    /// the pointers are correct. Kanzi automatically restores all other resources.
    ///
    /// The default behavior can be changed by overriding suspendGLOverride().
    void suspendGL();

    /// Resumes the graphics language subsystem.
    /// 
    /// This function is called by the application framework during application resume,
    /// if suspendGL() was called during suspension.
    /// It deploys GPU resources that were undeployed during suspendGL().
    ///
    /// The default behavior can be changed by overriding resumeGLOverride().
    void resumeGL();

    // Accessors and mutators.

    /// Access domain.
    ///
    /// \return Pointer to domain.
    Domain* getDomain() const;

    /// Access the renderer.
    ///
    /// \return Renderer3D pointer.
    Renderer3D* getRenderer3D() const;

    /// Access root node.
    ///
    /// \return Node shared pointer.
    Node2DSharedPtr getRoot() const;

    /// Access screen.
    ///
    /// \return Screen shared pointer.
    ScreenSharedPtr getScreen() const;

    /// Set screen.
    void setScreen(ScreenSharedPtr screen);

    /// Access engine task scheduler.
    ///
    /// \return Engine task scheduler pointer.
    KzuTaskScheduler* getTaskScheduler() const;

    /// Queue a task to be executed once by the internal task scheduler.
    /// \param taskName Task name, must be unique.
    /// \param task Task to execute.
    void queueTaskExecuteOnce(string_view taskName, Scheduler::Task task);

    /// Access resource manager.
    ///
    /// \return Resource manager pointer.
    ResourceManager* getResourceManager() const;

    /// Access input manager.
    ///
    /// \return Input manager pointer.
    InputManager* getInputManager() const;

    /// Access binary loader.
    ///
    /// \return Binary loader pointer.
    KzuBinaryLoader* getBinaryLoader() const;

    /// Access message dispatcher.
    ///
    /// \return Message dispatcher pointer.
    KzuMessageDispatcher* getMessageDispatcher() const;

    /// Access FPS info.
    ///
    /// \return Frames per second measurement.
    float getFramesPerSecond() const;

    virtual void projectReloaded();

    /// Access graphics output count.
    ///
    /// \return Number of attached graphics output.
    size_t getGraphicsOutputCount() const;

    /// Access graphics outputs.
    ///
    /// \param index Index of the graphics output to access.
    /// \return Shared pointer to the specified graphics output.
    GraphicsOutputSharedPtr getGraphicsOutput(size_t index = 0) const;

    /// Attach graphics output.
    ///
    /// \param graphicsOutput Shared pointer to the graphics output to attach.
    void appendGraphicsOutput(GraphicsOutputSharedPtr graphicsOutput);

    /// Remove graphics output.
    ///
    /// \param index Index of the graphics output to remove.
    void removeGraphicsOutput(size_t index = 0);

    /// Access event source count.
    ///
    /// \return Number of attached event sources.
    size_t getEventSourceCount() const;

    /// Access event sources.
    ///
    /// \param index Index of the event source to access.
    /// \return Shared pointer to the specified event source.
    EventSourceSharedPtr getEventSource(size_t index = 0) const;

    /// Attach event source.
    ///
    /// \param eventSource Shared pointer to the event source to attach.
    void appendEventSource(EventSourceSharedPtr eventSource);

    /// Remove event source.
    ///
    /// \param index Index of the event source to remove.
    void removeEventSource(size_t index = 0);

    /// Access application state.
    ///
    /// \return Current application state.
    State getState();

    /// Gets time taken to render last frame.
    chrono::microseconds getLastFrameTime() const;

    /// Access application properties.
    ///
    /// \return Current application properties.
    ApplicationProperties getApplicationProperties() const;

    /// Application entry point.
    ///
    /// This high-level function implements the default initialization and main loop.
    /// It is called by the application framework, except on callbacks-only systems.
    ///
    /// The default behavior can be changed by overriding mainOverride().
    ///
    /// \param systemProperties Command line parameters of the program.
    void main(const SystemProperties& systemProperties);

    /// Application main loop.
    /// Does not return while application is in Running state.
    void run();

    /// Gathers events from event sources.
    ///
    /// This function is called once per frame during normal operation.
    /// The retrieved events are stored in the event queue to be processed later by update().
    void input();

    /// Updates application logic.
    ///
    /// This function is called once per frame during normal operation.
    /// It refreshes the application state and prepares the scene for rendering.
    ///
    /// The default behavior can be changed by overriding updateOverride().
    ///
    /// \param deltaTime The time elapsed since the previous call to update().
    void update(chrono::milliseconds deltaTime);

    /// Renders the root layer.
    ///
    /// This function is called after update once per frame during normal operation.
    /// It renders the current scene.
    ///
    /// The default behavior can be changed by overriding renderOverride().
    void render();

    /// Suspends the thread for the remainder of the frame.
    /// May suspend indefinitely, if there is no reason to update.
    /// Will return when there is input or a queued task available.
    void suspend();

    /// Irrevocably suspends the thread for the remainder of the frame.
    void yield();

    /// Processes the deployment queue for asynchronous loading tasks.
    ///
    /// By default this function processes a single item from the deployment queue of background loading tasks every frame.
    ///
    /// You can change the default behavior of the function by overriding the progressDeploymentQueueOverride() function.
    void progressDeploymentQueue();

    // State modifiers.

    /// Puts the application to sleep as soon as possible.
    void sleep();

    /// Wakes up the application from sleep as soon as possible.
    void wakeup();

    /// Quits the application as soon as possible.
    void quit();

    //////////////////////////////////////////////////////////////////////////

    void beginFrame(const GraphicsOutput& graphicsOutput);
    void renderFrame1(const GraphicsOutput& graphicsOutput, bool toolPresent, const RenderPassSharedPtr& debugComposer);
    void renderFrame2();
    void renderFrame3();
    void postRender(const GraphicsOutput& graphicsOutput);
    void endFrame();

    void update1(chrono::milliseconds deltaTime, const GraphicsOutput& graphicsOutput, kzBool /*toolPresent*/);
    void update2(chrono::milliseconds deltaTime, const GraphicsOutput& graphicsOutput, kzBool toolPresent, kzBool centerViewport);

    void executePendingChanges(kzBool toolPresent);
    void projectReloaded(bool isToolPresent);
    void initializeProject(kzBool toolPresent);
    void initializeProjectTask(kzBool toolPresent);
    void reloadProject(kzUint byteCount, const byte* bytes, bool isToolPresent);
    void reloadProjectFromFile(kzString binaryPath, bool isToolPresent);
    void reloadProjectFromFileResource(kzString resourceFile, bool isToolPresent);

    void initializeGLContext();
    void uninitializeGLContext();

    //////////////////////////////////////////////////////////////////////////

    /// Gets performance info level.
    /// If performance info is not #PerformanceInfoDisabled, textual information HUD will be drawn after onPostRender has been called.
    ApplicationProperties::PerformanceInfoLevel getPerformanceInfoLevel() const
    {
        return m_applicationProperties.performanceInfoLevel;
    }
    /// Sets performance info level.
    /// Equal to application configuration has "PerformanceInfoLevel" option. 
    /// Setting the level to #PerformanceInfoDisabled (0) will turn off the display (default).
    /// Setting the level to #PerformanceInfoFPS (1) will display framerate.
    /// Setting the level to #PerformanceInfoFull (2) will display additional information about rendering batches.
    void setPerformanceInfoLevel(ApplicationProperties::PerformanceInfoLevel level)
    {
        m_applicationProperties.performanceInfoLevel = level;
    }

    /// Gets default main loop timer.
    StopWatch& getStopWatch();

    /// Sets or resets flag for allowing indefinite sleep.
    /// \param enabled True to enable indefinite sleep, false to always wake up in frame time.
    void setAllowIndefiniteSleep(bool enabled)
    {
        m_applicationProperties.applicationIdleStateEnabled = enabled;
    }

    /// Returns whether an immediate redraw is needed.
    /// \return True, if rendering should be done as soon as possible.
    bool isRenderRequired() const;

protected:
    // Event handlers.

    /// Function callback for application start.
    virtual void onStartup();

    /// Function callback for application end.
    virtual void onShutdown();

    /// Function callback for initialization that is using the .KZB data. This function is called right after the .KZB binaries have been loaded.
    virtual void onProjectLoaded();

    /// User-defined configuration.
    ///
    /// This callback is called before the application.cfg is read,
    /// and before the graphics subsystem is initialized.
    /// \param configuration Allows modification of the application properties.
    virtual void onConfigure(ApplicationProperties& configuration);

    /// Function callback for updating logic. This function is called for every frame.
    /// \param deltaTime The delta time passed to update(). By default this is the time elapsed since the previous frame in milliseconds.
    virtual void onUpdate(chrono::milliseconds deltaTime);

    /// Function callback for rendering. This function is called for every frame before any other rendering function.
    virtual void onPreRender();

    /// Function callback for rendering. This function is called for every frame after the root layer has been rendered.
    virtual void onPostRender();

    /// Event callback for pointing device (e.g. mouse or touch screen) input events.
    virtual void onPointerInputEvent(const KzsInputEventPointer* inputData);

    /// Event callback for keyboard input events.
    virtual void onKeyInputEvent(const KzsInputEventKey* inputData);

    /// Event callback for idle loop.
    virtual void onIdle();

    /// Event callback for application sleep.
    virtual void onSleep();

    /// Event callback for application wakeup.
    virtual void onWakeup();

    // Main loop overrides.

    /// Override function for initialize().
    virtual void initializeOverride(const SystemProperties& systemProperties);

    /// Override function for uninitialize().
    virtual void uninitializeOverride();

    /// Override function for initializeGL().
    virtual void initializeGLOverride();

    /// Override function for uninitializeGL().
    virtual void uninitializeGLOverride();

    /// Override function for suspendGL().
    virtual void suspendGLOverride();

    /// Override function for resumeGL().
    virtual void resumeGLOverride();

    /// Override function for main().
    virtual void mainOverride(const SystemProperties& systemProperties);

    /// Override function for input().
    virtual void inputOverride();

    /// Override function for update().
    virtual void updateOverride(chrono::milliseconds deltaTime);

    /// Override function for render().
    virtual void renderOverride();

    /// Override function for suspend().
    virtual void suspendOverride();

    /// Override function for yield().
    virtual void yieldOverride();

    /// Override function for sleep().
    virtual void sleepOverride();

    /// Override function for wakeup().
    virtual void wakeupOverride();

    virtual void onProjectInitialized();

    /// Override function for progressDeploymentQueue().
    virtual void progressDeploymentQueueOverride();

    // Initialization functions.

    virtual void initializeProperties(const SystemProperties& systemProperties);
    virtual void initializeEngine();
    virtual void initializeSystem();

    void projectInitialized();
    void projectLoaded();

    /// To log startup profiling data, use logStartupProfilingData().
    void logStartupProfilingData() const;

    /// Gets the startup profiler registry.
    ///
    /// \return The reference to the startup profiler registry.
    StartupProfilerRegistry& getStartupProfilerRegistry() const
    {
        return *m_startupProfilerRegistry;
    }

    virtual void renderEngine();

    virtual void handleEvents(const KzsEventQueue* eventQueue);

    virtual bool isToolPresent() const { return false; };

    vector<EventSourceSharedPtr> m_eventSources; ///< Container for event sources.
    vector<GraphicsOutputSharedPtr> m_graphicsOutputs; ///< Container for graphics outputs.

    /// Override function for run().
    virtual void runOverride();
    void idle();
    void idleLoop();

    void loadPlugins();

    /// Log graphics information based on application properties.
    void logGraphicsInformation();

    /// Access engine.
    ///
    /// \return Engine instance.
    KzuEngine* getEngine() const;

#ifdef KANZI_FEATURE_3D
    /// Acquire performance info object.
    /// Will create the object if it does not exist.
    PerformanceInfo& acquirePerformanceInfo();
#endif

#ifdef KZU_ENGINE_ENABLE_WATERMARK
    /// Watermark displayed over trial content.
    kanzi::unique_ptr<kanzi::Watermark> m_watermark;

    /** Creates and prepares the watermark if it should be displayed. */
    void initializeWatermark();
#endif

#ifdef KZU_ENGINE_ENABLE_SPLASH_SCREEN
    /// Splash screen displayed at the startup.
    kanzi::unique_ptr<kanzi::SplashScreen> m_splashScreen;

    /** Creates and starts the splash screen if it should be displayed. */
    void initializeSplashScreen();
#endif

    /// Gets the time main thread can sleep in milliseconds, supposing given duration would have passed from the start of the frame.
    /// The time passed is used to determine the remaining sleep time of this frame, for example when some time has elapsed in animations.
    /// \param deltaTime Time passed since the frame started.
    /// \return Maximum time the main thread should sleep. Nothing, if indefinite sleep is proposed.
    optional<chrono::milliseconds> getProposedSleepTime(chrono::milliseconds deltaTime);
    /// Gets the time the main thread can sleep after rendering.
    /// Time spent since beginning of the frame is given so the time spent in rendering can be determined.
    /// \return Maximum time the main thread should sleep.
    chrono::milliseconds getProposedSleepTimePostRender(chrono::milliseconds deltaTime);

    /// Current state of the application.
    State m_state;
    /// System properties.
    SystemProperties m_systemProperties;
    /// Application properties.
    ApplicationProperties m_applicationProperties;

    /// System memory manager (legacy).
    KzcMemoryManager* m_systemMemoryManager;

    /// The event queue for user input and window events.
    KzsEventQueue* m_eventQueue;
    /// Temporary event queue used for combining similar events.
    KzsEventQueue* m_eventQueueBuffer;

    /// Engine instance.
    KzuEngine* m_engine;

    /// Execution scheduler.
    Scheduler m_scheduler;

#ifdef KANZI_FEATURE_3D
    /// Performance info.
    unique_ptr<PerformanceInfo> m_performanceInfo;
#endif

    /// Flag to be set when project has been loaded.
    bool m_projectLoaded;

    /// Suspension manager for main loop.
    SuspensionManager m_suspensionManager;

    /// FPS constraints for main loop.
    FPSConstraints m_fpsConstraints;

private:

    void destruct();

    /// Default timer for the main loop.
    /// Keeps time since start of frame.
    StopWatch m_stopWatch;

    /// Startup profiler registry.
    StartupProfilerRegistryUniquePtr m_startupProfilerRegistry;

    // List of friends of getEngine():
    friend class PreviewApplication;
};

}

#endif
