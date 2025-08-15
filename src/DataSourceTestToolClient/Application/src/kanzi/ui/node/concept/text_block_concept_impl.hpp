// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_TEXT_CONCEPT_IMPL_HPP
#define KZU_TEXT_CONCEPT_IMPL_HPP

#include <kanzi/core.ui/assets/runtime_assets.hpp>
#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node/resource_reference.hpp>
#include <kanzi/core.ui/text/kzu_text_renderer.h>
#include <kanzi/ui/node/concept/text_block.hpp>

#include <kanzi/core/legacy/util/math/kzc_rectangle.hpp>

namespace kanzi
{
namespace
{
inline bool checkTextFormatSize(const KzuTextFormat* textFormat, float newTextFormatWidth, float newTextFormatHeight, bool measure, bool ceiledSizes)
{
    // The getMaximumWidth() method returns inf if maximum value is not specified.
    float cachedTextFormatWidth = kzuTextFormatGetMaximumWidth(textFormat);
    float cachedTextFormatHeight = kzuTextFormatGetMaximumHeight(textFormat);

    if (measure)
    {
        // Check whether last time text format was created with same maximum width & height as requested now.
        // Re-measure if that is not the case.
        if (cachedTextFormatWidth == newTextFormatWidth && cachedTextFormatHeight == newTextFormatHeight)
        {
            return true;
        }
        return false;
    }

    // Arrange

    // Possible combinations:
    // 1. GetMaximumWidth() = inf  && newTextFormatWidth = !inf and equal to current text format width. (Do not re-create text format.)
    // 2. GetMaximumWidth() = inf  && newTextFormatWidth = !inf but greater than current text format width. (Do not re-create text format.)
    // 3. GetMaximumWidth() = inf  && newTextFormatWidth = !inf but less than current text format width. (Re-create text format.)
    // 4. GetMaximumWidth() = inf  && newTextFormatWidth = inf (Do not re-create text format.)
    // 5. GetMaximumWidth() = !inf && newTextFormatWidth = inf (Re-create text format anyway.)
    // 6. GetMaximumWidth() = !inf && newTextFormatWidth = !inf (Can be same size or not. If not, re-create text format.)
    //
    // In cases 1-3 compare against actual size of the text format.
    if (!isfinite(cachedTextFormatWidth) && isfinite(newTextFormatWidth))
    {
        cachedTextFormatWidth = kzuTextFormatGetWidth(textFormat);
        if(ceiledSizes)
        {
            cachedTextFormatWidth = kzsCeilf(cachedTextFormatWidth);
        }
        if (cachedTextFormatWidth < newTextFormatWidth) // case 2
        {
            cachedTextFormatWidth = newTextFormatWidth;
        }
    }
    if (!isfinite(cachedTextFormatHeight) && isfinite(newTextFormatHeight))
    {
        cachedTextFormatHeight = kzuTextFormatGetHeight(textFormat);
        if (ceiledSizes)
        {
            cachedTextFormatHeight = kzsCeilf(cachedTextFormatHeight);
        }
        
        if (cachedTextFormatHeight < newTextFormatHeight) // case 2
        {
            cachedTextFormatHeight = newTextFormatHeight;
        }
    }
    return cachedTextFormatWidth == newTextFormatWidth &&
           cachedTextFormatHeight == newTextFormatHeight;
}

inline bool checkFixedCharacterWidth(const float textFormatFixedCharacterWidth, const float requiredFixedCharacterWidth)
{
    return textFormatFixedCharacterWidth == requiredFixedCharacterWidth ||
           (textFormatFixedCharacterWidth <= 0 && requiredFixedCharacterWidth <= 0);
}
}

template <typename TBaseClass, typename TDerivedClass>
TDerivedClass* TextBlockConceptImpl<TBaseClass, TDerivedClass>::getThisObject()
{
    return static_cast<TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
const TDerivedClass* TextBlockConceptImpl<TBaseClass, TDerivedClass>::getThisObject() const
{
    return static_cast<const TDerivedClass*>(this);
}

template <typename TBaseClass, typename TDerivedClass>
float TextBlockConceptImpl<TBaseClass, TDerivedClass>::getFontSize() const
{
    return getThisObject()->getProperty(FontSizeProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setFontSize(float value)
{
    getThisObject()->setProperty(FontSizeProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
MaterialSharedPtr TextBlockConceptImpl<TBaseClass, TDerivedClass>::getFontMaterial() const
{
    return dynamic_pointer_cast<Material>(getThisObject()->getProperty(FontMaterialProperty));
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setFontMaterial(MaterialSharedPtr value)
{
    getThisObject()->setProperty(FontMaterialProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
ColorRGBA TextBlockConceptImpl<TBaseClass, TDerivedClass>::getFontColor() const
{
    return getThisObject()->getProperty(FontColorProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setFontColor(ColorRGBA value)
{
    getThisObject()->setProperty(FontColorProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
TextBlockConcept::TextHorizontalAlignment TextBlockConceptImpl<TBaseClass, TDerivedClass>::getTextHorizontalAlignment() const
{
    return getThisObject()->getProperty(TextHorizontalAlignmentProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setTextHorizontalAlignment(TextBlockConcept::TextHorizontalAlignment value)
{
    getThisObject()->setProperty(TextHorizontalAlignmentProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
TextBlockConcept::TextVerticalAlignment TextBlockConceptImpl<TBaseClass, TDerivedClass>::getTextVerticalAlignment() const
{
    return getThisObject()->getProperty(TextVerticalAlignmentProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setTextVerticalAlignment(TextBlockConcept::TextVerticalAlignment value)
{
    getThisObject()->setProperty(TextVerticalAlignmentProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
float TextBlockConceptImpl<TBaseClass, TDerivedClass>::getLineSpacing() const
{
    return getThisObject()->getProperty(LineSpacingProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setLineSpacing(float value)
{
    getThisObject()->setProperty(LineSpacingProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
float TextBlockConceptImpl<TBaseClass, TDerivedClass>::getCharacterSpacing() const
{
    return getThisObject()->getProperty(CharacterSpacingProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setCharacterSpacing(float value)
{
    getThisObject()->setProperty(CharacterSpacingProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
float TextBlockConceptImpl<TBaseClass, TDerivedClass>::getFixedCharacterWidth() const
{
    return getThisObject()->getProperty(FixedCharacterWidthProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setFixedCharacterWidth(float value)
{
    getThisObject()->setProperty(FixedCharacterWidthProperty, value);
}


template <typename TBaseClass, typename TDerivedClass>
string TextBlockConceptImpl<TBaseClass, TDerivedClass>::getOverflow() const
{
    return getThisObject()->getProperty(OverflowProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setOverflow(string_view value)
{
    getThisObject()->setProperty(OverflowProperty, string(value));
}

template <typename TBaseClass, typename TDerivedClass>
string TextBlockConceptImpl<TBaseClass, TDerivedClass>::getText() const
{
    return getThisObject()->getProperty(TextProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setText(string value)
{
    getThisObject()->setProperty(TextProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
bool TextBlockConceptImpl<TBaseClass, TDerivedClass>::isWordWrap() const
{
    return getThisObject()->getProperty(WordWrapProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setWordWrap(bool value)
{
    getThisObject()->setProperty(WordWrapProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
bool TextBlockConceptImpl<TBaseClass, TDerivedClass>::isConstrainContentHeight() const
{
    return getThisObject()->getProperty(ConstrainContentHeightProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setConstrainContentHeight(bool value)
{
    getThisObject()->setProperty(ConstrainContentHeightProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
Vector2 TextBlockConceptImpl<TBaseClass, TDerivedClass>::getHorizontalPadding() const
{
    return getThisObject()->getProperty(HorizontalPaddingProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setHorizontalPadding(Vector2 value)
{
    getThisObject()->setProperty(HorizontalPaddingProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
Vector2 TextBlockConceptImpl<TBaseClass, TDerivedClass>::getVerticalPadding() const
{
    return getThisObject()->getProperty(VerticalPaddingProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::setVerticalPadding(Vector2 value)
{
    getThisObject()->setProperty(VerticalPaddingProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
TextBlockConceptImpl<TBaseClass, TDerivedClass>::TextBlockConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name)
#ifdef KANZI_FEATURE_3D
    ,
    m_classValueFontMaterialProperty(*this, FontMaterialProperty, Material::acquireDefaultFontMaterial(*this->getResourceManager())),
    m_classValueFontProperty(*this, Node::FontProperty, this->getResourceManager()->acquireResource(KZ_RUNTIME_ASSETS_URL_PREFIX "Resource Files/Fonts/DefaultFont.ttf"))
#endif
{
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::prepareTextFormat(float textFormatWidth, float textFormatHeight, bool constrainToActualSize)
{
    prepareTextFormat(textFormatWidth, textFormatHeight, !constrainToActualSize, false);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::prepareTextFormat(float textFormatWidth, float textFormatHeight, bool measure, bool ceiledSizes)
{
    const float zeroSize = 0.0001f;
    const float maxSize = 9999.0f;

    if (!m_cachedFont)
    {
        m_textFormat.reset();
        return;
    }

    const float fontSize = getFontSize();
    // Don't allow invalid values for font size.
    // In some rare cases the fontSize might be set to inf or a very large number, eg. when font size has bindings related to screen/container sizes.
    if (fontSize <= zeroSize || fontSize >= maxSize)
    {
        m_textFormat.reset();
        return;
    }

    // Get the rest of the parameters.
    const string text = getText();
    const float lineSpacing = getLineSpacing();
    const float characterSpacing = getCharacterSpacing();
    const TextHorizontalAlignment textHorizontalAlignment = getTextHorizontalAlignment();
    const TextVerticalAlignment textVerticalAlignment = getTextVerticalAlignment();
    const string overflowText = getOverflow();
    const float fixedCharacterWidth = getFixedCharacterWidth();
    const bool removeSideBearingsEnabled = getThisObject()->getProperty(RemoveSideBearingsProperty);

    if (m_textFormat)
    {
        kzString cachedOverflowText = kzuTextFormatGetOverflow(m_textFormat.get());
        const bool textFormatSizeMatches = checkTextFormatSize(m_textFormat.get(), textFormatWidth, textFormatHeight, measure, ceiledSizes);
        if (textFormatSizeMatches &&
            text == m_cachedText &&
            m_cachedFont.get() == kzuTextFormatGetFont(m_textFormat.get()) &&
            fontSize == kzuTextFormatGetFontSize(m_textFormat.get()) &&
            lineSpacing == kzuTextFormatGetLineSpacing(m_textFormat.get()) &&
            characterSpacing == kzuTextFormatGetCharacterSpacing(m_textFormat.get()) &&
            textHorizontalAlignment == static_cast<TextHorizontalAlignment>(kzuTextFormatGetTextHorizontalAlignment(m_textFormat.get())) &&
            textVerticalAlignment == static_cast<TextVerticalAlignment>(kzuTextFormatGetTextVerticalAlignment(m_textFormat.get())) &&
            checkFixedCharacterWidth(kzuTextFormatGetFixedCharacterWidth(m_textFormat.get()), fixedCharacterWidth) &&
            removeSideBearingsEnabled == kzuTextFormatGetRemoveSideBearingsEnabled(m_textFormat.get()) &&
            ((cachedOverflowText && (overflowText == cachedOverflowText)) || overflowText.empty()))
        {
            // All parameters match, use same text format.
            return;
        }
    }
    kzsError result;
    Domain* domain = getThisObject()->getDomain();
    KzuTextRenderer* textRenderer = domain->getTextRenderer();

    m_textFormat = kzuTextRendererCreateTextFormat(textRenderer, m_cachedFont.get(), fontSize, textFormatWidth, textFormatHeight);

    kzuTextFormatSetTextHorizontalAlignment(m_textFormat.get(), static_cast<TextConcept::TextHorizontalAlignment>(textHorizontalAlignment));
    kzuTextFormatSetTextVerticalAlignment(m_textFormat.get(), static_cast<TextConcept::TextVerticalAlignment>(textVerticalAlignment));
    kzuTextFormatSetLineSpacing(m_textFormat.get(), lineSpacing);
    kzuTextFormatSetCharacterSpacing(m_textFormat.get(), characterSpacing);
    kzuTextFormatSetFixedCharacterWidth(m_textFormat.get(), fixedCharacterWidth);
    kzuTextFormatSetRemoveSideBearingsEnabled(m_textFormat.get(), removeSideBearingsEnabled);
    result = kzuTextFormatSetOverflow(m_textFormat.get(), overflowText.c_str());
    kzThrowIfError(result);

    result = kzuTextFormatCalculateLayout(m_textFormat.get(), text.c_str());
    kzThrowIfError(result);

    m_cachedText = text;
    notifyPostPrepareTextFormat(true, measure);
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (propertyType == Node::FontProperty)
    {
        m_cachedFont = dynamic_pointer_cast<KzuFont>(TBaseClass::getProperty(Node::FontProperty));
    }
}


template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::onPostPrepareTextFormatMeasure(bool /*completeRelayoutingExecuted*/)
{
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::onPostPrepareTextFormatArrange(bool /*completeRelayoutingExecuted*/)
{
}

template <typename TBaseClass, typename TDerivedClass>
void TextBlockConceptImpl<TBaseClass, TDerivedClass>::notifyPostPrepareTextFormat(bool completeRelayoutingExecuted, bool measure)
{
    if (measure)
    {
        onPostPrepareTextFormatMeasure(completeRelayoutingExecuted);
    }
    else
    {
        onPostPrepareTextFormatArrange(completeRelayoutingExecuted);
    }
}

template <typename TBaseClass, typename TDerivedClass>
KzcRectangle TextBlockConceptImpl<TBaseClass, TDerivedClass>::getTextBounds() const
{
    return kzuTextFormatGetBoundingRectangle(m_textFormat.get());
}

template <typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr TextBlockConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Text Block";

                return dict;
            }()));
}

}

#endif
