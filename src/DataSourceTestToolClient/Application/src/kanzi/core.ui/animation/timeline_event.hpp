// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_EVENT_HPP
#define KZ_TIMELINE_EVENT_HPP


#include "timeline.hpp"

namespace kanzi
{

/// Event on a timeline.
class KANZI_API TimelineEvent : public Timeline
{
public:

    explicit TimelineEvent(Domain* domain) : Timeline(domain)
    {
    }

    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE
    {
        return chrono::milliseconds::zero();
    }
};

}

#endif