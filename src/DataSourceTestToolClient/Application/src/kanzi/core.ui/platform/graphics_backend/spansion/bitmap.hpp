// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_BITMAP_HPP
#define KZ_SPANSION_BITMAP_HPP

#include <kanzi/platform/memory.hpp>
#include <kanzi/graphics/format.hpp>

#include "kz_test.hpp"

namespace kanzi
{

GraphicsFormat convertFormat(MML_GDC_SURF_FORMAT spansionFormat);

class Bitmap
{
    
public:
    static bool formatHasAlpha(MML_GDC_SURF_FORMAT format);

    /// Constructs a bitmap from a native format binary blob.
    /// \param data Pointer to the beginning of the binary blob.
    explicit Bitmap(const void* data);

    /// Constructs a read-write bitmap by allocating video memory.
    /// The content of the bitmap is left uninitialized.
    /// \param width Width of the bitmap in pixels.
    /// \param width Height of the bitmap in pixels.
    /// \param format Data format of the bitmap.
    explicit Bitmap(MM_U32 width, MM_U32 height, MML_GDC_SURF_FORMAT format);

    /// Constructs a bitmap from image data.
    /// \param data Pointer to the beginning of image data.
    /// \param width Width of the bitmap in pixels.
    /// \param width Height of the bitmap in pixels.
    /// \param format Data format of the bitmap.
    explicit Bitmap(void* data, MM_U32 width, MM_U32 height, MML_GDC_SURF_FORMAT format);

    ~Bitmap();

    MML_GDC_SURFACE get() const
    {
        return m_surface;
    }

    MM_U32 getWidth() const
    {
        return utSurfWidth(m_surface);
    }

    MM_U32 getHeight() const
    {
        return utSurfHeight(m_surface);
    }

    MML_GDC_SURF_FORMAT getFormat() const;

    MM_U32 getStride() const
    {
        return getAttribute(MML_GDC_SURF_ATTR_STRIDE);
    }

    MM_U32 getBitsPerPixel() const
    {
        return getAttribute(MML_GDC_SURF_ATTR_BITPERPIXEL);
    }

    MM_U32 getColorBits() const
    {
        return getAttribute(MML_GDC_SURF_ATTR_COLORBITS);
    }

    MM_U32 getColorShift() const
    {
        return getAttribute(MML_GDC_SURF_ATTR_COLORSHIFT);
    }

    MM_U32 getSize() const
    {
        return getAttribute(MML_GDC_SURF_ATTR_SIZEINBYTES);
    }

    void* getPhysicalAddress() const
    {
        return reinterpret_cast<void*>(getAttribute(MML_GDC_SURF_ATTR_PHYS_ADDRESS));
    }

    void* getVirtualAddress() const
    {
        return reinterpret_cast<void*>(getAttribute(MML_GDC_SURF_ATTR_BASE_ADDRESS));
    }

    MM_U32 getAttribute(MML_GDC_SURF_ATTR attribute) const
    {
        MM_ERROR ret = MML_OK;
        MM_U32 value;

        KZ_TEST(ret, mmlGdcSmGetAttribute(m_surface, attribute, &value));

        return value;
    }

    void setAttribute(MML_GDC_SURF_ATTR attribute, MM_U32 value)
    {
        MM_ERROR ret = MML_OK;

        KZ_TEST(ret, mmlGdcSmSetAttribute(m_surface, attribute, value));
    }

    void setPixel(MM_U32 x, MM_U32 y, MM_U08 r, MM_U08 g, MM_U08 b, MM_U08 a)
    {
        MM_ERROR ret = MML_OK;

        KZ_TEST(ret, utSurfSetPixel(m_surface, x, y, r, g, b, a));
    }


protected:
    MML_GDC_SURFACE m_surface;
    bool m_ownsBuffer;
};

typedef shared_ptr<Bitmap> BitmapSharedPtr;

}

#endif
