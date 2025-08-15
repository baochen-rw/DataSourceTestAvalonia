// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_FIELD_TARGET_INTERPOLATION_TIMELINE_PLAYBACK_HPP
#define KZ_PROPERTY_FIELD_TARGET_INTERPOLATION_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"
#include "abstract_animation.hpp"

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core.ui/util/interpolated_value.hpp>


namespace kanzi
{

// Forward declarations.
class PropertyTargetInterpolationTimeline;
typedef shared_ptr<PropertyTargetInterpolationTimeline> PropertyTargetInterpolationTimelineSharedPtr;

class PropertyFieldTargetInterpolationTimelinePlayback;
typedef shared_ptr<PropertyFieldTargetInterpolationTimelinePlayback> PropertyFieldTargetInterpolationTimelinePlaybackSharedPtr;


/// Playback for property target interpolation timeline for interpolating specific property field.
///
/// Note that setting time to this playback or advancing it backwards
/// (calling its tick function with negative delta time) is not supported: negative delta time will be clamped to zero.
class KANZI_API PropertyFieldTargetInterpolationTimelinePlayback : public TimelinePlayback
{
public:

    /// Creates playback.
    /// \param timeline Timeline to play.
    /// \param object Object the property of which should be interpolated.
    /// \return Playback.
    static PropertyFieldTargetInterpolationTimelinePlaybackSharedPtr create(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object);

    /// Creates playback.
    /// \param timeline Timeline to play.
    /// \param context Context for resolving object the property of which should be interpolated.
    /// \return Playback.
    static PropertyFieldTargetInterpolationTimelinePlaybackSharedPtr create(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, TimelinePlaybackContext& context);

    /// Destructor.
    virtual ~PropertyFieldTargetInterpolationTimelinePlayback() KZ_OVERRIDE;

protected:

    /// Constructor.
    /// \param timeline Timeline to play.
    /// \param object Object the property of which should be interpolated.
    explicit PropertyFieldTargetInterpolationTimelinePlayback(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object);

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// Property modifier callback where interpolation happens.
    template <typename T>
    static void modifierCallback(PropertyObject& object, T& currentValue, PropertyNotificationReason reason, void* userData);

    /// Modifies property value.
    /// \param currentValue Reference to value to modify.
    /// \param reason Reason for which the modification is requested.
    template <typename T>
    void modifyPropertyValue(T& currentValue, PropertyNotificationReason reason);

    /// Modifies value.
    /// \param currentValue Reference to value to modify.
    template <typename T>
    void modifyValue(T& currentValue);

    /// Installs modifier to property the value of which should be interpolated.
    void installModifier();

    /// Installs interpolation modifier to property of specific type.
    template <typename T>
    void installModifier();

    /// Uninstalls interpolation modifier from property.
    void uninstallModifier();

    /// Uninstalls interpolation modifier from property of specific type.
    template <typename T>
    void uninstallModifier();

    /// Forgets modifier if it is removed from property from outside of playback (i.e. when target property is deleted).
    void forgetModifier();

    /// TimelinePlayback::onProgressTimeResetOverride() implementation.
    virtual void onProgressTimeResetOverride() KZ_OVERRIDE;

private:

    /// State of property modifier callback.
    enum CallbackState
    {
        /// Callback has not been installed yet.
        CallbackStateNotInstalled,
        /// Callback has been successfully installed.
        CallbackStateInstalled,
        /// The last attempt to install callback has failed.
        CallbackInstallationFailed
    };

    /// Timeline being played.
    PropertyTargetInterpolationTimelineSharedPtr m_timeline;

    /// Object the property of which is interpolated.
    weak_ptr<Object> m_object;

    /// Indicates whether modifier callback is installed to property.
    CallbackState m_callbackState;

    /// Interpolated value of the property.
    unique_ptr<InterpolatedValue> m_interpolatedValue;
};

}

#endif
