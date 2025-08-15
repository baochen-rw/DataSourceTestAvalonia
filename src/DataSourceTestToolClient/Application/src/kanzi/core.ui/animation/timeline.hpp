// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_HPP
#define KZ_TIMELINE_HPP


#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/time/time_interval.hpp>


namespace kanzi
{

class Timeline;
typedef shared_ptr<Timeline> TimelineSharedPtr;

class TimelinePlayback;
typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;

class TimelinePlaybackContext;

class KzbFile;
class KzbMemoryParser;

/// The Kanzi animation system consists of animations and timelines: animations define how the values of specific type
/// change in time, and timelines map the animations to properties of objects you want to animate.
///
/// The Timeline class defines common properties which specify how the playback of a timeline is performed. These 
/// properties include timeline \ref TimelineStartTime "start time", content \ref TimelineClipStartTimeClipDuration
/// "clip start time and clip duration", \ref TimelineRepeatCount "repeat count" and so on. Actual classes inherited from
/// the Timeline class define how animations are applied to the properties of objects. For an example of actual classes 
/// see PropertyAnimationTimeline, PropertyFieldAnimationTimeline or ParallelTimeline.
///
/// Timeline is a series of iterations played successively starting from specified start time. Each iteration is
/// a continuous portion of timeline content which is played in a specific manner. Timeline content can be a single
/// animation (as in PropertyAnimationTimeline), several animations which are animating fields of a single property
/// (as in PropertyFieldAnimationTimeline) or even other timelines (as in ParallelTimeline).
///
/// \section TimelineStartTime Start time
///
/// To specify the time at which the first iteration of a timeline starts to play, set the start time property of the
/// timeline. Start time is defined in the time space of the clock where the playback of this timeline is added or in the
/// time space of its parent playback. Start time can be positive or negative. Negative start time causes the timeline to
/// act like it started at some time in the past. It can cause the timeline to start as if it was half-way finished.
/// The default value for start time is 0 milliseconds.
///
/// To set the start time of Timeline call its setStartTime() function:
/// \snippet test_animation.cpp Timeline set start time
///
/// To retrieve the start time of Timeline call its getStartTime() function.
/// \snippet test_animation.cpp Timeline get start time
///
/// \section TimelineClipStartTimeClipDuration Clip start time and clip duration
///
/// To specify the portion of timeline content played in an iteration set the clip start time and clip duration
/// properties of the timeline. Clip start time and clip duration are defined in the time space of the timeline content.
/// By default, the whole timeline content is played in a single iteration.
///
/// To set the clip start time and clip duration of Timeline call its setClipStartTime() and setClipDuration()
/// functions:
/// \snippet test_animation.cpp Timeline set clip start time and clip duration
///
/// To retrieve the clip start time and clip duration of Timeline call its getClipStartTime() and getClipDuration()
/// functions. Note that getClipDuration() can return empty optional, meaning that clip duration is not specified.
/// \snippet test_animation.cpp Timeline get clip start time and clip duration
///
/// \section TimelineDurationScale Duration scale
///
/// To scale the portion of timeline content played in an iteration up or down, set the duration scale property of the timeline.
/// By default, the value of duration scale is 1 which means that timeline content is not scaled. If duration scale is larger than 1,
/// timeline content is scaled up when it is played in an iteration. For example, if you set duration scale to 2, timeline
/// content is played at half speed and the duration of the iteration is twice as long as normally. If duration scale is less
/// than 1, timeline content is scaled down when it is played. For example, if you set duration scale to 0.5, timeline content
/// is played twice as fast as normally and iteration duration is half of the normal. Timeline duration scale
/// cannot be negative or zero. If you set the duration scale to such a value, the timeline will clamp it to the minimum allowed
/// scale value. Timeline duration scale does not affect the start time of the timeline.
///
/// To set the duration scale of Timeline call its setDurationScale() function:
/// \snippet test_animation.cpp Timeline set duration scale
///
/// To retrieve the duration scale of Timeline call its getDurationScale() function.
/// \snippet test_animation.cpp Timeline get duration scale
///
/// \section TimelineDirectionBehavior Direction behavior
///
/// Timeline content in an iteration can be played in either normal or reverse direction. By default (or if you set the
/// direction behavior property of the timeline to Timeline::DirectionBehaviorNormal) the content is played in normal
/// direction. If you set the direction behavior property of the timeline to Timeline::DirectionBehaviorReverse,
/// each iteration plays its portion of timeline content in reverse manner, that is, from the end to the beginning
/// of the content portion. If you set direction behavior to Timeline::DirectionBehaviorPingPong, then each
/// odd iteration plays its content normally and each even iteration plays its content in reverse manner.
///
/// To set the direction behavior of Timeline to one of the values from Timeline::DirectionBehavior call Timeline's
/// setDirectionBehavior() function:
/// \snippet test_animation.cpp Timeline set direction behavior
///
/// To retrieve the direction behavior of Timeline call its getDirectionBehavior() function.
/// \snippet test_animation.cpp Timeline get direction behavior
///
/// \section TimelineRepeatCount Repeat count
///
/// The number of iterations in a timeline is affected by several properties of the timeline. In general, to define
/// how many iterations should be played in a timeline set its repeat count property. But if the direction behavior
/// of the timeline is set to Timeline::DirectionBehaviorPingPong, then each iteration has two sub-iterations 
/// (the first sub-iteration plays its portion of the timeline content in normal direction and the second one plays 
/// it in reverse direction), so the number of iterations defined by repeat count is doubled. 
/// For example, if you set repeat count to 10 and direction behavior to Timeline::DirectionBehaviorPingPong, the 
/// number of iterations in the timeline becomes 20. If you set repeat count to 0, the number of iterations in timeline 
/// becomes infinite.
///
/// To set the repeat count of Timeline call its setRepeatCount() function:
/// \snippet test_animation.cpp Timeline set repeat count
///
/// To retrieve the repeat count of Timeline call its getRepeatCount() function.
/// \snippet test_animation.cpp Timeline get repeat count
///
/// \section TimelinePlayback Timeline playback
///
/// To perform playback of Timeline, create a TimelinePlayback object by calling the createPlayback() function
/// of Timeline. After that you add playback to a TimelineClock by calling its TimelineClock::addTimelinePlayback()
/// function. TimelineClock will advance the global time of the TimelinePlayback object which in turn will advance Timeline.
///
/// To start the playback of Timeline:
/// \snippet test_animation.cpp Timeline start playback
///
/// Do not change the properties of a timeline after you have added its playback to a clock.
/// Changing any timeline property after its playback is added to a clock will result in undefined behavior.
///
/// \see ParallelTimeline
/// \see PropertyAnimationTimeline
/// \see PropertyFieldAnimationTimeline
/// \see TimelinePlayback
/// \see TimelineClock
///


class KANZI_API Timeline : public Object, public enable_shared_from_this<Timeline>
{
    friend class TimelinePlayback;

public:

    /// Specifies the direction behavior for a timeline.
    enum DirectionBehavior
    {
        /// Normal forward direction behavior.
        DirectionBehaviorNormal,

        /// Reverse direction behavior. Animation starts from the end and progresses backwards. Not supported if duration is infinite.
        DirectionBehaviorReverse,

        /// Animation first progresses forward, bounces from the end and then progresses backwards back to the beginning.
        DirectionBehaviorPingPong
    };

public:

    KZ_ABSTRACT_METACLASS_BEGIN(Timeline, Object, "Kanzi.Animation.Timeline")
    KZ_METACLASS_END()

    /// Gets the \ref TimelineStartTime "start time" of the timeline (in milliseconds).
    /// \return Start time of timeline.
    chrono::milliseconds getStartTime() const;

    /// Gets the \ref TimelineStartTime "start time" of the timeline (in milliseconds).
    /// \param startTime Start time of timeline.
    void setStartTime(chrono::milliseconds startTime);

    /// Gets the \ref TimelineClipStartTimeClipDuration "clip start time" of the timeline (in milliseconds).
    /// \return Clip start time of timeline.
    chrono::milliseconds getClipStartTime() const;

    /// Sets the \ref TimelineClipStartTimeClipDuration "clip start time" of the timeline (in milliseconds).
    /// \param clipStartTime Clip start time of timeline.
    void setClipStartTime(chrono::milliseconds clipStartTime);

    /// Gets the \ref TimelineClipStartTimeClipDuration "clip duration" of the timeline (in milliseconds).
    /// \return Clip duration of timeline.
    optional<chrono::milliseconds> getClipDuration() const;

    /// Sets the \ref TimelineClipStartTimeClipDuration "clip duration" of the timeline (in milliseconds).
    /// \param duration Clip duration of timeline.
    void setClipDuration(optional<chrono::milliseconds> duration);

    /// Gets the \ref TimelineRepeatCount "repeat count" of the timeline (zero indicates infinite repeats).
    /// \return Repeat count of timeline.
    unsigned int getRepeatCount() const;

    /// Sets the \ref TimelineRepeatCount "repeat count" of the timeline (zero indicates infinite repeats).
    /// \param repeatCount Repeat count of timeline.
    void setRepeatCount(unsigned int repeatCount);

    /// Gets the \ref TimelineDirectionBehavior "direction behavior" of a timeline.
    /// \return direction behavior of timeline.
    DirectionBehavior getDirectionBehavior() const;

    /// Sets the \ref TimelineDirectionBehavior "direction behavior" of a timeline.
    /// \param directionBehavior Direction behavior of timeline.
    void setDirectionBehavior(DirectionBehavior directionBehavior);

    /// Gets the \ref TimelineDurationScale "duration scale" of timeline.
    /// \return Duration scale of timeline.
    float getDurationScale() const;

    /// Sets the \ref TimelineDurationScale "duration scale" of timeline. If specified scale
    /// is smaller than minimum scale, the scale is clamped to minimum scale value.
    /// \param scale Duration scale of timeline.
    void setDurationScale(float scale);

    /// Gets minimum \ref TimelineDurationScale "duration scale".
    /// \return Minimum duration scale.
    float getMinimumDurationScale() const;

    /// Calculates clip interval of timeline. This content interval will be
    /// played by each iteration of timeline during its playback.
    /// Clip interval is calculated by applying \ref TimelineClipStartTimeClipDuration
    /// "clip start time and clip duration" to content duration of timeline.
    /// \return Content interval.
    TimeInterval calculateClipInterval();

    /// Calculates number of iterations in timeline.
    /// Number of iteration is calculated from \ref TimelineRepeatCount "repeat count" of timeline
    /// and its \ref TimelineDirectionBehavior "direction behavior".
    /// \return Number of iterations.
    unsigned int calculateIterationCount();

    /// Calculates iteration duration.
    /// Iteration duration is calculated by applying \ref TimelineDurationScale "duration scale"
    /// to duration of \ref TimelineClipStartTimeClipDuration "clipped content interval".
    /// \return Number of iterations.
    optional<chrono::milliseconds> calculateIterationDuration();

    /// Calculates the duration of the timeline.
    /// Timeline duration calculated as a iteration duration multiplied by iteration count.
    /// Timeline \ref TimelineStartTime "start time" does not affect timeline duration.
    /// Returns nullopt if the duration of timeline is infinite.
    /// \return Duration of timeline.
    optional<chrono::milliseconds> calculateDuration();

    /// Creates \ref TimelinePlayback "playback" for timeline.
    /// \param context Context for playback.
    /// \return Timeline playback object.
    TimelinePlaybackSharedPtr createPlayback(TimelinePlaybackContext& context);

protected:

    /// Constructor.
    /// \param domain Domain.
    explicit Timeline(Domain* domain);

    /// Creates playback of the timeline.
    /// \param context Context for playback.
    /// \return Playback of the timeline.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) = 0;

    /// Calculates the duration of the content of the timeline. No timeline playback
    /// properties (e.g. start time, clip start time and duration, repeat count, etc)
    /// should be used when calculating content duration. By default content duration
    /// of timeline is zero milliseconds (empty timeline).
    /// \return Duration of timeline content.
    virtual optional<chrono::milliseconds> calculateContentDuration();

    /// Loads timeline data from KZB.
    /// Subclasses of Timeline class can override this function to load type-specific timeline data. In this
    /// case override function should call loadOverride() of Timeline class before loading type-specific data.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load timeline data from.
    /// \param parser Parser to parse timeline data.
    virtual void loadOverride(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

private:

    /// Start time.
    chrono::milliseconds m_startTime;

    /// Clip start time.
    chrono::milliseconds m_clipStartTime;
    /// Clip duration.
    optional<chrono::milliseconds> m_clipDuration;

    /// Repeat count.
    unsigned int m_repeatCount;

    /// Direction behavior.
    DirectionBehavior m_directionBehavior;

    /// Duration scale.
    float m_durationScale;
};

}

#endif