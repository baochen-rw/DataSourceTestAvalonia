// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_CLOCK_HPP
#define KZ_TIMELINE_CLOCK_HPP

#include "timeline_playback.hpp"

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core.ui/object/object.hpp>

#include <kanzi/core/legacy/time/kzs_tick_highresolution.hpp>

#include <iterator>

namespace kanzi
{

class TimelineClock;
typedef shared_ptr<TimelineClock> TimelineClockSharedPtr;


/// Updates timelines based on time.
class KANZI_API TimelineClock : public Object
{
public:

    typedef vector<TimelinePlaybackSharedPtr> TimelinePlaybackContainer;

    /// Constructor.
    virtual ~TimelineClock()
    {
    }

    /// Adds a timeline playback.
    /// New timeline playbacks are initially added to the list of new playbacks, from where they are moved to the list of existing playbacks.
    /// New playbacks are updated with a time delta of 0 when added. Existing playbacks are updated with full time delta during update.
    /// \param timelinePlayback Timeline playback to add.
    void addTimelinePlayback(TimelinePlaybackSharedPtr timelinePlayback)
    {
        m_newTimelinePlaybacks.push_back(timelinePlayback);

        // Activate with 0 delta
        timelinePlayback->tick(chrono::milliseconds::zero());

        // Increase count of ongoing playbacks if this playback is already ongoing after the initial tick.
        if (isTimelinePlaybackActive(*timelinePlayback))
        {
            ++m_activePlaybackCount;
        }
    }

    /// Removes a timeline playback.
    void removeTimelinePlayback(const TimelinePlayback& timelinePlayback)
    {
        if (removeTimelinePlaybackFromContainer(timelinePlayback, m_newTimelinePlaybacks))
        {
            return;
        }
        removeTimelinePlaybackFromContainer(timelinePlayback, m_timelinePlaybacks);
    }

    /// Tick all playbacks in the timeline clock.
    /// New timeline playbacks are only advanced with one frame time, since they are newly added and should not be ticked forward with
    /// possibly arbitrarily long delta time since last frame.
    /// \param delta Delta time  since last frame.
    void tick(chrono::milliseconds delta)
    {
        chrono::microseconds startTimestamp(kzsTimeGetCurrentTimeMicroseconds());
        size_t activePlaybackCount = 0;

        // Process old playbacks.
        for (size_t i = 0; i != m_timelinePlaybacks.size(); ++i)
        {
            // Keep the playback alive during the tick even if the playback removes itself.
            TimelinePlaybackSharedPtr playback = m_timelinePlaybacks[i];

            // Check if the playback was removed during the tick of an earlier playback.
            if (!playback)
            {
                continue;
            }

            playback->tick(delta);

            // Check if the playback was removed during its own the tick.
            if (!m_timelinePlaybacks[i])
            {
                continue;
            }

            kzAssert(playback == m_timelinePlaybacks[i]);

            // Increase count of ongoing playbacks if this playback is still ongoing after the tick.
            if (isTimelinePlaybackActive(*playback))
            {
                ++activePlaybackCount;
            }
            // Otherwise remove playback if it has stopped.
            else if (playback->getState() == TimelinePlayback::StateStopped)
            {
                m_timelinePlaybacks[i].reset();
            }
        }

        // Process new playbacks.
        for (size_t i = 0; i != m_newTimelinePlaybacks.size(); ++i)
        {
            // Playback may have been added and then removed during the same frame.
            TimelinePlayback* playback = m_newTimelinePlaybacks[i].get();
            if (!playback)
            {
                continue;
            }

            // Increase count of ongoing playbacks if this playback is ongoing.
            if (isTimelinePlaybackActive(*playback))
            {
                ++activePlaybackCount;
            }

            // If playback is not stopped, add it to ongoing timeline playbacks.
            if (playback->getState() != TimelinePlayback::StateStopped)
            {
                m_timelinePlaybacks.push_back(m_newTimelinePlaybacks[i]);
            }

            // Reset all processed new playbacks.
            // Note: This can cause addition of new playbacks.
            m_newTimelinePlaybacks[i].reset();
        }

        // Cleanup.
        erase(m_newTimelinePlaybacks, TimelinePlaybackSharedPtr());
        erase(m_timelinePlaybacks, TimelinePlaybackSharedPtr());

        // Update clock statistics.
        m_lastTickMeasurement = chrono::microseconds(kzsTimeGetCurrentTimeMicroseconds()) - startTimestamp;
        m_activePlaybackCount = activePlaybackCount;
    }

    /// Gets time spent on last tick operation.
    chrono::microseconds getLastTickMeasurement() const
    {
        return m_lastTickMeasurement;
    }

    /// Returns the number of active timeline playbacks.
    /// Number of active timeline playbacks may differ from total number of timeline playbacks if some playbacks are not active.
    /// \return Number of active timeline playbacks.
    size_t getActiveTimelinePlaybackCount() const
    {
        return m_activePlaybackCount;
    }
    /// Returns whether there are any active timeline playbacks present.
    /// Active playback is the playback which is not paused and not yet completed or stopped.
    /// \return True if at least one timeline playback is active, false otherwise.
    bool hasActiveTimelinePlaybacks() const
    {
        return (getActiveTimelinePlaybackCount() > 0);
    }

    /// Returns the number of timeline playbacks.
    /// This is the total number of playbacks, active or not.
    /// Timeline playbacks that have been added this frame are included.
    /// \return Number of timeline playbacks root timeline clock holds reference to.
    size_t getTimelinePlaybackCount() const
    {
        size_t timelinePlaybackCount = 0;

        // Need to iterate playbacks since there may be empty shared pointers.
        for (vector<TimelinePlaybackSharedPtr>::const_iterator it = cbegin(m_timelinePlaybacks), endIt = cend(m_timelinePlaybacks); it != endIt; ++it)
        {
            if (*it)
            {
                ++timelinePlaybackCount;
            }
        }
        for (vector<TimelinePlaybackSharedPtr>::const_iterator it = cbegin(m_newTimelinePlaybacks), endIt = cend(m_newTimelinePlaybacks); it != endIt; ++it)
        {
            if (*it)
            {
                ++timelinePlaybackCount;
            }
        }

        return timelinePlaybackCount;
    }

    static TimelineClockSharedPtr create(Domain* domain)
    {
        return make_polymorphic_shared_ptr<Object>(new TimelineClock(domain));
    }

protected:

    explicit TimelineClock(Domain* domain) :
        Object(domain),
        m_lastTickMeasurement(0),
        m_activePlaybackCount(0)
    {
    }

    /// Removes a timeline playback from a timeline playback container.
    /// \param timelinePlayback Timeline playback to remove.
    /// \param container Container to remove from.
    /// \return True if found and removed, false if not.
    bool removeTimelinePlaybackFromContainer(const TimelinePlayback& timelinePlayback, TimelinePlaybackContainer& container)
    {
        for (TimelinePlaybackContainer::iterator it = begin(container), endIt = end(container); it != endIt; ++it)
        {
            TimelinePlaybackSharedPtr& currentTimelinePlayback = *it;
            if (currentTimelinePlayback.get() == &timelinePlayback)
            {
                // Decrease count of ongoing playbacks if this playback is still active.
                if (isTimelinePlaybackActive(timelinePlayback))
                {
                    kzAssert(m_activePlaybackCount > 0);
                    --m_activePlaybackCount;
                }

                // Remove playback from the clock.
                currentTimelinePlayback.reset();
                return true;
            }
        }
        return false;
    }

    static bool isTimelinePlaybackActive(const TimelinePlayback& timelinePlayback)
    {
        const TimelinePlayback::State playbackState = timelinePlayback.getState();
        return ((playbackState == TimelinePlayback::StateNotStarted) ||
                (playbackState == TimelinePlayback::StateOngoing));
    }

private:

    /// Timeline playbacks added to the root timeline clock.
    TimelinePlaybackContainer m_timelinePlaybacks;

    /// Timeline playbacks added this frame, they will not be executed with full time delta this frame.
    TimelinePlaybackContainer m_newTimelinePlaybacks;

    /// Time spent on last tick operation.
    chrono::microseconds m_lastTickMeasurement;

    /// The number of active playbacks after the last tick.
    /// Active playback is the playback which is not paused and not yet completed or stopped.
    size_t m_activePlaybackCount;
};

}

#endif
