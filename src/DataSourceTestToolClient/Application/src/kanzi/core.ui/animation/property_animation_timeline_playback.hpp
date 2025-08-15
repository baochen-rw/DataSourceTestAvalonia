// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_ANIMATION_TIMELINE_PLAYBACK_HPP
#define KZ_PROPERTY_ANIMATION_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"
#include "abstract_animation.hpp"


namespace kanzi
{

// Forward declarations.
class PropertyAnimationTimeline;
typedef shared_ptr<PropertyAnimationTimeline> PropertyAnimationTimelineSharedPtr;

class PropertyAnimationTimelinePlayback;
typedef shared_ptr<PropertyAnimationTimelinePlayback> PropertyAnimationTimelinePlaybackSharedPtr;


/// Playback class for PropertyAnimationTimeline.
class KANZI_API PropertyAnimationTimelinePlayback : public TimelinePlayback
{
public:

    /// Creates a PropertyAnimationTimelinePlayback instance from specified timeline and returns it.
    ///
    /// \param propertyAnimationTimeline Property animation timeline from which to create the playback.
    /// \param object Target object the property of which to animate.
    /// \param relativePlayback Flag indicating whether playback should be relative or not.
    /// \return The created playback.
    static PropertyAnimationTimelinePlaybackSharedPtr create(PropertyAnimationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object, bool relativePlayback);

    /// Creates a PropertyAnimationTimelinePlayback instance from specified timeline and returns it.
    ///
    /// \param propertyAnimationTimeline Property animation timeline from which to create the playback.
    /// \param context Context used to resolve the path of the timeline to the target object to the actual object.
    /// \return The created playback.
    static PropertyAnimationTimelinePlaybackSharedPtr create(PropertyAnimationTimelineSharedPtr propertyAnimationTimeline, TimelinePlaybackContext& context);

    /// Destructor.
    ~PropertyAnimationTimelinePlayback();

    /// Indicates whether the specified animation can be applied to a property of the specified property type.
    ///
    /// \param propertyType Property type to check.
    /// \param animation Animation to check.
    /// \return If animation can be applied to property type, true, false otherwise.
    static bool isCompatible(AbstractPropertyType& propertyType, AbstractAnimation& animation);

protected:

    /// Modifier callback function for target property.
    template <typename TPropertyDataType>
    static void modifierCallback(PropertyObject& object, TPropertyDataType& currentValue, PropertyNotificationReason reason, void* userData);

    /// Modifier callback function for target property.
    template <typename TPropertyDataType, typename TAnimationDataType>
    static void modifierCallback(PropertyObject& object, TPropertyDataType& currentValue, PropertyNotificationReason reason, void* userData);

    /// Modifies value of target property.
    ///
    /// \param currentValue Property value to modify.
    /// \param reason Reason for modifying the value.
    template <typename TPropertyDataType>
    void modifyAnimatedProperty(TPropertyDataType& currentValue, PropertyNotificationReason reason);

    /// Modifies value of target property.
    ///
    /// \param currentValue Property value to modify.
    /// \param reason Reason for modifying the value.
    template <typename TPropertyDataType, typename TAnimationDataType>
    void modifyAnimatedProperty(TPropertyDataType& currentValue, PropertyNotificationReason reason);

    /// Installs modifier to target property.
    void installModifier();

    /// Installs modifier to target property.
    template <typename TPropertyDataType>
    void installModifier();

    /// Installs modifier to target property.
    template <typename TPropertyDataType, typename TAnimationDataType>
    void installModifier();

    /// Uninstalls modifier from target property.
    void uninstallModifier();

    /// Uninstalls modifier from target property.
    template <typename TPropertyDataType>
    void uninstallModifier();

    /// Uninstalls modifier from target property.
    template <typename TPropertyDataType, typename TAnimationDataType>
    void uninstallModifier();

    /// Forgets property modifier installed on target property. For example, use this when the modifier is removed from the property elsewhere.
    void forgetModifier();

    /// Constructor.
    ///
    /// \param propertyAnimationTimeline Property animation timeline from which to create the playback.
    /// \param object Target object the property of which to animate.
    /// \param relative Flag indicating whether playback should be relative or not.
    explicit PropertyAnimationTimelinePlayback(PropertyAnimationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object, bool relative);

    /// Applies timeline animation at playback's content time.
    void applyAnimation();

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

    /// TimelinePlayback::onAppliedStateChangedOverride() implementation.
    virtual void onAppliedStateChangedOverride() KZ_OVERRIDE;

private:

    /// Timeline of the playback.
    PropertyAnimationTimelineSharedPtr m_propertyAnimationTimeline;

    /// Flag indicating whether target object is found and assigned to playback.
    bool m_objectAssigned;

    /// Target object.
    weak_ptr<Object> m_object;

    /// Flag indicating whether modifier is installed to the target property.
    bool m_callbackInstalled;

    /// Flag indicating whether playback is relative.
    bool m_relative;
};

}

#endif