// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SAMPLER_HPP
#define KZ_SAMPLER_HPP

#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>
#include <kanzi/core/string/fixed_string.hpp>

namespace kanzi
{

class Texture;
class Sampler;

/// Sampler provides the sampling parameters, such as minification and magnification filters, mipmap mode, and texture addressing mode for textures.
class KANZI_API Sampler
{
public:
    enum Filter
    {
        FilterNearest,
        FilterLinear,
    };

    enum AddressingMode
    {
        AddressingModeWrap,         ///< Wrap (Open GL ES 2 compatible)
        AddressingModeMirror,       ///< Mirror
        AddressingModeClamp,        ///< Clamp (Open GL ES 2 compatible)
        AddressingModeMirrorOnce,   ///< Mirror Once
        AddressingModeClampBorder   ///< Clamp to border
    };

    enum MipmapMode
    {
        MipmapModeBase,             ///< When sampling texture, use only base level image, no mipmap images are used/needed
        MipmapModeNearest,          ///< When sampling texture, pick one image, the nearest mipmap level, mipmap images are needed
        MipmapModeLinear            ///< When sampling texture, pick two nearest mipmap level images, mipmap images are needed
    };

    struct KANZI_API CreateInfo
    {
        explicit CreateInfo(MipmapMode mipmapMode, Filter minificationFilter, Filter magnificationFilter, AddressingMode addressingMode,
                            GraphicsCompareFunction depthCompareFunction, float anisotropy, float mipLodBias, float minLod, float maxLod);

        /// Mipmap mode for the texture. Default CreateInfo constructor initializes this to Sampler::MipmapModeBase.
        MipmapMode mipmapMode;

        /// Texture minification filter. Default CreateInfo constructor initializes this to Sampler::FilterNearest.
        Filter minificationFilter;

        /// Texture magnification filter. Default CreateInfo constructor initializes this to Sampler::FilterNearest.
        Filter magnificationFilter;

        /// Texture addressing mode. Default CreateInfo constructor initializes this to Sampler::AddressingModeClamp.
        AddressingMode addressingMode;

        /// Depth compare function. Default CreateInfo constructor initializes this to GraphicsCompareFunctionDisabled.
        GraphicsCompareFunction depthCompareFunction;

        /// Texture anisotropy. Default CreateInfo constructor initializes this to 1.0 (no anisotropy).
        /// \note Use of anisotropic texture filter requires GL extension.
        float anisotropy;

        /// Texture mipmap level of detail bias. 
        /// Default CreateInfo constructor initializes this to 0.
        /// \note Using texture Lod controls requires OpenGL ES 3.0.
        float mipLodBias;

        /// Minimum texture level of detail.
        /// Default CreateInfo constructor initializes this to -1000 (effectively no clamping for level of detail).
        /// \note Using texture Lod controls requires OpenGL ES 3.0.
        float minLod;

        /// Maximum texture level of detail.
        /// Default CreateInfo constructor initializes this to 1000 (effectively no clamping for level of detail).
        /// \note Using texture Lod controls requires OpenGL ES 3.0.
        float maxLod;
    };

    explicit Sampler();
    explicit Sampler(const CreateInfo& createInfo);

    /// Gets the sampler mipmap mode.
    MipmapMode getMipmapMode() const;

    /// Gets the sampler minification filter.
    Filter getMinificationFilter() const;

    /// Gets the sampler magnification filter.
    Filter getMagnificationFilter() const;

    /// Gets the sampler addressing mode.
    AddressingMode getAddressingMode() const;

    /// Gets the depth compare function.
    GraphicsCompareFunction getDepthCompareFunction() const;

    /// Gets the sampler anisotropy.
    float getAnisotropy() const;

    float getMipLodBias() const;

    float getMinLod() const;

    float getMaxLod() const;

    friend void swap(Sampler& left, Sampler& right)
    {
        using std::swap;
        swap(left.m_mipmapMode, right.m_mipmapMode);
        swap(left.m_minificationFilter, right.m_minificationFilter);
        swap(left.m_magnificationFilter, right.m_magnificationFilter);
        swap(left.m_addressingMode, right.m_addressingMode);
        swap(left.m_depthCompareFunction, right.m_depthCompareFunction);
        swap(left.m_anisotropy, right.m_anisotropy);
        swap(left.m_mipLodBias, right.m_mipLodBias);
        swap(left.m_minLod, right.m_minLod);
        swap(left.m_maxLod, right.m_maxLod);
    }

private:
    Sampler(const Sampler&) KZ_DELETED_FUNCTION;
    Sampler& operator=(const Sampler&) KZ_DELETED_FUNCTION;

    friend class Texture;
    void previewPatch(const CreateInfo& createInfo);

    // Data members
    MipmapMode m_mipmapMode;
    Filter m_minificationFilter;
    Filter m_magnificationFilter;
    AddressingMode m_addressingMode;
    GraphicsCompareFunction m_depthCompareFunction;
    float m_anisotropy;
    float m_mipLodBias;
    float m_minLod;
    float m_maxLod;
};

KANZI_API FixedString toFixedString(Sampler::Filter filter);
KANZI_API FixedString toFixedString(Sampler::MipmapMode mipmapMode);

} // namespace kanzi

#endif // KZ_SAMPLER_HPP
