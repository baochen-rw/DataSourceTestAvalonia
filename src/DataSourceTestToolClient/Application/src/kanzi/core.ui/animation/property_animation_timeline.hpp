// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_ANIMATION_TIMELINE_HPP
#define KZ_PROPERTY_ANIMATION_TIMELINE_HPP


#include "timeline.hpp"
#include "timeline_playback.hpp"
#include "abstract_animation.hpp"
#include <kanzi/core.ui/animation/value_animation.hpp>


namespace kanzi
{


class PropertyAnimationTimeline;
typedef shared_ptr<PropertyAnimationTimeline> PropertyAnimationTimelineSharedPtr;


/// The Kanzi animation system consists of animations, which define how to animate properties, and
/// timelines, which map animations to time and to the objects that you want to animate.
///
/// Property timeline applies an animation to a property of an object. For example, to change the layout size of an
/// Image2D node, use the property timeline to animate the Node::WidthProperty and Node::HeightProperty properties
/// of that node.
///
/// Examples
/// ----
///
/// To create a property timeline:
/// \snippet test_animation.cpp Create property timeline
///
/// To play an animation regardless of the timeline type:
/// \snippet test_animation.cpp Play animation


class KANZI_API PropertyAnimationTimeline : public Timeline
{
    friend class PropertyAnimationTimelinePlayback;

public:

    KZ_METACLASS_BEGIN(PropertyAnimationTimeline, Timeline, "Kanzi.Animation.PropertyAnimationTimeline")
    KZ_METACLASS_END()

    /// Creates new PropertyAnimationTimeline instance and returns it.
    ///
    /// \param domain Domain.
    /// \param name Name of PropertyAnimationTimeline.
    /// \return New PropertyAnimationTimeline instance.
    static TimelineSharedPtr create(Domain* domain, string_view name);

    /// Creates a PropertyAnimationTimeline instance and returns it.
    ///
    /// \param domain Domain.
    /// \param objectPath Relative path to the node to which to apply the timeline. This path is resolved when creating the playback from the timeline.
    /// \param propertyType The property type to which to apply the timeline animation.
    /// \param animation The animation to apply to the target property.
    /// \return New PropertyAnimationTimeline instance.
    /// \throws invalid_argument if the data types of the target property and animation are not compatible.
    template <typename TPropertyDataType, typename TAnimationDataType>
    static PropertyAnimationTimelineSharedPtr create(Domain* domain, string_view objectPath, const PropertyType<TPropertyDataType>& propertyType,
                                                     shared_ptr<ValueAnimation<TAnimationDataType> > animation)
    {
        return create(domain, objectPath, AbstractPropertyType(propertyType), dynamic_pointer_cast<AbstractAnimation>(animation));
    }

    /// Creates a PropertyAnimationTimeline instance and returns it.
    ///
    /// \param domain Domain.
    /// \param objectPath Relative path to the object to which to apply the timeline. This path is resolved when creating the playback from the timeline.
    /// \param propertyType The property type to which to apply the timeline animation.
    /// \param animation The animation to apply to the target property.
    /// \return New PropertyAnimationTimeline instance.
    /// \throws invalid_argument if the data types of the target property and animation are not compatible.
    static PropertyAnimationTimelineSharedPtr create(Domain* domain, string_view objectPath, AbstractPropertyType propertyType,
                                                     AbstractAnimationSharedPtr animation);

    /// Destructor.
    ~PropertyAnimationTimeline();

    /// Gets the target property type to which the timeline animation is applied.
    ///
    /// \return Target property.
    AbstractPropertyType getPropertyType() const;

    /// Gets the animation that is applied to the target property.
    ///
    /// \return Animation.
    AbstractAnimationSharedPtr getAnimation() const;

    /// Timeline::calculateContentDuration() implementation.
    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;

    /// Loads a timeline from a kzb file.
    ///
    /// \param domain Domain.
    /// \param name The name of the timeline.
    /// \param kzbFile The kzb file from which to load the timeline data.
    /// \param parser The parser for parsing the timeline data.
    /// \return Loaded timeline.
    static ObjectSharedPtr load(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

protected:

    /// Constructor.
    ///
    /// \param domain Domain.
    explicit PropertyAnimationTimeline(Domain* domain);

    /// Constructor.
    ///
    /// \param domain Domain.
    /// \param objectPath Relative path to the object to which to apply the timeline. This path is resolved when creating the playback from the timeline.
    /// \param propertyType The property type to which to apply the timeline animation.
    /// \param animation The animation to apply to the target property.
    explicit PropertyAnimationTimeline(Domain* domain, string_view objectPath, AbstractPropertyType propertyType,
                                       AbstractAnimationSharedPtr animation);

    /// Timeline::createPlaybackOverride() implementation.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// Timeline::loadOverride() implementation.
    virtual void loadOverride(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

private:

    // Relative path to the target node, which is animated.
    // This path is resolved through the timeline playback context when creating the playback.
    string m_objectPath;

    // Type of property on the target node to which the animation is applied.
    AbstractPropertyType m_propertyType;

    // Animation to apply to the target property.
    AbstractAnimationSharedPtr m_animation;
};

}

#endif