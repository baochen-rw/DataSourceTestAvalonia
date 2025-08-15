#ifdef KANZI_FEATURE_3D

/**
* \file
* Object source. Object source that can be coupled with filters.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SOURCE_H
#define KZU_OBJECT_SOURCE_H


#include "kzu_object_source_base.h"
#include "kzu_object_source_common.h"

#include <kanzi/core/legacy/util/collection/kzc_comparator.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuSortObjectSource;
struct KzuTransformedObjectNode;

namespace kanzi
{
class Domain;
class TransformedScene3D;
}


#define KZU_OBJECT_SOURCE_RUNTIME_CHANGE_FLAG_LOD_APPLY_REQUIRED 1 /**< Change flag specifying the LOD Apply is required. */


/**
 * \struct KzuObjectSourceCache
 * Storage for object source cache data.
 */
struct KzuObjectSourceCache;

/**
 * \struct KzuObjectSourceRuntimeData
 * Structure passed as parameter to object source reset.
 */
struct KzuObjectSourceRuntimeData;


/** Creates an object source, which combines several object sources together. */
KANZI_API kzsError kzuCombinerObjectSourceCreate(kanzi::Domain* domain, kanzi::string_view name, struct KzuObjectSource** out_objectSource);


/** Loads combiner object source from KZB. */
kzsError kzuCombinerObjectSourceLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Gets transformed object node from object source. out_objects is filled with transformed object nodes. */
KANZI_API kzsError kzuObjectSourceFetchGraph(const struct KzuObjectSource* objectSource, const struct KzuObjectSourceRuntimeData* runtimeData,
                                   const struct KzuTransformedObjectNode* camera, struct KzcDynamicArray** out_objects);

/** Checks if the object source is an object set filter. */
KANZI_API kzBool kzuObjectSourceIsFilter(const struct KzuObjectSource* objectSource);

/** Sets input for object source. In case of root object source does nothing. Combiner object source not supported. */
KANZI_API void kzuObjectSourceSetInput(KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr inputObjectSource);
/** Gets an input from object source, KZ_NULL if not specified. */
KANZI_API struct KzuObjectSource* kzuObjectSourceGetInput(const struct KzuObjectSource* objectSource);

/** Creates an object for object source reset data. */
KANZI_API kzsError kzuObjectSourceRuntimeDataCreate(const struct KzcMemoryManager* memoryManager, kanzi::TransformedScene3D* transformedScene,
                                            struct KzuObjectSourceRuntimeData** out_runtimeData);
/** Sets change flag for the object source runtime data. */
KANZI_API void kzuObjectSourceRuntimeDataSetChangeFlag(struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);
/** Clears object source runtime data change flag. */
KANZI_API void kzuObjectSourceRuntimeDataClearChangeFlag(struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);
/** Returns if specific change flag is set for object source runtime data. */
KANZI_API kzBool kzuObjectSourceRuntimeDataIsChangeFlagSet(const struct KzuObjectSourceRuntimeData* runtimeData, kzU32 flag);

/** Resets object source's runtime data, i.e. cache is cleaned. */
KANZI_API kzsError kzuObjectSourceResetRuntimeOutputData(const struct KzuObjectSource* objectSource, const struct KzuObjectSourceRuntimeData* objectSourceRuntimeData);



#endif

#endif
