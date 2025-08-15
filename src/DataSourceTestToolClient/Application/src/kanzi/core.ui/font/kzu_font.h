/**
* \file
* Font handling interface.
* This interface provides functionality for measuring font related information and for drawing pre-layeted text.
* To draw arbitrary strings with this interface, the text must be first layed out with kzu_text_layouter.h.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_FONT_H
#define KZU_FONT_H

#include "kzu_font_common.h"

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#define KZ_TRUETYPE_SYSTEM_FREETYPE 1 /**< Truetype support with Freetype. */
#define KZ_TRUETYPE_SYSTEM_ITYPE    2 /**< Truetype support with iType. */
#define KZ_TRUETYPE_SYSTEM_DUMMY    3 /**< No Truetype support. */

#ifndef KZ_TRUETYPE_SYSTEM_DEFAULT
/** Default truetype font system. */

#ifdef SPANSION
#define KZ_TRUETYPE_SYSTEM_DEFAULT KZ_TRUETYPE_SYSTEM_DUMMY
#else
#define KZ_TRUETYPE_SYSTEM_DEFAULT KZ_TRUETYPE_SYSTEM_FREETYPE
#endif

#endif

/* Forward declarations */
struct KzuBinaryFileInfo;
struct KzuTextLayout;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzcInputStream;

/**
* \struct KzuFont
* Font structure for rendering text.
*/
struct KzuFont;

namespace kanzi
{

class Renderer;
class Renderer3D;
class Texture;

}

/** Loads font from KZB. */
kzsError kzuFontLoadFromKZB(struct KzuFont* font, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Sets the size of the font. */
KANZI_API kzsError kzuFontSetSize(struct KzuFont* font, kzFloat size);
/** Returns the height of the font. */
KANZI_API kzsError kzuFontGetSize(struct KzuFont* font, kzFloat* out_size);

/** Sets the color of the font. */
KANZI_API kzsError kzuFontSetColor(struct KzuFont* font, kanzi::ColorRGBA color);
/** Gets the color of the font. */
KANZI_API kzsError kzuFontGetColor(struct KzuFont* font, kanzi::ColorRGBA& out_color);

/** Returns the fonts preferred line height. */
KANZI_API kzsError kzuFontGetLineHeight(struct KzuFont* font, kzFloat* out_lineHeight);

/** Returns the fonts ascender. This is how much the font ascends below the baseline. */
KANZI_API kzsError kzuFontGetAscender(struct KzuFont* font, kzFloat* out_ascender);

/** Returns the fonts descender. This is how much the font descends below the baseline. This is typically a positive value.*/
KANZI_API kzsError kzuFontGetDescender(struct KzuFont* font, kzFloat* out_descender);

/** Returns the glyph index in the font for the given unicode code point. */
KANZI_API kzsError kzuFontGetGlyphIndex(struct KzuFont* font, kzUnicodeChar character, kzUint* out_glyphIndex);

/** Gets the number of units that the cursor should move after given character glyph index. */
KANZI_API kzsError kzuFontGetCharacterMetrics(struct KzuFont* font, kzUint glyphIndex, kzFloat* out_advance, struct KzcRectangle* out_boundingBox);

/** Gets the kerning between two given character glyph indices. */
KANZI_API kzsError kzuFontGetKerning(struct KzuFont* font, kzUint previousGlyphIndex, kzUint glyphIndex, kzFloat* out_kerning);

/**
 * Loads the bitmap data for a single character glyph. The returned character glyph needs to be released with a call to release,
 * and the next glyph can't be loaded before the previous glyph has been released.
 * The bitmap data is returned as a greyscale image with 8 bits per pixel.
 */
KANZI_API kzsError kzuFontLoadCharacterGlyph(struct KzuFont* font, kzUint glyphIndex, kzUint* out_width,
                                             kzUint* out_height, const kanzi::byte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph. */
KANZI_API kzsError kzuFontReleaseCharacterGlyph(struct KzuFont* font, void* characterGlyph);

/** Prepares the given text layout for rendering. This step is automatically done when drawing for the first time if not already prepared before. */
kzsError kzuFontPrepareTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Draws the given text layout to given 2D position on the screen. */
KANZI_API kzsError kzuFontDrawTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

/** Draws the given text layout to 3D world with the current transformation. */
kzsError kzuFontDrawTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Frees the data allocated in the prepare. This is automatically done when deleting the text layout if needed. */
kzsError kzuFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/** Returns font's type */ 
KANZI_API KzuFontType kzuFontGetType(const struct KzuFont* font);



#endif
