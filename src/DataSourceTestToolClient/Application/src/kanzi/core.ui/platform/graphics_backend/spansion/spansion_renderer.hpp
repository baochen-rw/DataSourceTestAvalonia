// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDERING_SPANSION_RENDERER_HPP
#define KZ_RENDERING_SPANSION_RENDERER_HPP

#include <kanzi/platform/memory.hpp>
#include <system/kzs_types.h>
#include <kanzi/math/rectangle.hpp>

struct KzcMemoryManager;

namespace kanzi
{

typedef Rectangle<int> ViewportRectangle;

class Renderer;
typedef shared_ptr<Renderer> RendererSharedPtr;

class KANZI_API Renderer
{
public:
    explicit Renderer(const KzcMemoryManager* memoryManager)
    {
    }

    virtual void initialize(kzUint vertexBufferPoolSize, kzUint indexBufferPoolSize)
    {
    }
};

}


#endif
