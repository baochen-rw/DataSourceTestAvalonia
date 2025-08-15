// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_FIELD_ANIMATION_TIMELINE_HPP
#define KZ_PROPERTY_FIELD_ANIMATION_TIMELINE_HPP


#include "timeline.hpp"
#include "value_animation.hpp"

namespace kanzi
{

class PropertyFieldAnimationTimeline;

typedef shared_ptr<PropertyFieldAnimationTimeline> PropertyFieldAnimationTimelineSharedPtr;
class PropertyFieldAnimationTimelinePlayback;


/// The Kanzi animation system consists animations and timelines: animations define how to animate a property,
/// and timelines map the animations to time and to objects you want to animate.
///
/// Property field timeline applies an animation to one or more fields of a property of an object. For example,
/// you can use a separate animation for each color channel to change the color of the text in a Text Block node,
/// or use two different animations to scale a node along x and y axes.
///
/// Examples
/// ----
///
/// To create a property field timeline:
/// \snippet test_animation.cpp Create property field timeline
///
/// To play an animation regardless of the timeline type:
/// \snippet test_animation.cpp Play animation


class KANZI_API PropertyFieldAnimationTimeline : public Timeline
{
    friend class PropertyFieldAnimationTimelinePlayback;

public:

    KZ_METACLASS_BEGIN(PropertyFieldAnimationTimeline, Timeline, "Kanzi.Animation.PropertyFieldAnimationTimeline")
    KZ_METACLASS_END()

    static TimelineSharedPtr create(Domain* domain, string_view /*name*/)
    {
        return make_polymorphic_shared_ptr<Timeline>(new PropertyFieldAnimationTimeline(domain));
    }

    struct Entry
    {
        PropertyField field;
        FloatAnimationSharedPtr animation;
    };

    typedef vector<Entry> EntryContainer;
    typedef EntryContainer::const_iterator EntryConstIterator;

    void addEntry(PropertyField field, FloatAnimationSharedPtr animation)
    {
        Entry entry = { field, animation };

        m_entries.push_back(entry);
    }

    static PropertyFieldAnimationTimelineSharedPtr create(Domain* domain, string_view objectPath, AbstractPropertyType propertyType)
    {
        PropertyDataType dataType = propertyType.getDataType();
        if (dataType != PropertyDataTypeColor &&
            dataType != PropertyDataTypeVector2 &&
            dataType != PropertyDataTypeVector3 &&
            dataType != PropertyDataTypeVector4 &&
            dataType != PropertyDataTypeSRT2D &&
            dataType != PropertyDataTypeSRT3D)
        {
            kzThrowException(invalid_argument("Unsupported property data type in PropertyFieldAnimationTimeline."));
        }

        return make_polymorphic_shared_ptr<Timeline>(new PropertyFieldAnimationTimeline(domain, objectPath, propertyType));
    }

    /// Gets the property type associated with the timeline.
    AbstractPropertyType getPropertyType() const
    {
        return m_propertyType;
    }

    /// Gets the animation collection associated with the timeline.
    EntryContainer getAnimations() const
    {
        return m_entries;
    }

    EntryConstIterator beginEntries() const
    {
        return cbegin(m_entries);
    }

    EntryConstIterator endEntries() const
    {
        return cend(m_entries);
    }

    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;

    /// Loads timeline from KZB file.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load timeline data from.
    /// \param parser Parser to parse timeline data.
    /// \return Loaded timeline.
    static ObjectSharedPtr load(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

protected:

    explicit PropertyFieldAnimationTimeline(Domain* domain) :
        Timeline(domain)
    {
    }

    explicit PropertyFieldAnimationTimeline(Domain* domain, string_view objectPath, AbstractPropertyType propertyType) :
        Timeline(domain),
        m_objectPath(objectPath),
        m_propertyType(propertyType)
    {
    }

    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// Timeline::loadOverride() implementation.
    virtual void loadOverride(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

private:

    string m_objectPath;
    AbstractPropertyType m_propertyType;
    EntryContainer m_entries;
};

}

#endif