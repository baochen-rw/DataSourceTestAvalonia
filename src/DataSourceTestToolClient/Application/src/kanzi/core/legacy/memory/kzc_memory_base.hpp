/**
* \file
* Memory manager private members.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_BASE_H
#define KZC_MEMORY_BASE_H


#include <kanzi/core/legacy/memory/kzc_memory_common.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/thread/kzs_thread.hpp>


/* Forward declarations */
struct KzcMemoryManager;


/** Memory manager delete function type definition. */
typedef kzsError (*KzcMemoryManagerDeletor)(struct KzcMemoryManager* memoryManager);
/** Memory manager alloc function type definition. */
typedef kzsError (*KzcMemoryAllocator)(const struct KzcMemoryManager* memoryManager, kzSizeT size, void** out_pointer MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));
/** Memory manager dealloc function type definition. */
typedef kzsError (*KzcMemoryDeallocator)(const struct KzcMemoryManager* memoryManager, void* pointer MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));


/** Memory manager. */
struct KzcMemoryManager
{
    enum KzcMemoryManagerType type; /**< Type of the memory manager. */
    kzSizeT size; /**< Total size for the memory manager, KZC_MEMORY_MANAGER_SIZE_UNSPECIFIED if not specified. */
    KzcMemoryManagerDeletor deletor; /**< Memory manager deletor function. */
    KzcMemoryAllocator allocator; /**< Memory allocator function. */
    KzcMemoryDeallocator deallocator; /**< Memory deallocator function. */
};


#ifdef KZC_MEMORY_DEBUG
static const kzUint KZC_MEMORY_MANAGER_GUARD_PRE_SIZE = sizeof(kzSizeT);
static const kzUint KZC_MEMORY_MANAGER_GUARD_POST_SIZE = sizeof(kzSizeT);
#endif


/** Initializes a memory manager. */
void kzcMemoryManagerInitialize_protected(struct KzcMemoryManager* manager, enum KzcMemoryManagerType type, KzcMemoryManagerDeletor deletor,
                                          KzcMemoryAllocator allocator, KzcMemoryDeallocator deallocator, kzSizeT size);

#if defined KZC_MEMORY_DEBUG && defined KZC_MEMORY_DEBUG_GUARD_AGGRESSIVELY
/** Fills the given pointer with guard data. */
void kzcMemoryFillUnallocated(kzByte* pointer, kzSizeT size);

/** Checks if the given pointer contains proper memory guards. */
kzBool kzcMemoryCheckUnallocated(const kzByte* pointer, kzSizeT size);
#endif

void kzcMemoryManagerDumpLeaks(struct KzcMemoryManager* manager);


#endif
