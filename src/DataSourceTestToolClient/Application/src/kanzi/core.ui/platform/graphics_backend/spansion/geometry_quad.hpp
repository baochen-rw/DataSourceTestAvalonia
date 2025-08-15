// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GEOMETRY_QUAD_HPP
#define KZ_GEOMETRY_QUAD_HPP


#include "geometry.hpp"

#include <kanzi/graphics2d/quad_description.hpp>
#include <kanzi/math/vector2.hpp>


namespace kanzi
{


/// Renderable quad.
class KANZI_API GeometryQuad : public Geometry
{
public:
    /// Constructor.
    ///
    /// \param quad Quad to extract geometry from.
    explicit GeometryQuad(const QuadDescription& quad);

    /// Constructor.
    ///
    /// \param quad Quad to extract geometry from.
    /// \param tiling Tiling for the texture coordinates.
    explicit GeometryQuad(const QuadDescription& quad, Vector2 tiling);


    Vector2 getClipOffset() const;
    Vector2 getClipSize() const;

private:

    Vector2 m_clipOffset;
    Vector2 m_clipSize;
};


}


#endif
