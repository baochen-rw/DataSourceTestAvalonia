/**
* \file
* Core file utilities.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_FILE_H
#define KZC_FILE_H

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#ifndef SPANSION
#define KZ_FEATURE_MISC
#endif

/* Forward declarations */
struct KzcMemoryManager;


/** Get the file extension of a file with given path. */
KANZI_API kzsError kzcFileGetExtension(const struct KzcMemoryManager* memoryManger, kzString filePath, kzMutableString* out_extension);

/** Reads binary content of a file with given path. The caller must free the returned data using kzcMemoryFreePointer(). */
KANZI_API kzsException kzcFileReadBinaryFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint* out_size, kanzi::byte** out_data);

/** Reads binary content of a resource with given path. The caller must free the returned data using kzcMemoryFreePointer(). */
KANZI_API kzsException kzcFileReadBinaryResource(const struct KzcMemoryManager* memoryManager, kzString resourcePath, kzUint* out_size, kanzi::byte** out_data);

#ifdef KZ_FEATURE_MISC
/** Reads the data from the file system to the string with given path. */
KANZI_API kzsException kzcFileReadTextFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString* out_string);
/** Reads text lines of a file with given path. */
KANZI_API kzsException kzcFileReadTextFileLines(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString** out_lines);

/**
 * Reads the data from a resource file to the string with given path. The behavior is platform dependent. 
 * E.g. in Android, a "file" is something on the file system and a "resource" is inside APK. In Windows the path for "resources" can be configured.
 */
KANZI_API kzsException kzcFileReadTextResource(const struct KzcMemoryManager* memoryManager, kzString filePath, kzMutableString* out_string);
#endif
/** Reads text lines of a resource file with given path. */
KANZI_API kzsException kzcFileReadTextResourceLines(const struct KzcMemoryManager* memoryManager, kzString resourcePath, kzMutableString** out_lines);

#ifdef KZ_FEATURE_MISC
/** Writes binary data to a file with given path. */
KANZI_API kzsException kzcFileWriteBinaryFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint size, const kanzi::byte* data);

/** Writes text lines to a file with given path. */
KANZI_API kzsException kzcFileWriteTextFile(const struct KzcMemoryManager* memoryManager, kzString filePath, kzUint lineCount, const kzString* lines);

/** Returns true if file exists. */
KANZI_API kzBool kzcFileExists(kzString filePath);
#endif


#endif
