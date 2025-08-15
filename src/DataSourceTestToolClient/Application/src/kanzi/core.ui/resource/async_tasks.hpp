// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ASYNC_TASKS_HPP
#define KZ_ASYNC_TASKS_HPP

#include "resource_manager.hpp"

namespace kanzi
{

/// Acquires prefab and required nested resources recursively.
/// Callback is executed when all required resources have been acquired.
/// \param node Node where prefab will be instantiated, and the node to resolve from.
/// \param prefabResourceId Resource ID of the prefab to load.
/// \param callback Callback to execute upon completion.
KANZI_API void loadPrefabAsync(const Node& node, ResourceID prefabResourceId, ResourceManager::AsyncAcquireFinishedCallback callback);
}

#endif
