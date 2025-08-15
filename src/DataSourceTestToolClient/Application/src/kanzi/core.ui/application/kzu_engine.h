/** \file
* Structure for engine. Contains pipeline specific assets (current scene, renderer), timer, etc.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_ENGINE_H
#define KZU_ENGINE_H

#include <kanzi/core.ui/node/screen.hpp>

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <kanzi/core.ui/application/splash.hpp>
#include <kanzi/core.ui/application/watermark.hpp>
#include <kanzi/core.ui/assets/runtime_assets.hpp>
#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/node/camera.hpp>
#include <kanzi/core.ui/node/light.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node/scene.hpp>
#include <kanzi/core.ui/node/viewport2d.hpp>
#include <kanzi/core.ui/object/register_default_types.hpp>
#include <kanzi/core.ui/resource/register_default_resources.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core.ui/template/prefab.hpp>
#include <kanzi/core/legacy/legacy_conversions.hpp>
#include <kanzi/core/metadata/meta_object_factory.hpp>

#include <kanzi/core.ui/graphics3d/kzu_object_source.h>
#include <kanzi/core.ui/input/input_manager.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_directory.h>
#include <kanzi/core.ui/kzb/kzu_binary_loader.h>
#include <kanzi/core.ui/kzb/kzu_binary_util.h>
#include <kanzi/core.ui/kzb/kzu_preview_patcher.h>
#include <kanzi/core/legacy/kzu_error_codes.h>
#include <kanzi/core.ui/legacy/kzu_frame_time_queue.hpp>
#include <kanzi/core.ui/node/kzu_transformed_object.h>
#include <kanzi/core.ui/node/kzu_transformed_scene.h>
#include <kanzi/core.ui/scheduler/kzu_task_scheduler.h>
#include <kanzi/core.ui/text/kzu_text_renderer.h>


#include <kanzi/core/legacy/memory/kzc_memory_manager.hpp>
#include <kanzi/core/legacy/memory/kzc_memory_quick.hpp>
#include <kanzi/core/legacy/util/collection/kzc_dynamic_array.hpp>
#include <kanzi/core/legacy/util/collection/kzc_hash_map.hpp>
#include <kanzi/core/legacy/util/collection/kzc_hash_set.hpp>
#include <kanzi/core/legacy/util/string/kzc_string.hpp>

#include <kanzi/core/legacy/thread/kzs_thread.hpp>
#include <kanzi/core/legacy/time/kzs_tick.hpp>

#include <kanzi/core/legacy/file/kzs_mmap.hpp>
#include <kanzi/core/profiling/startup_profiler_registry.hpp>


/** Default vertex buffer pool size. */
#define KZU_ENGINE_DEFAULT_VERTEX_BUFFER_POOL_SIZE (1 << 22)
/** Default index buffer pool size. */
#define KZU_ENGINE_DEFAULT_INDEX_BUFFER_POOL_SIZE (1 << 20)


/* Forward declaration structures. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzuTaskScheduler;
struct KzuPreviewProperties;

namespace kanzi
{

class InputManager;
class GraphicsOutput;
class Scene;
class Domain;
class Camera;
class Framebuffer;
struct ApplicationProperties;
class ResourceManager;
class LayerRenderpass;
class Renderer3D;
class TransformedScene2D;

typedef shared_ptr<Framebuffer> FramebufferSharedPtr;
}

/**
* \struct KzuEngine
* Structure for graphics engine core functionality. Handles the state machine, pipeline and storage specific functionality.
*/
struct KzuEngine;

/** Structure for graphics engine core functionality. Handles the state machine, pipeline and storage specific functionality. */
struct KzuEngine
{
    explicit KzuEngine() :
        minimumDeltaTime(0),
        domain(),
        binaryLoader(),
        newBinaryName(),
        m_useMemoryMappedLoading(false),
        m_startupProfilerRegistry()
    {
    }

    kanzi::FrameTimeQueue frameTimeQueue; /**< FPS calculator. */
    unsigned int minimumDeltaTime;        /**< Minimum delta time (time from previous frame). */

    kanzi::Domain* domain;           /**< UI domain. */
    KzuBinaryLoader* binaryLoader;   /**< Binary loader. */
    kzMutableString newBinaryName;   /**< Name of binary file / config file, which will be loaded in the next update. */
    kzBool m_useMemoryMappedLoading; ///< Use memory mapping when loading KZB files.

    /// Rendering area offset.
    kanzi::Vector2 m_renderingAreaOffset;
    /// Root framebuffer to use, mostly empty.
    kanzi::FramebufferSharedPtr m_rootFramebuffer;

    kanzi::ScreenSharedPtr screen; ///< Screen to be rendered on the graphics output.

    kanzi::string m_startupPrefabUrl;

    kanzi::StartupProfilerRegistry* m_startupProfilerRegistry;
};


/** Create a new engine and necessary components for it, such as renderer and its default materials. */
KANZI_API kzsError kzuEngineCreate(KzcMemoryManager* memoryManager, kzUint loadingThreadCount, kzUint maxPendingResources, kzString binaryName, kzBool useMemoryMappedLoading, kzBool enableEditing, kanzi::StartupProfilerRegistry* m_startupProfilerRegistry, struct KzuEngine** out_engine);
/** Deletes an engine. */
KANZI_API kzsError kzuEngineDelete(KzuEngine* engine);

/** Updates engine FPS calculations. Should be called once per frame. */
KANZI_API void kzuEngineMeasurePerformance(struct KzuEngine* engine, kanzi::chrono::milliseconds deltaTime);
/** Gets frames per second from engine (FPS), measuring the overall frames per second. */
KANZI_API kzFloat kzuEngineGetFramesPerSecond(const struct KzuEngine* engine);

/** Initialization. Loads metadata, including properties and messages from all .KZB files. */
KANZI_API kzsError kzuEngineInitialize(struct KzuEngine* engine, kzBool toolPresent);
/** Loads the KZB files if they have not yet been loaded. */
KANZI_API kzsError kzuEngineLoadBinary(struct KzuEngine* engine, kzBool toolPresent);
/**
 * Makes engine to load a new binary from given binary name in the beginning of next update loop.
 * \param binaryName Path to either the binary config file listing all .kzb files that are loaded to project, or a path to a single .kzb file.
 * \return ::KZS_SUCCESS on success.
 */
KANZI_API kzsError kzuEngineSetBinary(struct KzuEngine* engine, kzString binaryName);

KANZI_API struct KzuBinaryLoader* kzuEngineGetBinaryLoader(const struct KzuEngine* engine);

/** Sets screen of engine. */
KANZI_API kzsError kzuEngineSetScreen(struct KzuEngine* engine, kanzi::ScreenSharedPtr screen);
/** Gets screen of engine. */
KANZI_API kanzi::ScreenSharedPtr kzuEngineGetScreen(const struct KzuEngine* engine);

/** Sets the orientation of the screen. */
KANZI_API kzsError kzuEngineSetScreenOrientation(struct KzuEngine* engine, enum KzsWindowOrientation orientation);

/** Invalidates the layout of the attached screen. */
KANZI_API void kzuEngineInvalidateScreenLayout(struct KzuEngine* engine);

KANZI_API kzsError kzuEnginePatchProject(struct KzuEngine* engine, kzUint byteCount, const kzByte* bytes);
KANZI_API kzsError kzuEnginePatchProjectFromFile(const struct KzuEngine* engine, kzString binaryPath);
KANZI_API kzsError kzuEnginePatchProjectFromFileResource(const struct KzuEngine* engine, kzString resourceFile);

KANZI_API kzsError kzuEngineInvalidateGPUResources(const struct KzuEngine* engine);
KANZI_API kzsError kzuEngineRestoreNodeResources(const struct KzuEngine* engine);

/// Set root framebuffer for engine to use.
///
/// \param engine Engine.
/// \param framebuffer Root framebuffer used from now on.
KANZI_API void kzuEngineSetRootFramebuffer(struct KzuEngine* engine, kanzi::FramebufferSharedPtr framebuffer);
/// Access root framebuffer from engine.
///
/// \param engine Engine.
/// \return Root framebuffer in use, may be an empty pointer.
KANZI_API kanzi::FramebufferSharedPtr kzuEngineGetRootFramebuffer(struct KzuEngine* engine);

KANZI_API kanzi::Vector2 kzuEngineGetRenderingAreaOffset(struct KzuEngine* engine);
KANZI_API void kzuEngineSetRenderingAreaOffset(struct KzuEngine* engine, const kanzi::Vector2& offset);

/** Gets last frame time in milliseconds. */
KANZI_API kzUint kzuEngineGetLastFrameTime(const struct KzuEngine* engine);

#endif
