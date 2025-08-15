/**
* \file
* Monotype's iType font.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_ITYPE_FONT_H
#define KZU_ITYPE_FONT_H


#include "kzu_font_common.h"

#include <kanzi/core.ui/platform/graphics_backend/gl/shader.hpp>
#include <kanzi/core/math/color_rgba.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>





/* Forward declaration structures. */
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
}

/** Font type identifier for font iType fonts. */
extern const KzuFontType KZU_FONT_TYPE_ITYPE;


/**
 * \struct KzuItypeSystem
 * Structure for iType font system. This system is needed for iType fonts.
 * Usually one iType font system per application is enough, but more can be used if needed.
 */
struct KzuItypeSystem;

/**
* \struct KzuItypeFont
* Font structure for rendering text with iType.
*/
struct KzuItypeFont;



/** Creates an iType font system. */
kzsError kzuItypeSystemCreate(const struct KzcMemoryManager* memoryManager, kanzi::Domain* domain,
                              struct KzuItypeSystem** out_itypeSystem);

/** Deletes an iType font system. */
kzsError kzuItypeSystemDelete(struct KzuItypeSystem* itypeSystem);

/** Sets shader for iType system. */
void kzuItypeSystemSetShader(struct KzuItypeSystem* itypeSystem, kzBool useDistanceField, kanzi::ShaderProgramSharedPtr shader);

/** Type casts a generic TrueType font system to more specific iType font system. */
struct KzuItypeSystem* kzuItypeSystemFromTruetypeSystem(struct KzuTruetypeSystem* truetypeSystem);

/** Type casts an iType font system to more generic TrueType font system. */
struct KzuTruetypeSystem* kzuItypeSystemToTruetypeSystem(struct KzuItypeSystem* itypeSystem);


/// Creates new iType font.
kzsError kzuItypeFontCreate(struct KzuItypeSystem* itypeSystem, kanzi::string_view name, struct KzuItypeFont** out_itypeFont);

/** Creates new iType font from resource. */
kzsError kzuItypeFontCreateFromResource(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                        kzString resourcePath, struct KzuItypeFont** out_itypeFont);

/// Creates new iType font from file.
kzsError kzuItypeFontCreateFromFile(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                    kzString filePath, struct KzuItypeFont** out_itypeFont);

/// Creates new iType font from memory.
kzsError kzuItypeFontCreateFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuItypeSystem* itypeSystem,
                                      const kzByte* data, kzUint size, kanzi::string_view name, bool createMemoryCopy,
                                      struct KzuItypeFont** out_itypeFont);

/** Loads iType font from KZB. */
kzsError kzuItypeFontLoadFromKZB(struct KzuItypeFont* itypeFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Type casts generic font structure to iType font structure. */
struct KzuItypeFont* kzuItypeFontFromFont(struct KzuFont* font);
/** Type casts iType font structure to generic font structure. */
struct KzuFont* kzuItypeFontToFont(struct KzuItypeFont* itypeFont);


/** Sets the size of iType font (in pixels). */
kzsError kzuItypeFontSetSize(struct KzuItypeFont* itypeFont, kzFloat size);
/** Returns the size of iType font. */
kzFloat kzuItypeFontGetSize(const struct KzuItypeFont* itypeFont);

/** Sets the color of the font. */
void kzuItypeFontSetColor(struct KzuItypeFont* itypeFont, kanzi::ColorRGBA color);
/** Gets the color of the font. */
kanzi::ColorRGBA kzuItypeFontGetColor(const struct KzuItypeFont* itypeFont);


/** Returns the line height of iType font. */
kzFloat kzuItypeFontGetLineHeight(const struct KzuItypeFont* itypeFont);
/** Returns the ascender of iType font. */
kzFloat kzuItypeFontGetAscender(const struct KzuItypeFont* itypeFont);
/** Returns the descender of iType font. */
kzFloat kzuItypeFontGetDescender(const struct KzuItypeFont* itypeFont);


/** Returns the glyph index in the iType font for the given unicode code point. */
kzUint kzuItypeFontGetGlyphIndex(const struct KzuItypeFont* itypeFont, kzUnicodeChar character);


/** Returns the advance of given character using iType font. */
kzsError kzuItypeFontGetCharacterMetrics(const struct KzuItypeFont* itypeFont, kzUint glyphIndex,
                                         kzFloat* out_advanceX, kzFloat* out_advanceY, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using iType font. */
kzsError kzuItypeFontGetKerning(const struct KzuItypeFont* itypeFont, kzUint previousGlyphIndex, kzUint glyphIndex,
                                kzFloat* out_kerningX, kzFloat* out_kerningY);


/** Prepares the given pre-layouted text for fast rendering using iType. */
kzsError kzuItypeFontPrepareTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Draw the given pre-layouted text using iType. */
kzsError kzuItypeFontDrawTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using iType. */
kzsError kzuItypeFontDrawTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuItypeFontFreeTextLayoutData(struct KzuTextLayout* textLayout);

/**
 * Loads a bitmap data for a single character glyph. The returned character glyph needs to be released with a call to release.
 * The bitmap data is returned as a greyscale image with 8 bits per pixel.
 */
kzsError kzuItypeFontLoadCharacterGlyph(const struct KzuItypeFont* itypeFont, kzUint glyphIndex, kzUint* out_width,
                                        kzUint* out_height, const kzByte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph. */
kzsError kzuItypeFontReleaseCharacterGlyph(const struct KzuItypeFont* itypeFont, void* characterGlyph);


/** Returns the FS_STATE* object from iType font. */
void* kzuItypeFontGetState(const struct KzuItypeFont* itypeFont);



#endif
