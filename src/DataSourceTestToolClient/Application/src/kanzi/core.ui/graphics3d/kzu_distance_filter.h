#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies distance filter.
* Distance filter accepts or rejects objects that are within given range from specified object.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_DISTANCE_FILTER_H
#define KZU_DISTANCE_FILTER_H


#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcMemoryManager;

namespace kanzi
{

class Node3D;
class Domain;

}

struct KzuObjectSource;


/**
 * Creates distance filter. All objects that are nearer than given maxDistance from given object are either
 * accepted or rejected depending on whether isExclusive is set or not.
 */
KANZI_API kzsError kzuDistanceFilterCreate(kanzi::Domain* domain,
                                 kanzi::ObjectSourceSharedPtr input, kanzi::string_view name, kanzi::Node3D* object,
                                 const kzFloat maxDistance, kzBool isExclusive, struct KzuObjectSource** out_objectSource);





#endif

#endif
