// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ANIMATION_PLAYER_HPP
#define KZ_ANIMATION_PLAYER_HPP


#include <kanzi/core.ui/animation/timeline_playback_mode.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node_component/node_component.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core/message/message_type.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

/// Forward declarations.
class Domain;
class ParallelTimeline;
class TimelinePlayback;
class AnimationPlayer;

typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;
typedef shared_ptr<AnimationPlayer> AnimationPlayerSharedPtr;
typedef shared_ptr<ParallelTimeline> ParallelTimelineSharedPtr;


/// Use the Animation Player to play back an animation timeline that you set using the
/// #TimelineProperty property in that Animation Player. Kanzi resolves paths to animated nodes
/// relative to the node where you attach an Animation Player.
///
/// To control the playback of an Animation Player, send these messages to the node where you attached
/// the Animation Player:
/// - #PlayMessage to start an animation timeline.
/// - #PauseMessage to pause a running animation timeline.
/// - #ResumeMessage to resume a paused or stopped animation timeline.
/// - #StopMessage to stop a running or paused animation timeline.
///
/// By default, an Animation Player does not start playback until you send the #PlayMessage message
/// to the node. To set an Animation Player to start the playback when you attach the Animation
/// Player to a node, enable the #AutoplayEnabledProperty property.
///
/// When you start the playback of an Animation Player by sending to it the #PlayMessage or #ResumeMessage
/// message, or if the #AutoplayEnabledProperty property is enabled, the player adds its 
/// timeline as a child to a parallel timeline and applies all playback settings from its 
/// #PlaybackModeProperty, #DurationScaleProperty and #RepeatCountProperty properties to it.
/// If you start the playback by sending a #PlayMessage message with playback arguments, the player
/// adds its parallel timeline as a child to yet another parallel timeline and applies playback
/// settings from the PlayMessageArguments to it.
///
/// \see PropertyDrivenAnimationPlayer, PropertyTargetInterpolator
///
/// Examples
/// ----
///
/// To create animation player and set timeline:
/// \snippet test_animation_player.cpp Create animation player
///
/// To attach animation player to the node:
/// \snippet test_animation_player.cpp Attach animation player to the node
///
/// To start animation player:
/// \snippet test_animation_player.cpp Start animation player
///
/// To pause animation player:
/// \snippet test_animation_player.cpp Pause animation player
///
/// To resume animation player:
/// \snippet test_animation_player.cpp Resume animation player
///
/// To stop animation player:
/// \snippet test_animation_player.cpp Stop animation player
///
/// To detach animation player from the node:
/// \snippet test_animation_player.cpp Detach animation player from the node
///
class KANZI_API AnimationPlayer : public NodeComponent
{
public:

    /// Sets the animation timeline that an Animation Player plays after you attach it.
    static PropertyType<ResourceSharedPtr> TimelineProperty;

    /// Sets whether an Animation Player starts the playback of its animation timeline immediately
    /// after the player is attached to a node which is attached to the scene graph.
    /// By default, autoplay is disabled.
    static PropertyType<bool> AutoplayEnabledProperty;

    /// Sets whether an Animation Player plays animation timelines in a relative manner by adding
    /// the animated value to the target property value instead of replacing the property value.
    /// By default, relative playback is disabled.
    static PropertyType<bool> RelativePlaybackProperty;

    /// Sets whether animated properties return to their initial values after the playback of
    /// an animation timeline ends. By default, this is disabled.
    static PropertyType<bool> RestoreOriginalValuesAfterPlaybackProperty;

    /// Sets the mode of an animation timeline playback to either:
    /// * Normal plays the animation timeline normally from the start to end. This is the default value.
    /// * Reverse plays the animation timeline in reverse from the end to start. 
    /// * Ping pong plays the animation timeline first normally, then in reverse.
    static PropertyType<KzuTimeLineEntryPlaybackMode> PlaybackModeProperty;

    /// Sets the amount by which the duration of an animation timeline is scaled during its playback.
    /// For example:
    /// * When set to 1.0, the animation is of the same length as it is defined in the animation. This is
    ///   the default value.
    /// * When set to 0.5, the animation is half as long as it is defined in the animation.
    /// * When set to 2.0, the animation is twice as long as it is defined in the animation.
    static PropertyType<float> DurationScaleProperty;

    /// Sets how many times an animation timeline is played during its playback.
    /// The default value is 1.
    static PropertyType<int> RepeatCountProperty;

    /// Message arguments for Play message.
    class KANZI_API PlayMessageArguments : public NodeComponentTargetMessageArguments
    {
    public:

        /// Sets the mode of an animation timeline playback to either:
        /// * Normal plays the animation timeline normally from the start to end. This is the default value.
        /// * Reverse plays the animation timeline in reverse from the end to start. 
        /// * Ping pong plays the animation timeline first normally, then in reverse.
        static PropertyType<int> PlaybackModeProperty;

        /// Sets the amount by which the duration of an animation timeline is scaled during its playback.
        /// For example:
        /// * When set to 1.0, the animation is of the same length as it is defined in the animation. This is
        ///   the default value.
        /// * When set to 0.5, the animation is half as long as it is defined in the animation.
        /// * When set to 2.0, the animation is twice as long as it is defined in the animation.
        static PropertyType<float> DurationScaleProperty;

        /// Sets how many times an animation timeline is played during its playback.
        /// The default value is 1.
        static PropertyType<int> RepeatCountProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PlayMessageArguments, NodeComponentTargetMessageArguments, "Kanzi.AnimationPlayer.PlayMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(PlaybackModeProperty)
            KZ_METACLASS_PROPERTY_TYPE(DurationScaleProperty)
            KZ_METACLASS_PROPERTY_TYPE(RepeatCountProperty)
        KZ_METACLASS_END()

        /// Sets the value of the PlaybackModeProperty property.
        /// \param mode Playback mode.
        void setPlaybackMode(Timeline::DirectionBehavior direction)
        {
            KzuTimeLineEntryPlaybackMode playbackMode = convert(direction);
            setArgument(PlaybackModeProperty, static_cast<int>(playbackMode));
        }

        /// Gets the value of the PlaybackModeProperty property.
        /// \return Playback mode.
        Timeline::DirectionBehavior getPlaybackMode() const
        {
            KzuTimeLineEntryPlaybackMode playbackMode = static_cast<KzuTimeLineEntryPlaybackMode>(getArgument(PlaybackModeProperty));
            return convert(playbackMode);
        }

        /// Sets the value of the DurationScaleProperty property.
        /// \param durationScale Duration scale.
        void setDurationScale(float durationScale)
        {
            setArgument(DurationScaleProperty, durationScale);
        }

        /// Gets the value of the DurationScaleProperty property.
        /// \return Duration scale.
        float getDurationScale() const
        {
            return getArgument(DurationScaleProperty);
        }

        /// Sets the value of the RepeatCountProperty property.
        /// \param repeatCount Repeat count.
        void setRepeatCount(int repeatCount)
        {
            setArgument(RepeatCountProperty, repeatCount);
        }

        /// Gets the value of the RepeatCountProperty property.
        /// \return Repeat count.
        int getRepeatCount() const
        {
            return getArgument(RepeatCountProperty);
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Message arguments for Resume message.
    class KANZI_API ResumeMessageArguments : public NodeComponentTargetMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ResumeMessageArguments, NodeComponentTargetMessageArguments, "Kanzi.AnimationPlayer.ResumeMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for Pause message.
    class KANZI_API PauseMessageArguments : public NodeComponentTargetMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PauseMessageArguments, NodeComponentTargetMessageArguments, "Kanzi.AnimationPlayer.PauseMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for Stop message.
    class KANZI_API StopMessageArguments : public NodeComponentTargetMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StopMessageArguments, NodeComponentTargetMessageArguments, "Kanzi.AnimationPlayer.StopMessageArguments")
        KZ_METACLASS_END()
    };


    /// Message arguments for Started message.
    class KANZI_API StartedMessageArguments : public NodeComponentSourceMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StartedMessageArguments, NodeComponentSourceMessageArguments, "Kanzi.AnimationPlayer.StartedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for Stopped message.
    class KANZI_API StoppedMessageArguments : public NodeComponentSourceMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StoppedMessageArguments, NodeComponentSourceMessageArguments, "Kanzi.AnimationPlayer.StoppedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for Completed message.
    class KANZI_API CompletedMessageArguments : public NodeComponentSourceMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(CompletedMessageArguments, NodeComponentSourceMessageArguments, "Kanzi.AnimationPlayer.CompletedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Play message.
    /// When you send this message to a node to which an Animation Player is attached, that Animation Player starts to
    /// play the animation timeline set in its #TimelineProperty property. When you send the Play message to an Animation Player
    /// that is playing back an animation timeline, the Animation Player stops that playback and starts a new playback.
    static MessageType<PlayMessageArguments> PlayMessage;

    /// Resume message.
    /// When you send this message to the node to which an animation player is attached, the animation player starts to
    /// play the animation timeline set in its #TimelineProperty property. If the animation player has paused a playback, it
    /// resumes playing it.
    static MessageType<ResumeMessageArguments> ResumeMessage;

    /// Pause message.
    /// When you send this message to the node to which an animation player is attached, the animation player pauses the current
    /// playback. If the playback is paused of stopped, the animation player does nothing.
    static MessageType<PauseMessageArguments> PauseMessage;

    /// Stop message.
    /// When you send this message to the node to which an animation player is attached, the animation player stops the playback.
    /// The next #PlayMessage message starts to play the animation timeline from the beginning.
    static MessageType<StopMessageArguments> StopMessage;

    /// Started message.
    /// When the animation player starts the playback of its timeline, it dispatches the Started message.
    /// The animation player does not dispatch this message when it resumes playback after it was paused.
    /// After this message is sent the timeline is actively applied to animate the target properties.
    static MessageType<StartedMessageArguments> StartedMessage;

    /// Stopped message.
    /// When the animation player stops the playback of its timeline, it dispatches the Stopped message.
    /// After this message is sent the timeline is not applied to the target properties.
    static MessageType<StoppedMessageArguments> StoppedMessage;

    /// Completed message.
    /// When the animation player completes the playback of its timeline, it dispatches the Completed message.
    /// After this message is sent the timeline is still applied to the target properties.
    static MessageType<CompletedMessageArguments> CompletedMessage;

    KZ_METACLASS_BEGIN(AnimationPlayer, NodeComponent, "Kanzi.AnimationPlayer")
        KZ_METACLASS_PROPERTY_TYPE(TimelineProperty)
        KZ_METACLASS_PROPERTY_TYPE(AutoplayEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(RelativePlaybackProperty)
        KZ_METACLASS_PROPERTY_TYPE(RestoreOriginalValuesAfterPlaybackProperty)
        KZ_METACLASS_PROPERTY_TYPE(PlaybackModeProperty)
        KZ_METACLASS_PROPERTY_TYPE(DurationScaleProperty)
        KZ_METACLASS_PROPERTY_TYPE(RepeatCountProperty)

        KZ_METACLASS_MESSAGE_TYPE(PlayMessage)
        KZ_METACLASS_MESSAGE_TYPE(ResumeMessage)
        KZ_METACLASS_MESSAGE_TYPE(PauseMessage)
        KZ_METACLASS_MESSAGE_TYPE(StopMessage)
        KZ_METACLASS_MESSAGE_TYPE(StartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(StoppedMessage)
        KZ_METACLASS_MESSAGE_TYPE(CompletedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates animation player.
    /// \param domain Domain.
    /// \param name Name of animation player.
    /// \return animation player.
    static AnimationPlayerSharedPtr create(Domain* domain, string_view name)
    {
        return AnimationPlayerSharedPtr(new AnimationPlayer(domain, name));
    }

    /// Sets the #TimelineProperty property of an Animation Player to the animation timeline that you pass in this method.
    /// The Animation Player uses this timeline the next time it starts animation playback.
    /// \param animationTimeline The animation timeline that you want to set to the Animation Player.
    void setTimeline(TimelineSharedPtr animationTimeline);

    /// Gets the animation timeline from the #TimelineProperty property of an Animation Player.
    /// \return The animation timeline of the Animation Player. 
    TimelineSharedPtr getTimeline() const;

    /// Gets the timeline playback made for the timeline.
    /// \return %Timeline playback. The return value can be null.
    TimelinePlaybackSharedPtr getTimelinePlayback() const;

    /// Sets the value of the #AutoplayEnabledProperty property of an Animation Player.
    /// The Animation Player uses this value the next time you attach that Animation Player.
    /// \param enabled If the Animation Player starts playback of its animation timeline
    /// on attach automatically, true, otherwise false.
    void setAutoplayEnabled(bool enabled);

    /// Gets the value of the #AutoplayEnabledProperty property.
    /// \return If the Animation Player starts the playback of its animation timeline on attach
    /// automatically, true, otherwise false.
    bool isAutoplayEnabled() const;

    /// Sets the value of the #RelativePlaybackProperty property.
    /// \param relativePlayback Specifies whether playback is relative.
    void setRelativePlayback(bool relativePlayback);

    /// Gets the value of the #RelativePlaybackProperty property.
    /// \return If the playback is relative, true, otherwise false.
    bool isRelativePlayback() const;

    /// Sets the values of the #RestoreOriginalValuesAfterPlaybackProperty property.
    /// \param restore Specifies whether original values restored after playback finishes.
    void setRestoreOriginalValuesAfterPlayback(bool restore);

    /// Gets the values of the #RestoreOriginalValuesAfterPlaybackProperty property.
    /// \return If the original values are restored after playback finishes, true, otherwise false.
    bool isRestoreOriginalValuesAfterPlayback() const;

    /// Sets the value of the #PlaybackModeProperty property.
    /// \param mode Playback mode.
    void setPlaybackMode(Timeline::DirectionBehavior mode);

    /// Gets the value of the #PlaybackModeProperty property.
    /// \return Playback mode.
    Timeline::DirectionBehavior getPlaybackMode() const;

    /// Sets the value of the #DurationScaleProperty property.
    /// \param durationScale Duration scale.
    void setDurationScale(float durationScale);

    /// Gets the value of the #DurationScaleProperty property.
    /// \return Duration scale.
    float getDurationScale() const;

    /// Sets the value of the #RepeatCountProperty property.
    /// \param repeatCount Repeat count.
    void setRepeatCount(int repeatCount);

    /// Gets the value of the #RepeatCountProperty property.
    /// \return Repeat count.
    int getRepeatCount() const;

    /// Starts a new playback from the state of any animation player.
    /// Kanzi applies the parameters, which you pass to this function, as a whole on top of the property values that
    /// are set in the animation player. For example, if in the animation player the AnimationPlayer::PlaybackModeProperty
    /// property is set to Timeline::DirectionBehaviorNormal and the AnimationPlayer::RepeatCountProperty property is
    /// set to 2, and you call this function with the \p direction parameter set to Timeline::DirectionBehaviorPingPong,
    /// the animation player plays its timeline first twice normally and then twice in reverse.
    /// \param direction The playback mode that you want to apply on top of the value of the AnimationPlayer::PlaybackModeProperty property.
    /// \param durationScale The duration scale that you want to apply on top of the value of the AnimationPlayer::DurationScaleProperty property.
    /// \param repeatCount The repeat count that you want to apply on top of the value of the AnimationPlayer::RepeatCountProperty property.
    void start(Timeline::DirectionBehavior direction, float durationScale, unsigned int repeatCount);

    /// Resumes playing a paused timeline. If the playback is stopped, starts playing the timeline from the beginning.
    void resume();

    /// Pauses running playback. If the playback is already paused or stopped, does nothing.
    void pause();

    /// Stops running or paused playback. If the playback is already stopped, does nothing.
    /// To start a new playback after stopping the playback, call start() or resume(). 
    void stop();

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name The name of the animation player.
    explicit AnimationPlayer(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

    /// Message handler for the #PlayMessage message.
    /// \param messageArguments Arguments of Play message.
    void playMessageHandler(PlayMessageArguments& messageArguments);
    /// Message handler for the #ResumeMessage message.
    /// \param messageArguments Arguments of Resume message.
    void resumeMessageHandler(ResumeMessageArguments& messageArguments);
    /// Message handler for the #PauseMessage message.
    /// \param messageArguments Arguments of pause message.
    void pauseMessageHandler(PauseMessageArguments& messageArguments);
    /// Message handler for the #StopMessage message.
    /// \param messageArguments Arguments of Stop message.
    void stopMessageHandler(StopMessageArguments& messageArguments);

    /// Handler for finish timeline playback.
    /// \param timelinePlayback Finished playback.
    void onPlaybackFinished(TimelinePlayback& timelinePlayback);

private:

    /// Resumes current timeline playback of the animation player.
    /// If there is no playback, does nothing.
    void resumeTimelinePlayback();

    /// Pauses current timeline playback of the animation player.
    /// If there is no playback, does nothing.
    void pauseTimelinePlayback();

    /// Stops current timeline playback of the animation player.
    /// If there is no playback, does nothing.
    void stopTimelinePlayback();

    /// Removes the timeline playback from the root timeline clock.
    void removeTimelinePlaybackFromTimelineClock();

private:

    /// Timeline playback states.
    enum PlaybackState
    {
        /// Playback is active and is advanced by the clock.
        PlaybackStatePlaying,
        /// Playback is active, but is not advanced by the clock. 
        PlaybackStatePaused,
        /// Playback has completed and is still active.
        PlaybackStateCompleted,
        /// Playback is not active.
        PlaybackStateStopped
    };

    /// Root timeline where all playback options are set and where animation timeline is added.
    ParallelTimelineSharedPtr m_rootTimeline;

    /// State of playback.
    PlaybackState m_playbackState;
    /// Currently ongoing timeline playback of root timeline.
    TimelinePlaybackSharedPtr m_timelinePlayback;

    /// Subscription to Play message.
    Node::MessageSubscriptionToken m_playMessageSubscription;
    /// Subscription to Resume message.
    Node::MessageSubscriptionToken m_resumeMessageSubscription;
    /// Subscription to Pause message.
    Node::MessageSubscriptionToken m_pauseMessageSubscription;
    /// Subscription to Stop message.
    Node::MessageSubscriptionToken m_stopMessageSubscription;
};

}

#endif
