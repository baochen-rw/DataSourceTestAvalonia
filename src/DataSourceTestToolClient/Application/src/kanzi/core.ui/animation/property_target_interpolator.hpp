// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TARGET_INTERPOLATOR_HPP
#define KZ_PROPERTY_TARGET_INTERPOLATOR_HPP

#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node_component/node_component.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core/message/message_type.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

/// Forward declarations.
class Domain;
class TimelinePlayback;
class PropertyTargetInterpolator;

typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;
typedef shared_ptr<PropertyTargetInterpolator> PropertyTargetInterpolatorSharedPtr;


/// Use a Property Target Interpolator when you want to dynamically set the target value 
/// of a property and want to interpolate the current value to the target value over time.
/// With a Property Target Interpolator you can automatically animate the change of a
/// property value to achieve a smooth transition. Without a Property Target Interpolator
/// Kanzi immediately applies a new value to a property. For example, when you
/// use the Object::setProperty() function, Kanzi immediately applies a new value.
///
/// Use the #InterpolatedPropertyTypeProperty to set the property type that you want
/// the Property Target Interpolator to interpolate in the node to which you attach the Property
/// Target Interpolator.
///
/// Property Target Interpolator emulates the behavior of a spring-damper system which never overshoots. 
/// Use these properties to control the behavior of the interpolation:
/// * #AccelerationProperty sets the force with which the spring moves the object. The larger
///   the value of the Acceleration property is, the faster the property reaches its new value.
/// * #DragProperty sets the damping coefficient. The larger the value of the Drag property is, the lower 
/// is the maximum interpolation speed.
///
/// The Property Target Interpolator applies the #InterpolatedPropertyTypeProperty,
/// #AccelerationProperty, and #DragProperty properties only when you attach the Property 
/// Target Interpolator to a node. You cannot change the target property or interpolation
/// behavior of the Property Target Interpolator by setting the values of these properties after
/// the Property Target Interpolator is already attached to a node.
///
/// \see AnimationPlayer, PropertyDrivenAnimationPlayer
///
/// Examples
/// ----
///
/// To create a Property Target Interpolator and set its target property and interpolation settings:
/// \snippet test_property_target_interpolator.cpp Create property target interpolator
///
/// To attach a Property Target Interpolator to a node:
/// \snippet test_property_target_interpolator.cpp Attach property target interpolator to the node
///
class KANZI_API PropertyTargetInterpolator : public NodeComponent
{
public:

    /// Message arguments for Completed message.
    class CompletedMessageArguments : public NodeComponentSourceMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(CompletedMessageArguments, NodeComponentSourceMessageArguments, "Kanzi.PropertyTargetInterpolator.CompletedMessageArguments")
        KZ_METACLASS_END()
    };

    /// The node to which the Property Target Interpolator is attached sends
    /// the Completed message when the Property Target Interpolator completes the interpolation.  
    static MessageType<CompletedMessageArguments> CompletedMessage;

    /// Sets the property type that you want interpolate with a Property Target Interpolator
    /// in the node to which you attach the Property Target Interpolator. The default value
    /// of this property is "".
    /// \see setInterpolatedPropertyType(), getInterpolatedPropertyType(), InterpolatedPropertyFieldProperty
    static PropertyType<string> InterpolatedPropertyTypeProperty;

    /// Gets the value of the #InterpolatedPropertyTypeProperty.
    /// \see setInterpolatedPropertyType()
    string getInterpolatedPropertyType() const;

    /// Sets the value of the #InterpolatedPropertyTypeProperty.
    /// \see getInterpolatedPropertyType()
    void setInterpolatedPropertyType(string_view value);

    /// Sets the property field of the property type that you want to interpolate with a
    /// Property Target Interpolator. The default value of this property is "".
    /// \see setInterpolatedPropertyField(), getInterpolatedPropertyField(), InterpolatedPropertyTypeProperty
    static PropertyType<KzuPropertyBinaryTargetAttribute> InterpolatedPropertyFieldProperty;

    /// Gets the value of the #InterpolatedPropertyFieldProperty.
    /// \see setInterpolatedPropertyField()
    PropertyField getInterpolatedPropertyField() const;

    /// Sets the value of the #InterpolatedPropertyFieldProperty.
    /// \see getInterpolatedPropertyField()
    void setInterpolatedPropertyField(PropertyField value);

    /// Sets the speed at which the interpolated property reaches its new value.
    /// 
    /// Property Target Interpolator emulates the behavior of a spring-damper system which never overshoots.
    /// The Acceleration property sets the force with which the spring moves the object. The larger the value
    /// of the Acceleration property is, the faster the property reaches its new value. The default value is 1.0f.
    /// \see setAcceleration(), getAcceleration(), DragProperty
    static PropertyType<float> AccelerationProperty;

    /// Gets the value of the #AccelerationProperty.
    /// \see setAcceleration()
    float getAcceleration() const;

    /// Sets the value of the #AccelerationProperty.
    /// \see getAcceleration()
    void setAcceleration(float value);

    /// Controls the maximum interpolation speed.
    ///
    /// Property Target Interpolator emulates the behavior of a spring-damper system which never overshoots.
    /// The Drag property sets the damping coefficient. The larger the value of the Drag property is, 
    /// the lower is the maximum interpolation speed. The default value is 0.0f.
    /// \see setDrag(), getDrag(), AccelerationProperty
    static PropertyType<float> DragProperty;

    /// Gets the value of the #DragProperty.
    /// \see setDrag()
    float getDrag() const;

    /// Sets the value of the #DragProperty.
    /// \see getDrag()
    void setDrag(float value);

    KZ_METACLASS_BEGIN(PropertyTargetInterpolator, NodeComponent, "Kanzi.PropertyTargetInterpolator")
        KZ_METACLASS_PROPERTY_TYPE(InterpolatedPropertyTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(InterpolatedPropertyFieldProperty)
        KZ_METACLASS_PROPERTY_TYPE(AccelerationProperty)
        KZ_METACLASS_PROPERTY_TYPE(DragProperty)

        KZ_METACLASS_MESSAGE_TYPE(CompletedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Creates a Property Target Interpolator.
    /// \param domain Domain.
    /// \param name Name of the Property Target Interpolator.
    /// \return The Property Target Interpolator.
    static PropertyTargetInterpolatorSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name of the Property Target Interpolator.
    explicit PropertyTargetInterpolator(Domain* domain, string_view name);

    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

    /// Sends message about completion of interpolation.
    /// The Property Target Interpolator calls this function when its interpolation completes.
    /// \param playback The Playback of the interpolation which completed.
    void onInterpolationCompleted(TimelinePlayback& playback);

private:

    /// Currently ongoing timeline playback.
    TimelinePlaybackSharedPtr m_timelinePlayback;
};

}

#endif
