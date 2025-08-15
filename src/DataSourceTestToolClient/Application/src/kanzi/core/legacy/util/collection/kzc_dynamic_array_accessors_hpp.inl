/**
* \file
* Accessor declarations for dynamic array. To be included in kzc_dynamic_array.h
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/** Adds the given pointer element to the pointer dynamic array. */ 
KANZI_API kzsError kzcDynamicArrayPointerAdd(struct KzcDynamicArray* dynamicArray, const void* value);
/** Adds the given integer element to the integer dynamic array. */ 
KANZI_API kzsError kzcDynamicArrayIntAdd(struct KzcDynamicArray* dynamicArray, kzInt value);
/** Adds the given unsigned integer element to the unsigned integer dynamic array. */ 
KANZI_API kzsError kzcDynamicArrayUintAdd(struct KzcDynamicArray* dynamicArray, kzUint value);
/** Adds the given float element to the float dynamic array. */ 
KANZI_API kzsError kzcDynamicArrayFloatAdd(struct KzcDynamicArray* dynamicArray, kzFloat value);
/** Adds the given string element to the string dynamic array. */ 
KANZI_API kzsError kzcDynamicArrayStringAdd(struct KzcDynamicArray* dynamicArray, kzString value);

/** Retrieves an element from the pointer dynamic array from the given index. The index must not be out of bounds. */
KANZI_API void* kzcDynamicArrayPointerGet(const struct KzcDynamicArray* dynamicArray, kzUint index);
/** Retrieves an element from the integer dynamic array from the given index. The index must not be out of bounds. */
KANZI_API kzInt kzcDynamicArrayIntGet(const struct KzcDynamicArray* dynamicArray, kzUint index);
/** Retrieves an element from the unsigned integer dynamic array from the given index. The index must not be out of bounds. */
KANZI_API kzUint kzcDynamicArrayUintGet(const struct KzcDynamicArray* dynamicArray, kzUint index);
/** Retrieves an element from the float dynamic array from the given index. The index must not be out of bounds. */
KANZI_API kzFloat kzcDynamicArrayFloatGet(const struct KzcDynamicArray* dynamicArray, kzUint index);
/** Retrieves an element from the string dynamic array from the given index. The index must not be out of bounds. */
KANZI_API kzString kzcDynamicArrayStringGet(const struct KzcDynamicArray* dynamicArray, kzUint index);

/** Replaces the pointer element at the specified index in the pointer dynamic array with the given pointer element. */
KANZI_API void kzcDynamicArrayPointerReplace(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element);
/** Replaces the integer element at the specified index in the integer dynamic array with the given integer element. */
KANZI_API void kzcDynamicArrayIntReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element);
/** Replaces the unsigned integer element at the specified index in the unsigned integer dynamic array with the given unsigned integer element. */
KANZI_API void kzcDynamicArrayUintReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element);
/** Replaces the float element at the specified index in the float dynamic array with the given float element. */
KANZI_API void kzcDynamicArrayFloatReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element);
/** Replaces the string element at the specified index in the string dynamic array with the given string element. */
KANZI_API void kzcDynamicArrayStringReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element);

/**
 * Sets the element at the given index of the pointer dynamic array.
 * If the index is out of bounds, the array is resized to support the given index and new slots filled with default values.
 * Otherwise replaces the existing pointer element.
 */
KANZI_API kzsError kzcDynamicArrayPointerSet(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element);
/**
 * Sets the element at the given index of the integer dynamic array.
 * If the index is out of bounds, the array is resized to support the given index and new slots filled with default values.
 * Otherwise replaces the existing integer element.
 */
KANZI_API kzsError kzcDynamicArrayIntSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element);
/**
 * Sets the element at the given index of the unsigned integer dynamic array.
 * If the index is out of bounds, the array is resized to support the given index and new slots filled with default values.
 * Otherwise replaces the existing unsigned integer element.
 */
KANZI_API kzsError kzcDynamicArrayUintSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element);
/**
 * Sets the element at the given index of the float dynamic array.
 * If the index is out of bounds, the array is resized to support the given index and new slots filled with default values.
 * Otherwise replaces the existing float element.
 */
KANZI_API kzsError kzcDynamicArrayFloatSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element);
/**
 * Sets the element at the given index of the string dynamic array.
 * If the index is out of bounds, the array is resized to support the given index and new slots filled with default values.
 * Otherwise replaces the existing string element.
 */
KANZI_API kzsError kzcDynamicArrayStringSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element);

/**
 * Removes the specified pointer element from the pointer dynamic array. Decides equality by simple comparison.
 * Returns an error if the element is not found.
 */
KANZI_API kzsError kzcDynamicArrayPointerRemove(struct KzcDynamicArray* dynamicArray, const void* element);
/**
 * Removes the specified integer element from the integer dynamic array. Decides equality by simple comparison.
 * Returns an error if the element is not found.
 */
KANZI_API kzsError kzcDynamicArrayIntRemove(struct KzcDynamicArray* dynamicArray, kzInt element);
/**
 * Removes the specified unsigned integer element from the unsigned integer dynamic array. Decides equality by simple comparison.
 * Returns an error if the element is not found.
 */
KANZI_API kzsError kzcDynamicArrayUintRemove(struct KzcDynamicArray* dynamicArray, kzUint element);
/**
 * Removes the specified float element from the float dynamic array. Decides equality by simple comparison.
 * Returns an error if the element is not found.
 */
KANZI_API kzsError kzcDynamicArrayFloatRemove(struct KzcDynamicArray* dynamicArray, kzFloat element);
/**
 * Removes the specified string element from the string dynamic array. Decides equality by simple comparison.
 * Returns an error if the element is not found.
 */
KANZI_API kzsError kzcDynamicArrayStringRemove(struct KzcDynamicArray* dynamicArray, kzString element);

/**
 * Removes from the dynamic array all elements that are found equal to the given pointer element using the given comparator.
 * Returns the number of elements removed.
 */
KANZI_API kzsError kzcDynamicArrayPointerRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* element, kzUint* out_removedCount);
/**
 * Removes from the dynamic array all elements that are found equal to the given integer element using the given comparator.
 * Returns the number of elements removed.
 */
KANZI_API kzsError kzcDynamicArrayIntRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt element, kzUint* out_removedCount);
/**
 * Removes from the dynamic array all elements that are found equal to the given unsigned integer element using the given comparator.
 * Returns the number of elements removed.
 */
KANZI_API kzsError kzcDynamicArrayUintRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint element, kzUint* out_removedCount);
/**
 * Removes from the dynamic array all elements that are found equal to the given float element using the given comparator.
 * Returns the number of elements removed.
 */
KANZI_API kzsError kzcDynamicArrayFloatRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat element, kzUint* out_removedCount);
/**
 * Removes from the dynamic array all elements that are found equal to the given string element using the given comparator.
 * Returns the number of elements removed.
 */
KANZI_API kzsError kzcDynamicArrayStringRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString element, kzUint* out_removedCount);

/** Checks if pointer dynamic array contains the specific pointer element. */
KANZI_API kzBool kzcDynamicArrayPointerContains(const struct KzcDynamicArray* dynamicArray, const void* element);
/** Checks if integer dynamic array contains the specific integer element. */
KANZI_API kzBool kzcDynamicArrayIntContains(const struct KzcDynamicArray* dynamicArray, kzInt element);
/** Checks if unsigned integer dynamic array contains the specific unsigned integer element. */
KANZI_API kzBool kzcDynamicArrayUintContains(const struct KzcDynamicArray* dynamicArray, kzUint element);
/** Checks if float dynamic array contains the specific float element. */
KANZI_API kzBool kzcDynamicArrayFloatContains(const struct KzcDynamicArray* dynamicArray, kzFloat element);
/** Checks if string dynamic array contains the specific string element. */
KANZI_API kzBool kzcDynamicArrayStringContains(const struct KzcDynamicArray* dynamicArray, kzString element);

/** Finds the first index of the pointer dynamic array whose value is the given pointer element. Returns ::KZ_TRUE if the element was found. */
KANZI_API kzBool kzcDynamicArrayPointerFindIndex(const struct KzcDynamicArray* dynamicArray, const void* element, kzUint* out_index);
/** Finds the first index of the integer dynamic array whose value is the given integer element. Returns ::KZ_TRUE if the element was found. */
KANZI_API kzBool kzcDynamicArrayIntFindIndex(const struct KzcDynamicArray* dynamicArray, kzInt element, kzUint* out_index);
/** Finds the first index of the unsigned integer dynamic array whose value is the given unsigned integer element. Returns ::KZ_TRUE if the element was found. */
KANZI_API kzBool kzcDynamicArrayUintFindIndex(const struct KzcDynamicArray* dynamicArray, kzUint element, kzUint* out_index);
/** Finds the first index of the float dynamic array whose value is the given float element. Returns ::KZ_TRUE if the element was found. */
KANZI_API kzBool kzcDynamicArrayFloatFindIndex(const struct KzcDynamicArray* dynamicArray, kzFloat element, kzUint* out_index);
/** Finds the first index of the string dynamic array whose value is the given string element. Returns ::KZ_TRUE if the element was found. */
KANZI_API kzBool kzcDynamicArrayStringFindIndex(const struct KzcDynamicArray* dynamicArray, kzString element, kzUint* out_index);

/**
 * Finds the first element of the pointer dynamic array that is found equal to the given pointer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayPointerFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* elementToCompare, void** out_element);
/**
 * Finds the first element of the integer dynamic array that is found equal to the given integer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayIntFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt elementToCompare, kzInt* out_element);
/**
 * Finds the first element of the unsigned integer dynamic array that is found equal to the given unsigned integer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayUintFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint elementToCompare, kzUint* out_element);
/**
 * Finds the first element of the float dynamic array that is found equal to the given float element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayFloatFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat elementToCompare, kzFloat* out_element);
/**
 * Finds the first element of the string dynamic array that is found equal to the given string element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayStringFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString elementToCompare, kzString* out_element);

/**
 * Finds the index of the first element of the pointer dynamic array that is found equal to the given pointer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayPointerFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* elementToCompare, kzUint* out_index);
/**
 * Finds the index of the first element of the integer dynamic array that is found equal to the given integer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayIntFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt elementToCompare, kzUint* out_index);
/**
 * Finds the index of the first element of the unsigned integer dynamic array that is found equal to the given unsigned integer element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayUintFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint elementToCompare, kzUint* out_index);
/**
 * Finds the index of the first element of the float dynamic array that is found equal to the given float element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayFloatFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat elementToCompare, kzUint* out_index);
/**
 * Finds the index of the first element of the string dynamic array that is found equal to the given string element by using the given comparator.
 * Returns ::KZ_TRUE if a matching element is found.
 */
KANZI_API kzBool kzcDynamicArrayStringFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString elementToCompare, kzUint* out_index);

/** Inserts the given pointer element before the element at the given index.
 * If the index is out of bounds adds the given element at the end of the array.
 */
KANZI_API kzsError kzcDynamicArrayPointerInsert(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element);
/** Inserts the given integer element before the element at the given index.
 * If the index is out of bounds adds the given element at the end of the array.
 */
KANZI_API kzsError kzcDynamicArrayIntInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element);
/** Inserts the given unsigned integer element before the element at the given index.
 * If the index is out of bounds adds the given element at the end of the array.
 */
KANZI_API kzsError kzcDynamicArrayUintInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element);
/** Inserts the given float element before the element at the given index.
 * If the index is out of bounds adds the given element at the end of the array.
 */
KANZI_API kzsError kzcDynamicArrayFloatInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element);
/** Inserts the given string element before the element at the given index.
 * If the index is out of bounds adds the given element at the end of the array.
 */
KANZI_API kzsError kzcDynamicArrayStringInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element);

/** Creates a new pointer array from the content of the given pointer dynamic array. Returns an array of pointers. */
KANZI_API kzsError kzcDynamicArrayPointerToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, void*** out_array);
/** Creates a new integer array from the content of the given integer dynamic array. Returns an array of integers. */
KANZI_API kzsError kzcDynamicArrayIntToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzInt** out_array);
/** Creates a new unsigned integer array from the content of the given unsigned integer dynamic array. Returns an array of unsigned integers. */
KANZI_API kzsError kzcDynamicArrayUintToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzUint** out_array);
/** Creates a new float array from the content of the given float dynamic array. Returns an array of floats. */
KANZI_API kzsError kzcDynamicArrayFloatToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzFloat** out_array);
/** Creates a new string array from the content of the given string dynamic array. Returns an array of strings. */
KANZI_API kzsError kzcDynamicArrayStringToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzString** out_array);

/** Returns the value of the pointer dynamic array element pointed by the iterator. */
#define kzcDynamicArrayIteratorPointerGetValue(iterator_param) kzcDynamicArrayIteratorPointerGetValue_private(&iterator_param)
/** Returns the value of the integer dynamic array element pointed by the iterator. */
#define kzcDynamicArrayIteratorIntGetValue(iterator_param) kzcDynamicArrayIteratorIntGetValue_private(&iterator_param)
/** Returns the value of the unsigned integer dynamic array element pointed by the iterator. */
#define kzcDynamicArrayIteratorUintGetValue(iterator_param) kzcDynamicArrayIteratorUintGetValue_private(&iterator_param)
/** Returns the value of the float dynamic array element pointed by the iterator. */
#define kzcDynamicArrayIteratorFloatGetValue(iterator_param) kzcDynamicArrayIteratorFloatGetValue_private(&iterator_param)
/** Returns the value of the string dynamic array element pointed by the iterator. */
#define kzcDynamicArrayIteratorStringGetValue(iterator_param) kzcDynamicArrayIteratorStringGetValue_private(&iterator_param)

/** Returns the value of the pointer dynamic array element pointed by the mutable iterator. */
#define kzcDynamicArrayMutableIteratorPointerGetValue(iterator_param) kzcDynamicArrayMutableIteratorPointerGetValue_private(&iterator_param)
/** Returns the value of the integer dynamic array element pointed by the mutable iterator. */
#define kzcDynamicArrayMutableIteratorIntGetValue(iterator_param) kzcDynamicArrayMutableIteratorIntGetValue_private(&iterator_param)
/** Returns the value of the unsigned integer dynamic array element pointed by the mutable iterator. */
#define kzcDynamicArrayMutableIteratorUintGetValue(iterator_param) kzcDynamicArrayMutableIteratorUintGetValue_private(&iterator_param)
/** Returns the value of the float dynamic array element pointed by the mutable iterator. */
#define kzcDynamicArrayMutableIteratorFloatGetValue(iterator_param) kzcDynamicArrayMutableIteratorFloatGetValue_private(&iterator_param)
/** Returns the value of the string dynamic array element pointed by the mutable iterator. */
#define kzcDynamicArrayMutableIteratorStringGetValue(iterator_param) kzcDynamicArrayMutableIteratorStringGetValue_private(&iterator_param)


/* Private definitions. */

/** \see kzcDynamicArrayIteratorPointerGetValue */
KZ_INLINE void* kzcDynamicArrayIteratorPointerGetValue_private(const struct KzcDynamicArrayIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    return (void*)iterator->elements_private[iterator->currentIndex_private].pointerValue;
}

/** \see kzcDynamicArrayIteratorIntGetValue */
KZ_INLINE kzInt kzcDynamicArrayIteratorIntGetValue_private(const struct KzcDynamicArrayIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    return iterator->elements_private[iterator->currentIndex_private].intValue;
}

/** \see kzcDynamicArrayIteratorUintGetValue */
KZ_INLINE kzUint kzcDynamicArrayIteratorUintGetValue_private(const struct KzcDynamicArrayIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    return iterator->elements_private[iterator->currentIndex_private].uintValue;
}

/** \see kzcDynamicArrayIteratorFloatGetValue */
KZ_INLINE kzFloat kzcDynamicArrayIteratorFloatGetValue_private(const struct KzcDynamicArrayIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    return iterator->elements_private[iterator->currentIndex_private].floatValue;
}

/** \see kzcDynamicArrayIteratorStringGetValue */
KZ_INLINE kzString kzcDynamicArrayIteratorStringGetValue_private(const struct KzcDynamicArrayIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    return iterator->elements_private[iterator->currentIndex_private].stringValue;
}


/** \see kzcDynamicArrayMutableIteratorPointerGetValue */
KZ_INLINE void* kzcDynamicArrayMutableIteratorPointerGetValue_private(const struct KzcDynamicArrayMutableIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    return kzcDynamicArrayPointerGet(iterator->dynamicArray_private, (kzUint)iterator->currentIndex_private);
}

/** \see kzcDynamicArrayMutableIteratorIntGetValue */
KZ_INLINE kzInt kzcDynamicArrayMutableIteratorIntGetValue_private(const struct KzcDynamicArrayMutableIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    return kzcDynamicArrayIntGet(iterator->dynamicArray_private, (kzUint)iterator->currentIndex_private);
}

/** \see kzcDynamicArrayMutableIteratorUintGetValue */
KZ_INLINE kzUint kzcDynamicArrayMutableIteratorUintGetValue_private(const struct KzcDynamicArrayMutableIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    return kzcDynamicArrayUintGet(iterator->dynamicArray_private, (kzUint)iterator->currentIndex_private);
}

/** \see kzcDynamicArrayMutableIteratorFloatGetValue */
KZ_INLINE kzFloat kzcDynamicArrayMutableIteratorFloatGetValue_private(const struct KzcDynamicArrayMutableIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    return kzcDynamicArrayFloatGet(iterator->dynamicArray_private, (kzUint)iterator->currentIndex_private);
}

/** \see kzcDynamicArrayMutableIteratorStringGetValue */
KZ_INLINE kzString kzcDynamicArrayMutableIteratorStringGetValue_private(const struct KzcDynamicArrayMutableIterator* iterator)
{
#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(iterator->dynamicArray_private, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    return kzcDynamicArrayStringGet(iterator->dynamicArray_private, (kzUint)iterator->currentIndex_private);
}