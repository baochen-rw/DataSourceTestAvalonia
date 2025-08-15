/**
 * \file
 * System header.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_DYNAMIC_LIBRARY_H
#define KZS_DYNAMIC_LIBRARY_H

#include <kanzi/core/legacy/kzs_types.hpp>


typedef void (*PFNDYNAMICLIBRARYMUSTCASTPROC)(void);

struct KzsDynamicLibrary;

KANZI_API struct KzsDynamicLibrary* kzsDynamicLibraryOpen(const char* path);

KANZI_API void kzsDynamicLibraryClose(struct KzsDynamicLibrary* library);

KANZI_API PFNDYNAMICLIBRARYMUSTCASTPROC kzsDynamicLibraryGetProcAddress(struct KzsDynamicLibrary* library, const char* symbolName);


#endif
