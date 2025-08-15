// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STANDARD_MATERIAL_HPP
#define KZ_STANDARD_MATERIAL_HPP


#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/metadata/metaclass.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// Contains property types of Standard material.
class KANZI_API StandardMaterial
{
public:

    /// \name Properties
    /// \{

    /// GlobalAmbient property.
    /// The default value is ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f).
    /// \see setGlobalAmbient(), getGlobalAmbient()
    static PropertyType<ColorRGBA> GlobalAmbientProperty;

    /// Ambient property.
    /// The default value is ColorRGBA(0.2f, 0.2f, 0.2f, 1.0f).
    /// \see setAmbient(), getAmbient()
    static PropertyType<ColorRGBA> AmbientProperty;

    /// Diffuse property.
    /// The default value is ColorRGBA(0.8f, 0.8f, 0.8f, 1.0f).
    /// \see setDiffuse(), getDiffuse()
    static PropertyType<ColorRGBA> DiffuseProperty;

    /// Emissive property.
    /// The default value is ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f).
    /// \see setEmissive(), getEmissive()
    static PropertyType<ColorRGBA> EmissiveProperty;

    /// SpecularColor property.
    /// The default value is ColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f).
    /// \see setSpecularColor(), getSpecularColor()
    static PropertyType<ColorRGBA> SpecularColorProperty;

    /// SpecularExponent property.
    /// The default value is 50.0f.
    /// \see setSpecularExponent(), getSpecularExponent()
    static PropertyType<float> SpecularExponentProperty;

    /// Texture property.
    /// The default value is ResourceSharedPtr().
    /// \see setTexture(), getTexture()
    static PropertyType<ResourceSharedPtr> TextureProperty;

    /// MaskTexture property.
    /// The default value is ResourceSharedPtr().
    /// \see setMaskTexture(), getMaskTexture()
    static PropertyType<ResourceSharedPtr> MaskTextureProperty;

    /// TextureTiling property.
    /// The default value is Vector2(1.0f,  1.0f).
    /// \see setTextureTiling(), getTextureTiling()
    static PropertyType<Vector2> TextureTilingProperty;

    /// TextureOffset property.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setTextureOffset(), getTextureOffset()
    static PropertyType<Vector2> TextureOffsetProperty;

    /// MaskTextureTiling property.
    /// The default value is Vector2(1.0f,  1.0f).
    /// \see setMaskTextureTiling(), getMaskTextureTiling()
    static PropertyType<Vector2> MaskTextureTilingProperty;

    /// MaskTextureOffset property.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setMaskTextureOffset(), getMaskTextureOffset()
    static PropertyType<Vector2> MaskTextureOffsetProperty;

    /// BlendIntensity property.
    /// The default value is 1.0f.
    /// \see setBlendIntensity(), getBlendIntensity()
    static PropertyType<float> BlendIntensityProperty;

    /// BlendMode property.
    /// The default value is GraphicsBlendModeOpaque.
    /// \see setBlendMode(), getBlendMode()
    static PropertyType<GraphicsBlendMode> BlendModeProperty;

    /// GlyphTexture property.
    /// The default value is ResourceSharedPtr().
    /// \see setGlyphTexture(), getGlyphTexture()
    static PropertyType<ResourceSharedPtr> GlyphTextureProperty;

    /// \}

    KZ_STATIC_METACLASS_BEGIN(StandardMaterial, "Kanzi.StandardMaterial")
        KZ_METACLASS_PROPERTY_TYPE(GlobalAmbientProperty)
        KZ_METACLASS_PROPERTY_TYPE(AmbientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DiffuseProperty)
        KZ_METACLASS_PROPERTY_TYPE(EmissiveProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpecularColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpecularExponentProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextureProperty)
        KZ_METACLASS_PROPERTY_TYPE(BlendIntensityProperty)
        KZ_METACLASS_PROPERTY_TYPE(BlendModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(GlyphTextureProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaskTextureProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextureTilingProperty)
        KZ_METACLASS_PROPERTY_TYPE(TextureOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaskTextureTilingProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaskTextureOffsetProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of GlobalAmbient property of object.
    /// \param object An object.
    /// \return Returns value of the GlobalAmbient property.
    static ColorRGBA getGlobalAmbientColor(const Object& object)
    {
        return object.getProperty(GlobalAmbientProperty);
    }

    /// Sets the value of GlobalAmbient property of object.
    /// \param object An object.
    /// \param value Value of GlobalAmbientColor property.
    static void setGlobalAmbientColor(Object& object, ColorRGBA value)
    {
        object.setProperty(GlobalAmbientProperty, value);
    }

    /// Gets the value of Ambient property of object.
    /// \param object An object.
    /// \return Returns value of the AmbientColor property.
    static ColorRGBA getAmbientColor(const Object& object)
    {
        return object.getProperty(AmbientProperty);
    }

    /// Sets the value of Ambient property of object.
    /// \param object An object.
    /// \param value Value of Ambient property.
    static void setAmbientColor(Object& object, ColorRGBA value)
    {
        object.setProperty(AmbientProperty, value);
    }

    /// Gets the value of Diffuse property of object.
    /// \param object An object.
    /// \return Returns value of the Diffuse property.
    static ColorRGBA getDiffuseColor(const Object& object)
    {
        return object.getProperty(DiffuseProperty);
    }

    /// Sets the value of Diffuse property of object.
    /// \param object An object.
    /// \param value Value of Diffuse property.
    static void setDiffuseColor(Object& object, ColorRGBA value)
    {
        object.setProperty(DiffuseProperty, value);
    }

    /// Gets the value of Emissive property of object.
    /// \param object An object.
    /// \return Returns value of the Emissive property.
    static ColorRGBA getEmissiveColor(const Object& object)
    {
        return object.getProperty(EmissiveProperty);
    }

    /// Sets the value of Emissive property of object.
    /// \param object An object.
    /// \param value Value of Emissive property.
    static void setEmissiveColor(Object& object, ColorRGBA value)
    {
        object.setProperty(EmissiveProperty, value);
    }

    /// Gets the value of SpecularColor property of object.
    /// \param object An object.
    /// \return Returns value of the SpecularColor property.
    static ColorRGBA getSpecularColor(const Object& object)
    {
        return object.getProperty(SpecularColorProperty);
    }

    /// Sets the value of SpecularColor property of object.
    /// \param object An object.
    /// \param value Value of SpecularColor property.
    static void setSpecularColor(Object& object, ColorRGBA value)
    {
        object.setProperty(SpecularColorProperty, value);
    }

    /// Gets the value of SpecularExponent property of object.
    /// \param object An object.
    /// \return Returns value of the SpecularExponent property.
    static float getSpecularExponent(const Object& object)
    {
        return object.getProperty(SpecularExponentProperty);
    }

    /// Sets the value of SpecularExponent property of object.
    /// \param object An object.
    /// \param value Value of SpecularExponent property.
    static void setSpecularExponent(Object& object, float value)
    {
        object.setProperty(SpecularExponentProperty, value);
    }

    /// Gets the value of Texture property of object.
    /// \param object An object.
    /// \return Returns value of the Texture property.
    static ResourceSharedPtr getTexture(const Object& object)
    {
        return object.getProperty(TextureProperty);
    }

    /// Sets the value of Texture property of object.
    /// \param object An object.
    /// \param value Value of Texture property.
    static void setTexture(Object& object, ResourceSharedPtr value)
    {
        object.setProperty(TextureProperty, value);
    }
};

}



#endif
