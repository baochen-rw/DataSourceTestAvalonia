// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_PLAY_ANIMATION_ACTION_H
#define KZU_PLAY_ANIMATION_ACTION_H

#include "action.hpp"

#include <kanzi/core.ui/animation/timeline_resource.hpp>
#include <kanzi/core.ui/animation/timeline_playback_mode.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

class Domain;
class Node;

class ParallelTimeline;
typedef shared_ptr<ParallelTimeline> ParallelTimelineSharedPtr;


class PlayAnimationAction;
typedef shared_ptr<PlayAnimationAction> PlayAnimationActionSharedPtr;


/// Play animation action is the action which starts playback of specified
/// timeline when it is invoked.
///
/// Play animation action performs playback of timeline specified in the Animation
/// property. All animations in applied timeline are relative: values calculated
/// in animations are added to property values instead of replacing it. Paths
/// to animated objects are resolved relative to the path specified in the
/// AnimatedObjectPathProperty. The path in AnimatedObjectPathProperty is resolved
/// relative to the node where play animation action is attached. If the path
/// could not be resolved, play animation action will not start playback.
///
/// If play animation action is invoked before its ongoing playback is finished,
/// the action will stop ongoing playback and start new one. If play animation
/// action is detached from the node while its playback is ongoing, the action
/// will stop the playback.
class KANZI_API PlayAnimationAction : public Action
{
public:

    /// \name Properties
    /// \{
#include "play_animation_action_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(PlayAnimationAction, Action, "Kanzi.PlayAnimationAction")
        KZ_METACLASS_PROPERTY_TYPE(AnimatedObjectPathProperty)
        KZ_METACLASS_PROPERTY_TYPE(AnimationProperty)
        KZ_METACLASS_PROPERTY_TYPE(PlaybackModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(DurationScaleProperty)
        KZ_METACLASS_PROPERTY_TYPE(RepeatCountProperty)
        KZ_METACLASS_PROPERTY_TYPE(RestoreOriginalValuesAfterPlaybackProperty)
        KZ_METACLASS_PROPERTY_TYPE(RelativePlaybackProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static PlayAnimationActionSharedPtr create(Domain* domain, string_view name);

    /// Starts playback of timeline specified in the Animation property.
    /// If play animation action has currently ongoing playback, the
    /// playback will be stopped before starting new one.
    void play();

    /// Stops currently ongoing playback. Next invocation of play animation action
    /// or next call to its play() function will start new playback. If there is
    /// no currently ongoing playback, this function will do nothing.
    void stop();

protected:

    /** Create a play animation action. */
    explicit PlayAnimationAction(Domain* domain, string_view name);

    /** Attach play animation action. */
    virtual void onAttach() KZ_OVERRIDE;
    /** Detach play animation action. */
    virtual void onDetach() KZ_OVERRIDE;
    /** Invoke play animation action. */
    virtual void onInvoke() KZ_OVERRIDE;
    /** Implementation of delayed invoke of play animation action. */
    virtual void onDelayedInvoke() KZ_OVERRIDE;

    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

private:

    void onPlaybackFinished(TimelinePlayback& timelinePlayback);

    /// Animation timeline.
    TimelineResourceSharedPtr m_timeline;

    /// Root timeline where all playback options are set and where animation timeline is added.
    ParallelTimelineSharedPtr m_rootTimeline;

    /// Playback for timelines.
    TimelinePlaybackSharedPtr m_playback;
};

}

#endif
