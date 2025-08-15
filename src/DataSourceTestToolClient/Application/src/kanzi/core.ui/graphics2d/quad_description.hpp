// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_QUAD_DESCRIPTION_HPP
#define KZ_QUAD_DESCRIPTION_HPP

#include <kanzi/core/math/vector2.hpp>

#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/legacy/util/math/kzc_rectangle.hpp>

namespace kanzi
{

/// Quad description. Used to create renderable quad geometry.
class KANZI_API QuadDescription
{
public:
    /// Clipping mask - center area.
    static const unsigned int ClippingResultCenter = (1 << 0);

    /// Clipping mask - bottom part.
    static const unsigned int ClippingResultBottom = (1 << 1);
    
    /// Clipping mask - left part.
    static const unsigned int ClippingResultLeft = (1 << 2);

    /// Clipping mask - right part.
    static const unsigned int ClippingResultRight = (1 << 3);

    /// Clipping mask - top part.
    static const unsigned int ClippingResultTop = (1 << 4);

    /// Single rectangular outside area, do not care which one.
    static const unsigned int ClippingResultSingleOutsideRectangle = (1 << 5);

    /// Layer clipping result - any outside area.
    static const unsigned int ClippingResultOutside = (2 + 4 + 8 + 16 + 32);

public:
    /// Empty constructor.
    explicit QuadDescription()
    {
    }

    /// Constructor.
    ///
    /// \param offset Offset.
    /// \param size Size.
    explicit QuadDescription(Vector2 offset, Vector2 size) :
        m_coords(offset.getX(), offset.getY(), size.getX(), size.getY()),
        m_texcoords(0.0f, 0.0f, 1.0f, 1.0f)
    {
    }

    /// Constructor with full info.
    ///
    /// \param offset Offset.
    /// \param size Size.
    /// \param texcoordOffset Texcoord offset.
    /// \param texcoordSize Texcoord size.
    explicit QuadDescription(Vector2 offset, Vector2 size, Vector2 texcoordOffset, Vector2 texcoordSize) :
        m_coords(offset.getX(), offset.getY(), size.getX(), size.getY()),
        m_texcoords(texcoordOffset.getX(), texcoordOffset.getY(), texcoordSize.getX(), texcoordSize.getY())
    {
    }

    /// Clip from bottom side.
    ///
    /// \param border Border to clip to.
    /// \return Clip mask of areas remaining.
    unsigned int clipBottom(float border);

    /// Clip from left side.
    ///
    /// \param border Border to clip to.
    /// \return Clip mask of areas remaining.
    unsigned int clipLeft(float border);

    /// Clip from right side.
    ///
    /// \param border Border to clip to.
    /// \return Clip mask of areas remaining.
    unsigned int clipRight(float border);

    /// Clip from top side.
    ///
    /// \param border Border to clip to.
    /// \return Clip mask of areas remaining.
    unsigned int clipTop(float border);

    /// Get quad offset.
    ///
    /// \return Quad offset vector.
    Vector2 getOffset() const
    {
        return Vector2(m_coords.x, m_coords.y);
    }

    /// Get quad size.
    ///
    /// \return Quad size vector.
    Vector2 getSize() const
    {
        return Vector2(m_coords.width, m_coords.height);
    }

    /// Get texture size.
    ///
    /// \return Texture offset vector.
    Vector2 getTextureOffset() const
    {
        return Vector2(m_texcoords.x, m_texcoords.y);
    }

    /// Get texture size.
    ///
    /// \return Texture size vector.
    Vector2 getTextureSize() const
    {
        return Vector2(m_texcoords.width, m_texcoords.height);
    }

private:
    /// Position.
    struct KzcRectangle m_coords;

    /// Texture coordinates.
    struct KzcRectangle m_texcoords;
};

}

#endif
