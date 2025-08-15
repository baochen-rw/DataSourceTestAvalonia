// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_RUNTIME_ASSETS_HPP
#define KANZI_RUNTIME_ASSETS_HPP

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

/// Prefix for runtime asset binary.
#define KZ_RUNTIME_ASSETS_URL_PREFIX "kzb://runtimeassets/"

struct KzuBinaryDirectory;
struct KzcMemoryManager;

namespace kanzi
{

class Domain;


/// Gets size of runtime asset data.
/// \return Data size in bytes.
KANZI_API size_t getRuntimeAssetDataSize();

/// Gets runtime asset data.
/// \return Pointer to runtime asset data.
KANZI_API const byte* getRuntimeAssetData();

/// Create runtime asset binary directory.
/// Uses old binary format.
/// \param memoryManager Memory manager to use.
/// \return Newly created binary directory.
KANZI_API KzuBinaryDirectory* createRuntimeAssetsDirectory(KzcMemoryManager* memoryManager);

/// Registers build-in runtime assets in resource manager of domain so they can be acquired at runtime.
///
/// \param resourceManager Domain in resource manager of which to register runtime assets.
KANZI_API void registerRuntimeAssets(Domain* domain);


}

#endif
