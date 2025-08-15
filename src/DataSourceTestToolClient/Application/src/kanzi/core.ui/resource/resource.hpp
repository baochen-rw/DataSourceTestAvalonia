// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_RESOURCE_H
#define KZU_RESOURCE_H

#include <kanzi/core.ui/coreui_api.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/error/legacy_error.hpp>
#include <kanzi/core/profiling/profiling.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

struct KzcMemoryManager;
struct KzuBinaryDirectory;
struct KzcInputStream;
struct KzuBinaryFileInfo;

namespace kanzi
{

// Forward declarations.
class Domain;
class KzbFile;
class KzbMemoryParser;
class ReadOnlyMemoryFile;
class Resource;
class ResourceManager;
typedef weak_ptr<Resource> ResourceWeakPtr;
typedef shared_ptr<Resource> ResourceSharedPtr;


/// Resource loader thread local data.
struct ResourceLoaderThreadContext
{
    /// Constructor.
    /// \param name Name of the loader thread.
    explicit ResourceLoaderThreadContext(string_view name);

    /// Returns the name of thread that is doing the loading.
    /// \return The name of the active thread.
    string_view getThreadName() const
    {
        return m_name;
    }

private:
    /// Name of the thread.
    string m_name;
};
}

typedef kanzi::ResourceLoaderThreadContext KzuResourceLoaderThreadContext;

/** Resource loading state. */
enum KzuResourceLoadState
{
    KZU_RESOURCE_LOAD_STATE_NOT_LOADED, /**< The resource has not yet been loaded. */
    KZU_RESOURCE_LOAD_STATE_LOADED      /**< The resource has been loaded. */
};

/** Resource loading strategy specifies when the resource is loaded and unloaded. */
enum KzuResourceLoadingStrategy
{
    /**
    * When using the default strategy the engine loads the resource before it is needed.
    * The loading strategy depends on the platform and Kanzi application,
    * but the engine optimizes the loading strategy.
    */
    KZU_RESOURCE_LOADING_STRATEGY_DEFAULT,

    /**
    * When using the manual loading strategy you must load and unload the resource
    * manually by calling the \ref kzuResourceLoad and \ref kzuResourceUnload functions.
    * This is the only loading strategy that you can control completely.
    */
    KZU_RESOURCE_LOADING_STRATEGY_MANUAL,

    /**
    * When using the optimize speed strategy the engine keeps the resource in RAM.
    * When the application needs the resource, the engine can deploy the resource
    * from RAM to GPU as fast as possible. The engine releases the resource from RAM
    * only when the resource is not accessible anymore.
    * This strategy guarantees that the engine does not unload the resource during runtime. */
    KZU_RESOURCE_LOADING_STRATEGY_OPTIMIZE_SPEED,

    /**
    * When using the optimize memory loading strategy the engine unloads the resource as soon as possible.
    * The engine releases the GPU resources from RAM after deploying the resources.
    */
    KZU_RESOURCE_LOADING_STRATEGY_OPTIMIZE_MEMORY,
};


namespace kanzi
{

/**
 * Represents the base class for all resources.
 * This base class contains information related to the type of the resource and the
 * loading status of the resource data. The actual resource data is specific to the sub-classes.
 */
class KANZI_API Resource : public Object
{
    friend class ResourceManager;

public:
    KzcMemoryManager* getMemoryManager() const;

    Resource(Domain* domain, string_view name);

    virtual ~Resource();

    /**
    * Function for loading the resource from .KZB. This function is called when loading the data from .KZB file.
    * Implementations should call super class loadFromKZB before reading anything else from inputStream.
    * This function is called from arbitrary loading threads. The parameter threadContext contains thread safe memory
    * manager and a thread specific Property manager which can be locked with the threadLock in the threadContext.
    * This function may not access resource manager or the UIDomain due to race conditions.
    */
    virtual void loadFromKZB(
        const ResourceLoaderThreadContext* threadContext,
        KzcInputStream* inputStream,
        const KzuBinaryFileInfo* file);

    /// Unload function for resource. Releases all CPU memory taken by the resource except the resource loader.
    virtual void unloadOverride();

    /** Function for getting the memory usage of a resource. */
    virtual unsigned int getCPUMemoryUsage() const;

    /// Set the binary directory and path of the resource.
    /// Used for old KZB loading path only.
    /// Will construct url from binary directory and path.
    void setKZB(const KzuBinaryDirectory* binaryDirectory, string_view path);

    /// Gets the resource name.
    const string& getName() const
    {
        return m_name;
    }

    /// Gets the resource URL.
    /// Note that the URL is not necessarily in URL form if resource has been just created.
    /// \return URL string.
    const string& getUrl() const
    {
        return m_url;
    }
    /// Sets the resource URL.
    /// \param url New URL.
    void setUrl(string_view url);

    void setNotLoaded()
    {
        m_loadState = KZU_RESOURCE_LOAD_STATE_NOT_LOADED;
    }

    bool isFromKZB() const
    {
        return m_binaryDirectory != 0;
    }

    void reload();
    void reloadFromKzb(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);
    void reloadFromKzb(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);
    void reloadFromFile(string_view filePath);

    void load();
    void unload();
    bool isLoaded() const;


    /** Private function for kzuResourceLoad() with specified thread context. */
    void kzuResourceLoad_private(const ResourceLoaderThreadContext* threadContext);

    /** Private function for finishing the loading of the resource. */
    void kzuResourceFinishLoading_private(const ResourceLoaderThreadContext* threadContext);

    /// Tells if the resource has keep alive flag set. Resource manager keeps resources with keep alive flag alive even if ResourceManager::purge() is called.
    /// \return True if the flag is set.
    bool isKeepAlive() const;

    /// Sets the keep alive flag. Can be set only before the resource is registered to the resource manager. Normally set by loadFromKZB.
    /// \param keepAlive Value for the keep alive flag.
    void setKeepAlive(bool keepAlive);

protected:
    virtual void reloadOverride();
    virtual void reloadFromKzbOverride(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);
    virtual void reloadFromKzbOverride(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);
    virtual void reloadFromFileOverride(string_view filePath);
    virtual unsigned int getCPUMemoryUsageOverride() const;

private:
    /// Binary directory where the the .KZB file can be loaded from.
    const KzuBinaryDirectory* m_binaryDirectory;

    /// URL where resource was loaded from.
    string m_url;
    /// Path of the resource in .KZB file.
    /// Points to a substring of #m_url.
    string_view m_path;

    /// Name of the resource.
    string m_name;

    /// Has the resource been loaded yet.
    KzuResourceLoadState m_loadState;

    /// Should the resource manager keep the resource alive even when the resource is unreferenced.
    bool m_keepAlive;
};

}


#endif
