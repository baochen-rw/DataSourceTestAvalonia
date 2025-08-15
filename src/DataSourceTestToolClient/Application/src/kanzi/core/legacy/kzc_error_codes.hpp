/**
 * \file
 * Core layer error codes.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZC_ERROR_CODES_H
#define KZC_ERROR_CODES_H


/* Core layer error codes have reserved range of 20000 - 29999 */

/* Util / Collection error codes. (20200 - 20299) */
#define KZC_ERROR_ELEMENT_NOT_FOUND (kzsError)20201 /**< Given element not found from the collection. */
#define KZC_ERROR_DUPLICATE_ELEMENT (kzsError)20202 /**< Element already exists in the given collection. */

/* Util / io error codes. (20300 - 20399) */
#define KZC_EXCEPTION_END_OF_STREAM (kzsException)(-20301) /**< End of stream encountered while reading/writing a stream. */
#define KZC_ERROR_UNSPECIFIED_ENDIANNESS (kzsError)20302 /**< Stream endianness was unspecified while trying to read/write non-bytes. */

/* Util / image error codes. (20400 - 20499) */
#define KZC_ERROR_IMAGE_FORMAT_UNSUPPORTED (kzsError)20401 /**< Unsupported image format. */
#define KZC_EXCEPTION_IMAGE_FORMAT_UNSUPPORTED ((kzsException)-20401) /**< Unsupported image format. */
#define KZC_ERROR_IMAGE_INVALID (kzsError)20402 /**< Corrupted image data. */
#define KZC_EXCEPTION_IMAGE_INVALID ((kzsException)-20402) /**< Corrupted image data. */
#define KZC_ERROR_IMAGE_WRITE_ERROR (kzsError)20403 /**< Error occurred while writing image data. */
#define KZC_ERROR_IMAGE_MANIPULATION_ERROR (kzsError)20404 /**< Unable to perform given image manipulation operation. */

/* Renderer error codes (21200 - 21299) */
#define KZC_ERROR_OPENGL_ERROR (kzsError)21201 /**< OpenGL related error. */


#endif
