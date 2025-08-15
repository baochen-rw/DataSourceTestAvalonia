// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_PLAYBACK_HPP
#define KZ_TIMELINE_PLAYBACK_HPP


#include <kanzi/core.ui/animation/timeline.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/time/time_interval.hpp>


namespace kanzi
{

// Forward declarations.
class TimelinePlayback;

typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;


/// Playback object for Timelines. TimelinePlayback keeps track of how timeline is played.
///
/// To perform playback of Timeline, create a TimelinePlayback object by calling the Timeline::createPlayback()
/// function of Timeline. After that you add playback to a TimelineClock by calling its TimelineClock::addTimelinePlayback()
/// function. TimelineClock will advance the global time of TimelinePlayback object which in turn will advance Timeline.
///
/// Playback is associated with its timeline during its complete lifetime. It is possible to create multiple playbacks from
/// a single timeline. Each playback of timeline has its own track of how timeline is played at current point in time:
/// \snippet test_property_animation_timeline.cpp TimelinePlayback multiple playbacks
///
/// Once playback of timeline starts playing timeline, none of timeline properties should be changed.
///
/// \section TimelinePlaybackGlobalTime Global time
///
/// After TimelinePlayback is added to a clock, the clock applies it by periodically calling its tick() function. Delta time
/// argument of this function is interpreted by TimelinePlayback as change in its global time. Timeline start time and duration
/// are defined in global time space. Playback calculates all its parameters from global time: current iteration index,
/// progress time inside the iteration, whether it is applied and so on. Before playback is added to a clock, its global time
/// is undefined.
///
/// To manually set global time of TimelinePlayback call its setGlobalTime() function:
/// \snippet test_property_animation_timeline.cpp TimelinePlayback set global time
///
/// To retrieve global time of TimelinePlayback call its getGlobalTime() function:
/// \snippet test_property_animation_timeline.cpp TimelinePlayback get global time
///
/// Note that setting global time of TimelinePlayback which has parent TimelinePlayback can result in undefined behavior.
///
/// \section TimelinePlaybackProgressTime Progress time
///
/// When global time is changing, TimelinePlayback calculates progress time from it. Progress time is defined in Timeline's
/// progress time space and it is the time at which the progress of timeline is applied. TimelinePlayback notifies its
/// subclasses every time it calculates its progress time from global time. TimelinePlayback can notify its subclasses about
/// gradual change in progress time or about reset of progress time. When TimelinePlayback notifies its subclasses that progress
/// time has changed gradually, they advance their timelines gradually from previous progress time value to the new one. When
/// TimelinePlayback notifies its subclasses that progress time has been reset to a new value they reset their animations to
/// new progress time. Before playback is added to a clock, its progress time is undefined. After playback is added to a clock,
/// its progress time is always within timeline progress interval.
///
/// To retrieve the progress time of TimelinePlayback call its getProgressTime() function:
/// \snippet test_property_animation_timeline.cpp TimelinePlayback get progress time
///
/// \section TimelinePlaybackAppliedState Applied state
///
/// Depending on global time TimelinePlayback can decide whether its timeline should be applied or not. TimelinePlayback is not
/// applied (that is, its timeline is not applied) if its global time goes before timeline start time or if TimelinePlayback's parent
/// playback is not applied. In all other cases TimelinePlayback is applied, even if its global time advances past timeline duration
/// interval. When TimelinePlayback changes from applied to not applied (or the other way around) it notifies its subclasses so they
/// start or stop applying their Timelines. If TimelinePlayback with child TimelinePlaybacks changes its applied state, this change
/// propagates down the hierarchy of playbacks. For example, if parent TimelinePlayback becomes not applied, then its child playbacks
/// also become not applied even though they have their global times inside Timeline duration interval.
///
/// After the global time of TimelinePlayback has come to an end of its Timeline duration and it is still advancing beyond the end
/// of Timeline duration, then TimelinePlayback is still applied. In this case TimelinePlayback clamps the progress time of timeline
/// to the last valid value inside Timeline's progress interval and keeps applying the Timeline.
///
/// To retrieve the applied state of TimelinePlayback call its isApplied() function:
/// \snippet test_property_animation_timeline.cpp TimelinePlayback get applied state
///
/// \section TimelinePlaybackCompletion Completion
///
/// At some point every TimelinePlayback can become complete. Root TimelinePlayback becomes complete when its total time goes past
/// its timeline duration. In this case TimelinePlayback propagates completion down the tree of child playbacks so each of them can
/// notify that it is complete. It means that child TimelinePlayback is complete only when its root playback is complete. However,
/// even though TimelinePlayback has notified about its completion, it continues to apply its Timeline. TimelinePlayback stops
/// applying its timeline only after it is destroyed.


class KANZI_API TimelinePlayback : public Object
{
public:

    /// Callback for complete timeline.
    typedef function<void(TimelinePlayback&)> CompleteCallback;

    /// Status of the playback.
    enum State
    {
        /// Playback has not started: playback's global time goes before the Timeline's start time.
        StateNotStarted,
        /// Playback is progressing: playback's global time is within Timeline duration interval.
        StateOngoing,
        /// Whole timeline has completed: playback's global time goes after Timeline's end.
        StateCompleted,
        /// Playback of timeline has stopped. Stopped playback could not be resumed.
        StateStopped
    };

public:

    /// Constructor.
    /// \param domain Domain.
    /// \param timeline Timeline to perform playback on.
    explicit TimelinePlayback(Domain* domain, TimelineSharedPtr timeline);

    /// Destructor.
    virtual ~TimelinePlayback();

    /// Sets parent playback. This function should only be called
    /// before this playback or parent playback are added to the clock.
    /// \param playback Parent playback.
    void setParent(TimelinePlayback* playback);

    /// Sets complete callback.
    /// \param callback which is called when playback is \ref TimelinePlaybackCompletion "complete".
    void setCompleteCallback(CompleteCallback callback);

    /// Gets current state of playback.
    /// \return Playback status.
    State getState() const;

    /// Advances TimelinePlayback's \ref TimelinePlaybackGlobalTime "global time" by delta time and calculates new
    /// \ref TimelinePlaybackProgressTime "progress time" from it as well as other parameters such as current iteration index,
    /// etc. During the call to this function TimelinePlayback can call its tickOverride() and onProgressTimeResetOverride()
    /// functions multiple times. Also TimelinePlayback can become \ref TimelinePlaybackCompletion "complete" during the call
    /// to this function (and onPlaybackCompletedOverride() function called) or its \ref TimelinePlaybackAppliedState "applied"
    /// state can change (and onAppliedStateChangedOverride() function called).
    /// \param deltaTime Delta time of Playback's global time since last tick.
    void tick(chrono::milliseconds deltaTime);

    /// Gets current \ref TimelinePlaybackGlobalTime "global time" of TimelinePlayback.
    /// \return Global time of playback.
    chrono::milliseconds getGlobalTime() const;

    /// Sets \ref TimelinePlaybackGlobalTime "global time" of playback and calculates new \ref TimelinePlaybackProgressTime
    /// "global time" from it as well as other parameters such as current iteration index, etc. During the call to this
    /// function Playback will call its onProgressTimeResetOverride() function. Also Playback can become complete during
    /// the call to this function (and onPlaybackCompletedOverride() function called) or its applied state can change
    /// (and onAppliedStateChangedOverride() function called).
    /// \param time Global time of playback.
    void setGlobalTime(chrono::milliseconds time);

    /// Gets current \ref TimelinePlaybackProgressTime "progress time" of TimelinePlayback.
    /// \return Progress time.
    chrono::milliseconds getProgressTime() const;

    /// Indicates whether TimelinePlayback is \ref TimelinePlaybackAppliedState "applied".
    /// \return true if TimelinePlayback is applied, false otherwise.
    bool isApplied() const;

    /// Notifies TimelinePlayback whether the applied state of its parent playback has changed.
    /// This function should only be called by parent playback.
    void onParentAppliedStateChanged();

    /// Notifies TimelinePlayback whether its parent playback has completed.
    /// This function should only be called by parent playback.
    void onParentCompleted();

    /// Stops playback. Stopped playback does not animate any properties and subsequent calls to its tick() and
    /// setGlobalTime() methods does not have any effect. Once playback has stopped, it is not possible to resume
    /// it again. It is allowed to stop playback by calling this method in completion callback of playback.
    /// Global time and local time of stopped playback are undefined.
    void stop();

protected:

    /// TimelinePlayback calls this function after its \ref TimelinePlaybackProgressTime "progress time" has
    /// gradually changed from its old value to new one. Subclasses of Playback should gradually advance their
    /// animations from old progress time to new one during call to this function.
    /// \param deltaTime Delta time. It can be positive as well as negative.
    virtual void tickOverride(chrono::milliseconds deltaTime) = 0;

    /// TimelinePlayback calls this function after its \ref TimelinePlaybackProgressTime "progress time" has
    /// been reset to a new value. Subclasses of TimelinePlayback should reset their animations to new time
    /// during call to this function; it is not necessary to gradually advance animations from old progress time
    /// to new one. This function does nothing by default.
    virtual void onProgressTimeResetOverride();

    /// TimelinePlayback calls this function after its \ref TimelinePlaybackAppliedState "applied" state has changed.
    /// Subclasses of TimelinePlayback should stop applying their animations on target properties if TimelinePlayback
    /// has become not applied or start applying animations if TimelinePlayback has become applied. This function does
    /// nothing by default.
    virtual void onAppliedStateChangedOverride();

    /// TimelinePlayback calls this function after it has become \ref TimelinePlaybackCompletion "complete".
    /// This function does nothing by default.
    virtual void onPlaybackCompletedOverride();

    /// Calls completion callback if it is available.
    void notifyPlaybackCompleted();

private:

    /// Direction of timeline iteration.
    enum Direction
    {
        /// Forward direction.
        DirectionForward,

        /// Backwards direction.
        DirectionBackwards
    };

private:

    /// Get opposite direction.
    /// \param direction Direction.
    /// \return Opposite direction.
    static Direction getOpposite(Direction direction);

    /// Returns direction sign.
    /// \param direction Direction.
    /// \return 1 is direction is Positive, -1 if direction is negative.
    static int getSign(Direction direction);

    /// Converts global time to timeline time and returns it.
    /// \param globalTime Global time.
    /// \return Timeline time.
    chrono::milliseconds globalTimeToTimelineTime(chrono::milliseconds globalTime) const;

    /// Converts timeline time to global time and returns it.
    /// \param timelineTime Timeline time.
    /// \return Global time.
    chrono::milliseconds timelineTimeToGlobalTime(chrono::milliseconds timelineTime) const;

    /// Converts iteration time to progress time and returns it.
    /// \param iterationTime Time of iteration.
    /// \param iterationDirection Direction of iteration.
    /// \return Progress time.
    chrono::milliseconds iterationTimeToProgressTime(chrono::milliseconds iterationTime, Direction iterationDirection) const;

    /// Updates playback state (determine playback status, determine if playback is applied, etc).
    /// State is updated based on playback's current global time.
    void updatePlaybackState();

    /// Updates playback applied state.
    void updateAppliedState();

    /// Completes the playback.
    void onPlaybackCompleted();

private:

    // Timeline on which playback is operating.
    // TODO: get rid of double storage of timeline here and in derived classes. crtp?
    TimelineSharedPtr m_timeline;

    // Parent playback.
    TimelinePlayback* m_parentPlayback;

    /// State of playback.
    State m_state;
    /// Indicates whether playback applies its timeline.
    /// Playback is applied if it has started and its parent playback is also applied.
    bool m_applied;

    /// Callback which is invoked when playback is complete.
    CompleteCallback m_completeCallback;

    // Global time of animation timeline.
    chrono::milliseconds m_globalTime;
    // Indicates if global time is set at least once.
    bool m_globalTimeSet;

    // Direction behavior. The behavior is typically taken from timeline,
    // but in certain cases can be different from direction behavior of timeline.
    Timeline::DirectionBehavior m_directionBehavior;

    // Duration of timeline. The duration is defined as iteration duration multiplies by
    // iteration count. If either iteration duration or count is infinite, then
    // timeline duration is also infinite (nullopt).
    optional<chrono::milliseconds> m_timelineDuration;

    // Total number of iterations in timeline. Zero value specifies infinite number of iterations.
    unsigned int m_iterationCount;
    // Duration of a single iteration. Null optional specifies infinite iteration duration.
    optional<chrono::milliseconds> m_iterationDuration;
    // Index of currently ongoing iteration.
    unsigned int m_iterationIndex;
    // Playback direction in currently ongoing iteration.
    Direction m_iterationDirection;
    // Time in currently ongoing iteration.
    chrono::milliseconds m_iterationTime;

    // Interval which defines starting and ending time value in timeline content
    // which is played during single iteration.
    TimeInterval m_clipInterval;
    // Current playback time in timeline content.
    chrono::milliseconds m_progressTime;
};

}

#endif
