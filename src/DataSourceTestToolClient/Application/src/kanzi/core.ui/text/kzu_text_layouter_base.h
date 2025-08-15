/**
* \file
* Text layouter class and virtual/base functions.
*
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TEXT_LAYOUTER_BASE_H
#define KZU_TEXT_LAYOUTER_BASE_H


#include "kzu_text_layouter.h"

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuTextLayout;
struct KzuTextLayouter;


/** Defines functions for different text layouter implementations. */
struct KzuTextLayouterClass
{
    /** Deletes the text layouter. */
    kzsError (*destructor)(struct KzuTextLayouter* textLayouter);

    /** Creates a text layout using this text layouter. */
    kzsError (*createLayout)(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                             kzString text, struct KzuTextLayout** out_textLayout);
};


struct KzuTextLayouter
{
    const struct KzuTextLayouterClass* textLayouterClass; /**< Class of the text layouter. */
    struct KzuFont* font; /**< Font used for layouting the text. */
    TextConcept::TextHorizontalAlignment horizontalAlignment; /**< Horizontal alignment. */
    TextConcept::TextVerticalAlignment verticalAlignment; /**< Vertical alignment. */
    kzFloat maximumWidth; /**< Maximum width in pixels or KZS_INFINITY if no maximum specified. */
    kzUint maximumCharactersPerLine; /**< Maximum width in characters or KZ_UINT_MAXIMUM if no maximum specified. */
    kzFloat maximumHeight; /**< Maximum height in pixels or KZS_INFINITY if no maximum specified. */
    kzUint maximumLines; /**< Maximum height in lines or KZ_UINT_MAXIMUM if no maximum specified. */
    kzFloat lineSpacing; /**< Line spacing in multiples of line height. */
    kzFloat characterSpacing; /**< Additional spacing that is added between each charater. Specified in pixels. */
    kzBool fixedCharacterWidthEnabled; /**< Is fixed character width specified. */
    kzFloat fixedCharacterWidth; /**< Fixed character width if it has been enabled. */
    kzMutableString terminator; /**< Terminator string to use if the given text does not fit to the given maximum size. */
    kzBool bidiShapingEnabled; /**< Is BiDi and text shaping enabled or not. If KZ_FALSE, the basic layouting is used. */
    bool removeSideBearingsEnabled; /**< If enabled removes side bearings for each line separately making text start right next to the sides. */
};

/** Base function for initializing a text layouter. */
kzsError kzuTextLayouterCreate_protected(struct KzuTextLayouter* textLayouter, const struct KzuTextLayouterClass* textLayouterClass,
                                         struct KzuFont* font);

/** Base function for deleting a text layouter. */
kzsError kzuTextLayouterDestructor_protected(struct KzuTextLayouter* textLayouter);


/** Base function for creating a text layout. */
kzsError kzuTextLayouterCreateLayout_protected(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                               kzString text, struct KzuTextLayout** out_textLayout);


#endif
