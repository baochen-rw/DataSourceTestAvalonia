// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_FRAMEBUFFER_HPP
#define KZ_SPANSION_FRAMEBUFFER_HPP

#include <kanzi/platform/memory.hpp>
#include <kanzi/resource/resource.hpp>
#include "texture.hpp"

namespace kanzi
{

class Framebuffer;

typedef shared_ptr<Framebuffer> FramebufferSharedPtr;

class KANZI_API Framebuffer: public Resource
{
public:
    enum AttachmentPoint
    {
        AttachmentPointColor0
    };

    unsigned int getCommonWidth() const
    {
        return m_width;
    }

    unsigned int getCommonHeight() const
    {
        return m_height;
    }

    TextureSharedPtr getTexture(AttachmentPoint attachment) const
    {
        return m_texture;
    }

    Texture* getNativeHandle() const
    {
        return m_texture.get();
    }

    TextureSharedPtr m_texture;
    unsigned m_width;
    unsigned m_height;
};

}

#endif
