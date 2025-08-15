// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_KZB_ENUMS_HPP
#define KZ_KZB_ENUMS_HPP

#include <kanzi/core.ui/graphics/format.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/sampler.hpp>
#include <kanzi/core/cpp/optional.hpp>


namespace kanzi
{

enum KzbProgramType
{
    KzbProgramTypeSeparate = 0,
    KzbProgramTypeCombined = 1
};

enum KzbTextureType
{
    KzbTextureTypeOneDimensional      = 0,
    KzbTextureTypeTwoDimensional      = 1,
    KzbTextureTypeThreeDimensional    = 2,
    KzbTextureTypeCubeMap             = 3,
    KzbTextureTypeRenderTarget        = 4,
    KzbTextureTypeGenerated           = 5,
    KzbTextureTypeRenderTargetCubeMap = 6,
    KzbTextureTypeMultiRenderTarget   = 7,
    KzbTextureTypeDepthRenderTarget   = 8
};

enum KzbTextureFormat
{
    KzbTextureFormatRGB_8                       =   0,
    KzbTextureFormatRGBA_8                      =   1,
    KzbTextureFormatRGB_FLOAT_16                =   2,
    KzbTextureFormatRGBA_FLOAT_16               =   3,
    KzbTextureFormatRGB_FLOAT_32                =   4,
    KzbTextureFormatRGBA_FLOAT_32               =   5,
    KzbTextureFormatALPHA_8                     =   6,
    KzbTextureFormatALPHA_FLOAT_16              =   7,
    KzbTextureFormatALPHA_FLOAT_32              =   8,
    KzbTextureFormatRGB_565                     =   9,
    KzbTextureFormatGRAYSCALE_8                 =  10,
    KzbTextureFormatGRAYSCALE_ALPHA_8           =  11,
    KzbTextureFormatAUTOMATIC                   =  12,
    KzbTextureFormatR8_UNORM                    =  13,
    KzbTextureFormatR8_UINT                     =  14,
    KzbTextureFormatR8_SINT                     =  15,
    KzbTextureFormatR8G8_UNORM                  =  16,
    KzbTextureFormatR8G8_UINT                   =  17,
    KzbTextureFormatR8G8_SINT                   =  18,
    KzbTextureFormatR8G8B8A8_UINT               =  19,
    KzbTextureFormatR8G8B8A8_SINT               =  20,
    KzbTextureFormatR16_UINT                    =  21,
    KzbTextureFormatR16_SINT                    =  22,
    KzbTextureFormatR16_SFLOAT                  =  23,
    KzbTextureFormatR16G16_UINT                 =  24,
    KzbTextureFormatR16G16_SINT                 =  25,
    KzbTextureFormatR16G16_SFLOAT               =  26,
    KzbTextureFormatR16G16B16A16_UINT           =  27,
    KzbTextureFormatR16G16B16A16_SINT           =  28,
    KzbTextureFormatA2B10G10R10_UNORM_PACK32    =  29,
    KzbTextureFormatA2B10G10R10_UINT_PACK32     =  30,
    KzbTextureFormatSRGB_R8G8B8_UNORM           =  31,
    KzbTextureFormatSRGB_R8G8B8A8_UNORM         =  32,
    KzbTextureFormatR8_SNORM                    = 33,
    KzbTextureFormatR32_UINT                    = 34,
    KzbTextureFormatR32_SINT                    = 35,
    KzbTextureFormatR32_SFLOAT                  = 36,
    KzbTextureFormatR8G8_SNORM                  = 37,
    KzbTextureFormatR32G32_UINT                 = 38,
    KzbTextureFormatR32G32_SINT                 = 39,
    KzbTextureFormatR32G32_SFLOAT               = 40,
    KzbTextureFormatR8G8B8_SNORM                = 41,
    KzbTextureFormatR32G32B32_UINT              = 42,
    KzbTextureFormatR32G32B32_SINT              = 43,
    KzbTextureFormatR8G8B8A8_SNORM              = 44,
    KzbTextureFormatR32G32B32A32_UINT           = 45,
    KzbTextureFormatR32G32B32A32_SINT           = 46,
    KzbTextureFormatR16G16B16_UINT              = 47,
    KzbTextureFormatR16G16B16_SINT              = 48,
    KzbTextureFormatR16_UNORM                   = 51,
    KzbTextureFormatR16_SNORM                   = 52,
    KzbTextureFormatR16G16_UNORM                = 53,
    KzbTextureFormatR16G16_SNORM                = 54,
    KzbTextureFormatR16G16B16_UNORM             = 55,
    KzbTextureFormatR16G16B16_SNORM             = 56,
    KzbTextureFormatR16G16B16A16_UNORM          = 57,
    KzbTextureFormatR16G16B16A16_SNORM          = 58,
    KzbTextureFormatSPANSION_A8R8G8B8           = 100,
    KzbTextureFormatSPANSION_R8G8B8             = 101,
    KzbTextureFormatSPANSION_R6G6B6             = 102,
    KzbTextureFormatSPANSION_R5G6B5             = 103,
    KzbTextureFormatSPANSION_A4R4G4B4           = 104,
    KzbTextureFormatSPANSION_A1R5G5B5           = 105,
    KzbTextureFormatSPANSION_A8PAL8             = 106,
    KzbTextureFormatSPANSION_A8                 = 107,
    KzbTextureFormatSPANSION_PAL8               = 108,
    KzbTextureFormatSPANSION_PAL4               = 109,
    KzbTextureFormatSPANSION_A4                 = 110,
    KzbTextureFormatSPANSION_A1                 = 111,
    KzbTextureFormatDEPTH_COMPONENT             = 200,
    KzbTextureFormatDEPTH_COMPONENT_16          = 201,
    KzbTextureFormatDEPTH_COMPONENT_24          = 202,
    KzbTextureFormatDEPTH_COMPONENT_32          = 203,
    KzbTextureFormatDEPTH_COMPONENT_32F         = 204,
    KzbTextureFormatDEPTH_24_STENCIL_8          = 205,
    KzbTextureFormatSTENCIL_8                   = 206
};

enum KzbTextureFilter
{
    KzbTextureFilterNearest = 0,
    KzbTextureFilterLinear = 1
};

enum KzbTextureMipmapMode
{
    KzbTextureMipmapModeBase = 0,
    KzbTextureMipmapModeNearest = 1,
    KzbTextureMipmapModeLinear = 2
};

enum KzbTextureWrapMode
{
    KzbTextureWrapModeRepeat = 0,
    KzbTextureWrapModeClamp = 1
};

KANZI_API optional<GraphicsElementType> toGraphicsElementType(unsigned int kzbElementType);

KANZI_API optional<GraphicsDataType> toGraphicsDataType(unsigned int kzbMeshVertexAttributeDataType);

KANZI_API optional<GraphicsFormat> toGraphicsFormatFromKzbDepthAttachment(int kzbFormat);

KANZI_API optional<GraphicsFormat> toGraphicsFormatFromKzbTextureFormat(unsigned int kzbTextureFormat);

KANZI_API optional<GraphicsFormat> toGraphicsFormatFromKzbImageFormat(unsigned int kzbFormat);

KANZI_API optional<Sampler::Filter> toSamplerFilterFromKzbTextureFilter(unsigned int kzbTextureFilter);

KANZI_API optional<Sampler::MipmapMode> toSamplerMipmapModeFromKzbMipmapMode(unsigned int kzbMipmapMode);

KANZI_API optional<Sampler::AddressingMode> toSamplerAddressingModeFromKzbWrapMode(unsigned int kzbWrapMode);

}

#endif // KZB_ENUMS_HPP

