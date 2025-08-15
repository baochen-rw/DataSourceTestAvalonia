// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_TRANSFORMED_OBJECT_H
#define KZU_TRANSFORMED_OBJECT_H


#include <kanzi/core/legacy/util/collection/kzc_dynamic_array.hpp>
#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector2.hpp>
#include <kanzi/core/math/vector3.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{
class Node3D;
class Box;
}


/* Forward declaration structures. */
struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzcVector2;
struct KzcVector3;


/** 
* \struct KzuTransformedObjectNode
* Structure for transformed object node that contains reference to original object in scene graph and transformation
* in calculated world coordinates (affected by hierarchy).
*/
struct KzuTransformedObjectNode;


/** Creates new Transformed object node from regular scene graph object. Saves the reference to original scene graph object and copies the matrix data. */
KANZI_API void kzuTransformedObjectNodeCreate(const KzcMemoryManager* memoryManager, kanzi::Node3D* object,
                                              KzuTransformedObjectNode* parent, bool parentTransformChanged,
                                              bool visible, KzuTransformedObjectNode* instantiatorParentNode, bool* out_transformChanged, KzuTransformedObjectNode** out_object);

/** Adds a child transformed object for parent. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedObjectNodeGetParent(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Adds a child transformed object for parent. */
KANZI_API kzsError kzuTransformedObjectNodeAddChildNode(struct KzuTransformedObjectNode* parentObject,
                                              struct KzuTransformedObjectNode* childNode);

/** Gets instantiator from given node. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedObjectNodeGetInstantiator3DNode(const struct KzuTransformedObjectNode* node);

/** Returns a children of transformed object node as iterator (list of KzuTransformedObjectNode:s). */
KANZI_API struct KzcDynamicArrayIterator kzuTransformedObjectNodeGetChildren(const struct KzuTransformedObjectNode* transformedObjectNode);

/** Returns a KzuObjectNode owned by transformed object node. */
KANZI_API kanzi::Node3D* kzuTransformedObjectNodeGetObjectNode(const struct KzuTransformedObjectNode* transformedObjectNode);
/** Finds transformed object node from destination object node's direct children. NULL if nothing was found. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedObjectNodeFindChildObjectNode(const struct KzuTransformedObjectNode* transformedObjectNode,
                                                                             const kanzi::Node3D* objectToFind);

/** Gets bounding volume union from transformed object node and its children. */
KANZI_API kzsError kzuTransformedObjectNodeGetBoundingVolumeUnionWorld(const struct KzuTransformedObjectNode* transformedObjectNode, kanzi::Box& out_volume);
/** Gets bounding volume union from transformed object node without children taken into account. */
KANZI_API kzsError kzuTransformedObjectNodeGetBoundingVolumeWorld(const struct KzuTransformedObjectNode* transformedObjectNode, kanzi::Box& out_volume);

/** Sets the world matrix for transformed object node. */
KANZI_API void kzuTransformedObjectNodeSetMatrix(struct KzuTransformedObjectNode* transformedObjectNode, const struct KzcMatrix4x4* matrix);
/** Returns the world matrix of transformed object node. */
KANZI_API KzcMatrix4x4 kzuTransformedObjectNodeGetMatrix(const struct KzuTransformedObjectNode* transformedObjectNode);


/** Returns a position of this transformed object node */
KANZI_API void kzuTransformedObjectNodeGetPosition(const struct KzuTransformedObjectNode* transformedObjectNode, struct KzcVector3* out_position);

KANZI_API kanzi::Vector3 kzuTransformedObjectNodeGetPosition(const struct KzuTransformedObjectNode* transformedObjectNode);

/** Finds transformed object node from object list. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedObjectListFindObject(const struct KzcDynamicArray* objectList,
                                                                              const kanzi::Node3D* objectToFind);

/** Returns visibility of a transformed object node. */
KANZI_API kzBool kzuTransformedObjectNodeIsVisible(const struct KzuTransformedObjectNode* transformedObjectNode);





#endif

#endif
