// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_REGISTER_DEFAULT_RESOURCES_HPP
#define KZ_REGISTER_DEFAULT_RESOURCES_HPP

#include <kanzi/core/legacy/kzs_types.hpp>

namespace kanzi
{

class Domain;
class Screen;
class Renderer3D;


/// Registers default resources in the resource manager and Screen node's dictionary.
KANZI_API void registerDefaultResources(Screen& screen);

}


#endif
