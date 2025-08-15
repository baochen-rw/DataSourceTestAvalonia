// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PREVIEW_TIMELINE_HPP
#define KZ_PREVIEW_TIMELINE_HPP


#include "timeline.hpp"


namespace kanzi
{

class PreviewTimeline;
typedef shared_ptr<PreviewTimeline> PreviewTimelineSharedPtr;

class PreviewTimelinePlayback;
typedef shared_ptr<PreviewTimelinePlayback> PreviewTimelinePlaybackSharedPtr;


/// Preview timeline,

class KANZI_API PreviewTimeline : public Timeline
{
public:

    /// Creates preview timeline.
    /// \param domain Domain.
    /// \return Preview timeline.
    static PreviewTimelineSharedPtr create(Domain* domain);

protected:

    /// Constructor.
    /// \param domain Domain.
    explicit PreviewTimeline(Domain* domain);

    /// Timeline::createPlaybackOverride() implementation.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// Timeline::calculateContentDuration() implementation.
    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;
};

}

#endif
