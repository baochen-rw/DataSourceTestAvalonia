// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_DICTIONARY_HPP
#define KZ_RESOURCE_DICTIONARY_HPP

#include <kanzi/core.ui/resource/resource_manager.hpp>

namespace kanzi
{

class ResourceDictionary;

/// Resource dictionary shared pointer.
typedef shared_ptr<ResourceDictionary> ResourceDictionarySharedPtr;

/// A resource dictionary is a container that maps resource IDs to resources. A node can
/// refer to resources by setting resource IDs to resource ID properties. You can set a resource
/// dictionary to the node or to any of its parent nodes to define which resources the node will use.
/// You can use resource dictionary to group similar resources to logical entities like themes or locales,
/// and change a resource dictionary of a node to change multiple resources at the same time.
///
/// You can use Node::acquireResource to get the resource from the resource dictionary of a node
/// or from the resource dictionaries of its parent nodes.
///
/// A resource dictionary can map resource IDs to resources in these ways:
/// 1) Resource ID can map directly to a resource pointer.
/// 2) Resource ID can map indirectly to a resource with a resource URL.
/// Use #acquire and #tryAcquire functions to get a mapped resource regardless of the way how a
/// resource ID is mapped to a resource.
///
/// You can store nested resource dictionaries in a resource dictionary. When you are getting a resource
/// from a resource dictionary and the resource dictionary cannot find the resource ID you specify,
/// the resource dictionary looks for the resource ID recursively in the nested resource dictionaries.
///
/// In a resource dictionary you can store resources without mapping a resource ID to them.
/// In Kanzi Engine such resources are called anonymous resources. You can get anonymous resources
/// with #beginAnonymousResources and #endAnonymousResources.
///
/// Examples
/// ----
///
/// To create a resource dictionary:
/// \snippet test_resource_dictionary.cpp Create
///
/// To add content to a resource dictionary:
/// \snippet test_resource_dictionary.cpp Add content
///
/// To get resources from a resource dictionary:
/// \snippet test_resource_dictionary.cpp Query content
///
/// To change the resource dictionary of a node:
/// \snippet test_resource_dictionary.cpp Change dictionary
///
/// To extend the existing resource dictionary of a node:
/// \snippet test_resource_dictionary.cpp Extend dictionary
class KANZI_API ResourceDictionary : public Resource
{
public:

    /// The type used for container of nested resource dictionaries.
    typedef vector<ResourceDictionarySharedPtr> DictionaryContainer;
    /// The type used for iterators of nested resource dictionary containers.
    typedef DictionaryContainer::const_iterator DictionaryConstIterator;
    /// The type used for reverse iterators of nested resource dictionary containers.
    typedef DictionaryContainer::const_reverse_iterator DictionaryConstReverseIterator;

    /// The type used for mapping resource IDs to URLs.
    typedef unordered_map<ResourceID, string> URLMap;
    /// The type used for iterators of the mapping of resource IDs to URLs.
    typedef URLMap::const_iterator URLConstIterator;

    /// The type used for mapping resource IDs to resources.
    typedef unordered_map<ResourceID, ResourceSharedPtr> ResourceMap;
    /// The type used for iterators of the mapping of resource IDs to resources.
    typedef ResourceMap::const_iterator ResourceConstIterator;

    /// The type used for the container of anonymous resources.
    typedef vector<ResourceSharedPtr> AnonymousResourceContainer;
    /// The type used for iterators of the anonymous resource container.
    typedef AnonymousResourceContainer::const_iterator AnonymousResourceConstIterator;


    KZ_METACLASS_BEGIN(ResourceDictionary, Resource, "Kanzi.ResourceDictionary")
    KZ_METACLASS_END()


    /// Creates a resource dictionary.
    /// \param domain The domain to which the resource dictionary belongs.
    /// \param name The name of the resource dictionary.
    /// \return The pointer to the resource dictionary.
    static ResourceDictionarySharedPtr create(Domain* domain, string_view name);


    /// Adds a resource ID to a resource URL mapping to the resource dictionary.
    /// \param key The resource id.
    /// \param url The URL pointing to the resource.
    void add(const ResourceID& key, string_view url);

    /// Adds a resource ID to a resource pointer mapping to the resource dictionary.
    /// \param key The resource id.
    /// \param resource The resource pointer.
    void add(const ResourceID& key, ResourceSharedPtr resource);

    /// Removes a resource ID mapping from the resource dictionary.
    /// \param key The resource ID you want to remove.
    void remove(const ResourceID& key);

    /// Tells whether the resource dictionary contains a mapping for the resource ID you pass to the function.
    /// \param key The resource ID for which you want to check whether there is a mapping in the resource dictionary.
    /// \return True if the resource dictionary or a nested resource dictionary contains a mapping for the resource ID you passed to the function.
    bool contains(const ResourceID& key) const;


    /// Resolves the mapping from the resource ID you pass to the function to the URL of the resource. This function ignores the direct resource ID to resource mappings.
    /// \param key The resource ID of the resource for which you want to get the URL.
    /// \return The resource URL if the resource dictionary or a nested resource dictionary contains a resource ID you passed. Otherwise returns nullopt.
    optional<string> find(const ResourceID& key) const;

    /// Implementation for find().
    virtual optional<string> findOverride(const ResourceID& key) const;

    /// Returns an iterator pointing to the first element of the URL mappings container.
    /// \return An iterator pointing to the first element of the container.
    URLConstIterator beginUrls() const;

    /// Returns an iterator pointing to the element following the last element of the URL mappings container.
    /// \return An iterator pointing to the element following the last element of the URL mappings container.
    URLConstIterator endUrls() const;


    /// Returns an iterator pointing to the first element of the anonymous resources container.
    /// \return An iterator pointing to the first element of the anonymous resources container.
    AnonymousResourceConstIterator beginAnonymousResources() const;

    /// Returns an iterator pointing to the element following the last element of the anonymous resources container.
    /// \return An iterator pointing to the element following the last element of the anonymous resources container.
    AnonymousResourceConstIterator endAnonymousResources() const;

    /// Adds an anonymous resource to the resource dictionary.
    /// \param resource The anonymous resource you want to add to the resource dictionary.
    void addAnonymousResource(ResourceSharedPtr resource);

    /// Removes an anonymous resource from the resource dictionary.
    /// \param resource The anonymous resource you want to remove from the resource dictionary. If the resource does not exist in the resource dictionary, the function does not do anything.
    void removeAnonymousResource(const Resource& resource);


    /// Adds a nested resource dictionary to the resource dictionary. Since only a pointer to the nested resource dictionary is stored, the same resource dictionary can be
    /// added as a nested resource dictionary to multiple dictionaries. Note that it is forbidden to form cycles with the nested resource dictionaries.
    /// \param resourceDictionary The nested resource dictionary you want to add to the resource dictionary.
    void add(ResourceDictionarySharedPtr resourceDictionary);

    /// Gets the number of nested resource dictionaries in the resource dictionary.
    /// \return The number of nested resource dictionaries in the resource dictionary.
    size_t getDictionaryCount() const;

    /// Removes a nested resource dictionary from the resource dictionary.
    /// \param index The index of the nested resource dictionary you want to remove.
    void removeDictionary(size_t index);

    /// Returns a reverse iterator to the first element of the reversed nested resource dictionary container.
    /// It corresponds to the last element of the non-reversed container.
    /// \return A reverse iterator to the first element of the reversed nested resource dictionary container.
    DictionaryConstReverseIterator crbeginDictionaries() const;

    /// Returns a reverse iterator to the element following the last element of the reversed nested resource dictionary container.
    /// It corresponds to the element preceding the first element of the non-reversed container.
    /// \return A reverse iterator to the element following the last element of the reversed nested resource dictionary container.
    DictionaryConstReverseIterator crendDictionaries() const;

    /// Searches for a nested dictionary with the specified name and returns a pointer to it.
    /// \param name The name of the dictionary to find.
    /// \return A child dictionary with the specified name, null otherwise.
    ResourceDictionarySharedPtr findDictionary(string_view name) const;

    /// Find explicitly stored resource pointer from the dictionary.
    /// Does not try to acquire from resource manager, use acquire() if necessary.
    ResourceSharedPtr findStoredResource(const ResourceID& key) const;

    /// Gets from the resource dictionary the resource with the resource ID you pass to the function.
    /// Any resource URL mappings are forwarded to ResourceManager::acquireResource.
    /// Classes that derive from ResourceDictionary can override the behavior of acquire by implementing acquireOverride.
    ///
    /// \param key The resource ID of the resource you want to get.
    /// \returns The resource to which the resource ID is mapped.
    /// - If the resource ID is mapped to a resource pointer, the function returns the resource pointer.
    /// - If the resource ID is mapped to a resource URL, the function uses the URL to query the resource from ResourceManager::acquireResource.
    /// - If the resource dictionary has nested resource dictionaries, the function forwards the query to the nested dictionaries:
    ///   the last nested resource dictionary is searched first, and the first nested resource dictionary is searched last.
    /// - If the resource ID is not mapped to anything in this resource dictionary or any of the nested dictionaries, the function returns nullptr.
    ResourceSharedPtr acquire(const ResourceID& key) const;

    /// Gets from the resource dictionary the resource with the resource ID you pass to the function and casts the resource to the type you specify.
    /// \see #acquire
    template <typename Type>
    shared_ptr<Type> acquire(const ResourceID& key) const
    {
        return dynamic_pointer_cast<Type>(acquire(key));
    }

    /// Gets from the resource dictionary the resource with the resource ID you pass to the function.
    /// Any resource URL mappings are forwarded to ResourceManager::tryAcquireResource.
    /// Classes that derive from ResourceDictionary can override the behavior of tryAcquire by implementing tryAcquireOverride.
    ///
    /// \param key The resource ID of the resource you want to get.
    /// \returns The resource to which the resource ID is mapped.
    /// - If the resource ID is mapped to a resource pointer, the function returns the resource pointer.
    /// - If the resource ID is mapped to a resource URL, the function uses the URL to query the resource from ResourceManager::tryAcquireResource.
    /// - If the resource dictionary has nested resource dictionaries, the function forwards the query to the nested dictionaries:
    ///   the last nested resource dictionary is searched first, and the first nested resource dictionary is searched last.
    /// - If the resource ID is not mapped to anything in this resource dictionary or any of the nested dictionaries, the function returns nullptr.
    ResourceSharedPtr tryAcquire(const ResourceID& key) const;

    /// Gets from the resource dictionary the resource with the resource ID you pass to the function and casts the resource to the type you specify.
    /// \see #tryAcquire
    template <typename Type>
    shared_ptr<Type> tryAcquire(const ResourceID& key) const
    {
        return dynamic_pointer_cast<Type>(tryAcquire(key));
    }

    /// Acquire resource asynchronously.
    /// If no resource URL mapping is found, an asynchronous task is not launched.
    /// Even if no asynchronous task is launched, the callback is not executed until the next time when callbacks would be executed normally.
    /// \param key The resource ID of the resource you want to get.
    /// \param func Callback to execute when loading is complete.
    /// \return Async task launched.
    ResourceManager::AcquireTaskSharedPtr acquireAsync(const ResourceID& key, ResourceManager::AsyncAcquireFinishedCallback func) const;

    /// Modifies this resource dictionary by copying into this resource dictionary the contents of the resource dictionary you pass to the function.
    ///
    /// Adds resource ID mappings, pointers to nested resource directories, and anonymous resources from the given resource directory to this resource directory.
    /// If there are duplicate values for the resource id mappings, prefers the values in the resource directory passed to the function.
    /// \param preferredDictionary The resource dictionary to which you want to merge this resource dictionary.
    void merge(const ResourceDictionary& preferredDictionary);


    /// Duplicates a resource dictionary. When you duplicate a resource dictionary which contains nested resource dictionaries,
    /// copies the pointers to the nested resource dictionaries but not the contents of the nested resource dictionaries (i.e. creates a shallow copy).
    /// Class that derive from ResourceDictionary must override the cloning implementation in #cloneOverride.
    /// \return The pointer to the duplicated resource dictionary.
    ResourceDictionarySharedPtr clone() const;


    /// Loads a resource dictionary from input stream. Used internally by Kanzi Engine.
    /// \param inputStream Input stream where the resource dictionary is loaded from.
    /// \param fileInfo The descriptor for the file where the resource dictionary is loaded from.
    void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* fileInfo);

    /// Loads a resource dictionary from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Resource Dictionary file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static ResourceDictionarySharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

protected:

    /// Loads a resource dictionary from a file. Used internally by Kanzi Engine.
    ///
    /// \param kzbFile KZB file where to load from.
    /// \param file Resource Dictionary file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    void loadFromKZB(KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /// Constructor.
    /// \param domain The domain to which the resource dictionary belongs.
    /// \param name The name of the resource dictionary.
    explicit ResourceDictionary(Domain* domain, string_view name);

    /// Implements resource lookup described in #acquire.
    virtual ResourceSharedPtr acquireOverride(const ResourceID& key) const;
    /// Implements resource lookup described in #tryAcquire.
    virtual ResourceSharedPtr tryAcquireOverride(const ResourceID& key) const;
    /// Implements asynchronous resource acquire described in #acquireResourceAsync.
    virtual ResourceManager::AcquireTaskSharedPtr acquireAsyncOverride(const ResourceID& key, ResourceManager::AsyncAcquireFinishedCallback func) const;
    /// Implements cloning of the object in #clone.
    virtual ResourceDictionarySharedPtr cloneOverride() const;

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

private:

    // Suppress warning about hidden overloaded virtual function.
    using Resource::loadFromKZB;

    /// Nested resource dictionaries.
    DictionaryContainer m_dictionaries;

    /// Mapping from resource IDs to resource URLs.
    URLMap m_urlMap;

    /// Mapping from resource IDs to resource pointers.
    ResourceMap m_resourceMap;

    /// Anonymous resources.
    AnonymousResourceContainer m_anonymousResources;
};

}


#endif
