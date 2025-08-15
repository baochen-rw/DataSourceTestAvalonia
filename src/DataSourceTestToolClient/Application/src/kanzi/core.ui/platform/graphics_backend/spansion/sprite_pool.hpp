// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPRITE_POOL_HPP
#define KZ_SPRITE_POOL_HPP


#include <cstdlib>

#include "mm_types.h"
#include "pe_matrix.h"

#include <kanzi/platform/vector.hpp>
#include <kanzi/platform/utility.hpp>
#include <kanzi/platform/iterator.hpp>
#include <kanzi/math/matrix4x4.hpp>
#include <kanzi/error/exception.hpp>

#include "sprite.hpp"


namespace kanzi
{

class KANZI_API SpritePool
{
public:
    explicit SpritePool();
    ~SpritePool();

    void initialize(const MML_GDC_DISPLAY& display);

    SpriteSharedPtr getNext();
    SpriteSharedPtr getNextBlending(MM_U32 x, MM_U32 y, MM_U32 width, MM_U32 height);

    void commitAll();

    void syncAll(MML_GDC_SYNC sync);

    /// Disable unused sprites. Free all sprites for reuse in next frame.
    void reset();

private:

    SpriteSharedPtr getNextFallback();

    struct Impl;
    Impl* m_impl;
};

}

#endif
