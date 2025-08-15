// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDERING_SPANSION_RENDERER3D_HPP
#define KZ_RENDERING_SPANSION_RENDERER3D_HPP

#include <system/kzs_types.h>
#include <kanzi/platform/memory.hpp>
#include <kanzi/rendering/composition_stack.hpp>

#include "sprite_pool.hpp"

#include <ut_class_ctx.h>

namespace kanzi
{

class Renderer3D;
typedef shared_ptr<Renderer3D> Renderer3DSharedPtr;

class KANZI_API Renderer3D
{
public:

    explicit Renderer3D();

    ~Renderer3D();

    CompositionStack& getCompositionStack()
    {
        return m_compositionStack;
    }

    CompositionStack m_compositionStack;

    MML_GDC_PE_CONTEXT getContext() const
    {
        return m_ctx;
    }

    SpritePool& getSpritePool()
    {
        return m_spritePool;
    }

    CCtx& getFontContext()
    {
        return m_cctx;
    }

    void present(unsigned int DisplayHeight);

    void clearFramebuffer(Texture* texture, Vector2 limits);

    void clearScreen(ColorRGBA clearColor);

    void initialize(MML_GDC_DISPLAY display, MML_GDC_PE_CONTEXT context, void* pipeline);

    void resetFrame();

    void endFrame();

    void reset();

    void uninitialize();

private:

    SpritePool m_spritePool;
    MML_GDC_DISPLAY    m_display;
    MML_GDC_PE_CONTEXT m_ctx;
    void*              m_pipeline;
    MML_GDC_SYNC m_sync;
    CCtx m_cctx;
    MM_U32 m_screenClearColor;
};

void convertMatrix(const Matrix4x4& transform, Mat3x3& spansionTransform, float screenHeight, float imageHeight);


}


#endif
