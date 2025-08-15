/**
 * \file
 * Text Renderer.
 *
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZU_TEXT_RENDERER_H
#define KZU_TEXT_RENDERER_H

#include <kanzi/core/math/rectangle.hpp>
#include <kanzi/core/cpp/memory.hpp>

#include <kanzi/core.ui/text/kzu_text_layouter.h>

 // Forward declaration.
struct KzcMemoryManager;
struct KzuFont;
struct KzcRectangle;
struct KzuBitmapFontSystem;
struct KzuTruetypeSystem;
struct KzuCharacterLayout;

namespace kanzi
{

// Forward declaration.
class Material;
class Node;
class ResourceManager;
class Renderer3D;
class Texture;
typedef shared_ptr<Material> MaterialSharedPtr;
typedef shared_ptr<Node> NodeSharedPtr;
typedef shared_ptr<Texture> TextureSharedPtr;

}

/// Text renderer creates and renders text layouts.
struct KzuTextRenderer;

/// Text format combines the data that is needed for text layouting and the data that is needed for rendering the text.
struct KzuTextFormat;

namespace kanzi
{

/// Text format shared pointer.
typedef shared_ptr<KzuTextFormat> TextFormatSharedPtr;

}

/** Pointer to a function that creates a text layouter. */
typedef kzsError (*kzuTextRendererCreateTextLayouterFunction)(const struct KzcMemoryManager* memoryManager, struct KzuFont* font,
                                                              void* userData, struct KzuTextLayouter** out_textLayouter);

/** Creates a text renderer. */
KANZI_API kzsError kzuTextRendererCreate(const KzcMemoryManager* memoryManager, kanzi::ResourceManager* resourceManager, KzuTextRenderer** out_textRenderer);

/** Deletes a text renderer. */
KANZI_API kzsError kzuTextRendererDelete(struct KzuTextRenderer* textRenderer);

/** Clears all resources that the text renderer holds. */
KANZI_API void kzuTextRendererClearResources(struct KzuTextRenderer* textRenderer);

/** Returns the text manager of the text renderer. */
KANZI_API struct KzuTextManager* kzuTextRendererGetTextManager(const struct KzuTextRenderer* textRenderer);

/** Creates a text layout. The text layout specifies the maximum area which can be used to layout text. The width and height are specified in pixels and they can be KZS_INFINITY for an unbounded area. */
KANZI_API kanzi::TextFormatSharedPtr kzuTextRendererCreateTextFormat(const struct KzuTextRenderer* textRenderer, struct KzuFont* font, kzFloat fontSize, kzFloat width, kzFloat height);


/** Gets the maximum width of the text. */
KANZI_API kzFloat kzuTextFormatGetMaximumWidth(const struct KzuTextFormat* textFormat);

/** Gets the maximum height of the text. */
KANZI_API kzFloat kzuTextFormatGetMaximumHeight(const struct KzuTextFormat* textFormat);

/** Gets the the font of the text. */
KANZI_API KzuFont* kzuTextFormatGetFont(const struct KzuTextFormat* textFormat);

/** Gets the font size of the text. */
KANZI_API kzFloat kzuTextFormatGetFontSize(const struct KzuTextFormat* textFormat);

/** Sets the horizontal alignment of the text. */
KANZI_API void kzuTextFormatSetTextHorizontalAlignment(struct KzuTextFormat* textFormat, TextConcept::TextHorizontalAlignment alignment);

/** Gets the horizontal alignment of the text. */
KANZI_API TextConcept::TextHorizontalAlignment kzuTextFormatGetTextHorizontalAlignment(const struct KzuTextFormat* textFormat);

/** Sets the vertical alignment of the text. */
KANZI_API void kzuTextFormatSetTextVerticalAlignment(struct KzuTextFormat* textFormat, TextConcept::TextVerticalAlignment alignment);

/** Gets the vertical alignment of the text. */
KANZI_API TextConcept::TextVerticalAlignment kzuTextFormatGetTextVerticalAlignment(const struct KzuTextFormat* textFormat);

/** Sets the line spacing of the text. The line spacing is specified in multiples of the normal line height which is specified by the font. */
KANZI_API void kzuTextFormatSetLineSpacing(const struct KzuTextFormat* textFormat, kzFloat lineSpacing);

/** Gets the line spacing of the text. */
KANZI_API kzFloat kzuTextFormatGetLineSpacing(const struct KzuTextFormat* textFormat);

/** Sets the character spacing of the text. The character spacing is specified in multiples of the normal character spacing which is specified by the font. */
KANZI_API void kzuTextFormatSetCharacterSpacing(const struct KzuTextFormat* textFormat, kzFloat characterSpacing);

/** Gets the character spacing of the text. */
KANZI_API kzFloat kzuTextFormatGetCharacterSpacing(const struct KzuTextFormat* textFormat);

/** Sets the fixed character width of the text. The character width is specified in pixels. */
KANZI_API void kzuTextFormatSetFixedCharacterWidth(const struct KzuTextFormat* textFormat, kzFloat fixedCharacterWidth);

/** Gets the fixed character width of the text. */
KANZI_API kzFloat kzuTextFormatGetFixedCharacterWidth(const struct KzuTextFormat* textFormat);

/** Sets the overflow text that is displayed when the text doesn't fit to the layout. */
KANZI_API kzsError kzuTextFormatSetOverflow(const struct KzuTextFormat* textFormat, kzString overflowText);

/** Gets the overflow text that is displayed when the text doesn't fit to the layout. */
KANZI_API kzString kzuTextFormatGetOverflow(const struct KzuTextFormat* textFormat);

/** Sets whether support for complex scripts is enabled. This includes support for bi-directional text and languages that require ligatures. */
KANZI_API void kzuTextFormatSetBidiShapingEnabled(const struct KzuTextFormat* textFormat, kzBool bidiShapingEnabled);

/** Sets whether text side bearings removal is enabled. If enabled removes side bearings for each line separately making text start right next to the sides. */
KANZI_API void kzuTextFormatSetRemoveSideBearingsEnabled(const struct KzuTextFormat* textFormat, bool removeSideBearingsEnabled);

/** Gets status of side bearing removal enabled flag of the text. */
KANZI_API bool kzuTextFormatGetRemoveSideBearingsEnabled(const struct KzuTextFormat* textFormat);

/** Calculates the text layout. */
KANZI_API kzsError kzuTextFormatCalculateLayout(struct KzuTextFormat* textFormat, kzString text);

/** Gets the width of the area that the text layout actually used. The width is returned in pixels. The text layout must be calculated before calling this function. */
KANZI_API kzFloat kzuTextFormatGetWidth(const struct KzuTextFormat* textFormat);

/** Gets the height of the area that the text layout actually used. The height is returned in pixels. The text layout must be calculated before calling this function. */
KANZI_API kzFloat kzuTextFormatGetHeight(const struct KzuTextFormat* textFormat);

/** Gets the layout structure of the given character. The text layout must be calculated before calling this function. */
KANZI_API const KzuCharacterLayout* kzuTextFormatGetCharacterLayout(const struct KzuTextFormat* textFormat, kzUint index);

/** Gets the text layout structure. The text layout must be calculated before calling this function. */
KANZI_API KzuTextLayout* kzuTextFormatGetLayout(const struct KzuTextFormat* textFormat);

/** Gets the count of characters. The text layout must be calculated before calling this function. */
KANZI_API kzUint kzuTextFormatGetCharacterCount(const struct KzuTextFormat* textFormat);

/** Checks if text layout has generated glyph run. */
KANZI_API kzBool kzuTextFormatHasGlyphRun(const struct KzuTextFormat* textFormat);

/** Checks if layouted text got truncated, i.e. it did not fit. The text layout must be calculated before calling this function. */
KANZI_API kzBool kzuTextFormatIsTruncated(const struct KzuTextFormat* textFormat);

/**
 * Prepares a text layout for rendering in 3d space, where x-coordinates increase to the right and y-coordinates increase going upward. The z-coordinate of the text is always 0.0f.
 * The pixel size of the text font is multiplied by the scale to get the size of the text in the 3d space. The text offsets given in 3d space units are used to calculate
 * proper horizontal aligning. They should be set to half of the width and height of the whole text format.
 */
KANZI_API void kzuTextFormatPrepareForRendering3D(struct KzuTextFormat* textFormat, kzFloat unitScale, kzFloat offsetX, kzFloat offsetY);

/**
 * Prepares a text layout for rendering in a bounded 3d space. Generates unclipped vertex positions and bounding box coordinates for the clipping function to use.
 */
KANZI_API void kzuTextFormatPrepareForRendering3DWithClipping(struct KzuTextFormat* textFormat, kzFloat unitScale, const kanzi::Rectangle<float>* clippingRectangle,
                                                              kzFloat offsetX, kzFloat offsetY);

/**
 * Prepares a text layout for rendering in 2d space, where x-coordinates increase to the right and y-coordinates increase going downward. The pixel size of the text font is multiplied by
 * the scale to get the size of the text in the 2d space.
 */
KANZI_API void kzuTextFormatPrepareForRendering2D(struct KzuTextFormat* textFormat, kzFloat unitScale, kzFloat offsetX, kzFloat offsetY);

/**
 * Prepares a text layout for rendering in a bounded 2d space. Generates unclipped vertex positions and bounding box coordinates for the clipping function to use.
 */
KANZI_API void kzuTextFormatPrepareForRendering2DWithClipping(struct KzuTextFormat* textFormat, kzFloat unitScale, const kanzi::Rectangle<float>* clippingArea,
                                                              kzFloat offsetX, kzFloat offsetY);

/**
 * Calculates clipped vertex coordinates from the bounding coordinates generated in the preparation function. Characters that are outside the bounded area are clipped completely, and 
 * characters that are on the border of area are clipped so that only part of the character is visible.
 */
KANZI_API kzsError kzuTextFormatCalculateClipping(struct KzuTextFormat* textFormat, const kanzi::Rectangle<float>* clippingArea);

/**
* Get clipped bounding rectangle for text format.
*
* \param textFormat Text format to query.
* \return Rectangle.
*/
KANZI_API KzcRectangle kzuTextFormatGetBoundingRectangle(const struct KzuTextFormat* textFormat);

/**
* Acquire texture for rendering text format.
*
* \param textRenderer Text renderer to use.
* \param textFormat Text format to render.
* \return Glyph texture.
*/
KANZI_API kanzi::TextureSharedPtr kzuTextRendererGetGlyphTexture(const struct KzuTextRenderer* textRenderer, const struct KzuTextFormat* textFormat);

/// Renders text format.
/// Used for rendering with a brush or material renderer. Shader and glyph texture are assumed to be
/// already bound by brush or material renderer.
///
/// If two-pass rendering is enabled, all color information is first written with depth write disabled
/// and then in the second pass depth information is written with color write disabled. This is slower than
/// rendering in one pass, but needed for correct rendering result when glyph bounds are overlapping.
///
/// \param textRenderer Text renderer to use.
/// \param renderer Renderer to use.
/// \param textFormat Text format to draw.
KANZI_API kzsError kzuTextRendererDrawTextFormatBrush(const struct KzuTextRenderer* textRenderer, kanzi::Renderer3D* renderer, const struct KzuTextFormat* textFormat, bool twoPass);

/// Renders a text format. The text format must be calculated and prepared for rendering before calling this function.
/// If the material is KZ_NULL, uses the default font material.
KANZI_API kzsError kzuTextRendererDrawTextFormat(const struct KzuTextRenderer* textRenderer, kanzi::Renderer3D* renderer, const struct KzuTextFormat* textFormat, const kanzi::Node* node, kanzi::Material& material);

/** Gets a bitmap font system. It is created and deleted automatically if necessary. */
KANZI_API kzsError kzuTextRendererGetBitmapFontSystem(struct KzuTextRenderer* textRenderer, struct KzuBitmapFontSystem** out_bitmapFontSystem);

/** Gets a TrueType font system. It is created and deleted automatically if necessary. */
KANZI_API kzsError kzuTextRendererGetTruetypeSystem(struct KzuTextRenderer* textRenderer, struct KzuTruetypeSystem** out_truetypeSystem);
/** Sets a TrueType font system, which overrides the default TrueType system. */
KANZI_API kzsError kzuTextRendererSetTruetypeSystem(struct KzuTextRenderer* textRenderer, struct KzuTruetypeSystem* truetypeSystem);

/** Sets a creator function for creating text layouters. Pass KZ_NULL as the function to reset to the default implementation. */
KANZI_API kzsError kzuTextRendererSetTextLayouterCreator(struct KzuTextRenderer* textRenderer, kzuTextRendererCreateTextLayouterFunction createFunction, void* userData);


#endif
