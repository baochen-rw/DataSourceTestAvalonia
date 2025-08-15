// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FORMAT_HPP
#define KZ_FORMAT_HPP

#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/string/fixed_string.hpp>

namespace kanzi
{

class Renderer;

/// GraphicsElementType is used to specify type of element of data consumed by shaders.
/// An element is a scalar used to build scalars (single element), vectors (one row)
/// and matrices (multiple rows and columns) consumed by shaders.
/// \see ShaderVertexAttribute
enum GraphicsElementType
{
    /// Unsigned integer element type.
    GraphicsElementTypeUINT,

    /// Signed integer element type.
    GraphicsElementTypeSINT,

    /// Floating point element type.
    GraphicsElementTypeFLOAT
};

/// GraphicsDataType is used to specify type of data in textures and vertex buffers.
enum GraphicsDataType
{
    /// Indicates unused, empty or invalid data type.
    GraphicsDataTypeNone,

    /// Unsigned normalized 8-bit data type.
    GraphicsDataTypeUNORM8,

    /// Signed normalized 8-bit data type.
    GraphicsDataTypeSNORM8,

    /// Unsigned normalized 16-bit data type.
    GraphicsDataTypeUNORM16,

    /// Signed normalized 16-bit data type.
    GraphicsDataTypeSNORM16,

    /// Unsigned normalized 32-bit data type.
    GraphicsDataTypeUNORM32,

    /// Signed normalized 32-bit data type.
    GraphicsDataTypeSNORM32,

    /// A three-component, 16-bit packed unsigned normalized data type that has a 5-bit R component in bits 11..15,
    /// a 6-bit G component in bits 5..10, and a 5-bit B component in bits 0..4.
    GraphicsDataTypeUNORM_PACK16_5_6_5,

    /// A compressed data type, used for compressed texture formats.
    GraphicsDataTypeCOMPRESSED,

    /// 8-bit unsigned integer data type.
    GraphicsDataTypeUINT8,

    /// 8-bit signed integer data type.
    GraphicsDataTypeSINT8,

    /// 16-bit unsigned integer data type.
    GraphicsDataTypeUINT16,

    /// 16-bit signed integer data type.
    GraphicsDataTypeSINT16,

    /// 32-bit unsigned integer data type.
    GraphicsDataTypeUINT32,

    /// 32-bit signed integer data type.
    GraphicsDataTypeSINT32,

    /// 16-bit signed floating-point data type.
    GraphicsDataTypeSFLOAT16,

    /// 32-bit signed floating-point data type.
    GraphicsDataTypeSFLOAT32,

    /// 24-bit unsigned normalized data type.
    GraphicsDataTypeUNORM24,

    /// 32-bit packed data type that has 8 unsigned integer bits in the first component, and 24 unsigned normalized bits in the second component.
    GraphicsDataTypeUNORM24_UINT8,

    /// A four-component, 32-bit packed unsigned normalized data type that has a 2-bit A component in bits 30..31,
    /// a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9
    GraphicsDataTypeUNORM_PACK32_2_10_10_10,

    /// A four-component, 32-bit packed signed normalized data type that has a 2-bit A component in bits 30..31,
    /// a 10-bit B component in bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R component in bits 0..9
    GraphicsDataTypeSNORM_PACK32_2_10_10_10,

    /// Placeholder value for GraphicsFormats that do not use the GraphicsDataType abstraction.
    GraphicsDataTypeNative
};

/// GraphicsFormat specifies format of graphics data used for example in textures and vertex attributes.
enum GraphicsFormat
{
    /// Indicates unused, empty or invalid graphics format.
    GraphicsFormatNone = 0,

    // Legacy formats:

    /// Single channel luminance 8-bit unsigned normalized format, one byte per pixel.
    GraphicsFormatLUMINANCE8_UNORM = 1,

    /// Single channel alpha 8-bit unsigned normalized format, one byte per pixel.
    GraphicsFormatALPHA8_UNORM = 2,

    /// Two channel luminance and alpha 8-bit unsigned normalized format, two bytes per pixel.
    GraphicsFormatLUMINANCE8_ALPHA8_UNORM = 3,

    /// One channel red 8-bit unsigned normalized format, one byte per pixel.
    /// \note Requires OpenGL ES 3 or rg texture extension.
    GraphicsFormatR8_UNORM = 4,

    /// One channel red 8-bit unsigned integer format, one byte per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8_UINT = 5,

    /// One channel red 8-bit signed integer format, one byte per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8_SINT = 6,

    /// Two channel red green 8-bit unsigned normalized format, two bytes per pixel.
    /// \note Requires OpenGL ES 3 or rg texture extension.
    GraphicsFormatR8G8_UNORM = 7,

    /// Two channel red green 8-bit unsigned integer format, two bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8_UINT = 8,

    /// Two channel red green 8-bit signed integer format, two bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8_SINT = 9,

    /// Three channel RGB 8-bit unsigned normalized format, three bytes per pixel.
    GraphicsFormatR8G8B8_UNORM = 10,

    /// Three channel RGB 8-bit unsigned normalized format in sRGB color space, three bytes per pixel.
    GraphicsFormatR8G8B8_SRGB = 11,

    /// Three channel RGB 8-bit unsigned integer format, three bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8B8_UINT = 12,

    /// Three channel RGB 8-bit signed integer format, three bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8B8_SINT = 13,

    /// Four channel RGB and alpha 8-bit unsigned normalized format, four bytes per pixel.
    GraphicsFormatR8G8B8A8_UNORM = 14,

    /// Four channel RGB and alpha 8-bit unsigned normalized format in sRGB color space, four bytes per pixel.
    GraphicsFormatR8G8B8A8_SRGB = 15,

    /// Four channel RBGA 8-bit unsigned integer format, four bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8B8A8_UINT = 16,

    /// Four channel RBGA 8-bit signed integer format, four bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR8G8B8A8_SINT = 17,

    /// One channel red 16-bit unsigned integer format, two bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16_UINT = 18,

    /// One channel red 16-bit signed integer format, two bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16_SINT = 19,

    /// One channel red 16-bit half float format, two bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR16_SFLOAT = 20,

    /// Two channel red green 16-bit unsigned integer format, four bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16G16_UINT = 21,

    /// Two channel red green 16-bit signed integer format, four bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16G16_SINT = 22,

    /// Two channel red green 16-bit half float format, four bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR16G16_SFLOAT = 23,

    /// Three channel RGB 16-bit unsigned integer format, six bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16G16B16_UINT = 24,

    /// Three channel RGB 16-bit signed integer format, six bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR16G16B16_SINT = 25,

    /// Three channel RGB 16-bit half float format, six bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR16G16B16_SFLOAT = 26,

    /// Four channel RGBA 16-bit unsigned integer format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR16G16B16A16_UINT = 27,

    /// Four channel RGBA 16-bit signed integer format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR16G16B16A16_SINT = 28,

    /// Four channel RGBA 16-bit half float format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR16G16B16A16_SFLOAT = 29,

    /// Three channel RGB 5, 6, 5-bit unsigned normalized format, two bytes per pixel.
    GraphicsFormatR5G6B5_UNORM_PACK16 = 30,

    /// Three channel RGB ETC1 compressed format, 4 by 4 pixels per block, 64 bits per block.
    GraphicsFormatETC1_R8G8B8_UNORM = 31,

    /// Three channel RGB ETC2 compressed format, 4 by 4 pixels per block, 64 bits per block.
    GraphicsFormatETC2_R8G8B8_UNORM = 32,

    /// Four channel RGB and punchthrough alpha ETC2 compressed format, 4 by 4 pixels per block, 64 bits per block.
    GraphicsFormatETC2_R8G8B8A1_UNORM = 33,

    /// Four channel RGB and alpha ETC2 compressed format, 4 by 4 pixels per block, 128 bits per block.
    GraphicsFormatETC2_R8G8B8A8_UNORM = 34,

    /// Four channel RGB and alpha DXT3 compressed format, 4 by 4 pixels per block, 128 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/EXT/texture_compression_s3tc.txt
    GraphicsFormatBC2_UNORM = 35,

    /// Four channel RGB and alpha DXT5 compressed format, 4 by 4 pixels per block, 128 bits per block, interpolated alpha.
    /// \see https://www.khronos.org/registry/gles/extensions/EXT/texture_compression_s3tc.txt
    GraphicsFormatBC3_UNORM = 36,

    /// Three channel RGB PVR1 compressed format, 8 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
    GraphicsFormatPVRTC1_RGB_2BPP = 37,

    /// Three channel RGB PVR1 compressed format, 4 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
    GraphicsFormatPVRTC1_RGB_4BPP = 38,

    /// Four channel RGB and alpha PVR1 compressed format, 2 bits per pixel, 8 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
    GraphicsFormatPVRTC1_RGBA_2BPP = 39,

    /// Four channel RGB and alpha PVR1 compressed format, 4 bits per pixel, 4 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
    GraphicsFormatPVRTC1_RGBA_4BPP = 40,

    /// Four channel RGB and alpha PVR2 compressed format, 2 bits per pixel, 8 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc2.txt
    GraphicsFormatPVRTC2_RGBA_2BPP = 41,

    /// Four channel RGB and alpha PVR2 compressed format, 4 bits per pixel, 4 by 4 pixels per block, 64 bits per block.
    /// \see https://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc2.txt
    GraphicsFormatPVRTC2_RGBA_4BPP = 42,

    /// Three channel RGB ATC compressed format.
    /// \see https://www.khronos.org/registry/gles/extensions/AMD/AMD_compressed_ATC_texture.txt
    GraphicsFormatATC_RGB = 43,

    /// Four channel RGB and alpha compressed format.
    /// \see https://www.khronos.org/registry/gles/extensions/AMD/AMD_compressed_ATC_texture.txt
    GraphicsFormatATC_RGBA_EXPLICIT_ALPHA = 44,

    /// Four channel RGB and alpha compressed format.
    /// \see https://www.khronos.org/registry/gles/extensions/AMD/AMD_compressed_ATC_texture.txt
    GraphicsFormatATC_RGBA_INTERPOLATED_ALPHA = 45,

    /// Single channel depth 16-bit unsigned normalized format.
    /// \see https://www.khronos.org/registry/gles/extensions/OES/OES_depth_texture.txt
    GraphicsFormatD16_UNORM = 46,

    /// Single channel depth 24-bit unsigned normalized format.
    GraphicsFormatD24_UNORM = 47,

    /// Single channel depth 32-bit float format.
    GraphicsFormatD32_SFLOAT = 48,

    /// Two channel depth stencil format.
    GraphicsFormatD24_UNORM_S8_UINT = 49,

    /// Single channel stencil 8-bit unsigned integer format.
    GraphicsFormatS8_UINT = 50,

    /// Unsigned normalized ASTC-compressed packed 4x4 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_4x4_UNORM_BLOCK = 51,

    /// sRGB-corrected ASTC-compressed packed 4x4 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_4x4_SRGB_BLOCK = 52,

    /// Unsigned normalized ASTC-compressed packed 5x4 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_5x4_UNORM_BLOCK = 53,

    /// sRGB-corrected ASTC-compressed packed 5x4 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_5x4_SRGB_BLOCK = 54,

    /// Unsigned normalized ASTC-compressed packed 5x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_5x5_UNORM_BLOCK = 55,

    /// sRGB-corrected ASTC-compressed packed 5x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_5x5_SRGB_BLOCK = 56,

    /// Unsigned normalized ASTC-compressed packed 6x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_6x5_UNORM_BLOCK = 57,

    /// sRGB-corrected ASTC-compressed packed 6x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_6x5_SRGB_BLOCK = 58,

    /// Unsigned normalized ASTC-compressed packed 6x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_6x6_UNORM_BLOCK = 59,

    /// sRGB-corrected ASTC-compressed packed 6x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_6x6_SRGB_BLOCK = 60,

    /// Unsigned normalized ASTC-compressed packed 8x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x5_UNORM_BLOCK = 61,

    /// sRGB-corrected ASTC-compressed packed 8x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x5_SRGB_BLOCK = 62,

    /// Unsigned normalized ASTC-compressed packed 8x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x6_UNORM_BLOCK = 63,

    /// sRGB-corrected ASTC-compressed packed 8x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x6_SRGB_BLOCK = 64,

    /// Unsigned normalized ASTC-compressed packed 8x8 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x8_UNORM_BLOCK = 65,

    /// sRGB-corrected ASTC-compressed packed 8x8 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_8x8_SRGB_BLOCK = 66,

    /// Unsigned normalized ASTC-compressed packed 10x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x5_UNORM_BLOCK = 67,

    /// sRGB-corrected ASTC-compressed packed 10x5 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x5_SRGB_BLOCK = 68,

    /// Unsigned normalized ASTC-compressed packed 10x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x6_UNORM_BLOCK = 69,

    /// sRGB-corrected ASTC-compressed packed 10x6 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x6_SRGB_BLOCK = 70,

    /// Unsigned normalized ASTC-compressed packed 10x8 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x8_UNORM_BLOCK = 71,

    /// sRGB-corrected ASTC-compressed packed 10x8 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x8_SRGB_BLOCK = 72,

    /// Unsigned normalized ASTC-compressed packed 10x10 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x10_UNORM_BLOCK = 73,

    /// sRGB-corrected ASTC-compressed packed 10x10 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_10x10_SRGB_BLOCK = 74,

    /// Unsigned normalized ASTC-compressed packed 12x10 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_12x10_UNORM_BLOCK = 75,

    /// sRGB-corrected ASTC-compressed packed 12x10 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_12x10_SRGB_BLOCK = 76,

    /// Unsigned normalized ASTC-compressed packed 12x12 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_12x12_UNORM_BLOCK = 77,

    /// sRGB-corrected ASTC-compressed packed 12x12 block format.
    /// \note Do not change the ordering of ASTC entries in this enum.
    GraphicsFormatASTC_12x12_SRGB_BLOCK = 78,

    /// Two channel 1-bit alpha and 7-bit luminance unsigned normalized format, 8 bits per pixel.
    GraphicsFormatALPHA1_LUMINANCE7_UNORM = 79,

    /// Two channel 4-bit alpha and 4-bit luminance unsigned normalized format, 8 bits per pixel.
    GraphicsFormatALPHA4_LUMINANCE4_UNORM = 80,

    /// Two channel alpha and luminance 8-bit unsigned normalized format, 16 bits per pixel.
    GraphicsFormatALPHA8_LUMINANCE8_UNORM = 81,

    /// Two channel aliased single 1-bit alpha/luminance component unsigned normalized texture only format, 1 bit per pixel.
    GraphicsFormatALPHALUMINANCE1_UNORM = 82,

    /// Two channel aliased single 2-bit alpha/luminance component unsigned normalized texture only format, 2 bits per pixel.
    GraphicsFormatALPHALUMINANCE2_UNORM = 83,

    /// Two channel aliased single 4-bit alpha/luminance component unsigned normalized texture only format, 4 bits per pixel.
    GraphicsFormatALPHALUMINANCE4_UNORM = 84,

    /// Two channel aliased single 8-bit alpha/luminance component unsigned normalized texture only format, 8 bits per pixel.
    GraphicsFormatALPHALUMINANCE8_UNORM = 85,

    /// Four channel 1-bit alpha and 5-bit RGB unsigned normalized format, 16 bits per pixel.
    GraphicsFormatA1R5G5B5_UNORM = 86,

    /// Four channel 5-bit RGB and 1-bit alpha unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR5G5B5A1_UNORM = 87,

    //// Four channel 4-bit alpha and 4-bit RGB unsigned normalized format, 16 bits per pixel.
    GraphicsFormatA4R4G4B4_UNORM = 88,

    /// Four channel 4-bit RGB and 4-bit alpha unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR4G4B4A4_UNORM = 89,

    /// Four channel ARGB 8-bit unsigned normalized format, 32 bits per pixel.
    GraphicsFormatA8R8G8B8_UNORM = 90,

    /// Single component 8-bit unsigned integer texture only color lookup table format, 8 bits per component.
    GraphicsFormatCLUT8_UINT = 91,

    /// Single component 4-bit unsigned integer texture only color lookup table format, 4 bits per component.
    GraphicsFormatCLUT4_UINT = 92,

    /// Single component 2-bit unsigned integer texture only color lookup table format, 2 bits per component.
    GraphicsFormatCLUT2_UINT = 93,

    /// Single component 1-bit unsigned integer texture only color lookup table format, 1 bit per component.
    GraphicsFormatCLUT1_UINT = 94,

    /// One channel red 8-bit signed normalized format, one byte per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR8_SNORM = 95,

    /// One channel red 32-bit unsigned integer format, four bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32_UINT = 96,

    /// One channel red 32-bit signed integer format, four byte per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32_SINT = 97,

    /// One channel red 32-bit float format, four bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR32_SFLOAT = 98,

    /// Two channel red green 8-bit signed normalized format, two bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR8G8_SNORM = 99,

    /// Two channel red green 32-bit unsigned integer format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32G32_UINT = 100,

    /// Two channel red green 32-bit signed integer format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32G32_SINT = 101,

    /// Two channel red green 32-bit float format, eight bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR32G32_SFLOAT = 102,

    /// Three channel RGB 8-bit signed normalized format, three bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR8G8B8_SNORM = 103,

    /// Three channel RGB 32-bit unsigned integer format, twelve bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32G32B32_UINT = 104,

    /// Three channel RGB 32-bit signed integer format, twelve bytes per pixel.
    /// \note Requires OpenGL ES 3.
    GraphicsFormatR32G32B32_SINT = 105,

    /// Three channel red green blue 32-bit float format, twelve bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR32G32B32_SFLOAT = 106,

    /// Four channel RGB and alpha 8-bit signed normalized format, four bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR8G8B8A8_SNORM = 107,

    /// Four channel RGBA 32-bit signed integer format, sixteen bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR32G32B32A32_UINT = 108,

    /// Four channel RGBA 32-bit signed integer format, sixteen bytes per pixel.
    /// \note Requires OpenGL ES 3
    GraphicsFormatR32G32B32A32_SINT = 109,

    /// Four channel RGB and alpha 32-bit float format, sixteen bytes per pixel.
    /// \note Requires OpenGL ES 3 or ES 2 with extensions.
    GraphicsFormatR32G32B32A32_SFLOAT = 110,

    /// Single channel Red 16-bit unsigned normalized, two bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16_UNORM = 111,

    /// Single channel Red 16-bit signed normalized, two bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16_SNORM = 112,

    /// Two channel RG 16-bit unsigned normalized, four bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16_UNORM = 113,

    /// Two channel RG 16-bit signed normalized, four bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16_SNORM = 114,

    /// Three channel RGB 16-bit unsigned normalized, six bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16B16_UNORM = 115,

    /// Three channel RGB 16-bit signed normalized, six bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16B16_SNORM = 116,

    /// Four channel RGBA 16-bit unsigned normalized, eight bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16B16A16_UNORM = 117,

    /// Four channel RGBA 16-bit signed normalized, eight bytes per pixel.
    /// \see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_norm16.txt
    GraphicsFormatR16G16B16A16_SNORM = 118,


    /// The first format in the range of valid, usable GL graphics formats.
    GraphicsFormatGlRangeBegin = GraphicsFormatLUMINANCE8_UNORM,

    /// The last format in the range of valid, usable GL graphics formats.
    GraphicsFormatGlRangeEnd = 119,

    // Graphics formats targeting Dave backend:

    /// Single channel alpha 8-bit unsigned normalized framebuffer only format, 8 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_ALPHA8 = GraphicsFormatALPHA8_UNORM,

    /// Single channel luminance 8-bit unsigned normalized framebuffer only format, 8 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_LUM8 = GraphicsFormatLUMINANCE8_UNORM,

    /// Two channel 1-bit alpha and 7-bit luminance unsigned normalized format, 8 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL17 = GraphicsFormatALPHA1_LUMINANCE7_UNORM,

    /// Two channel 4-bit alpha and 4-bit luminance unsigned normalized format, 8 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL44 = GraphicsFormatALPHA4_LUMINANCE4_UNORM,

    /// Two channel alpha and luminance 8-bit unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL88 = GraphicsFormatALPHA8_LUMINANCE8_UNORM,

    /// Two channel aliased single 1-bit alpha/luminance component unsigned normalized texture only format, 1 bit per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL1 = GraphicsFormatALPHALUMINANCE1_UNORM,

    /// Two channel aliased single 2-bit alpha/luminance component unsigned normalized texture only format, 2 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL2 = GraphicsFormatALPHALUMINANCE2_UNORM,

    /// Two channel aliased single 4-bit alpha/luminance component unsigned normalized texture only format, 4 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL4 = GraphicsFormatALPHALUMINANCE4_UNORM,

    /// Two channel aliased single 8-bit alpha/luminance component unsigned normalized texture only format, 8 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_AL8 = GraphicsFormatALPHALUMINANCE8_UNORM,

    /// Three channel RGB 5, 6, 5-bit unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_RGB565 = GraphicsFormatR5G6B5_UNORM_PACK16,

    /// Four channel 1-bit alpha and 5-bit RGB unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_ARGB1555 = GraphicsFormatA1R5G5B5_UNORM,

    /// Four channel 5-bit RGB and 1-bit alpha unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_RGBA5551 = GraphicsFormatR5G5B5A1_UNORM,

    /// Four channel 4-bit alpha and 4-bit RGB unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_ARGB4444 = GraphicsFormatA4R4G4B4_UNORM,

    /// Four channel 4-bit RGB and 4-bit alpha unsigned normalized format, 16 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_RGBA4444 = GraphicsFormatR4G4B4A4_UNORM,

    /// Four channel ARGB 8-bit unsigned normalized format, 32 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_ARGB8888 = GraphicsFormatA8R8G8B8_UNORM,

    /// Four channel RGBA 8-bit unsigned normalized format, 32 bits per pixel.
    GraphicsFormatR_DRW2D_PIXELFORMAT_RGBA8888 = GraphicsFormatR8G8B8A8_UNORM,

    /// Single component 8-bit unsigned integer texture only color lookup table format, 8 bits per component.
    GraphicsFormatR_DRW2D_PIXELFORMAT_CLUT_8 = GraphicsFormatCLUT8_UINT,

    /// Single component 4-bit unsigned integer texture only color lookup table format, 4 bits per component.
    GraphicsFormatR_DRW2D_PIXELFORMAT_CLUT_4 = GraphicsFormatCLUT4_UINT,

    /// Single component 2-bit unsigned integer texture only color lookup table format, 2 bits per component.
    GraphicsFormatR_DRW2D_PIXELFORMAT_CLUT_2 = GraphicsFormatCLUT2_UINT,

    /// Single component 1-bit unsigned integer texture only color lookup table format, 1 bit per component.
    GraphicsFormatR_DRW2D_PIXELFORMAT_CLUT_1 = GraphicsFormatCLUT1_UINT,

    // Metadata values:

    /// The first format in the full range of graphics formats, including invalid values.
    GraphicsFormatFullRangeBegin = GraphicsFormatGlRangeBegin,

    /// The last format in the full range of graphics formats, including invalid values.
    GraphicsFormatFullRangeEnd = GraphicsFormatGlRangeEnd
};

/// Indicates whether format is valid.
/// \param format graphics format to query.
/// \return True if format is valid, otherwise false.
KANZI_API bool isValid(GraphicsFormat format);

/// Returns number of bits per block of the specified format.
/// \param format Graphics format to query.
/// \return Number of bits per block of specified format. For GraphicsFormatNone, 0 is returned.
KANZI_API unsigned int getBitsPerBlock(GraphicsFormat format);

/// Returns number of bytes per block of the specified format.
/// \param format Graphics format to query.
/// \return Number of bytes per block of specified format, rounded down to whole bytes.
/// \see getBitsPerBlock.
KANZI_API unsigned int getBytesPerBlock(GraphicsFormat format);

/// Indicates whether format is compressed format or not.
/// \param format graphics format to query.
/// \return True if format is compressed, otherwise false.
KANZI_API bool isCompressed(GraphicsFormat format);

/// Returns an alternative format which is potentially more widely supported.
/// Fallback format may have more bits for some or all of the component, but never less.
/// Fallback format may have additional channels, fallback format may not drop any component.
/// For example, if R8G8B8 texture format is not supported by graphics device.
/// getFallback() returns R8G8B8A8 format since that is potentially more widely supported.
/// Fallback format is a format which can represent all information of the given format.
/// \param format Format for which fallback format is queried.
/// \return A fallback format for given format, or GraphicsFormatNone if no suitable format was found.
KANZI_API GraphicsFormat getFallback(GraphicsFormat format);

/// Returns a common superset of two formats, or GraphicsFormatNone if formats cannot be combined.
/// The returned common format must have all channels from both given formats. For each channel, the
/// number of bits must equal or exceed number of bits in the given formats.
/// \parem format1 First format
/// \param format2 Second format
/// \return Format which is compatible with both given formats, or GraphicsFormatNone if no suitable format was found.
KANZI_API GraphicsFormat getCommon(GraphicsFormat format1, GraphicsFormat format2);

/// Returns data type of the format.
/// \param format Format to query.
/// \return Data type of given format.
KANZI_API GraphicsDataType getDataType(GraphicsFormat format);

/// Returns number of unique color channels of the format.
/// \param format Format to query.
/// \return Number of unique color channels of given format.
/// If the channel count cannot be determined from the graphics format, 0 is returned.
KANZI_API unsigned int getChannelCount(GraphicsFormat format);

/// Returns data size in bytes for image with specified dimensions and format.
/// For block based images, number of blocks is calculated, and image size is returned
/// as block size times number of blocks. For formats which are not block based,
/// minimum byte-aligned stride size is calculated and height times stride size is
/// returned.
/// \param width Width of image.
/// \param height Height of image.
/// \param format Format of image.
/// \return Size of image of given size and format.
KANZI_API unsigned int getDataSizeBytes(int width, int height, GraphicsFormat format);

/// Indicates whether given format has one more more color channels.
/// Red, green, blue, and luminance are considered color channels.
/// \param format Format to query.
/// \return True if given format has any of the color channels.
KANZI_API bool hasColor(GraphicsFormat format);

/// Indicates whether given format has alpha channel.
/// \param format Format to query.
/// \return True if given format has alpha channel.
KANZI_API bool hasAlpha(GraphicsFormat format);

/// Indicates whether given format has depth channel.
/// \param format Format to query.
/// \return True if given format has depth channel.
KANZI_API bool hasDepth(GraphicsFormat format);

/// Indicates whether given format has stencil channel.
/// \param format Format to query.
/// \return True if given format has stencil channel.
KANZI_API bool hasStencil(GraphicsFormat format);

/// Indicates whether given format has an aliased color channel.
/// \param format Format to query.
/// \return True if given format has an aliased color channel.
KANZI_API bool hasAliasedChannel(GraphicsFormat format);

/// Return number of bits per one element of data type.
/// For GraphicsDataTypeNone, 0 is returned.
/// \param dataType Data type to query.
/// \return Number of bits in given data type.
KANZI_API unsigned int getBitCount(GraphicsDataType dataType);

/// Return number of bits per one element of data type.
/// For GraphicsDataTypeNone, 0 is returned.
/// \param dataType Data type to query.
/// \param componentCount Number of components of the given data type in one element.
/// If the data type is packed, this parameter is ignored and the return value is calculated from the data type alone.
/// \return Number of bits in given data type.
KANZI_API unsigned int getBitCount(GraphicsDataType dataType, unsigned int componentCount);

/// Return number of bytes per one element of data type.
/// \param dataType Data type to query.
/// \return Number of bytes in given data type, rounded down to whole bytes.
/// \see getBitCount.
KANZI_API unsigned int getByteCount(GraphicsDataType dataType);

/// Indicates whether given data type is packed or not.
/// \param dataType Data type to query.
/// \return True if data type is packed. otherwise false.
KANZI_API bool isPacked(GraphicsDataType dataType);

/// Returns number of bytes for graphics data.
/// \param dataType Data type for elements.
/// \param componentCount Number of components of the given data type in one element.
/// If the data type is packed, this parameter is ignored and the return value is calculated from the data type alone.
/// \return Number of bytes in graphics data, rounded down to whole bytes.
/// \see getBitCount.
KANZI_API unsigned int getByteCount(GraphicsDataType dataType, unsigned int componentCount);

/// Returns human readable string for GraphicsDataType.
/// \param dataType Data type to query.
/// \return Human readable string for given graphics data type.
KANZI_API FixedString toFixedString(GraphicsDataType dataType);

/// Returns human readable string for GraphicsFormat.
/// \param format Format to query.
/// \return Human readable string for given graphics format.
KANZI_API FixedString toFixedString(GraphicsFormat format);

/// Returns GraphicsFormat given its name as a human readable string.
/// \param formatName Name of the format.
/// \return GraphicsFormat corresponding to the given format name.
/// If the format cannot be found, nullopt is returned.
KANZI_API optional<GraphicsFormat> findGraphicsFormatByName(string_view formatName);

} // namespace kanzi

#endif // KZ_FORMAT_HPP
