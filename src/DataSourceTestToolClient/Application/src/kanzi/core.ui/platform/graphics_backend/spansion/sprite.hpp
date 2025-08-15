// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_SPRITE_HPP
#define KZ_SPANSION_SPRITE_HPP

#include "mml_gdc_driver_api.h"

#include <kanzi/graphics_backend/bitmap.hpp>

#include <kanzi/graphics_backend/kz_test.hpp>


namespace  kanzi
{

class Sprite;
typedef shared_ptr<Sprite> SpriteSharedPtr;

class Sprite
{
public:
    explicit Sprite(const MML_GDC_DISPLAY& display, MML_GDC_DISP_LAYER layer, MML_GDC_DISP_SUB_LAYER sublayer, shared_ptr<Bitmap> bitmap, MM_U32 x = 0, MM_U32 y = 0);

    explicit Sprite(const MML_GDC_DISPLAY& display, MM_U32 x = 0, MM_U32 y = 0, MM_U32 width = 0, MM_U32 height = 0, MML_GDC_DISP_LAYER layer = MML_GDC_DISP_LAYER_0, MM_U32 features = 0, MML_GDC_DISP_SUB_LAYER sublayer = MML_GDC_DISP_SUB_LAYER_1);

    virtual ~Sprite();

    void setPosition(MM_U32 x, MM_U32 y);

    void setSize(MM_U32 width, MM_U32 height);

    void setMatrix(MM_U32 target, MM_FLOAT* matrix);

    void setBlendMode(MM_U32 mode);

    /// Sets the sprite color.
    /// \param color The color in 0xRRGGBBAA format.
    void setColor(MM_U32 color);

    void disable();

    void enable();

    void setAttribute(MML_GDC_DISP_WIN_ATTR attribute, MM_U32 value);

    void commit();

    void syncToWindow(MML_GDC_SYNC sync);

    void setBitmap(shared_ptr<Bitmap> bitmap);

    Bitmap* getBitmap() const;

    MM_U32 getAttribute(MML_GDC_DISP_WIN_ATTR attribute) const;

    MM_U32 getWidth() const
    {
        return m_width;
    }

    MM_U32 getHeight() const
    {
        return m_height;
    }

    MM_U32 getX() const
    {
        return m_x;
    }

    MM_U32 getY() const
    {
        return m_y;
    }

    bool enabled() const
    {
        return m_enabled;
    }

    MML_GDC_DISP_LAYER getLayer() const
    {
        return m_layer;
    }

    MML_GDC_DISP_SUB_LAYER getSubLayer() const
    {
        return m_sublayer;
    }

protected:
    MML_GDC_DISP_WINDOW m_win;
    BitmapSharedPtr m_bitmap;
    MML_GDC_SYNC m_syncBlit;
    MM_U32 m_width;
    MM_U32 m_height;
    MM_U32 m_x;
    MM_U32 m_y;
    bool m_enabled;
    MML_GDC_DISP_LAYER m_layer;
    MML_GDC_DISP_SUB_LAYER m_sublayer;
};

}


#endif
