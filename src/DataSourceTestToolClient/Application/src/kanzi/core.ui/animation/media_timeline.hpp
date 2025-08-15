// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MEDIA_TIMELINE_HPP
#define KZ_MEDIA_TIMELINE_HPP


#include "timeline.hpp"

namespace kanzi
{

/// Timeline playing a media file.
class KANZI_API MediaTimeline: public Timeline
{
public:

    explicit MediaTimeline(Domain* domain) : Timeline(domain)
    {
    }
};

}

#endif