/**
 * \file
 * Glyph cache.
 *
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZU_GLYPH_CACHE_H
#define KZU_GLYPH_CACHE_H

#include <kanzi/core.ui/graphics2d/texture.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuImageTexture;

namespace kanzi
{

class Renderer;
class ResourceManager;

}

/**
 * \struct KzuGlyphCache
 */
struct KzuGlyphCache;

/** Creates a glyph cache. The texture should be in alpha_8 format. */
KANZI_API KzuGlyphCache* kzuGlyphCacheCreate(kanzi::ResourceManager* resourceManager, kanzi::TextureSharedPtr texture, KzuFont* font, kzFloat glyphSize);

/** Deletes a glyph cache. */
KANZI_API kzsError kzuGlyphCacheDelete(struct KzuGlyphCache* glyphCache);

/** Removes all stored glyphs from the cache. */
KANZI_API kzsError kzuGlyphCacheClear(struct KzuGlyphCache* glyphCache);

/** Removes a stored glyph from the cache. */
KANZI_API kzsError kzuGlyphCacheRemove(struct KzuGlyphCache* glyphCache, kzUint glyph);

/**
 * Retrieves texture coordinates for a given glyph. If the glyph is not in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. In this case, if there is no more empty space left in the glyph cache
 * for the new glyph, then no texture coordinates are written and KZ_FALSE is written to the output parameter 'success'.
 */
KANZI_API kzsError kzuGlyphCacheRetrieveTextureCoordinates(struct KzuGlyphCache* glyphCache, kzUint glyph, kzBool* out_success,
                                                           kzFloat* out_leftU, kzFloat* out_topV, kzFloat* out_rightU, kzFloat* out_bottomV);

/**
 * Retrieves texture coordinates for a given glyph. If the glyph is not in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. In this case, if there is no more empty space left in the glyph cache
 * for the new glyph, then old glyphs are recycled in the least recently used order.
 */
KANZI_API kzsError kzuGlyphCacheRetrieveTextureCoordinatesRecycling(struct KzuGlyphCache* glyphCache, kzUint glyph,
                                                                    kzFloat* out_leftU, kzFloat* out_topV, kzFloat* out_rightU, kzFloat* out_bottomV);

/**
 * Retrieves texture coordinates for multiple glyphs. If a glyph is not found in the glyph cache texture, it is rendered there using
 * the font that was given when creating the glyph cache. The 12 texture coordinates of a glyph are written to the output parameter 'data'.
 * If there is no more empty space left in the glyph cache for a new glyph,
 * then that glyph and the following glyphs are not written. The amount of glyphs written is returned in the 'count' output parameter.
 */
KANZI_API kzsError kzuGlyphCacheRetrieveMultipleTextureCoordinates(struct KzuGlyphCache* glyphCache, const kzUint* glyphs, kzUint glyphCount,
                                                                   kzUint stride, kzUint* out_count, kzByte* out_data);

/**
 * Retrieves texture coordinates for multiple glyphs that might be partially clipped. 
 */
KANZI_API kzsError kzuGlyphCacheRetrieveMultipleTextureCoordinatesWithClipping(struct KzuGlyphCache* glyphCache, const kzUint* glyphs, kzUint glyphCount,
                                                                               kzUint stride, const kzFloat* clippingCoordinates, kzUint* out_count, kzByte* out_data);

/** Returns the texture that the cache was created with. */
KANZI_API kanzi::TextureSharedPtr kzuGlyphCacheGetTexture(const struct KzuGlyphCache* glyphcache);





#endif
