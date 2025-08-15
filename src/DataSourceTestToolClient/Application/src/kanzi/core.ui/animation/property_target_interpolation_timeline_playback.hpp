// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TARGET_INTERPOLATION_TIMELINE_PLAYBACK_HPP
#define KZ_PROPERTY_TARGET_INTERPOLATION_TIMELINE_PLAYBACK_HPP

#include "timeline_playback.hpp"
#include "abstract_animation.hpp"

#include <kanzi/core/cpp/array.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core.ui/util/interpolated_value.hpp>


namespace kanzi
{

// Forward declarations.
class PropertyTargetInterpolationTimeline;
typedef shared_ptr<PropertyTargetInterpolationTimeline> PropertyTargetInterpolationTimelineSharedPtr;

class PropertyTargetInterpolationTimelinePlayback;
typedef shared_ptr<PropertyTargetInterpolationTimelinePlayback> PropertyTargetInterpolationTimelinePlaybackSharedPtr;


/// Playback for property target interpolation timeline.
///
/// Note that setting time to this playback or advancing it backwards
/// (calling its tick function with negative delta time) is not supported: negative delta time will be clamped to zero.
class KANZI_API PropertyTargetInterpolationTimelinePlayback : public TimelinePlayback
{
public:

    /// Creates playback.
    /// \param timeline Timeline to play.
    /// \param object Object the property of which should be interpolated.
    /// \return Playback.
    static PropertyTargetInterpolationTimelinePlaybackSharedPtr create(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object);

    /// Creates playback.
    /// \param timeline Timeline to play.
    /// \param context Context for resolving object the property of which should be interpolated.
    /// \return Playback.
    static PropertyTargetInterpolationTimelinePlaybackSharedPtr create(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, TimelinePlaybackContext& context);

    /// Destructor.
    virtual ~PropertyTargetInterpolationTimelinePlayback() KZ_OVERRIDE;

protected:

    /// Constructor.
    /// \param timeline Timeline to play.
    /// \param object Object the property of which should be interpolated.
    explicit PropertyTargetInterpolationTimelinePlayback(PropertyTargetInterpolationTimelineSharedPtr propertyAnimationTimeline, ObjectSharedPtr object);

    /// TimelinePlayback::tickOverride() implementation.
    virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    /// Property modifier callback where interpolation happens.
    /// \param object Object the property of which is modified.
    /// \param currentValue Reference to property value to modify.
    /// \param reason Reason for which the modification is requested.
    /// \param userData User data.
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

    /// TimelinePlayback::onAppliedStateChangedOverride() implementation.
    virtual void onAppliedStateChangedOverride() KZ_OVERRIDE;

private:

    /// Interpolates multiple values.
    class CompoundInterpolatedValue
    {
    public:
        
        /// Creates an interpolated value integrator.
        /// Larger acceleration coefficient leads to faster interpolation, larger drag coefficient lowers maximum speed.
        /// \param startingValues Array of starting values for interpolation.
        /// \param accelerationCoefficient Acceleration coefficient of interpolation.
        /// \param dragCoefficient Drag coefficient of interpolation.
        template <size_t count>
        CompoundInterpolatedValue(const array<float, count> startingValues, float accelerationCoefficient, float dragCoefficient);

        /// Returns current value of the interpolator.
        /// The value is normalized to the allowed range if a looping interpolator is used.
        /// \return Array of current values of interpolation.
        template <size_t count>
        array<float, count> getValue() const;

        /// Sets current value of the interpolator.
        /// \param value Array of new current values for interpolation.
        /// \param resetInterpolation If true, sets target to the new value and resets speed.
        template <size_t count>
        void setValue(const array<float, count> values, bool resetInterpolation);

        /// Integrates simulation for 'timeDelta' milliseconds.
        /// \param timeDelta Time delta for advancing interpolation.
        void update(chrono::milliseconds timeDelta);

        /// Returns true if interpolation has ended for now, i.e. target reached and speed close to zero.
        /// \return True if interpolation has ended, false otherwise.
        bool interpolationEnded() const;

        /// Sets target value of the interpolator.
        /// If the interpolator is looping, the target value may be out bounds to indicate direction and repetition.
        /// \param targets Array of new target values for interpolation.
        template <size_t count>
        void setTarget(const array<float, count>& targets);

    private:

        /// Interpolated values.
        vector<InterpolatedValue> m_interpolatedValues;
    };

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

    /// Object whose property is interpolated.
    weak_ptr<Object> m_object;

    /// Indicates whether modifier callback is installed to property.
    CallbackState m_callbackState;

    /// Interpolated value of the property.
    unique_ptr<CompoundInterpolatedValue> m_interpolatedValue;
};

}

#endif
