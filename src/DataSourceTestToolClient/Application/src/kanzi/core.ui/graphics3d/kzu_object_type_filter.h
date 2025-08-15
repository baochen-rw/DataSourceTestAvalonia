#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies object type filter. This filter accepts or rejects specific types of objects.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_TYPE_FILTER_H
#define KZU_OBJECT_TYPE_FILTER_H


#include "kzu_object_source_base.h"

#include <kanzi/core.ui/node/node.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/// Object type identifier for all renderable object types.
extern const KANZI_API void* const KZU_OBJECT_TYPE_RENDERABLE;


// Forward declarations
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuObjectTypeFilter;

namespace kanzi
{
class Domain;
typedef shared_ptr<KzuObjectTypeFilter> ObjectTypeFilterSharedPtr;
}


/// Structure for object type filter.
struct KANZI_API KzuObjectTypeFilter: public KzuFilterObjectSource
{
    explicit KzuObjectTypeFilter(kanzi::Domain *domain, kanzi::string_view name);

    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);


    const void* type; /**< Object type. */
};

/// Creates an object type filter.
KANZI_API KzuObjectTypeFilter* kzuObjectTypeFilterCreate(kanzi::Domain* domain, kanzi::string_view name);

/// Loads an object type filter from KZB.
kzsError kzuObjectTypeFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/// Initializes an object type filter.
KANZI_API kzsError kzuObjectTypeFilterInitialize(struct KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr input,
                                       const void* objectType, kzBool isExclusive);





#endif

#endif

