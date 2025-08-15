// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SEQUENTIAL_TIMELINE_HPP
#define KZ_SEQUENTIAL_TIMELINE_HPP


#include "timeline.hpp"

namespace kanzi
{

class SequentialTimeline;
typedef shared_ptr<SequentialTimeline> SequentialTimelineSharedPtr;


/// The Kanzi animation system consists animations and timelines: animations define how to animate a property,
/// and timelines map the animations to time and to objects you want to animate.
///
/// Sequential timeline allows you to group timelines which Kanzi plays one after another. A sequential timeline
/// ends when the last animations in the last child timeline end. Use this timeline to organize collections of
/// timelines and create a composition of timelines.


class KANZI_API SequentialTimeline : public Timeline
{
    typedef vector<TimelineSharedPtr> ChildContainer;

public:

    void addChild(TimelineSharedPtr childTimeline)
    {
        m_children.push_back(childTimeline);
    }

protected:

    explicit SequentialTimeline(Domain* domain) : Timeline(domain)
    {
    }

private:

    ChildContainer m_children;
};

}

#endif