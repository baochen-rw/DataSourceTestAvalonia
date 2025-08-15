/**
* \file
* Binary loader for .kzb format.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_LOADER_H
#define KZU_BINARY_LOADER_H

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#ifndef SPANSION
#define KZ_FEATURE_MMAP
#endif

// Forward declarations.
struct KzcMemoryManager;
struct KzcProject;
struct KzcInputStream;

namespace kanzi
{
class ResourceManager;
}


/**
 * \struct KzuBinaryLoader
 * Binary loader structure.
 */
struct KzuBinaryLoader;


/** Callback that is asked for if a binary name is valid for loading. */
typedef kzsError (*KzuBinaryLoaderValidator)(kzString binaryPath, void* userData, kzBool* out_valid);


/** Creates a new binary loader. */
kzsError kzuBinaryLoaderCreate(const KzcMemoryManager* memoryManager, kanzi::ResourceManager* resourceManager, KzuBinaryLoader** out_binaryLoader);

/** Deletes a binary loader. */
kzsError kzuBinaryLoaderDelete(struct KzuBinaryLoader* binaryLoader);


/** Sets a callback that is asked for if a binary name is valid for loading. */
KANZI_API kzsError kzuBinaryLoaderSetValidator(struct KzuBinaryLoader* binaryLoader, KzuBinaryLoaderValidator validator, void* userData);


/** Reads the directory structure of given file resource to memory and merges it with the current state. */
kzsError kzuBinaryLoaderAddBinary(const struct KzuBinaryLoader* binaryLoader, kzString binaryPath);

/** Reads the directory structure of given memory block to memory and merges it with the current state. */
kzsError kzuBinaryLoaderAddBinaryMemory(const struct KzuBinaryLoader* binaryLoader, kzUint byteCount, const kanzi::byte* bytes);

#ifdef KZ_FEATURE_MMAP
/** Maps the binary file to memory and reads the directory structure from it and merges it with the current state. */
kzsError kzuBinaryLoaderAddMemoryMappedBinary(const struct KzuBinaryLoader* binaryLoader, kzString binaryPath);
#endif






#endif
