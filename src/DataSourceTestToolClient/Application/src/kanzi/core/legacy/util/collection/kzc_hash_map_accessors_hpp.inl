/**
* \file
* Accessor declarations for hash map. To be included in kzc_hash_map.h
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/** Adds an entry to a hash map from pointers to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapPointerPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value);
/** Adds an entry to a hash map from pointers to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapPointerPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value);
/** Adds an entry to a hash map from pointers to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapPointerPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value);
/** Adds an entry to a hash map from pointers to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapPointerPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value);
/** Adds an entry to a hash map from pointers to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapPointerPutString(struct KzcHashMap* hashMap, const void* key, kzString value);
/** Adds an entry to a hash map from integers to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapIntPutPointer(struct KzcHashMap* hashMap, kzInt key, const void* value);
/** Adds an entry to a hash map from integers to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapIntPutInt(struct KzcHashMap* hashMap, kzInt key, kzInt value);
/** Adds an entry to a hash map from integers to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapIntPutUint(struct KzcHashMap* hashMap, kzInt key, kzUint value);
/** Adds an entry to a hash map from integers to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapIntPutFloat(struct KzcHashMap* hashMap, kzInt key, kzFloat value);
/** Adds an entry to a hash map from integers to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapIntPutString(struct KzcHashMap* hashMap, kzInt key, kzString value);
/** Adds an entry to a hash map from unsigned integers to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapUintPutPointer(struct KzcHashMap* hashMap, kzUint key, const void* value);
/** Adds an entry to a hash map from unsigned integers to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapUintPutInt(struct KzcHashMap* hashMap, kzUint key, kzInt value);
/** Adds an entry to a hash map from unsigned integers to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapUintPutUint(struct KzcHashMap* hashMap, kzUint key, kzUint value);
/** Adds an entry to a hash map from unsigned integers to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapUintPutFloat(struct KzcHashMap* hashMap, kzUint key, kzFloat value);
/** Adds an entry to a hash map from unsigned integers to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapUintPutString(struct KzcHashMap* hashMap, kzUint key, kzString value);
/** Adds an entry to a hash map from floats to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapFloatPutPointer(struct KzcHashMap* hashMap, kzFloat key, const void* value);
/** Adds an entry to a hash map from floats to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapFloatPutInt(struct KzcHashMap* hashMap, kzFloat key, kzInt value);
/** Adds an entry to a hash map from floats to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapFloatPutUint(struct KzcHashMap* hashMap, kzFloat key, kzUint value);
/** Adds an entry to a hash map from floats to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapFloatPutFloat(struct KzcHashMap* hashMap, kzFloat key, kzFloat value);
/** Adds an entry to a hash map from floats to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapFloatPutString(struct KzcHashMap* hashMap, kzFloat key, kzString value);
/** Adds an entry to a hash map from strings to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapStringPutPointer(struct KzcHashMap* hashMap, kzString key, const void* value);
/** Adds an entry to a hash map from strings to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapStringPutInt(struct KzcHashMap* hashMap, kzString key, kzInt value);
/** Adds an entry to a hash map from strings to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapStringPutUint(struct KzcHashMap* hashMap, kzString key, kzUint value);
/** Adds an entry to a hash map from strings to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapStringPutFloat(struct KzcHashMap* hashMap, kzString key, kzFloat value);
/** Adds an entry to a hash map from strings to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapStringPutString(struct KzcHashMap* hashMap, kzString key, kzString value);
/** Adds an entry to a hash map from pointers to pointers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapCustomPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value);
/** Adds an entry to a hash map from pointers to integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapCustomPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value);
/** Adds an entry to a hash map from pointers to unsigned integers. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapCustomPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value);
/** Adds an entry to a hash map from pointers to floats. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapCustomPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value);
/** Adds an entry to a hash map from pointers to strings. In case of a key collision the existing entry is replaced. */
KANZI_API kzsError kzcHashMapCustomPutString(struct KzcHashMap* hashMap, const void* key, kzString value);

/** Gets the value associated with the specified key from the hash map from pointers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapPointerGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the value associated with the specified key from the hash map from pointers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapPointerGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapPointerGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapPointerGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapPointerGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from integers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapIntGetPointer(const struct KzcHashMap* hashMap, kzInt key, void** out_value);
/** Gets the value associated with the specified key from the hash map from integers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapIntGetInt(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from integers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapIntGetUint(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from integers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapIntGetFloat(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from integers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapIntGetString(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapUintGetPointer(const struct KzcHashMap* hashMap, kzUint key, void** out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapUintGetInt(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapUintGetUint(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapUintGetFloat(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from unsigned integers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapUintGetString(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from floats to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapFloatGetPointer(const struct KzcHashMap* hashMap, kzFloat key, void** out_value);
/** Gets the value associated with the specified key from the hash map from floats to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapFloatGetInt(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from floats to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapFloatGetUint(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from floats to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapFloatGetFloat(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from floats to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapFloatGetString(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from strings to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapStringGetPointer(const struct KzcHashMap* hashMap, kzString key, void** out_value);
/** Gets the value associated with the specified key from the hash map from strings to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapStringGetInt(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from strings to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapStringGetUint(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from strings to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapStringGetFloat(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from strings to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapStringGetString(const struct KzcHashMap* hashMap, kzString key, kzString* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to pointers. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapCustomGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the value associated with the specified key from the hash map from pointers to integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0. */
KANZI_API kzBool kzcHashMapCustomGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to unsigned integers. If the key is not found, KZ_FALSE is returned and out_value is set to 0U. */
KANZI_API kzBool kzcHashMapCustomGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to floats. If the key is not found, KZ_FALSE is returned and out_value is set to 0.0f. */
KANZI_API kzBool kzcHashMapCustomGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the value associated with the specified key from the hash map from pointers to strings. If the key is not found, KZ_FALSE is returned and out_value is set to KZ_NULL. */
KANZI_API kzBool kzcHashMapCustomGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);

/** Gets an iterator to the location of the given pointer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapPointerFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given integer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapIntFind(const struct KzcHashMap* hashMap, kzInt key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given unsigned integer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapUintFind(const struct KzcHashMap* hashMap, kzUint key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given float key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapFloatFind(const struct KzcHashMap* hashMap, kzFloat key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given string key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapStringFind(const struct KzcHashMap* hashMap, kzString key, struct KzcHashMapIterator* out_iterator);
/** Gets an iterator to the location of the given pointer key in the hash map. If the key is not found, KZ_FALSE is returned and 'out_iterator' is unchanged. */
KANZI_API kzBool kzcHashMapCustomFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator);

/** Removes an entry with the given pointer key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapPointerRemove(struct KzcHashMap* hashMap, const void* key);
/** Removes an entry with the given integer key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapIntRemove(struct KzcHashMap* hashMap, kzInt key);
/** Removes an entry with the given unsigned integer key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapUintRemove(struct KzcHashMap* hashMap, kzUint key);
/** Removes an entry with the given float key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapFloatRemove(struct KzcHashMap* hashMap, kzFloat key);
/** Removes an entry with the given string key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapStringRemove(struct KzcHashMap* hashMap, kzString key);
/** Removes an entry with the given pointer key from the hash map. If the key does not exist, an error is returned. */
KANZI_API kzsError kzcHashMapCustomRemove(struct KzcHashMap* hashMap, const void* key);

/** Removes an entry with the given pointer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapPointerRemoveIfExists(struct KzcHashMap* hashMap, const void* key);
/** Removes an entry with the given integer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapIntRemoveIfExists(struct KzcHashMap* hashMap, kzInt key);
/** Removes an entry with the given unsigned integer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapUintRemoveIfExists(struct KzcHashMap* hashMap, kzUint key);
/** Removes an entry with the given float key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapFloatRemoveIfExists(struct KzcHashMap* hashMap, kzFloat key);
/** Removes an entry with the given string key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapStringRemoveIfExists(struct KzcHashMap* hashMap, kzString key);
/** Removes an entry with the given pointer key from the hash map, if such an entry exists. If the key does not exist, silently does nothing. */
KANZI_API kzsError kzcHashMapCustomRemoveIfExists(struct KzcHashMap* hashMap, const void* key);

/** Gets the stored key corresponding to the pointer key given as a parameter. Returns ::KZ_NULL if an entry with a matching key does not exist in the hash map. */
KANZI_API const void* kzcHashMapPointerGetStoredKey(const struct KzcHashMap* hashMap, const void* key);
/** Gets the stored key corresponding to the pointer key given as a parameter. Returns ::KZ_NULL if an entry with a matching key does not exist in the hash map. */
KANZI_API const void* kzcHashMapCustomGetStoredKey(const struct KzcHashMap* hashMap, const void* key);

/** Checks if the specified key exists in the hash map from pointers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapPointerContains(const struct KzcHashMap* hashMap, const void* key);
/** Checks if the specified key exists in the hash map from integers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapIntContains(const struct KzcHashMap* hashMap, kzInt key);
/** Checks if the specified key exists in the hash map from unsigned integers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapUintContains(const struct KzcHashMap* hashMap, kzUint key);
/** Checks if the specified key exists in the hash map from floats. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapFloatContains(const struct KzcHashMap* hashMap, kzFloat key);
/** Checks if the specified key exists in the hash map from strings. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapStringContains(const struct KzcHashMap* hashMap, kzString key);
/** Checks if the specified key exists in the hash map from pointers. Returns ::KZ_TRUE if the key is found and KZ_FALSE otherwise. */
KANZI_API kzBool kzcHashMapCustomContains(const struct KzcHashMap* hashMap, const void* key);

/** Gets the specified value from the hash map from pointers to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapPointerGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the specified value from the hash map from pointers to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapPointerGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the specified value from the hash map from pointers to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapPointerGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the specified value from the hash map from pointers to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapPointerGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the specified value from the hash map from pointers to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapPointerGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);
/** Gets the specified value from the hash map from integers to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapIntGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzInt key, void** out_value);
/** Gets the specified value from the hash map from integers to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapIntGetIntOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value);
/** Gets the specified value from the hash map from integers to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapIntGetUintOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value);
/** Gets the specified value from the hash map from integers to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapIntGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value);
/** Gets the specified value from the hash map from integers to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapIntGetStringOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value);
/** Gets the specified value from the hash map from unsigned integers to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapUintGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzUint key, void** out_value);
/** Gets the specified value from the hash map from unsigned integers to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapUintGetIntOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value);
/** Gets the specified value from the hash map from unsigned integers to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapUintGetUintOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value);
/** Gets the specified value from the hash map from unsigned integers to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapUintGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value);
/** Gets the specified value from the hash map from unsigned integers to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapUintGetStringOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value);
/** Gets the specified value from the hash map from floats to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapFloatGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, void** out_value);
/** Gets the specified value from the hash map from floats to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapFloatGetIntOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value);
/** Gets the specified value from the hash map from floats to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapFloatGetUintOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value);
/** Gets the specified value from the hash map from floats to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapFloatGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value);
/** Gets the specified value from the hash map from floats to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapFloatGetStringOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value);
/** Gets the specified value from the hash map from strings to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapStringGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzString key, void** out_value);
/** Gets the specified value from the hash map from strings to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapStringGetIntOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value);
/** Gets the specified value from the hash map from strings to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapStringGetUintOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value);
/** Gets the specified value from the hash map from strings to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapStringGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value);
/** Gets the specified value from the hash map from strings to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapStringGetStringOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzString* out_value);
/** Gets the specified value from the hash map from pointers to pointers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapCustomGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value);
/** Gets the specified value from the hash map from pointers to integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapCustomGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value);
/** Gets the specified value from the hash map from pointers to unsigned integers. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapCustomGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value);
/** Gets the specified value from the hash map from pointers to floats. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapCustomGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value);
/** Gets the specified value from the hash map from pointers to strings. Returns error if the key is not found. */
KANZI_API kzsError kzcHashMapCustomGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value);

/** Returns the pointer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorPointerGetKey(iterator_param) (kzcHashMapIteratorPointerGetKey_private(&iterator_param))
/** Returns the integer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorIntGetKey(iterator_param) (kzcHashMapIteratorIntGetKey_private(&iterator_param))
/** Returns the unsigned integer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorUintGetKey(iterator_param) (kzcHashMapIteratorUintGetKey_private(&iterator_param))
/** Returns the float key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorFloatGetKey(iterator_param) (kzcHashMapIteratorFloatGetKey_private(&iterator_param))
/** Returns the string key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorStringGetKey(iterator_param) (kzcHashMapIteratorStringGetKey_private(&iterator_param))
/** Returns the pointer key of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorCustomGetKey(iterator_param) (kzcHashMapIteratorCustomGetKey_private(&iterator_param))

/** Returns the pointer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetPointerValue(iterator_param) (kzcHashMapIteratorGetPointerValue_private(&iterator_param))
/** Returns the integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetIntValue(iterator_param) (kzcHashMapIteratorGetIntValue_private(&iterator_param))
/** Returns the unsigned integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetUintValue(iterator_param) (kzcHashMapIteratorGetUintValue_private(&iterator_param))
/** Returns the float value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetFloatValue(iterator_param) (kzcHashMapIteratorGetFloatValue_private(&iterator_param))
/** Returns the string value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorGetStringValue(iterator_param) (kzcHashMapIteratorGetStringValue_private(&iterator_param))

/** Sets the pointer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetPointerValue(iterator_param, value_param) (kzcHashMapIteratorSetPointerValue_private(&iterator_param, value_param))
/** Sets the integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetIntValue(iterator_param, value_param) (kzcHashMapIteratorSetIntValue_private(&iterator_param, value_param))
/** Sets the unsigned integer value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetUintValue(iterator_param, value_param) (kzcHashMapIteratorSetUintValue_private(&iterator_param, value_param))
/** Sets the float value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetFloatValue(iterator_param, value_param) (kzcHashMapIteratorSetFloatValue_private(&iterator_param, value_param))
/** Sets the string value of the hash map entry pointed by the iterator. */
#define kzcHashMapIteratorSetStringValue(iterator_param, value_param) (kzcHashMapIteratorSetStringValue_private(&iterator_param, value_param))


/* Private definitions. */

/** \see kzcHashMapIteratorPointerGetKey */
KANZI_API const void* kzcHashMapIteratorPointerGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorIntGetKey */
KANZI_API kzInt kzcHashMapIteratorIntGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorUintGetKey */
KANZI_API kzUint kzcHashMapIteratorUintGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorFloatGetKey */
KANZI_API kzFloat kzcHashMapIteratorFloatGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorStringGetKey */
KANZI_API kzString kzcHashMapIteratorStringGetKey_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorCustomGetKey */
KANZI_API const void* kzcHashMapIteratorCustomGetKey_private(const struct KzcHashMapIterator* iterator);

/** \see kzcHashMapIteratorGetPointerValue */
KANZI_API void* kzcHashMapIteratorGetPointerValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetIntValue */
KANZI_API kzInt kzcHashMapIteratorGetIntValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetUintValue */
KANZI_API kzUint kzcHashMapIteratorGetUintValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetFloatValue */
KANZI_API kzFloat kzcHashMapIteratorGetFloatValue_private(const struct KzcHashMapIterator* iterator);
/** \see kzcHashMapIteratorGetStringValue */
KANZI_API kzString kzcHashMapIteratorGetStringValue_private(const struct KzcHashMapIterator* iterator);

/** \see kzcHashMapIteratorSetPointerValue */
KANZI_API void kzcHashMapIteratorSetPointerValue_private(const struct KzcHashMapIterator* iterator, const void* value);
/** \see kzcHashMapIteratorSetIntValue */
KANZI_API void kzcHashMapIteratorSetIntValue_private(const struct KzcHashMapIterator* iterator, kzInt value);
/** \see kzcHashMapIteratorSetUintValue */
KANZI_API void kzcHashMapIteratorSetUintValue_private(const struct KzcHashMapIterator* iterator, kzUint value);
/** \see kzcHashMapIteratorSetFloatValue */
KANZI_API void kzcHashMapIteratorSetFloatValue_private(const struct KzcHashMapIterator* iterator, kzFloat value);
/** \see kzcHashMapIteratorSetStringValue */
KANZI_API void kzcHashMapIteratorSetStringValue_private(const struct KzcHashMapIterator* iterator, kzString value);
