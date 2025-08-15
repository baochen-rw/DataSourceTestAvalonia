// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PARALLEL_TIMELINE_PLAYBACK_HPP
#define KZ_PARALLEL_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{

// Forward declaration.
class TimelinePlaybackContext;

class ParallelTimeline;
typedef shared_ptr<ParallelTimeline> ParallelTimelineSharedPtr;

class ParallelTimelinePlayback;
typedef shared_ptr<ParallelTimelinePlayback> ParallelTimelinePlaybackSharedPtr;

/// Playback control class for ParallelTimeline.
class KANZI_API ParallelTimelinePlayback : public TimelinePlayback
{
public:

    static ParallelTimelinePlaybackSharedPtr create(ParallelTimelineSharedPtr parallelTimeline, TimelinePlaybackContext& context)
    {
        ParallelTimelinePlaybackSharedPtr timelinePlayback = make_polymorphic_shared_ptr<TimelinePlayback>(new ParallelTimelinePlayback(parallelTimeline, context));
        return timelinePlayback;
    }

protected:

    explicit ParallelTimelinePlayback(ParallelTimelineSharedPtr parallelTimeline, TimelinePlaybackContext& context);

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

    /// TimelinePlayback::onAppliedStateChangedOverride() implementation.
    virtual void onAppliedStateChangedOverride() KZ_OVERRIDE;

    /// TimelinePlayback::onPlaybackCompletedOverride() implementation.
    virtual void onPlaybackCompletedOverride() KZ_OVERRIDE;

private:

    typedef vector<TimelinePlaybackSharedPtr> ChildContainer;
    typedef ChildContainer::const_iterator ChildConstIterator;

    ChildContainer m_children;
    ParallelTimelineSharedPtr m_parallelTimeline;
};

}

#endif