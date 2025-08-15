// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TEXTURE_BRUSH_HPP
#define KZ_TEXTURE_BRUSH_HPP


#include "brush.hpp"
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core/cpp/string_view.hpp>


namespace kanzi
{


// Forward declarations.
class TextureBrush;
class Framebuffer;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;


/// Shared pointer definition.
typedef shared_ptr<TextureBrush> TextureBrushSharedPtr;
typedef shared_ptr<Framebuffer> FramebufferSharedPtr;


/// Texture brush class.
///
/// Implements a textured brush used to fill areas with patterns.
class KANZI_API TextureBrush : public Brush
{
public:
    /// \name Properties
    /// \{

    /// Texture property.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture(), getTexture()
    static PropertyType<ResourceSharedPtr> RenderTextureProperty;
    /// Gets the value of #TextureProperty.
    /// \see setTexture()
    TextureSharedPtr getRenderTexture() const { return dynamic_pointer_cast<Texture>(getProperty(RenderTextureProperty)); }
    /// Sets the value of #TextureProperty.
    /// \see getTexture()
    void setRenderTexture(ResourceSharedPtr value) { setProperty(RenderTextureProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(TextureBrush, Brush, "Kanzi.TextureBrush")
        KZ_METACLASS_PROPERTY_TYPE(RenderTextureProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new texture brush.
    ///
    /// Leaves all properties unset.
    ///
    /// \param domain uiDomain the brush belongs to.
    /// \param name of this texture brush.
    static TextureBrushSharedPtr create(Domain* domain, string_view name);

    /// Create a new texture brush.
    ///
    /// Brush will retain shared ownership of texture passed.
    ///
    /// \param domain uiDomain the brush belongs to.
    /// \param name of this texture brush.
    /// \param texture Texture to use for rendering the brush.
    static TextureBrushSharedPtr create(Domain* domain, string_view name, TextureSharedPtr texture);

    /// Create a new texture brush.
    ///
    /// Brush will retain shared ownership of texture passed.
    ///
    /// \param domain uiDomain the brush belongs to.
    /// \param name of this texture brush.
    /// \param texture Texture to use for rendering the brush.
    /// \param color Color to use for modulating the texture.
    static TextureBrushSharedPtr create(Domain* domain, string_view name, TextureSharedPtr texture, const ColorRGBA& color);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

    /// Brush::load() implementation.
    virtual void load(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file) KZ_OVERRIDE;

protected:
    /// Constructor.
    /// Leaves all properties unset.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    explicit TextureBrush(Domain* domain, string_view name) :
             Brush(domain, name)
    {
    }

    /// Constructor.
    /// Will use white modulating color by default.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    /// \param texture Texture to use for rendering the brush.
    explicit TextureBrush(Domain* domain, string_view name, TextureSharedPtr texture) :
             Brush(domain, name)
    {
        setRenderTexture(texture);
    }

    /// Constructor.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    /// \param texture Texture to use for rendering the brush.
    /// \param color Color to use for modulating the texture.
    explicit TextureBrush(Domain* domain, string_view name, TextureSharedPtr texture, const ColorRGBA& color) :
        Brush(domain, name)
    {
        setRenderTexture(texture);
        setModulateColor(color);
    }

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Recalculate rendering properties.
    ///
    /// Must be called when a relevant property has been reassigned.
    void calculateRenderingProperties();

    /// Object::initialize() interface.
    void initialize();
};


}


#endif
