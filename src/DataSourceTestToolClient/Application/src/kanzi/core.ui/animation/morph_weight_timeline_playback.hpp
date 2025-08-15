// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MORPH_WEIGHT_TIMELINE_PLAYBACK_HPP
#define KZ_MORPH_WEIGHT_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"

namespace kanzi
{

// Forward declarations.
class Model3D;
class MorphRuntime;
class TimelinePlaybackContext;

class MorphWeightTimeline;
typedef shared_ptr<MorphWeightTimeline> MorphWeightTimelineSharedPtr;

class MorphWeightTimelinePlayback;
typedef shared_ptr<MorphWeightTimelinePlayback> MorphWeightTimelinePlaybackSharedPtr;

/// Timeline Playback for morph timeline.
class MorphWeightTimelinePlayback : public TimelinePlayback
{
public:
    /// Creates morph weight timeline playback.
    ///
    /// \param timeline Morph timeline this playback is going to run.
    /// \param context Playback context used to resolve targets.
    static MorphWeightTimelinePlaybackSharedPtr create(MorphWeightTimelineSharedPtr timeline, TimelinePlaybackContext& context);

protected:
    /// Constructor.
    ///
    /// \param timeline Morph timeline this playback is going to run.
    /// \param context Playback context used to resolve targets.
    explicit MorphWeightTimelinePlayback(MorphWeightTimelineSharedPtr timeline, TimelinePlaybackContext& context);

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

private:
    /// Morph timeline being animated.
    MorphWeightTimelineSharedPtr m_morphTimeline;
    /// Model whose morph runtime should be modified.
    weak_ptr<Model3D> m_model;
};

}

#endif // KZ_MORPH_TIMELINE_HPP

#endif
