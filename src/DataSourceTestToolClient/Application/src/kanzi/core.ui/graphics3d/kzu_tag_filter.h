#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies tag filter.
* Tag filter is used to collect all objects that have been assigned a certain tag.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TAG_FILTER_H
#define KZU_TAG_FILTER_H

#include "kzu_object_source_base.h"

#include <kanzi/core.ui/domain/domain.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuTagFilter;

namespace kanzi
{
class Domain;
typedef shared_ptr<KzuTagFilter> TagFilterSharedPtr;
}

/** Structure for tag filter. */
struct KANZI_API KzuTagFilter: public KzuFilterObjectSource
{
    explicit KzuTagFilter(kanzi::Domain *domain, kanzi::string_view name);

    virtual ~KzuTagFilter() KZ_OVERRIDE;


    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);

    kanzi::vector<kanzi::AbstractPropertyType> m_inclusiveTags;
    kanzi::vector<kanzi::AbstractPropertyType> m_exclusiveTags;
};

/** Creates tag filter. */
KANZI_API KzuTagFilter* kzuTagFilterCreate(const struct KzcMemoryManager* memoryManager, kanzi::Domain* domain, kzString name);

/** Loads a tag filter from KZB. */
kzsError kzuTagFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Tells if object source is tag filter. */
KANZI_API kzBool kzuObjectSourceIsTagFilter(const struct KzuObjectSource* objectSource);

/** Initializes a tag filter. */
KANZI_API kzsError kzuTagFilterInitialize(struct KzuObjectSource* objectSource, kanzi::ObjectSourceSharedPtr  input,
                                kanzi::AbstractPropertyType const* inclusiveTags, kzUint inclusiveCount,
                                kanzi::AbstractPropertyType const* exclusiveTags, kzUint exclusiveCount,
                                kzBool isExclusive);


/** Converts object source to tag filter. */
struct KzuTagFilter* kzuTagFilterFromObjectSource_private(struct KzuObjectSource* objectSource);





#endif

#endif
