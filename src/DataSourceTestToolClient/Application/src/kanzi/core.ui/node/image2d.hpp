// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_IMAGE_LAYER_H
#define KZU_IMAGE_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/graphics2d/texture_brush.hpp>

#include <kanzi/core.ui/graphics2d/texture.hpp>

namespace kanzi
{

class Image2D;
class CompositionStack;

typedef shared_ptr<Image2D> Image2DSharedPtr;


class KANZI_API Image2D : public Node2D
{
public:
    KZ_METACLASS_BEGIN(Image2D, Node2D, "Kanzi.Image2D")
        KZ_METACLASS_PROPERTY_TYPE(ImageProperty)
    KZ_METACLASS_END()

    /// Create a 2D image node.
    ///
    /// \param domain The UI domain.
    /// \param name Name of the new image node.
    /// \return Image node shared pointer.
    static Image2DSharedPtr create(Domain* domain, string_view name);

    /// Create a 2D image node.
    ///
    /// \param domain The UI domain.
    /// \param name Name of the new image node.
    /// \param texture Texture to assign to the image node.
    /// \return Image node shared pointer.
    static Image2DSharedPtr create(Domain* domain, string_view name, TextureSharedPtr texture);

    /// Image property.
    static PropertyType<ResourceSharedPtr> ImageProperty;
    /// Gets value of #ImageProperty.
    TextureSharedPtr getImage() const
    {
        return dynamic_pointer_cast<Texture>(getProperty(ImageProperty));
    }
    /// Sets value of #ImageProperty.
    void setImage(TextureSharedPtr value)
    {
        setProperty(ImageProperty, value);
    }

protected:

    /// Constructor.
    ///
    /// \param domain The UI domain.
    /// \param name Name of the new image layer.
    explicit Image2D(Domain* domain, string_view name);

    /// Node2D::measureOverride() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    /// Node2D::updateRenderOverride() implementation.
    virtual void updateRenderOverride() KZ_OVERRIDE;

private:
    /// Texture reference.
    TextureSharedPtr m_texture;

    /// Default value for foreground brush.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueForegroundBrush;
};

}


#endif
