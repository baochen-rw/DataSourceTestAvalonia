// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_WGL_H
#define KZS_WGL_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


struct WglLibrary;

kzsError kzsWglLibraryOpen(WglLibrary** out_library);

void kzsWglLibraryClose(WglLibrary* library);


#endif
