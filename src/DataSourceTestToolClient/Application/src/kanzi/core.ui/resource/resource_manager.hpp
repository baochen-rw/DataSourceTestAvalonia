// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_MANAGER_HPP
#define KZ_RESOURCE_MANAGER_HPP

#include <kanzi/core.ui/bitmap/bitmap_image.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_common.h>
#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core.ui/resource/resource_profiler.hpp>
#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/detail/thread_handle.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/cpp/variant.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/util/byte_span.hpp>

// Forward declaration.
struct KzcMemoryManager;
struct KzcSpline;
struct KzuBinaryDirectory;

namespace kanzi
{

// Forward declaration.
class Brush;
class Domain;
class GPUResource;
class KzbFile;
class KzbMemoryParser;
class PreviewPatcher;
class ResourceManager;
class ReadOnlyMemoryFile;
struct ResourceLoaderThreadContext;
class ResourceProfilingLoadTask;
typedef shared_ptr<Brush> BrushSharedPtr;
typedef shared_ptr<KzbFile> KzbFileSharedPtr;

/// Resource manager shared pointer type.
typedef shared_ptr<ResourceManager> ResourceManagerSharedPtr;

/// Use the %resource manager to access and use resources in kzb files. The resource manager maintains
/// kzb files and provides mechanisms to load resources from kzb files.
///
/// To access resources in a kzb file, use the kzb URL of the resource that you want to access.
/// For example, the URL string "kzb://programmer_tutorial/Prefabs/Widget Item Prefab" refers to
/// the resource called "Widget Item Prefab" inside the folder "Prefabs" in the kzb file of the
/// "programmer_tutorial" project.
///
/// Acquiring resources from kzb
/// ----
/// When you acquire a URL for the first time, the resource manager loads the resource and caches it.
/// The next time you use the same URL, Kanzi does not load the resource again, but returns the previously
/// loaded resource instead.
///
/// To acquire a single resource, use #acquireResource:
/// \snippet snippets_resource_manager.cpp Acquiring a single resource
///
/// Releasing resources
/// ----
/// Kanzi manages the lifetime of resources with shared pointers, but to cache resources, the resource
/// manager maintains a shared pointer to each acquired resource. This means that Kanzi does not
/// automatically release the memory used by resources, even if you are not using those resources.
///
/// To destroy resources and release the memory used up by those resources, use #purge:
/// \snippet snippets_resource_manager.cpp Purging resources
///
/// Acquiring resources asynchronously
/// ----
/// The resource manager uses worker threads to load multiple resources simultaneously and in the background, while the application is running.
/// You can use Application::onConfigure to specify the number of loader threads. With loader threads
/// you can load textures, meshes, and shaders. Kanzi uses the main thread to load all other types of resources.
///
/// You can decrease the loading time of resources by first collecting the URLs of all resources and loading multiple resources
/// simultaneously. Kanzi does this automatically for the startup screen. If you are instantiating prefabs using the API, you can
/// use #collectResourceUrls to collect the URLs and #acquireResourcesAsync to acquire the resources:
/// \snippet snippets_resource_manager.cpp Acquiring resources asynchronously
/// If you need the results immediately, you can use #wait:
/// \snippet snippets_resource_manager.cpp Waiting on an acquire task
/// \see collectResourceUrls, loadPrefabAsync
///
/// Managing kzb files
/// ----
/// At application startup, Kanzi opens the kzb files that you specify in the application.cfg or in the configuration file specified
/// by the Application::onConfigure. With the resource manager you can use #addKzbFile to open additional kzb files at runtime:
/// \snippet snippets_resource_manager.cpp Adding KZB files
///
/// Acquiring resources from the file system
/// ----
/// Besides loading resources from kzb files, you can load resources from the file system. The resource manager supports the loading
/// of these resource types from the file system:
/// - Texture from png, jpg, and jpeg files
/// - KzuFont from ttf files
/// - BinaryResource from js files
///
/// Kanzi determines the type of the resource it creates from the file extension, not from the file contents.
/// You have to ensure that the files use correct extensions.
///
/// To load resources from the file system, use the %file:// protocol:
/// \snippet snippets_resource_manager.cpp Using file protocol
class KANZI_API ResourceManager
{
public:
    /// %Resource manager memory strategy.
    enum MemoryStrategy
    {
        /// When a resource is no longer referenced, the resource manager keeps the resource in memory
        /// until you call \ref purge().
        KeepInMemory,

        /// When a resource is no longer referenced, the resource manager deletes the resource and frees
        /// the (CPU and GPU) memory used by the resource.
        OptimizeMemory
    };

    /// Container type for URL set.
    typedef unordered_set<string> UrlContainer;

    /// Use this base class to implement load tasks to load new resources.
    /// A load task is split into an optional #loadFunction and a mandatory #finishFunction.
    /// You can call the #loadFunction in a background worker thread, instead of the main thread.
    /// In the #loadFunction execute only thread-independent work.
    /// Kanzi always calls the #finishFunction in the main thread.
    /// Kanzi executes the load task in this order:
    /// -# The loading thread or main thread executes the #loadFunction.
    /// -# The main thread executes the #finishFunction.
    /// -# The load task returns the created resource with #getResult.
    /// To trigger background loading of dependencies, in the #loadFunction call #enqueueDependencies.
    struct KANZI_API LoadTask : public enable_shared_from_this<LoadTask>
    {
        /// The type of the load task.
        enum Type
        {
            /// Load task type with both #loadFunction and #finishFunction parts.
            LoadAndFinish,

            /// Load task type that executes everything only in the #finishFunction.
            /// For such tasks, Kanzi never calls the #loadFunction.
            FinishOnly
        };

        /// The state of the load task.
        enum State
        {
            /// The initial state of the task when you create the task.
            Initialized,

            /// Waiting for the execution of the #loadFunction that is usually in the loading queue.
            WaitingToLoad,

            /// Kanzi is executing the #loadFunction.
            Loading,

            /// Waiting for completion of dependencies.
            WaitingForDependencies,

            /// Waiting for the execution of the #finishFunction that is usually in the finishing queue.
            WaitingToFinish,

            /// Kanzi is executing the #finishFunction.
            Finishing,

            /// Kanzi completed the execution of both #loadFunction and #finishFunction.
            Finished
        };

        /// Constructor.
        /// Type is set to LoadAndFinish.
        explicit LoadTask();

        /// Constructor.
        /// \param type Load task type.
        explicit LoadTask(const Type type);

        /// Destructor.
        virtual ~LoadTask();

        /// You can override this function to define the part of the resource loading task that a worker thread executes.
        /// You cannot access any shared data inside the function.
        /// \param resourceLoaderThreadContext The context of the loader thread.
        virtual void loadFunction(const ResourceLoaderThreadContext* resourceLoaderThreadContext) = 0;

        /// The part of the loading that the main thread executes. The function creates and stores
        /// a new resource that #getResult returns.
        /// \param resourceLoaderThreadContext The context of the loader thread that was used to call loadFunction.
        virtual void finishFunction(const ResourceLoaderThreadContext* resourceLoaderThreadContext) = 0;

        /// Returns the created resource.
        /// \return The created resource.
        virtual ResourceSharedPtr getResult() = 0;

        /// Gets the type of a load task.
        /// \return The type of the load task.
        Type getType() const;

        /// Gets the resource manager of a load task.
        /// \return Pointer to the resource manager.
        ResourceManager* getResourceManager() const;

    protected:
        /// Adds resource dependencies for a load task.
        /// Inside a #loadFunction implementation you can call this function any number of times.
        /// When you call this function it informs the main thread about the dependencies of a load task, which then triggers
        /// the asynchronous loading of these dependencies.
        /// \param urls Container of dependency URLs.
        void enqueueDependencies(UrlContainer urls);

    private:
        /// Implementation class.
        class Impl;

        /// Alias for unique pointer of implementation.
        typedef unique_ptr<Impl> ImplUniquePtr;

        /// Implementation instance.
        ImplUniquePtr m_impl;

        /// Friend classes.
        friend class ResourceManager;
        friend class FinishingQueue;
    };

    /// LoadTask shared pointer type.
    typedef shared_ptr<LoadTask> LoadTaskSharedPtr;

    /// Type definition for the protocol handler of the load function. The load function takes a resource
    /// URL and creates either a new resource or a load task that creates a new resource.
    ///
    /// \param resourceManager The resource manager.
    /// \param resourceURL The full URL of the resource in the form of protocol://hostname[:port]/path.
    /// \param protocol Extracted protocol part of the resource URL.
    /// \param hostname Extracted hostname part of the resource URL.
    /// \param port Extracted port part of the resource URL. This is 0 if the port is omitted from the URL.
    /// \param path Extracted path part of the resource URL.
    /// \param userData The extra protocol specific data object that was stored when the protocol handler was registered.
    /// \param out_resource The loaded resource, or nullptr.
    /// \param out_loadTask A load task for the resource, or nullptr.
    /// \return Success or exception.
    typedef kzsException (*ProtocolHandler)(ResourceManager* resourceManager, string_view resourceURL,
                                            string_view protocol, string_view hostname, unsigned port, string_view path, void* userData, ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Type definition for the protocol handler of the reload function. The reload function takes a resource
    /// URL and an existing resource, and reloads the resource.
    typedef function<void(ResourceManager*, string_view resourceURL, string_view protocol, string_view hostname, unsigned port, string_view path, void* userData, Resource* resource)> ProtocolResourceReloadFunction;

    /// Type for the directory container.
    /// \deprecated Part of the legacy kzb loading.
    typedef vector<pair<string, KzuBinaryDirectory*> > DirectoryContainer;

    /// Container type for the finishing queue. Used internally.
    typedef vector<LoadTaskSharedPtr> FinishingQueueContainer;

    /// Constructor.
    /// \param memoryManager Memory manager to use.
    explicit ResourceManager(KzcMemoryManager* memoryManager);

    /// Destructor.
    ~ResourceManager();

    /// Initializes the additional resource loader threads for the resource manager.
    /// Do not call this function, because Kanzi automatically calls it.
    /// \param threadCount The number of loader threads. If 0, parallel loading is disabled.
    /// \param maxPendingResources The maximum number of resources that can be processed by the loading threads at the same time. If set to 0, behaves as if set to threadCount + 1.
    void initializeLoaderThreads(size_t threadCount, size_t maxPendingResources);

    /// Kanzi internally uses this function when application is about to lose GL context, to wait for all existing acquire tasks to finish.
    void waitForAcquireTasks();

    /// Stops and removes the loader threads. After the call, all loading happens in the main thread.
    void uninitializeLoaderThreads();

    /// Gets the native handle of a loader thread.
    /// You can use the native handle of a thread to set the priority of that thread,
    /// or to assign that thread to a dedicated CPU core:
    /// \snippet snippets_resource_manager.cpp Retrieving loader thread handle
    ///
    /// %Resource manager creates all its loader threads during application startup
    /// and does not add or delete loader threads during the rest of application runtime,
    /// except during shutdown.
    /// An appropriate place to adjust loader thread settings is in the Application::onStartup()
    /// overloaded function. Kanzi calls this function after the ResourceManager created
    /// its loader threads and before Kanzi starts using loader threads for loading assets
    /// from kzb files.
    /// \param threadIndex Index of the loader thread.
    /// \return Returns the native handle of the thread at threadIndex. If \a threadIndex is out of bounds, throws an \a out_of_range exception.
    ThreadNativeHandleType getLoaderThreadHandle(size_t threadIndex);

    /// Gets the number of loader threads of the resource manager.
    /// \return The number of loader threads. If parallel loading is disabled, the function returns 0.
    size_t getLoaderThreadCount() const;

    /// You can use this function to change the maximum number of resources that can be processed by the loading threads at the same time.
    /// \param maxPendingResources The maximum number of resources that can be processed by the loading threads at the same time. If set to 0, behaves as if set to threadCount + 1.
    void setMaxPendingResources(size_t maxPendingResources);


    /// Adds a binary directory to the resource manager to be used with the kzb protocol.
    /// This transfers the ownership of the binary directory to the resource manager.
    /// \param directory The binary directory you want to add.
    /// \deprecated Part of the legacy kzb loading. Use #addKzbFile instead.
    void addDirectory(KzuBinaryDirectory* directory);

    /// Merges a binary directory with another binary directory that has the same name and that already exists
    /// in the resource manager:
    /// - If a directory with the same name already exists, this function merges the directory you
    /// pass to the existing directory and destroys the directory you passed. The files in the binary
    /// directory you pass take precedence over the files with the same name in the existing directory.
    /// - If a binary directory with the same name does not exist, the result is the same as when
    /// you use addDirectory.
    /// \param directory The binary directory you want to merge.
    /// \return A pointer to the merged directory.
    /// \deprecated Part of the legacy kzb loading. Use #addKzbFile instead.
    KzuBinaryDirectory* mergeDirectory(KzuBinaryDirectory* directory);

    /// Removes a binary directory from the resource manager.
    /// \param directory The binary directory you want to remove.
    /// \deprecated Part of the legacy kzb loading.
    void removeDirectory(KzuBinaryDirectory* directory);


    /// Opens a kzb file from the file system and adds it to the list of files. If this function cannot
    /// open the file you pass to it or that file is not a kzb file, the function throws an exception.
    /// \param fileName The name of the file to open.
    void addKzbFile(string_view fileName);

    /// Adds a kzb file to the list of files.
    /// \param kzbFile File to add.
    void addKzbFile(unique_ptr<KzbFile> kzbFile);

    /// Adds a memory block as a kzb file. This function internally creates a kzb file by reading the memory block.
    /// \param data Data to add. The memory area must be readable as long as the resource manager is alive.
    void addKzbFile(ConstByteSpan data);

    /// Opens a handle to a resource file inside a kzb file. You can use this handle to read data directly from the kzb file.
    /// \param url URL of the resource.
    /// \param [out] kzbFile If the function finds the resource file, returns a pointer to the kzb file.
    /// \return Handle that points to the data inside the kzb file.
    unique_ptr<ReadOnlyMemoryFile> openFile(string_view url, KzbFile** kzbFile);


    /// Gets the binary directory with the given name from the resource manager.
    /// \return nullptr if the function cannot find the directory.
    /// \deprecated Part of the legacy kzb loading. Use #getKzbFile instead.
    KzuBinaryDirectory* getDirectory(string_view name) const;

    /// Adds a binary directory from a kzb file to the resource manager, which you can then use with
    /// the kzb protocol. The resource manager keeps the ownership of the binary directory.
    /// \param fileName Path to the kzb file.
    ///                 Note that the filename can be different from the directory name stored in the
    ///                 kzb file. For example, file Programmer_tutorial.kzb can contain a directory named
    ///                 programmer_tutorial.
    /// \return A pointer that is set to point to the binary directory of the loaded kzb file.
    /// \deprecated Part of the legacy kzb loading. Use #addKzbFile instead.
    KzuBinaryDirectory* addDirectoryFromFile(string_view fileName);

    /// Loads a binary directory from a kzb file and merges it with another binary directory with the
    /// same name that already exists in the resource manager.
    /// \see For details about the merge process, see mergeDirectory().
    /// \param fileName The name of the kzb file from which to load the binary directory.
    /// \return If successful, a pointer to the merged directory, otherwise nullptr.
    /// \deprecated Part of the legacy kzb loading. Use #addKzbFile instead.
    KzuBinaryDirectory* mergeDirectoryFromFile(string_view fileName);

    /// Returns the iterator to the beginning of binary directories.
    /// \deprecated Part of the legacy kzb loading. Use #beginKzbFiles instead.
    DirectoryContainer::const_iterator beginDirectories() const
    {
        return m_directories.begin();
    }
    /// Returns the iterator to the end of binary directories.
    /// \deprecated Part of the legacy kzb loading. Use #endKzbFiles instead.
    DirectoryContainer::const_iterator endDirectories() const
    {
        return m_directories.end();
    }

    /// Kanzi internally uses this function to set all the GPU resources to undeployed state when an
    /// application loses and recreates the GL context after a pause-resume event.
    void invalidateAllGPUResources();

    /// Calculates the memory usage summary for all resources.
    /// \param out_resourceCount The total number of resources.
    /// \param out_cpuMemoryUsage Estimate for the total amount of bytes of CPU memory that the resources use.
    /// \param out_gpuMemoryUsage Estimate for the total amount of bytes of GPU memory that the resources use.
    void getMemoryUsage(size_t* out_resourceCount, size_t* out_cpuMemoryUsage, size_t* out_gpuMemoryUsage) const;

    /// Returns the number of acquire tasks that have been started with a call to acquireResourcesAsync and have not yet been
    /// completed. Each acquire task can load multiple resources.
    /// \return The number of acquire tasks.
    size_t getAcquireTaskCount() const;

    /// Returns the number of resource load tasks in the load queue.
    /// This includes the load tasks that are waiting to be loaded and load tasks that are currently being loaded.
    /// This does not include the load tasks that are in the finishing queue.
    /// \return The number of load tasks in load queue.
    size_t getLoadQueueSize() const;

    /// Returns the domain.
    /// \return The domain.
    Domain* getDomain() const;

    /// Registers a protocol handler for loading resources specified with the given resource URL protocol (scheme name).
    /// \param protocol The protocol name. For example, "http".
    /// \param handler The protocol loader function. Kanzi calls this function when you use a URL with the given protocol,
    ///                and Kanzi does not find an existing resource with that URL. This loader function creates a resource.
    /// \paran reloadFunction The protocol reloader function. Kanzi calls this function to recreate an existing resource.
    ///                       Kanzi uses this function only for GPU resources when an application loses GL context in a
    ///                       pause-resume event.
    /// \param userData Extra data that you want to pass to the handler functions.
    void registerProtocolHandler(kzString protocol, ProtocolHandler handler, ProtocolResourceReloadFunction reloadFunction, void* userData);
    /// Unregisters the protocol handler with the given resource URL protocol (scheme name).
    void unregisterProtocolHandler(kzString protocol);
    /// Checks whether the given resource URL protocol (scheme name) is registered as a protocol handler for the resource manager.
    /// \param protocol The protocol to check.
    /// \return True if the protocol is registered, otherwise False.
    bool supportsProtocolHandler(kzString protocol) const;

    /// Acquires a resource associated with the given URL. If no resource is associated with the URL, tries to load the resource from
    /// the location specified by the URL. The URL specifies the location with a protocol and a protocol-specific path.
    /// If you already earlier acquired the resource at the given URL, this function returns a shared pointer to the already acquired resource.
    ///
    /// The supported protocols are:
    /// - kzb protocol for loading resources from kzb files. For example, "kzb://programmer_tutorial/Prefabs/Widget Item Prefab".
    ///   If the function cannot find the given URL in the added binary directories, the function throws an exception.
    /// - File protocol for loading resources from external files. For example, "file://./Icon.png".
    ///
    /// \param url URL of the resource.
    /// \return Shared pointer to the resource.
    ResourceSharedPtr acquireResource(string_view url);

    /// Acquires a resource associated with the given URL, like #acquireResource, but does not throw exceptions.
    /// \see acquireResource
    /// \param url URL of the resource.
    /// \return Shared pointer to the resource. If the resource does not exist, nullptr.
    ResourceSharedPtr tryAcquireResource(string_view url);

    /// Acquires a resource associated with the given URL and casts the resource to the given type.
    /// If the type cast fails, the function returns nullptr.
    /// \see acquireResource
    /// \param url URL of the resource.
    /// \return Shared pointer to the resource. If the resource does not exist, or has different type, nullptr.
    template <typename Type>
    shared_ptr<Type> tryAcquireResource(string_view url)
    {
        return dynamic_pointer_cast<Type>(tryAcquireResource(url));
    }

    /// Acquires a resource associated with the given URL and casts the resource to the given type.
    /// If the resource does not exist or the type cast fails, the function throws an exception.
    /// \see acquireResource
    /// \param url URL of the resource.
    /// \return Shared pointer to the resource.
    template <typename Type>
    shared_ptr<Type> acquireResource(string_view url)
    {
        ResourceSharedPtr baseResource = acquireResource(url);
        if (!baseResource)
        {
            kzThrowException(runtime_error("Resource with URL '" + string(url) + "' not found."));
        }

        shared_ptr<Type> resource = dynamic_pointer_cast<Type>(baseResource);
        if (!resource)
        {
            kzThrowException(runtime_error("Bad dynamic cast when acquiring resource URL '" + string(url) + "'."));
        }
        return resource;
    }

    /// Associates the given URL with the resource so that the next #acquireResource with the URL returns the resource.
    /// You can use this function to provide a URL to a resource that you created using the API.
    /// \param url URL of the resource.
    /// \param resource The registered resource.
    void registerResource(string_view url, ResourceSharedPtr resource);
    /// Associates the given URL with the resource so that the next #acquireResource with the URL completes the load task and returns the result.
    /// \param url URL of the resource.
    /// \param loadTask A load task that creates the resource at the given URL.
    void registerLoadTask(string_view url, LoadTaskSharedPtr loadTask);
    /// Removes the association of the given URL to a resource or a load task.
    /// You can use this function to force Kanzi to recreate a resource the next time you use this URL.
    /// \param url URL of the resource.
    void unregisterResource(string_view url);

    /// Acquires a resource associated with the given URL. If no resource is associated with the URL, does not try to load the resource.
    /// \param url URL of the resource.
    /// \return The resource that was loaded with the given URL. If no resource was loaded with the given URL, nullptr.
    ResourceSharedPtr acquireLoadedResource(string_view url) const;

    /// Loads an image from the given URL.
    /// \deprecated Part of the legacy kzb loading.
    BitmapImageUniquePtr loadImage(string_view url) const;

    /// Loads a spline from the given URL.
    /// \deprecated Part of the legacy kzb loading.
    KzcSpline* loadSpline(string_view url) const;

    /// Tries to find a URL for the given resource. This function loops over all resources,
    /// so it can take a long time to complete.
    /// \param resource The resource.
    /// \return The resource URL. If the resource does not have a registered URL, an empty string.
    string getResourceURL(const Resource& resource) const;

    /// Kanzi internally uses this function to convert a resource URL to a resource path by dropping
    /// the protocol and project name from the path. For example, converts the URL "kzb://programmer_tutorial/Textures/bgr"
    /// to "Textures/bgr".
    /// \param resourceURL A resource URL.
    /// \return The resource URL without protocol and project name.
    static kzString getResourcePathFromURL(kzString resourceURL);

    /// Kanzi internally uses this function to convert an absolute path to a node to a relative path
    /// by removing the screen name part of the path. For example, converts the path "Screen/RootPage/Viewport 2D"
    /// to "RootPage/Viewport 2D".
    /// \param absolutePath Absolute path to a node in the tree.
    /// \return Relative path to the node from the Screen node.
    static kzString getRelativePathFromAbsolutePath(kzString absolutePath);

    /// Sets the memory release strategy for new resources.
    /// \param resourceReleaseStrategy The new memory strategy.
    void setDefaultMemoryStrategy(MemoryStrategy resourceReleaseStrategy);
    /// Gets the memory release strategy.
    /// \return The current memory strategy.
    MemoryStrategy getDefaultMemoryStrategy() const;

    /// Deletes unreferenced resources. You can use this function to free memory.
    /// Destroys all resources that are referenced only by the resource manager.
    void purge();

    /// Processes resource manager load and deployment queues to progress the background tasks.
    /// Kanzi calls this function once every frame.
    void update();

    /// Collection of resource loading tasks that have been already been loaded by a loader thread and are waiting to be finished by the main thread.
    /// You can override the Application::progressDeploymentQueueOverride and access the finishing queue with ResourceManager::getFinishingQueue
    /// to control when and which resources are deployed.
    class KANZI_API FinishingQueue
    {
    public:
        /// Returns the number of load tasks in the finishing queue that are waiting to be finished.
        /// \return The number of load tasks in the finishing queue.
        size_t size() const
        {
            return m_tasks.size();
        }

        /// Indicates whether the finishing queue contains load tasks that are waiting to be finished.
        /// \return If the queue is empty, true, otherwise false.
        bool empty() const
        {
            return m_tasks.empty();
        }

        /// Returns the URL of the load task with the given index in the finishing queue.
        /// \param index Index the load task.
        /// \return The URL of the load task. Valid until the load task if completed.
        string_view getTaskUrl(size_t index) const;

        /// Completes the finishing part of a load task with the given index in the finishing queue.
        /// Note that this removes the task from the finishing queue and changes the indices of the remaining items.
        /// \param index Index of the load task that is finished.
        void finishTask(size_t index);

    private:
        friend class ResourceManager;

        /// Constructor.
        explicit FinishingQueue(ResourceManager& resourceManager) :
            m_resourceManager(resourceManager)
        {
        }

        /// Adds a task to the finishing queue.
        /// \param task The added task. The task should have the loading part completed.
        void addTask(LoadTaskSharedPtr task);

        /// Adds multiple tasks to the finishing queue.
        /// \param queue Container with tasks that have completed the loading part.
        void addTasks(FinishingQueueContainer queue);

        /// Completes a single task in the finishing queue.
        /// \param loadTask A load task that is in the finishing queue.
        void finishTask(LoadTaskSharedPtr loadTask);

        FinishingQueue(const DefaultLogger& origin) KZ_DELETED_FUNCTION;
        FinishingQueue& operator=(const DefaultLogger& origin) KZ_DELETED_FUNCTION;

        /// Reference to the resource manager.
        ResourceManager& m_resourceManager;

        /// The load tasks in the finishing queue.
        FinishingQueueContainer m_tasks;
    };

    /// Gets the finishing queue for asynchronous loading tasks. You can use this to control the deployment strategy of the resources.
    /// \return The finishing queue.
    FinishingQueue& getFinishingQueue()
    {
        return m_mainThreadFinishingQueue;
    }

    /// Processes asynchronous loading tasks by deploying a single loaded GPU resource.
    /// This function does not do anything if there are no active asynchronous loading tasks with loaded resources.
    /// Kanzi calls this function once every frame. Call this function periodically to ensure that asynchronous loading tasks are completed.
    /// \return False if there is no asynchronously loaded resources in the deployment queue.
    bool processDeploymentQueueItem();

    /// Tell if deployment queue is empty.
    /// \return True if empty, otherwise False.
    bool hasDeploymentTasks() const;

    /// Callback function type for acquire tasks.
    typedef function<void()> AsyncAcquireFinishedCallback;

    /// Load task for a group of resources.
    /// The task is created from a set of URLs and a callback. When Kanzi loads all URLs, it calls the callback.
    /// \see acquireResourcesAsync, wait
    class AcquireTask
    {
    public:
        /// Gets a resource that has been loaded by this task.
        /// If the loading is not yet finished, or if the given URL has failed to load, returns a null pointer.
        /// \param url The URL of a resource in this load task.
        /// \return The loaded resource, or null if the resource has not been successfully loaded.
        ResourceSharedPtr getLoadedResource(string_view url) const
        {
            LoadedContainer::const_iterator it = loadedResources.find(string(url));
            if (it != loadedResources.end())
            {
                return it->second;
            }
            return ResourceSharedPtr();
        }

        /// Indicates whether the task has been finished and the callback called.
        /// \return If the task has finished, true, otherwise false.
        bool isFinished() const
        {
            return m_finished;
        }

        /// Default constructor.
        AcquireTask() :
            m_finished(false),
            m_loadsDependencies(false)
        {
        }

    private:
        KZ_MOVABLE_BUT_NOT_COPYABLE(AcquireTask)

        /// Container type for resources that are still being loaded.
        typedef unordered_map<LoadTaskSharedPtr, string> LoadingContainer;

        /// Container type for resources that have been loaded.
        typedef unordered_map<string, ResourceSharedPtr> LoadedContainer;

        /// Resources that are still being loaded.
        LoadingContainer loadingResources;

        /// Resources that have been loaded.
        LoadedContainer loadedResources;

        /// Callback that Kanzi calls when all of the resources are loaded.
        AsyncAcquireFinishedCallback callback;

        /// Indicates whether the task has been finished and the callback called.
        bool m_finished;

        /// Indicates whether the task has been created internally to load dependencies.
        bool m_loadsDependencies;

        /// Friend classes.
        friend class ResourceManager;
    };

    /// AcquireTask shared pointer type.
    typedef shared_ptr<AcquireTask> AcquireTaskSharedPtr;

    /// Creates a background task that loads and deploys all resources from a set of URLs. After Kanzi loads
    /// and deploys all resources, the function calls the callback you provide.
    /// \param urls Set of URLs for resources that you want to load.
    /// \param callback Callback function that this function calls when Kanzi loads all specified resources.
    /// \return Handle to the async load task. You can pass the handle to #wait to wait for the completion of the load.
    AcquireTaskSharedPtr acquireResourcesAsync(const UrlContainer& urls, AsyncAcquireFinishedCallback callback);

    /// Blocks the execution until the async acquire task finishes and calls the callback of the task (unless it has been called already).
    /// \param acquireTask Acquire task created by #acquireResourcesAsync.
    void wait(AcquireTask& acquireTask);

    /// Kanzi internally uses this function to reload all GPU resources that have been invalidated by the pause-resume event.
    void deployGPUResources();

    /// Kanzi internally uses this function to set the domain of the resource manager when it creates a resource manager.
    void setDomain(Domain* domain);

    /// Returns the memory manager.
    /// \return The memory manager.
    KzcMemoryManager* getMemoryManager() const;

#ifdef SPANSION
    /// Returns the default image brush.
    /// \return The default image brush.
    BrushSharedPtr getImageBrush();
    /// Returns the default text brush.
    /// \return The default text brush.
    BrushSharedPtr getTextBrush();
#endif

    /// Gets the kzb file information for a file from the given URL.
    /// \param url URL of the binary file.
    /// \return Binary file information, or nullptr if URL does not point to any file.
    /// \deprecated Part of the legacy kzb loading. Use #openFile instead.
    KzuBinaryFileInfo* getBinaryFileInfo(string_view url) const;

    /// Get the kzb file construct corresponding to the given name.
    /// \param hostname Hostname of the kzb file.
    /// \param index Index of the file for the given hostname, typically 0. Can be set to higher than 0 when a single hostname has multiple kzb files.
    /// \return The kzb file, or nullptr if no matching kzb file is found.
    KzbFile* getKzbFile(string_view hostname, size_t index = 0) const;

    /// Kanzi internally uses this function to reload a resource from a kzb file.
    /// \param resource The reloaded resource.
    void reloadFromUrl(Resource* resource);

    /// Type for a smart pointer to a KZB file.
    typedef unique_ptr<KzbFile> KzbFilePtr;

    /// Type for the KZB file container.
    typedef map<string, vector<KzbFilePtr> > KzbFileDictionary;

    /// Returns the iterator to the beginning of loaded KZB files.
    /// \return A const iterator to the beginning of KZB dictionary.
    KzbFileDictionary::const_iterator beginKzbFiles() const
    {
        return m_kzbFiles.begin();
    }
    /// Returns the iterator to the end of loaded KZB files.
    /// \return A const iterator to the end of KZB dictionary.
    KzbFileDictionary::const_iterator endKzbFiles() const
    {
        return m_kzbFiles.end();
    }

    /// Enqueue resource dependencies of a load task for asynchronous loading.
    /// Meant to be called by LoadTask::enqueueDependencies.
    /// When you call this function it informs the main thread about the dependencies of a load task, which then triggers
    /// the asynchronous loading of these dependencies.
    /// \param loadTask The load task requesting the dependencies.
    /// \param urls Container of dependency URLs.
    void enqueueDependencies(LoadTaskSharedPtr loadTask, UrlContainer urls);

#if kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)
    /// Gets resource profiler.
    ///
    /// \return The resource profiler.
    ResourceProfiler& getResourceProfiler()
    {
        return *m_resourceProfiler;
    }
#endif

    /// Alias for a container of resources.
    typedef vector<ResourceSharedPtr> ResourceContainer;

    /// Get a container of all existing resources.
    /// \return A container of shared_ptrs to all existing resources.
    ResourceContainer getAllLoadedResources() const;

private:
    friend class FinishingQueue;
    friend class Resource;
    friend class GPUResource;

    /// Adds a resource to the resource manager. Resources themselves are responsible for adding them, so this function is not public.
    void addResource(Resource* resource);

    /// Removes a resource from the resource manager. Resources themselves are responsible for removing them, so this function is not public.
    void removeResource(Resource* resource);

    /// Notifies the resource manager that a resource loading has been processed by placing the task in the queue for finishing the loading in the main thread.
    void enqueueResourceFinishLoading(LoadTaskSharedPtr task);

    /// Gets the resource loader thread context for the main thread.
    const ResourceLoaderThreadContext* getMainThreadContext() const;

    /// Finishes the load task. If the task has already started in a loader thread, waits until the task is finished.
    void completeLoadTask(LoadTaskSharedPtr loadTask);

    typedef vector<AcquireTaskSharedPtr> AcquireTaskContainer;
    typedef unordered_set<Resource*> PriorityResourceSet;
    typedef map<string, KzuBinaryFileType> ResourceFileExtensionMap; /**< Type of resource file extension map. */

    /// Notifies all acquire tasks about a loaded resource.
    void updateAcquireTasks(LoadTaskSharedPtr finishedLoadTask);

    /// Loads a single resource using the main thread, unless there are active loader threads.
    void ensureLoadQueueProgress();

    /// Cancels all active acquire tasks.
    void cancelAcquireTasks();

    /// Calls the callbacks for all the finished acquire tasks.
    void processFinishedAcquireTasks();

    /// Finishes dependency acquire tasks which have loaded all resources.
    void processFinishedDependencyAcquireTasks();

    /// Creates acquire tasks for resources with dependencies.
    void processNewWaitingLoadTasks();

    /// Updates the status of waiting load tasks.
    void updateWaitingLoadTasks();

    /// Processes the loading part of a load task.
    void processTaskLoad(LoadTaskSharedPtr task, ResourceLoaderThreadContext* threadContext);

    /// Processes the finishing part of a load task.
    void processTaskFinish(LoadTaskSharedPtr task);

    /// Processes all load tasks loaded in a loader thread.
    void processFinishingQueue();

    /// Processes a single load task that has been loaded by a loader thread. Does nothing if the task has not been transferred to the main thread finishing queue.
    /// Called when a resource is acquired directly, but its loading has already been started by another background loading task.
    /// \param loadTask The load task that will be removed from the finishing queue and that will have the finishing part of the load task processed.
    void processFinishingQueueTask(LoadTaskSharedPtr loadTask);

    /// Transfers loaded tasks from loader threads to the main thread. Called typically once per frame by the main thread, but also if any load task
    /// needs to be completed right away.
    void transferFinishingQueue();

    struct LoaderThread;

    /// The loader thread loop function.
    void loaderThreadFunction(LoaderThread* loaderThread);

    /// Stops the loader threads.
    void stopLoaderThreads();

    /// Enqueues a load task to the load queue so that loader threads can start loading it.
    /// \param loadTask The enqueued load task.
    void enqueueResourceForLoading(LoadTaskSharedPtr loadTask);

    /// Helper function for acquireResource and tryAcquireResource.
    kzsException acquireResourceHelper(string_view url, bool async, ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Loads any kind of resource from a binary file.
    /// \deprecated Part of legacy kzb loading.
    void loadResourceFile(const KzuBinaryDirectory* directory, const KzuBinaryFileInfo* file, ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Prunes nullified resources from resource manager.
    void pruneResources();

    /// Protocol handler for loading kzb:// URLs.
    static kzsException kzbProtocolHandler(ResourceManager* resourceManager, string_view, string_view, string_view hostname, unsigned, string_view resourcePath, void*,
                                           ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Protocol handler for loading kzb:// URLs for new kzb format.
    static kzsException newKzbProtocolHandler(ResourceManager* resourceManager, string_view, string_view, string_view hostname, unsigned, string_view resourcePath, void*,
                                              ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Protocol handler for reloading kzb:// URLs.
    static void kzbProtocolReloadFunction(ResourceManager* resourceManager, string_view url, string_view protocol, string_view hostname, unsigned port, string_view path, void* userData, Resource* resource);

    /// Protocol handler for reloading file:// URLs.
    static void fileProtocolReloadFunction(ResourceManager* resourceManager, string_view url, string_view protocol, string_view hostname, unsigned port, string_view path, void* userData, Resource* resource);

    void kzbProtocolReload(string_view hostname, string_view path, Resource* resource);
    void newKzbProtocolReload(string_view resourceURL, Resource* resource);
    void fileProtocolReload(string_view hostname, string_view path, Resource* resource);

    /// Protocol handler for ignoring obj:// URLs.
    static kzsException objProtocolHandler(ResourceManager*, string_view, string_view, string_view, unsigned, string_view, void*,
                                           ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Protocol handler for file:// URLs.
    static kzsException fileProtocolHandler(ResourceManager* resourceManager, string_view url, string_view, string_view hostname, unsigned, string_view path, void* userData,
                                            ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask);

    /// Reads an image from the given binary file info.
    /// \deprecated Part of the legacy kzb loading.
    kzsException readImage(KzuBinaryFileInfo* file, BitmapImageUniquePtr& out_image) const;

    /// Creates and registers the default objects. The default objects are kept alive by the resource manager.
    void registerDefaultObjects();
    /// Releases the default objects.
    void releaseDefaultObjects();
    // Reset all shared pointers that the resource manager has to any resources.
    void releaseAllResources();

    /// Removes all the files corresponding to the given hostname from the list of kzb files.
    /// If file does not exist, silently does nothing.
    /// This function is private since it's only intended to be called during patching.
    /// \param hostname Hostname to clear.
    void removeKzbFile(string_view hostname);

    // Declare #PreviewPatcher as friend so it can use #removeKzbFile.
    friend class PreviewPatcher;

    ResourceManager(const ResourceManager&) KZ_DELETED_FUNCTION;
    ResourceManager& operator=(const ResourceManager&) KZ_DELETED_FUNCTION;

    /// Protocol handler structure.
    struct ProtocolHandlerObject
    {
        ProtocolHandlerObject() :
            handler(),
            reload(),
            userData()
        {
        }

        explicit ProtocolHandlerObject(ProtocolHandler handler, ProtocolResourceReloadFunction reload, void* userData) :
            handler(handler),
            reload(reload),
            userData(userData)
        {
        }

        /// Callback function for loading the resource.
        ProtocolHandler handler;

        /// Resource reload function
        ProtocolResourceReloadFunction reload;

        /// userData object passed to callback function.
        void* userData;
    };
    typedef unordered_map<string, ProtocolHandlerObject> ProtocolMap;

    struct LookupResultPointer
    {
        ResourceWeakPtr weakResource;
        ResourceSharedPtr strongResource;
    };
    typedef variant<LookupResultPointer, LoadTaskSharedPtr> LookupResult;
    enum LookupResultVariantIndices
    {
        PointerVariantIndex,
        LoadTaskVariantIndex
    };
    typedef unordered_map<string, LookupResult> LookupMap;

    static bool canBePurged(const LookupMap::value_type& pair);

    /// The memory manager.
    KzcMemoryManager* m_memoryManager;

#ifdef SPANSION
    /// Default image brush object. Kept alive by the resource manager.
    BrushSharedPtr m_imageBrush;

    /// Default text brush object. Kept alive by the resource manager.
    BrushSharedPtr m_textBrush;
#endif

    /// The domain.
    Domain* m_domain;

    /// Legacy binary directories.
    /// \deprecated Part of the legacy kzb loading.
    DirectoryContainer m_directories;

    /// Map of registered protocol handlers.
    ProtocolMap m_protocolHandlers;

    /// The main resources lookup map. Maps resource URL to a resource or active load task.
    LookupMap m_resourceLookup;

    /// Flag to control if the resource pointer will be set to nullptr on removal or removed.
    bool m_nullifyResourcesOnRemove;

    /// List of all resources. Resources register themselves in their constructor.
    vector<Resource*> m_allResources;

    /// Implementation class.
    struct Impl;

    /// Implementation instance.
    unique_ptr<Impl> m_impl;

    /// Flag that overrides the loading strategy of resources. If set to true, then GPU resources are always kept in CPU memory after deployment.
    bool m_keepGPUResourcesInCPUMemory;

    /// Memory strategy for new resources.
    MemoryStrategy m_defaultMemoryStrategy;

    /// Container for active async load tasks.
    AcquireTaskContainer m_acquireTasks;

    /// Resource loader thread context for the main thread.
    ResourceLoaderThreadContext m_mainThreadContext;

    /// Resources that have been loaded by a loader thread and are waiting to be finished by the main thread.
    FinishingQueue m_mainThreadFinishingQueue;

    /// Default null brush object. Kept alive by the resource manager.
    BrushSharedPtr m_nullBrush;

    /// Kzb files.
    KzbFileDictionary m_kzbFiles;

#if kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)
    /// The resource profiler.
    ResourceProfilerUniquePtr m_resourceProfiler;
#endif
};
}

#endif
