#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies sort object source for material type.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_SORT_OBJECT_SOURCE_H
#define KZU_SORT_OBJECT_SOURCE_H


#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuSortObjectSource;

namespace kanzi
{
class Domain;
}


/** Creates an object source which performs sorting. */
KANZI_API KzuSortObjectSource* kzuSortObjectSourceCreate(kanzi::Domain* domain, kanzi::string_view name);

KANZI_API KzuSortObjectSource* kzuSortByShaderObjectSourceCreate(kanzi::Domain* domain, kanzi::ObjectSourceSharedPtr input, kanzi::string_view name);

/** Creates an object source which performs sorting by object view z value. */
KzuSortObjectSource* kzuSortByZObjectSourceCreate_internal(kanzi::Domain* domain, kanzi::ObjectSourceSharedPtr input, kanzi::string_view name, kzBool frontToBack);

/** Creates an object source which performs sorting by object view z value. */
KANZI_API kanzi::SortObjectSourceSharedPtr kzuSortByZObjectSourceCreate(kanzi::Domain* domain, kanzi::ObjectSourceSharedPtr input, kanzi::string_view name, bool frontToBack);


/** Loads sort object source from KZB. */
kzsError kzuSortObjectSourceLoadFromKZB(KzuObjectSource* objectSource, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);





#endif

#endif
