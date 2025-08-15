/**
* \file
* Accessor implementations for hash map. To be included in kzc_hash_map.c
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/


kzsError kzcHashMapPointerPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapPointerPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapPointerPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapPointerPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapPointerPutString(struct KzcHashMap* hashMap, const void* key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapIntPutPointer(struct KzcHashMap* hashMap, kzInt key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapIntPutInt(struct KzcHashMap* hashMap, kzInt key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapIntPutUint(struct KzcHashMap* hashMap, kzInt key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapIntPutFloat(struct KzcHashMap* hashMap, kzInt key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapIntPutString(struct KzcHashMap* hashMap, kzInt key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapUintPutPointer(struct KzcHashMap* hashMap, kzUint key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapUintPutInt(struct KzcHashMap* hashMap, kzUint key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapUintPutUint(struct KzcHashMap* hashMap, kzUint key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapUintPutFloat(struct KzcHashMap* hashMap, kzUint key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapUintPutString(struct KzcHashMap* hashMap, kzUint key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapFloatPutPointer(struct KzcHashMap* hashMap, kzFloat key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapFloatPutInt(struct KzcHashMap* hashMap, kzFloat key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapFloatPutUint(struct KzcHashMap* hashMap, kzFloat key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapFloatPutFloat(struct KzcHashMap* hashMap, kzFloat key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapFloatPutString(struct KzcHashMap* hashMap, kzFloat key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapPutWithHash_internal(hashMap, hashCode, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapStringPutPointer(struct KzcHashMap* hashMap, kzString key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapStringPutInt(struct KzcHashMap* hashMap, kzString key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapStringPutUint(struct KzcHashMap* hashMap, kzString key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapStringPutFloat(struct KzcHashMap* hashMap, kzString key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapStringPutString(struct KzcHashMap* hashMap, kzString key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapCustomPutPointer(struct KzcHashMap* hashMap, const void* key, const void* value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.pointerValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapCustomPutInt(struct KzcHashMap* hashMap, const void* key, kzInt value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.intValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapCustomPutUint(struct KzcHashMap* hashMap, const void* key, kzUint value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.uintValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapCustomPutFloat(struct KzcHashMap* hashMap, const void* key, kzFloat value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.floatValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}

kzsError kzcHashMapCustomPutString(struct KzcHashMap* hashMap, const void* key, kzString value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    valueUnion.stringValue = value;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    kzcHashMapRequireOrSetValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);

    {
        result = kzcHashMapPut_internal(hashMap, keyUnion, valueUnion);
        kzsErrorForward(result);
    }
 
    kzsSuccess();
}


kzBool kzcHashMapPointerGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapPointerGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapPointerGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapPointerGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapPointerGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}

kzBool kzcHashMapIntGetPointer(const struct KzcHashMap* hashMap, kzInt key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapIntGetInt(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapIntGetUint(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapIntGetFloat(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapIntGetString(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}

kzBool kzcHashMapUintGetPointer(const struct KzcHashMap* hashMap, kzUint key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapUintGetInt(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapUintGetUint(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapUintGetFloat(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapUintGetString(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}

kzBool kzcHashMapFloatGetPointer(const struct KzcHashMap* hashMap, kzFloat key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapFloatGetInt(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapFloatGetUint(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapFloatGetFloat(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapFloatGetString(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}

kzBool kzcHashMapStringGetPointer(const struct KzcHashMap* hashMap, kzString key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapStringGetInt(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapStringGetUint(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapStringGetFloat(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapStringGetString(const struct KzcHashMap* hashMap, kzString key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}

kzBool kzcHashMapCustomGetPointer(const struct KzcHashMap* hashMap, const void* key, void** out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.pointerValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
        }
#endif
    }

    *out_value = (void*)valueUnion.pointerValue;
    return result;
}

kzBool kzcHashMapCustomGetInt(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.intValue = 0;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
        }
#endif
    }

    *out_value = valueUnion.intValue;
    return result;
}

kzBool kzcHashMapCustomGetUint(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.uintValue = 0U;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
        }
#endif
    }

    *out_value = valueUnion.uintValue;
    return result;
}

kzBool kzcHashMapCustomGetFloat(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.floatValue = 0.0f;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
        }
#endif
    }

    *out_value = valueUnion.floatValue;
    return result;
}

kzBool kzcHashMapCustomGetString(const struct KzcHashMap* hashMap, const void* key, kzString* out_value)
{
    kzBool result;
    union KzcCollectionValue valueUnion;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGet_internal(hashMap, keyUnion, &valueUnion);
        if(!result)
        {
            valueUnion.stringValue = KZ_NULL;
        }
#if defined(KANZI_DEBUG)
        else
        {
            kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
        }
#endif
    }

    *out_value = valueUnion.stringValue;
    return result;
}


kzBool kzcHashMapPointerFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        returnValue = kzcHashMapFindWithHash_internal(hashMap, hashCode, keyUnion, out_iterator);
    }

    return returnValue;
}

kzBool kzcHashMapIntFind(const struct KzcHashMap* hashMap, kzInt key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapFindWithHash_internal(hashMap, hashCode, keyUnion, out_iterator);
    }

    return returnValue;
}

kzBool kzcHashMapUintFind(const struct KzcHashMap* hashMap, kzUint key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapFindWithHash_internal(hashMap, hashCode, keyUnion, out_iterator);
    }

    return returnValue;
}

kzBool kzcHashMapFloatFind(const struct KzcHashMap* hashMap, kzFloat key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapFindWithHash_internal(hashMap, hashCode, keyUnion, out_iterator);
    }

    return returnValue;
}

kzBool kzcHashMapStringFind(const struct KzcHashMap* hashMap, kzString key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    
    {
        returnValue = kzcHashMapFind_internal(hashMap, keyUnion, out_iterator);
    }

    return returnValue;
}

kzBool kzcHashMapCustomFind(const struct KzcHashMap* hashMap, const void* key, struct KzcHashMapIterator* out_iterator)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    
    {
        returnValue = kzcHashMapFind_internal(hashMap, keyUnion, out_iterator);
    }

    return returnValue;
}


kzsError kzcHashMapPointerRemove(struct KzcHashMap* hashMap, const void* key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapRemoveWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapIntRemove(struct KzcHashMap* hashMap, kzInt key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapUintRemove(struct KzcHashMap* hashMap, kzUint key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapFloatRemove(struct KzcHashMap* hashMap, kzFloat key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapStringRemove(struct KzcHashMap* hashMap, kzString key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    
    {
        result = kzcHashMapRemove_internal(hashMap, keyUnion);
    }

    return result;
}

kzsError kzcHashMapCustomRemove(struct KzcHashMap* hashMap, const void* key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    
    {
        result = kzcHashMapRemove_internal(hashMap, keyUnion);
    }

    return result;
}


kzsError kzcHashMapPointerRemoveIfExists(struct KzcHashMap* hashMap, const void* key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapRemoveIfExistsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapIntRemoveIfExists(struct KzcHashMap* hashMap, kzInt key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveIfExistsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapUintRemoveIfExists(struct KzcHashMap* hashMap, kzUint key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveIfExistsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapFloatRemoveIfExists(struct KzcHashMap* hashMap, kzFloat key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif
    
    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapRemoveIfExistsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return result;
}

kzsError kzcHashMapStringRemoveIfExists(struct KzcHashMap* hashMap, kzString key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif
    
    {
        result = kzcHashMapRemoveIfExists_internal(hashMap, keyUnion);
    }

    return result;
}

kzsError kzcHashMapCustomRemoveIfExists(struct KzcHashMap* hashMap, const void* key)
{
    kzsError result;
    union KzcCollectionValue keyUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif
    
    {
        result = kzcHashMapRemoveIfExists_internal(hashMap, keyUnion);
    }

    return result;
}


const void* kzcHashMapPointerGetStoredKey(const struct KzcHashMap* hashMap, const void* key)
{
    union KzcCollectionValue keyUnion;
    const void* returnValue;

    kzAssert(kzcIsValidPointer(hashMap));
    
    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        returnValue = kzcHashMapGetStoredKeyWithHash_internal(hashMap, hashCode, keyUnion).pointerValue;
    }

    return returnValue;
}

const void* kzcHashMapCustomGetStoredKey(const struct KzcHashMap* hashMap, const void* key)
{
    union KzcCollectionValue keyUnion;
    const void* returnValue;

    kzAssert(kzcIsValidPointer(hashMap));
    
    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        returnValue = kzcHashMapGetStoredKey_internal(hashMap, keyUnion).pointerValue;
    }

    return returnValue;
}


kzBool kzcHashMapPointerContains(const struct KzcHashMap* hashMap, const void* key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        returnValue = kzcHashMapContainsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return returnValue;
}

kzBool kzcHashMapIntContains(const struct KzcHashMap* hashMap, kzInt key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapContainsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return returnValue;
}

kzBool kzcHashMapUintContains(const struct KzcHashMap* hashMap, kzUint key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapContainsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return returnValue;
}

kzBool kzcHashMapFloatContains(const struct KzcHashMap* hashMap, kzFloat key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        returnValue = kzcHashMapContainsWithHash_internal(hashMap, hashCode, keyUnion);
    }

    return returnValue;
}

kzBool kzcHashMapStringContains(const struct KzcHashMap* hashMap, kzString key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        returnValue = kzcHashMapContains_internal(hashMap, keyUnion);
    }

    return returnValue;
}

kzBool kzcHashMapCustomContains(const struct KzcHashMap* hashMap, const void* key)
{
    union KzcCollectionValue keyUnion;
    kzBool returnValue;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        returnValue = kzcHashMapContains_internal(hashMap, keyUnion);
    }

    return returnValue;
}


kzsError kzcHashMapPointerGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapPointerGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapPointerGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapPointerGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapPointerGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromPointerUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}

kzsError kzcHashMapIntGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzInt key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapIntGetIntOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapIntGetUintOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapIntGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapIntGetStringOrThrowError(const struct KzcHashMap* hashMap, kzInt key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.intValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}

kzsError kzcHashMapUintGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzUint key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapUintGetIntOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapUintGetUintOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapUintGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapUintGetStringOrThrowError(const struct KzcHashMap* hashMap, kzUint key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.uintValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}

kzsError kzcHashMapFloatGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapFloatGetIntOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapFloatGetUintOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapFloatGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapFloatGetStringOrThrowError(const struct KzcHashMap* hashMap, kzFloat key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.floatValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    {
        kzU32 hashCode = kzcHashCodeFromUint(keyUnion.uintValue);

        result = kzcHashMapGetOrThrowErrorWithHash_internal(hashMap, hashCode, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}

kzsError kzcHashMapStringGetPointerOrThrowError(const struct KzcHashMap* hashMap, kzString key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapStringGetIntOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapStringGetUintOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapStringGetFloatOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapStringGetStringOrThrowError(const struct KzcHashMap* hashMap, kzString key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.stringValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}

kzsError kzcHashMapCustomGetPointerOrThrowError(const struct KzcHashMap* hashMap, const void* key, void** out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif
    
    *out_value = (void*)valueUnion.pointerValue;
    kzsSuccess();
}

kzsError kzcHashMapCustomGetIntOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzInt* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_INT);
#endif
    
    *out_value = valueUnion.intValue;
    kzsSuccess();
}

kzsError kzcHashMapCustomGetUintOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzUint* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif
    
    *out_value = valueUnion.uintValue;
    kzsSuccess();
}

kzsError kzcHashMapCustomGetFloatOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzFloat* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif
    
    *out_value = valueUnion.floatValue;
    kzsSuccess();
}

kzsError kzcHashMapCustomGetStringOrThrowError(const struct KzcHashMap* hashMap, const void* key, kzString* out_value)
{
    kzsError result;
    union KzcCollectionValue keyUnion;
    union KzcCollectionValue valueUnion;

    kzAssert(kzcIsValidPointer(hashMap));

    keyUnion.comparisonValue = 0;
    keyUnion.pointerValue = key;
        
#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(hashMap, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    {
        result = kzcHashMapGetOrThrowError_internal(hashMap, keyUnion, &valueUnion);
        kzsErrorForward(result);
    }

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(hashMap, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif
    
    *out_value = valueUnion.stringValue;
    kzsSuccess();
}


const void* kzcHashMapIteratorPointerGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_POINTER);
#endif

    return keyUnion.pointerValue;
}

kzInt kzcHashMapIteratorIntGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_INT);
#endif

    return keyUnion.intValue;
}

kzUint kzcHashMapIteratorUintGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_UINT);
#endif

    return keyUnion.uintValue;
}

kzFloat kzcHashMapIteratorFloatGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_FLOAT);
#endif

    return keyUnion.floatValue;
}

kzString kzcHashMapIteratorStringGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_STRING);
#endif

    return keyUnion.stringValue;
}

const void* kzcHashMapIteratorCustomGetKey_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue keyUnion = kzcHashMapIteratorGetKey_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireKeyType_internal(iterator->map_private, KZC_HASH_MAP_KEY_TYPE_CUSTOM);
#endif

    return keyUnion.pointerValue;
}


void* kzcHashMapIteratorGetPointerValue_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue valueUnion = kzcHashMapIteratorGetValue_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    return (void*)valueUnion.pointerValue;
}

kzInt kzcHashMapIteratorGetIntValue_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue valueUnion = kzcHashMapIteratorGetValue_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    return valueUnion.intValue;
}

kzUint kzcHashMapIteratorGetUintValue_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue valueUnion = kzcHashMapIteratorGetValue_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    return valueUnion.uintValue;
}

kzFloat kzcHashMapIteratorGetFloatValue_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue valueUnion = kzcHashMapIteratorGetValue_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    return valueUnion.floatValue;
}

kzString kzcHashMapIteratorGetStringValue_private(const struct KzcHashMapIterator* iterator)
{
    union KzcCollectionValue valueUnion = kzcHashMapIteratorGetValue_internal(iterator);

#if defined(KANZI_DEBUG)
    kzcHashMapRequireValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    return valueUnion.stringValue;
}


void kzcHashMapIteratorSetPointerValue_private(const struct KzcHashMapIterator* iterator, const void* value)
{
    union KzcCollectionValue valueUnion;
    valueUnion.pointerValue = value;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireOrSetValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_POINTER);
#endif

    kzcHashMapIteratorSetValue_internal(iterator, valueUnion);
}

void kzcHashMapIteratorSetIntValue_private(const struct KzcHashMapIterator* iterator, kzInt value)
{
    union KzcCollectionValue valueUnion;
    valueUnion.intValue = value;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireOrSetValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_INT);
#endif

    kzcHashMapIteratorSetValue_internal(iterator, valueUnion);
}

void kzcHashMapIteratorSetUintValue_private(const struct KzcHashMapIterator* iterator, kzUint value)
{
    union KzcCollectionValue valueUnion;
    valueUnion.uintValue = value;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireOrSetValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_UINT);
#endif

    kzcHashMapIteratorSetValue_internal(iterator, valueUnion);
}

void kzcHashMapIteratorSetFloatValue_private(const struct KzcHashMapIterator* iterator, kzFloat value)
{
    union KzcCollectionValue valueUnion;
    valueUnion.floatValue = value;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireOrSetValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_FLOAT);
#endif

    kzcHashMapIteratorSetValue_internal(iterator, valueUnion);
}

void kzcHashMapIteratorSetStringValue_private(const struct KzcHashMapIterator* iterator, kzString value)
{
    union KzcCollectionValue valueUnion;
    valueUnion.stringValue = value;
    
#if defined(KANZI_DEBUG)
    kzcHashMapRequireOrSetValueType_internal(iterator->map_private, KZC_COLLECTION_VALUE_TYPE_STRING);
#endif

    kzcHashMapIteratorSetValue_internal(iterator, valueUnion);
}

