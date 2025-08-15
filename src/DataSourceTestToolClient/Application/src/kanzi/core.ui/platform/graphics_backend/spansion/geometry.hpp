// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_GEOMETRY_HPP
#define KZ_GEOMETRY_HPP


#include "renderer.hpp"


namespace kanzi
{


/// Renderable geometry.
///
/// This is a generic base class that is inherited by distinct geometric forms.
class KANZI_API Geometry
{
public:
    /// Need virtual destructor, later inherited by classes with virtuals.
    virtual ~Geometry()
    {
    }
};


}


#endif