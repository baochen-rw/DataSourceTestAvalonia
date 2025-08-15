/**
* \file
* Text layouter is used for laying out text to a constrained area.
* The text is splitted to several lines when necessary.
*
* Below is a common use scenario for the text layouting.
* initialization:
*     result = kzuBasicTextLayouterCreate(memoryManager, font, &textLayouter);
*     kzsErrorForward(result);
*
*     Optionally set text layout parameters such as alignment and maximum bounds
*
* when the text has changed or in initialization for static text:
*     result = kzuTextLayouterCreateLayout(textLayouter, memoryManager, text, &textLayout);
*     kzsErrorForward(result);
*
*     result = kzuFontPrepareTextLayout(textLayout, renderer);
*     kzsErrorForward(result);
*
* rendering:
*     result = kzuFontDrawTextLayout(textLayout, renderer, x, y);
*     kzsErrorForward(result);
*
* uninitialization:
*     result = kzuTextLayoutDelete(textLayout);
*     kzsErrorForward(result);
*
*     result = kzuTextLayouterDelete(textLayouter);
*     kzsErrorForward(result);
*     Text layouter can also be deleted already right after the text layout is created.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TEXT_LAYOUTER_H
#define KZU_TEXT_LAYOUTER_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/wrappers/kzs_math.hpp>



/* Forward declaration structures. */
struct KzcMemoryManager;
struct KzuFont;
struct KzuTextLayout;

namespace kanzi {

class Renderer;

}


/**
* \struct KzuTextLayouter
* Structure for text layouting and rendering.
*/
struct KzuTextLayouter;

class TextConcept
{
public:

    enum TextHorizontalAlignment
    {
        TextHorizontalAlignmentLeft,  ///< Text is aligned to the left.
        TextHorizontalAlignmentRight, ///< Text is aligned to the right.
        TextHorizontalAlignmentCenter ///< Text is centered horizontally.
    };

    /// Vertical alignment options for text layout.
    enum TextVerticalAlignment
    {
        TextVerticalAlignmentTop,      ///< Text is aligned to the top.
        TextVerticalAlignmentBaseline, ///< Text is aligned to the baseline of the first line of the text.
        TextVerticalAlignmentCenter,   ///< Text is centered vertically.
        TextVerticalAlignmentBottom    ///< Text is aligned to the bottom.
    };

};


/** Deletes the text layouter. */
KANZI_API kzsError kzuTextLayouterDelete(struct KzuTextLayouter* textLayouter);

/**
 * Sets the maximum width in pixels for the text layout area. Note that at least one character per line will always be layouted.
 * Use KZS_INFINITY for unlimited width.
 */
KANZI_API void kzuTextLayouterSetMaximumWidth(struct KzuTextLayouter* textLayouter, kzFloat width);

/** Gets the maximum width in pixels for the text layout area. */
KANZI_API kzFloat kzuTextLayouterGetMaximumWidth(const struct KzuTextLayouter* textLayouter);

/**
 * Sets the maximum number of characters per line for the text layout area.
 */
KANZI_API void kzuTextLayouterSetMaximumCharactersPerLine(struct KzuTextLayouter* textLayouter, kzUint charactersPerLine);

/**
 * Sets the maximum height in pixels for the layout. Note that at least one line will always be layouted.
 * Use KZS_INFINITY for unlimited height.
 */
KANZI_API void kzuTextLayouterSetMaximumHeight(struct KzuTextLayouter* textLayouter, kzFloat height);

/** Gets the maximum height in pixels for the text layout area. */
KANZI_API kzFloat kzuTextLayouterGetMaximumHeight(const struct KzuTextLayouter* textLayouter);

/**
 * Sets the maximum number of lines for the layout.
 */
KANZI_API void kzuTextLayouterSetMaximumLines(struct KzuTextLayouter* textLayouter, kzUint maximumLines);

/** Sets the terminator string used when both horizontal and vertical space is running out for the text layout. */
KANZI_API kzsError kzuTextLayouterSetTerminator(struct KzuTextLayouter* textLayouter, kzString terminator);

/** Gets the terminator string used when both horizontal and vertical space is running out for the text layout. */
KANZI_API kzString kzuTextLayouterGetTerminator(const struct KzuTextLayouter* textLayouter);

/** Sets the horizontal alignment of the text. */
KANZI_API void kzuTextLayouterSetHorizontalAlignment(struct KzuTextLayouter* textLayouter, TextConcept::TextHorizontalAlignment alignment);

/** Sets the vertical alignment of the text. */
KANZI_API void kzuTextLayouterSetVerticalAlignment(struct KzuTextLayouter* textLayouter, TextConcept::TextVerticalAlignment alignment);

/** Sets the line spacing. The value is relative to the font height, for example 1 is normal spacing and 2 is double spacing. */
KANZI_API void kzuTextLayouterSetLineSpacing(struct KzuTextLayouter* textLayouter, kzFloat lineSpacing);

/** Gets the line spacing */
KANZI_API kzFloat kzuTextLayouterGetLineSpacing(const struct KzuTextLayouter* textLayouter);

/** Sets the character spacing. The value is relative to the character advance, for example 1 is the normal advance and 2 is double advance. */
KANZI_API void kzuTextLayouterSetCharacterSpacing(struct KzuTextLayouter* textLayouter, kzFloat characterSpacing);

/** Gets the character spacing */
KANZI_API kzFloat kzuTextLayouterGetCharacterSpacing(const struct KzuTextLayouter* textLayouter);

/** Sets the fixed character width. To disable the feature, set to a non-positive value. */
KANZI_API void kzuTextLayouterSetFixedCharacterWidth(struct KzuTextLayouter* textLayouter, kzFloat fixedCharacterWidth);

/** Gets the fixed character width. */
KANZI_API kzFloat kzuTextLayouterGetFixedCharacterWidth(const struct KzuTextLayouter* textLayouter);

/** Sets whether support for complex scripts is enabled. This includes support for bi-directional text and languages that require ligatures. */
KANZI_API void kzuTextLayouterSetBidiShapingEnabled(struct KzuTextLayouter* textLayouter, kzBool bidiShapingEnabled);

/** Sets whether text side bearings removal is enabled. If enabled removes side bearings for each line separately making text start right next to the sides. */
KANZI_API void kzuTextLayouterSetRemoveSideBearingsEnabled(struct KzuTextLayouter* textLayouter, bool removeSideBearingsEnabled);

/** Gets status of side bearing removal enabled flag of the text. */
KANZI_API bool kzuTextLayouterGetRemoveSideBearingsEnabled(struct KzuTextLayouter* textLayouter);

/**
 * Lays out the given text using the given text layouter.
 * The returned text layout can be directly rendered with the associated font
 * or the layout information can be read from the structure.
 */
KANZI_API kzsError kzuTextLayouterCreateLayout(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                     kzString text, struct KzuTextLayout** out_textLayout);

/**
 * Helper function for performing the layout and drawing the result on the screen. If the same text is rendered more
 * than once, the layout and drawing should be done separately.
 * Parameters x and y specifies where the text layout is drawn and depends on the specified alignments of the text layouter.
 */
KANZI_API kzsError kzuTextLayouterDrawText(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                 kanzi::Renderer* renderer, kzString text, kzFloat x, kzFloat y);

/**
 * Helper function for performing the layout and drawing the result to 3D space. If the same text is rendered more
 * than once, the layout and drawing should be done separately.
 */
KANZI_API kzsError kzuTextLayouterDrawText3D(const struct KzuTextLayouter* textLayouter, const struct KzcMemoryManager* memoryManager,
                                   kanzi::Renderer* renderer, kzString text);

/** Gets the font used for the text layout. */
KANZI_API struct KzuFont* kzuTextLayoutGetFont(const struct KzuTextLayout* textLayout);

/** Deletes the text layout. */
KANZI_API kzsError kzuTextLayoutDelete(struct KzuTextLayout* textLayout);





#endif
