// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_RESOURCE_HPP
#define KZ_TIMELINE_RESOURCE_HPP


#include "timeline.hpp"

#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/node/abstract_resource_reference.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/resource/resource.hpp>


namespace kanzi
{

// Forward declaration.
class ReadOnlyMemoryFile;

/// A Resource wrapper class for animation timelines.
class TimelineResource;
typedef shared_ptr<TimelineResource> TimelineResourceSharedPtr;

class KANZI_API TimelineResource : public Resource
{
public:

    KZ_METACLASS_BEGIN(TimelineResource, Resource, "Kanzi.Animation.TimelineResource")
    KZ_METACLASS_END()

    /// Creates a new empty timeline resource instance. The timeline can be initialized using loadFromKZB function.
    static TimelineResourceSharedPtr create(Domain* domain, string_view name);

    /// Creates a new timeline resource wrapping the given timeline.
    static TimelineResourceSharedPtr create(Domain* domain, string_view name, TimelineSharedPtr timeline);

    /// Gets the timeline of the timeline resource.
    TimelineSharedPtr getTimeline() const;

    /// Loads the timeline from the given KZB stream/file.
    void loadFromKZBWithoutContext(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

    /// Loads timeline from KZB file.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load timeline data from.
    /// \param parser Parser to parse timeline data.
    /// \return Loaded timeline resource.
    static TimelineResourceSharedPtr loadFromKZB(Domain*domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

private:
    TimelineResource(Domain* domain, string_view name);

    // Actual animation timeline.
    TimelineSharedPtr m_timeline;
};

}


#endif
