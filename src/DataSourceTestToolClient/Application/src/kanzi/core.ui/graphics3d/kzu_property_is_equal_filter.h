/**
* \file
* Specifies property is equal filter.
* Filter that compares object property default value to 
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_IS_EQUAL_FILTER_H
#define KZU_PROPERTY_IS_EQUAL_FILTER_H


#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>



/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuPropertyIsEqualFilter;

namespace kanzi
{
class Domain;
typedef shared_ptr<KzuPropertyIsEqualFilter> PropertyIsEqualFilterSharedPtr;
}


/** Structure for property is equal filter. */
struct KANZI_API KzuPropertyIsEqualFilter : public KzuFilterObjectSource
{
    explicit KzuPropertyIsEqualFilter(kanzi::Domain* domain, kanzi::string_view name);

    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);

    kanzi::AbstractPropertyType propertyType; /**< Property type is used as condition for this filter. */
};

/** Creates property is equal filter. */
KANZI_API kzsError kzuPropertyIsEqualFilterCreate(const struct KzcMemoryManager* memoryManager, kanzi::Domain* domain,
                                        kzString name, struct KzuObjectSource** out_objectSource);

/** Loads a property is equal filter from KZB. */
KANZI_API kzsError kzuPropertyIsEqualFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes a property is equal filter. 
 * \param propertyType Property type that is used in comparison. Compared property is the one that the filter contains in property manager.
 */
KANZI_API kzsError kzPropertyIsEqualFilterInitialize(struct KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr input,
                                           struct KzuPropertyManager* propertyManager, kanzi::AbstractPropertyType propertyType, kzBool isExclusive);





#endif
