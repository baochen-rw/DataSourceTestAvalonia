/**
* \file
* Accessor implementations for hash set. To be included in kzc_hash_set.c
* Do not change this file, as the file is generated automatically.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/


kzsError kzcHashSetPointerAdd(struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapPointerPutPointer(hashSet->hashMap, value, value);
}

kzsError kzcHashSetIntAdd(struct KzcHashSet* hashSet, kzInt value)
{
    return kzcHashMapIntPutInt(hashSet->hashMap, value, value);
}

kzsError kzcHashSetUintAdd(struct KzcHashSet* hashSet, kzUint value)
{
    return kzcHashMapUintPutUint(hashSet->hashMap, value, value);
}

kzsError kzcHashSetFloatAdd(struct KzcHashSet* hashSet, kzFloat value)
{
    return kzcHashMapFloatPutFloat(hashSet->hashMap, value, value);
}

kzsError kzcHashSetStringAdd(struct KzcHashSet* hashSet, kzString value)
{
    return kzcHashMapStringPutString(hashSet->hashMap, value, value);
}

kzsError kzcHashSetCustomAdd(struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapCustomPutPointer(hashSet->hashMap, value, value);
}


kzsError kzcHashSetPointerRemove(struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapPointerRemove(hashSet->hashMap, value);
}

kzsError kzcHashSetIntRemove(struct KzcHashSet* hashSet, kzInt value)
{
    return kzcHashMapIntRemove(hashSet->hashMap, value);
}

kzsError kzcHashSetUintRemove(struct KzcHashSet* hashSet, kzUint value)
{
    return kzcHashMapUintRemove(hashSet->hashMap, value);
}

kzsError kzcHashSetFloatRemove(struct KzcHashSet* hashSet, kzFloat value)
{
    return kzcHashMapFloatRemove(hashSet->hashMap, value);
}

kzsError kzcHashSetStringRemove(struct KzcHashSet* hashSet, kzString value)
{
    return kzcHashMapStringRemove(hashSet->hashMap, value);
}

kzsError kzcHashSetCustomRemove(struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapCustomRemove(hashSet->hashMap, value);
}


void* kzcHashSetPointerGetStoredValue(const struct KzcHashSet* hashSet, const void* value)
{
    return (void*)kzcHashMapPointerGetStoredKey(hashSet->hashMap, value);
}

void* kzcHashSetCustomGetStoredValue(const struct KzcHashSet* hashSet, const void* value)
{
    return (void*)kzcHashMapCustomGetStoredKey(hashSet->hashMap, value);
}


kzBool kzcHashSetPointerContains(const struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapPointerContains(hashSet->hashMap, value);
}

kzBool kzcHashSetIntContains(const struct KzcHashSet* hashSet, kzInt value)
{
    return kzcHashMapIntContains(hashSet->hashMap, value);
}

kzBool kzcHashSetUintContains(const struct KzcHashSet* hashSet, kzUint value)
{
    return kzcHashMapUintContains(hashSet->hashMap, value);
}

kzBool kzcHashSetFloatContains(const struct KzcHashSet* hashSet, kzFloat value)
{
    return kzcHashMapFloatContains(hashSet->hashMap, value);
}

kzBool kzcHashSetStringContains(const struct KzcHashSet* hashSet, kzString value)
{
    return kzcHashMapStringContains(hashSet->hashMap, value);
}

kzBool kzcHashSetCustomContains(const struct KzcHashSet* hashSet, const void* value)
{
    return kzcHashMapCustomContains(hashSet->hashMap, value);
}

