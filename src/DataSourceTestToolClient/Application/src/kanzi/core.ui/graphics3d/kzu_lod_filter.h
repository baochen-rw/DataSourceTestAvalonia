/**
* \file
* Specifies level of detail filter.
* Level of detail filter filters any undesired level of detail object nodes that occur.
*
* Basic functionality for LOD filter:
*
* 1) Loop through scene graph, search for LOD nodes.
* 2) Add child nodes recursively to hash map.
* 3) When applying filter
*   - If node was not found from hash map, nothing is filtered.
*   - If node was found, see the hash map value and if LOD constraint is fulfilled, nothing is filtered,
*      otherwise node is selected away.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/

#ifdef KANZI_FEATURE_3D

#ifndef KZU_LOD_FILTER_H
#define KZU_LOD_FILTER_H

#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>



/* Forward declarations */
struct KzcMemoryManager;
struct KzuObjectSource;

namespace kanzi
{
class Domain;
}

/** Structure for level of detail filter. Node's child object with ancestors is selected if it meets constraint the best. */
struct KzuLODFilter: public KzuFilterObjectSource
{
    KzuLODFilter(kanzi::Domain* domain, kanzi::string_view name);
};


/** Creates level of detail filter. */
KANZI_API KzuLODFilter* kzuLODFilterCreate(kanzi::Domain* domain, kanzi::ObjectSourceSharedPtr input, kanzi::string_view name);

#endif

#endif  // KANZI_FEATURE_3D
