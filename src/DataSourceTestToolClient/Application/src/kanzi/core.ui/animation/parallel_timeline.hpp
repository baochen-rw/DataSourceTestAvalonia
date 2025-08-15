// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PARALLEL_TIMELINE_HPP
#define KZ_PARALLEL_TIMELINE_HPP


#include "timeline.hpp"

#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

class ParallelTimeline;
typedef shared_ptr<ParallelTimeline> ParallelTimelineSharedPtr;


/// The Kanzi animation system consists of animations and timelines: animations define how to animate a property,
/// and timelines map the animations to time and to objects you want to animate.
///
/// Parallel timeline allows you to group timelines which Kanzi plays at the same time. Use this timeline
/// to organize collections of timelines and create a composition of timelines.
///
/// To add child timelines to parallel timeline call the addChild() function of parallel timeline. To adjust
/// the position of a child timeline inside parallel timeline set the start time of the child timeline. Start
/// time of child timeline as well as its global time is defined in content time space of parallel timeline.
/// It is possible to set negative start time to child timeline. In this case the portion of timeline which
/// is going before the zero time is clipped and will not be played.
///
/// It is not allowed to add child timelines after any playback of parallel timeline is added to a clock.
/// Doing so will result in undefined behavior.
///
/// Since the content of parallel timeline is a group of its child timelines, the content duration of parallel
/// timeline is defined as union of timeline durations of child timelines affected by their start times.
/// For example, if a single timeline with a duration of 10 milliseconds and a start time of 5 milliseconds
/// is added as a child to a parallel timeline, then the content duration of the parallel timeline is 15 milliseconds.
/// Parallel timeline has its content duration set to 0 milliseconds if no child timelines were added to it.
///
/// Timeline properties affecting playback such as start time, repeat count, duration scale factor, direction
/// behavior, clip start and clip duration, which are specified in parallel timeline, affect its child
/// timelines. For example, if direction behavior of parallel timeline is set to reverse, then all its child
/// timelines are played in reverse manner, from the end to beginning. In this case the time for child timelines
/// will appear as going backwards.
///
/// Examples
/// ----
///
/// To create a parallel timeline:
/// \snippet test_animation.cpp Create parallel timeline
///
/// To play an animation regardless of the timeline type:
/// \snippet test_animation.cpp Play animation


class KANZI_API ParallelTimeline : public Timeline
{
    friend class ParallelTimelinePlayback;
    typedef vector<TimelineSharedPtr> ChildContainer;

public:

    KZ_METACLASS_BEGIN(ParallelTimeline, Timeline, "Kanzi.Animation.ParallelTimeline")
    KZ_METACLASS_END()

    static TimelineSharedPtr create(Domain* domain, string_view /*name*/)
    {
        return make_polymorphic_shared_ptr<Timeline>(new ParallelTimeline(domain));
    }

    typedef ChildContainer::const_iterator ChildConstIterator;

    /// Adds child timeline to the parallel timeline.
    /// This function should not be called after playback of the
    /// parallel timeline has been added to a timeline clock.
    /// \param childTimeline Timeline to add to the parallel timeline.
    void addChild(TimelineSharedPtr childTimeline);

    /// Creates parallel timeline.
    /// \param domain Domain.
    /// \return Parallel timeline.
    static ParallelTimelineSharedPtr create(Domain* domain);

    size_t getChildCount() const
    {
        return m_children.size();
    }

    ChildConstIterator beginChildren() const
    {
        return cbegin(m_children);
    }

    ChildConstIterator endChildren() const
    {
        return cend(m_children);
    }

    string_view getObjectPath() const
    {
        return m_objectPath;
    }

    /// Loads timeline from KZB file.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load timeline data from.
    /// \param parser Parser to parse timeline data.
    /// \return Loaded timeline.
    static ObjectSharedPtr load(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

protected:

    /// Constructor.
    /// \param domain Domain.
    explicit ParallelTimeline(Domain* domain);

    /// Timeline::createPlaybackOverride() implementation.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// Timeline::calculateContentDuration() implementation.
    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;

    /// Timeline::loadOverride() implementation.
    virtual void loadOverride(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

private:

    string m_objectPath;
    ChildContainer m_children;
};

}

#endif
