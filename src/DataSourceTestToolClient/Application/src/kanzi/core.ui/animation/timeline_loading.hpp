// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_LOADING_HPP
#define KZ_TIMELINE_LOADING_HPP


#include <kanzi/core.ui/kzb/object_loader.hpp>


namespace kanzi
{

/// Registers loaders for build-in timeline types.
void registerTimelineLoaders(ObjectLoader& objectLoader);

}

#endif
