/**
 * \file
 * Hash map. Hash map stores arbitrary key -> value mappings.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZC_HASH_MAP_H
#define KZC_HASH_MAP_H


#include <kanzi/core/legacy/util/collection/kzc_hash_code.hpp>
#include <kanzi/core/legacy/util/collection/kzc_comparator.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/* Forward declarations */
struct KzcMemoryManager;
struct KzcHashMapOrderedEntry;


/** Chain length elementary type */
typedef kzUint KzcHashMapChainLengthType;


/**
* Key type identifier for hash map.
* To use custom hash and comparator functions set key type to KZC_HASH_MAP_KEY_TYPE_CUSTOM.
*/
enum KzcHashMapKeyType
{
    KZC_HASH_MAP_KEY_TYPE_INT = 1,      /**< Integer key. */
    KZC_HASH_MAP_KEY_TYPE_UINT = 2,     /**< Unsigned integer key. */
    KZC_HASH_MAP_KEY_TYPE_FLOAT = 4,    /**< Float key. */
    KZC_HASH_MAP_KEY_TYPE_POINTER = 8,  /**< Pointer key. */
    KZC_HASH_MAP_KEY_TYPE_STRING = 16,  /**< String key (kzString). */
    KZC_HASH_MAP_KEY_TYPE_CUSTOM = 32   /**< Pointer key with custom hash function and comparator. */
};


/**
* Accessor to the contents of a HashMap
*
* Usage:
*     struct KzcHashMapIterator it = KzcHashMapGetIterator(map);
*     while (KzcHashMapIterate(it))
*     {
*         struct SomeKey* key = (struct SomeKey*)kzcHashMapIteratorPointerGetKey(it); (Optional)
*         struct SomeStruct* value = (struct SomeStruct*)kzcHashMapIteratorGetPointerValue(it);
*         somestruct_some_operation(value);
*         ... etc ...
*     }
*
* Alternative accessor functions are listed in "kzc_hash_map_accessors.h".
*/
struct KzcHashMapIterator
{
    struct KzcHashMap* map_private;        /**< Reference to the hash map accessed by this iterator. */
    kzInt tableIndex;                      /**< Current index in the iterator. */
    kzInt chainIndex;                      /**< Index in the current chain. */
    kzInt chainStart;                      /**< Start of chain in the table. */
    KzcHashMapChainLengthType chainLength; /**< Length of current chain. */
};

/**
 * Configuration parameters for a HashMap. The configuration specifies what type of keys are used in the hash map.
 * The most common configurations are KZC_HASH_MAP_CONFIGURATION_POINTER if the keys are arbitrary pointers and
 * KZC_HASH_MAP_CONFIGURATION_STRING if the keys are strings.
 * Custom configurations can also be created for other key types such as structs by setting key type to be
 * KZC_HASH_MAP_KEY_TYPE_CUSTOM and providing the required callbacks.
 *
 * \see KZC_HASH_MAP_CONFIGURATION_INT
 * \see KZC_HASH_MAP_CONFIGURATION_UINT
 * \see KZC_HASH_MAP_CONFIGURATION_FLOAT
 * \see KZC_HASH_MAP_CONFIGURATION_POINTER
 * \see KZC_HASH_MAP_CONFIGURATION_STRING
 */
struct KzcHashMapConfiguration
{
    enum KzcHashMapKeyType keyType; /**< Type of hash map key. */
    KzcHashFunction hashFunction; /**< Returns a hash code for the specified key. */
    KzcComparatorFunction keyComparator; /**< Comparator for the key. */
};


/**
 * \struct KzcHashMap
 * Hash map.
 */
struct KzcHashMap;


/** Configuration for hash maps where key type is an integer. */
KANZI_API extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_INT;
/** Configuration for hash maps where key type is an unsigned integer. */
KANZI_API extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_UINT;
/** Configuration for hash maps where key type is a float. */
KANZI_API extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_FLOAT;
/** Configuration for hash maps where key type is an arbitrary pointer. */
KANZI_API extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_POINTER;
/** Configuration for hash maps where key type is a string. */
KANZI_API extern const struct KzcHashMapConfiguration KZC_HASH_MAP_CONFIGURATION_STRING;


/**
 * Creates a new initially empty hash map. Stores key-value pairs. Initial capacity is given as a parameter. configuration specifies what type of keys are used in the map.
 * The caller is responsible for deleting returned hash map object with kzcHashMapDelete function.
 */
KANZI_API kzsError kzcHashMapCreateWithCapacity(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                                      kzUint capacity, struct KzcHashMap** out_hashMap);

/**
 * Creates a new initially empty hash map. Stores key-value pairs. configuration specifies what type of keys are used in the map.
 * The caller is responsible for deleting returned hash map object with kzcHashMapDelete function.
 */
KANZI_API kzsError kzcHashMapCreate(const struct KzcMemoryManager* memoryManager, struct KzcHashMapConfiguration configuration,
                          struct KzcHashMap** out_hashMap);

/** Frees the memory allocated for the hash map. */
KANZI_API kzsError kzcHashMapDelete(struct KzcHashMap* hashMap);


/**
* Clears the content of the hash map.
*
* The capacity of the hash map does not change.
*
* \param hashMap Hash map to clear.
* \return Error code.
*/
KANZI_API kzsError kzcHashMapClear(struct KzcHashMap* hashMap);

/** Get hash map configuration. */
KANZI_API struct KzcHashMapConfiguration kzcHashMapGetConfiguration(const struct KzcHashMap* hashMap);


/** Returns the number of entries stored in the hash map. */
KANZI_API kzUint kzcHashMapGetSize(const struct KzcHashMap* HashMap);

/** Checks if the hash map is empty or not. */
KANZI_API kzBool kzcHashMapIsEmpty(const struct KzcHashMap* hashMap);


/** Returns an iterator to the hash map. Call kzcHashMapIterate before accessing the first and any subsequent entries. */
KANZI_API struct KzcHashMapIterator kzcHashMapGetIterator(const struct KzcHashMap* hashMap);

#if defined(KANZI_DEBUG)
/** Disable active iterator status. */
KANZI_API void kzcHashMapDisableActiveIterator_private(const struct KzcHashMap* hashMap);
/** Break from hash map iteration. */
#define kzcHashMapIterationBreak(hashMap) \
{ \
    kzcHashMapDisableActiveIterator_private(hashMap); \
    break; \
}
#else
/** Break from hash map iteration - do nothing on release build. */
#define kzcHashMapIterationBreak(hashMap) \
{ \
    break; \
}
#endif


/** Finds the next entry in the attached hash map. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzcHashMapIterate(iterator_param) kzcHashMapIterate_private(&iterator_param)
/**
 * Removes current entry of hash map pointed by the iterator.
 * Next iteration gives the entry that would have been next. Iterator should not be dereferenced at current state.
 */
#define kzcHashMapIteratorRemove(iterator_param) kzcHashMapIteratorRemove_private(&iterator_param)


/** \see kzcHashMapIterate */
KANZI_API kzBool kzcHashMapIterate_private(struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorRemove */
KANZI_API kzsError kzcHashMapIteratorRemove_private(struct KzcHashMapIterator* it);


#include "kzc_hash_map_accessors_hpp.inl"


#endif
