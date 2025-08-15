#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies object set filter.
* Object set filter accepts or rejects all specified objects and all their ancestors.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SET_FILTER_H
#define KZU_OBJECT_SET_FILTER_H

#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;

namespace kanzi
{
class Domain;
class Node;
}


/** Creates object set filter. */
KANZI_API kzsError kzuObjectSetFilterCreate(kanzi::Domain* domain, kanzi::string_view name, struct KzuObjectSource** out_objectSource);

/** Initializes an object set filter. */
KANZI_API kzsError kzuObjectSetFilterInitialize(struct KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr input, kzBool isExclusive);

/** Adds objects to object set filter. */
KANZI_API kzsError kzuObjectSetFilterAddObjects(const struct KzuObjectSource* objectSource, kzUint objectCount, kanzi::Node* const* objects);

/** Adds new object to object set filter. */
KANZI_API kzsError kzuObjectSetFilterAddObject(const struct KzuObjectSource* objectSource, const kanzi::Node* objectNode);

/** Returns KZ_TRUE if object set contains given object. */
KANZI_API kzBool kzuObjectSetFilterContainsObject(const struct KzuObjectSource* objectSource, const kanzi::Node* objectNode);

/** Removes an object from an object set filter. */
KANZI_API kzsError kzuObjectSetFilterRemoveObject(const struct KzuObjectSource* objectSource, const kanzi::Node* objectNode);

/** Tells if objects source if the object set filter. */
KANZI_API kzBool kzuObjectSourceIsObjectSetFilter(const struct KzuObjectSource* objectSource);

/** Returns collections of objects of object source. */
KANZI_API struct KzcHashSet* kzuObjectSetFilterGetObjects_private(const struct KzuObjectSource* objectSource);





#endif

#endif
