/**
* \file
* Font private members.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_FONT_BASE_H
#define KZU_FONT_BASE_H

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/math/color_rgba.hpp>

// Forward declarations.
struct KzcInputStream;
struct KzcMemoryManager;
struct KzcRectangle;
struct KzuBinaryFileInfo;
struct KzuTextLayout;
struct KzuTruetypeSystem;
struct KzuFont;

namespace kanzi
{

class Domain;
class ShaderProgram;
class Renderer;
class Renderer3D;
class Texture;

typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
typedef shared_ptr<KzuFont> FontSharedPtr;
}

/** Function definition for deleting TrueType font system. */
typedef kzsError (*KzuTruetypeSystemDeletor)(struct KzuTruetypeSystem* truetypeSystem);
/** Function definition for creating TrueType fonts. */
typedef kzsError (*KzuTruetypeFontCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem, kanzi::string_view name,
                                           struct KzuFont** out_font);
/** Function definition for creating TrueType fonts from file. */
typedef kzsError (*KzuTruetypeFontFileCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                               kzString filePath, struct KzuFont** out_font);
/** Function definition for creating TrueType fonts from memory. */
typedef kzsError (*KzuTruetypeFontMemoryCreator)(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                                 const kanzi::byte* data, kzUint size, kanzi::string_view name, bool createCopy, struct KzuFont** out_font);

struct KzuTruetypeSystem
{
    explicit KzuTruetypeSystem() :
        domain(),
        systemDeletor(),
        fontCreator(),
        fontFileCreator(),
        fontMemoryCreator(),
        textureUniformLocation(-1),
        fontColorUniformLocation(-1)
    {
    }

    kanzi::Domain* domain;                          /**< UI domain. */
    KzuTruetypeSystemDeletor systemDeletor;         /**< Function for deleting the font system. */
    KzuTruetypeFontCreator fontCreator;             /**< Function for creating a font. */
    KzuTruetypeFontFileCreator fontFileCreator;     /**< Function for creating a font from file. */
    KzuTruetypeFontMemoryCreator fontMemoryCreator; /**< Function for creating a font from memory. */
    kanzi::ShaderProgramSharedPtr fontShader;       /**< ShaderProgram for rendering truetype fonts. */
    int textureUniformLocation;                     // uniform location for: truetype "Texture", itype "kzTexture"
    int fontColorUniformLocation;                   // uniform location for: "kzFontColorUniform"
};

/** Defines functions for different font implementations. */
struct KzuFontClass
{
    static const kanzi::ColorRGBA DefaultFontColor;

    /** Loads font from .KZB. */
    kzsError (*loadfromKZB)(struct KzuFont* font, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

    /** Sets the size of the font (in pixels). */
    kzsError (*setSize)(struct KzuFont* font, kzFloat size);
    /** Returns the size of the font. */
    kzsError (*getSize)(struct KzuFont* font, kzFloat* out_size);

    /** Sets the color of the font. */
    kzsError (*setColor)(struct KzuFont* font, kanzi::ColorRGBA color);
    /** Gets the color of the font. */
    kzsError (*getColor)(struct KzuFont* font, kanzi::ColorRGBA& out_color);

    /** Returns the line height of the font. */
    kzsError (*getLineHeight)(struct KzuFont* font, kzFloat* out_lineHeight);

    /** Returns the ascender of the font. */
    kzsError (*getAscender)(struct KzuFont* font, kzFloat* out_ascender);

    /** Returns the descender of the font. */
    kzsError (*getDescender)(struct KzuFont* font, kzFloat* out_descender);

    /** Returns the glyph index in the font for the given unicode code point. */
    kzsError (*getGlyphIndex)(struct KzuFont* font, kzUnicodeChar character, kzUint* out_glyphIndex);

    /** Returns the advance of given character using. */
    kzsError (*getCharacterMetrics)(struct KzuFont* font, kzUint glyphIndex, kzFloat* out_advance, struct KzcRectangle* out_boundingBox);

    /** Returns the kerning of given character pair using. */
    kzsError (*getKerning)(struct KzuFont* font, kzUint previousGlyphIndex, kzUint glyphIndex, kzFloat* out_kerning);

    /** Loads a bitmap data for a single character glyph. */
    kzsError (*loadCharacterGlyph)(struct KzuFont* font, kzUint glyphIndex, kzUint* out_width,
                                   kzUint* out_height, const kanzi::byte** out_bitmapData, void** out_characterGlyph);

    /** Releases a loaded character glyph. */
    kzsError (*releaseCharacterGlyph)(struct KzuFont* font, void* characterGlyph);

    /** Prepares the given pre-layouted text for fast rendering. */
    kzsError (*prepareTextLayout)(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

    /** Draw the given pre-layouted text. */
    kzsError (*drawTextLayout)(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer, kzFloat x, kzFloat y);

    /** Draw the given pre-layouted text in 3D space. */
    kzsError (*drawTextLayout3D)(struct KzuTextLayout* textLayout, kanzi::Renderer* renderer);

    /** Frees the data and resources created by the prepare function. */
    kzsError (*freeTextLayoutData)(struct KzuTextLayout* textLayout);
};

struct KANZI_API KzuFont : public kanzi::Resource
{
    KZ_ABSTRACT_METACLASS_BEGIN(KzuFont, Object, "Kanzi.Font")
    KZ_METACLASS_END()

    explicit KzuFont(kanzi::Domain* domain, kanzi::string_view name) :
        Resource(domain, name),
        fontClass()
    {
    }

    virtual ~KzuFont() KZ_OVERRIDE;

    const struct KzuFontClass* fontClass; /**< Class of the font. */
};


/** Initializes the base of a TrueType font system. */
kzsError kzuTruetypeSystemInitialize_protected(struct KzuTruetypeSystem* truetypeSystem, kanzi::Domain* domain, KzuTruetypeSystemDeletor systemDeletor,
                                               KzuTruetypeFontCreator fontCreator, KzuTruetypeFontFileCreator fontFileCreator,
                                               KzuTruetypeFontMemoryCreator fontMemoryCreator);


/** Creates a font. */
kzsError kzuFontCreate_protected(const struct KzuFontClass* fontClass, kanzi::Domain* domain, struct KzuFont* font);


#endif
