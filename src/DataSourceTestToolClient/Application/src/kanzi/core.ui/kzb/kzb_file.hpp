// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_KZB_FILE_HPP
#define KZ_KZB_FILE_HPP

#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core/file/file.hpp>
#include <kanzi/core/file/read_only_memory_file.hpp>
#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/math/srt_value_2d.hpp>
#include <kanzi/core/math/srt_value_3d.hpp>

#include <kanzi/core/legacy/legacy_conversions.hpp>
#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>

namespace kanzi
{

// Forward declarations.
class Domain;
class KzbMemoryParser;
class Metaclass;


/// KZB file loader.
/// Used to store all KZB information. This includes dictionaries for strings, files, property types, metaclasses.
/// Resource manager refers to the #KzbFile dictionaries when loading resources.
/// Internally uses #KzbMemoryParser to parse the values from files.
class KANZI_API KzbFile
{
public:
    /// The version number for the current KZB format. Increased when the format changes.
    /// Major versions represent mainline (master branch) changes.
    /// Minor versions represent changes done on a specific branch.
    /// Version history:
    /// 0.0. The initial version. Used in Kanzi 3.6.1.
    /// 1.0. Introduced new versioning format that removes the Kanzi tool version from the kzb. Used in Kanzi 3.6.2.
    /// 2.0. Added multisample samples to render target textures. Cubemap images are flipped already in Kanzi Tool.
    /// 3.0. Added simple render target mode toggle to render target textures.
    /// 3.1. Storing resource dictionary text resource strings locally.
    /// 3.2. Support for deferred loading of state node component templates.
    /// 3.3. Added depth compare mode setting to render target textures.
    /// \{
    static const uint16_t KzbFormatVersionMajor = 3;
    static const uint16_t KzbFormatVersionMinor = 3;
    /// \}

    friend class KzbMemoryParser;

    typedef vector<pair<AbstractPropertyType, Variant> > PropertyContainer;

    /// Type specifying maximum size of files. Currently at 4Gb.
    typedef uint32_t SizeType;

    /// Constructor.
    /// \param domain.
    /// \param file File to read from.
    explicit KzbFile(Domain* domain, unique_ptr<File> file);

    /// Open a file by path.
    /// Throws an error if file is not found.
    /// \param path to open.
    /// \return File opened.
    unique_ptr<ReadOnlyMemoryFile> open(string_view path);
    /// Tries to open file by path.
    /// Silently returns an empty unique pointer if file is not found.
    /// \param path Path to open.
    /// \return File opened.
    unique_ptr<ReadOnlyMemoryFile> tryOpen(string_view path);

    /// Load a resource identified by path.
    /// \param path Path to resource.
    /// \return Resource loaded.
    ResourceSharedPtr loadResource(string_view path);

    /// Gets load task for given path.
    /// \param path Path to load.
    /// \return Load task created.
    ResourceManager::LoadTaskSharedPtr getLoadTask(string_view path);

    Domain* getDomain() const;

    /// Gets metaclass by index.
    /// \param index Index of metaclass.
    /// \return Metaclass.
    const Metaclass* getMetaclass(size_t index) const;
    /// Gets property type by index.
    /// \param index Index of property type.
    /// \return Property type.
    AbstractPropertyType getPropertyType(size_t index) const;
    /// Gets string from string dictionary by index.
    /// \param index Index of string.
    /// \return View into string.
    string_view getString(size_t index) const;

    /// Gets project name.
    /// Project name is the base filename part of the URL identifying the KZB.
    /// This corresponds to what is called a 'hostname' in URLs. KZB files loaded are identified by this name.
    /// Multiple .kzb -files can correspond to the same project name in the resource manager.
    string getProjectName() const;

    /// Collects resource urls for this kzb file.
    /// \param urls List to store URLs to.
    void collectResourceUrls(ResourceManager::UrlContainer& urls);

private:
    enum FileCompression
    {
        FileCompressionNone = 0
    };

    struct FileEntry
    {
        explicit FileEntry(string_view name, uint32_t metaclass, SizeType offset, SizeType size, FileCompression compression, SizeType uncompressedSize) :
            name(name),
            metaclass(metaclass),
            offset(offset),
            size(size),
            compression(compression),
            uncompressedSize(uncompressedSize)
        {
        }

        string_view name;
        uint32_t metaclass;
        SizeType offset;
        SizeType size;
        FileCompression compression;
        SizeType uncompressedSize;
    };

    const FileEntry* getFileEntry(string_view filePath) const;

    string_view getName(const FileEntry& fileEntry) const;
    const Metaclass* getMetaclass(const FileEntry& fileEntry) const;
    unique_ptr<ReadOnlyMemoryFile> open(const FileEntry& fileEntry) const;

    void loadAndVerifyKzbMagic(KzbMemoryParser& parser);
    void loadVersionAndProjectName(KzbMemoryParser& parser);
    void loadFileDictionary(KzbMemoryParser& parser);
    void loadStringDictionary();
    void loadPlugins();
    void loadMetaclassDictionary();
    void loadPropertyTypeDictionary();
    void loadCustomPropertyTypes();
    void loadCustomMessageTypes();

    typedef vector<string> StringCollection;
    typedef vector<string> FileNameCollection;
    typedef map<string_view, FileEntry> FileDictionary;
    typedef vector<AbstractPropertyType> PropertyTypeDictionary;
    typedef vector<const Metaclass*> MetaclassDictionary;

    Domain* m_domain;
    unique_ptr<File> m_file;
    string m_projectName;
    StringCollection m_stringCollection;
    FileNameCollection m_fileNameDictionary;
    FileDictionary m_fileDictionary;
    PropertyTypeDictionary m_propertyTypeDictionary;
    MetaclassDictionary m_metaclassDictionary;
};


/// Gets the supported KZB format version.
///
/// \return KZB format version number.
KANZI_API uint32_t getSupportedKzbFormatVersion();

/// Gets the KZB magic byte sequence.
///
/// \return KZB magic byte sequence.
KANZI_API ConstByteSpan getKzbMagic();

/// Tells if beginning of given byte span matches KZB magic.
///
/// \param data Data to test.
/// \return True if matches KZB magic.
KANZI_API bool isKzbMagic(ConstByteSpan data);

/// Tells if beginning of given file matches KZB magic.
///
/// \param file File to test.
/// \return True if matches KZB magic.
KANZI_API bool isKzbMagic(File& file);
}

#endif // KZ_KZB_FILE_HPP
