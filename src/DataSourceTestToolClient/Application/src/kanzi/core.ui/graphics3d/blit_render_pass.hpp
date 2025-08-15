// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BLIT_RENDER_PASS_HPP
#define KZ_BLIT_RENDER_PASS_HPP

#ifdef KANZI_FEATURE_3D

#include <kanzi/core.ui/graphics2d/geometry_quad.hpp>
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core.ui/graphics3d/render_pass.hpp>

namespace kanzi
{

// Forward declarations.
class BlitRenderPass;
class MaterialBrush;
class MaterialBrushRenderer;
typedef shared_ptr<MaterialBrush> MaterialBrushSharedPtr;

/// BlitRenderPass shared pointer type.
typedef shared_ptr<BlitRenderPass> BlitRenderPassSharedPtr;

/// Use the Blit Render Pass to blit one or more textures to the screen of the current rendering context using
/// a material. After the blit operation, a Blit Render Pass passes the control to its descendants and then
/// further to its siblings and parent.
///
/// Use the Blit Render Pass to show the result of other render passes. For example, to show the result of
/// a Composition Target Render Pass, in the Blit Render Pass bind one of the texture properties (#Texture0Property,
/// #Texture1Property, #Texture2Property, or #Texture3Property) to the render target texture that the
/// Composition Target Render Pass creates:
/// \snippet test_render_pass_snippets.cpp Binding to blit render pass
///
/// Kanzi Studio uses a default blit material named "DefaultBlitMaterial" which is in the resource dictionary
/// of the Screen node. This default blit material uses only the #Texture0Property and its purpose is to show
/// the result of a CompositionTargetRenderPass.
///
/// If you use your own materials in a Blit Render Pass, to ensure ease of use in Kanzi Studio projects, use
/// the Blit Render Pass default texture properties.
class KANZI_API BlitRenderPass : public RenderPass
{
public:

    /// \name Properties
    /// \{

    /// Use the Texture0 property to set the first texture you want a Blit Render Pass to blit.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture0(), getTexture0()
    static PropertyType<ResourceSharedPtr> Texture0Property;
    /// Gets the value of the #Texture0Property property.
    /// \see setTexture0()
    ResourceSharedPtr getTexture0() const { return getProperty(Texture0Property); }
    /// Sets the value of the #Texture0Property property.
    /// \see getTexture0()
    void setTexture0(ResourceSharedPtr value) { setProperty(Texture0Property, value); }

    /// Use the Texture1 property to set the second texture you want a Blit Render Pass to blit.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture1(), getTexture1()
    static PropertyType<ResourceSharedPtr> Texture1Property;
    /// Gets the value of the #Texture1Property property.
    /// \see setTexture1()
    ResourceSharedPtr getTexture1() const { return getProperty(Texture1Property); }
    /// Sets the value of the #Texture1Property property.
    /// \see getTexture1()
    void setTexture1(ResourceSharedPtr value) { setProperty(Texture1Property, value); }

    /// Use the Texture2 property to set the third texture you want a Blit Render Pass to blit.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture2(), getTexture2()
    static PropertyType<ResourceSharedPtr> Texture2Property;
    /// Gets the value of the #Texture2Property property.
    /// \see setTexture2()
    ResourceSharedPtr getTexture2() const { return getProperty(Texture2Property); }
    /// Sets the value of the #Texture2Property property.
    /// \see getTexture2()
    void setTexture2(ResourceSharedPtr value) { setProperty(Texture2Property, value); }

    /// Use the Texture3 property to set the fourth texture you want a Blit Render Pass to blit.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture3(), getTexture3()
    static PropertyType<ResourceSharedPtr> Texture3Property;
    /// Gets the value of the #Texture3Property property.
    /// \see setTexture3()
    ResourceSharedPtr getTexture3() const { return getProperty(Texture3Property); }
    /// Sets the value of the #Texture3Property property.
    /// \see getTexture3()
    void setTexture3(ResourceSharedPtr value) { setProperty(Texture3Property, value); }

    /// Use the Material property to set the material that you want a Blit Render Pass to use to blit one or more textures.
    /// The default value is ResourceSharedPtr().
    /// \see setMaterial(), getMaterial()
    static PropertyType<ResourceSharedPtr> MaterialProperty;
    /// Gets the value of the #MaterialProperty property.
    /// \see setMaterial()
    ResourceSharedPtr getMaterial() const { return getProperty(MaterialProperty); }
    /// Sets the value of the #MaterialProperty property.
    /// \see getMaterial()
    void setMaterial(ResourceSharedPtr value) { setProperty(MaterialProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(BlitRenderPass, RenderPass, "Kanzi.BlitRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(Texture0Property)
        KZ_METACLASS_PROPERTY_TYPE(Texture1Property)
        KZ_METACLASS_PROPERTY_TYPE(Texture2Property)
        KZ_METACLASS_PROPERTY_TYPE(Texture3Property)
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a Blit Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Blit Render Pass.
    /// \return The created Blit Render Pass.
    static BlitRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the Blit Render Pass.
    explicit BlitRenderPass(Domain* domain, string_view name);

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

private:

    /// Set a texture property value to the brush renderer.
    /// \param propertyType Property type to set.
    /// \param texture Texture to assign.
    void updateBrushRendererTexture(const PropertyType<ResourceSharedPtr>& propertyType, TextureSharedPtr texture);

    /// Brush for rendering the blit quad.
    MaterialBrushSharedPtr m_brush;

    /// Brush renderer for blit quad.
    BrushRendererPtr m_brushRenderer;

    /// Default value for blit material.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueMaterial;

    /// Quad used for rendering.
    GeometryPtr m_quad;

    /// Last size of the viewport, used for checking if quad needs to be recreated.
    Vector2 m_lastViewportSize;
};

} // namespace kanzi

#endif

#endif // KZ_BLIT_RENDER_PASS_HPP

