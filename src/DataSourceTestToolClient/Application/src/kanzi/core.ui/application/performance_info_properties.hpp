// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PERFORMANCE_INFO_PROPERTIES_HPP
#define KZ_PERFORMANCE_INFO_PROPERTIES_HPP

namespace kanzi
{

/// Configurable performance info display properties.
struct PerformanceInfoProperties
{
    PerformanceInfoProperties() :
        positionX(0),
        positionY(0)
    {
    }

    /// X position of the HUD text.
    int positionX;

    /// Y position of the HUD text.
    int positionY;
};
}

#endif // KZ_PERFORMANCE_INFO_PROPERTIES_HPP
