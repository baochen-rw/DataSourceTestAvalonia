// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_GL_GEOMETRY_FRAME_HPP
#define KZ_GL_GEOMETRY_FRAME_HPP


#include "geometry_gl.hpp"

#include <kanzi/core.ui/graphics2d/quad_description.hpp>


namespace kanzi
{


// Forward declaration.
class FrameDescription;


/// Geometry representing a quad that has its center cut out.
class KANZI_API GeometryFrame : public GeometryGlBuffer<25>
{
public:
    /// Constructor.
    ///
    /// \param frame Frame description used to generate the geometry.
    /// \param tiling Tiling for the texture coordinates.
    explicit GeometryFrame(const FrameDescription& frame, Vector2 tiling);

protected:
    /// Add single quad description.
    ///
    /// \param offset Vertex offset to add to.
    /// \param quad Quad description to add.
    /// \param tiling Tiling for the texture coordinates.
    /// \param duplicateFirstVertex True to duplicate first vertex.
    /// \param duplicateLastVertex True to duplicate last vertex.
    void addQuadDescription(size_t offset, const QuadDescription& quad, Vector2 tiling, bool duplicateFirstVertex, bool duplicateLastVertex);
};


}


#endif
