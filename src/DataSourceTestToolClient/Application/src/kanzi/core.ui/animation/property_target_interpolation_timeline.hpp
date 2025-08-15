// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TARGET_INTERPOLATION_TIMELINE_HPP
#define KZ_PROPERTY_TARGET_INTERPOLATION_TIMELINE_HPP


#include "timeline.hpp"
#include "timeline_playback.hpp"
#include <kanzi/core/cpp/string.hpp>


namespace kanzi
{

class PropertyTargetInterpolationTimeline;
typedef shared_ptr<PropertyTargetInterpolationTimeline> PropertyTargetInterpolationTimelineSharedPtr;


/// Property target interpolation timeline is a timeline that gradually interpolates
/// specified property from its old value to new one each time new value is set to the property.
/// Timeline interpolates property of specified type on the object specified by its path.
///
/// Interpolation of the property value is done by emulating behavior of
/// critically damped harmonic oscillator. The behavior of interpolation is controlled
/// by acceleration and drag coefficients:
/// * Acceleration specifies how fast interpolation will be done from old property value
///   to new one. Larger acceleration leads to faster reaching new property value.
/// * Drag affects the maximum speed of interpolation. Larger drag lowers
///   maximum speed of interpolation.
///
/// Note that setting time to playback of this timeline or advancing it in reverse direction is not supported.
///
/// Examples
/// ----
///
/// To create property target interpolation timeline and set its target property and interpolation settings:
/// \snippet test_property_target_interpolation_timeline.cpp Create property target interpolation timeline
///
/// To create playback for property target interpolation timeline:
/// \snippet test_property_target_interpolation_timeline.cpp Create property target interpolation timeline playback
///
/// To add playback of property target interpolation timeline to the clock:
/// \snippet test_property_target_interpolation_timeline.cpp Add property target interpolation timeline playback to the clock
///
class KANZI_API PropertyTargetInterpolationTimeline : public Timeline
{
public:

    /// Creates property target interpolation timeline.
    /// \param domain Domain.
    /// \param objectPath Path to object the property of which should be interpolated.
    /// \param interpolatedPropertyType Type of property the value of which should be interpolated.
    /// \param interpolatedPropertyField Field of property the value of which should be interpolated.
    /// \param acceleration Acceleration coefficient of interpolation.
    /// \param drag Drag coefficient of interpolation.
    static PropertyTargetInterpolationTimelineSharedPtr create(Domain* domain, string_view objectPath, AbstractPropertyType interpolatedPropertyType,
                                                               PropertyField interpolatedPropertyField, float acceleration, float drag)
    {
        PropertyTargetInterpolationTimelineSharedPtr timeline(new PropertyTargetInterpolationTimeline(domain, objectPath, interpolatedPropertyType,
                                                                                                      interpolatedPropertyField, acceleration, drag));

        return timeline;
    }

    /// Creates property target interpolation timeline with default interpolation parameter values.
    /// Default value for acceleration is 1.0, default value for drag is 0.0.
    /// \param domain Domain.
    /// \param objectPath Path to object the property of which should be interpolated.
    /// \param interpolatedPropertyType Type of property the value of which should be interpolated.
    /// \param interpolatedPropertyField Field of property the value of which should be interpolated.
    static PropertyTargetInterpolationTimelineSharedPtr create(Domain* domain, string_view objectPath, AbstractPropertyType interpolatedPropertyType,
                                                               PropertyField interpolatedPropertyField)
    {
        return create(domain, objectPath, interpolatedPropertyType, interpolatedPropertyField, 1.0f, 0.0f);
    }

    /// Gets path to object the property of which should be interpolated.
    /// \return Object path.
    string getObjectPath() const
    {
        return m_objectPath;
    }

    /// Gets the type of property the value of which should be interpolated.
    /// \return Property type.
    AbstractPropertyType getInterpolatedPropertyType() const
    {
        return m_interpolatedPropertyType;
    }

    /// Gets the field of property the value of which should be interpolated.
    /// \return Property field.
    PropertyField getInterpolatedPropertyField() const
    {
        return m_interpolatedPropertyField;
    }

    /// Sets acceleration coefficient of interpolation.
    /// \param acceleration Acceleration coefficient of interpolation.
    void setAcceleration(float acceleration)
    {
        m_acceleration = acceleration;
    }

    /// Gets acceleration coefficient of interpolation.
    /// \return Acceleration coefficient of interpolation.
    float getAcceleration() const
    {
        return m_acceleration;
    }

    /// Sets drag coefficient of interpolation.
    /// \param drag Drag coefficient of interpolation.
    void setDrag(float drag)
    {
        m_drag = drag;
    }

    /// Gets drag coefficient of interpolation.
    /// \return Drag coefficient of interpolation.
    float getDrag() const
    {
        return m_drag;
    }

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param objectPath Path to object the property of which should be interpolated.
    /// \param interpolatedPropertyType Type of property the value of which should be interpolated.
    /// \param interpolatedPropertyField Field of property the value of which should be interpolated.
    /// \param acceleration Acceleration coefficient of interpolation.
    /// \param drag Drag coefficient of interpolation.
    explicit PropertyTargetInterpolationTimeline(Domain* domain, string_view objectPath, AbstractPropertyType interpolatedPropertyType,
                                                 PropertyField interpolatedPropertyField, float acceleration, float drag) :
        Timeline(domain),
        m_objectPath(objectPath),
        m_interpolatedPropertyType(interpolatedPropertyType),
        m_interpolatedPropertyField(interpolatedPropertyField),
        m_acceleration(acceleration),
        m_drag(drag)
    {
    }

    /// Timeline::createPlaybackOverride() implementation.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// Timeline::calculateContentDuration() implementation.
    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;

private:

    /// Path to object the property of which should be interpolated.
    string m_objectPath;
    /// Type of property the value of which should be interpolated.
    AbstractPropertyType m_interpolatedPropertyType;
    /// Field of property the value of which should be interpolated.
    PropertyField m_interpolatedPropertyField;
    /// Acceleration coefficient of interpolation.
    float m_acceleration;
    /// Drag coefficient of interpolation.
    float m_drag;
};

}

#endif
