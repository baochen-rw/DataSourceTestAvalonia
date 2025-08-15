/**
* \file
* Value union definitions for collections.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_VALUE_UNION_H
#define KZC_VALUE_UNION_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/wrappers/kzs_memory.hpp>


namespace kanzi
{
class Node;
class Resource;
}
struct KzuTransformedObjectNode;

/**
* Collection value types.
*/
union KzcCollectionValue
{
    kzSizeT comparisonValue; /**< Value used for comparison within this collection. Size of kzSizeT is the size of a pointer. */

    const void* pointerValue;   /**< Pointer value. */
    kzString stringValue; /**< String value. */
    kzInt intValue;       /**< Integer value. */
    kzUint uintValue;     /**< Unsigned integer value. */
    kzFloat floatValue;   /**< Float value. */

#ifdef KANZI_DEBUG
    /*
     * The following members of the union are only for debugging purposes to allow easier visualization of the items in the collection.
     * Engine or applications are not allowed to use these.
     */
    kanzi::Node* pointerObjectNode; /**< Pointer value as an object node. DO NOT access this field. */
    KzuTransformedObjectNode* transformedNode; /**< Pointer value as a transformed node. DO NOT access this field. */
    kanzi::Resource* pointerResource; /**< Pointer value as a resource. DO NOT access this field. */
#endif
    KzcCollectionValue() : pointerValue(0) {}
};


/**
* Value type identifiers.
*/
enum KzcCollectionValueType
{
    KZC_COLLECTION_VALUE_TYPE_NOT_ASSIGNED = 0, /**< No value type. */
    KZC_COLLECTION_VALUE_TYPE_INT = 1,          /**< Integer value. */
    KZC_COLLECTION_VALUE_TYPE_UINT = 2,         /**< Unsigned integer value. */
    KZC_COLLECTION_VALUE_TYPE_FLOAT = 4,        /**< Float value */
    KZC_COLLECTION_VALUE_TYPE_POINTER = 8,      /**< Pointer value. */
    KZC_COLLECTION_VALUE_TYPE_STRING = 16       /**< String value (kzString). */
};


#endif
