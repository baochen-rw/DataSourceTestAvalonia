/**
 * \file
 * User layer error codes.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZU_ERROR_CODES_H
#define KZU_ERROR_CODES_H


/* User layer error codes have reserved range of 30000 - 39999 */

/* Binary loader error codes. (30100 - 30199) */
#define KZU_EXCEPTION_FILE_NOT_FOUND (kzsException)(-30101) /**< Given file was not found from a binary. */
#define KZU_ERROR_INVALID_BINARY_DATA (kzsError)30102 /**< Encountered invalid binary data while reading .kzb. */
#define KZU_ERROR_WRONG_BINARY_FILE_TYPE (kzsError)30103 /**< Wrong binary file type for given file. */
#define KZU_ERROR_INVALID_FILE_PATH (kzsError)30104 /**< Invalid file path. */
#define KZU_EXCEPTION_INCOMPLETE_BINARY_FILE (kzsException)(-30105) /**< Binary file is truncated and does not contain requested data. */

/* Scene specific error codes. (30200 - 30299) */
#define KZU_ERROR_INVALID_SCENE_GRAPH (kzsError)30202 /**< Scene graph contains invalid data. */

/* Property specific error codes (30300 - 30399) */
#define KZU_ERROR_PROPERTY_NOT_FOUND (kzsError)30301 /**< Requested property was not found. */
#define KZU_ERROR_INVALID_PROPERTY (kzsError)30302 /**< Property was invalid. */
#define KZU_ERROR_WRONG_PROPERTY_DATA_TYPE (kzsError)30304 /**< Property data type was wrong in the context. */

/* Mesh specific error codes (30500 - 30599) */
#define KZU_ERROR_MESH_INVALID_VERTEX_ATTRIBUTE_MAPPING (kzsError)30502 /**< Invalid vertex attribute mapping for mesh. */

/* Project error codes (30600 - 30699) */
#define KZU_ERROR_PROJECT_LOADING_FAILED (kzsError)30601 /**< Failed to load project. */
#define KZU_ERROR_PROJECT_OBJECT_NOT_FOUND (kzsError)30602 /**< Requested object not found from project. */

/* Scheduling error codes (31100 - 31199) */
#define KZU_ERROR_SCHEDULER_TASK_NOT_FOUND (kzsError)31101 /**< Task not found from scheduler. */

/* Util / font error codes (31400 - 31499) */
#define KZU_ERROR_FONT_INVALID_DATA (kzsError)31401 /**< Font data is corrupt. */
#define KZU_ERROR_ITYPE_FAILED (kzsError)31402 /**< Error with iType. */
#define KZU_ERROR_FREETYPE_FAILED (kzsError)31403 /**< Error with FreeType. */
#define KZU_ERROR_FONT_SHADER_NOT_INITIALIZED (kzsError)31404 /**< Uninitialized font shader. */
#define KZU_ERROR_WTSHAPER_FAILED (kzsError)31405 /**< Error with WTShaper. */
#define KZU_ERROR_ICU_FAILED (kzsError)31406 /**< Error with ICU. */

/* License restriction error codes (31500 - 31599). */
#define KZU_ERROR_LICENSE_RESTRICTION (kzsError)31501 /**< Operation is not allowed with the given license type. */

/* Resource manager error codes (31600 - 31699). */
#define KZU_ERROR_RESOURCE_NOT_LOADED (kzsError)31602 /**< An operation with a resource failed because the resource has not yet been loaded. */
#define KZU_ERROR_INVALID_RESOURCE_PATH (kzsError)31603 /**< Invalid resource path was given. */
#define KZU_ERROR_PROTOCOL_ALREAY_REGISTERED (kzsError)31606 /**< Trying to register a resource handler protocol, which has already been registered. */

/* Binding error codes (31800 - 31899). */
#define KZU_ERROR_EXPRESSION_VALIDATOR_INVALID_OPERATION_CODE (kzsError)(31803) /**< Expression validator operation code is unknown. */
#define KZU_ERROR_VALIDATOR_CHANGED_AFTER_ATTACH (kzsError)(31804) /**< Expression validator operation code is unknown. */


#endif
