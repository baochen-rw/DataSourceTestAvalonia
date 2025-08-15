// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_LOADER_FACTORY_HPP
#define KZ_RESOURCE_LOADER_FACTORY_HPP

#include <kanzi/core.ui/kzb/kzb_file.hpp>
#include <kanzi/core.ui/kzb/kzb_memory_parser.hpp>
#include <kanzi/core.ui/resource/resource_dictionary.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core/file/read_only_memory_file.hpp>

namespace kanzi
{

/// Factory for resource loader tasks.
///
/// Tasks for resource loading are registered to the factory, that creates them as needed.
///
/// Existing resources may use default tasks and potentially override #loadFromKZB() method.
/// New types of resources with new base classes require a new load task.
class ResourceLoaderFactory
{
private:

    template <typename TResource>
    class ResourceLoadTask : public ResourceManager::LoadTask
    {
    public:

        static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view resourceName, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file)
        {
            return make_shared< ResourceLoadTask<TResource> >(resourceName, kzbFile, kanzi::move(file));
        }

        explicit ResourceLoadTask(string_view resourceName, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file) :
            ResourceManager::LoadTask(ResourceManager::LoadTask::FinishOnly),
            m_name(resourceName),
            m_kzbFile(kzbFile),
            m_file(kanzi::move(file))
        {
        }

        virtual void loadFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
        {
            kzAssertUnreachableMessage(("ResourceLoadTask::loadFunction() should not get called due to task type FinishOnly"));
        }

        virtual void finishFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
        {
            // Load resource in main thread for now.
            KzbMemoryParser parser(m_kzbFile, m_file->map(), m_file->size());

            // Load KeepAlive flag.
            const bool keepAlive = parser.parseBool();

            // Load resource.
            m_result = TResource::loadFromKZB(m_kzbFile->getDomain(), m_name, *m_kzbFile, *m_file, parser);

            // Set KeepAlive flag.
            m_result->setKeepAlive(keepAlive);
        }

        virtual ResourceSharedPtr getResult() KZ_OVERRIDE
        {
            return m_result;
        }

    private:

        string m_name;

        KzbFile* m_kzbFile;
        unique_ptr<ReadOnlyMemoryFile> m_file;

        shared_ptr<TResource> m_result;
    };

public:

    typedef ResourceSharedPtr(*LoaderCallback)(Domain*, string_view, KzbFile*, unique_ptr<ReadOnlyMemoryFile>);
    typedef map<const Metaclass*, LoaderCallback> LoaderCallbackDictionary;

    typedef ResourceManager::LoadTaskSharedPtr(*LoadTaskFactoryFunction)(string_view, KzbFile*, unique_ptr<ReadOnlyMemoryFile>);
    typedef map<const Metaclass*, LoadTaskFactoryFunction> LoadTaskFactoryDictionary;

    /// Constructor.
    explicit ResourceLoaderFactory();

    /// Get loader callback for given metaclass.
    /// Returns empty function pointer (0) if metaclass has not been registered.
    /// \param metaclass Metaclass to get callback for.
    /// \return Loader callback.
    LoaderCallback tryGetLoaderCallback(const Metaclass* metaclass) const
    {
        LoaderCallbackDictionary::const_iterator iter = m_loaderCallbackDictionary.find(metaclass);
        if (iter == cend(m_loaderCallbackDictionary))
        {
            return 0;
        }
        return (*iter).second;
    }

    /// Get loader callback for given metaclass.
    /// Throws an error if metaclass has not been registered.
    /// \param metaclass Metaclass to get callback for.
    /// \return Loader callback.
    LoaderCallback getLoaderCallback(const Metaclass* metaclass) const
    {
        LoaderCallback callback = tryGetLoaderCallback(metaclass);
        if (!callback)
        {
            kzThrowException(runtime_error(string("Could not find loader callback for metaclass '") + metaclass->getName().c_str() + "'"));
        }
        return callback;
    }

    /// Check if loader callback has been registered.
    /// \param metaclass Metaclass to check.
    /// \return True if registered, false if not.
    bool hasLoaderCallback(const Metaclass* metaclass) const
    {
        return (m_loaderCallbackDictionary.find(metaclass) != cend(m_loaderCallbackDictionary));
    }

    /// Register loader callback for a metaclass.
    /// \param metaclass Metaclass to register for.
    /// \param callback Loader callback.
    void registerLoaderCallback(const Metaclass* metaclass, LoaderCallback callback)
    {
        m_loaderCallbackDictionary[metaclass] = callback;
    }

    /// Shorthand for registering loader callback for given type.
    template <typename T> void registerLoaderCallback()
    {
        registerLoaderCallback(T::getStaticMetaclass(), T::loaderCallback);
    }

    /// Get load task factory function for given metaclass.
    /// Returns empty function pointer (0) if metaclass has not been registered.
    /// \param Metaclass to get load task factory function for.
    /// \return Load task factory function.
    LoadTaskFactoryFunction tryGetLoadTaskFactoryFunction(const Metaclass* metaclass) const
    {
        LoadTaskFactoryDictionary::const_iterator iter = m_loadTaskFactoryDictionary.find(metaclass);
        if (iter == cend(m_loadTaskFactoryDictionary))
        {
            return 0;
        }
        return (*iter).second;
    }

    /// Get load task factory function for given metaclass.
    /// Throws an error if metaclass has not been registered.
    /// \param Metaclass to get load task factory function for.
    /// \return Load task factory function.
    LoadTaskFactoryFunction getLoadTaskFactoryFunction(const Metaclass* metaclass) const
    {
        LoadTaskFactoryFunction func = tryGetLoadTaskFactoryFunction(metaclass);
        if (!func)
        {
            kzThrowException(runtime_error(string("Could not find loader task factory function for metaclass '") + metaclass->getName().c_str() + "'"));
        }
        return func;
    }

    /// Check if load task factory function has been registered.
    /// \param metaclass Metaclass to check.
    /// \return True if registered, false if not.
    bool hasLoadTaskFactoryFunction(const Metaclass* metaclass) const
    {
        return (m_loadTaskFactoryDictionary.find(metaclass) != cend(m_loadTaskFactoryDictionary));
    }

    /// Register load task factory function for given metaclass.
    /// \param metaclass Metaclass to register for.
    /// \param func Load task factory function.
    void registerLoadTaskFactoryFunction(const Metaclass* metaclass, LoadTaskFactoryFunction func)
    {
        m_loadTaskFactoryDictionary[metaclass] = func;
    }

    /// Shorthand for registering a generic load task factory function.
    template <typename T> void registerLoadTask()
    {
        registerLoadTaskFactoryFunction(T::getStaticMetaclass(), &(T::createLoadTask));
    }

    /// Shorthand for registering load task factory function for a resource.
    template <typename T> void registerResourceLoadTask()
    {
        registerLoadTaskFactoryFunction(T::getStaticMetaclass(), &(ResourceLoadTask<T>::createLoadTask));
    }

private:

    /// Dictionary for loader callbacks.
    LoaderCallbackDictionary m_loaderCallbackDictionary;
    /// Dictionary for load tasks.
    LoadTaskFactoryDictionary m_loadTaskFactoryDictionary;
};

}

#endif // KZ_RESOURCE_LOADER_FACTORY_HPP