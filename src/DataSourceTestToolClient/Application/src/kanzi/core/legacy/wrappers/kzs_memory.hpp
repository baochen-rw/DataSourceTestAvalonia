/**
* \file
* System memory manager.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_MEMORY_H
#define KZS_MEMORY_H

#include <kanzi/core/legacy/kzs_types.hpp>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


/** Memory allocation size type. */
typedef size_t kzSizeT;


/** System level malloc. */
KANZI_API void* kzsMalloc(kzSizeT size);

/** System level malloc. */
void* kzsRealloc(void* pointer, kzSizeT newSize);

/** System level free. */
KANZI_API void kzsFree(void* pointer);

/** System level memcpy. */
KZ_INLINE void kzsMemcpy(void* destinationPointer, const void* sourcePointer, kzSizeT size)
{
    memcpy(destinationPointer, sourcePointer, size);
}

/** System level memmove. */
KZ_INLINE void kzsMemmove(void* destinationPointer, const void* sourcePointer, kzSizeT size)
{
    memmove(destinationPointer, sourcePointer, size);
}

/** System level memset. */
KZ_INLINE void kzsMemset(void* pointer, kzInt valueToSet, kzSizeT size)
{
    memset(pointer, valueToSet, size);
}


#endif
