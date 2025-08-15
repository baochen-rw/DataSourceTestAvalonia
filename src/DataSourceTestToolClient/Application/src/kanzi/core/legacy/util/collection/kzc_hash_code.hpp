/**
 * \file
 * General purpose hash code functions.
 * Hash code and comparator is related such that for two objects a and b if compare(a,b) == 0 then hashCode(a) == hashCode(b).
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZC_HASH_CODE_H
#define KZC_HASH_CODE_H


#include <kanzi/core/legacy/util/collection/kzc_collection_value.hpp>

#include <kanzi/core/legacy/util/string/kzc_string.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>


/** Knuth's hash multiplier for 32-bit constants. */
#define KZ_KNUTH_HASH_MUL 2654435761U

/** When defined, use Knuth's hash over FNV hash. */
#undef KZ_USE_KNUTH_HASH

/** FNV-1 hash seed. */
#define KZ_FNV1_HASH_SEED 2166136261U

/** FNV-1 hash prime. */
#define KZ_FNV1_HASH_PRIME 16777619U

/** Custom hash function definition. */
typedef kzU32 (*KzcHashFunction)(const void* object);


/* Hash code functions for fundamental Kanzi collection data types. */

/** Hash code function for unsigned integers. */
KZ_INLINE kzU32 kzcHashCodeFromUint(kzUint value)
{
#if defined(KZ_USE_KNUTH_HASH)
    return KZ_KNUTH_HASH_MUL * (kzU32)value;
#else
    kzU32 inputValue = (kzU32)value;
    kzU32 hash = KZ_FNV1_HASH_SEED;
    hash ^= inputValue & 0xFF; /* FNV-1a, do XOR before MUL. */
    hash *= KZ_FNV1_HASH_PRIME;
    hash ^= (inputValue >> 8) & 0xFF;
    hash *= KZ_FNV1_HASH_PRIME;
    hash ^= (inputValue >> 16) & 0xFF;
    hash *= KZ_FNV1_HASH_PRIME;
    hash ^= (inputValue >> 24);
    return hash * KZ_FNV1_HASH_PRIME;
#endif
}

/** Hash code function for floats. */
KZ_INLINE kzU32 kzcHashCodeFromFloat(kzFloat value)
{
    union KzcCollectionValue key;
    key.floatValue = value;
    return kzcHashCodeFromUint(key.uintValue);
}

/** Hash code function for signed integers. */
KZ_INLINE kzU32 kzcHashCodeFromInt(kzInt value)
{
    union KzcCollectionValue key;
    key.intValue = value;
    return kzcHashCodeFromUint(key.uintValue);
}

/** Hash code function for pointers that are already casted to uints. */
KZ_INLINE kzU32 kzcHashCodeFromPointerUint(kzUint value)
{
    return kzcHashCodeFromUint((value >> 3) + (value << 29)); /* Pointer alignment decreases entropy. 'Rotate' them out. */
}

/** Hash code function for pointers. */
KZ_INLINE kzU32 kzcHashCodeFromPointer(const void* value)
{
    union KzcCollectionValue key;
    key.pointerValue = value;
    return kzcHashCodeFromPointerUint(key.uintValue);
}

/** Hash code function for strings. */
KZ_INLINE kzU32 kzcHashCodeFromString(kzString value)
{
    kzU32 hash = 5381;
    kzUint i;

    /* djb2 hash algorithm */

    for (i = 0; value[i] != KZC_STRING_TERMINATION_SYMBOL; ++i)
    {
        hash = ((hash << 5) + hash) + (kzU32)(kzByte)value[i]; /* hash * 33 + c */
    }

    return hash;
}


#endif

