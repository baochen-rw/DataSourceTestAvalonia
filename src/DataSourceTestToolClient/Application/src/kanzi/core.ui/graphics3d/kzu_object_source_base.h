/**
* \file
* Object source private members.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_SOURCE_BASE_H
#define KZU_OBJECT_SOURCE_BASE_H


#include "kzu_object_source_common.h"

#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core.ui/resource/resource.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>




/* Forward declarations */
struct KzcDynamicArray;
struct KzcInputStream;
struct KzcMatrix4x4;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuFilterObjectSource;
struct KzuObjectSourceRuntimeData;
struct KzuSortObjectSource;
struct KzuTransformedObjectNode;
struct KzuObjectSource;
struct KzuFilterObjectSource;
struct KzuCombinerObjectSource;

namespace kanzi
{
class Camera;
class Domain;
class TransformedScene3D;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;
typedef shared_ptr<KzuObjectSource> ObjectSourceSharedPtr;
typedef shared_ptr<KzuFilterObjectSource> FilterObjectSourceSharedPtr;
typedef shared_ptr<KzuSortObjectSource> SortObjectSourceSharedPtr;
typedef shared_ptr<KzuCombinerObjectSource> CombinerObjectSourceSharedPtr;
}


/* Filters */

/** Function type for per frame filter initialization. */
typedef kzsError (*KzuFilterResetFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData);
/** Function type for filter start function. This is called just before apply, but only once per frame */
typedef kzsError (*KzuFilterStartFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData,
                                           const struct KzuTransformedObjectNode* camera,
                                           const struct KzcDynamicArray* inputObjects);
/** Function type for cleaning up filter. */
typedef kzsError (*KzuFilterDeleteFunction)(struct KzuFilterObjectSource* filterObjectSource);
/** Function type for determining whether to accept given object or not. */
typedef kzsError (*KzuFilterApplyFunction)(struct KzuFilterObjectSource* filterObjectSource,
                                           const struct KzuObjectSourceRuntimeData* runtimeData,
                                           const struct KzuTransformedObjectNode* camera,
                                           const struct KzuTransformedObjectNode* object,
                                           kzBool* out_accepted);


/** Configuration for filter types. */
struct KzuFilterConfiguration
{
    KzuFilterStartFunction startFunction; /**< Function to call every frame in the beginning of apply. Can be KZ_NULL. */
    KzuFilterApplyFunction applyFunction; /**< Function to use for evaluation whether a specific object will be included or not. */
};


/* Sort */

/** Function type for per frame sort object source initialization. */
typedef kzsError (*KzuSortObjectSourceResetFunction)(struct KzuSortObjectSource* sortObjectSource,
                                                     const struct KzuObjectSourceRuntimeData* runtimeData);
/** Function type for sort start function. This is called just before sorting. */
typedef kzsError (*KzuSortObjectSourceStartFunction)(struct KzuSortObjectSource* sortObjectSource,
                                                     const struct KzuObjectSourceRuntimeData* runtimeData,
                                                     const struct KzuTransformedObjectNode* camera,
                                                     const struct KzcDynamicArray* inputObjects);
/** Function type for cleaning up sort object source. */
typedef kzsError (*KzuSortObjectSourceDeleteFunction)(struct KzuSortObjectSource* sortObjectSource);
/** Function type for sorting transformed object nodes with sort object sources. */
typedef kzInt (*KzuSortObjectSourceComparatorFunction)(const struct KzuTransformedObjectNode* first,
                                                       const struct KzuTransformedObjectNode* second,
                                                       const struct KzcMatrix4x4* cameraMatrix,
                                                       const struct KzuObjectSourceRuntimeData* runtimeData);

/** Configuration for sort object sources. */
struct KzuSortObjectSourceConfiguration
{
    KzuSortObjectSourceStartFunction startFunction; /**< Function to call just before sorting. Can be KZ_NULL. */
    KzuSortObjectSourceComparatorFunction comparator; /**< Comparator function to use for sorting objects. */
};

/** Structure for object source. */
struct KANZI_API KzuObjectSource: public kanzi::Resource
{
    enum ObjectSourceType
    {
        Combine = 10,
        Sort = 50,
        FrustumCullFilter = 102, // Can't be created in studio.
        ContainsPropertyFilter = 103,
        ObjectTypeFilter = 104,
        PropertyIsEqualFilter = 105,
        TagFilter = 106
    };

    KZ_ABSTRACT_METACLASS_BEGIN(KzuObjectSource, Resource, "Kanzi.ObjectSource")
    KZ_METACLASS_END()

    explicit KzuObjectSource(kanzi::Domain *domain, kanzi::string_view name, enum KzuObjectSourceType type):
        Resource(domain, name),
        type(type)
    {
    }

    enum KzuObjectSourceType type;  /**< Type of object source. */

    /// Loads a resource dictionary from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Object source file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);
};

/** Structure for filter object source. */
struct KANZI_API KzuFilterObjectSource: public KzuObjectSource
{
    explicit KzuFilterObjectSource(kanzi::Domain* domain, kanzi::string_view name, const struct KzuFilterConfiguration* configuration):
        KzuObjectSource(domain, name, KZU_OBJECT_SOURCE_TYPE_FILTER),
        isExclusive(KZ_FALSE),
        applyRequired(KZ_TRUE),
        configuration(configuration)
    {
    }

    kanzi::ObjectSourceSharedPtr input; /**< Object source that goes in filter. */

    kzBool isExclusive; /**< Is this filter exclusive. */
    kzBool applyRequired; /**< Is apply for filter required. */

    const struct KzuFilterConfiguration* configuration; /**< Filter type configuration. */
};

/** Sort object source. This sorts the object list according to specified comparator. */
struct KANZI_API KzuSortObjectSource: public KzuObjectSource
{
    explicit KzuSortObjectSource(kanzi::Domain* domain, kanzi::string_view name):
        KzuObjectSource(domain, name, KZU_OBJECT_SOURCE_TYPE_SORT),
        configuration(0)
    {
    }

    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);


    kanzi::ObjectSourceSharedPtr input; /**< Input object source. */
    const KzuSortObjectSourceConfiguration* configuration; /**< Sort configuration. */
};

/** Combiner object source. This combines several input object sources by appending. */
struct KANZI_API KzuCombinerObjectSource: public KzuObjectSource
{
    explicit KzuCombinerObjectSource(kanzi::Domain* domain, kanzi::string_view name):
        KzuObjectSource(domain, name, KZU_OBJECT_SOURCE_TYPE_COMBINER)
    {
    }

    virtual ~KzuCombinerObjectSource() KZ_OVERRIDE;

    static kanzi::ObjectSourceSharedPtr loadFromKZB(kanzi::Domain* domain, kanzi::string_view name, kanzi::KzbFile& kzbFile, kanzi::ReadOnlyMemoryFile& file, kanzi::KzbMemoryParser& parser);


    typedef kanzi::vector<kanzi::ObjectSourceSharedPtr> ObjectSourceContainer;

    ObjectSourceContainer inputs;
};


struct KzuObjectSourceRuntimeData
{
    kanzi::TransformedScene3D* transformedScene; /**< Transformed scene the runtime data was extracted from. */
    struct KzcDynamicArray* allTransformedObjects; /**< All transformed objects of the scene. */

    kzU32 changeFlags; /**< Change flags of the runtime data. */

    struct KzcHashMap* objectSourceOutputs; /**< Cached outputs for object sources. <KzuObjectSource,KzcDynamicArray<KzuObjectNode>>. */
    struct KzcHashMap* objectSourceCameras; /**< Cached cameras for object sources. <KzuObjectSource, KzuTransformedObjectNode>. */
    struct KzcHashMap* objectSourceCacheDatas; /**< Arbitrary object source specific data. <KzuObjectSourceData,void>. */
};


/** Creates an object source. */
kzsError kzuObjectSourceCreate_protected(enum KzuObjectSourceType type, kanzi::Domain* domain, kanzi::string_view name,
                                         struct KzuObjectSource* objectSource);

/** Creates a filter object source. */
kzsError kzuFilterObjectSourceCreate_protected(const struct KzuFilterConfiguration* configuration, kanzi::Domain* domain,
                                               kanzi::string_view name, struct KzuFilterObjectSource* filterObjectSource);

/** Loads a filter object source from KZB. */
kzsError kzuFilterObjectSourceLoadFromKZB_protected(struct KzuFilterObjectSource* filterObjectSource, struct KzcInputStream* inputStream,
                                                    const struct KzuBinaryFileInfo* file);

/** Initializes a filter object source. */
void kzuFilterObjectSourceInitialize_protected(KzuFilterObjectSource* filterObjectSource, kanzi::ObjectSourceSharedPtr input, kzBool isExclusive);


/** Converts an object source into a filter object source */
struct KzuFilterObjectSource* kzuFilterObjectSourceFromObjectSource_protected(const struct KzuObjectSource* objectSource);


/** Store the cache data for an object source. */
kzsError kzuObjectSourceSetRuntimeCacheData_protected(const struct KzuObjectSource* objectSource,
                                                      const struct KzuObjectSourceRuntimeData* runtimeData,
                                                      const void* data);

/** Get the cache data of an object source. */
void* kzuObjectSourceGetRuntimeCacheData_protected(const struct KzuObjectSource* objectSource,
                                                   const struct KzuObjectSourceRuntimeData* runtimeData);





#endif
