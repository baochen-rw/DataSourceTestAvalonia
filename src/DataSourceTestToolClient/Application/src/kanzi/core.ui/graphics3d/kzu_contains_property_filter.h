#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies contains property filter.
* Contains property filter accepts or rejects an object if it contains a property of specified type.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_CONTAINS_PROPERTY_FILTER_H
#define KZU_CONTAINS_PROPERTY_FILTER_H

#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuContainsPropertyFilter;

namespace kanzi
{
class Domain;
typedef shared_ptr<KzuContainsPropertyFilter> ContainsPropertyFilterSharedPtr;
}

/** Structure for property filter. */
struct KANZI_API KzuContainsPropertyFilter : public KzuFilterObjectSource
{
    explicit KzuContainsPropertyFilter(kanzi::Domain* domain, kanzi::string_view name);

    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);


    kanzi::AbstractPropertyType propertyType; /**< Property type is used as condition for this filter. */
};

/** Creates property filter. */
KANZI_API kzsError kzuContainsPropertyFilterCreate(kanzi::Domain* domain, kanzi::string_view name, struct KzuObjectSource** out_objectSource);

/** Loads a contain property filter from KZB. */
kzsError kzuContainsPropertyFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes a contains property filter. */
KANZI_API kzsError kzuContainsPropertyFilterInitialize(struct KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr input,
                                             kanzi::AbstractPropertyType propertyType, kzBool isExclusive);

/** Tells if object source is the contains property filter. */
KANZI_API kzBool kzuObjectSourceIsContainsPropertyFilter(const struct KzuObjectSource* objectSource);

/** Gets property type of the filter. */
KANZI_API kanzi::AbstractPropertyType kzuContainsPropertyFilterGetPropertyType(struct KzuObjectSource* objectSource);

/** Sets property type of the filter. */
KANZI_API void kzuContainsPropertyFilterSetPropertyType(struct KzuObjectSource* objectSource, kanzi::AbstractPropertyType propertyType);


#endif

#endif
