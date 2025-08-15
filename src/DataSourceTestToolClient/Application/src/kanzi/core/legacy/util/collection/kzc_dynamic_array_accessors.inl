/**
* \file
* Accessor implementations for dynamic array. To be included in kzc_dynamic_array.c
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/


kzsError kzcDynamicArrayPointerAdd(struct KzcDynamicArray* dynamicArray, const void* element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.pointerValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    return kzcDynamicArrayAdd_internal(dynamicArray, valueUnion);
}

kzsError kzcDynamicArrayIntAdd(struct KzcDynamicArray* dynamicArray, kzInt element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.intValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    return kzcDynamicArrayAdd_internal(dynamicArray, valueUnion);
}

kzsError kzcDynamicArrayUintAdd(struct KzcDynamicArray* dynamicArray, kzUint element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.uintValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    return kzcDynamicArrayAdd_internal(dynamicArray, valueUnion);
}

kzsError kzcDynamicArrayFloatAdd(struct KzcDynamicArray* dynamicArray, kzFloat element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.floatValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    return kzcDynamicArrayAdd_internal(dynamicArray, valueUnion);
}

kzsError kzcDynamicArrayStringAdd(struct KzcDynamicArray* dynamicArray, kzString element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.stringValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    return kzcDynamicArrayAdd_internal(dynamicArray, valueUnion);
}

kzInt kzcDynamicArrayIntGet(const struct KzcDynamicArray* dynamicArray, kzUint index)
{
    kzInt result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    if (index >= dynamicArray->elementCount)
    {
        kzAssertUnreachableMessage(("Dynamic array index {} is out of bounds.", index));
        result = 0;
    }
    else
    {
        result = dynamicArray->elements[index].intValue;
    }

    return result;
}

kzUint kzcDynamicArrayUintGet(const struct KzcDynamicArray* dynamicArray, kzUint index)
{
    kzUint result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    if (index >= dynamicArray->elementCount)
    {
        kzAssertUnreachableMessage(("Dynamic array index {} is out of bounds.", index));
        result = 0U;
    }
    else
    {
        result = dynamicArray->elements[index].uintValue;
    }

    return result;
}

kzFloat kzcDynamicArrayFloatGet(const struct KzcDynamicArray* dynamicArray, kzUint index)
{
    kzFloat result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    if (index >= dynamicArray->elementCount)
    {
        kzAssertUnreachableMessage(("Dynamic array index {} is out of bounds.", index));
        result = 0.0f;
    }
    else
    {
        result = dynamicArray->elements[index].floatValue;
    }

    return result;
}

kzString kzcDynamicArrayStringGet(const struct KzcDynamicArray* dynamicArray, kzUint index)
{
    kzString result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    if (index >= dynamicArray->elementCount)
    {
        kzAssertUnreachableMessage(("Dynamic array index {} is out of bounds.", index));
        result = KZ_NULL;
    }
    else
    {
        result = dynamicArray->elements[index].stringValue;
    }

    return result;
}


void kzcDynamicArrayPointerReplace(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.pointerValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    kzcDynamicArrayReplace_internal(dynamicArray, index, valueUnion);
}

void kzcDynamicArrayIntReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.intValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    kzcDynamicArrayReplace_internal(dynamicArray, index, valueUnion);
}

void kzcDynamicArrayUintReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.uintValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    kzcDynamicArrayReplace_internal(dynamicArray, index, valueUnion);
}

void kzcDynamicArrayFloatReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.floatValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    kzcDynamicArrayReplace_internal(dynamicArray, index, valueUnion);
}

void kzcDynamicArrayStringReplace(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element)
{
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    valueUnion.stringValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    kzcDynamicArrayReplace_internal(dynamicArray, index, valueUnion);
}


kzsError kzcDynamicArrayPointerSet(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element)
{
    kzsError result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    while (index >= dynamicArray->elementCount)
    {
        result = kzcDynamicArrayGrowIfFull_internal(dynamicArray);
        kzsErrorForward(result);

        dynamicArray->elements[dynamicArray->elementCount++].pointerValue = KZ_NULL;
    }
    
    dynamicArray->elements[index].pointerValue = element;

    kzsSuccess();
}

kzsError kzcDynamicArrayIntSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element)
{
    kzsError result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    while (index >= dynamicArray->elementCount)
    {
        result = kzcDynamicArrayGrowIfFull_internal(dynamicArray);
        kzsErrorForward(result);

        dynamicArray->elements[dynamicArray->elementCount++].intValue = 0;
    }
    
    dynamicArray->elements[index].intValue = element;

    kzsSuccess();
}

kzsError kzcDynamicArrayUintSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element)
{
    kzsError result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    while (index >= dynamicArray->elementCount)
    {
        result = kzcDynamicArrayGrowIfFull_internal(dynamicArray);
        kzsErrorForward(result);

        dynamicArray->elements[dynamicArray->elementCount++].uintValue = 0U;
    }
    
    dynamicArray->elements[index].uintValue = element;

    kzsSuccess();
}

kzsError kzcDynamicArrayFloatSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element)
{
    kzsError result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    while (index >= dynamicArray->elementCount)
    {
        result = kzcDynamicArrayGrowIfFull_internal(dynamicArray);
        kzsErrorForward(result);

        dynamicArray->elements[dynamicArray->elementCount++].floatValue = 0.0f;
    }
    
    dynamicArray->elements[index].floatValue = element;

    kzsSuccess();
}

kzsError kzcDynamicArrayStringSet(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element)
{
    kzsError result;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    while (index >= dynamicArray->elementCount)
    {
        result = kzcDynamicArrayGrowIfFull_internal(dynamicArray);
        kzsErrorForward(result);

        dynamicArray->elements[dynamicArray->elementCount++].stringValue = KZ_NULL;
    }
    
    dynamicArray->elements[index].stringValue = element;

    kzsSuccess();
}


kzsError kzcDynamicArrayPointerRemove(struct KzcDynamicArray* dynamicArray, const void* element)
{
    kzsError result;
    kzUint index;
    kzBool indexFound;

    kzAssert(kzcIsValidPointer(dynamicArray));

    indexFound = kzcDynamicArrayPointerFindIndex(dynamicArray, element, &index);
    kzsErrorTest(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Element to be removed not found in DynamicArray"));

    result = kzcDynamicArrayRemoveByIndex(dynamicArray, index);
    kzsErrorForward(result);

    kzsSuccess();
}

kzsError kzcDynamicArrayIntRemove(struct KzcDynamicArray* dynamicArray, kzInt element)
{
    kzsError result;
    kzUint index;
    kzBool indexFound;

    kzAssert(kzcIsValidPointer(dynamicArray));

    indexFound = kzcDynamicArrayIntFindIndex(dynamicArray, element, &index);
    kzsErrorTest(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Element to be removed not found in DynamicArray"));

    result = kzcDynamicArrayRemoveByIndex(dynamicArray, index);
    kzsErrorForward(result);

    kzsSuccess();
}

kzsError kzcDynamicArrayUintRemove(struct KzcDynamicArray* dynamicArray, kzUint element)
{
    kzsError result;
    kzUint index;
    kzBool indexFound;

    kzAssert(kzcIsValidPointer(dynamicArray));

    indexFound = kzcDynamicArrayUintFindIndex(dynamicArray, element, &index);
    kzsErrorTest(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Element to be removed not found in DynamicArray"));

    result = kzcDynamicArrayRemoveByIndex(dynamicArray, index);
    kzsErrorForward(result);

    kzsSuccess();
}

kzsError kzcDynamicArrayFloatRemove(struct KzcDynamicArray* dynamicArray, kzFloat element)
{
    kzsError result;
    kzUint index;
    kzBool indexFound;

    kzAssert(kzcIsValidPointer(dynamicArray));

    indexFound = kzcDynamicArrayFloatFindIndex(dynamicArray, element, &index);
    kzsErrorTest(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Element to be removed not found in DynamicArray"));

    result = kzcDynamicArrayRemoveByIndex(dynamicArray, index);
    kzsErrorForward(result);

    kzsSuccess();
}

kzsError kzcDynamicArrayStringRemove(struct KzcDynamicArray* dynamicArray, kzString element)
{
    kzsError result;
    kzUint index;
    kzBool indexFound;

    kzAssert(kzcIsValidPointer(dynamicArray));

    indexFound = kzcDynamicArrayStringFindIndex(dynamicArray, element, &index);
    kzsErrorTest(indexFound, KZC_ERROR_ELEMENT_NOT_FOUND, ("Element to be removed not found in DynamicArray"));

    result = kzcDynamicArrayRemoveByIndex(dynamicArray, index);
    kzsErrorForward(result);

    kzsSuccess();
}


kzsError kzcDynamicArrayPointerRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* element, kzUint* out_removedCount)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.pointerValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    return kzcDynamicArrayRemoveIfEqual_internal(dynamicArray, comparator, elementUnion, out_removedCount);
}

kzsError kzcDynamicArrayIntRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt element, kzUint* out_removedCount)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.intValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    return kzcDynamicArrayRemoveIfEqual_internal(dynamicArray, comparator, elementUnion, out_removedCount);
}

kzsError kzcDynamicArrayUintRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint element, kzUint* out_removedCount)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.uintValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    return kzcDynamicArrayRemoveIfEqual_internal(dynamicArray, comparator, elementUnion, out_removedCount);
}

kzsError kzcDynamicArrayFloatRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat element, kzUint* out_removedCount)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.floatValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    return kzcDynamicArrayRemoveIfEqual_internal(dynamicArray, comparator, elementUnion, out_removedCount);
}

kzsError kzcDynamicArrayStringRemoveIfEqual(struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString element, kzUint* out_removedCount)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.stringValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    return kzcDynamicArrayRemoveIfEqual_internal(dynamicArray, comparator, elementUnion, out_removedCount);
}


kzBool kzcDynamicArrayPointerContains(const struct KzcDynamicArray* dynamicArray, const void* element)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

#if defined(KANZI_DEBUG)
    if(size > 0) {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
    }
#endif

    for (i = 0; i < size; ++i)
    {
        if (elements[i].pointerValue == element) 
        {
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}

kzBool kzcDynamicArrayIntContains(const struct KzcDynamicArray* dynamicArray, kzInt element)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

#if defined(KANZI_DEBUG)
    if(size > 0) {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
    }
#endif

    for (i = 0; i < size; ++i)
    {
        if (elements[i].intValue == element) 
        {
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}

kzBool kzcDynamicArrayUintContains(const struct KzcDynamicArray* dynamicArray, kzUint element)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

#if defined(KANZI_DEBUG)
    if(size > 0) {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
    }
#endif

    for (i = 0; i < size; ++i)
    {
        if (elements[i].uintValue == element) 
        {
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}

kzBool kzcDynamicArrayFloatContains(const struct KzcDynamicArray* dynamicArray, kzFloat element)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

#if defined(KANZI_DEBUG)
    if(size > 0) {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
    }
#endif

    for (i = 0; i < size; ++i)
    {
        if (elements[i].floatValue == element)
        {
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}

kzBool kzcDynamicArrayStringContains(const struct KzcDynamicArray* dynamicArray, kzString element)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

#if defined(KANZI_DEBUG)
    if(size > 0) {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
    }
#endif

    for (i = 0; i < size; ++i)
    {
        if (elements[i].stringValue == element) 
        {
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}


kzBool kzcDynamicArrayPointerFindIndex(const struct KzcDynamicArray* dynamicArray, const void* element, kzUint* out_index)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

    for (i = 0; i < size; ++i)
    {
        if (elements[i].pointerValue == element) 
        {
            *out_index = i;
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}
kzBool kzcDynamicArrayIntFindIndex(const struct KzcDynamicArray* dynamicArray, kzInt element, kzUint* out_index)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

    for (i = 0; i < size; ++i)
    {
        if (elements[i].intValue == element) 
        {
            *out_index = i;
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}
kzBool kzcDynamicArrayUintFindIndex(const struct KzcDynamicArray* dynamicArray, kzUint element, kzUint* out_index)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

    for (i = 0; i < size; ++i)
    {
        if (elements[i].uintValue == element) 
        {
            *out_index = i;
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}
kzBool kzcDynamicArrayFloatFindIndex(const struct KzcDynamicArray* dynamicArray, kzFloat element, kzUint* out_index)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

    for (i = 0; i < size; ++i)
    {
        if (elements[i].floatValue == element)
        {
            *out_index = i;
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}
kzBool kzcDynamicArrayStringFindIndex(const struct KzcDynamicArray* dynamicArray, kzString element, kzUint* out_index)
{
    kzUint size;
    kzUint i;
    union KzcCollectionValue* elements;
    kzBool indexFound = KZ_FALSE;

    kzAssert(kzcIsValidPointer(dynamicArray));

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    size = dynamicArray->elementCount;
    elements = dynamicArray->elements;

    for (i = 0; i < size; ++i)
    {
        if (elements[i].stringValue == element) 
        {
            *out_index = i;
            indexFound = KZ_TRUE;
            break;
        }
    }

    return indexFound;
}

kzBool kzcDynamicArrayPointerFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* elementToCompare, void** out_element)
{
    kzBool found;
    union KzcCollectionValue elementToCompareUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.pointerValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    found = kzcDynamicArrayFindIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, &valueUnion);
    
    if (found)
    {
        *out_element = (void*)valueUnion.pointerValue;
    }

    return found;
}
kzBool kzcDynamicArrayIntFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt elementToCompare, kzInt* out_element)
{
    kzBool found;
    union KzcCollectionValue elementToCompareUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.intValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    found = kzcDynamicArrayFindIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, &valueUnion);
    
    if (found)
    {
        *out_element = valueUnion.intValue;
    }

    return found;
}
kzBool kzcDynamicArrayUintFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint elementToCompare, kzUint* out_element)
{
    kzBool found;
    union KzcCollectionValue elementToCompareUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.uintValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    found = kzcDynamicArrayFindIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, &valueUnion);
    
    if (found)
    {
        *out_element = valueUnion.uintValue;
    }

    return found;
}
kzBool kzcDynamicArrayFloatFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat elementToCompare, kzFloat* out_element)
{
    kzBool found;
    union KzcCollectionValue elementToCompareUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.floatValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    found = kzcDynamicArrayFindIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, &valueUnion);
    
    if (found)
    {
        *out_element = valueUnion.floatValue;
    }

    return found;
}
kzBool kzcDynamicArrayStringFindIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString elementToCompare, kzString* out_element)
{
    kzBool found;
    union KzcCollectionValue elementToCompareUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.stringValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    found = kzcDynamicArrayFindIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, &valueUnion);
    
    if (found)
    {
        *out_element = valueUnion.stringValue;
    }

    return found;
}

kzBool kzcDynamicArrayPointerFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, const void* elementToCompare, kzUint* out_index)
{
    union KzcCollectionValue elementToCompareUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.pointerValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    return kzcDynamicArrayFindIndexIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, out_index);
}
kzBool kzcDynamicArrayIntFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzInt elementToCompare, kzUint* out_index)
{
    union KzcCollectionValue elementToCompareUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.intValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    return kzcDynamicArrayFindIndexIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, out_index);
}
kzBool kzcDynamicArrayUintFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzUint elementToCompare, kzUint* out_index)
{
    union KzcCollectionValue elementToCompareUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.uintValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    return kzcDynamicArrayFindIndexIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, out_index);
}
kzBool kzcDynamicArrayFloatFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzFloat elementToCompare, kzUint* out_index)
{
    union KzcCollectionValue elementToCompareUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.floatValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    return kzcDynamicArrayFindIndexIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, out_index);
}
kzBool kzcDynamicArrayStringFindIndexIfEqual(const struct KzcDynamicArray* dynamicArray, KzcComparatorFunction comparator, kzString elementToCompare, kzUint* out_index)
{
    union KzcCollectionValue elementToCompareUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementToCompareUnion.stringValue = elementToCompare;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    return kzcDynamicArrayFindIndexIfEqual_internal(dynamicArray, comparator, elementToCompareUnion, out_index);
}

kzsError kzcDynamicArrayPointerInsert(struct KzcDynamicArray* dynamicArray, kzUint index, const void* element)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.pointerValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    return kzcDynamicArrayInsert_internal(dynamicArray, index, elementUnion);
}
kzsError kzcDynamicArrayIntInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzInt element)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.intValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    return kzcDynamicArrayInsert_internal(dynamicArray, index, elementUnion);
}
kzsError kzcDynamicArrayUintInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzUint element)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.uintValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    return kzcDynamicArrayInsert_internal(dynamicArray, index, elementUnion);
}
kzsError kzcDynamicArrayFloatInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzFloat element)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.floatValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    return kzcDynamicArrayInsert_internal(dynamicArray, index, elementUnion);
}
kzsError kzcDynamicArrayStringInsert(struct KzcDynamicArray* dynamicArray, kzUint index, kzString element)
{
    union KzcCollectionValue elementUnion;

    kzAssert(kzcIsValidPointer(dynamicArray));

    elementUnion.stringValue = element;

#if defined(KANZI_DEBUG)
    kzcDynamicArrayRequireOrSetValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    return kzcDynamicArrayInsert_internal(dynamicArray, index, elementUnion);
}

kzsError kzcDynamicArrayPointerToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, void*** out_array)
{
    kzsError result;
    void** array;
    kzUint i;
    
    kzAssert(kzcIsValidPointer(dynamicArray));
    
#if defined(KANZI_DEBUG)
    if(dynamicArray->elementCount != 0)
    {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_POINTER);
    }
#endif

    result = kzcMemoryAllocArray(memoryManager, array, dynamicArray->elementCount, "Array from dynamic array");
    kzsErrorForward(result);
    
    for(i = 0; i < dynamicArray->elementCount; ++i)
    {
        array[i] = (void*)dynamicArray->elements[i].pointerValue;
    }
    
    *out_array = array;
    kzsSuccess();
}
kzsError kzcDynamicArrayIntToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzInt** out_array)
{
    kzsError result;
    kzInt* array;
    kzUint i;
    
    kzAssert(kzcIsValidPointer(dynamicArray));
    
#if defined(KANZI_DEBUG)
    if(dynamicArray->elementCount != 0)
    {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_INT);
    }
#endif

    result = kzcMemoryAllocArray(memoryManager, array, dynamicArray->elementCount, "Array from dynamic array");
    kzsErrorForward(result);
    
    for(i = 0; i < dynamicArray->elementCount; ++i)
    {
        array[i] = dynamicArray->elements[i].intValue;
    }
    
    *out_array = array;
    kzsSuccess();
}
kzsError kzcDynamicArrayUintToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzUint** out_array)
{
    kzsError result;
    kzUint* array;
    kzUint i;
    
    kzAssert(kzcIsValidPointer(dynamicArray));
    
#if defined(KANZI_DEBUG)
    if(dynamicArray->elementCount != 0)
    {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_UINT);
    }
#endif

    result = kzcMemoryAllocArray(memoryManager, array, dynamicArray->elementCount, "Array from dynamic array");
    kzsErrorForward(result);
    
    for(i = 0; i < dynamicArray->elementCount; ++i)
    {
        array[i] = dynamicArray->elements[i].uintValue;
    }
    
    *out_array = array;
    kzsSuccess();
}
kzsError kzcDynamicArrayFloatToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzFloat** out_array)
{
    kzsError result;
    kzFloat* array;
    kzUint i;
    
    kzAssert(kzcIsValidPointer(dynamicArray));
    
#if defined(KANZI_DEBUG)
    if(dynamicArray->elementCount != 0)
    {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_FLOAT);
    }
#endif

    result = kzcMemoryAllocArray(memoryManager, array, dynamicArray->elementCount, "Array from dynamic array");
    kzsErrorForward(result);
    
    for(i = 0; i < dynamicArray->elementCount; ++i)
    {
        array[i] = dynamicArray->elements[i].floatValue;
    }
    
    *out_array = array;
    kzsSuccess();
}
kzsError kzcDynamicArrayStringToArray(const struct KzcMemoryManager* memoryManager, const struct KzcDynamicArray* dynamicArray, kzString** out_array)
{
    kzsError result;
    kzString* array;
    kzUint i;
    
    kzAssert(kzcIsValidPointer(dynamicArray));
    
#if defined(KANZI_DEBUG)
    if(dynamicArray->elementCount != 0)
    {
        kzcDynamicArrayRequireValueType_private(dynamicArray, KZC_COLLECTION_VALUE_TYPE_STRING);
    }
#endif

    result = kzcMemoryAllocArray(memoryManager, array, dynamicArray->elementCount, "Array from dynamic array");
    kzsErrorForward(result);
    
    for(i = 0; i < dynamicArray->elementCount; ++i)
    {
        array[i] = dynamicArray->elements[i].stringValue;
    }
    
    *out_array = array;
    kzsSuccess();
}
