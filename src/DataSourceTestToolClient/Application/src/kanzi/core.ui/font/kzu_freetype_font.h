/**
* \file
* FreeType font.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/

#ifndef KZU_FREETYPE_FONT_H
#define KZU_FREETYPE_FONT_H

#include "kzu_font_common.h"

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

// Forward declarations.
struct KzuFont;
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzuBinaryFileInfo;
struct KzuTextLayout;
struct KzuTruetypeSystem;

namespace kanzi
{

class Domain;
class Renderer;
class Renderer3D;
class Texture;

}

/**
 * \struct KzuFreetypeSystem
 * Structure for FreeType font system. This system is needed for FreeType fonts.
 * Usually one FreeType font system per application is enough, but more can be used if needed.
 */
struct KzuFreetypeSystem;

/**
* \struct KzuFreetypeFont
* Font structure for rendering text with FreeType.
*/
struct KzuFreetypeFont;


/** Font type identifier for font FreeType fonts. */
KANZI_API extern const KzuFontType KZU_FONT_TYPE_FREETYPE;


/** Creates an FreeType font system. */
KANZI_API kzsError kzuFreetypeSystemCreate(const struct KzcMemoryManager* memoryManager, kanzi::Domain* domain,
                                 struct KzuFreetypeSystem** out_freetypeSystem);

/** Deletes an FreeType font system. */
KANZI_API kzsError kzuFreetypeSystemDelete(struct KzuFreetypeSystem* freetypeSystem);

/** Type casts a generic TrueType font system to more specific FreeType font system. */
KANZI_API struct KzuFreetypeSystem* kzuFreetypeSystemFromTruetypeSystem(struct KzuTruetypeSystem* truetypeSystem);

/** Type casts a FreeType font system to more generic TrueType font system. */
KANZI_API struct KzuTruetypeSystem* kzuFreetypeSystemToTruetypeSystem(struct KzuFreetypeSystem* freetypeSystem);


/** Creates new FreeType font. */
KANZI_API kzsError kzuFreetypeFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem, kanzi::string_view name,
                                         struct KzuFreetypeFont** out_freetypeFont);

/** Creates new FreeType font from resource. */
KANZI_API kzsError kzuFreetypeFontCreateFromResource(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                           kzString resourcePath, struct KzuFreetypeFont** out_freetypeFont);


/** Creates new FreeType font from file. */
KANZI_API kzsError kzuFreetypeFontCreateFromFile(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                                 kzString filePath, struct KzuFreetypeFont** out_freetypeFont);

/** Creates new FreeType font from memory. */
KANZI_API kzsError kzuFreetypeFontCreateFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuFreetypeSystem* freetypeSystem,
                                                   const kanzi::byte* data, kzUint size, kanzi::string_view name, bool createMemoryCopy,
                                                   struct KzuFreetypeFont** out_freetypeFont);

/** Loads FreeType font from KZB. */
KANZI_API kzsError kzuFreetypeFontLoadFromKZB(struct KzuFreetypeFont* freetypeFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Type casts generic font structure to FreeType font structure. */
KANZI_API struct KzuFreetypeFont* kzuFreetypeFontFromFont(struct KzuFont* font);
/** Type casts FreeType font structure to generic font structure. */
KANZI_API struct KzuFont* kzuFreetypeFontToFont(struct KzuFreetypeFont* freetypeFont);

/** Sets the size of FreeType font (in pixels). */
KANZI_API kzsError kzuFreetypeFontSetSize(struct KzuFreetypeFont* freetypeFont, kzFloat size);
/** Returns the size of FreeType font. */
KANZI_API kzFloat kzuFreetypeFontGetSize(const struct KzuFreetypeFont* freetypeFont);

/** Sets the color of the font. */
KANZI_API void kzuFreetypeFontSetColor(struct KzuFreetypeFont* freetypeFont, kanzi::ColorRGBA color);
/** Gets the color of the font. */
KANZI_API kanzi::ColorRGBA kzuFreetypeFontGetColor(const struct KzuFreetypeFont* freetypeFont);


/** Returns the line height of FreeType font. */
KANZI_API kzFloat kzuFreetypeFontGetLineHeight(const struct KzuFreetypeFont* freetypeFont);
/** Returns the ascender of FreeType font. */
KANZI_API kzFloat kzuFreetypeFontGetAscender(const struct KzuFreetypeFont* freetypeFont);
/** Returns the descender of FreeType font. */
KANZI_API kzFloat kzuFreetypeFontGetDescender(const struct KzuFreetypeFont* freetypeFont);

/** Returns the glyph index in the font for the given unicode code point. */
KANZI_API kzUint kzuFreetypeFontGetGlyphIndex(const struct KzuFreetypeFont* freetypeFont, kzUnicodeChar character);

/** Returns the advance of given character using FreeType font. */
KANZI_API kzsError kzuFreetypeFontGetCharacterMetrics(const struct KzuFreetypeFont* freetypeFont, kzUint glyphIndex,
                                            kzFloat* out_advanceX, kzFloat* out_advanceY, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using FreeType font. */
KANZI_API kzsError kzuFreetypeFontGetKerning(const struct KzuFreetypeFont* freetypeFont, kzUint previousGlyphIndex,
                                             kzUint glyphIndex, kzFloat* out_kerningX, kzFloat* out_kerningY);

/** Prepares the given pre-layouted text for fast rendering using FreeType. */
KANZI_API kzsError kzuFreetypeFontPrepareTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Draw the given pre-layouted text into a texture using FreeType */
kzsError kzuFreetypeFontPrepareTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer3D* renderer, kanzi::Texture* texture);

/** Draw the given pre-layouted text using FreeType. */
KANZI_API kzsError kzuFreetypeFontDrawTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using FreeType. */
KANZI_API kzsError kzuFreetypeFontDrawTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Frees the data and resources created by the prepare function. */
KANZI_API kzsError kzuFreetypeFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/**
 * Loads a bitmap data for a single character glyph. The data doesn't need to be released, but it is valid only until prepare text
 * layout, draw text layout or this function gets called again. The data is returned as a greyscale image with 8 bits per pixel,
 * with the first scanline being the bottom line of the image.
 */
KANZI_API kzsError kzuFreetypeFontLoadCharacterGlyph(const struct KzuFreetypeFont* freetypeFont, kzUint glyphIndex, kzUint* out_width,
                                                     kzUint* out_height, const kanzi::byte** out_data);

/** Returns the FT_Face object from FreeType font. */
KANZI_API void* kzuFreetypeFontGetFace(const struct KzuFreetypeFont* freetypeFont);


#endif

