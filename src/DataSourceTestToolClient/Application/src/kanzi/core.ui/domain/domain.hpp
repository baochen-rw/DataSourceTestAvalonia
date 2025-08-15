// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_UI_DOMAIN_H
#define KZU_UI_DOMAIN_H

#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core.ui/resource/resource_loader_factory.hpp>
#include <kanzi/core.ui/scheduler/task_dispatcher.hpp>
#include <kanzi/core/profiling/profiling.hpp>
#include <kanzi/core/profiling/main_loop_task_profiler_registry.hpp>

struct KzcMemoryManager;
struct KzuBinaryDirectory;
struct KzuBinaryFileInfo;
struct KzuTextRenderer;

namespace kanzi
{

class InputManager;
class FocusManager;
class CompositionManager;
class Module;
class ObjectLoader;
class Renderer;
class Renderer3D;
class PreviewTimeline;
class PreviewTimelinePlayback;
class TimelineClock;

typedef shared_ptr<void> ScriptingSystemSharedPtr;
typedef shared_ptr<PreviewTimeline> PreviewTimelineSharedPtr;
typedef shared_ptr<PreviewTimelinePlayback> PreviewTimelinePlaybackSharedPtr;
typedef shared_ptr<TimelineClock> TimelineClockSharedPtr;

/// Domain binds Kanzi subsystems and objects together.
///
/// All objects and subsystems in Kanzi are associated with a domain when created.
/// Objects in the same domain share access to the same subsystems.
/// Objects from different domains cannot be used together.
class KANZI_API Domain : public Object
{
public:

    /// \name Properties
    /// \{
#include "domain_properties.h"
    /// \}

    KZ_STATIC_METACLASS_BEGIN(Domain, "Kanzi.Domain")
        KZ_METACLASS_PROPERTY_TYPE(ProjectPluginReferencesProperty)
        KZ_METACLASS_PROPERTY_TYPE(StartupScreenProperty)
        KZ_METACLASS_PROPERTY_TYPE(StateToolsEditStateEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(PreviewWindowBackgroundColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(MessageLimitPerFrameProperty)
        KZ_METACLASS_PROPERTY_TYPE(HalfFloatTextureFormatProperty)
        KZ_METACLASS_PROPERTY_TYPE(HalfFloatTextureFormatLinearProperty)
        KZ_METACLASS_PROPERTY_TYPE(HalfFloatColorAttachmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderToMipmapLevelsProperty)
        KZ_METACLASS_PROPERTY_TYPE(ExternalTextureProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    static Domain* create(KzcMemoryManager* memoryManager);

    static void destroy(Domain* domain);

    // TODO: when removing this try remove all includes of domain that were forced due to this function
    KzcMemoryManager* getMemoryManager() const;

    Renderer* getRenderer() const;
    Renderer3D* getRenderer3D() const;
    ResourceManager* getResourceManager() const;
    ResourceLoaderFactory* getResourceLoaderFactory() const;
    KzuMessageDispatcher* getMessageDispatcher() const;
    /// Returns the task dispatcher of this domain.
    /// You can use the task dispatcher returned by this function to dispatch tasks that the system will execute on the thread of this domain.
    /// \see TaskDispatcher
    TaskDispatcher* getTaskDispatcher() const;
    InputManager* getInputManager() const;
    /// Returns the domain's focus manager.
    /// \return The focus manager of the domain.
    FocusManager* getFocusManager() const;
    KzuTaskScheduler* getTaskScheduler() const;
    KzuTextRenderer* getTextRenderer() const;
    ObjectFactory* getObjectFactory() const;
    ObjectLoader* getObjectLoader() const;
    TimelineClockSharedPtr getRootTimelineClock() const;
    PreviewTimelinePlaybackSharedPtr getPreviewTimelinePlayback() const;
    CompositionManager* getCompositionManager() const;

    /// Set composition manager.
    /// Will take ownership of composition manager passed.
    /// \param compositionManager New composition manager.
    void setCompositionManager(unique_ptr<CompositionManager> compositionManager);

    ScriptingSystemSharedPtr getScriptingSystem() const;
    void setScriptingSystem(ScriptingSystemSharedPtr scriptingSystem);

    /// Register a Module and the metadata it contains.
    void registerModule(string_view moduleName, shared_ptr<Module> module);

    template<typename TModule>
    void registerModule(string_view moduleName)
    {
        shared_ptr<TModule> module = make_shared<TModule>();
        registerModule(moduleName, module);
    }

    /// Get Module instance by the name it is registered with.
    Module* getModule(string_view moduleName);

    void loadPlugin(string_view moduleName);

    /// Enables or disables editing mode.
    ///
    /// Preview timeline will be created or destroyed depending on whether editing is enabled or not..
    void enableEditing(bool enable)
    {
        m_isEditingEnabled = enable;

        if (enable)
        {
            createPreviewTimeline();
        }
        else
        {
            destroyPreviewTimeline();
        }
    }

    bool isEditingEnabled() const
    {
        return m_isEditingEnabled;
    }

    /// Create preview timeline context.
    void createPreviewTimeline();
    /// Destroy preview timeline context.
    void destroyPreviewTimeline();

    /// Gets the main loop task profiler registry.
    ///
    /// \return The reference to the main loop task profiler registry.
    MainLoopTaskProfilerRegistry& getMainLoopTaskProfilerRegistry()
    {
        return *m_mainLoopTaskProfiler;
    }

protected:

    static kzsError timelineClockTask(kzUint deltaTime, void* userData, kzBool* out_done);

private:

    explicit Domain();
    ~Domain();

    Domain(const Domain&) KZ_DELETED_FUNCTION;
    Domain& operator=(const Domain&) KZ_DELETED_FUNCTION;

    struct TaskSchedulerDeleter
    {
        void operator()(KzuTaskScheduler* p) const;
    };

    struct MessageDispatcherDeleter
    {
        void operator()(KzuMessageDispatcher* p) const;
    };

    struct TextRendererDeleter
    {
        void operator()(KzuTextRenderer* p) const;
    };

    KzcMemoryManager* m_memoryManager;
    unique_ptr<ObjectFactory> m_objectFactory;
    unique_ptr<ObjectLoader> m_objectLoader;
    unique_ptr<KzuTaskScheduler, TaskSchedulerDeleter> m_taskScheduler;
    unique_ptr<KzuMessageDispatcher, MessageDispatcherDeleter> m_messageDispatcher;
    unique_ptr<TaskDispatcher> m_taskDispatcher;

    unique_ptr<ResourceManager> m_resourceManager;
    unique_ptr<ResourceLoaderFactory> m_resourceLoaderFactory;

    unique_ptr<Renderer> m_renderer;
    unique_ptr<Renderer3D> m_renderer3D;
    unique_ptr<CompositionManager> m_compositionManager;
    unique_ptr<KzuTextRenderer, TextRendererDeleter> m_textRenderer;

    // Focus manager object.
    unique_ptr<FocusManager> m_focusManager;
    unique_ptr<InputManager> m_inputManager;

    ScriptingSystemSharedPtr m_scriptingSystem;
    TimelineClockSharedPtr m_rootTimelineClock;
    PreviewTimelineSharedPtr m_previewTimeline;
    PreviewTimelinePlaybackSharedPtr m_previewTimelinePlayback;

    unordered_map<string, shared_ptr<Module> > m_registeredModules;

    /// Flag indicating if editing should be enabled.
    bool m_isEditingEnabled;

    /// The main loop task profiler registry.
    MainLoopTaskProfilerRegistryUniquePtr m_mainLoopTaskProfiler;
};

}

/** Loads settings from directory. */
KANZI_API kzsError kzuUIDomainLoadSettingsFromDirectory(const kanzi::Domain* domain, const KzuBinaryDirectory* directory);
/** Loads settings from file. */
KANZI_API kzsException kzuUIDomainLoadSettingsFromFile(kanzi::Domain* domain, const KzuBinaryFileInfo* file);


#endif
