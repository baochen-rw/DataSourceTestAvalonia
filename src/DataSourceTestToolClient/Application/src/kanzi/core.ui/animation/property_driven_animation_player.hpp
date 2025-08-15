// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_DRIVEN_ANIMATION_PLAYER_HPP
#define KZ_PROPERTY_DRIVEN_ANIMATION_PLAYER_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node_component/node_component.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

/// Forward declarations.
class Domain;
class TimelinePlayback;
class PropertyDrivenAnimationPlayer;

typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;
typedef shared_ptr<PropertyDrivenAnimationPlayer> PropertyDrivenAnimationPlayerSharedPtr;


/// Use Property Driven Animation Player when you want to use a property type to control a 
/// keyframe animation. 
/// Property Driven Animation Player applies an animation with the time taken from a specific
/// property in the node, to which you attach the player, every time that property changes.
///
/// Property Driven Animation Player applies the timeline specified in the #TimelineProperty
/// property of the player. Kanzi resolves paths to animated objects relative to the node
/// to which you attach the player. All animations in the applied timeline
/// are relative: values calculated in animations are added to property values
/// instead of replacing them.
///
/// The time for the timeline is taken from a property of the node to which you attach the 
/// Property Driven Animation Player. To set the type name of this property, use the
/// #TimeControllerPropertyTypeProperty property of the player. You can use any integer and
/// float properties. Property Driven Animation Player does not support using properties of 
/// other data types.
/// The time calculated from the value of the property depends on its data type:
/// * For float properties, property value 1.0 is interpreted
///   as 1 second. For example, if the value of the time property is 5.5f, the time
///   for the timeline is 5.5 seconds, and so on.
/// * For integer properties, property value 1 is interpreted
///   as 1 millisecond. For example, if the value of the time property is 2300, the
///   time for the timeline is 2.3 seconds, and so on.
///
/// It is recommended to use integer properties as time controllers.
/// Using an integer property enables precise control of the time at which the
/// animations in the timeline are applied. If you use a floating point property
/// as a time controller, the Property Driven Animation Player rounds it to an
/// integer number of milliseconds. In this case the result time, at which the
/// animations in the timeline are applied, is not precise, but you can apply various effects
/// to a floating point time property. For example, smooth interpolation by 
/// PropertyTargetInterpolator.
///
/// Property Driven Animation Player starts to apply animations from the timeline
/// immediately after it is attached to the node. If the time controller property
/// cannot be resolved or if it has an unsupported data type, the player does not apply
/// the timeline. If the time controller property is resolved but is not set to the node,
/// the player calculates the time using the default property value.
///
/// Note that the #TimelineProperty and #TimeControllerPropertyTypeProperty properties
/// are applied only once when you attach the Property Driven Animation Player to the node.
/// New values, which you set to these properties after attaching the player, are ignored.
///
/// \see AnimationPlayer, PropertyTargetInterpolator
///
/// Examples
/// ----
///
/// To create a Property Driven Animation Player and sets its timeline and time controller property:
/// \snippet test_property_driven_animation_player.cpp Create property driven animation player
///
/// To attach a Property Driven Animation Player to a node:
/// \snippet test_property_driven_animation_player.cpp Attach property driven animation player to the node
///
class KANZI_API PropertyDrivenAnimationPlayer : public NodeComponent
{
public:

    /// Sets the animation timeline that the Property Driven Animation Player applies at the time
    /// that is set in the #TimeControllerPropertyTypeProperty property every time the value
    /// of that property changes.
    static PropertyType<ResourceSharedPtr> TimelineProperty;

    /// Sets the type name of the time controller property.
    /// The time controller property can be any property of float or integer type in the node to which
    /// the Property Driven Animation Player is attached. When attached, Property Driven Animation Player
    /// uses the type name to find the time controller property in the node. It then uses the value
    /// of the time controller property to calculate the time at which to apply the animation timeline
    /// set in the #TimelineProperty property.
    static PropertyType<string> TimeControllerPropertyTypeProperty;

    /// Sets whether a Property Driven Animation Player plays animation timelines in a relative manner by
    /// adding the animated value to the target property value instead of replacing the property value.
    /// By default, relative playback is disabled.
    static PropertyType<bool> RelativePlaybackProperty;

    /// Sets whether a Property Driven Animation Player applies the animation timeline. The default value is true.
    /// When you modify the value of the EnabledProperty property in a Property Driven Animation Player that is
    /// attached to a node, the effect is immediate. You do not have to reattach the player.
    static PropertyType<bool> EnabledProperty;

    KZ_METACLASS_BEGIN(PropertyDrivenAnimationPlayer, NodeComponent, "Kanzi.PropertyDrivenAnimationPlayer")
        KZ_METACLASS_PROPERTY_TYPE(TimelineProperty)
        KZ_METACLASS_PROPERTY_TYPE(TimeControllerPropertyTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(RelativePlaybackProperty)
        KZ_METACLASS_PROPERTY_TYPE(EnabledProperty)
    KZ_METACLASS_END()

    /// Returns PropertyType editor info of a Property Driven Animation Player.
    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a Property Driven Animation Player.
    /// \param domain Domain.
    /// \param name Name of the Property Driven Animation Player.
    /// \return Property Driven Animation Player.
    static PropertyDrivenAnimationPlayerSharedPtr create(Domain* domain, string_view name);

    /// Sets an animation timeline to the #TimelineProperty property of the player.
    /// \param animationTimeline timeline.
    void setTimeline(TimelineSharedPtr animationTimeline);

    /// Gets an animation timeline from the #TimelineProperty property of the player.
    /// \return timelime.
    TimelineSharedPtr getTimeline() const;

    /// Sets the value of the #TimeControllerPropertyTypeProperty property of the player.
    /// \param value Name of property type.
    void setTimeControllerPropertyType(string propertyTypeName);

    /// Gets the value of the #TimeControllerPropertyTypeProperty property of the player.
    /// \return Name of property type.
    string getTimeControllerPropertyType() const;

    /// Sets the value of the #RelativePlaybackProperty property.
    /// \param relativePlayback Sets whether the playback is relative.
    void setRelativePlayback(bool relativePlayback);

    /// Gets the value of the #RelativePlaybackProperty property.
    /// \return If the playback is relative, true, otherwise false.
    bool isRelativePlayback() const;

    /// Sets the value of the #EnabledProperty property.
    /// \param enabled Sets whether to apply the animation timeline.
    void setEnabled(bool enabled);

    /// Gets the value of the #EnabledProperty property.
    /// \return If the animation timeline is applied, true, otherwise false.
    bool isEnabled() const;

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name of animation player.
    explicit PropertyDrivenAnimationPlayer(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Notification handler for time property.
    template <typename T>
    static void timeControllerPropertyNoticationHandler(PropertyObject&, const T&, PropertyNotificationReason, void* userData);

    /// Starts playback of an animation timeline assigned to the player through the #TimelineProperty property.
    /// If the playback is running, does nothing.
    void startTimelinePlayback();

    /// Stops ongoing playback of an animation timeline.
    /// If the playback is already stopped, does nothing.
    void stopTimelinePlayback();

    /// Updates timeline playback by time calculated from the time controller property.
    template <typename T>
    void updateTimelinePlaybackTime();

    /// Converts integer number of milliseconds to
    /// chrono duration in milliseconds.
    /// \param milliseconds Number of milliseconds to convert to duration.
    /// \return result duration.
    chrono::milliseconds convertToMilliseconds(int milliseconds);

    /// Converts floating point number of seconds to
    /// chrono duration in milliseconds.
    /// \param seconds Number of seconds to convert to duration.
    /// \return result duration.
    chrono::milliseconds convertToMilliseconds(float seconds);

private:

    /// Currently ongoing timeline playback.
    TimelinePlaybackSharedPtr m_timelinePlayback;

    // Time controller property type.
    AbstractPropertyType m_timeControllerPropertyType;
};

}

#endif
