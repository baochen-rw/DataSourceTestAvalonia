/**
* \file
* Text layout.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TEXT_LAYOUT_H
#define KZU_TEXT_LAYOUT_H


#include <kanzi/core/legacy/kzs_types.hpp>





/* Forward declarations */
struct KzuFont;


/** Structure for layout of a single character for text rendering. */
struct KzuCharacterLayout
{
    kzUint character; /**< Character glyph index in the font. */
    kzFloat x; /**< X coordinate of the left side of the character. */
    kzFloat y; /**< y coordinate of the bottom of the character. */
    kzUint originalTextIndex; /**< index of character in original text */
};


/** Structure for layout of arbitrary number of characters for text rendering. */
struct KzuTextLayout
{
    struct KzuFont* font; /**< Font used for rendering the text. */
    kzFloat left; /**< X-coordinate of the left size of the text bounds. */
    kzFloat top; /**< Y-coordinate of the top size of the text bounds. */
    kzFloat right; /**< X-coordinate of the right size of the text bounds. */
    kzFloat bottom; /**< Y-coordinate of the bottom size of the text bounds. */
    kzFloat width; /**< Width of the text bounds. */
    kzFloat height; /**< Height of the text bounds. */
    kzUint lineCount; /**< Number of lines. */
    kzUint characterCount; /**< Number of characters. */
    kzBool truncated; /**< Set to KZ_TRUE if the text did not fit to the given maximum bounds. */
    kzBool overlaps; /**< Set to KZ_TRUE if at least two characters overlap each other. */
    struct KzuCharacterLayout* characters; /**< Layouted characters of the text. */
    void* renderData; /**< Font implementation specific rendering data calculated in the prepare. */
};





#endif
