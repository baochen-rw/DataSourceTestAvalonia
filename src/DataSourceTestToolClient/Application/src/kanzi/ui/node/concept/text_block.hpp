// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TEXT_BLOCK_HPP
#define KZ_TEXT_BLOCK_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node/resource_reference.hpp>
#include <kanzi/core.ui/content/text_resource.hpp>

#include <kanzi/core.ui/font/kzu_font_base.h>
#include <kanzi/core.ui/graphics3d/material.hpp>

struct KzuTextFormat;

namespace kanzi
{

/// TextFormat shared pointer.
typedef shared_ptr<KzuTextFormat> TextFormatSharedPtr;


/// TextConcept is base class for nodes that implement text rendering.
class KANZI_UI_API TextBlockConcept
{
public:
    /// Horizontal alignment options for text layout.
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

    /// \name Properties
    /// \{

    /// Use the Font Color property to set the text color for the default font material and for the materials with a fragment shader that uses the FontColor uniform.
    /// The default value is ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f).
    /// \see TextBlockConceptImpl::setFontColor(), TextBlockConceptImpl::getFontColor()
    static PropertyType<ColorRGBA> FontColorProperty;

    /// Use the Font Size property to set the size of the font in device-independent pixels.
    /// The default value is 36.0f.
    /// \see TextBlockConceptImpl::setFontSize(), TextBlockConceptImpl::getFontSize()
    static PropertyType<float> FontSizeProperty;

    /// Use the Font Material property to set the material whose shader is used to render the text. The shader must use the ContentTexture uniform which is automatically filled with glyph data.
    /// The default value is ResourceSharedPtr().
    /// \see TextBlockConceptImpl::setFontMaterial(), TextBlockConceptImpl::getFontMaterial()
    static PropertyType<ResourceSharedPtr> FontMaterialProperty;

    /// Use the Text Horizontal Alignment property to set the horizontal alignment of the text.
    /// The default value is TextBlockConcept::TextHorizontalAlignmentLeft.
    /// \see TextBlockConceptImpl::setTextHorizontalAlignment(), TextBlockConceptImpl::getTextHorizontalAlignment()
    static PropertyType<TextBlockConcept::TextHorizontalAlignment> TextHorizontalAlignmentProperty;

    /// Use the Text Vertical Alignment property to set the vertical alignment of the text.
    /// The default value is TextBlockConcept::TextVerticalAlignmentTop.
    /// \see TextBlockConceptImpl::setTextVerticalAlignment(), TextBlockConceptImpl::getTextVerticalAlignment()
    static PropertyType<TextBlockConcept::TextVerticalAlignment> TextVerticalAlignmentProperty;

    /// Use the Line Spacing property to set the line spacing in multiples of the normal line height of the selected font.
    /// The default value is 1.0f.
    /// \see TextBlockConceptImpl::setLineSpacing(), TextBlockConceptImpl::getLineSpacing()
    static PropertyType<float> LineSpacingProperty;

    /// Use the Character Spacing property to set the character spacing in device-independent pixels.
    /// The default value is 0.0f.
    /// \see TextBlockConceptImpl::setCharacterSpacing(), TextBlockConceptImpl::getCharacterSpacing()
    static PropertyType<float> CharacterSpacingProperty;

    /// Use the Overflow property to set the characters that represent the clipped text when the text string to be rendered is too long to fit in the node.
    /// The default value is "...".
    /// \see TextBlockConceptImpl::setOverflow(), TextBlockConceptImpl::getOverflow()
    static PropertyType<string> OverflowProperty;

    /// Use the Text property to set the text content that the text block renders.
    /// The default value is "Text".
    /// \see TextBlockConceptImpl::setText(), TextBlockConceptImpl::getText()
    static PropertyType<string> TextProperty;

    /// Use the Word Wrap property to break long text lines to multiple lines to make the text fit within the boundaries of the text block.
    /// The default value is true.
    /// \see TextBlockConceptImpl::setWordWrap(), TextBlockConceptImpl::isWordWrap()
    static PropertyType<bool> WordWrapProperty;

    /// Use the Constrain Content Height property to cut out the last lines that do not fit within the boundaries of the text block.
    /// The default value is true.
    /// \see TextBlockConceptImpl::setConstrainContentHeight(), TextBlockConceptImpl::isConstrainContentHeight()
    static PropertyType<bool> ConstrainContentHeightProperty;

    /// Use the Fixed Character Width property to override the font advance widths and make each character take a fixed amount of space specified in device-independent pixels.
    /// The default value is -1.0f.
    /// \see TextBlockConceptImpl::setFixedCharacterWidth(), TextBlockConceptImpl::getFixedCharacterWidth()
    static PropertyType<float> FixedCharacterWidthProperty;

    /// Use the Horizontal Padding property to set the padding spaces between the content and the left and right boundaries of the text block.
    /// The default value is Vector2(0.0f, 0.0f).
    /// \see TextBlockConceptImpl::setHorizontalPadding(), TextBlockConceptImpl::getHorizontalPadding()
    static PropertyType<Vector2> HorizontalPaddingProperty;

    /// Use the Vertical Padding property to set the padding spaces between the content and the top and bottom boundaries of the text block.
    /// The default value is Vector2(0.0f, 0.0f).
    /// \see TextBlockConceptImpl::setVerticalPadding(), TextBlockConceptImpl::getVerticalPadding()
    static PropertyType<Vector2> VerticalPaddingProperty;

    /// Use the Remove Side Bearings property to position the leftmost characters of left-aligned text and rightmost characters of right-aligned text exactly within the boundary of the text block.
    /// The default value is false.
    static PropertyType<bool> RemoveSideBearingsProperty;

    /// \}

    KZ_MIXIN_METACLASS_BEGIN(TextBlockConcept, "Kanzi.TextBlockConcept")
        KZ_METACLASS_PROPERTY_TYPE(FontSizeProperty)
        KZ_METACLASS_PROPERTY_TYPE(FontMaterialProperty)
        KZ_METACLASS_PROPERTY_TYPE(FontColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextHorizontalAlignmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextVerticalAlignmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(LineSpacingProperty)
        KZ_METACLASS_PROPERTY_TYPE(CharacterSpacingProperty)
        KZ_METACLASS_PROPERTY_TYPE(OverflowProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextProperty)
        KZ_METACLASS_PROPERTY_TYPE(WordWrapProperty)
        KZ_METACLASS_PROPERTY_TYPE(ConstrainContentHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(FixedCharacterWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(HorizontalPaddingProperty)
        KZ_METACLASS_PROPERTY_TYPE(VerticalPaddingProperty)
        KZ_METACLASS_PROPERTY_TYPE(RemoveSideBearingsProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

/// TextConceptImplementation is an abstract class for implementing text concept.
template<typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API TextBlockConceptImpl: public TBaseClass, public TextBlockConcept
{
    TDerivedClass* getThisObject();

    const TDerivedClass* getThisObject() const;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(TextBlockConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(TextBlockConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of the #FontSizeProperty.
    /// \return The size of the font in device independent pixels.
    /// \see setFontSize()
    float getFontSize() const;

    /// Sets the value of the #FontSizeProperty.
    /// \param value The size of the font in device independent pixels.
    /// \see getFontSize()
    void setFontSize(float value);

    /// Gets the value of the #FontMaterialProperty.
    /// \return The font material currently in use.
    /// \see setFontMaterial()
    MaterialSharedPtr getFontMaterial() const;

    /// Sets the value of the #FontMaterialProperty.
    /// \param value The font material.
    /// \see getFontMaterialResourceID()
    void setFontMaterial(MaterialSharedPtr value);

    /// Gets the value of the #FontColorProperty.
    /// \return The color value of the default font material, or the color value of materials with fragment shader that uses the FontColor uniform. Returns the value in range [0,1].
    /// \see setFontColor()
    ColorRGBA getFontColor() const;

    /// Sets the value of the #FontColorProperty.
    /// \param value The ColorRGBA color value of the font material with fragment shader that uses the FontColor uniform.
    /// \see getFontColor()
    void setFontColor(ColorRGBA value);

    /// Gets the value of the #TextHorizontalAlignmentProperty.
    /// \return The horizontal alignment of the object.
    /// \see setTextHorizontalAlignment()
    TextHorizontalAlignment getTextHorizontalAlignment() const;

    /// Sets the value of the #TextHorizontalAlignmentProperty.
    /// \param value One of the #TextHorizontalAlignment enumerator values.
    /// \see getTextHorizontalAlignment()
    void setTextHorizontalAlignment(TextHorizontalAlignment value);

    /// Gets the value of the #TextVerticalAlignmentProperty.
    /// \return The vertical alignment of the object.
    /// \see setTextVerticalAlignment()
    TextVerticalAlignment getTextVerticalAlignment() const;

    /// Sets the value of the #TextVerticalAlignmentProperty.
    /// \param value One of the #TextVerticalAlignment enumerator values.
    /// \see getTextVerticalAlignment()
    void setTextVerticalAlignment(TextVerticalAlignment value);

    /// Gets the value of the #LineSpacingProperty.
    /// \return The line spacing in multiples of the normal line height of the selected font.
    /// \see setLineSpacing()
    float getLineSpacing() const;

    /// Sets the value of the #LineSpacingProperty.
    /// \param value The line spacing in multiples of the normal line height of the selected font.
    /// \see getLineSpacing()
    void setLineSpacing(float value);

    /// Gets the value of the #CharacterSpacingProperty.
    /// \return The character spacing in device independent pixels.
    /// \see setCharacterSpacing()
    float getCharacterSpacing() const;

    /// Sets the value of the #CharacterSpacingProperty.
    /// \param value The character spacing in device independent pixels.
    /// \see getCharacterSpacing()
    void setCharacterSpacing(float value);

    /// Gets the value of the #FixedCharacterWidthProperty.
    /// \return The fixed character width in device independent pixels.
    /// \see setFixedCharacterWidth()
    float getFixedCharacterWidth() const;

    /// Sets the value of the #FixedCharacterWidthProperty.
    /// \param value The fixed character width in device independent pixels.
    /// \see getFixedCharacterWidth()
    void setFixedCharacterWidth(float value);

    /// Gets the value of the #OverflowProperty.
    /// \return The characters that represent the clipped text when the text string is too long to fit in the node.
    /// \see setOverflow()
    string getOverflow() const;

    /// Sets the value of the #OverflowProperty.
    /// \param value The characters that represent the clipped text when the text string is too long to fit in the node.
    /// \see getOverflow()
    void setOverflow(string_view value);

    /// Gets the value of #TextProperty.
    /// \see setText()
    string getText() const;

    /// Sets the value of #TextProperty.
    /// \see getText()
    void setText(string value);

    /// Gets the value of #WordWrapProperty.
    /// \see setWordWrap()
    bool isWordWrap() const;

    /// Sets the value of #WordWrapProperty.
    /// \see isWordWrap()
    void setWordWrap(bool value);

    /// Gets the value of #ConstrainContentHeightProperty.
    /// \see setConstrainContentHeight()
    bool isConstrainContentHeight() const;

    /// Sets the value of #ConstrainContentHeightProperty.
    /// \see isConstrainContentHeight()
    void setConstrainContentHeight(bool value);

    /// Gets the value of #HorizontalPaddingProperty.
    /// \see setHorizontalPadding()
    Vector2 getHorizontalPadding() const;

    /// Sets the value of #HorizontalPaddingProperty.
    /// \see getHorizontalPadding()
    void setHorizontalPadding(Vector2 value);

    /// Gets the value of #VerticalPaddingProperty.
    /// \see setVerticalPadding()
    Vector2 getVerticalPadding() const;

    /// Sets the value of #VerticalPaddingProperty.
    /// \see getVerticalPadding()
    void setVerticalPadding(Vector2 value);

    /// Get bounding rectangle for the text.
    ///
    /// \return Rectangle.
    KzcRectangle getTextBounds() const;

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit TextBlockConceptImpl(Domain* domain, string_view name);

    /// Position the text.
    /// \param textFormatWidth The width of the area available for the glyphs in font units. Set to infinity for an unbound area.
    /// \param textFormatHeight The height of the area available for the glyphs in font units. Set to infinity for an unbound area.
    /// \param constrainToActualSize Flag indicating whether text format should be constrained to actual size provided by layout. Set to false to use unconstrained layout.
    void prepareTextFormat(float textFormatWidth, float textFormatHeight, bool constrainToActualSize);

    /// Position the text.
    /// \param textFormatWidth The width of the area available for the glyphs in font units. Set to infinity for an unbound area.
    /// \param textFormatHeight The height of the area available for the glyphs in font units. Set to infinity for an unbound area.
    /// \param measure Indicates whether Kanzi executes measure or arrange phase during the layouting of the node.
    ///                For the measure phase use True, for the arrange phase use False.
    /// \param ceiledSizes Flag indicating whether the textFormatWidth and textFormatHeight have be ceiled before passing to this function.
    void prepareTextFormat(float textFormatWidth, float textFormatHeight, bool measure, bool ceiledSizes);

    /// Node::onPropertyChanged implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// When in measure layouting phase, Kanzi calls this function every time it completes the prepareTextFormat function.
    /// \param completeRelayoutingExecuted Indicates whether a complete relayouting of the glyphs was required during the
    ///                                    measure phase.
    virtual void onPostPrepareTextFormatMeasure(bool completeRelayoutingExecuted);

    /// When in arrange layouting phase, Kanzi calls this function every time it completes the prepareTextFormat function.
    /// \param completeRelayoutingExecuted Indicates whether a complete relayouting of the glyphs was required during the
    ///                                    arrange phase.
    virtual void onPostPrepareTextFormatArrange(bool completeRelayoutingExecuted);

    /// Font resource reference.
    FontSharedPtr m_cachedFont;

    /// The text layout for the glyphs that this node displays.
    TextFormatSharedPtr m_textFormat;

#ifdef KANZI_FEATURE_3D
    /// Default value for font material property.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueFontMaterialProperty;
    /// Default value for font property.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueFontProperty;
#endif

private:
    /// Kanzi calls this function every time it completes the prepareTextFormat function.
    /// \param completeRelayoutingExecuted Indicates whether a complete relayouting of the glyphs was required
    ///                                    while preparing the text format.
    /// \param measure Indicates whether Kanzi executes measure or arrange phase during the layouting of the node.
    ///                For the measure phase use True, for the arrange phase use False.
    void notifyPostPrepareTextFormat(bool completeRelayoutingExecuted, bool measure);
    
    /// Cached text.
    string m_cachedText;
};

}

#endif
