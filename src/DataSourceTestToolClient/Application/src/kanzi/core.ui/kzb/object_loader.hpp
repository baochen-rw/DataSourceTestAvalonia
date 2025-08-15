// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_OBJECT_LOADER_HPP
#define KZ_OBJECT_LOADER_HPP


#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/metadata/meta_object_factory.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>

#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_directory.h>


namespace kanzi
{

/// Forward declarations.
class KzbFile;
class KzbMemoryParser;
class Object;

typedef shared_ptr<Object> ObjectSharedPtr;


/// ObjectLoader loads objects from KZB.
class KANZI_API ObjectLoader
{
public:

    typedef function<ObjectSharedPtr(Domain*, string_view, KzcInputStream*, const KzuBinaryFileInfo*)> LoadFunctionOld;
    typedef function <ObjectSharedPtr(Domain*, string_view, KzbFile&, KzbMemoryParser&)> LoadFunction;

    /// Constructor.
    explicit ObjectLoader();

    /// Registers object load functions by metaclass.
    /// Functions might return objects whose type is different from the type specified by metaclass.
    /// \param metaclass Metaclass of object to load.
    /// \param loadFunctionOld Function to load object from old-format KZB.
    /// \param loadFunction Function to load object from KZB.
    void registerObjectLoadFunctions(const Metaclass* metaclass, const LoadFunctionOld& loadFunctionOld, const LoadFunction& loadFunction);

    /// Loads object by metaclass from old-style KZB.
    /// Returned object might have different type than type specified by metaclass.
    /// \param domain Domain to use when loading object.
    /// \param metaclass Metaclass of object to load.
    /// \param name Name of object to load.
    /// \param inputStream Stream to load object from.
    /// \param file File to load object from.
    /// \return Loaded object.
    ObjectSharedPtr loadObject(Domain* domain, const Metaclass* metaclass, string_view name, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

    /// Loads object by metaclass from KZB.
    /// Returned object might have different type than type specified by metaclass.
    /// \param domain Domain to use when loading object.
    /// \param metaclass Metaclass of object to load.
    /// \param name Name of object to load.
    /// \param kzbFile KZB to load object from.
    /// \param parser Parser to parse object data from.
    /// \return Loaded object.
    ObjectSharedPtr loadObject(Domain* domain, const Metaclass* metaclass, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

    /// Indicates whether loading for objects with specified metaclass is possible via this object loader.
    /// \param metaclass Object metaclass.
    /// \returns true if loading is possible, false otherwise.
    bool isLoadingEnabled(const Metaclass* metaclass) const;

private:

    /// ObjectLoader contains functions to load object from KZB.
    struct ObjectLoaderEntry
    {
        /// Function to load object from old-format KZB.
        LoadFunctionOld loadFunctionOld;
        /// Function to load object from KZB.
        LoadFunction loadFunction;
    };

    /// Maps load functions to metaclass.
    typedef map<const Metaclass*, ObjectLoaderEntry> ObjectLoaderDictionary;
    ObjectLoaderDictionary m_objectLoaderDictionary;
};


/// Loads embedded object.
/// Embedded objects are objects which are stored in binary file along with their metaclass and name.
///
/// \param domain Domain.
/// \param inputStream Input stream from which to read object.
/// \param file Binary file where object is embedded.
KANZI_API ObjectSharedPtr loadEmbeddedObject(Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

}

#endif // KZ_OBJECT_LOADER_HPP
