/**
* \file
* Binary directory for .kzb format.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_DIRECTORY_H
#define KZU_BINARY_DIRECTORY_H

#ifndef SPANSION
#define KZ_FEATURE_MMAP
#endif

#include "kzu_binary_common.h"

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/util/io/kzc_io_stream.hpp>
#include <kanzi/core/legacy/util/collection/kzc_hash_set.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

/** Current binary format version. */
#define KZU_BINARY_FORMAT_VERSION 140

/* Forward declarations. */
struct KzuBinaryDirectoryFilter;
struct KzcMemoryManager;
struct KzcInputStream;
struct KzcDynamicArray;


#define KZU_BINARY_FILE_INFO_FLAG_CACHED_RESOURCE (1 << 2) /**< If the flag is true, the object will not be released when calling kzuProjectClear. */
#define KZU_BINARY_FILE_INFO_FLAG_IMAGE_USED_IN_CUBE_MAPS (1 << 4) /**< This flag is only available in images. If the flag is true, the image is used in a cube map and should not be flipped internally. */
#define KZU_BINARY_FILE_INFO_FLAG_IMAGE_PREMULTIPLIED_ALPHA (1 << 5) /**< This flag is only available in images. If the flag is true, the image has premultiplied alpha. */
#define KZU_BINARY_DIRECTORY_DEFAULT_FILE_FLAG_MASK 0xFF /**< Default mask to pass all flags. */


/** License type restrictions. */
enum KzuBinaryLicenseRestriction
{
    KZU_BINARY_LICENSE_RESTRICTION_SHOW_SPLASH_SCREEN, /**< Splash screen will be shown during startup. */
    KZU_BINARY_LICENSE_RESTRICTION_SHOW_WATERMARK /**< Watermark will be displayed on top of everything else. */
};


/**
 * \struct KzuBinarySource
 * Specifies a source where file content can be read with an input stream.
 */
struct KzuBinarySource;

/**
 * \struct KzuBinaryFileInfo
 * Represents a single file inside a directory.
 */
struct KzuBinaryFileInfo;

/**
 * \struct KzuBinaryFolderInfo
 * Represents a single folder inside a directory.
 */
struct KzuBinaryFolderInfo;

/**
 * \struct KzuBinaryDirectory
 * Directory of a single .kzb binary or a merged result of several .kzb binaries.
 */
struct KzuBinaryDirectory;


/* Binary source */

/**
 * Gets a URL for the given reference index from the binary source.
 * \return URL of the reference with the given index or KZ_NULL if index == 0.
 */
KANZI_API kzString kzuBinarySourceGetReferencedURL(const struct KzuBinarySource* source, kzUint index);

/**
 * Invalidates the given binary source. After invalidating a source it will be impossible to load the files from it,
 * but the references can be queried.
 */
KANZI_API kzsError kzuBinarySourceInvalidate(struct KzuBinarySource* source);


/* Binary file info */

/** Gets the name of a file. */
KANZI_API kzString kzuBinaryFileInfoGetName(const struct KzuBinaryFileInfo* file);

/** Gets a directory of the binary file info. */
KANZI_API struct KzuBinaryDirectory* kzuBinaryFileInfoGetDirectory(const struct KzuBinaryFileInfo* file);

/** Gets the binary source of a file. */
KANZI_API struct KzuBinarySource* kzuBinaryFileInfoGetSource(const struct KzuBinaryFileInfo* file);

/** Gets the size of a file. */
KANZI_API kzUint kzuBinaryFileInfoGetSize(const struct KzuBinaryFileInfo* file);

/** Gets the type of a file. */
KANZI_API enum KzuBinaryFileType kzuBinaryFileInfoGetType(const struct KzuBinaryFileInfo* file);

/** Gets the path of a file. */
KANZI_API kzString kzuBinaryFileInfoGetPath(const struct KzuBinaryFileInfo* file);

/** Gets flags from binary file. */
KANZI_API kzU32 kzuBinaryFileInfoGetFlags(const struct KzuBinaryFileInfo* file);

/** Returns true if the file should be cached. */
KANZI_API bool kzuBinaryFileInfoIsCached(const struct KzuBinaryFileInfo* file);

/** Returns true if the file is an image file that is used in cubemaps. */
KANZI_API bool kzuBinaryFileInfoIsImageUsedInCubemaps(const struct KzuBinaryFileInfo* file);

/** Returns true if the file is an image file that has premultiplied alpha. */
KANZI_API bool kzuBinaryFileInfoIsImagePremultipliedAlpha(const struct KzuBinaryFileInfo* file);


/* Binary folder info */

/** Gets the name of a folder. */
KANZI_API kzString kzuBinaryFolderInfoGetName(const struct KzuBinaryFolderInfo* folder);

/**
 * Gets the sub folders of a folder.
 * \return Hash map of kzString -> KzuBinaryDirectoryFolder entries.
 */
KANZI_API struct KzcHashMap* kzuBinaryFolderInfoGetSubFolders(const struct KzuBinaryFolderInfo* folder);

/**
 * Gets the files of a folder.
 * \return Hash map of kzString -> KzuBinaryDirectoryFile entries.
 */
KANZI_API struct KzcHashMap* kzuBinaryFolderInfoGetFiles(const struct KzuBinaryFolderInfo* folder);

/** Gets all files recursively from a folder. The files are added to the given dynamic array. */
KANZI_API kzsError kzuBinaryFolderInfoGetAllFiles(const struct KzuBinaryFolderInfo* folder, struct KzcDynamicArray* files);

/**
 * Gets a specific sub folder from a folder.
 * \param name Name of the sub folder.
 * \return Returns a sub folder or KZ_NULL if a sub folder with the given name was not found.
 */
KANZI_API struct KzuBinaryFolderInfo* kzuBinaryFolderInfoGetSubFolder(const struct KzuBinaryFolderInfo* folder, kzString name);

/**
 * Gets a specific sub file from a folder.
 * \param name Name of the file.
 * \return Returns a file or KZ_NULL if a file with the given name was not found.
 */
KANZI_API struct KzuBinaryFileInfo* kzuBinaryFolderInfoGetFile(const struct KzuBinaryFolderInfo* folder, kzString name);


/* Binary directory */

/** Creates an empty directory. Content can be added to the directory with kzuBinaryDirectoryMerge(). */
KANZI_API kzsError kzuBinaryDirectoryCreateEmpty(const struct KzcMemoryManager* memoryManager, struct KzuBinaryDirectory** out_directory);

/// Set name of a binary directory.
/// \param directory Directory to set the name for.
/// \param name Name to set.
KANZI_API void kzuBinaryDirectorySetName(struct KzuBinaryDirectory* directory, kanzi::string_view name);

/** Creates a directory and fills the content from a .kzb file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
KANZI_API kzsError kzuBinaryDirectoryCreateFromFile(const struct KzcMemoryManager* memoryManager, kzString filePath,
                                          struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);
#ifdef KZ_FEATURE_MMAP
/** Creates a directory and fills the content from a .kzb memory mapped file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
KANZI_API kzsError kzuBinaryDirectoryCreateFromMemoryMappedFile(const struct KzcMemoryManager* memoryManager, kzString filePath, 
                                                                struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);
#endif
/** Creates a directory and fills the content from a .kzb resource file. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
KANZI_API kzsError kzuBinaryDirectoryCreateFromFileResource(const struct KzcMemoryManager* memoryManager, kzString resourcePath,
                                                  struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);

/** Creates a directory and fills the content from memory buffer with .kzb content. Returns a binary directory and an associated binary source. out_binarySource can be KZ_NULL. */
KANZI_API kzsException kzuBinaryDirectoryCreateFromMemory(const struct KzcMemoryManager* memoryManager, const kanzi::byte* buffer, kzUint size, 
                                                          struct KzuBinaryDirectory** out_directory, struct KzuBinarySource** out_binarySource);
/**
* Create a directory from memory buffer with .kzb content.
* The memory buffer is assumed temporary, so trying to map for permanent use is not allowed.
*/
KANZI_API kzsException kzuBinaryDirectoryCreateFromMemoryTemporary(const struct KzcMemoryManager* memoryManager, const kanzi::byte* buffer,
                                                                   kzUint size, struct KzuBinaryDirectory** out_directory,
                                                                   struct KzuBinarySource** out_binarySource);

/** Deletes a directory. */
KANZI_API kzsError kzuBinaryDirectoryDelete(struct KzuBinaryDirectory* directory);


/** Clears a directory. */
KANZI_API kzsError kzuBinaryDirectoryClear(struct KzuBinaryDirectory* directory);

/**
 * Checks if the binary directory is empty. A directory is not empty if it was created with some other function than kzuBinaryDirectoryCreateEmpty
 * or a non-empty directory was merged to an empty directory.
 */
KANZI_API kzBool kzuBinaryDirectoryIsEmpty(const struct KzuBinaryDirectory* directory);

/**
 * Merges the content of two directories.
 * Note: This function will completely delete sourceDirectory rendering any references to it invalid.
 * This is to ensure that each directory entry is owned by only one directory.
 * \param mergedFiles If this parameter is not NULL, all merged files are recorded in this dynamic array of KzuBinaryFileInfo objects.
 */
KANZI_API kzsError kzuBinaryDirectoryMerge(struct KzuBinaryDirectory* targetDirectory, struct KzuBinaryDirectory* sourceDirectory,
                                 struct KzcDynamicArray* mergedFiles);

/** Gets the root folder of a directory. */
KANZI_API struct KzuBinaryFolderInfo* kzuBinaryDirectoryGetRootFolder(const struct KzuBinaryDirectory* directory);

/** Gets the directory name. */
KANZI_API kzString kzuBinaryDirectoryGetName(const struct KzuBinaryDirectory* directory);

/** Gets an iterator of all deleted files in a directory. */
KANZI_API struct KzcHashSetIterator kzuBinaryDirectoryGetDeletedFiles(const struct KzuBinaryDirectory* directory);

/** Gets a file with the given full path from a binary directory. */
KANZI_API kzsException kzuBinaryDirectoryGetFile(const struct KzuBinaryDirectory* directory, kzString filePath, struct KzuBinaryFileInfo** out_file);

/** Gets flags from binary directory. */
KANZI_API kzU32 kzuBinaryDirectoryGetFlags(const struct KzuBinaryDirectory* directory);

/** Gets a folder with given path from binary directory. E.g. "Objects/" would return Object library. */
KANZI_API kzsException kzuBinaryDirectoryGetFolder(const struct KzuBinaryDirectory* directory, kzString folderPath, struct KzuBinaryFolderInfo** out_folder);

/** Opens a given file for reading. */
KANZI_API kzsException kzuBinaryDirectoryOpenFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file,
                                    struct KzcInputStream** out_inputStream);

/** Opens a given file for reading with the specified endianness. */
KANZI_API kzsException kzuBinaryDirectoryOpenFileWithEndianness(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file,
                                                  enum KzcIOStreamEndianness endianness, struct KzcInputStream** out_inputStream);

/** Returns binary data from file.*/
KANZI_API kzsError kzuBinaryDirectoryReadFile(const struct KzcMemoryManager* memoryManager, const struct KzuBinaryFileInfo* file, kanzi::byte** out_data);

/**
 * Opens a given file for reading with reference positions returned in an array.
 * The references in the file can be queried with the functions kzuBinaryFileInfoGetSource() and kzuBinarySourceGetReferencedFilePath().
 * \param out_referencePositions This array will be filled with positions of each reference in the file.
 *                               If this parameter is KZ_NULL, the position information is ignored and the array is not created.
 *                               The caller must free the array with kzcMemoryFreeArray afterwards.
 */
KANZI_API kzsException kzuBinaryDirectoryOpenFileWithReferences(const struct KzcMemoryManager* memoryManager,
                                                      const struct KzuBinaryFileInfo* file, kzUint** out_referencePositions,
                                                      enum KzcIOStreamEndianness endianness, struct KzcInputStream** out_inputStream);

/**
 * Gets all URLs referenced by the given file. The URLs are returned in an array of strings, which the caller
 * must delete after done using it.
 */
KANZI_API kzsError kzuBinaryDirectoryGetFileReferenceURLs(const struct KzcMemoryManager* memoryManager,
                                                const struct KzuBinaryFileInfo* file, kzString** out_references);

/** Gets all binary sources from directory. */
KANZI_API struct KzcHashSetIterator kzuBinaryDirectoryGetBinarySources(const struct KzuBinaryDirectory* directory);

/** Gets a string description of a given file. This is for debugging purposes only. */
KANZI_API kzsError kzuBinaryDirectoryGetFileDebugDescription(const struct KzuBinaryFileInfo* file, kzMutableString* out_description);

/** Gets file from property type library, using optimized search. */
KANZI_API kzsException kzuBinaryDirectoryGetFileFromPropertyTypeLibrary(const struct KzuBinaryDirectory* directory, kzString name,
                                                              struct KzuBinaryFileInfo** out_file);
/** Gets file from animation library, using optimized search. */
KANZI_API kzsException kzuBinaryDirectoryGetFileFromAnimationLibrary(const struct KzuBinaryDirectory* directory, kzString filePath,
                                                           struct KzuBinaryFileInfo** out_file);
/** Gets file from mesh library, using optimized search. */
KANZI_API kzsException kzuBinaryDirectoryGetFileFromMeshLibrary(const struct KzuBinaryDirectory* directory, kzString filePath,
                                                      struct KzuBinaryFileInfo** out_file);

/** Loads reference. Returns the URL for the reference or NULL if the reference was empty. */
KANZI_API kzsError kzuBinaryDirectoryReadReference(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file, kzString* out_path);
/** Sets file flag mask for binary directory files. Results loaded files to have flags with formula: flags = file.flags & directory.mask */
KANZI_API void kzuBinaryDirectorySetFileFlagMask(struct KzuBinaryDirectory* binaryDirectory, kzU32 fileFlagMask);
/** Gets file flag mask from directory. */
KANZI_API kzU32 kzuBinaryDirectoryGetFileFlagMask(const struct KzuBinaryDirectory* directory);


/** Checks if any of the loaded binaries have the given license restriction enabled. */
KANZI_API kzBool kzuBinaryDirectoryHasLicenseRestriction(const struct KzuBinaryDirectory* directory, enum KzuBinaryLicenseRestriction licenseRestriction);





#endif
