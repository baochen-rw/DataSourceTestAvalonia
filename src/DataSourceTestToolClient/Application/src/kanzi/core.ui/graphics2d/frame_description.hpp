// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_FRAME_DESCRIPTION_HPP
#define KZ_FRAME_DESCRIPTION_HPP

#include "quad_description.hpp"

#include <kanzi/core/cpp/optional.hpp>

namespace kanzi
{

/// Description of a frame, the remaining area of a quad with another quad cut out.
class KANZI_API FrameDescription
{
public:
    /// Constructor.
    ///
    /// \param bg Background quad.
    /// \param fg Foreground quad.
    explicit FrameDescription(const QuadDescription& bg, const QuadDescription& fg, unsigned int clippingMask);

    /// Access frame component.
    ///
    /// \param idx Index of component.
    const optional<QuadDescription>& getQuad(size_t idx) const
    {
        return m_quads[idx];
    }

private:
    /// First component quad of the frame.
    optional<QuadDescription> m_quads[4];
};

}

#endif
