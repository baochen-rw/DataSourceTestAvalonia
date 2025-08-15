// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_BINARY_RESOURCE_H
#define KZU_BINARY_RESOURCE_H

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

struct KzuResourceLoader;
struct KzuBinaryFileInfo;
struct KzcInputStream;

namespace kanzi
{

class BinaryResource;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;

typedef shared_ptr<BinaryResource> BinaryResourceSharedPtr;


class KANZI_API BinaryResource: public Resource
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(BinaryResource, Resource, "Kanzi.BinaryResource")
    KZ_METACLASS_END()

    typedef vector<byte> DataContainer;
    typedef DataContainer::const_iterator DataConstIterator;

    /** Creates a binary resource. */
    static BinaryResourceSharedPtr create(kanzi::Domain* domain, string_view name);

    /** Creates a empty binary resource. */
    static BinaryResource* createEmpty(kanzi::Domain* domain, string_view name);

    /** Loads resource wrapper from KZB. */
    void loadFromKZBWithoutContext(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

    /// Loads a binary resource from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Binary file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static BinaryResourceSharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /** Loads resource wrapper from a file. */
    void loadFromFile(string_view filePath);

    /** Loads resource wrapper from a file. If loading fails, function will return false. */
    bool tryLoadFromFile(string_view filePath);

    /** Returns resource data. */
    const byte* getData();

    /** Returns resource data size. */
    size_t getDataSize();

    /** Returns const iterator to beginning of data. */
    DataConstIterator cbegin();

    /** Returns const iterator to end of data. */
    DataConstIterator cend();

protected:
    BinaryResource(kanzi::Domain *domain, string_view name) :
        Resource(domain, name)
    {
    }

    DataContainer m_data; /**< Binary data. */
};

}

#endif
