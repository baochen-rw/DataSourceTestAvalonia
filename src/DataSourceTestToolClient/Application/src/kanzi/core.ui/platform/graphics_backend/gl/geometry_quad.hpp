// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_GL_GEOMETRY_QUAD_HPP
#define KZ_GL_GEOMETRY_QUAD_HPP

#include "geometry_gl.hpp"

namespace kanzi
{

// Forward declaration.
class QuadDescription;

/// Renderable quad.
class KANZI_API GeometryQuad : public GeometryGlBuffer<4>
{
public:
    /// Constructor.
    /// \param quad Quad to extract geometry from.
    explicit GeometryQuad(const QuadDescription& quad);

    /// Constructor.
    /// \param quad Quad to extract geometry from.
    /// \param tiling Tiling for the texture coordinates.
    explicit GeometryQuad(const QuadDescription& quad, Vector2 tiling);

    /// Create geometry based on tiling.
    /// Called upon construction, but can also be called to replace existing geometry.
    /// \param quad Quad to read.
    /// \param tiling Tiling for the texture coordinates.
    void setGeometry(const QuadDescription& quad, Vector2 tiling);
};

}

#endif