// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_FIELD_ANIMATION_TIMELINE_PLAYBACK_HPP
#define KZ_PROPERTY_FIELD_ANIMATION_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"
#include "abstract_animation.hpp"


namespace kanzi
{


class PropertyFieldAnimationTimeline;
typedef shared_ptr<PropertyFieldAnimationTimeline> PropertyFieldAnimationTimelineSharedPtr;

class PropertyFieldAnimationTimelinePlayback;
typedef shared_ptr<PropertyFieldAnimationTimelinePlayback> PropertyFieldAnimationTimelinePlaybackSharedPtr;

/// Playback control for PropertyFieldAnimationTimeline.
class KANZI_API PropertyFieldAnimationTimelinePlayback : public TimelinePlayback
{
public:

    static PropertyFieldAnimationTimelinePlaybackSharedPtr create(PropertyFieldAnimationTimelineSharedPtr propertyFieldAnimationTimeline, ObjectSharedPtr object, bool relativePlayback);
    static PropertyFieldAnimationTimelinePlaybackSharedPtr create(PropertyFieldAnimationTimelineSharedPtr propertyFieldAnimationTimeline, TimelinePlaybackContext& context);

    virtual ~PropertyFieldAnimationTimelinePlayback() KZ_OVERRIDE;

protected:

    template <typename T>
    static void modifierCallback(PropertyObject& object, T& currentValue, PropertyNotificationReason reason, void* userData);

    void modifyAnimatedProperty(ColorRGBA& currentValue, PropertyNotificationReason reason);

    void modifyAnimatedProperty(Vector2& currentValue, PropertyNotificationReason reason);

    void modifyAnimatedProperty(Vector3& currentValue, PropertyNotificationReason reason);

    void modifyAnimatedProperty(Vector4& currentValue, PropertyNotificationReason reason);

    void modifyAnimatedProperty(SRTValue3D& currentValue, PropertyNotificationReason reason);

    void modifyAnimatedProperty(SRTValue2D& currentValue, PropertyNotificationReason reason);

    template <typename T>
    void installModifier();

    void installModifier();

    template <typename T>
    void uninstallModifier();

    void uninstallModifier();

    void forgetModifier();

    explicit PropertyFieldAnimationTimelinePlayback(PropertyFieldAnimationTimelineSharedPtr propertyFieldAnimationTimeline, ObjectSharedPtr object, bool relative);

    /// Applies timeline animations at playback's content time.
    void applyAnimations();

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

    /// TimelinePlayback::onAppliedStateChangedOverride() implementation.
    virtual void onAppliedStateChangedOverride() KZ_OVERRIDE;

private:

    PropertyFieldAnimationTimelineSharedPtr m_propertyFieldAnimationTimeline;
    bool m_objectAssigned;
    weak_ptr<Object> m_object;
    bool m_callbackInstalled;
    bool m_relative;
};

}

#endif