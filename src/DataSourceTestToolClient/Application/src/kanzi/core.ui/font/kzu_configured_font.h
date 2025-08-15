/**
* \file
* Configured font. This font implementation wraps an existing font with given font configuration (size, color).
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_CONFIGURED_FONT_H
#define KZU_CONFIGURED_FONT_H

#include "kzu_font_common.h"

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

// Forward declarations.
struct KzuFont;
struct KzuTextLayout;
struct KzcMemoryManager;
struct KzcRectangle;

namespace kanzi
{

class Domain;
class Renderer;

}

/**
* \struct KzuConfiguredFont
* Font structure for rendering text.
*/
struct KzuConfiguredFont;


/** Font type identifier for configured font objects. */
extern const KzuFontType KZU_FONT_TYPE_CONFIGURED;


/** Creates new configured font wrapping the given target font. */
kzsError kzuConfiguredFontCreate(const struct KzcMemoryManager* memoryManager, struct KzuFont* targetFont,
                                 kzFloat size, kanzi::ColorRGBA color, const kanzi::Domain* domain, kzString name, struct KzuConfiguredFont** out_configuredFont);


/** Type cast from generic font to configured font. */
struct KzuConfiguredFont* kzuConfiguredFontFromFont(struct KzuFont* font);
/** Type cast from configured font to generic font. */
struct KzuFont* kzuConfiguredFontToFont(struct KzuConfiguredFont* configuredFont);


/** Sets the size of configured font. */
kzsError kzuConfiguredFontSetSize(struct KzuConfiguredFont* configuredFont, kzFloat size);
/** Returns the size of configured font. */
kzFloat kzuConfiguredFontGetSize(const struct KzuConfiguredFont* configuredFont);

/** Sets the color of the font. */
kzsError kzuConfiguredFontSetColor(struct KzuConfiguredFont* configuredFont, kanzi::ColorRGBA color);
/** Gets the color of the font. */
kanzi::ColorRGBA kzuConfiguredFontGetColor(const struct KzuConfiguredFont* configuredFont);


/** Returns the line height of configured font. */
kzsError kzuConfiguredFontGetLineHeight(const struct KzuConfiguredFont* configuredFont, kzFloat* out_lineHeight);
/** Returns the ascender of configured font. */
kzsError kzuConfiguredFontGetAscender(const struct KzuConfiguredFont* configuredFont, kzFloat* out_ascender);


/** Returns the glyph index in the font for the given unicode code point. */
kzsError kzuConfiguredFontGetGlyphIndex(const struct KzuConfiguredFont* configuredFont, kzUnicodeChar character, kzUint* out_glyphIndex);


/** Returns the advance of given character using configured font. */
kzsError kzuConfiguredFontGetCharacterMetrics(const struct KzuConfiguredFont* configuredFont, kzUint glyphIndex,
                                              kzFloat* out_advance, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using configured font. */
kzsError kzuConfiguredFontGetKerning(const struct KzuConfiguredFont* configuredFont, kzUint previousGlyphIndex,
                                     kzUint glyphIndex, kzFloat* out_kerning);

/** Loads a bitmap data for a single character glyph using configured font. */
kzsError kzuConfiguredFontLoadCharacterGlyph(const struct KzuConfiguredFont* configuredFont, kzUint glyphIndex, kzUint* out_width,
                                             kzUint* out_height, const kanzi::byte** out_bitmapData, void** out_characterGlyph);
/** Releases a loaded character glyph using configured font. */
kzsError kzuConfiguredFontReleaseCharacterGlyph(const struct KzuConfiguredFont* configuredFont, void* characterGlyph);


/** Prepares the given pre-layouted text for fast rendering using configured font. */
kzsError kzuConfiguredFontPrepareTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);
 
/** Draw the given pre-layouted text using configured font. */
kzsError kzuConfiguredFontDrawTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using configured font. */
kzsError kzuConfiguredFontDrawTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuConfiguredFontFreeTextLayoutData(struct KzuTextLayout* textLayout);





#endif
