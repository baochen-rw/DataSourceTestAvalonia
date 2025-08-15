// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PINCH_MANIPULATOR_HPP
#define KZ_PINCH_MANIPULATOR_HPP


#include <kanzi/core.ui/input/input_manipulator.hpp>


namespace kanzi
{


class PinchManipulator;

typedef shared_ptr<PinchManipulator> PinchManipulatorSharedPtr;


/// Pinch input manipulator recognizes the pinch gesture from incoming touch events. It generates the required messages to 
/// implement the logic for objects which react to the pinch gesture. For example, use the pinch input manipulator to zoom in
/// or zoom out a map using the pinch gesture.
///
/// \see ClickManipulator, DragAndDropManipulator, LongPressManipulator, MultiClickManipulator, PanManipulator
///
/// Examples:
/// ---
///
/// To receive the pinch update events, add message handler for the MovedMessage message.
///
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Pinch moved message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe pinch moved
class KANZI_API PinchManipulator : public InputManipulator
{
public:
    /// Message arguments for pinch gesture started message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API StartedMessageArguments : public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StartedMessageArguments, InputMessageArguments, "Kanzi.PinchManipulator.StartedMessageArguments")
        KZ_METACLASS_END()
    };
    
    /// Message arguments for moved message sent during pan gesture. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API MovedMessageArguments : public InputMessageArguments
    {
    public:

#include "pinch_manipulator_properties.h"

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(MovedMessageArguments, InputMessageArguments, "Kanzi.PinchManipulator.MovedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(PinchScaleProperty)
            KZ_METACLASS_PROPERTY_TYPE(PinchRotationProperty)
        KZ_METACLASS_END()

        /// The scale value recognized from the pinch gesture.
        float getScale() const { return getArgument(PinchScaleProperty); };
        void setScale(float value) { setArgument(PinchScaleProperty, value); };

        /// The rotation value recognized from the pinch gesture.
        float getRotation() const { return getArgument(PinchRotationProperty); };
        void setRotation(float value) { setArgument(PinchRotationProperty, value); };

		static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };
    
    /// Message arguments for pinch gesture finished message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API FinishedMessageArguments : public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(FinishedMessageArguments, InputMessageArguments, "Kanzi.PinchManipulator.FinishedMessageArguments")
        KZ_METACLASS_END()
    };
    
    /// Message type for notifying start of the pinch gesture.
    /// StartedMessage is generated when touch is pressed or arrives to the attached node area.
    static MessageType<StartedMessageArguments> StartedMessage;
    /// Message type for notifying scale and rotation updates during pinch gesture.
    /// MovedMessage is sent first when the scale or rotation threshold is exceeded and after that when the tracked touches have moved between updates.
    static MessageType<MovedMessageArguments> MovedMessage;
    /// Message type for notifying completion of the pinch gesture.
    /// FinishedMessage is sent when the tracked touches are released or the gesture is canceled.
    static MessageType<FinishedMessageArguments> FinishedMessage;

    KZ_METACLASS_BEGIN(PinchManipulator, InputManipulator, "Kanzi.PinchManipulator")
        KZ_METACLASS_MESSAGE_TYPE(StartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(MovedMessage)
        KZ_METACLASS_MESSAGE_TYPE(FinishedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static PinchManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new PinchManipulator(domain));
    }

    /// Set the threshold the fingers have to move away from each other before scale is recognized. The default value is 5 screen units.
    void setScaleRecognitionThreshold(float threshold);
    /// Set the threshold the fingers have to rotate around the midpoint before rotation is recognized. The default value is 5 screen units along the circle.
    void setRotationRecognitionThreshold(float threshold);

protected:

    /// Constructor.
    explicit PinchManipulator(Domain* domain);

    /// Touch inside implementation for pinch manipulator.
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// Touch outside implementation for pinch manipulator.
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// Reset implementation for pinch input manipulator.
    virtual void onReset() KZ_OVERRIDE;

    /// Update the state of the pinch gesture with the new touch event
    void trackPinch(const TouchInfo& touchInfo);

public:
    /// Scale threshold.
    float m_scaleThreshold;
    /// Rotate threshold.
    float m_rotateThreshold;
    /// First touch ID.
    unsigned int m_touchIdA;
    /// Second touch ID.
    unsigned int m_touchIdB;
    /// Is scaling.
    bool m_scaling;
    /// Is rotating.
    bool m_rotating;
    /// Reference direction vector for the difference between the touch points.
    Vector2 m_normalizedReferenceVector;
    /// Reference scale of the difference between the touch points.
    float m_referenceScale;
};

}

#endif
