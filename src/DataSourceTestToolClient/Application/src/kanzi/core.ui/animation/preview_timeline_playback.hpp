// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PREVIEW_TIMELINE_PLAYBACK_HPP
#define KZ_PREVIEW_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"

namespace kanzi
{

class PreviewTimeline;
typedef shared_ptr<PreviewTimeline> PreviewTimelineSharedPtr;

class PreviewTimelinePlayback;
typedef shared_ptr<PreviewTimelinePlayback> PreviewTimelinePlaybackSharedPtr;

/// Preview timeline playback controls child timeline playbacks based on preview instructions.
class KANZI_API PreviewTimelinePlayback : public TimelinePlayback
{
public:

    /// Creates preview timeline playback.
    /// \param previewTimeline Preview timeline to create playback for.
    static PreviewTimelinePlaybackSharedPtr create(PreviewTimelineSharedPtr previewTimeline);

    /// Adds timeline playback to preview timeline playback.
    /// \param timelinePlayback Timeline playback to add.
    void addTimelinePlayback(TimelinePlaybackSharedPtr timelinePlayback);
    
    /// Removes timeline playback from preview timeline playback.
    /// \param timelinePlayback Timeline playback to remove.
    void removeTimelinePlayback(TimelinePlayback& timelinePlayback);

    /// Turns on scrubbing. When scrubbing is turned on, the preview timeline playback
    /// does not tick timeline playbacks added to it. The time of timeline playbacks is
    /// modified when global time of preview timeline playback is adjusted.
    void enableScrubbing();

    /// Disables scrubbing.
    void disableScrubbing();

protected:
    /// Constructor.
    /// \param previewTimeline Preview timeline to create playback for.
    explicit PreviewTimelinePlayback(PreviewTimelineSharedPtr previewTimeline);

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

    /// Erases timeline playbacks that have been completed or stopped.
    void eraseCompletedTimelinePlaybacks();

private:

    /// Entry for child timeline playback which keeps track at which
    /// moment of time (global time of the preview timeline playback)
    /// child playback was added.
    struct TimelinePlaybackEntry
    {
        /// Constructor.
        /// \param startTime Time at which the timeline playback was added to preview timeline playback.
        /// \param timelinePlayback Timeline playback.
        TimelinePlaybackEntry(chrono::milliseconds startTime, TimelinePlaybackSharedPtr timelinePlayback) :
            startTime(startTime), timelinePlayback(timelinePlayback)
        {
        }

        /// Time at which the timeline playback was added to preview timeline playback.
        chrono::milliseconds startTime;
        /// Timeline playback.
        TimelinePlaybackSharedPtr timelinePlayback;
    };

    /// Determines whether the timeline playback in the entry did not complete yet.
    /// \param entry The entry playback of which should be examined.
    /// \return True is playback in the entry has completed, false otherwise.
    static bool isCompletedTimelinePlayback(const TimelinePlaybackEntry& entry);

    typedef vector<TimelinePlaybackEntry> TimelinePlaybackEntryContainer;
    typedef TimelinePlaybackEntryContainer::iterator TimelinePlaybackEntryIterator;
    typedef TimelinePlaybackEntryContainer::const_iterator TimelinePlaybackEntryConstIterator;

    /// Timeline playbacks added to preview timeline playback.
    TimelinePlaybackEntryContainer m_timelinePlaybackEntries;

    /// Scrubbed time.
    chrono::milliseconds m_scrubbedTime;

    /// Flag telling if scrubbing is enabled.
    bool m_isScrubbing;
};

}

#endif