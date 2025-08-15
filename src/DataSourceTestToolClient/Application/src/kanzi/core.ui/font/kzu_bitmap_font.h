
/**
* \file
* Bitmap font.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/

#ifdef KANZI_FEATURE_3D

#ifndef KZU_BITMAP_FONT_H
#define KZU_BITMAP_FONT_H

#include "kzu_font_base.h"
#include "kzu_font_common.h"

#include <kanzi/core/cpp/vector.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzuBinaryFileInfo;
struct KzuFont;
struct KzuTextLayout;

namespace kanzi
{
class Domain;
class ShaderProgram;
class Texture;
class Renderer;
typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
typedef shared_ptr<Texture> TextureSharedPtr;
}

/**
 * \struct KzuBitmapFontSystem
 * Structure for bitmap font system. This system is needed for bitmap fonts.
 * Usually one bitmap font system per application is enough, but more can be used if needed.
 */
struct KzuBitmapFontSystem;

/**
* \struct KzuBitmapFont
* Font structure for rendering text.
*/
struct KANZI_API KzuBitmapFont : public KzuFont
{
    KZ_ABSTRACT_METACLASS_BEGIN(KzuBitmapFont, KzuFont, "Kanzi.BitmapFont")
    KZ_METACLASS_END()

    explicit KzuBitmapFont(kanzi::Domain* domain, kanzi::string_view name) :
        KzuFont(domain, name),
        system(),
        resourceManager(),
        characters(),
        kerningPairs(),
        size(0u),
        lineHeight(0u),
        ascender(0u),
        descender(0u),
        textureCount(0u),
        scale(1.0f),
        textureNames()
    {
    }

    virtual ~KzuBitmapFont() KZ_OVERRIDE;

    struct KzuBitmapFontSystem* system;      /**< Reference to bitmap font system. */
    kanzi::ResourceManager* resourceManager; /**< Resource manager for the bitmap font. */

    struct KzcHashMap* characters;   /**< Available characters. <kzUint, KzuFontCharacter> */
    struct KzcHashMap* kerningPairs; /**< Available kerning pairs. <struct KzuFontKerningPairKey, kzInt>. */

    kzUint size;         /**< Height of font. */
    kzUint lineHeight;   /**< Height of a line. */
    kzUint ascender;     /**< The ascender value. */
    kzUint descender;    /**< The descender value. */
    kzUint textureCount; /**< How many textures this font requires */

    kzFloat scale; /**< Font scale factor relative to the size which the bitmap font was generated. */

    kanzi::ColorRGBA color; /**< Current drawing color of the font. */
    typedef kanzi::vector<kanzi::TextureSharedPtr> TextureContainer;
    TextureContainer fontTextures;        /**< Texture used with this font. */
    struct KzcDynamicArray* textureNames; /**< Names of bitmap files constructing this font. */
};


/** Font type identifier for bitmap font objects. */
extern const KzuFontType KZU_FONT_TYPE_BITMAP;


/** Creates a bitmap font system. */
kzsError kzuBitmapFontSystemCreate(const struct KzcMemoryManager* memoryManager, struct KzuBitmapFontSystem** out_bitmapSystem);

/** Deletes a bitmap font system. */
kzsError kzuBitmapFontSystemDelete(struct KzuBitmapFontSystem* bitmapSystem);

/** Sets shader for bitmap font system. */
void kzuBitmapFontSystemSetShader(struct KzuBitmapFontSystem* bitmapSystem, kanzi::ShaderProgramSharedPtr shader);


/** Creates new font without any data. */
kzsError kzuBitmapFontCreate(struct KzuBitmapFontSystem* bitmapSystem,
                             kanzi::Domain* domain, kzString name, struct KzuBitmapFont** out_bitmapFont);
/** Creates new font from file. */
kzsError kzuBitmapFontCreateFromFile(struct KzuBitmapFontSystem* bitmapSystem,
                                     kanzi::Domain* domain, kzString filePath,
                                     struct KzuBitmapFont** out_bitmapFont);

/** Creates new font from resource. */
kzsError kzuBitmapFontCreateFromResource(struct KzuBitmapFontSystem* bitmapSystem,
                                         kanzi::Domain* domain, kzString resourcePath,
                                         struct KzuBitmapFont** out_bitmapFont);
/** Creates new font from preloaded resources. */
KANZI_API kzsError kzuBitmapFontCreateFromMemory(struct KzuBitmapFontSystem* bitmapSystem,
                                                 kanzi::Domain* domain, kzString fntFileContent,
                                                 kzString name, struct KzuBitmapFont** out_bitmapFont);

/** Loads font from KZB. */
kzsError kzuBitmapFontLoadFromKZB(struct KzuBitmapFont* bitmapFont, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


/** Type cast from generic font to bitmap font. */
struct KzuBitmapFont* kzuBitmapFontFromFont(struct KzuFont* font);
/** Type cast from bitmap font to generic font. */
struct KzuFont* kzuBitmapFontToFont(struct KzuBitmapFont* bitmapFont);


/** Gets font texture names from font. */
struct KzcDynamicArrayIterator kzuBitmapFontGetFontTextureNames(const struct KzuBitmapFont* bitmapFont);
/** Sets texture to given slot in font. The font takes ownership of the font after the operation and releases the texture when font is released. */
KANZI_API void kzuBitmapFontSetTexture(KzuBitmapFont* bitmapFont, kanzi::TextureSharedPtr texture, kzUint slot);


/** Sets the size of bitmap font (in pixels). */
void kzuBitmapFontSetSize(struct KzuBitmapFont* bitmapFont, kzUint size);
/** Sets the scale (relative size) of bitmap font. */
void kzuBitmapFontSetScale(struct KzuBitmapFont* bitmapFont, kzFloat scale);
/** Returns the size of bitmap font. */
kzFloat kzuBitmapFontGetSize(const struct KzuBitmapFont* bitmapFont);

/** Sets the color of the font. */
void kzuBitmapFontSetColor(struct KzuBitmapFont* bitmapFont, kanzi::ColorRGBA color);
/** Gets the color of the font. */
kanzi::ColorRGBA kzuBitmapFontGetColor(const struct KzuBitmapFont* bitmapFont);


/** Returns the line height of bitmap font. */
kzFloat kzuBitmapFontGetLineHeight(const struct KzuBitmapFont* bitmapFont);
/** Returns the ascender of bitmap font. */
kzFloat kzuBitmapFontGetAscender(const struct KzuBitmapFont* bitmapFont);
/** Returns the descender of bitmap font. */
kzFloat kzuBitmapFontGetDescender(const struct KzuBitmapFont* bitmapFont);

/** Returns the glyph index in the font for the given unicode code point. */
kzUint kzuBitmapFontGetGlyphIndex(const struct KzuBitmapFont* bitmapFont, kzUnicodeChar character);


/** Returns the advance of given character using bitmap font. */
void kzuBitmapFontGetCharacterMetrics(const struct KzuBitmapFont* bitmapFont, kzUint glyphIndex,
                                      kzFloat* out_advance, struct KzcRectangle* out_boundingBox);
/** Returns the kerning of given character pair using bitmap font. */
kzFloat kzuBitmapFontGetKerning(const struct KzuBitmapFont* bitmapFont, kzUint previousGlyphIndex, kzUint glyphIndex);


/**
 * Draws a character at given coordinates. The coordinates indicate the character left point on the baseline.
 * This function is meant for debugging purposes only. For real text rendering, use KzcTextLayouter.
 */
kzsError kzuBitmapFontDrawCharacter(const struct KzuBitmapFont* bitmapFont, kanzi::Renderer* renderer,
                                    kzUint glyphIndex, kzFloat x, kzFloat y);


/** Prepares the given pre-layouted text for fast rendering using bitmap font. */
kzsError kzuBitmapFontPrepareTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Draw the given pre-layouted text using bitmap font. */
kzsError kzuBitmapFontDrawTextLayout(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

/** Draw the given pre-layouted text in 3D space using bitmap font. */
kzsError kzuBitmapFontDrawTextLayout3D(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

/** Frees the data and resources created by the prepare function. */
kzsError kzuBitmapFontFreeTextLayoutData(struct KzuTextLayout* textLayout);


#endif

#endif // KANZI_FEATURE_3D
