#ifndef SPANSION
#define KZ_FEATURE_MMAP
#endif

#ifdef KZ_FEATURE_MMAP
/**
* \mmap
* 
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_MMAP_H
#define KZS_MMAP_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/wrappers/kzs_memory.hpp>


struct KzsMemoryMappedFile;

/** Returns true if memory mapped files are supported on this platform. */
kzBool kzsMemoryMappedFileIsSupported(void);

/** Opens a memory mapped file. */
kzsError kzsMemoryMappedFileCreate(kzString filePath, struct KzsMemoryMappedFile** out_memoryMappedFile);

/** Closes a memory mapped file. */
kzsError kzsMemoryMappedFileDelete(struct KzsMemoryMappedFile* memoryMappedFile);

/** Returns true if the file exists and is over 0 bytes in size. */
kzBool kzsMemoryMappedFileIsValid(kzString filePath);

/** Returns the size of the memory mapped file. */
kzSizeT kzsMemoryMappedFileGetSize(const struct KzsMemoryMappedFile* memoryMappedFile);

/** Returns the address of the beginning of the memory mapped file. */
void* kzsMemoryMappedFileGetPointer(const struct KzsMemoryMappedFile* memoryMappedFile);


#endif

#endif
