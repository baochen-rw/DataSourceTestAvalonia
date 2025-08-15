/**
 * \file
 * Text Manager.
 *
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_MANAGER_H
#define KZU_TEXT_MANAGER_H


#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuGlyphCache;

namespace kanzi
{

class ResourceManager;

}

/**
 * \struct KzuTextManager
 */
struct KzuTextManager;

/** Creates a text manager. */
KANZI_API kzsError kzuTextManagerCreate(const KzcMemoryManager* memoryManager, kanzi::ResourceManager* resourceManager, KzuTextManager** out_textManager);

/** Deletes a text manager. */
KANZI_API kzsError kzuTextManagerDelete(KzuTextManager* textManager);

/** Sets the size of the textures in glyph caches created by the text manager. */
KANZI_API void kzuTextManagerSetGlyphCacheSize(KzuTextManager* textManager, kzUint glyphCacheWidth, kzUint glyphCacheHeight);

/** Retrieves the glyph cache associated with the given font and font size. */
KANZI_API kzsError kzuTextManagerGetGlyphCache(const KzuTextManager* textManager, KzuFont* font, kzFloat fontSize, KzuGlyphCache** out_glyphCache);

/** Notifies the text manager that the given font has been deleted. This allows the text manager to clean-up glyph caches for that font. */
KANZI_API void kzuTextManagerNotifyFontDeleted(const KzuTextManager* textManager, KzuFont* font);

/** Removes all glyph caches. */
KANZI_API void kzuTextManagerClearGlyphCaches(const KzuTextManager* textManager);


#endif
