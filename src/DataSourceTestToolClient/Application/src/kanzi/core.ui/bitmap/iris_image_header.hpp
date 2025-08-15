// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_IRIS_IMAGE_HEADER_HPP
#define KZ_IRIS_IMAGE_HEADER_HPP

#include <kanzi/core.ui/graphics/format.hpp>


namespace kanzi
{

#pragma pack(push, 1)
struct IrisImageHeader
{
    uint32_t size;
    uint16_t width;
    uint16_t height;
    uint16_t stride;
    uint8_t bpp;
    uint8_t flags;
    uint8_t componentBits[4];
    uint8_t componentShift[4];
    uint16_t clutCount;
    uint8_t clutMode;
    uint8_t clutBpp;
    uint8_t clutComponentBits[4];
    uint8_t clutComponentShift[4];

public:
    uint32_t getSize() const { return size; }
    uint16_t getWidth() const { return width; }
    uint16_t getHeight() const { return height; }

    GraphicsFormat getFormat() const;

    bool hasClut() const;
};
#pragma pack(pop)

}

#endif
