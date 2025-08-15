// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_TEXT_LAYER_H
#define KZU_TEXT_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/text_block.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{


// Forward declarations.
class TextBlock2D;


/// TextLayer shared pointer.
typedef shared_ptr<TextBlock2D> TextBlock2DSharedPtr;


/// Text Block 2D displays a small amount of text in 2D.
///
/// \see For a 3D text node, see TextBlock3D.
///
/// Examples
/// ----
/// 
/// To create a Text Block 2D node:
/// \snippet test_text_block2d.cpp Create
/// 
/// To set the font of a text block:
/// \snippet test_text_block2d.cpp Set font
/// 
/// To add the text shown by a text block:
/// \snippet test_text_block2d.cpp Add text
/// 
/// To adjust the appearance of the text:
/// \snippet test_text_block2d.cpp Style text
class KANZI_UI_API TextBlock2D : public TextBlockConceptImpl<Node2D, TextBlock2D>
{
public:

    typedef TextBlockConceptImpl<Node2D, TextBlock2D> ConceptClass;

    /// Creates a TextBlock2D node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static TextBlock2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(TextBlock2D, ConceptClass, "Kanzi.TextBlock2D")
    KZ_METACLASS_END()

    static TextBlock2DSharedPtr create(Domain* domain, string_view name, string_view text);

    /// Returns glyph rectangle of given index in layer space 
    KzcRectangle getGlyphPosition(size_t index) const;

protected:
    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit TextBlock2D(Domain* domain, string_view name);

    /// Node2D::measure() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    /// Node2D::arrange() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

    /// Node2D::updateRenderOverride() implementation.
    virtual void updateRenderOverride() KZ_OVERRIDE;

    /// Node2D::onAttached() implementation.
    virtual void onAttached() KZ_OVERRIDE;
    /// Node2D::onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Node2D::renderSelfOverride() implementation.
    virtual void renderSelfOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform) KZ_OVERRIDE;

    /// Node2D::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Positions the text and prepares the rendering data.
    void arrangeText();

    /// Returns how much the text format needs to be translated so that it is positioned according to the alignment properties.
    /// \return Offset in x and y-directions.
    Vector2 calculateAlignmentOffset() const;

private:

#ifdef SPANSION
    /// Utility for simplified text rendering 
    bool renderToBuffer(Renderer3D& renderer, const Matrix3x3& baseTransform);
#endif

    /// calculate and set text offset within a target space
    void adjustTextOffset(float targetWidth, float targetHeight, float& offsetX, float& offsetY);

    /// Default value for foreground brush.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueForegroundBrush;

    /// Default value for constrain text layout height.
    ClassPropertyDefaultValue<bool> m_classValueConstrainTextLayoutHeight;

    /// Default value for clip children.
    ClassPropertyDefaultValue<bool> m_classValueClipChildren;

    /// The alignment offset that was used last time the text format was prepared for rendering.
    Vector2 m_previousAlignmentOffset;
};

}

#endif
