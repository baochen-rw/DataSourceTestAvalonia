/**
* \file
* Base functions for file related operations.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_FILE_BASE_H
#define KZS_FILE_BASE_H


#include <kanzi/core/legacy/kzs_types.hpp>


/**
 * Sets the active working directory to the given one.
 * All relative file and resource paths will be relative to the given path after this call, unless path is null.
 * Note that caller is responsible for keeping the path string alive as long as the application is running and accessing resource files.
 */
KANZI_API void kzsFileBaseSetResourceDirectory(kzString path);

/** Returns the active working directory. */
KANZI_API kzString kzsFileBaseGetResourceDirectory(void);


#endif
