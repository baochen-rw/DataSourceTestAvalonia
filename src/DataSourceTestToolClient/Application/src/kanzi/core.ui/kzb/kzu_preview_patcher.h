/**
* \file
* Preview patcher. 
* This component provides mechanism for loading and patching .KZB binary data while running under Tool preview.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_PREVIEW_PATCHER_H
#define KZU_PREVIEW_PATCHER_H

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#ifndef SPANSION
#define KZ_FEATURE_PATCHING
#endif

#ifdef KZ_FEATURE_PATCHING

/* Forward declarations */
struct KzuBinaryDirectory;
struct KzuBinarySource;

namespace kanzi
{

class Domain;

}

/** Patches with the given .KZB data. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromMemory(const kanzi::Domain* domain, kzUint byteCount, const kanzi::byte* bytes, struct KzuBinarySource** out_binarySource);

/** Patches with the .KZB data of given file. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromFile(const kanzi::Domain* domain, kzString filePath, struct KzuBinarySource** out_binarySource);

/** Patches with the .KZB data of given resource. Returns the binary source that was created for the data. out_binarySource can be KZ_NULL. */
kzsError kzuPreviewPatcherPatchFromFileResource(const kanzi::Domain* domain, kzString resourcePath, struct KzuBinarySource** out_binarySource);

#endif

#endif // KZU_PREVIEW_PATCHER_H