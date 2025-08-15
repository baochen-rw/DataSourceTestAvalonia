// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GEOMETRY_FRAME_HPP
#define KZ_GEOMETRY_FRAME_HPP


#include "geometry.hpp"

#include <kanzi/graphics2d/frame_description.hpp>


namespace kanzi
{

// Forward declaration.
class FrameDescription;


/// Geometry representing a quad that has its center cut out.
class KANZI_API GeometryFrame : public Geometry
{
public:
    /// Constructor.
    ///
    /// \param frame Frame description used to generate the geometry.
    /// \param tiling Tiling for the texture coordinates.
    explicit GeometryFrame(const FrameDescription& frame, Vector2 tiling);

private:
    FrameDescription m_frame;
};


}


#endif
