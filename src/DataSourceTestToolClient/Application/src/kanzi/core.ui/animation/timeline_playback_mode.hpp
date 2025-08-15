// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PLAYBACK_MODE_HPP
#define KZ_PLAYBACK_MODE_HPP


#include <kanzi/core.ui/animation/timeline.hpp>


namespace kanzi
{

/// Playback type of the timeline.
enum KzuTimeLineEntryPlaybackMode
{
    /// Plays the animation timeline normally from the start to end.
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_NORMAL,

    /// Plays the animation timeline in reverse from the end to start.
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_REVERSE,

    /// Plays the animation timeline first normally, then in reverse.
    KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_PINGPONG
};


Timeline::DirectionBehavior convert(KzuTimeLineEntryPlaybackMode mode);
KzuTimeLineEntryPlaybackMode convert(Timeline::DirectionBehavior behavior);

}

#endif
