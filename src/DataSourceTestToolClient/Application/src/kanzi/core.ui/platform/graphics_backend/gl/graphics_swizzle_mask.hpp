// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GRAPHIC_SWIZZLE_MASK_HPP
#define KZ_GRAPHIC_SWIZZLE_MASK_HPP

#include <kanzi/core/cpp/array.hpp>

namespace kanzi
{

typedef array<int, 4> GLSwizzleMask;

/// Texture swizzle mask.
///
/// The texture swizzle mask can used to reorder the color channel value, returned by the texture function in a shader.
/// For more info see https://www.khronos.org/opengl/wiki/Texture#Swizzle_mask.
/// Note: To apply a swizzle mask, the target platform must support GL_ARB_texture_swizzle or GL_EXT_texture_swizzle extension.
///
/// Example
/// -------
/// TextureSwizzleMask redOverAlphaMask = TextureSwizzleMask(ColorComponent::Zero, ColorComponent::Zero, ColorComponent::Zero, ColorComponent::Red);
/// Renderer::setTextureSwizzleMask(..., redOverAlphaMask);
/// This mask will map the red channel in the texture to the alpha channel.
class KANZI_API TextureSwizzleMask
{
public:
    /// Wraps the graphics library's color components.
    enum ColorComponent
    {
        /// The component is disabled.
        /// Maps to #KZS_GL_ZERO.
        Zero,
        /// The component is kept as-is.
        /// Maps to #KZS_GL_ONE.
        One,
        /// The value for this component comes from the red channel of the texture.
        /// All texture color formats have at least a red channel.
        /// Maps to #KZS_GL_RED.
        Red,
        /// The value for this component comes from the green channel of the texture,
        /// or 0 if it has no green channel.
        /// Maps to #KZS_GL_GREEN.
        Green,
        /// The value for this component comes from the blue channel of the texture,
        /// or 0 if it has no blue channel.
        /// Maps to #KZS_GL_BLUE.
        Blue,
        /// The value for this component comes from the alpha channel of the texture,
        /// or 1 if it has no alpha channel.
        /// Maps to #KZS_GL_ALPHA.
        Alpha,
        /// The number of supported color components
        Count
    };

    /// Constructs the mask using separate value for each channel.
    /// \param redChannelMask Mask for red channel.
    /// \param greenChannelMask Mask for green channel.
    /// \param blueChannelMask Mask for blue channel.
    /// \param alphaChannelMask Mask for alpha channel.
    explicit TextureSwizzleMask(ColorComponent redChannelMask,
                                ColorComponent greenChannelMask,
                                ColorComponent blueChannelMask,
                                ColorComponent alphaChannelMask)
    {
        m_mask[0] = redChannelMask;
        m_mask[1] = greenChannelMask;
        m_mask[2] = blueChannelMask;
        m_mask[3] = alphaChannelMask;
    }

    /// Constructs the mask using the same value for each color channel.
    /// \param mask Swizzle mask for all the channels.
    explicit TextureSwizzleMask(ColorComponent mask)
    {
        m_mask.fill(mask);
    }

    /// Destructor.
    ~TextureSwizzleMask()
    {
    }

    /// Gets the swizzle mask.
    /// \return Internal GL representation of the swizzle mask.
    GLSwizzleMask getMask() const;

private:
    explicit TextureSwizzleMask() KZ_DELETED_FUNCTION;
    explicit TextureSwizzleMask(const TextureSwizzleMask& other) KZ_DELETED_FUNCTION;
    TextureSwizzleMask& operator=(const TextureSwizzleMask& other) KZ_DELETED_FUNCTION;

    /// The swizzle mask.
    array<ColorComponent, 4> m_mask;
};

/// Mask all of the color channels with red.
KANZI_API extern const TextureSwizzleMask SwizzleMaskRGBToLuminanceAlpha;
/// Mask all of the color channels with alpha.
KANZI_API extern const TextureSwizzleMask SwizzleMaskLuminanceToRGBA;
}

#endif