// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COLLECT_RESOURCE_URLS_HPP
#define KZ_COLLECT_RESOURCE_URLS_HPP

#include <kanzi/core.ui/resource/resource_manager.hpp>

namespace kanzi
{

class ResourceDictionary;
class PrefabTemplateNode;
class PrefabTemplate;

/// Collects URLs from all resource properties that are used by the nodes in a prefab template.
/// If the nodes contain nested prefab templates (i.e. prefab placeholders) or node components, collects URLs also from those.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab and node tree, and then collects them too.
/// \param prefabTemplate The prefab template instance.
/// \param node Node where the template will be instantiated.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(const PrefabTemplate& prefabTemplate, const Node& node, ResourceManager::UrlContainer& urls);

/// Looks up resource properties of type StateManager in the nodes of a prefab template.
/// Acquires them, and then collects URLs from all their resource properties.
/// Typically called after acquiring the collected urls of a prefab template, for a deeper collection.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab and node tree, and then collects them too.
/// \param prefabTemplate The prefab template instance.
/// \param node Node where the template will be instantiated.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrlsFromStateManagers(const PrefabTemplate& prefabTemplate, const Node& node, ResourceManager::UrlContainer& urls);


/// Collects URLs from all resource properties that are used by the nodes in a prefab template.
/// If the nodes contain nested prefab templates (i.e. prefab placeholders) or node components, collects URLs also from those.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab tree, and then collects them too.
/// \param prefabTemplate The prefab template.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(const PrefabTemplate& prefabTemplate, ResourceManager::UrlContainer& urls);

/// Collects URLs from all resource properties that are used by a prefab template node and its children.
/// If the nodes contain nested prefab templates (i.e. prefab placeholders) or node components, collects URLs also from those.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab tree, and then collects them too.
/// \param prefabTemplateNode The prefab template node.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(const PrefabTemplateNode& prefabTemplateNode, ResourceManager::UrlContainer& urls);

/// Looks up resource properties of type StateManager in the nodes of a prefab template.
/// Acquires them, and then collects URLs from all their resource properties.
/// Typically called after acquiring the collected urls of a prefab template, for a deeper collection.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab tree, and then collects them too.
/// \param prefabTemplate The prefab template instance.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrlsFromStateManagers(const PrefabTemplate& prefabTemplate, ResourceManager::UrlContainer& urls);


/// Collects the URLs from a resource dictionary.
/// If the resource dictionary has nested dictionary, collects URLs also from those.
/// \param resourceDictionary The resource dictionary.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(const ResourceDictionary& resourceDictionary, ResourceManager::UrlContainer& urls);

/// Collect resource urls from a named file.
/// \param resourceManager Resource manager to collect from.
/// \param hostname KZB hostname part of the URL.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(ResourceManager* resourceManager, string_view hostname, ResourceManager::UrlContainer& urls);


/// Collects URLs from all resource properties that are used by the nodes in a prefab template.
/// If the nodes contain nested prefab templates (i.e. prefab placeholders) or node components, collects URLs also from those.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab and node tree, and then collects them too.
/// \param resourceManager The resource manager.
/// \param prefabTemplateUrl The URL of a prefab template. For example "kzb://asynchronous_loading/Prefabs/Prefab that uses many textures".
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrlsFromPrefabTemplateUrl(ResourceManager* resourceManager, string_view prefabTemplateUrl, const Node& node, ResourceManager::UrlContainer& urls);

/// Collects URLs from all resource properties that are used by the nodes in a prefab template.
/// If the nodes contain nested prefab templates (i.e. prefab placeholders) or node components, collects URLs also from those.
/// For resources set with resource IDs, resolves their URLs by looking up in the prefab tree, and then collects them too.
/// \param resourceManager The resource manager.
/// \param prefabTemplateUrl The URL of a prefab template. For example "kzb://asynchronous_loading/Prefabs/Prefab that uses many textures".
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrlsFromPrefabTemplateUrl(ResourceManager* resourceManager, string_view prefabTemplateUrl, ResourceManager::UrlContainer& urls);


/// Collects the URLs of resources from the resource dictionaries of the prefab templates you specify.
/// \param resourceManager The resource manager.
/// \param prefabTemplateNodeUrls Semicolon separated list of urls to prefab template nodes.
///                               For example "kzb://preloading_test/Prefabs/Empty Node 2D/Empty Node 2D;kzb://preloading_text/Prefabs/Stack Layout 2D/Stack Layout 2D".
/// \param urls A container where the collected URLs will be added.
/// \deprecated Part of legacy KZB loading. The new KZB format does not store prefab template nodes separately.
KANZI_API void collectResourceUrlsFromPrefabTemplateNodeResourceDictionaryUrls(ResourceManager* resourceManager, string_view prefabTemplateNodeUrls, ResourceManager::UrlContainer& urls);


/// Collects the URLs of all resources in the binary directory you specify.
/// \param resourceManager The resource manager.
/// \param binaryDirectory The binary directory of the .kzb that you want to preload.
/// \param urls A container where the collected URLs will be added.
/// \deprecated Part of legacy KZB loading.
KANZI_API void collectResourceUrls(ResourceManager* resourceManager, KzuBinaryDirectory* binaryDirectory, ResourceManager::UrlContainer& urls);

/// Collects the URLs of all resources from all the binary directories that have been added to the resource manager. This includes resources you did not include in the
/// resource dictionaries of specific nodes.
/// \param resourceManager The resource manager.
/// \param urls A container where the collected URLs will be added.
KANZI_API void collectResourceUrls(ResourceManager* resourceManager, ResourceManager::UrlContainer& urls);
}

#endif
