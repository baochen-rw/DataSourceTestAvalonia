/**
* \file
* Output stream
* Output streams are used for writing binary data to several different data sources.
* Supported data sources are:
* <ul>
*   <li>Files</li>
*   <li>Resources</li>
*   <li>Memory buffers</li>
*   <li>Nested output streams</li>
* </ul>
* Streams are configured to write data in either little-endian, big-endian or platform's native endianness format.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_OUTPUT_STREAM_H
#define KZC_OUTPUT_STREAM_H

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/util/io/kzc_io_stream.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

// Forward declarations.
struct KzcMemoryManager;

/**
 * \struct KzcOutputStream
 * Output stream for writing binary data to files, memory or nested output streams.
 */
struct KzcOutputStream;


/** Function type for deleting custom output stream. */
typedef kzsError (*KzcCustomOutputStreamDeleteFunction)(void* customData);
/** Function type for writing bytes to custom output stream. */
typedef kzsError (*KzcCustomOutputStreamWriteFunction)(void* customData, kzUint byteCount, const kanzi::byte* bytes, kzUint* out_bytesWrittenCount);
/** Function type for skipping in a custom output stream. */
typedef kzsException (*KzcCustomOutputStreamSkipFunction)(void* customData, kzUint skipAmount);


/** Creates an output stream pointing to a file, whose path is given as a parameter. */
KANZI_API kzsException kzcOutputStreamCreateToFile(const struct KzcMemoryManager* memoryManager, kzString filePath,
                                                   enum KzcIOStreamEndianness endianness, struct KzcOutputStream** out_outputStream);

/** Creates an output stream pointing to a given memory buffer of given size. */
KANZI_API kzsException kzcOutputStreamCreateToMemory(const struct KzcMemoryManager* memoryManager, kanzi::byte* buffer, kzUint size,
                                                     enum KzcIOStreamEndianness endianness, struct KzcOutputStream** out_outputStream);

/**
 * Creates an output stream pointing to another output stream.
 * Length of the target output stream can be given as a parameter. In this case the stream will write at most
 * that many bytes to the target stream and possibly unwritten bytes are skipped when deleting the stream.
 * \param targetLength Length of the output stream or KZC_IO_STREAM_LENGTH_UNKNOWN if unknown.
 */
KANZI_API kzsException kzcOutputStreamCreateToStream(const struct KzcMemoryManager* memoryManager, struct KzcOutputStream* targetOutputStream, kzInt targetLength,
                                                     enum KzcIOStreamEndianness endianness, struct KzcOutputStream** out_outputStream);

/** Creates an output stream using custom write functions. */
KANZI_API kzsException kzcOutputStreamCreateCustom(const struct KzcMemoryManager* memoryManager, void* customData,
                                                   KzcCustomOutputStreamDeleteFunction deleteFunction, KzcCustomOutputStreamWriteFunction writeFunction,
                                                   KzcCustomOutputStreamSkipFunction skipFunction, enum KzcIOStreamEndianness endianness,
                                                   struct KzcOutputStream** out_outputStream);


/** Deletes an output stream. */
KANZI_API kzsError kzcOutputStreamDelete(struct KzcOutputStream* outputStream);


/**
 * Writes some amount of bytes to the given output stream.
 * The maximum number of bytes is given as parameter and the actual number of bytes written is returned.
 * Negative number is returned, if no bytes can be written because end of stream has been reached.
 * This function can be used to write to output stream when the number of bytes that can be written at once is not known.
 */
KANZI_API kzsException kzcOutputStreamWrite(struct KzcOutputStream* outputStream, kzUint byteCount, const kzByte* bytes, kzUint* out_bytesWrittenCount);

/** Skips the given amount of bytes in an output stream. */
KANZI_API kzsException kzcOutputStreamSkip(struct KzcOutputStream* outputStream, kzUint skipAmount);

/** Gets the current position in an output stream. */
KANZI_API kzUint kzcOutputStreamGetPosition(const struct KzcOutputStream* outputStream);


/** Gets endianness of output stream. */
KANZI_API enum KzcIOStreamEndianness kzcOutputStreamGetEndianness(const struct KzcOutputStream* outputStream);
/** Sets endianness for output stream. */
KANZI_API void kzcOutputStreamSetEndianness(struct KzcOutputStream* outputStream, enum KzcIOStreamEndianness endianness);


/** Flushes the output stream. */
KANZI_API kzsException kzcOutputStreamFlush(const struct KzcOutputStream* outputStream);

/**
 * Writes given amount of bytes to the output stream.
 * An error is returned if the output stream has an error, or end of stream is reached too soon.
 */
KANZI_API kzsException kzcOutputStreamWriteBytes(struct KzcOutputStream* outputStream, kzUint byteCount, const kanzi::byte* bytes);

/** Writes a boolean to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteBoolean(struct KzcOutputStream* outputStream, kzBool value);

/** Writes an unsigned 8-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteU8(struct KzcOutputStream* outputStream, kzU8 value);
/** Writes a signed 8-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteS8(struct KzcOutputStream* outputStream, kzS8 value);

/** Writes an unsigned 16-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteU16(struct KzcOutputStream* outputStream, kzU16 value);
/** Writes an array of unsigned 16-bit values to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteU16Array(struct KzcOutputStream* outputStream, kzUint numValues, const kzU16* values);
/** Writes a signed 16-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteS16(struct KzcOutputStream* outputStream, kzS16 value);
/** Writes an array of signed 16-bit values to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteS16Array(struct KzcOutputStream* outputStream, kzUint numValues, const kzS16* values);

/** Writes an unsigned 32-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteU32(struct KzcOutputStream* outputStream, kzU32 value);
/** Writes an array of unsigned 32-bit values to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteU32Array(struct KzcOutputStream* outputStream, kzUint numValues, const kzU32* values);
/** Writes a signed 32-bit value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteS32(struct KzcOutputStream* outputStream, kzS32 value);
/** Writes an array of signed 32-bit values to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteS32Array(struct KzcOutputStream* outputStream, kzUint numValues, const kzS32* values);

/** Writes a 32-bit floating point value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteFloat(struct KzcOutputStream* outputStream, kzFloat value);
/** Writes an array of 32-bit floating point values to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteFloatArray(struct KzcOutputStream* outputStream, kzUint numValues, const kzFloat* values);
/** Writes a 64-bit floating point value to an output stream. */
KANZI_API kzsException kzcOutputStreamWriteDouble(struct KzcOutputStream* outputStream, kzDouble value);


#endif
