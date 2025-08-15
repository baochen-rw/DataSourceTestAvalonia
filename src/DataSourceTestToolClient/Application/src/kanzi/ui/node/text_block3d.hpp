// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_TEXT_BLOCK_H
#define KZU_UI_TEXT_BLOCK_H

#include <kanzi/core.ui/graphics3d/material_renderer.hpp>
#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/text_block.hpp>

namespace kanzi
{

class TextBlock3D;

/// TextBlock shared pointer.
typedef shared_ptr<TextBlock3D> TextBlock3DSharedPtr;

/// Text Block 3D displays a small amount of text in 3D.

/// To render a Text Block 3D node Kanzi:
/// -# Prepares the text as 2D text using device-independent pixel metrics.
/// -# Projects the prepared text to 3D space using the value of Node::Projection2DTo3DScaleProperty
/// to scale device-independent pixels to 3D units.
///
/// Use device-independent pixel values to set the values of text block specific properties such as
/// TextBlockConcept::FontSizeProperty or TextBlockConcept::FixedCharacterWidthProperty.
///
/// Use 3D units to adjust the layout of a Text Block 3D node in 3D space. For example, use 3D units to
/// set the values of the Node::WidthProperty and Node::HeightProperty properties in a Text Block 3D node.
///
/// Text Block 3D does not support clipping.
///
///
/// \see For a 2D text node, see TextBlock2D.
///
/// Examples
/// ----
///
/// To create a Text Block 3D node:
/// \snippet test_text_block3d.cpp Create
///
/// To set the font of a text block:
/// \snippet test_text_block3d.cpp Set font
///
/// To add the text shown by a text block:
/// \snippet test_text_block3d.cpp Add text
///
/// To adjust the appearance of the text:
/// \snippet test_text_block3d.cpp Style text
///
/// To adjust the scaling factor of the 2D to 3D projection:
/// \snippet test_text_block3d.cpp 2D to 3D scaling

class KANZI_UI_API TextBlock3D : public TextBlockConceptImpl<Node3D, TextBlock3D>
{
public:

    typedef TextBlockConceptImpl<Node3D, TextBlock3D> ConceptClass;

    /// The size of the text block in Z-direction. Used when constructing the text bounding box.
    /// By default, this value is insignificant as compared to normal layout sizes.
    static const float DefaultTextLayoutDepth;

public:

    /// \name Properties
    /// \{

    /// Baseline property.
    /// Font baseline in 3D space units.
    /// The default value is 0.0f.
    /// \see setBaseline(), getBaseline()
    static PropertyType<float> BaselineProperty;

    /// Gets the value of #BaselineProperty.
    /// \see setBaseline()
    float getBaseline() const { return getProperty(BaselineProperty); }


    /// TwoPassRendering property.
    /// Defines whether the Text Block 3D is rendered in two passes. Disabling the two pass rendering improves performance, but can cause invalid rendering result when glyph bounds overlap.
    /// The default value is true.
    /// \see setTwoPassRendering(), isTwoPassRendering()
    static PropertyType<bool> TwoPassRenderingProperty;

    /// Gets the value of #TwoPassRenderingProperty.
    /// \see setTwoPassRendering()
    bool isTwoPassRendering() const { return getProperty(TwoPassRenderingProperty); }

    /// Sets the value of #TwoPassRenderingProperty.
    /// \see isTwoPassRendering()
    void setTwoPassRendering(bool value) { setProperty(TwoPassRenderingProperty, value); }

    /// \}

    /// Creates a TextBlock3D node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static TextBlock3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(TextBlock3D, ConceptClass, "Kanzi.TextBlock3D")
        KZ_METACLASS_PROPERTY_TYPE(TwoPassRenderingProperty)
        KZ_METACLASS_PROPERTY_TYPE(BaselineProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Destructor.
    virtual ~TextBlock3D();

    /// Node::restoreResources() implementation.
    virtual void restoreResources() KZ_OVERRIDE;

    /// Access material renderer.
    /// \return Material renderer.
    MaterialRenderer* getMaterialRenderer()
    {
        return m_materialRenderer.get();
    }
    /// Access glyph texture.
    /// \return Glyph texture.
    TextureSharedPtr getGlyphTexture() const;

protected:
    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit TextBlock3D(Domain* domain, string_view name);

    /// Do TextBlock3D-specific initialization.
    void initialize();

    /// Reattach material renderer if necessary and return current font material in use.
    /// Will do nothing if material renderer is already attached to the correct material.
    /// \return Current font material.
    MaterialSharedPtr reattachMaterialRenderer();

    /// Node3D::render() implementation.
    virtual void render(Renderer3D& renderer, const KzuTransformedObjectNode& transformedObjectNode, const Matrix4x4& worldTransformation) KZ_OVERRIDE;

    /// Node3D::getBoundingVolume() implementation.
    virtual const KzuBoundingVolume* getBoundingVolume() const KZ_OVERRIDE;

    /// Node3D::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;

    /// Node3D::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;

    /// Node3D::onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

private:

    /// Sets the value of #BaselineProperty.
    /// \see getBaseline()
    void setBaseline(float value)
    {
        setProperty(BaselineProperty, value);
    }

    /// The bounding volume of the TextBlock3D node.
    KzuBoundingVolume* m_boundingVolume;

    /// Material renderer for text.
    MaterialRendererPtr m_materialRenderer;
    /// Content texture handle for material renderer.
    GlRenderState::HandleType m_contentTextureHandle;

    /// Overridden material renderer, only used if override has been used.
    /// Stored so material renderer does not need to be recreated.
    MaterialRendererPtr m_overrideMaterialRenderer;
};

}

#endif

#endif
